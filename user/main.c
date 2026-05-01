#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"
#include "Delay.h"

uint8_t a[4] = {0x1,0x2,0x3,0x4};
uint8_t b[4] = {0};

int main(void){
    OLED_Init();
    Fun_Init();
    Fun_DMA_Init((uint32_t)a,(uint32_t)b,4);
    OLED_ShowString(1,1,"A: ");
    OLED_ShowString(3,1,"B: ");
    while(1){
        OLED_ShowHexNum(1,3,a[0],2);
        OLED_ShowHexNum(1,7,a[1],2);
        OLED_ShowHexNum(1,11,a[2],2);
        OLED_ShowHexNum(1,15,a[3],2);

        OLED_ShowHexNum(2,3,b[0],2);
        OLED_ShowHexNum(2,7,b[1],2);
        OLED_ShowHexNum(2,11,b[2],2);
        OLED_ShowHexNum(2,15,b[3],2);
        Delay_ms(1000);
        Fun_DMA_Trans();

        OLED_ShowHexNum(1,3,a[0],2);
        OLED_ShowHexNum(1,7,a[1],2);
        OLED_ShowHexNum(1,11,a[2],2);
        OLED_ShowHexNum(1,15,a[3],2);

        OLED_ShowHexNum(2,3,b[0],2);
        OLED_ShowHexNum(2,7,b[1],2);
        OLED_ShowHexNum(2,11,b[2],2);
        OLED_ShowHexNum(2,15,b[3],2);

        a[0]+=1;
        a[1]+=1;
        a[2]+=1;
        a[3]+=1;
    }
    // OLED_ShowString(1,1,"AD1: ");
    // OLED_ShowString(2,1,"AD2: ");
    // OLED_ShowString(3,1,"AD3: ");
    // OLED_ShowString(4,1,"AD4: ");

    // while(1){
    //     OLED_ShowNum(1,6,Get_AD(ADC_Channel_0),4);
    //     OLED_ShowNum(2,6,Get_AD(ADC_Channel_1),4);
    //     OLED_ShowNum(3,6,Get_AD(ADC_Channel_2),4);
    //     OLED_ShowNum(4,6,Get_AD(ADC_Channel_3),4);
    // }
}
