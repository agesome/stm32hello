/**
  ******************************************************************************
  * @file    app_calendar.c
  * @author  MCD Application Team
  * @brief   Calendar application implementation.
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
#ifndef __APP_CALENDAR_C
#define __APP_CALENDAR_C

/* Includes ------------------------------------------------------------------*/
#include "app_calendar.h"
#include "k_config.h"
/* Private typedef ----------------------------------------------------------*/

extern __IO uint8_t AlarmStatus;
static __IO uint8_t LedCounter = 0;
static uint32_t DateNb = 0;
static uint32_t wn = 0;
static uint32_t dn = 0;
static uint16_t daycolumn = 0, dayline = 0;
static uint8_t monthlength = 0;

const char DayNames[7][10] =
  {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
  };

const uint8_t MonLen[12] =
  {
    32, 29, 32, 31, 32, 31, 32, 32, 31, 32, 31, 32
  };
const char MonthNames[12][10] =
  {"JANUARY", "FEBRUARY", "MARCH",
   "APRIL", "MAY", "JUNE",
   "JULY", "AUGUST", "SEPTEMBER",
   "OCTOBER", "NOVEMBER", "DECEMBER"
  };

RTC_TimeTypeDef Time = {0};
RTC_DateTypeDef Date = {0};

TX_THREAD                                cal_app_thread;
TX_THREAD                                da_app_thread;
TX_THREAD                                da_set_app_thread;
TX_THREAD                                da_show_app_thread;
TX_THREAD                                ti_app_thread;
TX_THREAD                                ti_set_app_thread;
TX_THREAD                                ti_show_app_thread;
TX_THREAD                                al_app_thread;
TX_THREAD                                al_set_app_thread;
TX_THREAD                                al_dis_app_thread;

extern TX_THREAD                         Display_thread_entry;

/* Private constants ----------------------------------------------------------*/
#define DATE_LINE_NB                        6
#define TIME_LINE_NB                        4
#define CALENDAR_MEMORY_SIZE               (1024*2)
#define CALENDAR_APP_STACK_SIZE            (1024)

/* Private function prototypes -----------------------------------------------*/
KMODULE_RETURN _CalendarDemoExec(void);
KMODULE_RETURN _DateDemoExec(void);
KMODULE_RETURN _TimeDemoExec(void);
KMODULE_RETURN _AlarmDemoExec(void);
KMODULE_RETURN _CalendarConfig(void);

static void Calendar_TimeRegulate(RTC_TimeTypeDef *TimeInput, RTC_TimeTypeDef *TimeOutput);
static void Calendar_TimeSet(void);
static void Calendar_TimeDisplay(RTC_TimeTypeDef *time);
static void Calendar_DateRegulate(RTC_DateTypeDef *DateInput, RTC_DateTypeDef *DateOutput);
static void Calendar_DatePreAdjust(void);
static void Calendar_DateSet(void);
static void Calendar_DateShow(void);
static void Calendar_DateDisplay(uint8_t Year, uint8_t Month, uint8_t Day);
static void Calendar_AlarmPreAdjust(void);
static void Calendar_AlarmDisable(void);
static void Calendar_ClearMenuLines(void);
static void Calendar_WeekDayNum(uint32_t nyear, uint8_t nmonth, uint8_t nday);
static uint8_t Calendar_IsLeapYear(uint16_t nYear);
static void Calendar_TimePreAdjust(void);


/* Private Variable ----------------------------------------------------------*/
/* Time Menu */
const tMenuItem TimeMenuItems[] =
{
  {"Set"   , 14, 30, NULL, NULL  },
  {"Show"  , 14, 30, NULL, NULL  },
  {"Return", 14, 30, NULL, NULL  },
};
const tMenu TimeMenu = {"Time", TimeMenuItems, countof(TimeMenuItems), 1, 1 };

/* Date Menu */
const tMenuItem DateMenuItems[] =
{
  {"Set"   , 14, 30, NULL, NULL  },
  {"Show"  , 14, 30, NULL, NULL  },
  {"Return", 14, 30, NULL, NULL  },
};
const tMenu DateMenu = {"Date", DateMenuItems, countof(DateMenuItems), 1, 1 };

/* Alarm Menu */
const tMenuItem AlarmMenuItems[] =
{
  {"Set"    , 14, 30, NULL, NULL  },
  {"Disable", 14, 30, NULL, NULL  },
  {"Return" , 14, 30, NULL, NULL  },
};
const tMenu AlarmMenu = {"Alarm", AlarmMenuItems, countof(AlarmMenuItems), 1, 1 };

/* Main Menu */
const tMenuItem CalendarMenuItems[] =
{
  {"Date"  , 14, 30, NULL, NULL  },
  {"Time"  , 14, 30, NULL, NULL  },
  {"Alarm" , 14, 30, NULL, NULL  },
  {"Return", 14, 30, NULL, NULL  },
};
const tMenu CalendarMenu = {"Calendar", CalendarMenuItems, countof(CalendarMenuItems), 1, 1 };

/* Character usage */
uint8_t CharWidth;
uint8_t CharHeight;

/* Private typedef -----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/* RTC Handle variable */
extern RTC_HandleTypeDef RtcHandle;
extern __IO uint8_t TsStateCallBack;
extern TS_State_t TS_State;

