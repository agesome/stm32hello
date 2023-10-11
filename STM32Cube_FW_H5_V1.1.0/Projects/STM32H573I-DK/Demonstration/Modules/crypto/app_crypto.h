/**
  ******************************************************************************
  * @file    app_crypto.h
  * @author  MCD Application Team
  * @brief   Images browser application header file
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
#ifdef __APP_IMAGEBROWSER_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
  typedef struct complex {
    float real;
    float imag;
  } complex;
/* External variables --------------------------------------------------------*/
UINT Crypto_Init_pool(VOID *memory_ptr);
void  cr_app_thread_entry(ULONG arg);

/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CIPHER_ZONE_NONCE0               0xA5A5A5A5
#define CIPHER_ZONE_NONCE1               0xC3C3C3C3
#define CIPHER_ZONE__START_ADRESS        0x90000000
#define CIPHER_ZONE__END_ADRESS          0x90001FFF
#define CIPHER_ZONE_FIRMWARE_VERSION     0xDCBA

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
