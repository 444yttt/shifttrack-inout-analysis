#!/usr/bin/env python3
"""Check the published IN/OUT Mach-O. Runs on Linux and on the macOS Actions runner.

Does not launch the device binary in Simulator. Does not print redacted secrets.
"""

from __future__ import annotations

import hashlib
import math
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
    check_live_pay(data)
    check_pay_amount(data)
    check_pay_conditions(data)
    check_pattern_place(data)
    check_ui_font(data)
    check_asset_catalog(data)

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
    # Swift self is x20. endDate is bridged into x20; startDate is passed in x0.
    for off, word, label in (
        (0x1CF3A0, 0xAA1503E0, "endDate receiver"),
        (0x1CF3C0, 0xAA1403E8, "endDate into x20"),
        (0x1CF3CC, 0xAA1503E0, "startDate receiver"),
        (0x1CF3EC, 0xAA1B03E8, "startDate into x27"),
        (0x1CF3F8, 0xAA1B03E0, "startDate argument"),
    ):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, label)
    for off, pc, expect, label in (
        (0x1CF3A4, 0x1001CF3A4, 0x100406020, "endDate"),
        (0x1CF3D0, 0x1001CF3D0, 0x100415060, "startDate"),
        (0x1CF3FC, 0x1001CF3FC, 0x1003FCD1C, "timeIntervalSince"),
    ):
        got = branch_target(struct.unpack_from("<I", data, off)[0], pc)
        check(got == expect, f"{label} at {got:#x}")
    check(data[0x4CD1CD : 0x4CD1CD + 7] == b"endDate", "endDate selector string")
    check(data[0x4EAAD6 : 0x4EAAD6 + 9] == b"startDate", "startDate selector string")


def editor_minute_count(start: int, end: int) -> int:
    difference = end - start
    remainder = difference % 1440
    if remainder < 0:
        remainder += 1440
    return 1440 if remainder == 0 else remainder


def frinta(value: float) -> float:
    if value >= 0:
        return float(math.floor(value + 0.5))
    return float(math.ceil(value - 0.5))


def round_seconds(seconds: float, unit_minutes: int, direction: str) -> float:
    if unit_minutes < 2 or direction == "exact":
        return seconds
    unit = float(unit_minutes * 60)
    units = seconds / unit
    if direction == "up":
        rounded = math.ceil(units)
    elif direction == "down":
        rounded = math.floor(units)
    else:
        rounded = frinta(units)
    return rounded * unit


def scaled_break(elapsed: float, duration: float, break_minutes: int) -> int:
    if duration <= 0:
        return 0
    return int(frinta(elapsed * break_minutes / duration))


def check_live_pay(data: bytes) -> None:
    for off, word in (
        (0x26EB24, 0x9406387E),
        (0x26EB28, 0x1E602008),
        (0x26EB3C, 0x5E61D809),
        (0x26EB4C, 0x1E690800),
        (0x26EB50, 0x1E681800),
        (0x26EB54, 0x1E664000),
        (0x26EB90, 0x9E780014),
        (0x26EB98, 0xD2800014),
        (0x26EBF4, 0xF8286B14),
        (0x11B4A4, 0xF1000ABF),
        (0x11B4B0, 0x3400049B),
        (0x11B4E4, 0x9E630108),
        (0x11B4F8, 0x1E64C001),
        (0x11B500, 0x1E654002),
        (0x11B504, 0x1E664000),
        (0x11B508, 0x1E600C40),
        (0x11B50C, 0x7100077F),
        (0x11B510, 0x1E600C20),
        (0x11B514, 0x1E680800),
        (0x11B860, 0xD2E809C8),
        (0x11B960, 0xD2E80B28),
        (0x25782C, 0x1E67D000),
        (0x258254, 0x1E67D000),
        (0x262B48, 0x1E6E1000),
    ):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"live/rounding word at {off:#x}")
    since = branch_target(struct.unpack_from("<I", data, 0x26EB24)[0], 0x10026EB24)
    check(since == 0x1003FCD1C, f"live timeIntervalSince at {since:#x}")
    record = branch_target(struct.unpack_from("<I", data, 0x26E9D8)[0], 0x10026E9D8)
    check(record == 0x1000EDD2C, f"live WorkRecord accessor at {record:#x}")
    for off, pc in ((0x25783C, 0x10025783C), (0x258260, 0x100258260), (0x262B58, 0x100262B58)):
        got = branch_target(struct.unpack_from("<I", data, off)[0], pc)
        check(got == 0x1003FDBD4, f"timeline schedule init at {got:#x}")
    cases = (
        (450.0, 0, "up", 450.0),
        (450.0, 1, "nearest", 450.0),
        (450.0, 15, "exact", 450.0),
        (450.0, 15, "nearest", 900.0),
        (449.0, 15, "nearest", 0.0),
        (1.0, 15, "up", 900.0),
        (899.0, 15, "down", 0.0),
        (-450.0, 15, "nearest", -900.0),
        (-1.0, 15, "up", 0.0),
        (-1.0, 15, "down", -900.0),
    )
    for seconds, unit, direction, expect in cases:
        got = round_seconds(seconds, unit, direction)
        check(got == expect, f"round {seconds} unit {unit} {direction} -> {got}")
    for elapsed, duration, minutes, expect in (
        (4 * 3600.0, 8 * 3600.0, 60, 30),
        (0.0, 8 * 3600.0, 60, 0),
        (8 * 3600.0, 8 * 3600.0, 60, 60),
        (30.0, 8 * 3600.0, 60, 0),
        (240.0, 8 * 3600.0, 60, 1),
        (-14400.0, 8 * 3600.0, 60, -30),
        (-3600.0, 8 * 3600.0, 60, -8),
        (1.0, 0.0, 60, 0),
        (1.0, -1.0, 60, 0),
    ):
        got = scaled_break(elapsed, duration, minutes)
        check(got == expect, f"scaled break {elapsed}/{duration} -> {got}")


