/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "region_defs.h"
#include "mcuboot_config/mcuboot_config.h"

#define _HEX(n) 0x##n
#define HEX(n)  _HEX(n)

/* Enumeration that is used by the assemble.py and imgtool\main.py scripts
 * for correct binary generation when nested macros are used
 */

enum image_attributes
{
  RE_FLASH_AREA_BL2_OFFSET = FLASH_AREA_BL2_OFFSET,
  RE_FLASH_AREA_BL2_SIZE = FLASH_AREA_BL2_SIZE,
  RE_FLASH_AREA_SCRATCH_OFFSET = FLASH_AREA_SCRATCH_OFFSET,
  RE_FLASH_AREA_SCRATCH_SIZE = FLASH_AREA_SCRATCH_SIZE,
/* area for preparing images */
  RE_IMAGE_FLASH_SECURE_IMAGE_SIZE = (SECURE_IMAGE_MAX_SIZE),
  RE_IMAGE_NON_SECURE_IMAGE_SIZE = (NON_SECURE_IMAGE_MAX_SIZE),
#if MCUBOOT_APP_IMAGE_NUMBER == 2
  RE_IMAGE_FLASH_NON_SECURE_IMAGE_SIZE = (NON_SECURE_IMAGE_MAX_SIZE),
  RE_CODE_IMAGE_ASSEMBLY = (0x0),
#else
  RE_IMAGE_FLASH_NON_SECURE_IMAGE_SIZE = (NON_SECURE_IMAGE_MAX_SIZE+SECURE_IMAGE_MAX_SIZE),
  RE_CODE_IMAGE_ASSEMBLY = (0x1),
#endif
  RE_ADDRESS_SECURE_START = S_CODE_START - BL2_HEADER_SIZE,
  RE_ADDRESS_NON_SECURE_START = NS_CODE_START - BL2_HEADER_SIZE,
/* area for flashing images */
  RE_IMAGE_FLASH_ADDRESS_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_IMAGE_FLASH_ADDRESS_SECURE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET+FLASH_AREA_0_SIZE-0x10),
  RE_APP_IMAGE_NUMBER = (HEX(MCUBOOT_APP_IMAGE_NUMBER)),
  RE_EXTERNAL_FLASH_ENABLE = (0x0),
#if (MCUBOOT_APP_IMAGE_NUMBER == 2)
  RE_CODE_START_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET+FLASH_AREA_1_SIZE-0x10),
  /* area for updates slot address */
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET),
  RE_IMAGE_FLASH_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET+FLASH_AREA_2_SIZE-0x10),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_3_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_3_OFFSET+FLASH_AREA_3_SIZE-0x10),
  RE_PRIMARY_ONLY = (0x0),
#else
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_IMAGE_FLASH_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET+FLASH_AREA_0_SIZE-0x10),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_1_OFFSET+FLASH_AREA_1_SIZE-0x10),
  RE_PRIMARY_ONLY = (0x1),
#endif /* MCUBOOT_PRIMARY_ONLY */
#else /*(MCUBOOT_APP_IMAGE_NUMBER == 1) */
  RE_CODE_START_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE_MAGIC_INSTALL_REQ = (0x0),
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET),
  RE_IMAGE_FLASH_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_2_OFFSET+FLASH_AREA_2_SIZE-0x10),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_PRIMARY_ONLY = (0x0),
#else
  RE_IMAGE_FLASH_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET),
  RE_IMAGE_FLASH_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_0_OFFSET+FLASH_AREA_0_SIZE-0x10),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_PRIMARY_ONLY = (0x1),
#endif /* MCUBOOT_PRIMARY_ONLY */
#endif /* (MCUBOOT_APP_IMAGE_NUMBER == 2) */
  RE_S_DATA_IMAGE_NUMBER = (HEX(MCUBOOT_S_DATA_IMAGE_NUMBER)),
#if (MCUBOOT_S_DATA_IMAGE_NUMBER == 1)
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_4_OFFSET),
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_4_OFFSET+FLASH_AREA_4_SIZE-0x10),
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_6_OFFSET),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_6_OFFSET+FLASH_AREA_6_SIZE-0x10),
#else
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_4_OFFSET),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_4_OFFSET+FLASH_AREA_4_SIZE-0x10),
#endif /* MCUBOOT_PRIMARY_ONLY */
  RE_IMAGE_FLASH_SECURE_DATA_IMAGE_SIZE = (FLASH_S_DATA_PARTITION_SIZE),
#else
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_SECURE_DATA_IMAGE_SIZE = (0x0),
#endif /* (MCUBOOT_S_DATA_IMAGE_NUMBER == 1) */
  RE_NS_DATA_IMAGE_NUMBER = (HEX(MCUBOOT_NS_DATA_IMAGE_NUMBER)),
