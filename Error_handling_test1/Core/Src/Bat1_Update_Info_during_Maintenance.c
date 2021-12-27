/*
 * Bat1_Update_Info_during_Maintenance.c
 *
 *  Created on: 07-Dec-2021
 *      Author: shubham
 */
#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "string.h"
#include "Bat1_Update_Info_during_Maintenance.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

extern bool bat1_geninfo_voltage_flag;
extern bool bat1_geninfo_asoc_flag;
extern bool bat1_geninfo_remainingcapacity_flag;
extern bool bat1_geninfo_cycle_flag;
extern bool bat1_geninfo_batterystatus_flag;
extern bool bat1_geninfo_temperature_flag ;
extern bool bat1_geninfo_current_flag;


extern uint16_t bat1_geninfo_cycle_counter ;
extern uint16_t bat1_geninfo_asoc_counter ;
extern uint16_t bat1_geninfo_remainingcapacity_counter ;
extern uint16_t bat1_geninfo_voltage_counter ;
extern uint16_t bat1_geninfo_temperature_counter ;
extern uint16_t bat1_geninfo_batterystatus_counter ;
extern uint16_t bat1_geninfo_current_counter;









extern int _write(int file, char *ptr, int len);

uint8_t transmit_info_to_be_updated[16];

uint8_t transmit_asoc[14];


void update_voltage_during_maintenance_bat1()
{


	if(bat1_geninfo_voltage_flag==true)
	{
		bat1_geninfo_voltage_flag = false;

		uint8_t rx_geninfo_voltage[2]={0x00};
		uint8_t tx_voltage[1]={0x09};                       // Voltage
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_voltage, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_voltage, 2);
		HAL_Delay(5);
		uint16_t Bat1_Volt_Maint_GI = rx_geninfo_voltage[1];
		Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI << 8;
		Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI + rx_geninfo_voltage[0];


////		uint8_t send_update_voltage[14]={'1','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
//

	//	uint8_t transmit_voltage[14];
		transmit_info_to_be_updated[0]='s';
		transmit_info_to_be_updated[1]='1';
		transmit_info_to_be_updated[2]='M';
		transmit_info_to_be_updated[3]='U';
		transmit_info_to_be_updated[4]='P';
		transmit_info_to_be_updated[5]='V';
		transmit_info_to_be_updated[6]='T';
		transmit_info_to_be_updated[7]='S';
		transmit_info_to_be_updated[8]=rx_geninfo_voltage[1];
		transmit_info_to_be_updated[9]=rx_geninfo_voltage[0];
		transmit_info_to_be_updated[10]='V';
		transmit_info_to_be_updated[11]='T';
		transmit_info_to_be_updated[12]='U';
		transmit_info_to_be_updated[13]='P';
		transmit_info_to_be_updated[14]='E';
		transmit_info_to_be_updated[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}

void update_asoc_during_maintenance_bat1()
{

if(bat1_geninfo_asoc_flag==true)
{

	bat1_geninfo_asoc_flag = false;

	uint8_t rx_geninfo_asoc[1]={0x00};
	uint8_t tx_geninfo_asoc[1]={0x0E};          // asoc

	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_geninfo_asoc, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_asoc, 1);
	HAL_Delay(5);

//	uint8_t transmit_asoc[14]={'1','M','U','P','A','S','S',rx_geninfo_asoc[0] ,'A','S','E','U','P','E'};

	transmit_info_to_be_updated[0]='s';
	transmit_info_to_be_updated[1]='1';
	transmit_info_to_be_updated[2]='M';
	transmit_info_to_be_updated[3]='U';
	transmit_info_to_be_updated[4]='P';
	transmit_info_to_be_updated[5]='A';
	transmit_info_to_be_updated[6]='S';
	transmit_info_to_be_updated[7]='S';
	transmit_info_to_be_updated[8]=rx_geninfo_asoc[0];
	transmit_info_to_be_updated[9]='A';
	transmit_info_to_be_updated[10]='S';
	transmit_info_to_be_updated[11]='E';
	transmit_info_to_be_updated[12]='U';
	transmit_info_to_be_updated[13]='P';
	transmit_info_to_be_updated[14]='E';
	transmit_info_to_be_updated[15]='e';

	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);





}


}

