#pragma once
#include<cstdint>
#include "apm32f072xx.h"
#include "apm32f0xx_fmc.h"

extern volatile uint8_t mode;
extern volatile bool FLAG_MODE_CHANGE;

void storage_init(void);

void save_mode(uint8_t mode);