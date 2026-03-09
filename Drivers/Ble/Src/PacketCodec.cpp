#include "DataConfig.hpp"
#include "PacketCodec.hpp"


void * PacketCodec::Encoding(void *argument){
    data = *static_cast<Data*>(argument);
    buf[0] = SOF;
    buf[1] = data.mode_data;
    buf[2] = data.gripper;
    
    buf[3] = (uint8_t)(data.moter_x);
    buf[4] = (uint8_t)(data.moter_x >> 8);

    buf[5] = (uint8_t)(data.moter_y);
    buf[6] = (uint8_t)(data.moter_y >> 8);

    buf[7] = (uint8_t)(data.servo_top);
    buf[8] = (uint8_t)(data.servo_top >> 8);

    buf[9] = (uint8_t)(data.servo_mid);
    buf[10] = (uint8_t)(data.servo_mid >> 8);

    buf[11] = (uint8_t)(data.servo_bot);
    buf[12] = (uint8_t)(data.servo_bot >> 8);




    for(uint8_t i = 0; i < Packet_len; i++){
        buf[13] ^= buf[i];
    }
    return buf;
}

//여기서부터 다시 수정
void *PacketCodec::Decoding(void *argument){
    uint8_t *buf = static_cast<uint8_t *>(argument);
    data.mode_data = buf[1];
    data.moter_x = buf[2];
    data.moter_y = buf[3];
    data.gripper = buf[4];
    data.servo_top = 0;
    data.servo_top = (uint32_t)(buf[5]);
    data.servo_top |= (uint32_t)(buf[6] << 8);
    data.servo_top |= (uint32_t)(buf[7] << 16);
    data.servo_top |= (uint32_t)(buf[8] << 24);
    
    data.servo_mid = 0;
    data.servo_mid = (uint32_t)(buf[9]);
    data.servo_mid |= (uint32_t)(buf[10] << 8);
    data.servo_mid |= (uint32_t)(buf[11] << 16);
    data.servo_mid |= (uint32_t)(buf[12] << 24);

    data.servo_bot = 0;
    data.servo_bot = (uint32_t)(buf[13]);
    data.servo_bot |= (uint32_t)(buf[14] << 8);
    data.servo_bot |= (uint32_t)(buf[15] << 16);
    data.servo_bot |= (uint32_t)(buf[16] << 24);

    return &data;
}