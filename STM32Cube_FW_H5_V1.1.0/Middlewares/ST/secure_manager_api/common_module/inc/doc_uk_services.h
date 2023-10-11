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
 * @file          doc_uk_services.h
 * @brief         uKernel API - Main uKernel API Documentation file -
 *  uKernel Services C-Functions sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API Documentation file for a
 *  given uKernel Target dedicated to the uKernel Services.
 *
 * See main uKernel API include file "uk_services.h" for details on the uKernel
 *  Services C-Functions.
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 *
 * @note This file is used only for documentation purpose. It is not required
 *  to be included as part of the compilation chain (excepted if needed for
 *  helping IDE parsing).
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(DOC_UK_SERVICES_H)


/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  DOC_UK_SERVICES_H

/* Define that we are inside this file (definition is undone at its end). */
#define  DOC_UK_SERVICES_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Source the uKernel Configuration file part of uKernel API used for the
 *  compilation of the given uKernel Target (i.e uKernel Target definitions,
 *  uKernel Features defined, uKernel Options values, ...). */
#include "uk_config.h"



/* ######################################################################## */
/*               UKERNEL API - DOC - UKERNEL PRIVILEGED SERVICES            */
/* ######################################################################## */
/* Hereafter are defined uKernel Privileged Services, which are uKernel API
 *  Entry Points (C-Functions) that require switch to uKernel internal code
 *  executed with CPU Privileged Execution Mode to provide requested service.
 */

/* The C-Functions declarations shall not be done when this file is used by
 *  the C-Assembler. */
#if !defined(__ASSEMBLER__)


/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - DOC - PRIVILEGED - UKPROC MANAGEMENT            */
/* //////////////////////////////////////////////////////////////////////// */
#define docUKProcManagement
/**
 * @page docUKProcManagement ukProc Management
 * The following sections provides more information on the different actions
 *  relative to ukProc Management which can be performed during ukProcs
 *  execution through uKernel Privileged Services.
 */


/* ------------------------------------------------------------------------ */
/*                         UKPROC MANAGEMENT - CREATION                     */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementCreation
/**
 * @section docUKProcManagementCreation ukProc Management: Creation
 *
 * A ukProc Creation consists in the creation of a new ukProc Instance from
 *  a given ukApp part of the ukApps Bundle.
 *
 * In order to differentiate a new ukProc Instance from a previous one of the
 *  same ukApp, the uKernel will enforce that the new ukProc Instance has a
 *  different PUID (see TukUKPROC_PUID). So, the other ukProcs are able to
 *  detect that a new ukProc Instance has been created form this ukApp, and
 *  react accordingly.
 *
 * At any moment, only one ukProc Instance can be created from a given ukApp,
 *  and thus a ukApp code cannot be executed by several ukProc Instances at
 *  the same time (no need to consider re-entrance in the ukApp
 *  implementation).
 * The whole data and execution context from previous ukProc Instance is lost,
 *  excepting its ukProc Termination Context (see
 *  DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST).
 *
 * Upon creation of the ukProc Instance, the following actions are performed by
 *  the uKernel in sequence:
 *   - The ukProc is set as schedulable in the ukScheduler (uKernel Scheduler).
 *   - Its ukApp Data Volatile Block is initialized while it is the Scheduled
 *    ukProc. This initialization may require a significant time in function of
 *    the size of the ukApp Data Volatile Block.
 *   - Once the ukApp Data Volatile Block initialization is over, the
 *    Scheduling ukProc State is set to Ready: from then on the execution of
 *    its ukApp Entry Point ukappMain() occurs when it is elected as the
 *    Scheduled ukProc.
 */


/* ------------------------------------------------------------------------ */
/*                           UKPROC MANAGEMENT - EXIT                       */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementExit
/**
 * @section docUKProcManagementExit ukProc Management: Exit
 *
 * A ukProc Exit is occurring when a ukProc is requesting the definitive halt
 *  of the execution of its current ukProc Instance.
 * The ukProc Exit can be triggered only by the ukApp code itself through the
 *  invocation of the uKernel Privileged Service ukUKProcExit() in one of its
 *  ukApp Entry Points:
 * - ukappMain(), ukappException(): When ukUKProcExit() is invoked in one of
 *  these ukApp Entry Points, the given boolean parameter <is_exit_in_error__i>
 *  indicates the nature of the ukProc Exit:
 *  + DukBOOL_FALSE: Successful end of all its operations (i.e without
 *    reporting any error), which leads to a ukProc End.
 *  + (other value): Detection of an erroneous internal condition during its
 *    operations, which leads to a ukProc Abort.
 * - ukappCleanup(): When ukUKProcExit() is invoked in this ukApp Entry Point,
 *  the given boolean parameter <is_exit_in_error__i> indicates if the ukProc
 *  Cleanup is successful.
 */


/* ------------------------------------------------------------------------ */
/*                            UKPROC MANAGEMENT - END                       */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementEnd
/**
 * @section docUKProcManagementEnd ukProc Management: End
 *
 * A ukProc End is a ukProc Termination after its ukProc Instance has ended
 *  successfully all its operations without reporting any error.
 * A ukProc End process is triggered upon one of the following events:
 *  - A ukProc Exit occurs from its ukApp Entry Point ukappMain() or
 *   ukappException() by invoking the uKernel Privileged Service
 *   ukUKProcExit(), with its boolean parameter <is_exit_in_error__i> set to
 *   DukBOOL_FALSE (indicating an exit without error).
 * The processing of a ukProc End is always finalized by a ukProc Termination
 *  (and the deletion of its current ukProc Instance).
 */


/* ------------------------------------------------------------------------ */
/*                          UKPROC MANAGEMENT - ABORT                       */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementAbort
/**
 * @section docUKProcManagementAbort ukProc Management: Abort
 *
 * A ukProc Abort is a ukProc Termination after the triggering of an erroneous
 *  internal condition or illegal operation during the operations of its ukProc
 *  Instance.
 * A ukProc Abort is triggered upon one of the following events:
 *  - A ukProc Fatal Error occurring during execution of the ukProc Instance
 *   (Illegal opcode, illegal memory access, ukProc Watchdog expiration, ...).
 *  - A ukProc Exit occurs from its ukApp Entry Point ukappMain() or
 *   ukappException() using uKernel Privileged Service ukUKProcExit(), with its
 *   given boolean parameter <is_exit_in_error__i> not set to DukBOOL_FALSE
 *   (indicating an exit in error).
 *  - A uKernel Session End has been triggered by the uKernel or by a ukProc
 *   (see DukPLATFORM_ATTRIBUTE_TAG_STATE).
 *  The processing of a ukProc Abort is always finalized by a ukProc
 *   Termination (and the deletion of its current ukProc Instance).
 */


