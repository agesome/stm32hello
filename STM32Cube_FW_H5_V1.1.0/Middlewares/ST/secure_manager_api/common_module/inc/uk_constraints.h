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
 * @file          uk_constraints.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  C-Constants constraints sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the definitions of the C-Constants constraints
 *  relative to the implementation of the uKernel Target used.
 *
 * See main uKernel API file "uk.h" for details.
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note This file is a child file of the "uk.h" include file and SHALL BE
 *  included only by it.
 ******************************************************************************
 * @addtogroup       uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_CONSTRAINTS_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_constraints.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONSTRAINTS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONSTRAINTS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*             UKERNEL IMPLEMENTATION - C-CONSTANTS CONSTRAINTS             */
/* ######################################################################## */
/* Hereafter are defined the C-Constants specifying constraints (minimal and
 *  maximal values) of the uKernel Target used.
 *
 * NOTE: These constraints are relative to architecture and internal
 *  implementations choices, either coming from Platform and/or MCU
 *  limitations, or made in the framework of uKernel performances and/or
 *  resources optimizations.
 *
 * @implementation These C-Constants are defined at first (even before uKernel
 *  C-Type and C-Macros) as they are are needed for:
 *  - Definition of basic uKernel C-Type, C-Constants and C-Macros (e.g. limit
 *   values, maximal count of elements in array, ...).
 *  - Static compilation checks.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL IMPLEMENTATION CONSTRAINTS - UKAPP                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum count of ukApps supported by the
 *  uKernel Target implementation
 *
 * Definition of the C-Constant for the maximum count of ukApps (uKernel
 *  Application) supported by the uKernel Target implementation that can be
 *  present in a ukApps Bundle.
 */
#define DukCONSTRAINT_UKAPP_COUNT_MAX                                         \
            MukVAL_TYPED(TukCOUNT8, 64)

/**
 * @brief C-Constant defining the minimum size of the ukApp Data Volatile
 *  Shared uKernel Services Block required by the uKernel Target
 *  implementation.
 *
 * Definition of the C-Constant for the minimum size (in bytes) of the
 *  ukApp Data Volatile Shared uKernel Services Block (ukAppDVSUKSVC Data Block)
 *  of a ukApp required by the uKernel Target implementation.
 *
 * @implementation The size of this area is fixed during uKernel Target
 *  implementation. This value depends of various constraints as memory
 *  resources and/or performances optimizations, as well as limitations of
 *  the Platform and of the MCU.
 *  This value is always a multiple of 4, and on some MCU core, notably on
 *  ARMv7-M architecture, this value shall be a power of 2.
 *
 * @usage The uKernel Option
 *  DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE shall be
 *  higher or equal to this minimum size.
 */
#define DukCONSTRAINT_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE_MIN         \
            MukVAL_TYPED(TukLENGTH32, 64U)


/**
 * @brief C-Constant defining the maximum size of a ukApp Code Block.
 *
 * Definition of the C-Constant for the maximum size (in bytes) of a ukApp Code
 *  Block.
 *
 * @implementation The size of this area is fixed during uKernel Target
 *  implementation. This value depends of various constraints as memory
 *  resources and/or performances optimizations, as well as limitations of
 *  the Platform and of the MCU.
 *
 * @usage The field <MemoryRegionCodeSize> in ukApp Descriptor shall be lower
 *  or equal to this maximum size.
 */
#define DukCONSTRAINT_UKAPP_CODE_BLOCK_SIZE_MAX                               \
            MukVAL_TYPED(TukLENGTH32, 0x100000UL) /* 1Mbytes */


/**
 * @brief C-Constant defining the maximum size of a ukApp Data Volatile Block.
 *
 * Definition of the C-Constant for the maximum size (in bytes) of a ukApp Data
 *  Volatile Block.
 *
 * @implementation The size of this area is fixed during uKernel Target
 *  implementation. This value depends of various constraints as memory
 *  resources and/or performances optimizations, as well as limitations of
 *  the Platform and of the MCU.
 *
 * @usage The field <MemoryRegionDataVolatileSize> in ukApp Descriptor shall
 *  be lower or equal to this maximum size.
 */