/**
* @brief  Application Calendar Initialization.
* @param memory_ptr: memory pointer
* @retval int
*/
UINT Calendar_Init_pool(VOID *memory_ptr)
{
  UINT ret = UX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_CALENDAR_Host_MEM_POOL */
#if (USE_MEMORY_POOL_ALLOCATION == 1)
  CHAR *pointer;

  /* USER CODE END App_CALENDAR_Host_MEM_POOL */

  /* USER CODE BEGIN MX_CALENDAR_Host_Init */

  /* Allocate the stack for the main App thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       (CALENDAR_APP_STACK_SIZE * 2), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main App thread. */
  if (tx_thread_create(&cal_app_thread, "cal_app_thread", cal_app_thread_entry, 0,
                       pointer, (CALENDAR_APP_STACK_SIZE * 2), 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the date app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the date app thread.  */
  if (tx_thread_create(&da_app_thread, "da_app_thread", da_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the date set app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the date set app thread.  */
  if (tx_thread_create(&da_set_app_thread, "da_set_app_thread", da_set_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the date show app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the date show app thread.  */
  if (tx_thread_create(&da_show_app_thread, "da_show_app_thread", da_show_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

    /* Allocate the stack for the time app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the time app thread.  */
  if (tx_thread_create(&ti_app_thread, "ti_app_thread", ti_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

    /* Allocate the stack for the time set app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the time set app thread.  */
  if (tx_thread_create(&ti_set_app_thread, "ti_set_app_thread", ti_set_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

    /* Allocate the stack for the time show app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the time show app thread.  */
  if (tx_thread_create(&ti_show_app_thread, "ti_show_app_thread", ti_show_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the alarm app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the alarm app thread.  */
  if (tx_thread_create(&al_app_thread, "al_app_thread", al_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

    /* Allocate the stack for the alarm set app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the alarm set app thread.  */
  if (tx_thread_create(&al_set_app_thread, "al_set_app_thread", al_set_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the alarm show app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       CALENDAR_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the alarm show app thread.  */
  if (tx_thread_create(&al_dis_app_thread, "al_dis_app_thread", al_dis_app_thread_entry, 0,
                       pointer, CALENDAR_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

#endif
  /* USER CODE END MX_USBX_Host_Init */

  return ret;
}

/**
  * @brief  setup the HW for Calendar application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _CalendarConfig(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* HAL_RTC_Init has been already called for Backup reg access */
  /* check if Date has been already set one time, else configure it to
  1st of january 2023 */
  if(__HAL_RTC_GET_FLAG(&RtcHandle, RTC_FLAG_INITS) == 0x00u)
  {
    /* Set Date to 01.01.2023 */
    Date.Date = 0x01u;
    Date.Month = 0x01u;
    Date.Year = 0x23u;
    Date.WeekDay = RTC_WEEKDAY_MONDAY;

    /* Set time to default */
    Time.Hours = 0x00u;
    Time.Minutes = 0x00u;
    Time.Seconds = 0x00u;
    Time.TimeFormat = RTC_HOURFORMAT12_AM;

    /* Set the RTC current Time */
    status = HAL_RTC_SetTime(&RtcHandle, &Time, RTC_FORMAT_BCD);
    if(status != HAL_OK)
    {
      return KMODULE_ERROR_PRE;
    }

    /* Set the RTC current Date */
    HAL_RTC_SetDate(&RtcHandle, &Date, RTC_FORMAT_BCD);
    if(status != HAL_OK)
    {
      return KMODULE_ERROR_PRE;
    }
  }

  CharHeight = (((sFONT *)UTIL_LCD_GetFont())->Height);
  CharWidth = (((sFONT *)UTIL_LCD_GetFont())->Width);

  return KMODULE_OK;
}

/**
  * @brief  Run the application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _CalendarDemoExec(void)
{
  uint8_t exit = 0;
  uint8_t index = 0;

  /* Display the menu */
  while (!(index >= CalendarMenu.nItems))
  {
    /* Set the Back Color */
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    /* Set the Text Color */
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
    /* Get the current menu */
    UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*index+1), (uint8_t *)CalendarMenu.psItems[index].pszTitle,LEFT_MODE);
    index++;
  }

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  /* Set the Back Color */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  /* Set the Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if((TS_State.TouchY > 24) && (TS_State.TouchY < 70))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*0+1), (uint8_t *)CalendarMenu.psItems[0].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&da_app_thread);
        tx_thread_reset(&da_app_thread);
        tx_thread_resume(&da_app_thread); /* Date module selected */
      }
      else if((TS_State.TouchY > 72) && (TS_State.TouchY < 118))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*1+1), (uint8_t *)CalendarMenu.psItems[1].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&ti_app_thread);
        tx_thread_reset(&ti_app_thread);
        tx_thread_resume(&ti_app_thread); /* Time module selected */
      }
      else if((TS_State.TouchY > 120) && (TS_State.TouchY < 166))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*2+1), (uint8_t *)CalendarMenu.psItems[2].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&al_app_thread);
        tx_thread_reset(&al_app_thread);
        tx_thread_resume(&al_app_thread); /* Alarm module selected */
      }
      else if((TS_State.TouchY > 168) && (TS_State.TouchY < 214))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*3+1), (uint8_t *)CalendarMenu.psItems[3].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&Display_thread_entry);
        tx_thread_reset(&Display_thread_entry);
        tx_thread_resume(&Display_thread_entry);/* back touch */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);

  tx_thread_suspend(&cal_app_thread);

  return KMODULE_OK;
}

/**
  * @brief  Run the application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _DateDemoExec(void)
{
  uint8_t exit = 0;
  uint8_t index = 0;

  /* Display the menu */
  while (!(index >= DateMenu.nItems))
  {
    /* Set the Back Color */
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    /* Set the Text Color */
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
    /* Get the current menu */
    UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*index+1), (uint8_t *)DateMenu.psItems[index].pszTitle,LEFT_MODE);
    index++;
  }

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  /* Set the Back Color */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  /* Set the Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if((TS_State.TouchY > 24) && (TS_State.TouchY < 70))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*0+1), (uint8_t *)DateMenu.psItems[0].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&da_set_app_thread);
        tx_thread_reset(&da_set_app_thread);
        tx_thread_resume(&da_set_app_thread); /* Date set module selected */
      }
      else if((TS_State.TouchY > 72) && (TS_State.TouchY < 118))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*1+1), (uint8_t *)DateMenu.psItems[1].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&da_show_app_thread);
        tx_thread_reset(&da_show_app_thread);
        tx_thread_resume(&da_show_app_thread); /* date show module selected */
      }
      else if((TS_State.TouchY > 120) && (TS_State.TouchY < 166))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*2+1), (uint8_t *)DateMenu.psItems[2].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&cal_app_thread);
        tx_thread_reset(&cal_app_thread);
        tx_thread_resume(&cal_app_thread);/* back touch */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);

  tx_thread_suspend(&da_app_thread);

  return KMODULE_OK;
}

