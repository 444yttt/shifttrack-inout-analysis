# Ghidra pseudocode

These files are Ghidra 11.4 PUBLIC headless output (Linux, JDK 21) after importing `bin/IN-OUT` with the Mach-O loader. The loader reported 36904 `DYLD_CHAINED_PTR_64_OFFSET` chained pointers.

This is decompiler pseudocode. It is not the original Swift source. Register and stack assignments in the larger functions are noisy; the constants and Foundation/SwiftUI symbols cited in `notes/FINDINGS.md` were checked against the instruction bytes as well.

`workplace_defaults.c` is the long initializer at 0x1000defb8. Only the stores described in FINDINGS are used. The rest of that file is not a payroll formula.
