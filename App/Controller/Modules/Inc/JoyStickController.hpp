#ifndef __JOYSTICK_CONTROLLER_H__
#define __JOYSTICK_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"
#include "ButtonState.hpp"
#include <cstdint>

struct JoyStickState{
    uint16_t x;
    uint16_t y;
};

class JoyStickController : public IController
{
public:
    JoyStickController() : ADC_Buf(nullptr){};
    virtual ~JoyStickController(){};

    void update(Data* data) override;
    
    void readJoyStickADC();
    void syncADC();
    void setBuffer(uint16_t* buf);

private:
    void process();
    void makePacket(Data* data);
    
    uint16_t* ADC_Buf;
    
    ButtonState RotateButton;
    JoyStickState Current;
    JoyStickState Prev;

    static constexpr float P_RATIO = 0.05f;
    static constexpr uint16_t ThresHold = static_cast<uint16_t>((1 << 12) * P_RATIO);
};

#endif