/**
  * @brief  Run the application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _TimeDemoExec(void)
{
  uint8_t exit = 0;
  uint8_t index = 0;

  /* Display the menu */
  while (!(index >= TimeMenu.nItems))
  {
    /* Set the Back Color */
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    /* Set the Text Color */
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
    /* Get the current menu */
    UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*index+1), (uint8_t *)TimeMenu.psItems[index].pszTitle,LEFT_MODE);
    index++;
  }

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      /* Set the Back Color */
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
      /* Set the Text Color */
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

      if((TS_State.TouchY > 24) && (TS_State.TouchY < 70))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*0+1), (uint8_t *)TimeMenu.psItems[0].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&ti_set_app_thread);
        tx_thread_reset(&ti_set_app_thread);
        tx_thread_resume(&ti_set_app_thread); /* Time set module selected */
      }
      else if((TS_State.TouchY > 72) && (TS_State.TouchY < 118))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*1+1), (uint8_t *)TimeMenu.psItems[1].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&ti_show_app_thread);
        tx_thread_reset(&ti_show_app_thread);
        tx_thread_resume(&ti_show_app_thread); /* Time show module selected */
      }
      else if((TS_State.TouchY > 120) && (TS_State.TouchY < 166))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*2+1), (uint8_t *)TimeMenu.psItems[2].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&cal_app_thread);
        tx_thread_reset(&cal_app_thread);
        tx_thread_resume(&cal_app_thread);/* back touch */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);

  tx_thread_suspend(&ti_app_thread);

  return KMODULE_OK;
}

/**
  * @brief  Run the application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _AlarmDemoExec(void)
{
  uint8_t exit = 0;
  uint8_t index = 0;

  /* Display the menu */
  while (!(index >= AlarmMenu.nItems))
  {
    /* Set the Back Color */
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    /* Set the Text Color */
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
    /* Get the current menu */
    UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*index+1), (uint8_t *)AlarmMenu.psItems[index].pszTitle,LEFT_MODE);
    index++;
  }

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      /* Set the Back Color */
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
      /* Set the Text Color */
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

      if((TS_State.TouchY > 24) && (TS_State.TouchY < 70))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*0+1), (uint8_t *)AlarmMenu.psItems[0].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&al_set_app_thread);
        tx_thread_reset(&al_set_app_thread);
        tx_thread_resume(&al_set_app_thread); /* Alarm set module selected */
      }
      else if((TS_State.TouchY > 72) && (TS_State.TouchY < 118))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*1+1), (uint8_t *)AlarmMenu.psItems[1].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&al_dis_app_thread);
        tx_thread_reset(&al_dis_app_thread);
        tx_thread_resume(&al_dis_app_thread); /* Alarm disable module selected */
      }
      else if((TS_State.TouchY > 120) && (TS_State.TouchY < 166))
      {
        exit = 1;
        UTIL_LCD_DisplayStringAt(0, Font24.Height*(2*2+1), (uint8_t *)AlarmMenu.psItems[2].pszTitle,LEFT_MODE);
        HAL_Delay(50);
        tx_thread_terminate(&cal_app_thread);
        tx_thread_reset(&cal_app_thread);
        tx_thread_resume(&cal_app_thread);/* back touch */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);

  tx_thread_suspend(&al_app_thread);

  return KMODULE_OK;
}


/**
  * @brief  Adjusts time.
  * @param  None
  * @retval None
  */
