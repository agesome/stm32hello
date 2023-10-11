/**
  ******************************************************************************
  * @file    app_usbpd.c
  * @author  MCD Application Team
  * @brief   usbpd application implementation.
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
#include "usbpd_dpm_user.h"
#include "usbpd_dpm_core.h"
#include "stm32h573i_discovery_usbpd_pwr.h"
#include "app_usbpd.h"
/* Private typedef ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Menu_Init(void);
void Data_Role_Swap(void);
void Power_Role_Swap(void);
void Get_Src_Capa(void);
void Get_Sink_Capa(void);
void Switch_Command_Menu(void);
void Get_Name_Device(void);
void Mouse_Direction(void);
/* Private Variable ----------------------------------------------------------*/
#define CURSOR_STEP     2
uint8_t Device_Menu = 3;
#define USER_Delay 600 /* 600ms for delay display */
uint8_t PortNum =0;
extern uint8_t AlertPower;
extern uint8_t AlertRole;
extern TX_THREAD                                MenuUSBPD_app_thread;
extern TX_THREAD                                Display_thread_entry;
/* Private typedef -----------------------------------------------------------*/
Point MouseUp[]= {{90, 95}, {120, 35}, {150, 95}};
Point MouseLeft[]= {{25, 130}, {85, 100}, {85, 160}};
Point MouseRigh[]= {{155, 100}, {215, 130}, {155, 160}};
Point MouseDown[]= {{90, 165}, {150, 165}, {120, 225}};
/* External variables --------------------------------------------------------*/
extern ux_app_devInfotypeDef          ux_dev_info;
LONG  old_Pos_X;
LONG  old_Pos_Y;
extern LONG Pos_x;
extern LONG Pos_y;
__IO uint32_t tsState = 0;
__IO uint32_t TsState_Mouse = 0;
extern Button_State Button_State_Pressed;
extern int Cable_State;
/* Initialize position menu value*/
int Button   = 0;
/* Callback the Joystick Event */
extern __IO int TsStateCallBack;
extern __IO int Ts_MouseCallback;
extern TS_State_t TS_State;
extern UCHAR String_Descriptor[50];
uint8_t  NameDevice_In_LCD[50];
/* Initialize graphical mouse value */
int X=0 ,Y=24 , Old_X=0 ,Old_Y=24;

