#include "SystemManager.hpp"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <cstdio>

// 디폴트 모드 주행 모드
// main.c에서 hadc1을 가져와서 저장
void SystemManager::initSystem(ADC_HandleTypeDef* hadc)
{
    // adc 주솟값 전달
    //this->m_hadc = hadc;
    Joy_Controller.setADC(hadc);
    Servo_Controller.setADC(hadc);

    Joy_Controller.readJoyStickADC();
    Joy_Controller.syncADC();

    Servo_Controller.readServoADC();
    Servo_Controller.syncADC();

    // 디폴트 주행 모드
    Current_Controller = &Joy_Controller;
    Current_Mode = driving;
}

void SystemManager::run()
{
    if(Current_Controller != nullptr)
    {
        checkModeSwitch();
        Current_Controller->update(&m_packet);
        updateLED(); 
    }
}

// 현재 모드 확인
// 폴링 방식에서 flag를 보내는데 굳이 UGV에서 mode에 대한 정보를 알아야 하나?
void SystemManager::checkModeSwitch() 
{
    static GPIO_PinState Prev_State = GPIO_PIN_RESET;

    GPIO_PinState Current_State = HAL_GPIO_ReadPin(Mode_Change_Button_GPIO_Port, Mode_Change_Button_Pin);
    uint32_t Current_Time = HAL_GetTick();
    
    if(Current_State == GPIO_PIN_SET && Prev_State == GPIO_PIN_RESET)
    {
        if(Current_Time - Last_Pressed_Time > DEBOUNCE_TIME)
        {
            Last_Pressed_Time = Current_Time;
           
            if(Current_Mode == driving || Current_Mode == rotate)
            {
                Current_Mode = arm;
                Current_Controller = &Servo_Controller;
            }
            else
            {
                Current_Mode = driving;
                Current_Controller = &Joy_Controller;
            }
        }
    }
    Prev_State = Current_State;
}
void SystemManager::updateLED()
{    
    // 초기화
    HAL_GPIO_WritePin(Driving_Mode_LED_GPIO_Port,Driving_Mode_LED_Pin | Robot_Arm_Mode_LED_Pin, GPIO_PIN_RESET);
    
    // led 키기
    uint16_t tmIdx = 0;
    if(Current_Mode == driving || Current_Mode == rotate) tmIdx = 0;
    else if(Current_Mode == arm)tmIdx = 1;

    HAL_GPIO_WritePin(Driving_Mode_LED_GPIO_Port,LED_Pin_arr[tmIdx],GPIO_PIN_SET);
}