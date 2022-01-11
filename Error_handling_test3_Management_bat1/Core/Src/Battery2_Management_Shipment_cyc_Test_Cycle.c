/*
 * Battery2_Management_Shipment_cyc_Test_Cycle.c
 *
 *  Created on: Jan 9, 2022
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


/*
 * Important Note : For 15 minutes waiting period same function from Maintenance use case has been used.
 *                  Reason : A single battery cannot be in Maintenance and Management Use Case at the same time. Since the task of waiting for 15 min in both
 *                  use cases is exactly the same,  function from Maintenance Use Case is used in Management
 *                  as well.
 *
 */


#include "stm32f7xx_hal.h"
#include "Battery2_Management_Shipment_cyc_Test_Cycle.h"
#include "stdbool.h"
#include "bat2_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include "Bat2_Update_Info_during_Maintenance.h"
#include "main.h"
#include "Specific_parameters_management_BAT2_ShipmentTest.h"
#include "Results_Auto_Test_Bat2_Management_Shipment_Test_Cycle.h"

extern bool _bat2timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat2_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat2_counter_var ;

extern  uint16_t BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;



extern bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ;

extern bool Bat2_Management_Shipment_testycycle_Autotestflag;




extern bool Bat2_Management_Shipment_chg_dischg_to_30_percent_flag ;

extern bool Bat2_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ;

extern uint8_t BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE; // Bat 1 state during Shipment Test cycle - Management Use Case

extern bool BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;


extern bool bat2charge ;				// Flag to start and stop charging of the battery
extern bool bat2discharge ;				// Flag to start and stop discharging of the battery


extern bool bat2_management_shipment_testcycle_state1guard ;
extern bool bat2_management_shipment_testcycle_state2guard ;
extern bool bat2_management_shipment_testcycle_state3guard ;
extern bool bat2_management_shipment_testcycle_state4guard ;
extern bool bat2_management_shipment_testcycle_state5guard ;
extern bool bat2_management_shipment_testcycle_state6guard ;
extern bool bat2_management_shipment_testcycle_state7guard ;
extern bool bat2_management_shipment_testcycle_state8guard ;

extern bool connect_flag;


extern I2C_HandleTypeDef hi2c2;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;




