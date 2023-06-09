#include "stm32f10x.h"                  // Device header

//输入捕获
void IC_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//TIM3CH1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//TIM3时钟来源 内部时钟（72mhz）
	TIM_InternalClockConfig(TIM3);
	
	//时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);


	//输入捕获初始化
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xf;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//TIM_ICInit(TIM3 ,&TIM_ICInitStructure);
	
	//快捷配置 配置一个另一个自动配置 可替代 TIM_ICInit()
	TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);//输入捕获双通道交叉相反参数配置
	
	//配置输入信号源
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	
	//选择从模式位自动CCR清零
 	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	//开
	TIM_Cmd(TIM3, ENABLE);

}

uint32_t IC_GetFreg(void){
	return 1000000 / TIM_GetCapture1(TIM3);
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}


