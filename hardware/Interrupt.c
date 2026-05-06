#include "stm32f10x.h"
#include "Serial.h"

void USART1_IRQHandler(void){
    static uint8_t RxState = 0; // 0: wait for Start 1: wait for other data 2: wait for End
    static uint8_t pRxPkt = 0;

    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){
        // receive Pkt, storage data -> RxPkt 
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);

        uint8_t RxData = USART_ReceiveData(USART1);

        if(RxState == 0){
            if(RxData == '@'){
                RxState = 1;
            }
        }else if(RxState == 1){
            if(RxData == '\r'){
                RxState =2;
            }else{
                Serial_RxPkt[pRxPkt++] = RxData;
            }

        }else if(RxState == 2){
            if(RxData == '\n'){
                RxState=0;
                Serial_RxPkt[pRxPkt] = '\0';
                pRxPkt = 0;
                Serial_RxFlag = 1; // Receive a valid packet
            }
        }
    }
}
