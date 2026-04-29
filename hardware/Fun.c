#include "stm32f10x.h"

// fun 1. when switch rotary , LED flash once.
void Fun_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Pin = GPIO_Pin_12;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    // B12 -> connect to LED ,When B12 output High -> LED light
    // A8 -> Rotary's A
    // A12 -> Rotary's B

    GPIO_Init(GPIOB,&init);
}

// Rotary 's A -> A8 
// Set to IPU when rotary, A8 -> Low , EXTI once -> LED light(0.5)ms

void Fun_EXTI_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA,&init);

    // AFIO
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);

    // EXTI
    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_Line = EXTI_Line8;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&exti_init);

    // NVIC
    NVIC_PriorityGroupConfig(2);

    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&nvic_init);
}

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line8) != RESET){
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}
