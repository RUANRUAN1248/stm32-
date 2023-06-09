#include "stm32f10x.h"                  // Device header

//ʱ��Դ�ͼ��������ɱ������ӹܵ����벶��
void Encoder_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;//A��B�� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//ʱ��Դ�ɱ������ӹ�
	//TIM3ʱ����Դ �ڲ�ʱ�ӣ�72mhz��
	//TIM_InternalClockConfig(TIM3);
	
	//ʱ����Ԫ��ʼ����������ֻ��ARR PSC�õ��ˣ�
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);


	//���벶���ʼ��
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xf;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//������
	TIM_ICInit(TIM3 ,&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xf;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//������
	TIM_ICInit(TIM3 ,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
	TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_Get(void){
	
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Temp;
	
}

//Timer_Init(); //һ�붨ʱ ���ж�

//void TIM2_IRQHandler(void)//�ο� �жϺ���
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		Speed = Encoder_Get();
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

