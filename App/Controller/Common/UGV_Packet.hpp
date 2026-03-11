#ifndef __UGV_PACKET_H__
#define __UGV_PACKET_H__

#include "main.h"

#pragma pack(push, 1) 


#define driving 0xFF
#define rotate 0xDD
#define arm 0x00
#define ack_driving 0xA5
#define ack_arm 0x5A

typedef struct{
    uint8_t mode_data;
    uint8_t gripper;
    uint16_t moter_x;
    uint16_t moter_y;
    uint16_t servo_top;
    uint16_t servo_mid;
    uint16_t servo_bot;
}Data;
#pragma pack(pop)
#endif