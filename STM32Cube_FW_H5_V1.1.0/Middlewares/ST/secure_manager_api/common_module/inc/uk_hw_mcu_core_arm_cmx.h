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
 * @file          uk_hw_mcu_core_arm_cmx.h
 * @brief         uKernel API - Platform MCU Core ARM CMx specifics.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file contains the Platform's MCU Core specific part of the uKernel
 *  API for the selected MCU Device.
 *
 * This file supports the following MCU Core Architecture(s):
 *   - ARM v7-M architecture
 *    + Cortex M3
 *    + Cortex M4
 *    + Cortex M7
 *   - ARM v8-M architecture
 *    + Cortex M23
 *    + Cortex M33
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target and a specific Platform.
 *
 * @warning This file is specific to a given uKernel Target and MCU Core.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target and on the selected MCU Core.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note This include file serves the same purpose as the uKernel API defined
 *  in the "uk.h" file while containing only the elements for which there is
 *  some specificities relative to the Platform MCU Core it supports.
 *
 * @usage This file is a child file of the "uk_hw_mcu_device.h" include file
 *  and SHALL BE included only by it.
 ******************************************************************************
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.              */
#if !defined(UK_HW_MCU_CORE_ARM_CMX_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by our parent file.                   */
#if !defined(UK_HW_MCU_DEVICE_H_INSIDE)
    #error 'The "uk_hw_mcu_core_arm_cmx.h" include file shall be included only in the "uk_hw_mcu_device.h" file'
#endif /* !defined(UK_HW_MCU_DEVICE_H_INSIDE) */


/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_HW_MCU_CORE_ARM_CMX_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_HW_MCU_CORE_ARM_CMX_H_INSIDE

/*__________________________________________________________________________*/
/* Source the include files needed by the Public API of this Code Module. */

/* Add inclusion of uKernel API only to help IDE parsing. */
#include "uk.h"


/* ######################################################################## */
/*           PLATFORM'S MCU CORE SPECIFIC - CONFIGURATION CHECK             */
/* ######################################################################## */
/* Platform's MCU Core specific consistency and implementation checks. */

/* Enforce that this file supports the defined MCU Core. */
#if defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM3)
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM4)
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM7)
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM23)
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM33)
#else
  #error "This include file supports only the following ARM Cortex-M MCU Cores: M3, M4, M7, M23, M33."
#endif


/* ######################################################################## */
/*          PLATFORM'S MCU CORE SPECIFIC - CORE VENDOR DEFINITIONS          */
/* ######################################################################## */

/* Source the needed MCU Core vendor definitions include files. */
#if defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM3)
  #include "core_cm3.h"
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM4)
  #include "core_cm4.h"
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM7)
  #include "core_cm7.h"
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM23)
  #include "core_cm23.h"
#elif defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TYPE_CM33)
  #include "core_cm33.h"
#else
  #error "This include file supports only the following ARM Cortex-M MCU Cores: M3, M4, M7, M23, M33."
#endif


/* ######################################################################## */
/*                  UKERNEL API / PLATFORM'S CORE - C-TYPES                 */
/* ######################################################################## */

/* Type definitions shall not be done when this file is used by
 * assembler pre-processor. */
