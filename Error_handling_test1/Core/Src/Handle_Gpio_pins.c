/*
 * Handle_Gpio_pins.c
 *
 *  Created on: Oct 29, 2021
 *      Author: shubham
 */

#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "Handle_Gpio_pins.h"
//#include "Variable_defintions.h"

extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery

extern bool bat2charge ;				// Flag to start and stop charging of the battery
extern bool bat2discharge ;				// Flag to start and stop discharging of the battery

extern bool bat3charge ;				// Flag to start and stop charging of the battery
extern bool bat3discharge ;				// Flag to start and stop discharging of the battery

void gpio_func()

{
	if(bat1charge==true)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //PB12 charge, PB13 discharge
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

void gpio_func_bat2_chg_dschg()
{

	if(bat2charge==true)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);  // PC5 charge // PC6 Discharge
	}

	if(bat2charge==false)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	}

	if(bat2discharge==true)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	}

	if(bat2discharge==false)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}


}

void gpio_func_bat3_chg_dschg()
{
	if(bat3charge==true)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);  // PD8 charge // PA12 Discharge
	}

	if(bat3charge==false)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
	}

	if(bat3discharge==true)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	}

	if(bat3discharge==false)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	}

}
