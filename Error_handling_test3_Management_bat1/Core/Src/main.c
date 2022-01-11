/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
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
#include "Commands_from_Raspi_To_STM32.h"
#include <Results_Auto_Test_Bat1_Maintenance.h>

#include "bat2_asoc.h"
#include "Battery2_Maintenance_General_Info.h"
#include"Specific_parameters_main_BAT2.h"
#include <Results_Auto_Test_Bat2_Maintenance.h>
#include "Bat2_Update_Info_during_Maintenance.h"
#include "SubStatemachine_bat2_Maintenance.h"

#include "bat3_asoc.h"
#include "Battery3_Maintenance_General_Info.h"
#include"Specific_parameters_main_BAT3.h"
#include <Results_Auto_Test_Bat3_Maintenance.h>
#include "Bat3_Update_Info_during_Maintenance.h"
#include "SubStatemachine_bat3_Maintenance.h"

#include "Battery1_Management_General_Info.h"
#include "Specific_parameters_management_BAT1.h"
#include "Bat1_Management_Keep_Bat_Alive_cycle.h"
#include "Battery1_Management_Shipment_cyc_Test_Cycle.h"
#include "Battery1_Management_Shipment_cyc_Discharge_to_30_percent.h"
#include "Specific_parameters_management_BAT1_ShipmentTest.h"
#include "Results_Auto_Test_Bat1_Management_Shipment_Test_Cycle.h"
#include "Bat1_Update_Info_during_Management.h"
#include "SubStatemachine_bat1_Management.h"



#include "Battery2_Management_General_Info.h"
#include "Specific_parameters_management_BAT2_ShipmentTest.h"
#include "Specific_parameters_management_BAT2.h"
#include "Results_Auto_Test_Bat2_Management_Shipment_Test_Cycle.h"
#include "Bat2_Update_Info_during_Management.h"
#include "Bat2_Management_Keep_Bat_Alive_cycle.h"
#include "Battery2_Management_Shipment_cyc_Discharge_to_30_percent.h"
#include "Battery2_Management_Shipment_cyc_Test_Cycle.h"
#include "SubStatemachine_bat2_Management.h"


#include "Battery3_Management_General_Info.h"
#include "Specific_parameters_management_BAT3.h"
#include "Specific_parameters_management_BAT3_ShipmentTest.h"
#include "Results_Auto_Test_Bat3_Management_Shipment_Test_Cycle.h"
#include "Bat3_Update_Info_during_Management.h"
#include "Bat3_Management_Keep_Bat_Alive_cycle.h"
#include "SubStatemachine_bat3_Management.h"
#include "Battery3_Management_Shipment_cyc_Test_Cycle.h"
#include "Battery3_Management_Shipment_cyc_Discharge_to_30_percent.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/////////////////////// Maintenance cycle BAT 1 definitions////////////////////////////////////////////

bool _bat1timerfunc = false;		     // Flag to start and stop the 15 min wait function
bool _bat1_15min_wait_over = false;  		// To indicate 15 min delay is over
uint16_t _bat1_counter_var = 0;				//   Variable as a counter
//int8_t bat1_state=0;  						// Indicates the current state in Maintenance cycle
uint8_t BAT1_MAINT_STATE=0;


uint16_t BAT_1_ASOC_MAINTENANCE;
uint16_t BAT1_VOLTAGE_MAINTENANCE;

bool bat1charge = false;				// Flag to start and stop charging of the battery
bool bat1discharge = false;				// Flag to start and stop discharging of the battery

bool state1guard = false;
bool state2guard = false;
bool state3guard = false;
bool state4guard = false;
bool state5guard = false;
bool state6guard = false;
bool state7guard = false;
bool state8guard = false;

bool Autotestflag = false;				// Flag to start automatic testing of the maintenance cycle

uint8_t rx_buffer[14];					// Receives command from Pi

