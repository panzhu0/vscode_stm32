#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

#include "Fun.h"

int main(){
    OLED_Init();
    OLED_ShowString(1,1,"Hello world");
    Fun_Init();
    Fun_EXTI_Init();

    while(1){
        Delay_ms(500);
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    };
}
