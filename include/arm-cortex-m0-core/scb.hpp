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

namespace ArmCortex::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID; //!< Processor part number, version, and implementation information.
        volatile uint32_t ICSR; //!< Interrupt control and state register.
        volatile uint32_t RESERVED0;
        volatile uint32_t AIRCR; //!< Application interrupt and reset control register.
        volatile uint32_t SCR; //!< Low power state control.
        volatile uint32_t CCR; //!< Configuration and control register (read-only).
        volatile uint32_t RESERVED1;
        volatile uint32_t SHPR2; //!< System handler priority register (SVCall).
        volatile uint32_t SHPR3; //!< System handler priority register (PendSV, SysTick).
        volatile uint32_t SHCSR; //!< System handler control and state register.
    };

    //! Processor part number, version, and implementation information.
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!< Patch release (p in Rnpn).
            uint32_t PARTNO: 12; //!< Part number (0xC20: Cortex-M0).
            uint32_t ARCHITECTURE: 4; //!< Architecture (0xC: ARMv6-M).
            uint32_t VARIANT: 4; //!< Variant number (r in Rnpn).
            uint32_t IMPLEMENTER: 8; //!< Implementer code (0x41: ARM).
        } bits;

        uint32_t value = 0;

        CPUID() = default;

        CPUID(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Interrupt control and state register.
    //! Provides set/clear-pending bits for NMI, PendSV, and SysTick exceptions.
    //! Indicates active and pending exception numbers.
    //! \note Do not simultaneously set both set and clear bits for the same exception.
    union ICSR {
        struct Bits {
            uint32_t VECTACTIVE: 9; //!< Active exception number.
            uint32_t RESERVED0: 3;
            uint32_t VECTPENDING: 9; //!< Highest priority pending exception number (0: none).
            uint32_t RESERVED1: 1;
            uint32_t ISRPENDING: 1; //!< Interrupt pending (excluding NMI and faults).
            uint32_t ISRPREEMPT: 1; //!< Preempted exception is active.
            uint32_t RESERVED2: 1;
            uint32_t PENDSTCLR: 1; //!< Write 1 to clear SysTick pending state (write-only).
            uint32_t PENDSTSET: 1; //!< SysTick pending (read), write 1 to set pending.
            uint32_t PENDSVCLR: 1; //!< Write 1 to clear PendSV pending state (write-only).
            uint32_t PENDSVSET: 1; //!< PendSV pending (read), write 1 to set pending.
            uint32_t RESERVED3: 2;
            uint32_t NMIPENDSET: 1; //!< NMI pending (read), write 1 to set pending.
        } bits;

        uint32_t value = 0;

        ICSR() = default;

        ICSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Application interrupt and reset control register.
    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!< Write key to enable AIRCR writes.

        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTCLRACTIVE: 1; //!< Reserved. Write 0.
            uint32_t SYSRESETREQ: 1; //!< System reset request.
            uint32_t RESERVED1: 12;
            uint32_t ENDIANNESS: 1; //!< Data endianness (0: little endian).
            uint32_t VECTKEY: 16; //!< Write VECTKEY_VALUE to enable writes, otherwise ignored.
        } bits;

        uint32_t value = 0;

        AIRCR() = default;

        AIRCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System control register - low power state configuration.
    union SCR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SLEEPONEXIT: 1; //!< Enter sleep/deep sleep on ISR return to Thread mode.
            uint32_t SLEEPDEEP: 1; //!< Use deep sleep instead of sleep.
            uint32_t RESERVED1: 1;
            uint32_t SEVONPEND: 1; //!< Wake from WFE on any interrupt (including disabled).
            uint32_t RESERVED2: 27;
        } bits;

        uint32_t value = 0;

        SCR() = default;

        SCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Configuration and control register (read-only).
    union CCR {
        struct Bits {
            uint32_t RESERVED0: 3;
            uint32_t UNALIGN_TRP: 1; //!< Always 1. All unaligned accesses generate HardFault.
            uint32_t RESERVED1: 5;
            uint32_t STKALIGN: 1; //!< Always 1. 8-byte stack alignment on exception entry.
            uint32_t RESERVED2: 22;
        } bits;

        uint32_t value = 0;

        CCR() = default;

        CCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System handler priority register 2 (SVCall priority).
    union SHPR2 {
        struct Bits {
            uint32_t RESERVED0: 24;
            uint32_t PRI_11: 8; //!< SVCall priority (exception 11).
        } bits;

        uint32_t value = 0;

        SHPR2() = default;

        SHPR2(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System handler priority register 3 (PendSV and SysTick priorities).
    union SHPR3 {
        struct Bits {
            uint32_t RESERVED0: 16;
            uint32_t PRI_14: 8; //!< PendSV priority (exception 14).
            uint32_t PRI_15: 8; //!< SysTick priority (exception 15).
        } bits;

        uint32_t value = 0;

        SHPR3() = default;

        SHPR3(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System handler control and state register.
    union SHCSR {
        struct Bits {
            uint32_t RESERVED0: 15;
            uint32_t SVCALLPENDED: 1; //!< SVCall pending state.
            uint32_t RESERVED1: 16;
        } bits;

        uint32_t value = 0;

        SHCSR() = default;

        SHCSR(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace ArmCortex {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace ArmCortex::Scb {
    [[gnu::noreturn, gnu::always_inline]] static inline void systemReset()
    {
        asm volatile("dsb sy" ::: "memory");

        AIRCR aircr { SCB->AIRCR };

        aircr.bits.VECTCLRACTIVE = 0;
        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB->AIRCR = aircr.value;

        asm volatile("dsb sy" ::: "memory");
        asm volatile("isb sy" ::: "memory");

        while(true);
    }

    // =========================================================================
    // ICSR W1S/W1C Helper Functions
    // =========================================================================

    //! Check if SysTick exception is pending.
    [[gnu::always_inline]] static inline bool isSysTickPending()
    {
        ICSR icsr { SCB->ICSR };
        return icsr.bits.PENDSTSET;
    }

    //! Set SysTick exception pending. PENDSTSET is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setSysTickPending()
    {
        constexpr uint32_t PENDSTSET_BIT = uint32_t{1} << 26;
        SCB->ICSR = PENDSTSET_BIT;
    }

    //! Clear SysTick exception pending. PENDSTCLR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearSysTickPending()
    {
        constexpr uint32_t PENDSTCLR_BIT = uint32_t{1} << 25;
        SCB->ICSR = PENDSTCLR_BIT;
    }

    //! Check if PendSV exception is pending.
    [[gnu::always_inline]] static inline bool isPendSVPending()
    {
        ICSR icsr { SCB->ICSR };
        return icsr.bits.PENDSVSET;
    }

    //! Set PendSV exception pending. PENDSVSET is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setPendSV()
    {
        constexpr uint32_t PENDSVSET_BIT = uint32_t{1} << 28;
        SCB->ICSR = PENDSVSET_BIT;
    }

    //! Clear PendSV exception pending. PENDSVCLR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearPendSV()
    {
        constexpr uint32_t PENDSVCLR_BIT = uint32_t{1} << 27;
        SCB->ICSR = PENDSVCLR_BIT;
    }

    //! Check if NMI exception is pending.
    [[gnu::always_inline]] static inline bool isNMIPending()
    {
        ICSR icsr { SCB->ICSR };
        return icsr.bits.NMIPENDSET;
    }

    //! Trigger NMI exception. NMIPENDSET is W1S (write-1-to-set).
    //! \note NMI cannot be cleared by software once set.
    [[gnu::always_inline]] static inline void triggerNMI()
    {
        constexpr uint32_t NMIPENDSET_BIT = uint32_t{1} << 31;
        SCB->ICSR = NMIPENDSET_BIT;
    }
}
