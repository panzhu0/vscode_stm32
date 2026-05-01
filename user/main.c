#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"
#include "Delay.h"

int main(void){
    OLED_Init();
    Fun_DMA_Init();
    Fun_Init();

    OLED_ShowString(1,1,"AD1: ");
    OLED_ShowString(2,1,"AD2: ");
    OLED_ShowString(3,1,"AD3: ");
    OLED_ShowString(4,1,"AD4: ");

    while(1){
        Fun_DMA_Trans();
        OLED_ShowNum(1,6,AD_Val[0],4);
        OLED_ShowNum(2,6,AD_Val[1],4);
        OLED_ShowNum(3,6,AD_Val[2],4);
        OLED_ShowNum(4,6,AD_Val[3],4);
    }
}