#if !defined(__ASSEMBLER__)


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - SVC IDENTIFIER                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type defining the Identifier used to reference a uKernel
 *  Privileged Service.
 *
 * Definition of the uKernel C-Type for the Identifier used to reference a
 *  uKernel Privileged Service.
 * This uKernel Service Identifier is an internal uKernel value that is used
 *  to reference unambiguously each uKernel Privileged Service inside uKernel.
 *
 * @implementation The uKernel Privileged Service Identifier values are kept
 *  fixed independently of the uKernel Features chosen for a given uKernel
 *  Target or of the uKernel Version (no renumbering is done due to
 *  unsupported uKernel Services: a given uKernel Privileged Service has
 *  always the same Identifier value).
 *
 * @implementation On the ARMv7-M and ARMv8-M architectures, the uKernel
 *  Privileged Service Identifier value is used directly as part of the
 *  coding of the SVC assembly instruction used to switch to uKernel (see
 *  ukSVC() for details).
 *
 * @implementation In order to increase robustness and code efficiency, the
 *  uKernel Privileged Debug Service Identifiers (part of Debug facilities) has
 *  its own dedicated range of identifiers values.
 *
 * @usage The valid range for uKernel Privileged Service Identifier is
 *  [DukSVC_ID8_MIN ... DukSVC_ID8_MAX].
 *  Additionally, if SukCONFIG_FEATURE_PRODUCTION_RELEASE is not supported, the
 *  valid range for uKernel Privileged Debug Service Identifier is
 *  [DukSVC_DEBUG_ID8_MIN ... DukSVC_DEBUG_ID8_MAX].
 */
typedef TukUINT8 TukSVC_ID8;

#endif /* !defined(__ASSEMBLER__) */


/* ######################################################################## */
/*                     UKERNEL API / MCU CORE - C-CONSTANTS                 */
/* ######################################################################## */
/* IMPLEMENTATION: These C-Constants may be used in assembly code and thus
 *  shall be defined only using literals and C-Preprocessor definitions.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - SAFE BOOLEAN                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the 'false' value for a Safe Boolean.
 *
 * Definition of the C-Constant 'false' value for a Safe Boolean (see
 *  <TukSAFEBOOL>).
 *
 * @note The value chosen for this constants is optimized to provide a good
 *  level of robustness (not commonly used constant, with low chance of being
 *  issued by other parts of the code), and also for keeping good efficiency
 *  level when generating low level code for manipulating it.
 *
 * @implementation The chosen value is tuned in function of the MCU Core
 *  Architecture to keep good level of efficiency of generated low level code.
 */
#define DukSAFEBOOL_FALSE MukVAL_TYPED(TukSAFEBOOL, 0x00170017U)

/**
 * @brief C-Constant defining the 'true' value for a Safe Boolean.
 *
 * Definition of the C-Constant 'true' value for a Safe Boolean (see
 *  <TukSAFEBOOL>).
 *
 * @note The value chosen for this constants is optimized to provide a good
 *  level of robustness (not commonly used constant, with low chance of being
 *  issued by other parts of the code), and also for keeping good efficiency
 *  level when generating low level code for manipulating it.
 *
 * @implementation The chosen value is tuned in function of the MCU Core
 *  Architecture to keep good level of efficiency of generated low level code.
 */
#define DukSAFEBOOL_TRUE  MukVAL_TYPED(TukSAFEBOOL, 0x8E008E00U)


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - ADDRESS BLOCK WINDOW                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximal count of simultaneously active
 *  Address Block Windows in a ukProc.
 *
 * Definition of the C-Constant of the maximal count of simultaneously active
 *  Address Block Windows in a ukProc.
 *
 * @note This value is Platform AND uKernel Target dependent.
 *
 * @implementation On most MCU Devices, this count is directly tied to the
 *  number of MPU regions supported by the MCU.
 */
#define DukADDRESSBLOCKWINDOW_COUNT_MAX                                       \
            MukVAL_TYPED(TukCOUNT8, 7U)



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - SVC IDENTIFIERS                   */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter is the definition of each of the uKernel Privileged Service
 *  Identifier (SVC ID) value.
 * This identifier allows to reference the invoked uKernel Service when
 *  switching in uKernel code (this invocation can be done only through
 *  specific MCU instruction; see ukSVC() for details).
 *
 * NOTE: The uKernel Privileged Debug Services (part of Debug facilities) have
 *  their own dedicated range of identifiers.
 *
 * @implementation In order to increase robustness of ukApp code, the
 *  uKernel Privileged Service Identifier values are kept fixed independently
 *  of the uKernel Features chosen for a given uKernel Target or of the
 *  uKernel Version (no renumbering is done due to unsupported uKernel
 *  Services: a given uKernel Service has always the same identifier value).
 *
 * @implementation The identifier values SHALL BE incremented sequentially
 *  from 0.
 */

