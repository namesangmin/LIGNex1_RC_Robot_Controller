#ifndef __JOYSTICK_CONTROLLER_H__
#define __JOYSTICK_CONTROLLER_H__
#include "main.h"

#include "IController.hpp"
#include "UGV_Packet.hpp"
#include "ButtonState.hpp"

struct JoyStickState{
    uint16_t x;
    uint16_t y;
};

class JoyStickController : public IController
{
public:
    JoyStickController() : m_hadc(nullptr){};
    virtual ~JoyStickController(){};

    void update(Data* data) override;
    
    void readJoyStickADC();
    void syncADC();
    void setADC(ADC_HandleTypeDef* m_hadc);

private:
    void process();
    void makePacket(Data* data);

    ADC_HandleTypeDef* m_hadc;

    ButtonState RotateButton;
    JoyStickState Current;
    JoyStickState Prev;

    static constexpr float P_RATIO = 0.05f;
    static constexpr uint16_t ThresHold = static_cast<uint16_t>((1 << 12) * P_RATIO);
};

#endif