#include "stm32f10x.h"

void Fun_Init(void){
    // RCC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

    // GPIO
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AIN;
    init.GPIO_Pin = GPIO_Pin_0;
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

    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1,ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);

    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t Get_AD(uint8_t ADC_Channel){
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}