__IO uint32_t Old_Device_Menu;
void MenuUSBPD(void)
{
  uint8_t exit = 0;
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"  USBPD  ", CENTER_MODE);
  /* Initialize Old_Device_Menu MODE */
  Old_Device_Menu = 3;
  /* Initialize Button mouse */
  Button_State_Pressed = Button_Reset;
  /* Initialize BOARD MODE */
  uint32_t Old_Board_Mode;
  /* Initialize Cable State */
  uint32_t Old_Cable_State = 3;
  /* Initialize position menu value */
  Button = 0;
  /* Make sure to refresh with the right board mode */
  /* No DFP/No UFP */
  Old_Board_Mode = 3;
  do
  {
    Ts_MouseCallback = 0;
    tsState = Ts_MouseCallback;
    if((Cable_State != USBPD_CAD_EVENT_ATTACHED) && (Cable_State != USBPD_CAD_EVENT_ATTEMC))
    {
      if (Old_Cable_State != 0)
      {
        Menu_Init();
        Old_Cable_State = 0;
      }
      tsState = Ts_MouseCallback;
      /* Exit button */
      BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
      if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
      {
        exit = 1;
        HAL_Delay(50);
      }
    }
    else
    {
      if (!Old_Cable_State)
      {
        UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
        Old_Cable_State = 1;
      }
      /* display power role */
      /* Board on Sink Mode */
      if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SNK)
      {
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)"SNK  ", RIGHT_MODE);
      }
      /* Board on Source Mode */
      else if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SRC)
      {
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_LIGHTRED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)"SRC  ", RIGHT_MODE);
      }
      tsState = Ts_MouseCallback;

      /* Board in Device Mode */
      if  (USBPD_PORTDATAROLE_UFP == DPM_Params[0].PE_DataRole)
      {
        if  (Old_Board_Mode != DPM_Params[0].PE_DataRole)
        {
          UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
          Device_Menu = 0;
          Old_Board_Mode = DPM_Params[0].PE_DataRole;
        }
        if (Device_Menu == 0)
        {
          if (Old_Device_Menu != Device_Menu)
          {
            Mouse_Direction();
            Old_Device_Menu = Device_Menu;
          }
          /* MOUSE traitement */

          if((TS_State.TouchX > 90) && (TS_State.TouchX < 150) && (TS_State.TouchY > 35) && (TS_State.TouchY < 95)&&(TS_State.TouchDetected))
          {
            TsState_Mouse = 1; /* Mouse to UP */
          }
          else if((TS_State.TouchX > 25) && (TS_State.TouchX < 85) && (TS_State.TouchY > 100) && (TS_State.TouchY < 160)&&(TS_State.TouchDetected))
          {
            TsState_Mouse = 2; /* Mouse to LEFT */
          }
          else if((TS_State.TouchX > 155) && (TS_State.TouchX < 215) && (TS_State.TouchY > 100) && (TS_State.TouchY < 160)&&(TS_State.TouchDetected))
          {
            TsState_Mouse = 3; /* Mouse to RIGHT */
          }
          else if((TS_State.TouchX > 90) && (TS_State.TouchX < 155) && (TS_State.TouchY > 165) && (TS_State.TouchY < 225)&&(TS_State.TouchDetected))
          {
            TsState_Mouse = 4; /* Mouse to DOWN */
          }
          else if((TS_State.TouchX > 90) && (TS_State.TouchX < 150) && (TS_State.TouchY > 100) && (TS_State.TouchY < 160))
          {
            if(Ts_MouseCallback)
            {
              TsState_Mouse = 5; /* Select */
            }
            else
            {
              extern uint32_t Old_TsState_Mouse ;
              if (!Old_TsState_Mouse)
              {
                TsState_Mouse = 6; /* Released */
              }
              else
              {
              TsState_Mouse = 0; /* Released */
              }
            }
          }
          else
          {
            TsState_Mouse = 0;
          }
        }
        else if (Device_Menu == 1)
        {
          Switch_Command_Menu();
          if (Old_Device_Menu != Device_Menu)
          {
            UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
            Old_Device_Menu = Device_Menu;
          }
        }
        /* Switch menu request */
        UTIL_LCD_SetFont(&Font20);
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_DARKBLUE);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
        UTIL_LCD_DisplayStringAt(0, 220, (uint8_t *)"Switch", LEFT_MODE);
        if((TS_State.TouchX < 67) && (TS_State.TouchY > 210)&&(TS_State.TouchDetected))
        {
          Device_Menu = !(Device_Menu);
          UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKBLUE);
          UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"Switching menu..", CENTER_MODE);
          HAL_Delay(500);
          UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
        }
        /* Exit button */
        BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
        if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
        {
          exit = 1;
          HAL_Delay(50);
        }
      }
      /* Board in Host Mode */
      else if (USBPD_PORTDATAROLE_DFP == DPM_Params[0].PE_DataRole)
      {
        /* Clear Display */
        if  (Old_Board_Mode !=DPM_Params[0].PE_DataRole)
        {
          UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
          Switch_Command_Menu();
          Old_Board_Mode = DPM_Params[0].PE_DataRole;
        }
        /* Exit button */
        BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
        if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
        {
          exit = 1;
          HAL_Delay(50);
        }
        Get_Name_Device();
        /* refresh screen when DRS is done */
        if  (Old_Board_Mode !=DPM_Params[0].PE_DataRole)
        {
          UTIL_LCD_FillRect(0, 30, 240, 210,UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetFont(&Font20);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)"Data Role Swap", CENTER_MODE);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
          UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)"Power Role Swap", CENTER_MODE);
          if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SRC)
          {
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
            UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" Get Sink Capa ", CENTER_MODE);
          }
          else  if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SNK)
          {
            UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
            UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)"Get Source Capa", CENTER_MODE);
          }
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
          UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)"Return", CENTER_MODE);
          Old_Board_Mode = DPM_Params[0].PE_DataRole;
        }
        /* GET BOARD MODE MOUSE */
        if ((ux_dev_info.Device_Type == Mouse_Device) && (ux_dev_info.Dev_state == Device_connected))
        {
          UTIL_LCD_SetFont(&Font12);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
          UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)NameDevice_In_LCD, CENTER_MODE);

          if ((Pos_x != old_Pos_X) || (Pos_y != old_Pos_Y))
          {
            /* screen cropping */
            if (Pos_x > old_Pos_X )
            {
              X = X + CURSOR_STEP;
              if (X > 115 )
                X = 115;
            }
            if (Pos_x < old_Pos_X )
            {
              X = X-CURSOR_STEP;
              if (X < -144 )
                X = -144;
            }
            if (Pos_y > old_Pos_Y )
            {
              Y = Y+CURSOR_STEP;
              if (Y > 220 )
                Y = 220;
            }
            if (Pos_y < old_Pos_Y )
            {
              Y = Y-CURSOR_STEP;
              if (Y < 24 )
                Y = 24;
            }
            /* delete the old cursor */
            UTIL_LCD_SetFont(&Font24);
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
            UTIL_LCD_DisplayStringAt(Old_X, Old_Y, (uint8_t *)" ", CENTER_MODE);
            /*check change position*/
            old_Pos_X = Pos_x;
            old_Pos_Y = Pos_y;
            /* refresh screen */
            Old_X = X;
            Old_Y = Y;
            UTIL_LCD_SetFont(&Font20);
            if ((( Old_X > -100 )&& ( Old_X < 100 )) && ((Old_Y > 30 ) && (Old_Y < 52 )))
            {
              Button = 0;
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(74, 215, (uint8_t *)" ", CENTER_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)">", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)"<", RIGHT_MODE);
            }
            else if ((( Old_X > -99 )&& ( Old_X < 99 )) &&  ((Old_Y > 87 ) && (Old_Y < 99 )))
            {
              Button = 1;
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(74, 215, (uint8_t *)" ", CENTER_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)">", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)"<", RIGHT_MODE);
            }
            else if ((( Old_X > -92 )&& ( Old_X < 85 )) &&  ((Old_Y > 132 ) && (Old_Y < 150 )))
            {
              Button = 2;
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(74, 215, (uint8_t *)" ", CENTER_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)">", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)"<", RIGHT_MODE);
            }
            else if ((( Old_X > 80 )&& ( Old_X < 112 )) &&  ((Old_Y > 180 ) && (Old_Y < 220 )))
            {
              Button = 3;
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(74, 215, (uint8_t *)">", CENTER_MODE);
            }
            else
            {
              Button = 4;
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", LEFT_MODE);
              UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" ", RIGHT_MODE);
              UTIL_LCD_DisplayStringAt(74, 215, (uint8_t *)" ", CENTER_MODE);
            }
            UTIL_LCD_SetFont(&Font24);
            UTIL_LCD_SetBackColor(UTIL_LCD_GetBackColor());
            UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
            UTIL_LCD_DisplayStringAt(X, Y, (uint8_t *)"*", CENTER_MODE);
          }
          if (Button_State_Pressed == LEFT_Button_Pressed )
          {
            Button_State_Pressed = Button_Reset;
            /* Data Role Swap */
            if (Button == 0)
            {
              /* Power Role Swap */
              Data_Role_Swap();
            }
            /* Power Role Swap */
            if (Button == 1)
            {
              Power_Role_Swap();
            }
            /* Get SNK Capa*/
            if ((Button == 2)&&(DPM_Params[0].PE_PowerRole ==  USBPD_PORTPOWERROLE_SRC))
            {
              Get_Sink_Capa();
            }
            /* Get SRC Capa */
            if ((Button == 2)&&(DPM_Params[0].PE_PowerRole ==  USBPD_PORTPOWERROLE_SNK))
            {
              Get_Src_Capa();
            }
            if (Button == 3)
            {
              /* Exit */
              exit = 1;
              HAL_Delay(50);
            }
            /* Exit button */
            BSP_LCD_FillRGBRect(0, 200, 200, (uint8_t *)GoBack, 40, 40);
            if((TS_State.TouchX > 200) && (TS_State.TouchY > 200))
            {
              exit = 1;
              HAL_Delay(50);
            }
            Button_State_Pressed = Button_Reset;
          }
          Switch_Command_Menu();
        }
        else
        {
          UTIL_LCD_SetFont(&Font12);
          UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
          UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE);
          UTIL_LCD_DisplayStringAt(0, 180, (uint8_t *)NameDevice_In_LCD, CENTER_MODE);
          Switch_Command_Menu();
        }
        Old_Device_Menu = 3;
      }

      if (USBPD_PORTDATAROLE_DFP == DPM_Params[0].PE_DataRole)
      {
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_LIGHTRED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)" HOST  ", LEFT_MODE);
      }
      else if (USBPD_PORTDATAROLE_UFP == DPM_Params[0].PE_DataRole)
      {
        UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)" DEVICE", LEFT_MODE);
      }
    }
  } while (exit == 0);
  tsState = 0;
  tx_thread_terminate(&Display_thread_entry);
  tx_thread_reset(&Display_thread_entry);
  tx_thread_resume(&Display_thread_entry);
  tx_thread_suspend(&MenuUSBPD_app_thread);
}
void Menu_Init(void)
{
  /* Initialize menu */
  UTIL_LCD_FillRect(0, 25, 240, 214,UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_DisplayStringAt(0, 100, (uint8_t *)"Please connect", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 135, (uint8_t *)"Your USB Cable", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)"DRP  ", RIGHT_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(1, 2, (uint8_t *)"        ", LEFT_MODE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"  USBPD  ", CENTER_MODE);
  Old_Device_Menu = 3;
}
void Switch_Command_Menu(void)
{
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)"Data Role Swap", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)"Power Role Swap", CENTER_MODE);
  if (DPM_Params[0].PE_PowerRole ==  USBPD_PORTPOWERROLE_SRC)
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" Get Sink Capa ", CENTER_MODE);
  }
  else  if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SNK )
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)"Get Source Capa", CENTER_MODE);
  }

  /* Data Role Swap Request */
  if((TS_State.TouchX > 25) &&(TS_State.TouchX < 225) && (TS_State.TouchY > 30)&& (TS_State.TouchY < 75)&&(TS_State.TouchDetected))
  {
    UTIL_LCD_SetFont(&Font20);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 40, (uint8_t *)"Data Role Swap", CENTER_MODE);
    Data_Role_Swap();
  }

  /* Power Role Swap Request */
  if((TS_State.TouchX > 25) &&(TS_State.TouchX < 225) && (TS_State.TouchY > 75)&& (TS_State.TouchY < 120)&&(TS_State.TouchDetected))
  {
    UTIL_LCD_SetFont(&Font20);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 90, (uint8_t *)"Power Role Swap", CENTER_MODE);
    Power_Role_Swap();
  }
  /* Get Source/Sink Capabilities Request */
  if((TS_State.TouchX > 25) && (TS_State.TouchX < 225) && (TS_State.TouchY > 120) && (TS_State.TouchY < 165) && (TS_State.TouchDetected))
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SRC)
    {
      UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)" Get Sink Capa ", CENTER_MODE);
      Get_Sink_Capa();
    }
    else  if (DPM_Params[0].PE_PowerRole == USBPD_PORTPOWERROLE_SNK)
    {
      UTIL_LCD_DisplayStringAt(0, 140, (uint8_t *)"Get Source Capa", CENTER_MODE);
      Get_Src_Capa();
    }
  }
}
void Get_Sink_Capa(void)
{
  if (USBPD_DPM_RequestGetSinkCapability(PortNum))
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" GET_SINK_CAPA not accepted ", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, 210, (uint8_t *)" by the stack ", CENTER_MODE);
    HAL_Delay(3*USER_Delay);
  }
  else
  {
    UTIL_LCD_FillRect(16, 46,208, 168, UTIL_LCD_COLOR_GRAY);
    UTIL_LCD_FillRect(20, 50,200, 160, UTIL_LCD_COLOR_BLACK);
    UTIL_LCD_FillRect(16, 46,208, 168, UTIL_LCD_COLOR_GRAY);
    UTIL_LCD_FillRect(20, 50,200, 160, UTIL_LCD_COLOR_BLACK);
    do
    {
      UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
      UTIL_LCD_SetFont(&Font20);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_YELLOW);
      UTIL_LCD_DisplayStringAt(22, 50, (uint8_t *)"Get SNK Capa", LEFT_MODE);
      uint8_t _str[30];
      uint8_t Y_PoS = 100;
      uint32_t maxcurrent = DPM_Ports[PortNum].DPM_RequestedCurrent;
      uint32_t maxvoltage = DPM_Ports[PortNum].DPM_RequestedVoltage;
      sprintf((char*)_str, "USED :%2ldV %2ld.%ldA", maxvoltage/1000, maxcurrent/1000, (maxcurrent % 1000) /100);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
      UTIL_LCD_SetFont(&Font16);
      UTIL_LCD_DisplayStringAt(22, 80, (uint8_t *)_str, LEFT_MODE);
      for(int8_t index=0; index < DPM_Ports[PortNum].DPM_NumberOfRcvSNKPDO; index++)
      {
        switch((uint32_t)((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_TYPE_Msk) >> USBPD_PDO_TYPE_Pos))
        {
        case USBPD_CORE_PDO_TYPE_FIXED :
          {
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_FIXED_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_FIXED_MAX_CURRENT_Pos)*10;
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_FIXED_VOLTAGE_Msk) >> USBPD_PDO_SRC_FIXED_VOLTAGE_Pos)*50;
           if (maxcurrent != 0)
              sprintf((char*)_str, "FIXED:%2ldV %ld.%ldA", maxvoltage/1000, maxcurrent/1000, (maxcurrent % 1000) /100);
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        case USBPD_CORE_PDO_TYPE_BATTERY :
          {
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_BATTERY_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_BATTERY_MAX_VOLTAGE_Pos) * 50;
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_BATTERY_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_BATTERY_MIN_VOLTAGE_Pos) * 50;
            uint32_t maxpower = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_BATTERY_MAX_POWER_Msk) >> USBPD_PDO_SRC_BATTERY_MAX_POWER_Pos) * 250;
            if (maxpower != 0)
              sprintf((char*)_str, "BATT :%ld-%2ldV %ldW", (minvoltage/1000), (maxvoltage/1000), (maxpower/1000));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        case USBPD_CORE_PDO_TYPE_VARIABLE :
          {
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_VARIABLE_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_VARIABLE_MAX_VOLTAGE_Pos) * 50;
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_VARIABLE_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_VARIABLE_MIN_VOLTAGE_Pos) * 50;
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_VARIABLE_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_VARIABLE_MAX_CURRENT_Pos) * 10;
            if (maxcurrent != 0)
              sprintf((char*)_str, "VAR  :%ld-%2ldV %ld.%ldA", (minvoltage/1000), (maxvoltage/1000), (maxcurrent/1000), ((maxcurrent % 1000) /100));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        case USBPD_CORE_PDO_TYPE_APDO :
          {
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_APDO_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_APDO_MIN_VOLTAGE_Pos) * 100;
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_APDO_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_APDO_MAX_VOLTAGE_Pos) * 100;
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] & USBPD_PDO_SRC_APDO_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_APDO_MAX_CURRENT_Pos) * 50;
            if (maxcurrent != 0)
              sprintf((char*)_str, "APDO :%ld-%2ldV %ld.%ldA", (minvoltage/1000), (maxvoltage/1000), (maxcurrent/1000), ((maxcurrent % 1000) /100));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        }

        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, Y_PoS, (uint8_t *)_str, LEFT_MODE);
        Y_PoS += 20;
      }
      UTIL_LCD_SetFont(&Font12);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
      UTIL_LCD_DisplayStringAt(22, 197, (uint8_t *)"press anywhere to exit.", LEFT_MODE);
    } while ((TS_State.TouchDetected == 0) && (Pos_x == old_Pos_X) && (Pos_y == old_Pos_Y));
  }
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_FillRect(0, 0, 240, 24,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)" USBPD", CENTER_MODE);
  Switch_Command_Menu();
}
void Get_Src_Capa(void)
{

  if (USBPD_DPM_RequestGetSourceCapability(PortNum))
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" GET_SRC_CAPA not accepted ", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, 210, (uint8_t *)" by the stack ", CENTER_MODE);
    HAL_Delay(3*USER_Delay);
  }
  else{

    UTIL_LCD_FillRect(16, 46,208, 168, UTIL_LCD_COLOR_GRAY);
    UTIL_LCD_FillRect(20, 50,200, 160, UTIL_LCD_COLOR_BLACK);
    UTIL_LCD_FillRect(16, 46,208, 168, UTIL_LCD_COLOR_GRAY);
    UTIL_LCD_FillRect(20, 50,200, 160, UTIL_LCD_COLOR_BLACK);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_PINK);
    UTIL_LCD_SetFont(&Font16);
    UTIL_LCD_DisplayStringAt(22, 80 , (uint8_t *)"Capas:", LEFT_MODE);
    do
    {
      uint8_t _str[30];
      uint8_t Y_PoS = 80;

      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
      for(int8_t index=0; index < DPM_Ports[PortNum].DPM_NumberOfRcvSRCPDO; index++)
      {
        switch((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_TYPE_Msk) >> USBPD_PDO_TYPE_Pos)
        {
        case USBPD_CORE_PDO_TYPE_FIXED :
          {
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_FIXED_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_FIXED_MAX_CURRENT_Pos)*10;
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_FIXED_VOLTAGE_Msk) >> USBPD_PDO_SRC_FIXED_VOLTAGE_Pos)*50;
            if (maxcurrent != 0)
              sprintf((char*)_str, "FIXED: %2ldV %ld.%ldA", (maxvoltage/1000), (maxcurrent/1000), ((maxcurrent % 1000) /100));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        case USBPD_CORE_PDO_TYPE_BATTERY :
          {
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_BATTERY_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_BATTERY_MAX_VOLTAGE_Pos) * 50;
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_BATTERY_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_BATTERY_MIN_VOLTAGE_Pos) * 50;
            uint32_t maxpower = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_BATTERY_MAX_POWER_Msk) >> USBPD_PDO_SRC_BATTERY_MAX_POWER_Pos) * 250;
            if (maxpower != 0)
              sprintf((char*)_str, "BATT:%ld-%2ldV %ldW", (minvoltage/1000),(maxvoltage/1000),(maxpower/1000));
            else
              sprintf((char*)_str, "Error in decoding");

          }
          break;
        case USBPD_CORE_PDO_TYPE_VARIABLE :
          {
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_VARIABLE_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_VARIABLE_MAX_VOLTAGE_Pos) * 50;
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_VARIABLE_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_VARIABLE_MIN_VOLTAGE_Pos) * 50;
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_VARIABLE_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_VARIABLE_MAX_CURRENT_Pos) * 10;
            if (maxcurrent != 0)
              sprintf((char*)_str, "VAR: %ld-%2ldV %ld.%ldA", (minvoltage/1000), (maxvoltage/1000), (maxcurrent/1000), ((maxcurrent % 1000) /100));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        case USBPD_CORE_PDO_TYPE_APDO :
          {
            uint32_t minvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_APDO_MIN_VOLTAGE_Msk) >> USBPD_PDO_SRC_APDO_MIN_VOLTAGE_Pos) * 100;
            uint32_t maxvoltage = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_APDO_MAX_VOLTAGE_Msk) >> USBPD_PDO_SRC_APDO_MAX_VOLTAGE_Pos) * 100;
            uint32_t maxcurrent = ((DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] & USBPD_PDO_SRC_APDO_MAX_CURRENT_Msk) >> USBPD_PDO_SRC_APDO_MAX_CURRENT_Pos) * 50;
            if (maxcurrent != 0)
              sprintf((char*)_str, "APDO:%ld-%ldV %ld.%ldA", (minvoltage/1000),(maxvoltage/1000),(maxcurrent/1000), ((maxcurrent % 1000) /100));
            else
              sprintf((char*)_str, "Error in decoding");
          }
          break;
        }
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(100, Y_PoS, (uint8_t *)_str, LEFT_MODE);
        Y_PoS += 20;
      }
      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_DRD_SUPPORT_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 100, (uint8_t *)"DRD *", LEFT_MODE);
      }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 100, (uint8_t *)"DRD     ", LEFT_MODE);
      }

      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_DRP_SUPPORT_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 115, (uint8_t *)"DRP *", LEFT_MODE);       }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 115, (uint8_t *)"DRP     ", LEFT_MODE);
      }
      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_USBCOMM_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 130, (uint8_t *)"USB *", LEFT_MODE);
      }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 130, (uint8_t *)"USB     ", LEFT_MODE);
      }
      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_UNCHUNK_SUPPORT_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 145, (uint8_t *)"UNCK *", LEFT_MODE);
      }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 145, (uint8_t *)"UNCK    ", LEFT_MODE);
      }
      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_EXT_POWER_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 160, (uint8_t *)"EPW *", LEFT_MODE);
      }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 160, (uint8_t *)"EPW    ", LEFT_MODE);
      }
      if( DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[0] & USBPD_PDO_SRC_FIXED_USBSUSPEND_Msk)
      {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_CYAN);
        UTIL_LCD_SetFont(&Font16);
        UTIL_LCD_DisplayStringAt(22, 175, (uint8_t *)"SUSP *", LEFT_MODE);      }
      else {
        UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
        UTIL_LCD_SetFont(&Font12);
        UTIL_LCD_DisplayStringAt(22, 175, (uint8_t *)"SUSP    ", LEFT_MODE);
      }
      UTIL_LCD_SetFont(&Font20);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_YELLOW);
      UTIL_LCD_DisplayStringAt(22, 50, (uint8_t *)"Get SRC Capa", LEFT_MODE);
      UTIL_LCD_SetFont(&Font12);
      UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
      UTIL_LCD_DisplayStringAt(22, 195, (uint8_t *)"press anywhere to exit.", LEFT_MODE);
    } while ((TS_State.TouchDetected == 0) && (Pos_x == old_Pos_X) && (Pos_y == old_Pos_Y));
  }
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_FillRect(0, 0, 240, 24,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)" USBPD", CENTER_MODE);
  Switch_Command_Menu();
}
void Power_Role_Swap(void)
{
  if ( USBPD_DPM_RequestPowerRoleSwap(PortNum) )
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" PWR_Role_SWAP not accepted ", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, 210, (uint8_t *)" by the stack ", CENTER_MODE);
  }
  else
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_GREEN);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" POWER SWAPPED ", CENTER_MODE);
  }
  if ( AlertPower == PowerRejected )
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" PWR_Role_SWAP rejected ", CENTER_MODE);
    AlertPower= PowerInitState;
  }
  else if ( AlertPower == PowerNotSupported )
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" PWR_Role_SWAP Not Supported ", CENTER_MODE);
    AlertPower= PowerInitState;
  }
  HAL_Delay(3*USER_Delay);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_FillRect(0, 0, 240, 24,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)" USBPD", CENTER_MODE);
  Switch_Command_Menu();
}
void Data_Role_Swap(void)
{
  if (USBPD_DPM_RequestDataRoleSwap(PortNum))
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" DRS not accepted by the stack ", CENTER_MODE);
  }
  else
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_GREEN);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" DATA Role SWAPPED ", CENTER_MODE);
  }
  if ( AlertRole == RoleRejected )
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" DATA_Role_SWAP rejected ", CENTER_MODE);

    AlertRole= RoleInitState;
  }
  else if ( AlertRole == RoleNotSupported )
  {
    UTIL_LCD_SetFont(&Font12);
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_FillRect(0, 200,240, 40, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(0, 200, (uint8_t *)" DATA_Role_SWAP Not Supported ", CENTER_MODE);
    AlertRole= RoleInitState;
  }
  HAL_Delay(3*USER_Delay);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_FillRect(0, 0, 240, 24,UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)" USBPD", CENTER_MODE);
  Switch_Command_Menu();
}
void Get_Name_Device(void)
{
  int j =0;
  for (int i=2; i< 49; i++)
  {
    if ( String_Descriptor[i] != 0 )
    {
      NameDevice_In_LCD[j] = String_Descriptor[i];
      j++;
    }
  }
  for (int i=j; i< 49; i++)
  {
    NameDevice_In_LCD[i] = 0;
  }
}
void Mouse_Direction(void)
{
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_ST_BLUE_DARK);
  UTIL_LCD_DisplayStringAt(0, 30, (uint8_t *)"MOUSE", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(0, 55, (uint8_t *)"MODE", LEFT_MODE);
  /* Display Mouse arrow */
  UTIL_LCD_FillPolygon(MouseUp, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MouseLeft, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MouseRigh, 3, UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_FillPolygon(MouseDown, 3, UTIL_LCD_COLOR_GREEN);
  BSP_LCD_FillRGBRect(0, 85, 95, (uint8_t *)EnterIcon, 70, 70);
}
