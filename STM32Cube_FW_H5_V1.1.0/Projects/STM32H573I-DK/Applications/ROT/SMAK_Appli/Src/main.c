/**
  ******************************************************************************
  * @file    main.c
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
#include "its.h"
#include "cryp.h"
#include "fwu.h"
#include "eat.h"


/** @addtogroup STM32H5xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#if defined(__ICCARM__)
#include <LowLevelIOInterface.h>
#endif /* __ICCARM__ */

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int32_t iar_fputc(int32_t ch);
#define PUTCHAR_PROTOTYPE int32_t iar_fputc(int32_t ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
int io_putchar(int ch);
#define PUTCHAR_PROTOTYPE int io_putchar(int ch)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int32_t uart_putc(int32_t ch)
#endif /* __ICCARM__ */

PUTCHAR_PROTOTYPE
{
  (void)COM_Transmit((uint8_t *)&ch, 1, TX_TIMEOUT);
  return ch;
}

/* Redirects printf to TFM_DRIVER_STDIO in case of ARMCLANG*/
#if defined(__ARMCC_VERSION)
FILE __stdout;

/* __ARMCC_VERSION is only defined starting from Arm compiler version 6 */
int fputc(int ch, FILE *f)
{
  /* Send byte to USART */
  io_putchar(ch);

  /* Return character written */
  return ch;
}
#elif defined(__GNUC__)
/* Redirects printf to TFM_DRIVER_STDIO in case of GNUARM */
int32_t _write(int32_t fd, char *str, int32_t len)
{
  int32_t i;

  for (i = 0; i < len; i++)
  {
    /* Send byte to USART */
    uart_putc(str[i]);
  }

  /* Return the number of characters written */
  return len;
}
#elif defined(__ICCARM__)
size_t __write(int32_t file, unsigned char const *ptr, size_t len)
{
  UNUSED(file);
  size_t idx;
  unsigned char const *pdata = ptr;

  for (idx = 0; idx < len; idx++)
  {
    (void)iar_fputc((int32_t)*pdata);
    pdata++;
  }
  return len;
}

#endif /*  __GNUC__ */

/* Private variables ---------------------------------------------------------*/
uint8_t *pUserAppId;
const uint8_t UserAppId = 'A';

/* Private function prototypes -----------------------------------------------*/
static void FW_APP_MAIN_PrintMenu(void);
static void FW_APP_MAIN_Run(void);
static void SystemClock_Config(void);
static void CACHE_Enable(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*  set example to const : this const changes in binary without rebuild */
  pUserAppId = (uint8_t *)&UserAppId;

  /* STM32H5xx HAL library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  if (HAL_Init() != HAL_OK)
  {
    Error_Handler();
  }

  /* This project template calls CACHE_Enable() in order to enable the Instruction
     and Data Cache. This function is provided as template implementation that
     User may integrate in his application in order to enhance performance */

  /* Enable the Instruction Cache */
  CACHE_Enable();

  /* Configure the System clock to have a frequency of 250 MHz */
  SystemClock_Config();

  /* Configure Communication module */
  if (COM_Init() != HAL_OK)
  {
    Error_Handler();
  }

  /* Add your application code here */
  HAL_Delay(100);
  (void)printf("\r\n======================================================================");
  (void)printf("\r\n=              (C) COPYRIGHT 2022 STMicroelectronics                 =");
  (void)printf("\r\n=                                                                    =");
  (void)printf("\r\n=          Non Secure User App related to Secure Manager #%c          =", *pUserAppId);
  (void)printf("\r\n======================================================================");
  (void)printf("\r\n\r\n");

  FW_APP_MAIN_Run();

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Display the Main Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
void FW_APP_MAIN_PrintMenu(void)
{
  (void)printf("\r\n=================== Main Menu ============================\r\n\n");
  (void)printf("  Internal Trusted Storage ----------------------------- 1\r\n\n");
  (void)printf("  Cryptography ----------------------------------------- 2\r\n\n");
  (void)printf("  Initial Attestation ---------------------------------- 3\r\n\n");
  (void)printf("  Firmware Update -------------------------------------- 4\r\n\n");
  (void)printf("  Selection :\r\n\n");
  (void)printf("  ");
}

/**
  * @brief  Run the Main menu
  * @param  None.
  * @retval None.
  */
void FW_APP_MAIN_Run(void)
{
  uint8_t key = 0U;

  /* Print Menu message*/
  FW_APP_MAIN_PrintMenu();

  while (1U)
  {
    /* Clean the input path */
    (void)COM_Flush();

    /* Receive key */
    if (COM_Receive(&key, 1U, RX_TIMEOUT) == HAL_OK)
    {
      (void)printf("%c\r\n", key);
      switch (key)
      {
        case '1' :
          FW_APP_ITS_Run();
          break;
        case '2' :
          FW_APP_CRYPTO_Run();
          break;
        case '3' :
          FW_APP_EAT_Run();
          break;
        case '4' :
          FW_APP_FWU_Run();
          break;

        default:
          (void)printf("\rInvalid Number !\r\n");
          break;
      }

      /* Print Main Menu message */
      FW_APP_MAIN_PrintMenu();
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

  if (HAL_RCC_DeInit() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* The voltage scaling allows optimizing the power consumption when the device is
  clocked below the maximum system frequency, to update the voltage scaling value
  regarding system frequency refer to product datasheet.
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

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
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                 RCC_CLOCKTYPE_PCLK3);
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
  * @brief  Enable ICACHE with 2-ways set-associative configuration.
  * @param  None
  * @retval None
  */
static void CACHE_Enable(void)
{
  /* Enable instruction cache (default 2-ways set associative cache) */
  (void)HAL_ICACHE_Enable();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while (1)
  {
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
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */
