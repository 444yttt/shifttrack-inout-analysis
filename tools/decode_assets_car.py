#!/usr/bin/env python3
"""Read names, colors, and pixel sizes from an Apple Assets.car.

This follows the BOMStore index and the CoreUI CSI header (the records
`assetutil --info` reads). It prints JSON and does not write images or fonts.

The catalog itself is not part of this repository. Pass a local path:

    python3 tools/decode_assets_car.py /path/to/Assets.car

On macOS, `assetutil --info Assets.car` is the vendor tool for the same file.
That command is not run here: putting the catalog on the public runner would
publish the images.
"""

from __future__ import annotations

import json
import struct
import sys
from pathlib import Path


ATTR = [
    "ThemeLook",
    "Element",
    "Part",
    "Size",
    "Direction",
    "Placeholder",
    "Value",
    "ThemeAppearance",
    "Dimension1",
    "Dimension2",
    "State",
    "Layer",
    "Scale",
    "Localization",
    "PresentationState",
    "Idiom",
    "Subtype",
    "Identifier",
]


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from(">I", data, off)[0]


def load_bom(data: bytes):
    if data[:8] != b"BOMStore":
        raise SystemExit("not a BOMStore asset catalog")
    _, _, index_off, _, vars_off, _ = struct.unpack_from(">IIIIII", data, 8)
    count = u32(data, index_off)
    ptrs = []
    off = index_off + 4
    for _ in range(count):
        ptrs.append(struct.unpack_from(">II", data, off))
        off += 8

    def block(index: int) -> bytes:
        addr, length = ptrs[index]
        return data[addr : addr + length]

    names = {}
    nvars = u32(data, vars_off)
    pos = vars_off + 4
    for _ in range(nvars):
        idx = u32(data, pos)
        pos += 4
        nlen = data[pos]
        pos += 1
        names[data[pos : pos + nlen].split(b"\x00", 1)[0].decode()] = idx
        pos += nlen
    return block, names


def tree_nodes(block, root: int):
    seen: set[int] = set()

    def read(index: int):
        if index in seen:
            raise SystemExit(f"tree cycle at {index}")
        seen.add(index)
        buf = block(index)
        is_leaf, count, forward, _back = struct.unpack_from(">HHII", buf, 0)
        return is_leaf, count, forward, buf[12:]

    def descend(index: int):
        is_leaf, count, forward, rest = read(index)
        while is_leaf == 0:
            value, _key = struct.unpack_from(">II", rest, 0)
            is_leaf, count, forward, rest = read(value)
        return is_leaf, count, forward, rest

    header = block(root)
    child = struct.unpack_from(">I", header, 8)[0]
    leaves = []
    is_leaf, count, forward, rest = descend(child)
    while True:
        items = []
        off = 0
        for _ in range(count):
            value, key = struct.unpack_from(">II", rest, off)
            off += 8
            items.append((key, value))
        leaves.append(items)
        if forward == 0:
            break
        is_leaf, count, forward, rest = read(forward)
    return leaves


def cstring(buf: bytes) -> str:
    return buf.split(b"\x00", 1)[0].decode("utf-8", "replace")


def jpeg_size(buf: bytes) -> tuple[int, int] | None:
    sof = buf.find(b"\xff\xc0")
    if sof < 0 or sof + 9 > len(buf):
        return None
    height, width = struct.unpack_from(">HH", buf, sof + 5)
    return width, height


def appearances(block, names) -> dict[int, str]:
    found = {}
    for items in tree_nodes(block, names["APPEARANCEKEYS"]):
        for key, value in items:
            name = cstring(block(key))
            code = struct.unpack_from("<H", block(value), 0)[0]
            found[code] = name
    return found


