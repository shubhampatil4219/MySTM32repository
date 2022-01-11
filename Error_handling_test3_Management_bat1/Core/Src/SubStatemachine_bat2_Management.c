/*
 * SubStatemachine_bat2_Management.c
 *
 *  Created on: Jan 9, 2022
 *      Author: shubham
 */




#include "stdbool.h"
#include "SubStatemachine_bat2_Management.h"
#include "stm32f7xx_hal.h"
#include "Battery2_Management_General_Info.h"
#include "Bat2_Update_Info_during_Management.h"
#include "Specific_parameters_management_BAT2.h"
#include "Bat2_Management_Keep_Bat_Alive_cycle.h"
#include "Battery2_Management_Shipment_cyc_Test_Cycle.h"
#include "Battery2_Management_Shipment_cyc_Discharge_to_30_percent.h"

extern bool BAT_2_MANAGEMENT_FLAG ;  // Flag to enter Bat 1 in Management Use Case

extern bool BAT_2_MANAGEMENT_ENTERED_GUARD_FLAG; // Flag to send instruction only once to Pi that Bat 1
												  // has entered Management Use Case

extern bool BAT_2_MANAGEMENT_GENERAL_INFO_FLAG ; // Flag to

extern bool BAT_2_MANAGEMENT_GENERAL_INFO_GUARD_FLAG;    // Flag to display General Info only once


extern I2C_HandleTypeDef hi2c2;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;

void substatemachine_battery2_management()
{

	if(BAT_2_MANAGEMENT_FLAG==true)
	{
		if(BAT_2_MANAGEMENT_ENTERED_GUARD_FLAG == false)
		{
			BAT_2_MANAGEMENT_ENTERED_GUARD_FLAG = true;
			// Add command to inform Pi that Battery 1 has entered management use case
			// Executed only once
		}


		if(BAT_2_MANAGEMENT_GENERAL_INFO_FLAG == true)
		{

			if(BAT_2_MANAGEMENT_GENERAL_INFO_GUARD_FLAG==false)
			{
				BAT_2_MANAGEMENT_GENERAL_INFO_GUARD_FLAG = true;

				//printf("Displayed General Info once \n");

				Transmit_Bat2_Management_General_Info_to_Raspi(); // This function is working now
				Send_Bat2_Management_Specific_Info_To_Pi();



			}
			else if(BAT_2_MANAGEMENT_GENERAL_INFO_GUARD_FLAG == true)
			{

			   // Update general info periodically // this function works
//				if(update_maintenance_info_flag==true)
//				{

						 update_voltage_during_management_bat2();
						 update_asoc_during_management_bat2();
						 update_RemCap_during_management_bat2();
						 update_cyclecount_during_management_bat2();
						 update_batstatus_during_management_bat2();
						 update_temperature_during_management_bat2();
						 update_current_during_management_bat2();
//				}

			}
		}

		Bat2_Management_Keep_Battery_Alive_Cycle();

		Battery2_Management_Use_Case_Shipment_Test_Cycle();
		Bat2_Management_Shipment_Cycle_Charge_Discharge_to_30();


	}


}
