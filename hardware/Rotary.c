#include "stm32f10x.h"

volatile int16_t count_rotary;

void Rotary_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    // init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // AFIO
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);

    // EXTI
    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_Line = EXTI_Line8 | EXTI_Line11;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&exti_init);

    // NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic_init);

    nvic_init.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&nvic_init);

}


int16_t Get_Count_Rotary(void){
    return count_rotary;
}
