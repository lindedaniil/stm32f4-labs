#include "stm32f4xx.h"
#include "Lab3_Test.h"

uint32_t i;

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

int main(void)
{
	GPIO_InitTypeDef GPIO_struct_Button;
	uint8_t button_pressed = 0;
	uint8_t click_counter = 0;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_struct_Button.GPIO_Mode =  GPIO_Mode_IN;
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed ;
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_struct_Button);
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	
    GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;
	
	while(1)
	{	
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			for(i = 0; i < 10000; i++) {}
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1 && button_pressed == 0)
			{   
				nextLed(click_counter);
				if(click_counter < 7)
				{
					++click_counter;			
				}
				else
				{
					click_counter = 0;
				}
				button_pressed = 1;
				for(i = 0; i < 10000; i++) {}
			}
		}	
		else
		{
			button_pressed = 0;
			for(i = 0; i < 10000; i++) {}
		}
	}
}
