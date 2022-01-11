/*
 * Battery1_Management_Shipment_cyc_Discharge_to_30_percent.c
 *
 *  Created on: Jan 4, 2022
 *      Author: shubham
 */

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat1_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Battery1_Management_Shipment_cyc_Discharge_to_30_percent.h"


extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once



extern bool BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern bool Bat1_Management_Shipment_chg_dischg_to_30_percent_flag;
extern bool Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag ;

extern bool Bat1_Management_Shipment_testycycle_Autotestflag;

extern uint16_t BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; //


extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart2;

extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery




void Bat1_Management_Shipment_Cycle_Charge_Discharge_to_30()
{

	if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{

		if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat1_Management_Shipment_testycycle_Autotestflag == false)
			{
				if(Bat1_Management_Shipment_chg_dischg_to_30_percent_flag == true)
				{
					if(Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag == false)
					{
						Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag = true;

						BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat1_asoc();

						if(BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 > 78)
						{
							bat1charge = false;
							bat1discharge = true;
							gpio_func();
						}

						if(BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 < 78)
						{
							bat1charge = true;
							bat1discharge = false;
							gpio_func();
						}


					}



					else if(Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag == true)
					{

						BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat1_asoc();

						if(BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 == 78)
						{
							bat1charge = false;
							bat1discharge = false;
							gpio_func();

							Bat1_Management_Shipment_chg_dischg_to_30_percent_flag = false;
							Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false;

							BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

						}




					}


				}

			}

		}
	}






}
