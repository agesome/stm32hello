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
 * @file          uk_config_hw_mcu_device.h
 * @brief         uKernel API - Platform's MCU Device specific configuration.
 * @author        pierre-julien.bringer@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file contains the Platform's MCU Device specific part of the uKernel
 *  API.
 * It contains the root definitions for the MCU Device used. These root
 *  definitions are then used in the other uKernel API files to derive other
 *  definitions.
 *
 * This file supports the following Platform MCU Device(s):
 *   - STMicroelectronics
 *    + STM32H5 family
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
 * @note This file is a child file of the "uk_config.h" include file and
 *  SHALL BE included only by it.
 *
 * @implementation To ease uKernel API definition and maintenance for several
 *  Platform MCU Devices, the definitions relative to the MCU Family and the
 *  definitions relative to MCU Core are each done in dedicated separate
 *  include files (which are included at the end of this file).
 *
 * @implementation This uKernel API file "uk_config_hw_mcu_device.h" is
 *  selected for inclusion by adding the following directory in the compiler
 *  include files configuration:
 *   "ukernel_api/target/<target>/uk/include/config/hw/mcu/device/<vendor>/<family>/<device>"
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
/* Verify that this include file has not been already processed.            */
#if !defined(UK_CONFIG_HW_MCU_DEVICE_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk_config.h" file.                */
#if !defined(UK_CONFIG_H_INSIDE)
    #error 'The "uk_config_hw_mcu_device.h" include file shall be included only in the "uk_config.h" file'
#endif /* !defined(UK_CONFIG_H_INSIDE) */

/*__________________________________________________________________________*/
/* Enforces that the 'uk_config_features.h' file has already been included. */
#if !defined(UK_CONFIG_FEATURES_H)
 #error 'The "uk_config_hw_mcu_device.h" include file shall be included only after the "uk_config_features.h" file'
#endif /* !defined(UK_CONFIG_FEATURES_H) */


/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_CONFIG_HW_MCU_DEVICE_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_HW_MCU_DEVICE_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the uKernel Configuration file.       */


/* ######################################################################## */
/*          PLATFORM MCU DEVICE SPECIFIC - DEVICE VENDOR DEFINITIONS        */
/* ######################################################################## */
/* Hereafter are defined the C-Preprocessor definitions used in the vendor
 *  definitions needed for supporting the chosen MCU Device.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @usage These C-Preprocessor definitions SHOULD NOT be used by ukApp
 *  code in order to keep portability (use uKernel C-Constants definitions
 *  instead).
 */

#if !defined(STM32H573xx)
    #define STM32H573xx
#endif /* !defined(STM32H573xx) */

#if !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)
    #if !defined(DEBUG)
        #define DEBUG
    #endif /* !defined(DEBUG) */
#endif /* !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */

/* Source the MCU Device vendor definitions include files.
 * NOTE: The C-Preprocessor definitions defined above are needed for
 *  processing properly these include files.
 * NOTE: The following definitions shall be done:
 *  - STM32H573xx
 *  - DEBUG
 *  - USE_FULL_ASSERT
 *  - USE_HAL_DRIVER */
MukBEGIN_EXTERNAL_CODE
#include "stm32h5xx.h"
MukEND_EXTERNAL_CODE

/* Let's do a consistency check with vendor supplied macros. Most compilers
 * provide this, and for those that don't, CMSIS fills the gap. */
#if !defined(__ARM_ARCH_8M_MAIN__)
    #error "Inconsistent target architecture: this device expects an ARMv8-M profile."
#endif


