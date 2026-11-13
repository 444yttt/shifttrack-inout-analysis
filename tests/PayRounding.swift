import Foundation

/// Not original Swift source.
/// 0x10011b1d0 applies PayRounding to one instant:
/// unitMinutes < 2 or direction exact leaves it unchanged.
/// Otherwise seconds-from-startOfDay / (unitMinutes * 60), then
/// up = frintp, down = frintm, nearest = frinta, times the unit, added
/// back onto that start of day.

enum Direction {
    case exact, up, down, nearest
}

func roundSeconds(_ seconds: Double, unitMinutes: Int, direction: Direction) -> Double {
    if unitMinutes < 2 || direction == .exact {
        return seconds
    }
    let unit = Double(unitMinutes * 60)
    let units = seconds / unit
    let rounded: Double
    switch direction {
    case .exact:
        rounded = units
    case .up:
        rounded = units.rounded(.up)
    case .down:
        rounded = units.rounded(.down)
    case .nearest:
        rounded = units.rounded(.toNearestOrAwayFromZero)
    }
    return rounded * unit
}

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fatalError(message)
    }
}

expect(roundSeconds(450, unitMinutes: 0, direction: .up) == 450, "unit 0 is unchanged")
expect(roundSeconds(450, unitMinutes: 1, direction: .nearest) == 450, "unit 1 is unchanged")
expect(roundSeconds(450, unitMinutes: -5, direction: .up) == 450, "negative unit is unchanged")
expect(roundSeconds(450, unitMinutes: 15, direction: .exact) == 450, "exact is unchanged")
expect(roundSeconds(450, unitMinutes: 15, direction: .nearest) == 900, "half unit ties away from zero")
expect(roundSeconds(449, unitMinutes: 15, direction: .nearest) == 0, "just under half stays down")
expect(roundSeconds(1, unitMinutes: 15, direction: .up) == 900, "one second rounds up a unit")
expect(roundSeconds(899, unitMinutes: 15, direction: .down) == 0, "just under a unit rounds down")
expect(roundSeconds(900, unitMinutes: 15, direction: .up) == 900, "exact unit stays")
expect(roundSeconds(0, unitMinutes: 15, direction: .nearest) == 0, "midnight stays")
expect(roundSeconds(-450, unitMinutes: 15, direction: .nearest) == -900, "negative tie goes away from zero")
expect(roundSeconds(-1, unitMinutes: 15, direction: .up) == 0, "negative fraction toward +inf is zero")
expect(roundSeconds(-1, unitMinutes: 15, direction: .down) == -900, "negative fraction toward -inf is one unit")

var calendar = Calendar(identifier: .gregorian)
calendar.timeZone = TimeZone(secondsFromGMT: 0)!
let day = calendar.date(from: DateComponents(year: 2024, month: 1, day: 1))!
let sevenAndAHalf = day.addingTimeInterval(450)
let start = calendar.startOfDay(for: sevenAndAHalf)
let rounded = start.addingTimeInterval(roundSeconds(sevenAndAHalf.timeIntervalSince(start), unitMinutes: 15, direction: .nearest))
expect(rounded.timeIntervalSince(day) == 900, "startOfDay plus rounded seconds")
print("pay rounding tests passed")
