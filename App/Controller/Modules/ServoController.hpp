#ifndef __SERVO_CONTROLLER_H__
#define __SERVO_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"

class ServoController : public IController
{
public:
    ServoController() : m_hadc(nullptr){};
    virtual ~ServoController(){};
    void update(Data* data) override;
    void readServoADC();
    void syncADC();
    void setADC(ADC_HandleTypeDef* m_hadc);

private:
    void process();
    void makePacket(Data* data);

    ADC_HandleTypeDef* m_hadc;
    uint32_t Last_Time = 0;
    uint8_t Last_Gripper_button = 0;
    
    uint8_t Gripper_button;
    uint16_t Outer_Servo;
    uint16_t Inner_Servo;
    uint16_t Base_Servo;
    
    uint16_t Prev_Outer_Servo;
    uint16_t Prev_Inner_Servo;
    uint16_t Prev_Base_Servo;

    static constexpr float P_RATIO = 0.05f;
    static constexpr uint16_t ThresHold = static_cast<uint16_t>((1 << 12) * P_RATIO);
    static constexpr uint32_t DEBOUNCE_INTERVAL = 50;
};

#endif