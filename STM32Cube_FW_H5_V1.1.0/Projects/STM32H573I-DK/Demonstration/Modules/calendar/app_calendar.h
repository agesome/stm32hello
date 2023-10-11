/**
  ******************************************************************************
  * @file    app_calendar.h
  * @author  MCD Application Team
  * @brief   Calendar application interface
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

#undef GLOBAL
#ifdef __APP_CALENDAR_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* External constants --------------------------------------------------------*/
/* RTC divider to get 1s time base */
#define RTC_ASYNCH_PREDIV   0x7F   /* LSE as RTC clock */
#define RTC_SYNCH_PREDIV    0x00FF /* LSE as RTC clock */

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
UINT Calendar_Init_pool(VOID *memory_ptr);
VOID cal_error_callback(UINT system_level, UINT system_context, UINT error_code);
void  cal_app_thread_entry(ULONG arg);
void  da_app_thread_entry(ULONG arg);
void  da_set_app_thread_entry(ULONG arg);
void  da_show_app_thread_entry(ULONG arg);
void  ti_app_thread_entry(ULONG arg);
void  ti_set_app_thread_entry(ULONG arg);
void  ti_show_app_thread_entry(ULONG arg);
void  al_app_thread_entry(ULONG arg);
void  al_set_app_thread_entry(ULONG arg);
void  al_dis_app_thread_entry(ULONG arg);
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
