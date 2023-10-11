/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *
 *****************************************************************************
 * @file          uk_config_features.h
 * @brief         uKernel API - uKernel Features definitions.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 * This file contains the uKernel Features exposed in the uKernel API for the
 *  uKernel Target used.
 * A uKernel Feature is a defined C-Preprocessor statement representing the
 *  support (when defined) of a uKernel functionality or of a specific variant
 *  of uKernel implementation (optimized for speed, resources, ...).
 *
 * The purpose of having some of these uKernel Features be part of the uKernel
 *  API is because they may be of interest for:
 *  - ukApp code: they allow to adapt and fine tune the ukApp implementation
 *   (e.g. by using conditional compilation) by relying on the uKernel
 *   functionalities effectively supported by the uKernel Target used.
 *  - ukApp configuration: they allow to adapt the configuration of the ukApp
 *   in their ukApp Descriptors in function of uKernel Features effectively
 *   supported (e.g. available resources consistent with supported
 *   functionalities).
 *
 * Example of uKernel Features:
 *  - uKernel built for Production Target.
 *  - uKernel Scheduler specific behavior.
 *  - uKernel support of ukProc Debug functionalities.
 *  - ...
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Release.
 *
 * @robustness The uKernel Features are taken into account only during the
 *  compilation of the uKernel Release used. It enforces that the
 *  implementation code relative to the uKernel functionalities
 *  associated to a uKernel Feature is included in uKernel Target binary only
 *  when supported (this participates to minimize the attack surface of the
 *  uKernel). The consistency of the uKernel Features supported is enforced
 *  during the compilation of the uKernel Release.
 *
 * @warning This file is specific to a given uKernel Target.
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
#if !defined(UK_CONFIG_FEATURES_H)

/*__________________________________________________________________________*/
/* Enforces that the 'uk_release.h' file has already been included. */
#if !defined(UK_RELEASE_H)
 #error 'The "uk_config_features.h" include file shall be included only after the "uk_release.h" file'
#endif /* !defined(UK_RELEASE_H) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONFIG_FEATURES_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_FEATURES_H_INSIDE


/* ######################################################################## */
/*                       UKERNEL FEATURES - DEFINITIONS                     */
/* ######################################################################## */
/* Hereafter are defined the uKernel Features (i.e. functional requirements
 *  of uKernel) part of uKernel API of the uKernel Release used.
 * Each of uKernel Feature is a C-Preprocessor statement defined or not to
 *  indicate its support or not in the uKernel Release.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Release to be taken into account.
 * @implementation A uKernel Feature named 'FFF' is supported if its
 *  corresponding statement 'SukCONFIG_FEATURE_<FFF>' is effectively defined
 *  using a C-Preprocessor '#define' (as statement, no value is associated to
 *  the definition).
 * @implementation A specific file section below is reserved for the uKernel
 *  Debug Features.
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Release used.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                   UKERNEL FEATURE - PRODUCTION RELEASE                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining that the uKernel is a Production Release.
 *
 * Definition of the uKernel Feature for indicating the uKernel is compiled
 *  for a Production Release.
 *
 * When this uKernel Feature is supported, additional consistency checks are
 *  done during the uKernel compilation, and all the debug functionalities
 *  that may be provided by the uKernel are removed (the associated uKernel
 *  code is not included in uKernel Release binary).
 *
 * @warning This uKernel Feature SHALL be supported for final product, for
 *  enforcing that all the security and robustness functionalities are fully
 *  effective during uKernel execution, and that the attack surface of the
 *  uKernel code is lowered to the strict necessary.
 *
 * @usage When not performing final integration testing of the uKernel Image
 *  (i.e. uKernel Core and the ukApps part of the ukApps Bundle), it is
 *  recommended to not enable this uKernel Feature for benefiting of more
 *  precise errors reports and debug functionalities.
 *
 * Default: NOT DEFINED.
 * Production Release: SHALL BE DEFINED.
 */
/* #define SukCONFIG_FEATURE_PRODUCTION_RELEASE */


/* //////////////////////////////////////////////////////////////////////// */
/*                         UKERNEL FEATURES - PLATFORM                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the request of an MCU Halt upon a uKernel
 *  FATAL Error.
 *
 * Definition of the uKernel Feature for the request of an MCU Halt upon a
 *  uKernel FATAL Error.
 *
 * @implementation Once an MCU Halt has been performed, an external reset signal
 *  sent to the MCU will be necessary to start a new uKernel Session. Till
 *  then, the MCU will remain halted.
 *
 * @implementation If this uKernel Feature is not supported, then a uKernel
 *  FATAL Error will trigger an MCU Reset, and thus the automatic restarting of
 *  a new uKernel Session.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/*#define SukCONFIG_FEATURE_PLATFORM_MCU_HALT_UPON_UKERNEL_FATAL_ERROR*/


/**
 * @brief uKernel Feature defining the request of an MCU Halt upon no more
 *  Schedulable ukProcs.
 *
 * Definition of the uKernel Feature for the request of an MCU Halt upon no more
 *  Schedulable ukProcs.
 *
 * @implementation Once an MCU Halt has been performed, an external reset signal
 *  sent to the MCU will be necessary to start a new uKernel Session. Till
 *  then, the MCU will remain halted.
 *
 * @implementation If this uKernel Feature is not supported, then a uKernel
 *  FATAL Error will trigger an MCU Reset, and thus the automatic restarting of
 *  a new uKernel Session.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/*#define SukCONFIG_FEATURE_PLATFORM_MCU_HALT_UPON_NO_SCHEDULABLE_UKPROC */



