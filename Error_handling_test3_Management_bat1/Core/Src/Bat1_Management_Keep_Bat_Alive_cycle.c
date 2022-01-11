/*
 * Bat1_Management_Keep_Bat_Alive_cycle.c
 *
 *  Created on: Jan 4, 2022
 *      Author: shubham
 */

#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat1_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Bat1_Management_Keep_Bat_Alive_cycle.h"

extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

extern uint16_t BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle;

extern bool BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart2;

extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery


void Bat1_Management_Keep_Battery_Alive_Cycle()
{

	if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false)
	{

		if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG == true  )

		{
			if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == false)
			{
				BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = true;

				BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat1_asoc();

				if(BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle>80)
				{
					bat1charge = false;
					bat1discharge = true;
					gpio_func();
				}

				if(BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle<80)
				{
					bat1charge = true;
					bat1discharge = false;
					gpio_func();
				}


			}

			else if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == true)
			{
				BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat1_asoc();

				if(BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle == 80)
				{
					bat1charge = false;
					bat1discharge = false;
					gpio_func();

					BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false;
					BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false;


				}
			}
		}
	}


}
