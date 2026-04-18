#include "stm32f10x.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
#include "Delay.h"

int main(void){
    OLED_Init();
    PWM_Init();
    IC_Init();
    OLED_ShowString(1,1,"Freq: ");
    while(1){
        Delay_ms(200);
        OLED_ShowNum(1,7,IC_GetFreq(),5);
    };
}