#define DukCONSTRAINT_UKAPP_DATA_VOLATILE_BLOCK_SIZE_MAX                      \
            MukVAL_TYPED(TukLENGTH32, 0x100000UL) /* 1Mbytes */


/**
 * @brief C-Constant defining the maximum size of a ukApp Data Persistent Block.
 *
 * Definition of the C-Constant for the maximum size (in bytes) of a ukApp Data
 *  Persistent Block.
 *
 * @implementation The size of this area is fixed during uKernel Target
 *  implementation. This value depends of various constraints as memory
 *  resources and/or performances optimizations, as well as limitations of
 *  the Platform and of the MCU.
 *
 * @usage The field <MemoryRegionDataPersistentSize> in ukApp Descriptor shall
 *  be lower or equal to this maximum size.
 */
#define DukCONSTRAINT_UKAPP_DATA_PERSISTENT_BLOCK_SIZE_MAX                    \
            MukVAL_TYPED(TukLENGTH32, 0x100000UL) /* 1Mbytes */


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL IMPLEMENTATION CONSTRAINTS - UKPROC                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum count of ukProc supported by the
 *  uKernel Target implementation
 *
 * Definition of the C-Constant for the maximum count of ukProc (uKernel
 *  Process) present simultaneously, supported by the uKernel Target
 *  implementation.
 *
 * @implementation The virtual ukProc Idle used when uKernel Scheduler is
 *  entering in Idle is not counted in this maximum count.
 *
 * @usage The uKernel Option DukCONFIG_OPTION_UKPROC_COUNT_MAX SHALL BE lower
 *  than this maximum number.
 */
#define DukCONSTRAINT_UKPROC_COUNT_MAX                                        \
            MukVAL_TYPED(TukCOUNT8, 32)


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL IMPLEMENTATION CONSTRAINTS - IPC                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum number of uKernel Signals supported
 *   by the uKernel Target implementation
 *
 * Definition of the C-Constant for the maximum number of different uKernel
 *  Signals supported by the uKernel Target implementation.
 */
#define DukCONSTRAINT_SIGNAL_COUNT_MAX                                        \
            MukVAL_TYPED(TukCOUNT8, 32)



/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL IMPLEMENTATION CONSTRAINTS - SCHEDULING              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximal Scheduling Priority value supported
 *   by the uKernel Target implementation.
 *
 * Definition of the C-Constant for the maximal value for the Scheduling
 *  Priority (see TukSCHEDULING_PRIORITY) in the ukScheduler (uKernel
 *  Scheduler), supported by the uKernel Target implementation.
 *
 * @implementation The maximal Scheduling Priority value corresponds to the
 *  Lowest Scheduling Priority in the ukScheduler (i.e. the one scheduled in
 *  last place, with lowest precedence in the ukScheduler for electing a new
 *  Scheduled ukProc).
 *  The minimal Scheduling Priority value is fixed to null (0) and corresponds
 *  to the Highest Scheduling Priority (i.e. the one scheduled in first place,
 *  with highest precedence in the ukScheduler for electing a new Scheduled
 *  ukProc).
 *
 * @usage The uKernel Option DukCONFIG_OPTION_SCHEDULING_PRIORITY_MAX shall be
 *   lower than this maximum value.
 */
#define DukCONSTRAINT_SCHEDULING_PRIORITYMAX                                  \
            MukVAL_TYPED(TukSCHEDULING_PRIORITY, 31)



/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL IMPLEMENTATION CONSTRAINTS - PERIPHERAL IRQ              */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the maximum number of Peripheral IRQ registered
 *  by a ukApp supported by the uKernel Target implementation.
 *
 * Definition of the C-Constant for the maximum number of Peripheral IRQ
 *  (Peripheral Interrupt Request) registered by a ukApp supported by the
 *  uKernel Target implementation.
 *
 * @usage The uKernel Option DukCONFIG_OPTION_UKAPP_PIRQ_REGISTERED_COUNT_MAX
 *  shall be lower than this maximum number.
 */
#define DukCONSTRAINT_UKAPP_PIRQ_REGISTERED_COUNT_MAX                         \
            MukVAL_TYPED(TukCOUNT8, 32)


