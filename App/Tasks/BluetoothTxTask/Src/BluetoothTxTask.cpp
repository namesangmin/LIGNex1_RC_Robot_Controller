#include "BluetoothTxTask.hpp"

#include "cmsis_os2.h"

extern "C"
void BlueToothTxTaskHandler(void *argument){

    for(;;){
        osDelay(1);
    }
}