#include "stm32f10x.h"

void IC_Init(void){
    // CLOCK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);     // TIM3 's CH1 -> PA6
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_6;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // Timebase
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 65536-1;
    timebase_init.TIM_Prescaler = 72-1;     // 1MHz
    timebase_init.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM3,&timebase_init);

    // IC
    TIM_ICInitTypeDef ic_init;
    ic_init.TIM_Channel = TIM_Channel_1;
    ic_init.TIM_ICFilter= 0xf;
    ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;
    ic_init.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    ic_init.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_ICInit(TIM3,&ic_init);

    // PWMI
    // ic_init.TIM_Channel = TIM_Channel_2;
    // ic_init.TIM_ICFilter= 0xf;
    // ic_init.TIM_ICPolarity = TIM_ICPolarity_Falling;
    // ic_init.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    // ic_init.TIM_ICSelection = TIM_ICSelection_IndirectTI;
    // TIM_ICInit(TIM3,&ic_init);

    // equality (Set to reverse to CH1 's settings)
    TIM_PWMIConfig(TIM3,&ic_init);  // CH2 + Falling + IndirectTI

    // TRGI
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);     // Timer3 's CH1 's filter output Rising polarity Trigger
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);  // When trigger -> Reset CNT

    // Start
    TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void){
    return 72000000/ (TIM_GetPrescaler(TIM3) + 1)/ (TIM_GetCapture1(TIM3) + 1);
    // real Freq Need to divide (CCR+1) and (PSC+1)
}

uint32_t IC_GetDuty(void){
    return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1) ;
}
