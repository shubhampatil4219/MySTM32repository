/*
 * bat2_asoc.c
 *
 *  Created on: 21-Dec-2021
 *      Author: shubham
 */



#include "bat2_asoc.h"
#include "timer_delay.h"

//extern uint16_t BAT_1_ASOC;
extern uint16_t BAT2_VOLTAGE_MAINTENANCE;
					// 0x0E   Command to get ASOC of the battery


extern I2C_HandleTypeDef hi2c2;

int read_bat2_asoc()
{
	uint8_t rx_bat2_asoc[1]={0x00};
	uint8_t tx_asoc[1]={0x0E};
	HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_asoc, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_bat2_asoc, 1);
	msdelay(1);
	uint16_t BAT_2_ASOC_Read = rx_bat2_asoc[0];
	rx_bat2_asoc[0]=0;


	uint8_t tx_voltage[1]={0x09};
	uint8_t rx_bat2_volt[2]={0x00,0x00};
	HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_voltage, 1);
	msdelay(5);
	HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_bat2_volt, 2);
	msdelay(1);
	BAT2_VOLTAGE_MAINTENANCE = rx_bat2_volt[1];
	BAT2_VOLTAGE_MAINTENANCE = BAT2_VOLTAGE_MAINTENANCE << 8;
	BAT2_VOLTAGE_MAINTENANCE = BAT2_VOLTAGE_MAINTENANCE + rx_bat2_volt[0];
	rx_bat2_volt[0]=0;
	rx_bat2_volt[1]=0;

	return BAT_2_ASOC_Read;

}

