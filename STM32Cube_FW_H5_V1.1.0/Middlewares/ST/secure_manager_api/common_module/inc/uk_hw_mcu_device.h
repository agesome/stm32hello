/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 * @file          uk_hw_mcu_device.h
 * @brief         uKernel API - Platform's MCU Device specifics.
 * @author        pierre-julien.bringer@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file contains the Platform's MCU Device specific part of the uKernel
 *  API Definitions.
 *
 * This file supports the following Platform MCU Device(s):
 *   - STMicroelectronics
 *    + STM32Hx family
 *     --- STM32H573xx
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target and a specific Platform.
 *
 * @warning This file is specific to a given uKernel Target and MCU Device.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target and on the selected MCU Device.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note This include file serves the same purpose as the uKernel API defined
 *  in the "uk.h" file while containing only the elements specific to the
 *  Platform MCU Device used.
 * This file is a child file of the "uk.h" include file and SHALL BE
 *  included only by it.
 *
 * @implementation To ease uKernel API definition and maintenance for several
 *  Platform MCU Devices, the definitions relative to the MCU Family and the
 *  definitions relative to MCU Core are each done in dedicated separate
 *  include files (which are included at the end of this file).
 *
 * @implementation This uKernel API file "uk_hw_mcu_device.h" is selected for
 *  inclusion by adding the following directory in the compiler include files
 *  configuration:
 *   "uk/include/hw/mcu/device/<vendor>/<family>/<device>"
 *  This directory, which is set only in the configuration of the compiler
 *  include files (no reference in source code), is built using the following
 *  directory definitions (all in lower case):
 *   - <target>: Target Name
 *     Eclipse Build Variable: BVukTARGET_NAME__lc
 *   - <vendor>: Device vendor shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_VENDOR__lc
 *   - <family>: Device family shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_FAMILY__lc
 *   - <device>: Device name
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_DEVICE__lc
 ******************************************************************************
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.              */
#if !defined(UK_HW_MCU_DEVICE_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_hw_mcu_device.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_HW_MCU_DEVICE_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_HW_MCU_DEVICE_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the Public API of this Code Module. */

/* Add inclusion of uKernel API only to help IDE parsing. */
#include "uk.h"

/* ######################################################################## */
/*            PLATFORM MCU DEVICE SPECIFIC - CONFIGURATION CHECK            */
/* ######################################################################## */
/* Platform MCU Device specific consistency and implementation checks. */

/* Enforce that this file supports the used MCU Device. */
#if defined(SukCONFIG_HW_MCU_DEVICE_STM_STM32H5XX_STM32H573)
#else
  #error "This include file supports only the following MCU Device: STM32H573"
#endif


/* ######################################################################## */
/*              UKERNEL API / MCU DEVICE SPECIFIC - C-CONSTANTS             */
/* ######################################################################## */
/* Hereafter are defined the C-Constants of the uKernel API whose definitions
 *  are depending of the selected Platform's MCU Device.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - PERIPHERAL IRQ                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining maximum value for the Peripheral IRQ Vector
 *  Identifier.
 *
 * Definition of the C-Constant for the maximum value for the Peripheral IRQ
 *  Vector Identifier supported by the given MCU family in the uKernel.
 *
 * @note This value is in general defined as the last identifier of Peripheral
 *  IRQ supported by the hardware interruption controller of the MCU family.
 *
 * @note This value is MCU Device specific.
 */
#define DukPIRQ_IDX_MAX    MukVAL_TYPED(TukPIRQ_MCU_IDX, 130)


/* ######################################################################## */
/*               UKERNEL API / PLATFORM'S MCU FAMILY SPECIFIC               */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel API definitions
 *  specific to the MCU Family to which belongs selected MCU Device.
 *
 * NOTE: To ease uKernel API definition and maintenance for several MCU
 *  Devices, these definitions are managed in a dedicated include file
 *  for each MCU Family.
 */
#include "uk_hw_mcu_family_stm_stm32h5xx.h"


/* ######################################################################## */
/*                 UKERNEL API / PLATFORM'S MCU CORE SPECIFIC               */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel API definitions
 *  specific to the MCU Core used in the selected MCU Device.
 *
 * NOTE: To ease uKernel API definition and maintenance for several MCU
 *  Devices, these definitions are managed in a dedicated include file
 *  for each MCU Core.
 */
#include "uk_hw_mcu_core_arm_cmx.h"



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_HW_MCU_DEVICE_H_INSIDE
#endif /* !defined(UK_HW_MCU_DEVICE_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */
