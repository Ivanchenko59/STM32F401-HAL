/*
 * gpio.h
 *
 *  Created on: Jan 7, 2022
 *      Author: ivanc
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

/*
 * @brief LED GPIO configuration
 */
void GPIO_Config(void);

/*
 * LED write state
 */
void GPIO_WritePin(uint8_t state);
/*
 * LED toggle
 */
void GPIO_TogglePin(void);

#endif /* INC_GPIO_H_ */
