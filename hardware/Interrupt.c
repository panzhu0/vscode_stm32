#include "stm32f10x.h"
#include "Fun.h"
#include "OLED.h"

void EXTI15_10_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line14) != RESET){
        count_t +=1;

        EXTI_ClearITPendingBit(EXTI_Line14);
    }

    if(EXTI_GetITStatus(EXTI_Line11)!=RESET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == Bit_SET){
            count_r -=1;
        }
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line8)!=RESET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == Bit_SET){
            count_r+=1;
        }
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}
