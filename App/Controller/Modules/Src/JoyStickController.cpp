#include "JoyStickController.hpp"
#include "main.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"
#include <cmath>

void JoyStickController::update(Data* data)
{
    readJoyStickADC();
    process();
    makePacket(data);
}

void JoyStickController::readJoyStickADC()
{
    for(int idx = 1; idx <=5; idx++){
        HAL_ADC_Start(m_hadc);
        if(HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK){
            uint16_t val = HAL_ADC_GetValue(m_hadc);

            if(idx == 4) Current.x = val;
            else if(idx == 5) Current.y = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}

// 변화량 감지
void JoyStickController::process()
{
    JoyStickButton.Current_Time = HAL_GetTick();
    GPIO_PinState temp_Current_Val = HAL_GPIO_ReadPin(Rotate_Mode_Button_GPIO_Port,Rotate_Mode_Button_Pin);
    
    // 한 번 누르면 계속 1이 유지 되는 것이 아니라 1 번만 1이 저장이 됨. 
    // 50ms 미만일 때 무시(이전 누른 시간 vs 현재 누른 시간)
    if(temp_Current_Val != JoyStickButton.prev){
        if(JoyStickButton.Current_Time - JoyStickButton.Last_Time > JoyStickButton.DEBOUNCE_INTERVAL){            
            if(temp_Current_Val == 1){
                JoyStickButton.current ^= 1;
            }

            JoyStickButton.Last_Time = JoyStickButton.Current_Time;
            JoyStickButton.prev = temp_Current_Val;
        }
    }

    uint16_t diff_x = abs((int32_t)Prev.x - (int32_t)Prev.y);
    uint16_t diff_y = abs((int32_t)Prev.y - (int32_t)Prev.y);
    
    if(diff_x > ThresHold){
        Prev.x = Current.x;
    }
    if(diff_y > ThresHold){
        Prev.y = Current.y;
    }
}

void JoyStickController::makePacket(Data* data)
{
    data->moter_x = Prev.x;
    data->moter_y = Prev.y;
    
    if(JoyStickButton.current){
        data->mode_data = rotate;
    }
    else{
        data->mode_data = driving;
    }
}

void JoyStickController::setADC(ADC_HandleTypeDef* m_hadc)
{
    this->m_hadc = m_hadc;
}

void JoyStickController::syncADC()
{
    Prev.x = Current.x;
    Prev.y = Current.y;
}