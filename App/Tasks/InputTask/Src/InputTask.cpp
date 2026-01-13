#include "InputTask.hpp"

#include "cmsis_os2.h"

extern "C"
void InputTaskHandler(void *argument){

    for(;;){
        osDelay(1);
    }
}