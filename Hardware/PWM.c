#include "stm32f10x.h"                  // Device header
//PWMƵ�ʣ�	Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//PWMռ�ձȣ�	Duty = CCR / (ARR + 1)
//PWM�ֱ��ʣ�	Reso = 1 / (ARR + 1)

//����TIM2 PA0���PWM
//����TIM3 PA6���PWM
void PWM_Init(void){
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //���߼���ʱ������APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//TIM2Ĭ������
	//GPIO_Pin_4 pwm GPIO_Pin_2 gnd
	//GPIO_Pin_5 pwm GPIO_Pin_3 gnd
	//���ų�ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM2ʱ����Դ���ڲ�ʱ�ӣ�72mhz��
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
	//ʱ����Ԫ��ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//����Ƚϳ�ʼ��
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//��Ĭ��ֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 50; //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//����TIM
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

//����CCR
void PWM_SetCompare1(uint16_t Compare, TIM_TypeDef * TIMx){
	TIM_SetCompare1(TIMx, Compare);
}

//����Ԥ��Ƶ
void PWM_SetPrescaler(uint16_t Prescaler, TIM_TypeDef * TIMx){
	TIM_PrescalerConfig(TIMx, Prescaler, TIM_PSCReloadMode_Immediate);
}
