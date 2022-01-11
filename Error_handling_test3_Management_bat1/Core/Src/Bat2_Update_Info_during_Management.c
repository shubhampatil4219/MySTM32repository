/*
 * Bat2_Update_Info_during_Management.c
 *
 *  Created on: Jan 9, 2022
 *      Author: shubham
 */




#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "string.h"
#include "Bat2_Update_Info_during_Management.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c2;

extern bool bat2_geninfo_voltage_flag;
extern bool bat2_geninfo_asoc_flag;
extern bool bat2_geninfo_remainingcapacity_flag;
extern bool bat2_geninfo_cycle_flag;
extern bool bat2_geninfo_batterystatus_flag;
extern bool bat2_geninfo_temperature_flag ;
extern bool bat2_geninfo_current_flag;


extern uint16_t bat2_geninfo_cycle_counter ;
extern uint16_t bat2_geninfo_asoc_counter ;
extern uint16_t bat2_geninfo_remainingcapacity_counter ;
extern uint16_t bat2_geninfo_voltage_counter ;
extern uint16_t bat2_geninfo_temperature_counter ;
extern uint16_t bat2_geninfo_batterystatus_counter ;
extern uint16_t bat2_geninfo_current_counter;

uint8_t transmit_info_to_be_updated_during_bat2_management[16];


void update_voltage_during_management_bat2()
{


	if(bat2_geninfo_voltage_flag==true)
	{
		bat2_geninfo_voltage_flag = false;

		uint8_t rx_geninfo_voltage[2]={0x00};
		uint8_t tx_voltage[1]={0x09};                       // Voltage
		HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_voltage, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_geninfo_voltage, 2);
		HAL_Delay(5);
		uint16_t Bat1_Volt_Maint_GI = rx_geninfo_voltage[1];
		Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI << 8;
		Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI + rx_geninfo_voltage[0];


////		uint8_t send_update_voltage[14]={'1','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
//


		transmit_info_to_be_updated_during_bat2_management[0]='s';
		transmit_info_to_be_updated_during_bat2_management[1]='2';
		transmit_info_to_be_updated_during_bat2_management[2]='N';
		transmit_info_to_be_updated_during_bat2_management[3]='U';
		transmit_info_to_be_updated_during_bat2_management[4]='P';
		transmit_info_to_be_updated_during_bat2_management[5]='V';
		transmit_info_to_be_updated_during_bat2_management[6]='T';
		transmit_info_to_be_updated_during_bat2_management[7]='S';
		transmit_info_to_be_updated_during_bat2_management[8]=rx_geninfo_voltage[1];
		transmit_info_to_be_updated_during_bat2_management[9]=rx_geninfo_voltage[0];
		transmit_info_to_be_updated_during_bat2_management[10]='V';
		transmit_info_to_be_updated_during_bat2_management[11]='T';
		transmit_info_to_be_updated_during_bat2_management[12]='U';
		transmit_info_to_be_updated_during_bat2_management[13]='P';
		transmit_info_to_be_updated_during_bat2_management[14]='E';
		transmit_info_to_be_updated_during_bat2_management[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}


void update_asoc_during_management_bat2()
{

if(bat2_geninfo_asoc_flag==true)
{

	bat2_geninfo_asoc_flag = false;

	uint8_t rx_geninfo_asoc[1]={0x00};
	uint8_t tx_geninfo_asoc[1]={0x0E};          // asoc

	HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_geninfo_asoc, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_geninfo_asoc, 1);
	HAL_Delay(5);

//	uint8_t transmit_asoc[14]={'1','M','U','P','A','S','S',rx_geninfo_asoc[0] ,'A','S','E','U','P','E'};

	transmit_info_to_be_updated_during_bat2_management[0]='s';
	transmit_info_to_be_updated_during_bat2_management[1]='2';
	transmit_info_to_be_updated_during_bat2_management[2]='N';
	transmit_info_to_be_updated_during_bat2_management[3]='U';
	transmit_info_to_be_updated_during_bat2_management[4]='P';
	transmit_info_to_be_updated_during_bat2_management[5]='A';
	transmit_info_to_be_updated_during_bat2_management[6]='S';
	transmit_info_to_be_updated_during_bat2_management[7]='S';
	transmit_info_to_be_updated_during_bat2_management[8]=rx_geninfo_asoc[0];
	transmit_info_to_be_updated_during_bat2_management[9]='A';
	transmit_info_to_be_updated_during_bat2_management[10]='S';
	transmit_info_to_be_updated_during_bat2_management[11]='E';
	transmit_info_to_be_updated_during_bat2_management[12]='U';
	transmit_info_to_be_updated_during_bat2_management[13]='P';
	transmit_info_to_be_updated_during_bat2_management[14]='E';
	transmit_info_to_be_updated_during_bat2_management[15]='e';

	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);





}


}

