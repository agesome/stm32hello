/**
  ******************************************************************************
  * @file    app_multimedia .c
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

/* Includes ------------------------------------------------------------------*/
#include "k_config.h"
#include "app_audio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define AUDIO_APP_STACK_SIZE                          (1024)
/* Display columns positions */
/* Private function prototypes -----------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
TX_THREAD                                au_app_thread;
/* Private typedef -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/**
* @brief  Application Audio Initialization.
* @param memory_ptr: memory pointer
* @retval int
*/
UINT Audio_Init_pool(VOID *memory_ptr)
{
  UINT ret = UX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_USBX_Host_MEM_POOL */
#if (USE_MEMORY_POOL_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for multimedia App thread. */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       (AUDIO_APP_STACK_SIZE * 2), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the multimedia App thread. */
  if (tx_thread_create(&au_app_thread, "cr_app_thread", au_app_thread_entry, 0,
                       pointer, (AUDIO_APP_STACK_SIZE * 2), 25, 25, 0,
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
void  au_app_thread_entry(ULONG arg)
{
  while (1)
  {
    Audio_Recplay_Demo();
  }
}
