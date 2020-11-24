#include "stm32f4xx.h"

uint32_t i;



int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	
	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;
	
	while(1)
	{
		//R -> G -> B -> R -> G -> R -> Y -> B
		GPIOD->ODR = 0x4000; //Red
		for(i = 0; i < 1000000; i++){}
		GPIOD->ODR = 0x1000; //Green
		for(i = 0; i < 1000000; i++){}	
		GPIOD->ODR = 0x8000; //Blue
		for(i = 0; i < 1000000; i++){}
		GPIOD->ODR = 0x4000; //Red
		for(i = 0; i < 1000000; i++){}
		GPIOD->ODR = 0x1000; //Green
		for(i = 0; i < 1000000; i++){}
		GPIOD->ODR = 0x4000; //Red
		for(i = 0; i < 1000000; i++){}
		GPIOD->ODR = 0x2000; //Yellow
		for(i = 0; i < 1000000; i++){}	
		GPIOD->ODR = 0x8000; //Blue
		for(i = 0; i < 1000000; i++){}
	
	}
}

