/*
 * Bat3_Management_Keep_Bat_Alive_cycle.c
 *
 *  Created on: Jan 10, 2022
 *      Author: shubham
 */







#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat3_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Bat3_Management_Keep_Bat_Alive_cycle.h"

extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

extern uint16_t BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle;

extern bool BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern I2C_HandleTypeDef hi2c3;

extern UART_HandleTypeDef huart2;

extern bool bat3charge ;				// Flag to start and stop charging of the battery
extern bool bat3discharge ;				// Flag to start and stop discharging of the battery


void Bat3_Management_Keep_Battery_Alive_Cycle()
{

	if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false)
	{

		if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG == true  )

		{
			if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == false)
			{
				BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = true;

				BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat3_asoc();

				if(BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle>80)
				{
					bat3charge = false;
					bat3discharge = true;
					gpio_func_bat3_chg_dschg();
				}

				if(BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle<80)
				{
					bat3charge = true;
					bat3discharge = false;
					gpio_func_bat3_chg_dschg();
				}


			}

			else if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == true)
			{
				BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat3_asoc();

				if(BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle == 80)
				{
					bat3charge = false;
					bat3discharge = false;
					gpio_func_bat3_chg_dschg();

					BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false;
					BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false;


				}
			}
		}
	}


}
