#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void KEY_Init(void){
//浮空输入		GPIO_MODE_IN_FLOATING	数字输入	可读取引脚电平，若引脚悬空，则电平不确定
//上拉输入		GPIO_MODE_IPU			数字输入	可读取引脚电平，内部连接上拉电阻，悬空时默认高电平
//下拉输入		GPIO_MODE_IPD			数字输入	可读取引脚电平，内部连接下拉电阻，悬空时默认低电平
//模拟输入		GPIO_MODE_AIN			模拟输入	GPIO无效，引脚直接接入内部ADC
//开漏输出		GPIO-MODE_OUT_OD		数字输出	可输出引脚电平，高电平为高阻态，低电平接VSS
//推挽输出		GPIO_MODE_OUT_PP		数字输出	可输出引脚电平，高电平接VDD，低电平接VSS
//复用开漏输出	GPIO_MODE_AF_OD			数字输出	由片上外设控制，高电平为高阻态，低电平接VSS
//复用推挽输出	GOIO_MODE_AF_PP			数字输出	由片上外设控制，高电平接VDD，低电平接VSS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint32_t Key_GetNum(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	uint32_t KeyNum = 0;
	//KeyNum = GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
	if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)
		Delay_ms(20);
		KeyNum = 1;
	}
//	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0){
//		Delay_ms(20);
//		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
//		Delay_ms(20);
//		KeyNum = 2;
//	}
	return KeyNum;
}

