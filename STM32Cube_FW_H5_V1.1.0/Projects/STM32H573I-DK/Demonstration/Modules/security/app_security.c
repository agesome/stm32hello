/**
  ******************************************************************************
  * @file    app_lpbam.c
  * @author  MCD Application Team
  * @brief   Audio application implementation.
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

#define __APP_TRUSTZONE_C

/* Includes ------------------------------------------------------------------*/
#include "app_security.h"
#include "k_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define ICON_WIDTH  64
#define ICON_HEIGHT 64
#define SECURITY_MEMORY_SIZE         (1024*2)
/* Security stack size */
#define SECURITY_APP_STACK_SIZE       (1024)

/* Display columns positions */
#define X1_POS    35
#define X2_POS    X1_POS + ICON_WIDTH + 40
#define X3_POS    (X1_POS + X2_POS) / 2

#define Y1_POS     54
#define Y2_POS     Y1_POS + ICON_HEIGHT + 10

/* Private function prototypes -----------------------------------------------*/
static KMODULE_RETURN _TrustZoneDemoExec(void);
void myControl_Access_UserAction(uint8_t sel);

/* Private Variable ----------------------------------------------------------*/
TX_THREAD                                sc_app_thread;
TX_THREAD                                ca_app_thread;
TX_THREAD                                ma_app_thread;
extern TX_THREAD                         Display_thread_entry;
extern __IO uint8_t TsStateCallBack;
extern TS_State_t TS_State;
/* TrustZone menu */
static const tMenuItem TrustZoneMenuMenuItems[] =
{
    {"Security Access"  , X1_POS, Y1_POS, (char*)IconTrustZonePerith0  , (char*)IconTrustZonePerith1   },
    {"Memory Access"   , X2_POS, Y1_POS, (char*)IconTrustZoneMemory0  , (char*)IconTrustZoneMemory1 },
    {"Return"          , X3_POS, Y2_POS, (char*)IconReturn0           , (char*)IconReturn1     },
};

static const tMenu TrustZoneMenu = {
  "Trust Zone", TrustZoneMenuMenuItems, countof(TrustZoneMenuMenuItems), 1, 1 };

/* Private typedef -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
  * @brief  Run the applications
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
static KMODULE_RETURN _TrustZoneDemoExec(void)
{
  uint8_t exit = 0;

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 35) && (TS_State.TouchX < 99) && (TS_State.TouchY > 45) && (TS_State.TouchY < 110))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)TrustZoneMenu.psItems[0].x+1, (uint32_t)TrustZoneMenu.psItems[0].y+1, (uint8_t *)TrustZoneMenu.psItems[0].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&ca_app_thread);
        tx_thread_reset(&ca_app_thread);
        tx_thread_resume(&ca_app_thread); /* control access module selected */
      }
      else if((TS_State.TouchX > 139) && (TS_State.TouchX < 203) && (TS_State.TouchY > 45) && (TS_State.TouchY < 110))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)TrustZoneMenu.psItems[1].x+1, (uint32_t)TrustZoneMenu.psItems[1].y+1, (uint8_t *)TrustZoneMenu.psItems[1].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&ma_app_thread);
        tx_thread_reset(&ma_app_thread);
        tx_thread_resume(&ma_app_thread); /* memory access module selected */
      }
      else if((TS_State.TouchX > 89) && (TS_State.TouchX < 153) && (TS_State.TouchY > 140) && (TS_State.TouchY < 230))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)TrustZoneMenu.psItems[2].x+1, (uint32_t)TrustZoneMenu.psItems[2].y+1, (uint8_t *)TrustZoneMenu.psItems[2].pIconSelectedPath, 64, 64);
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

  tx_thread_suspend(&sc_app_thread);

  return KMODULE_OK;
}

/**
  * @brief  Application Security Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT Security_Init_pool(VOID *memory_ptr)
{
  UINT ret = UX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;


#if (USE_MEMORY_POOL_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for the main App thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       (SECURITY_APP_STACK_SIZE * 2), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main App thread. */
  if (tx_thread_create(&sc_app_thread, "security_app_thread", sc_app_thread_entry, 0,
                       pointer, (SECURITY_APP_STACK_SIZE * 2), 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the control access app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       SECURITY_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the control access app thread.  */
  if (tx_thread_create(&ca_app_thread, "ca_app_thread", ca_app_thread_entry, 0,
                       pointer, SECURITY_APP_STACK_SIZE * 2, 2, 2, 0,
                       TX_DONT_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the stack for the memory access app thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       SECURITY_APP_STACK_SIZE * 2, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the memory access app thread.  */
  if (tx_thread_create(&ma_app_thread, "ma_app_thread", ma_app_thread_entry, 0,
                       pointer, SECURITY_APP_STACK_SIZE * 2, 2, 2, 0,
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
void  sc_app_thread_entry(ULONG arg)
{
  uint8_t index;
  uint32_t pXSize;

  /* Clear the LCD Screen */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  /* Set the Back Color */
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  BSP_LCD_GetXSize(0, &pXSize);
  UTIL_LCD_FillRect(0, 0, pXSize, Font24.Height, UTIL_LCD_COLOR_ST_BLUE_DARK);

  /* Set the Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

  if(TrustZoneMenu.psItems[0].pszTitle != NULL)
  {
    UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)TrustZoneMenu.pszTitle, CENTER_MODE);
  }

  for(index = 0; index < TrustZoneMenu.nItems; index++)
  {
    if(TrustZoneMenu.psItems[index].pIconPath != NULL)
    {
      BSP_LCD_FillRGBRect(0, (uint32_t)TrustZoneMenu.psItems[index].x+1, (uint32_t)TrustZoneMenu.psItems[index].y+1, (uint8_t *)TrustZoneMenu.psItems[index].pIconPath, 64, 64);
    }
  }
  while (1)
  {
    _TrustZoneDemoExec();
  }
}

/**
  * @brief  Application_thread_entry .
  * @param  ULONG arg
  * @retval Void
  */
void  ca_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Control_Access_Demo();
  }
}

/**
  * @brief  Application_thread_entry .
  * @param  ULONG arg
  * @retval Void
  */
void  ma_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Memory_Access_Demo();
  }
}