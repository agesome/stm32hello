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
 * @file          uk_app.c
 * @brief         uKernelAPI - ukApp uKernel Framework C-Code implementation.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 * This file contains the C-Code of the ukApp uKernel Framework needed by the
 *  uKernel for managing the ukApp and integrating it as part of the ukApps
 *  Bundle.
 *
 * This file contains notably the following definitions:
 *  - C-Variable defining the ukApp Data Volatile Shared uKernel Services Block,
 *   used by uKernel Privileged Services for exchanging data with the ukProc.
 *  - Constant C-Structure of the ukApp Descriptor, containing all the
 *   information and configuration needed by the uKernel for managing the ukApp
 *   (memory areas, name, priority, credentials, ...).
 *  - Helpers C-Functions for uKernel Privileged Services.
 *
 * This file is part of the ukApp SDK.
 *
 * @warning This file is specific to a given uKernel Target.
 *  This file SHALL NOT BE MODIFIED.
 *  It shall be used only for compiling and linking ukApp aiming at running on
 *   this given uKernel Target.
 *  If improper version is used, the ukApp proper execution cannot be
 *   guaranteed. However, the ukApp security properties, and notably its
 *   isolation, remain always enforced even in case an improper version is
 *   used.
 *
 * @usage In order to ease maintenance and centralize the modifications needed
 *  for the configuration of the ukApp by the Developer, all the Developer
 *  inputs are centralized in the Developer definition file
 *  "ukapp/include/config/ukapp_config_descriptor.h" (this file is part of
 *  ukApp SDK).
 *
 * @usage This file shall be compiled with the rest of ukApp code, and
 *  resulting compilation data included in the released ukApp binary file.
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Do not compile this file if compiling uKernel Core. */
#if !defined(UKCORE)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_APP_C

/* Define that we are inside a C-file of the module (definition is undone at
 *  its end). */
#define  UK_APP_INMODULE

/*__________________________________________________________________________*/
/* Source the public uKernel API include files. */

#ifdef __IARCC__
#include "ukapp_config_sections.h"
#include "uk.h"
#else
#include "uk/include/uk.h"
#endif
/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                     COMPILATION CONFIGURATION CHECK                      */
/* ######################################################################## */
/* Consistency and implementation checks of the ukApp definitions specific to
 *  this ukApp, part of the ukApp uKernel Framework, and done in the
 *  "ukapp_config_descriptor.h" file.
 *
 * NOTE: Some of the checks may depend of the uKernel Features and uKernel
 *  Options of the used uKernel Target.
 * @implementation These checks contain only static assertions verified at
 *  compilation time (no generation of code).
 */

/**
 * Check if the C-PreProcessor value DukappCONFIG_NAMESPACE is defined.
 * This C-PreProcessor value is used when needing to provide unique symbols
 *  namespace for each ukApp.
 * @implementation It is advised to define it using the Eclipse Project name.
 */
#if !defined(DukappCONFIG_NAMESPACE)
    #error "The DukappCONFIG_NAMESPACE C-PreProcessor symbol shall be defined as global C-Preprocessor symbol using the Eclipse Project Name (see 'Project/Properties/C C++ General/Path and Symbols')."
#endif

/** Check if the ukApp Framework files have been updated with latest version
 *  provided with uKernel Target. */
#if (UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MAJOR !=                               \
     DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MAJOR) ||              \
    (UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MINOR !=                               \
     DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MINOR)
    #warning 'The file "ukapp/include/config/ukapp_config_descriptor.h" is not using the latest version provided with uKernel Target: some new fields are set to default value.'
#else
    #if (UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MICRO !=                           \
     DukRELEASE_FILE_UKAPP_CONFIG_DESCRIPTOR_H_VERSION_MICRO)
        #warning message 'The file "ukapp/include/config/ukapp_config_options.h" is not using the latest version provided with uKernel Target which include some minors changes(documentation, ...).'
    #endif
#endif

