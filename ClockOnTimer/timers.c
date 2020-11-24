#include "stm32f4xx.h"
#include "timers.h"
#include "clock.h"

struct clock clock1;
struct clock alarm;

void  TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		clock1.seconds++;
		
		if(clock1.seconds == 60)
		{
			clock1.minutes++;
			clock1.seconds = 0;
		}
		
		if(clock1.minutes == 60)
		{
			clock1.hours++;
			clock1.minutes = 0;
		}
		
		if(clock1.hours == 24)
		{
			clock1.hours = 0;
		}
		
		if(clock1.hours == alarm.hours && clock1.minutes == alarm.minutes && clock1.seconds == alarm.seconds)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
		}
		
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
	}
}

void timer_ini(void)
{
	TIM_TimeBaseInitTypeDef timers_struct;
	NVIC_InitTypeDef NVIC_struct;
	clock1.seconds = 0;
	clock1.minutes = 0;
	clock1.hours = 12;
	alarm.seconds = 15;
	alarm.minutes = 0;
	alarm.hours = 12;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	timers_struct.TIM_Prescaler = 20000 - 1;
	timers_struct.TIM_CounterMode = TIM_CounterMode_Up;
	timers_struct.TIM_Period = 1000;
	timers_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	timers_struct.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2, &timers_struct);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_struct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_struct);
	
	TIM_Cmd(TIM2, ENABLE);
	
}