/* ######################################################################## */
/*      UKERNEL API / MCU DEVICE SPECIFIC - C-PREPROCESSOR STATEMENTS       */
/* ######################################################################## */
/* Hereafter are defined the C-Preprocessor statements of the uKernel API
 *  whose definitions are depending of the selected Platform's MCU Device.
 *
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @usage These uKernel Configuration C-Preprocessor Statements are used for:
 *  - During the build of a uKernel Release, to check that the chosen uKernel
 *   Features and Options values are pertinent and consistent with the selected
 *   MCU Device and Platform capabilities (e.g. some Device may not support
 *   some features, or only some restricted range for clock configuration).
 *  - Selecting the proper uKernel implementation when building a uKernel
 *   Release.
 *  - Selecting the specific low level code HAL (Hardware Abstraction Layer)
 *   associated to the selected MCU Device when compiling ukApp code.
 *  - The ukApp code to update their implementation in function of the
 *   selected Platform's MCU Device onto which they may be executed.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*             C-PREPROCESSOR STATEMENTS - MCU DEVICE DEFINITION            */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Preprocessor Statement for the name of the
 *  MCU Vendor Family.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for
 *  the name of the MCU Vendor Family of the selected MCU Device.
 */
#define SukCONFIG_HW_MCU_FAMILY_STM_STM32H5XX

/**
 * @brief uKernel Configuration C-Preprocessor Statement for the name of the
 *  MCU Vendor Sub-Family.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for
 *  the name of the MCU Vendor Sub-Family of the selected MCU Device.
 *
 * @implementation This statement SHALL BE composed of the uKernel
 *  Configuration C-Preprocessor Statement for the name of the MCU Vendor
 *  Family, to which is added a suffix for the Sub-Family.
 */
#define SukCONFIG_HW_MCU_FAMILY_STM_STM32H5XX_STM32H5XX

/**
 * @brief uKernel Configuration C-Preprocessor Statement for the name of the
 *  MCU Device.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for
 *  the name of the MCU Device.
 *
 * @robustness During uKernel Initialization checks are performed to enforce
 *  that the MCU device defined by this uKernel Configuration C-Preprocessor
 *  Statement is corresponding to the MCU Device on which is executed the
 *  uKernel. If checks fail, it is a uKernel Initialization Fatal Error.
 *
 * @implementation This statement SHALL BE composed of the uKernel
 *  Configuration C-Preprocessor Statement for the name of the MCU Vendor
 *  Family, to which is added a suffix for the precise MCU Device name.
 */
#define SukCONFIG_HW_MCU_DEVICE_STM_STM32H5XX_STM32H573


/* //////////////////////////////////////////////////////////////////////// */
/*              C-PREPROCESSOR STATEMENTS - MCU CORE DEFINITION             */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if MCU CPU
 *  Core is an ARM Cortex-M.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if
 *  MCU CPU Core is an ARM Cortex-M on the selected MCU Device.
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining which Type
 *  of ARM Cortex-M is the MCU CPU Core.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for which
 *  Type of ARM Cortex-M is the MCU CPU Core.
 *
 * @note the following C-Preprocessor Statement are also supported by this
 *  uKernel implementation:
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM3
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM4
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM7
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM33
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM33


/**
 * @brief uKernel Configuration C-Preprocessor Statement defining which
 *  Architecture version of ARM Cortex-M is the MCU CPU Core.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for which
 *  Architecture version of ARM Cortex-M is the MCU CPU Core.
 *
 * @note the following C-Preprocessor Statement are also supported by this
 *  uKernel implementation:
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V7M
 *  - SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V8M
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V8M



/* //////////////////////////////////////////////////////////////////////// */
/*                C-PREPROCESSOR STATEMENTS - MCU CORE SUPPORT              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if the
 *  MCU Core used support non-aligned 32-bit accesses.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if the
 *  MCU Core used support non-aligned 32-bit accesses.
 *
 * A non-aligned 32-bit access consists to perform an access (read or write) to
 *  a 32-bit value at an address which is not a multiple of 4 (non aligned on
 *  32-bit).
 *
 * @usage This C-Preprocessor Statement allows to select proper uKernel
 *  implementation when compiling a uKernel Release.
 */
#define SukCONFIG_HW_MCU_CORE_32BIT_ACCESS_UNALIGNED_SUPPORTED

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if MCU ARM
 *  TrustZone is supported.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if
 *  MCU ARM TrustZone is supported on the selected MCU Device.
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_SUPPORTED

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if MCU ARM
 *  TrustZone is enabled.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if
 *  MCU ARM TrustZone is enabled on the selected MCU Device.
 *
 * @usage This C-Preprocessor Statement SHALL NOT be defined if
 *  SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_SUPPORTED is not defined.
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_ENABLED

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if the
 *  MPU internal to the MCU ARM Core is used.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if
 *  the MPU internal to the MCU ARM Core is used on the selected MCU Device.
 *
 * @usage This C-Preprocessor Statement allows to select proper uKernel
 *  implementation when compiling a uKernel Release.
 */
