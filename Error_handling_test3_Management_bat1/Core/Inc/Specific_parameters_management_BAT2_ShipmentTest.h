/*
 * Specific_parameters_management_BAT2_ShipmentTest.h
 *
 *  Created on: Jan 8, 2022
 *      Author: shubham
 */

#ifndef INC_SPECIFIC_PARAMETERS_MANAGEMENT_BAT2_SHIPMENTTEST_H_
#define INC_SPECIFIC_PARAMETERS_MANAGEMENT_BAT2_SHIPMENTTEST_H_

#include "stm32f7xx_hal.h"

void Read_and_Compare_Specific_para_Bat2_Management_Shipment_Test_STM_to_Pi();
void Compare_Specifi_para_Bat2_Management_Shipment_Test(uint16_t , uint16_t, uint16_t);

void Read_bat2_management_Run_time_to_empty_Shipment_Test_Cycle_start_of_discharge();
void Read_bat2_management_Run_time_to_empty_Shipment_Test_Cycle_end_of_discharge();


#endif /* INC_SPECIFIC_PARAMETERS_MANAGEMENT_BAT2_SHIPMENTTEST_H_ */
