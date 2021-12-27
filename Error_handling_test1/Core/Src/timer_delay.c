/*
 * timer_delay.c
 *
 *  Created on: Nov 11, 2021
 *      Author: shubham
 */


#include "stm32f7xx_hal.h"
#include "timer_delay.h"

extern TIM_HandleTypeDef htim4;


void usdelay (uint32_t us)
{
	__HAL_TIM_SET_COUNTER(&htim4,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim4) < us);  // wait for the counter to reach the us input in the parameter
}

void msdelay(uint32_t ms)
{
	for(uint32_t i=0;i<ms;i++)
	{
		usdelay(1000);                  // 1ms delay
	}
}


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
