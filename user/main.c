#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"
#include "Delay.h"

int main(void){
    OLED_Init();
    Fun_Init();
    OLED_ShowString(1,1,"AD1: ");
    OLED_ShowString(2,1,"AD2: ");
    OLED_ShowString(3,1,"AD3: ");
    OLED_ShowString(4,1,"AD4: ");
    while(1){
        OLED_ShowNum(1,6,Get_AD(ADC_Channel_0),4);
        OLED_ShowNum(2,6,Get_AD(ADC_Channel_1),4);
        OLED_ShowNum(3,6,Get_AD(ADC_Channel_2),4);
        OLED_ShowNum(4,6,Get_AD(ADC_Channel_3),4);
    }
}