/* ------------------------------------------------------------------------ */
/*                     UKPROC MANAGEMENT - TERMINATION                      */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementTermination
/**
 * @section docUKProcManagementTermination ukProc Management: Termination
 *
 * A ukProc Termination is the process performed by the uKernel leading to the
 *  deletion of a ukProc Instance.
 * It consists in the following actions:
 *  - Triggers the ukProc Cleanup and waits for it to be over or aborted (the
 *   subsequent actions of ukProc Termination process will continue only
 *   afterwards).
 *   This action is performed only if uKernel Feature
 *   SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported and if the ukApp
 *   Entry Point ukappCleanup() is not already invoked.
 *  - Set in the ukScheduler (uKernel Scheduler) the Scheduling ukProc State of
 *   the terminated ukProc to Halted (this prevents definitively the terminated
 *   ukProc Instance to be schedulable again).
 *  - An IPC Message of Nature ukProc Raw Data sent to a ukProc Recipient that
 *   has not yet gone to reception are deleted.
 *   The IPC Messages of Nature ukProc IPC Notification already sent by the
 *   terminated ukProc are however not affected by the ukProc Termination (the
 *   Recipient ukProc(s) will received the notification).
 *  - The ongoing reception of other ukProcs expecting IPC message specifically
 *   from the terminated ukProc in Receiving Blocking Mode is aborted with
 *   Status Code DukSTATUS_ERR_UKPROC_TERMINATED (this abortion will set their
 *   Scheduling ukProc State back from Blocked to Ready).
 *  - If the terminated ukProc has been instantiated by its ukProc Parent, then
 *   the uKernel sends, if still present, the uKernel Signal
 *   DukSIGNAL_ID_UKPROC_CHILD_TERMINATED to the ukProc Instance of its ukApp
 *   Parent.
 *  - If the terminated ukProc has instantiated some ukProcs (i.e. the
 *   terminated ukProc is the ukProc Parent of some other ukProcs), then the
 *   uKernel sends to each of its ukProc Child, if still present, the uKernel
 *   Signal DukSIGNAL_ID_UKPROC_PARENT_TERMINATED.
 *  - All the resources used by the terminated ukProc are released:
 *    + All the Extra Address Blocks mapped in the Address Block Windows of
 *   this ukProc are unmapped.
 *    + All the Shared Buffers transferred to this ukProc (i.e. for which the
 *   the current ukProc is the Managing ukProc) are returned to their
 *   respective ukProc Owners. No action is done on the Shared Buffers owned by
 *   this ukProc and already transferred to other ukProcs (they can still be
 *   operated by their Managing ukProc).
 *   This action is performed only if uKernel Feature
 *   SukCONFIG_FEATURE_SHARED_BUFFERS is supported.
 *    + All the DMA Streams assigned to the ukProc are stopped and then
 *   released.
 *   This action is performed only if uKernel Feature
 *   SukCONFIG_FEATURE_MCU_DMA is supported.
 *  - The ukApp Data Volatile Block of terminated ukProc is fully wiped.
 *   No action is performed on the data in its ukApp Data Persistent Block.
 *  - Delete the current ukProc Instance and releases all associated internal
 *   resources in the uKernel.
 *  - In function of the ukApp Profile (see <Profile> field in the ukApp
 *   Descriptor of the ukApp of this ukProc), perform if required a
 *   reincarnation by creating a new ukProc Instance from the same ukApp.
 */


/* ------------------------------------------------------------------------ */
/*                       UKPROC MANAGEMENT - CLEANUP                        */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementCleanup
/**
 * @section docUKProcManagementCleanup ukProc Management: Cleanup
 *
 * The ukProc Cleanup is the process allowing dedicated ukApp code to perform
 *  its necessary cleanup (e.g. wiping of sensitive data, resetting of some
 *  peripherals, ...) before being effectively terminated by the uKernel upon
 *  a ukProc Termination.
 *
 * The ukProc Cleanup is triggered by the uKernel only if uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported. If supported,
 *  the definition of the ukApp Entry Point ukappCleanup() is optional (if not
 *  defined, no ukProc Cleanup occurs).
 *
 * The ukProc Cleanup is performed by the invocation of the dedicated ukApp
 *  Entry Point ukappCleanup() by the uKernel at the beginning of the ukProc
 *  Termination process. It is invoked only once during a ukProc Termination
 *  process: a ukProc Fatal Error triggered during its invocation will not
 *  trigger a new invocation, but will stop immediately its execution, trigger
 *  the finalization of the ukProc Termination process, and set the ukProc
 *  Cleanup as unsuccessful.
 *
 * The execution time allocated by the ukScheduler (uKernel Scheduler) to a
 *  ukProc Instance to perform its cleanup is limited: the invocation of the
 *  ukApp Entry Point ukappCleanup() shall be over before the end of the
 *  Scheduling Time Quantum defined by uKernel Option
 *  DukCONFIG_OPTION_SCHEDULING_TIME_QUANTUM_UKPROC_CLEANUP_systick.
 *  If this Scheduling Time Quantum, which is set as the Scheduling Time
 *  Quantum Allocated during the ukProc Cleanup, is expired, then the execution
 *  of the ukApp Entry Point ukappCleanup() is stopped, and the ukProc
 *  Termination process is finalized, with the ukProc Cleanup process set as
 *  unsuccessful.
 *
 * The ukApp Entry Point ukappCleanup() has a restricted set of uKernel
 *  Privileged Services which can be invoked (see
 *  DukUKAPP_CLEANUP_PRIVILEGED_SERVICES_AUTHORIZED_BITMASK64). If a
 *  unauthorized uKernel Privileged Services is invoked, it is a ukProc Fatal
 *  Error: the execution of the ukApp Entry Point ukappCleanup(), and the
 *  ukProc Termination process is finalized, with the ukProc Cleanup process
 *  set as unsuccessful.

 * The ukProc Cleanup is managed as follows at the very start of the ukProc
 *  Termination process:
 *  - If the ukProc is the Scheduled ukProc, the execution of the ukApp Code
 *   currently executed is stopped.
 *  - The ukProc Watchdog, if started (see ukWatchdogStart()), is stopped.
 *  - The ukProc CPU Stack contents is updated to allow execution of the ukApp
 *   Entry Point ukappCleanup().
 *  - The Scheduling ukProc State is set to Halting (even if it was previously
 *   set to Blocked): the ukProc Instance is schedulable by the ukScheduler
 *   (uKernel Scheduler).
 *  - The ukApp Entry Point ukappCleanup(), if defined in ukApp code, is
 *   invoked, with following parameters:
 *   + (TukUKPROC_TERMINATION_REASON)ukproc_termination_reason__i: The ukProc
 *     Termination Reason provides details on the event (e.g. ukProc End,
 *     ukProc Fatal Error due to lack of credentials, ...) having triggered the
 *     ukProc Termination.
 *   + (TukUKPROC_TERMINATION_INFO)ukproc_termination_info__i: The ukProc
 *     Termination Info value contains additional information (e.g. address in
 *     ukProc code having triggered a ukProc Fatal Error, ...) in the specific
 *     context of the Reason having triggered the ukProc Termination.
 *  - Wait for the invocation of ukApp Entry Point ukappCleanup() to be over,
 *   which is due to either:
 *   + Returning from ukApp Entry Point ukappCleanup().
 *   + Invocation of uKernel Privileged Service ukUKProcEntryPointReturn().
 *   + Invocation of uKernel Privileged Service ukUKProcExit().
 *   + Triggering of a ukProc Fatal Error.
 *   + Expiration of the Scheduling Time Quantum defined by the uKernel Option
 *     DukCONFIG_OPTION_SCHEDULING_TIME_QUANTUM_UKPROC_CLEANUP_systick.
 *  - The Scheduling ukProc State is set to Halted: the ukProc is definitively
 *   unschedulable in the ukScheduler.
 *  - The ukProc Termination process is finalized (see ukProc Termination
 *   documentation).
 *
 * The ukProc Cleanup is successful if the ukApp Entry Point ukappCleanup()
 *  ends from one of the following events:
 *  - Returning (with C-Statement 'return').
 *  - Invoking the uKernel Privileged Service ukUKProcEntryPointReturn().
 *  - Invoking the uKernel Privileged Service ukUKProcExit() with its
 *   boolean parameter <is_exit_in_error__i> set to DukBOOL_FALSE).
 * All the other events leading to the end of this C-Function (ukProc Fatal
 * Error, ...) make the ukProc Cleanup as unsuccessful.
 * If the ukProc Cleanup is unsuccessful, the uKernel Signal
 *  DukSIGNAL_ID_UKPROC_CLEANUP_IN_ERROR is sent to all the other ukProcs. The
 *  ukProc Termination Reason set upon the triggering of the ukProc
 *  Termination process is however never modified, even in case of ukProc Fatal
 *  Error.
 *
 * The success of the ukProc Cleanup process is reported in the field
 *  <IsUKProcCleanupInError> in ukProc Termination Context (see
 *  TukUKPROC_TERMINATION_CONTEXT). The field is set to DukBOOL_FALSE if the
 *  ukProc Cleanup process is successful, else it is set to DukBOOL_TRUE.
 */