/* //////////////////////////////////////////////////////////////////////// */
/*                  UKERNEL FEATURE - UKERNEL INITIALIZATION                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of non-fatal uKernel
 *  Initialization error.
 *
 * Definition of the uKernel Feature for allowing uKernel Initialization to
 *  be in non-fatal mode.
 *
 * If this uKernel Feature is supported, then the uKernel will continue its
 *  Initialization even if:
 *  - An invalid or inconsistent value is found in one of the ukApp Descriptor.
 *  In that case the last ukApp Descriptor checked leading to the error is
 *  considered as invalid and its ukApp is ignored by the uKernel.
 *  - A ukProc Creation fails during the uKernel Initialization, which may be
 *   due to:
 *   + The count of ukProcs to create upon uKernel Initialization is bigger
 *    than the maximum supported (see DukCONFIG_OPTION_UKPROC_COUNT_MAX).
 *  - The uKernel Initialization Check Up fails, which may be due to:
 *   + Modifications having occurred in the Platform identifiers after the
 *    very first Initialization of the uKernel (note that this check depends
 *    of the Security Policy defined for the uKernel Release).
 *   + Platform hardware configuration is not consistent with the expected one
 *    for enforcing uKernel Security Policy.
 *
 * @warning When this uKernel Feature is supported, if some ukApp Descriptors
 *  have triggered an error and have been ignored (and thus considered as
 *  not being part of ukApps Bundle), other ukApp(s) relying on interactions
 *  with these removed ukApp(s) will fail.
 *
 * @implementation If uKernel Debug Trace are enabled, then the uKernel will
 *  print the errors encountered during its Initialization.
 *
 * Default: NOT DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
#define SukCONFIG_FEATURE_UKERNEL_INITIALIZATION_NON_FATAL_MODE


/* //////////////////////////////////////////////////////////////////////// */
/*                   UKERNEL FEATURES - UKERNEL CONFIGURATION               */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief uKernel Feature defining the support of a uKernel Configuration
 *  Customizable.
 *
 * Definition of the uKernel Feature for the support of a uKernel Configuration
 *  Customizable.
 * The uKernel Configuration Customizable has to be defined by the uKernel
 *  Owner, and written at the very beginning of the dedicated MCU Memory Region
 *  UKCORE_CONFIG_FLASH using the uKernel Configuration Descriptor structure
 *  (see C-Type TukUKERNEL_CONFIG_DESCRIPTOR ).
 *
 * @robustness If the uKernel Configuration Customizable is not present in the
 *  Memory Region UKCORE_CONFIG_FLASH or if its contents is invalid, then the
 *  uKernel will automatically use the default one defined in the C-Constant
 *  table DukUKERNEL_CONFIG_DEFAULT_TABLE.
 *
 * @implementation If this uKernel Feature is not supported, then the uKernel
 *  Configuration Static is used: it is hard coded inside uKernel
 *  implementation. The value hard coded are the same ones as the ones defined
 *  in the C-Constant table DukUKERNEL_CONFIG_DEFAULT_TABLE.
 *
 * Default: DEFINED.
 * Production Release: /.
 *
 * @implementation #NOTYETSUPPORTED
 */
#define SukCONFIG_FEATURE_UKERNEL_CONFIG_CUSTOMIZABLE


/**
 * @brief uKernel Feature defining the support of uKernel Configuration
 *  Customizable by ukProcs.
 *
 * Definition of the uKernel Feature for the support of uKernel Configuration
 *  Customizable by ukProcs.
 * When this uKernel Feature is supported, ukProcs with the proper credentials
 *  (see DukUKAPP_PROFILE_xxx) can update some parts of the uKernel
 *  Configuration (e.g. uKernel Systick Period).
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_CONFIG_CUSTOMIZABLE is supported.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 *
 * @implementation #NOTYETSUPPORTED
 */
/* #define SukCONFIG_FEATURE_UKERNEL_CONFIG_CUSTOMIZABLE_BY_UKPROC */




/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURE - UKAPP MANAGEMENT                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support for fine administration of
 *  ukProc.
 *
 * Definition of the uKernel Feature for allowing the support of fine
 *  administration of ukProc.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Instantiation of a ukProc by the ukProc instantiated from its ukApp
 *    Parent (see ukUKProcInstantiate()).
 *   - Fine granularity on the authorized recipient for the IPC message sent
 *    by the ukProc (see in ukApp Descriptor field
 *    <IPCSendToASIDAuthorizedList>).
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 *
 * @implementation #NOTYETSUPPORTED
 */
#define SukCONFIG_FEATURE_UKAPP_ADMINISTRATION_FINE


