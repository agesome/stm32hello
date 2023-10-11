/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 */
/**************************************************************************//**
 * @file          uk_hw_mcu_family_stm_stm32h5xx.h
 * @brief         uKernel API - Platform MCU Family STM32Hx specifics.
 * @author        pierre-julien.bringer@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file contains the Platform's MCU Family specific part of the uKernel
 *  API for the selected MCU Device.
 *
 * This file supports the following Platform MCU Family(ies):
 *   - STMicroelectronics
 *    + STM32Hx family
 *     --- STM32H5xx
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target and a specific Platform.
 *
 * @warning This file is specific to a given uKernel Target and MCU Family.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target and on the selected MCU family.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note This include file serves the same purpose as the uKernel API defined
 *  in the "uk.h" file while containing only the elements for which there is
 *  some specificities relative to the Platform MCU Family it supports.
 *
 * @usage This file is a child file of the "uk_hw_mcu_device.h" include file
 *  and SHALL BE included only by it.
 ******************************************************************************
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.            */
#if !defined(UK_HW_MCU_FAMILY_STM_STM32H5XX_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by our parent file.                   */
#if !defined(UK_HW_MCU_DEVICE_H_INSIDE)
    #error 'The "uk_hw_mcu_family_stm_stm32h5xx.h" include file shall be included only in the "uk_hw_mcu_device.h" file'
#endif /* !defined(UK_HW_MCU_DEVICE_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_HW_MCU_FAMILY_STM_STM32H5XX_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_HW_MCU_FAMILY_STM_STM32H5XX_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the Public API of this Code Module. */

/* Add inclusion of uKernel API only to help IDE parsing. */
#include "uk.h"

/* ######################################################################## */
/*          PLATFORM'S MCU FAMILY SPECIFIC - CONFIGURATION CHECK            */
/* ######################################################################## */
/* Platform's MCU Family specific consistency and implementation checks. */

/* Enforce that this file supports the used MCU Family. */
#if defined(SukCONFIG_HW_MCU_FAMILY_STM_STM32H5XX)
#else
  #error "This include file supports only the following MCU Family(ies): STM32H5xx"
#endif

/* ######################################################################## */
/*                   UKERNEL API / MCU FAMILY - C-CONSTANTS                 */
/* ######################################################################## */
/* Hereafter are defined the C-Constants specific of the uKernel API whose
 *  definitions are depending of the selected Platform's MCU Family.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */

#if defined(SukCONFIG_FEATURE_MCU_DMA)

/**
 * @brief C-Constant defining the count of DMA Stream Engines in the used MCU
 *  Family.
 *
 * Definition of the C-Constant of the count of DMA Stream Engines in the
 *  hardware of used MCU Family.
 *
 * @implementation This value shall be retrieved from MCU device documentation.
 *
 * @implementation If more DMA Stream Engines than the maximum number of DMA
 *  Stream Instance supported by the uKernel (see
 *  DukCONSTRAINT_DMAS_INSTANCE_COUNT_MAX) are present,
 *  then some DMA Stream Engines can not be used.
 *
 * @usage If no DMA Stream Engine is present on the used MCU Family, then
 *  the uKernel Feature for DMA support shall be disabled (see
 *  SukCONFIG_FEATURE_MCU_DMA).
 *
 * Default value: /
 * Supported values: [1 ...
 *              DukCONSTRAINT_DMAS_INSTANCE_COUNT_MAX].
 */
#define DukDMAS_ENGINE_COUNT                                            \
            MukVAL_TYPED(TukCOUNT8, 16)

/**
 * @brief C-Constant defining the maximum size that can be transferred by a
 *  DMA Stream on the used MCU Family.
 *
 * Definition of the C-Constant of the maximum size that can be transferred by
 *  a DMA Stream on the used MCU Family.
 *
 * @implementation This value shall be retrieved from MCU device documentation.
 *
 * Default value: /
 * Supported values: [ >= 4 ]
 */
#define DukDMAS_ENGINE_TRANSFER_SIZE_MAX                                \
            MukVAL_TYPED(TukCOUNT32, 32767)

#endif /* defined(SukCONFIG_FEATURE_MCU_DMA) */

/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL CORE OPTIONS / ADDRESS Translations                  */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_ENABLED)

/**
 * @brief C-Function providing a Non-secure version of the RAM address,
 *  regardless of the input type.
 *
 * This C-Function provides a Non-secure version of the RAM address. This
 *  works both for Non-secure (0x2.....) and Secure (0x3......) input
 *  addresses.
 *
 * @param[in] (TukADDRESS32)x Input address, either Secure or Non-Secure,
 *  always in RAM.
 *
 * @return (TukADDRESS32) Corresponding Non-Secure RAM address.
 *
 * @usage This function doesn't verify its inputs.
 */
static inline TukADDRESS32 CAukVAR_UNUSED_MAYBE RAMNS(TukADDRESS32 x) {
    return x & 0xEFFFFFFFUL;
}

/**
 * @brief C-Function providing a Secure version of the RAM address,
 *  regardless of the input type.
 *
 * This C-Function provides a Secure version of the RAM address. This
 *  works both for Non-secure (0x2.....) and Secure (0x3......) input
 *  addresses.
 *
 * @param[in] (TukADDRESS32)x Input address, either Secure or Non-Secure,
 *  always in RAM.
 *
 * @return (TukADDRESS32) Corresponding Secure RAM address.
 *
 * @usage This function doesn't verify its inputs.
 */
static inline TukADDRESS32 CAukVAR_UNUSED_MAYBE RAMS(TukADDRESS32 x) {
    return x | 0x10000000UL;
}

/**
 * @brief C-Function providing a Non-secure version of the ROM address,
 *  regardless of the input type.
 *
 * This C-Function provides a Non-secure version of the ROM address. This
 *  works both for Non-secure (0x2.....) and Secure (0x3......) input
 *  addresses.
 *
 * @param[in] (TukADDRESS32)x Input address, either Secure or Non-Secure,
 *  always in ROM.
 *
 * @return (TukADDRESS32) Corresponding Non-Secure ROM address.
 *
 * @usage This function doesn't verify its inputs.
 */
static inline TukADDRESS32 CAukVAR_UNUSED_MAYBE ROMNS(TukADDRESS32 x) {
    return x & 0xFBFFFFFFUL;
}

/**
 * @brief C-Function providing a Secure version of the ROM address,
 *  regardless of the input type.
 *
 * This C-Function provides a Secure version of the ROM address. This
 *  works both for Non-secure (0x2.....) and Secure (0x3......) input
 *  addresses.
 *
 * @param[in] (TukADDRESS32)x Input address, either Secure or Non-Secure,
 *  always in ROM.
 *
 * @return (TukADDRESS32) Corresponding Secure ROM address.
 *
 * @usage This function doesn't verify its inputs.
 */
static inline TukADDRESS32 CAukVAR_UNUSED_MAYBE ROMS(TukADDRESS32 x) {
    return x | 0x04000000UL;
}

#endif /* defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_ENABLED)*/

/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_HW_MCU_FAMILY_STM_STM32H5XX_H_INSIDE
#endif /* !defined(UK_HW_MCU_FAMILY_STM_STM32H5XX_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */