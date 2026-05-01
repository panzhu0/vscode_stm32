#include "stm32f10x.h"
#include "Delay.h"

uint16_t count;

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line8)==SET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == RESET && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == SET){
            count+=1;
            TIM3->CCR1 = count;
            TIM3->CCR2 = count;
        }
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}

void EXTI15_10_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line11) == SET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == RESET && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == SET){
            count-=1;
            TIM3->CCR1 = count;
            TIM3->CCR2 = count;
        }

        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}
