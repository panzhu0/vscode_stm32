#include "stm32f10x.h"

void Fun_Init(void){
    // RCC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);


    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AIN;
    init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA,&init);

    // ADC
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 12MHz

    ADC_InitTypeDef adc_init;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc_init.ADC_Mode = ADC_Mode_Independent;
    adc_init.ADC_ContinuousConvMode = ENABLE;  // Only Convert Once when called
    adc_init.ADC_ScanConvMode = DISABLE;    // Only CH1 work
    adc_init.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1,&adc_init);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);

    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t Get_AD(uint8_t ADC_Channel){
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);

    // while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

void Fun_DMA_Init(uint32_t MemAddr, uint32_t PeriphAddr,uint32_t Size){
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    DMA_InitTypeDef dma_init;
    dma_init.DMA_BufferSize = Size;
    dma_init.DMA_DIR = DMA_DIR_PeripheralDST;
    dma_init.DMA_M2M = DMA_M2M_Enable;
    dma_init.DMA_MemoryBaseAddr = MemAddr;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_Mode = DMA_Mode_Normal;
    dma_init.DMA_PeripheralBaseAddr = PeriphAddr;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    dma_init.DMA_Priority = DMA_Priority_Medium;

    DMA_Init(DMA1_Channel1,&dma_init);
}

void Fun_DMA_Trans(void){

    DMA_Cmd(DMA1_Channel1,DISABLE);

    DMA_SetCurrDataCounter(DMA1_Channel1,4);

    DMA_ClearFlag(DMA1_FLAG_TC1);
    DMA_Cmd(DMA1_Channel1,ENABLE);

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
}
