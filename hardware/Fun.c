#include "stm32f10x.h"

void Fun_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;
    init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 100-1;
    timebase_init.TIM_Prescaler = 7200-1;
    TIM_TimeBaseInit(TIM2,&timebase_init);

    TIM_OCInitTypeDef oc_init;
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    oc_init.TIM_OutputState = TIM_OutputState_Enable;
    oc_init.TIM_Pulse = 2;
    TIM_OC1Init(TIM2,&oc_init);
    TIM_OC2Init(TIM2,&oc_init);

    TIM_Cmd(TIM2,ENABLE);

    // IC
    init.GPIO_Mode = GPIO_Mode_IPD;
    init.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA,&init);

    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 65536-1;
    timebase_init.TIM_Prescaler = 72-1;
    TIM_TimeBaseInit(TIM3,&timebase_init);

    TIM_ICInitTypeDef ic_init;
    ic_init.TIM_Channel = TIM_Channel_1;
    ic_init.TIM_ICFilter = 0xf;
    ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;
    ic_init.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    ic_init.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3,&ic_init);

    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    ic_init.TIM_Channel = TIM_Channel_2;
    ic_init.TIM_ICFilter = 0xf;
    ic_init.TIM_ICPolarity = TIM_ICPolarity_Falling;
    ic_init.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    ic_init.TIM_ICSelection = TIM_ICSelection_IndirectTI;
    TIM_ICInit(TIM3,&ic_init);

    TIM_Cmd(TIM3,ENABLE);
}

uint16_t Get_Freq(void){
    return 72000000/(TIM_GetPrescaler(TIM3)+1)/(TIM_GetCapture1(TIM3)+1);
}

uint16_t Get_Duty(void){
    return  (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}
