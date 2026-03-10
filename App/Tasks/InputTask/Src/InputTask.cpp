#include "InputTask.hpp"
#include "SystemManager.hpp"
#include "adc.h"
#include "cmsis_os2.h"

extern "C"
void InputTaskHandler(void *argument){

    SystemManager* manager = new SystemManager();
    manager->initSystem(&hadc1);
    for(;;){
        manager->run();
        osDelay(1);
    }
}