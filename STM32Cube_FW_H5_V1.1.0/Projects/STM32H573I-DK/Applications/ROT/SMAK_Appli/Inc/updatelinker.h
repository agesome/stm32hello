/**
  ******************************************************************************
  * @file    update_linker.h
  * @author  MCD Application Team
  * @brief   Header for .icf and .ld files
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UPDATELINKER_H
#define UPDATELINKER_H

/* 
   Do not edit manually !!!
   The values below are automatically updated by Firmware\Projects\STM32H573I-DK\ROT_Provisioning\SMAK\Provisioning.bat/sh script
 */

#define CODE_OFFSET          0x77*0x2000              /* This define is updated automatically by SMAK provisioning script */
#define CODE_SIZE            0x77*0x2000              /* This define is updated automatically by SMAK provisioning script */
#define IMAGE_HEADER_SIZE    0x400                    /* mcuboot header size */
#define TRAILER_MAX_SIZE     0x40                     /* max size trailer */


#endif /* UPDATELINKER_H */