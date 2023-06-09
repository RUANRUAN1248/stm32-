#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	//��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��ʱ���ⲿ�ж�
	
	//��ʱ���ⲿ�ж� ��������
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//ʱ��Դѡ��
	TIM_InternalClockConfig(TIM2);
	
	//��ʱ���ⲿ�ж� ѡ��Ϊ�ⲿʱ��Դ
//	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
	
	//��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//��� �����жϱ�־λ���������������/�����������������ʼ��(ͨ����������ڲ�/�ⲿ����)���ᴥ�������־λ 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	//ʹ�ܶ�ʱ���ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//�жϷ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//�жϳ�ʼ��
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//������ʱ��
	//TIM_Cmd(TIM2, ENABLE);
}
//�жϷ�����ģ��
/*
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/

