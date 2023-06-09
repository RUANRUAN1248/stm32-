#include "stm32f10x.h"                  // Device header
//PWM频率：	Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//PWM占空比：	Duty = CCR / (ARR + 1)
//PWM分辨率：	Reso = 1 / (ARR + 1)

//设置TIM2 PA0输出PWM
//设置TIM3 PA6输出PWM
void PWM_Init(void){
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //除高级定时器都在APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//TIM2默认引脚
	//GPIO_Pin_4 pwm GPIO_Pin_2 gnd
	//GPIO_Pin_5 pwm GPIO_Pin_3 gnd
	//引脚初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM2时钟来源：内部时钟（72mhz）
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
	//时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//输出比较初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//赋默认值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 50; //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//启动TIM
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

//设置CCR
void PWM_SetCompare1(uint16_t Compare, TIM_TypeDef * TIMx){
	TIM_SetCompare1(TIMx, Compare);
}

//设置预分频
void PWM_SetPrescaler(uint16_t Prescaler, TIM_TypeDef * TIMx){
	TIM_PrescalerConfig(TIMx, Prescaler, TIM_PSCReloadMode_Immediate);
}
