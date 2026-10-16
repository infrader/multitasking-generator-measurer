#include"logger.hpp"

void logger::logger_init(){
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);
    GPIO_Config_T cfg;
    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_9;
    cfg.mode = GPIO_MODE_AF;
    cfg.outtype = GPIO_OUT_TYPE_PP;
    cfg.pupd = GPIO_PUPD_NO;
    cfg.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &cfg);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_9, GPIO_AF_PIN1); // PIN1 USART1_TX

    GPIO_ConfigStructInit(&cfg);
    cfg.pin = GPIO_PIN_10;
    cfg.mode = GPIO_MODE_AF;
    cfg.outtype = GPIO_OUT_TYPE_PP;
    cfg.pupd = GPIO_PUPD_PU;
    cfg.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &cfg);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_PIN1); // PIN1 USART1_RX
    
    USART_Config_T cfg_u;
    USART_ConfigStructInit(&cfg_u);
    cfg_u.baudRate = 115200;
    cfg_u.wordLength = USART_WORD_LEN_8B;
    cfg_u.stopBits = USART_STOP_BIT_1;
    cfg_u.parity = USART_PARITY_NONE;
    cfg_u.mode = USART_MODE_TX_RX;
    cfg_u.hardwareFlowCtrl = USART_FLOW_CTRL_NONE;
    USART_Config(USART1, &cfg_u);   
    USART_Enable(USART1);
};

void logger::log_tx(const char* log)
{
    while (*log != '\0')
    {
        while (USART_ReadStatusFlag(USART1, USART_FLAG_TXBE) == RESET);
        USART_TxData(USART1, static_cast<uint16_t>(*log++));
    }
    while (USART_ReadStatusFlag(USART1, USART_FLAG_TXC) == RESET);
}

void logger::log_mode(uint32_t mode){
    switch (mode)
    {
    case 1:
        log_tx("Slow mode(1): 1000ms\r\n"); break;
    case 2:
        log_tx("Fast mode(2): 200ms\r\n"); break;
    case 3:
        log_tx("Fastest mode(3): 100ms\r\n"); break;
    default:
        break;
    }
};