#define SukCONFIG_HW_MCU_CORE_ARM_CMX_MPU_ENABLED


/* //////////////////////////////////////////////////////////////////////// */
/*       C-PREPROCESSOR STATEMENTS - MCU INTERNAL PERIPHERAL SUPPORT        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if the
 *  MCU has an internal TRNG.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if the
 *  MCU has an internal TRNG (True Random Generator).
 *
 * @usage This C-Preprocessor Statement allows to select proper uKernel
 *  implementation and supported uKernel functionalities when compiling a
 *  uKernel Release.
 */
#define SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED


/**
 * @brief uKernel Configuration C-Preprocessor Statement defining if the
 *  MCU has an internal TRNG compliant with AIS31.
 *
 * Definition of the uKernel Configuration C-Preprocessor Statement for if the
 *  MCU has an internal TRNG (True Random Generator) compliant with AIS31.
 *
 * @implementation If this uKernel Configuration C-Preprocessor Statement is
 *  defined, then SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED SHALL BE also
 *  defined.
 *
 * @usage This C-Preprocessor Statement allows to select proper uKernel
 *  implementation and supported uKernel functionalities when compiling a
 *  uKernel Release.
 */
#define SukCONFIG_HW_MCU_PERIPHERALS_TRNG_AIS31_SUPPORTED


/* ######################################################################## */
/*              UKERNEL API / MCU DEVICE SPECIFIC - C-CONSTANTS             */
/* ######################################################################## */
/* Hereafter are defined the C-Constants of the uKernel API whose definitions
 *  are depending of the selected Platform's MCU Device.
 *
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Release to be taken into account.
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - MCU DEVICE DEFINITION                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Constant defining the MCU device hardware
 *  revision used on the selected Platform.
 *
 * Definition of the uKernel Configuration C-Constant of the MCU device
 *  hardware revision used on the selected Platform.
 *
 * @robustness During uKernel Initialization checks are performed to enforce
 *  that the MCU device defined by this uKernel Configuration is effectively
 *  the one present on the Platform. If checks fail, it is a uKernel
 *  Initialization Fatal Error.
 */
#define DukCONFIG_HW_MCU_DEVICE_REVISION      MukVAL_TYPED(TukUINT32, 1UL)


/**
 * @brief uKernel Configuration C-Constant defining the 128-bit Identifier
 *  for an MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the 128-bit Identifier
 *  for an MCU Device.
 * This Identifier allows to reference the Manufacturer, Family, Reference in
 *  the family, and Revision of the MCU used on the Platform (see
 *  TukMCU_ID_bv).
 *
 * @robustness During uKernel Initialization checks are performed to enforce
 *  that this MCU Device Identifier is corresponding to the MCU Device on
 *  which is executed the uKernel. If checks fail, it is a uKernel
 *  Initialization Fatal Error.
 *
 * @usage During uKernel Initialization checks are performed to enforce
 *  that the ukApps part of the ukApps Bundle have been compiled with this
 *  same MCU Device Identifier. If checks fail, the ukApp Descriptor is
 *  declared invalid and ignored. This failure may also, in function of
 *  uKernel Security Policy configured, be a uKernel Initialization Fatal
 *  Error.
 *
 * @usage This identifier is returned when getting Platform Attribute with
 *  tag DukPLATFORM_ATTRIBUTE_TAG_MCU_ID.
 */
#define DukCONFIG_HW_MCU_DEVICE_IDENTIFIER128                                 \
      {                                                                       \
        (('S' << 24) | ('T' << 16) | ('M' << 8) | (0U  << 0)),                \
        (('3' << 24) | ('2' << 16) | ('H' << 8) | (0U  << 0)),                \
        (('5' << 24) | ('7' << 16) | ('3' << 8) | (0U  << 0)),                \
        1UL                                                                   \
      }



