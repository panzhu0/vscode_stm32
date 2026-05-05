#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void){
    OLED_Init();
    Serial_Init();

    Serial_TxPkt[0] = 0x01;
    Serial_TxPkt[1] = 0x02;
    Serial_TxPkt[2] = 0x03;
    Serial_TxPkt[3] = 0x04;

    Serial_SendPkt();

    while (1){
        if(Serial_GetRxFlag() == 1){
            OLED_ShowHexNum(1,1,Serial_RxPkt[0],2);
            OLED_ShowHexNum(1,4,Serial_RxPkt[1],2);
            OLED_ShowHexNum(1,7,Serial_RxPkt[2],2);
            OLED_ShowHexNum(1,10,Serial_RxPkt[3],2);
        }
    };
}
