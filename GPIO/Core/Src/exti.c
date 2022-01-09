/*
 * exti.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ivanc
 */

#include "exti.h"

void EXTI_BTN_Config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpioInitStruct = {0};
	gpioInitStruct.Pin = GPIO_PIN_0;
	gpioInitStruct.Mode = GPIO_MODE_IT_RISING;
	gpioInitStruct.Pull = GPIO_PULLUP;
	gpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);

	//Enable Interrupt
	HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
