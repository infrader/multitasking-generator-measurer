#pragma once
#include<cstdint>
#include "apm32f072xx.h"
#include "apm32f0xx_fmc.h"

void storage_init(void);

void save_mode(uint32_t mode);