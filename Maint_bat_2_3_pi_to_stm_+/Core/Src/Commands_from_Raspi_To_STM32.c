/*
 * Commands_from_Raspi_To_STM32.c
 *
 *  Created on: Dec 20, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"


extern uint8_t rx_buffer[14];

extern bool Autotestflag;
extern bool update_maintenance_info_flag;
extern bool BAT_1_MAINT_GENERAL_INFO_FLAG;
extern bool BAT_1_MAINTENANCE_FLAG;

extern bool Bat2_Maint_Autotestflag;
extern bool bat2_update_maintenance_info_flag;
extern bool BAT_2_MAINT_GENERAL_INFO_FLAG;
extern bool BAT_2_MAINTENANCE_FLAG;

extern bool Bat3_Maint_Autotestflag;
extern bool bat3_update_maintenance_info_flag;
extern bool BAT_3_MAINT_GENERAL_INFO_FLAG;
extern bool BAT_3_MAINTENANCE_FLAG;


void commands_from_pi_to_stm()
{

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')
	{
		Autotestflag=true;
		update_maintenance_info_flag=true;

	}


	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F')
	{
		BAT_1_MAINT_GENERAL_INFO_FLAG=true;

	}


	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T')
	{
		BAT_1_MAINTENANCE_FLAG=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')
	{
		Bat2_Maint_Autotestflag=true;
		bat2_update_maintenance_info_flag=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F')
	{
		BAT_2_MAINT_GENERAL_INFO_FLAG=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T')
	{
		BAT_2_MAINTENANCE_FLAG=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')
	{
		Bat3_Maint_Autotestflag=true;
		bat3_update_maintenance_info_flag=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F')
	{
		BAT_3_MAINT_GENERAL_INFO_FLAG=true;

	}

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T')
	{
		BAT_3_MAINTENANCE_FLAG=true;

	}




}
