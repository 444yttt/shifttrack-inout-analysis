import Foundation

/// Reconstructed from `bin/IN-OUT`. This is not the original Swift source,
/// not a paste of Ghidra output, and not a feature imitation of screens whose
/// calculation was not found.
///
/// Ghidra pseudocode for the same addresses is in `notes/ghidra/`.
/// Week shifting is the checked multiply at 0x10020499c.
/// Break selection is the comparison at 0x1000e967c. It takes minutes already
/// computed; it does not define how those minutes are produced.
/// PayRounding, the on-shift break scale, and the hourly yen expression in
/// 0x10011b1d0 are reconstructed below. They are not the original source.
/// Allowance and deduction amounts are not closed. Do not fill those in.
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

/// `RoundingDirection` case order is exact, up, down, nearest.
/// Raw values 0, 1, 2 match the compares in 0x10011b1d0. Any other byte,
/// including nearest, takes `frinta`.
enum RecoveredRoundingDirection: UInt8 {
    case exact = 0
    case up = 1
    case down = 2
    case nearest = 3
}

/// `PayRounding` is `unitMinutes` then the two direction bytes at +8 and +9.
/// `PayTerms.rounding` is field 6 (metadata +0x28).
struct RecoveredPayRounding {
    var unitMinutes: Int
    var start: RecoveredRoundingDirection
    var end: RecoveredRoundingDirection
}