/* ------------------------------------------------------------------------ */
/*                     UKPROC MANAGEMENT - FATAL ERROR                      */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementFatalError
/**
 * @section docUKProcManagementFatalError ukProc Management: Fatal Error
 *
 * A ukProc Fatal Error is an error triggered during the execution of a ukProc
 *  Instance by the ukApp code being executed, whose level of severity of the
 *  error prevents further continuation of the execution of ukProc Instance.
 * Such an error will always lead the uKernel to abort immediately the ukProc
 *  execution by triggering a ukProc Abort. The ukProc Abort will lead to the
 *  ukProc Termination and the deletion of the current ukProc Instance.
 * A ukProc Fatal Error is triggered during ukProc Instance execution by any
 *  of the following erroneous condition:
 *  - Invocation of a uKernel Privileged Service:
 *   + Non existing
 *   + Not authorized in the <UKPrivilegedServicesAuthorizedBitMask64> field of
 *    its ukApp Descriptor.
 *   + Requiring specific credentials not present in the <Profile> field of
 *    its ukApp Descriptor.
 *  - Trigger of an MCU Exception Fault, which may be due to:
 *   + A bug in ukApp binary code, due to an issue in the C-Compiler or
 *    C-Linker used generating improper assembly code (i.e. illegal CPU
 *    instruction).
 *   + A bug in ukApp code implementation, leading to:
 *    * An illegal Address Block access (i.e. an access to an Address Block
 *     not authorized for this ukProc, or to an Address Block not mapped in one
 *     of the ukProc Address Block Windows).
 *    * An illegal CPU operation (i.e. divide by zero).
 *    * An access to an MCU Register requiring CPU Privileged Execution Mode
 *     without using dedicated uKernel Privileged Service.
 *   + An unexpected Platform hardware behavior, due to an hardware failure,
 *    or an inconsistency with its specifications (error in provided MCU device
 *    documentation, or issue in its manufacturing batch).
 *   + External perturbations of the Platform hardware, due to electromagnetic
 *    noisy environment, or to a fault injection attack.
 *  - Expiration of the Scheduling Time Quantum Allocated for ukProc Exception
 *   defined in the field
 *   <UKProcExceptionSchedulingTimeQuantumAllocated_systick> in ukApp
 *   Descriptor.
 *   This condition can occur only if uKernel Feature
 *   SukCONFIG_FEATURE_UKPROC_EXCEPTION is supported.
 *  - Expiration of one of the ukProc Watchdog Timers.
 *  - ukProc CPU Stack underflow or overflow.
 */



/* ------------------------------------------------------------------------ */
/*                      UKPROC MANAGEMENT - EXCEPTION                       */
/* ------------------------------------------------------------------------ */
#define docUKProcManagementException
/**
 * @section docUKProcManagementException ukProc Management: Exception
 * (#NOTYETSUPPORTED)
 *
 * The processing of a ukProc Exception consists in the following actions:
 * - If the ukProc for which a ukProc Exception is triggered is the Scheduled
 *  ukProc:
 *  + The execution of the ukApp Entry Point ukappMain() is suspended until
 *   the end of the processing of the ukProc Exception (the full execution
 *   context is saved on the CPU Stack dedicated to the ukProc).
 *  + The ukApp Entry Point ukappException() is invoked and its execution
 *   starts immediately for processing the ukProc Exception.
 *  + Wait for the invocation of ukApp Entry Point ukappException() to be over,
 *   which is due to either:
 *   * Returning from ukApp Entry Point ukappException().
 *   * Invocation of uKernel Privileged Service ukUKProcEntryPointReturn().
 *   * Invocation of uKernel Privileged Service ukUKProcExit().
 *   * Triggering of a ukProc Fatal Error.
 *   * Expiration of the Scheduling Time Quantum Allocated for ukProc
 *      Exception defined in the field
 *      <UKProcExceptionSchedulingTimeQuantumAllocated_systick> of its ukApp
 *      Descriptor.
 *  + The execution of the ukApp Entry Point ukappMain() is resumed from where
 *   it has been suspended.
 * - If the ukProc for which a ukProc Exception is triggered is not the
 *  Scheduled ukProc:
 *  + If the ukProc for which a ukProc Exception is triggered has a higher
 *   Scheduling Priority than the Scheduled ukProc:
 *   * The ukProc for which a ukProc Exception is triggered is elected as
 *    the Scheduled ukProc during the processing of the ukProc Exception.
 *  + Else, the ukProc for which a ukProc Exception is triggered will be
 *   elected as the Scheduled ukProc as soon it has the highest Scheduling
 *   Priority.
 *
 * The ukApp Entry Point ukappException() is never invoked once the ukProc
 *  Termination process has started (and thus it is never invoked during the
 *  execution of the ukApp Entry Point ukappCleanup()).
 */



/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL API - DOC - PRIVILEGED - UKERNEL CORE MANAGEMENT        */
/* //////////////////////////////////////////////////////////////////////// */



/* //////////////////////////////////////////////////////////////////////// */
/*       UKERNEL API - DOC - PRIVILEGED - HARDWARE PLATFORM MANAGEMENT      */
/* //////////////////////////////////////////////////////////////////////// */



/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - DOC - PRIVILEGED - UKAPP MANAGEMENT             */
/* //////////////////////////////////////////////////////////////////////// */



