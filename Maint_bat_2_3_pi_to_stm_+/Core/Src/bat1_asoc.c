/*
 * bat1_asoc.c
 *
 *  Created on: 15-Nov-2021
 *      Author: shubham
 */

#include "bat1_asoc.h"
#include "timer_delay.h"

//extern uint16_t BAT_1_ASOC;
extern uint16_t BAT1_VOLTAGE_MAINTENANCE;
					// 0x0E   Command to get ASOC of the battery


extern I2C_HandleTypeDef hi2c1;

int read_bat1_asoc()
{
	uint8_t rx_bat1_asoc[1]={0x00};
	uint8_t tx_asoc[1]={0x0E};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_asoc, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_bat1_asoc, 1);
	msdelay(1);
	uint16_t BAT_1_ASOC_Read = rx_bat1_asoc[0];
	rx_bat1_asoc[0]=0;


	uint8_t tx_voltage[1]={0x09};
	uint8_t rx_bat1_volt[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_voltage, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_bat1_volt, 2);
	msdelay(1);
	BAT1_VOLTAGE_MAINTENANCE = rx_bat1_volt[1];
	BAT1_VOLTAGE_MAINTENANCE = BAT1_VOLTAGE_MAINTENANCE << 8;
	BAT1_VOLTAGE_MAINTENANCE = BAT1_VOLTAGE_MAINTENANCE + rx_bat1_volt[0];
	rx_bat1_volt[0]=0;
	rx_bat1_volt[1]=0;

	return BAT_1_ASOC_Read;

}
