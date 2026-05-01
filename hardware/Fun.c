#include "stm32f10x.h"

void Fun_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOA,&init);

    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_Period = 65536-1;
    timebase_init.TIM_Prescaler = 1-1;
    TIM_TimeBaseInit(TIM3,&timebase_init);

    TIM_ICInitTypeDef ic_init;
    ic_init.TIM_Channel = TIM_Channel_1;
    ic_init.TIM_ICFilter = 0xf;
    TIM_ICInit(TIM3,&ic_init);

    ic_init.TIM_Channel = TIM_Channel_2;
    ic_init.TIM_ICFilter = 0xf;
    // In Encoder mode : means High & Low not change
    TIM_ICInit(TIM3,&ic_init);

    // Encoder
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3,ENABLE);
}

int16_t Get_CNT(void){
    int16_t tmp;
    tmp= TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return tmp;
}