static void Calendar_TimeSet(void)
{
  Point HourUp[]= {{55, 70}, {70, 50}, {85, 70}};
  Point HourDown[]= {{55, 143}, {70, 163}, {85, 143}};
  Point MinUp[]= {{105, 70}, {120, 50}, {135, 70}};
  Point MinDown[]= {{105, 143}, {120, 163}, {135, 143}};
  Point SecUp[]= {{155, 70}, {170, 50}, {185, 70}};
  Point SecDown[]= {{155, 143}, {170, 163}, {185, 143}};
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Clear menu lines */
  Calendar_ClearMenuLines();

  /* Add Control icons */
  BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
  UTIL_LCD_FillPolygon(HourUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(HourDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MinUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MinDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(SecUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(SecDown, 3, UTIL_LCD_COLOR_GREEN);

  /* PreAdjust Time */
  Calendar_TimePreAdjust();
}


/**
  * @brief  Displays the current time.
  * @param  time current time
  * @retval None
  */
static void Calendar_TimeDisplay(RTC_TimeTypeDef *time)
{
  char showtime[14] = {0};

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
  sprintf((char*)showtime,"   %02X:%02X:%02X",time->Hours,time->Minutes,time->Seconds);
  UTIL_LCD_DisplayStringAtLine(TIME_LINE_NB, (uint8_t *) showtime);

}


/**
  * @brief  Displays information on LCD for the time configuration
  * @param  None
  * @retval None
  */
static void Calendar_TimePreAdjust()
{
  RTC_TimeTypeDef timecurrent = {0};
  RTC_TimeTypeDef timeset = {0};
  RTC_DateTypeDef dateset = {0};

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &timecurrent, RTC_FORMAT_BCD);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &dateset, RTC_FORMAT_BCD);

  /* Display the current time */
  Calendar_TimeDisplay(&timecurrent);

  /* Call Time selection function */
  Calendar_TimeRegulate(&timecurrent, &timeset);

  /* Set the RTC current Date */
  HAL_RTC_SetDate(&RtcHandle, &dateset, RTC_FORMAT_BCD);

  /* Set the updated Time */
  HAL_RTC_SetTime(&RtcHandle,&timeset,RTC_FORMAT_BCD);

  tx_thread_terminate(&ti_app_thread);
  tx_thread_reset(&ti_app_thread);
  tx_thread_resume(&ti_app_thread);
  tx_thread_suspend(&ti_set_app_thread);
}


/**
  * @brief  Adjusts the current date (MM/DD/YYYY).
  * @param  None
  * @retval None
  */
static void Calendar_DateSet(void)
{
  /* Get back font specifications */
  UTIL_LCD_SetFont(&Font16);
  CharHeight = (((sFONT *)UTIL_LCD_GetFont())->Height);
  CharWidth = (((sFONT *)UTIL_LCD_GetFont())->Width);

  /* Clear the LCD */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  Calendar_DatePreAdjust();

}


/**
  * @brief  Displays the date in graphic mode.
  * @param  Year    Year to display
  * @param  Month   Month to display
  * @param  Date    Date to display
  * @retval None
  */
static void Calendar_DateDisplay(uint8_t Year, uint8_t Month, uint8_t Day)
{
  uint32_t mline = 0, mcolumn = 319, month = 0;
  char linedisplay[25];
  uint32_t pXSize;

  monthlength = 0;

  if (Month == 2)
  {
    if (Calendar_IsLeapYear(Year))
    {
      monthlength = 30;
    }
    else
    {
      monthlength = MonLen[Month - 1];
    }
  }
  else
  {
    monthlength = MonLen[Month - 1];
  }

  /* Set the Back Color */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(41,LINE(0), 156, Font16.Height,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(81, LINE(1), 58, Font16.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(0, LINE(2), pXSize, Font16.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);
  /* Set the Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  sprintf((char*)linedisplay,"%s", MonthNames[Month - 1]);
  UTIL_LCD_DisplayStringAt(0, LINE(0), (uint8_t*)linedisplay, CENTER_MODE);


  sprintf((char*)linedisplay," 20%02d",Year);
  UTIL_LCD_DisplayStringAt(0, LINE(1), (uint8_t*)linedisplay, CENTER_MODE);


  /* Determines the week number, day of the week of the selected date */
  Calendar_WeekDayNum(Year, Month, Day);
  DateNb = dn;

  sprintf((char*)linedisplay,"   WEEK:%02lu  DAY:%02lu    ", (unsigned long)wn, (unsigned long)Day);
  UTIL_LCD_DisplayStringAtLine(2, (uint8_t*)linedisplay);

  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_FillRect(0, LINE(3), pXSize, Font16.Height, UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAtLine(3, (uint8_t*) " Mo Tu We Th Fr Sa Su");
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);

  /* Determines the week number, day of the week of the selected date */
  Calendar_WeekDayNum(Year, Month, 1);

  /* Clear first & last calendar lines */
  UTIL_LCD_ClearStringLine(4);
  UTIL_LCD_ClearStringLine(8);
  UTIL_LCD_ClearStringLine(9);

  mline = LINE(4);
  mcolumn = ((CharWidth * 3) * dn);
  for (month = 1; month < monthlength; month++)
  {
    mcolumn += CharWidth;
    if (month == Day)
    {
      daycolumn = mcolumn;
      dayline = mline;
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
    }
    else
    {
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    }
     /* display first space */
    UTIL_LCD_DisplayChar(mcolumn, mline, ' ');

    if (month / 10)
    {
      UTIL_LCD_DisplayChar(mcolumn, mline, ((month / 10) + 0x30));
    }
    else
    {
      UTIL_LCD_DisplayChar(mcolumn, mline, ' ');
    }
    mcolumn += CharWidth;

    UTIL_LCD_DisplayChar(mcolumn, mline, ((month % 10) + 0x30));
    UTIL_LCD_DrawRect(mcolumn -CharWidth, mline, CharWidth*2, CharHeight -2, UTIL_LCD_COLOR_ST_GREEN_LIGHT);
    mcolumn += CharWidth;

    if (mcolumn >= ((7 * 3) * CharWidth))
    {
      mcolumn = 0;
      mline += CharHeight*2;
    }
  }
}


/**
  * @brief  Displays information on LCD for the time configuration
  * @param  None
  * @retval None
  */
static void Calendar_DatePreAdjust(void)
{
  RTC_DateTypeDef datecurrent = {0};
  RTC_DateTypeDef dateset = {0};
  RTC_TimeTypeDef timeset = {0};

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &timeset, RTC_FORMAT_BCD);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &datecurrent, RTC_FORMAT_BCD);

  /* Call Time selection function */
  Calendar_DateRegulate(&datecurrent, &dateset);

  /* Set the RTC current Time */
  HAL_RTC_SetTime(&RtcHandle, &timeset, RTC_FORMAT_BCD);
  /* Set the RTC current Date */
  HAL_RTC_SetDate(&RtcHandle, &dateset, RTC_FORMAT_BCD);

  tx_thread_terminate(&da_app_thread);
  tx_thread_reset(&da_app_thread);
  tx_thread_resume(&da_app_thread);
  tx_thread_suspend(&da_set_app_thread);
}


/**
  * @brief  Basically show date (MM/DD/YYYY).
  * @param  None
  * @retval None
  */
static void Calendar_DateShow(void)
{
  RTC_TimeTypeDef time = {0};
  RTC_DateTypeDef date = {0};
  char showdate[20] = {0};
  uint8_t exit = 0;

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Clear menu lines */
  Calendar_ClearMenuLines();

  UTIL_LCD_DrawRect(160, 200, 77, 36,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect(161, 201, 75, 34,UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_DisplayStringAt(165, 206, (uint8_t *)"BACK", LEFT_MODE);

  /* Set the Back Color */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &time, RTC_FORMAT_BCD);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &date, RTC_FORMAT_BCD);

  UTIL_LCD_DisplayStringAt(0,LINE(DATE_LINE_NB-2), (uint8_t *)(uint8_t *)DayNames[date.WeekDay - 1], CENTER_MODE);
  sprintf((char*)showdate,"  %02X.%02X.20%02X", date.Date, date.Month, date.Year);
  UTIL_LCD_DisplayStringAtLine(DATE_LINE_NB - 1, (uint8_t *) showdate);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0;
      if((TS_State.TouchX > 160) && (TS_State.TouchY > 200))
      {
        exit = 1;
      }
    }
  } while(exit == 0);

  tx_thread_terminate(&da_app_thread);
  tx_thread_reset(&da_app_thread);
  tx_thread_resume(&da_app_thread);
  tx_thread_suspend(&da_show_app_thread);
}


