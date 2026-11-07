import Foundation

/// Reconstructed from `bin/IN-OUT`. This is not the original Swift source,
/// not a paste of Ghidra output, and not a feature imitation of screens whose
/// calculation was not found.
///
/// Ghidra pseudocode for the same addresses is in `notes/ghidra/`.
/// Week shifting is the checked multiply at 0x10020499c.
/// Break selection is the comparison at 0x1000e967c. It takes minutes already
/// computed; it does not define how those minutes are produced.
/// Payroll arithmetic and minute rounding were not recovered as functions.
/// Do not fill those in from the UI strings.
/// No advertisements.

struct RecoveredBreakRule {
    var overMinutes: Int
    var breakMinutes: Int
}

struct RecoveredNightPremium {
    var enabled: Bool
    var startMinute: Int
    var endMinute: Int
    var ratePercent: Int
}

struct RecoveredOvertimePremium {
    var enabled: Bool
    var thresholdMinutes: Int
    var ratePercent: Int
}

struct RecoveredHolidayPremium {
    var enabled: Bool
    var ratePercentByWeekday: [Int]
}

enum InOutRecovered {
    /// `legal_break_defaults` at 0x1000da43c writes these into two BreakRule
    /// values and stores the array at global 0x1005d0a40.
    static let legalBreakRules: [RecoveredBreakRule] = [
        .init(overMinutes: 360, breakMinutes: 45),
        .init(overMinutes: 480, breakMinutes: 60),
    ]

    /// `workplace_defaults` at 0x1000defb8. Constant pool 0x10042d680 is
    /// (1320, 300); the following byte field is 25; the enabled byte is 1.
    /// 1320 and 300 are 22:00 and 05:00 in minutes.
    static let defaultNight = RecoveredNightPremium(
        enabled: true,
        startMinute: 1320,
        endMinute: 300,
        ratePercent: 25
    )

    /// Same function. Constant pool 0x10042d690 is (480, 25); enabled byte is 1.
    /// 480 minutes is 8 hours.
    static let defaultOvertime = RecoveredOvertimePremium(
        enabled: true,
        thresholdMinutes: 480,
        ratePercent: 25
    )

    /// Same function allocates `[Int]` of count 7, zeroes it, and stores enabled = 0.
    static let defaultHoliday = RecoveredHolidayPremium(
        enabled: false,
        ratePercentByWeekday: Array(repeating: 0, count: 7)
    )

    /// Field immediately after holiday in that initializer is the byte 0.
    /// Metadata order matches `Workplace.customBreaks` before `breakRules`.
    static let defaultCustomBreaks = false

    /// Positive minute-of-day. Ghidra simplified 0x1000968c4 to `% 0x5a0`,
    /// adding 1440 when negative, then `/ 0x3c` and remainder.
    static func minuteOfDay(_ absoluteMinutes: Int) -> (hour: Int, minute: Int) {
        var wrapped = absoluteMinutes % 1440
        if wrapped < 0 {
            wrapped += 1440
        }
        let hour = wrapped / 60
        let minute = wrapped - hour * 60
        return (hour, minute)
    }

    /// 0x100027f04 reads a SwiftUI Binding wrapped value, normalizes it with
    /// the same 1440/60 split, then calls
    /// `Calendar.date(bySettingHour:minute:second:of:matchingPolicy:repeatedTimePolicy:direction:)`
    /// with second 0, matchingPolicy `.nextTime`, repeatedTimePolicy `.first`,
    /// direction `.forward`.
    static func date(
        fromMinuteBinding minutes: Int,
        on day: Date,
        calendar: Calendar = .current
    ) -> Date? {
        let parts = minuteOfDay(minutes)
        return calendar.date(
            bySettingHour: parts.hour,
            minute: parts.minute,
            second: 0,
            of: day,
            matchingPolicy: .nextTime,
            repeatedTimePolicy: .first,
            direction: .forward
        )
    }

    /// 0x1001b4a94: `startOfDay`, then `Calendar.Component.day` with values -1 and +2.
    /// wrappingComponents is false. These are two separate dates, not a week-of-year step.
    static func dayWindow(around day: Date, calendar: Calendar = .current) -> (Date?, Date?) {
        let start = calendar.startOfDay(for: day)
        let previous = calendar.date(byAdding: .day, value: -1, to: start, wrappingComponents: false)
        let twoAhead = calendar.date(byAdding: .day, value: 2, to: start, wrappingComponents: false)
        return (previous, twoAhead)
    }

