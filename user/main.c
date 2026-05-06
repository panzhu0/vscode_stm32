#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"
#include "string.h"
#include "Fun.h"

int main(void){
    OLED_Init();
    Serial_Init();
    Fun_Init();
    OLED_ShowString(1,1,"Working ...");

    while (1){
        if(Serial_GetRxFlag() == 1){
            OLED_ShowString(4,1,"               ");
            OLED_ShowString(4,1,Serial_RxPkt);
            
            if(strcmp(Serial_RxPkt,"LED_ON") == 0 ){
                LED_ON();
                Serial_SendString("LED_ON_OK\r\n");
                OLED_ShowString(2,1,"               ");
                OLED_ShowString(2,1,"LED_ON_OK");
            }else if(strcmp(Serial_RxPkt,"LED_OFF") == 0 ){
                LED_OFF();
                Serial_SendString("LED_OFF_OK\r\n");
                OLED_ShowString(2,1,"               ");
                OLED_ShowString(2,1,"LED_OFF_OK");
            }else{
                Serial_SendString("ERROR_COMMAND\r\n");
                OLED_ShowString(2,1,"               ");
                OLED_ShowString(2,1,"ERROR_COMMAND");
            }
        }
    };
}
