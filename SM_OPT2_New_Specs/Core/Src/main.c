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
#include "timer_delay.h"
#include "Getbattery1asoc.h"
#include "Handle_Gpio_pins.h"
#include "Timer_function.h"

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

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

// Maintenance cycle BAT 1 definitions

bool _bat1timerfunc = false;		// Flag to start and stop the 15 min wait function
bool _bat1_15min_wait_over = false;  		// To indicate 15 min delay is over
uint16_t _bat1_counter_var = 0;				//   Variable as a counter
int8_t bat1_state=0;  						// Indicates the current state in Maintenance cycle






uint16_t BAT_1_ASOC_VALUE;

bool bat1charge = false;				// Flag to start and stop charging of the battery
bool bat1discharge = false;				// Flag to start and stop discharging of the battery

bool state1guard = false;
bool state2guard = false;
bool state3guard = false;
bool state4guard = false;
bool state5guard = false;
bool state6guard = false;
bool state7guard = false;

bool Autotestflag = true;				// Flag to start automatic testing of the maintenance cycle

uint8_t rx_buffer[3];


// Maintenance cycle BAT 1 definitions - End

// Flags to update the general information of battery in Maintenance Use Case

uint16_t bat1_geninfo_cycle_counter = 0;
uint16_t bat1_geninfo_asoc_counter = 0;
uint16_t bat1_geninfo_remainingcapacity_counter = 0;
uint16_t bat1_geninfo_voltage_counter = 0;
uint16_t bat1_geninfo_temperature_counter = 0;
uint16_t bat1_geninfo_batterystatus_counter = 0;




bool bat1_geninfo_cycle_flag = false;
bool bat1_geninfo_asoc_flag = false;
bool bat1_geninfo_remainingcapacity_flag = false;
bool bat1_geninfo_voltage_flag = false;
bool bat1_geninfo_temperature_flag = false;
bool bat1_geninfo_batterystatus_flag = false;

// Flags to update the general information of battery in Maintenance Use Case



uint8_t tx_asoc[1]={0x0E}; 					// 0x0E   Command to get ASOC of the battery
uint8_t tx_voltage[1]={0x09};				// 0x09   Command to get battery voltage
uint8_t tx_current[1]={0x0A};				// 0x0A   Command to get battery current
uint8_t tx_temperature[1]={0x08};			// 0x08
uint8_t tx_battery_status[1]={0x16};		// 0x16
uint8_t tx_remaining_capacity[1]={0x0F};	// 0x0F
uint8_t tx_cyclecount[1]={0x17};			// 0x17
uint8_t tx_serial_number[1]={0x1C};			// 0x1C
uint8_t tx_manufacturer_date[1]={0x1B};		// 0x1B
uint8_t tx_full_charge_capacity[1]={0x10};	// 0x10
uint8_t tx_design_capacity[1]={0x18};		// 0x18
uint8_t tx_run_timet_to_empty[1]={0x11};	// 0x11




uint16_t Bat1_Volt_Maint_GI;  //16 bit value
uint8_t Bat1_Asoc_Maint_GI;   // 8 bit value
int16_t Bat1_Temperature_Maint_GI;
uint16_t Bat1_RemCapacity_Maint_GI;
uint16_t Bat1_Cyclecount_Maint_GI;

