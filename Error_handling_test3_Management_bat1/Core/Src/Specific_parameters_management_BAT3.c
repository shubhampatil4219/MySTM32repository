/*
 * Specific_parameters_management_BAT3.c
 *
 *  Created on: Jan 10, 2022
 *      Author: shubham
 */






#include "stm32f7xx_hal.h"

#include "Specific_parameters_management_BAT3.h"
#include "timer_delay.h"
#include "stdio.h"
#include "stdbool.h"





extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef huart2;

void Send_Bat3_Management_Specific_Info_To_Pi()
{

	uint8_t tx_bat3_device_chem[1]={0x22};  // Device Chemistry
	uint8_t rx_bat3_device_chem[5]={0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_bat3_device_chem, 1);
	HAL_Delay(5);
	HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_bat3_device_chem, 5);
	HAL_Delay(1);
	uint8_t send_specific_devchem[16]={'s','3','N','S','I','D','C','M',rx_bat3_device_chem[1],rx_bat3_device_chem[2],rx_bat3_device_chem[3],rx_bat3_device_chem[4],'S','I','E','e'};
	HAL_UART_Transmit_IT(&huart2, send_specific_devchem, 16);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart2, send_specific_devchem, 16);

}
