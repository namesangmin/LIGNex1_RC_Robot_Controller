#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__
#include "main.h"

#include "IController.hpp"
#include "JoyStickController.hpp"
#include "ServoController.hpp"
//#include "UGV_Packet.hpp"
#include "stm32f1xx_hal_adc.h"

#include "BleTx.hpp"
#include "ITx.hpp"
#include <cstddef>

#define MAX_MODULES 2
#define DEBOUNCE_TIME 200
#define MAX_ADC_CHANNEL 5
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

private:
    ~SystemManager();
    Data m_packet;
    void checkModeSwitch();
    void updateLED();

    uint16_t ADC_Buffer[MAX_ADC_CHANNEL];

    uint8_t Current_Mode;
    uint32_t Last_Pressed_Time = 0;
    uint16_t LED_Pin_arr[MAX_MODULES] = {Driving_Mode_LED_Pin, Robot_Arm_Mode_LED_Pin};

    // 모드 설정
    IController* Current_Controller;

    // 데이터 send 클래스
    ITx* Tx;
    
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