/// Boundary checks for the comparison at 0x1000e967c.
/// Not the original Swift source. Minutes are an input; this file does not
/// decide whether they came from seconds/60 or from a 1440-minute wrap.

struct Rule {
    var overMinutes: Int
    var breakMinutes: Int
}

func selectedBreakMinutes(_ minutes: Int, rules: [Rule]) -> Int {
    var best: Rule?
    for rule in rules where rule.overMinutes < minutes {
        if let current = best, current.overMinutes >= rule.overMinutes {
            continue
        }
        best = rule
    }
    return best?.breakMinutes ?? 0
}

func expect(_ condition: Bool, _ message: String) {
    if !condition {
        fputs("FAIL \(message)\n", stderr)
        exit(1)
    }
}

let legal = [Rule(overMinutes: 360, breakMinutes: 45), Rule(overMinutes: 480, breakMinutes: 60)]
expect(selectedBreakMinutes(360, rules: legal) == 0, "360 is not over 360")
expect(selectedBreakMinutes(361, rules: legal) == 45, "361 selects 45")
expect(selectedBreakMinutes(480, rules: legal) == 45, "480 still selects 45")
expect(selectedBreakMinutes(481, rules: legal) == 60, "481 selects 60")
expect(selectedBreakMinutes(0, rules: legal) == 0, "zero")
expect(selectedBreakMinutes(-5, rules: legal) == 0, "negative")
expect(
    selectedBreakMinutes(101, rules: [
        Rule(overMinutes: 100, breakMinutes: 10),
        Rule(overMinutes: 100, breakMinutes: 99),
    ]) == 10,
    "tie keeps the earlier rule"
)
expect(selectedBreakMinutes(50, rules: []) == 0, "empty")
print("break selection tests passed")
