#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__
#include "main.h"

#include "IController.hpp"
#include "JoyStickController.hpp"
#include "ServoController.hpp"
#include "UGV_Packet.hpp"
#include "stm32f1xx_hal_adc.h"

#define MAX_MODULES 2
#define DEBOUNCE_TIME 200

enum mode
{
    JOY_MODE,
    SERVO_MODE
};

class SystemManager
{
public:
    void initSystem(ADC_HandleTypeDef* hadc);
    void run();
    Data* getter(){return &m_packet;}

private:
    Data m_packet;
    void checkModeSwitch();
    void updateLED();

    ADC_HandleTypeDef* m_hadc;
    uint8_t Current_Mode;
    uint32_t Last_Pressed_Time = 0;
    uint16_t LED_Pin_arr[MAX_MODULES] = {Driving_Mode_LED_Pin, Robot_Arm_Mode_LED_Pin};

    // 모드 설정
    IController* Current_Controller;
    // 미리 객체를 만들어 놓음
    JoyStickController Joy_Controller;
    ServoController Servo_Controller;
};

#ifdef __cplusplus
extern "C"{
#endif
    void SystemManager_Init(ADC_HandleTypeDef* hadc);
    void SystemManager_Run();
#ifdef __cplusplus
}
#endif

#endif