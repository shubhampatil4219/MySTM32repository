/*
 * Battery3_Management_Shipment_cyc_Test_Cycle.c
 *
 *  Created on: Jan 11, 2022
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
#include "Battery3_Management_Shipment_cyc_Test_Cycle.h"
#include "stdbool.h"
#include "bat3_asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"
#include "Bat3_Update_Info_during_Maintenance.h"
#include "main.h"
#include "Specific_parameters_management_BAT3_ShipmentTest.h"
#include "Results_Auto_Test_Bat3_Management_Shipment_Test_Cycle.h"

extern bool _bat3timerfunc ;		     // Flag to start and stop the 15 min wait function
extern bool _bat3_15min_wait_over ;  		// To indicate 15 min delay is over
extern uint16_t _bat3_counter_var ;

extern  uint16_t BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;



extern bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG ;

extern bool Bat3_Management_Shipment_testycycle_Autotestflag;




extern bool Bat3_Management_Shipment_chg_dischg_to_30_percent_flag ;

extern bool Bat3_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ;

extern uint8_t BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE; // Bat 1 state during Shipment Test cycle - Management Use Case

extern bool BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG ;


extern bool bat3charge ;				// Flag to start and stop charging of the battery
extern bool bat3discharge ;				// Flag to start and stop discharging of the battery


extern bool bat3_management_shipment_testcycle_state1guard ;
extern bool bat3_management_shipment_testcycle_state2guard ;
extern bool bat3_management_shipment_testcycle_state3guard ;
extern bool bat3_management_shipment_testcycle_state4guard ;
extern bool bat3_management_shipment_testcycle_state5guard ;
extern bool bat3_management_shipment_testcycle_state6guard ;
extern bool bat3_management_shipment_testcycle_state7guard ;
extern bool bat3_management_shipment_testcycle_state8guard ;

extern bool connect_flag;


extern I2C_HandleTypeDef hi2c3;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;




void Battery3_Management_Use_Case_Shipment_Test_Cycle()
{
	if(BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG==false)
	{


		if(BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG == true)
		{
			if(Bat3_Management_Shipment_chg_dischg_to_30_percent_flag==false)
			{

				if(BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE==0)
				{
					bat3charge = false;
					bat3discharge = false;
					gpio_func_bat3_chg_dschg();

				}



				if(Bat3_Management_Shipment_testycycle_Autotestflag == true)
				{


					if(Bat3_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag ==false)
					{
						Bat3_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = true;
						Read_and_Compare_Specific_para_Bat3_Management_Shipment_Test_STM_to_Pi();  // This function is also working

						// send specific info during test cycle

					}

					if(BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE == 0 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=1 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=2
							&& BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=3 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=4 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=5
							&& BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=6 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=7 && BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE !=8)
					{
						BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 1;
					}



					switch(BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE)
					{

					case 1:  // 80 % start state

						BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat3_asoc();

							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
							}

							else if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle <BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 3;
							}

							else if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle >BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 4;
							}


						break;

					case 2:    // = 80 % state

						if(bat3_management_shipment_testcycle_state2guard == false)
						{
							bat3charge = false;
							bat3discharge = false;
							gpio_func_bat3_chg_dschg();
							_bat3timerfunc = true;
							bat3_management_shipment_testcycle_state2guard = true;
						}

						else if(bat3_management_shipment_testcycle_state2guard == true)
						{
							if(_bat3_15min_wait_over==true)
							{

//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
							//	update_maintenance_info_flag=false;
								Read_Bat3_Management_Shipment_autotest_result_first_80_percent(); // This function works
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 5;
								bat3_management_shipment_testcycle_state2guard = false;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
							//	update_maintenance_info_flag=true;
							}
						}

						break;

					case 3:    // <80 % state

						if(bat3_management_shipment_testcycle_state3guard == false)
						{
							bat3charge = true;
							bat3discharge = false;
							gpio_func_bat3_chg_dschg();
							bat3_management_shipment_testcycle_state3guard = true;
						}

						else if(bat3_management_shipment_testcycle_state3guard == true)
						{
							BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat3_asoc();
							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat3_management_shipment_testcycle_state3guard = false;
							}
						}
						break;




					case 4:   // > 80 % state
						if(bat3_management_shipment_testcycle_state4guard == false)
						{
							bat3discharge = true;
							bat3charge = false;
							gpio_func_bat3_chg_dschg();
							bat3_management_shipment_testcycle_state4guard = true;
						}

						else if(bat3_management_shipment_testcycle_state4guard == true)
						{
							BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat3_asoc();
							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_80)
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 2;
								bat3_management_shipment_testcycle_state4guard = false;
							}
						}
						break;

					case 5:   // Discharge to 10 %

						if(bat3_management_shipment_testcycle_state5guard==false)
						{
							bat3discharge = true;
							bat3charge = false;
							gpio_func_bat3_chg_dschg();
							bat3_management_shipment_testcycle_state5guard = true;
							_bat3timerfunc=false;
							_bat3_15min_wait_over=false;
							_bat3_counter_var = 0;
					//		Read_bat1_maint_Run_time_to_empty(); // RTE
						}

						else if(bat3_management_shipment_testcycle_state5guard==true)
						{


							BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat3_asoc();



//							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==79 && bat1_specific_info_rte_flag==true)
//							{
//						//		Read_bat1_maint_Run_time_to_empty();
//						//		bat1_specific_info_rte_flag=false;
//						//		printf(" line 310==79 && specific info\n");
//							}


							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle == BAT_AUTOTEST_MAINTENANCE_ASOC_10)   // 72
							{
						//		printf(" line 316==10");
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 6;
								bat3_management_shipment_testcycle_state5guard=false;
							}

						}
						break;

					case 6:  // ASOC = 10% state
						if(bat3_management_shipment_testcycle_state6guard==false)
						{
							bat3charge=false;
							bat3discharge=false;
							gpio_func_bat3_chg_dschg();
							_bat3timerfunc=true;
							bat3_management_shipment_testcycle_state6guard=true;
						//	Read_bat1_maint_Run_time_to_empty_end_of_discharge();  // RTE
						}
						else if(bat3_management_shipment_testcycle_state6guard==true)
						{

							if(_bat3_15min_wait_over==true)
							{


//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat3_Management_Shipment_autotest_result_middle_10_percent();
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=7;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);
						//		update_maintenance_info_flag=true;
								bat3_management_shipment_testcycle_state6guard=false;
							}
						}
						break;

					case 7:  // Again charge to 80 % state
						if(bat3_management_shipment_testcycle_state7guard == false)
						{
							bat3charge=true;
							bat3discharge=false;
							gpio_func_bat3_chg_dschg();
							bat3_management_shipment_testcycle_state7guard = true;
							_bat3timerfunc = false;
							_bat3_15min_wait_over=false;
							_bat3_counter_var = 0;
						}
						else if(bat3_management_shipment_testcycle_state7guard==true)
						{
							BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle = read_bat3_asoc();
							if(BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle==BAT_AUTOTEST_MAINTENANCE_ASOC_80)   // 73
							{
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=8;
								bat3_management_shipment_testcycle_state7guard=false;
							}
						}
						break;

					case 8:
						if(bat3_management_shipment_testcycle_state8guard==false)
						{
							bat3discharge=false;
							bat3charge=false;
							gpio_func_bat3_chg_dschg();
							_bat3timerfunc=true;
							bat3_management_shipment_testcycle_state8guard=true;

						}
						else if(bat3_management_shipment_testcycle_state8guard==true)
						{
							if(_bat3_15min_wait_over==true)
							{
//								HAL_TIM_Base_Stop_IT(&htim2);
//								HAL_TIM_Base_Stop_IT(&htim3);
						//		update_maintenance_info_flag=false;
								Read_Bat3_Management_Shipment_autotest_result_last_80_percent();
								bat3_management_shipment_testcycle_state8guard=false;

								_bat3timerfunc=false;
								_bat3_15min_wait_over=false;
								_bat3_counter_var = 0;
								Bat3_Management_Shipment_testycycle_Autotestflag=false;
								BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false;

								Bat3_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag =false;

//								BAT_1_MAINTENANCE_FLAG = false;
//								BAT_1_MAINT_GENERAL_INFO_FLAG = false;
//
//								BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG=false;
//								BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG=false;
//								Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG=false;
//								bat1_specific_info_rte_flag=true;

								//printf("Auotest is finished\n");
								BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0;
//								HAL_TIM_Base_Start_IT(&htim2);
//								HAL_TIM_Base_Start_IT(&htim3);

								connect_flag = true;

							}
						}
						break;

					default:
						BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE = 0;
						break;
					}









				}






			}
		}




	}




}
