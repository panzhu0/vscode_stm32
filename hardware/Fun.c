#include "stm32f10x.h"

uint16_t count_t;
uint16_t count_r;

void Fun_Init(void){
    // CLK
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);


    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB,&init);

    init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_12;
    GPIO_Init(GPIOA,&init);

    // AFIO
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);

    // EXTI
    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_Line = EXTI_Line8 |EXTI_Line12 | EXTI_Line14; 
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&exti_init);

    // NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = EXTI15_10_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic_init);

    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 2;

    NVIC_Init(&nvic_init);
};

uint16_t Get_Count(void){
    return count_t;
}

uint16_t Get_Count_R(void){
    return count_r;
}

