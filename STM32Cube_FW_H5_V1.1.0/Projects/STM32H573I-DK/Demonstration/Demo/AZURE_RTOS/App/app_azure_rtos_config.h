
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos_config.h
  * @author  MCD Application Team
  * @brief   app_azure_rtos config header file
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_AZURE_RTOS_CONFIG_H
#define APP_AZURE_RTOS_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* Using static memory allocation via threadX Byte memory pools */

#define USE_MEMORY_POOL_ALLOCATION               1

#define TX_APP_MEM_POOL_SIZE                     1024

#define FX_APP_MEM_POOL_SIZE                     1024

#define UX_USB_APP_MEM_POOL_SIZE                 (120 * 1024)

#if defined(GUI_INTERFACE)
#define GUI_INTERFACE_APP_MEM_POOL_SIZE           5000
#endif /* GU_INTERFACE */
  
#define USBPD_DEVICE_APP_MEM_POOL_SIZE           5000

#define Kmodule_APP_MEM_POOL_SIZE                (10 * 1024)

#define Calendar_APP_MEM_POOL_SIZE               (24 * 1024)

#define Crypto_APP_MEM_POOL_SIZE                 (5 * 1024)

#define Security_APP_MEM_POOL_SIZE               (10 * 1024)

#define Audio_APP_MEM_POOL_SIZE                  (5 * 1024)

#define About_Demo_APP_MEM_POOL_SIZE             (5 * 1024)

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

#ifdef __cplusplus
}
#endif

#endif /* APP_AZURE_RTOS_CONFIG_H */
