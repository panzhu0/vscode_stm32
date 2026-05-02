#include "stm32f10x.h"
#include "Serial.h"

void USART1_IRQHandler(void){
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);

        Serial_RxData = USART_ReceiveData(USART1);
        Serial_RxFlag = 1;
        
    }
}