#if (UKAPP_CONFIG_OPTIONS_H_VERSION_MAJOR !=                                  \
     DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MAJOR) ||                 \
    (UKAPP_CONFIG_OPTIONS_H_VERSION_MINOR !=                                  \
     DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MINOR)
    #warning 'The file "ukapp/include/config/ukapp_config_options.h" is not using the latest version provided with uKernel Target: some new options are set to default value.'
#else
    #if (UKAPP_CONFIG_OPTIONS_H_VERSION_MICRO !=                              \
     DukRELEASE_FILE_UKAPP_CONFIG_OPTIONS_H_VERSION_MICRO)
        #warning message 'The file "ukapp/include/config/ukapp_config_options.h" is not using the latest version provided with uKernel Target which include some minors changes(documentation, ...).'
    #endif
#endif



/* ######################################################################## */
/*                  UKAPP UKERNEL FRAMEWORK -  C-CONSTANTS                  */
/* ######################################################################## */
/* Hereafter are defined the C-Constants specific to this ukApp, and part of
 *  the ukApp uKernel Framework.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */



/* //////////////////////////////////////////////////////////////////////// */
/*                C-CONSTANTS - DEVELOPER DEFINITIONS DEFAULT               */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter are defined with default values the Developer Definitions
 *  C-Constants that are needed by used uKernel Target but that have not been
 *  be defined in "ukapp_config_descriptor.h" file because an older version of
 *  the file is used.
 */

#if !defined(Dukapp_config_PrivilegedServicesAuthorizedBitMask64)
    #warning 'Dukapp_config_PrivilegedServicesAuthorizedBitMask64 is not defined: use last uKernel Target version of file "ukapp_config_descriptor.h"'
    #define Dukapp_config_PrivilegedServicesAuthorizedBitMask64               \
        0xFFFFFFFFFFFFFFFFULL
#endif /* !defined(Dukapp_config_PrivilegedServicesAuthorizedBitMask64) */
#ifndef __IARCC__
#if !defined(Dukapp_config_MCURegisterDescriptorList)
    #warning 'Dukapp_config_MCURegisterDescriptorList is not defined: use last uKernel Target version of file "ukapp_config_descriptor.h"'
    #define Dukapp_config_MCURegisterDescriptorList                           \
        { }
#endif /* !defined(Dukapp_config_MCURegisterDescriptorList) */
#else
   // With IAR, we should not define Dukapp_config_MCURegisterDescriptorList as it creates an error
#endif
#if !defined(Dukapp_config_UKAppCodeBodyBlockSHA256)
    #warning 'Dukapp_config_UKAppCodeBodyBlockSHA256 is not defined: use last uKernel Target version of file "ukapp_config_descriptor.h"'
    #define Dukapp_config_UKAppCodeBodyBlockSHA256  {                         \
            0x5A5A5A5A, 0x1CCCCCC1, 0x2CCCCCC2, 0x3CCCCCC3,                   \
            0x4CCCCCC4, 0x5CCCCCC5, 0x6CCCCCC6, 0x5A5A5A5A                    \
                                                    }
#endif /* !defined(Dukapp_config_UKAppCodeBodyBlockSHA256) */

#if !defined(Dukapp_config_UKAppDescriptorSHA256)
    #warning 'Dukapp_config_UKAppDescriptorSHA256 is not defined: use last uKernel Target version of file "ukapp_config_descriptor.h"'
    #define Dukapp_config_UKAppDescriptorSHA256 {                             \
            0x5A5A5A5A, 0x1DDDDDD1, 0x2DDDDDD2, 0x3DDDDDD3,                   \
            0x4DDDDDD4, 0x5DDDDDD5, 0x6DDDDDD6, 0x5A5A5A5A                    \
                                                }
#endif /* !defined(Dukapp_config_UKAppDescriptorSHA256) */

#if !defined(Dukapp_config_DebugTraceNatureFilter)
    #define Dukapp_config_DebugTraceNatureFilter Dukapp_config_DebugTraceNatures
#endif /* !defined(Dukapp_config_DebugTraceNatureFilter) */

#if !defined(Dukapp_config_DebugTraceVerbosityFilter)
    #define Dukapp_config_DebugTraceVerbosityFilter Dukapp_config_DebugTraceVerbosity
