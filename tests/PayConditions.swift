import Foundation

/// Not original Swift source.
/// The 1-second list timeline is installed only when start <= gate < end.
/// That compare does not replace the shift end. selectedHourlyWage walks
/// history from the end. Transport items add their integer once.
/// None of these tests are an observation of the on-screen yen.

func showsTimeline(start: Date, end: Date, gate: Date) -> Bool {
    start <= gate && gate < end
}

struct Rate {
    var effectiveFrom: Date
    var hourlyWage: Int
}

func selectedHourly(on day: Date, history: [Rate], calendar: Calendar) -> Int? {
    if history.isEmpty { return 0 }
    let shiftDay = calendar.startOfDay(for: day)
    for rate in history.reversed() {
        let parts = calendar.dateComponents([.year, .month, .day], from: rate.effectiveFrom)
        guard let rateDay = calendar.date(from: parts) else { continue }
        if rateDay <= shiftDay { return rate.hourlyWage }
    }
    return nil
}

func transportItem(current: Double, kind: Int, unit: Int, amount: Int, condition: Int, nightMinutes: Double) -> Double {
    if unit == 2 || kind != 0 { return current }
    if condition == 1 && !(nightMinutes > 0) { return current }
    if amount < 1 { return current }
    return current + Double(amount)
}

func expect(_ condition: Bool, _ message: String) {
    if !condition { fatalError(message) }
}

var calendar = Calendar(identifier: .gregorian)
calendar.timeZone = TimeZone(secondsFromGMT: 0)!
let start = calendar.date(from: DateComponents(year: 2024, month: 6, day: 1, hour: 9))!
let end = calendar.date(from: DateComponents(year: 2024, month: 6, day: 1, hour: 17))!
let during = calendar.date(from: DateComponents(year: 2024, month: 6, day: 1, hour: 12))!
let before = calendar.date(from: DateComponents(year: 2024, month: 6, day: 1, hour: 8))!
expect(showsTimeline(start: start, end: end, gate: during), "mid-shift gate installs the timeline")
expect(showsTimeline(start: start, end: end, gate: start), "the start instant is included")
expect(!showsTimeline(start: start, end: end, gate: end), "the end instant is excluded")
expect(!showsTimeline(start: start, end: end, gate: before), "before the shift the timeline is not installed")

let jan = calendar.date(from: DateComponents(year: 2024, month: 1, day: 1, hour: 15))!
let jun = calendar.date(from: DateComponents(year: 2024, month: 6, day: 1, hour: 8))!
let history = [Rate(effectiveFrom: jan, hourlyWage: 1000), Rate(effectiveFrom: jun, hourlyWage: 1500)]
let may = calendar.date(from: DateComponents(year: 2024, month: 5, day: 20, hour: 9))!
expect(selectedHourly(on: may, history: history, calendar: calendar) == 1000, "May uses the January rate")
expect(selectedHourly(on: jun, history: history, calendar: calendar) == 1500, "June 1 uses the June rate")
expect(selectedHourly(on: during, history: history, calendar: calendar) == 1500, "later in June keeps the June rate")
expect(selectedHourly(on: may, history: [], calendar: calendar) == 0, "empty history is zero")
let beforeAll = calendar.date(from: DateComponents(year: 2023, month: 1, day: 1))!
expect(selectedHourly(on: beforeAll, history: history, calendar: calendar) == nil, "no rate on or before the day is not given a wage here")

expect(transportItem(current: 0, kind: 0, unit: 0, amount: 500, condition: 0, nightMinutes: 0) == 500, "per-shift transport adds the integer")
expect(transportItem(current: 100, kind: 0, unit: 1, amount: 500, condition: 0, nightMinutes: 0) == 600, "per-day transport uses the same integer add")
expect(transportItem(current: 0, kind: 0, unit: 2, amount: 500, condition: 0, nightMinutes: 0) == 0, "per-period is skipped")
expect(transportItem(current: 0, kind: 1, unit: 0, amount: 500, condition: 0, nightMinutes: 0) == 0, "allowance does not use this add")
expect(transportItem(current: 0, kind: 2, unit: 0, amount: 500, condition: 0, nightMinutes: 0) == 0, "deduction does not use this add")
expect(transportItem(current: 0, kind: 0, unit: 0, amount: 0, condition: 0, nightMinutes: 0) == 0, "amount below 1 is skipped")
expect(transportItem(current: 0, kind: 0, unit: 0, amount: 500, condition: 1, nightMinutes: 0) == 0, "night condition with no night minutes")
expect(transportItem(current: 0, kind: 0, unit: 0, amount: 500, condition: 1, nightMinutes: 30) == 500, "night condition with night minutes")
print("pay condition tests passed")
