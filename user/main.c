#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

#include "Encoder.h"
#include "Timer.h"

int16_t speed;

int main(void){
    OLED_Init();
    Timer_Init();
    Encoder_Init();
    OLED_ShowString(1,1,"Speed: ");
    while(1){
        OLED_ShowSignedNum(1,8,speed,4);
    };
}

// Timer2 's interrupt function
void TIM2_IRQHandler(){
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
        speed = Encoder_Get();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