void update_RemCap_during_management_bat2()
{

	if(bat2_geninfo_remainingcapacity_flag==true)
	{
		bat2_geninfo_remainingcapacity_flag = false;

		uint8_t rx_geninfo_remcap[2]={0x00};
		uint8_t tx_remcap[1]={0x0F};               // Rem Cap
		HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_remcap, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_geninfo_remcap, 2);
		HAL_Delay(5);



////		uint8_t send_update_voltage[14]={'1','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
//

		transmit_info_to_be_updated_during_bat2_management[0]='s';
		transmit_info_to_be_updated_during_bat2_management[1]='2';
		transmit_info_to_be_updated_during_bat2_management[2]='N';
		transmit_info_to_be_updated_during_bat2_management[3]='U';
		transmit_info_to_be_updated_during_bat2_management[4]='P';
		transmit_info_to_be_updated_during_bat2_management[5]='R';
		transmit_info_to_be_updated_during_bat2_management[6]='C';
		transmit_info_to_be_updated_during_bat2_management[7]='S';
		transmit_info_to_be_updated_during_bat2_management[8]=rx_geninfo_remcap[1];
		transmit_info_to_be_updated_during_bat2_management[9]=rx_geninfo_remcap[0];
		transmit_info_to_be_updated_during_bat2_management[10]='R';
		transmit_info_to_be_updated_during_bat2_management[11]='C';
		transmit_info_to_be_updated_during_bat2_management[12]='U';
		transmit_info_to_be_updated_during_bat2_management[13]='P';
		transmit_info_to_be_updated_during_bat2_management[14]='E';
		transmit_info_to_be_updated_during_bat2_management[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}

 void update_cyclecount_during_management_bat2()
 {
	 if(bat2_geninfo_cycle_flag==true)
	 {
		 bat2_geninfo_cycle_flag=false;
		uint8_t tx_cyclecount[1]={0x17}; // CycleCount
		uint8_t rx_cyclecount[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_cyclecount, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_cyclecount, 2);
		HAL_Delay(5);


		transmit_info_to_be_updated_during_bat2_management[0]='s';
		transmit_info_to_be_updated_during_bat2_management[1]='2';
		transmit_info_to_be_updated_during_bat2_management[2]='N';
		transmit_info_to_be_updated_during_bat2_management[3]='U';
		transmit_info_to_be_updated_during_bat2_management[4]='P';
		transmit_info_to_be_updated_during_bat2_management[5]='C';
		transmit_info_to_be_updated_during_bat2_management[6]='C';
		transmit_info_to_be_updated_during_bat2_management[7]='S';
		transmit_info_to_be_updated_during_bat2_management[8]=rx_cyclecount[1];
		transmit_info_to_be_updated_during_bat2_management[9]=rx_cyclecount[0];
		transmit_info_to_be_updated_during_bat2_management[10]='C';
		transmit_info_to_be_updated_during_bat2_management[11]='C';
		transmit_info_to_be_updated_during_bat2_management[12]='U';
		transmit_info_to_be_updated_during_bat2_management[13]='P';
		transmit_info_to_be_updated_during_bat2_management[14]='E';
		transmit_info_to_be_updated_during_bat2_management[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);


	 }




 }

 void update_batstatus_during_management_bat2()
 {

	 if(bat2_geninfo_batterystatus_flag==true)
		 {
		 bat2_geninfo_batterystatus_flag=false;

			uint8_t tx_batstatus[1]={0x16}; // Bat status
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_batstatus, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_batstatus, 2);
			HAL_Delay(5);


			transmit_info_to_be_updated_during_bat2_management[0]='s';
			transmit_info_to_be_updated_during_bat2_management[1]='2';
			transmit_info_to_be_updated_during_bat2_management[2]='N';
			transmit_info_to_be_updated_during_bat2_management[3]='U';
			transmit_info_to_be_updated_during_bat2_management[4]='P';
			transmit_info_to_be_updated_during_bat2_management[5]='B';
			transmit_info_to_be_updated_during_bat2_management[6]='S';
			transmit_info_to_be_updated_during_bat2_management[7]='S';
			transmit_info_to_be_updated_during_bat2_management[8]=rx_batstatus[1];
			transmit_info_to_be_updated_during_bat2_management[9]=rx_batstatus[0];
			transmit_info_to_be_updated_during_bat2_management[10]='B';
			transmit_info_to_be_updated_during_bat2_management[11]='S';
			transmit_info_to_be_updated_during_bat2_management[12]='U';
			transmit_info_to_be_updated_during_bat2_management[13]='P';
			transmit_info_to_be_updated_during_bat2_management[14]='E';
			transmit_info_to_be_updated_during_bat2_management[15]='e';




	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);


		 }




 }

 void update_temperature_during_management_bat2()
 {
if(bat2_geninfo_temperature_flag==true)
{

	bat2_geninfo_temperature_flag=false;

		uint8_t tx_temp[1]={0x08}; // Temperature
				uint8_t rx_temp[2]={0x00,0x00};
				HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_temp, 1);
				HAL_Delay(5);
				HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_temp, 2);
				HAL_Delay(5);


				transmit_info_to_be_updated_during_bat2_management[0]='s';
				transmit_info_to_be_updated_during_bat2_management[1]='2';
				transmit_info_to_be_updated_during_bat2_management[2]='N';
				transmit_info_to_be_updated_during_bat2_management[3]='U';
				transmit_info_to_be_updated_during_bat2_management[4]='P';
				transmit_info_to_be_updated_during_bat2_management[5]='T';
				transmit_info_to_be_updated_during_bat2_management[6]='P';
				transmit_info_to_be_updated_during_bat2_management[7]='S';
				transmit_info_to_be_updated_during_bat2_management[8]=rx_temp[1];
				transmit_info_to_be_updated_during_bat2_management[9]=rx_temp[0];
				transmit_info_to_be_updated_during_bat2_management[10]='T';
				transmit_info_to_be_updated_during_bat2_management[11]='P';
				transmit_info_to_be_updated_during_bat2_management[12]='U';
				transmit_info_to_be_updated_during_bat2_management[13]='P';
				transmit_info_to_be_updated_during_bat2_management[14]='E';
				transmit_info_to_be_updated_during_bat2_management[15]='e';




		HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);


}



}



 void update_current_during_management_bat2() //0x0A
  {


 		if(bat2_geninfo_current_flag==true)
 		{
 			bat2_geninfo_current_flag = false;

 			uint8_t rx_geninfo_current[2]={0x00};
 			uint8_t tx_current[1]={0x0A};                       // Current
 			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_current, 1);
 			HAL_Delay(5);
 			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_geninfo_current, 2);
 			HAL_Delay(5);
