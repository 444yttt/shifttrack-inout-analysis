/// Not original Swift source.
/// Editor path: ShiftEntryEditor end minute minus start minute, then the
/// 1440-minute normalization at 0x1001b8a28. Equal minutes become 1440.
/// Date path: only the toward-zero conversion of an already computed seconds
/// value. Do not use either function as payslip minutes.

func editorMinuteCount(startMinute: Int, endMinute: Int) -> Int {
    let difference = endMinute - startMinute
    let remainder = difference % 1440
    let positive = remainder < 0 ? remainder + 1440 : remainder
    return positive == 0 ? 1440 : positive
}

func truncatedMinutes(towardZero seconds: Double) -> Int {
    Int(seconds / 60.0)
}

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fatalError(message)
    }
}

expect(editorMinuteCount(startMinute: 540, endMinute: 1020) == 480, "eight hours")
expect(editorMinuteCount(startMinute: 1320, endMinute: 360) == 480, "overnight eight hours")
expect(editorMinuteCount(startMinute: 1320, endMinute: 361) == 481, "overnight just over eight hours")
expect(editorMinuteCount(startMinute: 100, endMinute: 100) == 1440, "equal minutes are 24 hours")
expect(editorMinuteCount(startMinute: 100, endMinute: 99) == 1439, "one minute before is almost 24 hours")
expect(editorMinuteCount(startMinute: 0, endMinute: 1) == 1, "one minute")
expect(truncatedMinutes(towardZero: 3599.9) == 59, "truncate fraction")
expect(truncatedMinutes(towardZero: 3600) == 60, "exact hour")
expect(truncatedMinutes(towardZero: -119) == -1, "negative truncates toward zero")
print("minute input tests passed")