/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - DOC - PRIVILEGED - TIME INFORMATION             */
/* //////////////////////////////////////////////////////////////////////// */


/* //////////////////////////////////////////////////////////////////////// */
/*              UKERNEL API - DOC - PRIVILEGED - IPC MANAGEMENT             */
/* //////////////////////////////////////////////////////////////////////// */


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL API - DOC - PRIVILEGED - ADDRESS BLOCK MANAGEMENT        */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @page docAddressBlockManagement Address Block Management
 * The following sections provides more information on the different actions
 *  relative to Address Block Management.
 */


/* ------------------------------------------------------------------------ */
/*                     ADDRESS BLOCK MANAGEMENT - GENERAL                   */
/* ------------------------------------------------------------------------ */
#define docAddressBlockManagementGeneral
/**
 * @section docAddressBlockManagementGeneral Address Block Management: Generalities
 *
 * An Address Block consists in:
 *  - A label (see TukADDRESSBLOCK_LABEL).
 *  - A continuous range of addresses, defined by its start address and length.
 *  - Attributes for defining its management rights and accesses policy (see
 *   TukADDRESSBLOCK_ATTRIBUTES)
 *
 * The management of Address Block relies on the following ukProc roles:
 *  - Owner ukProc: It is the ukProc instantiated from the ukApp where it has
 *   been defined. This ukProc always keep some management rights on the
 *   Address Block.
 *  - Managing ukProc: It is the ukProc that has currently the usage of the
 *   Address Block. Some kind of Address Block (Shared Buffer) support to have
 *   a Managing ukProc different from its Owner ukProc, by allowing the
 *   transfer of the Address Block to other ukProcs.
 *
 * An Address Block can be of two kinds:
 *  - Extra Address Block (see @ref docAddressBlockManagementExtra).
 *  - Shared Buffer (see @ref docAddressBlockManagementSharedBuffer).
 *
 */


/* ------------------------------------------------------------------------ */
/*             ADDRESS BLOCK MANAGEMENT - EXTRA ADDRESS BLOCK               */
/* ------------------------------------------------------------------------ */
#define docAddressBlockManagementExtra
/**
 * @section docAddressBlockManagementExtra Address Block Management: Extra Address Block
 *
 * The purpose of an Extra Address Block is to give access to extra
 *  address ranges to the ukApp (e.g. memory mapped peripheral registers,
 *  ...). The characteristics of an Extra Address Block are be fully set
 *  in its Extra Address Block Descriptor entry (see
 *  TukADDRESSBLOCK_EXTRA_DESCRIPTOR). The entry is part of the Address Block
 *  Descriptor List of the ukApp Descriptor (see
 *  <AddressBlockExtraDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  An Extra Address Block can be accessed and managed only by the ukProc
 *  instantiated from the ukApp into which it has been defined, which is its
 *  Owner ukProc. It cannot be transferred to or accessed by other ukProcs,
 *  and thus its Managing ukProc remains always its Owner ukProc.
 *  An Extra Address Block can be referenced only inside its Owner ukProc
 *  by using:
 *   - Its label (see TukADDRESSBLOCK_LABEL) set in the field
 *    <AddressBlockExtraLabel> of the Extra Address Block Descriptor entry
 *    defining it.
 *    As the uKernel Privileges Services for managing Address Blocks are
 *    taking as parameter an Address Block Identifier,
 *    ukAddressBlockGetIDFromLabel() has to be used to retrieve it from
 *    its label. The retrieving can be done only in its Owner ukProc.
 *   - The index of its Extra Address Block Descriptor entry in the list
 *    defining the Extra Address Blocks of the ukApp
 *    (see field <AddressBlockExtraDescriptorList> in
 *    TukUKAPP_DESCRIPTOR).
 *    This referencing is encoded as an Address Block Identifier of Nature
 *    DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX. It can be used only in its Owner
 *    ukProc.
 */


/* ------------------------------------------------------------------------ */
/*                 ADDRESS BLOCK MANAGEMENT - SHARED BUFFER                 */
/* ------------------------------------------------------------------------ */
#define docAddressBlockManagementSharedBuffer
/**
 * @section docAddressBlockManagementSharedBuffer Address Block Management: Shared Buffer
 *
 * The purpose of a Shared Buffer is to exchange data between ukProcs by
 *  authorizing access to a same memory area of predefined fixed size.
 *  The characteristics of a Shared Buffer are partially set in its Shared
 *  Buffer Descriptor entry (see TukSHAREDBUFFER_DESCRIPTOR). The entry is
 *  part of the Shared Buffer Descriptor List of the ukApp Descriptor (see
 *  <SharedBufferDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  A Shared Buffer can be accessed and managed by the ukProc instantiated
 *  from the ukApp into which it has been defined, which is its Owner
 *  ukProc. A Shared Buffer can be transferred (see ukSharedBufferTransfer())
 *  only by its Managing ukProc: the ukProc to which it has transferred
 *  becomes its new Managing ukProc. Before transferring the Shared Buffer,
 *  access and managing rights shall have been added to the ukProc to which
 *  it will be transferred (see ukSharedBufferAddCredentials()). Note that
 *  only the access rights are transferred: no copy of the Shared Buffer
 *  contents is performed. Even when transferred, its Owner ukProc still
 *  keeps access to its contents (but not its managing rights).
 *  A Shared Buffer can be referenced:
 *   - Its label (see TukADDRESSBLOCK_LABEL) set in the field
 *    <SharedBufferLabel> of the Shared Buffer Descriptor entry defining it.
 *    As the uKernel Privileges Services for managing Address Blocks are
 *    taking as parameter an Address Block Identifier,
 *    ukAddressBlockGetIDFromLabel() has to be used to retrieve it from
 *    its label. The retrieving can be done only in its Owner ukProc.
 *   - The index of its Shared Buffer Descriptor entry in the list defining
 *    the Shared Buffers of the ukApp (see field
 *    <SharedBufferDescriptorList> in TukUKAPP_DESCRIPTOR)
 *    This referencing is encoded as an Address Block Identifier of Nature
 *    DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX. It can be used only in
 *    its Owner ukProc.
 *   - Its Address Block Bundle Identifier, which can be used even if the
 *    current ukProc is not its Owner ukProc (i.e. when the Shared Buffer
 *    has been transferred). It is a uKernel Identifier that can be obtained
 *    using ukAddressBlockGetBundleID().
 *    This referencing is encoded as an Address Block Identifier of Nature
 *    DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*      UKERNEL API - DOC - PRIVILEGED - ADDRESS BLOCK WINDOW MANAGEMENT    */
/* //////////////////////////////////////////////////////////////////////// */



/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL API - DOC - PRIVILEGED - SHARED BUFFER MANAGEMENT         */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_SHARED_BUFFERS)


#endif /* defined(SukCONFIG_FEATURE_SHARED_BUFFERS) */



/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL API - DOC - PRIVILEGED - PERIPHERAL IRQ MANAGEMENT        */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ)

#endif /* defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ) */


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL API - DOC - PRIVILEGED - MCU REGISTERS MANAGEMENT        */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @page docMCURegistersManagement MCU Registers Management
 * The following sections provides more information on the different actions
 *  relative to MCU Registers Management.
 */