/* ukProc management. */
#define DukSVC_ID8_ukUKProcExit                     MukVAL_TYPED(TukSVC_ID8,0U)
#define DukSVC_ID8_ukUKProcEntryPointReturn         MukVAL_TYPED(TukSVC_ID8,1U)
#define DukSVC_ID8_ukUKProcYield                    MukVAL_TYPED(TukSVC_ID8,2U)
#define DukSVC_ID8_ukUKProcInstantiate              MukVAL_TYPED(TukSVC_ID8,3U)

/* Watchdog Management. */
#define DukSVC_ID8_ukWatchdogStart                  MukVAL_TYPED(TukSVC_ID8,4U)
#define DukSVC_ID8_ukWatchdogStop                   MukVAL_TYPED(TukSVC_ID8,5U)
#define DukSVC_ID8_ukWatchdogKick                   MukVAL_TYPED(TukSVC_ID8,6U)

/* uKernel Core management. */
#define DukSVC_ID8_ukUKCoreGetAttribute             MukVAL_TYPED(TukSVC_ID8,7U)

/* Platform management. */
#define DukSVC_ID8_ukPlatformGetAttribute           MukVAL_TYPED(TukSVC_ID8,8U)
#define DukSVC_ID8_ukPlatformSetAttribute           MukVAL_TYPED(TukSVC_ID8,9U)

/* ukApp management. */
#define DukSVC_ID8_ukUKAppGetAIDXFromAUID           MukVAL_TYPED(TukSVC_ID8,10U)
#define DukSVC_ID8_ukUKAppGetAttribute              MukVAL_TYPED(TukSVC_ID8,11U)

/* ukProc management. */
#define DukSVC_ID8_ukUKProcGetPUIDFromAUID          MukVAL_TYPED(TukSVC_ID8,12U)
#define DukSVC_ID8_ukUKProcGetAttribute             MukVAL_TYPED(TukSVC_ID8,13U)

/* Time information. */
#define DukSVC_ID8_ukUptimeGet_us                   MukVAL_TYPED(TukSVC_ID8,14U)
#define DukSVC_ID8_ukSystickGetCount                MukVAL_TYPED(TukSVC_ID8,15U)

/* Inter-Process-Communication management. */
#define DukSVC_ID8_ukIPCSendNotificationToProcess   MukVAL_TYPED(TukSVC_ID8,16U)
#define DukSVC_ID8_ukIPCSendDataToProcess           MukVAL_TYPED(TukSVC_ID8,17U)
#define DukSVC_ID8_ukIPCReceive                     MukVAL_TYPED(TukSVC_ID8,18U)
#define DukSVC_ID8_ukIPCSendReceiveDataToProcess    MukVAL_TYPED(TukSVC_ID8,19U)

/* Address Block management. */
#define DukSVC_ID8_ukAddressBlockGetInfo            MukVAL_TYPED(TukSVC_ID8,20U)
#define DukSVC_ID8_ukAddressBlockGetIDFromLabel     MukVAL_TYPED(TukSVC_ID8,21U)
#define DukSVC_ID8_ukAddressBlockGetBundleID        MukVAL_TYPED(TukSVC_ID8,22U)

/* Address Block Window management. */
#define DukSVC_ID8_ukAddressBlockWindowMap          MukVAL_TYPED(TukSVC_ID8,23U)
#define DukSVC_ID8_ukAddressBlockWindowUnMap        MukVAL_TYPED(TukSVC_ID8,24U)
#define DukSVC_ID8_ukAddressBlockWindowGetMapped    MukVAL_TYPED(TukSVC_ID8,25U)

