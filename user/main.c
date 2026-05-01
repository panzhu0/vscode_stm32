#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"
#include "Delay.h"

int main(void){
    OLED_Init();
    Fun_Init();
    OLED_ShowString(1,1,"CNT: ");
    while(1){
        OLED_ShowSignedNum(1,6,Get_CNT(),5);
        Delay_ms(500);  // Use TIM interrupt better that Delay_ms!!!
    };
}
