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
 * @file          uk_config_options.h
 * @brief         uKernel API - uKernel Options definitions.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 * This configuration file contains the uKernel Options exposed in the uKernel
 *  API for the uKernel Target used.
 * A uKernel Option is a constant value representing a uKernel internal
 *  parameter used during its compilation, and whose value is defining limits,
 *  constraints, or choices on the uKernel functionalities and behaviors.
 *
 * The purpose of having some of these uKernel Options be part of the uKernel
 *  API is that they may be of interest for:
 *  - ukApp code: they allow to adapt and fine tune the ukApp implementation
 *   by using the same C-Constant parameters definitions than the ones of the
 *   uKernel Target used.
 *  - ukApp configuration: they provide some constraints global to the uKernel
 *   System and to each ukApp. These constrains may be needed to fill
 *   consistently ukApp Descriptors (e.g. available resources consistent with
 *   what is needed by ukApps present in ukAppq Bundle).
 *
 * Example of uKernel Options:
 *  - Maximal length of ukProc NTString Name.
 *  - Maximal number of ukApps and ukProcs.
 *  - Limit for Scheduling Priority and maximal Scheduled Duration.
 *  - ...
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
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @implementation The uKernel Options definitions specific to given Platform
 *  elements are defined in separate files. The main entry configuration file
 *  for these definitions is the file "uk_config_options_hw_mcu_device.h",
 *  containing the master definitions relative to the MCU Device selected for
 *  the uKernel Target.
 *  This configuration file "uk_config_options_hw_mcu_device.h" is
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
 *
 * @implementation During uKernel compilation for a given uKernel Target
 *  <target>, the "uk_config_options.h" file is placed in the directory
 *  "ukernel_api/target/<target>/uk/include/config/".
 *
 * @usage The uKernel Options part of the uKernel API that are specific to a
 *  given Platform SHALL BE defined in Platform specific files under directory
 *  "ukernel_api/target/<target>/uk/include/config/hw/mcu/..." for a uKernel
 *  Target <target>.
 *
 * @usage This file SHALL BE included only after the "uk_config_features.h"
 *  include file.
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_CONFIG_OPTIONS_H)

/*__________________________________________________________________________*/
/* Enforces that the 'uk_config_features.h' file has already been included. */
#if !defined(UK_CONFIG_FEATURES_H)
 #error 'The "uk_config_options.h" include file shall be included only after the "uk_config_features.h" file'
#endif /* !defined(UK_CONFIG_FEATURES_H) */

/*__________________________________________________________________________*/
/* Enforces that the 'uk_config_hw_mcu_device.h' file has already been
 *  included. */
#if !defined(UK_CONFIG_FEATURES_H)
 #error 'The "uk_config_options.h" include file shall be included only after the "uk_config_hw_mcu_device.h" file'
#endif /* !defined(UK_CONFIG_FEATURES_H) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONFIG_OPTIONS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_OPTIONS_H_INSIDE


/* ######################################################################## */
/*                              UKERNEL OPTIONS                             */
/* ######################################################################## */
/* Hereafter are defined the uKernel Options (i.e. C-Constant values of uKernel
 *  configuration parameters) that are part of the uKernel API of the uKernel
 *  Target used.
 * Each of the uKernel Option is defined as a C-Constant value. The definition
 *  is casting the value with the C-Type associated to the nature of the
 *  uKernel Option, excepted when defining a number of supported elements (as
 *  then the value may be used for defining arrays or tables, and typed values
 *  are not supported by C-Compiler in such definitions).
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A uKernel Option named <ooo> is defined by associating its
 *  corresponding label DukCONFIG_OPTION_<ooo> to the wanted parameter value
 *  using the C-Preprocessor '#define'.
 * @implementation A specific file section below is reserved for the uKernel
 *  Debug Options.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 */



/* //////////////////////////////////////////////////////////////////////// */
/*                       UKERNEL OPTIONS - UKERNEL TIME                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the default uKernel SysTick
 *  period in us.
 *
 * Definition of the uKernel Option C-Constant for the default uKernel SysTick
 *  period value in microseconds (us).
 * The uKernel SysTick period is used as unit for all Scheduling Time Quantum
 *  used by the ukScheduler (uKernel Scheduler).
 *
 * @robustness To enforce uKernel internal consistency of time measurements (as
 *  well as for the ukApp), the uKernel SysTick period remains fixed during a
 *  whole uKernel Session.
 *  If the uKernel SysTick period is updated by a ukProc, it will be taken
 *  into account only upon the next uKernel Session.
 *
 * @warning The value given shall result in a valid configuration for the MCU
 *  Device used when combined with the MCU Clock Frequency defined by CPU
 *  Clock Index 0 (see DukCONFIG_OPTION_HW_MCU_CLOCK_PARAMETERS_TABLE). In
 *  case an invalid configuration is detected, the uKernel Initialization will
 *  fail with Fatal Error.
 *
 * @note The indicative supported range values given may be reduced due to
 *  hardware limitation of the MCU Device used in the Platform (see MCU
 *  documentation) and selected MCU Clocks supported by the uKernel.
 *
 * @implementation In case MCU Clocks are updated, the uKernel will perform
 *  the necessary internal adjustments to keep the period for the uKernel
 *  SysTick constant during a uKernel Session.
 *
 * @usage It is advised of not having a too long uKernel SysTick period value
 *  in order to keep efficient responsiveness between ukProcs. Thus this value
 *  SHOULD BE defined to the maximal acceptable response time when several
 *  ukProcs need to share concurrent executions.
 *
 * @usage This value is the default value used during first uKernel Session.
 *  It can be updated by a ukProc with appropriate credentials by using
 *  uKernel Privileged Services (the updated value being taking into account
 *  only for the following uKernel Sessions).
 *
 * Default value: 10000us (10ms)
 * Supported values: [500 ... 1000000].
 */
