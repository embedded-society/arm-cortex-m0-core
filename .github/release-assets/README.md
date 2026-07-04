# arm-cortex-m0-core __VERSION__

CMSIS-like header-only C++20 library for accessing ARM Cortex-M0 core peripherals.

This archive contains just the library and its licence. The full project — documentation, issue tracker, and
contribution guide — lives on GitHub:

<https://github.com/embedded-society/arm-cortex-m0-core>

## What's in this bundle

| Path | Purpose |
|------|---------|
| `include/arm-cortex-m0-core/` | The library headers (`nvic.hpp`, `scb.hpp`, `systick.hpp`, `special_regs.hpp`, `exceptions.hpp`, `bit_utils.hpp`). |
| `CMakeLists.txt` | Defines the `arm-cortex-m0-core` `INTERFACE` CMake target. |
| `CHANGELOG.md` | Release history. |
| `LICENCE` | Apache License 2.0. |

## Usage

Drop the bundle into your project (e.g. into `lib/arm-cortex-m0-core/`) and add it via CMake:

```cmake
add_subdirectory(lib/arm-cortex-m0-core)
target_link_libraries(your_target PRIVATE arm-cortex-m0-core)
```

Then include what you need:

```cpp
#include <arm-cortex-m0-core/nvic.hpp>
#include <arm-cortex-m0-core/systick.hpp>

ArmCortex::Nvic::enableIrq(5);
```

Requires a C++20 cross-compiler targeting `arm-none-eabi`. See the project page for the full API reference.

## Verifying this download

This archive ships with a signed build-provenance attestation. To confirm it was produced by the project's own
release workflow and has not been tampered with, run (needs the [GitHub CLI](https://cli.github.com/)):

```bash
gh attestation verify arm-cortex-m0-core-__VERSION__.zip --repo embedded-society/arm-cortex-m0-core
```

## Contributing

This is an open project and contributions are very welcome. If you have a suggestion, spot a bug, or want another
register or peripheral supported, please open an issue or pull request — it genuinely helps:

<https://github.com/embedded-society/arm-cortex-m0-core/issues>

Thank you for using arm-cortex-m0-core! 🙏
