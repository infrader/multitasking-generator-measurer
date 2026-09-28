cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-toolchain.cmake)

project(generator_measurer CXX C ASM)

add_subdirectory(sdk)

set(STARTUP ${CMAKE_SOURCE_DIR}/sdk/Libraries/Device/Geehy/APM32F0xx/Source/gcc/startup_apm32f072.S)
set(LINKER ${CMAKE_SOURCE_DIR}/sdk/Libraries/Device/Geehy/APM32F0xx/Source/gcc/gcc_APM32F07xx8.ld)

add_executable(run src/main.cpp ${STARTUP})
target_link_libraries(run PRIVATE apm32f0xx_sdk)

target_link_options(run PRIVATE -T ${LINKER} -nostartfiles  -Wl,-Map=${CMAKE_BINARY_DIR}/output.map)  