/**
 * @brief uKernel Feature defining the support for enforcing the checks done
 *  for verifying that a ukApp is Genuine.
 *
 * Definition of the uKernel Feature for enforcing the checks done for
 *  verifying that a ukApp is Genuine.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - If the SHA256 value computed by the uKernel on the whole contents of
 *    the ukApp Code Body Block of the ukApp is not equal to the field
 *    <UKAppCodeBodyBlockSHA256> then the ukApp is not Genuine, and the ukApp
 *    Descriptor is invalid.
 *   - If the SHA256 value computed by the uKernel on the contents of a
 *    ukApp Descriptor from its start up to its field <UKAppDescriptorSHA256>
 *    (not included) is not equal to the field <UKAppDescriptorSHA256> then
 *    the ukApp is not Genuine, and the ukApp Descriptor is invalid.
 *
 * Default: DEFINED.
 * Production Release: Forced to DEFINED.
 */
/* #define SukCONFIG_FEATURE_UKAPP_GENUINE_CHECKS_ENFORCE */


/**
 *
 * @brief uKernel Feature defining the support for wrapping applications in
 *  MCUBoot images.
 *
 * Definition of the uKernel Feature for allowing applications to be wrapped
 *  as MCUBoot images.
 *
 * If this uKernel Feature is supported, then ukApps are allowed to be prefixed
 *  by a 32 byte header. This header is ignored, and the application is found
 *  32 bytes after the usual position.
 *
 * Default: UNDEFINED.
 */
#define SukCONFIG_FEATURE_MCUBOOT_APP_IMAGE


/**
 *
 * @brief uKernel Feature defining the support for enforcing the safe overlap
 *  of MCURegister uses.
 *
 * Definition of the uKernel Feature for enforcing the safe overlap of
 *  MCURegisters.
 *
 * If this uKernel Feature is supported, then ukApps which declare wanting to
 *  write bit of MCURegisters in their descriptor cannot coexist with other
 *  applications which either read or write the same bits.
 *
 * Default: UNDEFINED.
 */
#define SukCONFIG_FEATURE_MCUREGISTER_NO_OVERLAP


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURE - UKPROC MANAGEMENT                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support for ukProc Termination.
 *
 * Definition of the uKernel Feature for allowing the support for ukProc
 *  Termination.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - The ukProc Termination process allowing the deletion of a ukProc
 *    Instance. Two Natures of ukProc Termination are supported:
 *    + ukProc End: ukProc Exit following the successful end of all the
 *     operations of the ukProc Instance (i.e without reporting any error).
 *    + ukProc Abort: ukProc Instance execution aborted following the
 *     reporting of an erroneous internal condition during the ukProc Instance
 *     operations, the triggering of a ukProc Fatal Error during ukProc
 *     Instance execution (triggering of an MCU Exception, improper credentials,
 *     ...), or the termination of current uKernel Session.
 *   - Reincarnation of a ukProc after previous ukProc Instance of same ukApp
 *    has been terminated (see in ukApp Descriptor field <Profile>, and
 *    ukApp Profile flags DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG and
 *    DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG).
 *
 * @warning If this uKernel Feature is not supported, then any ukProc
 *  Termination triggers a uKernel Session End with Status Code
 *  DukSTATUS_ERR_UKPROC_TERMINATED, followed by an MCU Reset.
 *
 * @note See ukProc Management Documentation for more details on:
 *  - The conditions triggering each supported Nature of ukProc Termination
 *   (ukProc End or ukProc Abort).
 *  - The actions performed by the uKernel on the ukProc Instance upon a ukProc
 *   Termination.
 *
 * @implementation When this uKernel Feature is not supported, it allows to
 *  minimize the uKernel Core code size, as all the uKernel code related to the
 *  processing and checking to be made upon termination of a ukProc Instance
 *  is not included.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED


/**
 * @brief uKernel Feature defining the support for ukProc Cleanup upon ukProc
 *  Termination.
 *
 * Definition of the uKernel Feature for the support for ukProc Cleanup upon
 *  ukProc Termination.
 * When the uKernel has triggered a ukProc Termination (i.e a ukProc End or
 *  a ukProc Abort), the ukProc Cleanup support allows dedicated ukApp code
 *  to perform its necessary cleanup (e.g. wiping of sensitive data, resetting
 *  of some peripherals, ...) before being effectively terminated by the
 *  uKernel.
 * The ukProc Cleanup is performed by the invocation of the dedicated ukApp
 *  Entry Point ukappCleanup() by the uKernel at the beginning of the ukProc
 *  Termination process.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Implementation of the ukApp Entry Point ukappCleanup() in ukApp.
 *    The definition of this ukApp Entry Point is optional in the ukApp code of
 *    each ukApp part of the ukApps Bundle.
 *   - Invocation of the ukApp Entry Point ukappCleanup() by the uKernel, if
 *    defined in ukApp code, upon the start of the ukProc Termination process.
 *    Once the invocation is over, the ukProc Termination process is finalized
 *    (current ukProc Instance is deleted).
 *
 * @implementation When this uKernel Feature is not supported, it allows to
 *  minimize the uKernel Core code size, as all the uKernel code related to the
 *  checking and processing of the ukApp Entry Point ukappCleanup() of a ukApp
 *  is not included.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED is supported.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP


/**
 * @brief uKernel Feature defining the support of ukProc Exception.
 *
 * Definition of the uKernel Feature for allowing the support of ukProc
 *  Exception.
 * A ukProc Exception is processed by the immediate invocation of the dedicated
 *  ukApp Entry Point ukappException() with a guaranteed maximal fixed latency
 *  upon the occurrence of one of the following events:
 *   - Triggering of a PIRQ (Peripheral IRQ) registered by the ukProc.
 *   - uKernel Signal sent to the ukProc.
 *
 * The execution time allocated by the ukScheduler (uKernel Scheduler) to a
 *  ukProc Instance to perform the processing of the ukProc Exception is
 *  limited: the invocation of the ukApp Entry Point ukappException() shall be
 *  over before the end of the Scheduling Time Quantum Allocated for ukProc
 *  Exception defined in the field
 *  <UKProcExceptionSchedulingTimeQuantumAllocated_systick> of its ukApp
 *  Descriptor.
 *  If this Scheduling Time Quantum, which runs only while the ukProc is the
 *  Scheduled ukProc, is exhausted, then it is a ukProc Fatal Error, the
 *  execution of the ukApp Entry Point ukappException() is stopped, and the
 *  uKernel triggers a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_INVALID_STATE.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Implementation of the ukApp Entry Point ukappException() in ukApp.
 *    The definition of this ukApp Entry Point becomes mandatory in the
 *    ukApp code of each ukApp part of the ukApps Bundle.
 *   - Invocation of the ukApp Entry Point ukappException() by the uKernel upon
 *    the occurrence of one of the following events:
 *    + Triggering of a PIRQ (Peripheral IRQ) registered by the ukProc.
 *    + uKernel Signal sent to the ukProc.
 *    Once the invocation is over, the ukProc Instance execution is resumed to
 *    where it has been suspended.
 *
 * @implementation During the invocation of the ukApp Entry Point
 *  ukappException(), the Scheduling ukProc State is set to Interrupted.
 *
 * @implementation When this uKernel Feature is not supported, it allows to
 *  minimize the uKernel Core code size, as all the uKernel code related to the
 *  checking and processing of the ukApp Entry Point ukappException() of a
 *  ukApp is not included.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 *
 * @implementation #NOTYETSUPPORTED
 */
/*#define SukCONFIG_FEATURE_UKPROC_EXCEPTION*/


/**
 * @brief uKernel Feature defining the support of updating the MCU Clocks Set
 *  used by ukProcs.
 *
 * Definition of the uKernel Feature for the support of updating the MCU Clocks
 *  Set used by ukProcs.
 * When this uKernel Feature is supported, ukProcs with the proper credentials
 *  (see DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG), can update the MCU Clocks
 *  Set used (see ukPlatformSetAttribute() and
 *  DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX).
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/* #define SukCONFIG_FEATURE_UKPROC_MCU_CLOCKS_SET_UPDATABLE */


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURE - PERIPHERAL IRQ                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support Peripheral IRQ.
 *
 * Definition of the uKernel Feature for allowing the support of Peripheral
 *  IRQ for ukProc.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Registering to Peripheral IRQ (see ukPeripheralIRQRegister()).
 *   - Receiving IPC Message of Nature DukIPC_MSG_NATURE_PIRQ_TRIGGERED
 *    when a Peripheral IRQ is triggered.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_PERIPHERAL_IRQ

/* //////////////////////////////////////////////////////////////////////// */
/*                        UKERNEL FEATURE - SCHEDULING                      */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief uKernel Feature defining the support for uKernel Scheduler preemption
 *  upon ukProc unblocking.
 *
 * Definition of the uKernel Feature for allowing the support for uKernel
 *  Scheduler preemption upon ukProc unblocking.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - If a ukProc currently in Scheduling State BLOCKED is unblocked, and
 *    if its Scheduling Priority has an strictly higher precedence than the one
 *    of the Scheduled ukProc (i.e. its value is strictly lower than the one
 *    of the Scheduled ukProc), then the Scheduled ukProc is preempted, and
 *    the election of a new Scheduled ukProc is triggered.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/* #define SukCONFIG_FEATURE_SCHEDULER_PREEMPTION_ON_UNBLOCKING */


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURE - SHARED BUFFERS                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support Shared Buffers.
 *
 * Definition of the uKernel Feature for allowing the support of Shared
 *  Buffers for ukProc.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - The transfer of Shared Buffer to other ukProc (see
 *    ukSharedBufferTransfer()).
 *   - Mapping of Shared Buffer in ukProc address space using
 *    ukAddressBlockWindowMap().
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_SHARED_BUFFERS


