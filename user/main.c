#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"
#include "Delay.h"

volatile int8_t a[4]={0x1,0x2,0x3,0x4};
volatile int8_t b[4]={0};

int main(void){
    OLED_Init();
    Fun_Init((uint32_t)a,(uint32_t)b);
    OLED_ShowString(1,1,"A: ");
    OLED_ShowString(2,1,"B: ");
    while(1){
        OLED_ShowHexNum(1,3,a[0],2);
        OLED_ShowHexNum(1,7,a[1],2);
        OLED_ShowHexNum(1,11,a[2],2);
        OLED_ShowHexNum(1,15,a[3],2);

        OLED_ShowHexNum(2,3,b[0],2);
        OLED_ShowHexNum(2,7,b[1],2);
        OLED_ShowHexNum(2,11,b[2],2);
        OLED_ShowHexNum(2,15,b[3],2);

        Delay_ms(500);
        DMA_Trans();

        OLED_ShowHexNum(1,3,a[0],2);
        OLED_ShowHexNum(1,7,a[1],2);
        OLED_ShowHexNum(1,11,a[2],2);
        OLED_ShowHexNum(1,15,a[3],2);

        OLED_ShowHexNum(2,3,b[0],2);
        OLED_ShowHexNum(2,7,b[1],2);
        OLED_ShowHexNum(2,11,b[2],2);
        OLED_ShowHexNum(2,15,b[3],2);
        Delay_ms(500);
        a[0]+=1;
        a[1]+=1;
        a[2]+=1;
        a[3]+=1;
    }
}
