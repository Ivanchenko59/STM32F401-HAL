/*
 * RECEIVE
 * https://controllerstech.com/uart-receive-in-stm32/
 *
 * TRANSMIT
 * https://controllerstech.com/uart-transmit-in-stm32/
 *
 */


#include "main.h"

void SystemClock_Config(void);
void UART1_GPIOInit(void);
void UART1_Init(void);
void GPIO_LED_Config(void);
uint8_t data_TX[] = "Hello UART\n";
uint8_t data_RX[4];
uint8_t status;

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	UART1_GPIOInit();
	UART1_Init();
	GPIO_LED_Config();

	HAL_UART_Receive_IT(&huart1, data_RX, 4);

    while(1) {
//    	status = HAL_UART_Transmit_IT(&huart1, data_TX, sizeof(data_TX));
//    	HAL_Delay(13);
//    	if(status == HAL_BUSY)
//    		while(1);

//    	HAL_UART_Receive(&huart1, data_RX, 4, HAL_MAX_DELAY);



    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    	HAL_Delay(250);
    }
}


void UART1_Init(void)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart1);
}

void UART1_GPIOInit(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(&huart1, data_RX, 4);
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
