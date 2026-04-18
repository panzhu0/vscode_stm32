#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init(void){
    PWM_Init();
    // Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // GPIO conf
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    GPIO_SetBits(GPIOA,GPIO_Pin_5);
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
