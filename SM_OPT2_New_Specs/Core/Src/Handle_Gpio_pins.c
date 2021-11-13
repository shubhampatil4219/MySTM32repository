/*
 * Handle_Gpio_pins.c
 *
 *  Created on: Oct 29, 2021
 *      Author: shubham
 */

#include "stm32f7xx_hal.h"
#include "stdbool.h"
//#include "Variable_defintions.h"

extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery



void gpio_func()

{
	if(bat1charge==true)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}

	if(bat1charge==false)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	}

	if(bat1discharge==true)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}

	if(bat1discharge==false)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}



}
