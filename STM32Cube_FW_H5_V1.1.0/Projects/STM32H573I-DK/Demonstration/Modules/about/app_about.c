/**
  ******************************************************************************
  * @file    app_about.c
  * @author  MCD Application Team
  * @brief   Shows the demonstration information
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
#define __APP_ABOUT_C

/* Includes ------------------------------------------------------------------*/
#include "k_config.h"
#include "app_about.h"

/* Private typedef ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
#define ABOUT_MEMORY_SIZE                             (1024*2)
#define ABOUT_APP_STACK_SIZE                          (1024)
/* Private function prototypes -----------------------------------------------*/
KMODULE_RETURN _SystemInfoDemoExec(void);
void SystemInfoDemo(void);

/* Private Variable ----------------------------------------------------------*/
extern __IO uint8_t TsStateCallBack ;
extern TS_State_t TS_State;

TX_THREAD                                ab_app_thread;
/* Private typedef -----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern TX_THREAD                         Display_thread_entry;

/**
  * @brief  Run the 8 uart application
  * @param  None.
  * @note   run and display information about the uart transaction.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _SystemInfoDemoExec(void)
{
  SystemInfoDemo();

  return KMODULE_OK;
}


/**
  * @brief  Run the image browser
  * @param  None.
  * @note   run and display image according the user action.
  * @retval None.
  */
void SystemInfoDemo(void)
{
  uint8_t exit = 0;

  /* Clear the LCD */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(0, 40, 20, 200, UTIL_LCD_COLOR_ST_YELLOW);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  /* Set the display font */
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(0, 10, (uint8_t *)"System Information", LEFT_MODE);
  BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);

    /* Set the display font */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(20, 70, (uint8_t *)"MCU: STM32H573IIK3Q", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(20, 110, (uint8_t *)"Board: STM32H573I-DK", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(20, 150, (uint8_t *)"CPU Speed: 250 MHZ", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(20, 190, (uint8_t *)"FW Version: V1.1.0", LEFT_MODE);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(0, 220, (uint8_t *)"STMicroelectronics 2023", CENTER_MODE);

  HAL_Delay(100);
    /* Wait a press to the return position */
  while (exit == 0U)
  {
    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(50);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 200) && (TS_State.TouchY < 40))
      {
        exit = 1;
      }
    }
  }
  TsStateCallBack = 0;
  tx_thread_terminate(&Display_thread_entry);
  tx_thread_reset(&Display_thread_entry);
  tx_thread_resume(&Display_thread_entry);/* back touch */
  tx_thread_suspend(&ab_app_thread);
}

/**
* @brief  Application About Demo Initialization.
* @param memory_ptr: memory pointer
* @retval int
*/
UINT About_Demo_Init_pool(VOID *memory_ptr)
{
  UINT ret = UX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_USBX_Host_MEM_POOL */
#if (USE_MEMORY_POOL_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for about App thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       (ABOUT_APP_STACK_SIZE * 2), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main App thread. */
  if (tx_thread_create(&ab_app_thread, "ab_app_thread", ab_app_thread_entry, 0,
                       pointer, (ABOUT_APP_STACK_SIZE * 2), 25, 25, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

#endif
  /* USER CODE END MX_USBX_Host_Init */

  return ret;
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  ab_app_thread_entry(ULONG arg)
{
  while (1)
  {
    _SystemInfoDemoExec();
  }
}

