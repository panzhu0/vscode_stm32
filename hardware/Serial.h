#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

extern uint8_t Serial_RxData;
extern uint8_t Serial_RxFlag;
extern uint8_t Serial_TxPkt[4];
extern uint8_t Serial_RxPkt[4];

uint8_t Serial_GetRxData(void);
uint8_t Serial_GetRxFlag(void);
void Serial_SendPkt(void);

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Array,uint16_t Length);
void Serial_SendString(char* Str);
void Serial_SendNum(uint32_t Num,uint16_t Length);
void Serial_Printf(char* format,...);

#endif
