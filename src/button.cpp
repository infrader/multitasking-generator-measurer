#include "button.hpp" 

static uint32_t last_state = 0; // time previous state
static const uint32_t DEBOUNSE = 50; // debounce 50 ms

void disable_tamper_pullup(void) {
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    PMU_EnableBackupAccess();
    RTC_DisableWriteProtection();
    RTC->TACFG = 0x00000000;  
    RTC_EnableWriteProtection();
}

void button_init(void){
    disable_tamper_pullup();
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    GPIO_Config_T cfg;
    EINT_Config_T eintConfig;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_0 | GPIO_PIN_1;
    cfg.mode = GPIO_MODE_IN;
    cfg.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &cfg);
    SYSCFG_EINTLine(SYSCFG_PORT_GPIOA, SYSCFG_PIN_0);
    eintConfig.line    =  EINT_LINE0;
    eintConfig.lineCmd =  ENABLE;
    eintConfig.mode    =  EINT_MODE_INTERRUPT;
    eintConfig.trigger =  EINT_TRIGGER_FALLING;
    EINT_Config(&eintConfig);
    NVIC_EnableIRQRequest(EINT0_1_IRQn, 0x0f);
}

extern "C" void EINT0_1_IRQHandler(void){
    if (EINT_ReadStatusFlag(EINT_LINE0) == SET){
        EINT_ClearStatusFlag(EINT_LINE0);
        uint32_t now = millis();
        if((now - last_state) < DEBOUNSE){
            return;
        }
        last_state = now;
        if (++mode > 3) mode = 1;
    }
}


