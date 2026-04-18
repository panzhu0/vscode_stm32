#include "stm32f10x.h"

void IC_Init(void){
    // CLOCK
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}