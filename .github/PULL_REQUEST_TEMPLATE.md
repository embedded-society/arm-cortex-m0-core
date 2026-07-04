## Description

Brief description of the changes in this PR.

## Related Issue

Fixes #(issue number)

## Type of Change

- [ ] Bug fix (non-breaking change that fixes an issue)
- [ ] New feature (non-breaking change that adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update
- [ ] Refactoring (no functional changes)
- [ ] CI/CD changes

## Testing

The C++ here is compiled and exercised by the
[`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests) superproject, not in this
repo. Confirm the suite stays green for the `M0` target:

- [ ] I built the `arm-cortex-mx-core-tests` suite with this branch for the `M0` target and **all tests pass**
- [ ] If this change alters the public API or a register layout, I opened a **companion PR** to `arm-cortex-mx-core-tests`
      that updates/adds tests, and linked it below
- [ ] I ran `clang-format -i include/arm-cortex-m0-core/*.hpp` and the headers are unchanged by it

**Companion tests PR (if any):** <!-- link to the arm-cortex-mx-core-tests PR, or "n/a" -->

**Environment used:**

- Compiler and version: <!-- e.g. arm-none-eabi-gcc 13.3.1; LLVM clang 19.1.0 -->
- Target device / Cortex-M0 part: <!-- e.g. STM32F0, RP2040 core, ... -->

## Code Quality

- [ ] No trailing whitespace; final newline present (`.editorconfig`)
- [ ] British spelling used in comments and documentation (see [STYLE.md](../STYLE.md))
- [ ] C++ and register-map conventions match [STYLE.md](../STYLE.md), checked against the ARM datasheet where relevant

## Additional Notes

Any additional context reviewers should know.
