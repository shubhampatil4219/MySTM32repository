/*
 * Battery3_Management_Shipment_cyc_Discharge_to_30_percent.c
 *
 *  Created on: Jan 11, 2022
 *      Author: shubham
 */







#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "bat3_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Battery3_Management_Shipment_cyc_Discharge_to_30_percent.h"


extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ; // Flag to start Keep Battery Alive cycle

extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG ; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once



extern bool BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;

extern bool Bat3_Management_Shipment_chg_dischg_to_30_percent_flag;
extern bool Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag ;

extern bool Bat3_Management_Shipment_testycycle_Autotestflag;

extern uint16_t BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; //


extern I2C_HandleTypeDef hi2c3;

extern UART_HandleTypeDef huart2;

extern bool bat3charge ;				// Flag to start and stop charging of the battery
extern bool bat3discharge ;				// Flag to start and stop discharging of the battery




void Bat3_Management_Shipment_Cycle_Charge_Discharge_to_30()
{

	if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{

		if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat3_Management_Shipment_testycycle_Autotestflag == false)
			{
				if(Bat3_Management_Shipment_chg_dischg_to_30_percent_flag == true)
				{
					if(Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag == false)
					{
						Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag = true;

						BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat3_asoc();

						if(BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 > 78)
						{
							bat3charge = false;
							bat3discharge = true;
							gpio_func_bat3_chg_dschg();
						}

						if(BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 < 78)
						{
							bat3charge = true;
							bat3discharge = false;
							gpio_func_bat3_chg_dschg();
						}


					}



					else if(Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag == true)
					{

						BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 = read_bat3_asoc();

						if(BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30 == 78)
						{
							bat3charge = false;
							bat3discharge = false;
							gpio_func_bat3_chg_dschg();

							Bat3_Management_Shipment_chg_dischg_to_30_percent_flag = false;
							Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false;

							BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

						}




					}


				}

			}

		}
	}






}
