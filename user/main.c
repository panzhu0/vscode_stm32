#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

#include "Timer.h"


// Review: Timer interrupt & EXIT interrupt
// Write both TIM & EXTI interrupt into Timer.c / .h
// Write interrupt function in main.c
int main(void){
    OLED_Init();
    TimerTest_Init();
    EXTITest_Init();
    OLED_ShowString(1,1,"Count: ");
    OLED_ShowString(2,1,"Count_exti: ");
    while(1){
        OLED_ShowNum(1,7,GetCount(),3);
        OLED_ShowNum(2,12,Get_Count_Exti(),3);
    }
}