#endif /* !defined(Dukapp_config_DebugTraceVerbosityFilter) */


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - UKAPP ENTRY POINT                   */
/* //////////////////////////////////////////////////////////////////////// */
#ifndef __IARCC__
#if defined(SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP)
    #define Dukapp_ENTRY_POINT_CLEANUP_ADDRESS      \
        MukVAL_TYPED(TukADDRESS32, &ukappCleanup)
#else /* defined(SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP) */
    #define Dukapp_ENTRY_POINT_CLEANUP_ADDRESS                                \
        MukVAL_TYPED(TukADDRESS32, DukADDRESS_IGNORE)
#endif /* defined(SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP) */
#endif /*ifndef __IARCC__ */

#if defined(SukCONFIG_FEATURE_UKPROC_EXCEPTION)
    #define Dukapp_ENTRY_POINT_EXCEPTION_ADDRESS                              \
        MukVAL_TYPED(TukADDRESS32, &ukappException)
#else /* defined(SukCONFIG_FEATURE_UKPROC_EXCEPTION) */
    #define Dukapp_ENTRY_POINT_EXCEPTION_ADDRESS                              \
        MukVAL_TYPED(TukADDRESS32, DukADDRESS_IGNORE)
#endif /* defined(SukCONFIG_FEATURE_UKPROC_EXCEPTION) */



/* ######################################################################## */
/*                   UKAPP UKERNEL FRAMEWORK - C-VARIABLES                  */
/* ######################################################################## */
/* Hereafter are defined the C-Variables, with global C-Scope, specific to
 *  this ukApp, and part of the ukApp uKernel Framework.
 *
 * NOTE: See the "uk_app.h" include file for the documentation relative to
 *  these C-Variables.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-VARIABLES - UKAPP DATA BLOCK SHARED                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief UKAPP Data block shared section must be defined in this source file.
 */
#ifndef __IARCC__
MukVAR_DEFINE_SECTION(GVukappBlockDataSharedUKSVC,
                      TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC,
                      ".ukapp_block_data_shared_uksvc");
#else
#pragma section=".ukapp_data_volatile_shared_uksvc"
__root TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC GVukappBlockDataSharedUKSVC __attribute__((used, section(".ukapp_data_volatile_shared_uksvc")));

/**
 * @brief Extra section added to the elf with IAR
 * This section allows to store start/end addresses of different section
 * needed to compute size of dynamic sections during the post-build execution with IAR
 * A program (named parser) is used to retrieve these info and compute the different size
 * and it is used for editing the ukapp_code_descriptor section with appropriate information.
 *
 * These information are mandatory for the ukernel in order to start the ukapp.
 */
#pragma section=".info_addr"
const __no_alloc uint32_t addr[8] __attribute__((used, section(".info_addr"))) =
{
  (uint32_t)__section_end(".ukapp_code_const_tail"),
  (uint32_t)__section_begin(".ukapp_code_const_head"),
  (uint32_t)__section_end(".ukapp_data_volatile_shared_uksvc"),
  (uint32_t)__section_begin(".ukapp_data_volatile_shared_uksvc"),
  (uint32_t)__section_end(".ukapp_data_volatile_var_init_tail"),
  (uint32_t)__section_begin(".ukapp_data_volatile_var_init_head"),
  (uint32_t)__section_end(".ukapp_data_volatile_var_null_tail"),
  (uint32_t)__section_end(".ukapp_data_volatile_var_null_head"),
};
#endif


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-VARIABLES - UKAPP DESCRIPTOR                     */
/* //////////////////////////////////////////////////////////////////////// */

#ifndef __IARCC__
MukCONST_STRUCT_DEFINE_SECTION(GKukappApplicationDescriptor,
                               TukUKAPP_DESCRIPTOR,
                               ".ukapp_descriptor") =
