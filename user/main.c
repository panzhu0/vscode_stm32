#include "stm32f10x.h"
#include "OLED.h"
#include "string.h"
#include "Fun.h"
#include "MyI2C.h"

int main(void){
    OLED_Init();
    MyI2C_Init();

    MyI2C_Start();
    MyI2C_SendByte(0xD0);   // 1101 000 0
    uint8_t AckBit;
    AckBit = MyI2C_RecvAck();
    MyI2C_Stop();

    OLED_ShowNum(1,1,AckBit,3);

    while(1){};
}
