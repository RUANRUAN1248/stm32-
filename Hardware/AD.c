#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4 ];

void AD_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//ѡ��ʱ�ӷ�Ƶ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72mhz / 6 = 12mhz
	 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//ѡ������Ͷ�ͨ��
	//ѡ��					 adc       ͨ�� 	����		����ʱ��
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
		
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //����
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //���뷽ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //��ʹ���ⲿ����
	ADC_InitStructure.ADC_NbrOfChannel = 4;//ɨ��ģʽ�µ�ͨ����Ŀ ��ͨ��д���
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//DISABLE������ת�� ENABLE������ת��  ����
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//DISABLE����ɨ��ģʽ ENABLE��ɨ��ģʽ  ����
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//DMA��ʼ��
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//ADC1Ϊ�����ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//ADC���ݴ洢��AD_Value������
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 4;//ɨ��4ͨ��
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ��ģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//Ӳ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//���ȼ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	//Ӳ������ ֱ��DMAʹ��
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//����ADC1 ��DMAͨ��
	ADC_DMACmd(ADC1, ENABLE);
	//ͨ��
	ADC_Cmd(ADC1, ENABLE);
	//У׼
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)); 
	
	//ADC���������һ�� ���Ż�һֱӲ���Զ�����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	//���� ADC���ϲɼ� DMA����ת��
}

//uint16_t AD_GetValue(void){ //��ʹ����ٵ�AD��ͨ��ʱ���ԼӲ���uint8_t ADC_Channel
//	
//	//ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);//���AD��ͨ��
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�����Ҫ����ת�� ��������Ƶ�����AD_Init()���
//	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//������ת������Ҫ����־λ ɾ��
//	return ADC_GetConversionValue(ADC1);//����ֵ�Զ������־λ 
//	
//}

