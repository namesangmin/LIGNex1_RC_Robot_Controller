#include "BleRx.hpp"
#include "PacketCodec.hpp"
#include "DataConfig.hpp"

extern "C"{
    #include "main.h"
}

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

    rx_old_pos = 0;

    processor = new PacketCodec;
     HAL_UART_Receive_DMA(huart, rx_buf, RX_BUF_SIZE);
     __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
     __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
}

uint16_t BleRx::uart_dma_read(void *argument)
{
    (void)argument;

    uint16_t pos = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);

    uint16_t avail;
    if (pos >= rx_old_pos)
        avail = pos - rx_old_pos;
    else
        avail = RX_BUF_SIZE - rx_old_pos + pos;

    if (avail < Packet_len)
        return 0;

    uint16_t scan_pos = rx_old_pos;

    while (avail >= Packet_len)
    {
        if (rx_buf[scan_pos] == SOF)
        {
            uint16_t copy_pos = scan_pos;

            for (uint16_t i = 0; i < Packet_len; i++)
            {
                tmp[i] = rx_buf[copy_pos];

                copy_pos++;
                if (copy_pos >= RX_BUF_SIZE)
                    copy_pos = 0;
            }

            uint8_t checksum = 0;
            for (uint16_t i = 0; i < Packet_len - 1; i++)
                checksum ^= tmp[i];

            if (checksum == tmp[Packet_len - 1])
            {
                rx_old_pos = copy_pos;
                return Packet_len;
            }
        }

        /* scan만 이동 */
        scan_pos++;
        if (scan_pos >= RX_BUF_SIZE)
            scan_pos = 0;

        avail--;
    }

    /* 여기서만 reader pointer 이동 */
    rx_old_pos = scan_pos;

    return 0;
}

// 컨트롤러와 rc카에 각 디바이스를 구분할 수 있는 표시 해야함
void BleRx::GetFromRx(void *argument){
    osStatus_t st = osMessageQueueGet(this->qhandle, &receive_flag, NULL, osWaitForever);
    if (st == osOK && uart_dma_read(NULL)){
        Data *data = (Data*)(processor->Decoding(tmp));
        #if RC_Car
        if (data->mode_data == driving || data->mode_data == rotate){
            Servo_type servo = {
                .servo_top  = data->servo_top,
                .servo_mid  = data->servo_mid,
                .servo_bot  = data->servo_bot,
                .gripper    = data->gripper
            };
            osMessageQueuePut(moter_q, &servo, 0, 10);
        }
        else if(data->mode_data == arm){
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

BleRx::~BleRx(){
    delete processor;
}