#else
#pragma location=".ukapp_descriptor"
__root
TukUKAPP_DESCRIPTOR GKukappApplicationDescriptor __attribute__((used, section(".ukapp_descriptor")))=
#endif
{
    /* UKAppDescriptorMagicStart64 */
    (TukMAGIC64)DukUKAPP_DESCRIPTOR_MAGIC64,

    /* UKAppDescriptorVersion */
    (TukVERSION)DukRELEASE_UKAPP_DESCRIPTOR_VERSION,

    /* PaddingVariability */
    { MukPADDING_GENERATE32(
            0x0B908057UL ^ ((Dukapp_config_AUID64 >> 00) & 0xFFFFFFFFUL)),
      MukPADDING_GENERATE32(
            0x2EA4AB75UL ^ ((Dukapp_config_AUID64 >> 32) & 0xFFFFFFFFUL)) },

    /* ReleaseuKernelVersion */
    (TukVERSION)DukRELEASE_UKERNEL_VERSION,

    /* ReleaseCustomerConfiguration */
    (TukCUSTOMER_CONFIG)DukRELEASE_CUSTOMER_CONFIG,

    /* ReleaseMCUDeviceIdentifier */
    DukCONFIG_HW_MCU_DEVICE_IDENTIFIER128,
#ifndef __IARCC__
    /* MemoryRegionCodeAddressStart */
    (TukADDRESS32)&LukUKAPP_BLOCK_CODE_ADDRESS_START,
    /* MemoryRegionCodeSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_CODE_SIZE_RESERVED,
    /* MemoryRegionCodeExecutableSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_CODE_EXEC_SIZE,
    /* MemoryRegionCodeConstantSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_CODE_CONSTANT_SIZE,
    /* MemoryRegionDataVolatileAddressStart */
    (TukADDRESS32)&LukUKAPP_BLOCK_DATA_VOLATILE_ADDRESS_START,
    /* MemoryRegionDataVolatileSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_DATA_VOLATILE_SIZE_RESERVED,
    /* MemoryRegionDataVolatileSharedUKSVCSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE,
    /* MemoryRegionDataVolatileVarInitSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_DATA_VOLATILE_VAR_INIT_SIZE,
    /* MemoryRegionDataVolatileVarInitLoadAddress */
    (TukADDRESS32)&LukUKAPP_BLOCK_CODE_VAR_INIT_LOAD_ADDRESS,
    /* MemoryRegionDataVolatileVarNullSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_DATA_VOLATILE_VAR_NULL_SIZE,
    /* MemoryRegionDataVolatileStackSize */
    (TukLENGTH32)&LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED,
    /* MemoryRegionDataPersistentAddressStart */
    (TukADDRESS32)&LukUKAPP_BLOCK_DATA_PERSISTENT_ADDRESS_START,
    /* MemoryRegionDataPersistentSize */
    (TukLENGTH32)&LukUKAPP_BLOCK_DATA_PERSISTENT_SIZE_RESERVED,
#else
    /* MemoryRegionCodeAddressStart */
    (TukADDRESS32)(UKAPP_MEMORY_REGION_CODE_ORIGIN),
    /* MemoryRegionCodeSize */
    (TukLENGTH32)(UKAPP_MEMORY_REGION_CODE_ORIGIN_END - UKAPP_MEMORY_REGION_CODE_ORIGIN),
    /* MemoryRegionCodeExecutableSize */
    (TukLENGTH32)((uint32_t)__section_end(".ukapp_code_exec_tail") - UKAPP_MEMORY_REGION_CODE_ORIGIN),
    /* MemoryRegionCodeConstantSize - force to arbitrary value - it will be replaced with parser program */
      0x11111111U,
    /* MemoryRegionDataVolatileAddressStart */
    (TukADDRESS32)(UKAPP_MEMORY_REGION_DATA_VOLATILE_ORIGIN),
    /* MemoryRegionDataVolatileSize */
    (TukLENGTH32)(UKAPP_MEMORY_REGION_DATA_VOLATILE_ORIGIN_END - UKAPP_MEMORY_REGION_DATA_VOLATILE_ORIGIN),
    /* MemoryRegionDataVolatileSharedUKSVCSize - force to arbitrary value - it will be replaced with parser program */
      0x22222222U,
    /* MemoryRegionDataVolatileVarInitSize - force to arbitrary value - it will be replaced with parser program */
      0x33333333U,
    /* MemoryRegionDataVolatileVarInitLoadAddress */
    (TukLENGTH32)((uint32_t)__section_begin(".ukapp_data_volatile_var_init_head")),
    /* MemoryRegionDataVolatileVarNullSize - force to arbitrary value - it will be replaced with parser program */
      0x44444444U,
    /* MemoryRegionDataVolatileStackSize */
    (TukLENGTH32)(LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED),
    /* MemoryRegionDataPersistentAddressStart */
    (TukADDRESS32)(UKAPP_MEMORY_REGION_DATA_PERSISTENT_ORIGIN),
    /* MemoryRegionDataPersistentSize */
    (TukLENGTH32)(UKAPP_MEMORY_REGION_DATA_PERSISTENT_ORIGIN_END - UKAPP_MEMORY_REGION_DATA_PERSISTENT_ORIGIN),
#endif

    /* UKAppEntryPointMainAddress */
    (TukADDRESS32)&ukappMain,
#ifndef __IARCC__
    /* UKAppEntryPointCleanupAddress */
    (TukADDRESS32)Dukapp_ENTRY_POINT_CLEANUP_ADDRESS,
#else
    (TukADDRESS32)LDukADDRESS_IGNORE,
#endif
    /* UKAppEntryPointExceptionAddress */
    (TukADDRESS32)Dukapp_ENTRY_POINT_EXCEPTION_ADDRESS,
    /* UKAppEntryPointReturnAddress */
    (TukADDRESS32)&ukappEntryPointReturn,
    /* UKAppEntryPointUKernelManager */
    (TukADDRESS32)0UL,


    /* NameNTString */
    Dukapp_config_NAME_NTARRAY,
    /* AUID */
    Dukapp_config_AUID64,
    /* Version */
    Dukapp_config_VERSION32,

    /* Profile */
    Dukapp_config_UKAPP_PROFILE,

    /* ParentASID */
    Dukapp_config_PARENT_ASID,

    /* SchedulingPriorityBase */
    Dukapp_config_PRIORITY,
    /* SchedulingTimeQuantumAllocated_systick */
    Dukapp_config_TIME_QUANTUM_systick,
    /* UKProcExceptionSchedulingPriority */
    0UL,
    /* UKProcExceptionSchedulingTimeQuantumAllocated_systick */
    0UL,

    /* UKPrivilegedServicesAuthorizedBitMask64 */
    Dukapp_config_PrivilegedServicesAuthorizedBitMask64,
#ifdef Dukapp_config_PIRQMCUIndexAuthorized
    /* PIRQMCUIndexAuthorizedCount */
    (sizeof((TukPIRQ_MCU_IDX[])Dukapp_config_PIRQMCUIndexAuthorized)/sizeof(TukPIRQ_MCU_IDX)),
    /* PIRQMCUIndexAuthorized */
    Dukapp_config_PIRQMCUIndexAuthorized,
#else
    0U,
    {0UL},
#endif

    /* IPCSendToASIDAuthorizedCount */
    sizeof((TukUKAPP_ASID[])Dukapp_config_IPCSendToAuthorizedASID)/sizeof(TukUKAPP_ASID),
    /* IPCSendToASIDAuthorizedList */
    Dukapp_config_IPCSendToAuthorizedASID,
#ifdef Dukapp_config_SharedBufferDescriptorList
    /* SharedBufferDescriptorCount */
    sizeof((TukSHAREDBUFFER_DESCRIPTOR[])Dukapp_config_SharedBufferDescriptorList)/sizeof(TukSHAREDBUFFER_DESCRIPTOR),
    /* SharedBufferDescriptorList */
    Dukapp_config_SharedBufferDescriptorList,
#else
    0U,
    {{0UL}},
#endif
#ifdef Dukapp_config_AddressBlockExtraDescriptorList
    /* AddressBlockExtraDescriptorCount */
    sizeof((TukADDRESSBLOCK_EXTRA_DESCRIPTOR[])Dukapp_config_AddressBlockExtraDescriptorList)/sizeof(TukADDRESSBLOCK_EXTRA_DESCRIPTOR),
    /* AddressBlockExtraDescriptorList */
   Dukapp_config_AddressBlockExtraDescriptorList,
#else
    0U,
    {{0UL}},
#endif
#ifdef Dukapp_config_MCURegisterDescriptorList
    /* MCURegisterDescriptorCount */
    sizeof((TukMCUREGISTER_DESCRIPTOR[])Dukapp_config_MCURegisterDescriptorList)/sizeof(TukMCUREGISTER_DESCRIPTOR),
    /* MCURegisterDescriptorList */
    Dukapp_config_MCURegisterDescriptorList,
#else
    0U,
    {{0UL}},
#endif

#ifdef Dukapp_config_DMAStreamDescriptorList
    /* DMAStreamDescriptorCount */
    sizeof((TukDMAS_DESCRIPTOR[])Dukapp_config_DMAStreamDescriptorList)/sizeof(TukDMAS_DESCRIPTOR),
    /* DMAStreamDescriptorList */
    Dukapp_config_DMAStreamDescriptorList,
#else
    0U,
    {{0UL}},
#endif

    /* DebugTraceNatureFilter */
    Dukapp_config_DebugTraceNatureFilter,
    /* DebugTraceVerbosityFilter */
    Dukapp_config_DebugTraceVerbosityFilter,

    /*  UKAppCodeBodyBlockSHA256 */
    Dukapp_config_UKAppCodeBodyBlockSHA256,

    /*  UKAppDescriptorSHA256 */
    Dukapp_config_UKAppDescriptorSHA256

    };


