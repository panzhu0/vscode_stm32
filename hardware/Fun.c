#include "stm32f10x.h"

void Fun_Init(void){
    // CLK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;
    init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_Init(GPIOA,&init);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);

    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_Line = EXTI_Line8;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&exti_init);

    exti_init.EXTI_Line = EXTI_Line11;
    EXTI_Init(&exti_init);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&nvic_init);

    nvic_init.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&nvic_init);

    // TIMEBASE
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 100-1;   // 72M / 1M / ARR
    timebase_init.TIM_Prescaler = 72-1; // 1MHz
    TIM_TimeBaseInit(TIM3,&timebase_init);

    // OC
    TIM_OCInitTypeDef oc_init;
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    oc_init.TIM_OutputState = TIM_OutputState_Enable;
    oc_init.TIM_Pulse = 10;
    TIM_OC2Init(TIM3,&oc_init);     // PA7
    TIM_OC1Init(TIM3,&oc_init);  // PA6

    TIM_Cmd(TIM3,ENABLE);

    // IC (TIM2)
}
