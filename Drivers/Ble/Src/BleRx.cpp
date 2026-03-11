#include "BleRx.hpp"
#include "PacketCodec.hpp"
#include "DataConfig.hpp"

extern "C"{
    #include "main.h"
}

BleRx* BleRx::instance = nullptr;

//반드시 Interrupt 설정 필요함
//#include "cmsis_os2.h"
// static uint8_t Rxflag = 1;
// void USART1_IRQHandler(void)
// {
//   /* USER CODE BEGIN USART1_IRQn 0 */
//   if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET){
//     __HAL_UART_CLEAR_IDLEFLAG(&huart1);
    
//     osMessageQueuePut(RxQhandleHandle, &Rxflag, 0, 0);
//     Rxflag = 0;
//   }
//   /* USER CODE END USART1_IRQn 0 */
//   HAL_UART_IRQHandler(&huart1);
//   /* USER CODE BEGIN USART1_IRQn 1 */

//   /* USER CODE END USART1_IRQn 1 */
// }

// Init_type 구조체에 데이터 저장 후 주소값 전달할것
void BleRx::Init(void *argument){
    huart = RX_HUART;
    qhandle = COM_QUEUE;
    servo_q = SERVO_QUEUE;
    moter_q = MOTER_QUEUE;

    instance = this;

    rx_old_pos = 0;

    processor = new PacketCodec;
     HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buf, RX_BUF_SIZE);
     __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
     __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
}


bool BleRx::check_cs(uint8_t *ptr, uint8_t size){
    uint8_t idx = 0;
    // SOF 찾기
    while (idx < size && ptr[idx] != SOF){
        idx++;
    }

    // SOF 못 찾으면 실패
    if (idx >= size){
        return false;
    }

    // 패킷 길이 부족
    if (idx + Packet_len > size){
        return false;
    }

    uint8_t checksum = 0;

    // checksum 계산
    for (uint8_t i = 0; i < Packet_len - 1; i++){
        checksum ^= ptr[idx + i];
    }

    // checksum 비교
    if (checksum == ptr[idx + Packet_len - 1]){
        return true;
    }

    return false;
}

// 컨트롤러와 rc카에 각 디바이스를 구분할 수 있는 표시 해야함
void BleRx::GetFromRx(void *argument){
    osStatus_t st = osMessageQueueGet(this->qhandle, &receive_flag, NULL, osWaitForever);
    if (st == osOK && check_cs(rx_buf, receive_flag)){
        Data *data = (Data*)(processor->Decoding(tmp));
        #if RC_Controller
        if (data->mode_data == arm){
            Servo_type servo = {
                .servo_top  = data->servo_top,
                .servo_mid  = data->servo_mid,
                .servo_bot  = data->servo_bot,
                .gripper    = data->gripper
            };
            osMessageQueuePut(moter_q, &servo, 0, 10);
        }
        else if(data->mode_data == driving || data->mode_data == rotate){
            Moter_type moter = {
                .mode_data  = data->mode_data,
                .moter_x    = data->moter_x,
                .moter_y    = data->moter_y
            };
            osMessageQueuePut(servo_q, &moter, 0, 10);
        }
        #else
        if (data->mode_data == ack_driving){
            //HAL_GPIO_WritePin(~~);
        }
        else if (data->mode_data == ack_arm){
            //HAL_GPIO_WritePin(~~);
        }
        else
        {}
        #endif
        
    }
}

void BleRx::Callback(UART_HandleTypeDef *huart, uint8_t Size){
    if(instance) instance->OnRxEvent(Size);
}

void BleRx::OnRxEvent(uint8_t size){
    osMessageQueuePut(COM_QUEUE, &size, 0, 0);
    HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buf, RX_BUF_SIZE);
}
BleRx::~BleRx(){
    delete processor;
}