#include "stm32f10x.h"

// TIM 
void Fun_Init(void)
{
    // -- 时钟 --
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // -- GPIO : PA0, PA1 作为编码器输入, 使用内部上拉 --
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode  = GPIO_Mode_IPU;
    gpio.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    // -- 时基 --
    TIM_TimeBaseInitTypeDef timebase;
    TIM_TimeBaseStructInit(&timebase);       // ✅ 先全部默认值
    timebase.TIM_Period        = 65536 - 1; // 满量程
    timebase.TIM_Prescaler     = 0;          // 编码器模式一般用0
    timebase.TIM_ClockDivision = TIM_CKD_DIV1;
    timebase.TIM_CounterMode   = TIM_CounterMode_Up; // 不影响编码器方向
    TIM_TimeBaseInit(TIM2, &timebase);

    // -- 直接配置编码器模式 --
    TIM_EncoderInterfaceConfig(TIM2,
        TIM_EncoderMode_TI12,           // 两个边沿都计数
        TIM_ICPolarity_Rising,          // TI1 上升沿
        TIM_ICPolarity_Rising);         // TI2 上升沿

    // -- 想加滤波器直接写寄存器 (IC1F, IC2F) --
    TIM2->CCMR1 |= (0x0F << 4);   // CH1 滤波 0xF
    TIM2->CCMR1 |= (0x0F << 12);  // CH2 滤波 0xF

    // -- 启动定时器 --
    TIM_Cmd(TIM2, ENABLE);
}

uint16_t GetVal(void){
    return TIM_GetCounter(TIM2);
}
