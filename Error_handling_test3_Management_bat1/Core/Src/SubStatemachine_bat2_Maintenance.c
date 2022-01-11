/*
 * SubStatemachine_bat2_Maintenance.c
 *
 *  Created on: 23-Dec-2021
 *      Author: shubham
 */
// This file contains the function for Battery 2 Maintenance Use Case

#include <Results_Auto_Test_Bat2_Maintenance.h>
#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "bat2_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include"Specific_parameters_main_BAT2.h"
#include "Battery2_Maintenance_General_Info.h"

#include "Bat2_Update_Info_during_Maintenance.h"
#include <string.h>
#include "SubStatemachine_bat2_Maintenance.h"

extern bool _bat2timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat2_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat2_counter_var ;				//   Variable as a counter
//extern int8_t bat2_state;  						// Indicates the current state in Maintenance cycle
extern uint8_t BAT2_MAINT_STATE;

extern uint16_t BAT_2_ASOC_MAINTENANCE;
extern uint16_t BAT2_VOLTAGE_MAINTENANCE;

extern bool bat2charge ;				// Flag to start and stop charging of the battery
extern bool bat2discharge ;				// Flag to start and stop discharging of the battery

extern bool bat2_maint_state1guard ;
extern bool bat2_maint_state2guard ;
extern bool bat2_maint_state3guard ;
extern bool bat2_maint_state4guard ;
extern bool bat2_maint_state5guard ;
extern bool bat2_maint_state6guard ;
extern bool bat2_maint_state7guard ;
extern bool bat2_maint_state8guard ;

extern bool Bat2_Maint_Autotestflag ;

extern bool BAT_2_MAINTENANCE_FLAG ;  				// Flag for battery 1 to enter the maintenance process
extern bool BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG ;

extern bool BAT_2_MAINT_GENERAL_INFO_FLAG ;
extern bool BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG ;    // Flag to display General Info only once

extern bool Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG;   // Flag to compare specific Info only once

extern uint16_t bat2_geninfo_cycle_counter ;
extern uint16_t bat2_geninfo_asoc_counter;
extern uint16_t bat2_geninfo_remainingcapacity_counter ;
extern uint16_t bat2_geninfo_voltage_counter ;
extern uint16_t bat2_geninfo_temperature_counter ;
extern uint16_t bat2_geninfo_batterystatus_counter ;
extern uint16_t bat2_geninfo_current_counter;



extern bool bat2_geninfo_cycle_flag ;
extern bool bat2_geninfo_asoc_flag ;
extern bool bat2_geninfo_remainingcapacity_flag ;
extern bool bat2_geninfo_voltage_flag ;
extern bool bat2_geninfo_temperature_flag ;
extern bool bat2_geninfo_batterystatus_flag ;
extern bool bat2_geninfo_current_flag;

extern bool bat2_specific_info_rte_flag;

extern bool connect_flag;

extern bool bat2_update_maintenance_info_flag;

extern I2C_HandleTypeDef hi2c2;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;

