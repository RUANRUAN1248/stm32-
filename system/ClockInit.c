#include "stm32f10x.h"
#include "ClockInit.h" 
void SystemClock(uint16_t PLL_Pin){
	RCC->CR |= 0x01 << 16;
	while(!(RCC->CR & (1 << 17)));
	RCC->CFGR |= (0x04 << 8);
	RCC->CFGR |= ((PLL_Pin - 2) << 18);
	FLASH->ACR |= 2;
	RCC->CFGR |= 1 << 16;
	RCC->CR |= (0x01 << 24);
	while(!(RCC->CR & (0x01 << 25)));
	RCC->CFGR |= 2;
	while(!((RCC->CFGR & 0x03 << 2) == 0x08));

}