/* //////////////////////////////////////////////////////////////////////// */
/*                        UKERNEL FEATURE - MCU DMA                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support MCU DMA Streams.
 *
 * Definition of the uKernel Feature for allowing the support of MCU DMA
 *  Streams for ukProc.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Creation by the ukProc of MCU DMA Stream Instances from predefined
 *    MCU DMA Streams in ukApp Descriptor (see ukMCUDMAInstanceCreate()).
 *   - Management of MCU DMA transfers by the ukProc from created MCU DMA
 *    Stream Instances.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_MCU_DMA


/* //////////////////////////////////////////////////////////////////////// */
/*                       UKERNEL FEATURE - WATCHDOG                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of ukProc Watchdogs.
 *
 * Definition of the uKernel Feature for allowing the support of Watchdog
 *  for ukProc.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Management of a ukProc Watchdog (see ukWatchdogStart(),
 *    ukWatchdogStop()).
 *   - Kicking a ukProc Watchdog (see ukWatchdogKick()).
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_WATCHDOG_UKPROC


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURE - RANDOM GENERATION                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of Random Generator services
 *  for ukProcs.
 *
 * Definition of the uKernel Feature for allowing the support of Random
 *  Generator (RNG) services for ukProcs.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Generation of random values using a selected Random Generator:
 *    + ukRandomGetBytes().
 *   - Seeding a selected Random Generator:
 *    + ukRandomSetSeed64().
 *
 * Default: DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_RNG_UKPROC


/* //////////////////////////////////////////////////////////////////////// */
/*              UKERNEL FEATURE - UKAPP DATA PERSISTENT BLOCK               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support for ukApp Data Persistent Block.
 *
 * Definition of the uKernel Feature for allowing the support of ukApp
 *  Data Persistent Block.
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Management of a dedicated ukApp Data Persistent Block by the uKernel
 *    for each ukApp (the <DataPersistentBlockLength> field in ukApp
 *    Descriptor contains the size of the ukApp Data Persistent Block).
 *   - Reading and writing to the ukApp Data Persistent Block by using the
 *    following uKernel Privileged Services:
 *    + ukPersistentDataBlockEraseSector().
 *    + ukPersistentDataBlockRead().
 *    + ukPersistentDataBlockWrite().
 *
 * @robustness In order to enforce isolation of uKernel and of executed
 *  ukProcs, direct access to MCU Flash Controller is never authorized by
 *  uKernel. Thus the sole way to let ukProcs manage persistent data is to
 *  enable this uKernel Feature in order to let them have access to a private
 *  ukApp Data Persistent Block.
 *
 * @implementation The uKernel implementation of the ukApp Data Persistent
 *  Block is conceived in order to enforce isolation in regards of the MCU
 *  Flash Controller between ukApps. Notably, two ukApp Data Persistent Blocks
 *  are enforced to never share a same Flash Sector.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK

/**
 * @brief uKernel Feature defininf the support for alternative configuration
 *  of ukApp Data Persistent Block
 *
 * Definition of the uKernel Feature for supporting alternative configuration
 *  of ukApp Data Persistent Block.
 *
 * In the normal case, the address and size of ukApp Data Persistent areas is
 *  found in the application descriptor. With this feature enabled, the address
 *  can instead be DukADDRESS_INVALID_DATA_PERSISTENT, and a target-specific
 *  function is called to provide the suitable values.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
#define SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK_ALTERNATE


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL FEATURE - UKERNEL IMAGE UPDATE                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of uKernel Image Update.
 *
 * Definition of the uKernel Feature for allowing the support of uKernel Image
 *  Update.
 *
 * The uKernel Image Update support provides the necessary functionalities to
 *  allow a ukProc to perform a partial or complete update of the current
 *  uKernel Image (composed of uKernel core code, and ukApps Bundle containing
 *  all the code and configuration of the ukApps).
 * The uKernel Image Update process is performed as follows:
 *  - Writing the data of the uKernel Image Updated Part in uKernel Image
 *   Update Storage (a dedicated reserved part of the MCU Flash).
 *  - Verifying the integrity and structure validity of the uKernel Image
 *   Updated Part.
 *  - Replacing with the provided uKernel Image Updated Part whole or part of
 *   the uKernel Image. This replacement is done only at the startup of a new
 *   uKernel Session after a uKernel Session End of the current one (i.e. the
 *   uKernel Session has been terminated without any errors).
 *
 * If this uKernel Feature is supported, then the following uKernel
 *  functionalities will be supported:
 *   - Erasing blocks of the uKernel Image Update Storage (see
 *    ukUKImageUpdateEraseSector()).
 *   - Reading and Writing blocks data in the uKernel Image Update Storage (see
 *    ukUKImageUpdateRead(),
 *    ukUKImageUpdateWrite()).
 *   - Switching to the updated uKernel Image by requesting copy of the new
 *    data in the uKernel Image upon next uKernel Session (see
 *    ukUKImageUpdateOperate()).
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/* #define SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE */

/** Documentation must be updated */
#define SukCONFIG_FEATURE_PSA_FIRMWARE_UPDATE


/**
 * @brief uKernel Feature defining the support for keeping previous uKernel
 *  Image updated part.
 *
 * Definition of the uKernel Feature for allowing the support for keeping
 *  previous uKernel Image updated part.
 *
 * This uKernel Feature act on the uKernel Security Policy for uKernel Image
 *  Update as follows:
 *  - SUPPORTED:  When replacing a uKernel Image part (see
 *   ukUKImageUpdateOperate()), a copy of the replaced part is stored in
 *   uKernel Image Update Storage. This copy can be used to perform a roll-back
 *   to the previous version of the uKernel Image part updated.
 *  The default uKernel Security Policy is to trigger the roll-back to the
 *   previous version if after a certain consecutive count (see
 *   DukCONFIG_OPTION_UKERNEL_IMAGE_UPDATE_VALIDATE_SESSION_COUNT_MAX)
 *   of consecutive uKernel Sessions, the uKernel Image Update Operation
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE has not been performed. The
 *   roll-back is performed by the uKernel Bootloader before the start of the
 *   uKernel Session.
 *  The uKernel Image Update Storage keeps the previous version until the
 *   the uKernel Image Update Operation
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE is performed. While
 *   keeping the previous version, the uKernel Image Update Storage is locked
 *   and cannot be used for storing a new uKernel Image part for update.
 *  The roll-back can also be triggered by the ukApp code itself (see
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_ROLLBACK) as long as the uKernel Image
 *   Update Storage is locked.
 *  - NOT SUPPORTED: When replacing a uKernel Image part (see
 *   ukUKImageUpdateOperate()), no copy of the replaced part is kept in
 *   uKernel Image Update Storage, and thus it is not possible to roll-back
 *   to the previous version after having triggered the update.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE is supported.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 *
 * @implementation #NOTYETSUPPORTED
 */