/* Shared Buffer management. */
#define DukSVC_ID8_ukSharedBufferResetCredentials   MukVAL_TYPED(TukSVC_ID8,26U)
#define DukSVC_ID8_ukSharedBufferAddCredentials     MukVAL_TYPED(TukSVC_ID8,27U)
#define DukSVC_ID8_ukSharedBufferTransfer           MukVAL_TYPED(TukSVC_ID8,28U)

/* MCU Register management. */
#define DukSVC_ID8_ukMCURegisterRead                MukVAL_TYPED(TukSVC_ID8,29U)
#define DukSVC_ID8_ukMCURegisterWrite               MukVAL_TYPED(TukSVC_ID8,30U)

/* Peripheral IRQ management. */
#define DukSVC_ID8_ukPeripheralIRQRegister          MukVAL_TYPED(TukSVC_ID8,31U)
#define DukSVC_ID8_ukPeripheralIRQUnregister        MukVAL_TYPED(TukSVC_ID8,32U)
#define DukSVC_ID8_ukPeripheralIRQGetInfo           MukVAL_TYPED(TukSVC_ID8,33U)
#define DukSVC_ID8_ukPeripheralIRQPerformAction     MukVAL_TYPED(TukSVC_ID8,34U)

/* DMA Stream management. */
#define DukSVC_ID8_ukDMAStreamGetIDFromLabel        MukVAL_TYPED(TukSVC_ID8,35U)
#define DukSVC_ID8_ukDMAStreamGetInfo               MukVAL_TYPED(TukSVC_ID8,36U)
#define DukSVC_ID8_ukDMAStreamAssign                MukVAL_TYPED(TukSVC_ID8,37U)
#define DukSVC_ID8_ukDMAStreamUnassign              MukVAL_TYPED(TukSVC_ID8,38U)
#define DukSVC_ID8_ukDMAStreamTransferStart         MukVAL_TYPED(TukSVC_ID8,39U)
#define DukSVC_ID8_ukDMAStreamTransferStop          MukVAL_TYPED(TukSVC_ID8,40U)
#define DukSVC_ID8_ukDMAStreamTransferGetInfo       MukVAL_TYPED(TukSVC_ID8,41U)
#define DukSVC_ID8_ukDMAStreamTransferGetState      MukVAL_TYPED(TukSVC_ID8,42U)

/* Data Persistent Block Management */
#define DukSVC_ID8_ukPersistentDataBlockEraseSector MukVAL_TYPED(TukSVC_ID8,43U)
#define DukSVC_ID8_ukPersistentDataBlockWrite       MukVAL_TYPED(TukSVC_ID8,44U)
#define DukSVC_ID8_ukPersistentDataBlockRead        MukVAL_TYPED(TukSVC_ID8,45U)

/* uKernel Image Update. */
#define DukSVC_ID8_ukUKImageUpdateEraseSector       MukVAL_TYPED(TukSVC_ID8,46U)
#define DukSVC_ID8_ukUKImageUpdateWrite             MukVAL_TYPED(TukSVC_ID8,47U)
#define DukSVC_ID8_ukUKImageUpdateRead              MukVAL_TYPED(TukSVC_ID8,48U)
#define DukSVC_ID8_ukUKImageUpdateOperate           MukVAL_TYPED(TukSVC_ID8,49U)

/* Random generation. */
#define DukSVC_ID8_ukRandomSetSeed64                MukVAL_TYPED(TukSVC_ID8,50U)
#define DukSVC_ID8_ukRandomGetBytes                 MukVAL_TYPED(TukSVC_ID8,51U)


/**
 * @brief C-Constant defining the minimum value for a uKernel Privileged
 *  Service Identifier not part of Debug facilities.
 *
 * Definition of the C-Constant of the minimum value for a uKernel Privileged
 *  Service Identifier which is not part of Debug facilities.
 *
 * @implementation This C-Constant shall be equal to null(0).
 */
#define DukSVC_ID8_MIN      MukVAL_TYPED(TukSVC_ID8,                          \
                                         DukSVC_ID8_ukUKProcExit)