/**
 * @brief C-Constant defining the maximum number of registered Peripheral IRQ
 *   supported by the uKernel Target implementation.
 *
 * Definition of the C-Constant for the maximum number of registered Peripheral
 *  IRQ (Peripheral Interrupt Request) supported by the uKernel Target
 *  implementation.
 *
 * This number corresponds to the maximum number of PIRQ that can be registered
 *  at the same time by all the ukProcs Instance present.
 */
#define DukCONSTRAINT_PIRQ_REGISTERED_COUNT_MAX                               \
            MukVAL_TYPED(TukCOUNT8, 64)



/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL IMPLEMENTATION CONSTRAINTS - SHARED BUFFER              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum count of Shared Buffers supported
 *  by the uKernel Target implementation.
 *
 * Definition of the C-Constant for the maximum count of Shared Buffers
 *  supported by the uKernel Target implementation.
 *
 * @implementation The total count of Shared Buffers is obtained by adding the
 *  count of Shared Buffers defined in each ukApp present in the ukApps Bundle.
 *  The count of Shared Buffer in a ukApp is defined in the field
 *  <SharedBufferDescriptorCount> of its ukApp Descriptor.
 *
 * @usage The uKernel Option DukCONFIG_OPTION_SHAREDBUFFER_COUNT_MAX shall be
 *  lower than this maximum count.
 */
#define DukCONSTRAINT_SHAREDBUFFER_COUNT_MAX                                  \
            MukVAL_TYPED(TukCOUNT8, 254)



/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL IMPLEMENTATION CONSTRAINTS - MCU REGISTER             */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximal count of MCU Registers that can be
 *  accessed at a time supported by the uKernel Target implementation.
 *
 * Definition of the C-Constant of the maximal count of MCU Registers that can
 *  be accessed at a time by dedicated uKernel Privileged Services supported
 *  by the uKernel Target implementation.
 * This count corresponds to the count of entries MCU Register Access Entry
 *  (see TukMCUREGISTER_ACCESS_ENTRY) fitting in the <ServiceParameter.Input>
 *  or <ServiceParameter.Output> fields of a ukApp Data Volatile Shared uKernel
 *  Services Block (see GVukappBlockDataSharedUKSVC).
 *
 * @implementation This value is computed from the size of the ukApp Data
 *  Volatile Shared uKernel Services Block (see
 *  DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE).
 */
#define DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX                            \
            MukVAL_TYPED(TukCOUNT8,                                           \
                     ((sizeof(((TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC*)0) \
                                ->ServiceParameter.Output) -                  \
                       sizeof(TukCOUNT32))                                  / \
                      sizeof(TukMCUREGISTER_ACCESS_ENTRY)))


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL IMPLEMENTATION CONSTRAINTS - DMA STREAM INSTANCE         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum number of DMA Stream Instance
 *  supported by the uKernel Target implementation.
 *
 * Definition of the C-Constant for the maximum number of DMA Stream Instances
 *  supported by the uKernel Target implementation.
 *
 * @usage The uKernel Option DukCONFIG_OPTION_DMAS_INSTANCE_COUNT_MAX
 *  shall be lower than this maximum number.
 */
#define DukCONSTRAINT_DMAS_INSTANCE_COUNT_MAX                                 \
            MukVAL_TYPED(TukCOUNT8, 32)


/* //////////////////////////////////////////////////////////////////////// */
/*       UKERNEL IMPLEMENTATION CONSTRAINTS - UKERNEL IMAGE UPDATE          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximum number of Address Blocks composing
 *  the uKernel Image Update Storage.
 *
 * Definition of the C-Constant for the maximum number of composing the uKernel
 *  Image Update Storage supported by the uKernel Target implementation.
 *
 * @usage The uKernel Option
 *  DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT SHALL
 *  BE lower than this maximum number.
 */
#define DukCONSTRAINT_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT_MAX     \
            MukVAL_TYPED(TukCOUNT8, 4)


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONSTRAINTS_H_INSIDE
#endif /* !defined(UK_CONSTRAINTS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