/**
  * @brief  Set the time entered by user, using menu navigation keys.
  * @param  TimeInput     current time when entering function
  * @param  TimeOutput    value selected by user
  * @retval None
  */
static void Calendar_TimeRegulate(RTC_TimeTypeDef *TimeInput, RTC_TimeTypeDef *TimeOutput)
{
  uint8_t exit = 0;
  uint8_t Hours = 0;
  uint8_t Minutes = 0;
  uint8_t Seconds = 0;
  char display[14];

  Hours = RTC_Bcd2ToByte(TimeInput->Hours);
  Minutes = RTC_Bcd2ToByte(TimeInput->Minutes);
  Seconds = RTC_Bcd2ToByte(TimeInput->Seconds);

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  /* Set the Back Color */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Set the Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(50);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 50) && (TS_State.TouchX < 90) && (TS_State.TouchY > 40) && (TS_State.TouchY < 75))
      {
        /* Hour Up */
        Hours++;
        if(Hours >23 )
        {
          Hours = 0;
        }
      }
      else if((TS_State.TouchX > 50) && (TS_State.TouchX < 90) && (TS_State.TouchY > 138) && (TS_State.TouchY < 173))
      {
        /* Hour Down */
        if(Hours == 0)
        {
          Hours = 23;
        }
        else
        {
          Hours--;
        }
      }
      else if((TS_State.TouchX > 100) && (TS_State.TouchX < 140) && (TS_State.TouchY > 40) && (TS_State.TouchY < 75))
      {
        /* Min Up */
        Minutes++;
        if(Minutes > 59)
        {
          Minutes = 0;
        }
      }
      else if((TS_State.TouchX > 100) && (TS_State.TouchX < 140) && (TS_State.TouchY > 138) && (TS_State.TouchY < 173))
      {
        /* Min Down */
        if(Minutes == 0)
        {
          Minutes = 59;
        }
        else
        {
          Minutes--;
        }
      }
      else if((TS_State.TouchX > 150) && (TS_State.TouchX < 190) && (TS_State.TouchY > 40) && (TS_State.TouchY < 75))
      {
        /* Sec Up */
        Seconds++;
        if(Seconds > 59)
        {
          Seconds = 0;
        }
      }
      else if((TS_State.TouchX > 150) && (TS_State.TouchX < 190) && (TS_State.TouchY > 138) && (TS_State.TouchY < 173))
      {
        /* Sec Down */
        if(Seconds == 0)
        {
          Seconds = 59;
        }
        else
        {
          Seconds--;
        }
      }
      else if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
      {
        exit = 1;
      }
      sprintf((char*)display,"   %02X:%02X:%02X",RTC_ByteToBcd2(Hours),RTC_ByteToBcd2(Minutes),RTC_ByteToBcd2(Seconds));
      UTIL_LCD_DisplayStringAtLine(TIME_LINE_NB, (uint8_t *) display);
    }
  } while(exit == 0);

  /* store time */
  TimeOutput->Hours = RTC_ByteToBcd2(Hours);
  TimeOutput->Minutes = RTC_ByteToBcd2(Minutes);
  TimeOutput->Seconds = RTC_ByteToBcd2(Seconds);
}



/**
  * @brief  Set date entered by user, using menu navigation keys.
  * @param  DateInput    current date when entering function
  * @param  DateOutput   value selected by user
  * @retval None
  */
static void Calendar_DateRegulate(RTC_DateTypeDef *DateInput, RTC_DateTypeDef *DateOutput)
{
  uint8_t year = RTC_Bcd2ToByte(DateInput->Year);
  uint8_t month = RTC_Bcd2ToByte(DateInput->Month);
  uint8_t day = RTC_Bcd2ToByte(DateInput->Date);
  uint8_t exit = 0;
  uint8_t touched_column = 0;
  uint8_t touched_line = 0;
  uint8_t selected_day = 0;
  uint32_t pXSize;
  char linedisplay[25];

  Point MonthDown[]= {{10, 8}, {40, 3}, {40, 13}};
  Point MonthUp[]= {{200, 13}, {200, 3}, {230, 8}};
  Point YearDown[]= {{50, 24}, {80, 19}, {80, 29}};
  Point YearUp[]= {{160, 29}, {160, 19}, {190, 24}};

  UTIL_LCD_DrawRect(170, 215, 67, 22,UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_FillRect(171, 216, 65, 20,UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
  UTIL_LCD_DisplayStringAt(175, 218, (uint8_t *)"Apply", LEFT_MODE);

  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, LINE(0), pXSize, Font16.Height,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(0, LINE(1), pXSize, Font16.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_FillRect(0, LINE(2), pXSize, Font16.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_FillPolygon(MonthDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MonthUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(YearDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(YearUp, 3, UTIL_LCD_COLOR_GREEN);

  Calendar_DateDisplay(year, month, day);

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0;

      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);

      if((TS_State.TouchX < 40) && (TS_State.TouchY < 17))
      {
        if(month == 1)
        {
          month= 12;
          year--;
        }
        else
        {
          month--;
        }

        day = 1;
        UTIL_LCD_ClearStringLine(12);
        UTIL_LCD_DisplayStringAt(0, 224, (uint8_t *)"        ", LEFT_MODE);
        Calendar_DateDisplay(year, month, day);
      }
      else if((TS_State.TouchX > 200) && (TS_State.TouchY < 17))
      {
        if(month == 12)
        {
          month = 1;
          year++;
        }
        else
        {
          month++;
        }

        day = 1;
        UTIL_LCD_ClearStringLine(12);
        UTIL_LCD_DisplayStringAt(0, 224, (uint8_t *)"        ", LEFT_MODE);
        Calendar_DateDisplay(year, month, day);
      }
      else if((TS_State.TouchX > 40) && (TS_State.TouchX < 110) && (TS_State.TouchY > 5) && (TS_State.TouchY < 40))
      {
        if(year != 0)
        {
          year--;
        }
        day = 1;
        UTIL_LCD_ClearStringLine(12);
        UTIL_LCD_DisplayStringAt(0, 224, (uint8_t *)"        ", LEFT_MODE);
        Calendar_DateDisplay(year, month, day);
      }
      else if((TS_State.TouchX > 120) && (TS_State.TouchX < 190) && (TS_State.TouchY > 4) && (TS_State.TouchY < 40))
      {
        year++;
        day = 1;
        UTIL_LCD_ClearStringLine(12);
        UTIL_LCD_DisplayStringAt(0, 224, (uint8_t *)"        ", LEFT_MODE);
        Calendar_DateDisplay(year, month, day);
      }
      else if((TS_State.TouchX > 170) && (TS_State.TouchY > 220))
      {
        exit =1;
      }
      else if(TS_State.TouchY > LINE(4))
      {
        touched_column = TS_State.TouchX/ (CharWidth*3 + 2) + 1;
        touched_line = (TS_State.TouchY - CharHeight * 4)/(CharHeight*2);
        if((touched_line == 0) && (touched_column < dn + 1))
        {
          selected_day = 0;
        }
        else
        {
          selected_day = touched_line*7 + touched_column - dn;
        }

        if(selected_day > monthlength - 1)
        {
          selected_day = 0;
        }
        if(selected_day != 0 && selected_day != day)
        {
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_GREEN_LIGHT);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
          if (selected_day/10)
          {
            UTIL_LCD_DisplayChar(((touched_column - 1)*(CharWidth*3)) + CharWidth, LINE(4) + touched_line*CharHeight*2, ((selected_day / 10) + 0x30));
            UTIL_LCD_DisplayChar(((touched_column - 1)*(CharWidth*3)) + (CharWidth*2), LINE(4) + touched_line*CharHeight*2, (selected_day % 10) + 0x30);
          }
          else
          {
            UTIL_LCD_DisplayChar(((touched_column - 1)*(CharWidth*3)) + CharWidth,  LINE(4) + touched_line*CharHeight*2, ' ');
            UTIL_LCD_DisplayChar(((touched_column - 1)*(CharWidth*3)) + (CharWidth*2), LINE(4) + touched_line*CharHeight*2, (selected_day % 10) + 0x30);
          }

          /* clear previous selection */
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          if (day/10)
          {
            UTIL_LCD_DisplayChar(daycolumn, dayline, ((day / 10) + 0x30));
            UTIL_LCD_DisplayChar(daycolumn + CharWidth, dayline, ((day % 10) + 0x30));
          }
          else
          {
            UTIL_LCD_DisplayChar(daycolumn, dayline, ' ');
            UTIL_LCD_DisplayChar(daycolumn + CharWidth, dayline, ((day % 10) + 0x30));
          }
          UTIL_LCD_DrawRect(daycolumn, dayline, CharWidth*2, CharHeight -2, UTIL_LCD_COLOR_ST_GREEN_LIGHT);

          day = selected_day;
          daycolumn = ((touched_column - 1)*(CharWidth*3)) + CharWidth;
          dayline =  LINE(4) + touched_line*CharHeight*2;
          /* Determines the week number, day of the week of the selected date */
          Calendar_WeekDayNum(year, month, day);
          DateNb = dn;
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
          sprintf((char*)linedisplay,"   WEEK:%02lu  DAY:%02lu    ", (unsigned long)wn, (unsigned long)day);
          UTIL_LCD_DisplayStringAtLine(2, (uint8_t*)linedisplay);
          Calendar_WeekDayNum(year, month, 1);
        }
      }
    }
  } while(exit == 0);

  DateOutput->Year = RTC_ByteToBcd2(year);
  DateOutput->Month = RTC_ByteToBcd2(month);
  DateOutput->Date = RTC_ByteToBcd2(day);
  DateOutput->WeekDay= RTC_ByteToBcd2(DateNb+1);
}

/**
  * @brief  Displays information on LCD for the alarm time configuration
  * @param  None
  * @retval None
  */
static void Calendar_AlarmPreAdjust(void)
{
  RTC_TimeTypeDef timecurrent = {0};
  RTC_TimeTypeDef timeset = {0};
  RTC_DateTypeDef dateset = {0};
  RTC_AlarmTypeDef alarm = {0};

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &timecurrent, RTC_FORMAT_BCD);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &dateset, RTC_FORMAT_BCD);

  /* Display the current time */
  Calendar_TimeDisplay(&timecurrent);

  /* Call Time selection function */
  Calendar_TimeRegulate(&timecurrent, &timeset);

  /* Get back alarm time */
  alarm.Alarm = RTC_ALARM_A;
  alarm.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
  alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  alarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
  alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  alarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
  alarm.AlarmTime.Hours = timeset.Hours;
  alarm.AlarmTime.Minutes = timeset.Minutes;
  alarm.AlarmTime.Seconds = timeset.Seconds;

  /* Set the new alarm time */
  HAL_RTC_SetAlarm_IT(&RtcHandle, &alarm, RTC_FORMAT_BCD);

  tx_thread_terminate(&al_app_thread);
  tx_thread_reset(&al_app_thread);
  tx_thread_resume(&al_app_thread);
  tx_thread_suspend(&al_set_app_thread);
}


/**
  * @brief  Adjusts Alarm.
  * @param  None
  * @retval None
  */
static void Calendar_AlarmDisable(void)
{
  /* Clear menu lines */
  Calendar_ClearMenuLines();

  /* Deactivate alarm */
  HAL_RTC_DeactivateAlarm(&RtcHandle, RTC_ALARM_A);

  /* Alarm led off */
  BSP_LED_Off(LED_GREEN);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
  UTIL_LCD_SetFont(&Font20);
  /* Display information */
  UTIL_LCD_DisplayStringAtLine(TIME_LINE_NB, (uint8_t *)"Alarm is disabled");
  HAL_Delay(1000);
}


/**
  * @brief  Alarm A callback function of the Irq Handler that makes led toggling
  * @param  None
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  uint32_t time = 0x40;
  __IO uint32_t period;

  while(time > 0)
  {
    BSP_LED_Toggle(LED_GREEN);

    /* waiting period */
    period = 0xFFFFF;
    while(period > 0)
    {
      period--;
    }

    /* decrease time */
    time--;
  }

  /* make sure led is off when leaving */
  BSP_LED_Off(LED_GREEN);
}


/**
  * @brief  Manage menu lines clearing
  * @param  None
  * @retval None
  */
static void Calendar_ClearMenuLines(void)
{
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Clear menu lines */
  for(uint32_t i = 1; i< 6; i++)
  {
    UTIL_LCD_ClearStringLine(i);
  }
}


/**
  * @brief  Determines the week number, the month number and the week day number.
  * @param  nyear   the week number
  * @param  nmonth  the month number
  * @param  nday    the week day number
  * @retval None
  */
