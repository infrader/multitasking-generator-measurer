cmake_minimum_required(VERSION 3.20)


set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

add_library(apm32f0xx_sdk STATIC
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/src/apm32f0xx_gpio.c
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/src/apm32f0xx_rcm.c
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/src/apm32f0xx_usart.c
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/src/apm32f0xx_tmr.c
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/src/apm32f0xx_adc.c
${SDK_ROOT}/Device/Geehy/APM32F0xx/Source/system_apm32f0xx.c
)

target_include_directories(apm32f0xx_sdk PUBLIC
${SDK_ROOT}/APM32F0xx_StdPeriphDriver/inc
${SDK_ROOT}/Device/Geehy/APM32F0xx/Include
${SDK_ROOT}/CMSIS/Include
)

target_compile_definitions(apm32f0xx_sdk PUBLIC
APM32F072xB
USE_STDPERIPH_DRIVER
)
