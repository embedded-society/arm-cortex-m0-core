/*
    Copyright (C) 2025 The Embedded Society <https://github.com/embedded-society/arm-cortex-m0-core>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace ArmCortex {
    inline constexpr uint8_t NUM_OF_IRQS = 32;

    enum class ExceptionNumber : uint8_t {
        THREAD_MODE = 0,
        RESET = 1,
        NMI = 2,
        HARD_FAULT = 3,
        SV_CALL = 11,
        PEND_SV = 14,
        SYS_TICK = 15,
        FIRST_IRQ = 16,
        LAST_IRQ = FIRST_IRQ + NUM_OF_IRQS - 1
    };

    static constexpr bool isIrqNumber(uint8_t exception)
    {
        return ((exception >= static_cast<uint8_t>(ExceptionNumber::FIRST_IRQ)) &&
            (exception <= static_cast<uint8_t>(ExceptionNumber::LAST_IRQ)));
    }
}
