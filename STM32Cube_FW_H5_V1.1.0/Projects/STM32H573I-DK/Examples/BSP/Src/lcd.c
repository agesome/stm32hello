/**
  ******************************************************************************
  * @file    Examples/BSP/Src/lcd.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the LCD display feature in the 
  *          STM32H573I-DK driver
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

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/  
/* Private variables ---------------------------------------------------------*/
uint32_t  colors[6][4] = {{UTIL_LCD_COLOR_BLUE, UTIL_LCD_COLOR_GREEN, UTIL_LCD_COLOR_RED, UTIL_LCD_COLOR_CYAN}, 
                          {UTIL_LCD_COLOR_MAGENTA, UTIL_LCD_COLOR_YELLOW,UTIL_LCD_COLOR_LIGHTBLUE, UTIL_LCD_COLOR_LIGHTGREEN},
                          {UTIL_LCD_COLOR_LIGHTRED, UTIL_LCD_COLOR_WHITE, UTIL_LCD_COLOR_LIGHTMAGENTA, UTIL_LCD_COLOR_LIGHTYELLOW}, 
                          {UTIL_LCD_COLOR_DARKGREEN, UTIL_LCD_COLOR_DARKRED, UTIL_LCD_COLOR_DARKCYAN,UTIL_LCD_COLOR_DARKMAGENTA}, 
                          {UTIL_LCD_COLOR_LIGHTGRAY, UTIL_LCD_COLOR_GRAY, UTIL_LCD_COLOR_DARKGRAY, UTIL_LCD_COLOR_DARKYELLOW},
                          {UTIL_LCD_COLOR_BLACK, UTIL_LCD_COLOR_BROWN, UTIL_LCD_COLOR_ORANGE, UTIL_LCD_COLOR_DARKBLUE}};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  LCD demo
  * @param  None
  * @retval None
  */
void Test_Lcd(void)
{
  uint32_t  i, k;
  uint32_t  Orientation[4] = {LCD_ORIENTATION_PORTRAIT, LCD_ORIENTATION_LANDSCAPE_ROT180, LCD_ORIENTATION_PORTRAIT_ROT180, LCD_ORIENTATION_LANDSCAPE};
  Point     triangle[3] = {{0, 0}, {0, 0}, {0, 0}};
  
  StepBack = 0;
 
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
  UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test LCD  ", CENTER_MODE);
  BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
  
  for(k = 0; k < 6; k++)
  {
    for(i = 0; i < 4; i++)
    {
      UTIL_LCD_FillRect(40*k, 40 + 50*i,40,50, colors[k][i]);
      if(colors[k][i] == UTIL_LCD_COLOR_WHITE)
      {
        UTIL_LCD_FillRect(40*k, 40 + 50*i,40,50, UTIL_LCD_COLOR_BLACK);
      }
    }
  }
  HAL_Delay(1000);
  UTIL_LCD_FillRect(0, 40, 240, 200, UTIL_LCD_COLOR_WHITE);
  for(k = 0; k < 6; k++)
  {
    for(i = 0; i < 4; i++)
    {
      UTIL_LCD_DrawCircle(20 + 40*k, 65 + 50*i,19, UTIL_LCD_COLOR_BLACK);
    }
  }
  HAL_Delay(1000);
  
  UTIL_LCD_FillRect(0, 40, 240, 200, UTIL_LCD_COLOR_WHITE);
  for(k = 0; k < 6; k++)
  {
    for(i = 0; i < 4; i++)
    {
      UTIL_LCD_FillCircle(20 + 40*k, 65 + 50*i,18, colors[k][i]);
    }
  }
  HAL_Delay(1000);
  
  UTIL_LCD_FillRect(0, 40, 240, 200, UTIL_LCD_COLOR_WHITE);
  for(k = 0; k < 6; k++)
  {
    for(i = 0; i < 4; i++)
    {
      triangle[0].X = 40*k;
      triangle[0].Y = 40 + 50*(i);
      triangle[1].X = 40*(k+1);
      triangle[1].Y = 65 + 50*(i);      
      triangle[2].X = 40*k;
      triangle[2].Y = 40 + 50*(1+i);      
      UTIL_LCD_FillPolygon(triangle, 3, colors[k][i]);
      if(colors[k][i] == UTIL_LCD_COLOR_WHITE)
      {
        UTIL_LCD_DrawPolygon(triangle, 3, UTIL_LCD_COLOR_BLACK);
      }
    }
  }
  HAL_Delay(1000);
  
  for (k = 0; k < 4; k++)
  {
    /* De-initialize LCD */
    if (BSP_LCD_DeInit(0) != BSP_ERROR_NONE) Error_Handler();
    /* Initialize LCD */
    if (BSP_LCD_Init(0, Orientation[k]) != BSP_ERROR_NONE) Error_Handler();    
    /* Set GUI functions */
    UTIL_LCD_SetFuncDriver(&LCD_Driver);
    UTIL_LCD_SetFont(&Font16);
    UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);  
    UTIL_LCD_FillRect(0, 0, 240, 40, UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_DisplayStringAt(0, 15, (uint8_t *)" Test LCD  ", CENTER_MODE);
    BSP_LCD_FillRGBRect(0, 200, 0, (uint8_t *)GoBack, 40, 40);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);    
    UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)"LCD ORIENTATION", CENTER_MODE);
    switch(k)
    {
    case 0:
      UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"PORTRAIT", CENTER_MODE);
      break;
    case 1:
      UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"LANDSCAPE_ROT180", CENTER_MODE);
      break;
    case 2:
      UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"PORTRAIT_ROT180", CENTER_MODE);
      break;
    case 3:
    default:
      UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"LANDSCAPE", CENTER_MODE);
      UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"GO BACK TO MENU", CENTER_MODE);      
      break;    
    }
    
    /* Draw bitmap */
    UTIL_LCD_DrawBitmap(80, 130, (uint8_t *)stlogo);
    HAL_Delay(2000);
  }
  
  while (StepBack != 1)
  {
    if(TouchPressed > 0)
    {
      TouchPressed = 0;
      /* Quit the Test */
      if ((TS_State.TouchX > 200) && (TS_State.TouchX < 240)&&(TS_State.TouchY > 0) && (TS_State.TouchY < 40))
      {
        StepBack = 1;
        Menu_Display();
      }
    }
  }  
}


/**
  * @}
  */ 

/**
  * @}
  */ 