/**
 * @brief uKernel Configuration C-Constant defining the 64-bit Identifier for
 *  the CPU Core in an MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the 64-bit Identifier
 *  for the CPU Core in an MCU Device.
 * This Identifier allows to reference the Manufacturer, Architecture type,
 *  and Revision of the CPU Core inside the MCU used in the Platform (see
 *  TukCPU_CORE_ID).
 *
 * @robustness During uKernel Initialization checks are performed to enforce
 *  that this CPU Core Identifier is corresponding to the CPU Core on which
 *  is executed the uKernel. If checks fail, it is a uKernel Initialization
 *  Fatal Error.
 *
 * @usage This identifier is returned when getting Platform Attribute with
 *  tag DukPLATFORM_ATTRIBUTE_TAG_PLATFORM_ID.
 */
#define DukCONFIG_HW_MCU_CPU_CORE_IDENTIFIER64   MukVAL_TYPED(                \
      TukCPU_CORE_ID,                                                         \
      ((((uint8_t)'A' << 24) |                                                \
        ((uint8_t)'R' << 16) |                                                \
        ((uint8_t)'M' <<  8) |                                                \
                (0ULL <<  0)) << 32)                                        | \
                                                                              \
      (0x41U    << SCB_CPUID_IMPLEMENTER_Pos)  /* Implementer : ARM */      | \
      (0x0U     << SCB_CPUID_VARIANT_Pos)      /* Variant     : 0 */        | \
      (0xFU     << SCB_CPUID_ARCHITECTURE_Pos) /* Architecture: ARM v8-M */ | \
                                               /* with Main Extension    */   \
      (0xD21U   << SCB_CPUID_PARTNO_Pos)       /* Part        : Cortex-M33*/| \
      (0x4U     << SCB_CPUID_REVISION_Pos)     /* Revision    : 4 */          \
                                                             )


/**
 * @brief uKernel Configuration C-Constant defining the 128-bit Identifier
 *  for a Platform.
 *
 * Definition of the uKernel Configuration C-Constant of the 128-bit Identifier
 *  for a Platform.
 * This Identifier allows to reference the Designer, Type, Reference for given
 *  Type, and Options for a Platform (see TukPLATFORM_ID_bv).
 *
 * @usage This identifier is returned when getting Platform Attribute with
 *  tag DukPLATFORM_ATTRIBUTE_TAG_PLATFORM_ID.
 */
#define DukCONFIG_HW_PLATFORM_IDENTIFIER128                                   \
      {                                                                       \
        (('S' << 24) | ('T' << 16) | ('M' << 8) | (0U  << 0)),                \
        (('N' << 24) | ('U' << 16) | ('C' << 8) | (0U  << 0)),                \
        (('H' << 24) | ('5' << 16) | ('6' << 8) | ('3' << 0)),                \
        (('R' << 24) | ('E' << 16) | (' ' << 8) | (0U  << 0)),                \
      }



