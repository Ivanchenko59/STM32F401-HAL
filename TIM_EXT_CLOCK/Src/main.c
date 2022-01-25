#include "main.h"

/*
 * https://istarik.ru/blog/stm32/118.html
 * https://deepbluembedded.com/stm32-counter-mode-example-frequency-counter-timer-in-counter-mode/
 *
 */


void SystemClock_Config(void);
void GPIO_LED_Config(void);
void GPIO_TIM_Clock_Config(void);
void GPIO_Clock_Source_Config(void);
void TIM1_Init(void);

TIM_HandleTypeDef htim1;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_LED_Config();
	GPIO_Clock_Source_Config();
	GPIO_TIM_Clock_Config();
	TIM1_Init();

	HAL_TIM_Base_Start_IT(&htim1);

    while(1) {
    	//Clocking signal
    	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    	HAL_Delay(500);

    }
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
// HAL Callback when UEV event
	if(htim->Instance == TIM1)
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void TIM1_Init(void)
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.Period = 10;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&htim1);

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
	sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
	sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
	sClockSourceConfig.ClockFilter = 0;
	HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);

}

void GPIO_TIM_Clock_Config(void)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpioInitStruct.Pin = GPIO_PIN_12;
	gpioInitStruct.Mode = GPIO_MODE_AF_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_HIGH;
	gpioInitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}

void GPIO_Clock_Source_Config(void)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	gpioInitStruct.Pin = GPIO_PIN_0;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &gpioInitStruct);
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
