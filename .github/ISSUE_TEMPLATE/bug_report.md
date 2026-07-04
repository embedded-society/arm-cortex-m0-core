---
name: Bug Report
about: Report a bug to help us improve
title: '[BUG] '
labels: bug
assignees: ''
---

## Bug Description

A clear and concise description of what the bug is (e.g. a wrong register address, incorrect bit layout, or an
accessor that misbehaves).

## Steps to Reproduce

1.
2.
3.

If possible, include a **minimal code snippet** that uses the library and reproduces the problem.

## Expected Behaviour

What you expected to happen (e.g. which register/bit should have been written, referencing the ARM datasheet if relevant).

## Actual Behaviour

What actually happened. Include the observed hardware behaviour, disassembly, or compiler diagnostics where relevant.

## Error Messages / Logs

```text
Paste any compiler errors, warnings, or relevant disassembly here.
```

## Environment

- **Compiler and version:** <!-- e.g. arm-none-eabi-gcc 13.3.1; LLVM clang 19.1.0 -->
- **Target device:** <!-- e.g. specific Cortex-M0 MCU part number -->
- **Header(s) involved:** <!-- e.g. nvic.hpp, systick.hpp -->
- **Compile flags:** <!-- e.g. -mcpu=cortex-m0 -mthumb -Os -->
- **Library commit / version:** <!-- short SHA or tag of arm-cortex-m0-core -->

## Additional Context

Add any other context about the problem here (e.g. build system, optimisation level, linker script specifics).
