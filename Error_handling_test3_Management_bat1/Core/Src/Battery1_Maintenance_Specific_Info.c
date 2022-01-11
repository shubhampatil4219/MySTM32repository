/*
 * Battery1_Maintenance_Specific_Info.c
 *
 *  Created on: 06-Dec-2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "Battery1_Maintenance_Specific_Info.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

void Send_Bat1_Maintenance_Specific_Info_To_Pi()
{

	uint8_t tx_bat1_specf_battery_status[1] = {0x16};		// 0x16
	// Battery Status
	uint8_t rx_batstatus[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_bat1_specf_battery_status, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_batstatus, 2);
	msdelay(1);
	uint16_t bs = rx_batstatus[1];
	bs = bs << 8;
	bs = bs + rx_batstatus[0];
	uint8_t send_specific_batstatus[14]={'1','M','S','I','B','S','S',rx_batstatus[1],rx_batstatus[0],'B','S','S','I','E'};
	HAL_UART_Transmit_IT(&huart2, send_specific_batstatus, 14);


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

	uint8_t send_specific_fcc[14]={'1','M','S','I','F','C','S',rx_full_charge_capacity[1],rx_full_charge_capacity[0],'F','C','S','I','E'};
	HAL_UART_Transmit_IT(&huart2, send_specific_fcc, 14);
	msdelay(2);
	HAL_UART_Transmit_IT(&huart2, send_specific_fcc, 14);


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

	uint8_t send_specific_design_cap[14]={'1','M','S','I','D','C','S',rx_design_capacity[1],rx_design_capacity[0],'D','C','S','I','E'};
	HAL_UART_Transmit_IT(&huart2, send_specific_design_cap, 14);






}

void design_capacity()
{

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

	uint8_t send_specific_design_cap[14]={'1','M','S','I','D','C','S',rx_design_capacity[1],rx_design_capacity[0],'D','C','S','I','E'};
	HAL_UART_Transmit_IT(&huart2, send_specific_design_cap, 14);


}
