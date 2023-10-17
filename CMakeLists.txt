cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

project(hello C CXX ASM)

find_package(CMSIS COMPONENTS STM32H503 REQUIRED)
find_package(HAL COMPONENTS STM32H503 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

add_executable(hello main.cpp stm32h5xx_nucleo.c syscalls.c)
target_link_libraries(hello
        HAL::STM32::H5::ADC
        HAL::STM32::H5::ADCEx
        HAL::STM32::H5::DMA
        HAL::STM32::H5::DMAEx
        HAL::STM32::H5::ICACHE
        HAL::STM32::H5::RCCEx
        HAL::STM32::H5::EXTI
        HAL::STM32::H5::GPIO
        HAL::STM32::H5::UART
        HAL::STM32::H5::CORTEX
        CMSIS::STM32::H503RB
        STM32::NoSys
)
stm32_generate_hex_file(hello)
stm32_print_size_of_target(hello)