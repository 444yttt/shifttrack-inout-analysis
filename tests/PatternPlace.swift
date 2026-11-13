import Foundation

/// Not original Swift source.
/// 0x1001c75ec reduces a ShiftPart minute with the signed 1440 division
/// in that function, then splits hour and minute for bySettingHour.
/// start >= end, including equal minutes, is the branch that adds one day.
/// These checks are the instruction arithmetic. They are not a screen reading.

func minuteWithinDay(_ minute: Int) -> Int {
    let magic = Int(bitPattern: 0x2D82_D82D_D82D_82D3)
    let (high, _) = minute.multipliedFullWidth(by: magic)
    let quotient = (high >> 8) &+ (high < 0 ? 1 : 0)
    var remainder = minute &- quotient &* 1440
    if remainder < 0 {
        remainder &+= 1440
    }
    return remainder
}

func clock(from minute: Int) -> (hour: Int, minute: Int) {
    let remainder = minuteWithinDay(minute)
    let hour = (remainder * 0x8889) >> 21
    return (hour, remainder - hour * 60)
}

func endAddsOneDay(startMinute: Int, endMinute: Int) -> Bool {
    startMinute >= endMinute
}

let cases: [(Int, Int, Int)] = [
    (0, 0, 0),
    (59, 0, 59),
    (60, 1, 0),
    (1439, 23, 59),
    (1500, 1, 0),
    (-1, 23, 59),
    (-1440, 0, 0),
    (-1441, 23, 59),
    (22 * 60, 22, 0),
    (5 * 60, 5, 0),
]
for item in cases {
    let got = clock(from: item.0)
    if got.hour != item.1 || got.minute != item.2 {
        fatalError("minute \(item.0) became \(got)")
    }
}
if endAddsOneDay(startMinute: 9 * 60, endMinute: 17 * 60) {
    fatalError("same-day range rolled")
}
if !endAddsOneDay(startMinute: 22 * 60, endMinute: 5 * 60) {
    fatalError("overnight range did not roll")
}
if !endAddsOneDay(startMinute: 10 * 60, endMinute: 10 * 60) {
    fatalError("equal minutes did not roll")
}
print("pattern place minutes ok")
