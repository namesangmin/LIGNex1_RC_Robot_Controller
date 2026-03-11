#include "BluetoothRxTask.hpp"
#include "IRx.hpp"
#include "BleRx.hpp"
#include "DataConfig.hpp"
#include "cmsis_os2.h"

extern "C"
void BluetoothRxTaskHandler(void *argument){

    for(;;){
        //Rx->GetFromRx(NULL);
        HAL_Delay(1);
    }
    // IRx *Rx = new BleRx;
    // Init_type init = {&huart1, &RxQhandleHandle, NULL, NULL};
    // Rx->Init(&init);
    // for(;;){
    //     Rx->GetFromRx(NULL);
    // }
}