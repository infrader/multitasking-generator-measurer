#include "apm32f072xx.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_gpio.h" 
#include "button.hpp"
#include "logger.hpp"
#include "storage.hpp"


extern "C" void _init(void){};

static volatile uint32_t tms = 0;
volatile uint8_t mode = 1;
static const uint32_t interval[3] = {500, 100, 50};
extern "C" void SysTick_Handler(void){
    ++tms;
};
uint32_t millis(void){
    return tms;
};

void led_init(void){
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOE);
    GPIO_Config_T cfg;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_5;
    cfg.mode = GPIO_MODE_OUT;
    cfg.speed = GPIO_SPEED_2MHz;
    cfg.pupd = GPIO_PUPD_NO;
    GPIO_Config(GPIOE, &cfg);

}
void timer_init(void){
    SysTick_Config(SystemCoreClock/1000);
}

int main(){
    led_init();
    timer_init(); 
    storage_init();
    button_init();
    logger::logger_init();
    //local
    uint32_t last_log_time{millis()};
    uint32_t last_toggle = 0;
    while(1){
        if(FLAG_MODE_CHANGE){
            save_mode(mode);
        }
        if((millis() - last_toggle) >= interval[mode - 1]){
            last_toggle += interval[mode - 1];
            if(GPIO_ReadOutputBit(GPIOE, GPIO_PIN_5)){
                GPIO_ClearBit(GPIOE, GPIO_PIN_5);
            }else{
                GPIO_SetBit(GPIOE, GPIO_PIN_5);
            }
        }
        if((millis() - last_log_time) >= 1000){
            last_log_time = millis();
            logger::log_mode(mode);
        }
    }
} 