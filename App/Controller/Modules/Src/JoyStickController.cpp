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
    HAL_ADC_Start(m_hadc);
    for(int idx = 1; idx <=5; idx++){
        if(HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK){
            uint16_t val = HAL_ADC_GetValue(m_hadc);

            if(idx == 4) Current.x = val;
            else if(idx == 5) Current.y = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}

// 변화량 감지
// rotate 모드 감지
void JoyStickController::process()
{
    RotateButton.Current_Time = HAL_GetTick();
    GPIO_PinState temp_Current_Val = HAL_GPIO_ReadPin(Rotate_Mode_Button_GPIO_Port,Rotate_Mode_Button_Pin);
    
    if(temp_Current_Val != RotateButton.prev)
    {
        if(RotateButton.Current_Time - RotateButton.Last_Time > RotateButton.DEBOUNCE_INTERVAL)
        {            
            if(temp_Current_Val == 1)
            {
                RotateButton.current ^= 1;
            }

            RotateButton.Last_Time = RotateButton.Current_Time;
            RotateButton.prev = temp_Current_Val;
        }
    }

    uint16_t diff_x = abs((int32_t)Prev.x - (int32_t)Current.x);
    uint16_t diff_y = abs((int32_t)Prev.y - (int32_t)Current.y);
    
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
    
    if(RotateButton.current){
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