#!/usr/bin/env python3
"""Check the published IN/OUT Mach-O. Runs on Linux and on the macOS Actions runner.

Does not launch the device binary in Simulator. Does not print redacted secrets.
"""

from __future__ import annotations

import hashlib
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / "bin" / "IN-OUT"
BASE = 0x100000000
EXPECTED_SHA256 = "11b0cf24cb5beabcc440ab1b54ba8886aee25b9e6caf686009397289d8b3b4a5"
EXPECTED_SIZE = 6379760

BRANCHES = {
    0x100071B20: 0x1000541DC,
    0x100028500: 0x100027B88,
    0x100048F9C: 0x10003CDD8,
    0x1000BA040: 0x1000B2154,
    0x1000C0280: 0x1000BC9B8,
}

FAILS: list[str] = []


def check(cond: bool, msg: str) -> None:
    print(("ok  " if cond else "FAIL") + " " + msg)
    if not cond:
        FAILS.append(msg)


def uleb(buf: bytes, i: int) -> tuple[int, int]:
    value = 0
    shift = 0
    while True:
        b = buf[i]
        i += 1
        value |= (b & 0x7F) << shift
        if b < 0x80:
            return value, i
        shift += 7


def load_commands(data: bytes):
    magic, cputype, _, filetype, ncmds, _, _, _ = struct.unpack_from("<IIIIIIII", data, 0)
    off = 32
    cmds = []
    for _ in range(ncmds):
        cmd, cmdsize = struct.unpack_from("<II", data, off)
        cmds.append((cmd, cmdsize, off))
        off += cmdsize
    return magic, cputype, filetype, cmds


def branch_target(word: int, pc: int) -> int | None:
    if (word >> 26) not in (0b000101, 0b100101):
        return None
    imm = word & 0x3FFFFFF
    if imm & 0x2000000:
        imm -= 0x4000000
    return pc + imm * 4


def main() -> int:
    data = BIN.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    print(f"path {BIN}")
    print(f"size {len(data)}")
    print(f"sha256 {digest}")
    check(len(data) == EXPECTED_SIZE, f"size {EXPECTED_SIZE}")
    check(digest == EXPECTED_SHA256, "sha256 matches the reviewed redacted binary")

    magic, cputype, filetype, cmds = load_commands(data)
    check(magic == 0xFEEDFACF, "MH_MAGIC_64")
    check(cputype == 0x100000C, "CPU_TYPE_ARM64")
    check(filetype == 2, "MH_EXECUTE")

    sig = None
    fs = None
    fix = None
    sym = None
    for cmd, cmdsize, off in cmds:
        if cmd == 0x1D:
            sig = struct.unpack_from("<II", data, off + 8)
        elif cmd == 0x26:
            fs = struct.unpack_from("<II", data, off + 8)
        elif cmd == 0x80000034:
            fix = struct.unpack_from("<II", data, off + 8)
        elif cmd == 0x2:
            sym = struct.unpack_from("<IIII", data, off + 8)
    check(sig == (0, 0), "LC_CODE_SIGNATURE cleared")
    check(fs is not None and sym is not None and fix is not None, "function starts, symtab, chained fixups present")

    blob = data[fs[0] : fs[0] + fs[1]]
    funcs = []
    addr = 0
    i = 0
    while i < len(blob) and blob[i] != 0:
        delta, i = uleb(blob, i)
        addr += delta
        funcs.append(addr)
    check(len(funcs) == 15672, f"LC_FUNCTION_STARTS count {len(funcs)}")

    symoff, nsyms, stroff, strsize = sym
    defined = []
    for n in range(nsyms):
        n_strx, n_type, _, _, n_value = struct.unpack_from("<IBBHQ", data, symoff + n * 16)
        name = data[stroff + n_strx : stroff + strsize].split(b"\0", 1)[0]
        if n_type == 0x0F:
            defined.append((n_value, name))
    check(defined == [(BASE, b"__mh_execute_header")], "only defined symbol is __mh_execute_header")

    fo, _fsz = fix
    hdr = struct.unpack_from("<7I", data, fo)
    starts = fo + hdr[1]
    seg_count = struct.unpack_from("<I", data, starts)[0]
    seg_offs = struct.unpack_from("<" + str(seg_count) + "I", data, starts + 4)
    formats = []
    for off in seg_offs:
        if off == 0:
            continue
        seg = starts + off
        _size, _page, pointer_format = struct.unpack_from("<IHH", data, seg)
        formats.append(pointer_format)
    print("chained pointer formats", formats)
    check(formats == [6, 6], "chained fixups are DYLD_CHAINED_PTR_64_OFFSET (format 6)")

    for src, dst in BRANCHES.items():
        word = struct.unpack_from("<I", data, src - BASE)[0]
        got = branch_target(word, src)
        check(got == dst, f"B at {src:#x} -> {got:#x} expected {dst:#x}")

    fn = data[0xDA43C:0xDA574]
    imms = []
    for i in range(0, len(fn) - 3, 4):
        word = struct.unpack_from("<I", fn, i)[0]
        if (word & 0x7F800000) == 0x52800000:
            imm = (word >> 5) & 0xFFFF
            if imm in (0x168, 0x2D, 0x1E0, 0x3C):
                imms.append(imm)
    check(imms == [0x168, 0x2D, 0x1E0, 0x3C], f"legal break movz immediates {imms}")
    pool = struct.unpack_from("<4q", data, 0x42D680)
    check(pool == (1320, 300, 480, 25), f"premium constant pool {pool}")
    check_week_shift(data)

    check(re.search(rb"ca-app-pub-[0-9]{16}/[0-9]{10}", data) is None, "no ad unit id")
    check(
        re.search(rb"[A-Za-z0-9._%+\-]{1,64}@[A-Za-z0-9.\-]{1,255}\.[A-Za-z]{2,24}", data) is None,
        "no email address",
    )
    check(b"embedded.mobileprovision" not in data, "no provisioning profile name")
    check(b"BEGIN PRIVATE KEY" not in data and b"BEGIN RSA" not in data, "no private key pem")

    print("device IPA is not launched in Simulator")
    macos_tools()
    if FAILS:
        print(f"{len(FAILS)} checks failed")
        return 1
    print("all checks passed")
    return 0


