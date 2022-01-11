/*
 * Battery1_Management_Shipment_cyc_Test_Cycle.c
 *
 *  Created on: Jan 4, 2022
 *      Author: shubham
 */


/*
 * Important Note : To update the parameters periodically in Management Use case, the same update function
 *                  of Maintenance Use Case has been used.  Reason : A single battery cannot be in Maintenance
 *                  and Management Use Case at the same time. Since the task of updating the parameters in both
 *                  use cases is exactly the same, update function of Maintenance Use Case is used in Management
 *                  as well.
 *
 */


#include "stm32f7xx_hal.h"
#include "Battery1_Management_Shipment_cyc_Test_Cycle.h"
#include "stdbool.h"
#include "bat1_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include "Bat1_Update_Info_during_Maintenance.h"
#include "main.h"
#include "Specific_parameters_management_BAT1_ShipmentTest.h"
#include "Results_Auto_Test_Bat1_Management_Shipment_Test_Cycle.h"

extern bool _bat1timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat1_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat1_counter_var ;

extern  uint16_t BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;

//extern uint8_t BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE; // Battery State

extern bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ;

extern bool Bat1_Management_Shipment_testycycle_Autotestflag;




extern bool Bat1_Management_Shipment_chg_dischg_to_30_percent_flag ;

extern bool Bat1_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ;

extern uint8_t BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE; // Bat 1 state during Shipment Test cycle - Management Use Case

extern bool BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;


extern bool bat1charge ;				// Flag to start and stop charging of the battery
extern bool bat1discharge ;				// Flag to start and stop discharging of the battery


extern bool bat1_management_shipment_testcycle_state1guard ;
extern bool bat1_management_shipment_testcycle_state2guard ;
extern bool bat1_management_shipment_testcycle_state3guard ;
extern bool bat1_management_shipment_testcycle_state4guard ;
extern bool bat1_management_shipment_testcycle_state5guard ;
extern bool bat1_management_shipment_testcycle_state6guard ;
extern bool bat1_management_shipment_testcycle_state7guard ;
extern bool bat1_management_shipment_testcycle_state8guard ;

extern bool connect_flag;


extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;


void Battery1_Management_Use_Case_Shipment_Test_Cycle()
{
	if(BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{


		if(BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat1_Management_Shipment_chg_dischg_to_30_percent_flag==false)
			{

				if(BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE==0)
				{
					bat1charge = false;
					bat1discharge = false;
					gpio_func();

				}



				if(Bat1_Management_Shipment_testycycle_Autotestflag == true)
				{


					if(Bat1_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ==false)
					{
						Bat1_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = true;
						Read_and_Compare_Specific_para_Bat1_Management_Shipment_Test_STM_to_Pi();  // This function is also working

						// send specific info during test cycle

					}

					if(BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE == 0 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=1 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=2
							&& BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=3 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=4 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=5
							&& BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=6 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=7 && BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=8)
					{
						BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 1;
					}



					switch(BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE)
					{

					case 1:  // 80 % start state

						BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat1_asoc();

							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
							}

							else if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 3;
							}

							else if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 4;
							}


						break;

					case 2:    // = 80 % state

						if(bat1_management_shipment_testcycle_state2guard == false)
						{
							bat1charge = false;
							bat1discharge = false;
							gpio_func();
							_bat1timerfunc = true;
							bat1_management_shipment_testcycle_state2guard = true;
						}

						else if(bat1_management_shipment_testcycle_state2guard == true)
						{
							if(_bat1_15min_wait_over==true)
							{

//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
							//	update_maintenance_info_flag=false;
								Read_Bat1_Management_Shipment_autotest_result_first_80_percent(); // This function works
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 5;
								bat1_management_shipment_testcycle_state2guard = false;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
							//	update_maintenance_info_flag=true;
							}
						}

						break;

					case 3:    // <80 % state

						if(bat1_management_shipment_testcycle_state3guard == false)
						{
							bat1charge = true;
							bat1discharge = false;
							gpio_func();
							bat1_management_shipment_testcycle_state3guard = true;
						}

						else if(bat1_management_shipment_testcycle_state3guard == true)
						{
							BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat1_asoc();
							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat1_management_shipment_testcycle_state3guard = false;
							}
						}
						break;




					case 4:   // > 80 % state
						if(bat1_management_shipment_testcycle_state4guard == false)
						{
							bat1discharge = true;
							bat1charge = false;
							gpio_func();
							bat1_management_shipment_testcycle_state4guard = true;
						}

						else if(bat1_management_shipment_testcycle_state4guard == true)
						{
							BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat1_asoc();
							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat1_management_shipment_testcycle_state4guard = false;
							}
						}
						break;

					case 5:   // Discharge to 10 %

						if(bat1_management_shipment_testcycle_state5guard==false)
						{
							bat1discharge = true;
							bat1charge = false;
							gpio_func();
							bat1_management_shipment_testcycle_state5guard = true;
							_bat1timerfunc=false;
							_bat1_15min_wait_over=false;
							_bat1_counter_var = 0;
					//		Read_bat1_maint_Run_time_to_empty(); // RTE
						}

						else if(bat1_management_shipment_testcycle_state5guard==true)
						{


							BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat1_asoc();



//							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==79 && bat1_specific_info_rte_flag==true)
//							{
//						//		Read_bat1_maint_Run_time_to_empty();
//						//		bat1_specific_info_rte_flag=false;
//						//		printf(" line 310==79 && specific info\n");
//							}


							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
							{
						//		printf(" line 316==10");
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 6;
								bat1_management_shipment_testcycle_state5guard=false;
							}

						}
						break;

					case 6:  // ASOC = 10% state
						if(bat1_management_shipment_testcycle_state6guard==false)
						{
							bat1charge=false;
							bat1discharge=false;
							gpio_func();
							_bat1timerfunc=true;
							bat1_management_shipment_testcycle_state6guard=true;
						//	Read_bat1_maint_Run_time_to_empty_end_of_discharge();  // RTE
						}
						else if(bat1_management_shipment_testcycle_state6guard==true)
						{

							if(_bat1_15min_wait_over==true)
							{


//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat1_Management_Shipment_autotest_result_middle_10_percent();
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=7;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
						//		update_maintenance_info_flag=true;
								bat1_management_shipment_testcycle_state6guard=false;
							}
						}
						break;

					case 7:  // Again charge to 80 % state
						if(bat1_management_shipment_testcycle_state7guard == false)
						{
							bat1charge=true;
							bat1discharge=false;
							gpio_func();
							bat1_management_shipment_testcycle_state7guard = true;
							_bat1timerfunc = false;
							_bat1_15min_wait_over=false;
							_bat1_counter_var = 0;
						}
						else if(bat1_management_shipment_testcycle_state7guard==true)
						{
							BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat1_asoc();
							if(BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
							{
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=8;
								bat1_management_shipment_testcycle_state7guard=false;
							}
						}
						break;

					case 8:
						if(bat1_management_shipment_testcycle_state8guard==false)
						{
							bat1discharge=false;
							bat1charge=false;
							gpio_func();
							_bat1timerfunc=true;
							bat1_management_shipment_testcycle_state8guard=true;

						}
						else if(bat1_management_shipment_testcycle_state8guard==true)
						{
							if(_bat1_15min_wait_over==true)
							{
//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat1_Management_Shipment_autotest_result_last_80_percent();
								bat1_management_shipment_testcycle_state8guard=false;

								_bat1timerfunc=false;
								_bat1_15min_wait_over=false;
								_bat1_counter_var = 0;
								Bat1_Management_Shipment_testycycle_Autotestflag=false;
								BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

								Bat1_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag =false;

//								BAT_1_MAINTENANCE_FLAG = false;
//								BAT_1_MAINT_GENERAL_INFO_FLAG = false;
//
//								BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG=false;
//								BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG=false;
//								Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
//								bat1_specific_info_rte_flag=true;

								//printf("Auotest is finished\n");
								BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);

								connect_flag = true;

							}
						}
						break;

					default:
						BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 0;
						break;
					}









				}






			}
		}




	}




}
