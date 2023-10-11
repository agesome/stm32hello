/**
  ******************************************************************************
  * @file    app_multimedia.h
  * @author  MCD Application Team
  * @brief   Audio application interface
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
#ifndef __APP_AUDIO_H
#define __APP_AUDIO_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
UINT Audio_Init_pool(VOID *memory_ptr);
void  au_app_thread_entry(ULONG arg);

#endif /* __APP_AUDIO_H */
