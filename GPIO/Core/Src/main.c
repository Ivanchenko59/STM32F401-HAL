/*
 * main.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ivanc
 */

#include "main.h"

#include "gpio.h"
#include "exti.h"

void SystemClock_Config(void);

uint8_t btn_interrupt_flag = 0;

int main(void)
{
	HAL_Init();

	SystemClock_Config();
	GPIO_LED_Config();
	GPIO_BTN_Config();
	EXTI_BTN_Config();

    while(1) {
    	if (GPIO_BTN_ReadPin() == GPIO_PIN_SET) {
    		//GPIO_LED_WritePin(GPIO_PIN_SET);
    	}
    	else {
    	//GPIO_LED_WritePin(GPIO_PIN_RESET);
    	}
//    	uint8_t prev_state = GPIO_BTN_ReadPin();
//    	if (prev_state != GPIO_BTN_ReadPin()) GPIO_LED_TogglePin();

    	if (btn_interrupt_flag) {
    		GPIO_LED_TogglePin();
    		btn_interrupt_flag = 0;
//    		EXTI->IMR |= EXTI_IMR_IM0;
    	}
    }

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0) {
		btn_interrupt_flag = 1;
//		EXTI->IMR &= ~EXTI_IMR_IM0;
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //Error_Handler();
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
    //Error_Handler();
  }
}
