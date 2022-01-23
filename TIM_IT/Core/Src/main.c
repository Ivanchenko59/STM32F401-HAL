#include "main.h"

void SystemClock_Config(void);
void GPIO_LED_Config(void);

TIM_HandleTypeDef htim9;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_LED_Config();

	htim9.Instance = TIM9;
	htim9.Init.Prescaler = 41999; 		// 84MHz / 42000 = 2000 Hz
	htim9.Init.Period = 999;			// 2000 Hz / 1000 = 2 Hz = 0.5 s

	__HAL_RCC_TIM9_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

	HAL_TIM_Base_Init(&htim9);
	HAL_TIM_Base_Start_IT(&htim9);

    while(1) {

    }
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim9);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
// HAL Callback when UEV event
	if(htim->Instance == TIM9)
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
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