void substatemachine_battery2_maintenance()
{

	if(BAT_2_MAINTENANCE_FLAG == true)   // Works with GUI updated periodically
	{

		if(BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG==false)
		{
		//	printf("Battery has entered Maintenance Use case \n");  // Displayed only once
			BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG = true;

		}




		if(BAT_2_MAINT_GENERAL_INFO_FLAG == true)
		{
			connect_flag = false;
			if(BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG==false)
			{
				BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG = true;

				//printf("Displayed General Info once \n");

				Transmit_Bat2_Maintenance_General_Info_to_Raspi(); // This function is working now




			}
			else if(BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG == true)
			{
				connect_flag=true;
			   // Update general info periodically // this function works
				if(bat2_update_maintenance_info_flag==true)
				{
					connect_flag=false;
				update_RemCap_during_maintenance_bat2();
				update_voltage_during_maintenance_bat2();
				update_asoc_during_maintenance_bat2();
				update_cyclecount_during_maintenance_bat2();
				update_batstatus_during_maintenance_bat2();
				update_temperature_during_maintenance_bat2();
				}

			}
		}

		if(BAT2_MAINT_STATE==0)
		{
			bat2charge = false;
			bat2discharge = false;
			gpio_func_bat2_chg_dschg();

		}

		if(Bat2_Maint_Autotestflag == true)
		{


			if(Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG ==false)
			{
				Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG = true;
			    Read_and_Compare_Specific_para_Bat2_STM_to_Pi();  // This function is also working



			}

			if(BAT2_MAINT_STATE == 0 && BAT2_MAINT_STATE !=1 && BAT2_MAINT_STATE !=2
					&& BAT2_MAINT_STATE !=3 && BAT2_MAINT_STATE !=4 && BAT2_MAINT_STATE !=5
					&& BAT2_MAINT_STATE !=6 && BAT2_MAINT_STATE !=7 && BAT2_MAINT_STATE !=8)
			{
				BAT2_MAINT_STATE = 1;
			}

			switch(BAT2_MAINT_STATE)
			{

			case 1:  // 80 % start state

				    BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
					if(BAT_2_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT2_MAINT_STATE = 2;
					}

					else if(BAT_2_ASOC_MAINTENANCE <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT2_MAINT_STATE = 3;
					}

					else if(BAT_2_ASOC_MAINTENANCE >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT2_MAINT_STATE = 4;
					}


				break;

			case 2:    // = 80 % state

				if(bat2_maint_state2guard == false)
				{
					bat2charge = false;
					bat2discharge = false;
					gpio_func_bat2_chg_dschg();
					_bat2timerfunc = true;
					bat2_maint_state2guard = true;
				}

				else if(bat2_maint_state2guard == true)
				{
					if(_bat2_15min_wait_over==true)
					{

//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat2_update_maintenance_info_flag=false;
						Read_Bat2_Maint_autotest_result_first_80_percent(); // This function works
						BAT2_MAINT_STATE = 5;
						bat2_maint_state2guard = false;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);
						bat2_update_maintenance_info_flag=true;
					}
				}

				break;

			case 3:    // <80 % state

				if(bat2_maint_state3guard == false)
				{
					bat2charge = true;
					bat2discharge = false;
					gpio_func_bat2_chg_dschg();
					bat2_maint_state3guard = true;
				}

				else if(bat2_maint_state3guard == true)
				{
					BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
					if(BAT_2_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT2_MAINT_STATE = 2;
						bat2_maint_state3guard = false;
					}
				}
				break;




			case 4:   // > 80 % state
				if(bat2_maint_state4guard == false)
				{
					bat2discharge = true;
					bat2charge = false;
					gpio_func_bat2_chg_dschg();
					bat2_maint_state4guard = true;
				}

				else if(bat2_maint_state4guard == true)
				{
					BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
					if(BAT_2_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT2_MAINT_STATE = 2;
						bat2_maint_state4guard = false;
					}
				}
				break;

			case 5:   // Discharge to 10 %

				if(bat2_maint_state5guard==false)
				{
					bat2discharge = true;
					bat2charge = false;
					gpio_func_bat2_chg_dschg();
					bat2_maint_state5guard = true;
					_bat2timerfunc=false;
					_bat2_15min_wait_over=false;
					_bat2_counter_var = 0;

				}

				else if(bat2_maint_state5guard==true)
				{


					BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();



					if(BAT_2_ASOC_MAINTENANCE==79 && bat2_specific_info_rte_flag==true)
					{
						Read_bat2_maint_Run_time_to_empty_start_of_discharge();
						bat2_specific_info_rte_flag=false;
					}


					if(BAT_2_ASOC_MAINTENANCE ==BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
					{

						BAT2_MAINT_STATE = 6;
						bat2_maint_state5guard=false;
					}

				}
				break;

			case 6:  // ASOC = 10% state
				if(bat2_maint_state6guard==false)
				{
					bat2charge=false;
					bat2discharge=false;
					gpio_func_bat2_chg_dschg();
					_bat2timerfunc=true;
					bat2_maint_state6guard=true;
					Read_bat2_maint_Run_time_to_empty_end_of_discharge();  // RTE
				}
				else if(bat2_maint_state6guard==true)
				{

					if(_bat2_15min_wait_over==true)
					{


//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat2_update_maintenance_info_flag=false;
						Read_Bat2_Maint_autotest_result_middle_10_percent();
						BAT2_MAINT_STATE=7;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);
						bat2_update_maintenance_info_flag=true;
						bat2_maint_state6guard=false;
					}
				}
				break;

			case 7:  // Again charge to 80 % state
				if(bat2_maint_state7guard == false)
				{
					bat2charge=true;
					bat2discharge=false;
					gpio_func_bat2_chg_dschg();
					bat2_maint_state7guard = true;
					_bat2timerfunc = false;
					_bat2_15min_wait_over=false;
					_bat2_counter_var = 0;
				}
				else if(bat2_maint_state7guard==true)
				{
					BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
					if(BAT_2_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
					{
						BAT2_MAINT_STATE=8;
						bat2_maint_state7guard=false;
					}
				}
				break;

			case 8:
				if(bat2_maint_state8guard==false)
				{
					bat2discharge=false;
					bat2charge=false;
					gpio_func_bat2_chg_dschg();
					_bat2timerfunc=true;
					bat2_maint_state8guard=true;

				}
				else if(bat2_maint_state8guard==true)
				{
					if(_bat2_15min_wait_over==true)
					{
//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat2_update_maintenance_info_flag=false;
	          Read_Bat2_Maint_autotest_result_last_80_percent();
	          bat2_maint_state8guard=false;

						_bat2timerfunc=false;
						_bat2_15min_wait_over=false;
						_bat2_counter_var = 0;
						Bat2_Maint_Autotestflag = false;
						BAT_2_MAINTENANCE_FLAG = false;
						BAT_2_MAINT_GENERAL_INFO_FLAG = false;

						BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG=false;
						BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG=false;

						Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
						bat2_specific_info_rte_flag=true;

					//	printf("Auotest is finished\n");
						BAT2_MAINT_STATE=0;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);
					//	bat2_update_maintenance_info_flag=true;
						connect_flag = true;

					}
				}
				break;

			default:
				BAT2_MAINT_STATE = 0;
				break;
			}

		}   // End of Autotest

	}   // end of maintenance





}