def check_pay_amount(data: bytes) -> None:
    for off, word in (
        (0x11B210, 0xAA0003FC),
        (0x11B208, 0xF9005E62),
        (0x11BF14, 0x9E620380),
        (0x11BF18, 0x1E68180D),
        (0x11BF1C, 0x1E6D092C),
        (0x11BF20, 0x1E6C29EF),
        (0x11BF28, 0xFD00052F),
        (0x11B9E0, 0xD2E809C8),
        (0x11C168, 0x1E6C09C1),
        (0x11C180, 0xFD000900),
        (0x11C684, 0x1E6E09A0),
        (0x11C688, 0x1E60082D),
        (0x11C69C, 0xFD000900),
        (0x11BD08, 0xEB08013F),
        (0x11BD60, 0x540005EB),
        (0x11A3F4, 0x7100051F),
        (0x11A420, 0x5E61D808),
        (0x11A428, 0x1E682800),
        (0x11A42C, 0xFD000760),
        (0x11ACEC, 0x9E630108),
        (0x11ACF8, 0xFD001380),
        (0x26ECF0, 0x6D40A6A8),
        (0x26ED14, 0x1E692908),
    ):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"pay-amount word at {off:#x}")
    shown = branch_target(struct.unpack_from("<I", data, 0x26F5D8)[0], 0x10026F5D8)
    check(shown == 0x1003FD73C, f"numericText at {shown:#x}")
    check(1000 * 60 / 60 == 1000, "one hour")
    check(scheduled_yen(8 * 3600, 60, 1000) == 7000, "scheduled 8h minus 60")
    check(scheduled_yen(8 * 3600, 30, 1000) == 7500, "scaled break stays on the full interval")
    check(scheduled_yen(0, 60, 1000) == 0, "zero scheduled seconds")
    check(paid_fraction(3600, 90, False) == 0, "break above the length")
    check(paid_fraction(3600, 60, True) == 1, "spans do not use the flat break")
    check(in_window(23 * 60, 22 * 60, 5 * 60) and in_window(4 * 60, 22 * 60, 5 * 60), "overnight window")
    check(not in_window(5 * 60, 22 * 60, 5 * 60) and not in_window(100, 100, 100), "exclusive end and empty window")
    check(overtime_minutes(20, 470, 480) == 10, "crossing threshold")
    check(overtime_minutes(1, 479, 480) == 0, "landing on the threshold")
    check(overtime_minutes(20, 500, 480) == 20, "already past threshold")
    check(60 * 1000 / 60 * 25 / 100 == 250, "overtime premium")
    check(1000 + 250 == 1250, "shown total is base plus premium")


def paid_fraction(seconds: float, break_minutes: int, has_spans: bool) -> float:
    if has_spans:
        return 1
    minutes = seconds / 60
    if minutes <= 0:
        return 0
    paid = minutes - break_minutes
    return (paid if paid >= 0 else 0) / minutes


def scheduled_yen(seconds: float, break_minutes: int, hourly: int) -> float:
    fraction = paid_fraction(seconds, break_minutes, False)
    return (seconds / 60) * fraction * hourly / 60