/**
 * @brief C-Constant defining the maximum value for a uKernel Privileged
 *  Service Identifier not part of Debug facilities.
 *
 * Definition of the C-Constant of the maximum value for a uKernel Privileged
 *  Service Identifier which is not part of Debug facilities.
 *
 * @usage An identifier for referencing a uKernel Privileged Service will
 *  trigger a Fatal Error for the ukProc if not in one of the following ranges:
 *  - [DukSVC_ID8_MIN ... DukSVC_ID8_MAX].
 *  - [DukSVC_DEBUG_ID8_MIN ... DukSVC_DEBUG_ID8_MAX] if
 *   SukCONFIG_FEATURE_PRODUCTION_RELEASE is not supported.
 */
#define DukSVC_ID8_MAX      MukVAL_TYPED(TukSVC_ID8,                          \
                                         DukSVC_ID8_ukRandomGetBytes)


/**
 * @brief C-Constant defining the count of defined uKernel Privileged Service
 *  Identifiers not part of Debug facilities.
 *
 * Definition of the C-Constant of the count of defined uKernel Privileged
 *  Service Identifiers not part of Debug facilities.
 *
 * @implementation This C-Constant shall be in the range [1 ... 64].
 */
#define DukSVC_ID8_COUNT    MukVAL_TYPED(TukCOUNT8,                           \
                                        (DukSVC_ID8_MAX - DukSVC_ID8_MIN + 1U))


/* //////////////////////////////////////////////////////////////////////// */
/*                     C-CONSTANTS - DEBUG - SVC IDENTIFIERS                */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter is the definition of each of the uKernel Privileged Debug Service
 *  Identifier value.
 * This identifier allows to reference the invoked uKernel Debug Service when
 *  switching in uKernel code (this invocation can be done only through
 *  specific MCU instruction; see ukSVC() for details).
 *
 * @implementation In order to increase robustness of ukApp code, the
 *  uKernel Privileged Debug Service Identifier values are kept fixed
 *  independently of the uKernel Features chosen for a given uKernel Target
 *  or of the uKernel Version (no renumbering is done due to unsupported
 *  uKernel Services: a given uKernel Service has always the same identifier
 *  value).
 *
 * @implementation The identifier for uKernel Privileged Debug Service values
 *  SHALL BE incremented sequentially from 0x40 (64).
 */

/* ukProc Debug facilities. */
#define DukSVC_DEBUG_ID8_ukDebugTracePrint         MukVAL_TYPED(TukSVC_ID8,64U)
#define DukSVC_DEBUG_ID8_ukDebugTracePrintf        MukVAL_TYPED(TukSVC_ID8,65U)
#define DukSVC_DEBUG_ID8_ukDebugTracePrintBuffer   MukVAL_TYPED(TukSVC_ID8,66U)
#define DukSVC_DEBUG_ID8_ukDebugLEDSetPattern      MukVAL_TYPED(TukSVC_ID8,67U)

/**
 * @brief C-Constant defining the maximum value for a uKernel Privileged
 *  Debug Service Identifier.
 *
 * Definition of the C-Constant of the maximum value for a uKernel Privileged
 *  Debug Service Identifier (i.e. part of Debug facilities).
 *
 * @implementation This C-Constant shall be equal to 0x40(64).
 */
#define DukSVC_DEBUG_ID8_MIN    MukVAL_TYPED(TukSVC_ID8,                      \
                                    DukSVC_DEBUG_ID8_ukDebugTracePrint)

/**
 * @brief C-Constant defining the maximum value for a uKernel Privileged
 *  Debug Service Identifier.
 *
 * Definition of the C-Constant of the maximum value for a uKernel Privileged
 *  Debug Service Identifier (i.e. part of Debug facilities).
 *
 * @usage An identifier for referencing a uKernel Privileged Debug Service
 *  (that is in the range [DukSVC_DEBUG_ID8_MIN ... DukSVC_DEBUG_ID8_MAX]) will
 *  trigger a Fatal Error if SukCONFIG_FEATURE_PRODUCTION_RELEASE is
 *  supported.
 */
