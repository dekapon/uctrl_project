/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
enum Speed {Slow = 1999, Medium = 299, Fast = 139};
enum Dir{Right, Left};
bool isHoming = false;
bool isEndstopTriggered = false;
void startTimer(){
	HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_3);
}

void stopTimer(){
	HAL_TIM_OC_Stop(&htim2, TIM_CHANNEL_3);
}

char receivedMessage;
char messageToSend;

void sendMessage(char *messageToSend){
	char * messageEnding = "\r\n";
	int messageLen = strlen(messageToSend) + strlen(messageEnding);
	char * message = malloc(messageLen);
	strcpy(message, messageToSend);
	strcat(message, messageEnding);
	HAL_UART_Transmit(&huart2, (uint8_t*)message, messageLen, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart4, (uint8_t*)message, messageLen, HAL_MAX_DELAY);
	free(message);
}
void turnmot(int speed, int time, int dir){
	/*for (int i = 1; i < 2000; ++i)
	  {
		HAL_GPIO_TogglePin(motStep_GPIO_Port, motStep_Pin);
		HAL_Delay(2);
	  }*/
	if(dir == 1){
		HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, 1);
	}
	else{
		HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, 0);
	}
	startTimer();
	TIM2->PSC = speed;
	HAL_Delay(time);
	stopTimer();
}

void goHome(){
	HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, Left);
	startTimer();
	//HAL_GPIO_WritePin(eV1_GPIO_Port, eV1_Pin, 1);
	TIM2->PSC = Medium;
	while(isEndstopTriggered != true){
	}
	sendMessage("triggered !");
	HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, Right);
	startTimer();
	TIM2->PSC = Slow;
	HAL_Delay(500);
	stopTimer();
	isEndstopTriggered = false;
	sendMessage("done !");
	//HAL_GPIO_WritePin(eV1_GPIO_Port, eV1_Pin, 0);
}

void smoothTurn(int pres){
	startTimer();
	int max = 200000;
	double percent;
	/*for (int i = 1; i < max; ++i)
	{
		percent = (double)i / (double)max;
		if (percent*(double)100 > 20){
			TIM2->PSC = (int)(percent * (double)pres);
		}

	}*/
	for (int i = 1; i < max; ++i)
		{
			percent = (double)i / (double)max;
			if (percent*(double)100 > 20){
				TIM2->PSC = (int)(percent * (double)pres);
			}

		}
	//HAL_Delay(2000);
	stopTimer();
}
void decodeMessage(char key){
	switch(key){
	case 't':
		HAL_GPIO_WritePin(eV1_GPIO_Port, eV1_Pin, 1);
		sendMessage("Electrovalve 1 ON!");
		break;
	case 'z':
		HAL_GPIO_WritePin(eV1_GPIO_Port, eV1_Pin, 0);
		sendMessage("Electrovalve 1 OFF!");
		break;
	case 'g':
		HAL_GPIO_WritePin(eV2_GPIO_Port, eV2_Pin, 1);
		sendMessage("Electrovalve 2 ON!");
		break;
	case 'h':
		HAL_GPIO_WritePin(eV2_GPIO_Port, eV2_Pin, 0);
		sendMessage("Electrovalve 2 OFF!");
		break;
	case 'b':
		//HAL_GPIO_WritePin(motStep_GPIO_Port, motStep_Pin, 1);
		//sendMessage("Motor step ON!");
		//turnmot(1999); // 1999 = 40 Hz, 199 = 394khz
		//turnmot(1999); // slow
		//turnmot(499); // 1kHz
		//turnmot(899); // 553 Hz
		//turnmot(299); // 1.66 kHz // moderate speed
		//turnmot(199); // 2.49 khZ
		turnmot(Fast, 2300, Right);
		//smoothTurn(199);
		break;
	case 'n':
		//HAL_GPIO_WritePin(motStep_GPIO_Port, motStep_Pin, 0);
		//sendMessage("Motor step OFF!");
		turnmot(Fast, 2300, Left);
		break;
	case 'c':
		HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, 1);
		sendMessage("Motor dir ON!");
		break;
	case 'v':
		HAL_GPIO_WritePin(motDir_GPIO_Port, motDir_Pin, 0);
		sendMessage("Motor dir OFF!");
		break;
	case 'l':
			sendMessage("Homing !");
			goHome();
			break;
	case 'm':
			turnmot(Fast, 4600, Left);
			break;

	}
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM6_Init();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_UART_Receive(&huart4, &receivedMessage, 1, HAL_MAX_DELAY);
		HAL_UART_Receive(&huart2, &receivedMessage, 1, HAL_MAX_DELAY);
		decodeMessage(receivedMessage);
		if(receivedMessage == 'd'){
			HAL_GPIO_TogglePin(LED_GPIO_Port , LED_Pin);
			sendMessage("Yo!");
		}
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim ->Instance == TIM6){
		//HAL_GPIO_TogglePin(LED_GPIO_Port , LED_Pin);
	}
}

// endstop callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == endstop_Pin){ // Check pin
		isEndstopTriggered = true;
		stopTimer();
	}
	else{
		__NOP();
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
