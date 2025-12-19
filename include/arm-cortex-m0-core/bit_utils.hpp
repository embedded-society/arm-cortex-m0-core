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
#include <concepts>

namespace ArmCortex {
    //! Check if the n-th bit is set in the value.
    template<std::integral T>
    [[gnu::always_inline]] constexpr bool isBitSet(T value, uint8_t n)
    {
        return (value >> n) & T{1};
    }

    //! Sets the n-th bit in the value.
    template<std::integral T>
    [[gnu::always_inline]] constexpr void setBit(T& value, uint8_t n)
    {
        value |= T{1} << n;
    }

    //! Clears the n-th bit in the value.
    template<std::integral T>
    [[gnu::always_inline]] constexpr void clearBit(T& value, uint8_t n)
    {
        value &= ~(T{1} << n);
    }
}
