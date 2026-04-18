#include "stm32f10x.h"
#include "OLED.h"
#include "PWM.h"
#include "Rotary.h"
#include "Motor.h"

int main(void){
    OLED_Init();
    PWM_Init();
    Rotary_Init();
    Motor_Init();
    while(1){
        Show();
    };
}