// Test

//		if(BAT_2_MAINTENANCE_FLAG == true)   // Works with GUI updated periodically
//		{
//
//			if(BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG==false)
//			{
//				printf("Battery has entered Maintenance Use case \n");  // Displayed only once
//				BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG = true;
//
//			}
//
//
//
//
//			if(BAT_2_MAINT_GENERAL_INFO_FLAG == true)
//			{
//				connect_flag = false;
//				if(BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG==false)
//				{
//					BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG = true;
//
//					//printf("Displayed General Info once \n");
//
//					Transmit_Bat2_Maintenance_General_Info_to_Raspi(); // This function is working now
//
//
//
//
//				}
//				else if(BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG == true)
//				{
//					connect_flag=true;
//				   // Update general info periodically // this function works
//					if(bat2_update_maintenance_info_flag==true)
//					{
//						connect_flag=false;
//					update_RemCap_during_maintenance_bat2();
//					update_voltage_during_maintenance_bat2();
//					update_asoc_during_maintenance_bat2();
//					update_cyclecount_during_maintenance_bat2();
//					update_batstatus_during_maintenance_bat2();
//					update_temperature_during_maintenance_bat2();
//					}
//
//				}
//			}
//
//			if(BAT2_MAINT_STATE==0)
//			{
//				bat2charge = false;
//				bat2discharge = false;
//				gpio_func_bat2_chg_dschg();
//
//			}
//
//			if(Bat2_Maint_Autotestflag == true)
//			{
//
//
//				if(Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG ==false)
//				{
//					Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG = true;
//				    Read_and_Compare_Specific_para_Bat2_STM_to_Pi();  // This function is also working
//
//
//
//				}
//
//				if(BAT2_MAINT_STATE == 0 && BAT2_MAINT_STATE !=1 && BAT2_MAINT_STATE !=2
//						&& BAT2_MAINT_STATE !=3 && BAT2_MAINT_STATE !=4 && BAT2_MAINT_STATE !=5
//						&& BAT2_MAINT_STATE !=6 && BAT2_MAINT_STATE !=7 && BAT2_MAINT_STATE !=8)
//				{
//					BAT2_MAINT_STATE = 1;
//				}
//
//				switch(BAT2_MAINT_STATE)
//				{
//
//				case 1:  // 80 % start state
//
//					    BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
//						if(BAT_2_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//						{
//							BAT2_MAINT_STATE = 2;
//						}
//
//						else if(BAT_2_ASOC_MAINTENANCE <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//						{
//							BAT2_MAINT_STATE = 3;
//						}
//
//						else if(BAT_2_ASOC_MAINTENANCE >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//						{
//							BAT2_MAINT_STATE = 4;
//						}
//
//
//					break;
//
//				case 2:    // = 80 % state
//
//					if(bat2_maint_state2guard == false)
//					{
//						bat2charge = false;
//						bat2discharge = false;
//						gpio_func_bat2_chg_dschg();
//						_bat2timerfunc = true;
//						bat2_maint_state2guard = true;
//					}
//
//					else if(bat2_maint_state2guard == true)
//					{
//						if(_bat2_15min_wait_over==true)
//						{
//
//							HAL_TIM_Base_Stop_IT(&htim2);
//							HAL_TIM_Base_Stop_IT(&htim3);
//							bat2_update_maintenance_info_flag=false;
//							Read_Bat2_Maint_autotest_result_first_80_percent(); // This function works
//							BAT2_MAINT_STATE = 5;
//							bat2_maint_state2guard = false;
//							HAL_TIM_Base_Start_IT(&htim2);
//							HAL_TIM_Base_Start_IT(&htim3);
//							bat2_update_maintenance_info_flag=true;
//						}
//					}
//
//					break;
//
//				case 3:    // <80 % state
//
//					if(bat2_maint_state3guard == false)
//					{
//						bat2charge = true;
//						bat2discharge = false;
//						gpio_func_bat2_chg_dschg();
//						bat2_maint_state3guard = true;
//					}
//
//					else if(bat2_maint_state3guard == true)
//					{
//						BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
//						if(BAT_2_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//						{
//							BAT2_MAINT_STATE = 2;
//							bat2_maint_state3guard = false;
//						}
//					}
//					break;
//
//
//
//
//				case 4:   // > 80 % state
//					if(bat2_maint_state4guard == false)
//					{
//						bat2discharge = true;
//						bat2charge = false;
//						gpio_func_bat2_chg_dschg();
//						bat2_maint_state4guard = true;
//					}
//
//					else if(bat2_maint_state4guard == true)
//					{
//						BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
//						if(BAT_2_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//						{
//							BAT2_MAINT_STATE = 2;
//							bat2_maint_state4guard = false;
//						}
//					}
//					break;
//
//				case 5:   // Discharge to 10 %
//
//					if(bat2_maint_state5guard==false)
//					{
//						bat2discharge = true;
//						bat2charge = false;
//						gpio_func_bat2_chg_dschg();
//						bat2_maint_state5guard = true;
//						_bat2timerfunc=false;
//						_bat2_15min_wait_over=false;
//						_bat2_counter_var = 0;
//
//					}
//
//					else if(bat2_maint_state5guard==true)
//					{
//
//
//						BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
//
//
//
//						if(BAT_2_ASOC_MAINTENANCE==83 && bat2_specific_info_rte_flag==true)
//						{
//							Read_bat2_maint_Run_time_to_empty_start_of_discharge();
//							bat2_specific_info_rte_flag=false;
//						}
//
//
//						if(BAT_2_ASOC_MAINTENANCE ==BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
//						{
//
//							BAT2_MAINT_STATE = 6;
//							bat2_maint_state5guard=false;
//						}
//
//					}
//					break;
//
//				case 6:  // ASOC = 10% state
//					if(bat2_maint_state6guard==false)
//					{
//						bat2charge=false;
//						bat2discharge=false;
//						gpio_func_bat2_chg_dschg();
//						_bat2timerfunc=true;
//						bat2_maint_state6guard=true;
//						Read_bat2_maint_Run_time_to_empty_end_of_discharge();  // RTE
//					}
//					else if(bat2_maint_state6guard==true)
//					{
//
//						if(_bat2_15min_wait_over==true)
//						{
//
//
//							HAL_TIM_Base_Stop_IT(&htim2);
//							HAL_TIM_Base_Stop_IT(&htim3);
//							bat2_update_maintenance_info_flag=false;
//							Read_Bat2_Maint_autotest_result_middle_10_percent();
//							BAT2_MAINT_STATE=7;
//							HAL_TIM_Base_Start_IT(&htim2);
//							HAL_TIM_Base_Start_IT(&htim3);
//							bat2_update_maintenance_info_flag=true;
//							bat2_maint_state6guard=false;
//						}
//					}
//					break;
//
//				case 7:  // Again charge to 80 % state
//					if(bat2_maint_state7guard == false)
//					{
//						bat2charge=true;
//						bat2discharge=false;
//						gpio_func_bat2_chg_dschg();
//						bat2_maint_state7guard = true;
//						_bat2timerfunc = false;
//						_bat2_15min_wait_over=false;
//						_bat2_counter_var = 0;
//					}
//					else if(bat2_maint_state7guard==true)
//					{
//						BAT_2_ASOC_MAINTENANCE = read_bat2_asoc();
//						if(BAT_2_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
//						{
//							BAT2_MAINT_STATE=8;
//							bat2_maint_state7guard=false;
//						}
//					}
//					break;
//
//				case 8:
//					if(bat2_maint_state8guard==false)
//					{
//						bat2discharge=false;
//						bat2charge=false;
//						gpio_func_bat2_chg_dschg();
//						_bat2timerfunc=true;
//						bat2_maint_state8guard=true;
//
//					}
//					else if(bat2_maint_state8guard==true)
//					{
//						if(_bat2_15min_wait_over==true)
//						{
//							HAL_TIM_Base_Stop_IT(&htim2);
//							HAL_TIM_Base_Stop_IT(&htim3);
//							bat2_update_maintenance_info_flag=false;
//		          Read_Bat2_Maint_autotest_result_last_80_percent();
//		          bat2_maint_state8guard=false;
//
//							_bat2timerfunc=false;
//							_bat2_15min_wait_over=false;
//							_bat2_counter_var = 0;
//							Bat2_Maint_Autotestflag = false;
//							BAT_2_MAINTENANCE_FLAG = false;
//							BAT_2_MAINT_GENERAL_INFO_FLAG = false;
//
//							BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG=false;
//							BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG=false;
//
//							Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
//							bat2_specific_info_rte_flag=true;
//
//							printf("Auotest is finished\n");
//							BAT2_MAINT_STATE=0;
//							HAL_TIM_Base_Start_IT(&htim2);
//							HAL_TIM_Base_Start_IT(&htim3);
//						//	bat2_update_maintenance_info_flag=true;
//							connect_flag = true;
//
//						}
//					}
//					break;
//
//				default:
//					BAT2_MAINT_STATE = 0;
//					break;
//				}
//
//			}   // End of Autotest
//
//		}   // end of maintenance


