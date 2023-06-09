#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4 ];

void AD_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//选择时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72mhz / 6 = 12mhz
	 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//选择规则型多通道
	//选择					 adc       通道 	次序		采样时间
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
		
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //独立
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //对齐方式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不使用外部触发
	ADC_InitStructure.ADC_NbrOfChannel = 4;//扫描模式下的通道数目 多通道写多个
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//DISABLE：单次转换 ENABLE：连续转换  常改
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//DISABLE：非扫描模式 ENABLE：扫描模式  常改
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//DMA初始化
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//ADC1为外设地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//ADC数据存储在AD_Value数组里
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 4;//扫描4通道
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//循环模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//硬件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//优先级中
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	//硬件触发 直接DMA使能
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//开启ADC1 的DMA通道
	ADC_DMACmd(ADC1, ENABLE);
	//通电
	ADC_Cmd(ADC1, ENABLE);
	//校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)); 
	
	//ADC先软件触发一次 接着会一直硬件自动触发
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	//至此 ADC不断采集 DMA不断转运
}

//uint16_t AD_GetValue(void){ //当使用虚假的AD多通道时可以加参数uint8_t ADC_Channel
//	
//	//ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);//虚假AD多通道
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//如果需要连续转换 则把这行移到上面AD_Init()最后
//	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//若连续转换则不需要读标志位 删除
//	return ADC_GetConversionValue(ADC1);//读数值自动清除标志位 
//	
//}

