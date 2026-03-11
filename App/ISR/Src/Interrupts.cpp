#if __cplusplus
extern "C" {
#endif
    #include "usart.h"
#if __cplusplus
}
#endif
#include "DataConfig.hpp"
#include "BleRx.hpp"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == RX_HUART){
        BleRx::Callback(huart, (uint8_t)Size);
    }
}