WEEK_WORDS = {
    0x2049C0: 0xAA0003F9,  # mov x25, x0
    0x204B40: 0xF945DD08,  # ldr x8, [x8, #0xbb8]  Component.day
    0x204B68: 0xD37DF328,  # lsl x8, x25, #3
    0x204B6C: 0xCB190118,  # sub x24, x8, x25
    0x204B70: 0x528000E8,  # mov w8, #7
    0x204B74: 0x9B487F28,  # smulh x8, x25, x8
    0x204BE4: 0xAA1803E1,  # mov x1, x24
    0x204BEC: 0x52800003,  # mov w3, #0
    0x204BF0: 0x9407E0B1,  # bl date(byAdding:)
    0x204C68: 0xF100011F,  # cmp x8, #0
    0x204C6C: 0x52800068,  # mov w8, #3
    0x204C70: 0x1A9FC508,  # csinc w8, w8, wzr, gt
    0x204ECC: 0xD4200020,  # brk #1
}


def week_slide_tag(weeks: int) -> int:
    return 3 if weeks > 0 else 1


def check_week_shift(data: bytes) -> None:
    for off, word in WEEK_WORDS.items():
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"week-shift word at {off:#x}")
    bl = struct.unpack_from("<I", data, 0x204BF0)[0]
    target = branch_target(bl, 0x100204BF0)
    check(target == 0x1003FCEB4, f"week-shift calls date(byAdding:) at {target:#x}")
    for weeks, days, tag in ((0, 0, 1), (1, 7, 3), (-1, -7, 1), (2, 14, 3), (-3, -21, 1)):
        check(weeks * 7 == days and week_slide_tag(weeks) == tag, f"week {weeks} -> {days} days tag {tag}")
    check_break_selection(data)


BREAK_WORDS = {
    0xE9770: 0xEB0B013F,  # cmp x9, x11
    0xE9774: 0x540000AB,  # b.lt keep
    0xE9904: 0xEB08013F,  # cmp x9, x8
    0xE9908: 0x54FFFF2A,  # b.ge keep earlier
    0xE9898: 0xB9801A68,  # ldrsw x8, [x19, #0x18]
    0xE98B4: 0xD2800013,  # mov x19, #0
    0x1CF41C: 0xD2E809C8,  # mov x8, #0x404e000000000000
    0x1CF424: 0x1E601908,  # fdiv d8, d8, d0
    0x1CF700: 0x9E780113,  # fcvtzs x19, d8
    0x1CF714: 0x7100051F,  # cmp w8, #1
    0x1CF764: 0x97FC67C6,  # bl break selector
}


def selected_break_minutes(minutes: int, rules: list[tuple[int, int]]) -> int:
    best = None
    for over, brk in rules:
        if over < minutes and (best is None or best[0] < over):
            best = (over, brk)
    return 0 if best is None else best[1]


