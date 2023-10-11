/**
  ******************************************************************************
  * @file    app_security.h
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

#undef GLOBAL
#ifdef __APP_TRUST_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
void Control_Access_Demo(void);
void Memory_Access_Demo(void);
UINT Security_Init_pool(VOID *memory_ptr);
void  sc_app_thread_entry(ULONG arg);
void  ca_app_thread_entry(ULONG arg);
void  ma_app_thread_entry(ULONG arg);

/* Exported functions --------------------------------------------------------*/
