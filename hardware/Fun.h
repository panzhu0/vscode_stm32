#ifndef __FUN_H
#define __FUN_H

void Fun_Init(void);
uint16_t Get_AD(uint8_t ADC_Channel);
void Fun_DMA_Init(uint32_t MemAddr, uint32_t PeriphAddr,uint32_t Size);
void Fun_DMA_Trans(void);
#endif
