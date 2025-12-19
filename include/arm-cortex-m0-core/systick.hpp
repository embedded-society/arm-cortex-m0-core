/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache Licence, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the Licence.
    You may obtain a copy of the Licence at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the Licence is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the Licence for the specific language governing permissions and
    limitations under the Licence.
*/

#pragma once

#include <cstdint>

namespace ArmCortex::SysTick {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E010u;

    struct Registers
    {
        volatile uint32_t CTRL; //!< Control and status register.
        volatile uint32_t LOAD; //!< Reload value.
        volatile uint32_t VAL; //!< Current counter value.
        volatile uint32_t CALIB; //!< Calibration value register.
    };

    union CTRL {
        //! Timer clock source selection.
        enum class CLKSOURCE : bool {
            EXTERNAL = false, //!< External reference clock.
            CPU = true //!< Processor clock.
        };

        struct Bits {
            uint32_t ENABLE: 1; //!< Counter enable (counts down, reloads on zero, sets COUNTFLAG).
            uint32_t TICKINT: 1; //!< SysTick exception request on count to zero.
            uint32_t CLKSOURCE: 1; //!< Clock source (0: external, 1: processor).
            uint32_t RESERVED0: 13;
            uint32_t COUNTFLAG: 1; //!< Timer counted to zero since last read (read clears).
            uint32_t RESERVED1: 15;
        } bits;

        uint32_t value = 0;

        CTRL() = default;

        CTRL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Calibration value register.
    //! \note TENMS reads as zero (calibration value unknown).
    union CALIB {
        struct Bits {
            uint32_t TENMS: 24; //!< Calibration value for 10ms (reads as 0: unknown).
            uint32_t RESERVED: 6;
            uint32_t SKEW: 1; //!< Reads as 1: 10ms calibration value is inexact.
            uint32_t NOREF: 1; //!< Reads as 1: No separate reference clock provided.
        } bits;

        uint32_t value = 0;

        CALIB() = default;

        CALIB(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace ArmCortex {
    inline volatile SysTick::Registers* const SYS_TICK = reinterpret_cast<volatile SysTick::Registers*>(SysTick::BASE_ADDRESS);
}