float temp;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim4);        // Timer 4 for providing delay
	HAL_TIM_Base_Start_IT(&htim3);	   // Timer 3 for waiting purpose in the maintenance case
	HAL_TIM_Base_Start_IT(&htim2);	   // Timer 2 to update the maintenance use case parameters periodically


	if(HAL_I2C_IsDeviceReady(&hi2c1,0x16, 5, 10)==HAL_OK)
	{

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);


	}


	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);

	/* USER CODE END 2 */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{

		// Maintenance cycle
		//	  		switch(bat1_state)
		//	  		{
		//
		//	  		case 0:
		//
		//	  			bat1charge = false;
		//	  			bat1discharge = false;
		//	  			gpio_func();
		//
		//	  			if(Autotestflag==true)
		//	  			{
		//	  				getbattery1asoc();
		//	  				if(BAT_1_ASOC_VALUE==77)
		//	  				{
		//	  					bat1_state = 1;
		//	  				}
		//
		//	  				else if(BAT_1_ASOC_VALUE <77)
		//	  				{
		//	  					bat1_state = 2;
		//	  				}
		//
		//	  				else if(BAT_1_ASOC_VALUE >77)
		//	  				{
		//	  					bat1_state = 3;
		//	  				}
		//	  			}
		//
		//	  			break;
		//
		//	  		case 1:
		//
		//	  			if(state1guard == false)
		//	  			{
		//	  				bat1charge = false;
		//	  				bat1discharge = false;
		//	  				gpio_func();
		//	  				_bat1timerfunc = true;
		//	  				state1guard = true;
		//	  			}
		//
		//	  			else if(state1guard == true)
		//	  			{
		//	  				if(_bat1_15min_wait_over==true)
		//	  				{
		//	  					bat1_state = 4;
		//	  					state1guard = false;
		//	  				}
		//	  			}
		//
		//	  			break;
		//
		//	  		case 2:
		//
		//	  			if(state2guard == false)
		//	  			{
		//	  				bat1charge = true;
		//	  				bat1discharge = false;
		//	  				gpio_func();
		//	  				state2guard = true;
		//	  			}
		//
		//	  			else if(state2guard == true)
		//	  			{
		//	  				getbattery1asoc();
		//	  				if(BAT_1_ASOC_VALUE == 77)
		//	  				{
		//	  					bat1_state = 1;
		//	  					state2guard = false;
		//	  				}
		//	  			}
		//	  			break;
		//
		//
		//
		//
		//	  		case 3:
		//	  			if(state3guard == false)
		//	  			{
		//	  				bat1discharge = true;
		//	  				bat1charge = false;
		//	  				gpio_func();
		//	  				state3guard = true;
		//	  			}
		//
		//	  			else if(state3guard == true)
		//	  			{
		//	  				getbattery1asoc();
		//	  				if(BAT_1_ASOC_VALUE == 77)
		//	  				{
		//	  					bat1_state = 1;
		//	  					state3guard = false;
		//	  				}
		//	  			}
		//	  			break;
		//
		//	  		case 4:
		//
		//	  			if(state4guard==false)
		//	  			{
		//	  				bat1discharge = true;
		//	  				bat1charge = false;
		//	  				gpio_func();
		//	  				state4guard = true;
		//	  				_bat1timerfunc=false;
		//	  				_bat1_15min_wait_over=false;
		//	  				_bat1_counter_var = 0;
		//	  			}
		//
		//	  			else if(state4guard==true)
		//	  			{
		//
		//	  				getbattery1asoc();
		//	  				if(BAT_1_ASOC_VALUE==75)
		//	  				{
		//	  					bat1_state = 5;
		//	  					state4guard=false;
		//	  				}
		//
		//	  			}
		//	  			break;
		//
		//	  		case 5:
		//	  			if(state5guard==false)
		//	  			{
		//	  				bat1charge=false;
		//	  				bat1discharge=false;
		//	  				gpio_func();
		//	  				_bat1timerfunc=true;
		//	  				state5guard=true;
		//	  			}
		//	  			else if(state5guard==true)
		//	  			{
		//
		//	  				if(_bat1_15min_wait_over==true)
		//	  				{
		//	  					bat1_state=6;
		//	  					state5guard=false;
		//	  				}
		//	  			}
		//	  			break;
		//
		//	  		case 6:
		//	  			if(state6guard == false)
		//	  			{
		//	  				bat1charge=true;
		//	  				bat1discharge=false;
		//	  				gpio_func();
		//	  				state6guard = true;
		//	  				_bat1timerfunc = false;
		//	  				_bat1_15min_wait_over=false;
		//	  				_bat1_counter_var = 0;
		//	  			}
		//	  			else if(state6guard==true)
		//	  			{
		//	  				getbattery1asoc();
		//	  				if(BAT_1_ASOC_VALUE==77)
		//	  				{
		//	  					bat1_state=7;
		//	  					state6guard=false;
		//	  				}
		//	  			}
		//	  			break;
		//
		//	  		case 7:
		//	  			if(state7guard==false)
		//	  			{
		//	  				bat1discharge=false;
		//	  				bat1charge=false;
		//	  				gpio_func();
		//	  				_bat1timerfunc=true;
		//	  				state7guard=true;
		//
		//	  			}
		//	  			else if(state7guard==true)
		//	  			{
		//	  				if(_bat1_15min_wait_over==true)
		//	  				{
		//	  					bat1_state=0;
		//	  					state7guard=false;
		//	  					_bat1timerfunc=false;
		//	  					_bat1_15min_wait_over=false;
		//	  					_bat1_counter_var = 0;
		//	  					Autotestflag = false;
		//
		//	  				}
		//	  			}
		//	  			break;
		//
		//	  		default:
		//	  			bat1_state = 0;
		//	  			break;
		//	  		}
		//
		//	  		msdelay(10);

		// Maintenance cycle End /////////////////////




		//HAL_UART_Transmit_IT(&huart2, tx, 2);
		//msdelay(100);

		/* Works with GUI on the Pi Start

		uint8_t tx[1]={0x09};
		uint8_t rx[2]={0x00};

		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx, 1);
		msdelay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx, 2);
		msdelay(1);

		voltage = rx[1];
		voltage = voltage << 8; //--
		voltage  = voltage + rx[0]; //--




		uint8_t tx2[1]={0x0A};
		uint8_t rx2[2]={0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx2, 1);
		msdelay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx2, 2);
		msdelay(1);
		 current  = rx2[1];
		current = current << 8;
		current = current  + rx2[0];


		uint8_t tx3[1]={0x0D};
		uint8_t rx3[1]={0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx3, 1);
		msdelay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx3,2);
		msdelay(1);
		 rsoc  = rx3[0];




		uint8_t tx6[1]={0x0E};
		uint8_t rx6[2]={0x00};
		HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx6, 1);
		msdelay(5);
		HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx6, 2);
		msdelay(1);
		 asoc  = rx6[0];


		uint8_t t2x[6];
		t2x[0]=rx[1];
		t2x[1]=rx[0];
		t2x[2]=rx2[1];
		t2x[3]=rx2[0];
		t2x[4]=rx3[0];
		t2x[5]=rx6[0];


		HAL_UART_Transmit_IT(&huart2, t2x, 6);
		msdelay(500);
		rx6[0]=0;

		rx3[0]=0;

		rx2[0]=0;
		rx2[1]=0;
		rx[1]=0;
		rx[0]=0;
 Works with GUI on the Pi end
		 */







		// Update ASOC  -  General Info Bat 1 Maintenance Use Case
		if(bat1_geninfo_asoc_flag==true)
		{
			bat1_geninfo_asoc_flag=false;

			uint8_t rx_geninfo_asoc[1]={0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_asoc, 1);
			msdelay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_asoc, 1);
			msdelay(1);
			Bat1_Asoc_Maint_GI= rx_geninfo_asoc[0];

			uint8_t transmit_asoc[2]={0x00};
			transmit_asoc[0]='A';
			transmit_asoc[1]=rx_geninfo_asoc[0];
			HAL_UART_Transmit_IT(&huart2, transmit_asoc, 2);
			rx_geninfo_asoc[0]=0;


		}

		// Update Voltage  -  General Info Bat 1 Maintenance Use Case
		if(bat1_geninfo_voltage_flag==true)
		{
			bat1_geninfo_voltage_flag=false;

			uint8_t rx_geninfo_voltage[2]={0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_voltage, 1);
			msdelay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_voltage, 2);
			msdelay(1);
			Bat1_Volt_Maint_GI = rx_geninfo_voltage[1];
			Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI << 8;
			Bat1_Volt_Maint_GI = Bat1_Volt_Maint_GI + rx_geninfo_voltage[0];

			uint8_t transmit_volt[3]={0x00};
			transmit_volt[0]='V';
			transmit_volt[1]=rx_geninfo_voltage[1];
			transmit_volt[2]=rx_geninfo_voltage[0];
			HAL_UART_Transmit_IT(&huart2, transmit_volt, 3);
			rx_geninfo_voltage[0]=0;
			rx_geninfo_voltage[1]=0;

		}

		// Update Remaining Capacity - General Info Bat 1 Maintenance Use Case

		if(bat1_geninfo_remainingcapacity_flag==true)
		{
			bat1_geninfo_remainingcapacity_flag=false;

			uint8_t rx_geninfo_remcapacity[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16, tx_remaining_capacity, 1);
			msdelay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_remcapacity, 2);
			msdelay(1);
			Bat1_RemCapacity_Maint_GI = rx_geninfo_remcapacity[1];
			Bat1_RemCapacity_Maint_GI = Bat1_RemCapacity_Maint_GI << 8;
			Bat1_RemCapacity_Maint_GI = Bat1_RemCapacity_Maint_GI + rx_geninfo_remcapacity[0];

			uint8_t transmit_remcapacity[3]={0x00,0x00};
			transmit_remcapacity[0]='R';
			transmit_remcapacity[1]=rx_geninfo_remcapacity[1];
			transmit_remcapacity[2]=rx_geninfo_remcapacity[0];
			HAL_UART_Transmit_IT(&huart2, transmit_remcapacity, 3);
			rx_geninfo_remcapacity[0]=0;
			rx_geninfo_remcapacity[1]=0;




		}

		// Update Temperature - General Info Bat 1 Maintenance Use Case

		if(bat1_geninfo_temperature_flag==true)
		{
			bat1_geninfo_temperature_flag=0;

			uint8_t	rx_geninfo_temperature[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_temperature, 1);
			msdelay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_geninfo_temperature, 2);
			msdelay(1);
			Bat1_Temperature_Maint_GI = rx_geninfo_temperature[1];
			Bat1_Temperature_Maint_GI = Bat1_Temperature_Maint_GI << 8;
			Bat1_Temperature_Maint_GI = Bat1_Temperature_Maint_GI + rx_geninfo_temperature[0];
			temp = (float)(Bat1_Temperature_Maint_GI/10.0)-273.15;

			uint8_t transmit_temperature[3]={0x00,0x00};
			transmit_temperature[0]='T';
			transmit_temperature[1]=rx_geninfo_temperature[1];
			transmit_temperature[2]= rx_geninfo_temperature[0];
			HAL_UART_Transmit_IT(&huart2, transmit_temperature, 3);
			rx_geninfo_temperature[1]=0;
			rx_geninfo_temperature[0]=0;

		}

		// Update Cycle Count - General Info Bat 1 Maintenance Use Case

		if(bat1_geninfo_cycle_flag==true)
		{
			bat1_geninfo_cycle_flag= false;

			uint8_t rx_getinfo_cyclecount[2]={0x00,0x00};
			HAL_I2C_Master_Transmit_IT(&hi2c1, 0x16,tx_cyclecount, 1);
			msdelay(5);
			HAL_I2C_Master_Receive_IT(&hi2c1, 0x16, rx_getinfo_cyclecount, 2);
			msdelay(1);
			Bat1_Cyclecount_Maint_GI = rx_getinfo_cyclecount[1];
			Bat1_Cyclecount_Maint_GI = Bat1_Cyclecount_Maint_GI << 8;
			Bat1_Cyclecount_Maint_GI = Bat1_Cyclecount_Maint_GI + rx_getinfo_cyclecount[0];

			uint8_t transmit_cyclecount[3]={0x00,0x00};
			transmit_cyclecount[0]='C';
			transmit_cyclecount[1]=rx_getinfo_cyclecount[1];
			transmit_cyclecount[2]=rx_getinfo_cyclecount[0];
			HAL_UART_Transmit_IT(&huart2, transmit_cyclecount, 3);
			rx_getinfo_cyclecount[1]=0;
			rx_getinfo_cyclecount[0]=0;

		}

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
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
	PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
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
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
			|GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pins : PB0 PB12 PB13 PB14
                           PB7 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
			|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  // 16-bit TIM3 is used as an interrupt - every 10 ms
{
	if(htim==&htim3)
	{
		Timer_15min();

	}

	if(htim==&htim2)
	{

		bat1_geninfo_asoc_counter++;
		bat1_geninfo_voltage_counter++;
		bat1_geninfo_remainingcapacity_counter++;
		bat1_geninfo_temperature_counter++;
		bat1_geninfo_cycle_counter++;


		if(bat1_geninfo_asoc_counter==100)
		{
			bat1_geninfo_asoc_counter=0;
			bat1_geninfo_asoc_flag=true;
		}

		if(bat1_geninfo_voltage_counter==50)  // update time - 2 minutes
		{
			bat1_geninfo_voltage_counter=0;
			bat1_geninfo_voltage_flag=true;
		}

		if(bat1_geninfo_remainingcapacity_counter==70)
		{
			bat1_geninfo_remainingcapacity_counter=0;
			bat1_geninfo_remainingcapacity_flag=true;
		}
		if(bat1_geninfo_temperature_counter==10)
		{
			bat1_geninfo_temperature_counter=0;
			bat1_geninfo_temperature_flag=true;
		}
		if(bat1_geninfo_cycle_counter==400)
		{
			bat1_geninfo_cycle_counter=0;
			bat1_geninfo_cycle_flag=true;
		}



	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Prevent unused argument(s) compilation warning */
	// UNUSED(huart);
	if(rx_buffer[0]=='B' && rx_buffer[1]=='1' && rx_buffer[2]=='M')
	{
		Autotestflag=true;
	}
	else
	{
		Autotestflag=false;
	}

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
