cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain-arm-none-eabi-clang.cmake)

project(hello C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)

# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wframe-larger-than=32  -fstack-protector-strong -Oz")
# set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wframe-larger-than=32  -fstack-protector-strong -Oz")

set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src CACHE STRING "")
set(FREERTOS_PORT GCC_ARM_CM33_NTZ_NONSECURE CACHE STRING "")
set(FREERTOS_HEAP 3 CACHE STRING "")
add_subdirectory(3rdparty/freertos)

add_subdirectory(3rdparty/lvgl EXCLUDE_FROM_ALL)
target_include_directories(lvgl PRIVATE src)

add_library(stmicro OBJECT
    3rdparty/stmicro/hal/stm32h5xx_hal.c
    3rdparty/stmicro/hal/stm32h5xx_hal_adc.c
    3rdparty/stmicro/hal/stm32h5xx_hal_adc_ex.c
    3rdparty/stmicro/hal/stm32h5xx_hal_cortex.c
    3rdparty/stmicro/hal/stm32h5xx_hal_dma.c
    3rdparty/stmicro/hal/stm32h5xx_hal_dma_ex.c
    3rdparty/stmicro/hal/stm32h5xx_hal_gpio.c
    3rdparty/stmicro/hal/stm32h5xx_hal_icache.c
    3rdparty/stmicro/hal/stm32h5xx_hal_rcc.c
    3rdparty/stmicro/hal/stm32h5xx_hal_rcc_ex.c
    3rdparty/stmicro/hal/stm32h5xx_hal_uart.c
    3rdparty/stmicro/hal/stm32h5xx_hal_spi.c
    3rdparty/stmicro/hal/stm32h5xx_hal_spi_ex.c
    3rdparty/stmicro/hal/stm32h5xx_hal_tim.c
    3rdparty/stmicro/hal/stm32h5xx_hal_tim_ex.c
    3rdparty/stmicro/cmsis/system_stm32h5xx.c
)

target_include_directories(stmicro PUBLIC
    src
    3rdparty/stmicro/hal
    3rdparty/stmicro/cmsis
    3rdparty/stmicro/cmsis/Core/Include
)

target_compile_definitions(stmicro PUBLIC STM32H5 STM32H503xx)

add_executable(hello
    src/main.cpp
    src/adcdma.cpp
    src/clock.cpp
    src/interrupts.c
    src/syscalls.c
    src/uart.cpp
    src/util.cpp
    src/lcd.cpp
    # src/sdcard.cpp
    src/hooks.c
    src/spi.cpp
    src/ui.cpp
    src/timebase.cpp
)

target_include_directories(hello PUBLIC src)

target_link_libraries(hello
    freertos_kernel
    lvgl
    crt0
    stmicro
)

target_link_options(hello PUBLIC
    -Wl,--defsym=vfprintf=__i_vfprintf -Wl,--defsym=vfscanf=__i_vfscanf
    -T${CMAKE_CURRENT_SOURCE_DIR}/src/pico.ld
)
set_target_properties(hello PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.ld)

set_property(TARGET hello PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

add_custom_target(display_size ALL COMMAND llvm-size "$<TARGET_FILE:hello>" DEPENDS hello COMMENT "Binary size:")

