/*
 * timer_delay.c
 *
 *  Created on: Nov 11, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "timer_delay.h"

extern TIM_HandleTypeDef htim4;


void usdelay (uint32_t us)
{
	__HAL_TIM_SET_COUNTER(&htim4,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim4) < us);  // wait for the counter to reach the us input in the parameter
}

void msdelay(uint32_t ms)
{
	for(uint32_t i=0;i<ms;i++)
	{
		usdelay(1000);                  // 1ms delay
	}
}
