#ifndef __BUTTON_STATE_H__
#define __BUTTON_STATE_H__

//#include "main.h"
#include <stdint.h>

struct ButtonState{
    uint32_t Last_Time = 0;
    uint32_t Current_Time = 0;
    uint8_t current = 0;
    uint8_t prev = 0;
    static constexpr uint32_t DEBOUNCE_INTERVAL = 50;
};

#endif