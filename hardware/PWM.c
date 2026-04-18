#include "stm32f10x.h"

void PWM_Init(void){
    // 1.clock 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // 2.timebase 2 conf
    TIM_TimeBaseInitTypeDef time_init;
    time_init.TIM_ClockDivision = TIM_CKD_DIV1;
    time_init.TIM_CounterMode = TIM_CounterMode_Up;
    time_init.TIM_Prescaler = 720-1;     // 72/72= 1Mhz 
    time_init.TIM_Period = 100-1;          // RCC
    TIM_TimeBaseInit(TIM2,&time_init);

    // 3. OC conf
    TIM_OCInitTypeDef oc_init;
    oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    oc_init.TIM_OutputState = ENABLE;
    oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    oc_init.TIM_Pulse = 15;// CCR
    TIM_OC1Init(TIM2,&oc_init);     // TIM2 's OC CH3 -> PA1

    // 5. GPIO conf
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;
    init.GPIO_Pin = GPIO_Pin_0;     // PWM output
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // 5. enable TIM
    TIM_Cmd(TIM2,ENABLE);
};


// Set Prescalar
void PWM_SetPrescalar(uint16_t prescalar){
    TIM_PrescalerConfig(TIM2,prescalar,TIM_PSCReloadMode_Immediate);
}

// Set compare: CCR
void PWM_SetCompare1(uint8_t compare){
    TIM_SetCompare1(TIM2,compare);
}
