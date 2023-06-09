#include "stm32f10x.h"                  // Device header
#include "PreiphIncludeAll.h"
//所有的外设初始化函数
void PreiphAllInit(void){

	
//	KEY_Init();
	PWM_Init();
//	MyDMA_Init();
	AD_Init();
	TTS_Init();
//	Servo_Init();
//	Motor_Init();
	IC_Init();	
	OLED_Init();
	Encoder_Init();
	Serial_Init();
//	MyI2C_Init();
//	MPU6050_Init();
	MY_LED_Init();
	Infrared_Init();
}

