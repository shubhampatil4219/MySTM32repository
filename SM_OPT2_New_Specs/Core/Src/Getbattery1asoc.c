///*
// * Getbattery1asoc.c
// *
// *  Created on: Nov 11, 2021
// *      Author: shubham
// */
//
//#include "stm32f7xx_hal.h"
//#include "timer_delay.h"
////#include "Variable_defintions.h"
//
//extern uint8_t tx_asoc[1]; 			// Command to get ASOC of the battery
//extern uint8_t rx_asoc[1];
//extern uint8_t tx_voltage[1];			// Command to get battery voltage
//extern uint8_t rx_voltage[2];
//extern uint16_t voltage_bat_1;
//extern uint16_t BAT_1_ASOC_VALUE;
//
//extern I2C_HandleTypeDef hi2c1;
//
//void getbattery1asoc()
//{
//
//			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_voltage, 1);
//			msdelay(5);
//			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_voltage, 2);
//			msdelay(1);
//			voltage_bat_1 = rx_voltage[1];
//			voltage_bat_1 = voltage_bat_1 << 8;
//			voltage_bat_1 = voltage_bat_1 + rx_voltage[0];
//			rx_voltage[0]=0;
//			rx_voltage[1]=0;
//
//			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_asoc, 1);
//			msdelay(5);
//			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_asoc, 1);
//			msdelay(1);
//			BAT_1_ASOC_VALUE= rx_asoc[0];
//			rx_asoc[0]=0;
//
//
//}
