/*
 * gpio.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ivanc
 */

#include "gpio.h"


void GPIO_Config(void)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	gpioInitStruct.Pin = GPIO_PIN_13;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

void GPIO_WritePin(uint8_t state)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)state);
}

void GPIO_TogglePin(void)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
