#include "stm32f10x.h"

uint16_t AD_Value[4];

// ADC + DMA 
void AD_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    // DMA
    DMA_InitTypeDef dma_init;

    dma_init.DMA_BufferSize = 4 ;
    dma_init.DMA_DIR = DMA_DIR_PeripheralSRC;
    dma_init.DMA_M2M = DMA_M2M_Disable;

    dma_init.DMA_MemoryBaseAddr= (uint32_t)AD_Value;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;

    dma_init.DMA_Mode = DMA_Mode_Circular;

    dma_init.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// 16bit
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 

    dma_init.DMA_Priority = DMA_Priority_Medium;

    // ADC1 -> DMA CH1
    DMA_Init(DMA1_Channel1,&dma_init);
    DMA_Cmd(DMA1_Channel1,ENABLE);

    // ADC clock
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   // PCLK2 ==> APB2

    // OPEN DMA1 's 
    ADC_DMACmd(ADC1,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AIN;
    init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA,&init);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);   // ADC CH0 -> PA0
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);   
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);   
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);   

    ADC_InitTypeDef adc_init;
    adc_init.ADC_Mode = ADC_Mode_Independent;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfChannel = 4;
    adc_init.ADC_ScanConvMode = ENABLE;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc_init.ADC_ContinuousConvMode = ENABLE;
    ADC_Init(ADC1,&adc_init);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);

    // ADC continuous convert , DMA circular transfer.
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}


// void AD_GetValue(void){
//     DMA_Cmd(DMA1_Channel1,DISABLE);
//     DMA_SetCurrDataCounter(DMA1_Channel1,4);
//     DMA_Cmd(DMA1_Channel1,ENABLE);

//     while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//     DMA_ClearFlag(DMA1_FLAG_TC1);
// }