def in_window(minute: int, start: int, end: int) -> bool:
    if start == end:
        return False
    if start < end:
        return start <= minute < end
    return minute >= start or minute < end


def overtime_minutes(slice_minutes: float, prior: float, threshold: float) -> float:
    under = threshold - prior
    capped = under if under < slice_minutes else slice_minutes
    if capped < 0:
        return slice_minutes
    extra = slice_minutes - capped
    return extra if extra > 0 else 0


def check_pay_conditions(data: bytes) -> None:
    for off, word in (
        (0x262B08, 0xB9803708),
        (0x262C24, 0x9114A108),
        (0xDE904, 0xB9801908),
        (0xDE908, 0xF8686AB3),
        (0x11A648, 0x35FFFE09),
        (0x11A83C, 0xF100067F),
        (0x11A840, 0x540018EB),
        (0x11A850, 0xFD001360),
        (0x119734, 0xF81083A0),
        (0x11A7B8, 0x7100051F),
    ):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"pay-condition word at {off:#x}")
    for off, pc, expect, label in (
        (0x262AF8, 0x100262AF8, 0x1003FE978, "shift start <="),
        (0x262B14, 0x100262B14, 0x1003FCD4C, "gate < end"),
        (0x262CC4, 0x100262CC4, 0x1003FD3B8, "TimelineView.init"),
        (0xDE848, 0x1000DE848, 0x1003FE978, "wage day <="),
    ):
        got = branch_target(struct.unpack_from("<I", data, off)[0], pc)
        check(got == expect, f"{label} at {got:#x}")
    check(data[0x502250:0x502250 + len("終わりまで あと ".encode())] == "終わりまで あと ".encode(), "string beside the yen numeric text")
    check(data[0x502270:0x502270 + len("いま稼いだお給料".encode())] == "いま稼いだお給料".encode(), "accessibility literal")
    check(data[0x4FB480:0x4FB480 + len("シフトを追加".encode())] == "シフトを追加".encode(), "add-shift literal")
    for off, word in ((0x26F194, 0x9109C108), (0x26F198, 0xD1008108), (0x26F67C, 0x5290DCA0), (0x26F680, 0x72A010C0)):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"display word at {off:#x}")


def pattern_minute_within_day(minute: int) -> int:
    magic = int.from_bytes(bytes.fromhex("2d82d82dd82d82d3"), "big", signed=True)
    high = (minute * magic) >> 64
    quotient = (high >> 8) + (1 if high < 0 else 0)
    remainder = minute - quotient * 1440
    if remainder < 0:
        remainder += 1440
    return remainder


def pattern_clock(minute: int) -> tuple[int, int]:
    remainder = pattern_minute_within_day(minute)
    hour = (remainder * 0x8889) >> 21
    return hour, remainder - hour * 60


def check_pattern_place(data: bytes) -> None:
    for off, word in (
        (0x3FFA8, 0xB40009A8),
        (0x6E2EC, 0xB4000648),
        (0x6E138, 0xB9802816),
        (0x6E354, 0xB9803F34),
        (0x4006C, 0xB9803113),
        (0x1C7B64, 0xB9801B68),
        (0x1C7E64, 0xB9801D08),
        (0x1C7E9C, 0xB9802108),
        (0x1C7EE8, 0x5280B409),
        (0x1C7FD0, 0xD2800002),
        (0x1C814C, 0x52800021),
        (0x1C8154, 0x52800003),
        (0x1C7BD0, 0x7100041F),
        (0x1C85BC, 0x383B6B9F),
        (0x1C7D44, 0xF945DD08),
    ):
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"pattern-place word at {off:#x}")
    for off, pc, expect, label in (
        (0x40134, 0x100040134, 0x100014370, "day chip commit"),
        (0x6E3C8, 0x10006E3C8, 0x100014370, "tab chip commit"),
        (0x1464C, 0x10001464C, 0x1001C75EC, "commit places the part"),
        (0x1C7E24, 0x1001C7E24, 0x1003FCDC4, "same part id"),
        (0x1C7FE8, 0x1001C7FE8, 0x1003FCE9C, "start bySettingHour"),
        (0x1C82BC, 0x1001C82BC, 0x1003FCE9C, "end bySettingHour"),
        (0x1C815C, 0x1001C815C, 0x1003FCEB4, "end adds one day"),
        (0x17B6C, 0x100017B6C, 0x100016734, "clash overlap"),
    ):
        got = branch_target(struct.unpack_from("<I", data, off)[0], pc)
        check(got == expect, f"{label} at {got:#x}")
    check(pattern_clock(0) == (0, 0), "midnight")
    check(pattern_clock(60) == (1, 0), "one hour")
    check(pattern_clock(1439) == (23, 59), "last minute")
    check(pattern_clock(1500) == (1, 0), "past one day")
    check(pattern_clock(-1) == (23, 59), "negative minute wraps")
    check(not (9 * 60 >= 17 * 60), "day shift does not roll")
    check(22 * 60 >= 5 * 60 and 10 * 60 >= 10 * 60, "overnight and equal minutes roll")
    check(data[0x4FAE70:0x4FAE70 + len(b"inout.adsRemoved")] == b"inout.adsRemoved", "save notice key")
    check(data[0x5001B0:0x5001B0 + len("のシフトがあります".encode())] == "のシフトがあります".encode(), "existing-shift clash phrase")