void update_RemCap_during_maintenance_bat1()
{

	if(bat1_geninfo_remainingcapacity_flag==true)
	{
		bat1_geninfo_remainingcapacity_flag = false;

		uint8_t rx_geninfo_remcap[2]={0x00};
		uint8_t tx_remcap[1]={0x0F};               // Rem Cap
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_remcap, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_remcap, 2);
		HAL_Delay(5);



////		uint8_t send_update_voltage[14]={'1','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
//

		transmit_info_to_be_updated[0]='s';
		transmit_info_to_be_updated[1]='1';
		transmit_info_to_be_updated[2]='M';
		transmit_info_to_be_updated[3]='U';
		transmit_info_to_be_updated[4]='P';
		transmit_info_to_be_updated[5]='R';
		transmit_info_to_be_updated[6]='C';
		transmit_info_to_be_updated[7]='S';
		transmit_info_to_be_updated[8]=rx_geninfo_remcap[1];
		transmit_info_to_be_updated[9]=rx_geninfo_remcap[0];
		transmit_info_to_be_updated[10]='R';
		transmit_info_to_be_updated[11]='C';
		transmit_info_to_be_updated[12]='U';
		transmit_info_to_be_updated[13]='P';
		transmit_info_to_be_updated[14]='E';
		transmit_info_to_be_updated[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}

 void update_cyclecount_during_maintenance_bat1()
 {
	 if(bat1_geninfo_cycle_flag==true)
	 {
		 bat1_geninfo_cycle_flag=false;
		uint8_t tx_cyclecount[1]={0x17}; // CycleCount
		uint8_t rx_cyclecount[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_cyclecount, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_cyclecount, 2);
		HAL_Delay(5);


		transmit_info_to_be_updated[0]='s';
		transmit_info_to_be_updated[1]='1';
		transmit_info_to_be_updated[2]='M';
		transmit_info_to_be_updated[3]='U';
		transmit_info_to_be_updated[4]='P';
		transmit_info_to_be_updated[5]='C';
		transmit_info_to_be_updated[6]='C';
		transmit_info_to_be_updated[7]='S';
		transmit_info_to_be_updated[8]=rx_cyclecount[1];
		transmit_info_to_be_updated[9]=rx_cyclecount[0];
		transmit_info_to_be_updated[10]='C';
		transmit_info_to_be_updated[11]='C';
		transmit_info_to_be_updated[12]='U';
		transmit_info_to_be_updated[13]='P';
		transmit_info_to_be_updated[14]='E';
		transmit_info_to_be_updated[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);


	 }




 }

 void update_batstatus_during_maintenance_bat1()
 {

	 if(bat1_geninfo_batterystatus_flag==true)
		 {
		 bat1_geninfo_batterystatus_flag=false;

			uint8_t tx_batstatus[1]={0x16}; // Bat status
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_batstatus, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_batstatus, 2);
			HAL_Delay(5);


			transmit_info_to_be_updated[0]='s';
			transmit_info_to_be_updated[1]='1';
			transmit_info_to_be_updated[2]='M';
			transmit_info_to_be_updated[3]='U';
			transmit_info_to_be_updated[4]='P';
			transmit_info_to_be_updated[5]='B';
			transmit_info_to_be_updated[6]='S';
			transmit_info_to_be_updated[7]='S';
			transmit_info_to_be_updated[8]=rx_batstatus[1];
			transmit_info_to_be_updated[9]=rx_batstatus[0];
			transmit_info_to_be_updated[10]='B';
			transmit_info_to_be_updated[11]='S';
			transmit_info_to_be_updated[12]='U';
			transmit_info_to_be_updated[13]='P';
			transmit_info_to_be_updated[14]='E';
			transmit_info_to_be_updated[15]='e';




	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);


		 }




 }

 void update_temperature_during_maintenance_bat1()
 {
if(bat1_geninfo_temperature_flag==true)
{

	bat1_geninfo_temperature_flag=false;

		uint8_t tx_temp[1]={0x08}; // Temperature
				uint8_t rx_temp[2]={0x00,0x00};
				HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_temp, 1);
				HAL_Delay(5);
				HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_temp, 2);
				HAL_Delay(5);


				transmit_info_to_be_updated[0]='s';
				transmit_info_to_be_updated[1]='1';
				transmit_info_to_be_updated[2]='M';
				transmit_info_to_be_updated[3]='U';
				transmit_info_to_be_updated[4]='P';
				transmit_info_to_be_updated[5]='T';
				transmit_info_to_be_updated[6]='P';
				transmit_info_to_be_updated[7]='S';
				transmit_info_to_be_updated[8]=rx_temp[1];
				transmit_info_to_be_updated[9]=rx_temp[0];
				transmit_info_to_be_updated[10]='T';
				transmit_info_to_be_updated[11]='P';
				transmit_info_to_be_updated[12]='U';
				transmit_info_to_be_updated[13]='P';
				transmit_info_to_be_updated[14]='E';
				transmit_info_to_be_updated[15]='e';




		HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated, 16);


}



}

 void update_periodic_flags_during_maintenance_bat1()
 {

		bat1_geninfo_asoc_counter++;
			bat1_geninfo_voltage_counter++;
			bat1_geninfo_remainingcapacity_counter++;
			bat1_geninfo_temperature_counter++;
			bat1_geninfo_cycle_counter++;
			bat1_geninfo_current_counter++;
			bat1_geninfo_batterystatus_counter++;

			if(bat1_geninfo_asoc_counter==100)
			{
				bat1_geninfo_asoc_counter=0;
				bat1_geninfo_asoc_flag=true;
			}

			if(bat1_geninfo_voltage_counter==50)  // update time - 2 minutes - 50
			{
				bat1_geninfo_voltage_counter=0;
				bat1_geninfo_voltage_flag=true;
			}

			if(bat1_geninfo_remainingcapacity_counter==70)
			{
				bat1_geninfo_remainingcapacity_counter=0;
				bat1_geninfo_remainingcapacity_flag=true;
			}
			if(bat1_geninfo_temperature_counter==10)
			{
				bat1_geninfo_temperature_counter=0;
				bat1_geninfo_temperature_flag=true;
			}
			if(bat1_geninfo_cycle_counter==400)
			{
				bat1_geninfo_cycle_counter=0;
				bat1_geninfo_cycle_flag=true;
			}
			if(bat1_geninfo_current_counter==200)
			{
				bat1_geninfo_current_counter=0;
				bat1_geninfo_current_flag=true;
			}
			if(bat1_geninfo_batterystatus_counter==25)
			{
				bat1_geninfo_batterystatus_counter=0;
				bat1_geninfo_batterystatus_flag =true;
			}




		}