bool BAT_1_MAINTENANCE_FLAG = false;  				// Flag for battery 1 to enter the maintenance process
bool BAT_1_MAINTENANCE_ENTERED_GUARD_FLAG = false;

bool BAT_1_MAINT_GENERAL_INFO_FLAG = false;
bool BAT_1_MAINT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once

bool Bat_1_MAINT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once

uint8_t Bat1_Current_Mode_in_Maint = 0;      // 0 - Bat 1 is in running mode
// 1 - Bat 1 is in pause mode
// 2- Bat1 is in stop mode



// Flags to update the general information of battery 1 in Maintenance Use Case

uint16_t bat1_geninfo_cycle_counter = 0;
uint16_t bat1_geninfo_asoc_counter = 0;
uint16_t bat1_geninfo_remainingcapacity_counter = 0;
uint16_t bat1_geninfo_voltage_counter = 0;
uint16_t bat1_geninfo_temperature_counter = 0;
uint16_t bat1_geninfo_batterystatus_counter = 0;
uint16_t bat1_geninfo_current_counter=0;




bool bat1_geninfo_cycle_flag = false;
bool bat1_geninfo_asoc_flag = false;
bool bat1_geninfo_remainingcapacity_flag = false;
bool bat1_geninfo_voltage_flag = false;
bool bat1_geninfo_temperature_flag = false;
bool bat1_geninfo_batterystatus_flag = false;
bool bat1_geninfo_current_flag=false;

bool bat1_specific_info_rte_flag=true;

bool connect_flag=true;
bool update_maintenance_info_flag=false;

uint8_t tx_init[14];



// Flags to update the general information of battery in Maintenance Use Case

////////////////////////////////// Maintenance cycle BAT 1 definitions - End//////////////////////////////////////


/////////////////////// Maintenance cycle BAT 2 definitions - Start////////////////////////////////////////////

bool _bat2timerfunc = false;		     // Flag to start and stop the 15 min wait function
bool _bat2_15min_wait_over = false;  		// To indicate 15 min delay is over
uint16_t _bat2_counter_var = 0;				//   Variable as a counter
//int8_t bat2_state=0;  						// Indicates the current state in Maintenance cycle
//int8_t *BAT2_MAINT_STATE;
uint8_t BAT2_MAINT_STATE=0;

uint16_t BAT_2_ASOC_MAINTENANCE;
uint16_t BAT2_VOLTAGE_MAINTENANCE;

bool bat2charge = false;				// Flag to start and stop charging of the battery
bool bat2discharge = false;				// Flag to start and stop discharging of the battery


bool bat2_maint_state1guard = false;
bool bat2_maint_state2guard = false;
bool bat2_maint_state3guard = false;
bool bat2_maint_state4guard = false;
bool bat2_maint_state5guard = false;
bool bat2_maint_state6guard = false;
bool bat2_maint_state7guard = false;
bool bat2_maint_state8guard = false;

bool Bat2_Maint_Autotestflag = false;

bool BAT_2_MAINTENANCE_FLAG = false;  				// Flag for battery 1 to enter the maintenance process
bool BAT_2_MAINTENANCE_ENTERED_GUARD_FLAG = false;

bool BAT_2_MAINT_GENERAL_INFO_FLAG = false;
bool BAT_2_MAINT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once

bool Bat_2_MAINT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once

uint16_t bat2_geninfo_cycle_counter = 0;
uint16_t bat2_geninfo_asoc_counter = 0;
uint16_t bat2_geninfo_remainingcapacity_counter = 0;
uint16_t bat2_geninfo_voltage_counter = 0;
uint16_t bat2_geninfo_temperature_counter = 0;
uint16_t bat2_geninfo_batterystatus_counter = 0;
uint16_t bat2_geninfo_current_counter=0;




