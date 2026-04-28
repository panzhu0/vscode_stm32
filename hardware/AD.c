#include "stm32f10x.h"

uint16_t ADC_Val;

void AD_Init(void){
    // CLK
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // GPIO init
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AIN;
    init.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA,&init);

    // ADC init
    ADC_InitTypeDef adc_init;
    adc_init.ADC_ContinuousConvMode = DISABLE;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc_init.ADC_Mode = ADC_Mode_Independent;
    adc_init.ADC_NbrOfChannel = 1;
    adc_init.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1,&adc_init);

    // ADC regular config
    // ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);

    // ADC enable
    ADC_Cmd(ADC1,ENABLE);

    // ADC calibration
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetVal(uint8_t ADC_Channel){
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

