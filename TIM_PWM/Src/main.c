#include "main.h"

/*
 * https://istarik.ru/blog/stm32/118.html
 * https://deepbluembedded.com/stm32-pwm-example-timer-pwm-mode-tutorial/
 *
 */

TIM_HandleTypeDef htim1;

void SystemClock_Config(void);
void GPIO_LED_Config(void);
void TIM1_Init(void);
void TIM_GPIO_Config(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_LED_Config();
	TIM_GPIO_Config();
	TIM1_Init();

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	uint16_t duty_cycle = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2);
	while(1) {
		while(duty_cycle < __HAL_TIM_GET_AUTORELOAD(&htim1)) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty_cycle++);
			HAL_Delay(1);
		}
		while(duty_cycle > 0) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty_cycle--);
			HAL_Delay(1);
		}
    }
}

void TIM1_Init(void)
{
	__HAL_RCC_TIM1_CLK_ENABLE();

	TIM_OC_InitTypeDef sConfigOC;

	htim1.Instance = TIM1;
	htim1.Init.Period = 500;
	htim1.Init.Prescaler = 2;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(&htim1);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
}

void TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpioInitStruct.Pin = GPIO_PIN_9;
	gpioInitStruct.Mode = GPIO_MODE_AF_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_HIGH;
	gpioInitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}

void GPIO_LED_Config(void)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	gpioInitStruct.Pin = GPIO_PIN_13;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
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
//    Error_Handler();
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
//    Error_Handler();
  }
}
