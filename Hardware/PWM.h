#ifndef __PWM_H__
#define __PWM_H__

	void PWM_Init(void);
	void PWM_SetCompare1(uint16_t Compare, TIM_TypeDef * TIMx);
	void PWM_SetPrescaler(uint16_t Prescaler, TIM_TypeDef * TIMx);
	
#endif