/* #define SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS */


/* //////////////////////////////////////////////////////////////////////// */
/*                           UKERNEL FEATURE - FPU                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support for enabling the FPU on the
 *  Non-Secure side.
 *
 * Definition of the uKernel Feature for enabling the FPU on the Non-Secure
 *  side.
 *
 * When the uKernel Feature is enabled, it is possible for the Non-Secure to
 *  enable the FPU.
 *
 * @note: This feature is only relevant with configuration where there is
 *  support for a Non-Secure side/
 **/
#define SukCONFIG_FEATURE_UKERNEL_MCU_FPU_NS



/* ######################################################################## */
/*                         UKERNEL FEATURES - DEBUG                         */
/* ######################################################################## */
/* Hereafter are defined the uKernel Debug Features (i.e. functional
 *  requirements of uKernel) part of uKernel API of the uKernel Release used
 *  and dedicated to the debug functionalities offered by the uKernel.
 * These definitions are similar to the uKernel Features above (and can also be
 *  used by the uKernel Core and ukApp implementations), but care has to be
 *  taken by that they are NOT defined for a uKernel Release that is a
 *  Production Release.
 * WARNING: Change in these definitions require the compilation of a new
 *  uKernel Release to be taken into account.
 * @implementation A uKernel Debug Feature named 'FFF' is supported if its
 *  corresponding statement 'SukCONFIG_FEATURE_DEBUG_<FFF>' is effectively
 *  defined using a C-Preprocessor '#define' (as statement, no value is
 *  associated to the definition).
 * @usage These definitions can be used in uKernel Core and ukApp
 *  implementations to fine tune it in function of the uKernel functionalities
 *  declared as supported in the uKernel Release used.
 */

/* ROBUSTNESS: None of the uKernel Debug Features defined hereafter are
 *  supported if the uKernel compilation is aiming a Production Release. */

/* //////////////////////////////////////////////////////////////////////// */
/*                    UKERNEL FEATURES - DEBUG - DEBUGGER                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of an external Debugger
 *  connected to the CPU.
 *
 * Definition of the uKernel Feature for the support of an external Debugger
 *  connected to the CPU onto which uKernel is executed.
 *
 * @implementation As additional robustness, if this uKernel Feature is not
 *  supported, then the interface used for the external Debugger to connect
 *  (GPIO, ...) is disabled at hardware level during the uKernel
 *  Initialization.
 *
 * Default: DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
#define SukCONFIG_FEATURE_DEBUG_DEBUGGER_ALLOWED


/* //////////////////////////////////////////////////////////////////////// */
/*                    UKERNEL FEATURES - DEBUG - GOD MODE                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of God Mode.
 *
 * Definition of the uKernel Feature for the support of of God Mode.
 * When this uKernel Feature is supported:
 *  - The MPU is not used by the uKernel for preventing access to unauthorized
 *   memory.
 *  - The ukProcs are executed with the CPU mode privileged.
 *
 * @usage The God Mode allows to quickly develop and test some application
 *  prototypes using uKernel services, without having to care at first about
 *  the strong security restrictions conditions imposed by the uKernel security
 *  architecture.
 *  It allows notably to test some prototype code without having to modify the
 *  code of the low level hardware layer drivers.
 *
 * Default: NOT DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
/* #define SukCONFIG_FEATURE_DEBUG_GOD_MODE */


/* //////////////////////////////////////////////////////////////////////// */
/*                     UKERNEL FEATURES - DEBUG - DEBUG TRACE               */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief uKernel Feature defining the support of ukProc Debug Traces.
 *
 * Definition of the uKernel Feature for the support of ukProc Debug Traces.
 *
 * If ukProc Debug Trace is supported, the following uKernel Service are
 *  available for printing ukProc Debug Traces:
 *  - ukDebugTracePrint: Print a Null Terminated String (NTString).
 *  - ukDebugTracePrintf: Print a string resulting from the processing of
 *   printf like format Null Terminated String (NTString) with associated
 *   format values passed as arguments.
 *  - ukDebugTracePrintBuffer: Print the contents of a Buffer as a table of
 *   hexadecimal bytes. The access to the referenced Buffer shall be granted to
 *   the ukProc.
 *
 * The uKernel Configuration Default used for Debug Trace is defined as
 *  follows:
 *  - The maximal number of characters per Debug Trace print is defined by
 *   the uKernel Option DukCONFIG_OPTION_DEBUG_TRACE_LENGTH_PER_PRINT_MAX.
 *  - The column wrapping is defined by the uKernel Option
 *   DukCONFIG_OPTION_DEBUG_TRACE_LINE_COLUMN_WRAP.
 *
 * If several ukProc Debug Trace Interfaces are supported (see
 *  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_xxx), then the printing of a
 *  Debug Trace will be performed on ALL the supported Debug Trace Interfaces.
 *
 * @warning The printing of a Debug Trace may slow down significantly the
 *  effective uKernel execution speed (compared to the speed where the Debug
 *  Trace is disabled). It should be keep in mind that this change of execution
 *  speed may result in different behaviors of the ukProcs executed, notably in
 *  regards of external events.
 *  The effective impact on execution speed is depending mainly of the
 *  transmission speed on the chosen Debug Trace interfaces, and of the number
 *  of Debug Trace printed (i.e. Debug Trace Filter used).
 *
 * @warning The printing of a ukProc Debug Trace cannot be interrupted.
 *  Thus, if a Peripheral IRQ is triggering during the printing, it will be
 *  postponed till the end of the printing.
 *
 * Default: DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
