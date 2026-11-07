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
    if (word >> 26) != 0b000101:
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
    else:
        print("dyld_info not on PATH; format 6 was checked from the Mach-O header")


if __name__ == "__main__":
    sys.exit(main())
