#include "stm32f10x.h"

void Encoder_Init(void){
    // CLOCK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    // TIMEBASE
    TIM_TimeBaseInitTypeDef timebase_init;
    // decided by Timer 's encoder (Automatically)
    // timebaes_init.TIM_ClockDivision;
    // timebaes_init.TIM_CounterMode;
    // timebaes_init.TIM_RepetitionCounter;
    timebase_init.TIM_Period = 65536-1;
    timebase_init.TIM_Prescaler= 1-1;
    TIM_TimeBaseInit(TIM3,&timebase_init);

    // IC
    TIM_ICInitTypeDef ic_init;
    TIM_ICStructInit(&ic_init);
    ic_init.TIM_Channel = TIM_Channel_1;
    ic_init.TIM_ICFilter = 0xF;
    // When we using Timer encoder, Rising means Priority not reverse
    // ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;     // NOT REVERSE
    // ic_init.TIM_ICPrescaler;
    // ic_init.TIM_ICSelection;
    TIM_ICInit(TIM3,&ic_init);

    ic_init.TIM_Channel = TIM_Channel_2;
    ic_init.TIM_ICFilter = 0xF;
    // ic_init.TIM_ICPolarity = TIM_ICPolarity_Rising;     // NOT REVERSE
    TIM_ICInit(TIM3,&ic_init);

    // ENCODER
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    // START
    TIM_Cmd(TIM3,ENABLE);
};

int16_t Encoder_Get(void){
    int16_t temp;
    temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return temp;
}
