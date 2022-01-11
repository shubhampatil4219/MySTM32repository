/*
 * Bat1_Update_Info_during_Maintenance.h
 *
 *  Created on: 07-Dec-2021
 *      Author: shubham
 */

#ifndef INC_BAT1_UPDATE_INFO_DURING_MAINTENANCE_H_
#define INC_BAT1_UPDATE_INFO_DURING_MAINTENANCE_H_

#include "stm32f7xx_hal.h"

void update_voltage_during_maintenance_bat1();
void update_asoc_during_maintenance_bat1();
void update_RemCap_during_maintenance_bat1();
void update_cyclecount_during_maintenance_bat1();
void update_batstatus_during_maintenance_bat1();
void update_temperature_during_maintenance_bat1();
void update_current_during_maintenance_bat1();



void update_periodic_flags_during_maintenance_bat1();
#endif /* INC_BAT1_UPDATE_INFO_DURING_MAINTENANCE_H_ */
