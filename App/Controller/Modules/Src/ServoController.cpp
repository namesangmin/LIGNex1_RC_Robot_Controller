#include "ServoController.hpp"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <cmath>
void ServoController::update(Data* data)
{
    readServoADC();
    process();
    makePacket(data);
}

void ServoController::readServoADC()
{
    for(int idx = 1; idx <=5; idx++){
        HAL_ADC_Start(m_hadc);
        if(HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK){
            uint16_t val = HAL_ADC_GetValue(m_hadc);

            if(idx == 1) Current.outer = val;
            else if(idx == 2) Current.inner = val;
            else if(idx == 3) Current.base = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}

// 변화량 감지
// 버킷 버튼 감지
void ServoController::process()
{
    Gripper_Button.Current_Time  = HAL_GetTick();
    GPIO_PinState temp_Current_Val = HAL_GPIO_ReadPin(Gripper_Button_GPIO_Port, Gripper_Button_Pin);
    
    if(temp_Current_Val != Gripper_Button.prev)
    {
        if(Gripper_Button.Current_Time - Gripper_Button.Last_Time > Gripper_Button.DEBOUNCE_INTERVAL)
        {
            if(temp_Current_Val == 1)
            {
                Gripper_Button.current ^= 1;
            }

            Gripper_Button.Last_Time = Gripper_Button.Current_Time;
            Gripper_Button.prev = temp_Current_Val;
        }
    }
    
    uint16_t diff_outer = abs((int32_t)Prev.outer - (int32_t)Current.outer);
    uint16_t diff_inner = abs((int32_t)Prev.inner - (int32_t)Current.inner);
    uint16_t diff_base = abs((int32_t)Prev.base - (int32_t)Current.base);

    if(diff_base > ThresHold)
    {
        Prev.base = Current.base;
    }

    if(diff_outer > ThresHold)
    {
        Prev.outer = Current.outer;
    }

    if(diff_inner > ThresHold)
    {
        Prev.inner = Current.inner;
    }
}

void ServoController::makePacket(Data* data)
{
    data->servo_top = Prev.outer;
    data->servo_mid = Prev.inner;
    data->servo_bot = Prev.base;

    data->gripper = Gripper_Button.current;
    data->mode_data = arm;
}

void ServoController::setADC(ADC_HandleTypeDef* m_hadc)
{
    this->m_hadc = m_hadc;
}

void ServoController::syncADC()
{
    Prev.outer = Current.outer;
    Prev.inner = Current.inner;
    Prev.base = Current.base;
}