    /// 0x1000837d8: `Calendar.Component.day` with values +14 and -1. wrappingComponents is false.
    static func dayOffsets(from day: Date, calendar: Calendar = .current) -> (Date?, Date?) {
        let ahead = calendar.date(byAdding: .day, value: 14, to: day, wrappingComponents: false)
        let previous = calendar.date(byAdding: .day, value: -1, to: day, wrappingComponents: false)
        return (ahead, previous)
    }

    /// 0x10020499c. `x0` is kept in `x25` and multiplied by 7
    /// (`lsl #3`, `sub`, `smulh` by 7). Overflow goes to `brk #1` at 0x100204ecc.
    /// The component loaded at 0x100204b40 is `Calendar.Component.day` (bind 0x10056bbb8),
    /// not `weekOfYear` (0x10056bbb0). The call at 0x100204bf0 passes that product
    /// as the value, with wrappingComponents false. The base date is the Date in a
    /// SwiftUI `State` (`wrappedValue` is read immediately before the call).
    static func addingWeeks(_ weeks: Int, to stateDate: Date, calendar: Calendar = .current) -> Date? {
        calendar.date(byAdding: .day, value: weeks * 7, to: stateDate, wrappingComponents: false)
    }

    /// 0x100204c68: `cmp` the saved week count with 0, `mov w8, #3`, `csinc w8, w8, wzr, gt`.
    /// Positive weeks store 3. Zero and negative store 1. The byte is then passed to a
    /// `LazyState` setter. These tags are not named in the function.
    static func weekSlideTag(weeks: Int) -> Int {
        weeks > 0 ? 3 : 1
    }

    /// 0x1000e967c. Not original source.
    /// Keeps rules whose `overMinutes` is strictly less than `minutes`
    /// (`cmp` / `b.lt` at 0x1000e9770). Among those, keeps the greatest
    /// `overMinutes`; an equal value does not replace the earlier rule
    /// (`cmp` / `b.ge` at 0x1000e9904). Returns that rule's `breakMinutes`
    /// (metadata field +0x18). No match, or an empty list, returns 0.
    /// This does not compute `minutes`. The two callers prepare it differently;
    /// do not pick one and use it as payslip minutes.
    static func selectedBreakMinutes(_ minutes: Int, rules: [RecoveredBreakRule]) -> Int {
        var best: RecoveredBreakRule?
        for rule in rules where rule.overMinutes < minutes {
            if let current = best, current.overMinutes >= rule.overMinutes {
                continue
            }
            best = rule
        }
        return best?.breakMinutes ?? 0
    }

    /// Caller `0x1001b8770` of the selector, for `ShiftEntryEditor`.
    /// Field-offset vector starts at metadata byte `0x10`. `+0x2c` is `_endMinute`
    /// and `+0x28` is `_startMinute`, both read with `State.wrappedValue`.
    /// `subs` at `0x1001b8870` is end minus start (overflow traps).
    /// The signed remainder of division by 1440 is made non-negative.
    /// A zero remainder, including equal minutes, becomes 1440.
    /// This is the editor input, not a payslip duration.
    static func editorMinuteCount(startMinute: Int, endMinute: Int) -> Int {
        let difference = endMinute - startMinute
        let remainder = difference % 1440
        let positive = remainder < 0 ? remainder + 1440 : remainder
        return positive == 0 ? 1440 : positive
    }

    /// Caller `0x1001cee68` divides the `Double` from `Date.timeIntervalSince`
    /// by 60 and truncates toward zero (`fcvtzs` at `0x1001cf700`).
    /// Which date is the receiver is not identified, so this is only the
    /// conversion of a seconds value the caller already has.
    static func truncatedMinutes(towardZero seconds: Double) -> Int {
        Int(seconds / 60.0)
    }

    /// Same caller, after the ARM64 Swift rule that `self` is `x20`.
    /// `x20` is the slot filled from `endDate` (`0x100406020`).
    /// `x0` is the slot filled from `startDate` (`0x100415060`) on the same object.
    /// The call is `endDate.timeIntervalSince(startDate)`, then truncate toward zero.
    /// Equal instants are 0 minutes, not 1440. This is not `editorMinuteCount`
    /// and not a wage formula.
    static func minutesFromEndDate(since start: Date, end: Date) -> Int {
        truncatedMinutes(towardZero: end.timeIntervalSince(start))
    }
}
