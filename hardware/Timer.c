#include "stm32f10x.h"

uint16_t count_t = 0;
uint16_t count_exti = 0;

void TimerTest_Init(void){
    // CLOCK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    // Timer 
    TIM_TimeBaseInitTypeDef timebase_init;
    timebase_init.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase_init.TIM_CounterMode = TIM_CounterMode_Up;
    timebase_init.TIM_Period = 10000-1;   // 10K
    timebase_init.TIM_Prescaler = 7200-1; // 10KHz
    timebase_init.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM2,&timebase_init);

    // TIM Interrupt
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    // NVIC 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = TIM2_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic_init);

    // Start
    TIM_Cmd(TIM2,ENABLE);
};

// Timer 2 's interrupt handler function
void TIM2_IRQHandler(void){
    // TIM2 's update interrupt
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
        count_t +=1;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}

uint16_t GetCount(void){
    return count_t;
}

// PA0 
void EXTITest_Init(void){
    // CLOCK
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // GPIOA init
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_0;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // EXTI
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_Pin_0);   // PA0

    EXTI_InitTypeDef exti_init;
    exti_init.EXTI_Line = EXTI_Line0;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&exti_init);

    // NVIC
    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = EXTI0_IRQn;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&nvic_init);

};

// PA0 's interrupt  function
void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) != RESET){
        count_exti+=1;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

uint16_t Get_Count_Exti(void){
    return count_exti;
}

