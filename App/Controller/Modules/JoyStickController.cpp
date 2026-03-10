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

            if(idx == 4) this->JoyStick_X = val;
            else if(idx == 5) this->JoyStick_Y = val;
        }
    }
    HAL_ADC_Stop(m_hadc);
}

// 변화량 감지
void JoyStickController::process()
{
    uint32_t Current_Time = HAL_GetTick();
    GPIO_PinState temp_Current_Val = HAL_GPIO_ReadPin(Rotate_Mode_Button_GPIO_Port,Rotate_Mode_Button_Pin);
    
    // 한 번 누르면 계속 1이 유지 되는 것이 아니라 1 번만 1이 저장이 됨. 
    // 50ms 미만일 때 무시(이전 누른 시간 vs 현재 누른 시간)
    if(temp_Current_Val != Last_Rotate_Mode_button){
        if(Current_Time - Last_Time > DEBOUNCE_INTERVAL){
            Last_Time = Current_Time;
            Last_Rotate_Mode_button = temp_Current_Val;
    
            if(temp_Current_Val == 1){
                this->Rotate_Mode_Button ^= 1;
            }
        }
    }

    uint16_t diff_x = abs((int32_t)this->Prev_Joystick_X - (int32_t)this->JoyStick_X);
    uint16_t diff_y = abs((int32_t)this->Prev_Joystick_Y - (int32_t)this->JoyStick_Y);
    
    if(diff_x > ThresHold){
        this->Prev_Joystick_X = this->JoyStick_X;
    }
    if(diff_y > ThresHold){
        this->Prev_Joystick_Y = this->JoyStick_Y;
    }
}

void JoyStickController::makePacket(Data* data)
{
    data->moter_x = this->Prev_Joystick_X;
    data->moter_y = this->Prev_Joystick_Y;

    if(this->Rotate_Mode_Button){
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
    Prev_Joystick_X = JoyStick_X;
    Prev_Joystick_Y = JoyStick_Y;
}