#define DukCONFIG_OPTION_UKERNEL_SYSTICK_PERIOD_DEFAULT_us                    \
            MukVAL_TYPED(TukTIME32_us, 10000UL) /* 10ms */



/* //////////////////////////////////////////////////////////////////////// */
/*                       UKERNEL OPTIONS - UKAPP SCANNING                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the interval between applications
 *  in flash.
 *
 * Definition of the uKernel Option C-Constant for the interval where to scan
 *  for applications for this given uKernel Target.
 *
 * At initialisation time, the ukApp Bundle Code area is scanned, looking for
 *  ukApp Descriptors. The normal interval to scan at is multiples of the
 *  required memory alignment for memory regions.
 * This interval can be reduced by defining this option.
 *
 * Default value: undefined.
 * Supported values:
 *  [DukCONSTRAINT_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE_MIN ...
 *                      2048].
 */
#define DukCONFIG_OPTION_UKAPP_SCANNING_INTERVAL                              \
            MukVAL_TYPED(TukLENGTH16, 2048U)


/* //////////////////////////////////////////////////////////////////////// */
/*                       UKERNEL OPTIONS - UKAPP RESOURCES                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the size of the ukApp Data
 *  Volatile Shared uKernel Services Block.
 *
 * Definition of the uKernel Option C-Constant for the size of the ukApp Data
 *  Volatile Shared uKernel Services Block (ukAppDVSUKSVC Data Block) for this
 *  given uKernel Target.
 *
 * The ukApp Data Volatile Shared uKernel Services Block is a continuous
 *  volatile memory area, sub-area of the ukApp Data Volatile Block, and placed
 *  at its very beginning.
 * This area is the sole where all the input and output parameters used
 *  upon the invocation of a uKernel Service by a ukApp can be placed.
 * This area is strictly private to the ukApp ((no access is allowed from other
 *  ukApp under any circumstances). Its contents is lost upon each Platform
 *  reset.
 * See TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC for more details on the
 *  structure of this area.
 *
 * @robustness It is the only memory area of the ukApp to which the uKernel
 *  can get access to (read / write) once ukProc execution has started. The
 *  uKernel core cannot have access (enforced by hardware restrictions) to the
 *  other data in the other sub-areas of the ukApp Data Volatile Block once
 *  ukProc execution has started (thus enforcing that an issue during uKernel
 *  execution will not in any case expose ukApp data).
 *
 * @warning On some MCU Core, notably on ARMv7-M architecture, this value
 *  shall be a power of 2.
 *
 * @implementation The size of this area CANNOT BE lower than
 *  DukCONSTRAINT_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE_MIN.
 *
 * @implementation The start address of this area is guaranteed to be aligned
 *  on a multiple of 8 (i.e. aligned on a 64-bit word).
 *  The size in bytes of this area SHALL ALWAYS be a multiple of 8.
 *
 * Default value: 64.
 * Supported values:
 *  [DukCONSTRAINT_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE_MIN ...
 *                      2048].
 */
#define DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE          \
            MukVAL_TYPED(TukLENGTH16, 80U)



/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL OPTIONS - UKAPP DESCRIPTOR                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum count of ukApps
 *  supported.
 *
 * Definition of the uKernel Option C-Constant of the maximum count of ukApps
 *  part of the ukApps Bundle supported by this uKernel Target.
 *
 * @implementation If more ukApps than this value are found in the ukApps
 *  Bundle, then it will be considered as a uKernel FATAL Error during uKernel
 *  Initialization.
 *
 * @implementation Each ukApp supported requires ~50 bytes of uKernel internal
 *  RAM.
 *
 * @implementation This number CANNOT BE higher than
 *  DukCONSTRAINT_UKAPP_COUNT_MAX.
 *
 * @implementation To optimize uKernel RAM memory consumption, this value
 *  should not be lower than the maximal supported count of ukProcs (see
 *  DukCONFIG_OPTION_UKPROC_COUNT_MAX). Else it will imply that some available
 *  uKernel internal slots for ukProc (and their associated memory resources)
 *  will never be used as only one ukProc Instance from a ukApp can be present
 *  at any moment.
 *
 * Default value: 8.
 * Supported values: [2 ... DukCONSTRAINT_UKAPP_COUNT_MAX].
 */
#define DukCONFIG_OPTION_UKAPP_COUNT_MAX                                      \
            MukVAL_TYPED(TukCOUNT8, 16U)

/**
 * @brief uKernel Option C-Constant defining the maximal length of the string
 *  containing the name of a ukApp.
 *
 * Definition of the uKernel Option C-Constant for the maximal length (in
 *  characters) of the Null Terminated String (NTString) containing the name
 *  of a ukApp defined in the field <NameNTString> of the ukApp Descriptor
 *  (see TukUKAPP_DESCRIPTOR and Dukapp_config_NAME_NTARRAY for more
 *  details).
 *
 * Default value: 31.
 * Supported values: [8 ... 128].
 */
