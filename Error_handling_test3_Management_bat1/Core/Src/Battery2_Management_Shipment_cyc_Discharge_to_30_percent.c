/*
 * Battery2_Management_Shipment_cyc_Discharge_to_30_percent.c
 *
 *  Created on: Jan 9, 2022
 *      Author: shubham
 */




#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat2_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Battery2_Management_Shipment_cyc_Discharge_to_30_percent.h"


extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once



extern bool BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern bool Bat2_Management_Shipment_chg_dischg_to_30_percent_flag;
extern bool Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag ;

extern bool Bat2_Management_Shipment_testycycle_Autotestflag;

extern uint16_t BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; //


extern I2C_HandleTypeDef hi2c2;

extern UART_HandleTypeDef huart2;

extern bool bat2charge ;				// Flag to start and stop charging of the battery
extern bool bat2discharge ;				// Flag to start and stop discharging of the battery




void Bat2_Management_Shipment_Cycle_Charge_Discharge_to_30()
{

	if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{

		if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat2_Management_Shipment_testycycle_Autotestflag == false)
			{
				if(Bat2_Management_Shipment_chg_dischg_to_30_percent_flag == true)
				{
					if(Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag == false)
					{
						Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag = true;

						BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat2_asoc();

						if(BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 > 78)
						{
							bat2charge = false;
							bat2discharge = true;
							gpio_func_bat2_chg_dschg();
						}

						if(BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 < 78)
						{
							bat2charge = true;
							bat2discharge = false;
							gpio_func_bat2_chg_dschg();
						}


					}



					else if(Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag == true)
					{

						BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat2_asoc();

						if(BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 == 78)
						{
							bat2charge = false;
							bat2discharge = false;
							gpio_func_bat2_chg_dschg();

							Bat2_Management_Shipment_chg_dischg_to_30_percent_flag = false;
							Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false;

							BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

						}




					}


				}

			}

		}
	}






}
