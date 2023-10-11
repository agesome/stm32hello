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
 * @file          uk_config_options_hw_mcu_family_stm_stm32h5xx.h
 * @brief         Configuration file containing Platform's MCU Family specific
 *                 uKernel Options.
 * @author        pierre-julien.bringer@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This configuration file contains the Platform's MCU Family specific uKernel
 *  Options exposed in the uKernel API for the uKernel Target used.
 * A uKernel Option is a constant value representing a uKernel internal
 *  parameter used during its compilation, and whose value is defining limits,
 *  constraints, or choices on the uKernel functionalities and behaviors.
 *
 * This file supports the following Platform MCU Family(ies):
 *   - STMicroelectronics
 *    + STM32Hx family
 *     --- STM32H5xx
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target.
 *
 * @robustness The uKernel Options are taken into account only during the
 *  compilation of the uKernel Target used. It enforces that internal checks
 *  relative to the uKernel parameters related to the uKernel Options are
 *  'hard-coded' in a uKernel Target code (this participates to minimize the
 *  attack surface of the uKernel).
 *
 * @implementation This file has a similar purpose and usage as the
 *  "uk_config_options.h" file, but it contains only the uKernel Options
 *  that may depend of the chosen Platform MCU Family (see "uk_config_options.h"
 *  file for more details on its contents and usage).
 *
 * @usage This configuration file SHALL ONLY BE sourced by a uKernel Option
 *  Platform's MCU Device specific file "uk_config_options_hw_mcu_device.h".
 *
 * @warning This file is specific to a given uKernel Target and MCU Family.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_CONFIG_OPTIONS_HW_MCU_FAMILY_STM_STM32H5XX_H)

/* Enforces that this file is included by 'uk_config_options_hw_mcu_device.h'
 *  file. */
#if !defined(UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H_INSIDE)
#error 'The "uk_config_options_hw_mcu_family_stm_stm32h5xx.h" include file shall be included only in the "uk_config_options_hw_mcu_device.h" file'
#endif /* !defined(UK_CONFIG_OPTIONS_HW_MCU_DEVICE_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONFIG_OPTIONS_HW_MCU_FAMILY_STM_STM32H5XX_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_OPTIONS_HW_MCU_FAMILY_STM_STM32H5XX_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the uKernel Configuration file. */

/* Add inclusion of parent include file of the Code Module only to help IDE
 *  parsing. */
#include "uk_config_options.h"


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
/*                   UKERNEL OPTIONS / MCU FAMILY SPECIFIC                  */
/* ######################################################################## */
/* Hereafter are listed the Platform's MCU Family specific uKernel Options
 *  (i.e. C-Constant values of uKernel configuration parameters depending of
 *  the MCU Family) that are part of the uKernel API of the uKernel Target
 *  used.
 * Each of the uKernel Option is defined as a C-Constant value. The definition
 *  is casting the value with the C-Type associated to the nature of the
 *  uKernel Options, excepted when defining a number of supported elements (as
 *  then the value may be used for defining arrays or tables, and typed values
 *  are not supported by C-Compiler in such definitions).
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A Platform specific uKernel Option <ooo> is defined by
 *  associating its corresponding label DukCONFIG_OPTION_HW_<ooo> to the wanted
 *  parameter value using the C-Preprocessor '#define'.
 * @implementation A specific file section below is reserved for the Platform
 *  specific uKernel Debug Options.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL OPTIONS / MCU FAMILY SPECIFIC - ADDRESS BLOCK            */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_MPU_ENABLED)

/**
 * @brief uKernel Option C-Constant defining the minimum size of an Address
 *  Block supported by the used MCU Family.
 *
 * Definition of the uKernel Option C-Constant for the minimum size of an
 *  Address Block supported by the used MCU Family.
 */
#define DukCONFIG_OPTION_HW_ADDRESSBLOCK_SIZE_MIN                             \
            MukVAL_TYPED(TukLENGTH32, 0x20UL)

/**
 * @brief uKernel Option C-Constant defining the maximum size of an Address
 *  Block supported by the used MCU Family.
 *
 * Definition of the uKernel Option C-Constant for the maximum size of an
 *  Address Block supported by the used MCU Family.
 */
#define DukCONFIG_OPTION_HW_ADDRESSBLOCK_SIZE_MAX                             \
            MukVAL_TYPED(TukLENGTH32, 0x40000000UL)

#endif /* !defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_MPU_ENABLED) */


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL OPTIONS / MCU FAMILY SPECIFIC - SHARED BUFFERS           */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_MPU_ENABLED)

