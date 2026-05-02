#include "stm32f10x.h"

// ADC  
void Fun_Init(uint32_t AddrA,uint32_t AddrB){
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_InitTypeDef dma_init;
    dma_init.DMA_BufferSize = 4;
    dma_init.DMA_DIR = DMA_DIR_PeripheralDST;
    dma_init.DMA_M2M = DMA_M2M_Enable;
    dma_init.DMA_MemoryBaseAddr = AddrA;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_Mode = DMA_Mode_Normal;
    dma_init.DMA_PeripheralBaseAddr = AddrB;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    dma_init.DMA_Priority = DMA_Priority_Medium;

    DMA_Init(DMA1_Channel1,&dma_init);
}


void DMA_Trans(void){
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1);

    DMA_SetCurrDataCounter(DMA1_Channel1,4);

    DMA_Cmd(DMA1_Channel1,ENABLE);

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
}