#define DukSVC_DEBUG_ID8_MAX    MukVAL_TYPED(TukSVC_ID8,                      \
                                    DukSVC_DEBUG_ID8_ukDebugLEDSetPattern)


/**
 * @brief C-Constant defining the count of defined uKernel Privileged Debug
 *  Service Identifiers.
 *
 * Definition of the C-Constant of the count of defined uKernel Privileged
 *  Debug Service Identifiers (i.e. part of Debug facilities).
 *
 * @implementation This C-Constant shall be in the range [0 ... 16].
 */
#define DukSVC_DEBUG_ID8_COUNT  MukVAL_TYPED(                                 \
                        TukCOUNT8,                                            \
                        (DukSVC_DEBUG_ID8_MAX - DukSVC_DEBUG_ID8_MIN + 1U))




/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - DEBUG - SVC DEBUG TRACE                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Debug Trace Attribute for reporting
 *  Status Code check of uKernel Privileges Services.
 *
 * Definition of the C-Constant of Debug Trace Attribute for reporting
 *  Status Code check of uKernel Privileges Services.
 *
 * @implementation This C-Constant is used only if the ukApp Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES is defined.
 *
 * @usage This Debug Trace Attribute is used by C-Macro
 *  ukSVC_DEBUG_TRACE_STATUS_CHECK().
 */
#define DukSVC_DEBUG_TRACE_STATUS_CHECK_ATTRIB                                \
            MukDEBUG_TRACE_ATTRIBUTES_BUILD(                                  \
                DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG,                        \
                0,                                                            \
                DukDEBUG_TRACE_VERBOSITY_FINER)


/* ######################################################################## */
/*                 UKERNEL API / PLATFORM'S CORE - C-COMPILER               */
/* ######################################################################## */

/* //////////////////////////////////////////////////////////////////////// */
/*               C-COMPILER - UKERNEL SERVICE HELPING DEFINITIONS           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Compiler Attribute definition for a uKernel Privileged Service
 *  Entry Point.
 *
 * This C-Compiler Attribute defines attributes to be used for the definition
 *  of a uKernel Privileged Service Entry Point.
 *
 * The C-Compiler attributes used are the following:
 *  - 'noinline': Prevents C-Compiler to use inline optimization to make sure
 *   that parameters are properly placed in registers as required by the EABI
 *   convention.
 *  - 'unused': Prevents C-Compiler warning if the Entry Point is not used.
 *
 * @implementation A uKernel Privileged Service Entry Point is a C-Function
 *  containing the stub code for invoking a uKernel Privileged Service (whose
 *  code is in uKernel Core).
 *  The stub code eases the invocation in ukApp code by being notably in
 *  charge of handling the proper set up of input/output parameters (see the
 *  GVukappBlockDataSharedUKSVC C-Variable).
 */
#define CAukFUNC_SERVICE_ENTRYPOINT __attribute__((noinline,unused))


/* ######################################################################## */
/*                 UKERNEL API / PLATFORM'S CORE - C-MACROS                 */
/* ######################################################################## */

/* //////////////////////////////////////////////////////////////////////// */
/*                                C-MACROS - SVC                            */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief C-Macro for invoking a uKernel Privileged Service.
 *
 * Definition of the uKernel C-Macro for the invocation of a uKernel
 *  Privileged Service.
 *
 * @implementation On ARMv7-M and ARMv8-M architectures, the invocation of a
 *  uKernel Privileged Service is based on the Service Handler Call (SVC) ARM
 *  instruction.
 *  The ID (8-bit value) part of the SVC instruction is used to transfer the
 *  uKernel Privileged Service Identifier (see <TukSVC_ID8>) referencing the
 *  uKernel Privileged Service to be invoked (the uKernel SVC handler then
 *  retrieves the ID and dispatch internally to the selected service code in
 *  uKernel Core implementation).
 *
 * @usage This C-Macro SHALL BE used only for the invocation of a uKernel
 *  Privileged Service.
 *
 * @usage For optimization reasons, this C-Macro may be used directly in
 *  ukApp code. However care has then to be taken by the ukApp code to have
 *  the proper set up of the input/output parameters in C-Variable
 *  GVukappBlockDataSharedUKSVC for the selected uKernel Privileged Service in
 *  function of used uKernel Target (as offsets are not guaranteed of
 *  remaining the same between different uKernel Targets).
 *
 * @param[in] svc_id8__i Identifier (8-bit) of the uKernel Privileged Service
 *  to invoke.
 */