/**
 * @brief uKernel Option C-Constant defining the minimum size of a Shared
 *  Buffer supported by the used MCU Family.
 *
 * Definition of the uKernel Option C-Constant for the minimum size of a
 *  Shared Buffer supported by the used MCU Family.
 *
 * Default value: 256.
 * Supported values: { 2^<n> }, with <n> in [5 ... 15].
 */
#define DukCONFIG_OPTION_HW_SHAREDBUFFER_SIZE_MIN                             \
            MukVAL_TYPED(TukLENGTH32, 0x100UL)

/**
 * @brief uKernel Option C-Constant defining the maximum size of a Shared
 *  Buffer supported by the used MCU Family.
 *
 * Definition of the uKernel Option C-Constant for the maximum size of a
 *  Shared Buffer supported by the used MCU Family.
 *
 * Default value: 32768.
 * Supported values: { 2^<n> }, with <n> in [5 ... 15].
 */
#define DukCONFIG_OPTION_HW_SHAREDBUFFER_SIZE_MAX                             \
            MukVAL_TYPED(TukLENGTH32, 0x8000UL)

#endif /* !defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_MPU_ENABLED) */


/* //////////////////////////////////////////////////////////////////////// */
/*  UKERNEL OPTIONS / MCU FAMILY SPECIFIC - SAU PERIPHERALS RANGE           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 *
 * @brief C-Macro defining the start address of the authorized address space
 *  for peripherals for the Non-Secure World.
 *
 * This C-Macro defines the start address of the authorized address space for
 *  peripherals for the Non-Secure world.
 *
 */
#define DukCONFIG_OPTION_HW_NSWORLD_PERIPHERALS_ADDRESS_START 0x40000000UL

/**
 *
 * @brief C-Macro defining the start address of the authorized address space
 *  for peripherals for the Non-Secure World.
 *
 * This C-Macro defines the start address of the authorized address space for
 *  peripherals for the Non-Secure world.
 *
 */
#define DukCONFIG_OPTION_HW_NSWORLD_PERIPHERALS_ADDRESS_ENDP1 0x50000000UL


/* //////////////////////////////////////////////////////////////////////// */
/*  UKERNEL OPTIONS / MCU FAMILY SPECIFIC - UKAPP DATA PERSISTENT BLOCK     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum size of a ukApp
 *  Data Persistent Block supported by the used MCU Family.
 *
 * Definition of the uKernel Option C-Constant for the maximum size of a
 * ukApp Data Persistent Block supported by the used MCU Family.
 *
 * Default value: 65536.
 * Supported values: { 2^<n> }, with <n> in [5 ... 16].
 */
#define DukCONFIG_OPTION_HW_UKAPP_DATA_PERSISTENT_BLOCK_SIZE_MAX              \
            MukVAL_TYPED(TukLENGTH32, 0X10000UL)



/* ######################################################################## */
/*              UKERNEL OPTIONS / MCU FAMILY SPECIFIC - DEBUG               */
/* ######################################################################## */
/* Hereafter are defined the Platform's MCU Family specific Debug uKernel
 *  Options (i.e. C-Constant values of uKernel configuration debug parameters
 *  depending of the MCU Family) that are part of the uKernel API of the
 *  uKernel Target used and of the debug functionalities offered by the
 *  uKernel.
 * These definitions are similar to the Platform's MCU Family specific uKernel
 *  Options above (and can also be used by the uKernel Core and ukApp
 *  implementations), but care has to be taken that they are NOT defined for
 *  a uKernel Target that is a Production Target.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A Platform specific uKernel Debug Option <ooo> is defined by
 *  associating its corresponding label DukCONFIG_OPTION_HW_DEBUG_<ooo> to the
 *  wanted parameter value using the C-Preprocessor '#define'.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 */

/* ROBUSTNESS: None of the uKernel Debug Options defined hereafter are
 *  supported if the uKernel compilation is aiming a Production Target. */
#if !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)


#endif /* !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* ######################################################################## */
/*                                 UNUSED                                   */
/* ######################################################################## */
/* The definitions hereafter allow to keep features that may be used in
 *  future developments of uKernel. */
#if 0


#endif /* 0 */


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_OPTIONS_HW_MCU_FAMILY_STM_STM32H5XX_H_INSIDE
#endif /* !defined(UK_CONFIG_OPTIONS_HW_MCU_FAMILY_STM_STM32H5XX_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */
