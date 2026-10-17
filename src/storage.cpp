#include<storage.hpp>

#define CHECK_NUM 0xA5A5A5A5
#define STORAGE_ADDRESS 0x0801F800


extern volatile uint32_t mode;
volatile bool FLAG_MODE_CHANGE;

void storage_init(void){
    uint32_t* ptr = (uint32_t*)STORAGE_ADDRESS;
    if(ptr[0] == CHECK_NUM){mode = ptr[1];}
}

void save_mode(uint32_t mode){
    uint32_t* ptr = (uint32_t*)STORAGE_ADDRESS;
    if(ptr[0] == CHECK_NUM && ptr[1] == mode){return;}
    __disable_irq();
    FMC_Unlock();
    FMC_ErasePage(STORAGE_ADDRESS);
    FMC_ProgramWord(STORAGE_ADDRESS, CHECK_NUM);
    FMC_ProgramWord(STORAGE_ADDRESS + 4, mode);
    FMC_Lock();
    FLAG_MODE_CHANGE = false;
    __enable_irq();
}