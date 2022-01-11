/*
 * Bat3_Update_Info_during_Maintenance.c
 *
 *  Created on: Dec 23, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "Bat3_Update_Info_during_Maintenance.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c3;

extern bool bat3_geninfo_voltage_flag;
extern bool bat3_geninfo_asoc_flag;
extern bool bat3_geninfo_remainingcapacity_flag;
extern bool bat3_geninfo_cycle_flag;
extern bool bat3_geninfo_batterystatus_flag;
extern bool bat3_geninfo_temperature_flag ;
extern bool bat3_geninfo_current_flag;


extern uint16_t bat3_geninfo_cycle_counter ;
extern uint16_t bat3_geninfo_asoc_counter ;
extern uint16_t bat3_geninfo_remainingcapacity_counter ;
extern uint16_t bat3_geninfo_voltage_counter ;
extern uint16_t bat3_geninfo_temperature_counter ;
extern uint16_t bat3_geninfo_batterystatus_counter ;
extern uint16_t bat3_geninfo_current_counter;

uint8_t transmit_info_to_be_updated_bat3_maint[16];

void update_voltage_during_maintenance_bat3()
{


	if(bat3_geninfo_voltage_flag==true)
	{
		bat3_geninfo_voltage_flag = false;

		uint8_t rx_geninfo_voltage[2]={0x00};
		uint8_t tx_voltage[1]={0x09};                       // Voltage
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_voltage, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_geninfo_voltage, 2);
		HAL_Delay(5);
		uint16_t Bat2_Volt_Maint_GI = rx_geninfo_voltage[1];
		Bat2_Volt_Maint_GI = Bat2_Volt_Maint_GI << 8;
		Bat2_Volt_Maint_GI = Bat2_Volt_Maint_GI + rx_geninfo_voltage[0];


//uint8_t transmit_info_to_be_updated_bat2_maint[14]={'2','M','U','P','V','T','S',rx_geninfo_voltage[1] , rx_geninfo_voltage[0],'V','T','U','P','E'};
// The above method of sending data to Pi didn't work properly.



		// The following method worked
		transmit_info_to_be_updated_bat3_maint[0]='s';
		transmit_info_to_be_updated_bat3_maint[1]='3';
		transmit_info_to_be_updated_bat3_maint[2]='M';
		transmit_info_to_be_updated_bat3_maint[3]='U';
		transmit_info_to_be_updated_bat3_maint[4]='P';
		transmit_info_to_be_updated_bat3_maint[5]='V';
		transmit_info_to_be_updated_bat3_maint[6]='T';
		transmit_info_to_be_updated_bat3_maint[7]='S';
		transmit_info_to_be_updated_bat3_maint[8]=rx_geninfo_voltage[1];
		transmit_info_to_be_updated_bat3_maint[9]=rx_geninfo_voltage[0];
		transmit_info_to_be_updated_bat3_maint[10]='V';
		transmit_info_to_be_updated_bat3_maint[11]='T';
		transmit_info_to_be_updated_bat3_maint[12]='U';
		transmit_info_to_be_updated_bat3_maint[13]='P';
		transmit_info_to_be_updated_bat3_maint[14]='E';
		transmit_info_to_be_updated_bat3_maint[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}

void update_asoc_during_maintenance_bat3()
{

if(bat3_geninfo_asoc_flag==true)
{

	bat3_geninfo_asoc_flag = false;

	uint8_t rx_geninfo_asoc[1]={0x00};
	uint8_t tx_geninfo_asoc[1]={0x0E};          // asoc

	HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_geninfo_asoc, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_geninfo_asoc, 1);
	HAL_Delay(5);


	transmit_info_to_be_updated_bat3_maint[0]='s';
	transmit_info_to_be_updated_bat3_maint[1]='3';
	transmit_info_to_be_updated_bat3_maint[2]='M';
	transmit_info_to_be_updated_bat3_maint[3]='U';
	transmit_info_to_be_updated_bat3_maint[4]='P';
	transmit_info_to_be_updated_bat3_maint[5]='A';
	transmit_info_to_be_updated_bat3_maint[6]='S';
	transmit_info_to_be_updated_bat3_maint[7]='S';
	transmit_info_to_be_updated_bat3_maint[8]=rx_geninfo_asoc[0];
	transmit_info_to_be_updated_bat3_maint[9]='A';
	transmit_info_to_be_updated_bat3_maint[10]='S';
	transmit_info_to_be_updated_bat3_maint[11]='E';
	transmit_info_to_be_updated_bat3_maint[12]='U';
	transmit_info_to_be_updated_bat3_maint[13]='P';
	transmit_info_to_be_updated_bat3_maint[14]='E';
	transmit_info_to_be_updated_bat3_maint[15]='e';

	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);





}


}

void update_RemCap_during_maintenance_bat3()
{

	if(bat3_geninfo_remainingcapacity_flag==true)
	{
		bat3_geninfo_remainingcapacity_flag = false;

		uint8_t rx_geninfo_remcap[2]={0x00};
		uint8_t tx_remcap[1]={0x0F};               // Rem Cap
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_remcap, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_geninfo_remcap, 2);
		HAL_Delay(5);





		transmit_info_to_be_updated_bat3_maint[0]='s';
		transmit_info_to_be_updated_bat3_maint[1]='3';
		transmit_info_to_be_updated_bat3_maint[2]='M';
		transmit_info_to_be_updated_bat3_maint[3]='U';
		transmit_info_to_be_updated_bat3_maint[4]='P';
		transmit_info_to_be_updated_bat3_maint[5]='R';
		transmit_info_to_be_updated_bat3_maint[6]='C';
		transmit_info_to_be_updated_bat3_maint[7]='S';
		transmit_info_to_be_updated_bat3_maint[8]=rx_geninfo_remcap[1];
		transmit_info_to_be_updated_bat3_maint[9]=rx_geninfo_remcap[0];
		transmit_info_to_be_updated_bat3_maint[10]='R';
		transmit_info_to_be_updated_bat3_maint[11]='C';
		transmit_info_to_be_updated_bat3_maint[12]='U';
		transmit_info_to_be_updated_bat3_maint[13]='P';
		transmit_info_to_be_updated_bat3_maint[14]='E';
		transmit_info_to_be_updated_bat3_maint[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);

//		rx_geninfo_voltage[0]=0;    //LSB
//		rx_geninfo_voltage[1]=0;



	}



}


void update_cyclecount_during_maintenance_bat3()
{
	 if(bat3_geninfo_cycle_flag==true)
	 {
		 bat3_geninfo_cycle_flag=false;
		uint8_t tx_cyclecount[1]={0x17}; // CycleCount
		uint8_t rx_cyclecount[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_cyclecount, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_cyclecount, 2);
		HAL_Delay(5);

		transmit_info_to_be_updated_bat3_maint[0]='s';
		transmit_info_to_be_updated_bat3_maint[1]='3';
		transmit_info_to_be_updated_bat3_maint[2]='M';
		transmit_info_to_be_updated_bat3_maint[3]='U';
		transmit_info_to_be_updated_bat3_maint[4]='P';
		transmit_info_to_be_updated_bat3_maint[5]='C';
		transmit_info_to_be_updated_bat3_maint[6]='C';
		transmit_info_to_be_updated_bat3_maint[7]='S';
		transmit_info_to_be_updated_bat3_maint[8]=rx_cyclecount[1];
		transmit_info_to_be_updated_bat3_maint[9]=rx_cyclecount[0];
		transmit_info_to_be_updated_bat3_maint[10]='C';
		transmit_info_to_be_updated_bat3_maint[11]='C';
		transmit_info_to_be_updated_bat3_maint[12]='U';
		transmit_info_to_be_updated_bat3_maint[13]='P';
		transmit_info_to_be_updated_bat3_maint[14]='E';
		transmit_info_to_be_updated_bat3_maint[15]='e';




HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);


	 }




}

void update_batstatus_during_maintenance_bat3()
{

	 if(bat3_geninfo_batterystatus_flag==true)
		 {
		 bat3_geninfo_batterystatus_flag=false;

			uint8_t tx_batstatus[1]={0x16}; // Bat status
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_batstatus, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_batstatus, 2);
			HAL_Delay(5);

			transmit_info_to_be_updated_bat3_maint[0]='s';
			transmit_info_to_be_updated_bat3_maint[1]='3';
			transmit_info_to_be_updated_bat3_maint[2]='M';
			transmit_info_to_be_updated_bat3_maint[3]='U';
			transmit_info_to_be_updated_bat3_maint[4]='P';
			transmit_info_to_be_updated_bat3_maint[5]='B';
			transmit_info_to_be_updated_bat3_maint[6]='S';
			transmit_info_to_be_updated_bat3_maint[7]='S';
			transmit_info_to_be_updated_bat3_maint[8]=rx_batstatus[1];
			transmit_info_to_be_updated_bat3_maint[9]=rx_batstatus[0];
			transmit_info_to_be_updated_bat3_maint[10]='B';
			transmit_info_to_be_updated_bat3_maint[11]='S';
			transmit_info_to_be_updated_bat3_maint[12]='U';
			transmit_info_to_be_updated_bat3_maint[13]='P';
			transmit_info_to_be_updated_bat3_maint[14]='E';
			transmit_info_to_be_updated_bat3_maint[15]='e';




	HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);


		 }




}

void update_temperature_during_maintenance_bat3()
{
if(bat3_geninfo_temperature_flag==true)
{

	bat3_geninfo_temperature_flag=false;

		uint8_t tx_temp[1]={0x08}; // Temperature
				uint8_t rx_temp[2]={0x00,0x00};
				HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_temp, 1);
				HAL_Delay(5);
				HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_temp, 2);
				HAL_Delay(5);

				transmit_info_to_be_updated_bat3_maint[0]='s';
				transmit_info_to_be_updated_bat3_maint[1]='3';
				transmit_info_to_be_updated_bat3_maint[2]='M';
				transmit_info_to_be_updated_bat3_maint[3]='U';
				transmit_info_to_be_updated_bat3_maint[4]='P';
				transmit_info_to_be_updated_bat3_maint[5]='T';
				transmit_info_to_be_updated_bat3_maint[6]='P';
				transmit_info_to_be_updated_bat3_maint[7]='S';
				transmit_info_to_be_updated_bat3_maint[8]=rx_temp[1];
				transmit_info_to_be_updated_bat3_maint[9]=rx_temp[0];
				transmit_info_to_be_updated_bat3_maint[10]='T';
				transmit_info_to_be_updated_bat3_maint[11]='P';
				transmit_info_to_be_updated_bat3_maint[12]='U';
				transmit_info_to_be_updated_bat3_maint[13]='P';
				transmit_info_to_be_updated_bat3_maint[14]='E';
				transmit_info_to_be_updated_bat3_maint[15]='e';




		HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);


}



}


void update_current_during_maintenance_bat3()
{
if(bat3_geninfo_current_flag==true)
{

	bat3_geninfo_current_flag=false;

		uint8_t tx_current[1]={0x0A}; // Current
				uint8_t rx_current[2]={0x00,0x00};
				HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_current, 1);
				HAL_Delay(5);
				HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_current, 2);
				HAL_Delay(5);

				transmit_info_to_be_updated_bat3_maint[0]='s';
				transmit_info_to_be_updated_bat3_maint[1]='3';
				transmit_info_to_be_updated_bat3_maint[2]='M';
				transmit_info_to_be_updated_bat3_maint[3]='U';
				transmit_info_to_be_updated_bat3_maint[4]='P';
				transmit_info_to_be_updated_bat3_maint[5]='C';
				transmit_info_to_be_updated_bat3_maint[6]='R';
				transmit_info_to_be_updated_bat3_maint[7]='S';
				transmit_info_to_be_updated_bat3_maint[8]=rx_current[1];
				transmit_info_to_be_updated_bat3_maint[9]=rx_current[0];
				transmit_info_to_be_updated_bat3_maint[10]='C';
				transmit_info_to_be_updated_bat3_maint[11]='R';
				transmit_info_to_be_updated_bat3_maint[12]='U';
				transmit_info_to_be_updated_bat3_maint[13]='P';
				transmit_info_to_be_updated_bat3_maint[14]='E';
				transmit_info_to_be_updated_bat3_maint[15]='e';




		HAL_UART_Transmit_IT(&huart2, transmit_info_to_be_updated_bat3_maint, 16);


}



}



void update_periodic_flags_during_maintenance_bat3()
 {

		    bat3_geninfo_asoc_counter++;
			bat3_geninfo_voltage_counter++;
			bat3_geninfo_remainingcapacity_counter++;
			bat3_geninfo_temperature_counter++;
			bat3_geninfo_cycle_counter++;
			bat3_geninfo_current_counter++;
			bat3_geninfo_batterystatus_counter++;

			if(bat3_geninfo_asoc_counter==100)
			{
				bat3_geninfo_asoc_counter=0;
				bat3_geninfo_asoc_flag=true;
			}

			if(bat3_geninfo_voltage_counter==50)  // update time - 2 minutes - 50
			{
				bat3_geninfo_voltage_counter=0;
				bat3_geninfo_voltage_flag=true;
			}

			if(bat3_geninfo_remainingcapacity_counter==70)
			{
				bat3_geninfo_remainingcapacity_counter=0;
				bat3_geninfo_remainingcapacity_flag=true;
			}
			if(bat3_geninfo_temperature_counter==10)
			{
				bat3_geninfo_temperature_counter=0;
				bat3_geninfo_temperature_flag=true;
			}
			if(bat3_geninfo_cycle_counter==400)
			{
				bat3_geninfo_cycle_counter=0;
				bat3_geninfo_cycle_flag=true;
			}
			if(bat3_geninfo_current_counter==200)
			{
				bat3_geninfo_current_counter=0;
				bat3_geninfo_current_flag=true;
			}
			if(bat3_geninfo_batterystatus_counter==25)
			{
				bat3_geninfo_batterystatus_counter=0;
				bat3_geninfo_batterystatus_flag =true;
			}




		}
