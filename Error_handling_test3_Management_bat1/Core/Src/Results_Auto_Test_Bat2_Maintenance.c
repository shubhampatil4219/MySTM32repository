/*
 * Results_Auto_Test_Bat2_Maintenance.c
 *
 *  Created on: Dec 21, 2021
 *      Author: shubham
 */




#include <Results_Auto_Test_Bat2_Maintenance.h>
#include "stm32f7xx_hal.h"

#include "timer_delay.h"
#include "stdio.h"
#include "stdbool.h"

extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart2;



 extern int _write(int file, char *ptr, int len);

void Read_Bat2_Maint_autotest_result_first_80_percent()
{


	uint8_t tx_asoc_auto[1] ={0x0E}; 					// 0x0E   Command to get ASOC of the battery
	 uint8_t tx_voltage_auto[1] = {0x09};				// 0x09   Command to get battery voltage
	 uint8_t tx_temperature_auto[1]={0x08};			        // 0x08
	 uint8_t tx_battery_status_auto[1]={0x16};		            // 0x16
	 uint8_t tx_remaining_capacity_auto[1]={0x0F};	             // 0x0F
	 uint8_t tx_cyclecount_auto[1]={0x17};			         // 0x17




//
//
//			// Cycle Count
//
			uint8_t rx_cyclecount[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_cyclecount_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_cyclecount, 2);
			HAL_Delay(5);
			uint8_t send_cycount[16]={'s','2','M','R','F','8','C','C',rx_cyclecount[1],rx_cyclecount[0],'C','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_cycount, 16);
//
//
//
//			// Cycle Count
//
//			// Remaining Capacity
//
			uint8_t rx_remcapacity[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_remaining_capacity_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_remcapacity, 2);
			HAL_Delay(5);
			uint8_t send_remcap[16]={'s','2','M','R','F','8','R','C',rx_remcapacity[1],rx_remcapacity[0],'R','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_remcap, 16);
//
//
//			// Remaining Capacity
//
//			// ASOC
			uint8_t rx_asoc[1]={0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_asoc_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_asoc, 1);
			HAL_Delay(5);
			uint8_t send_asoc[16]={'s','2','M','R','F','8','A','S',rx_asoc[0],'A','S','E','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_asoc, 16);



			// ASOC

			// Voltage

			uint8_t rx_voltage[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_voltage_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_voltage, 2);
			HAL_Delay(5);
			uint8_t send_voltage[16]={'s','2','M','R','F','8','V','T',rx_voltage[1],rx_voltage[0],'V','T','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_voltage, 16);


			// Voltage

			// Temperature

			uint8_t	rx_temperature[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_temperature_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_temperature, 2);
			HAL_Delay(5);
			uint8_t send_temp[16]={'s','2','M','R','F','8','T','P',rx_temperature[1],rx_temperature[0],'T','P','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_temp, 16);
//
//
//			// Temperature
//
//			//Add battery status
//
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_battery_status_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_batstatus, 2);
			HAL_Delay(5);
			uint8_t send_battery_status[16]={'s','2','M','R','F','8','B','S',rx_batstatus[1],rx_batstatus[0],'B','S','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);  // Transmitted 2 times because data was not
																	 // received correctly first time on the side of QT
																	// This behaviour is unknown for now.
																	// Using printf() command the data was printed on the serial
																	// console and the battery status was correctly printed.







}










void Read_Bat2_Maint_autotest_result_middle_10_percent()
{

	uint8_t tx_asoc_auto[1] ={0x0E}; 					// 0x0E   Command to get ASOC of the battery
	 uint8_t tx_voltage_auto[1] = {0x09};				// 0x09   Command to get battery voltage
	 uint8_t tx_temperature_auto[1]={0x08};			        // 0x08
	 uint8_t tx_battery_status_auto[1]={0x16};		            // 0x16
	 uint8_t tx_remaining_capacity_auto[1]={0x0F};	             // 0x0F
	 uint8_t tx_cyclecount_auto[1]={0x17};			         // 0x17




//
//
//			// Cycle Count
//
			uint8_t rx_cyclecount[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_cyclecount_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_cyclecount, 2);
			HAL_Delay(5);
			uint8_t send_cycount[16]={'s','2','M','R','M','1','C','C',rx_cyclecount[1],rx_cyclecount[0],'C','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_cycount, 16);
//
//
//
//			// Cycle Count
//
//			// Remaining Capacity
//
			uint8_t rx_remcapacity[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_remaining_capacity_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_remcapacity, 2);
			HAL_Delay(5);
			uint8_t send_remcap[16]={'s','2','M','R','M','1','R','C',rx_remcapacity[1],rx_remcapacity[0],'R','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_remcap, 16);
//
//
//			// Remaining Capacity
//
//			// ASOC
			uint8_t rx_asoc[1]={0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_asoc_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_asoc, 1);
			HAL_Delay(5);
			uint8_t send_asoc[16]={'s','2','M','R','M','1','A','S',rx_asoc[0],'A','S','E','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_asoc, 16);



			// ASOC

			// Voltage

			uint8_t rx_voltage[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_voltage_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_voltage, 2);
			HAL_Delay(5);
			uint8_t send_voltage[16]={'s','2','M','R','M','1','V','T',rx_voltage[1],rx_voltage[0],'V','T','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_voltage, 16);


			// Voltage

			// Temperature

			uint8_t	rx_temperature[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_temperature_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_temperature, 2);
			HAL_Delay(5);
			uint8_t send_temp[16]={'s','2','M','R','M','1','T','P',rx_temperature[1],rx_temperature[0],'T','P','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_temp, 16);
//
//
//			// Temperature
//
//			//Add battery status
//
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_battery_status_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_batstatus, 2);
			HAL_Delay(5);
			uint8_t send_battery_status[16]={'s','2','M','R','M','1','B','S',rx_batstatus[1],rx_batstatus[0],'B','S','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);  // Transmitted 2 times because data was not
																	 // received correctly first time


}
//
//
//
//
void Read_Bat2_Maint_autotest_result_last_80_percent()
{


	uint8_t tx_asoc_auto[1] ={0x0E}; 					// 0x0E   Command to get ASOC of the battery
	 uint8_t tx_voltage_auto[1] = {0x09};				// 0x09   Command to get battery voltage
	 uint8_t tx_temperature_auto[1]={0x08};			        // 0x08
	 uint8_t tx_battery_status_auto[1]={0x16};		            // 0x16
	 uint8_t tx_remaining_capacity_auto[1]={0x0F};	             // 0x0F
	 uint8_t tx_cyclecount_auto[1]={0x17};			         // 0x17




//
//
//			// Cycle Count
//
			uint8_t rx_cyclecount[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_cyclecount_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_cyclecount, 2);
			HAL_Delay(5);
			uint8_t send_cycount[16]={'s','2','M','R','L','8','C','C',rx_cyclecount[1],rx_cyclecount[0],'C','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_cycount, 16);
//
//
//
//			// Cycle Count
//
//			// Remaining Capacity
//
			uint8_t rx_remcapacity[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_remaining_capacity_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_remcapacity, 2);
			HAL_Delay(5);
			uint8_t send_remcap[16]={'s','2','M','R','L','8','R','C',rx_remcapacity[1],rx_remcapacity[0],'R','C','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_remcap, 16);
//
//
//			// Remaining Capacity
//
//			// ASOC
			uint8_t rx_asoc[1]={0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_asoc_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_asoc, 1);
			HAL_Delay(5);
			uint8_t send_asoc[16]={'s','2','M','R','L','8','A','S',rx_asoc[0],'A','S','E','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_asoc, 16);



			// ASOC

			// Voltage

			uint8_t rx_voltage[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16, tx_voltage_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_voltage, 2);
			HAL_Delay(5);
			uint8_t send_voltage[16]={'s','2','M','R','L','8','V','T',rx_voltage[1],rx_voltage[0],'V','T','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_voltage, 16);


			// Voltage

			// Temperature

			uint8_t	rx_temperature[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_temperature_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_temperature, 2);
			HAL_Delay(5);
			uint8_t send_temp[16]={'s','2','M','R','L','8','T','P',rx_temperature[1],rx_temperature[0],'T','P','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_temp, 16);
//
//
//			// Temperature
//
//			//Add battery status
//
			uint8_t rx_batstatus[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c2, 0x16,tx_battery_status_auto, 1);
			HAL_Delay(5);
			HAL_I2C_Master_Receive_IT(&hi2c2, 0x16, rx_batstatus, 2);
			HAL_Delay(5);
			uint8_t send_battery_status[16]={'s','2','M','R','L','8','B','S',rx_batstatus[1],rx_batstatus[0],'B','S','E','N','D','e'};
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, send_battery_status, 16);  // Transmitted 2 times because data was not
																	 // received correctly first time





}







