#include "stm32f10x.h"
#include "OLED.h"
#include "Fun.h"

int main(void){
    OLED_Init();
    Fun_Init();
    OLED_ShowString(1,1,"CNT: ");
    while(1){
        OLED_ShowNum(1,6,GetVal(),5);
    }
}
