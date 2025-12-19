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
    //! Exception return values saved to LR on exception entry.
    enum class LrExceptionReturnValue : uint32_t {
        HANDLER = 0xFFFFFFF1, //!< Return to Handler mode, use MSP.
        THREAD_MSP = 0xFFFFFFF9, //!< Return to Thread mode, use MSP.
        THREAD_PSP = 0xFFFFFFFD //!< Return to Thread mode, use PSP.
    };

    union PSR {
        struct Bits {
            uint32_t ISR: 9; //!< Current exception number.
            uint32_t RESERVED0: 15;
            uint32_t T: 1; //!< Thumb mode flag.
            uint32_t RESERVED1: 3;
            uint32_t V: 1; //!< Overflow flag.
            uint32_t C: 1; //!< Carry/borrow flag.
            uint32_t Z: 1; //!< Zero flag.
            uint32_t N: 1; //!< Negative flag.
        } bits;

        uint32_t value = 0;

        PSR() = default;

        PSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union PRIMASK {
        struct Bits {
            uint32_t PRIMASK: 1; //!< Disable all exceptions except NMI and HardFault.
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        PRIMASK() = default;

        PRIMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union CONTROL {
        //! Active stack pointer selection.
        enum class SPSEL : bool {
            MSP = false, //!< Main stack pointer.
            PSP = true //!< Process stack pointer.
        };

        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SPSEL: 1; //!< Active stack pointer (0: MSP, 1: PSP).
            uint32_t RESERVED1: 30;
        } bits;

        uint32_t value = 0;

        CONTROL() = default;

        CONTROL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    [[gnu::always_inline]] static inline uint32_t getLr()
    {
        uint32_t value;
        asm volatile("MOV %0, LR" : "=r" (value) : : "cc");
        return value;
    }

    [[gnu::always_inline]] static inline PSR getApsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, APSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getIpsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getEpsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, EPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getIepsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IEPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getIapsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getEapsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, EAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline PSR getPsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, PSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    [[gnu::always_inline]] static inline uint32_t getMspReg()
    {
        uint32_t value;
        asm volatile("MRS %0, MSP" : "=r" (value) : : "cc");
        return value;
    }

    [[gnu::always_inline]] static inline void setMspReg(uint32_t value)
    {
        asm volatile("MSR MSP, %0" : : "r" (value) : "cc", "memory");
    }

    [[gnu::always_inline]] static inline uint32_t getPspReg()
    {
        uint32_t value;
        asm volatile("MRS %0, PSP" : "=r" (value) : : "cc");
        return value;
    }

    [[gnu::always_inline]] static inline void setPspReg(uint32_t value)
    {
        asm volatile("MSR PSP, %0" : : "r" (value) : "cc", "memory");
    }

    [[gnu::always_inline]] static inline PRIMASK getPrimaskReg()
    {
        PRIMASK primask;
        asm volatile("MRS %0, PRIMASK" : "=r" (primask.value) : : "cc");
        return primask;
    }

    [[gnu::always_inline]] static inline void setPrimaskReg(PRIMASK primask)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (primask.value) : "cc", "memory");
    }

    [[gnu::always_inline]] static inline CONTROL getControlReg()
    {
        CONTROL control;
        asm volatile("MRS %0, CONTROL" : "=r" (control.value) : : "cc");
        return control;
    }

    [[gnu::always_inline]] static inline void setControlReg(CONTROL control)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (control.value) : "cc", "memory");
    }
}
