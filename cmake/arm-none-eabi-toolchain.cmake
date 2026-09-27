set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)
set(CMAKE_SYSTEM_PROCESSOR arm)

#compiler set
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CPU_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft")

set(CMAKE_CXX_FLAGS_INIT "${CPU_FLAGS} -Wall -Wextra -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -Os -g3 -std=c++17")
set(CMAKE_C_FLAGS_INIT "${CPU_FLAGS} -Wall -Wextra -ffunction-sections -fdata-sections -Os -g3")
set(CMAKE_ASM_FLAGS_INIT "${CPU_FLAGS} -Os -g3")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CPU_FLAGS} --specs=nano.specs -Wl,--gc-sections")


