#include "InputTask.hpp"
#include "SystemManager.hpp"
#include "adc.h"
#include "cmsis_os2.h"

extern "C"
void InputTaskHandler(void *argument){

    SystemManager* manager = new SystemManager();
    manager->initSystem(&hadc1);
    
    uint32_t delay_time = osKernelGetSysTimerCount();
    for(;;){
        manager->run();
        delay_time += DELAY_CYCLE;
        osDelayUntil(delay_time);
    }
}