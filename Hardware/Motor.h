#ifndef __Motor_H__
#define __Motor_H__


// #define black 1
// #define white 0

// #define ll  pb7()
// #define l   pb6()  
// #define m   pb6()  
// #define r   pb4() 
// #define rr  pb3()

// #define turn_left_left   (uint16_t)0
// #define turn_left        (uint16_t)1
// #define turn_straight    (uint16_t)2
// #define turn_right       (uint16_t)3
// #define turn_right_right (uint16_t)4

void Motor_SetSpeed(unsigned char Left_Speed, unsigned char Right_Speed);
void Motor_Init(void);
void SetRunMode(void);

#endif


