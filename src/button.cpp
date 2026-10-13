#include "button.hpp" 


static bool button_state = true; // button pressed or unpressed
static bool button_previous_state = true; // previous state
static uint32_t last_state = 0; // time previous state
static bool pressed_event = false; // button event
static const uint32_t DEBOUNSE = 50; // debounce 50 ms

void button_init(void){
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    GPIO_Config_T cfg;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_1;
    cfg.mode = GPIO_MODE_IN;
    cfg.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &cfg);

};

void button_poll(void){
    bool state = GPIO_ReadInputBit(GPIOA, GPIO_PIN_1);
    uint32_t now = millis();
    if(state != button_previous_state){
        button_previous_state = state;
        last_state = now;
        return;
    }

    if(state != button_state){
        if((now - last_state) >= DEBOUNSE){
            button_state = state;
            if(!state){
                pressed_event = true;
            }
        }
    }
};


bool button_pressed(void){
    button_poll();
    if(pressed_event){
        pressed_event = false;
        return true;
    }
    return false;
};