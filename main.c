/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int time=0,Rx_cn=0;
volatile int Rx_flg=0,check_num=0;
uint8_t Receive[1],Receive_All[256],useless[1];

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void removeNewline(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';  // '\n'
    }
    if ((pos = strchr(str, '\r')) != NULL) {
        *pos = '\0';  //  '\r'
    }
}
void check_string()
{
	if(Rx_flg==1)
	{
		
	}
	
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		Receive_All[Rx_cn]=Receive[0];
		Rx_cn++;
	
	if(0x0A==Receive[0])
	{
		
		Receive_All[Rx_cn] = '\0';
		if(strcmp((char*)Receive_All,"blink\r\n")==0)
		{
			Rx_flg=0;
			Rx_cn=0;
			 check_num=1;
			HAL_UART_Transmit_IT(&huart1,(uint8_t *)"blink ok\r\n",strlen("blink ok\r\n"));
			
		}else if(strcmp((char*)Receive_All,"flow\r\n")==0)
		{
			Rx_flg=0;
			Rx_cn=0;
			 check_num=2;
			HAL_UART_Transmit_IT(&huart1,(uint8_t *)"flow ok\r\n",strlen("flow ok\r\n"));
			
		}else if(strcmp((char*)Receive_All,"query\r\n")==0)
		{
			if( check_num==1)
			{
				HAL_UART_Transmit_IT(&huart1,(uint8_t *)"blink ok\r\n",strlen("blink ok\r\n"));
			}
			else if( check_num==2)
			{
				HAL_UART_Transmit_IT(&huart1,(uint8_t *)"flow ok\r\n",strlen("flow ok\r\n"));
			}
			else if( check_num==3)
			{
				HAL_UART_Transmit_IT(&huart1,(uint8_t *)"blink flow ok\r\n",strlen("blink flow ok\r\n"));
			}
		}else
		{
			Rx_flg = 0;
      Rx_cn = 0;
			HAL_UART_Transmit_IT(&huart1,(uint8_t *)"Error\r\n",strlen("Error\r\n"));
			
			
		}
		Rx_cn = 0;
		
	}
	HAL_UART_Receive_IT(&huart1,(uint8_t *)Receive,1);
	}
	}

	int check()
		{	
	int num=0;
	if(!key0)
	{
		HAL_Delay(20);
		if(!key0)
		{
			num=1;
			
			//TOG0;
		}
	}
	if(!key1)
	{
		HAL_Delay(20);
		if(!key1)
		{
			num=2;
			
			//TOG1;
		}
	}
	if(!WK_UP)
	{
		HAL_Delay(20);
		if(!WK_UP)
		{
			num=3;
		
			//TOG0;
			//TOG1;
		}
	}
	return num;
}

int check_Delay(int n)
	{
		int num=0;
		
	for(int i=0;i<n/50;i++)
		{
		HAL_Delay(50);
			num=check();
			
			if(num)
			{
				return num;
			}
			
		}
		return num;
	}

	int link()
{
	int num=0;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	
	if(num)
	{
		return num;
	}
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
	return num;
}
int current()
{
	int num=0;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
	return num;
}
int change()
{
	int num=0;
	if(time<5)
		{
			
		int num=0;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
			num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		time++;}
		else if(time<10&&time>4){

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
	num=check();
	if(num)
	{
		return num;
	}
	num=check_Delay(300);
	if(num)
	{
		return num;
	}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
			time++;
		}
		else{
			time=0;
		}
		return num;
	}
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
HAL_UART_Receive_IT(&huart1, (uint8_t *)Receive, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	int num;
  while (1)
  {
    /* USER CODE END WHILE */

		while(check_num==1)
		{
			num=link();
			if(num)
			{
				check_num=num;
			}
		}
		while(check_num==2)
		{
			num=current();
			if(num)
			{
				check_num=num;
			}
		}
		while(check_num==3)
		{
			num=change();
			if(num)
			{
				check_num=num;
			}
		}
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
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
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
