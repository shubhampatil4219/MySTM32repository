/*
 * Handle_Gpio_pins.h
 *
 *  Created on: Oct 29, 2021
 *      Author: shubham
 */

#ifndef INC_HANDLE_GPIO_PINS_H_
#define INC_HANDLE_GPIO_PINS_H_

#include "stm32f7xx_hal.h"

void gpio_func();

void gpio_func_bat2_chg_dschg();
void gpio_func_bat3_chg_dschg();

#endif /* INC_HANDLE_GPIO_PINS_H_ */
