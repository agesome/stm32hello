/**
  ******************************************************************************
  * @file    fwu.h
  * @author  MCD Application Team
  * @brief   Header for fwu.c module
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
#ifndef FWU_H
#define FWU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"
#include "psa/update.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define NB_MODULE 0x0
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FW_APP_FWU_Run(void);
void print_image_info(psa_image_info_t info, psa_status_t psa_status);

#endif /* FWU_H */
