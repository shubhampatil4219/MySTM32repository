/*
 * Bat2_Management_Keep_Bat_Alive_cycle.c
 *
 *  Created on: Jan 9, 2022
 *      Author: shubham
 */




#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat2_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Bat2_Management_Keep_Bat_Alive_cycle.h"

extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

extern uint16_t BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle;

extern bool BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern I2C_HandleTypeDef hi2c2;

extern UART_HandleTypeDef huart2;

extern bool bat2charge ;				// Flag to start and stop charging of the battery
extern bool bat2discharge ;				// Flag to start and stop discharging of the battery


void Bat2_Management_Keep_Battery_Alive_Cycle()
{

	if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false)
	{

		if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG == true  )

		{
			if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == false)
			{
				BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = true;

				BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat2_asoc();

				if(BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle>80)
				{
					bat2charge = false;
					bat2discharge = true;
					gpio_func_bat2_chg_dschg();
				}

				if(BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle<80)
				{
					bat2charge = true;
					bat2discharge = false;
					gpio_func_bat2_chg_dschg();
				}


			}

			else if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG == true)
			{
				BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle = read_bat2_asoc();

				if(BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle == 80)
				{
					bat2charge = false;
					bat2discharge = false;
					gpio_func_bat2_chg_dschg();

					BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false;
					BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false;


				}
			}
		}
	}


}
