#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"

int main(void){
    OLED_Init();
    Fun_Init();

    OLED_ShowString(1,2,"CCR: ");
    while(1){
        OLED_ShowNum(1,7,TIM3->CCR2,5);
    }
}
