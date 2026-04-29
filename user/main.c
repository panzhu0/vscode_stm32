#include "stm32f10x.h"
#include "OLED.h"

#include "Fun.h"
int main(void){
    OLED_Init();
    Fun_Init();
    OLED_ShowString(1,1,"CNT: ");
    OLED_ShowString(2,1,"CNT_R: ");

    while(1){
        OLED_ShowNum(1,7,Get_Count(),4);
        OLED_ShowNum(2,7,Get_Count_R(),4);
    };
}
