#ifndef __FUN_H
#define __FUN_H

extern uint16_t AD_Val[4];

void Fun_Init(void);
uint16_t Get_AD(void);
void Fun_DMA_Init(void);
void Fun_DMA_Trans(void);
#endif
