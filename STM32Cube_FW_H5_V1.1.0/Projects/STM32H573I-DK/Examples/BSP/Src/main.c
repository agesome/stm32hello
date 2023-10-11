/**
  ******************************************************************************
  * @file    Examples/BSP/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32H5xx_HAL_Examples
  * @{
  */

/** @addtogroup Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TS_State_t TS_State;    
__IO FlagStatus UserButtonPressed = RESET;
__IO uint32_t TouchPressed = 0;
__IO uint8_t StepBack = 0;
TS_Init_t   hTS;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32H5xx HAL library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* This project template calls CACHE_Enable() in order to enable the Instruction
     and Data Cache. This function is provided as template implementation that
     User may integrate in his application in order to enhance performance */

  /* Enable the Instruction Cache */
  CACHE_Enable();

  /* Configure the System clock to have a frequency of 250 MHz */
  SystemClock_Config();

  /* Initialize LCD */
  BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
  /* Set GUI functions */
  UTIL_LCD_SetFuncDriver(&LCD_Driver);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  hTS.Orientation = TS_ORIENTATION_LANDSCAPE;
  hTS.Accuracy = 5;
  hTS.Width = 240;
  hTS.Height = 240;

  BSP_TS_Init(0, &hTS);
  BSP_TS_EnableIT(0);

  BSP_LED_Init(LED_RED);
  
  Menu_Display();
  
  /* Infinite loop */
  while (1)
  {
    if(TouchPressed == 1)
    {
      TouchPressed = 0;
      if ((TS_State.TouchX > 12) && (TS_State.TouchX < 78)&&(TS_State.TouchY > 36) && (TS_State.TouchY < 100))
      {
        Test_Led();
      }
      if ((TS_State.TouchX > 88) && (TS_State.TouchX < 152)&&(TS_State.TouchY > 36) && (TS_State.TouchY < 100))
      {
        Test_Lcd();
      }
      if ((TS_State.TouchX > 164) && (TS_State.TouchX < 228)&&(TS_State.TouchY > 36) && (TS_State.TouchY < 100))
      {
        Test_Ts();
      }
      if ((TS_State.TouchX > 12) && (TS_State.TouchX < 78)&&(TS_State.TouchY > 136) && (TS_State.TouchY < 200))
      {
        Test_Sd();
      }
      if ((TS_State.TouchX > 88) && (TS_State.TouchX < 152)&&(TS_State.TouchY > 136) && (TS_State.TouchY < 200))
      {
        Test_Ospi();
      }
      if ((TS_State.TouchX > 164) && (TS_State.TouchX < 228)&&(TS_State.TouchY > 136) && (TS_State.TouchY < 200))
      {
        Test_Audio();
      }
    }
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE BYPASS)
  *            SYSCLK(Hz)                     = 250000000  (CPU Clock)
  *            HCLK(Hz)                       = 250000000  (Bus matrix and AHBs Clock)
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1 (APB1 Clock  250MHz)
  *            APB2 Prescaler                 = 1 (APB2 Clock  250MHz)
  *            APB3 Prescaler                 = 1 (APB3 Clock  250MHz)
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 5
  *            PLL_N                          = 100
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* The voltage scaling allows optimizing the power consumption when the device is
  clocked below the maximum system frequency, to update the voltage scaling value
  regarding system frequency refer to product datasheet.
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Use HSE in bypass mode and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1, PCLK2 and PCLK3
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2| RCC_CLOCKTYPE_PCLK3);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  Draw main menu
  * @param  None
  * @retval None
  */
void Menu_Display(void)
{
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(0, 0, 240, 30, UTIL_LCD_COLOR_ST_BLUE_DARK); 

  UTIL_LCD_DisplayStringAt(0, 10, (uint8_t *)"  BSP Example  ", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_FillRGBRect(0, 12, 36, (uint8_t *)IconLed, 64, 64);
  BSP_LCD_FillRGBRect(0, 88, 36, (uint8_t *)IconLcd, 64, 64);
  BSP_LCD_FillRGBRect(0, 164, 36, (uint8_t *)IconTs, 64, 64);
  UTIL_LCD_DisplayStringAt(0, 110, (uint8_t *)"  LED    LCD   Touch ", CENTER_MODE);
  BSP_LCD_FillRGBRect(0, 12, 136, (uint8_t *)IconSd, 64, 64);
  BSP_LCD_FillRGBRect(0, 88, 136, (uint8_t *)IconOspi, 64, 64);
  BSP_LCD_FillRGBRect(0, 164, 136, (uint8_t *)IconAudio, 64, 64);
  UTIL_LCD_DisplayStringAt(0, 210, (uint8_t *)"  uSD    OSPI   Audio ", CENTER_MODE);
}

uint32_t enter_bnr = 0, in;
/**
  * @brief  BSP TS Callback.
  * @param  Instance TS Instance.
  * @retval None.
  */
void BSP_TS_Callback(uint32_t Instance)
{
  BSP_TS_GetState(0, &TS_State);
  if(TS_State.TouchDetected == 1)
  {
    TouchPressed = 1;
  }
}

/**
  * @brief  Button Callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
  UserButtonPressed = SET;
}

/**
  * @brief  Enable ICACHE with 2-ways set-associative configuration.
  * @param  None
  * @retval None
  */
static void CACHE_Enable(void)
{
  /* Enable instruction cache (default 2-ways set associative cache) */
  HAL_ICACHE_Enable();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
    BSP_LED_Toggle(LED_RED);
    HAL_Delay(500);
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