def check_break_selection(data: bytes) -> None:
    for off, word in BREAK_WORDS.items():
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"break-select word at {off:#x}")
    bl = struct.unpack_from("<I", data, 0x1CF764)[0]
    target = branch_target(bl, 0x1001CF764)
    check(target == 0x1000E967C, f"duration caller reaches selector at {target:#x}")
    sixty = struct.unpack("<d", struct.pack("<Q", 0x404E000000000000))[0]
    check(sixty == 60.0, "caller divides the time interval by 60")
    legal = [(360, 45), (480, 60)]
    cases = [
        (360, legal, 0),
        (361, legal, 45),
        (480, legal, 45),
        (481, legal, 60),
        (0, legal, 0),
        (-1, legal, 0),
        (100, [(0, 15), (360, 45)], 15),
        (400, [(100, 10), (360, 45), (480, 60)], 45),
        (101, [(100, 10), (100, 99)], 10),
        (50, [], 0),
    ]
    for minutes, rules, expect in cases:
        got = selected_break_minutes(minutes, rules)
        check(got == expect, f"break {minutes} {rules} -> {got} expected {expect}")
    bl = struct.unpack_from("<I", data, 0x1B8A44)[0]
    target = branch_target(bl, 0x1001B8A44)
    check(target == 0x1000E967C, f"editor caller reaches selector at {target:#x}")
    for off, word in ((0x1B8870, 0xEB08033A), (0x1B8A3C, 0x9A880120), (0x1B8818, 0xB9802C08), (0x1B8850, 0xB9802AE8)):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"editor-minute word at {off:#x}")
    for start, end, expect in ((540, 1020, 480), (1320, 360, 480), (100, 100, 1440), (100, 99, 1439), (0, 1, 1)):
        got = editor_minute_count(start, end)
        check(got == expect, f"editor {start}->{end} = {got} expected {expect}")
    for seconds, expect in ((3599.9, 59), (3600.0, 60), (60.0, 1), (59.9, 0), (-1.0, 0), (-119.0, -1)):
        got = int(seconds / 60.0)  # toward zero, matching fcvtzs
        check(got == expect, f"trunc {seconds}s -> {got} expected {expect}")


def editor_minute_count(start: int, end: int) -> int:
    difference = end - start
    remainder = difference % 1440
    if remainder < 0:
        remainder += 1440
    return 1440 if remainder == 0 else remainder


def macos_tools() -> None:
    if not Path("/usr/bin/sw_vers").exists():
        print("macOS tools skipped (not macOS)")
        return
    sw = subprocess.run(["sw_vers"], text=True, capture_output=True)
    print(sw.stdout.strip())
    demangle = shutil.which("swift-demangle") or shutil.which("xcrun")
    names = []
    for line in (ROOT / "symbols" / "swiftui-view.txt").read_text().splitlines():
        if line.startswith("_$"):
            names.append(line.strip())
    if shutil.which("swift-demangle"):
        proc = subprocess.run(["swift-demangle", *names], text=True, capture_output=True)
        print(proc.stdout.strip())
        check(proc.returncode == 0, "swift-demangle")
    else:
        proc = subprocess.run(["xcrun", "swift-demangle", *names], text=True, capture_output=True)
        print((proc.stdout or proc.stderr).strip()[:2000])
        check(proc.returncode == 0, "xcrun swift-demangle")
    sdk = subprocess.run(
        ["xcrun", "--sdk", "iphoneos", "--show-sdk-path"], text=True, capture_output=True
    )
    print("iphoneos sdk", (sdk.stdout or sdk.stderr).strip())
    check(sdk.returncode == 0, "iphoneos SDK path")
    if sdk.returncode == 0:
        swiftui = Path(sdk.stdout.strip()) / "System/Library/Frameworks/SwiftUI.framework"
        print("SwiftUI.framework", swiftui, "exists" if swiftui.exists() else "missing")
        check(swiftui.exists(), "SDK SwiftUI.framework exists")
    dyld = shutil.which("dyld_info")
    if dyld:
        proc = subprocess.run([dyld, "-fixup_chains", str(BIN)], text=True, capture_output=True)
        text = (proc.stdout or "") + (proc.stderr or "")
        print("\n".join(text.splitlines()[:40]))
        check("pointer_format" in text or proc.returncode == 0, "dyld_info -fixup_chains ran")
        binds = subprocess.run([dyld, "-fixups", str(BIN)], text=True, capture_output=True)
        day_lines = [
            line
            for line in (binds.stdout or "").splitlines()
            if "56bbb8" in line.lower() or "56BBB8" in line or "ComponentO3day" in line
        ]
        print("Component.day bind lines", len(day_lines))
        print("\n".join(day_lines[:8]))
        check(any("3day" in line or "ComponentO3day" in line for line in day_lines), "dyld_info names Component.day at 0x10056bbb8")
    else:
        print("dyld_info not on PATH; format 6 was checked from the Mach-O header")
    swift = shutil.which("swift")
    if swift:
        for name in ("WeekShift.swift", "BreakSelection.swift", "MinuteInputs.swift"):
            proc = subprocess.run([swift, str(ROOT / "tests" / name)], text=True, capture_output=True)
            print((proc.stdout or "") + (proc.stderr or ""))
            check(proc.returncode == 0, f"swift tests/{name}")


if __name__ == "__main__":
    sys.exit(main())