#define SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC


/**
 * @brief uKernel Feature defining the support of ANSI colors for Debug Traces.
 *
 * Definition of the uKernel Feature for the support of ANSI colors for Debug
 *  Traces from uKernel or from ukProcs.
 *
 * If ANSI colors is supported, :
 *  - Different colors will be used for each Nature of a Debug Trace.
 *  - The uKernel Debug Traces will be printed in bold.
 *  - Different colors will be used by each ukProc for its Debug Trace banner
 *   (printed each time a different ukProc prints on the Debug Trace).
 *
 * @implementation If ANSI colors is supported, the printed Debug Traces will
 *  use the Escape code (0x1B) to change the text color with the following
 *  sequences:
 *  - '<ESC>[38;5;<color>m' for setting the foreground color.
 *  - '<ESC>[0m' for resetting the color to its default.
 *
 * Default: DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
/* #define SukCONFIG_FEATURE_DEBUG_TRACE_COLOR_ANSI */



/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL FEATURES - DEBUG - DEBUG TRACE INTERFACES         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of SemiHosting Debug Trace
 *  Interface for printing ukProc Debug Traces.
 *
 * Definition of the uKernel Feature for the support of the SemiHosting
 *  Debug Trace Interface for printing ukProc Debug Traces.
 *
 * @note The SemiHosting Debug Trace Interface may be shared between uKernel
 *  and ukProcs in function of uKernel Features enabled for uKernel Core.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is supported.
 *
 * Default: NOT DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
/* #define SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_SEMIHOSTING */


/**
 * @brief uKernel Feature defining the support of the UART Debug Trace
 *  Interface for printing ukProc Debug Traces.
 *
 * Definition of the uKernel Feature for the support of the UART Debug Trace
 *  Interface for printing ukProc Debug Traces.
 *
 * The uKernel Configuration Default used for UART Debug Trace Interface is
 *  defined as follows:
 *  - The GPIO Pin Map used for UART hardware interface are defined by the
 *   entry of index 0 in the uKernel Reporting Device UART Pin Map table
 *   defined by the uKernel Option
 *   DukCONFIG_OPTION_HW_DEBUG_REPORTING_DEVICE_UART_PIN_MAP_LIST.
 *  - The UART physical layer configuration is defined by the uKernel Option
 *   DukCONFIG_OPTION_DEBUG_TRACE_INTERFACE_UART_CONFIG.
 *  - The UART communication speed is defined by the uKernel Option
 *   DukCONFIG_OPTION_DEBUG_TRACE_INTERFACE_UART_BAUDRATE.
 *
 * @note The UART Debug Trace Interface may be shared between uKernel
 *  and ukProcs in function of uKernel Features enabled for uKernel Core.
 *
 * @implementation This uKernel Feature is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is supported.
 *
 * @usage In general, the UART Debug Trace Interface is much more efficient
 *  in term of performance than the SemiHosting one.
 *  Thus, if UART Debug Trace Interface is available on the used Platform, it
 *  is preferable to use it (and to disable the support of SemiHosting Debug
 *  Trace Interface).
 *
 * Default: DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
#define SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_UART


/* //////////////////////////////////////////////////////////////////////// */
/*              UKERNEL FEATURES - DEBUG - TRACE CONFIGURATION              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the use of 'LF' only for a new line when
 *  printing Debug Trace.
 *
 * Definition of the uKernel Feature for the sending of only the 'LF' character
 *  for performing a carriage return upon a new line when printing Debug Trace.
 * If this uKernel Feature is not supported, then 'CR'+'LF' is used.
 *
 * Default: NOT DEFINED.
 * Production Release: /.
 */
/*#define SukCONFIG_FEATURE_DEBUG_TRACE_NEWLINE_LF_ONLY*/