#define DukCONFIG_OPTION_UKAPP_NAME_STRING_LENGTH_MAX                         \
            MukVAL_TYPED(TukLENGTH8, 31U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of other
 *  ukApps to which a ukApp is authorized to send IPC message.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  other ukApps referenced by their ASID to which a given ukApp can send IPC
 *  message.
 *
 * @note As a reminder, it is possible to use the special value
 *  DukUKAPP_ASID_ANY to authorize the sending of IPC message to all the other
 *  ukApps present in the ukApps Bundle. And thus this number should be set
 *  in regards of the ukApp that have specific restrictions (it is not needed
 *  to be equal to DukCONFIG_OPTION_UKPROC_COUNT_MAX).
 *
 * @usage This value is used to define statically the length of the C-Array
 *  field <IPCSendToASIDAuthorizedList> in ukApp Descriptor (see
 *  TukUKAPP_DESCRIPTOR).
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_UKAPP_ADMINISTRATION_FINE is supported.
 *
 * Default value: 8.
 * Supported values: [2 ... 32].
 */
#define DukCONFIG_OPTION_UKAPP_IPC_SEND_TO_COUNT_MAX                          \
            MukVAL_TYPED(TukCOUNT8, 8U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of PIRQs that
 *  can be registered by a ukApp.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  PIRQ (Peripheral IRQ) that can be registered by a ukApp.
 *
 * @implementation This value SHALL BE be lower than
 *  DukCONSTRAINT_UKAPP_PIRQ_REGISTERED_COUNT_MAX.
 *
 * @implementation The higher this number is, the more the internal memory these
 *  uKernel needs for the management of PIRQs.
 *  Each PIRQ registration context requires ~20 bytes of uKernel RAM memory
 *  (whatever used or not).
 *
 * @usage This value is used to define statically the length of the C-Array
 *  <PIRQMCUIndexAuthorizedList> in ukApp Descriptor (see
 *  TukUKAPP_DESCRIPTOR).
 *
 * @usage This maximal number corresponds also to the maximum number of PIRQs
 *  that can be registered at a given time by a ukProc.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_PERIPHERAL_IRQ is supported.
 *
 * Default value: 4.
 * Supported values: [1 ... DukCONSTRAINT_UKAPP_PIRQ_REGISTERED_COUNT_MAX].
 */
#define DukCONFIG_OPTION_UKAPP_PIRQ_REGISTERED_COUNT_MAX                      \
            MukVAL_TYPED(TukCOUNT8, 12U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of Shared
 *  Buffer Descriptors per ukApp.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  Shared Buffer Descriptors that can be defined per ukApp (and thus for
 *  which instantiated ukProc will be the owner).
 *
 * @usage This value is used to define statically the length of the C-Array
 *  <SharedBufferDescriptorList> in ukApp Descriptor (see
 *  TukUKAPP_DESCRIPTOR).
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_SHARED_BUFFERS is supported.
 *
 * Default value: 8.
 * Supported values: [1 ... 32].
 */
#define DukCONFIG_OPTION_UKAPP_SHAREDBUFFER_DESCRIPTOR_COUNT_MAX              \
            MukVAL_TYPED(TukCOUNT8, 8U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of extra
 *  Address Blocks defined in ukApp Descriptors.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  extra Address Block defined in a ukApp Descriptor.
 *
 * @note This number does not encompass the Address Blocks defined as Shared
 *  Buffer (i.e. the maximal number of Shared Buffer has to be added to this
 *  value to have the maximal number of Address Block that are owned by the
 *  ukProc instantiated from the ukApp).
 *
 * @usage The mapping of these defined Address Blocks can be managed by the
 *  ukProc during its execution in order to allow it to access their contents.
 *
 * @usage This value is used to define statically the length of the C-Array
 *  <AddressBlockExtraDescriptorList> in ukApp Descriptor (see
 *  TukUKAPP_DESCRIPTOR).
 *
 * Default value: 8.
 * Supported values: [1 ... 32].
 */
#define DukCONFIG_OPTION_UKAPP_ADDRESSBLOCK_EXTRA_DESCRIPTOR_COUNT_MAX        \
            MukVAL_TYPED(TukCOUNT8, 16U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of MCU
 *  Register Descriptors defined in ukApp Descriptors.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  MCU Register Descriptors defined in a ukApp Descriptor.
 *
 * @usage This value is used to define statically the length of the C-Array
 *  <MCURegisterDescriptorList> in ukApp Descriptor (see
 *  TukUKAPP_DESCRIPTOR).
 *
 * Default value: 4.
 * Supported values: [1 ... 32].
 */
#define DukCONFIG_OPTION_UKAPP_MCUREGISTER_DESCRIPTOR_COUNT_MAX               \
            MukVAL_TYPED(TukCOUNT8, 32U)

/**
 * @brief uKernel Option C-Constant defining the maximal number of DMA Stream
 *  allowable in ukApp Descriptors.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of DMA
 *  Streams allowable in a ukApp Descriptor.
 *
 * @note As several DMA Stream Descriptors can reference (in the same ukApp)
 *  the same DMA Stream Engine, this value is independent of
 *  DukDMAS_ENGINE_COUNT.
 *
 * @usage This value is used to statically define the length of the C-Array
 *  <DMAStreamDescriptorList> in ukApp Descriptor (see TukUKAPP_DESCRIPTOR).
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_MCU_DMA is supported.
 *
 * Default value: 4.
 * Supported values: [1 ... 16].
 */
#define DukCONFIG_OPTION_UKAPP_DMAS_DESCRIPTOR_COUNT_MAX                      \
            MukVAL_TYPED(TukCOUNT8, 4U)



/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL OPTIONS - UKPROC MANAGEMENT                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum count of ukProcs
 *  supported.
 *
 * Definition of the uKernel Option C-Constant for the maximum count of
 *  ukProcs present at any moment during a uKernel Session (i.e. the maximal
 *  count of ukProcs that may be concurrently executed at any moment).
 *
 * @note This maximum count can be lower than the maximum count of ukApps.
 *  It then implies that all the ukApps can not be instantiated as ukProc at
 *  the same time. This can be useful when some ukApps need to run only upon
 *  specific events: it will then be possible to exit a ukProc (it implies
 *  losing its volatile state), and then use the just freed ukProc slot to
 *  instantiate a new ukProc from another ukApp.
 *
 * @implementation This maximum number CANNOT BE higher than the value
 *  DukCONSTRAINT_UKPROC_COUNT_MAX.
 *
 * @implementation The virtual ukProc Idle used when uKernel Scheduler is
 *  entering in Idle is not counted in this maximum count.
 *
 * @implementation Each ukProc supported requires ~200 bytes of uKernel RAM
 *  memory.
 *
 * Default value: 8.
 * Supported values: [2 ... DukCONSTRAINT_UKPROC_COUNT_MAX].
 */
#define DukCONFIG_OPTION_UKPROC_COUNT_MAX                                     \
            MukVAL_TYPED(TukCOUNT8, 16U)


/* //////////////////////////////////////////////////////////////////////// */
/*                        UKERNEL OPTIONS - SCHEDULING                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximal Scheduling Priority
 *  value.
 *
 * Definition of the uKernel Option C-Constant for the maximal value for the
 *  Scheduling Priority (see TukSCHEDULING_PRIORITY) in the ukScheduler
 *  (uKernel Scheduler).
 *
 * @implementation This maximal Scheduling Priority corresponds to the Lowest
 *  Scheduling Priority in the ukScheduler (i.e. the one that is scheduled in
 *  last place, with lowest precedence in the ukScheduler for electing a new
 *  Scheduled ukProc).
 *  The Highest Scheduling Priority (i.e. the one that is scheduled in first
 *  place, with highest precedence in the ukScheduler for electing a new
 *  Scheduled ukProc) has the null(0) Scheduling Priority value.
 *
 * @implementation The maximal Scheduling Priority CANNOT BE higher than
 *  DukCONSTRAINT_SCHEDULING_PRIORITYMAX.
 *
 * Default value: 7
 * Supported values: [1 ... DukCONSTRAINT_SCHEDULING_PRIORITYMAX].
 */
#define DukCONFIG_OPTION_SCHEDULING_PRIORITY_MAX                              \
          MukVAL_TYPED(TukSCHEDULING_PRIORITY, 7U)


/**
 * @brief uKernel Option C-Constant defining the Scheduling Time Quantum for a
 *  ukProc Cleanup.
 *
 * Definition of the uKernel Option C-Constant for the Scheduling Time Quantum
 *  for a ukProc Cleanup, in uKernel Systicks unit.
 * This Scheduling Time Quantum is set as the Scheduling Time Quantum Allocated
 *  during a ukProc Cleanup. It corresponds to the maximal execution time
 *  allowed for a ukProc to perform its ukProc Cleanup (if this time is
 *  exceeded the execution of the ukProc is stopped, the ukProc Termination
 *  process is finalized and the ukProc Cleanup is set as unsuccessful).
 *
 * @implementation This Scheduling Time Quantum for a ukProc Cleanup is managed
 *  similarly as during normal scheduling of a ukProc. When a ukProc starts its
 *  ukProc Cleanup, it is entering in Scheduling ukProc State Interrupt: its
 *  Scheduling Time Quantum Remaining is set to this C-Constant value, and
 *  then decremented upon each uKernel Systick only when the ukProc is the
 *  Scheduled ukProc. If the Scheduling Time Quantum Remaining reaches null(0)
 *  then the Scheduling Time Quantum is exhausted: the execution of the ukApp
 *  Entry Point ukappCleanup() is stopped, and the ukProc Termination process
 *  is finalized, with the ukProc Cleanup considered as unsuccessful.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported.
 *
 * Default value: 20
 * Supported values: [2 ... 127].
 */
#define DukCONFIG_OPTION_SCHEDULING_TIME_QUANTUM_UKPROC_CLEANUP_systick       \
            MukVAL_TYPED(TukSCHEDULING_TIME_QUANTUM_systick, 20U)


/**
 * @brief uKernel Option C-Constant defining the maximal Scheduled Duration In
 *  a Row for ukScheduler Idle mode.
 *
 * Definition of the uKernel Option C-Constant for the maximal Scheduling
 *  Duration In a Row, in uKernel Systick unit, allowed for the ukScheduler
 *  (uKernel Scheduler) Idle mode (i.e. the maximal time in a row where it
 *  remains active without being preempted by an Instantiated ukProc).
 *
 * @warning If the ukScheduler Idle mode remains active in a row during a
 *  count of uKernel Systicks greater than this maximal Scheduled Duration In a
 *  Row value, then it triggers a uKernel Session End with Status Code
 *  DukSTATUS_ERR_TIMEOUT.
 *
 * @implementation The ukScheduler Idle mode becomes active when there is no
 *  schedulable ukProc: the ukScheduler elects then as Scheduled uKproc a
 *  virtual ukProc, the ukProc Idle.
 *  The ukScheduler Idle mode remains active until at least an Instantiated
 *  ukProc is marked again as schedulable (one of them to being then elected
 *  as the new Scheduled ukProc) due to:
 *  - The Yield Delay of at least one ukProc in Scheduling ukProc State
 *   Blocked-Yield is over.
 *  - The Timeout of at least one ukProc in Scheduling ukProc State Blocked-IPC
 *   is over.
 *  - The occurrence of an external event (e.g. triggering of a Peripheral IRQ)
 *   expected by at least one ukProc in Scheduling ukProc State Blocked-IPC or
 *   Blocked-FLASH.
 *
 * @implementation If this uKernel Option is set to null(0), then there is no
 *  maximal Scheduled Duration In a Row for ukScheduler Idle mode (it can
 *  remains active indefinitely).
 *
 * @usage This maximal Scheduled Duration In a Row can be seen as a kind of
 *  Watchdog, which can be used to enforce that some events expected by
 *  ukProc(s) in Scheduling ukProc State Blocked occur regularly with a period
 *  not exceeding the maximal time defined by this uKernel Option.
 *
 * Default value: 1000
 * Supported values: { 0, [2 ... 100000] }.
 */
#define DukCONFIG_OPTION_SCHEDULER_IDLE_DURATION_INAROW_MAX_systick           \
            MukVAL_TYPED(TukTIME32_tick, 1000U)


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL OPTIONS - SHARED BUFFERS                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum count of Shared
 *  Buffers supported by the uKernel.
 *
 * Definition of the uKernel Option C-Constant for the maximum count of
 *  Shared Buffers supported by the uKernel.
 *
 * The total count of Shared Buffers is obtained by adding the count of Shared
 *  Buffers defined in each ukApp present in the ukApps Bundle.
 *  The count of Shared Buffer in a ukApp is defined in the field
 *  <SharedBufferDescriptorCount> of its ukApp Descriptor.
 *
 * @robustness The uKernel Initialization checks that this maximum value
 *  is consistent (i.e. superior) with the total count of Shared Buffers.
 *  Else the uKernel Initialization will fail.
 *  The purpose of this check is to enforce that no race condition may occur
 *  due to lack of resources during ukProc execution.
 *
 * @implementation The maximal number of Shared Buffers that can be defined per
 *  ukApp is defined independently by
 *  DukCONFIG_OPTION_UKAPP_SHAREDBUFFER_DESCRIPTOR_COUNT_MAX.
 *
 * @implementation As all the ukApps are not needing to use Shared Buffers,
 *  this value allows to minimize the uKernel RAM memory consumption needed
 *  for managing internally the Shared Buffers.
 *  Each Shared Buffer supported requires ~20 bytes of uKernel RAM memory.
 *
 * @implementation The maximal number of Shared Buffer CANNOT BE higher than
 *  DukCONSTRAINT_SHAREDBUFFER_COUNT_MAX.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_SHARED_BUFFERS is supported.
 *
 * Default value is: 16.
 * Supported values: [1 ... DukCONSTRAINT_SHAREDBUFFER_COUNT_MAX].
 */
#define DukCONFIG_OPTION_SHAREDBUFFER_COUNT_MAX                               \
            MukVAL_TYPED(TukCOUNT8, 16U)


/**
 * @brief uKernel Option C-Constant defining the maximal number of different
 *  ukProcs to which a Shared Buffer can be transferred to.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  different ukProcs to which a Shared Buffer can be transferred to.
 *
 * @note There is no limitation on the number of times that two ukProc
 *  can exchange each other a Shared Buffer. Only the number of different
 *  ukProcs to which a Shared Buffer can be transferred to is limited.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_SHARED_BUFFERS is supported.
 *
 * Default value: 2.
 * Supported values: [1 ... 7].
 */
#define DukCONFIG_OPTION_SHAREDBUFFER_TRANSFER_DIFFERENT_UKPROC_COUNT_MAX     \
            MukVAL_TYPED(TukCOUNT8, 2U)


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL OPTIONS - PERIPHERAL IRQ                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximal number of Peripheral
 *  IRQs that can be supported.
 *
 * Definition of the uKernel Option C-Constant for the maximal number of
 *  Peripheral IRQs that can be supported. This constant is used to set the
 *  size of PIRQ notifications.
 *
 * @note This constant should be at least equal to the platform number of IRQs
 *  defined by the constant DukPIRQ_IDX_MAX.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_PERIPHERAL_IRQ is supported.
 *
 * Default value: -
 * Supported values: [1 ... 496]
 */
#define DukCONFIG_OPTION_PIRQ_SUPPORTED_COUNT_MAX                             \
            MukVAL_TYPED(TukCOUNT32, 130U)


/* //////////////////////////////////////////////////////////////////////// */
/*                       UKERNEL OPTIONS - DMA STREAM                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum number of
 *  DMA Stream Instances supported by the uKernel.
 *
 * Definition of the uKernel Option C-Constant for the maximum number of
 *  DMA Stream Instances supported by the uKernel.
 *
 * @note This value also corresponds to the maximum number of DMA Stream
 *  Instances when summing all DMA Stream Instances across all ukApps at any
 *  time.
 *
 * @note If this value is higher than the number of DMA Stream Engines that
 *  are available at hardware level in the selected MCU Device (see
 *  DukDMAS_ENGINE_COUNT), then some of the DMA Stream Instances will stay
 *  unused.
 *
 * @implementation As not all ukApps need to use DMA Streams, this option
 *  allows reducing the uKernel RAM memory consumption needed for managing the
 *  DMA Stream Instances. Each DMA Stream Instance supported requires ~24 bytes
 *  of uKernel RAM memory.
 *
 * @implementation The maximum number of DMA Stream Instances CANNOT BE higher
 *  than DukCONSTRAINT_DMAS_INSTANCE_COUNT_MAX.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_MCU_DMA is supported.
 *
 * Default value is: 8.
 * Supported values: [1 ... DukCONSTRAINT_DMAS_INSTANCE_COUNT_MAX].
 */
#define DukCONFIG_OPTION_DMAS_INSTANCE_COUNT_MAX                              \
            MukVAL_TYPED(TukCOUNT8, 16U)



/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL OPTIONS - UKERNEL IMAGE UPDATE                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum number of
 *  consecutive uKernel Sessions allowed for validating a uKernel Image part
 *  updated.
 *
 * Definition of the uKernel Option C-Constant for the maximum number of
 *  consecutive uKernel Sessions allowed for validating (see uKernel Image
 *  Update Operation DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE) a uKernel
 *  Image part updated.
 *
 * @implementation uKernel Sessions are considered as consecutive when there is
 *  only MCU Warm Reset (i.e. no MCU Power Off) between them.
 *
 * @implementation If this maximum number of consecutive uKernel Sessions is
 *  reached without the uKernel Image part updated being validated, then the
 *  previous version kept in uKernel Image Update Storage is used to roll-back
 *  the uKernel Image part.
 *
 * @usage This uKernel Option is significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported.
 *
 * Default value is: 4.
 * Supported values: [1 ... 64]
 */
#define DukCONFIG_OPTION_UKERNEL_IMAGE_UPDATE_VALIDATE_SESSION_COUNT_MAX      \
            MukVAL_TYPED(TukCOUNT8, 4U)



/* ######################################################################## */
/*                         UKERNEL OPTIONS - DEBUG                          */
/* ######################################################################## */
/* Hereafter are defined the uKernel Debug Options (i.e. C-Constant values of
 *  uKernel configuration debug parameters) that are part of the uKernel API
 *  of the uKernel Target used and of the debug functionalities offered by the
 *  uKernel.
 * These definitions are similar to the uKernel Options above (and can also be
 *  used by the uKernel Core and ukApp implementations), but care has to be
 *  taken by that they are NOT defined for a uKernel Target that is a
 *  Production Target.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Target to be taken into account.
 * @implementation A uKernel Debug Option named <ooo> is defined by associating
 *  its corresponding label DukCONFIG_OPTION_DEBUG_<ooo> to the wanted
 *  parameter value using the C-Preprocessor '#define'.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Target used.
 */

/* ROBUSTNESS: None of the uKernel Debug Features defined hereafter are
 *  supported if the uKernel compilation is aiming a Production Target. */
#if !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)


/* //////////////////////////////////////////////////////////////////////// */
/*                      UKERNEL OPTIONS - DEBUG - DEBUG TRACE               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the maximum length (in
 *  characters) per print of a Debug Trace.
 *
 * Definition of the uKernel Option C-Constant for the maximum length (in
 *  characters) per print of a Debug Trace.
 * If more characters than this length is printed on Debug Trace during a
 *  print, subsequent characters are silently discarded, and a special
 *  character DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is set as last
 *  character printed.
 *
 * @implementation Additional formatting templates may be added by the uKernel
 *  (header, newline prefix) to the Debug Trace. These formatting templates
 *  are not counted in the computed length per print.
 *
 * @implementation This maximum length is not applying when printing a Buffer
 *  contents.
 *
 * @implementation This uKernel Option is significant only if Debug Trace is
 *  supported (see uKernel Feature SxxxCONFIG_FEATURE_DEBUG_TRACE_XXX).
 *
 * Default value is: 2048.
 * Supported values: [96 ... 8192].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_LENGTH_PER_PRINT_MAX                     \
            MukVAL_TYPED(TukLENGTH16, 2048U)

/**
 * @brief uKernel Option C-Constant defining the maximum length allowed for a
 *  Null Terminated String used in Debug Trace.
 *
 *  Definition of the uKernel Option C-Constant for the maximum length allowed
 *  for Null Terminated String (NTString) used in Debug Trace.
 * If the length of a NTString used in Debug Trace is strictly greater than
 *  this maximal length, the NTString is not printed, and the special character
 *  DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED is printed instead.
 *
 * @usage The definition of this C-Constant allows to detect erroneous Debug
 *  Trace String, and react accordingly by limiting unexpected dump of memory.
 *
 * Default value: 512.
 * Supported values: [128 ... 4096].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX                      \
    MukVAL_TYPED(TukLENGTH16, 512U)

/**
 * @brief uKernel Option C-Constant defining the maximum length of a Buffer
 *  printed on a Debug Trace.
 *
 * Definition of the uKernel Option C-Constant for the maximum length (in
 *  bytes) of a Buffer printed on a Debug Trace.
 * If the length of a Buffer printed on a Debug Trace is strictly greater than
 *  this maximal length, the Buffer is not printed, and the special character
 *  DukDEBUG_TRACE_ERROR_CHAR_BUFFER_LENGTH_EXCEEDED is printed instead.
 *
 * @implementation This uKernel Option is significant only if Debug Trace is
 *  supported (see uKernel Feature SxxxCONFIG_FEATURE_DEBUG_TRACE_XXX).
 *
 * Default value is: 1024.
 * Supported values: [256 ... 4096].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_BUFFER_PRINTED_LENGTH_MAX                \
            MukVAL_TYPED(TukLENGTH16, 1024U)

/**
 * @brief uKernel Option C-Constant defining the Column at which automatic
 *  wrapping is done when printing Debug Trace.
 *
 * Definition of the uKernel Option C-Constant for the column at which
 *  automatic wrapping is done when printing Debug Trace (the same wrapping
 *  applies on all enabled Debug Trace Interface).
 * When printing Debug Trace, each time the given column is reached, a carriage
 *  return is inserted automatically in order to print the subsequent
 *  characters on the next line.
 *
 * @note See SukCONFIG_FEATURE_DEBUG_TRACE_NEWLINE_LF_ONLY for the type of
 *  carriage return used.
 *
 * @usage If this uKernel Option is defined with null value, then the automatic
 *  wrapping is disabled.
 *
 * @implementation This uKernel Option is significant only if Debug Trace is
 *  supported (see uKernel Feature SxxxCONFIG_FEATURE_DEBUG_TRACE_XXX).
 *
 * Default value is: 120.
 * Supported values: { 0 }, [40 ... 320].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_LINE_COLUMN_WRAP                         \
            MukVAL_TYPED(TukCOUNT16, 120U)


/**
 * @brief uKernel Option C-Constant defining the uKernel Debug Trace Filter
 *  when printing uKernel Debug Trace during uKernel Initialization.
 *
 * Definition of the uKernel Option C-Constant for the uKernel Debug Trace
 *  Filter when printing uKernel Debug Trace during uKernel Initialization.
 *
 * The fields composing the uKernel Debug Trace Filter (see
 *  TukDEBUG_TRACE_ATTRIBUTES) are used as follows:
 *  - <Nature>: Upon a printing request for a uKernel Debug Trace, only the
 *  requests with a Nature flag (provided in the associated Debug Trace
 *  Attributes parameter) that is also set in this <Nature> field will be
 *  printed (others requests are silently discarded).
 *  - <Verbosity>: Upon a printing request for a uKernel Debug Trace, only
 *  the requests with a Verbosity level (provided in the associated Debug Trace
 *  Attributes parameter) that is lower or equal than this <Verbosity> field
 *  will be printed (others requests are silently discarded).
 *
 * @robustness If the defined uKernel Debug Trace Filter is not valid, then no
 *  uKernel Debug Trace is printed at all during uKernel Initialization.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_TRACE_UKERNEL is supported.
 *
 * @usage To allow all the supported uKernel Debug Trace Verbosity levels to be
 *  printed, the value DukDEBUG_TRACE_VERBOSITY_MAX has to be set for the
 *  <Verbosity> field. To fully disable the printing, the value
 *  DukDEBUG_TRACE_VERBOSITY_DISABLED has to be set.
 *
 * @usage To allow all the supported uKernel Debug Trace Natures to be printed,
 *  the value DukDEBUG_TRACE_NATURE_MASK value has to be set for the <Nature>
 *  field. To fully disable the printing, the null (0) value has to be set.
 *
 * @usage This uKernel Debug Trace Filter is used only during uKernel
 *  Initialization. The one used after uKernel Initialization is defined in
 *  uKernel Option DukCONFIG_OPTION_DEBUG_TRACE_UKERNEL_FILTER_AFTER_INIT.
 *
 * Default value is:
 *  - <Nature>: DukDEBUG_TRACE_NATURE_VALID_MASK
 *  - <Verbosity>: DukDEBUG_TRACE_VERBOSITY_FINEST
 * Supported values:
 *  - <Nature>: ORed { DukDEBUG_TRACE_NATURE_xxxx_FLAG }.
 *  - <Mode>: null(0).
 *  - <Verbosity>: [0 ... DukDEBUG_TRACE_VERBOSITY_MAX].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_UKERNEL_FILTER_WHILE_INIT                \
        MukVAL_TYPED(TukDEBUG_TRACE_ATTRIBUTES,                               \
                     MukDEBUG_TRACE_ATTRIBUTES_BUILD(                         \
                        (                                                     \
                            DukDEBUG_TRACE_NATURE_INFO_FLAG                 | \
                            DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG           | \
                            DukDEBUG_TRACE_NATURE_CONFIG_FLAG               | \
                            DukDEBUG_TRACE_NATURE_STAT_FLAG                 | \
                            DukDEBUG_TRACE_NATURE_WARNING_FLAG              | \
                            DukDEBUG_TRACE_NATURE_ERROR_FLAG                | \
                            DukDEBUG_TRACE_NATURE_ACTIVITY_FLAG             | \
                            0                                                 \
                        ),                                                    \
                        0U,                                                   \
                        DukDEBUG_TRACE_VERBOSITY_FINEST                       \
                                                    )                         \
                    )


/**
 * @brief uKernel Option C-Constant defining the uKernel Debug Trace Filter
 *  when printing uKernel Debug Trace after uKernel Initialization.
 *
 * Definition of the uKernel Option C-Constant for the uKernel Debug Trace
 *  Filter when printing uKernel Debug Trace after uKernel Initialization.
 *
 * This uKernel Debug Trace Filter is built and used similarly to the one
 *  used during uKernel Initialization: for more details see
 *  DukCONFIG_OPTION_DEBUG_TRACE_UKERNEL_FILTER_WHILE_INIT.
 *
 * @robustness If the defined uKernel Debug Trace Filter is not valid, then no
 *  uKernel Debug Trace is printed at all after uKernel Initialization.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_TRACE_UKERNEL is supported.
 *
 * @usage This uKernel Debug Trace Filter is used only after uKernel
 *  Initialization. The one used during uKernel Initialization is defined in
 *  uKernel Option DukCONFIG_OPTION_DEBUG_TRACE_UKERNEL_FILTER_WHILE_INIT.
 *
 * Default value is:
 *  - <Nature>: DukDEBUG_TRACE_NATURE_VALID_MASK
 *  - <Verbosity>: DukDEBUG_TRACE_VERBOSITY_FINEST
 * Supported values:
 *  - <Nature>: ORed { DukDEBUG_TRACE_NATURE_xxxx_FLAG }.
 *  - <Mode>: null(0).
 *  - <Verbosity>: [0 ... DukDEBUG_TRACE_VERBOSITY_MAX].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_UKERNEL_FILTER_AFTER_INIT                \
        MukVAL_TYPED(TukDEBUG_TRACE_ATTRIBUTES,                               \
                     MukDEBUG_TRACE_ATTRIBUTES_BUILD(                         \
                        (                                                     \
                            DukDEBUG_TRACE_NATURE_INFO_FLAG                 | \
                            DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG           | \
                            DukDEBUG_TRACE_NATURE_CONFIG_FLAG               | \
                            /*DukDEBUG_TRACE_NATURE_STAT_FLAG             |*/ \
                            DukDEBUG_TRACE_NATURE_WARNING_FLAG              | \
                            DukDEBUG_TRACE_NATURE_ERROR_FLAG                | \
                            DukDEBUG_TRACE_NATURE_ACTIVITY_FLAG             | \
                            0U                                                \
                        ),                                                    \
                        0U,                                                   \
                        DukDEBUG_TRACE_VERBOSITY_FINEST                       \
                                                    )                         \
                    )



/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL OPTIONS - DEBUG - DEBUG TRACE INTERFACES         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Option C-Constant defining the UART Device Configuration
 *  to use for Debug Trace UART Interface.
 *
 * Definition of the uKernel Option C-Constant for the UART Device
 *  Configuration to use for Debug Trace UART Interface (see
 *  DukdevUART_CONFIG_xxxx C-Constant for supported configuration).
 *
 * @implementation Some MCU family may not allow all the configuration defined
 *  by DukdevUART_CONFIG_xxxx C-Constants. If the configuration is not
 *  supported, the Debug Trace UART Interface will be disabled.
 *
 * @implementation This uKernel Option is significant only if UART Debug Trace
 *  Interface is supported (see uKernel Feature
 *  SxxxCONFIG_FEATURE_DEBUG_TRACE_XXX_INTERFACE_UART).
 *
 * @usage The configuration part for the speed of the UART shall not be
 *  included in this definition, as it is added afterwards to this
 *  configuration by using the uKernel Option
 *  DukCONFIG_OPTION_DEBUG_TRACE_INTERFACE_UART_BAUDRATE.
 *
 * Default value is:
 *  (DukdevUART_CONFIG_DATA_PARITY_NONE     |
 *   DukdevUART_CONFIG_MODE_SEND_RECEIVE    |
 *   DukdevUART_CONFIG_STOP_BITSIZE_1)
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_INTERFACE_UART_CONFIG                    \
        MukVAL_TYPED(TukdevUART_CONFIG,                                       \
            DukdevUART_CONFIG_DATA_PARITY_NONE                              | \
            DukdevUART_CONFIG_MODE_SEND_RECEIVE                             | \
            DukdevUART_CONFIG_STOP_BITSIZE_1                                | \
            0U)


/**
 * @brief uKernel Option C-Constant defining the Baudrate of the UART used as
 *  Debug Trace Interface.
 *
 * Definition of the uKernel Option C-Constant for the baudrate of the UART
 *  used as Debug Trace Interface for sending uKernel and/or ukProc Debug
 *  Traces.
 *
 * @implementation This uKernel Option is significant only if UART Debug Trace
 *  Interface is supported (see uKernel Feature
 *  SxxxCONFIG_FEATURE_DEBUG_TRACE_XXX_INTERFACE_UART).
 *
 * Default value is: 230400.
 * Supported values: [9600, 38400, 115200, 230400, 460800].
 */
#define DukCONFIG_OPTION_DEBUG_TRACE_INTERFACE_UART_BAUDRATE                  \
            MukVAL_TYPED(TukBAUDRATE, 115200U)


/* //////////////////////////////////////////////////////////////////////// */
/*                      UKERNEL OPTIONS - DEBUG - LED                       */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_LED)


/**
 * @brief uKernel Option C-Constant defining the Debug LED Blinking Period in
 *  microseconds (us).
 *
 * Definition of the uKernel Option C-Constant of the Debug LED Blinking
 *  period in microseconds (us).
 * Each time the Debug LED Blinking period is over, the blinking counter is
 *  incremented and leads to using the next bit the Debug LED Pattern of each
 *  Debug LED to its the ON/OFF state (see TukDEBUG_LED_PATTERN for more
 *  details).
 *
 * @implementation The Debug LED Blinking Period is checked to be over only
 *  upon a uKernel Systick. The Debug LED Blinking Period should thus be a
 *  multiple a of the uKernel Systick period to be accurate.
 *
 * Default value: 50000 (50ms).
 * Supported values: [1000 ... 200000].
 */
#define DukCONFIG_OPTION_DEBUG_LED_BLINKING_PERIOD_us                         \
            MukVAL_TYPED(TukTIME32_us,                                        \
                         50000 /* 50ms */                                     \
                        )


/**
 * @brief uKernel Option C-Constant defining the Debug LED Index used for
 *  reporting uKernel state.
 *
 * Definition of the uKernel Option C-Constant of the Debug LED Index used
 *  for reporting uKernel state.
 *
 * The following Debug LED Pattern are used for reporting the uKernel state:
 *  - DukDEBUG_LED_PATTERN_ON: uKernel Initialization.
 *  - DukDEBUG_LED_PATTERN_BLINK_MEDIUM: Nominal (heart beat indicating no
 *   error).
 */
#define DukCONFIG_OPTION_DEBUG_LED_INDEX_UKERNEL_STATE                        \
            MukVAL_TYPED(TukDEBUG_LED_IDX, 0U)


/**
 * @brief uKernel Option C-Constant defining the Debug LED Index used for
 *  reporting an internal uKernel Error.
 *
 * Definition of the uKernel Option C-Constant of the Debug LED Index used
 *  for reporting an internal uKernel Error.
 *
 * The following Debug LED Pattern are used during time given in parenthesis
 *  for reporting the uKernel Error:
 *  - DukDEBUG_LED_PATTERN_BLINK_FAST(2s): ukApps Bundle Initialization Error
 *   (non fatal).
 *  - DukDEBUG_LED_PATTERN_FLASH_LONG(2s): uKernel Debug Functionalities Error
 *   (non fatal).
 *  - DukDEBUG_LED_PATTERN_ON: uKernel Fatal Error.
 */
#define DukCONFIG_OPTION_DEBUG_LED_INDEX_UKERNEL_ERROR                        \
            MukVAL_TYPED(TukDEBUG_LED_IDX, 1U)


/**
 * @brief uKernel Option C-Constant defining the Debug LED Index used for
 *  reporting that a uKernel Image Update Operation is ongoing.
 *
 * Definition of the uKernel Option C-Constant of the Debug LED Index used
 *  for reporting that a uKernel Image Update Operation is ongoing
 *
 * The following Debug LED Pattern are used during time given in parenthesis
 *  for reporting the uKernel Image Update Operation:
 *  - DukDEBUG_LED_PATTERN_BLINK_FAST(2s): Transfers in FLASH memory during a
 *   uKernel Image Update Operation for uKernel Core replacement.
 *  - DukDEBUG_LED_PATTERN_FLASH_LONG(2s): Transfers in FLASH memory during a
 *   uKernel Image Update Operation for ukApp or ukApps Bundle replacement.
 *  - DukDEBUG_LED_PATTERN_ON: uKernel Image Update Operation checking.
 */
#define DukCONFIG_OPTION_DEBUG_LED_INDEX_UKERNEL_IMAGE_UPDATE                 \
            MukVAL_TYPED(TukDEBUG_LED_IDX, 2U)



#endif /* defined(SukCONFIG_FEATURE_DEBUG_LED) */

#endif /* !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* ######################################################################## */
/*                   UKERNEL OPTIONS / MCU DEVICE SPECIFIC                  */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel Options relative
 *  to the MCU Device selected.
 *
 * NOTE: To ease uKernel Configuration definition and maintenance for several
 *  MCU Devices, these definitions are managed in a dedicated include file
 *  for each MCU Device.
 */
#include "uk_config_options_hw_mcu_device.h"


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_OPTIONS_H_INSIDE
#endif /* !defined(UK_CONFIG_OPTIONS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

