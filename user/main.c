#include "stm32f10x.h"
#include "OLED.h"
#include "AD.h"

uint16_t ad_val;

int main(){
    OLED_Init();
    AD_Init();

    OLED_ShowString(1,1,"AD value: ");
    while(1){
        ad_val = AD_GetValue();
        OLED_ShowNum(1,11,ad_val,4);
    }
}
