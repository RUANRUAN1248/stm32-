#include "stm32f10x.h"
#include "PreiphIncludeAll.h"
#include "Delay.h"

#define PA3() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)	 // zz
#define PA1() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)	 // z
#define PC3() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)	 // zhong
#define PC1() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)	 // y
#define PF10() GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10) // yy

#define highhigh 80

#define mid 0

// a15 = in1 pc11 = in2 pd0 = in3 Pd2 = in4
// PA3() 红外
// PA1()
// PC3()
// PC1()
// F10()
// PA0 pwm
// pA6 pwm
// B8 OLED
// B9 OLED
// A9 uart
// A10 uart
int main()
{
	// 橙黄绿蓝
	//uint16_t data = 0;
	Serial_Init();
//	Timer_Init();
//	MY_GPIO_Init();
//	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
//	Delay_ms(500);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
//	Delay_us(50);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
	

	// GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_RESET);

	// turn_left_left   (uint16_t)0
	// #define turn_left        (uint16_t)1
	// #define turn_straight    (uint16_t)2
	// #define turn_right       (uint16_t)3
	// #define turn_right_right (uint16_t)4

	// GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_SET);
	while (1)
	{
		Serial_SendByte('A');
		Delay_ms(10);
		// Motor_SetDireLeft(highhigh, highhigh, GPIO_Pin_8, GPIO_Pin_6);
		// SetRunMode();
		//	 Delay_ms(100);
		// Motor_SetSpeed(highhigh, highhigh);
		// Motor_SetSpeed(lowlow, highhigh);

		// Motor_SetSpeed(highhigh, lowlow);

		// Motor_SetSpeed(mid, highhigh);

		// Motor_SetSpeed(highhigh, mid);

		// Motor_SetSpeed(highhigh, highhigh);

		// Motor_SetSpeed(highhigh, highhigh);

		//   Delay_ms(10);
		//  OLED_ShowNum(1, 1, PA3(), 1);
		//  OLED_ShowNum(1, 3, PA1(), 1);
		//  OLED_ShowNum(1, 5, PC3(), 1);
		//  OLED_ShowNum(1, 7, PC1(), 1);
		//  OLED_ShowNum(1, 9, PF10(), 1);

		// while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 1)
		// {
		// 	TIM_Cmd(TIM2, ENABLE);
		// 	while (0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
		// 	{
		// 		data = TIM_GetCounter(TIM2);
		// 		TIM_Cmd(TIM2, DISABLE);
		// 		Serial_SendByte(data);
		// 	}
			
		// }
	}
}
