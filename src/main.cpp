#include "apm32f072xx.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_gpio.h" 



extern "C" void _init(void){};

static volatile uint32_t tms = 0;
static volatile uint32_t mode = 1;
extern "C" void SysTick_Handler(void){
    ++tms;
};
uint32_t millis(void){
    return tms;
};
int main(){
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOE);
    GPIO_Config_T cfg;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_6;
    cfg.mode = GPIO_MODE_OUT;
    cfg.speed = GPIO_SPEED_2MHz;
    cfg.pupd = GPIO_PUPD_NO;
    GPIO_Config(GPIOE, &cfg);
    SysTick_Config(SystemCoreClock/1000);
    const uint32_t interval[3] = {500, 100, 50};
    while(1){
        if(millis() >= interval[mode - 1]){
            tms = 0;
            if(GPIO_ReadOutputBit(GPIOE, GPIO_PIN_6)){
                GPIO_ClearBit(GPIOE, GPIO_PIN_6);
            }else{
                GPIO_SetBit(GPIOE, GPIO_PIN_6);
            }
        }
    }
} 