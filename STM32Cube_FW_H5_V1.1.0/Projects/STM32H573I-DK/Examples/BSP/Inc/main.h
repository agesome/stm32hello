/**
  ******************************************************************************
  * @file    Examples/BSP/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
#ifndef MAIN_H
#define MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm32h5xx_hal.h"
#include "stm32h573i_discovery.h"
#include "stm32h573i_discovery_lcd.h"
#include "stm32h573i_discovery_sd.h"
#include "stm32h573i_discovery_ts.h"
#include "stm32h573i_discovery_audio.h"
#include "stm32h573i_discovery_ospi.h"
#include "stm32_lcd.h"
/* Include PDM to PCM lib header file */
#include "pdm2pcm_glo.h"
#include "resources.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TS_State_t TS_State;
extern __IO FlagStatus UserButtonPressed;
extern __IO uint32_t TouchPressed;
extern __IO uint8_t StepBack;
extern TS_Init_t hTS;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Menu_Display(void);
void Test_Led(void);
void Test_Lcd(void);
void Test_Ts(void);
void Test_Sd(void);
void Test_Ospi(void);
void Test_Audio(void);

uint8_t AUDIO_Process(void);
void Error_Handler(void);
#endif /* MAIN_H */
