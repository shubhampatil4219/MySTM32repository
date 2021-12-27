/*
 * SubStatemachine_bat1_Maintenance.c
 *
 *  Created on: 20-Dec-2021
 *      Author: shubham
 */
//This file contains the function for Battery 2 Maintenance Use Case

#include <Results_Auto_Test_Bat1_Maintenance.h>
#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "bat1_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include"Specific_parameters_main_BAT1.h"
#include "Battery1_Maintenance_General_Info.h"
#include "Battery1_Maintenance_Specific_Info.h"
#include "Bat1_Update_Info_during_Maintenance.h"
#include <string.h>
#include "Bat1_Maint_SPCI_RTE.h"
#include "SubStatemachine_bat1_Maintenance.h"

extern bool _bat1timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat1_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat1_counter_var ;				//   Variable as a counter
extern int8_t bat1_state;  						// Indicates the current state in Maintenance cycle
extern int8_t *BAT1_MAINT_STATE;


extern uint16_t BAT_1_ASOC_MAINTENANCE;
extern uint16_t BAT1_VOLTAGE_MAINTENANCE;

extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery

extern bool state1guard ;
extern bool state2guard ;
extern bool state3guard ;
extern bool state4guard ;
extern bool state5guard ;
extern bool state6guard ;
extern bool state7guard ;
extern bool state8guard ;

extern bool Autotestflag ;				// Flag to start automatic testing of the maintenance cycle

extern uint8_t rx_buffer[3];					// Receives command from Pi

extern bool BAT_1_MAINTENANCE_FLAG ;  				// Flag for battery 1 to enter the maintenance process
extern bool BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG ;

extern bool BAT_1_MAINT_GENERAL_INFO_FLAG ;
extern bool BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG ;    // Flag to display General Info only once

extern bool Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG;   // Flag to compare specific Info only once




// Flags to update the general information of battery in Maintenance Use Case

extern uint16_t bat1_geninfo_cycle_counter ;
extern uint16_t bat1_geninfo_asoc_counter;
extern uint16_t bat1_geninfo_remainingcapacity_counter ;
extern uint16_t bat1_geninfo_voltage_counter ;
extern uint16_t bat1_geninfo_temperature_counter ;
extern uint16_t bat1_geninfo_batterystatus_counter ;
extern uint16_t bat1_geninfo_current_counter;




extern bool bat1_geninfo_cycle_flag ;
extern bool bat1_geninfo_asoc_flag ;
extern bool bat1_geninfo_remainingcapacity_flag ;
extern bool bat1_geninfo_voltage_flag ;
extern bool bat1_geninfo_temperature_flag ;
extern bool bat1_geninfo_batterystatus_flag ;
extern bool bat1_geninfo_current_flag;

extern bool bat1_specific_info_rte_flag;

extern bool connect_flag;
extern bool update_maintenance_info_flag;

extern uint8_t tx_init[14];

extern bool rte_guard_flag;


extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;