bool bat2_geninfo_cycle_flag = false;
bool bat2_geninfo_asoc_flag = false;
bool bat2_geninfo_remainingcapacity_flag = false;
bool bat2_geninfo_voltage_flag = false;
bool bat2_geninfo_temperature_flag = false;
bool bat2_geninfo_batterystatus_flag = false;
bool bat2_geninfo_current_flag=false;

bool bat2_specific_info_rte_flag=true;

bool bat2_update_maintenance_info_flag=false;

/////////////////////// Maintenance cycle BAT 2 definitions - END////////////////////////////////////////////

/////////////////////// Maintenance cycle BAT 3 definitions - Start////////////////////////////////////////////

bool _bat3timerfunc = false;		     // Flag to start and stop the 15 min wait function
bool _bat3_15min_wait_over = false;  		// To indicate 15 min delay is over
uint16_t _bat3_counter_var = 0;				//   Variable as a counter
//int8_t bat3_state=0;  						// Indicates the current state in Maintenance cycle
//int8_t *BAT3_MAINT_STATE;
uint8_t BAT3_MAINT_STATE=0;

uint16_t BAT_3_ASOC_MAINTENANCE;
uint16_t BAT3_VOLTAGE_MAINTENANCE;

bool bat3charge = false;				// Flag to start and stop charging of the battery
bool bat3discharge = false;				// Flag to start and stop discharging of the battery

bool bat3_maint_state1guard = false;
bool bat3_maint_state2guard = false;
bool bat3_maint_state3guard = false;
bool bat3_maint_state4guard = false;
bool bat3_maint_state5guard = false;
bool bat3_maint_state6guard = false;
bool bat3_maint_state7guard = false;
bool bat3_maint_state8guard = false;

bool Bat3_Maint_Autotestflag = false;

bool BAT_3_MAINTENANCE_FLAG = false;  				// Flag for battery 3 to enter the maintenance process
bool BAT_3_MAINTENANCE_ENTERED_GUARD_FLAG = false;

bool BAT_3_MAINT_GENERAL_INFO_FLAG = false;
bool BAT_3_MAINT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once

bool Bat_3_MAINT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once

uint16_t bat3_geninfo_cycle_counter = 0;
uint16_t bat3_geninfo_asoc_counter = 0;
uint16_t bat3_geninfo_remainingcapacity_counter = 0;
uint16_t bat3_geninfo_voltage_counter = 0;
uint16_t bat3_geninfo_temperature_counter = 0;
uint16_t bat3_geninfo_batterystatus_counter = 0;
uint16_t bat3_geninfo_current_counter=0;




bool bat3_geninfo_cycle_flag = false;
bool bat3_geninfo_asoc_flag = false;
bool bat3_geninfo_remainingcapacity_flag = false;
bool bat3_geninfo_voltage_flag = false;
bool bat3_geninfo_temperature_flag = false;
bool bat3_geninfo_batterystatus_flag = false;
bool bat3_geninfo_current_flag=false;

bool bat3_specific_info_rte_flag=true;

bool bat3_update_maintenance_info_flag=false;


bool say=true;



/////////////////////// Maintenance cycle BAT 3 definitions - End////////////////////////////////////////////


/////////////////////// Management cycle BAT 1 definitions - Start////////////////////////////////////////////

bool BAT_1_MANAGEMENT_FLAG = false;  // Flag to enter Bat 1 in Management Use Case

bool BAT_1_MANAGEMENT_ENTERED_GUARD_FLAG = false; // Flag to send instruction only once to Pi that Bat 1
												  // has entered Management Use Case

bool BAT_1_MANAGEMENT_GENERAL_INFO_FLAG = false; // Flag to display Bat 1 Management use case general Info

bool BAT_1_MANAGEMENT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once - Management use case

bool Bat_1_MANAGEMENT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once - Management use case

bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false; // Flag to start Keep Battery Alive cycle - Management use case

bool BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

uint16_t BAT_1_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle; // Read ASOC during "Keep Battery Alive" cycle - Management Use Case





