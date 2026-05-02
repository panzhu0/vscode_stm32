#include "stm32f10x.h"

// TIM 
void Fun_Init(void){
    // TIM2 Encoder
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOA,&init);

    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 65536-1;
    timebase_init.TIM_Prescaler = 1-1;
    timebase_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&timebase_init);

    TIM_ICInitTypeDef ic_init;
    TIM_ICStructInit(&ic_init);
    ic_init.TIM_Channel = TIM_Channel_1;
    ic_init.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2,&ic_init);
    ic_init.TIM_Channel = TIM_Channel_2;
    ic_init.TIM_ICFilter = 0xF;
    TIM_ICInit(TIM2,&ic_init);

    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    TIM_Cmd(TIM2,ENABLE);
}

uint16_t GetVal(void){
    return TIM_GetCounter(TIM2);
}
