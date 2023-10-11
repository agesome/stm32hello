/**
  ******************************************************************************
  * @file    eat.h
  * @author  MCD Application Team
  * @brief   Header for eat.c module
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
#ifndef EAT_H
#define EAT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FW_APP_EAT_Run(void);
void dump_eat_token(uint8_t *token, size_t token_size);

#endif /* EAT_H */