// Bat 1 Management use case variables during shipment test cycle
uint16_t BAT_1_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;  // Read ASOC during shipment autotest cycle - Management Use Case

bool BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false; // Flag to enter the shipment cycle - Management Use case Bat 1

bool Bat1_Management_Shipment_testycycle_Autotestflag = false; // Flag to start Bat1 shipment test cycle - Management Use Case

bool Bat1_Management_Shipment_chg_dischg_to_30_percent_flag = false; // Flag to start Bat 1 Charge/Discharge to 30 % cycle - Shipment - Management Use Case

bool Bat1_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false; // Flag to Toggle the Charge / Discharge pin only once during 30 % cycle in Shipment - Management Use Case

bool Bat1_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = false;

uint8_t BAT1_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0; // Bat 1 state during Shipment Test cycle - Management Use Case

uint16_t BAT_1_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; // Read Bat 1 ASOC during Management use case - Shipment charge/ discharge to 30 % cycle


bool bat1_management_shipment_testcycle_state1guard = false;
bool bat1_management_shipment_testcycle_state2guard = false;
bool bat1_management_shipment_testcycle_state3guard = false;
bool bat1_management_shipment_testcycle_state4guard = false;
bool bat1_management_shipment_testcycle_state5guard = false;
bool bat1_management_shipment_testcycle_state6guard = false;
bool bat1_management_shipment_testcycle_state7guard = false;
bool bat1_management_shipment_testcycle_state8guard = false;



/////////////////////// Management cycle BAT 1 definitions - End////////////////////////////////////////////



/////////////////////// Management cycle BAT 2 definitions - Start////////////////////////////////////////////

bool BAT_2_MANAGEMENT_FLAG = false;  // Flag to enter Bat 2 in Management Use Case

bool BAT_2_MANAGEMENT_ENTERED_GUARD_FLAG = false; // Flag to send instruction only once to Pi that Bat 2
												  // has entered Management Use Case

bool BAT_2_MANAGEMENT_GENERAL_INFO_FLAG = false; // Flag to display Bat 2 Management use case general Info

bool BAT_2_MANAGEMENT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once - Management use case

bool Bat_2_MANAGEMENT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once - Management use case

bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false; // Flag to start Keep Battery Alive cycle - Management use case

bool BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

uint16_t BAT_2_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle; // Read ASOC during "Keep Battery Alive" cycle - Management Use Case


// Bat 2 Management use case variables during shipment test cycle
uint16_t BAT_2_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;  // Read Bat 2 ASOC during shipment autotest cycle - Management Use Case

bool BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false; // Flag to enter the shipment cycle - Management Use case Bat 2

bool Bat2_Management_Shipment_testycycle_Autotestflag = false; // Flag to start Bat2 shipment test cycle - Management Use Case

bool Bat2_Management_Shipment_chg_dischg_to_30_percent_flag = false; // Flag to start Bat 2 Charge/Discharge to 30 % cycle - Shipment - Management Use Case

bool Bat2_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false; // Flag to Toggle the Charge / Discharge pin only once during 30 % cycle in Shipment - Management Use Case

bool Bat2_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = false;

uint8_t BAT2_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0; // Bat 2 state during Shipment Test cycle - Management Use Case

uint16_t BAT_2_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; // Read Bat 2 ASOC during Management use case - Shipment charge/ discharge to 30 % cycle


bool bat2_management_shipment_testcycle_state1guard = false;
bool bat2_management_shipment_testcycle_state2guard = false;
bool bat2_management_shipment_testcycle_state3guard = false;
bool bat2_management_shipment_testcycle_state4guard = false;
bool bat2_management_shipment_testcycle_state5guard = false;
bool bat2_management_shipment_testcycle_state6guard = false;
bool bat2_management_shipment_testcycle_state7guard = false;
bool bat2_management_shipment_testcycle_state8guard = false;



/////////////////////// Management cycle BAT 2 definitions - End////////////////////////////////////////////