/* ------------------------------------------------------------------------ */
/*                     MCU REGISTERS MANAGEMENT - GENERAL                   */
/* ------------------------------------------------------------------------ */
#define docMCURegistersManagementGeneral
/**
 * @section docMCURegistersManagementGeneral MCU Registers Management: Generalities
 *
 * The ukProcs are executed using the MCU User Execution Mode, and thus
 *  cannot directly access the MCU Registers that require CPU Privileged
 *  Execution Mode without triggering an MCU Exception Fault. In order to allow
 *  the ukProcs to access to such MCU Registers, dedicated uKernel Privileged
 *  Services for handling MCU Register are available (see ukMCURegisterRead(),
 *  ukMCURegisterWrite().
 *
 * The MCU Registers requiring CPU Privileged Execution Mode are generally in
 *  charge of global Platform or MCU management (clock system, power mode, ...),
 *  and also of its security and safety features (memory access authorization,
 *  watchdogs, ...). As most of these MCU Registers may have significant effects
 *  in link with uKernel Security Policy and global Platform stability and
 *  robustness, the uKernel Privileged Services dedicated to their accesses
 *  implement authorization accesses, refined for each ukApp, in order to
 *  prevent that ukApps perform illegal operations affecting robustness,
 *  security or safety.
 *
 * At uKernel level, the MCU Registers that can be accessed by ukApps are
 *  defined in an MCU Registers White List in the uKernel Option
 *  DukCONFIG_OPTION_HW_MCUREGISTER_AUTHORIZED_LIST. This MCU Registers White
 *  List allows to enforce that ukApps can never perform modifications on MCU
 *  Registers not present in this list. This list shall exclude the MCU
 *  Register contents that may affect the uKernel Security Policy, and shall be
 *  minimal in order to circumvent the effects of possible illegal operations
 *  affecting robustness, security or safety.
 *
 * At ukApp level, each ukApp Developer defines its own list of authorized MCU
 *  Registers in the fields <MCURegisterDescriptorCount> and
 *  <MCURegisterDescriptorList> in its ukApp Descriptor (see C-Type
 *  TukUKAPP_DESCRIPTOR). The MCU Registers contained in this list SHALL BE
 *  part of the MCU Register White List, else the ukApp Descriptor is invalid.
 */



/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL API - DOC - PRIVILEGED - DMA STREAM               */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_MCU_DMA)
/**
 * @page docDMAStreamManagement DMA Stream Management
 * The following sections provides more information on the different actions
 *  relative to DMA Stream Management.
 */

/* ------------------------------------------------------------------------ */
/*                       DMA STREAM MANAGEMENT - GENERAL                    */
/* ------------------------------------------------------------------------ */
#define ddocDMAStreamManagementGeneral
/**
 * @section ddocDMAStreamManagementGeneral DMA Stream Management: Generalities
 *
 * An MCU DMA Stream allows a ukProc to initiate during its execution a DMA
 *  transfer using DMA hardware engine present in the MCU. The transfer is
 *  done between configurable memory ranges contained in predefined source
 *  Address Block and destination Address Block.
 */
#endif /* defined(SukCONFIG_FEATURE_MCU_DMA) */


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL API - DOC - PRIVILEGED - WATCHDOG                */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC)

#endif /* defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC) */



/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL API - DOC - PRIVILEGED - RANDOM GENERATOR            */
/* //////////////////////////////////////////////////////////////////////// */



/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL API - DOC - PRIVILEGED - DATA PERSISTENT MANAGEMENT       */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK)
/**
 * @page docDataPersistentManagement Data Persistent Management
 * The following sections provides more information on the different actions
 *  relative to Data Persistent Management, that is access to the ukApp Data
 *  Persistent Block that may be allocated to a ukApp.
 */


/* ------------------------------------------------------------------------ */
/*                    DATA PERSISTENT MANAGEMENT - GENERAL                  */
/* ------------------------------------------------------------------------ */
#define docDataPersistentManagementGeneral
/**
 * @section docDataPersistentManagementGeneral Data Persistent Management: Generalities
 *
 * The technology used for persistent data storage is in general based on
 *  Flash technology. In such memory type, internal hardware granularity
 *  implies that stored data are manipulated only through a memory Address
 *  Block named Flash Sector.
 *
 * A ukApp is owning a ukApp Data Persistent Block if its field
 *  <DataPersistentBlockLength> in its ukApp Descriptor is not null(0).
 *
 * If a ukApp owns a ukApp Data Persistent Block, it can use the following
 *  uKernel Privileged Services to access it:
 *  - ukPersistentDataBlockEraseSector()
 *  - ukPersistentDataBlockWrite()
 *  - ukPersistentDataBlockRead()
 *
 * @implementation The support of ukApp Data Persistent Block and associated
 *  uKernel Privileged Services is conditioned to the support of the uKernel
 *  Feature SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK.
 */

#endif /* defined(SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK) */



/* //////////////////////////////////////////////////////////////////////// */
/*           UKERNEL API - DOC - PRIVILEGED - UKERNEL IMAGE UPDATE          */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE)
/**
 * @page docDataPersistentManagement Data Persistent Management
 * The following sections provides more information on the different actions
 *  relative to Data Persistent Management, that is access to the ukApp Data
 *  Persistent Block that may be allocated to a ukApp.
 */


/* ------------------------------------------------------------------------ */
/*                    DATA PERSISTENT MANAGEMENT - GENERAL                  */
/* ------------------------------------------------------------------------ */
#define docDataPersistentManagementGeneral
/**
 * @section docDataPersistentManagementGeneral Data Persistent Management: Generalities
 *
 * The uKernel Privileged Services dedicated to uKernel Image Update
 *  management can be used only by a ukProc instantiated from a ukApp defined
 *  as the uKernel Image Update ukApp Manager. Only one ukApp  in the ukApps
 *  Bundle can be the uKernel Image Update ukApp Manager.
 * A ukApp is the uKernel Image Update ukApp Manager if it has the flag
 *  DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG set in its ukApp Profile
 *  (see <Profile> field in ukApp Descriptor).
 *
 * The ukApp that is defined as the uKernel Image Update ukApp Manager can use
 *  the following uKernel Privileged Services to access to uKernel Image Update
 *  Storage and to trigger an update:
 *  - ukPersistentDataBlockEraseSector()
 *  - ukPersistentDataBlockWrite()
 *  - ukPersistentDataBlockRead()
 *
 * @implementation The technology used for persistent data storage is in
 *  general based on Flash technology. In such memory type, internal hardware
 *  granularity implies that stored data are manipulated only through an
 *  Address Block named a Flash Sector, grouped in set composing a Flash Bank.
 * The Address Blocks list composing the uKernel Image Update
 *  Storage (see
 *  DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_LIST) may be
 *  contained in several Flash Banks with different Flash Sector lengths (see
 *  DukCONFIG_HW_MCU_DEVICE_FLASH_BANK_LIST for the definition of the Flash
 *  Banks part of the MCU Flash memory of the used MCU Device).

 * @implementation The support of uKernel Image Update and associated uKernel
 *  Privileged Services is conditioned to the support of the uKernel
 *  Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE.
 */

#endif /* defined(SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE) */


/* ######################################################################## */
/*          UKERNEL API - DOC - UKERNEL PRIVILEGED DEBUG SERVICES           */
/* ######################################################################## */
/**
 * @page docUKProcDebug ukProc Debug
 * The following sections provides more information on the different actions
 *  relative to debugging a ukProc.
 *
 * @robustness To avoid including debug code in the uKernel that may lead to
 *  security weaknesses, the uKernel Debug Features are all statically defined
 *  during the compilation of a uKernel Release.
 *  Their associated code is included in the uKernel Release only if the
 *  corresponding uKernel Feature is enabled: thus the uKernel Debug Features
 *  that have not been enabled at compilation time cannot be enabled later at
 *  runtime as their implementation code has not been compiled.
 *
 * @robustness When at least one of the uKernel Debug Feature is enabled, the
 *  internal security level of the uKernel is lowered in order to ease the
 *  debug of the ukApp code.
 *  The uKernel, after its initialization, has normally an access strictly
 *  limited to the ukApp Data Volatile Shared uKernel Services Block
 *  (ukAppDVSUKSVC Block) of each ukApp. But when a uKernel Debug Feature is
 *  enabled, the uKernel implementation of the Debug Features has then extended
 *  access to the whole code and data of the ukApp (this extended access is
 *  needed to allow uKernel Privileged Debug Services to retrieve needed debug
 *  parameters and data directly; as else using the ukAppDVSUKSVC Block would
 *  imply modifying its contents when using debug functionalities, and thus
 *  would imply altering more significantly the ukProc execution path compared
 *  to when uKernel Debug Features are not enabled).
 *
 * @robustness In order to guarantee the security level and robustness of the
 *  uKernel, as soon as the uKernel has been configured for a Production
 *  Release (see SukCONFIG_FEATURE_PRODUCTION_RELEASE), then whatever the
 *  uKernel Debug Features enabled, NONE of the uKernel Privileged Debug
 *  Services are available (indeed none of the uKernel Core implementation
 *  dedicated to debugging is compiled in the uKernel Release).
 *
 * @implementation In order to minimize the impact on the ukApp code, the
 *  uKernel Privileged Debug Service have their associated C-Functions defined
 *  as a null function (i.e. perform nothing and do not generate any code) when
 *  associated uKernel Debug Features are not enabled.
 *
 * @implementation The availability of these uKernel Privileged Debug Services
 *  are conditioned to dedicated uKernel Debug Features (see
 *  SukCONFIG_FEATURE_DEBUG_xxx).
 */


/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL API - DOC - PRIVILEGED - DEBUG - UKPROC DEBUG TRACE       */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC)
#define docUKProcDebugTrace
/**
 * @page docUKProcDebugTrace ukProc Debug Trace
 * The following sections provides more information on the different actions
 *  relative to Debug Trace printing by ukProcs.
 */


/* ------------------------------------------------------------------------ */
/*                           DEBUG TRACE - GENERAL                          */
/* ------------------------------------------------------------------------ */
#define docUKProcDebugTraceGeneral
/**
 * @section docUKProcDebugTraceGeneral ukProc Debug Trace: Generalities
 *
 * If ukProc Debug Trace is supported, the following uKernel Service are
 *  available for printing ukProc Debug Traces:
 *  - ukDebugTracePrint: Print a Null Terminated String (NTString).
 *  - ukDebugTracePrintf: Print a string resulting from the processing of
 *   printf like format Null Terminated String (NTString) with associated
 *   format values passed as arguments. Only a restricted set of formatting
 *   marks are supported, and some proprietary ones have also been added for
 *   convenience and code efficiency.
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
 * @implementation If more characters than the uKernel Option
 *  DukCONFIG_OPTION_DEBUG_TRACE_LENGTH_PER_PRINT_MAX is printed on Debug Trace
 *  during a print, subsequent characters are silently discarded, and a
 *  special character DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is set as
 *  last character printed.
 *  Additional formatting templates may be added by the uKernel (header,
 *  newline prefix) to the Debug Trace. These formatting templates are not
 *  counted in the computed length per print.
 */