#ifdef TESTSIM
extern void ukSVC(uint8_t);
#else
#define ukSVC(svc_id8__i)                                                     \
            __asm volatile (                                                  \
                          "SVC  %[svc_id8]\n\t"                               \
                          : : [svc_id8] "I" (svc_id8__i) : "cc", "memory");
#endif

/**
 * @brief C-Macro for invoking a uKernel Privileged Service returning a
 *  Status Code.
 *
 * Definition of the uKernel C-Macro for the invocation of a privileged
 *  uKernel Service returning a Status Code (see TukSTATUS).
 *
 * @note Excepted for the management of the returned value, this C-Macro is
 *  similar to ukSVC().
 *
 * @param[in] (TukSVC_ID8)svc_id8__i Identifier (8-bit) of the uKernel
 *  Privileged Service to invoke.
 * @param[in] (TukSTATUS)status_code Variable aimed at containing the Status
 *  Code indicating the level of success of the uKernel Privileged Service
 *  invocation.
 */
#define ukSVC_RETURN_STATUSCODE(svc_id8__i, status_code)                      \
    {                                                                         \
      ukSVC(svc_id8__i);                                                      \
      status_code = (TukSTATUS)                                               \
        GVukappBlockDataSharedUKSVC.ServiceResult.StatusCode;                 \
    }

/**
 * @brief C-Macro for invoking a uKernel Privileged Service returning a
 *  32-bit value.
 *
 * Definition of the uKernel C-Macro for the invocation of a uKernel Privileged
 *  Service returning a 32-bit value.
 *
 * @note Excepted for the management of the returned value, this C-Macro is
 *  similar to ukSVC().
 *
 * @param[in] (TukSVC_ID8)svc_id8__i Identifier (8-bit) of the uKernel
 *  Privileged Service to invoke.
 * @param[in] return_value32 Variable aimed at containing the 32-bit value
 *  returned by the uKernel Privileged Service invocation.
 */
#define ukSVC_RETURN32(svc_id8__i, return_value32)                            \
        {                                                                     \
          ukSVC(svc_id8__i);                                                  \
          return_value32 = (typeof(return_value32))                           \
                       (GVukappBlockDataSharedUKSVC.ServiceResult.Value32);   \
         }

/**
 * @brief C-Macro for invoking a uKernel Privileged Service returning a
 *  64-bit value.
 *
 * Definition of the uKernel C-Macro for the invocation of a uKernel Privileged
 *  Service returning a 64-bit value.
 *
 * @note Excepted for the management of the returned value, this C-Macro is
 *  similar to ukSVC().
 *
 * @param[in] (TukSVC_ID8)svc_id8__i Identifier (8-bit) of the uKernel Service
 *  to invoke.
 * @param[in] return_value64 Variable aimed at containing the 64-bit value
 *  returned by the uKernel Service invocation.
 */
#define ukSVC_RETURN64(svc_id8__i, return_value64)                            \
        {                                                                     \
          ukSVC(svc_id8__i);                                                  \
          return_value64 = GVukappBlockDataSharedUKSVC.ServiceResult.Value64; \
         }


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_HW_MCU_CORE_ARM_CMX_H_INSIDE
#endif /* !defined(UK_HW_MCU_CORE_ARM_CMX_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