void substatemachine_battery1_maintenance()
{



	//		// Maintenance cycle Start /////////////////////
	////
			if(BAT_1_MAINTENANCE_FLAG == true)   // Works with GUI updated periodically
			{

				if(BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG==false)
				{
				//	printf("Battery has entered Maintenance Use case \n");  // Displayed only once
					BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG = true;

				}




				if(BAT_1_MAINT_GENERAL_INFO_FLAG == true)
				{
					connect_flag = false;
					if(BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG==false)
					{
						BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG = true;

						//printf("Displayed General Info once \n");

						Transmit_Bat1_Maintenance_General_Info_to_Raspi(); // This function is working now




					}
					else if(BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG == true)
					{
						connect_flag=true;
					   // Update general info periodically // this function works
						if(update_maintenance_info_flag==true)
						{
							connect_flag=false;
						update_RemCap_during_maintenance_bat1();
						update_voltage_during_maintenance_bat1();
						update_asoc_during_maintenance_bat1();
						update_cyclecount_during_maintenance_bat1();
						update_batstatus_during_maintenance_bat1();
						update_temperature_during_maintenance_bat1();
						}

					}
				}

				if(*BAT1_MAINT_STATE==0)
				{
					bat1charge = false;
					bat1discharge = false;
					gpio_func();

				}

				if(Autotestflag == true)
				{


					if(Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG ==false)
					{
						Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG = true;
					    Read_and_Compare_Specific_para_Bat1_STM_to_Pi();  // This function is also working
					//	Send_Bat1_Maintenance_Specific_Info_To_Pi();





					}

					if(*BAT1_MAINT_STATE == 0 && *BAT1_MAINT_STATE !=1 && *BAT1_MAINT_STATE !=2
							&& *BAT1_MAINT_STATE !=3 && *BAT1_MAINT_STATE !=4 && *BAT1_MAINT_STATE !=5
							&& *BAT1_MAINT_STATE !=6 && *BAT1_MAINT_STATE !=7 && *BAT1_MAINT_STATE !=8)
					{
						*BAT1_MAINT_STATE = 1;
					}

					switch(*BAT1_MAINT_STATE)
					{

					case 1:  // 80 % start state

						BAT_1_ASOC_MAINTENANCE = read_bat1_asoc();
							if(BAT_1_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								*BAT1_MAINT_STATE = 2;
							}

							else if(BAT_1_ASOC_MAINTENANCE <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								*BAT1_MAINT_STATE = 3;
							}

							else if(BAT_1_ASOC_MAINTENANCE >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								*BAT1_MAINT_STATE = 4;
							}


						break;

					case 2:    // = 80 % state

						if(state2guard == false)
						{
							bat1charge = false;
							bat1discharge = false;
							gpio_func();
							_bat1timerfunc = true;
							state2guard = true;
						}

						else if(state2guard == true)
						{
							if(_bat1_15min_wait_over==true)
							{
							//	Bat1_result_First_80_percent_charge_Maintenance_Use_Case(); // Doesn't work
								HAL_TIM_Base_Stop_IT(&htim2);
								HAL_TIM_Base_Stop_IT(&htim3);
								update_maintenance_info_flag=false;
								Read_Bat1_Maint_autotest_result_first_80_percent(); // This function works
								*BAT1_MAINT_STATE = 5;
								state2guard = false;
								HAL_TIM_Base_Start_IT(&htim2);
								HAL_TIM_Base_Start_IT(&htim3);
								update_maintenance_info_flag=true;
							}
						}

						break;

					case 3:    // <80 % state

						if(state3guard == false)
						{
							bat1charge = true;
							bat1discharge = false;
							gpio_func();
							state3guard = true;
						}

						else if(state3guard == true)
						{
							BAT_1_ASOC_MAINTENANCE = read_bat1_asoc();
							if(BAT_1_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								*BAT1_MAINT_STATE = 2;
								state3guard = false;
							}
						}
						break;




					case 4:   // > 80 % state
						if(state4guard == false)
						{
							bat1discharge = true;
							bat1charge = false;
							gpio_func();
							state4guard = true;
						}

						else if(state4guard == true)
						{
							BAT_1_ASOC_MAINTENANCE = read_bat1_asoc();
							if(BAT_1_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								*BAT1_MAINT_STATE = 2;
								state4guard = false;
							}
						}
						break;

					case 5:   // Discharge to 10 %

						if(state5guard==false)
						{
							bat1discharge = true;
							bat1charge = false;
							gpio_func();
							state5guard = true;
							_bat1timerfunc=false;
							_bat1_15min_wait_over=false;
							_bat1_counter_var = 0;
					//		Read_bat1_maint_Run_time_to_empty(); // RTE
						}

						else if(state5guard==true)
						{


							BAT_1_ASOC_MAINTENANCE = read_bat1_asoc();



							if(BAT_1_ASOC_MAINTENANCE==79 && bat1_specific_info_rte_flag==true)
							{
								Read_bat1_maint_Run_time_to_empty();
								bat1_specific_info_rte_flag=false;
							}


							if(BAT_1_ASOC_MAINTENANCE ==BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
							{

								*BAT1_MAINT_STATE = 6;
								state5guard=false;
							}

						}
						break;

					case 6:  // ASOC = 10% state
						if(state6guard==false)
						{
							bat1charge=false;
							bat1discharge=false;
							gpio_func();
							_bat1timerfunc=true;
							state6guard=true;
							Read_bat1_maint_Run_time_to_empty_end_of_discharge();  // RTE
						}
						else if(state6guard==true)
						{

							if(_bat1_15min_wait_over==true)
							{

						//		Read_Bat1_Maint_autotest_result_middle_10_percent();
								HAL_TIM_Base_Stop_IT(&htim2);
								HAL_TIM_Base_Stop_IT(&htim3);
								update_maintenance_info_flag=false;
								Read_Bat1_Maint_autotest_result_middle_10_percent();
								*BAT1_MAINT_STATE=7;
								HAL_TIM_Base_Start_IT(&htim2);
								HAL_TIM_Base_Start_IT(&htim3);
								update_maintenance_info_flag=true;
								state6guard=false;
							}
						}
						break;

					case 7:  // Again charge to 80 % state
						if(state7guard == false)
						{
							bat1charge=true;
							bat1discharge=false;
							gpio_func();
							state7guard = true;
							_bat1timerfunc = false;
							_bat1_15min_wait_over=false;
							_bat1_counter_var = 0;
						}
						else if(state7guard==true)
						{
							BAT_1_ASOC_MAINTENANCE = read_bat1_asoc();
							if(BAT_1_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
							{
								*BAT1_MAINT_STATE=8;
								state7guard=false;
							}
						}
						break;

					case 8:
						if(state8guard==false)
						{
							bat1discharge=false;
							bat1charge=false;
							gpio_func();
							_bat1timerfunc=true;
							state8guard=true;

						}
						else if(state8guard==true)
						{
							if(_bat1_15min_wait_over==true)
							{
								HAL_TIM_Base_Stop_IT(&htim2);
								HAL_TIM_Base_Stop_IT(&htim3);
								update_maintenance_info_flag=false;
			          Read_Bat1_Maint_autotest_result_last_80_percent();
								state8guard=false;

								_bat1timerfunc=false;
								_bat1_15min_wait_over=false;
								_bat1_counter_var = 0;
								Autotestflag = false;
								BAT_1_MAINTENANCE_FLAG = false;
								BAT_1_MAINT_GENERAL_INFO_FLAG = false;

								BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG=false;
								BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG=false;
								Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
								bat1_specific_info_rte_flag=true;

								printf("Auotest is finished\n");
								*BAT1_MAINT_STATE=0;
								HAL_TIM_Base_Start_IT(&htim2);
								HAL_TIM_Base_Start_IT(&htim3);

								connect_flag = true;

							}
						}
						break;

					default:
						*BAT1_MAINT_STATE = 0;
						break;
					}

				}   // End of Autotest

			}   // end of maintenance



}