/////////////////////// Management cycle BAT 3 definitions - Start////////////////////////////////////////////

bool BAT_3_MANAGEMENT_FLAG = false;  // Flag to enter Bat 3 in Management Use Case

bool BAT_3_MANAGEMENT_ENTERED_GUARD_FLAG = false; // Flag to send instruction only once to Pi that Bat 3
												  // has entered Management Use Case

bool BAT_3_MANAGEMENT_GENERAL_INFO_FLAG = false; // Flag to display Bat 3 Management use case general Info

bool BAT_3_MANAGEMENT_GENERAL_INFO_GUARD_FLAG = false;    // Flag to display General Info only once - Management use case

bool Bat_3_MANAGEMENT_SPECIFIC_PARA_GUARD_FLAG = false;   // Flag to compare specific Info only once - Management use case

bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = false; // Flag to start Keep Battery Alive cycle - Management use case

bool BAT_3_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_GUARD_FLAG = false; // Flag to Enable Charge/ Discharge of Battery in Keep Battery Alive cycle once

uint16_t BAT_3_ASOC_MANAGEMENT_during_Keep_Bat_Alive_cycle; // Read ASOC during "Keep Battery Alive" cycle - Management Use Case


// Bat 3 Management use case variables during shipment test cycle
uint16_t BAT_3_ASOC_MANAGEMENT_during_Shipment_Test_Cycle;  // Read Bat 3 ASOC during shipment autotest cycle - Management Use Case

bool BAT3_MANAGEMENT_SHIPMENT_CYCLE_FLAG = false; // Flag to enter the shipment cycle - Management Use case Bat 2

bool Bat3_Management_Shipment_testycycle_Autotestflag = false; // Flag to start Bat3 shipment test cycle - Management Use Case

bool Bat3_Management_Shipment_chg_dischg_to_30_percent_flag = false; // Flag to start Bat 3 Charge/Discharge to 30 % cycle - Shipment - Management Use Case

bool Bat3_Management_Shipment_chg_dischg_to_30_percent_guard_flag = false; // Flag to Toggle the Charge / Discharge pin only once during 30 % cycle in Shipment - Management Use Case

bool Bat3_Manag_SpecificPara_during_Shipment_test_cycle_guard_flag = false;

uint8_t BAT3_MANAGEMENT_SHIPMENT_TEST_CYCLE_STATE=0; // Bat 3 state during Shipment Test cycle - Management Use Case

uint16_t BAT_3_ASOC_MANAGEMENT_during__SHIPMENT_TEST_CHARGE_DISCHARGE_30; // Read Bat 3 ASOC during Management use case - Shipment charge/ discharge to 30 % cycle


bool bat3_management_shipment_testcycle_state1guard = false;
bool bat3_management_shipment_testcycle_state2guard = false;
bool bat3_management_shipment_testcycle_state3guard = false;
bool bat3_management_shipment_testcycle_state4guard = false;
bool bat3_management_shipment_testcycle_state5guard = false;
bool bat3_management_shipment_testcycle_state6guard = false;
bool bat3_management_shipment_testcycle_state7guard = false;
bool bat3_management_shipment_testcycle_state8guard = false;



/////////////////////// Management cycle BAT 3 definitions - End////////////////////////////////////////////



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
	/* Implement your write code here, this is used by puts and printf for example */
	int i=0;
	for(i=0 ; i<len ; i++)
		ITM_SendChar((*ptr++));
	return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim4);        // Timer 4 for providing delay
	HAL_TIM_Base_Start_IT(&htim3);	   // Timer 3 for waiting purpose in the maintenance case
	HAL_TIM_Base_Start_IT(&htim2);	   // Timer 2 to update the maintenance use case parameters periodically



	if(HAL_I2C_IsDeviceReady(&hi2c1,0x16, 5, 10)==HAL_OK)   // BAT 1
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);


	}

	if(HAL_I2C_IsDeviceReady(&hi2c2,0x16, 5, 10)==HAL_OK)   // BAT 2
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);


	}

	if(HAL_I2C_IsDeviceReady(&hi2c3,0x16, 5, 10)==HAL_OK)  // BAT 3
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);


	}

	//printf("Started \n");

	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);

