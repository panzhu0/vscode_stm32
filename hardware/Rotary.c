#include "stm32f10x.h"
#include "PWM.h"
#include "Delay.h"
#include "OLED.h"

volatile uint16_t count=0;

void Rotary_Init(void){
    // Open clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
    // GPIO settings
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // AFIO settings
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);

    // EXTI settings
    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
    exti_init.EXTI_Line = EXTI_Line9;
    EXTI_Init(&exti_init);

    exti_init.EXTI_Line = EXTI_Line11;
    EXTI_Init(&exti_init);

    // NVIC settings
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannelPreemptionPriority= 2;
    nvic_init.NVIC_IRQChannelSubPriority= 2;
    nvic_init.NVIC_IRQChannelCmd= ENABLE;

    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&nvic_init);

    nvic_init.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&nvic_init);
}

void Show(void){
    OLED_ShowNum(1,4,count,3);
}

// interrupt function
void EXTI9_5_IRQHandler(void){
    // Line 9?
    if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == SET){
            Delay_ms(1);   // Agains noise of PWM
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == SET){
                // logic
                count ++;
                if(count > TIM2->ARR){
                    count = 0;
                }
                PWM_SetCompare1(count);
            }
        }
        // clear
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

void EXTI15_10_IRQHandler(void){
    // Line 11?
    if(EXTI_GetITStatus(EXTI_Line11)!=RESET){
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) == SET){
            Delay_ms(1);
            
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) == SET){
                // logic
                if(count==0){
                    count = TIM2->ARR;
                }else{
                    count--;
                }
                PWM_SetCompare1(count);
            }
        };
        // clear
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}

