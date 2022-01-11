/*
 * Bat3_Update_Info_during_Management.h
 *
 *  Created on: Jan 10, 2022
 *      Author: shubham
 */

#ifndef INC_BAT3_UPDATE_INFO_DURING_MANAGEMENT_H_
#define INC_BAT3_UPDATE_INFO_DURING_MANAGEMENT_H_

#include "stm32f7xx_hal.h"

void update_voltage_during_management_bat3();
void update_asoc_during_management_bat3();
void update_RemCap_during_management_bat3();
void update_cyclecount_during_management_bat3();
void update_batstatus_during_management_bat3();
void update_temperature_during_management_bat3();
void update_current_during_management_bat3();

#endif /* INC_BAT3_UPDATE_INFO_DURING_MANAGEMENT_H_ */
