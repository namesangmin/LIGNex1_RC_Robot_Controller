#ifndef __SERVO_CONTROLLER_H__
#define __SERVO_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "DataConfig.hpp"
//#include "UGV_Packet.hpp"
#include "ButtonState.hpp"

struct ServoState{
    uint16_t outer;
    uint16_t inner;
    uint16_t base;
};

class ServoController : public IController
{
public:
    ServoController() : ADC_Buf(nullptr){};
    virtual ~ServoController(){};
    
    void update(Data* data) override;
    void readServoADC();
    void syncADC();
    void setBuffer(uint16_t* buf);

private:
    void process();
    void makePacket(Data* data);

    uint16_t* ADC_Buf;
    
    ButtonState Gripper_Button;
    ServoState Current;
    ServoState Prev;

    static constexpr float P_RATIO = 0.05f;
    static constexpr uint16_t ThresHold = static_cast<uint16_t>((1 << 12) * P_RATIO);
};

#endif