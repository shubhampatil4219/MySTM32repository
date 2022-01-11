/*
 * SubStatemachine_bat3_Management.c
 *
 *  Created on: Jan 11, 2022
 *      Author: shubham
 */







#include "stdbool.h"
#include "SubStatemachine_bat3_Management.h"
#include "stm32f7xx_hal.h"
#include "Battery3_Management_General_Info.h"
#include "Bat3_Update_Info_during_Management.h"
#include "Specific_parameters_management_BAT3.h"
#include "Bat3_Management_Keep_Bat_Alive_cycle.h"
#include "Battery3_Management_Shipment_cyc_Test_Cycle.h"
#include "Battery3_Management_Shipment_cyc_Discharge_to_30_percent.h"

extern bool BAT_3_MANAGEMENT_FLAG ;  // Flag to enter Bat 3 in Management Use Case

extern bool BAT_3_MANAGEMENT_ENTERED_GUARD_FLAG; // Flag to send instruction only once to Pi that Bat 3
												  // has entered Management Use Case

extern bool BAT_3_MANAGEMENT_GENERAL_INFO_FLAG ; // Flag to

extern bool BAT_3_MANAGEMENT_GENERAL_INFO_GUARD_FLAG;    // Flag to display General Info only once


extern I2C_HandleTypeDef hi2c3;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;

void substatemachine_battery3_management()
{

	if(BAT_3_MANAGEMENT_FLAG==true)
	{
		if(BAT_3_MANAGEMENT_ENTERED_GUARD_FLAG == false)
		{
			BAT_3_MANAGEMENT_ENTERED_GUARD_FLAG = true;
			// Add command to inform Pi that Battery 3 has entered management use case
			// Executed only once
		}


		if(BAT_3_MANAGEMENT_GENERAL_INFO_FLAG == true)
		{

			if(BAT_3_MANAGEMENT_GENERAL_INFO_GUARD_FLAG==false)
			{
				BAT_3_MANAGEMENT_GENERAL_INFO_GUARD_FLAG = true;

				//printf("Displayed General Info once \n");

				Transmit_Bat3_Management_General_Info_to_Raspi(); // This function is working now
				Send_Bat3_Management_Specific_Info_To_Pi();



			}
			else if(BAT_3_MANAGEMENT_GENERAL_INFO_GUARD_FLAG == true)
			{

			   // Update general info periodically // this function works
//				if(update_maintenance_info_flag==true)
//				{

						 update_voltage_during_management_bat3();
						 update_asoc_during_management_bat3();
						 update_RemCap_during_management_bat3();
						 update_cyclecount_during_management_bat3();
						 update_batstatus_during_management_bat3();
						 update_temperature_during_management_bat3();
						 update_current_during_management_bat3();
//				}

			}
		}

		Bat3_Management_Keep_Battery_Alive_Cycle();

		Battery3_Management_Use_Case_Shipment_Test_Cycle();
		Bat3_Management_Shipment_Cycle_Charge_Discharge_to_30();


	}


}