extension InOutRecovered {
    /// 0x10011b4a4 through 0x10011b520, repeated for the end byte at 0x10011b560.
    /// `unitMinutes < 2` or direction `exact` (byte 0) copies the original instant.
    /// Otherwise `unitSeconds = unitMinutes * 60` (the multiply is checked and traps
    /// on overflow; this reconstruction does not trap). Seconds are
    /// `date.timeIntervalSince(startOfDay)`. Divide by the unit, then
    /// up = `frintp`, down = `frintm`, anything else = `frinta`, and add the
    /// rounded seconds back onto that same start of day.
    /// This is not a 1440-minute wrap. A negative `timeIntervalSince(startOfDay)`
    /// was not observed on a device; the floating-point ops still accept one.
    static func roundedSecondsFromStartOfDay(
        _ seconds: Double,
        unitMinutes: Int,
        direction: RecoveredRoundingDirection
    ) -> Double {
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

    /// Same passes. The first pass reads `PayRounding.start` (byte +8) and the
    /// second reads `PayRounding.end` (byte +9). Each date is rounded against
    /// its own `startOfDay`. Skipping the round returns that date unchanged.
    static func roundedDate(
        _ date: Date,
        unitMinutes: Int,
        direction: RecoveredRoundingDirection,
        calendar: Calendar = .current
    ) -> Date {
        let start = calendar.startOfDay(for: date)
        let seconds = roundedSecondsFromStartOfDay(
            date.timeIntervalSince(start),
            unitMinutes: unitMinutes,
            direction: direction
        )
        if seconds == date.timeIntervalSince(start) {
            return date
        }
        return start.addingTimeInterval(seconds)
    }

    /// 0x10026ea84 reads `TimelineView.Context.date`. The compare is
    /// `shiftEnd < now` (`x0` is the end, `x1` is now). The date copied into
    /// the second `timeIntervalSince` is `shiftEnd` when that compare is true,
    /// and `now` otherwise. Equal instants stay on `now`.
    static func liveAsOf(now: Date, shiftEnd: Date) -> Date {
        shiftEnd < now ? shiftEnd : now
    }

    /// 0x10026eb24. `d8` is `end.timeIntervalSince(start)`. `<= 0` stores 0
    /// (`mov x20, #0`). Otherwise `d9` is `ShiftInstance.breakMinutes`
    /// (metadata +0x38) as a Double, and the second interval is
    /// `asOf.timeIntervalSince(start)`.
    /// `frinta` then `fcvtzs` (toward zero of an already-integral value).
    /// The integer is stored at `WorkRecord.breakMinutes` (metadata +0x20).
    /// The record's start and end are still the shift's original dates.
    /// This is the break fed to payroll. It is not itself a yen amount.
    /// A negative elapsed value stays negative; that path was not seen on screen.
    static func scaledBreakMinutes(start: Date, end: Date, asOf: Date, breakMinutes: Int) -> Int {
        let duration = end.timeIntervalSince(start)
        if duration <= 0 {
            return 0
        }
        let elapsed = asOf.timeIntervalSince(start)
        let scaled = (elapsed * Double(breakMinutes) / duration).rounded(.toNearestOrAwayFromZero)
        return Int(scaled)
    }

    /// 0x10011b848. The seconds are `end.timeIntervalSince(start)` of the
    /// WorkRecord. If any BreakSpan is present the fraction stays 1 and those
    /// spans are skipped one minute at a time. Otherwise the fraction is
    /// `max(0, minutes - breakMinutes) / minutes`, or 0 when minutes <= 0.
    static func paidMinuteFraction(totalSeconds: Double, breakMinutes: Int, hasBreakSpans: Bool) -> Double {
        if hasBreakSpans {
            return 1
        }
        let minutes = totalSeconds / 60
        if minutes <= 0 {
            return 0
        }
        let paid = minutes - Double(breakMinutes)
        return (paid >= 0 ? paid : 0) / minutes
    }

    /// 0x10011bf14. `scvtf` of the hourly integer, divide by 60, multiply by
    /// the slice's paid minutes, add to `PayResult.base` (offset +8).
    /// The hourly integer is `WageBand.hourlyWage` when the slice midpoint's
    /// minute-of-day falls in a band, otherwise the `Int` returned by
    /// 0x1000de424 (wage history, labeled 時給).
    static func hourlyYen(paidMinutes: Double, hourlyWage: Int) -> Double {
        paidMinutes * Double(hourlyWage) / 60
    }

    /// No BreakSpans. The engine walks the record's own start and end, so
    /// `totalSeconds` is the scheduled interval. A live call changes
    /// `breakMinutes` and does not replace the end with now.
    static func scheduledHourlyYen(totalSeconds: Double, breakMinutes: Int, hourlyWage: Int) -> Double {
        let fraction = paidMinuteFraction(
            totalSeconds: totalSeconds,
            breakMinutes: breakMinutes,
            hasBreakSpans: false
        )
        return hourlyYen(paidMinutes: (totalSeconds / 60) * fraction, hourlyWage: hourlyWage)
    }

    /// 0x10011bd08. `start == end` is not a window. `start < end` is
    /// `start <= minute < end`. Otherwise the window wraps midnight.
    static func minuteIsInPremiumWindow(minuteOfDay: Int, start: Int, end: Int) -> Bool {
        if start == end {
            return false
        }
        if start < end {
            return minuteOfDay >= start && minuteOfDay < end
        }
        return minuteOfDay >= start || minuteOfDay < end
    }

    /// 0x10011c168. Added to `PayResult.premium` (+0x10) only for a slice
    /// already inside the night window, when night is enabled, the matching
    /// band does not set `includesNightPremium`, and the rate is not 0.
    /// The slice yen is the same value added to base.
    static func nightPremiumYen(
        sliceYen: Double,
        ratePercent: Int,
        enabled: Bool,
        inWindow: Bool,
        bandIncludesNight: Bool
    ) -> Double {
        if enabled && inWindow && !bandIncludesNight && ratePercent != 0 {
            return sliceYen * Double(ratePercent) / 100
        }
        return 0
    }

    /// 0x10011c454. `priorMinutes` is the Double pointed at by argument x2.
    /// Minutes at or below the threshold contribute 0. A slice that crosses
    /// the threshold contributes only the part above it. Once prior minutes
    /// are already past the threshold, the whole slice counts.
    static func overtimeMinutes(sliceMinutes: Double, priorMinutes: Double, threshold: Double) -> Double {
        let under = threshold - priorMinutes
        let capped = under < sliceMinutes ? under : sliceMinutes
        if capped < 0 {
            return sliceMinutes
        }
        let extra = sliceMinutes - capped
        return extra > 0 ? extra : 0
    }

    /// 0x10011c684. `premium += overtimeMinutes * hourly / 60 * rate / 100`.
    static func overtimePremiumYen(overtimeMinutes: Double, hourlyWage: Int, ratePercent: Int) -> Double {
        if ratePercent == 0 || overtimeMinutes == 0 {
            return 0
        }
        return overtimeMinutes * Double(hourlyWage) / 60 * Double(ratePercent) / 100
    }

    /// 0x10011c420 then 0x10011c4b4. Weekday comes from `DateComponents.weekday`.
    /// The index is that value minus 1. A missing weekday or an index outside
    /// the array applies no holiday premium here.
    static func holidayRatePercent(weekday: Int?, rates: [Int]) -> Int? {
        guard let weekday else { return nil }
        let index = weekday - 1
        guard index >= 0, index < rates.count else { return nil }
        return rates[index]
    }

    /// 0x10011c4c0. `sliceYen * rate / 100`, added to premium.
    static func holidayPremiumYen(sliceYen: Double, ratePercent: Int) -> Double {
        sliceYen * Double(ratePercent) / 100
    }

    /// 0x10011a3f4. `PayMethod.daily` is byte 1. The integer at
    /// `PayTerms.dailyWage` (metadata +0x1c) is added to base. An extra low
    /// bit must also be 1; the field that bit comes from was not identified,
    /// so the caller passes it in rather than guessing.
    static func baseAfterDailyWage(base: Double, dailyWage: Int, methodIsDaily: Bool, flagBit: Bool) -> Double {
        guard methodIsDaily, flagBit else { return base }
        return base + Double(dailyWage)
    }

    /// 0x10011acd0. `ExtraPayItem.kind == transport` (byte 0) and
    /// `amount >= 1` adds that integer to `PayResult.transport` (+0x20).
    /// Allowance and deduction are not this add.
    static func transportAfterExtra(transport: Double, amount: Int, kindIsTransport: Bool) -> Double {
        guard kindIsTransport, amount >= 1 else { return transport }
        return transport + Double(amount)
    }

    /// 0x10026ecf0 loads `PayResult.base` and `.premium`, adds them, and
    /// 0x10026efb0 passes the sum to `ContentTransition.numericText(value:)`.
    /// Transport, allowance, and deduction are not in this sum.
    static func liveNumericTotal(base: Double, premium: Double) -> Double {
        base + premium
    }
}
