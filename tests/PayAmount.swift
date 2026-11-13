import Foundation

/// Not original Swift source.
/// Hourly yen at 0x10011bf14 is paidMinutes * hourly / 60, added to base.
/// The minutes are the scheduled interval, minus breakMinutes when no
/// BreakSpan exists. now does not replace the end date.
/// Night, overtime, and holiday premiums add to premium, not base.
/// The live number is base + premium.

func paidFraction(totalSeconds: Double, breakMinutes: Int, hasBreakSpans: Bool) -> Double {
    if hasBreakSpans { return 1 }
    let minutes = totalSeconds / 60
    if minutes <= 0 { return 0 }
    let paid = minutes - Double(breakMinutes)
    return (paid >= 0 ? paid : 0) / minutes
}

func hourlyYen(paidMinutes: Double, hourlyWage: Int) -> Double {
    paidMinutes * Double(hourlyWage) / 60
}

func scheduledHourlyYen(totalSeconds: Double, breakMinutes: Int, hourlyWage: Int) -> Double {
    let fraction = paidFraction(totalSeconds: totalSeconds, breakMinutes: breakMinutes, hasBreakSpans: false)
    return hourlyYen(paidMinutes: (totalSeconds / 60) * fraction, hourlyWage: hourlyWage)
}

func inWindow(minute: Int, start: Int, end: Int) -> Bool {
    if start == end { return false }
    if start < end { return minute >= start && minute < end }
    return minute >= start || minute < end
}

func nightPremium(sliceYen: Double, rate: Int, enabled: Bool, inWindow: Bool, bandIncludesNight: Bool) -> Double {
    if enabled && inWindow && !bandIncludesNight && rate != 0 {
        return sliceYen * Double(rate) / 100
    }
    return 0
}

func overtimeMinutes(slice: Double, prior: Double, threshold: Double) -> Double {
    let under = threshold - prior
    let capped = under < slice ? under : slice
    if capped < 0 { return slice }
    let extra = slice - capped
    return extra > 0 ? extra : 0
}

func overtimePremium(minutes: Double, hourly: Int, rate: Int) -> Double {
    if rate == 0 || minutes == 0 { return 0 }
    return minutes * Double(hourly) / 60 * Double(rate) / 100
}

func holidayRate(weekday: Int?, rates: [Int]) -> Int? {
    guard let weekday else { return nil }
    let index = weekday - 1
    guard index >= 0, index < rates.count else { return nil }
    return rates[index]
}

func expect(_ condition: Bool, _ message: String) {
    if !condition { fatalError(message) }
}

expect(hourlyYen(paidMinutes: 60, hourlyWage: 1000) == 1000, "one hour at 1000")
expect(hourlyYen(paidMinutes: 30, hourlyWage: 1200) == 600, "half hour at 1200")
expect(hourlyYen(paidMinutes: 0, hourlyWage: 1000) == 0, "zero minutes")
expect(scheduledHourlyYen(totalSeconds: 8 * 3600, breakMinutes: 60, hourlyWage: 1000) == 7000, "8h minus 60 minutes")
expect(scheduledHourlyYen(totalSeconds: 8 * 3600, breakMinutes: 30, hourlyWage: 1000) == 7500, "scaled break is not half the shift")
expect(scheduledHourlyYen(totalSeconds: 0, breakMinutes: 60, hourlyWage: 1000) == 0, "zero duration")
expect(paidFraction(totalSeconds: 3600, breakMinutes: 60, hasBreakSpans: true) == 1, "spans keep fraction 1")
expect(paidFraction(totalSeconds: 3600, breakMinutes: 90, hasBreakSpans: false) == 0, "break larger than the shift clamps")

expect(inWindow(minute: 23 * 60, start: 22 * 60, end: 5 * 60), "23:00 is inside 22:00-05:00")
expect(inWindow(minute: 4 * 60, start: 22 * 60, end: 5 * 60), "04:00 is inside the wrap")
expect(!inWindow(minute: 5 * 60, start: 22 * 60, end: 5 * 60), "05:00 is the exclusive end")
expect(!inWindow(minute: 12 * 60, start: 22 * 60, end: 5 * 60), "noon is outside")
expect(inWindow(minute: 22 * 60, start: 22 * 60, end: 5 * 60), "22:00 is the inclusive start")
expect(!inWindow(minute: 100, start: 100, end: 100), "equal bounds are not a window")
expect(inWindow(minute: 150, start: 100, end: 200) && !inWindow(minute: 200, start: 100, end: 200), "same-day end is exclusive")

expect(nightPremium(sliceYen: 1000, rate: 25, enabled: true, inWindow: true, bandIncludesNight: false) == 250, "25 percent of the slice")
expect(nightPremium(sliceYen: 1000, rate: 25, enabled: true, inWindow: false, bandIncludesNight: false) == 0, "outside the window")
expect(nightPremium(sliceYen: 1000, rate: 25, enabled: true, inWindow: true, bandIncludesNight: true) == 0, "band already includes night")
expect(nightPremium(sliceYen: 1000, rate: 0, enabled: true, inWindow: true, bandIncludesNight: false) == 0, "zero rate")

expect(overtimeMinutes(slice: 20, prior: 470, threshold: 480) == 10, "slice crossing the threshold")
expect(overtimeMinutes(slice: 20, prior: 400, threshold: 480) == 0, "entirely under the threshold")
expect(overtimeMinutes(slice: 1, prior: 479, threshold: 480) == 0, "the minute that lands on the threshold")
expect(overtimeMinutes(slice: 20, prior: 480, threshold: 480) == 20, "already at the threshold")
expect(overtimeMinutes(slice: 20, prior: 500, threshold: 480) == 20, "already past the threshold")
expect(overtimePremium(minutes: 60, hourly: 1000, rate: 25) == 250, "one overtime hour at 25 percent")
expect(overtimePremium(minutes: 60, hourly: 1000, rate: 0) == 0, "zero overtime rate")

expect(holidayRate(weekday: 1, rates: [10, 0, 0, 0, 0, 0, 35]) == 10, "weekday 1 is index 0")
expect(holidayRate(weekday: 7, rates: [0, 0, 0, 0, 0, 0, 35]) == 35, "weekday 7 is the last slot")
expect(holidayRate(weekday: nil, rates: [10]) == nil, "missing weekday")
expect(holidayRate(weekday: 8, rates: Array(repeating: 1, count: 7)) == nil, "index 7 is outside seven slots")
expect(1000 * 35 / 100 == 350, "holiday percent of the slice yen")

func baseAfterDaily(base: Double, wage: Int, daily: Bool, flag: Bool) -> Double {
    guard daily, flag else { return base }
    return base + Double(wage)
}
expect(baseAfterDaily(base: 100, wage: 8000, daily: true, flag: true) == 8100, "daily wage adds to base")
expect(baseAfterDaily(base: 100, wage: 8000, daily: false, flag: true) == 100, "hourly does not add daily wage")
expect(baseAfterDaily(base: 100, wage: 8000, daily: true, flag: false) == 100, "the unnamed bit gates the add")

func transport(current: Double, amount: Int, isTransport: Bool) -> Double {
    guard isTransport, amount >= 1 else { return current }
    return current + Double(amount)
}
expect(transport(current: 0, amount: 500, isTransport: true) == 500, "transport item adds")
expect(transport(current: 0, amount: 0, isTransport: true) == 0, "amount 0 is skipped")
expect(transport(current: 0, amount: 500, isTransport: false) == 0, "allowance is not this add")

expect(7000 + 250 == 7250, "live number is base plus premium")
print("pay amount tests passed")
