/*
 * Commands_from_Raspi_To_STM32.c
 *
 *  Created on: Dec 20, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "stdio.h"

extern int _write(int file, char *ptr, int len);

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

extern bool BAT_1_MANAGEMENT_FLAG;
extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG;
extern bool BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG;
extern bool BAT_1_MANAGEMENT_GENERAL_INFO_FLAG;
extern bool Bat1_Management_Shipment_testycycle_Autotestflag ; // Flag to start Bat1 shipment test cycle - Management Use Case
extern bool Bat1_Management_Shipment_chg_dischg_to_30_percent_flag ; // Flag to start Bat 1 Charge/Discharge to 30 % cycle

extern bool BAT_2_MANAGEMENT_FLAG;
extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG;
extern bool BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG;
extern bool BAT_2_MANAGEMENT_GENERAL_INFO_FLAG;
extern bool Bat2_Management_Shipment_testycycle_Autotestflag ; // Flag to start Bat1 shipment test cycle - Management Use Case
extern bool Bat2_Management_Shipment_chg_dischg_to_30_percent_flag ; // Flag to start Bat 1 Charge/Discharge to 30 % cycle


extern bool BAT_3_MANAGEMENT_FLAG;
extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG;
extern bool BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG;
extern bool BAT_3_MANAGEMENT_GENERAL_INFO_FLAG;
extern bool Bat3_Management_Shipment_testycycle_Autotestflag ; // Flag to start Bat1 shipment test cycle - Management Use Case
extern bool Bat3_Management_Shipment_chg_dischg_to_30_percent_flag ; // Flag to start Bat 1 Charge/Discharge to 30 % cycle





void commands_from_pi_to_stm()
{

	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T') // Command to turn on Bat 1 Maintenance Use case Autotest
	{

		if(BAT_1_MAINTENANCE_FLAG == true)
		{

			Autotestflag=true;
			update_maintenance_info_flag=true;
		}
		else
		{
			printf("Cannot start the Bat 1 Maintenance Use case Autotest \nTurn Bat1 Maintenance flag on first\n");
		}

	}


	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 1 General Info during Maintenance Use case autotest
	{
		if(BAT_1_MAINTENANCE_FLAG == true)
		{
			BAT_1_MAINT_GENERAL_INFO_FLAG=true;

		}
		else
		{
			printf("Cannot display Bat 1 Maintenance Use case General Info\n Turn Bat1 Maintenance flag on first\n");
		}
	}


	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T') // Command to enter the Bat 1 in Maintenance Use case
	{
		if(BAT_1_MANAGEMENT_FLAG==false )
		{
			BAT_1_MAINTENANCE_FLAG=true;

		}
		else
		{
			printf("Cannot start the Maintenance Use Case since Battery 1 currently is in Management Use case\n");
		}
	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')  // Command to turn on Bat 2 Maintenance Use case Autotest
	{
		if(BAT_2_MAINTENANCE_FLAG == true)
		{
			Bat2_Maint_Autotestflag=true;
			bat2_update_maintenance_info_flag=true;
		}
		else
		{
			printf("Cannot start Bat 2 Maintenance Use case Autotest\nTurn Bat2 Maintenance flag on first\n");
		}

	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 2 General Info during Maintenance Use case autotest
	{
		if(BAT_2_MAINTENANCE_FLAG == true)
		{
		BAT_2_MAINT_GENERAL_INFO_FLAG=true;
		}
		else
		{
			printf("Cannot display Bat 2 Maintenance Use case General Info\n Turn Bat2 Maintenance flag on first\n");
		}

	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T') // Command to enter bat 2 in maintenance use case
	{
		if(BAT_2_MANAGEMENT_FLAG==false)
		{
		BAT_2_MAINTENANCE_FLAG=true;
		}
		else
		{
			printf("Cannot start the Maintenance Use Case since Battery 2 currently is in Management Use case\n");
		}

	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='S' && rx_buffer[5]=='T'
			&& rx_buffer[6]=='R' && rx_buffer[7]=='M' && rx_buffer[8]=='A'
					&&rx_buffer[9]=='I' && rx_buffer[10]=='N' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T') // Command to turn on Bat 3 Maintenance Use case Autotest
	{
		if(BAT_3_MAINTENANCE_FLAG == true)
		{
		Bat3_Maint_Autotestflag=true;
		bat3_update_maintenance_info_flag=true;
		}
		else
		{
			printf("Cannot start Bat 3 Maintenance Use case Autotest\nTurn Bat3 Maintenance flag on first\n");
		}

	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='I' && rx_buffer[7]=='N' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 3 General Info during Maintenance Use case autotest
	{
		if(BAT_3_MAINTENANCE_FLAG == true)
		{
		BAT_3_MAINT_GENERAL_INFO_FLAG=true;
		}
		else
		{
			printf("Cannot display Bat 3 Maintenance Use case General Info\n Turn Bat3 Maintenance flag on first\n");
		}


	}

	else	if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='I'
							&& rx_buffer[12]=='N' && rx_buffer[13]=='T')  // Command to enter bat 3 in maintenance use case
	{
		if(BAT_3_MANAGEMENT_FLAG==false)
		{
		BAT_3_MAINTENANCE_FLAG=true;
		}

		else
		{
			printf("Cannot start the Maintenance Use Case since Battery 3 currently is in Management Use case\n");
		}

	}

	// Bat 1 Management Use case functions

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='G') // Command to Enter Bat 1 in Management Use case
	{
		if(BAT_1_MAINTENANCE_FLAG==false)
		{
			BAT_1_MANAGEMENT_FLAG=true;
		}
		else
		{
			printf("Cannot start the Management Use Case since Battery 1 currently is in Maintenance Use case\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='A' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 1 Management Use Case General Info
	{
		if(BAT_1_MANAGEMENT_FLAG==true)
		{
			BAT_1_MANAGEMENT_GENERAL_INFO_FLAG=true;
		}
		else
		{
			printf("Cannot display Bat 1 Management Use case General Info\n Turn Bat1 Management flag on first\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='B' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='L') // Command to start Bat 1 Management use case keep battery alive cycle
	{
		if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false && BAT_1_MANAGEMENT_FLAG==true)
		{
			BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG=true;
		}
		else
		{
			printf("Cannot start Bat 1 'Keep Battery Alive' cycle because\n");
			printf("Either the battery is in Shipment Cycle or it has not entered the Management Use Case yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='Y'
							&& rx_buffer[12]=='C' && rx_buffer[13]=='L') // Command to start Bat 1 Management use case shipment cycle
	{

		if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false && BAT_1_MANAGEMENT_FLAG==true)
		{
			BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG = true;
		}
		else
		{
			printf(" Cannot Enter the Bat 1 shipment cycle because\n");
			printf("Either the battery is in 'Keep Battery Alive' cycle or it has not entered the Management Use Case yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='D'
							&& rx_buffer[12]=='3' && rx_buffer[13]=='0')
	{
		if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat1_Management_Shipment_testycycle_Autotestflag==false)
		{
			Bat1_Management_Shipment_chg_dischg_to_30_percent_flag = true;
		}
		else
		{
			printf(" Cannot start Bat 1 'chg dschg to 30 ' cycle because");
			printf("Either the battery is in shipment autotest cycle or it hasn't entered the shipment cycle mode yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='1' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='A' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')
	{
		if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat1_Management_Shipment_chg_dischg_to_30_percent_flag==false)
		{
			Bat1_Management_Shipment_testycycle_Autotestflag=true;
		}
		else
		{
			printf(" Cannot start Bat 1 'Shipment auto test cycle' because");
			printf("Either the battery is in 'shipment chg/dschg to 30' cycle or it hasn't entered the shipment cycle mode yet\n ");
		}
	}  //1


	// Bat 2 Management Use case functions

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='G') // Command to Enter Bat 2 in Management Use case
	{
		if(BAT_2_MAINTENANCE_FLAG==false)
		{
			BAT_2_MANAGEMENT_FLAG=true;
		}
		else
		{
			printf("Cannot start the Management Use Case since Battery 2 currently is in Maintenance Use case\n");
		}

	} //1


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='A' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 2 Management Use Case General Info
	{
		if(BAT_2_MANAGEMENT_FLAG==true)
		{
			BAT_2_MANAGEMENT_GENERAL_INFO_FLAG=true;
		}
		else
		{
			printf("Cannot display Bat 2 Management Use case General Info\n Turn Bat2 Management flag on first\n");
		}

	} //1


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='B' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='L') // Command to start Bat 2 Management use case keep battery alive cycle
	{
		if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false && BAT_2_MANAGEMENT_FLAG==true)
		{
			BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG=true;
		}
		else
		{
			printf("Cannot start Bat 2 'Keep Battery Alive' cycle because\n");
			printf("Either the battery is in Shipment Cycle or it has not entered the Management Use Case yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='Y'
							&& rx_buffer[12]=='C' && rx_buffer[13]=='L') // Command to start Bat 2 Management use case shipment cycle
	{

		if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false && BAT_2_MANAGEMENT_FLAG==true)
		{
			BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG = true;
		}
		else
		{
			printf(" Cannot Enter Bat 2 in the shipment cycle because\n");
			printf("Either the battery is in 'Keep Battery Alive' cycle or it has not entered the Management Use Case yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='D'
							&& rx_buffer[12]=='3' && rx_buffer[13]=='0')  // Command to start bat 2 management use case -shipment- charge/discharge to 30 % cycle
	{
		if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat2_Management_Shipment_testycycle_Autotestflag==false)
		{
			Bat2_Management_Shipment_chg_dischg_to_30_percent_flag = true;
		}
		else
		{
			printf(" Cannot start Bat 2 'chg dschg to 30 ' cycle because");
			printf("Either the battery is in shipment autotest cycle or it hasn't entered the shipment cycle mode yet\n");
		}

	} //1

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='2' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='A' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')  // Command to start bat 2 management use case - Shipment autotest
	{
		if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat2_Management_Shipment_chg_dischg_to_30_percent_flag==false)
		{
			Bat2_Management_Shipment_testycycle_Autotestflag=true;
		}
		else
		{
			printf(" Cannot start Bat 2 'Shipment auto test cycle' because");
			printf("Either the battery is in 'shipment chg/dschg to 30' cycle or it hasn't entered the shipment cycle mode yet\n ");
		}
	} //1


	// Bat 3 Management Use case functions

	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='E' && rx_buffer[5]=='N'
			&& rx_buffer[6]=='T' && rx_buffer[7]=='E' && rx_buffer[8]=='R'
					&&rx_buffer[9]=='M' && rx_buffer[10]=='A' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='G') // Command to Enter Bat 3 in Management Use case
	{
		if(BAT_3_MAINTENANCE_FLAG==false)
		{
			BAT_3_MANAGEMENT_FLAG=true;
		}
		else
		{
			printf("Cannot start the Management Use Case since Battery 3 currently is in Maintenance Use case\n");
		}

	}


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='A' && rx_buffer[8]=='D'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='G' && rx_buffer[11]=='N'
							&& rx_buffer[12]=='I' && rx_buffer[13]=='F') // Command to display Bat 3 Management Use Case General Info
	{
		if(BAT_3_MANAGEMENT_FLAG==true)
		{
			BAT_3_MANAGEMENT_GENERAL_INFO_FLAG=true;
		}
		else
		{
			printf("Cannot display Bat 3 Management Use case General Info\n Turn Bat3 Management flag on first\n");
		}

	}


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='B' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='A' && rx_buffer[13]=='L') // Command to start Bat 3 Management use case keep battery alive cycle
	{
		if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG==false && BAT_3_MANAGEMENT_FLAG==true)
		{
			BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG=true;
		}
		else
		{
			printf("Cannot start Bat 3 'Keep Battery Alive' cycle because\n");
			printf("Either the battery is in Shipment Cycle or it has not entered the Management Use Case yet\n");
		}

	}


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='Y'
							&& rx_buffer[12]=='C' && rx_buffer[13]=='L') // Command to start Bat 3 Management use case shipment cycle
	{

		if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false && BAT_3_MANAGEMENT_FLAG==true)
		{
			BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG = true;
		}
		else
		{
			printf(" Cannot Enter Bat 3 in the shipment cycle because\n");
			printf("Either the battery is in 'Keep Battery Alive' cycle or it has not entered the Management Use Case yet\n");
		}

	}


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='C' && rx_buffer[11]=='D'
							&& rx_buffer[12]=='3' && rx_buffer[13]=='0')  // Command to start bat 3 management use case -shipment- charge/discharge to 30 % cycle
	{
		if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat3_Management_Shipment_testycycle_Autotestflag==false)
		{
			Bat3_Management_Shipment_chg_dischg_to_30_percent_flag = true;
		}
		else
		{
			printf(" Cannot start Bat 3 'chg dschg to 30 ' cycle because");
			printf("Either the battery is in shipment autotest cycle or it hasn't entered the shipment cycle mode yet\n");
		}

	}


	else if(rx_buffer[0]=='B' && rx_buffer[1]=='A' && rx_buffer[2]=='T'&& rx_buffer[3]=='3' && rx_buffer[4]=='M' && rx_buffer[5]=='A'
			&& rx_buffer[6]=='N' && rx_buffer[7]=='S' && rx_buffer[8]=='H'
					&&rx_buffer[9]=='P' && rx_buffer[10]=='A' && rx_buffer[11]=='T'
							&& rx_buffer[12]=='S' && rx_buffer[13]=='T')  // Command to start bat 3 management use case - Shipment autotest
	{
		if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true && Bat3_Management_Shipment_chg_dischg_to_30_percent_flag==false)
		{
			Bat3_Management_Shipment_testycycle_Autotestflag=true;
		}
		else
		{
			printf(" Cannot start Bat 3 'Shipment auto test cycle' because");
			printf("Either the battery is in 'shipment chg/dschg to 30' cycle or it hasn't entered the shipment cycle mode yet\n ");
		}
	}






}
