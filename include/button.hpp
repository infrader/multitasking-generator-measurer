#pragma once
#include "apm32f072xx.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_pmu.h"
#include "apm32f0xx_rtc.h"
#include <cstdint>

extern uint32_t millis(void);

void button_init(void);

bool button_pressed(void);

void disable_tamper_pullup(void);