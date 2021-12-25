/*
 * Timer_function.c
 *
 *  Created on: 22-Oct-2021
 *      Author: shubham
 */

#include "Timer_function.h"
#include "stm32f7xx_hal.h"
#include "stdbool.h"
//#include "Variable_defintions.h"

extern bool _bat1timerfunc ;	// Flag to start and stop the wait time
extern uint16_t _bat1_counter_var;	//   Variable as a counter
extern bool _bat1_15min_wait_over;

extern bool _bat2timerfunc ;	// Flag to start and stop the wait time
extern uint16_t _bat2_counter_var;	//   Variable as a counter
extern bool _bat2_15min_wait_over;

extern bool _bat3timerfunc ;	// Flag to start and stop the wait time
extern uint16_t _bat3_counter_var;	//   Variable as a counter
extern bool _bat3_15min_wait_over;


void Timer_15min()
{
	if(_bat1timerfunc==true)
	{
		_bat1_counter_var++;
		if(_bat1_counter_var==6000)
		{
			_bat1_15min_wait_over = true;
		}
	}


	if(_bat2timerfunc==true)
	{
		_bat2_counter_var++;
		if(_bat2_counter_var==6000)
		{
			_bat2_15min_wait_over = true;
		}
	}

	if(_bat3timerfunc==true)
		{
			_bat3_counter_var++;
			if(_bat3_counter_var==6000)
			{
				_bat3_15min_wait_over = true;
			}
		}





}