/* //////////////////////////////////////////////////////////////////////// */
/*                      UKERNEL FEATURES - DEBUG - LED                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Feature defining the support of Debug LED for reporting
 *  debug information.
 *
 * Definition of the uKernel Feature for the support of the Debug LED for
 *  reporting debug information.
 *
 * A Debug LED is an indicator light (often a LED component is used indeed)
 *  that can be switched ON or OFF, possibly with a specific blinking pattern,
 *  to report a given information.
 * Each Debug LED is connected to one of the GPIO line of the MCU (and thus
 *  this GPIO line cannot be used anymore by applicative code in ukApp). The
 *  convention being that when the GPIO line is providing Vcc voltage level,
 *  the Debug LED is switched ON.
 *
 * The Debug LEDs can be used by:
 *  - The uKernel to report its internal state, and notably the following
 *   information:
 *    + uKernel Initialization ongoing.
 *    + uKernel Initialization failure.
 *    + uKernel FATAL Error (after its Initialization).
 *    + A ukProc Fatal Error.
 *    + uKernel Scheduler entering Idle Mode (no Schedulable ukProc available).
 *    + uKernel entering Low Power Mode.
 *  - A ukProc to report various information relative to its internal state
 *   (life-cycle, error, ...). The way to use the Debug LED, to report
 *   information with specific blinking pattern, is let open to the ukApp
 *   developer.
 *
 * @warning The GPIO lines (i.e. GPIO port and given pin) used as Debug LED
 *  are set up during uKernel Initialization. But their configuration is
 *  afterwards not protected by the uKernel: thus if a ukProc modifies the
 *  GPIO port configuration (e.g. cut the GPIO clock, ...), the Debug LED may
 *  not work anymore as expected. The reason why not to prevent such
 *  modifications is that, as GPIO port configuration implies various internal
 *  hardware modules in the MCU, it would have implied to much restrictions or
 *  modifications in the ukApp code to offer relative level of confidence on a
 *  uKernel Feature that is only for debug purpose.
 *
 * @note The implementation of the Debug LED management is performed very
 *  quickly, and thus should only affect slightly the uKernel execution speed.
 *  It should however be kept in mind that this change of execution speed, even
 *  if small, may result in different behaviors of the ukProcs executed,
 *  notably in regards of external events.
 *
 * Default: DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
#define SukCONFIG_FEATURE_DEBUG_LED


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL FEATURES - DEBUG - RANDOM GENERATION              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel Debug Feature defining the Random Generators as predictable
 *  PRNG.
 *
 * If this uKernel Feature is supported, then all the Random Generator supported
 *  by the implementation of the uKernel Release and the Platform are
 *  replaced by a PRNG dedicated to each ukProc (the PRNGs of each
 *  ukProc are however still fully independent).
 *
 * As as no other entropy source is pushed in each ukProc PRNG, the sequence
 *  of values that will be generated in each ukProc upon a new uKernel Session
 *  will always be the same. This is done on purpose in order to ease the
 *  debug of a ukProc.
 *
 * @note The PRNG used is a XorShift-32bit using Georges MARSAGLIA suggested
 *  coefficients '13, 17, 5' for XorShift-32bit:
 *    { prng_state ^= prng_state << 13;
 *      prng_state ^= prng_state >> 17;
 *      prng_state ^= prng_state << 5;
 *    }
 * The initial state is depending only of the ukProc Index (see TukUKPROC_PIDX).
 *
 * @note This uKernel Debug Feature is independent of the uKernel Feature
 *  SukCONFIG_FEATURE_RNG_UKPROC, as it concerns also the generation of
 *  random numbers in the uKernel Core code.
 *
 * Default: NOT DEFINED.
 * Production Release: Forced to NOT DEFINED.
 */
/* #define SukCONFIG_FEATURE_DEBUG_RNG_PREDICTABLE */


/* ######################################################################## */
/*                      UKERNEL FEATURES - NORMALIZATION                    */
/* ######################################################################## */
/* Hereafter is performed the normalization of the uKernel Features defined
 *  previously, in order to enforce proper consistency of the supported uKernel
 *  functionalities.
 *
 * @robustness The consistency of the uKernel Features supported is enforced
 *  during the compilation of the uKernel Release. This consistency check is
 *  made in uKernel Core implementation and not in this file which is an
 *  updatable file not part of uKernel Core implementation.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL FEATURES - NORMALIZATION - PRODUCTION RELEASE           */
/* //////////////////////////////////////////////////////////////////////// */

/* All the uKernel Features or uKernel Debug Features hereafter are forced
 *  to DEFINED if uKernel Release is a Production Release. */
#if defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)
    #define SukCONFIG_FEATURE_UKAPP_GENUINE_CHECKS_ENFORCE
#endif /* defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* All the uKernel Features or uKernel Debug Features hereafter are forced
 *  to NOT DEFINED if uKernel Release is a Production Release. */
#if defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)
    #undef  SukCONFIG_FEATURE_UKERNEL_INITIALIZATION_NON_FATAL_MODE
    #undef  SukCONFIG_FEATURE_UKAPP_GENUINE_CHECKS_IGNORE
    #undef  SukCONFIG_FEATURE_DEBUG_DEBUGGER_ALLOWED
    #undef  SukCONFIG_FEATURE_DEBUG_GOD_MODE
    #undef  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC
    #undef  SukCONFIG_FEATURE_DEBUG_TRACE_COLOR_ANSI
    #undef  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_SEMIHOSTING
    #undef  SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC_INTERFACE_UART
    #undef  SukCONFIG_FEATURE_DEBUG_LED
    #undef  SukCONFIG_FEATURE_DEBUG_RNG_PREDICTABLE
#endif /* defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_FEATURES_H_INSIDE
#endif /* !defined(UK_CONFIG_FEATURES_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

