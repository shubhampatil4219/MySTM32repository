/*
 * SubStatemachine_bat3_Maintenance.c
 *
 *  Created on: 24-Dec-2021
 *      Author: shubham
 */


// This file contains the function for Battery 3 Maintenance Use Case

#include <Results_Auto_Test_Bat3_Maintenance.h>
#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "timer_delay.h"
#include "bat3_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include"Specific_parameters_main_BAT3.h"
#include "Battery3_Maintenance_General_Info.h"

#include "Bat3_Update_Info_during_Maintenance.h"
#include <string.h>
#include "SubStatemachine_bat3_Maintenance.h"

extern bool _bat3timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat3_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat3_counter_var ;				//   Variable as a counter
//extern int8_t bat3_state;  						// Indicates the current state in Maintenance cycle
extern uint8_t BAT3_MAINT_STATE;

extern uint16_t BAT_3_ASOC_MAINTENANCE;
extern uint16_t BAT3_VOLTAGE_MAINTENANCE;

extern bool bat3charge ;				// Flag to start and stop charging of the battery
extern bool bat3discharge ;				// Flag to start and stop discharging of the battery

extern bool bat3_maint_state1guard ;
extern bool bat3_maint_state2guard ;
extern bool bat3_maint_state3guard ;
extern bool bat3_maint_state4guard ;
extern bool bat3_maint_state5guard ;
extern bool bat3_maint_state6guard ;
extern bool bat3_maint_state7guard ;
extern bool bat3_maint_state8guard ;

extern bool Bat3_Maint_Autotestflag ;

extern bool BAT_3_MAINTENANCE_FLAG ;  				// Flag for battery 1 to enter the maintenance process
extern bool BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG ;

extern bool BAT_3_MAINT_GENERAL_INFO_FLAG ;
extern bool BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG ;    // Flag to display General Info only once

extern bool Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG;   // Flag to compare specific Info only once

extern uint16_t bat3_geninfo_cycle_counter ;
extern uint16_t bat3_geninfo_asoc_counter;
extern uint16_t bat3_geninfo_remainingcapacity_counter ;
extern uint16_t bat3_geninfo_voltage_counter ;
extern uint16_t bat3_geninfo_temperature_counter ;
extern uint16_t bat3_geninfo_batterystatus_counter ;
extern uint16_t bat3_geninfo_current_counter;



extern bool bat3_geninfo_cycle_flag ;
extern bool bat3_geninfo_asoc_flag ;
extern bool bat3_geninfo_remainingcapacity_flag ;
extern bool bat3_geninfo_voltage_flag ;
extern bool bat3_geninfo_temperature_flag ;
extern bool bat3_geninfo_batterystatus_flag ;
extern bool bat3_geninfo_current_flag;

extern bool bat3_specific_info_rte_flag;

extern bool connect_flag;

extern bool bat3_update_maintenance_info_flag;

extern I2C_HandleTypeDef hi2c3;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;

