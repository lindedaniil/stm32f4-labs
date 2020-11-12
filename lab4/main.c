#include "stm32f4xx.h"
#include "Lab4_Test.h"

uint32_t periods[8] = {4900, 1000, 3400, 4300, 3500, 3400, 900, 2300};
uint32_t timeCounter;
uint8_t ledCounter;

void nextLed(uint8_t new_led)
{
	switch(new_led)
	{
		case 0:
			GPIOD->ODR = 0x4000; //Red
			break;
		case 1:
			GPIOD->ODR = 0x1000; //Green
			break;
		case 2:
			GPIOD->ODR = 0x8000; //Blue
			break;
		case 3:
			GPIOD->ODR = 0x4000; //Red
			break;
		case 4:
			GPIOD->ODR = 0x1000; //Green
			break;
		case 5:
			GPIOD->ODR = 0x4000; //Red
			break;
		case 6:
			GPIOD->ODR = 0x2000; //Yellow
			break;
		case 7:
			GPIOD->ODR = 0x8000; //Blue
			break;
	}
}

void SysTick_Handler(void)
{
	if(timeCounter == 0)
	{
		if(ledCounter < 7)
		{
			++ledCounter;
		}
		else
		{
			ledCounter = 0;
		}
		nextLed(ledCounter);
		timeCounter = periods[ledCounter];
	}
	else
	{
		--timeCounter;
	}
}

//R -> G -> B -> R -> G -> R -> Y -> B
//4,9 –> 1,0 –> 3,4 –> 4,3 –> 3,5 –> 3,4 –> 0,9 –> 2,3

int main(void)
{
	ledCounter = 0;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	
    GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;
	nextLed(ledCounter);
	
	timeCounter = periods[ledCounter];
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock /1000);//1ms
	
	while(1)
	{
	
	}
}
