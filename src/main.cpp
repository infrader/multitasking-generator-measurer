#include "apm32f072xx.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_gpio.h" 

extern "C" void _init(void){};

int main(){
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOE);
    GPIO_Config_T cfg;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_13;
    cfg.mode = GPIO_MODE_OUT;
    cfg.speed = GPIO_SPEED_2MHz;
    cfg.pupd = GPIO_PUPD_NO;
    GPIO_Config(GPIOE, &cfg);
    while(1){
        GPIO_SetBit(GPIOE, GPIO_PIN_13);
        for(volatile uint32_t i = 0; i < 500000; ++i);
        GPIO_ClearBit(GPIOE, GPIO_PIN_13);
        for(volatile uint32_t i = 0; i < 500000; ++i);
    }
}