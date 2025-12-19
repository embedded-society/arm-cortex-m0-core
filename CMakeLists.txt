# Copyright (C) 2025 The Embedded Society <https://github.com/embedded-society/arm-cortex-m0-core>

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.13)

project(arm-cortex-m0-core
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "CMSIS-like C++ library for accessing ARM Cortex-M0 core peripherals"
    HOMEPAGE_URL "https://github.com/embedded-society/arm-cortex-m0-core"
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_sources(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/bit_utils.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/nvic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/scb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/special_regs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/arm-cortex-m0-core/systick.hpp"
)
