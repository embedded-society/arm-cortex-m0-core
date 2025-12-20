/*
 * CodeQL Analysis Stub
 *
 * This file instantiates templates and exercises the library's API
 * to enable static analysis by CodeQL. It is not meant to be executed,
 * only compiled for analysis purposes.
 */

#include <arm-cortex-m0-core/bit_utils.hpp>
#include <arm-cortex-m0-core/exceptions.hpp>
#include <arm-cortex-m0-core/nvic.hpp>
#include <arm-cortex-m0-core/scb.hpp>
#include <arm-cortex-m0-core/special_regs.hpp>
#include <arm-cortex-m0-core/systick.hpp>

// Force template instantiation for bit_utils
template bool ArmCortex::isBitSet<uint8_t>(uint8_t, uint8_t);
template bool ArmCortex::isBitSet<uint16_t>(uint16_t, uint8_t);
template bool ArmCortex::isBitSet<uint32_t>(uint32_t, uint8_t);
template void ArmCortex::setBit<uint8_t>(uint8_t&, uint8_t);
template void ArmCortex::setBit<uint16_t>(uint16_t&, uint8_t);
template void ArmCortex::setBit<uint32_t>(uint32_t&, uint8_t);
template void ArmCortex::clearBit<uint8_t>(uint8_t&, uint8_t);
template void ArmCortex::clearBit<uint16_t>(uint16_t&, uint8_t);
template void ArmCortex::clearBit<uint32_t>(uint32_t&, uint8_t);

// Exercise NVIC functions
void exercise_nvic(uint8_t irq) {
    using namespace ArmCortex::Nvic;
    (void)isIrqEnabled(irq);
    enableIrq(irq);
    disableIrq(irq);
    (void)isIrqPending(irq);
    setPendingIrq(irq);
    clearPendingIrq(irq);
}

// Exercise SysTick functions
void exercise_systick() {
    using namespace ArmCortex::SysTick;
    (void)isEnabled();
    (void)isRunningOnProcessorClock();
    (void)isInterruptEnabled();
    (void)hasCountedToZero();
    (void)getReloadValue();
    (void)getCurrentValue();
    (void)getCalibrationValue();
    (void)isCalibrationValueExact();
    (void)hasSkewInfo();
    (void)has10msCalibration();
}

// Dummy main to make it a complete translation unit
int main() {
    exercise_nvic(0);
    exercise_systick();
    return 0;
}