/* ------------------------------------------------------------------------ */
/*              DEBUG TRACE - PRINTF STANDARD FORMAT SPECIFIERS             */
/* ------------------------------------------------------------------------ */
#define docUKProcDebugTracePrintfStandard
/**
 * @section docUKProcDebugTracePrintfStandard ukProc Debug Trace: Printf Standard Format Specifiers
 *
 * The following printf() C11 standard Format Specifiers supported in a Format
 *  NTString:
 *  - "%C": Print a character.
 *   + Description: Print the character given in argument.
 *   + Arguments:
 *    * (TukCHAR)<character>: Character to print.
 *       Only the lowest 8 bits corresponding to C-Type TukCHAR from the 32-bit
 *       value argument are used.
 *   + Format field modifiers:
 *    * <none>:
 *   + Examples:
 *    * ("%c", 'A')            => "A"
 *    * ("%c", 0x30313233)     => "3"
 *
 *  - "%S": Print a NTString.
 *   + Description: Print the NTString (Null Terminated String) whose address
 *     is given in argument.
 *   + Arguments:
 *    * (TukNTCSTRING_ADDRESS)<ntstring_addr>: Address of the NTString to
 *       print.
 *       If the length of NTString is strictly greater than
 *       DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX, then the NTString is
 *       not printed, and the error character
 *       DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED is printed in place.
 *   + Format field modifiers:
 *    * "%nns": <nn> being a 2-digit decimal number indicating the required
 *       count of characters to use for printing the NTString. If the NTString
 *       length is lower than this required count, then padding with space
 *       character ' ' is added to the left. If the NTString length is strictly
 *       greater than this required count, then only the character '#' is
 *       printed a number of times corresponding to the required count (the given
 *       NTString is not printed).
 *    * "%-nns": Same as for format field modifier "%nns", but the padding is
 *       added to the right.
 *    * "%*s": Same as for format field modifier "%nns", but <*> indicates
 *       that the count of characters to use for printing the NTString is given
 *       in a first additional argument.
 *    * "%-*s": Same as for format field modifier "%*s", but the padding is
 *       added to the right.
 *   + Examples:
 *    * ("%s", "")                   => ""
 *    * ("%s", "ABCDEFGH")           => "ABCDEFGH"
 *    * ("%-10s", "ABCDEFGH")        => "ABCDEFGH  "
 *    * ("%10s", "ABCDEFGH")         => "  ABCDEFGH"
 *    * ("%*s", 12, "ABCDEFGH")      => "    ABCDEFGH"
 *    * ("%4s", "ABCDEFGH")          => "####"
 *    * ("%s", DukADDRESS_IGNORE)    => ""
 *
 *  - "%D": Print a numerical value as a signed decimal value.
 *   + Description: Print the 32-bit or 64-bit value given in argument as a
 *     signed decimal value. If the value is negative, the character '-' is
 *     added before the digits representing the signed decimal value.
 *   + Arguments:
 *    * (TukUINT32)<value32>: 32-bit value to be printed (default if format
 *       field modifier "%LD" or "%LLD" are not used).
 *    * (TukUINT64)<value64>: 64-bit value to be printed.
 *   + Format field modifiers:
 *    * "%LD": Argument is a 32-bit value <value32>.
 *    * "%LLD" : Argument is a 64-bit value <value64>.
 *    * "%nnD": <nn> being a 2-digit decimal number indicating the required
 *       count of digits to use for printing given signed decimal value. If
 *       the number of digits for representing the signed decimal value is
 *       lower than this required count, then padding with space character ' '
 *       is added to the left. If the number of digits for representing the
 *       signed decimal value is strictly greater than this required count,
 *       then only the character '#' is printed a number of times corresponding
 *       to the required count (the signed decimal value is not printed).
 *    * "%-nnU": Same as for format field modifier "%nnD", but the padding is
 *       added to the right.
 *    * "%0nnU": Same as for format field modifier "%nnD", but the padding
 *       added to the left is done with '0' character.
 *    * "%+nnU": Same as for format field modifier "%nnD", but the character
 *       for the sign ('+' or '-') is systematically added before the digits
 *       representing the signed decimal value.
 *   + Examples:
 *    * ("%D", 1)                    => "1"
 *    * ("%D", -1)                   => "-1"
 *    * ("% D", 1)                   => " 1"
 *    * ("% D", -1)                  => "-1"
 *    * ("%+D", 1)                   => "+1"
 *    * ("%+D", -1)                  => "-1"
 *    * ("%4D", 1)                   => "   1"
 *    * ("%04D", 1)                  => "0001"
 *    * ("%-4D", 1)                  => "1   "
 *    * ("%LD" , 0x11223344)         => "287454020"
 *    * ("%LLD", 0x1122334455667788) => "1234605616436508552"
 *
 *  - "%U": Print a numerical value as a unsigned decimal value.
 *   + Description: Print the 32-bit or 64-bit value given in argument as a
 *     unsigned decimal value.
 *   + Arguments:
 *    * (TukUINT32)<value32>: 32-bit value to be printed (default if format
 *       field modifier "%LU" or "%LLU" are not used).
 *    * (TukUINT64)<value64>: 64-bit value to be printed.
 *   + Format field modifiers:
 *    * "%LU": Argument is a 32-bit value <value32>.
 *    * "%LLU" : Argument is a 64-bit value <value64>.
 *    * "%nnU": <nn> being a 2-digit decimal number indicating the required
 *       count of digits to use for printing given unsigned decimal value. If
 *       the number of digits for representing the unsigned decimal value is
 *       lower than this required count, then padding with space character ' '
 *       is added to the left. If the number of digits for representing the
 *       unsigned decimal value is strictly greater than this required count,
 *       then only the character '#' is printed a number of times corresponding
 *       to the required count (the unsigned decimal value is not printed).
 *    * "%-nnU": Same as for format field modifier "%nnU", but the padding is
 *       added to the right.
 *    * "%0nnU": Same as for format field modifier "%nnU", but the padding
 *       added to the left is done with '0' character.
 *   + Examples:
 *    * ("%U", 1)                    => "1"
 *    * ("%U", -1)                   => "1"
 *    * ("%4U", 1)                   => "   1"
 *    * ("%04U", 1)                  => "0001"
 *    * ("%-4U", 1)                  => "1   "
 *    * ("%LU" , 0x11223344)         => "287454020"
 *    * ("%LLU", 0x1122334455667788) => "1234605616436508552"
 *
 *  - "%X": Print a numerical value as an hexadecimal value.
 *   + Description: Print the 32-bit or 64-bit value given in argument as an
 *     hexadecimal value.
 *   + Arguments:
 *    * (TukUINT32)<value32>: 32-bit value to be printed (default if format
 *       field modifier "%LX" or "%LLX" are not used).
 *    * (TukUINT64)<value64>: 64-bit value to be printed.
 *   + Format field modifiers:
 *    * "%LX": Argument is a 32-bit value <value32>.
 *    * "%LLX" : Argument is a 64-bit value <value64>.
 *    * "%nnX": <nn> being a 2-digit decimal number indicating the required
 *       count of digits to use for printing given hexadecimal value. If the
 *       number of digits for representing the hexadecimal value is lower than
 *       this required count, then padding with space character ' ' is added to
 *       the left. If the number of digits for representing the hexadecimal
 *       value is strictly greater than this required count, then only the
 *       character '#' is printed a number of times corresponding to the
 *       required count (the hexadecimal value is not printed).
 *    * "%-nnX": Same as for format field modifier "%nnX", but the padding is
 *       added to the right.
 *    * "%0nnX": Same as for format field modifier "%nnX", but the padding
 *       added to the left is done with '0' character.
 *   + Examples:
 *    * ("%X", 1)                    => "1"
 *    * ("%X", -1)                   => "FFFFFFFF"
 *    * ("%4X", 16)                  => "  10"
 *    * ("%04X", 16)                 => "0010"
 *    * ("%-4X", 16)                 => "10  "
 *    * ("%LX" , 0x11223344)         => "11223344"
 *    * ("%LLX", 0x1122334455667788) => "1122334455667788"
 *
 *  - "%B": Print a numerical value as a binary value.
 *   + Description: Print the 32-bit or 64-bit value given in argument as a
 *     binary value.
 *   + Arguments:
 *    * (TukUINT32)<value32>: 32-bit value to be printed (default if format
 *       field modifier "%LB" or "%LLB" are not used).
 *    * (TukUINT64)<value64>: 64-bit value to be printed.
 *   + Format field modifiers:
 *    * "%LB": Argument is a 32-bit value <value32>.
 *    * "%LLB" : Argument is a 64-bit value <value64>.
 *    * "%nnB": <nn> being a 2-digit decimal number indicating the required
 *       count of digits to use for printing given binary value. If the
 *       number of digits for representing the binary value is lower than
 *       this required count, then padding with space character ' ' is added to
 *       the left. If the number of digits for representing the binary
 *       value is strictly greater than this required count, then only the
 *       character '#' is printed a number of times corresponding to the
 *       required count (the binary value is not printed).
 *    * "%-nnB": Same as for format field modifier "%nnB", but the padding is
 *       added to the right.
 *    * "%0nnB": Same as for format field modifier "%nnB", but the padding
 *       added to the left is done with '0' character.
 *   + Examples:
 *    * ("%B", 6)                    => "110"
 *    * ("%4B", 6)                   => " 110"
 *    * ("%04B", 6)                  => "0110"
 *    * ("%-4B", 6)                  => "110 "
 *    * ("%LB" , 0x11223344)         => "00010001001000100011001101000100"
 *    * ("%LLB", 0x1122334455667788) => "0001000100100010001100110100010001010101011001100111011110001000"
 *
 *  - "%%": Print '%' character.
 *   + Description: Print the '%' character.
 *   + Arguments:
 *    * <none>
 *   + Format field modifiers:
 *    * <none>
 *   + Examples:
 *    * ("%%")            => "%"
 */


