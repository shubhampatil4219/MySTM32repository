/*
 * Bat2_Update_Info_during_Maintenance.c
 *
 *  Created on: Dec 22, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "Bat2_Update_Info_during_Maintenance.h"

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

uint8_t transmit_info_to_be_updated_bat2_maint[14];

void update_voltage_during_maintenance_bat2()
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
		uint16_t Bat2_Volt_Maint_GI = rx_geninfo_voltage[1];
		Bat2_Volt_Maint_GI = Bat2_Volt_Maint_GI << 8;
		Bat2_Volt_Maint_GI = Bat2_Volt_Maint_GI + rx_geninfo_voltage[0];


//uint8_t transmit_info_to_be_updated_bat2_maint[14]={'2','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
// The above method of sending data to Pi didn't work properly.



		// The following method worked

		transmit_info_to_be_updated_bat2_maint[0]='2';
		transmit_info_to_be_updated_bat2_maint[1]='M';
		transmit_info_to_be_updated_bat2_maint[2]='U';
		transmit_info_to_be_updated_bat2_maint[3]='P';
		transmit_info_to_be_updated_bat2_maint[4]='V';
		transmit_info_to_be_updated_bat2_maint[5]='T';
		transmit_info_to_be_updated_bat2_maint[6]='S';
		transmit_info_to_be_updated_bat2_maint[7]=rx_geninfo_voltage[1];
		transmit_info_to_be_updated_bat2_maint[8]=rx_geninfo_voltage[0];
		transmit_info_to_be_updated_bat2_maint[9]='V';
		transmit_info_to_be_updated_bat2_maint[10]='T';
		transmit_info_to_be_updated_bat2_maint[11]='U';
		transmit_info_to_be_updated_bat2_maint[12]='P';
		transmit_info_to_be_updated_bat2_maint[13]='E';





HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}

void update_asoc_during_maintenance_bat2()
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



	transmit_info_to_be_updated_bat2_maint[0]='2';
	transmit_info_to_be_updated_bat2_maint[1]='M';
	transmit_info_to_be_updated_bat2_maint[2]='U';
	transmit_info_to_be_updated_bat2_maint[3]='P';
	transmit_info_to_be_updated_bat2_maint[4]='A';
	transmit_info_to_be_updated_bat2_maint[5]='S';
	transmit_info_to_be_updated_bat2_maint[6]='S';
	transmit_info_to_be_updated_bat2_maint[7]=rx_geninfo_asoc[0];
	transmit_info_to_be_updated_bat2_maint[8]='A';
	transmit_info_to_be_updated_bat2_maint[9]='S';
	transmit_info_to_be_updated_bat2_maint[10]='E';
	transmit_info_to_be_updated_bat2_maint[11]='U';
	transmit_info_to_be_updated_bat2_maint[12]='P';
	transmit_info_to_be_updated_bat2_maint[13]='E';


	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);





}


}

void update_RemCap_during_maintenance_bat2()
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


		transmit_info_to_be_updated_bat2_maint[0]='2';
		transmit_info_to_be_updated_bat2_maint[1]='M';
		transmit_info_to_be_updated_bat2_maint[2]='U';
		transmit_info_to_be_updated_bat2_maint[3]='P';
		transmit_info_to_be_updated_bat2_maint[4]='R';
		transmit_info_to_be_updated_bat2_maint[5]='C';
		transmit_info_to_be_updated_bat2_maint[6]='S';
		transmit_info_to_be_updated_bat2_maint[7]=rx_geninfo_remcap[1];
		transmit_info_to_be_updated_bat2_maint[8]=rx_geninfo_remcap[0];
		transmit_info_to_be_updated_bat2_maint[9]='R';
		transmit_info_to_be_updated_bat2_maint[10]='C';
		transmit_info_to_be_updated_bat2_maint[11]='U';
		transmit_info_to_be_updated_bat2_maint[12]='P';
		transmit_info_to_be_updated_bat2_maint[13]='E';





HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}


void update_cyclecount_during_maintenance_bat2()
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

		transmit_info_to_be_updated_bat2_maint[0]='2';
		transmit_info_to_be_updated_bat2_maint[1]='M';
		transmit_info_to_be_updated_bat2_maint[2]='U';
		transmit_info_to_be_updated_bat2_maint[3]='P';
		transmit_info_to_be_updated_bat2_maint[4]='C';
		transmit_info_to_be_updated_bat2_maint[5]='C';
		transmit_info_to_be_updated_bat2_maint[6]='S';
		transmit_info_to_be_updated_bat2_maint[7]=rx_cyclecount[1];
		transmit_info_to_be_updated_bat2_maint[8]=rx_cyclecount[0];
		transmit_info_to_be_updated_bat2_maint[9]='C';
		transmit_info_to_be_updated_bat2_maint[10]='C';
		transmit_info_to_be_updated_bat2_maint[11]='U';
		transmit_info_to_be_updated_bat2_maint[12]='P';
		transmit_info_to_be_updated_bat2_maint[13]='E';





HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);


	 }




}

void update_batstatus_during_maintenance_bat2()
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

			transmit_info_to_be_updated_bat2_maint[0]='2';
			transmit_info_to_be_updated_bat2_maint[1]='M';
			transmit_info_to_be_updated_bat2_maint[2]='U';
			transmit_info_to_be_updated_bat2_maint[3]='P';
			transmit_info_to_be_updated_bat2_maint[4]='B';
			transmit_info_to_be_updated_bat2_maint[5]='S';
			transmit_info_to_be_updated_bat2_maint[6]='S';
			transmit_info_to_be_updated_bat2_maint[7]=rx_batstatus[1];
			transmit_info_to_be_updated_bat2_maint[8]=rx_batstatus[0];
			transmit_info_to_be_updated_bat2_maint[9]='B';
			transmit_info_to_be_updated_bat2_maint[10]='S';
			transmit_info_to_be_updated_bat2_maint[11]='U';
			transmit_info_to_be_updated_bat2_maint[12]='P';
			transmit_info_to_be_updated_bat2_maint[13]='E';





	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);


		 }




}

void update_temperature_during_maintenance_bat2()
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

				transmit_info_to_be_updated_bat2_maint[0]='2';
				transmit_info_to_be_updated_bat2_maint[1]='M';
				transmit_info_to_be_updated_bat2_maint[2]='U';
				transmit_info_to_be_updated_bat2_maint[3]='P';
				transmit_info_to_be_updated_bat2_maint[4]='T';
				transmit_info_to_be_updated_bat2_maint[5]='P';
				transmit_info_to_be_updated_bat2_maint[6]='S';
				transmit_info_to_be_updated_bat2_maint[7]=rx_temp[1];
				transmit_info_to_be_updated_bat2_maint[8]=rx_temp[0];
				transmit_info_to_be_updated_bat2_maint[9]='T';
				transmit_info_to_be_updated_bat2_maint[10]='P';
				transmit_info_to_be_updated_bat2_maint[11]='U';
				transmit_info_to_be_updated_bat2_maint[12]='P';
				transmit_info_to_be_updated_bat2_maint[13]='E';





		HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat2_maint, 14);


}



}



void update_periodic_flags_during_maintenance_bat2()
 {

		    bat2_geninfo_asoc_counter++;
			bat2_geninfo_voltage_counter++;
			bat2_geninfo_remainingcapacity_counter++;
			bat2_geninfo_temperature_counter++;
			bat2_geninfo_cycle_counter++;
			bat2_geninfo_current_counter++;
			bat2_geninfo_batterystatus_counter++;

			if(bat2_geninfo_asoc_counter==100)
			{
				bat2_geninfo_asoc_counter=0;
				bat2_geninfo_asoc_flag=true;
			}

			if(bat2_geninfo_voltage_counter==50)  // update time - 2 minutes - 50
			{
				bat2_geninfo_voltage_counter=0;
				bat2_geninfo_voltage_flag=true;
			}

			if(bat2_geninfo_remainingcapacity_counter==70)
			{
				bat2_geninfo_remainingcapacity_counter=0;
				bat2_geninfo_remainingcapacity_flag=true;
			}
			if(bat2_geninfo_temperature_counter==10)
			{
				bat2_geninfo_temperature_counter=0;
				bat2_geninfo_temperature_flag=true;
			}
			if(bat2_geninfo_cycle_counter==400)
			{
				bat2_geninfo_cycle_counter=0;
				bat2_geninfo_cycle_flag=true;
			}
			if(bat2_geninfo_current_counter==200)
			{
				bat2_geninfo_current_counter=0;
				bat2_geninfo_current_flag=true;
			}
			if(bat2_geninfo_batterystatus_counter==25)
			{
				bat2_geninfo_batterystatus_counter=0;
				bat2_geninfo_batterystatus_flag =true;
			}




		}

