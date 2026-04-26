#include "stm32f10x.h"

void PWM_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;
    init.GPIO_Pin = GPIO_Pin_1;     // TIM2 CH2 -> PA1
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision= TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 100 - 1;     //  ARR -> 1M/100 = 20KHz
    timebase_init.TIM_Prescaler = 36 - 1;   // 2MHz
    TIM_TimeBaseInit(TIM2,&timebase_init);

    TIM_OCInitTypeDef oc_init;
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    oc_init.TIM_OutputState = ENABLE;
    oc_init.TIM_Pulse =  100;            // CCR
    TIM_OC2Init(TIM2,&oc_init);

    TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

    TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare(uint16_t u){
    TIM_SetCompare2(TIM2,u);
};
