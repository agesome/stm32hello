/**
  ******************************************************************************
  * @file    control_accees.c
  * @author  MCD Application Team
  * @brief   Security Control Access implementation
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
extern TS_State_t TS_State;
extern __IO uint8_t TsStateCallBack;

/* Private function prototypes -----------------------------------------------*/
COM_InitTypeDef COM_Init;
/* Private Variable ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern __IO uint8_t TsStateCallBack;
extern TX_THREAD                                sc_app_thread;
extern TX_THREAD                                ca_app_thread;

/* Private typedef -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Control_Access_Demo(void)
{
  /* This a simulation of IPs control access feature  */
  /* You can refer to GTZC examples for the functional implementation*/
  uint8_t exit = 0;
  uint8_t uart_sec = 0, led_sec = 0, uart_acces_sec =0, led_acces_sec =0;

  BSP_LED_Init(LED4);

  COM_Init.BaudRate    = 115200;
  COM_Init.WordLength  = COM_WORDLENGTH_8B;
  COM_Init.StopBits    = COM_STOPBITS_1;
  COM_Init.Parity      = COM_PARITY_NONE;
  COM_Init.HwFlowCtl   = COM_HWCONTROL_NONE;
  BSP_COM_Init(COM1, &COM_Init);

  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_ST_GRAY_DARK);

  UTIL_LCD_FillRect(0, 0, 320, 24,UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"Security Access", CENTER_MODE);

  /* Configuration Panel */
  UTIL_LCD_FillRect(0, 25, 320, 90,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GRAY_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
  UTIL_LCD_DisplayStringAt(0, 30, (uint8_t *)"Security Setup", CENTER_MODE);

  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_DisplayStringAt(4, 60, (uint8_t *)"UART:S            NS", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(4, 90, (uint8_t *)"LED :S            NS", LEFT_MODE);

  UTIL_LCD_DrawRect(90, 56, 107, 26,UTIL_LCD_COLOR_RED);
  UTIL_LCD_DrawRect(91, 57, 105, 24,UTIL_LCD_COLOR_RED);
  UTIL_LCD_FillRect(92, 58, 103, 22,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(143,59, 50, 20,UTIL_LCD_COLOR_DARKGREEN);

  UTIL_LCD_DrawRect(90, 86, 107, 26,UTIL_LCD_COLOR_RED);
  UTIL_LCD_DrawRect(91, 87, 105, 24,UTIL_LCD_COLOR_RED);
  UTIL_LCD_FillRect(92, 88, 103, 22,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(143,89, 50, 20,UTIL_LCD_COLOR_DARKGREEN);

  /* Change NS color*/
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
  UTIL_LCD_DisplayStringAt(202, 60, (uint8_t *)"NS", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(202, 90, (uint8_t *)"NS", LEFT_MODE);

  /* Execution Panel */
  UTIL_LCD_FillRect(2, 126, 316, 90,UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GRAY_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
  UTIL_LCD_DisplayStringAt(4, 128, (uint8_t *)"Access Mode", CENTER_MODE);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(4, 157, (uint8_t *)"UART:S       NS", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(4, 190, (uint8_t *)"LED :S       NS", LEFT_MODE);

  UTIL_LCD_DrawRect(4, 150, 236, 30,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_DrawRect(4, 184, 236, 30,UTIL_LCD_COLOR_BLACK);

  UTIL_LCD_DrawRect( 70, 152, 77, 26,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect( 71, 153, 75, 24,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(108, 154, 37, 22,UTIL_LCD_COLOR_DARKGREEN);

  UTIL_LCD_DrawRect( 70, 186, 77, 26,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect( 71, 187, 75, 24,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_FillRect(108, 188, 37, 22,UTIL_LCD_COLOR_DARKGREEN);

  /* Change NS color*/
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
  UTIL_LCD_DisplayStringAt(147, 157, (uint8_t *)"NS", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(147, 190, (uint8_t *)"NS", LEFT_MODE);

  /* Buttons Print and Toggle */
  UTIL_LCD_DrawRect(168, 152, 70, 26,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect(169, 153, 68, 24,UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(170, 154, 66, 22,UTIL_LCD_COLOR_BLACK);

  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DisplayStringAt(171, 159, (uint8_t *)"Print", LEFT_MODE);


  UTIL_LCD_DrawRect(168, 186, 70, 26,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect(169, 187, 68, 24,UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(170, 188, 66, 22,UTIL_LCD_COLOR_BLACK);

  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DisplayStringAt(170, 192, (uint8_t *)"Toggle", LEFT_MODE);



  /* Log panel part */
  UTIL_LCD_FillRect(2, 220, 316, 18,UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DrawRect(261, 220, 40, 18,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect(262, 221, 38, 16,UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_FillRect(263, 222, 36, 14,UTIL_LCD_COLOR_BLACK);

  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BROWN);
  UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access Control Simulation ", LEFT_MODE);

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
  UTIL_LCD_DisplayStringAt(267, 224, (uint8_t *)"BACK", LEFT_MODE);

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 90) && (TS_State.TouchX < 197) && (TS_State.TouchY > 56) && (TS_State.TouchY < 82))
      {
        /* UART security config */
        if(uart_sec == 0)
        {
          UTIL_LCD_FillRect(143,59, 50, 20,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(94,59, 50, 20,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(202, 60, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(59, 60, (uint8_t *)"S", LEFT_MODE);
          uart_sec = 1;
        }
        else
        {
          UTIL_LCD_FillRect(143,59, 50, 20,UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_FillRect(94,59, 50, 20,UTIL_LCD_COLOR_WHITE);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(202, 60, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(59, 60, (uint8_t *)"S", LEFT_MODE);
          uart_sec = 0;
        }
      }
      else if((TS_State.TouchX > 90) && (TS_State.TouchX < 197) && (TS_State.TouchY > 86) && (TS_State.TouchY < 102))
      {
        /* Led security config */
        if(led_sec == 0)
        {
          UTIL_LCD_FillRect(143,89, 50, 20,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(94,89, 50, 20,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(202, 90, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(59, 90, (uint8_t *)"S", LEFT_MODE);
          led_sec = 1;
        }
        else
        {
          UTIL_LCD_FillRect(143,89, 50, 20,UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_FillRect(94,89, 50, 20,UTIL_LCD_COLOR_WHITE);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(202, 90, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(59, 90, (uint8_t *)"S", LEFT_MODE);
          led_sec = 0;
        }
      }
      else if((TS_State.TouchX > 70) && (TS_State.TouchX < 154) && (TS_State.TouchY > 152) && (TS_State.TouchY < 178))
      {
        /* UART access config */
        if(uart_acces_sec == 0)
        {
          UTIL_LCD_FillRect( 71, 153, 75, 24,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(73,154, 37, 22,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(147, 157, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(59, 157, (uint8_t *)"S", LEFT_MODE);
          uart_acces_sec = 1;
        }
        else
        {
          UTIL_LCD_FillRect( 71, 153, 75, 24,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(108, 154, 37, 22,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(147, 157, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(59, 157, (uint8_t *)"S", LEFT_MODE);
          uart_acces_sec = 0;
        }
      }
      else if((TS_State.TouchX > 70) && (TS_State.TouchX < 154) && (TS_State.TouchY > 186) && (TS_State.TouchY < 222))
      {
        /* Led access config */
        if(led_acces_sec == 0)
        {
          UTIL_LCD_FillRect( 71, 187, 75, 24,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(73,188, 37, 22,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(147, 190, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(59, 190, (uint8_t *)"S", LEFT_MODE);
          led_acces_sec = 1;
        }
        else
        {
          UTIL_LCD_FillRect( 71, 187, 75, 24,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_FillRect(108, 188, 37, 22,UTIL_LCD_COLOR_DARKGREEN);
          /* Change NS color*/
          UTIL_LCD_SetFont(&Font16);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKGREEN);
          UTIL_LCD_DisplayStringAt(147, 190, (uint8_t *)"NS", LEFT_MODE);

          /* Change S color*/
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
          UTIL_LCD_DisplayStringAt(59, 190, (uint8_t *)"S", LEFT_MODE);
          led_acces_sec = 0;
        }
      }
      else if((TS_State.TouchX > 168) && (TS_State.TouchX < 241) && (TS_State.TouchY > 152) && (TS_State.TouchY < 178))
      {
        UTIL_LCD_FillRect(169, 153, 68, 24,UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_FillRect(170, 154, 66, 22,UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_DisplayStringAt(171, 159, (uint8_t *)"Print", LEFT_MODE);
        HAL_Delay(100);
        UTIL_LCD_FillRect(169, 153, 68, 24,UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_FillRect(170, 154, 66, 22,UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_DisplayStringAt(171, 159, (uint8_t *)"Print", LEFT_MODE);
        /* Print button */
        if (uart_sec == 1)
        {
          if (uart_acces_sec == 1)
          {
            printf("Authorized access from Secure Access to the UART device in Secure Configuration\n");
          }
          else
          {
            printf("Authorized access from Secure Access to the UART device in Non-Secure Configuration\n");
          }

          UTIL_LCD_SetFont(&Font12);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_DARK);
          UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access Authorized UART    ", LEFT_MODE);
        }
        else
        {
          if (uart_acces_sec == 0)
          {
            printf("Authorized access from Non-Secure Access to the UART device in Non-Secure Configuration\n");

            UTIL_LCD_SetFont(&Font12);
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_DARK);
            UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access Authorized UART    ", LEFT_MODE);
          }
          else
          {
            UTIL_LCD_SetFont(&Font12);
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
            UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access NOT Authorized UART  ", LEFT_MODE);
          }
        }
      }
      else if((TS_State.TouchX > 197) && (TS_State.TouchX < 240) && (TS_State.TouchY > 186) && (TS_State.TouchY < 230))
      {
        /* Toggle button */
        UTIL_LCD_FillRect(169, 187, 68, 24,UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_FillRect(170, 188, 66, 22,UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_DisplayStringAt(170, 192, (uint8_t *)"Toggle", LEFT_MODE);
        HAL_Delay(100);
        UTIL_LCD_FillRect(169, 187, 68, 24,UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_FillRect(170, 188, 66, 22,UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_YELLOW);
        UTIL_LCD_DisplayStringAt(170, 192, (uint8_t *)"Toggle", LEFT_MODE);
        
        if (led_sec == 1)
        {
          BSP_LED_Toggle(LED4);
          UTIL_LCD_SetFont(&Font12);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_DARK);
          UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access Authorized LED     ", LEFT_MODE);
        }
        else
        {
          if (led_acces_sec == 1)
          {
            UTIL_LCD_SetFont(&Font12);
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
            UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access NOT Authorized LED  ", LEFT_MODE);
          }
          else
          {
            BSP_LED_Toggle(LED4);
            UTIL_LCD_SetFont(&Font12);
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_DARK);
            UTIL_LCD_DisplayStringAt(50, 224, (uint8_t *)"Access Authorized LED     ", LEFT_MODE);
          }
        }
      }
      else if((TS_State.TouchX > 0) && (TS_State.TouchX < 40) && (TS_State.TouchY > 220) && (TS_State.TouchY < 240))
      {
        exit = 1;
        tx_thread_terminate(&sc_app_thread);
        tx_thread_reset(&sc_app_thread);
        tx_thread_resume(&sc_app_thread);
        tx_thread_suspend(&ca_app_thread);/* back touch */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);
}