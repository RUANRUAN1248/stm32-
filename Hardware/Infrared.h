#ifndef _INFRARED_H_
#define _INFRARED_H_

#define black 1
#define white 0

#define ll  pb7()
#define l   pb6()  
#define m   pb6()  
#define r   pb4() 
#define rr  pb3()

#define turn_left_left   (uint16_t)0
#define turn_left        (uint16_t)1
#define turn_straight    (uint16_t)2
#define turn_right       (uint16_t)3
#define turn_right_right (uint16_t)4


unsigned char DecideRunMode(void);
void Infrared_Init(void);
#endif

