#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

int main(void){
    OLED_Init();
    Serial_Init();
    Serial_Send(0x41);

    while(1){};
}