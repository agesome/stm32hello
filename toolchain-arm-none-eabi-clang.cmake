set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(COMMON_FLAGS "--target=arm-none-eabi -mthumb -mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-d16 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -ggdb")
set(CMAKE_C_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_ASM_FLAGS_INIT ${COMMON_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections")

set(CMAKE_C_COMPILER clang CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER clang++ CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER clang CACHE INTERNAL "ASM Compiler")

