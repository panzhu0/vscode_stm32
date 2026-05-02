#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void){
    OLED_Init();
    Serial_Init();

    while (1){
        if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET){ // receive register not empty
            RxData = USART_ReceiveData(USART1);     // After Received USART_FLAG_RXNE auto -> RESET
            OLED_ShowHexNum(1,1,RxData,2);
        }
    };
}