/* ######################################################################## */
/*                   UKAPP UKERNEL FRAMEWORK - C-FUNCTIONS                  */
/* ######################################################################## */
/* Hereafter are defined the C-Functions part of the ukApp uKernel Framework.
 *
 * NOTE: See the "uk_app.h" include file for the documentation relative to
 *  these C-Functions.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                      C-FUNCTIONS - SVC - DEBUG TRACE                     */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES)

/* ======================================================================== */
/*                      uk_appSVCDebugTraceStatusPrint                      */
/* ======================================================================== */
void uk_appSVCDebugTraceStatusPrint(
                TukSTATUS            status_code__i,
                TukNTCSTRING_ADDRESS svc_name_ntstring_addr__i) {


    if ((status_code__i &
         DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) != 0) {
        ukDebugTracePrintf(
                (DukSVC_DEBUG_TRACE_STATUS_CHECK_ATTRIB |
                 (DukDEBUG_TRACE_MODE_TIMESTAMP_PREFIX_FLAG <<
                  DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_LSb)
                ),
                "ukSVC(%s) => STATUS = %Ks",
                svc_name_ntstring_addr__i,
                status_code__i);
    }

    return;
}
#endif /* defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) */

#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) && \
    defined(DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL)
/* ======================================================================== */
/*                      uk_appSVCDebugTraceIPCStatusPrint                      */
/* ======================================================================== */
void uk_appSVCDebugTraceIPCStatusPrint(
                TukSTATUS            status_code__i,
                TukNTCSTRING_ADDRESS svc_name_ntstring_addr__i) {
TukSTATUS demoted_status;
    demoted_status = status_code__i;
    if( (demoted_status == DukSTATUS_ERR_TIMEOUT) ||
        (demoted_status == DukSTATUS_ERR_PRECOND) ) {
        demoted_status &= ~DukSTATUS_NATURE_ERROR_FLAG;
        demoted_status |= DukSTATUS_NATURE_INFO_FLAG;
    }

    if ((demoted_status &
         DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) != 0) {
        ukDebugTracePrintf(
                (DukSVC_DEBUG_TRACE_STATUS_CHECK_ATTRIB |
                 (DukDEBUG_TRACE_MODE_TIMESTAMP_PREFIX_FLAG <<
                  DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_LSb)
                ),
                "ukSVC(%s) => STATUS = %Ks",
                svc_name_ntstring_addr__i,
                status_code__i);
    }

    return;
}
#endif /* defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef  UK_APP_INMODULE
#undef  UK_APP_C

#endif /* !defined(UKCORE) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

