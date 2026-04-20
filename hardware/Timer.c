#include "stm32f10x.h"

void Timer_Init(void){
    // CLOCK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    // Timebase
    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 10000-1;    // ARR
    timebase_init.TIM_Prescaler = 7200-1; //  1KHz
    timebase_init.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM2,&timebase_init);

    // Timer interrupt 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    // NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = TIM2_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

    // Start
    TIM_Cmd(TIM2,ENABLE);
}

