#include "stm32f10x.h"

void AD_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

    // ADC clock
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   // PCLK2 ==> APB2

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AIN;
    init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA,&init);


    ADC_InitTypeDef adc_init;
    adc_init.ADC_Mode = ADC_Mode_Independent;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfChannel = 1;
    adc_init.ADC_ScanConvMode = DISABLE;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc_init.ADC_ContinuousConvMode = DISABLE;
    ADC_Init(ADC1,&adc_init);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);

}


uint16_t AD_GetValue(uint8_t ADC_Channel){
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);   // ADC CH0 -> PA0
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1);
}
