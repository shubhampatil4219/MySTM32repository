///*
// * Variable_defintions.h
// *
// *  Created on: 12-Nov-2021
// *      Author: shubham
// *      This file contains DECLARATION of the global variables
// *      Include this file in multiple source files where necessary to access the global variables
// */
//
//#ifndef INC_VARIABLE_DEFINTIONS_H_
//#define INC_VARIABLE_DEFINTIONS_H_
//
//#include "stdint.h"
//#include "stdbool.h"
//
//// Flags to update the general information of battery in Maintenance Use Case
//extern uint16_t bat1_geninfo_cycle_counter ;
//extern uint16_t bat1_geninfo_asoc_counter ;
//extern uint16_t bat1_geninfo_remainingcapacity_counter ;
//extern uint16_t bat1_geninfo_voltage_counter ;
//extern uint16_t bat1_geninfo_temperature_counter ;
//extern uint16_t bat1_geninfo_batterystatus_counter ;
//
//
//extern bool bat1_geninfo_cycle_flag ;
//extern bool bat1_geninfo_asoc_flag ;
//extern bool bat1_geninfo_remainingcapacity_flag ;
//extern bool bat1_geninfo_voltage_flag ;
//extern bool bat1_geninfo_temperature_flag ;
//extern bool bat1_geninfo_batterystatus_flag;
//// Flags to update the general information of battery in Maintenance Use Case
//
//
//// Maintenance cycle BAT 1 declarations
//
//extern bool _bat1timerfunc ;		       		// Flag to start and stop the 15 min wait function
//extern bool _bat1_15min_wait_over ;  			// To indicate 15 min delay is over
//extern uint16_t _bat1_counter_var ;				//   Variable as a counter
//extern int8_t bat1_state;  						// Indicates the current state in Maintenance cycle
//
//extern uint8_t tx_asoc[1]; 						// Command to get ASOC of the battery
//extern uint8_t rx_asoc[1];
//extern uint8_t tx_voltage[1];					// Command to get battery voltage 0x09
//extern uint8_t rx_voltage[2];
//extern uint16_t voltage_bat_1;
//extern uint16_t BAT_1_ASOC_VALUE;				// Store BAT 1 ASOC value
//
//extern bool bat1charge ;						// Flag to start and stop charging of the battery
//extern bool bat1discharge ;						// Flag to start and stop discharging of the battery
//
//extern bool state1guard ;
//extern bool state2guard ;
//extern bool state3guard ;
//extern bool state4guard ;
//extern bool state5guard ;
//extern bool state6guard ;
//extern bool state7guard ;
//
//extern bool Autotestflag ;						// Flag to start automatic testing of the maintenance cycle
//
//extern uint8_t rx_buffer[3];
//
//extern uint8_t transmit_volt[1];
//// Maintenance cycle BAT 1 definitions - End
//
//#endif /* INC_VARIABLE_DEFINTIONS_H_ */
