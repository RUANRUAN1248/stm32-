#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Infrared.h"
#include "Serial.h"
#include "Delay.h"


#define highhigh 100
#define high 60
#define mid 0
//#define low -50
//#define lowlow 80


#define turn_left_left   (uint16_t)0
#define turn_left        (uint16_t)1
#define turn_straight    (uint16_t)2
#define turn_right       (uint16_t)3
#define turn_right_right (uint16_t)4

//pwm1: GPIOA_Pin_0
//pwm2: GPIOA_Pin_6
uint16_t preMode = turn_straight;
uint16_t nowMode = turn_straight;

void Motor_Init(void){
	PWM_Init(); 
}
//橙PG8 黄PG6
void Motor_SetDireLeft(uint16_t preMode, uint16_t nowMode, uint16_t pinLeft, uint16_t pinRight){
	if(preMode != nowMode){
		GPIO_WriteBit(GPIOG, pinLeft, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOG, pinLeft)));
		GPIO_WriteBit(GPIOG, pinRight, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOG, pinRight)));
	}
	
}

//绿PG4 PG2
void Motor_SetDireRight(uint16_t preMode, uint16_t nowMode, uint16_t pinLeft, uint16_t pinRight){
	if(preMode != nowMode){
		GPIO_WriteBit(GPIOG, pinLeft, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOG, pinLeft)));
		GPIO_WriteBit(GPIOG, pinRight, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOG, pinRight)));
	}
	
}

void Motor_SetSpeed(int8_t Left_Speed, int8_t Right_Speed)
{
	PWM_SetCompare1(Left_Speed, TIM3);
	PWM_SetCompare1(Right_Speed, TIM2);
}

// Motor_SetDireLeft(GPIO_Pin_8, GPIO_Pin_6);
// Motor_SetDireRight(GPIO_Pin_4, GPIO_Pin_2);

void SetRunMode(){
    nowMode = DecideRunMode();
    if(nowMode == turn_left_left){
		Motor_SetDireLeft(preMode, nowMode, GPIO_Pin_8, GPIO_Pin_6);
		Motor_SetSpeed(high, high);
     Serial_SendString("left_left\r\n");
		Delay_ms(20);
    } else if(nowMode == turn_right_right){
		Motor_SetDireRight(preMode, nowMode, GPIO_Pin_4, GPIO_Pin_2);
		Motor_SetSpeed(high, high);
      	Serial_SendString("right_right\r\n");
		Delay_ms(200);
    } else if(nowMode == turn_left){
		Motor_SetSpeed(mid, highhigh);
      	Serial_SendString("left\r\n");
		Delay_ms(100);
    } else if(nowMode == turn_right){
		Motor_SetSpeed(highhigh, mid);
      	Serial_SendString("right\r\n");
		Delay_ms(100);
    } else {
		Motor_SetSpeed(highhigh, highhigh);
      	Serial_SendString("straight\r\n");
		Delay_ms(10);
    }
	preMode = nowMode;
}


