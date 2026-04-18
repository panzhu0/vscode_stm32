#include "stm32f10x.h"

void PWM_Init(void){
    // 1.clock 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // 2.timebase 2 conf
    TIM_TimeBaseInitTypeDef time_init;
    time_init.TIM_ClockDivision = TIM_CKD_DIV1;
    time_init.TIM_CounterMode = TIM_CounterMode_Up;
    time_init.TIM_Prescaler = 36-1;     // 72/36 = 2Mhz
    time_init.TIM_Period = 100;          // RCC
    TIM_TimeBaseInit(TIM2,&time_init);

    // 3. OC conf
    TIM_OCInitTypeDef oc_init;
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OutputState = ENABLE;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    oc_init.TIM_Pulse = 15;// CCR
    TIM_OC3Init(TIM2,&oc_init);     // TIM2 's OC CH3 -> PA2
    TIM_OC1
    Init(TIM2,&oc_init);     // TIM2 's OC CH3 -> PA2

    // 4. GPIO conf
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;
    init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_0;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // 5. enable TIM
    TIM_Cmd(TIM2,ENABLE);
};

void PWM_SetCompare(uint16_t compare){
    TIM_SetCompare1(TIM2,compare);
    TIM_SetCompare3(TIM2,compare);
};
