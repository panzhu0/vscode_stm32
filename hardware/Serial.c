#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_PP;   // Only send data
    init.GPIO_Pin = GPIO_Pin_9;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&init);

    USART_InitTypeDef usart_init;
    usart_init.USART_BaudRate = 9600;
    usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init.USART_Mode = USART_Mode_Tx;
    usart_init.USART_Parity = USART_Parity_No;
    usart_init.USART_StopBits = USART_StopBits_1;
    usart_init.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&usart_init);

    USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte){
    USART_SendData(USART1,Byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
    // When next write , USART_FLAG_TXE will auto set to RESET
}

void Serial_SendArray(uint8_t* Array,uint16_t Length){
    uint16_t i=0;
    while(i<Length) Serial_SendByte(Array[i++]);
}

void Serial_SendString(char* Str){
    uint16_t i=0;
    for(i=0;Str[i]!='\0';i++) Serial_SendByte(Str[i]);
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y){
    uint32_t Result = 1;
    while(Y--){
        Result *= X;
    }
    return Result;
}

void Serial_SendNum(uint32_t Num,uint16_t Length){
    int16_t i = 0;
    for(i=0;i<Length;i++) Serial_SendByte(  Num / Serial_Pow(10,Length-i-1) %10  + '0' );
}

// Redirect
int fputc(int ch,FILE* f){
    Serial_SendByte(ch);
    return ch;
}


void Serial_Printf(char* format,...){
    char String[100];
    va_list arg;
    va_start(arg,format);
    vsprintf(String,format,arg);
    va_end(arg);
    Serial_SendString(String);
}
