#include "apm32f072xx.h"
#include "apm32f0xx_gpio.h" 
#include "apm32f0xx_usart.h"
#include "apm32f0xx_rcm.h"


namespace logger{
    void logger_init();
    void log_tx(const char* log);
    void log_mode(uint32_t mode);
};
