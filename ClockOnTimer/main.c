#include "stm32f4xx.h"
#include "timers.h"

int main(void)
{
	
	
	GPIO_InitTypeDef GPIO_Struct_LED;
	RCC_ClocksTypeDef RCC_Clocks1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_Struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_Struct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct_LED.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Struct_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_Struct_LED);
	timer_ini();
	RCC_GetClocksFreq(&RCC_Clocks1);


	GPIO_Init(GPIOD, &GPIO_Struct_LED);
	
	while(1)
	{

	}
}