void substatemachine_battery3_maintenance()
{

	if(BAT_3_MAINTENANCE_FLAG == true)   // Works with GUI updated periodically
	{

		if(BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG==false)
		{
			printf("Battery has entered Maintenance Use case \n");  // Displayed only once
			BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG = true;

		}




		if(BAT_3_MAINT_GENERAL_INFO_FLAG == true)
		{
			connect_flag = false;
			if(BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG==false)
			{
				BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG = true;

				//printf("Displayed General Info once \n");

				Transmit_Bat3_Maintenance_General_Info_to_Raspi(); // This function is working now




			}
			else if(BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG == true)
			{
				connect_flag=true;
			   // Update general info periodically // this function works
				if(bat3_update_maintenance_info_flag==true)
				{
					connect_flag=false;
				update_RemCap_during_maintenance_bat3();
				update_voltage_during_maintenance_bat3();
				update_asoc_during_maintenance_bat3();
				update_cyclecount_during_maintenance_bat3();
				update_batstatus_during_maintenance_bat3();
				update_temperature_during_maintenance_bat3();
				}

			}
		}

		if(BAT3_MAINT_STATE==0)
		{
			bat3charge = false;
			bat3discharge = false;
			gpio_func_bat3_chg_dschg();

		}

		if(Bat3_Maint_Autotestflag == true)
		{


			if(Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG ==false)
			{
				Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG = true;
			    Read_and_Compare_Specific_para_Bat3_STM_to_Pi();  // This function is also working



			}

			if(BAT3_MAINT_STATE == 0 && BAT3_MAINT_STATE !=1 && BAT3_MAINT_STATE !=2
					&& BAT3_MAINT_STATE !=3 && BAT3_MAINT_STATE !=4 && BAT3_MAINT_STATE !=5
					&& BAT3_MAINT_STATE !=6 && BAT3_MAINT_STATE !=7 && BAT3_MAINT_STATE !=8)
			{
				BAT3_MAINT_STATE = 1;
			}

			switch(BAT3_MAINT_STATE)
			{

			case 1:  // 80 % start state

				    BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
					if(BAT_3_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT3_MAINT_STATE = 2;
					}

					else if(BAT_3_ASOC_MAINTENANCE <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT3_MAINT_STATE = 3;
					}

					else if(BAT_3_ASOC_MAINTENANCE >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT3_MAINT_STATE = 4;
					}


				break;

			case 2:    // = 80 % state

				if(bat3_maint_state2guard == false)
				{
					bat3charge = false;
					bat3discharge = false;
					gpio_func_bat3_chg_dschg();
					_bat3timerfunc = true;
					bat3_maint_state2guard = true;
				}

				else if(bat3_maint_state2guard == true)
				{
					if(_bat3_15min_wait_over==true)
					{

//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat3_update_maintenance_info_flag=false;
						Read_Bat3_Maint_autotest_result_first_80_percent(); // This function works
						BAT3_MAINT_STATE = 5;
						bat3_maint_state2guard = false;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);
						bat3_update_maintenance_info_flag=true;
					}
				}

				break;

			case 3:    // <80 % state

				if(bat3_maint_state3guard == false)
				{
					bat3charge = true;
					bat3discharge = false;
					gpio_func_bat3_chg_dschg();
					bat3_maint_state3guard = true;
				}

				else if(bat3_maint_state3guard == true)
				{
					BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
					if(BAT_3_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT3_MAINT_STATE = 2;
						bat3_maint_state3guard = false;
					}
				}
				break;




			case 4:   // > 80 % state
				if(bat3_maint_state4guard == false)
				{
					bat3discharge = true;
					bat3charge = false;
					gpio_func_bat3_chg_dschg();
					bat3_maint_state4guard = true;
				}

				else if(bat3_maint_state4guard == true)
				{
					BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
					if(BAT_3_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
					{
						BAT3_MAINT_STATE = 2;
						bat3_maint_state4guard = false;
					}
				}
				break;

			case 5:   // Discharge to 10 %

				if(bat3_maint_state5guard==false)
				{
					bat3discharge = true;
					bat3charge = false;
					gpio_func_bat3_chg_dschg();
					bat3_maint_state5guard = true;
					_bat3timerfunc=false;
					_bat3_15min_wait_over=false;
					_bat3_counter_var = 0;

				}

				else if(bat3_maint_state5guard==true)
				{


					BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();



					if(BAT_3_ASOC_MAINTENANCE==79 && bat3_specific_info_rte_flag==true)
					{
						Read_bat3_maint_Run_time_to_empty_start_of_discharge();
						bat3_specific_info_rte_flag=false;
					}


					if(BAT_3_ASOC_MAINTENANCE ==BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
					{

						BAT3_MAINT_STATE = 6;
						bat3_maint_state5guard=false;
					}

				}
				break;

			case 6:  // ASOC = 10% state
				if(bat3_maint_state6guard==false)
				{
					bat3charge=false;
					bat3discharge=false;
					gpio_func_bat3_chg_dschg();
					_bat3timerfunc=true;
					bat3_maint_state6guard=true;
					Read_bat3_maint_Run_time_to_empty_end_of_discharge();  // RTE
				}
				else if(bat3_maint_state6guard==true)
				{

					if(_bat3_15min_wait_over==true)
					{


//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat3_update_maintenance_info_flag=false;
						Read_Bat3_Maint_autotest_result_middle_10_percent();
						BAT3_MAINT_STATE=7;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);
						bat3_update_maintenance_info_flag=true;
						bat3_maint_state6guard=false;
					}
				}
				break;

			case 7:  // Again charge to 80 % state
				if(bat3_maint_state7guard == false)
				{
					bat3charge=true;
					bat3discharge=false;
					gpio_func_bat3_chg_dschg();
					bat3_maint_state7guard = true;
					_bat3timerfunc = false;
					_bat3_15min_wait_over=false;
					_bat3_counter_var = 0;
				}
				else if(bat3_maint_state7guard==true)
				{
					BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
					if(BAT_3_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
					{
						BAT3_MAINT_STATE=8;
						bat3_maint_state7guard=false;
					}
				}
				break;

			case 8:
				if(bat3_maint_state8guard==false)
				{
					bat3discharge=false;
					bat3charge=false;
					gpio_func_bat3_chg_dschg();
					_bat3timerfunc=true;
					bat3_maint_state8guard=true;

				}
				else if(bat3_maint_state8guard==true)
				{
					if(_bat3_15min_wait_over==true)
					{
//						HAL_TIM_Base_Stop_IT(&htim2);
//						HAL_TIM_Base_Stop_IT(&htim3);
						bat3_update_maintenance_info_flag=false;
	          Read_Bat3_Maint_autotest_result_last_80_percent();
	          bat3_maint_state8guard=false;

						_bat3timerfunc=false;
						_bat3_15min_wait_over=false;
						_bat3_counter_var = 0;
						Bat3_Maint_Autotestflag = false;
						BAT_3_MAINTENANCE_FLAG = false;
						BAT_3_MAINT_GENERAL_INFO_FLAG = false;

						BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG=false;
						BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG=false;

						Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
						bat3_specific_info_rte_flag=true;

						printf("Auotest is finished\n");
						BAT3_MAINT_STATE=0;
//						HAL_TIM_Base_Start_IT(&htim2);
//						HAL_TIM_Base_Start_IT(&htim3);

						connect_flag = true;

					}
				}
				break;

			default:
				BAT3_MAINT_STATE = 0;
				break;
			}

		}   // End of Autotest

	}   // end of maintenance




}


// Test

//				if(BAT_3_MAINTENANCE_FLAG == true)   // Works with GUI updated periodically
//				{
//
//					if(BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG==false)
//					{
//						printf("Battery has entered Maintenance Use case \n");  // Displayed only once
//						BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG = true;
//
//					}
//
//
//
//
//					if(BAT_3_MAINT_GENERAL_INFO_FLAG == true)
//					{
//						connect_flag = false;
//						if(BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG==false)
//						{
//							BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG = true;
//
//							//printf("Displayed General Info once \n");
//
//							Transmit_Bat3_Maintenance_General_Info_to_Raspi(); // This function is working now
//
//
//
//
//						}
//						else if(BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG == true)
//						{
//							connect_flag=true;
//						   // Update general info periodically // this function works
//							if(bat3_update_maintenance_info_flag==true)
//							{
//								connect_flag=false;
//							update_RemCap_during_maintenance_bat3();
//							update_voltage_during_maintenance_bat3();
//							update_asoc_during_maintenance_bat3();
//							update_cyclecount_during_maintenance_bat3();
//							update_batstatus_during_maintenance_bat3();
//							update_temperature_during_maintenance_bat3();
//							}
//
//						}
//					}
//
//					if(BAT3_MAINT_STATE==0)
//					{
//						bat3charge = false;
//						bat3discharge = false;
//						gpio_func_bat3_chg_dschg();
//
//					}
//
//					if(Bat3_Maint_Autotestflag == true)
//					{
//
//
//						if(Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG ==false)
//						{
//							Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG = true;
//						    Read_and_Compare_Specific_para_Bat3_STM_to_Pi();  // This function is also working
//
//
//
//						}
//
//						if(BAT3_MAINT_STATE == 0 && BAT3_MAINT_STATE !=1 && BAT3_MAINT_STATE !=2
//								&& BAT3_MAINT_STATE !=3 && BAT3_MAINT_STATE !=4 && BAT3_MAINT_STATE !=5
//								&& BAT3_MAINT_STATE !=6 && BAT3_MAINT_STATE !=7 && BAT3_MAINT_STATE !=8)
//						{
//							BAT3_MAINT_STATE = 1;
//						}
//
//						switch(BAT3_MAINT_STATE)
//						{
//
//						case 1:  // 80 % start state
//
//							    BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
//								if(BAT_3_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//								{
//									BAT3_MAINT_STATE = 2;
//								}
//
//								else if(BAT_3_ASOC_MAINTENANCE <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//								{
//									BAT3_MAINT_STATE = 3;
//								}
//
//								else if(BAT_3_ASOC_MAINTENANCE >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//								{
//									BAT3_MAINT_STATE = 4;
//								}
//
//
//							break;
//
//						case 2:    // = 80 % state
//
//							if(bat3_maint_state2guard == false)
//							{
//								bat3charge = false;
//								bat3discharge = false;
//								gpio_func_bat3_chg_dschg();
//								_bat3timerfunc = true;
//								bat3_maint_state2guard = true;
//							}
//
//							else if(bat3_maint_state2guard == true)
//							{
//								if(_bat3_15min_wait_over==true)
//								{
//
//									HAL_TIM_Base_Stop_IT(&htim2);
//									HAL_TIM_Base_Stop_IT(&htim3);
//									bat3_update_maintenance_info_flag=false;
//									Read_Bat3_Maint_autotest_result_first_80_percent(); // This function works
//									BAT3_MAINT_STATE = 5;
//									bat3_maint_state2guard = false;
//									HAL_TIM_Base_Start_IT(&htim2);
//									HAL_TIM_Base_Start_IT(&htim3);
//									bat3_update_maintenance_info_flag=true;
//								}
//							}
//
//							break;
//
//						case 3:    // <80 % state
//
//							if(bat3_maint_state3guard == false)
//							{
//								bat3charge = true;
//								bat3discharge = false;
//								gpio_func_bat3_chg_dschg();
//								bat3_maint_state3guard = true;
//							}
//
//							else if(bat3_maint_state3guard == true)
//							{
//								BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
//								if(BAT_3_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//								{
//									BAT3_MAINT_STATE = 2;
//									bat3_maint_state3guard = false;
//								}
//							}
//							break;
//
//
//
//
//						case 4:   // > 80 % state
//							if(bat3_maint_state4guard == false)
//							{
//								bat3discharge = true;
//								bat3charge = false;
//								gpio_func_bat3_chg_dschg();
//								bat3_maint_state4guard = true;
//							}
//
//							else if(bat3_maint_state4guard == true)
//							{
//								BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
//								if(BAT_3_ASOC_MAINTENANCE == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
//								{
//									BAT3_MAINT_STATE = 2;
//									bat3_maint_state4guard = false;
//								}
//							}
//							break;
//
//						case 5:   // Discharge to 10 %
//
//							if(bat3_maint_state5guard==false)
//							{
//								bat3discharge = true;
//								bat3charge = false;
//								gpio_func_bat3_chg_dschg();
//								bat3_maint_state5guard = true;
//								_bat3timerfunc=false;
//								_bat3_15min_wait_over=false;
//								_bat3_counter_var = 0;
//
//							}
//
//							else if(bat3_maint_state5guard==true)
//							{
//
//
//								BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
//
//
//
//								if(BAT_3_ASOC_MAINTENANCE==83 && bat3_specific_info_rte_flag==true)
//								{
//									Read_bat3_maint_Run_time_to_empty_start_of_discharge();
//									bat3_specific_info_rte_flag=false;
//								}
//
//
//								if(BAT_3_ASOC_MAINTENANCE ==BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
//								{
//
//									BAT3_MAINT_STATE = 6;
//									bat3_maint_state5guard=false;
//								}
//
//							}
//							break;
//
//						case 6:  // ASOC = 10% state
//							if(bat3_maint_state6guard==false)
//							{
//								bat3charge=false;
//								bat3discharge=false;
//								gpio_func_bat3_chg_dschg();
//								_bat3timerfunc=true;
//								bat3_maint_state6guard=true;
//								Read_bat3_maint_Run_time_to_empty_end_of_discharge();  // RTE
//							}
//							else if(bat3_maint_state6guard==true)
//							{
//
//								if(_bat3_15min_wait_over==true)
//								{
//
//
//									HAL_TIM_Base_Stop_IT(&htim2);
//									HAL_TIM_Base_Stop_IT(&htim3);
//									bat3_update_maintenance_info_flag=false;
//									Read_Bat3_Maint_autotest_result_middle_10_percent();
//									BAT3_MAINT_STATE=7;
//									HAL_TIM_Base_Start_IT(&htim2);
//									HAL_TIM_Base_Start_IT(&htim3);
//									bat3_update_maintenance_info_flag=true;
//									bat3_maint_state6guard=false;
//								}
//							}
//							break;
//
//						case 7:  // Again charge to 80 % state
//							if(bat3_maint_state7guard == false)
//							{
//								bat3charge=true;
//								bat3discharge=false;
//								gpio_func_bat3_chg_dschg();
//								bat3_maint_state7guard = true;
//								_bat3timerfunc = false;
//								_bat3_15min_wait_over=false;
//								_bat3_counter_var = 0;
//							}
//							else if(bat3_maint_state7guard==true)
//							{
//								BAT_3_ASOC_MAINTENANCE = read_bat3_asoc();
//								if(BAT_3_ASOC_MAINTENANCE==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
//								{
//									BAT3_MAINT_STATE=8;
//									bat3_maint_state7guard=false;
//								}
//							}
//							break;
//
//						case 8:
//							if(bat3_maint_state8guard==false)
//							{
//								bat3discharge=false;
//								bat3charge=false;
//								gpio_func_bat3_chg_dschg();
//								_bat3timerfunc=true;
//								bat3_maint_state8guard=true;
//
//							}
//							else if(bat3_maint_state8guard==true)
//							{
//								if(_bat3_15min_wait_over==true)
//								{
//									HAL_TIM_Base_Stop_IT(&htim2);
//									HAL_TIM_Base_Stop_IT(&htim3);
//									bat3_update_maintenance_info_flag=false;
//				          Read_Bat3_Maint_autotest_result_last_80_percent();
//				          bat3_maint_state8guard=false;
//
//									_bat3timerfunc=false;
//									_bat3_15min_wait_over=false;
//									_bat3_counter_var = 0;
//									Bat3_Maint_Autotestflag = false;
//									BAT_3_MAINTENANCE_FLAG = false;
//									BAT_3_MAINT_GENERAL_INFO_FLAG = false;
//
//									BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG=false;
//									BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG=false;
//
//									Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
//									bat3_specific_info_rte_flag=true;
//
//									printf("Auotest is finished\n");
//									BAT3_MAINT_STATE=0;
//									HAL_TIM_Base_Start_IT(&htim2);
//									HAL_TIM_Base_Start_IT(&htim3);
//								//	bat2_update_maintenance_info_flag=true;
//									connect_flag = true;
//
//								}
//							}
//							break;
//
//						default:
//							BAT3_MAINT_STATE = 0;
//							break;
//						}
//
//					}   // End of Autotest
//
//				}   // end of maintenance
