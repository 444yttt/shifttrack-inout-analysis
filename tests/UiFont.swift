import Foundation

/// Not original Swift source.
/// Font.custom at 0x10026f4b8 builds a 15-byte small string with the same
/// mov/movk immediates as the other Doto call sites. The point size there
/// is the 36.0 loaded just before the call. This is not a screen reading.

func smallString(low: UInt64, high: UInt64) -> String {
    let count = Int((high >> 56) & 0xF)
    var raw = low.littleEndian
    var bytes = withUnsafeBytes(of: &raw) { Array($0) }
    var rawHigh = high.littleEndian
    bytes += withUnsafeBytes(of: &rawHigh) { Array($0) }
    return String(bytes: bytes.prefix(count), encoding: .utf8) ?? ""
}

let low: UInt64 = 0x6F44 | (0x6F74 << 16) | (0x422D << 32) | (0x616C << 48)
let high: UInt64 = 0x6B63 | (0x6F52 << 16) | (0x6E75 << 32) | (0xEF64 << 48)
let name = smallString(low: low, high: high)
if name != "Doto-BlackRound" {
    fatalError("font name \(name)")
}
print("ui font ok")