def decode(path: Path) -> dict:
    data = path.read_bytes()
    block, names = load_bom(data)
    apps = appearances(block, names)
    keyfmt = block(names["KEYFORMAT"])
    if keyfmt[:4] != b"tmfk":
        raise SystemExit("KEYFORMAT tag is not kfmt")
    ntok = struct.unpack_from("<I", keyfmt, 8)[0]
    tokens = struct.unpack_from("<" + "I" * ntok, keyfmt, 12)
    facets = []
    for items in tree_nodes(block, names["FACETKEYS"]):
        for key, _value in items:
            try:
                facets.append(cstring(block(key)))
            except Exception:
                continue
    renditions = []
    istc_spans = []
    raw_positions = []
    for items in tree_nodes(block, names["RENDITIONS"]):
        for key, value in items:
            raw = block(value)
            at = raw.find(b"ISTC")
            raw_positions.append((key, value, raw, at))
    # JPEG size uses the distance to the next ISTC in the file, not in tree order.
    file_istc = []
    cursor = 0
    while True:
        at = data.find(b"ISTC", cursor)
        if at < 0:
            break
        file_istc.append(at)
        cursor = at + 4
    for key, _value, raw, at in raw_positions:
        keys = struct.unpack_from("<" + "H" * (len(block(key)) // 2), block(key))
        attrs = {}
        for index, token in enumerate(tokens):
            if index < len(keys):
                label = ATTR[token] if token < len(ATTR) else str(token)
                attrs[label] = keys[index]
        name = ""
        layout = None
        width = height = scale = None
        pixel = ""
        color = None
        if at >= 0:
            name = cstring(raw[at + 40 : at + 168])
            layout = struct.unpack_from("<H", raw, at + 36)[0]
            width, height, scale = struct.unpack_from("<III", raw, at + 12)
            pixel = raw[at + 24 : at + 28][::-1].decode("latin1")
            if layout == 1009:
                chain = struct.unpack_from("<I", raw, at + 168)[0]
                images = struct.unpack_from("<I", raw, at + 172)[0]
                payload = at + 176 + 4 * (images + 1) + chain
                count = struct.unpack_from("<I", raw, payload + 12)[0]
                comps = struct.unpack_from("<" + "d" * count, raw, payload + 16)
                color = {
                    "components": [float(f"{c:.8f}") for c in comps],
                    "srgb8": [int(round(c * 255)) for c in comps],
                    "space": "sRGB" if struct.unpack_from("<I", raw, payload + 8)[0] & 0xFF == 1 else "unspecified",
                }
        appearance = apps.get(attrs.get("ThemeAppearance", -1), str(attrs.get("ThemeAppearance")))
        renditions.append(
            {
                "name": name,
                "layout": layout,
                "appearance": appearance,
                "width": width,
                "height": height,
                "scaleFactor": scale,
                "pixelFormat": pixel.strip("\x00"),
                "idiom": attrs.get("Idiom"),
                "identifier": attrs.get("Identifier"),
                "color": color,
            }
        )
    file_jpegs: dict[str, list[tuple[int, int]]] = {}
    for index, at in enumerate(file_istc):
        end = file_istc[index + 1] if index + 1 < len(file_istc) else len(data)
        header_name = cstring(data[at + 40 : at + 168])
        if data[at + 24 : at + 28][::-1] != b"JPEG":
            continue
        size = jpeg_size(data[at:end])
        if size:
            file_jpegs.setdefault(header_name, []).append(size)
    used: dict[str, int] = {}
    for item in renditions:
        if item["pixelFormat"] != "JPEG":
            continue
        queue = file_jpegs.get(item["name"], [])
        n = used.get(item["name"], 0)
        if n < len(queue):
            item["jpegWidth"], item["jpegHeight"] = queue[n]
            used[item["name"]] = n + 1
    return {
        "facets": facets,
        "appearances": {str(k): v for k, v in sorted(apps.items())},
        "renditions": renditions,
    }


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: decode_assets_car.py Assets.car", file=sys.stderr)
        return 2
    json.dump(decode(Path(sys.argv[1])), sys.stdout, ensure_ascii=False, indent=2)
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
