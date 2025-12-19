# arm-cortex-m0-core

A minimal, header-only C++20 library for accessing ARM Cortex-M0 core peripherals. No dependencies, no opinions — just drop it into your project.

## Usage

Copy the library into your project (e.g., into `lib/`) and add it via CMake:

```cmake
add_subdirectory(lib/arm-cortex-m0-core)
target_link_libraries(your_target PRIVATE arm-cortex-m0-core)
```

Then include what you need:

```cpp
#include <arm-cortex-m0-core/nvic.hpp>
#include <arm-cortex-m0-core/systick.hpp>

int main() {
    // Enable IRQ 5
    ArmCortex::Nvic::enableIrq(5);

    // Configure SysTick
    ArmCortex::SYS_TICK->LOAD = 48000 - 1;  // 1ms @ 48MHz
    ArmCortex::SYS_TICK->VAL = 0;
    ArmCortex::SYS_TICK->CTRL = 0x07;       // Enable, interrupt, CPU clock

    while (true) {}
}
```

## Contents

| File | Description |
|------|-------------|
| `nvic.hpp` | NVIC (Nested Vectored Interrupt Controller) — enable/disable IRQs, set/clear pending, priority registers |
| `scb.hpp` | SCB (System Control Block) — CPUID, interrupt control, reset, sleep modes, system handler priorities |
| `systick.hpp` | SysTick timer — 24-bit countdown timer for RTOS ticks or delays |
| `special_regs.hpp` | CPU special registers — PSR, PRIMASK, CONTROL, MSP/PSP access via inline assembly |
| `exceptions.hpp` | Exception numbers — enum for Reset, NMI, HardFault, SVCall, PendSV, SysTick, IRQs |
| `bit_utils.hpp` | Bit manipulation helpers — `isBitSet()`, `setBit()`, `clearBit()` |

## Licence

This library is licensed under the Apache License Version 2.0.  
Copyright (C) 2025 The Embedded Society <https://github.com/embedded-society/arm-cortex-m0-core>.  
See the attached [LICENCE](./LICENCE) file for more info.