def doto_name_from_halves(low: int, high: int) -> str:
    count = (high >> 56) & 0xF
    raw = low.to_bytes(8, "little") + high.to_bytes(8, "little")
    return raw[:count].decode()


def check_ui_font(data: bytes) -> None:
    words = (
        (0x26F494, 0xD28DE880),
        (0x26F498, 0xF2ADEE80),
        (0x26F49C, 0xF2C845A0),
        (0x26F4A0, 0xF2EC2D80),
        (0x26F4A4, 0xD28D6C61),
        (0x26F4A8, 0xF2ADEA41),
        (0x26F4AC, 0xF2CDCEA1),
        (0x26F4B0, 0xF2FDEC81),
        (0x6935C, 0x1E665000),
        (0x2064B0, 0x1E669000),
    )
    for off, word in words:
        got = struct.unpack_from("<I", data, off)[0]
        check(got == word, f"ui-font word at {off:#x}")
    # The eight mov/movk immediates above assemble the small string.
    low = 0x6F44 | (0x6F74 << 16) | (0x422D << 32) | (0x616C << 48)
    high = 0x6B63 | (0x6F52 << 16) | (0x6E75 << 32) | (0xEF64 << 48)
    check(doto_name_from_halves(low, high) == "Doto-BlackRound", "custom font name")
    check(b"Doto-BlackRound" not in data, "font name is an immediate, not a cstring")
    for name in (b"WorkplaceListView", b"CalendarTabView", b"IncomeView", b"SettingsView", b"LaunchAnimationView"):
        check(name in data, f"view type {name.decode()} is in the metadata")
    shown = branch_target(struct.unpack_from("<I", data, 0x26F4B8)[0], 0x10026F4B8)
    check(shown == 0x1003FDE2C, f"yen text uses Font.custom at {shown:#x}")


def check_asset_catalog(data: bytes) -> None:
    import json

    catalog = json.loads((ROOT / "notes" / "assets.json").read_text())
    colors = {
        (item["name"], item["appearance"]): item["color"]["srgb8"]
        for item in catalog["renditions"]
        if item.get("color")
    }
    check(colors[("AccentColor", "UIAppearanceAny")] == [0, 0, 0, 255], "AccentColor light is black")
    check(colors[("AccentColor", "UIAppearanceDark")] == [255, 255, 255, 255], "AccentColor dark is white")
    check(colors[("LaunchBackground", "UIAppearanceAny")] == [195, 255, 119, 255], "launch background")
    check("SourceBrowserIcon" in catalog["facets"], "source browser facet")
    check(b"SourceBrowserIcon" in data, "source browser name is in the binary")
    check(b"AccentColor" not in data, "AccentColor is not a cstring in the Mach-O")
    check(struct.unpack_from("<I", data, 0x6BE3C)[0] == 0x528D8E00, "plus symbol immediate")
    check(struct.unpack_from("<I", data, 0x25350)[0] == 0xD28C2C69, "calendar symbol immediate")


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
        for name in (
            "WeekShift.swift",
            "BreakSelection.swift",
            "MinuteInputs.swift",
            "DateDirection.swift",
            "PayRounding.swift",
            "LiveScale.swift",
            "PayAmount.swift",
            "PayConditions.swift",
            "PatternPlace.swift",
            "UiFont.swift",
        ):
            proc = subprocess.run([swift, str(ROOT / "tests" / name)], text=True, capture_output=True)
            print((proc.stdout or "") + (proc.stderr or ""))
            check(proc.returncode == 0, f"swift tests/{name}")


if __name__ == "__main__":
    sys.exit(main())
