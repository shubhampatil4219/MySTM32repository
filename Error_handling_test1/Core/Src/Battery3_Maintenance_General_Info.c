/*
 * Battery3_Maintenance_General_Info.c
 *
 *  Created on: 23-Dec-2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "Battery3_Maintenance_General_Info.h"
#include "stdio.h"
#include "timer_delay.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c3;

// This function works
void Transmit_Bat3_Maintenance_General_Info_to_Raspi()
{

	// GI function starts From here

		uint8_t tx_serial_number_gen[1]={0x1C};  // Serial No
		uint8_t rx_serial_no[2]={0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_serial_number_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_serial_no, 2);
		HAL_Delay(1);
		uint16_t sn = rx_serial_no[1];
		sn = sn << 8;
		sn = sn + rx_serial_no[0];
		uint8_t send_serial_no[16]={'s','3','M','G','I','S','N','S',rx_serial_no[1],rx_serial_no[0],'S','N','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_serial_no, 16);

		uint8_t tx_manufacturer_date_gen[1]={0x1B}; // Maunfact date
		uint8_t rx_manuf_date[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_manufacturer_date_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_manuf_date, 2);
		HAL_Delay(1);
		uint16_t val=rx_manuf_date[1];
		val = val << 8;
		val = val + rx_manuf_date[0];
		//	uint16_t d= 0x001F & val;
		//	uint16_t m = 0x01E0 & val;
		//	m=m>>5;
		//	uint16_t y=0xFE00 & val;
		//	y=y>>9;
		//	y=y+1980;
		uint8_t send_manuf_date[16]={'s','3','M','G','I','M','D','S',rx_manuf_date[1],rx_manuf_date[0],'M','D','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_manuf_date, 16);



		uint8_t tx_cyclecount_gen[1]={0x17}; // CycleCount
		uint8_t rx_cyclecount[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_cyclecount_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_cyclecount, 2);
		HAL_Delay(1);
		uint16_t cc = rx_cyclecount[1];
		cc = cc << 8;
		cc = cc + rx_cyclecount[0];
		uint8_t send_cyclecount[16]={'s','3','M','G','I','C','C','S',rx_cyclecount[1],rx_cyclecount[0],'C','C','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_cyclecount, 16);



		uint8_t tx_remaining_capacity_gen[1]={0x0F};  // Remaining Capacity
		uint8_t rx_remcapacity[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_remaining_capacity_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_remcapacity, 2);
		HAL_Delay(1);
		uint16_t rc = rx_remcapacity[1];
		rc = rc << 8;
		rc = rc + rx_remcapacity[0];
		uint8_t send_remain_capcacity[16]={'s','3','M','G','I','R','C','S',rx_remcapacity[1],rx_remcapacity[0],'R','C','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_remain_capcacity, 16);



		uint8_t tx_voltage_gen[1]={0x09};    // Voltage
		uint8_t rx_voltage[2];
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_voltage_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_voltage, 2);
		HAL_Delay(1);
		uint16_t vt = rx_voltage[1];
		vt = vt << 8;
		vt = vt + rx_voltage[0];
		printf("\nVolatge in main function = %d",vt);

		uint8_t send[16]={'s','3','M','G','I','V','T','S',rx_voltage[1],rx_voltage[0],'V','T','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send, 16);


		uint8_t rx_asoc[1]={0x00};        // ASOC
		uint8_t tx_asoc_gen[1]={0x0E};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16, tx_asoc_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_asoc, 1);
		HAL_Delay(1);
		uint8_t as=rx_asoc[0];
		uint8_t send_asoc[16]={'s','3','M','G','I','A','S','S',rx_asoc[0],'A','S','E','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_asoc, 16);


		uint8_t tx_temperature_gen[1]={0x08};  // Temperature
		uint8_t	rx_temperature[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_temperature_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_temperature, 2);
		HAL_Delay(1);
		uint16_t tp = rx_temperature[1];
		tp = tp << 8;
		tp = tp + rx_temperature[0];
		uint8_t send_temp[16]={'s','3','M','G','I','T','P','S',rx_temperature[1],rx_temperature[0],'T','P','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_temp, 16);



		uint8_t tx_battery_status_gen[1]={0x16}; // Battery Status
		uint8_t rx_batstatus[2]={0x00,0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c3, 0x16,tx_battery_status_gen, 1);
		HAL_Delay(5);
		HAL_I2C_Master_Receive_IT(&hi2c3, 0x16, rx_batstatus, 2);
		HAL_Delay(1);
		uint16_t bs = rx_batstatus[1];
		bs = bs << 8;
		bs = bs + rx_batstatus[0];
		uint8_t send_bat_status[16]={'s','3','M','G','I','B','S','S',rx_batstatus[1],rx_batstatus[0],'B','S','G','I','E','e'};
		HAL_UART_Transmit_IT(&huart2, send_bat_status, 16);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&huart2, send_bat_status, 16);

//		uint8_t tx_battery_status_gen2[1]={0x16}; // Battery Status
//		uint8_t rx_batstatus2[2]={0x00,0x00};
//		HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_battery_status_gen2, 1);
//		HAL_Delay(5);
//		HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_batstatus2, 2);
//		HAL_Delay(1);
//		uint16_t bs2 = rx_batstatus2[1];
//		bs2 = bs2 << 8;
//		bs2 = bs2 + rx_batstatus2[0];
//		uint8_t send_bat_status2[14]={'2','M','G','I','B','S','S',rx_batstatus2[1],rx_batstatus2[0],'B','S','G','I','E'};
//		HAL_UART_Transmit_IT(&huart2, send_bat_status2, 14);








}
