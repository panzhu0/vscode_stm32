#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "MyDMA.h"

const uint8_t DataA[] = {0x01,0x02,0x03,0x04};  // In ROM memory (if const)
uint8_t DataB[] = {0,0,0,0};

int main(){
    OLED_Init();

    My_DMA_Init((uint32_t)DataA,(uint32_t)DataB,4);

    OLED_ShowString(1,1,"DataA");
    OLED_ShowHexNum(1,8,(uint32_t)DataA,8);
    OLED_ShowString(3,1,"DataB");
    OLED_ShowHexNum(3,8,(uint32_t)DataB,8);

    OLED_ShowHexNum(2,1,DataA[0],2);
    OLED_ShowHexNum(2,4,DataA[1],2);
    OLED_ShowHexNum(2,7,DataA[2],2);
    OLED_ShowHexNum(2,10,DataA[3],2);

    OLED_ShowHexNum(4,1,DataB[0],2);
    OLED_ShowHexNum(4,4,DataB[1],2);
    OLED_ShowHexNum(4,7,DataB[2],2);
    OLED_ShowHexNum(4,10,DataB[3],2);

    while (1){
        // DataA[0]++;
        // DataA[1]++;
        // DataA[2]++;
        // DataA[3]++;
        OLED_ShowHexNum(2,1,DataA[0],2);
        OLED_ShowHexNum(2,4,DataA[1],2);
        OLED_ShowHexNum(2,7,DataA[2],2);
        OLED_ShowHexNum(2,10,DataA[3],2);

        OLED_ShowHexNum(4,1,DataB[0],2);
        OLED_ShowHexNum(4,4,DataB[1],2);
        OLED_ShowHexNum(4,7,DataB[2],2);
        OLED_ShowHexNum(4,10,DataB[3],2);

        Delay_s(1);
        DMA_Transfer();

        OLED_ShowHexNum(2,1,DataA[0],2);
        OLED_ShowHexNum(2,4,DataA[1],2);
        OLED_ShowHexNum(2,7,DataA[2],2);
        OLED_ShowHexNum(2,10,DataA[3],2);

        OLED_ShowHexNum(4,1,DataB[0],2);
        OLED_ShowHexNum(4,4,DataB[1],2);
        OLED_ShowHexNum(4,7,DataB[2],2);
        OLED_ShowHexNum(4,10,DataB[3],2);
        Delay_s(1);
    };
}
