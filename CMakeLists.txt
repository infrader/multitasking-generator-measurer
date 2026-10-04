cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-toolchain.cmake)

project(generator_measurer CXX C ASM)

add_subdirectory(sdk)

set(STARTUP ${CMAKE_SOURCE_DIR}/sdk/Libraries/Device/Geehy/APM32F0xx/Source/gcc/startup_apm32f072.S)
set(LINKER ${CMAKE_SOURCE_DIR}/sdk/Libraries/Device/Geehy/APM32F0xx/Source/gcc/gcc_APM32F07xx8.ld)

set(SOURCE ${CMAKE_SOURCE_DIR}/src/logger.cpp)

add_executable(run src/main.cpp ${STARTUP} ${SOURCE})
target_include_directories(run PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run PRIVATE apm32f0xx_sdk)

target_link_options(run PRIVATE -T ${LINKER} -nostartfiles  -Wl,-Map=${CMAKE_BINARY_DIR}/output.map)  

add_custom_command(TARGET run POST_BUILD COMMAND arm-none-eabi-objcopy -O ihex #Post build for dfu 
    $<TARGET_FILE:run> ${CMAKE_BINARY_DIR}/run.hex
    COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:run> ${CMAKE_BINARY_DIR}/run.bin
    COMMAND arm-none-eabi-size $<TARGET_FILE:run>
    )