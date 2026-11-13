import Foundation

/// Same operations as `InOutRecovered.addingWeeks` / `weekSlideTag`.
/// The integer rules are the instruction semantics at 0x10020499c.
/// Calendar is only used to check that adding N*7 days matches Foundation.

func weekSlideTag(weeks: Int) -> Int {
    weeks > 0 ? 3 : 1
}

func addingWeeks(_ weeks: Int, to stateDate: Date, calendar: Calendar) -> Date? {
    calendar.date(byAdding: .day, value: weeks * 7, to: stateDate, wrappingComponents: false)
}

var calendar = Calendar(identifier: .gregorian)
calendar.timeZone = TimeZone(secondsFromGMT: 0)!
let anchor = calendar.date(from: DateComponents(year: 2024, month: 1, day: 1))!

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fputs("FAIL \(message)\n", stderr)
        exit(1)
    }
}

expect(weekSlideTag(weeks: 2) == 3, "positive tag")
expect(weekSlideTag(weeks: 1) == 3, "one week tag")
expect(weekSlideTag(weeks: 0) == 1, "zero tag")
expect(weekSlideTag(weeks: -4) == 1, "negative tag")

let forward = addingWeeks(1, to: anchor, calendar: calendar)
let back = addingWeeks(-1, to: anchor, calendar: calendar)
let stay = addingWeeks(0, to: anchor, calendar: calendar)
expect(forward == calendar.date(from: DateComponents(year: 2024, month: 1, day: 8)), "plus one week")
expect(back == calendar.date(from: DateComponents(year: 2023, month: 12, day: 25)), "minus one week")
expect(stay == anchor, "zero weeks")
print("week shift tests passed")