// 			uint16_t Bat2_Current_Manag = rx_geninfo_current[1];
// 			Bat2_Current_Manag = Bat2_Current_Manag << 8;
// 			Bat2_Current_Manag = Bat2_Current_Manag + rx_geninfo_current[0];


 	////		uint8_t send_update_voltage[14]={'1','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
 	//


 			transmit_info_to_be_updated_during_bat2_management[0]='s';
 			transmit_info_to_be_updated_during_bat2_management[1]='2';
 			transmit_info_to_be_updated_during_bat2_management[2]='N';
 			transmit_info_to_be_updated_during_bat2_management[3]='U';
 			transmit_info_to_be_updated_during_bat2_management[4]='P';
 			transmit_info_to_be_updated_during_bat2_management[5]='C';
 			transmit_info_to_be_updated_during_bat2_management[6]='R';
 			transmit_info_to_be_updated_during_bat2_management[7]='S';
 			transmit_info_to_be_updated_during_bat2_management[8]=rx_geninfo_current[1];
 			transmit_info_to_be_updated_during_bat2_management[9]=rx_geninfo_current[0];
 			transmit_info_to_be_updated_during_bat2_management[10]='C';
 			transmit_info_to_be_updated_during_bat2_management[11]='R';
 			transmit_info_to_be_updated_during_bat2_management[12]='U';
 			transmit_info_to_be_updated_during_bat2_management[13]='P';
 			transmit_info_to_be_updated_during_bat2_management[14]='E';
 			transmit_info_to_be_updated_during_bat2_management[15]='e';




 	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_during_bat2_management, 16);

 	//		rx_geninfo_voltage[0]=0;    //LSB
 	//		rx_geninfo_voltage[1]=0;



 		}






  }