/* //////////////////////////////////////////////////////////////////////// */
/*                      C-CONSTANTS - MCU DEVICE FLASH                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Configuration C-Constant defining the MCU Flash Access Block
 *  Size for the MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the MCU Flash Access
 *  (read / write) Block Size for the MCU Device.
 *
 * The MCU Flash Access Block Size corresponds to the size in bytes of each
 *  block that can be read or written per MCU FLash Operation. The following
 *  constraints apply upon an access (read / write) to the MCU Flash:
 *  - The start address of the access shall be aligned on this size.
 *  - The count of bytes accessed shall be a multiple of this size.
 *  - The access shall not cross a Flash Sector boundary.
 *
 * Default value: /.
 * Supported values: { 2^<n> }, with <n> in [0 ... 16].
 *
 * @note: See ST RM0481 7.2
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_ACCESS_BLOCK_SIZE                       \
                                    MukVAL_TYPED(TukLENGTH32, 16UL)


/**
 * @brief uKernel Configuration C-Constant defining the Maximal Size upon
 *  an MCU Flash Write for the MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the Maximal Size upon
 *  an MCU Flash Write for the MCU Device.
 *
 * @implementation The MCU Flash Write Maximal Size is used by the uKernel to
 *  limit the maximal time required for performing the MCU Flash Write
 *  Operation.
 *
 * Default value: /.
 * Supported values: { DukCONFIG_HW_MCU_DEVICE_FLASH_ACCESS_BLOCK_SIZE * <n> },
 *  with <n> in [1 ... 255].
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_WRITE_SIZE_MAX                          \
                                    MukVAL_TYPED(TukLENGTH32, 32UL)



/**
 * @brief uKernel Configuration C-Constant defining the maximal count of
 *  different Flash Sector Sizes in a Flash Bank of the internal Flash memory
 *  of the MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the maximal count of
 *  different Flash Sector Sizes in a Flash Bank of the internal Flash memory
 *  of the MCU Device.
 *
 * @usage This count is used for the list of Flash Banks definitions: it
 *  corresponds to the size of the C-Array in the field <SectorSizeList>.
 *
 * Default value: 1.
 * Supported values: [1 ... 8].
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_SECTOR_SIZE_PER_BANK_COUNT_MAX          \
                                    MukVAL_TYPED(TukCOUNT8, 1U)


/**
 * @brief uKernel Configuration C-Constant defining the count of Flash Banks
 *  in internal MCU Flash memory of the MCU Device.
 *
 * Definition of the uKernel Configuration C-Constant of the count of Flash
 *  Banks in internal MCU Flash memory of the MCU Device.
 *
 * @usage This count SHALL correspond to the number of entries in the list
 *  DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_LIST.
 *
 * @usage If no erase or writing in the internal MCU Flash memory is required,
 *  then this count SHALL BE set to null(0).
 *
 * Default value: /.
 * Supported values: [0 ... 16].
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_COUNT                              \
                                    MukVAL_TYPED(TukCOUNT8, 2U)


/**
 * @brief uKernel Configuration constant C-Array defining the list of Flash
 *  Banks in internal MCU Flash memory of the MCU Device.
 *
 * Definition of the uKernel Configuration constant C-Array containing the list
 *  of Flash Banks in internal MCU Flash memory of the MCU Device.
 *
 * A Flash Bank corresponds to a block of the Flash memory that can be erased
 *  and programmed independently and without affecting the other Flash Banks
 *  (when a given Flash Bank is erased or programmed, it does not affect the
 *  MCU accesses (code fetch, reading data) of the other Flash Banks).
 * A Flash Bank is composed of contiguous Flash Sectors. A Flash Sector is the
 *  smallest block that can be erased (erasing is mandatory before writing
 *  for Flash technology). Different sets of size of Flash Sectors may be
 *  present in a same Flash Banks (see MCU Device documentation).
 *
 * Each entry in the C-Array contains the following fields:
 *  - (TukADDRESS32)BankAddressStart: Start address of the Flash Bank.
 *  - SectorList[DukCONFIG_HW_MCU_DEVICE_FLASH_SECTOR_SIZE_PER_BANK_COUNT_MAX]:
 *   C-Array containing the list of Flash Sectors set of same length composing
 *   the Flash Bank:
 *   + (TukCOUNT16)SectorCount16: Count of Flash Sectors in the set.
 *   + (TukLENGTH32)SectorLength32: 32-bit Length of the Flash Sectors in the
 *     set.
 *
 * @robustness The number of entries in this list is checked to be equal to
 *  DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_COUNT.
 *
 * @implementation In case of invalid configuration provided for a Flash Banks,
 *  the uKernel Initialization will fail with Fatal Error.
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_LIST {                             \
        /* #01: [0x0C000000 ... 0x0C0FFFFF]  */     {                         \
        /*  - BankAddressStart   */     (TukADDRESS32)0x0C000000UL,           \
        /*  - SectorList[]       */     {                                     \
        /*    -- SectorCount16   */          {  (TukCOUNT16)  128,            \
        /*    -- SectorLength32  */             (TukLENGTH32) 0x00002000UL  },\
                                        }                                     \
                                                    },                        \
        /* #02: [0x0C100000 ... 0x0C1FFFFF]  */     {                         \
        /*  - BankAddressStart   */     (TukADDRESS32)0x0C100000UL,           \
        /*  - SectorList[]       */     {                                     \
        /*    -- SectorCount16   */          {  (TukCOUNT16)  128,            \
        /*    -- SectorLength32  */             (TukLENGTH32) 0x00002000UL  },\
                                        }                                     \
                                                    },                        \
                                                }


/**
 * @brief uKernel Configuration C-Constant defining the maximum duration time
 *  for an MCU Flash Operation Erase Sector.
 *
 * Definition of the uKernel Configuration C-Constant for the maximum duration
 *  time for an MCU Flash Operation Erase Sector in microseconds(us) performed
 *  by the MCU Flash Controller.
 *
 * @robustness This maximum duration time is used to prevent that an MCU Flash
 *  Controller failure lead to infinite waiting and to allow uKernel to take
 *  appropriate actions to manage this hardware error (reset the MCU Flash
 *  Controller, ...). A value of 10us should be added as error margin.
 *
 * @implementation This C-Constant is MCU Device dependent and SHALL BE
 *  retrieved from the MCU Device documentation (maximum value indicated in
 *  the documentation shall be taken).
 *
 * @usage If this duration is exceeded, then the MCU Flash Operation is
 *  considered as failed.
 *
 * @note: This value is from an e-mail by ST. It needs confirmation.
 *
 * Default value: /.
 * Supported values: >= 10.
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_OPERATION_ERASE_SECTOR_DURATION_MAX_us  \
                            MukVAL_TYPED(TukTIME32_us, 3000 + 10)


/**
 * @brief uKernel Configuration C-Constant defining the maximum duration time
 *  for an MCU Flash Operation Write Unit.
 *
 * Definition of the uKernel Configuration C-Constant for the maximum duration
 *  time for an MCU Flash Operation Write Unit in microseconds(us) performed by
 *  the MCU Flash Controller.
 *
 * @robustness This maximum duration time is used to prevent that an MCU Flash
 *  Controller failure lead to infinite waiting and to allow uKernel to take
 *  appropriate actions to manage this hardware error (reset the MCU Flash
 *  Controller, ...). A value of 10us should be added as error margin.
 *
 * @implementation This C-Constant is MCU Device dependent and SHALL BE
 *  retrieved from the MCU Device documentation (maximum value indicated in
 *  the documentation shall be taken).
 *
 * @usage If this duration is exceeded, then the MCU Flash Operation is
 *  considered as failed.
 *
 * @note: I don't know.
 *
 * Default value: /.
 * Supported values: >= 10.
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_OPERATION_WRITE_UNIT_DURATION_MAX_us    \
                            MukVAL_TYPED(TukTIME32_us, 200 + 10)


/**
 * @brief uKernel Configuration C-Constant defining the maximum duration time
 *  for a Flash Operation Check With Margin
 *
 * Definition of the uKernel Configuration C-Constant for the maximum duration
 *  time for an MCU Flash Operation Check With Margin in microseconds(us)
 *  performed by the MCU Flash Controller.
 *
 * @robustness This maximum duration time is used to prevent that an MCU Flash
 *  Controller failure lead to infinite waiting and to allow uKernel to take
 *  appropriate actions to manage this hardware error (reset the MCU Flash
 *  Controller, ...). A value of 10us should be added as error margin.
 *
 * @implementation This C-Constant is MCU Device dependent and SHALL BE
 *  retrieved from the MCU Device documentation (maximum value indicated in
 *  the documentation shall be taken).
 *
 * @usage If this duration is exceeded, then the MCU Flash Operation is
 *  considered as failed.
 *
 * @note: I don't know.
 *
 * Default value: /.
 * Supported values: >= 10.
 */
#define DukCONFIG_HW_MCU_DEVICE_FLASH_OPERATION_CHECK_MARGIN_DURATION_MAX_us  \
                            MukVAL_TYPED(TukTIME32_us, 200U + 10U)




/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_HW_MCU_DEVICE_H_INSIDE
#endif /* !defined(UK_CONFIG_HW_MCU_DEVICE_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */
