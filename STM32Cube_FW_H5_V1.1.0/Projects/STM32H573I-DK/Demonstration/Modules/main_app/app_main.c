/**
  ******************************************************************************
  * @file    app_main.c
  * @author  MCD Application Team
  * @brief   Main application (root menu) implementation
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
#define __APP_MAIN_C

/* Includes ------------------------------------------------------------------*/
#include "k_config.h"
#include "app_main.h"
/* Private constants ---------------------------------------------------------*/

/* Display columns positions */
#define X1_POS    32
#define X2_POS    X1_POS + ICON_WIDTH + 3
#define X3_POS    X2_POS + ICON_WIDTH + 3
#define X4_POS    X3_POS + ICON_WIDTH + 3

/* Display ranks positions */
#define Y1_POS    32
#define Y2_POS    Y1_POS + ICON_HEIGHT + 3

/* Private function prototypes -----------------------------------------------*/
KMODULE_RETURN AppMainExec(void);

/* Private Variable ----------------------------------------------------------*/
/* Variable used to exit an execution context */
__IO uint8_t exit_func;
extern TX_THREAD                                Display_thread_entry;
extern TX_THREAD                                sc_app_thread;
extern TX_THREAD                                au_app_thread;
extern TX_THREAD                                MenuUSBPD_app_thread;
extern TX_THREAD                                cal_app_thread;
extern TX_THREAD                                cr_app_thread;
extern TX_THREAD                                ab_app_thread;
extern __IO uint8_t TsStateCallBack;
extern TS_State_t TS_State;
tMenuItem MainMenuItems[] =
{
    {"TrustZone"            , X2_POS, Y1_POS, (char*) IconTrsutZone0   ,(char*) IconTrsutZone1    },
    {"Digital Filters"      , X3_POS, Y1_POS, (char*) IconAudio0       ,(char*) IconAudio1        },
    {"USB-PD"               , X4_POS, Y1_POS, (char*) IconUsbPd0       ,(char*) IconUsbPd1        },
    {"Calendar"             , X2_POS, Y2_POS, (char*) IconCalendar0    ,(char*) IconCalendar1     },
    {"Crypto"               , X3_POS, Y2_POS, (char*) IconCrypto0       ,(char*) IconCrypto1      },
    {"About Demo"           , X4_POS, Y2_POS, (char*) IconSysInfo0     ,(char*) IconSysInfo1      },
};


const tMenu MainMenu = {
  "Main menu", MainMenuItems, countof(MainMenuItems), 3, 4
  };

/* Private typedef -----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/**
  * @brief  Run the main application
  * @param  None.
  * @note   run and display main menu.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN AppMainExec(void)
{
  uint8_t index;
  uint8_t indexcol;
  uint8_t indexlin;
  uint8_t iconnb = countof(MainMenuItems);
  uint32_t x, y;
  uint8_t column_nb;
  uint8_t line_nb;
  uint8_t inter_x;
  uint8_t inter_y;

  kMenu_Init();

  BSP_LCD_GetXSize(0, &x);
  BSP_LCD_GetYSize(0, &y);

#define MIN_INTER_X 2 // Min 2 pixel between each icon
  /* compute nb of icon on a line */
  column_nb = ( x - MIN_INTER_X) / (ICON_WIDTH + MIN_INTER_X) ;

  /* compute nb of icon lines */
  line_nb = (iconnb / column_nb);

  if((iconnb % column_nb) != 0)
  {
    line_nb++;
  }

  /* compute space between incons on x axis */
  inter_x = ((x - (column_nb * ICON_WIDTH)) / (column_nb + 1)) ;

  /* compute space between incons on x axis */
  inter_y = ((y - UTIL_LCD_GetFont()->Height) - (line_nb * ICON_HEIGHT)) / (line_nb + 1);

  /* fill menu item icon position */
  indexcol = 0;
  indexlin = 0;
  for(index = 0; index < iconnb; index++)
  {
    MainMenuItems[index].x = (inter_x + (indexcol * (inter_x + ICON_WIDTH)));
    MainMenuItems[index].y = (inter_y + (UTIL_LCD_GetFont()->Height) + (indexlin * (inter_y + ICON_HEIGHT)));

    /* increment column index */
    indexcol++;
    if(indexcol >= column_nb)
    {
      indexcol = 0;
      indexlin++;
    }
  }

  return KMODULE_OK;
}

/**
  * @brief  function used to start a demo
  * @param  None
  * @retval None
  */
TS_State_t Touch_Status;
void kDemo_Start(void)
{
  uint32_t pXSize;
  uint8_t  index;

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

  if(MainMenu.psItems[0].pszTitle != NULL)
  {
    UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)MainMenu.pszTitle, CENTER_MODE);
  }

  for(index = 0; index < MainMenu.nItems; index++)
  {
    if(MainMenu.psItems[index].pIconPath != NULL)
    {
      BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[index].x+1, (uint32_t)MainMenu.psItems[index].y+1, (uint8_t *)MainMenu.psItems[index].pIconPath, 64, 64);
    }
  }

  uint8_t exit = 0;

  /* Enable the TS interrupt */
  BSP_TS_EnableIT(0);

  do{

    if(TsStateCallBack != 0)
    {
      /* Prevent a single key press being interpreted as multi press */
      HAL_Delay(100);

      TsStateCallBack = 0 ;

      if((TS_State.TouchX > 13) && (TS_State.TouchX < 77) && (TS_State.TouchY > 54) && (TS_State.TouchY < 118))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[0].x+1, (uint32_t)MainMenu.psItems[0].y+1, (uint8_t *)MainMenu.psItems[0].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&sc_app_thread);
        tx_thread_reset(&sc_app_thread);
        tx_thread_resume(&sc_app_thread); /* Security module selected */
      }
      else if((TS_State.TouchX > 89) && (TS_State.TouchX < 153) && (TS_State.TouchY > 54) && (TS_State.TouchY < 118))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[1].x+1, (uint32_t)MainMenu.psItems[1].y+1, (uint8_t *)MainMenu.psItems[1].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&au_app_thread);
        tx_thread_reset(&au_app_thread);
        tx_thread_resume(&au_app_thread); /* Multimidia module selected */
      }
      else if((TS_State.TouchX > 165) && (TS_State.TouchX < 229) && (TS_State.TouchY > 54) && (TS_State.TouchY < 118))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[2].x+1, (uint32_t)MainMenu.psItems[2].y+1, (uint8_t *)MainMenu.psItems[2].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&MenuUSBPD_app_thread);
        tx_thread_reset(&MenuUSBPD_app_thread);
        tx_thread_resume(&MenuUSBPD_app_thread); /* USBPD module selected */
      }
      else if((TS_State.TouchX > 13) && (TS_State.TouchX < 77) && (TS_State.TouchY > 147) && (TS_State.TouchY < 211))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[3].x+1, (uint32_t)MainMenu.psItems[3].y+1, (uint8_t *)MainMenu.psItems[3].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&cal_app_thread);
        tx_thread_reset(&cal_app_thread);
        tx_thread_resume(&cal_app_thread); /* Calendar module selected */
      }
      else if((TS_State.TouchX > 89) && (TS_State.TouchX < 153) && (TS_State.TouchY > 147) && (TS_State.TouchY < 211))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[4].x+1, (uint32_t)MainMenu.psItems[4].y+1, (uint8_t *)MainMenu.psItems[4].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&cr_app_thread);
        tx_thread_reset(&cr_app_thread);
        tx_thread_resume(&cr_app_thread); /* Crypto module selected */
      }
      else if((TS_State.TouchX > 165) && (TS_State.TouchX < 229) && (TS_State.TouchY > 147) && (TS_State.TouchY < 211))
      {
        exit = 1;
        BSP_LCD_FillRGBRect(0, (uint32_t)MainMenu.psItems[5].x+1, (uint32_t)MainMenu.psItems[5].y+1, (uint8_t *)MainMenu.psItems[5].pIconSelectedPath, 64, 64);
        HAL_Delay(50);
        tx_thread_terminate(&ab_app_thread);
        tx_thread_reset(&ab_app_thread);
        tx_thread_resume(&ab_app_thread); /* About module selected */
      }
      else
      {
        /* No module selected */
      }
    }
  } while(exit == 0);

  tx_thread_suspend(&Display_thread_entry);
}

/**
  * @brief  Function to initialize the module menu
  * @retval None
  */
void kMenu_Init(void) {
  TS_Init_t TsInit;

  /* Initialize the TouchScreen */
  TsInit.Width       = 240;
  TsInit.Height      = 240;
  TsInit.Orientation = TS_ORIENTATION_LANDSCAPE;
  TsInit.Accuracy    = 5;
  if (BSP_TS_Init(0, &TsInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
}