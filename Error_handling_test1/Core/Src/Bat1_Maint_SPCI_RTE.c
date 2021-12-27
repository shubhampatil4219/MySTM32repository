/*
 * Bat1_Maint_SPCI_RTE.c
 *
 *  Created on: 16-Dec-2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"

#include "Bat1_Maint_SPCI_RTE.h"



extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;


void read_battery1_maint_specific_info_RTE()
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
	uint8_t send_specific_rte[14]={'1','M','S','I','R','T','S',rx_rte[1],rx_rte[0],'R','T','S','I','E'};

	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 14);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart2, send_specific_rte, 14);


}