/* ------------------------------------------------------------------------ */
/*             DEBUG TRACE - PRINTF PROPRIETARY FORMAT SPECIFIERS           */
/* ------------------------------------------------------------------------ */
#define docUKProcDebugTracePrintfProprietary
/**
 * @section docUKProcDebugTracePrintfProprietary ukProc Debug Trace: Printf Proprietary Format Specifiers
 *
 * The following uKernel proprietary Format Specifiers are supported in a
 *  Format NTString:
 *  - "%N": Discard an argument from given arguments list.
 *   + Description: Discard an argument from given arguments list containing
 *     the values for each of the formatting marks present in the given Format
 *     NTString.
 *     The argument discarded may be a 32-bit (C-Type TukUINT32) or 64-bit
 *     (C-Type TukUINT64) value.
 *   + Arguments:
 *    * (TukUINT32)<value32>: 32-bit value to be discarded.
 *    * (TukUINT64)<value64>: 64-bit value to be discarded.
 *   + Format field modifiers:
 *    * 'l', 'L': Discarded argument is a 32-bit value <value32>.
 *    * 'll', 'LL': Discarded argument is a 64-bit value <value64>.
 *   + Examples:
 *    * ("%N %U", 0x11223344, 1)            => " 1"
 *    * ("%LN %U", 0x11223344, 1)           => " 1"
 *    * ("%LLN %U", 0x1122334455667788, 1)  => " 1"
 *
 *  - "%Kb": Print a banner.
 *   + Description: Print a banner on a line, composed of a given NTString
 *     centered in the middle of the line, surrounded by a given character
 *     repeated to compose its left and right side.
 *   + Arguments:
 *    * (TukCHAR)<char_surrounding>: Character composing the left and right
 *       part of the banner.
 *       This character has to be an ASCII character in range [32 ... 126].
 *    * (TukNTCSTRING_ADDRESS)<ntstring_addr>: Address of the NTString
 *       printed in the middle of the line.
 *       If the given NTString is not contained in the authorized Address
 *       Block(s) for the uKernel Entity printing on Debug Trace, only the
 *       error character DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED
 *       is printed in place of the NTString in the Debug Trace.
 *   + Format field modifiers: None supported
 *   + Examples:
 *    * ("%Kb", '=', "TITLE")    => "========= TITLE ========="
 *    * ("%Kb", '-', "SUBTITLE") => "-------- SUBTITLE -------"
 *    * ("%Kb", '-', "")         => "-------------------------"
 *
 *  - "%Kc": Print a given character a certain number of times.
 *   + Description: Print a given character a certain number of times. The
 *     number of times to print the given character can either be part of the
 *     Format specifier when indicating a given a expected length, or given
 *     as an argument.
 *     The character cannot be repeated more than the count of characters given
 *     by DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED.
 *   + Arguments:
 *    * (TukCHAR)<char_repeated>: Character to be printed repeatedly.
 *       This character has to be an ASCII character in range [32 ... 126].
 *   + Format field modifiers:
 *    * "%nnKc": <nn> being a 2-digit decimal number indicating the number of
 *       time the character has to be repeated.
 *    * "%*Kc": <*> indicating that a first additional argument is given,
 *       containing the number of times the character has to be repeated.
 *   + Examples:
 *    * ("%Kc", '=')      => "="
 *    * ("%5Kc", '=')     => "====="
 *    * ("%*Kc", 8, '=')  => "========"
 *
 *  - "%Kk": Print formatted size in Kilobytes.
 *   + Description: Print the given value as a size value in kilobytes.
 *    The print format used is as follows: "<k...k>.<dd> KB", where:
 *     --- <k...k> is the decimal value of the size in kilobytes. The number of
 *        digit depends of the Format specifier used.
 *     --- <cc> is a 2-digit decimal value representing the cents of the size
 *        in kilobytes.
 *   + Arguments:
 *    * (TukUITN32)<size_value32>: 32-bit value of the size to print in
 *       Kilobytes.
 *   + Format field modifiers:
 *    * "%nnKk": <nn> being a 2-digit decimal number indicating the required
 *       count of digits to use for printing the <k...k> part of the size in
 *       kilobytes. If the number of digits for representing the <k...k> part
 *       is lower than this required count, then padding with space character
 *       ' ' is added to the left. If the number of digits for representing the
 *       <k...k> part is strictly greater than this required count, then only
 *       the character '#' is printed a number of times corresponding to the
 *       required count (the size value is not printed).
 *    * "%0nnKk": Same as for format field modifier "%nnKk", but the padding
 *       is done with character '0'.
 *   + Examples:
 *    * ("%Kk", 2048)     => "2.00 KB"
 *    * ("%Kk", 2304)     => "2.25 KB"
 *    * ("%3Kk", 2304)    => "  2.25 KB"
 *    * ("%03Kk", 2304)   => "002.25 KB"
 *    * ("%1Kk", 20000)   => "#.## KB"
 *
 *  - "%Kv": Print formatted Version value (see TukVERSION).
 *   + Description: Print the given value as Version value, by isolating its
 *    different fields (see TukVERSION).
 *    The print format used is as follows: "0x<MM>.<mm>.<uuuu>", where:
 *    * <MM>: <Major> field of the Version in hexadecimal (2 digits).
 *    * <mm>: <Minor> field of the Version in hexadecimal (2 digits).
 *    * <uuuu>: <Micro> field of the Version in hexadecimal (4 digits).
 *   + Arguments:
 *    * (TukVERSION)<version_value>: Value of the Version to print.
 *   + Format field modifiers: None supported
 *   + Examples:
 *    * ("%Kv", 0x11223333)   => "0x11.22.3333"
 *
 *  - "%Kv": Print Status Code value (see TukSTATUS).
 *   + Description: Print the given value as a Status Code value, by isolating
 *    its different fields (see TukSTATUS) and printing associated Nature and
 *    Reason names.
 *    The print format used is as follows:
 *      "0x<ssss> (<status_nature_name>_<status_reason_name>), where:
 *    * <ssss>: Status Code value in hexadecimal (4 digits).
 *    * <status_nature_name>: Name of the Nature of the Status Code.
 *       If Status Code value is invalid, "????" is used instead.
 *    * <status_reason_name>: Name of the Reason of the Status Code.
 *       If Status Code value is invalid, "????" is used instead.
 *   + Arguments:
 *    * (TukSTATUS)<status_code_value>: Value of Status Code to print.
 *   + Format field modifiers: None supported
 *   + Examples:
 *    * ("%Ks", 0x0021)   => "0x0021 (INFO_OK)"
 *    * ("%Ks", 0x0081)   => "0x0081 (ERR_PARAM)"
 *    * ("%Ks", 0x0000)   => "0x0000 (????_????)"
 **/
#endif /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL API - DOC - PRIVILEGED - DEBUG - DEBUG LED           */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_LED)

#endif /* defined(SukCONFIG_FEATURE_DEBUG_LED) */


#endif /* !defined(__ASSEMBLER__) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef DOC_UK_SERVICES_H_INSIDE
#endif /* !defined(DOC_UK_SERVICES_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


