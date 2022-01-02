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
  *Author: Franziska Rothen, franziska.rothen@students.unibe.ch
  *
  *Functionalities:
  * - Navigation through the menu via LCD and joystick
  * - Detection of the size of the glass with a weighing scale
  * - Choice of syrup percentage via potentiometer
  * - Communication with the second microcontroller, giving orders to:
  * 	- Initialize motor
  * 	- Moving the glass to three predefined positions.
  * 	- Open and close valves
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "hx711.h"
#include "lcd_driver.h"
#include "menu.h"
#include "poti.h"
#include "scale.h"
#include "comm.h"

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
uint16_t rawValue;
HAL_StatusTypeDef status;
int step = 0;
bool button_state = true;
int percentage;
int weight;
char size;
int isFull;
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
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();													// initialize the lcd
  initScale();													// initialize scale
  sendMessage("l"); 											// initialize stepper motor
  HAL_Delay(1000);
  sendMessage("l");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  lcd_clear();													// clear lcd screen
  welcome_display();											// display welcome message
  status = HAL_OK;

  while (1) 													// Menu navigaion with different menus and functions.
  {
		if(status == HAL_OK){
			if(step == 0)
				menu1_display();								// display welcome message
			else if(step == 1)
				menu2_display();								// prompt to put the glass on the scale
			else if (step == 2)
				weight = getWeight();							// getting the weight
			else if(step == 3)
				size = menu3_display(weight);					// display which glass was chosen
			else if(step == 4){
				status = potiRead(&rawValue);					// initialize poti and start reading the value
				percentage = potiPrint(&rawValue);				// print current chosen syrup percentage
			}
			else if(step == 5){
				status = potiDeInit();							// de-initialize the poti
				menu4_display(percentage);						// display chosen percentage
			}
			else if(step == 6){
				sendMessage("b"); 								// move the glass to next position
				HAL_Delay(2500);
				sendMessage("t"); 								// open valve for syrup
				step ++;
			}
			else if(step == 7){
				weight = getWeight2();							// geting the weight
				isFull = checkWeight(size, weight, percentage);	// checking if the syrup has reached the desired level
				if(isFull){
					sendMessage("z"); 							// close valve for syrup
					HAL_Delay(10);
					sendMessage("b"); 							// move the glass to next position
					HAL_Delay(2500);
					sendMessage("g"); 							// open valve for water
					step ++;
				}
			}
			else if(step == 8){
				weight = getWeight2();							// getting the weight
				isFull = checkWeight2(size, weight, percentage);// checking if the water has reached the desired level
				if(isFull){
					sendMessage("h"); 							// close valve for water
					HAL_Delay(10);
					sendMessage("m"); 							// move glass back
					step ++;
				}
			}
			else if(step > 8){
				menu5_display();								// display final message
			}
		}
		else
			Error_Handler();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

// Increment step variable if joystick is pressed. With de-bouncing using TIM1 in interrupt mode.

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == joystick_Pin && button_state == true){ // Check pin
		HAL_TIM_Base_Start_IT(&htim1);
		button_state = false;
	}
	else{
		__NOP();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);		// Prevent unused argument(s) compilation warning

	if(HAL_GPIO_ReadPin(joystick_GPIO_Port, joystick_Pin) == GPIO_PIN_RESET){
		step ++;
		button_state = true;
		HAL_TIM_Base_Stop_IT(&htim1);
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
