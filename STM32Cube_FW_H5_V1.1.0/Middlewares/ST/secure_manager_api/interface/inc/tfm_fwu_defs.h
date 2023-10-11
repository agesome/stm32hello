/*
 * @copyright
 * Copyright (c) 2021-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * https://www.trustedfirmware.org/
 * 
 * This file was modified by ProvenRun
 * Copyright (c) 2015-2022 ProvenRun S.A.S. - All Rights Reserved
 * https://www.provenrun.com/ 
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

#ifndef TFM_FWU_BOOTLOADER_DEFS_H
#define TFM_FWU_BOOTLOADER_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Image type identities. When porting a specific bootloader to FWU partition,
 * the bootloader specific image types can be defined here.
 */
/***********
 * Modified by ProvenRun
 * **********/
/********
* Origin
* ********/
//#define FWU_IMAGE_TYPE_NONSECURE        0x01U
//#define FWU_IMAGE_TYPE_SECURE           0x02U
//#define FWU_IMAGE_TYPE_FULL             0x03U
/********
 * Added
 * *******/
 /* private internal values for BL2 access */
#define FWU_IMAGE_TYPE_SECURE_BL2             0x00U
#define FWU_IMAGE_TYPE_MODULE_0_BL2           0x01U
#define FWU_IMAGE_TYPE_MODULE_1_BL2           0x02U
#define FWU_IMAGE_TYPE_MODULE_2_BL2           0x03U
#define FWU_IMAGE_TYPE_MODULE_3_BL2           0x04U
#define FWU_IMAGE_TYPE_MODULE_4_BL2           0x05U
#define FWU_IMAGE_TYPE_MODULE_5_BL2           0x06U
#define FWU_IMAGE_TYPE_MODULE_6_BL2           0x07U
#define FWU_IMAGE_TYPE_MODULE_7_BL2           0x08U
#define FWU_IMAGE_TYPE_NONSECURE_BL2          0x09U

/* public values */
#define FWU_IMAGE_TYPE_SECURE             0x00U
#define FWU_IMAGE_TYPE_NONSECURE          0x01U
#define FWU_IMAGE_TYPE_MODULE_0           0x02U
#define FWU_IMAGE_TYPE_MODULE_1           0x03U
#define FWU_IMAGE_TYPE_MODULE_2           0x04U
#define FWU_IMAGE_TYPE_MODULE_3           0x05U
#define FWU_IMAGE_TYPE_MODULE_4           0x06U
#define FWU_IMAGE_TYPE_MODULE_5           0x07U
#define FWU_IMAGE_TYPE_MODULE_6           0x08U
#define FWU_IMAGE_TYPE_MODULE_7           0x09U
#define FWU_IMAGE_TYPE_BL                 0x1FU
#define FWU_IMAGE_TYPE_BL_DATA            0x20U


/******
 * End of modification
 * ********/
#ifdef __cplusplus
}
#endif
#endif /* TFM_FWU_BOOTLOADER_DEFS_H */
