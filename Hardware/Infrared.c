#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#define PA3() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) //zz
#define PA1() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) //z
#define PC3() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) //zhong
#define PC1() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)  //y
#define PF10() GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10) //yy

#define black 1
#define white 0


#define turn_left_left   (uint16_t)0
#define turn_left        (uint16_t)1
#define turn_straight    (uint16_t)2
#define turn_right       (uint16_t)3
#define turn_right_right (uint16_t)4

void Infrared_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF, ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

}

unsigned char DecideRunMode(void){
    // if (PB12() == white && PB13() == black && PB14() == black){
    //     return turn_right_right;
    // } else if (PB10() == black && PB11() == black && PB12() == white){
    //     return turn_left_left;
    // } else if (PB11() == white && PB12() == black && PB13() == black){
    //     return turn_right;
    // } else if (PB11() == black && PB12() == black && PB13() == white){
    //     return turn_left;
    // } else if (PB11() == white && PB12() == black && PB13() == white){
    //     return turn_straight;
    // } 
	// 	return -1;
//	#define PA3() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) //zz
//#define PA1() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) //z
//#define PC3() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) //zhong
//#define PC1() GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)  //y
//#define PF10() GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10) //yy
    if(PA3() == 1){
        return turn_left_left;
    } else if(PF10() == 1){
        return turn_right_right;
    } else if(PA1() == 1){
        return turn_left;
    } else if(PC1() == 1){
        return turn_right;
    } else if(PC3() == 1){
        return turn_straight;
    } else {
	    return turn_straight;
	}
}