//	BAT1_MAINT_STATE = &bat1_state;
//	BAT2_MAINT_STATE = &bat2_state;
//	BAT3_MAINT_STATE = &bat3_state;



//	__NVIC_SystemReset();

//	uint8_t uo=3;

//	int nn=uo/0;

//	int x = sizeof(uo);


//	Transmit_Bat2_Maintenance_General_Info_to_Raspi();
//	Read_and_Compare_Specific_para_Bat2_STM_to_Pi();
//	Read_bat3_maint_Run_time_to_empty_start_of_discharge();
//	Read_bat3_maint_Run_time_to_empty_end_of_discharge();
//	Read_Bat3_Maint_autotest_result_first_80_percent();
//	Read_Bat3_Maint_autotest_result_middle_10_percent();
//	Read_Bat3_Maint_autotest_result_last_80_percent();

//Transmit_Bat3_Maintenance_General_Info_to_Raspi();
//Read_and_Compare_Specific_para_Bat3_STM_to_Pi();
//Read_bat3_maint_Run_time_to_empty_start_of_discharge();
//Read_bat3_maint_Run_time_to_empty_end_of_discharge();
//Read_Bat1_Maint_autotest_result_first_80_percent();
//Read_Bat1_Maint_autotest_result_middle_10_percent();
//Read_Bat1_Maint_autotest_result_last_80_percent();
//Transmit_Bat3_Maintenance_General_Info_to_Raspi();

//	Transmit_Bat1_Maintenance_General_Info_to_Raspi();

//	Read_and_Compare_Specific_para_Bat1_STM_to_Pi();


//	BAT_1_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG = true;
//	bat2charge = true;
//	gpio_func();
//	gpio_func_bat2_chg_dschg();

//	Bat1_Management_Shipment_testycycle_Autotestflag = true;
//	BAT1_MANAGEMENT_SHIPMENT_CYCLE_FLAG = true;
	//Bat1_Management_Shipment_chg_dischg_to_30_percent_flag = true;

//	Read_Bat1_Management_Shipment_autotest_result_first_80_percent();
//	Read_Bat1_Management_Shipment_autotest_result_middle_10_percent();
//	Read_Bat1_Management_Shipment_autotest_result_last_80_percent();

//	Transmit_Bat1_Management_General_Info_to_Raspi();
//	Read_and_Compare_Specific_para_Bat1_Management_Shipment_Test_STM_to_Pi();
//	Read_Bat1_Management_Shipment_autotest_result_first_80_percent();
//	Read_Bat1_Management_Shipment_autotest_result_middle_10_percent();
//	Read_Bat1_Management_Shipment_autotest_result_last_80_percent();
////
//	Read_bat1_management_Run_time_to_empty_Shipment_Test_Cycle_start_of_discharge();
//	Read_bat1_management_Run_time_to_empty_Shipment_Test_Cycle_end_of_discharge();

//	Transmit_Bat1_Management_General_Info_to_Raspi();
//	Transmit_Bat2_Management_General_Info_to_Raspi();

	//Read_and_Compare_Specific_para_Bat1_Management_Shipment_Test_STM_to_Pi();
	//Read_and_Compare_Specific_para_Bat2_Management_Shipment_Test_STM_to_Pi();

//		Read_bat2_management_Run_time_to_empty_Shipment_Test_Cycle_start_of_discharge();
//		Read_bat2_management_Run_time_to_empty_Shipment_Test_Cycle_end_of_discharge();

