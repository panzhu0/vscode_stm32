#include "stm32f10x.h"

uint16_t My_DMA_Size;

void My_DMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size){
    My_DMA_Size = Size;

    // CLK
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    // DMA init
    DMA_InitTypeDef dma_init;
    dma_init.DMA_PeripheralBaseAddr = AddrA;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;      // 1Byte
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Enable; 

    dma_init.DMA_MemoryBaseAddr = AddrB;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;

    dma_init.DMA_DIR = DMA_DIR_PeripheralSRC;
    // Size once DMA
    dma_init.DMA_BufferSize = Size;
    dma_init.DMA_Mode = DMA_Mode_Normal;

    dma_init.DMA_M2M = DMA_M2M_Enable;

    dma_init.DMA_Priority = DMA_Priority_Medium;

    DMA_Init(DMA1_Channel1,&dma_init);

    DMA_Cmd(DMA1_Channel1,DISABLE);
}

void DMA_Transfer(void){
    DMA_Cmd(DMA1_Channel1,DISABLE);

    DMA_SetCurrDataCounter(DMA1_Channel1,My_DMA_Size);

    DMA_Cmd(DMA1_Channel1,ENABLE);

    // wait for DMA finish
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);   // reset
}
