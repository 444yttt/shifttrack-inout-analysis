import Foundation

/// Not original Swift source.
/// 0x10026e844 picks asOf = shiftEnd when shiftEnd < now, otherwise now.
/// scaled break is 0 when end.timeIntervalSince(start) <= 0.
/// Otherwise frinta(asOf.timeIntervalSince(start) * break / duration), then
/// toward-zero conversion. This replaces WorkRecord.breakMinutes.
/// It is not a yen amount.

func liveAsOf(now: Date, shiftEnd: Date) -> Date {
    shiftEnd < now ? shiftEnd : now
}

func scaledBreakMinutes(start: Date, end: Date, asOf: Date, breakMinutes: Int) -> Int {
    let duration = end.timeIntervalSince(start)
    if duration <= 0 {
        return 0
    }
    let elapsed = asOf.timeIntervalSince(start)
    let scaled = (elapsed * Double(breakMinutes) / duration).rounded(.toNearestOrAwayFromZero)
    return Int(scaled)
}

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fatalError(message)
    }
}

var calendar = Calendar(identifier: .gregorian)
calendar.timeZone = TimeZone(secondsFromGMT: 0)!
let start = calendar.date(from: DateComponents(year: 2024, month: 1, day: 1, hour: 9))!
let end = start.addingTimeInterval(8 * 3600)
let halfway = start.addingTimeInterval(4 * 3600)
let before = start.addingTimeInterval(-3600)
let after = end.addingTimeInterval(3600)

expect(liveAsOf(now: halfway, shiftEnd: end) == halfway, "during the shift, asOf is now")
expect(liveAsOf(now: after, shiftEnd: end) == end, "after the shift, asOf is the end")
expect(liveAsOf(now: end, shiftEnd: end) == end, "equal instants stay on now, which is the end")

expect(scaledBreakMinutes(start: start, end: end, asOf: halfway, breakMinutes: 60) == 30, "halfway of 60 is 30")
expect(scaledBreakMinutes(start: start, end: end, asOf: start, breakMinutes: 60) == 0, "at the start the scaled break is 0")
expect(scaledBreakMinutes(start: start, end: end, asOf: end, breakMinutes: 60) == 60, "at the end the scaled break is the full break")
expect(scaledBreakMinutes(start: start, end: start, asOf: start, breakMinutes: 60) == 0, "zero duration stores 0")
expect(scaledBreakMinutes(start: end, end: start, asOf: halfway, breakMinutes: 60) == 0, "reversed duration stores 0")
expect(scaledBreakMinutes(start: start, end: end, asOf: start.addingTimeInterval(30), breakMinutes: 60) == 0, "30s of an 8h shift is under half a break minute")
expect(scaledBreakMinutes(start: start, end: end, asOf: start.addingTimeInterval(240), breakMinutes: 60) == 1, "240s is the 0.5 tie and goes away from zero")
expect(scaledBreakMinutes(start: start, end: end, asOf: start.addingTimeInterval(-4 * 3600), breakMinutes: 60) == -30, "negative elapsed stays negative")
expect(scaledBreakMinutes(start: start, end: end, asOf: before, breakMinutes: 60) == -8, "negative 7.5 ties away from zero")
expect(scaledBreakMinutes(start: start, end: end, asOf: halfway, breakMinutes: 0) == 0, "zero break stays zero")
print("live scale tests passed")