//		BAT_2_MANAGEMENT_FLAG = true;
//		BAT2_MANAGEMENT_SHIPMENT_CYCLE_FLAG = true;
//		Bat2_Management_Shipment_testycycle_Autotestflag=true;
//		Bat2_Management_Shipment_chg_dischg_to_30_percent_flag = true;
//	BAT_2_MANAGEMENT_KEEP_BATTERY_ALIVE_CYCLE_FLAG=true;


//		Transmit_Bat3_Management_General_Info_to_Raspi();
//		Send_Bat3_Management_Specific_Info_To_Pi();
//		 Read_and_Compare_Specific_para_Bat3_Management_Shipment_Test_STM_to_Pi();
//
////
//		 Read_bat3_management_Run_time_to_empty_Shipment_Test_Cycle_start_of_discharge();
//		 Read_bat3_management_Run_time_to_empty_Shipment_Test_Cycle_end_of_discharge();

//			Read_Bat3_Management_Shipment_autotest_result_first_80_percent();
//			Read_Bat3_Management_Shipment_autotest_result_middle_10_percent();
//			Read_Bat3_Management_Shipment_autotest_result_last_80_percent();

  /* USER CODE END 2 */


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
//		connect_to_Pi();
//		Bat2_Management_Shipment_Cycle_Charge_Discharge_to_30();
//		Bat2_Management_Keep_Battery_Alive_Cycle();
//		substatemachine_battery1_management();

//		Bat1_Management_Keep_Battery_Alive_Cycle();
//		substatemachine_battery1_maintenance(); // This function Works
//		substatemachine_battery2_maintenance(); // This function Works
//		substatemachine_battery3_maintenance();


	//	NVIC_SystemReset(); // Works

//		Battery1_Management_Use_Case_Shipment_Test_Cycle();
//
//		Bat1_Management_Shipment_Cycle_Charge_Discharge_to_30();
//
//		Bat1_Management_Keep_Battery_Alive_Cycle();
//		 update_voltage_during_management_bat1();
//		 update_asoc_during_management_bat1();
//		 update_RemCap_during_management_bat1();
//		 update_cyclecount_during_management_bat1();
//		 update_batstatus_during_management_bat1();
//		 update_temperature_during_management_bat1();

//		Send_Bat1_Management_Specific_Info_To_Pi();

//		 update_voltage_during_management_bat2();
//		 update_asoc_during_management_bat2();
//		 update_RemCap_during_management_bat2();
//		 update_cyclecount_during_management_bat2();
//		 update_batstatus_during_management_bat2();
//		 update_temperature_during_management_bat2();
//		 update_current_during_management_bat2();

//		Battery2_Management_Use_Case_Shipment_Test_Cycle();
//		substatemachine_battery2_management();

//		 update_voltage_during_management_bat3();
//		 update_asoc_during_management_bat3();
//		 update_RemCap_during_management_bat3();
//		 update_cyclecount_during_management_bat3();
//		 update_batstatus_during_management_bat3();
//		 update_temperature_during_management_bat3();
//		 update_current_during_management_bat3();
//		substatemachine_battery1_management();
//		substatemachine_battery2_management();
//		substatemachine_battery3_management();
		update_current_during_management_bat1();
		update_current_during_management_bat2();
		update_current_during_management_bat3();

//		update_current_during_maintenance_bat1();
//		update_current_during_maintenance_bat2();
//		update_current_during_maintenance_bat3();



	}
}



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_I2C3;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00808CD2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00808CD2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00808CD2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7200-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC5 PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB12 PB13 PB14
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PD8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  // 16-bit TIM3 is used as an interrupt - every 10 ms
{
	if(htim==&htim3)
	{
		Timer_15min();

	}

	if(htim==&htim2)  // Configured as an interrupt - every 100 ms
	{


		update_periodic_flags_during_maintenance_bat1();
		update_periodic_flags_during_maintenance_bat2();
		update_periodic_flags_during_maintenance_bat3();

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Prevent unused argument(s) compilation warning */
	// UNUSED(huart);


	commands_from_pi_to_stm();


}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
