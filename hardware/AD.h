#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[4];

uint16_t AD_GetVal(uint8_t ADC_Channel);
void AD_Init(void);

#endif
