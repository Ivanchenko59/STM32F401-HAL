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
void GPIO_LED_Config(void);

/*
 * @brief LED write state
 */
void GPIO_LED_WritePin(uint8_t state);
/*
 * @brief LED toggle
 */
void GPIO_LED_TogglePin(void);

/*
 * @brief Button GPIO configuration
 */
void GPIO_BTN_Config(void);

/*
 * @brief Read button pin state
 */
GPIO_PinState GPIO_BTN_ReadPin(void);


#endif /* INC_GPIO_H_ */