void Battery2_Management_Use_Case_Shipment_Test_Cycle()
{
	if(BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{


		if(BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat2_Management_Shipment_chg_dischg_to_30_percent_flag==false)
			{

				if(BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE==0)
				{
					bat2charge = false;
					bat2discharge = false;
					gpio_func_bat2_chg_dschg();

				}



				if(Bat2_Management_Shipment_testycycle_Autotestflag == true)
				{


					if(Bat2_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ==false)
					{
						Bat2_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = true;
						Read_and_Compare_Specific_para_Bat2_Management_Shipment_Test_STM_to_Pi();  // This function is also working

						// send specific info during test cycle

					}

					if(BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE == 0 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=1 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=2
							&& BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=3 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=4 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=5
							&& BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=6 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=7 && BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=8)
					{
						BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 1;
					}



					switch(BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE)
					{

					case 1:  // 80 % start state

						BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat2_asoc();

							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
							}

							else if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 3;
							}

							else if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 4;
							}


						break;

					case 2:    // = 80 % state

						if(bat2_management_shipment_testcycle_state2guard == false)
						{
							bat2charge = false;
							bat2discharge = false;
							gpio_func_bat2_chg_dschg();
							_bat2timerfunc = true;
							bat2_management_shipment_testcycle_state2guard = true;
						}

						else if(bat2_management_shipment_testcycle_state2guard == true)
						{
							if(_bat2_15min_wait_over==true)
							{

//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
							//	update_maintenance_info_flag=false;
								Read_Bat2_Management_Shipment_autotest_result_first_80_percent(); // This function works
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 5;
								bat2_management_shipment_testcycle_state2guard = false;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
							//	update_maintenance_info_flag=true;
							}
						}

						break;

					case 3:    // <80 % state

						if(bat2_management_shipment_testcycle_state3guard == false)
						{
							bat2charge = true;
							bat2discharge = false;
							gpio_func_bat2_chg_dschg();
							bat2_management_shipment_testcycle_state3guard = true;
						}

						else if(bat2_management_shipment_testcycle_state3guard == true)
						{
							BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat2_asoc();
							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat2_management_shipment_testcycle_state3guard = false;
							}
						}
						break;




					case 4:   // > 80 % state
						if(bat2_management_shipment_testcycle_state4guard == false)
						{
							bat2discharge = true;
							bat2charge = false;
							gpio_func_bat2_chg_dschg();
							bat2_management_shipment_testcycle_state4guard = true;
						}

						else if(bat2_management_shipment_testcycle_state4guard == true)
						{
							BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat2_asoc();
							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat2_management_shipment_testcycle_state4guard = false;
							}
						}
						break;

					case 5:   // Discharge to 10 %

						if(bat2_management_shipment_testcycle_state5guard==false)
						{
							bat2discharge = true;
							bat2charge = false;
							gpio_func_bat2_chg_dschg();
							bat2_management_shipment_testcycle_state5guard = true;
							_bat2timerfunc=false;
							_bat2_15min_wait_over=false;
							_bat2_counter_var = 0;
					//		Read_bat1_maint_Run_time_to_empty(); // RTE
						}

						else if(bat2_management_shipment_testcycle_state5guard==true)
						{


							BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat2_asoc();



//							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==79 && bat1_specific_info_rte_flag==true)
//							{
//						//		Read_bat1_maint_Run_time_to_empty();
//						//		bat1_specific_info_rte_flag=false;
//						//		printf(" line 310==79 && specific info\n");
//							}


							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
							{
						//		printf(" line 316==10");
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 6;
								bat2_management_shipment_testcycle_state5guard=false;
							}

						}
						break;

					case 6:  // ASOC = 10% state
						if(bat2_management_shipment_testcycle_state6guard==false)
						{
							bat2charge=false;
							bat2discharge=false;
							gpio_func_bat2_chg_dschg();
							_bat2timerfunc=true;
							bat2_management_shipment_testcycle_state6guard=true;
						//	Read_bat1_maint_Run_time_to_empty_end_of_discharge();  // RTE
						}
						else if(bat2_management_shipment_testcycle_state6guard==true)
						{

							if(_bat2_15min_wait_over==true)
							{


//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat2_Management_Shipment_autotest_result_middle_10_percent();
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=7;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
						//		update_maintenance_info_flag=true;
								bat2_management_shipment_testcycle_state6guard=false;
							}
						}
						break;

					case 7:  // Again charge to 80 % state
						if(bat2_management_shipment_testcycle_state7guard == false)
						{
							bat2charge=true;
							bat2discharge=false;
							gpio_func_bat2_chg_dschg();
							bat2_management_shipment_testcycle_state7guard = true;
							_bat2timerfunc = false;
							_bat2_15min_wait_over=false;
							_bat2_counter_var = 0;
						}
						else if(bat2_management_shipment_testcycle_state7guard==true)
						{
							BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat2_asoc();
							if(BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
							{
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=8;
								bat2_management_shipment_testcycle_state7guard=false;
							}
						}
						break;

					case 8:
						if(bat2_management_shipment_testcycle_state8guard==false)
						{
							bat2discharge=false;
							bat2charge=false;
							gpio_func_bat2_chg_dschg();
							_bat2timerfunc=true;
							bat2_management_shipment_testcycle_state8guard=true;

						}
						else if(bat2_management_shipment_testcycle_state8guard==true)
						{
							if(_bat2_15min_wait_over==true)
							{
//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat2_Management_Shipment_autotest_result_last_80_percent();
								bat2_management_shipment_testcycle_state8guard=false;

								_bat2timerfunc=false;
								_bat2_15min_wait_over=false;
								_bat2_counter_var = 0;
								Bat2_Management_Shipment_testycycle_Autotestflag=false;
								BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

								Bat2_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag =false;

//								BAT_1_MAINTENANCE_FLAG = false;
//								BAT_1_MAINT_GENERAL_INFO_FLAG = false;
//
//								BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG=false;
//								BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG=false;
//								Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
//								bat1_specific_info_rte_flag=true;

								//printf("Auotest is finished\n");
								BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);

								connect_flag = true;

							}
						}
						break;

					default:
						BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 0;
						break;
					}









				}






			}
		}




	}




}
