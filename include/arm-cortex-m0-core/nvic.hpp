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

#include "./bit_utils.hpp"
#include <cstdint>

namespace ArmCortex::Nvic {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E100u;

    struct Registers
    {
        volatile uint32_t ISER; //!< Interrupt set-enable register (W1S).
        volatile uint32_t RESERVED0[31];
        volatile uint32_t ICER; //!< Interrupt clear-enable register (W1C).
        volatile uint32_t RESERVED1[31];
        volatile uint32_t ISPR; //!< Interrupt set-pending register (W1S).
        volatile uint32_t RESERVED2[31];
        volatile uint32_t ICPR; //!< Interrupt clear-pending register (W1C).
        volatile uint32_t RESERVED3[31];
        volatile uint32_t RESERVED4[64];
        volatile uint8_t IPR[32]; //!< Interrupt priority registers (byte-accessible).
    };
}

namespace ArmCortex {
    inline volatile Nvic::Registers* const NVIC = reinterpret_cast<volatile Nvic::Registers*>(Nvic::BASE_ADDRESS);
}

namespace ArmCortex::Nvic {
    [[gnu::always_inline]] static inline bool isIrqEnabled(uint8_t irq_number)
    {
        return ArmCortex::isBitSet(NVIC->ISER, irq_number);
    }

    //! Enable an interrupt. ISER is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void enableIrq(uint8_t irq_number)
    {
        NVIC->ISER = uint32_t{1} << irq_number;
    }

    //! Disable an interrupt. ICER is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void disableIrq(uint8_t irq_number)
    {
        NVIC->ICER = uint32_t{1} << irq_number;
    }

    [[gnu::always_inline]] static inline bool isIrqPending(uint8_t irq_number)
    {
        return ArmCortex::isBitSet(NVIC->ISPR, irq_number);
    }

    //! Set an interrupt pending. ISPR is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setPendingIrq(uint8_t irq_number)
    {
        NVIC->ISPR = uint32_t{1} << irq_number;
    }

    //! Clear a pending interrupt. ICPR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearPendingIrq(uint8_t irq_number)
    {
        NVIC->ICPR = uint32_t{1} << irq_number;
    }
}
