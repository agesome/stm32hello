/**
  ******************************************************************************
  * @file    memory_access.c
  * @author  MCD Application Team
  * @brief   Security Memory Access implementation
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
#include "k_config.h"
#include "app_security.h"

/* Private typedef ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Touch Calibration */

extern TS_State_t TS_State;
extern __IO uint8_t TsStateCallBack;

#if defined ( __ICCARM__ )
#pragma location=0x20000000
#elif defined(__ARMCC_VERSION) ||defined(__GNUC__)
__attribute__((section("DrawBuffersection")))
#endif
uint8_t DrawBuffer[LCD_DEFAULT_WIDTH*LCD_DEFAULT_HEIGHT];

/* Private function prototypes -----------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TX_THREAD                                sc_app_thread;
extern TX_THREAD                                ma_app_thread;
/* Exported functions --------------------------------------------------------*/
void Memory_Access_Demo(void)
{
  /* This a simulation of IPs control access feature  */
  /* You can refer to GTZC examples for the functional implementation*/
  char tmp[30];
  uint16_t TouchX;
  uint16_t TouchY;

  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_FillRect(0, 0, 240, 20,UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"Memory Access", CENTER_MODE);

  /* Forbidden Panel */
  UTIL_LCD_FillRect(0, 90, 240, 60,UTIL_LCD_COLOR_RED);

  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_DisplayStringAt(2, 110, (uint8_t *)"Secure Area", CENTER_MODE);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(2, 90, (uint8_t *)"0x20007D00", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(2, 138, (uint8_t *)"0x2000C800", LEFT_MODE);

  /* Log Panel */
  UTIL_LCD_FillRect(0, 218, 240, 2,UTIL_LCD_COLOR_ST_GRAY_DARK);

  UTIL_LCD_DrawRect(0, 219, 40, 20,UTIL_LCD_COLOR_RED);
  UTIL_LCD_DrawRect(1, 220, 40, 18,UTIL_LCD_COLOR_RED);  
  UTIL_LCD_FillRect(2, 221, 37, 16,UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(3, 222, 36, 14,UTIL_LCD_COLOR_BLACK);

  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(62, 224, (uint8_t *) " Draw with your Finger ", LEFT_MODE);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DisplayStringAt(7, 224, (uint8_t *)"BACK", LEFT_MODE);

  while(1)
  {
    if(TsStateCallBack != 0)
    {
      TouchX = TS_State.TouchX;
      TouchY = TS_State.TouchY;
      /* Disable the TS interrupt */
      BSP_TS_DisableIT(0);
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if ((TouchY > 90) && (TouchY < 150))
      {
        /* Illegal access */

        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        sprintf(tmp,"Illegal Access:0x%p ",&DrawBuffer[(320* TouchY)+TouchX]);
        UTIL_LCD_FillRect(62, 220, 178, 18,UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_DisplayStringAt(62, 224, (uint8_t *)tmp, LEFT_MODE);

        DrawBuffer[(320* TouchY)+TouchX] = 0xA5;
      }
      else if (((TouchY > 24) && (TouchY < 86)) || ((TouchY > 154) && (TouchY < 214)))
      {
        /* Authorized access */
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
        sprintf(tmp,"Legal Access:0x%p",&DrawBuffer[(320* TouchY)+TouchX]);
        UTIL_LCD_FillRect(62, 220, 178, 18,UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_DisplayStringAt(62, 224, (uint8_t *)tmp, LEFT_MODE);

        DrawBuffer[(320* TouchY)+TouchX] = 0xA5;
        UTIL_LCD_FillCircle(TouchX,TouchY,4,UTIL_LCD_COLOR_GREEN);
      }
      else if((TouchX > 0) && (TouchX < 40) && (TouchY > 220) && (TouchY < 240))
      {
        /* Enable the TS interrupt */
        BSP_TS_EnableIT(0);
        tx_thread_terminate(&sc_app_thread);
        tx_thread_reset(&sc_app_thread);
        tx_thread_resume(&sc_app_thread);
        tx_thread_suspend(&ma_app_thread);
      }

      /* Enable the TS interrupt */
      BSP_TS_EnableIT(0);
    }
  }
}