static void Calendar_WeekDayNum(uint32_t nyear, uint8_t nmonth, uint8_t nday)
{
  uint32_t a = 0, b = 0, c = 0, s = 0, e = 0, f = 0, g = 0, d = 0;
  int32_t n = 0;
  if (nmonth < 3)
  {
    a = nyear - 1;
  }
  else
  {
    a = nyear;
  }

  b = (a / 4) - (a / 100) + (a / 400);
  c = ((a - 1) / 4) - ((a - 1) / 100) + ((a - 1) / 400);
  s = b - c;
  if (nmonth < 3)
  {
    e = 0;
    f =  nday - 1 + 31 * (nmonth - 1);
  }
  else
  {
    e = s + 1;
    f = nday + (153 * (nmonth - 3) + 2) / 5 + 58 + s;
  }
  g = (a + b) % 7;
  d = (f + g - e) % 7;
  n = f + 3 - d;
  if (n < 0)
  {
    wn = 53 - ((g - s) / 5);
  }
  else if (n > (364 + s))
  {
    wn = 1;
  }
  else
  {
    wn = (n / 7) + 1;
  }
  dn = d;
}


/**
  * @brief  Check whether the passed year is Leap or not.
  * @param  nYear  year number to be checked
  * @retval 1: leap year
  *         0: not leap year
  */
static uint8_t Calendar_IsLeapYear(uint16_t nYear)
{
  if (nYear % 4 != 0) return 0;
  if (nYear % 100 != 0) return 1;
  return (uint8_t)(nYear % 400 == 0);
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  cal_app_thread_entry(ULONG arg)
{
  uint32_t pXSize;

  /* Clear the LCD Screen */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, Font24.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"Calendar", CENTER_MODE);

  if(_CalendarConfig() != KMODULE_OK)
  {
    while(1);
  }
  while (1)
  {
    _CalendarDemoExec();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  da_app_thread_entry(ULONG arg)
{
  uint32_t pXSize;

  /* Clear the LCD Screen */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, Font24.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0,(uint8_t *)"Date", CENTER_MODE);

  while (1)
  {
    _DateDemoExec();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  da_set_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Calendar_DateSet();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  da_show_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Calendar_DateShow();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  ti_app_thread_entry(ULONG arg)
{
  uint32_t pXSize;

  /* Clear the LCD Screen */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, Font24.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0,(uint8_t *)"Time", CENTER_MODE);

  while (1)
  {
    _TimeDemoExec();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  ti_set_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Calendar_TimeSet();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  ti_show_app_thread_entry(ULONG arg)
{
  uint32_t ypos = (CharHeight * (TIME_LINE_NB + 1));
  uint32_t xpos;
  uint32_t pXSize;
  uint8_t exit = 0;
  RTC_TimeTypeDef time = {0};
  RTC_DateTypeDef date = {0};

  BSP_LCD_GetXSize(0, &pXSize);
  xpos =  (pXSize - 64) >> 1;

  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Clear menu lines */
  Calendar_ClearMenuLines();

  BSP_LCD_FillRGBRect(0, (uint32_t)xpos, (uint32_t)ypos, (uint8_t *)IconWatch, 64, 64);

  /* Add Control icons */
  BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);

  /* Wait a press on any JoyStick pushbuttons */
  while (exit == 0x00u)
  {
    /* Get the RTC current Time */
    HAL_RTC_GetTime(&RtcHandle, &time, RTC_FORMAT_BCD);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(&RtcHandle, &date, RTC_FORMAT_BCD);

    /* Display current time */
    Calendar_TimeDisplay(&time);

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(50);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
      {
        exit = 1;
      }
    }
  }

  HAL_Delay(100);
  TsStateCallBack = 0;

  tx_thread_terminate(&ti_app_thread);
  tx_thread_reset(&ti_app_thread);
  tx_thread_resume(&ti_app_thread);
  tx_thread_suspend(&ti_show_app_thread);
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  al_app_thread_entry(ULONG arg)
{
  uint32_t pXSize;

  /* Clear the LCD Screen */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, Font24.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  UTIL_LCD_DisplayStringAt(0, 0,(uint8_t *)"Alarm", CENTER_MODE);

  while (1)
  {
    _AlarmDemoExec();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  al_set_app_thread_entry(ULONG arg)
{
  Point HourUp[]= {{55, 70}, {70, 50}, {85, 70}};
  Point HourDown[]= {{55, 143}, {70, 163}, {85, 143}};
  Point MinUp[]= {{105, 70}, {120, 50}, {135, 70}};
  Point MinDown[]= {{105, 143}, {120, 163}, {135, 143}};
  Point SecUp[]= {{155, 70}, {170, 50}, {185, 70}};
  Point SecDown[]= {{155, 143}, {170, 163}, {185, 143}};
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  /* Clear menu lines */
  Calendar_ClearMenuLines();

  /* Add Control icons */
  BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
  UTIL_LCD_FillPolygon(HourUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(HourDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MinUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MinDown, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(SecUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(SecDown, 3, UTIL_LCD_COLOR_GREEN);
  while (1)
  {
    Calendar_AlarmPreAdjust();
  }
}

/**
* @brief  Application_thread_entry .
* @param  ULONG arg
* @retval Void
*/
void  al_dis_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Calendar_AlarmDisable();

    tx_thread_terminate(&al_app_thread);
    tx_thread_reset(&al_app_thread);
    tx_thread_resume(&al_app_thread);
    tx_thread_suspend(&al_dis_app_thread);
  }
}

/**
* @brief cal_host_error_callback
* @param ULONG event
UINT system_context
UINT error_code
* @retval Status
*/
VOID cal_error_callback(UINT system_level, UINT system_context, UINT error_code)
{

}

#undef __APP_CALENDAR_C
#endif
