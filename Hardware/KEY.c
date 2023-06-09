#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void KEY_Init(void){
//��������		GPIO_MODE_IN_FLOATING	��������	�ɶ�ȡ���ŵ�ƽ�����������գ����ƽ��ȷ��
//��������		GPIO_MODE_IPU			��������	�ɶ�ȡ���ŵ�ƽ���ڲ������������裬����ʱĬ�ϸߵ�ƽ
//��������		GPIO_MODE_IPD			��������	�ɶ�ȡ���ŵ�ƽ���ڲ������������裬����ʱĬ�ϵ͵�ƽ
//ģ������		GPIO_MODE_AIN			ģ������	GPIO��Ч������ֱ�ӽ����ڲ�ADC
//��©���		GPIO-MODE_OUT_OD		�������	��������ŵ�ƽ���ߵ�ƽΪ����̬���͵�ƽ��VSS
//�������		GPIO_MODE_OUT_PP		�������	��������ŵ�ƽ���ߵ�ƽ��VDD���͵�ƽ��VSS
//���ÿ�©���	GPIO_MODE_AF_OD			�������	��Ƭ��������ƣ��ߵ�ƽΪ����̬���͵�ƽ��VSS
//�����������	GOIO_MODE_AF_PP			�������	��Ƭ��������ƣ��ߵ�ƽ��VDD���͵�ƽ��VSS
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