#if (MCUBOOT_NS_DATA_IMAGE_NUMBER == 1)
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE = (FLASH_BASE_ADDRESS+FLASH_AREA_5_OFFSET),
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_5_OFFSET+FLASH_AREA_5_SIZE-0x10),
#if !defined(MCUBOOT_PRIMARY_ONLY)
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_7_OFFSET),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_7_OFFSET+FLASH_AREA_7_SIZE-0x10),
#else
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE = (FLASH_BASE_ADDRESS+FLASH_AREA_5_OFFSET),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (FLASH_BASE_ADDRESS+FLASH_AREA_5_OFFSET+FLASH_AREA_5_SIZE-0x10),
#endif /* MCUBOOT_PRIMARY_ONLY */
  RE_IMAGE_FLASH_NON_SECURE_DATA_IMAGE_SIZE = (FLASH_NS_DATA_PARTITION_SIZE),
#else
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_NON_SECURE_DATA_IMAGE_SIZE = (0x0),
#endif /* (MCUBOOT_NS_DATA_IMAGE_NUMBER == 1) */
  RE_BL2_BOOT_ADDRESS = (BL2_BOOT_VTOR_ADDR),
  /* area for programming hardening on page */
#if (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE) < (FLASH_B_SIZE)
  /* config without secure on bank 2 */
  RE_BL2_SEC1_END = (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE-0x1),
  RE_BL2_SEC2_START = (FLASH_B_SIZE-0x1),
  RE_BL2_SEC2_END = (0x0),
#else
  /* config with secure on bank 2 */
  RE_BL2_SEC1_END = (FLASH_B_SIZE-0x1),
  RE_BL2_SEC2_START = 0x0,
  RE_BL2_SEC2_END = (FLASH_AREA_0_OFFSET+SECURE_IMAGE_MAX_SIZE-FLASH_B_SIZE-0x1)
#endif
  RE_BL2_WRP_START = (FLASH_AREA_BL2_OFFSET),

  RE_BL2_HDP_START = 0x0,
  RE_BL2_HDP_END = (FLASH_AREA_BL2_OFFSET+FLASH_AREA_BL2_SIZE+FLASH_AREA_SCRATCH_SIZE-0x1),
  RE_BL2_WRP_END = (FLASH_AREA_BL2_OFFSET+FLASH_AREA_BL2_SIZE-0x1),
  /* area for updates slot address */
  RE_AREA_0_OFFSET = FLASH_AREA_0_OFFSET,
  RE_AREA_0_SIZE = FLASH_AREA_0_SIZE,
  RE_AREA_1_OFFSET = FLASH_AREA_1_OFFSET,
  RE_AREA_1_SIZE = FLASH_AREA_1_SIZE,
  RE_AREA_2_OFFSET = FLASH_AREA_2_OFFSET,
  RE_AREA_2_SIZE = FLASH_AREA_2_SIZE,
  RE_AREA_3_OFFSET = FLASH_AREA_3_OFFSET,
  RE_AREA_3_SIZE = FLASH_AREA_3_SIZE,
  RE_AREA_4_OFFSET = FLASH_AREA_4_OFFSET,
  RE_AREA_4_SIZE = FLASH_AREA_4_SIZE,
  RE_AREA_5_OFFSET = FLASH_AREA_5_OFFSET,
  RE_AREA_5_SIZE = FLASH_AREA_5_SIZE,
  RE_AREA_6_OFFSET = FLASH_AREA_6_OFFSET,
  RE_AREA_6_SIZE = FLASH_AREA_6_SIZE,
  RE_AREA_7_OFFSET = FLASH_AREA_7_OFFSET,
  RE_AREA_7_SIZE = FLASH_AREA_7_SIZE,
  RE_S_NS_PARTITION_SIZE = FLASH_PARTITION_SIZE,
  RE_FLASH_B_SIZE = FLASH_B_SIZE,

  RE_CRYPTO_SCHEME = CRYPTO_SCHEME,
#if defined(MCUBOOT_ENC_IMAGES)
  RE_ENCRYPTION = (0x1),
#else
  RE_ENCRYPTION = (0x0),
#endif
#if defined(MCUBOOT_OVERWRITE_ONLY)
  RE_OVER_WRITE = (0x1),
  RE_TRAILER_MAX_SIZE = (0x40),
#else
  RE_OVER_WRITE = (0x0),
  RE_TRAILER_MAX_SIZE = (0x1E00),
#endif
  RE_OEMUROT_ENABLE = (0x0),
  RE_FLASH_PAGE_NBR = (0x7F)
};
