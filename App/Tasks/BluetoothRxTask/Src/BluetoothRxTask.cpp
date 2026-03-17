#include "BluetoothRxTask.hpp"

#include "cmsis_os2.h"

extern "C"
void BluetoothRxTaskHandler(void *argument){

    for(;;){
        osDelay(1000);
    }
}