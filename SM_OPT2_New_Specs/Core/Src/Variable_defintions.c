///*
// * Variable_defintions.c
// *
// *  Created on: 12-Nov-2021
// *      Author: shubham
// */
//#include "Variable_defintions.h"
//#include "stm32f7xx_hal.h"
//#include "stdbool.h"
//#include "stdint.h"
//
//// Flag definitions to update the general information of battery in Maintenance Use Case
//
//uint16_t bat1_geninfo_cycle_counter = 0;
//uint16_t bat1_geninfo_asoc_counter = 0;
//uint16_t bat1_geninfo_remainingcapacity_counter = 0;
//uint16_t bat1_geninfo_voltage_counter = 0;
//uint16_t bat1_geninfo_temperature_counter = 0;
//uint16_t bat1_geninfo_batterystatus_counter = 0;
//
//
//
//
//bool bat1_geninfo_cycle_flag = false;
//bool bat1_geninfo_asoc_flag = false;
//bool bat1_geninfo_remainingcapacity_flag = false;
//bool bat1_geninfo_voltage_flag = false;
//bool bat1_geninfo_temperature_flag = false;
//bool bat1_geninfo_batterystatus_flag = false;
//
//
//
//
//// Flags to update the general information of battery in Maintenance Use Case
//
//
//// Maintenance cycle BAT 1 definitions
//
//bool _bat1timerfunc = false;				// Flag to start and stop the 15 min wait function
//bool _bat1_15min_wait_over = false;  		// To indicate 15 min delay is over
//uint16_t _bat1_counter_var = 0;				//   Variable as a counter
//int8_t bat1_state=0;  						// Indicates the current state in Maintenance cycle
//
//uint8_t tx_asoc[1]={0x0E}; 					// Command to get ASOC of the battery
//uint8_t rx_asoc[1]={0x00};
//uint8_t tx_voltage[1]={0x09};				// Command to get battery voltage 0x09
//uint8_t rx_voltage[2]={0x00};
//uint16_t voltage_bat_1;
//uint16_t BAT_1_ASOC_VALUE;
//
//bool bat1charge = false;					// Flag to start and stop charging of the battery
//bool bat1discharge = false;					// Flag to start and stop discharging of the battery
//
//bool state1guard = false;
//bool state2guard = false;
//bool state3guard = false;
//bool state4guard = false;
//bool state5guard = false;
//bool state6guard = false;
//bool state7guard = false;
//
//bool Autotestflag = true;					// Flag to start automatic testing of the maintenance cycle
//
//uint8_t rx_buffer[3];
//
//uint8_t transmit_volt[1]={0xF0};
//// Maintenance cycle BAT 1 definitions - End
