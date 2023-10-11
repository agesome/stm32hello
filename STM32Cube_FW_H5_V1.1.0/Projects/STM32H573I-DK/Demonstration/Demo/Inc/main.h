/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_lcd.h"
#include "resources.h"
#include "stm32h573i_discovery.h"
#include "stm32h573i_discovery_ts.h"
#include "stm32h573i_discovery_lcd.h"
#include "stm32h573i_discovery_bus.h"
#include "stm32h573i_discovery_sd.h"
#include "stm32h573i_discovery_ospi.h"
#include "stm32h573i_discovery_audio.h"
#include "pdm2pcm_glo.h"
#include "app_usbx_host.h"
#include "audio_recplay.h"

/* Exported types ------------------------------------------------------------*/

typedef struct sMenuItem tMenuItem;
typedef struct sMenu tMenu;
struct sMenuItem
{
  char *pszTitle;
  uint16_t x;
  uint16_t y;
  char *pIconPath;
  char *pIconSelectedPath;
};

struct sMenu
{
  char* pszTitle;
  const tMenuItem *psItems;
  uint32_t nItems;
  uint8_t line;
  uint8_t column;
};

typedef enum {
  KMODULE_OK,
  /* Module exec */
  KMODULE_ERROR_PRE,
  KMODULE_ERROR_EXEC,
  KMODULE_ERROR_POST,
  KMODULE_ERROR_ICON,
  KMODULE_RESMISSIG
} KMODULE_RETURN;
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define ICON_WIDTH  64
#define ICON_HEIGHT 64
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_Config(void);
void RTC_UnConfig(void);
void SystemClock_Config(void);
extern void Error_Handler(void);


void Display_Thread_Entry(ULONG arg);
/* Private defines -----------------------------------------------------------*/
void   MX_USB_DRD_FS_HCD_Init(void);
void   MX_USB_DRD_FS_PCD_Init(void);
void   MX_USART1_UART_Init(void);
void   Board_Mode(void) ;
void   CACHE_Enable(void);
void   CACHE_Disable(void);
/* USER CODE BEGIN Private defines */

typedef enum {
 _HOST_ = 1,
 _DEVICE_,
} _BOARD_MODE;

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
