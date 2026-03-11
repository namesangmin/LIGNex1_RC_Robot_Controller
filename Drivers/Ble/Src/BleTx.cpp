#include "BleTx.hpp"
#include "IDataProcessor.hpp"
#include "PacketCodec.hpp"
#include "DataConfig.hpp"

#if __cplusplus
extern "C" {
#endif
    #include "main.h"
    #include "usart.h"
    #include <string.h>
#if __cplusplus
}
#endif

void BleTx::Init(void *argument){
    huart = TX_HUART;
    processor = new PacketCodec;
}

void BleTx::SendToTx(void *argument){
    Data *data = static_cast<Data*>(argument);
    uint8_t *buf = (uint8_t*)(processor->Encoding(data));
    HAL_UART_Transmit(huart, buf, Packet_len, 10);
}

BleTx::~BleTx(){
    delete processor;
}