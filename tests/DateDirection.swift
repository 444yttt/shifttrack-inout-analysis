import Foundation

/// Not original Swift source.
/// 0x1001cee68 calls endDate.timeIntervalSince(startDate), divides by 60,
/// and truncates toward zero. Equal instants are 0 minutes, unlike
/// editorMinuteCount, which turns equal clock minutes into 1440.

func truncatedMinutes(towardZero seconds: Double) -> Int {
    Int(seconds / 60.0)
}

func minutesFromEndDate(since start: Date, end: Date) -> Int {
    truncatedMinutes(towardZero: end.timeIntervalSince(start))
}

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fatalError(message)
    }
}

var calendar = Calendar(identifier: .gregorian)
calendar.timeZone = TimeZone(secondsFromGMT: 0)!
let start = calendar.date(from: DateComponents(year: 2024, month: 1, day: 1, hour: 22))!
let end = calendar.date(from: DateComponents(year: 2024, month: 1, day: 2, hour: 6))!
expect(minutesFromEndDate(since: start, end: end) == 480, "overnight is eight hours")
expect(minutesFromEndDate(since: start, end: start) == 0, "equal instants are zero, not 1440")
let almost = end.addingTimeInterval(-0.1)
expect(minutesFromEndDate(since: start, end: almost) == 479, "fraction truncates toward zero")
expect(minutesFromEndDate(since: end, end: start) == -480, "reversed dates stay negative")
print("date direction tests passed")
