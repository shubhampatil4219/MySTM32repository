/*
 * Specific_parameters_main_BAT1.c
 *
 *  Created on: 17-Nov-2021
 *      Author: shubham
 */
#include "stm32f7xx_hal.h"

#include"Specific_parameters_main_BAT1.h"
#include "timer_delay.h"
#include "stdio.h"
#include "stdbool.h"





extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;




extern bool Autotestflag;


//extern int _write(int file, char *ptr, int len);


void Read_and_Compare_Specific_para_Bat1_STM_to_Pi()
{


	uint8_t tx_bat1_specf_battery_status[1] = {0x16};		// 0x16

	//uint8_t tx_bat1_specf_run_time_to_empty[1]={0x11};	// 0x11

//	printf("Maintenance Use Case Bat 1 Specific parameters\n");
	// Battery Status
	uint8_t rx_batstatus[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_bat1_specf_battery_status, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_batstatus, 2);
	msdelay(1);
	uint16_t bs = rx_batstatus[1];
	bs = bs << 8;
	bs = bs + rx_batstatus[0];
//	printf("Battery Status = %d\n",bs);

	uint8_t send_specific_batstatus[16]={'s','1','M','S','I','B','S','S',rx_batstatus[1],rx_batstatus[0],'B','S','S','I','E','e'};
	HAL_UART_Transmit_IT(&huart2, send_specific_batstatus, 16);



	// Battery Full Charge Capacity
	uint8_t tx_bat1_specf_full_charge_capacity[1]={0x10};	// 0x10
	uint8_t rx_full_charge_capacity[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_bat1_specf_full_charge_capacity, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_full_charge_capacity, 2);
	msdelay(1);
	uint16_t fcc = rx_full_charge_capacity[1];
	fcc = fcc << 8;
	fcc = fcc + rx_full_charge_capacity[0];
//	printf("Full Charge Capacity = %d\n",fcc);

	uint8_t send_specific_fcc[16]={'s','1','M','S','I','F','C','S',rx_full_charge_capacity[1],rx_full_charge_capacity[0],'F','C','S','I','E','e'};
	HAL_UART_Transmit_IT(&huart2, send_specific_fcc, 16);




	// Battery Design Capacity
	uint8_t tx_bat1_specf_design_capacity[1]={0x18};		// 0x18
	uint8_t rx_design_capacity[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_bat1_specf_design_capacity, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_design_capacity, 2);
	msdelay(1);
	uint16_t designcap = rx_design_capacity[1];
	designcap = designcap << 8;
	designcap = designcap + rx_design_capacity[0];
//	printf("Design Capacity = %d\n",designcap);

	uint8_t send_specific_design_cap[16]={'s','1','M','S','I','D','C','S',rx_design_capacity[1],rx_design_capacity[0],'D','C','S','I','E','e'};
	HAL_UART_Transmit_IT(&huart2, send_specific_design_cap, 16);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart2, send_specific_design_cap, 16);

//	// Battery Design Capacity
//	uint8_t tx_bat1_specf_design_capacity2[1]={0x18};		// 0x18
//	uint8_t rx_design_capacity2[2]={0x00,0x00};
//	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_bat1_specf_design_capacity2, 1);
//	msdelay(5);
//	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_design_capacity2, 2);
//	msdelay(1);
//	uint16_t designcap2 = rx_design_capacity2[1];
//	designcap2 = designcap2 << 8;
//	designcap2 = designcap2 + rx_design_capacity2[0];
////	printf("Design Capacity = %d\n",designcap);
//
//	uint8_t send_specific_design_cap2[16]={'s','1','M','S','I','D','C','S',rx_design_capacity2[1],rx_design_capacity2[0],'D','C','S','I','E','e'};
//	HAL_UART_Transmit_IT(&huart2, send_specific_design_cap2, 16);












	// Battery Run Time To Empty
	//	uint8_t rx_run_time_to_empty[2]={0x00,0x00};
	//	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_run_time_to_empty, 1);
	//	msdelay(5);
	//	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_run_time_to_empty, 2);
	//	msdelay(1);
	//	uint16_t rte = rx_run_time_to_empty[1];
	//	rte = rte << 8;
	//	rte = rte + rx_run_time_to_empty[0];



	Compare_Specifi_para_Bat1(fcc,designcap,bs);   // Function to compare specific parameters of battery 1



//	printf("Battery 1 Read Specific parameter function executed only at the start\n");









}

void Compare_Specifi_para_Bat1(uint16_t fullchargecap , uint16_t designcap, uint16_t batterystatus)
{

	// Here Design Capacity and Full Charge Capacity are compared
	if(fullchargecap >4620  &&  fullchargecap <= designcap)
	{
	//	printf("Battery is in good condition\n");
		__NOP();  // It means no operation does nothing

	}
	if(fullchargecap<4620 && fullchargecap!=0)
	{
		Autotestflag = false;   // // Abort the test


	}

	// Function To convert decimal to binary. Add this function on Raspi Side
	uint8_t bat_status_array[16];
	if(0<=batterystatus && batterystatus<=65535){
		for(int j = 0; j < 16; j++) {
			if (batterystatus % 2 == 0) {
				bat_status_array[j] = 0;
			}
			else {
				bat_status_array[j] = 1;
			}
			batterystatus = batterystatus / 2;
		}
	}

	if(bat_status_array[15] == 1 || bat_status_array[14] == 1 || bat_status_array[12] == 1 || bat_status_array[11] == 1 )

	{


		Autotestflag = false;  // Abort the test

	//	printf("Auto test is terminated because one of the alarm flag is set\n");

	}


}

void Read_bat1_maint_Run_time_to_empty()
{

	uint8_t tx_rte[1]={0x11};	// 0x11
	uint8_t rx_rte[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_rte, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_rte, 2);
	HAL_Delay(5);
	uint16_t rte = rx_rte[1];
	rte = rte << 8;
	rte = rte + rx_rte[0];
	uint8_t send_specific_rte[16]={'s','1','M','S','I','R','T','S',rx_rte[1],rx_rte[0],'R','T','F','I','E','e'};

	// Test
//	uint8_t send_specific_rte[14];
//	send_specific_rte[0]='1';
//	send_specific_rte[1]='M';
//	send_specific_rte[2]='S';
//	send_specific_rte[3]='I';
//	send_specific_rte[4]='R';
//	send_specific_rte[5]='T';
//	send_specific_rte[6]='S';
//	send_specific_rte[7]=rx_rte[1];
//	send_specific_rte[8]=rx_rte[0];
//	send_specific_rte[9]='R';
//	send_specific_rte[10]='T';
//	send_specific_rte[11]='S';
//	send_specific_rte[12]='I';
//	send_specific_rte[13]='E';
//
	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 16);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 16);




}


void Read_bat1_maint_Run_time_to_empty_end_of_discharge()
{

	uint8_t tx_rte[1]={0x11};	// 0x11
	uint8_t rx_rte[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_rte, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_rte, 2);
	HAL_Delay(5);
	uint16_t rte = rx_rte[1];
	rte = rte << 8;
	rte = rte + rx_rte[0];
	uint8_t send_specific_rte[16]={'s','1','M','S','I','R','T','S',rx_rte[1],rx_rte[0],'R','T','L','I','E','e'};



	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 16);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 16);


}
