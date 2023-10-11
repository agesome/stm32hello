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
 * @file          uk_services.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  uKernel Services C-Functions sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 *
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the declarations of the C-Functions of the uKernel
 *  Services.
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
 *
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_SERVICES_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_services.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_SERVICES_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_SERVICES_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */



/* ######################################################################## */
/*                  UKERNEL API - UKERNEL PRIVILEGED SERVICES               */
/* ######################################################################## */
/* Hereafter are defined uKernel Privileged Services, which are uKernel API
 *  Entry Points (C-Functions) that require switch to uKernel internal code
 *  executed with CPU Privileged Execution Mode to provide requested service.
 */

/* The C-Functions declarations shall not be done when this file is used by
 *  the C-Assembler. */
#if !defined(__ASSEMBLER__)


/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL API - PRIVILEGED - UKPROC MANAGEMENT               */
/* //////////////////////////////////////////////////////////////////////// */
/** See ukProc Management documentation for more details on the different
 *   actions possible for managing a ukProc (uKernel Process):
 *   @ref docUKProcManagement
 */


/**
 *@}
 * @addtogroup ProcessManagement
 * @{
 */
 /**
 * @brief C-Function triggering a ukProc Exit.
 *
 * This C-Function triggers a ukProc Exit to halt definitively the execution of
 *  current ukProc Instance.
 * The ukProc Exit can be triggered only by the ukApp code itself through the
 *  invocation of this uKernel Privileged Service in one of its ukApp Entry
 *  Point.
 *
 * The ukProc Exit of a ukApp Entry Point is managed by the uKernel as follows
 *  upon invocation of this uKernel Privileged Service:
 * - Invocation from ukApp Entry Point ukappMain() or ukappException():
 *  + The given boolean parameter <is_exit_in_error__i> indicates the nature
 *    of the ukProc Exit:
 *   * DukBOOL_FALSE: Successful end of all the operations of the ukProc
 *      Instance (i.e without reporting any error), which leads to a ukProc
 *      End. The ukProc Termination Reason is set to
 *      DukUKPROC_TERMINATION_REASON_END.
 *   * (other value): An erroneous internal condition during the operations
 *      of the ukProc Instance has been spotted by the ukApp implementation,
 *      which leads to a ukProc Abort.
 *      The ukProc Termination Reason is set to
 *      DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR.
 *  + The given ukProc Termination Info <ukproc_termination_info__i> is
 *    stored in the ukProc Termination Context of the ukApp from which has
 *    been instantiated the current ukProc Instance.
 *
 * - Invocation from ukApp Entry Point ukappCleanup():
 *  + The given boolean parameter <is_exit_in_error__i> indicates the success
 *    of the ukProc Cleanup process:
 *   * DukBOOL_FALSE: ukProc Cleanup process is successful.
 *   * (other value): ukProc Cleanup process is unsuccessful.
 *   Note that the value of the given boolean parameter does not affect the
 *   ukProc Termination Reason (i.e. the value set upon the triggering of the
 *   ukProc Termination process is kept).
 *  + The given ukProc Termination Info <ukproc_termination_info__i> is
 *    ignored.
 *
 * Following a ukProc Exit, the uKernel always triggers a ukProc Termination,
 *  which leads to the deletion of the current ukProc Instance.
 *
 * See ukProc Management documentation for:
 *  - Details on ukProc End:
 *   + @ref docUKProcManagementEnd
 *  - Details on ukProc Abort:
 *   + @ref docUKProcManagementAbort
 *  - Details on ukProc Termination:
 *   + @ref docUKProcManagementTermination
 *
 * @implementation This uKernel Privileged Service, for sure, never returns!
 *
 * @implementation If the uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED is not defined, then invoking
 *  this uKernel Privileged Service will trigger during the ukProc Terminate
 *  process a uKernel Session End with Status Code
 *  DukSTATUS_ERR_UKPROC_TERMINATED, followed by an MCU Reset.
 *
 * @implementation Some additional actions defined in the uKernel Security
 *  Policy may be taken by the uKernel upon a ukProc Exit:
 *   - Analysis the occurrence of such events.
 *   - Report externally the ukProc Exit.
 *   - Prevent further creation of ukProc Instance from the same ukApp.
 *   - Trigger a uKernel Session End (see DukPLATFORM_ATTRIBUTE_TAG_STATE).
 *   - ...
 *
 * @usage This uKernel Privileged Service should be used to end the execution
 *  of a ukProc Instance that needs to be executed only spuriously.
 *
 * @usage This uKernel Privileged Service SHALL BE used to report the detection
 *  of an erroneous internal condition spotted by ukApp implementation during
 *  the operations of its ukProc Instance. This report will allow the uKernel
 *  to retrieve proper associated contextual information and to apply more
 *  efficiently defined uKernel Security Policy.
 *
 * @usage Following a ukProc Exit, the ukProc Termination Context is set with
 *  the information on the termination of the ukProc Instance. This information
 *  can be retrieved using the ukApp Attribute Tag
 *  DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST.
 *
 * @privileged
 *
 * @param[in] (TukBOOL)<is_exit_in_error__i> Boolean indicating if the ukProc
 *  Exit is done without any reported error (DukBOOL_FALSE), or due to an
 *  erroneous internal condition spotted by the ukProc Instance (other value).
 * @param[in] (TukUKPROC_TERMINATION_INFO)<ukproc_termination_info__i> User
 *  value containing additional information in the specific context of the
 *  ukProc Exit (this value is never interpreted by the uKernel; it is just
 *  stored in the ukProc Termination Context).
 *
 * @post This uKernel Privileged Service never returns.
 * 
 */
void ukUKProcExit(TukBOOL                    is_exit_in_error__i,
                     TukUKPROC_TERMINATION_INFO ukproc_termination_info__i);


/**
 *
 * @brief C-Function for returning from a ukApp Entry Point.
 *
 * This C-Function returns from a ukApp Entry Point part of the ukApp code.
 *
 * The return of a ukApp Entry Point using this C-Function is managed by the
 *  uKernel as follows:
 *  - ukappMain(): It is a ukProc Fatal Error, as this C-Function shall not be
 *   used for returning from this ukApp Entry Point (the uKernel Privileged
 *   Service ukUKProcExit() shall be used instead). The uKernel will then
 *   trigger a ukProc Abort with ukProc Termination Reason
 *   DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR.
 *  - ukappCleanup(): The ukProc Cleanup is successful.
 *   Upon return the ukProc Termination process is finalized.
 *  - ukappException(): No error to be reported during ukProc Exception
 *   processing.
 *   Upon return the execution of the ukApp Entry Point ukappMain() will be
 *   resumed.
 *
 * See ukProc Management documentation for:
 *  - Details on ukProc Abort:
 *   + @ref docUKProcManagementAbort
 *  - Details on ukProc Termination:
 *   + @ref docUKProcManagementTermination
 *  - Details on ukProc Cleanup:
 *   + @ref docUKProcManagementCleanup
 *
 * @privileged
 */
void ukUKProcEntryPointReturn(void);


/**
 * @brief C-Function yielding current ukProc.
 *
 * This C-Function yields the current ukProc in ukScheduler (uKernel Scheduler)
 *  during at least the given Yield Delay <yield_delay_systick__i> in uKernel
 *  SysTicks unit.
 *
 * A Yielded ukProc is set immediately in Scheduling ukProc State Blocked-Yield
 *  in the ukScheduler during at least the given Yield Delay
 *  <yield_delay_systick__i> in uKernel SysTicks unit.
 * As long as the ukProc is in Scheduling ukProc State Blocked-Yield, it is
 *  unschedulable and thus cannot be elected as the Scheduled ukProc.
 *
 * The management of a Yielded ukProc by the ukScheduler depends of the value
 *  of the given Yield Delay <yield_delay_systick__i>:
 *  - Null(0):
 *   + The Scheduling Time Quantum Remaining of the Yielded ukProc is reset to
 *     null(0) in the current Active Scheduling Window. It is thus
 *     unschedulable in the current Active Scheduling Window.
 *   + Once the current Active Scheduling Window is over, that is when all the
 *     other ukProcs in Scheduling ukProc State Ready have their Scheduling
 *     Time Quantum exhausted (i.e. their Scheduling Time Quantum Remaining
 *     having reached null(0)), the Yielded ukProc will have its Scheduling
 *     Time Quantum Remaining reset to its Scheduling Time Quantum Allocated
 *     value, and is again schedulable in the new current Active Scheduling
 *     Window.
 *  - Not null(<>0):
 *   + The Yielded ukProc is set in in Scheduling ukProc State Blocked-Yield.
 *     It remains in this Scheduling ukProc State, and thus unschedulable, as
 *     long as the given Yield Delay <yield_delay_systick> is not over.
 *   + Once the given Yield Delay is over, the Yielded ukProc will have its
 *     Scheduling ukProc State set back to Ready.
 *     Note that it does not implies it will be immediately elected as the
 *     Scheduled ukProc (as it depends of the current Scheduling ukProc State
 *     and Scheduling Properties of the other ukProcs).
 *
 * @implementation In case no schedulable ukProc remains after the current
 *  ukProc being yielded (i.e. none of the ukProcs have their Scheduling ukProc
 *  State set to Ready), then the ukScheduler Idle mode becomes active (the
 *  ukScheduler elects as Scheduled uKproc a virtual ukProc Idle).
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
 * @usage If this uKernel Privileged Service is invoked while in the ukApp
 *  Entry Point ukappCleanup() or ukappException(), it triggers a ukProc Abort
 *  with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS.
 *
 * @privileged
 *
 * @param[in] (TukTIME32_tick)yield_delay_systick__i Minimal delay (in uKernel
 *  SysTicks unit) during which the ukProc is yielded. This delay shall be
 *  lower or equal to DukSCHEDULING_DELAY_MAX_systick. If this delay is null(0)
 *  then the ukProc is yielded only up to the end of the current Active
 *  Scheduling Window.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, then the current ukProc
 *  has not been yielded.
 * @retval DukSTATUS_INFO_OK No error. The ukProc has been yielded for at least
 *  the given Yield Delay <yield_delay_systick__i>.
 * @retval DukSTATUS_ERR_PARAM The given Yield Delay <yield_delay_systick__i>
 *  is strictly greater than DukSCHEDULING_DELAY_MAX_systick.
 *
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS The ukApp Entry
 *  Point ukappCleanup() or ukappException() is currently invoked.
 */
TukSTATUS ukUKProcYield(TukTIME32_tick yield_delay_systick__i);


/**
 * @brief C-Function creating a ukProc Instance.
 *
 * This C-Function creates a ukProc Instance from a ukApp referenced by given
 *  AUID <ukapp_auid__i>.
 *
 * A ukProc Instance can be created from the referenced ukApp only if:
 *  - No ukProc Instance is currently already instantiated from referenced
 *   ukApp (only one ukProc Instance can exist at a time from a given ukApp).
 *  - The referenced ukApp has the ukApp from current ukProc set as ukApp
 *   Parent (see field <ParentASID> in ukApp Descriptor).
 *
 * See ukProc Management documentation for:
 *  - Details on ukProc Creation:
 *   + @ref docUKProcManagementCreation
 *
 * @implementation This uKernel Privileged Service is supported only if uKernel
 *  Feature SukCONFIG_FEATURE_UKAPP_ADMINISTRATION_FINE is supported.
 *
 * @privileged
 *
 * @param[in] (TukUKAPP_AUID)ukapp_auid__i AUID referencing the ukApp from
 *  which a ukProc shall be instantiated from.
 * @param[out] (TukUKPROC_PUID *)ukproc_puid__o Address where returning the
 *  PUID of the ukProc Instance created from the referenced ukApp.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then DukUKPROC_PUID_INVALID
 *  is returned in <ukproc_puid__o> parameter.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_ALREADY A ukProc Instance is currently already
 *  existing from the referenced ukApp.
 * @retval DukSTATUS_ERR_NOT_FOUND The given AUID has not been found in ukApps
 *  Bundle (ukApp Descriptor with this AUID value may have been invalidated
 *  during uKernel Initialization).
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc does not have the
 *  necessary credentials for creating a ukProc Instance from the given ukApp
 *  (the ASID of its ukApp is not the one defined in the <ParentASID> field of
 *  the Descriptor of the ukApp referenced by the given AUID).
 */
TukSTATUS ukUKProcInstantiate(TukUKAPP_AUID     ukapp_auid__i,
                              TukUKPROC_PUID   *ukproc_puid__o);


/**
 * @brief C-Function retrieving the PUID of the current ukProc instance from a
 *  referenced ukApp.
 *
 * This C-Function retrieves the Process Unique Identifier (PUID) of the
 *  current ukProc Instance from the ukApp referenced by the given AUID
 *  <ukapp_auid__i>.
 *
 * @implementation The PUID value is randomized upon each ukProc Instance
 *  creation, ant thus the retrieved PUID will be different upon:
 *  - Each uKernel Session.
 *  - Each time a new ukProc Instance is created from the referenced ukApp.
 *
 * @privileged
 *
 * @param[in] (TukUKAPP_AUID)ukapp_auid__i AUID referencing the ukApp whose
 *  ukProc's PUID has to be retrieved.
 * @param[out] (TukUKPROC_PUID)ukproc_puid__o Address where returning the PUID
 *  value. If Status Code is not DukSTATUS_INFO_OK, then DukUKPROC_PUID_INVALID
 *  is returned.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then DukUKPROC_PUID_INVALID
 *  is returned at the address <ukproc_puid__o>.
 * @retval DukSTATUS_INFO_OK No error. The PUID is returned.
 * @retval DukSTATUS_ERR_NOT_FOUND The given AUID has not been found in ukApps
 *  Bundle (ukApp Descriptor with this AUID value may have been declared as
 *  invalid by uKernel during uKernel Initialization).
 * @retval DukSTATUS_ERR_STATE_INVALID The given AUID has been found in ukApps
 *  Bundle but no ukProc is currently instantiated from the associated ukApp.
 */
TukSTATUS ukUKProcGetPUIDFromAUID(TukUKAPP_AUID     ukapp_auid__i,
                                  TukUKPROC_PUID   *ukproc_puid__o);


/**
 * @brief C-Function retrieving a ukProc Attribute.
 *
 * This C-Function retrieves the current value of a ukProc Attribute from the
 *  ukProc referenced by given PUID <ukproc_puid__i> (see TukUKPROC_PUID).
 * If the special PUID value DukUKPROC_PUID_MYSELF is used, then the referenced
 *  ukProc is the current ukProc.
 *
 * The ukProc Attribute to be retrieved is referenced using given tag
 *  <ukproc_attr_tag__i> (see TukUKPROC_ATTRIBUTE_TAG and
 *  DukUKPROC_ATTRIBUTE_TAG_xxx for the list of ukProc Attributes supported).
 *
 * The retrieved value is returned as a TLV (Tag/Length/Value) structure
 *  (see TukTLV_TAG for details). The contents of the TLV is specific to each
 *  ukApp Attribute (see documentation of each ukApp Attribute).
 * The retrieved value is returned in the <ServiceParameter.Output> field of
 *  the C-Variable GVukappBlockDataSharedUKSVC as follows:
 *  - (TukUINT16)<Padding16>: 16-bit padding for alignment (ignored).
 *  - (TukUKPROC_ATTRIBUTE_TAG> <T>: Tag referencing the Attribute retrieved,
 *   or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *  - (TukTLV_LENGTH) <L>: Length  in bytes of the Value field of the
 *   referenced Attribute, or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *   The maximal possible returned Length is 255 bytes.
 *  - (TukUINT8[]) <V[<L>]>: Value retrieved for the referenced Attribute.
 *   The length of this field is exactly <L> bytes.
 *
 * @implementation The Address of the <V> field of the returned TLV is at an
 *  address guaranteed to be 32-bit word aligned (i.e. multiple of 4).
 *
 * @usage One of the following conditions is necessary for getting the
 *  credentials to retrieve ukProc Attributes from referenced ukProc:
 *  - The referenced ukProc is the current ukProc.
 *  - The current ukProc has the DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the
 *    <Profile> field of its ukApp Descriptor.
 *  - The referenced ukProc has as ukApp Parent (see field <ParentASID> in
 *   ukApp Descriptor) the ukApp of current ukProc.
 *
 * @usage A ukProc Attribute can be used to retrieve data relative to the
 *  current state of a given ukProc, as:
 *  - AUID.
 *  - Scheduling Priority and Quantum.
 *  - Statistic information
 *  - ...
 *
 * @privileged
 *
 * @param[in] (TukUKPROC_PUID)ukproc_puid__i PUID of the ukProc whose Attribute
 *  value has to be retrieved. Special value DukUKPROC_PUID_MYSELF can be used
 *  for referencing the current ukProc.
 * @param[in] (TukUKPROC_ATTRIBUTE_TAG)ukproc_attr_tag__i Tag of the ukProc
 *  Attribute whose current value has to be retrieved (see
 *  DukUKPROC_ATTRIBUTE_TAG_xxx).
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values (and thus returned length in <L> field is
 *  set to null(0)).
 * @retval DukSTATUS_INFO_OK No error. The current value of the referenced
 *  ukProc Attribute has been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given ukProc Attribute Tag is invalid.
 * @retval DukSTATUS_ERR_NOT_FOUND The given PUID is invalid (referenced ukProc
 *  Instance may have been terminated).
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc does not have the
 *  necessary credentials for getting access to the ukProc Attributes of the
 *  referenced ukProc.
 */
TukSTATUS ukUKProcGetAttribute(TukUKPROC_PUID           ukproc_puid__i,
                               TukUKPROC_ATTRIBUTE_TAG  ukproc_attr_tag__i);


/** 
 * @}
 */
/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL API - PRIVILEGED - UKERNEL CORE MANAGEMENT           */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @addtogroup CoreManagement
 * @{
 */
/**
 * @brief C-Function retrieving a uKernel Core Attribute.
 *
 * This C-Function retrieves the current value of a uKernel Core Attribute.
 * The uKernel Core Attribute to be retrieved is referenced using given tag
 *  <ukcore_attr_tag__i> (see TukUKCORE_ATTRIBUTE_TAG and
 *  DukUKCORE_ATTRIBUTE_TAG_xxx for the list of ukProc Attributes supported).
 *
 * The retrieved value is returned as a TLV (Tag/Length/Value) structure
 *  (see TukTLV_TAG for details). The contents of the TLV is specific to each
 *  ukApp Attribute (see documentation of each ukApp Attribute).
 * The retrieved value is returned in the <ServiceParameter.Output> field of
 *  the C-Variable GVukappBlockDataSharedUKSVC as follows:
 *  - (TukUINT16)<Padding16>: 16-bit padding for alignment (ignored).
 *  - (TukUKCORE_ATTRIBUTE_TAG) <T>: Tag referencing the Attribute retrieved,
 *   or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *  - (TukTLV_LENGTH) <L>: Length  in bytes of the Value field of the
 *   referenced Attribute, or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *   The maximal possible returned Length is 255 bytes.
 *  - (TukUINT8[]) <V[<L>]>: Value retrieved for the referenced Attribute.
 *   The length of this field is exactly <L> bytes.
 *
 * @implementation The Address of the <V> field of the returned TLV is at an
 *  address guaranteed to be 32-bit word aligned (i.e. multiple of 4).
 *
 * @usage Some uKernel Core Attributes require as credential that the current
 *  ukProc has the DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the <Profile>
 *  field of its ukApp Descriptor (see DukUKCORE_ATTRIBUTE_TAG_xxx
 *  documentation for the ones requiring such credential).
 *
 * @usage A uKernel Core Attribute can be used to retrieve or update
 *  configuration data of the used uKernel Target, as:
 *  - uKernel identification (Release Version, ...).
 *  - uKernel SysTick configuration.
 *  - ukApps and ukProcs current count.
 *  - uKernel used Memory resources.
 *  - ...
 *
 * @privileged
 *
 * @param[in] (TukUKCORE_ATTRIBUTE_TAG)ukcore_attr_tag__i Tag of the uKernel
 *  Core Attribute whose current value has to be retrieved.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values (and thus returned length in <L> field is
 *  set to null(0)).
 * @retval DukSTATUS_INFO_OK No error. The current value of the referenced
 *  uKernel Core Attribute has been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given uKernel Core Attribute Tag is invalid.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc does not have the
 *  necessary credentials for getting access to the referenced uKernel Core
 *  Attribute.
 */
TukSTATUS ukUKCoreGetAttribute(TukUKCORE_ATTRIBUTE_TAG ukcore_attr_tag__i);

/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL API - PRIVILEGED - HARDWARE PLATFORM MANAGEMENT         */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @addtogroup PlatformManagement
 * @{
 */
/**
 * @brief C-Function retrieving a Platform Attribute.
 *
 * This C-Function retrieves the current value of a Platform Attribute.
 * The Platform Attribute to be retrieved is referenced using given tag
 *  <platform_attr_tag__i> (see TukPLATFORM_ATTRIBUTE_TAG and
 *  DukPLATFORM_ATTRIBUTE_TAG_xxx for the list of Platform Attributes
 *  supported).
 *
 * The retrieved value is returned as a TLV (Tag/Length/Value) structure
 *  (see TukTLV_TAG for details). The contents of the TLV is specific to each
 *  ukApp Attribute (see documentation of each ukApp Attribute).
 * The retrieved value is returned in the <ServiceParameter.Output> field of
 *  the C-Variable GVukappBlockDataSharedUKSVC as follows:
 *  - (TukUINT16)<Padding16>: 16-bit padding for alignment (ignored).
 *  - (TukPLATFORM_ATTRIBUTE_TAG) <T>: Tag referencing the Attribute retrieved,
 *   or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *  - (TukTLV_LENGTH) <L>: Length  in bytes of the Value field of the
 *   referenced Attribute, or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *   The maximal possible returned Length is 255 bytes.
 *  - (TukUINT8[]) <V[<L>]>: Value retrieved for the referenced Attribute.
 *   The length of this field is exactly <L> bytes.
 *
 * @implementation The Address of the <V> field of the returned TLV is at an
 *  address guaranteed to be 32-bit word aligned (i.e. multiple of 4).
 *
 * @usage Some Platform Attributes require as credential that the current
 *  ukProc has the DukUKAPP_PROFILE_PLATFORM_CONFIG_GET_FLAG set in the
 *  <Profile> field of its ukApp Descriptor (see DukPLATFORM_ATTRIBUTE_TAG_xxx
 *  documentation for the ones requiring such credential).
 *
 * @usage A Platform Attribute can be used to retrieve information and
 *  configuration data of the Platform hardware onto which the uKernel is
 *  running, as:
 *  - MCU Identification.
 *  - Platform (board) Identification
 *  - MCU Clocks configuration.
 *  - MCU Memory resources.
 *  - ...
 *
 * @privileged
 *
 * @param[in] (TukPLATFORM_ATTRIBUTE_TAG)platform_attr_tag__i Tag of the
 *  Platform Attribute whose current value has to be retrieved.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values (and thus returned length in <L> field is
 *  set to null(0)).
 * @retval DukSTATUS_INFO_OK No error. The current value of the referenced
 *  Platform Attribute has been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given Platform Attribute Tag is invalid.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc does not have the
 *  necessary credentials for getting access to the referenced Platform
 *  Attribute.
 */
TukSTATUS ukPlatformGetAttribute(
                    TukPLATFORM_ATTRIBUTE_TAG platform_attr_tag__i);

/**
 * @brief C-Function setting a Platform Attribute.
 *
 * This C-Function sets a new value for a Platform Attribute.
 * The Platform Attribute to be set is referenced using given tag
 *  <platform_attr_tag__i> (see TukPLATFORM_ATTRIBUTE_TAG and
 *  DukPLATFORM_ATTRIBUTE_TAG_xxx for the list of Platform Attributes
 *  supported).
 *
 * The new value to be set is retrieved from the <ServiceParameter.Input> field
 *  of the C-Variable GVukappBlockDataSharedUKSVC.
 * The <ServiceParameter.Input> field shall be structured as follows:
 *  - (TukACCESSKEY32)<PlatformAttributeAccessKey32>: 32-bit Access Key used to
 *   prevent Platform Attribute setting from misuse in ukApp code. It shall be
 *   equal to the value retrieved using uKernel Core Tag Attribute
 *   DukUKCORE_ATTRIBUTE_TAG_PLATFORM_ATTRIBUTE_ACCESSKEY.
 *   This field is always cleared (reset to null(0)) after invocation of this
 *   uKernel Privileged Service.
 *  - (TukUINT16)<Padding16>: 16-bit padding for alignment (ignored).
 *  - (TukPLATFORM_ATTRIBUTE_TAG) <T>: Tag of the Attribute to set. It shall be
 *   equal to the one given in parameter <platform_attr_tag__i>.
 *  -(TukTLV_LENGTH) <L>: Length of the Value field to set in bytes. It shall
 *   be equal to the size of the Attribute to set (see Attribute Tag
 *   documentation).
 *  - (TukUINT8[]) <V[<L>]>: Value to set for the referenced Attribute.
 *   The length of this field is exactly <L> bytes.
 *
 * @implementation The Address of the <V> field with the value to set is at an
 *  address guaranteed to be 32-bit word aligned (i.e. multiple of 4).
 *
 * @implementation The setting of some Platform Attributes may not or only
 *  partially supported on some Platform (see uKernel Platform's specific
 *  documentation for details).
 *
 * @usage Setting Platform Attributes require as credential that the current
 *  ukProc has the DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG flag set in the
 *  <Profile> field of its ukApp Descriptor (see DukPLATFORM_ATTRIBUTE_TAG_xxx
 *  documentation for the ones requiring such credential). Else it is a ukProc
 *  Fatal Error, and the uKernel triggers a ukProc Abort with ukProc
 *  Termination Reason DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS.
 *
 * @usage Setting a Platform Attribute can be used to update information and
 *  configuration data of the Platform hardware onto which the uKernel is
 *  running, as:
 *  - Platform state (MCU Reset request, ...).
 *  - MCU Clocks configuration.
 *
 * @privileged
 *
 * @param[in] (TukPLATFORM_ATTRIBUTE_TAG)platform_attr_tag__i Tag of the
 *  Platform Attribute whose current value has to be set. This Tag has to be
 *  equal to the one set in <ServiceParameter.Input> field.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then excepted noted otherwise in
 *  Platform Attribute Tag documentation (see DukPLATFORM_ATTRIBUTE_TAG_xxx) no
 *  update has been made on the referenced Platform Attribute (previous value
 *  is kept).
 *  The Status Code listed hereafter are the generic one relative to the
 *  global management of the setting process of a Platform Attribute.
 *  Additional Status Code may be returned in function of the given Platform
 *  Attribute Tag (see DukPLATFORM_ATTRIBUTE_TAG_xxx for more details).
 * @retval DukSTATUS_INFO_OK No error. The current value of the referenced
 *  Platform Attribute has been properly updated with new given value set in
 *  the <V> field of the TLV set in <ServiceParameter.Input> field.
 * @retval DukSTATUS_ERR_PARAM The given Platform Attribute Tag
 *  <platform_attr_tag__i> is invalid.
 * @retval DukSTATUS_ERR_STRUCT The given Platform Attribute Tag is not
 *  equal to the one set in the <T> field of the TLV set in
 *  <ServiceParameter.Input> field.
 * @retval DukSTATUS_ERR_SIZE The length in <L> field of the TLV set in
 *  <ServiceParameter.Input> is invalid.
 *
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS The current ukProc
 *  does not have the DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG flag
 *  set in the <Profile> field in its ukApp Descriptor.
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS The given Access
 *  Key in <ukimgupd_accesskey32__i> is invalid.
 */
TukSTATUS ukPlatformSetAttribute(
                    TukPLATFORM_ATTRIBUTE_TAG platform_attr_tag__i);

/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL API - PRIVILEGED - UKAPP MANAGEMENT                */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @addtogroup UkappManagement
 * @{
 */
/**
 * @brief C-Function retrieving the ukApp Index (AIDX) of a ukApp referenced by
 *  its AUID.
 *
 * This C-Function retrieves the Application Index (AIDX) of the ukApp
 *  referenced by the given AUID <ukapp_auid__i>.
 * The AIDX value is a sequential index (starting from 0) used to reference
 *  each valid ukApp Descriptor in the ukApps Bundle (see TukUKAPP_AIDX for
 *  details).
 *
 * @privileged
 *
 * @param[in] (TukUKAPP_AUID)app_auid__i AUID for which the corresponding AIDX
 *  needs to be retrieved.
 * @param[out] (TukUKAPP_AIDX *)app_aidx__o Address where returning the AIDX
 *  value. If Status Code is not DukSTATUS_INFO_OK, then DukUKAPP_AIDX_INVALID
 *  is returned.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then DukUKAPP_AIDX_INVALID
 *  is returned at the address <app_aidx__o>.
 * @retval DukSTATUS_INFO_OK No error. The AIDX is returned.
 * @retval DukSTATUS_ERR_NOT_FOUND The given AUID has not been found in ukApps
 *  Bundle (ukApp Descriptor with this AUID value may have been declared as
 *  invalid by the uKernel during uKernel Initialization).
 */
TukSTATUS ukUKAppGetAIDXFromAUID(TukUKAPP_AUID  app_auid__i,
                                 TukUKAPP_AIDX *app_aidx__o);


/**
 * @brief C-Function retrieving a ukApp Attribute.
 *
 * This C-Function retrieves a ukApp Attribute from the ukApp referenced by
 *  given AIDX <ukapp_aidx__i> (see TukUKAPP_AIDX).
 * If the special AIDX value DukUKAPP_AIDX_MYSELF is used, then the referenced
 *  ukApp is the one of the current ukProc.
 *
 * The ukApp Attribute to be retrieved is referenced using given tag
 *  <ukapp_attr_tag__i> (see TukUKAPP_ATTRIBUTE_TAG and
 *  DukUKAPP_ATTRIBUTE_TAG_xxx for the list of ukApp Attributes supported).
 *
 * The retrieved value is returned as a TLV (Tag/Length/Value) structure
 *  (see TukTLV_TAG for details). The contents of the TLV is specific to each
 *  ukApp Attribute (see documentation of each ukApp Attribute).
 * The retrieved value is returned in the <ServiceParameter.Output> field of
 *  the C-Variable GVukappBlockDataSharedUKSVC as follows:
 *  - (TukUINT16)<Padding16>: 16-bit padding for alignment (ignored).
 *  - (TukUKAPP_ATTRIBUTE_TAG> <T>: Tag referencing the Attribute retrieved,
 *   or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *  - (TukTLV_LENGTH) <L>: Length  in bytes of the Value field of the
 *   referenced Attribute, or null(0) if Status Code is not DukSTATUS_INFO_OK.
 *   The maximal possible returned Length is 255 bytes.
 *  - (TukUINT8[]) <V[<L>]>: Value retrieved for the referenced Attribute.
 *   The length of this field is exactly <L> bytes.
 *
 * @implementation The Address of the <V> field of the returned TLV is at an
 *  address guaranteed to be 32-bit word aligned (i.e. multiple of 4).
 *
 * @usage One of the following conditions is necessary for getting the
 *  credentials to retrieve ukApp Attributes from referenced ukApp:
 *  - The referenced ukApp is the one of the current ukProc.
 *  - The current ukProc has the DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the
 *    <Profile> field of its ukApp Descriptor.
 *  - The referenced ukApp has as ukApp Parent (see field <ParentASID> in ukApp
 *   Descriptor) the ukApp of current ukProc.
 *
 * @usage The AIDX is used to reference a ukApp instead of its AUID as
 *  this index value is lighter to manipulate and allows to perform
 *  walk-through without knowing in advance the AUIDs of all of the ukApps
 *  part of the ukApps Bundle.
 *
 * @usage A ukApp Attribute can be used to retrieve configuration data from a
 *  given ukApp, as:
 *  - AUID
 *  - Version
 *  - Name (as NTString)
 *  - Memory sizes
 *  - ...
 *
 * @privileged
 *
 * @param[in] (TukUKAPP_AIDX)ukapp_aidx__i ukApp Index (AIDX) referencing the
 *  ukApp whose Attribute value has to be retrieved. Special value
 *  DukUKAPP_AIDX_MYSELF can be used for referencing the ukApp of the current
 *  ukProc.
 * @param[in] (TukUKAPP_ATTRIBUTE_TAG)ukapp_attr_tag__i Tag of the ukApp
 *  Attribute whose current value has to be retrieved (see
 *  DukUKAPP_ATTRIBUTE_TAG_xxx).
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values (and thus returned length in <L> field is
 *  set to null(0)).
 * @retval DukSTATUS_INFO_OK No error. The current value of the referenced
 *  ukApp Attribute has been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given ukApp Attribute Tag is invalid.
 * @retval DukSTATUS_ERR_NOT_FOUND The given AIDX is invalid.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc does not have the
 *  necessary credentials for getting access to the referenced ukApp Attributes
 *  of the referenced ukApp.
 */
TukSTATUS ukUKAppGetAttribute(TukUKAPP_AIDX             ukapp_aidx__i,
                              TukUKAPP_ATTRIBUTE_TAG    ukapp_attr_tag__i);

/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL API - PRIVILEGED - TIME INFORMATION                */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @addtogroup TimeInformation
 * @{
 */
/**
 * @brief C-Function returning the Uptime since the start of current uKernel
 *  Session in microseconds (us).
 *
 * This C-Function returns the current uKernel Uptime since the start of
 *  current uKernel Session in microseconds (us) as a 64-bit value.
 *
 * @robustness If the uKernel Uptime value is going to overflow the 64-bit
 *  capacity, then the uKernel triggers a uKernel Session End with enough
 *  margin before the overflows occurs to let the current uKernel Session
 *  terminate properly (a new uKernel Session is started automatically
 *  afterwards).
 *
 * @note This uKernel Service is implemented to report as much as possible an
 *  accurate time, even when Platform or MCU current configuration is modified.
 *  Notably the uKernel performs the necessary compensations upon modifications
 *  of the MCU clocks set, or when the uKernel is entering uKernel Low Power
 *  Mode.
 *
 * @implementation The uKernel Session starting reference is the last Platform
 *  reset, and thus null(0) value for uKernel Uptime is aimed to correspond to
 *  the execution of the very first instruction by the MCU after a Platform
 *  reset. This starting reference allows ukProcs to retrieve information of
 *  the time since the start of the current uKernel Session (i.e. since last
 *  MCU Reset), and if need be, to adapt their own internal timing.
 *
 * @usage Execution time of this uKernel Privileged Service is very quick.
 *
 * @privileged
 *
 * @return (TukTIME64_us)Uptime value in microseconds (us) unit.
 */
TukTIME64_us ukUptimeGet_us(void);


/**
 * @brief C-Function returning the Count of uKernel SysTicks since the start
 *  of current uKernel Session.
 *
 * This C-Function returns the Count of uKernel SysTicks since the start of
 *  current uKernel Session as a 64-bit value.
 *
 * The uKernel SysTick counts remains to 0 until the first ukProc being
 *  scheduled by the ukScheduler (uKernel Scheduler). Then the count is
 *  incremented by one(1) each time a uKernel SysTick period is over (see
 *  DukUKCORE_ATTRIBUTE_TAG_SYSTICK_PERIOD_us for retrieving the uKernel
 *  SysTick period).
 *
 * @robustness The Count of uKernel SysTicks cannot overflow, as the uKernel
 *  Uptime in microseconds (us) will always overflow first (see
 *  ukUptimeGet_us()).
 *
 * @warning Upon entering uKernel Low Power Mode, the uKernel SysTick Period
 *  will not be kept constant (as no Systick is occurring). Thus it SHALL NOT
 *  be considered that there is a link between the uKernel Uptime (that is
 *  still counted when uKernel is in uKernel Low Power Mode) and the count of
 *  uKernel SysTicks having occurred since the start of current uKernel
 *  Session.
 *
 * @implementation To enforce uKernel consistency of time measurements the
 *  uKernel SysTick period remains fixed during a whole uKernel Session.
 *  If the uKernel SysTick period is updated, the updated value will be taken
 *  into account only upon the next uKernel Session.
 *
 * @usage Execution time of this uKernel Privileged Service is very quick.
 *
 * @privileged
 *
 * @return (TukTIME64_tick) Count of uKernel SysTicks since the start of the
 *  first ukProc execution in the current uKernel Session.
 */
TukTIME64_tick ukSystickGetCount(void);

/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL API - PRIVILEGED - IPC MANAGEMENT                */
/* //////////////////////////////////////////////////////////////////////// */
/* PRIVATE */

TukSTATUS ukIPCSendNotificationToProcess(TukUKPROC_PUID proc_notified_puid__i);

TukSTATUS ukIPCSendDataToProcess(TukUKPROC_PUID proc_to_puid__i,
                                 TukIPC_MODE     ipc_mode__i);

TukSTATUS ukIPCReceive(TukUKPROC_PUID   proc_from_puid__i,
                       TukIPC_MODE      ipc_mode__i);


TukSTATUS ukIPCSendReceiveDataToProcess(
                        TukUKPROC_PUID  proc_tofrom_puid__i,
                        TukIPC_MODE     ipc_mode__i);


/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - PRIVILEGED - ADDRESS BLOCK MANAGEMENT           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @addtogroup AddressBlockManagement
 * @{
 */
/**
 * @brief C-Function retrieving the Address Block Identifier from Address
 *  Block Label.
 *
 * This C-Function retrieves the Address Block Identifier from given Address
 *  Block Label.
 * The Address Block Label is present in each Address Block Descriptor entry.
 * It allows to references unambiguously an Address Block in the ukApp
 *  where it is defined (see TukADDRESSBLOCK_LABEL for more details).
 *
 * The Nature of the retrieved Address Block Identifier is fixed in function
 *  of the kind of Address Block referenced by the Address Block Label:
 *  - Extra Address Block: DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX
 *  - Shared Buffer: DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCK_LABEL) ab_label__i Address Block Label.
 * @param[out] (TukADDRESSBLOCK_ID *)abid__o Address Block Identifier of the
 *  Address Block with given Address Block Label.
 *  If Status Code is not DukSTATUS_INFO_OK, then DukADDRESSBLOCK_ID_INVALID
 *   is returned.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then returned Address Block
 *  Identifier <abid__o> is set with DukADDRESSBLOCK_ID_INVALID.
 * @retval DukSTATUS_INFO_OK No error. The retrieving of the Address Block
 *  Identifier has been successful.
 * @retval DukSTATUS_ERR_NOT_FOUND The given Address Block Label has not been
 *  found in ukApp Descriptor.
 */
TukSTATUS ukAddressBlockGetIDFromLabel(
                TukADDRESSBLOCK_LABEL   ab_label__i,
                TukADDRESSBLOCK_ID     *abid__o);

/**
 * @brief C-Function retrieving the Bundle Identifier of an Address Block.
 *
 * This C-Function retrieves the Address Block Bundle Identifier of a given
 *  Address Block referenced by its Address Block Identifier.
 *
 * A Bundle Identifier is a global index value, that is unique among all the
 *  ukApps present in the ukApps Bundle. It allows to reference unambiguously
 *  a Shared Buffer among the ukProcs, and has to be used when transferring
 *  Shared Buffer between ukProcs.
 *
 * The returned Address Block Bundle Identifier depends of the Nature of
 *  the given Address Block Identifier:
 *   - DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX: If given Address Block
 *    Identifier is valid, the corresponding Address Block Bundle Identifier
 *    is returned. Else, DukADDRESSBLOCK_ID_INVALID is returned, and Status
 *    Code is DukSTATUS_ERR_PARAM.
 *   - DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID: If given Address Block
 *    Identifier is valid, same value as the one given is returned. If invalid,
 *    DukADDRESSBLOCK_ID_INVALID is returned, and Status Code is
 *    DukSTATUS_ERR_PARAM.
 *   - Other Address Block Identifier Natures are not supported: Returned
 *    Address Block Bundle Identifier value is set with
 *    DukADDRESSBLOCK_ID_INVALID, and Status Code is
 *    DukSTATUS_ERR_NOT_SUPPORTED.
 *
 * As an Address Block Bundle Identifier can reference only a Shared Buffer,
 *  the retrieved Address Block Bundle Identifier is always of Nature
 *  DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 *
 * @usage The Address Block Bundle Identifier value of a Shared Buffer shall
 *  be retrieved for using uKernel Services dedicated to Shared Buffer
 *  management (see ukSharedBufferResetCredentials(),
 *  ukSharedBufferAddCredentials(), ukSharedBufferTransfer()).
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCK_ID)abid__i Address Block Identifier (ABID)
 *  referencing a Shared Buffer.
 * @param[out] (TukADDRESSBLOCK_ID *)abid_bundle__o Address Block Bundle
 *  Identifier of the referenced Shared Buffer.
 *  If an error has occurred, DukADDRESSBLOCK_ID_INVALID is returned.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then returned Address Block Bundle
 *  Identifier <abid_bundle__o> is set with DukADDRESSBLOCK_ID_INVALID.
 * @retval DukSTATUS_INFO_OK No error. The Address Block Bundle Identifier has
 *  been retrieved successfully.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid.
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The Nature of the given Address Block
 *  Identifier is not DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX or
 *  DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 */
TukSTATUS ukAddressBlockGetBundleID(
                TukADDRESSBLOCK_ID    abid__i,
                TukADDRESSBLOCK_ID   *abid_bundle__o);

/**
 * @brief C-Function retrieving information on an Address Block.
 *
 * This C-Function retrieves information (see TukADDRESSBLOCK_INFO) on a
 *  given Address Block referenced by its Address Block Identifier.
 * The retrieved information is returned in the <ServiceParameter.Output>
 *  field of the C-Variable GVukappBlockDataSharedUKSVC. The field is
 *  formatted using the TukADDRESSBLOCK_INFO structure.
 *
 * To be authorized to retrieve the information on the given Address Block,
 *  the current ukProc shall either:
 *   - Be the Owner of the Address Block.
 *   - Having credentials being added on the given Address Block (even if
 *    not currently the Managing uKProc).
 *   - Be instantiated from a ukApp with the flag
 *    DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the <Profile> field in its.
 *    ukApp Descriptor.
 *
 * See TukADDRESSBLOCK_INFO for the information retrieved on the Address Block.
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCK_ID)abid__i Address Block Identifier.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then this function performs no
 *  operation, and the TukADDRESSBLOCK_INFO structure returned is fully null.
 * @retval DukSTATUS_INFO_OK No error. The information on the given Address
 *  Block have been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid.
 * @retval DukSTATUS_ERR_PARAM The Nature of the given Address Block
 *  Identifier is invalid.
 * @retval DukSTATUS_ERR_CREDENTIALS No credentials have been granted to the
 *  current ukProc on the referenced Address Block to retrieve its
 *  information.
 */
TukSTATUS ukAddressBlockGetInfo(
                TukADDRESSBLOCK_ID    abid__i);

/**
 * @}
 */
/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL API - PRIVILEGED - ADDRESS BLOCK WINDOW MANAGEMENT       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @addtogroup AddressBlockWindowManagement
 * @{
 */
/**
 * @brief C-Function mapping an Address Block in the ukProc Address Space.
 *
 * This C-Function maps the Address Block referenced by its given Identifier
 *  in the ukProc Address Space, using the Address Block Window of given
 *  Index.
 *
 * Once the Address Block has been mapped in the ukProc Address Space, the
 *  ukProc can perform direct access operations in the address range of the
 *  Address Block:
 *   - The read access is allowed if the flag
 *    DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG has been setup in the
 *    credentials for the current ukProc.
 *   - The write access is allowed if the flag
 *    DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG has been setup in the
 *    credentials for the current ukProc.
 *
 * An Address Block can be mapped in an Address Block Window of the current
 *  ukProc only under the following conditions:
 *  - The current ukProc is the Owner ukProc or the Managing ukProc of the
 *   Address Block (and thus credentials are present for the current ukProc).
 *  - The Address Block has at least either the read flag (see
 *   DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG) set in the credentials of
 *   the current ukProc.
 *  - The Address Block has not already been mapped in the current ukProc.
 *
 * @implementation A Shared Buffer may be mapped in the Address Space of at
 *  most two different ukProcs at the same time (by its Owner ukProc and its
 *  Managing ukProc).
 *
 * @implementation An Address Block Window is needed to map an Address Block
 *  in the ukProc Address Space. As Address Block Window relies on hardware
 *  feature (in general MPU) to enforce required Security Policy (read/write
 *  access), the number of Address Block Windows that can be simultaneously
 *  active is limited by this hardware (see TukADDRESSBLOCKWINDOW_IDX for
 *  more details).
 *
 * @implementation The mapping/unmapping of an Address Block Window is
 *  an operation efficient in regards of uKernel processing.
 *
 * @usage In order to increase ukApp code robustness, and to minimize the
 *  number of Address Block Windows simultaneously active, it is advised to
 *  map an Address Block Window only during the sequence of code that need
 *  to have access to its address range (i.e. mapping the Address Block just
 *  before the sequence, and unmapping it just after).
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCKWINDOW_IDX)abwidx__i Index of Address Block
 *  Window into which we want to map the given Address Block.
 *  The Index shall be in the range [0 ... DukADDRESSBLOCKWINDOW_IDX_MAX].
 * @param[in] (TukADDRESSBLOCK_ID)abid__i Address Block Identifier of the
 *  Address Block to be mapped.
 *  The Address Block Identifier shall be of Nature
 *   DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX or
 *   DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The mapping has been done successfully.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Windows Index is invalid.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid.
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The given Address Block Identifier
 *  Nature is not supported.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc is not the Managing
 *  ukProc of the referenced Address Block.
 * @retval DukSTATUS_ERR_CREDENTIALS The referenced Address Block does not have
 *  at least read credentials setup for the current ukProc.
 * @retval DukSTATUS_ERR_IN_USE The referenced Address Block Windows is
 *  already mapping another Address Block.
 * @retval DukSTATUS_ERR_ALREADY The referenced Address Block is already
 *  mapped in this ukProc.
 */
TukSTATUS ukAddressBlockWindowMap(TukADDRESSBLOCKWINDOW_IDX     abwidx__i,
                                  TukADDRESSBLOCK_ID            abid__i);


/**
 * @brief C-Function unmapping an Address Block Window from the ukProc Address
 *  Space.
 *
 * This C-Function unmaps the Address Block Window of given Index from the
 *  ukProc Address Space.
 *
 * @implementation If the given Address Block Window was not mapped, this
 *  C-Function does nothing and the operation is considered as successful.
 *
 * @usage Once given Address Block Window is unmapped, if the Address Block has
 *  not the flag DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_OPTIONAL_FLAG set in its
 *  Attributes, any access to its address range is not authorized anymore by
 *  the uKernel: the MCU Exception Fault triggered upon the access will be
 *  a ukProc Fatal Error and the uKernel will trigger a ukProc Abort
 *  with ukProc Termination Reason DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *  If the flag is set, the access to its address range is still authorized by
 *  the uKernel, but performed using MCU Exception Fault (note that the access
 *  may then be quite slower).
 *
 * @usage In order to increase robustness of the ukApp implementation, it is
 *  recommenced to unmap Address Block Window as soon as the Address Block
 *  mapped is not used anymore in a given ukApp code block.
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCKWINDOW_IDX)abwidx__i Index of Address Block
 *  Window to unmap from the ukProc Address Space.
 *  The Index shall be in the range [0 ... DukADDRESSBLOCKWINDOW_IDX_MAX].
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The unmapping has been done successfully.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Window Index is invalid.
 * @retval DukSTATUS_WARN_ALREADY The given Address Block Window was already
 *  not mapped.
 */
TukSTATUS ukAddressBlockWindowUnMap(TukADDRESSBLOCKWINDOW_IDX   abwidx__i);


/**
 * @brief C-Function retrieving the Address Block Identifier mapped in an
 *  Address Block Window.
 *
 * This C-Function retrieves the Address Block Identifier that is currently
 *  mapped in the Address Block Window of given Index.
 *
 * If the Address Block Windows Index is invalid, or if no Address Block is
 *  mapped, then the specific Address Block Identifier value
 *  DukADDRESSBLOCK_ID_INVALID is returned.
 *
 * The Nature of the retrieved Address Block Identifier is fixed in function
 *  of the nature of the Address Block mapped:
 *  - Extra Address Block: DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX
 *  - Shared Buffer: DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCKWINDOW_IDX)abwidx__i Index of Address Block
 *  Window from which we want to retrieve the Identifier of the Address Block
 *  mapped.
 *  The Index shall be in the range [0 ... DukADDRESSBLOCKWINDOW_IDX_MAX].
 * @param[out] (TukADDRESSBLOCK_ID)abid__o Address Block Identifier mapped in
 *  the given Address Block Window, or DukADDRESSBLOCK_ID_INVALID if none is
 *  mapped or if the Status Code is in Error.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The Address Block Identifier mapped
 *  at the given Address Block Window Index has been properly retrieved.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Window Index is invalid.
 * @retval DukSTATUS_ERR_NOT_FOUND No Address Block is mapped in referenced
 *  Address Block Window.
 */
TukSTATUS ukAddressBlockWindowGetMapped(
                TukADDRESSBLOCKWINDOW_IDX   abwidx__i,
                TukADDRESSBLOCK_ID         *abid__o);

/**
 *@}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*           UKERNEL API - PRIVILEGED - SHARED BUFFER MANAGEMENT            */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_SHARED_BUFFERS)

/**
 * @addtogroup SharedBufferManagement
 * @{
 */
/**
 * @brief C-Function clearing all the other ukProcs credentials of a Shared
 *  Buffer.
 *
 * This C-Function clears all the credentials granted to other ukProcs of a
 *  Shared Buffer referenced by given Address Block Identifier.
 *
 * This C-Function can be invoked only by the Owner ukProc of the Shared Buffer
 *  and if the Managing ukProc is the Owner ukProc (i.e. the Shared Buffer has
 *  not been transferred to another ukProc).
 *
 * @param[in] (TukADDRESSBLOCK_ID)shbuf_abid_bundle__i Address Block Identifier
 *  of the Shared Buffer whose all credentials (Address Block Attributes) have
 *  to be cleared.
 *  The Address Block Identifier shall be of Nature
 *   DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID (see
 *   ukAddressBlockGetBundleID()).
 *
 * @privileged
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. All the credentials (Address Block
 *  Attributes) granted to other ukProc have been cleared.
 * @retval DukSTATUS_WARN_IN_USE The referenced Shared Buffer has been
 *  transferred to another ukProc (but is not mapped by this other ukProc).
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The Nature of the given Address Block
 *  Identifier is not DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc is not the Owner ukProc
 *  of the referenced Shared Buffer.
 * @retval DukSTATUS_WARN_IN_USE The referenced Shared Buffer has been
 *  transferred to another ukProc and is mapped.
 */
TukSTATUS ukSharedBufferResetCredentials(
              TukADDRESSBLOCK_ID shbuf_abid_bundle__i);


/**
 * @brief C-Function setting up credentials on a Shared Buffer for another
 *  ukProc.
 *
 * This C-Function setups credentials on a Shared Buffer for another ukProc.
 * This C-Function allows to prepare the transfer of a Shared Buffer to another
 *  ukProc by setting up for it the necessary credentials (access and
 *  management rights). The credentials are given using flags in the Address
 *  Block Attributes of Shared Buffer.
 *
 * This C-Function can be invoked on a Shared Buffer only by the following
 *  ukProcs:
 *  - Its Owner ukProc.
 *  - Its Managing ukProc if it has been setup with the credential
 *   DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG.
 *
 * This C-Function cannot modify the credentials on a Shared Buffer of a
 *  ukProc for which credentials have already been setup on this Shared Buffer
 *  (this rule covers its Owner and Managing ukProc).
 *
 * Only the following credentials (Address Block Attributes) can be setup to
 *  another ukProc (see DukADDRESSBLOCK_ATTRIBUTES_SHAREDBUFFER_MASK):
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG.
 *
 * @implementation For a given Shared Buffer, the number of different ukProcs
 *  to which credentials can be setup is limited to the maximal value
 *  DukCONFIG_OPTION_SHAREDBUFFER_TRANSFER_DIFFERENT_UKPROC_COUNT_MAX.
 *
 * @usage The transfer of a Shared Buffer cannot be done to a ukProc that has
 *  not been granted with credentials using this C-Function.
 *
 * @usage The credentials given to a ukProc on a given Shared Buffer remain
 *  active even after a transfer to another ukProc (thus allowing the
 *  Shared Buffer to be transferred back). The credentials can only be cleared
 *  by the Owner ukProc of the Shared Buffer (see
 *  ukSharedBufferResetCredentials()).
 *
 * @usage This C-Function can be invoked even if the Owner ukProc of the Shared
 *  Buffer has been terminated.
 *
 * @usage This C-Function can be invoked even if the Shared Buffer is currently
 *  mapped in an Address Block Window.
 *
 * @usage If credentials that have already been setup on a Shared Buffer need
 *  to be modified, the Owner ukProc has to first clear all the credentials
 *  given to ukProcs (see ukSharedBufferResetCredentials()).
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCK_ID)shbuf_abid_bundle__i Address Block Identifier
 *  of the Shared Buffer onto which credentials have to be setup.
 *  The Address Block Identifier shall be of Nature
 *   DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID (see
 *   ukAddressBlockGetBundleID()).
 * @param[in] (TukUKPROC_PUID)proc_to_puid__i PUID of the ukProc onto which
 *  credentials have to be setup.
 * @param[in] (TukADDRESSBLOCK_ATTRIBUTES)shbuf_proc_attr__i Credentials value
 *  (Address Block Attributes) that have to be setup onto the given ukProc.
 *  Only the flags set in
 *  DukADDRESSBLOCK_ATTRIBUTES_SHAREDBUFFER_MASK are authorized in this value.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The given Credentials on the referenced
 *  Shared Buffer have been properly setup on the referenced ukProc.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid
 * @retval DukSTATUS_ERR_PARAM The given Credentials are invalid (only the
 *  flags set in DukADDRESSBLOCK_ATTRIBUTES_SHAREDBUFFER_MASK are allowed).
 * @retval DukSTATUS_ERR_NOT_FOUND The given PUID is invalid (referenced ukProc
 *  Instance may have been terminated).
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The Nature of the given Address Block
 *  Identifier is not DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc is not the Managing
 *  ukProc of the referenced Shared Buffer.
 * @retval DukSTATUS_ERR_CREDENTIALS The Managing ukProc has not been granted
 *  with the necessary credentials to perform this operation (it has not the
 *  flag DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG set in its own
 *  credentials on the referenced Shared Buffer).
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The given PUID references either the
 *  Owner ukProc or the Managing ukProc (their credentials cannot be changed).
 * @retval DukSTATUS_ERR_ALREADY The given PUID has already been setup with
 *  credentials for the referenced Shared Buffer (they cannot be modified until
 *  fully reset: see ukSharedBufferResetCredentials()).
 * @retval DukSTATUS_ERR_NO_RESOURCE The maximal number of ukProcs onto
 *  which credentials can be setup has been reached for the referenced Shared
 *  Buffer.
 */
TukSTATUS ukSharedBufferAddCredentials(
              TukADDRESSBLOCK_ID           shbuf_abid_bundle__i,
              TukUKPROC_PUID               ukproc_to_puid__i,
              TukADDRESSBLOCK_ATTRIBUTES   shbuf_proc_attr__i);

/**
 * @brief C-Function transferring a Shared Buffer to another ukProc.
 *
 * This C-Function transfers the given Shared Buffer to the given ukProc.
 *
 * The transfer of a Shared Buffer can be done only when all the following
 *  conditions are met:
 *  - The current ukProc is the Managing ukProc of the given Shared Buffer.
 *  - The Shared Buffer is not mapped in an Address Block Window of its
 *   Managing ukProc (this condition does not apply if its Managing ukProc is
 *   its Owner ukProc).
 *  - The ukProc to which it has to be transferred is either its Owner ukProc,
 *   or a ukProc that has been granted with some credentials (see
 *   ukSharedBufferAddCredentials()).
 *
 * After that the Shared Buffer has been transferred, the ukProc to which the
 *  transfer has been made become the new Managing ukProc of the given Shared
 *  Buffer.
 *
 * The Managing ukProc of a Shared Buffer can perform the following operations
 *  on it:
 *  - Read its contents if the flag
 *   DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG is set in its credentials,
 *   by mapping it in its Address Space (see ukAddressBlockWindowMap()).
 *  - Write its contents (if the flag
 *   DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG is set in its credentials)
 *   by mapping it in its Address Space (see ukAddressBlockWindowMap()).
 *  - Adding credentials on the Shared Buffer for other ukProcs if
 *   the flag DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG is set in
 *   its credentials (see ukSharedBufferAddCredentials()).
 *  - Transfer the Shared Buffer to another ukProc if the flag
 *   DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG is set in its credentials.
 *  - Transfer the Shared Buffer back to its Owner ukProc.
 *
 * The Owner ukProc of a Shared Buffer can still perform the following
 *  operations on it even if it is not anymore the Managing ukProc:
 *  - Read its contents by mapping it in its Address Space (see
 *   ukAddressBlockWindowMap()).
 *  - Write its contents by mapping it in its Address Space (see
 *   ukAddressBlockWindowMap()).
 *
 * @implementation If the Managing ukProc of a Shared Buffer is terminated,
 *  then the Shared Buffer is transferred back automatically to its Owner
 *  ukProc, and all the credentials set on the Shared Buffer are cleared (as if
 *  ukSharedBufferResetCredentials() has been invoked).
 *
 * @usage To transfer back a Shared Buffer to its Owner ukProc it is
 *  recommended to use the special PUID value DukUKPROC_PUID_OWNER. This
 *  special PUID value will work even if the Owner ukProc Instance has been
 *  terminated.
 *
 * @privileged
 *
 * @param[in] (TukADDRESSBLOCK_ID)shbuf_abid_bundle__i Address Block Identifier
 *  of the Shared Buffer to be transferred.
 *  The Address Block Identifier shall be of Nature
 *   DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID (see
 *   ukAddressBlockGetBundleID()).
 * @param[in] (TukUKPROC_PUID)proc_to_puid__i PUID of the ukProc to which the
 *  Shared Buffer has to be transferred.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The Shared Buffer has been properly
 *  transferred to the referenced ukProc.
 * @retval DukSTATUS_ERR_PARAM The given Address Block Identifier is invalid
 * @retval DukSTATUS_ERR_NOT_FOUND The given PUID is invalid (referenced ukProc
 *  Instance may have been terminated).
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The Nature of the given Address Block
 *  Identifier is not DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID.
 * @retval DukSTATUS_ERR_CREDENTIALS The current ukProc is not the Managing
 *  ukProc of the referenced Shared Buffer.
 * @retval DukSTATUS_ERR_CREDENTIALS The Managing ukProc has not been granted
 *  with the necessary credentials to perform this operation (it has not the
 *  flag DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG set in its own
 *  credentials on the referenced Shared Buffer).
 * @retval DukSTATUS_ERR_NOT_FOUND The referenced ukProc to which the Shared
 *  Buffer has to be transferred to has not been granted with any credentials
 *  (see ukSharedBufferAddCredentials()).
 * @retval DukSTATUS_ERR_IN_USE The referenced Shared Buffer is mapped in an
 *  Address Block Window of the current ukProc.
 * @retval DukSTATUS_ERR_PRECOND The ukProc is not the Managing ukProc of the
 *  given Shared Buffer.
 */
TukSTATUS ukSharedBufferTransfer(
                    TukADDRESSBLOCK_ID       shbuf_abid_bundle__i,
                    TukUKPROC_PUID           ukproc_to_puid__i);

/**
 * @}
 */
#endif /* defined(SukCONFIG_FEATURE_SHARED_BUFFERS) */



/* //////////////////////////////////////////////////////////////////////// */
/*           UKERNEL API - PRIVILEGED - PERIPHERAL IRQ MANAGEMENT           */
/* //////////////////////////////////////////////////////////////////////// */
/* PRIVATE */

#if defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ)
TukSTATUS ukPeripheralIRQRegister(TukPIRQ_MCU_IDX           pirq_mcu_idx__i,
                                  TukPIRQ_ATTRIBUTES        pirq_attr_config__i,
                                  TukPIRQ_REGISTRATION_ID  *pirq_reg_id__o);


TukSTATUS ukPeripheralIRQUnregister(TukPIRQ_REGISTRATION_ID pirq_reg_id__i);


TukSTATUS ukPeripheralIRQGetInfo(TukPIRQ_REGISTRATION_ID    pirq_reg_id__i);


TukSTATUS ukPeripheralIRQPerformAction(TukPIRQ_REGISTRATION_ID pirq_reg_id__i,
                                       TukPIRQ_ACTION pirq_action__i);
#endif /* defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ) */


/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - PRIVILEGED - MCU REGISTERS MANAGEMENT           */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @addtogroup MCURegistersManagement
 * @{
 */
/** @brief See MCU Registers Management documentation for more details on the different
 *   actions possible on an MCU Register: @ref docMCURegistersManagement.
 */

/**
 * @brief C-Function reading a set of MCU Registers.
 *
 * This C-Function reads a set of MCU Registers.
 * The information describing the MCU Registers to be read are retrieved from
 *  a C-Structure of C-Type TukMCUREGISTER_ACCESS_SET that has to be
 *  populated in the <ServiceParameter.Input> field of the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 * The results of the reading are returned in the same C-Structure of C-Type
 *  TukMCUREGISTER_ACCESS_SET in the <ServiceParameter.Output> field of the
 *  C-Variable GVukappBlockDataSharedUKSVC.
 *
 * The <ServiceParameter.Input> field has to be populated with a C-Structure of
 *  C-Type TukMCUREGISTER_ACCESS_SET as follows:
 *  - (TukACCESSKEY32)<MCURegisterAccessKey32>: 32-bit Access Key used to
 *   prevent MCU Register access from misuse in ukApp code. It shall be equal
 *   to the value retrieved using uKernel Core Tag Attribute
 *   DukUKCORE_ATTRIBUTE_TAG_MCUREGISTER_ACCESSKEY.
 *  - (TukCOUNT32)<MCURegisterCount32>: 32-bit count of MCU Registers to access.
 *   This count corresponds to the number of MCU Register Access Entry
 *   populated in the <MCURegisterAccessEntryList> field. It shall not exceed
 *   DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX.
 *  - (TukMCUREGISTER_ACCESS_ENTRY[])<MCURegisterAccessEntryList>: List as a
 *   C-Array of MCU Register Access Entries. Each entry contains the
 *   information for performing the access to a referenced MCU Register. This
 *   List shall contain <MCURegisterCount32> entries.
 *   Each MCU Register Access Entry shall have its following fields populated
 *   as follows:
 *   + <MCURegisterAddress>: 32-bit address of the MCU Register to read.
 *     This address shall correspond to one the <MCURegisterAddress> field of a
 *     MCU Register Descriptor entry in the MCU Register Descriptors list in
 *     the ukApp Descriptor of the current ukProc (see field
 *     <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR).
 *   + <MCURegisterValueBitmask32>: Bitmask containing the bits to be read in
 *     the MCU Register (only the bits set in this bitmask will be significant
 *     in the returned read value; the other bits shall be ignored and are set
 *     to null(0)). All the bit(s) set in this bitmask shall be set in the field
 *     <MCURegisterReadBitmask32> of the MCU Register Descriptor (see
 *     TukMCUREGISTER_DESCRIPTOR) corresponding to the address accessed, else
 *     the read access will fail.
 *   + <MCURegisterValue32>: Ignored (should be set to null(0)).
 *
 * Upon return of this C-Function, the <ServiceParameter.Output> field has been
 *  populated with a C-Structure of C-Type TukMCUREGISTER_ACCESS_SET as
 *  follows:
 *  - (TukACCESSKEY32)<MCURegisterAccessKey32>: 32-bit Access Key set to
 *   null(0) to prevent further invocation without populating again the Access
 *   Key.
 *  - (TukCOUNT32)<MCURegisterCount32>: 32-bit count of MCU Registers
 *   effectively read. If returned Status Word is DukSTATUS_INFO_OK, this count
 *   is equal to the ones populated upon invocation of this C-Function. Else,
 *   in case of error, this count contains the number of MCU Registers
 *   successfully read (the MCU Register having raised the error is thus the
 *   one at the index in the C-Array equals to this count).
 *  - (TukMCUREGISTER_ACCESS_ENTRY[])<MCURegisterAccessEntryList>: List as a
 *   C-Array of MCU Register Access Entries. Each MCU Register Access Entry has
 *   its fields populated as this:
 *   + <MCURegisterAddress>: Value unchanged (same as the one populated upon
 *     the invocation of this C-Function).
 *   + <MCURegisterValueBitmask32>: Value unchanged (same as the one populated
 *     upon the invocation of this C-Function).
 *   + <MCURegisterValue32>: Value read from the referenced MCU Register.
 *     Only the bit(s) set to 1 in <MCURegisterValueBitmask32> field are
 *     significant, the other bits being set to null(0).
 *     The value returned in this field is computed as this:
 *          <MCURegisterValue32> =
 *              (*MCURegisterAddress) & <MCURegisterValueBitmask32>.
 *
 * See MCU Register Management documentation for:
 *  - Details on MCU Register definition:
 *   + @ref docMCURegistersManagementDefinition
 *  - Details on MCU Register access:
 *   + @ref docMCURegistersManagementAccess
 *
 * @privileged
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_PARAM The given Count <MCURegisterCount32> is invalid
 *  (strictly greater than DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX).
 * @retval DukSTATUS_ERR_NOT_FOUND The given Address in <MCURegisterAddress>
 *  field of an MCU Register Entry does not correspond to one of an MCU
 *  Register Descriptor entry in the MCU Register Descriptors list in the ukApp
 *  Descriptor (see field <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR).
 * @retval DukSTATUS_ERR_NOT_SUPPORTED All the bit(s) set in the given bitmask
 *  <MCURegisterValueBitmask32> are not set in the field
 *  <MCURegisterReadBitmask32> of the MCU Register Descriptor (see
 *  TukMCUREGISTER_DESCRIPTOR) corresponding to the address accessed.
 * @retval DukSTATUS_ERR_HW An hardware error has occurred during access of one
 *  of the MCU Register.
 *
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS The given Access
 *  Key in <MCURegisterAccessKey32> is invalid.
 */
TukSTATUS ukMCURegisterRead(void);


/**
 * @brief C-Function writing a set of MCU Registers.
 *
 * This C-Function writes a set of MCU Registers.
 * The information describing the MCU Registers to be written are retrieved
 *  from a C-Structure of C-Type TukMCUREGISTER_ACCESS_SET that has to be
 *  populated in the <ServiceParameter.Input> field of the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 * The results of the writing are returned in same C-Structure of C-Type
 *  TukMCUREGISTER_ACCESS_SET in the <ServiceParameter.Output> field of the
 *  C-Variable GVukappBlockDataSharedUKSVC.
 *
 * The <ServiceParameter.Input> field has to be populated with a C-Structure of
 *  C-Type TukMCUREGISTER_ACCESS_SET as follows:
 *  - (TukACCESSKEY32)<MCURegisterAccessKey32>: 32-bit Access Key used to
 *   prevent MCU Register access from misuse in ukApp code. It shall be equal
 *   to the value retrieved using uKernel Core Tag Attribute
 *   DukUKCORE_ATTRIBUTE_TAG_MCUREGISTER_ACCESSKEY.
 *  - (TukCOUNT32)<MCURegisterCount32>: 32-bit count of MCU Registers to access.
 *   This count corresponds to the number of MCU Register Access Entry
 *   populated in the <MCURegisterAccessEntryList> field. It shall not exceed
 *   DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX.
 *  - (TukMCUREGISTER_ACCESS_ENTRY[])<MCURegisterAccessEntryList>: List as a
 *   C-Array of MCU Register Access Entries. Each entry contains the
 *   information for performing the access to a referenced MCU Register. This
 *   List shall contain <MCURegisterCount32> entries.
 *   Each MCU Register Access Entry shall have its following fields populated
 *   as follows:
 *   + <MCURegisterAddress>: 32-bit address of the MCU Register to write.
 *     This address shall correspond to one the <MCURegisterAddress> field of a
 *     MCU Register Descriptor entry in the MCU Register Descriptors list in
 *     the ukApp Descriptor of the current ukProc (see field
 *     <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR).
 *   + <MCURegisterValueBitmask32>: Bitmask containing the bits to be written
 *     in the MCU Register (only the bits set in this bitmask are modified in
 *     the MCU Register; the other bits are kept unchanged). All the bit(s) set
 *     in this bitmask shall be set in the field <MCURegisterWriteBitmask32> of
 *     the MCU Register Descriptor (see TukMCUREGISTER_DESCRIPTOR)
 *     corresponding to the address accessed, else the write access will fail.
 *   + <MCURegisterValue32>: 32-bit Value to write in the MCU Register. The
 *     bits that are not set in <MCURegisterValueBitmask32> are ignored.
 *
 * Upon return of this C-Function, the <ServiceParameter.Output> field has been
 *  populated with a C-Structure of C-Type TukMCUREGISTER_ACCESS_SET as
 *  follows:
 *  - (TukACCESSKEY32)<MCURegisterAccessKey32>: 32-bit Access Key set to
 *   null(0) to prevent further invocation without populating again the Access
 *   Key.
 *  - (TukCOUNT32)<MCURegisterCount32>: 32-bit count of MCU Registers
 *   effectively written. If returned Status Word is DukSTATUS_INFO_OK, this
 *   count is equal to the ones populated upon invocation of this C-Function.
 *   Else, in case of error, this count contains the number of MCU Registers
 *   successfully written (the MCU Register having raised the error is thus the
 *   one at the index in the C-Array equals to this count).
 *  - (TukMCUREGISTER_ACCESS_ENTRY[])<MCURegisterAccessEntryList>: List as a
 *   C-Array of MCU Register Access Entries. Each MCU Register Access Entry has
 *   its fields unchanged (same as the ones populated upon the invocation of
 *   this C-Function).
 *
 * @privileged
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_PARAM The given Count <MCURegisterCount32> is invalid
 *  (strictly greater than DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX).
 * @retval DukSTATUS_ERR_NOT_FOUND The given Address in <MCURegisterAddress>
 *  field of an MCU Register Entry does not correspond to one of an MCU
 *  Register Descriptor entry in the MCU Register Descriptors list in the ukApp
 *  Descriptor (see field <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR).
 * @retval DukSTATUS_ERR_NOT_SUPPORTED All the bit(s) set in the given bitmask
 *  <MCURegisterValueBitmask32> are not set in the field
 *  <MCURegisterWriteBitmask32> of the MCU Register Descriptor (see
 *  TukMCUREGISTER_DESCRIPTOR) corresponding to the address accessed.
 * @retval DukSTATUS_ERR_HW An hardware error has occurred during access of one
 *  of the MCU Register.
 *
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS The given Access
 *  Key in <MCURegisterAccessKey32> is invalid.
 */
TukSTATUS ukMCURegisterWrite(void);

/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                   UKERNEL API - PRIVILEGED - DMA STREAM                  */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_MCU_DMA)
/**
 * @addtogroup DMAStream
 * @{
 */
 
/**
 * @brief C-Function retrieving the DMA Stream Identifier from DMA Stream
 *  Label.
 *
 * This C-Function retrieves the DMA Stream Identifier from given DMA Stream
 *  Label.
 * The DMA Stream is referenced by the DMA Stream Label given in
 * <dmas_label__i>.
 * The DMA Stream Label is present in each DMA Stream Descriptor entry.
 * It allows to references unambiguously a DMA Stream in the ukApp
 *  where it is defined (see TukDMAS_LABEL for more details).
 *
 * @privileged
 *
 * @param[in] (TukDMAS_LABEL)dmas_label__i DMA Stream Label.
 * @param[out] (TukDMAS_ID *)dmas_id__o DMA Stream Identifier of the
 *  DMA Stream with given DMA Stream Label.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then returned DMA Stream
 *  Identifier <dmas_id__o> is set with DukDMAS_ID_INVALID.
 * @retval DukSTATUS_INFO_OK No error. The retrieving of the DMA Stream
 *  Identifier has been successful.
 * @retval DukSTATUS_ERR_NOT_FOUND The given DMA Stream Label has not been
 *  found in ukApp Descriptor.
 */
TukSTATUS ukDMAStreamGetIDFromLabel(
                TukDMAS_LABEL     dmas_label__i,
                TukDMAS_ID       *dmas_id__o);


/**
 * @brief C-Function retrieving the information on a DMA Stream Descriptor
 *  entry.
 *
 * This C-Function retrieves the information on a DMA Stream Descriptor entry.
 * The DMA Stream Descriptor entry is referenced by the DMA Stream Identifier
 *  given in <dmas_id__i>.
 *
 * The retrieved information is returned in the <ServiceParameter.Output> field
 *  of the C-Variable GVukappBlockDataSharedUKSVC. The field is formatted using
 *  the C-Type TukDMAS_INFO structure.
 *
 * @privileged
 *
 * @param[in] (TukDMAS_ID)dmas_id__i DMA Stream Identifier for which information
 *  have to be retrieved.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values.
 * @retval DukSTATUS_INFO_OK No error. The retrieving of information on
 *  referenced DMA Stream has been successful.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Identifier is invalid.
 */
TukSTATUS ukDMAStreamGetInfo(
                TukDMAS_ID        dmas_id__i);


/**
 * @brief C-Function assigning a DMA Stream to a DMA Stream Engine.
 *
 * This C-Function assigns a DMA Stream to a DMA Stream Engine.
 * The DMA Stream is referenced by the DMA Stream Identifier given in
 * <dmas_id__i>.
 *
 * A DMA Stream shall be assigned to a DMA Stream Engine in order to be able
 *  to trigger DMA transfer. As the number of DMA Stream Engine is limited
 *  in hardware, this uKernel Privileged Service allows to select when required
 *  which DMA Stream shall allocate a DMA Stream Engine.
 *
 * @usage A DMA Stream Engine can be assigned only one time at a given moment.
 *  In order to prevent race conditions, is is strongly recommended to have
 *  each DMA Stream Engine usable by only one ukApp by providing adequate
 *  configuration of DMA Stream in the ukApp Descriptor.
 *
 * @usage A DMA Stream can be unassigned from a DMA Stream Engine by using
 *  ukDMAStreamUnassign().
 *
 * @implementation A DMA Stream Engine corresponds to an hardware module
 *  capable of performing the requested transfer. Each DMA controller has a
 *  limited number of DMA Stream Engine, some of them having priorities on
 *  other ones or exclusive running conditions (it is MCU Device dependent:
 *  see MCU Device documentation for details). A DMA Stream Engine is also
 *  often called a DMA Channel in hardware documentation.
 *
 * @privileged
 *
 * @param[in] (TukDMAS_LABEL)dmas_label__i DMA Stream Label.
 * @param[out] (TukDMAS_ID *)dmas_iid__o DMA Stream Instance Identifier of the
 *  assigned DMA Stream.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is not DukSTATUS_INFO_OK, then returned DMA Stream
 *  Identifier <dmas_iid__o> is set with DukDMAS_IID_INVALID.
 * @retval DukSTATUS_INFO_OK No error. The assigning of the DMA Stream
 *  Identifier has been successful.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Identifier is invalid.
 * @retval DukSTATUS_ERR_ALREADY The DMA Stream has already been assigned to its
 *  DMA Stream Engine.
 * @retval DukSTATUS_ERR_HW_IN_USE The DMA Stream Engine in the referenced DMA
 *  Stream is already used.
 */
TukSTATUS ukDMAStreamAssign(
                TukDMAS_ID        dmas_id__i,
                TukDMAS_IID      *dmas_iid__o);

/**
 * @brief C-Function unassigning a DMA Stream from a DMA Stream Engine.
 *
 * This C-Function unassigns a DMA Stream from a DMA Stream Engine.
 * The DMA Stream is referenced by the DMA Stream Instance Identifier given in
 * <dmas_iid__i>.
 *
 * @usage This uKernel Privileged Service can be used to free a DMA Stream
 *  Engine previously assigned with ukDMAStreamAssign() in order to make it
 *  usable for another DMA Stream.
 *
 * @privileged
 *
 * @param[in] (TukDMAS_IID)dmas_iid__i DMA Stream Instance Identifier.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The unassigning of the DMA Stream
 *  Identifier has been successful.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Instance Identifier is
 *  invalid.
 * @retval DukSTATUS_ERR_IN_USE The DMA Stream has a DMA Stream Transfer that
 *  is ongoing.
 */
TukSTATUS ukDMAStreamUnassign(
                TukDMAS_IID       dmas_iid__i);

/**
 * @brief C-Function starting a DMA Stream Transfer.
 *
 * This C-Function starts a DMA Stream Transfer.
 * The DMA Stream is referenced by the DMA Stream Instance identifier given in
 * <dmas_iid__i>.
 *
 * The parameters of the DMA Stream Transfer to be started have to be set in the
 *  <ServiceParameter.Input> field of the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 * The <ServiceParameter.Input> field shall be structured as follows:
 *  - (TukDMAS_TRANSFER_MODE)dmas_transfer_mode__i DMA Stream Transfer
 *  Mode to be used for the current DMA Stream Transfer (see C-Type
 *  TukDMAS_TRANSFER_MODE).
 *  - (TukOFFSET32)dmas_transfer_src_offset__i Offset in the Address
 *  Block Source used for this DMA Stream Transfer.
 *  If the Address Block Source is a peripheral, it shall be null(0).
 *  - (TukOFFSET32)dmas_transfer_dst_offset__i Offset in the Address
 *  Block Destination used for this Stream Transfer.
 *  If the Address Block Destination is a peripheral, it shall be null(0).
 *  - (TukCOUNT32)dmas_transfer_count32__i Count of data (in bytes) to
 *  be used for this DMA Stream Transfer. If a DMA Stream Transfer in circular
 *  mode is used, this count represents the size to be used for each circular
 *  transfer.
 *
 * @usage A DMA Stream Transfer can be started only on a DMA Stream that has
 *  is currently assigned to a DMA Stream Engine (see ukDMAStreamAssign()).
 *
 * @usage A DMA Stream Transfer that has been started can then be paused by
 *  using the uKernel Privileged Service ukDMAStreamTransferStop().
 *
 * @privileged
 *
 * @param[in] (TukDMAS_IID)dmas_iid__i DMA Stream Instance Identifier for which
 *  current DMA Stream Transfer has to be started.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The referenced DMA Stream Transfer has
 *  been started successfully.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Instance Identifier is
 *  invalid.
 * @retval DukSTATUS_ERR_ALREADY The referenced DMA Stream Transfer was already
 *  started (the configuration and current transfer state of the DMA Stream
 *  Transfer already started is not affected).
 * @retval DukSTATUS_ERR_HW_STATE The DMA Stream Engine hardware state is
 *  invalid or has reported an error. The DMA Stream Transfer has not been
 *  started.
 */
TukSTATUS ukDMAStreamTransferStart(
                TukDMAS_IID             dmas_iid__i);

/**
 * @brief C-Function stopping a DMA Stream Transfer.
 *
 * This C-Function stops a DMA Stream Transfer.
 * The DMA Stream is referenced by the DMA Stream Instance identifier given in
 * <dmas_iid__i>.
 *
 * @implementation When this uKernel Privileged Service returns, it is
 *  guaranteed that the DMA Stream Transfer has effectively been stopped (all
 *  ongoing transfer have been finalized, and computed DMA Transfer count of
 *  data transferred is accurate).
 *
 * @usage A DMA Stream Transfer that has been stopped can then be restarted by
 *  using the uKernel Privileged Service ukDMAStreamTransferStart().
 *
 * @privileged
 *
 * @param[in] (TukDMAS_ID)dmas_iid__i DMA Stream Instance Identifier for which
 *  current DMA Stream Transfer has to be stopped.
 * @param[out] (TukCOUNT32)dmas_transfer_count_current32__o Current count (in
 *  bytes) of data transferred during the current DMA Stream Transfer (i.e.
 *  since last DMA Stream Transfer start).
 *  This value is the same as one returned in the field
 *  <DMAStreamTransferCountCurrent> of C-Type TukDMAS_TRANSFER_INFO.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error. The referenced DMA Stream Transfer has
 *  been stopped successfully.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Instance Identifier is
 *  invalid.
 * @retval DukSTATUS_ERR_ALREADY The referenced DMA Stream Transfer was already
 *  stopped.
 * @retval DukSTATUS_ERR_HW_STATE The DMA Stream Engine hardware state is
 *  invalid or has reported an error.
 */
TukSTATUS ukDMAStreamTransferStop(
                TukDMAS_IID       dmas_iid__i,
                TukLENGTH32      *dmas_transfer_count_current32__o);


/**
 * @brief C-Function retrieving information on a DMA Stream Transfer.
 *
 * This C-Function retrieves information on a DMA Stream Transfer.
 * The DMA Stream Instance is referenced by the DMA Stream Instance Identifier
 *  given in <dmas_iid__i>.
 *
 * The retrieved information is returned in the <ServiceParameter.Output> field
 *  of the C-Variable GVukappBlockDataSharedUKSVC. The field is formatted using
 *  the C-Type TukDMAS_TRANSFER_INFO structure.
 *
 * @privileged
 *
 * @param[in] (TukDMAS_ID)dmas_iid__i DMA Stream Instance Identifier for which
 *  current transfer information have to be retrieved.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the
 *  <ServiceParameter.Output> field of C-Variable GVukappBlockDataSharedUKSVC
 *  is filled with null(0) values.
 * @retval DukSTATUS_INFO_OK No error. The retrieving of current transfer
 *  information on referenced DMA Stream has been successful.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Instance Identifier is
 *  invalid.
 * @retval DukSTATUS_ERR_HW_STATE The DMA Stream Engine hardware state is
 *  invalid or has reported an error.
 */
TukSTATUS ukDMAStreamTransferGetInfo(
                TukDMAS_IID       dmas_iid__i);

/**
 * @brief C-Function retrieving the current state of a DMA Stream Transfer.
 *
 * This C-Function retrieves the current state on a DMA Stream Transfer.
 * The DMA Stream Transfer is referenced by the DMA Stream Instance Identifier
 *  given in <dmas_iid__i>.
 *
 * @usage This C-Function returns in a more immediate way the same information
 *  on the DMA Stream transfer as the uKernel Privileged Service
 *  ukDMAStreamTransferGetInfo().
 *
 * @privileged
 *
 * @param[in] (TukDMAS_ID)dmas_iid__i DMA Stream Instance Identifier for which
 *  current transfer state have to be retrieved.
 * @param[out] (TukDMAS_STATE)dmas_state__o Current DMA State of the referenced
 *  DMA Stream Instance (see C-Type TukDMAS_STATE).
 *  This value is the same as one returned in the field <TukDMAS_STATE> of
 *  C-Type TukDMAS_TRANSFER_INFO.
 * @param[out] (TukCOUNT32)dmas_transfer_count_current32__o Current count (in
 *  bytes) of data transferred during the current or last DMA Stream transfer.
 *  This value is the same as one returned in the field
 *  <DMAStreamTransferCountCurrent> of C-Type TukDMAS_TRANSFER_INFO.
 * @param[out] (TukCOUNT32)dmas_transfer_count_total32__o Current cumulated
 *  count (in bytes) of all DMA Stream transfers. This count is computed by
 *  adding the count of previous DMA Stream transfer that have been over to the
 *  one currently ongoing (if there is one).
 *  This value is the same as one returned in the field
 *  <DMAStreamTransferCountCumulated> of C-Type TukDMAS_TRANSFER_INFO.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the returned value for
 *  the following parameters are set to null(0) values:
 *   - <dmas_state__o>
 *   - <dmas_transfer_count_current32__o>
 *   - <dmas_transfer_count_total32__o>
 * @retval DukSTATUS_INFO_OK No error. The retrieving of current transfer
 *  state on referenced DMA Stream has been successful.
 * @retval DukSTATUS_ERR_PARAM The given DMA Stream Instance Identifier is
 *  invalid.
 * @retval DukSTATUS_ERR_HW_STATE The DMA Stream Engine hardware state is
 *  invalid or has reported an error.
 */
TukSTATUS ukDMAStreamTransferGetState(
                TukDMAS_IID       dmas_iid__i,
                TukDMAS_STATE    *dmas_state__o,
                TukLENGTH32      *dmas_transfer_count_current32__o,
                TukLENGTH32      *dmas_transfer_count_total32__o);
/**
 * @}
 */
#endif /* defined(SukCONFIG_FEATURE_MCU_DMA) */


/* //////////////////////////////////////////////////////////////////////// */
/*                    UKERNEL API - PRIVILEGED - WATCHDOG                   */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC)
/**
 * @addtogroup ApiWatchdog
 * @{
 */
/**
 * @brief C-Function starting the ukProc Watchdog.
 *
 * This C-Function starts the ukProc Watchdog.
 * The Watchdog Attributes used for configuring the started ukProc Watchdog are
 *  given in <wtdg_attr__i> (see TukWATCHDOG_ATTRIBUTES).
 *
 * The ukProc Watchdog Timer Periods are set as followed for the started ukProc
 *  Watchdog:
 *  - <wtdg_timer_scheduled_period_systick__i>: The ukProc Watchdog Timer Period
 *   Scheduled, in uKernel Systicks unit, is the period value of the timer
 *   being decremented each time a uKernel Systick occurs while the ukProc is
 *   the Scheduled ukProc (this timer is on hold as soon as the ukProc is not
 *   anymore the Scheduled ukProc).
 *  - <wtdg_timer_uptime_period_systick__i>: The ukProc Watchdog Timer Period
 *   Uptime, in uKernel Systicks unit, is the period of the timer being
 *   decremented each time a uKernel Systick occurs (whatever the ukProc is the
 *   Scheduled ukProc or not).
 * If a given ukProc Watchdog Timer Period is null, then the corresponding
 *  ukProc Watchdog Timer is disabled (both ukProc Watchdog Timer Periods
 *  cannot be null however).
 *
 * @robustness If a ukProc Watchdog has been started without the ukProc Watchdog
 *  Attribute DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG, then it is not
 *  possible anymore to stop the ukProc Watchdog, neither to change its ukProc
 *  Watchdog Attributes and ukProc Watchdog Timer Periods.
 *  This allows to enforce robustness, by guaranteeing that the configuration
 *  of the ukProc Watchdog cannot be changed once started (even in case of bugs
 *  or attacks trying to update the ukProc Watchdog configuration).
 *
 * @implementation If a ukProc Watchdog expires (because a ukProc Watchdog
 *  Timer has exhausted as the time to invoke ukWatchdogKick() function has
 *  been too long), then it is a ukProc Fatal Error, and the uKernel triggers
 *  a ukProc Abort with ukProc Termination
 *  Reason DukUKPROC_TERMINATION_REASON_ABORT_WATCHDOG.
 *
 * @implementation As soon as ukApp Entry Point ukappCleanup() is invoked, the
 *  ukProc Watchdog is always stopped (even if started without the ukProc
 *  Watchdog Attribute DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG).
 *
 * @usage In order to prevent the ukProc Watchdog to expire once started, the
 *  ukProc Watchdog shall be kicked at regular interval (see ukWatchdogKick())
 *  as long as the ukProc Watchdog is not stopped (see ukWatchdogStop()).
 *  A ukProc Instance can have only one ukProc Watchdog.
 *
 *
 * @privileged
 *
 * @param[in] (TukWATCHDOG_ATTRIBUTES)wtdg_attr__i Watchdog Attributes to be
 *  used for the configuration of the ukProc Watchdog.
 * @param[in] (TukTIME32_tick)wtdg_timer_scheduled_period_systick__i ukProc
 *  Watchdog Timer Scheduled Period, in uKernel SysTicks unit. If null(0), the
 *  ukProc Watchdog Timer Scheduled is disabled.
 * @param[in] (TukTIME32_tick)wtdg_timer_uptime_period_systick__i ukProc
 *  Watchdog Timer Uptime Period, in uKernel SysTicks unit. If null(0), the
 *  ukProc Watchdog Timer Uptime is disabled.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_PARAM The given Watchdog Attribute <wtdg_attr__i> is
 *  invalid (see DukWATCHDOG_ATTRIBUTES_CONFIG_MASK).
 * @retval DukSTATUS_ERR_PARAM Both given ukProc Watchdog Timer Uptime Period
 *  and ukProc Watchdog Timer Uptime Period are null(0).
 * @retval DukSTATUS_ERR_ALREADY The ukProc Watchdog has already been started.
 */
TukSTATUS ukWatchdogStart(
                TukWATCHDOG_ATTRIBUTES  wtdg_attr__i,
                TukTIME32_tick          wtdg_timer_scheduled_period_systick__i,
                TukTIME32_tick          wtdg_timer_uptime_period_systick__i);


/**
 * @brief C-Function stopping a ukProc Watchdog.
 *
 * This C-Function stops the ukProc Watchdog.
 *
 * @implementation This C-Function can stop the ukProc Watchdog only if the
 *  ukProc Watchdog has been started with ukProc Watchdog Attribute
 *  DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG. Else the ukProc Watchdog is
 *  not stopped and this C-Function returns with Status Code
 *  DukSTATUS_ERR_CONFIG.
 *
 * @usage Once successfully stopped:
 *  - The ukProc Watchdog does not need anymore to be kicked regularly (see
 *   ukWatchdogKick()).
 *  - The ukProc Watchdog can be started again (see ukWatchdogStart()), with
 *   different Watchdog Attributes if need be.
 *
 * @privileged
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_ALREADY The ukProc Watchdog is already stopped (it has
 *  not been started).
 * @retval DukSTATUS_ERR_CONFIG The ukProc Watchdog has not been started with
 *  the Watchdog Attribute DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG.
 */
TukSTATUS ukWatchdogStop(void);


/**
 * @brief C-Function kicking a ukProc Watchdog.
 *
 * This C-Function kicks a ukProc Watchdog.
 * The kicking of a ukProc Watchdog resets its both ukProc Watchdog Timers to
 *  the period value given upon start of the ukProc Watchdog (see
 *  ukWatchdogStart()).
 *
 * @implementation If a ukProc Watchdog expires (because a ukProc Watchdog
 *  Timer has exhausted as the time to invoke ukWatchdogKick() function has
 *  been too long), then it is a ukProc Fatal Error, and the uKernel triggers
 *  a ukProc Abort with ukProc Termination
 *  Reason DukUKPROC_TERMINATION_REASON_ABORT_WATCHDOG.
 *
 * @usage This C-Function has to be invoked during ukProc execution at a
 *  regular interval with enough margin in regards of chosen ukProc Watchdog
 *  Timer Periods to prevent expiration of the ukProc Watchdog.
 *
 * @privileged
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_STATE_INVALID The ukProc Watchdog has not been
 *  started.
 */
TukSTATUS ukWatchdogKick(void);
/**
 * @}
 */
#endif /* defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC) */



/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL API - PRIVILEGED - RANDOM GENERATOR               */
/* //////////////////////////////////////////////////////////////////////// */
/***
 * @addtogroup RandomGenerator
 * @{
 */
/**
 * @brief C-Function retrieving Random Values from a given Random Generator.
 *
 * This C-Function retrieves Random Values from the Random Generator referenced
 *  by given Random Generator Identifier <rng_id__i>.
 * The count of random bytes to be retrieved is given in <rng_bytes_count16__i>.
 * As only 64-bit random values are generated, this count is rounded to the
 *  next multiple of 8 to give the count of random bytes that have to be
 *  generated. The count of random bytes generated cannot exceed the size of
 *  the field <ServiceParameter.Output>.
 *
 * The Random Values generated are returned in the <ServiceParameter.Output>
 *  field of the C-Variable GVukappBlockDataSharedUKSVC. If returned Status
 *  Code is not DukSTATUS_INFO_OK, the Random Value returned in this field
 *  are issued from the PRNG Random Generator with best entropy available.
 *
 * @robustness In case of any error occurring during the processing of this
 *  uKernel Privileged Service (i.e. returned Status Code is not
 *  DukSTATUS_INFO_OK), the <ServiceParameter.Output> field is guaranteed to be
 *  always filled with Random Values from the PRNG Random Generator with best
 *  entropy available. It allows to guarantee a certain level of entropy and
 *  thus minimize the impact of the failure if the returned error Status Code
 *  from this uKernel Privileged Service is not properly managed by ukApp
 *  Developer.
 *
 * @robustness In case an error is occurring in the hardware entropy source of
 *  selected Random Generator, the selected Random Generator will be marked as
 *  not reliable till the next uKernel Session (and Status Code
 *  DukSTATUS_ERR_HW will always be returned when this Random Generator is
 *  selected).
 *
 * @implementation All the defined Random Generators may not be supported: some
 *  Random Generators are based on the presence of specific hardware part(s)
 *  that may not be present in used MCUs or Platform. See uKernel Release
 *  dedicated Platform documentation for details.
 *
 * @implementation In case the uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_RNG_PREDICTABLE is supported, each Random Generator
 *  is replaced by a predictable Random Generator generating always the same
 *  sequence for a given ukProc from the start of the uKernel Session.
 *
 * @usage Some Random Generator may not be supported or become untrusted due to
 *  hardware issues during a uKernel Session: ukApp Developer SHALL ALWAYS
 *  check the Status Code returned when using a Random Generator before using
 *  the Random Values generated.
 *
 * @usage As only 64-bit Random Values are generated, the count of random bytes
 *  generated always corresponds to the count of random bytes given in
 *  <rng_bytes_count16__i> to the next multiple of 8 (i.e. if a count of 6
 *  bytes is requested, then 8 bytes will be generated).
 *
 * @privileged
 *
 * @param[in] (TukRNG_ID)rng_id__i Random Generator Identifier referencing
 *  the Random Generator selected.
 * @param[in] (TukCOUNT16)random_bytes_count16__i Count of Random bytes to be
 *  generated. This count is always rounded to the next multiple of 8 (64-bit
 *  Random Values are always generated).
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_ERR_PARAM The given Random Generator Identifier
 *  <rng_id__i> is invalid.
 * @retval DukSTATUS_ERR_SIZE The count of random values to be generated is
 *  exceeding the size of <ServiceParameter.Output> field.
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The given Random Generator Identifier
 *  <rng_id__i> is not supported on this MCU and/or Platform.
 * @retval DukSTATUS_ERR_HW An error for the entropy source in the hardware has
 *  occurred. The referenced Random Generator cannot be trusted anymore, and
 *  this Status Code will always be returned for the referenced Random
 *  Generator till the next uKernel Session.
 */
TukSTATUS ukRandomGetBytes(TukRNG_ID          rng_id__i,
                           TukCOUNT16         random_bytes_count16__i);



/**
 * @brief C-Function seeding a given Random Generator.
 *
 * This C-Function seeds a Random Generator referenced by given Random
 *  Generator Identifier <rng_id__i> with given 64-bit Seed value
 *  <random_seed64__i>.
 *
 * @robustness The given Seed value is never replacing part of the internal
 *  state of the referenced Random Generator, but is always mixed with it in
 *  order to always increase the internal level of entropy. Thus seeding a
 *  Random Generator several times with same value will not lower its internal
 *  level of entropy.
 *
 * @implementation In case the uKernel Feature
 *  SukCONFIG_FEATURE_DEBUG_RNG_PREDICTABLE is supported, the seeding of Random
 *  Generator is ignored (in order that the Random Generator remains
 *  predictable).

 * @usage Some Random Generators cannot be seeded, as relying exclusively on
 *  hardware in the MCU and Platform used (e.g TRNG). In that case, Status Code
 *  DukSTATUS_WARN_NOT_DONE is returned.
 *
 * @privileged
 *
 * @param[in] (TukRNG_ID)rng_id__i Random Generator Identifier referencing
 *  the Random Generator selected.
 * @param[in] (TukUINT64)random_seed64__i 64-bit Seed value to use for seeding
 *  selected Random Generator.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If returned Status Code is not DukSTATUS_INFO_OK, the given Seed value has
 *  not been applied.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_WARN_NOT_DONE The referenced Random Generator cannot be
 *  seeded due to its nature.
 * @retval DukSTATUS_ERR_PARAM The given Random Generator Identifier
 *  <rng_id__i> is invalid.
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The given Random Generator Identifier
 *  <rng_id__i> is not supported on this MCU and/or Platform.
 * @retval DukSTATUS_ERR_HW An error for the entropy source in the hardware has
 *  occurred. The referenced Random Generator cannot be trusted anymore, and
 *  this Status Code will always be returned for the referenced Random
 *  Generator till the next uKernel Session.
 */
TukSTATUS ukRandomSetSeed64(TukRNG_ID           rng_id__i,
                            TukUINT64           random_seed64__i);


/**
 * @}
 */

/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL API - PRIVILEGED - DEBUG - UKPROC DEBUG TRACE           */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC)
/**
 * @brief C-Function printing given NTString on ukProc Debug Trace.
 *
 * This C-Function prints on ukProc Debug Trace the given NTString (Null
 *  Terminated String) <dbgtrace_ntstr_addr__i>.
 *
 * The Debug Trace is printed on all the Debug Trace Interfaces that are
 *  enabled for the ukProcs (see SukCONFIG_FEATURE_DEBUG_TRACE_xxx_UKPROC
 *  uKernel Features).
 * The print of the Debug Trace is effectively done only if given Attribute
 *  <dbgtrace_attrib__i> to use for this print allows it when compared to the
 *  ukApp Debug Trace Filter built from Debug Trace Nature Filer and
 *  Verbosity Filter configured in the ukApp Descriptor of current ukProc (see
 *  fields <DebugTraceNatureFilter> and <DebugTraceVerbosityFilter>).
 *
 * See Debug Trace documentation for:
 *  - Details on the usage of Debug Trace by ukProcs:
 *   + @ref docUKProcDebugTrace
 *
 * @robustness The given NTString is checked to be fully contained in one of
 *  the following authorized Address Block(s):
 *   - ukApp Code Block.
 *   - ukApp Data Volatile Block.
 *   - Shared Buffer(s) owned by the ukApp.
 *  If given NTString is not in one of the authorized Address Block(s), the
 *   error character DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED
 *   is printed in place of the NTString in the Debug Trace and Status Code
 *   DukSTATUS_ERR_ADDRESS is returned.
 *
 * @implementation In order to ease global Debug Trace reading, different
 *  templates may be applied automatically to the printed Debug Trace (e.g.
 *  specific prefix related to previous printed trace, its Nature, ...).
 *
 * @implementation At most DukdbgDEBUG_TRACE_LENGTH_PER_PRINT_MAX characters
 *  can be printed per Debug Trace print (the ones added for template and
 *  formatting are not counted in). If more characters are effectively
 *  printed, then:
 *   - The additional characters are discarded (not printed in Debug Trace).
 *   - The error character DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is
 *    set at the end of the Debug Trace
 *   - Status Code DukSTATUS_WARN_PARTIAL is returned.
 *
 * @implementation If the given Debug Trace Attribute <dbgtrace_attrib__i> is
 *  invalid, only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 *
 * @implementation If the length of given NTString is strictly greater than
 *  DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX, the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED is printed in place of
 *  the erroneous NTString in the Debug Trace.
 *
 * @implementation Due to the lowering of some internal uKernel security
 *  mechanisms when at least a uKernel Debug Trace Feature is enabled, the
 *  current ukProc has not to copy the given NTString in its ukApp Data
 *  Volatile Shared uKernel Services Block (ukAppDVSUKSVC Block) before
 *  invoking this C-Function.
 *
 * @privileged
 *
 * @param[in] (TukDEBUG_TRACE_ATTRIBUTES)dbgtrace_attrib__i Debug Trace
 *  Attributes associated to the Debug Trace to print.
 * @param[in] (TukNTCSTRING_ADDRESS)dbgtrace_ntstr_addr__i Address of the
 *  NTString to print on Debug Trace.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is of Nature Error, then given NTString is not printed on
 *  Debug Trace.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_WARN_NOT_DONE The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> has led to discard the printing after comparison with
 *  the Debug Trace Filter defined in ukApp Descriptor of current ukProc.
 * @retval DukSTATUS_WARN_PARTIAL The number of characters printed on the Debug
 *  Trace is exceeding DukdbgDEBUG_TRACE_LENGTH_PER_PRINT_MAX. The subsequent
 *  characters are discarded, and the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is set at the end of the
 *  Debug Trace.
 * @retval DukSTATUS_ERR_IDENTIFIER The given PIDX <pidx__i> is invalid or the
 *  Debug Trace is not supported for referenced uKernel Entity.
 * @retval DukSTATUS_ERR_STATE_INVALID The instantiated ukProc referenced by
 *  ukProc Identifier <pidx__i> is not in Executable State.
 * @retval DukSTATUS_ERR_PARAM The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> is invalid. Only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 * @retval DukSTATUS_ERR_ADDRESS The given NTString is not fully contained in
 *  one of the authorized Address Block(s). Only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED is printed in place
 *  of the NTString in the Debug Trace.
 * @retval DukSTATUS_ERR_SIZE The length of given NTString is strictly greater
 *  than DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX.
 *  The error character DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED
 *  is printed in place of the NTString in the Debug Trace.
 */
TukSTATUS ukDebugTracePrint(
                TukDEBUG_TRACE_ATTRIBUTES   dbgtrace_attrib__i,
                TukNTCSTRING_ADDRESS        dbgtrace_ntstr_addr__i);


/**
 * @brief C-Function printing the processed Format NTString (similar format
 *  as printf() C11 standard) on ukProc Debug Trace.
 *
 * This C-Function prints on ukProc Debug Trace the string built by processing
 *  the given Format NTString <dbgtrace_format_ntstr_addr__i> (similar format
 *  as printf() C11 standard) and associated variables arguments.
 *
 * The string printed on Debug Trace is built using:
 *  - The given Format NTString <dbgtrace_format_ntstr_addr__i> containing
 *   formatting marks (similar to the ones of printf() C11 standard).
 *   If the given Format NTString is invalid (e.g. unsupported formatting marks,
 *   invalid sequence of formatting marks, ...):
 *    + It is processed up to the error mark.
 *    + The specific character DukDEBUG_TRACE_ERROR_CHAR_FORMAT_PARSING is
 *      appended to the resulting built string.
 *    + The remaining of the given Format NTString is not processed (only the
 *      string built up to the error is printed on the Debug Trace).
 *  - The given additional arguments <...> that are combined with the
 *   formatting marks contained in the given Format NTString.
 *   If more arguments than expected in the given Format NTString are present,
 *   they are ignored. If there is not enough arguments, inconsistent behavior
 *   may occur (sorely the C language does not allow to check number of
 *   arguments effectively passed to a C-Function).
 *
 * See Debug Trace documentation for:
 *  - Details on the usage of Debug Trace by ukProcs:
 *   + @ref docUKProcDebugTrace
 *  - The formatting marks supported in given Format NTString:
 *   + @ref docUKProcDebugTracePrintfStandard
 *   + @ref docUKProcDebugTracePrintfProprietary
 *
 * The printing of the resulting built string is then done using the uKernel
 *  Privileged Service ukDebugTracePrint() (see its documentation for more
 *  details).
 *
 * @robustness The given Format NTString, and the NTString(s) referenced in it
 *  (using "%s" format mark), are checked to be fully contained in one of the
 *  following authorized Address Block(s)
 *   - ukApp Code Block.
 *   - ukApp Data Volatile Block.
 *   - Shared Buffer(s) owned by the ukApp.
 *  If a NTString is not in any of the authorized Address Block(s), the error
 *   character DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED is
 *   printed in place of the NTString in the Debug Trace and Status Code
 *   DukSTATUS_ERR_ADDRESS is returned.
 *
 * @implementation In order to ease global Debug Trace reading, different
 *  templates may be applied automatically to the printed Debug Trace (e.g.
 *  specific prefix related to previous printed trace, its Nature, ...).
 *
 * @implementation At most DukdbgDEBUG_TRACE_LENGTH_PER_PRINT_MAX characters
 *  can be printed per Debug Trace print (the ones added for template and
 *  formatting are not counted in). If more characters are effectively
 *  printed, then:
 *   - The additional characters are discarded (not printed in Debug Trace).
 *   - The error character DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is
 *    set at the end of the Debug Trace
 *   - Status Code DukSTATUS_WARN_PARTIAL is returned.
 *
 * @implementation If the given Debug Trace Attribute <dbgtrace_attrib__i> is
 *  invalid, only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 *
 * @implementation If the length of given Format NTString, or of the
 *  NTString(s) referenced in it (using "%s" format mark), is strictly greater
 *  than DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX, the error
 *  character DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED is printed in
 *  place of the NTString in the Debug Trace.
 *
 * @implementation Due to the lowering of some internal uKernel security
 *  mechanisms when at least a uKernel Debug Trace Feature is enabled, the
 *  referenced instantiated ukProc has not to copy the given Format string, or
 *  the strings referenced by it (using '%s' format mark), in its ukApp Data
 *  Volatile Shared uKernel Services Block (ukAppDVSUKSVC Block) before
 *  invoking this C-Function.
 *
 * @privileged
 *
 * @param[in] (TukDEBUG_TRACE_ATTRIBUTES)dbgtrace_attrib__i Debug Trace
 *  Attributes associated to the Debug Trace to print.
 * @param[in] (TukNTCSTRING_ADDRESS)dbgtrace_format_ntstr_addr__i Address of
 *  the Format NTString (similar format as printf() C11 standard) to be used to
 *  build the string to be printed on Debug Trace.
 * @param[in] ... List containing a variable number of arguments for each of
 *  the formatting marks present in the given Format NTString.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is of Nature Error, then resulting string from given Format
 *  String may be only partially printed.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_WARN_NOT_DONE The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> has led to discard the printing after comparison with
 *  the Debug Trace Filter of the ukProc requesting the printing.
 * @retval DukSTATUS_WARN_PARTIAL The number of characters printed on the Debug
 *  Trace is exceeding DukdbgDEBUG_TRACE_LENGTH_PER_PRINT_MAX. The subsequent
 *  characters are discarded, and the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED is set at the end of the
 *  Debug Trace.
 * @retval DukSTATUS_ERR_PARAM The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> is invalid. Only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 * @retval DukSTATUS_ERR_NOT_SUPPORTED The given Format NTString
 *  <dbgtrace_format_ntstr_addr__i> structure is invalid. The Debug Trace
 *  printed is the one built from the given Format NTString up to the erroneous
 *  mark, appended with the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_FORMAT_PARSING.
 * @retval DukSTATUS_ERR_ADDRESS The given Format NTString, or one of the
 *  NTString(s) referenced in it (using "%s" format mark), is not fully
 *  contained in one of the authorized Address Block(s). The error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED is printed in place
 *  of the NTString in the Debug Trace.
 * @retval DukSTATUS_ERR_SIZE The length of given Format NTString, or of one of
 *  the NTString(s) referenced in it (using "%s" format mark), is strictly
 *  greater than DukCONFIG_OPTION_DEBUG_TRACE_NTSTRING_LENGTH_MAX.
 *  The error character DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED
 *  is printed in place of the NTString in the Debug Trace.
 */
TukSTATUS ukDebugTracePrintf(
                TukDEBUG_TRACE_ATTRIBUTES   dbgtrace_attrib__i,
                TukNTCSTRING_ADDRESS        dbgtrace_format_ntstr_addr__i,
                ...);


/**
 * @brief C-Function printing the contents of given Buffer on ukProc Debug
 *  Trace.
 *
 * This C-Function prints on ukProc Debug Trace the contents of a given Buffer
 *  owned by the current ukProc. The print is done as a table of hexadecimal
 *  bytes, with 16 bytes per row.
 * The Buffer is referenced by its start address <buffer_address32_start__i>
 *  and its length (in bytes) <buffer_length16__i>. The maximal Buffer length
 *  that can be printed is defined by uKernel Option
 *  DukCONFIG_OPTION_DEBUG_TRACE_BUFFER_PRINTED_LENGTH_MAX.
 *
 * The Debug Trace is printed on all the Debug Trace Interfaces that are
 *  enabled for the ukProcs (see SukCONFIG_FEATURE_DEBUG_TRACE_xxx_UKPROC
 *  uKernel Features).
 * The print of the Debug Trace is effectively done only if given Attribute
 *  <dbgtrace_attrib__i> to use for this print allows it when compared
 *  to the ukApp Debug Trace Filter built from Debug Trace Nature Filter and
 *  Verbosity Filter configured in the ukApp Descriptor of current ukProc (see
 *  fields <DebugTraceNatureFilter> and <DebugTraceVerbosityFilter>).
 *
 * See Debug Trace documentation for:
 *  - Details on the usage of Debug Trace by ukProcs:
 *   + @ref docUKProcDebugTrace
 *
 * @robustness The given Buffer is checked to be owned by the current ukProc,
 *  which implies that it shall be fully contained in one of the following
 *  authorized Address Block(s):
 *  - ukApp Code Block.
 *  - ukApp Data Volatile Block.
 *  - Shared Buffer(s) owned by the ukApp.
 *  If given Buffer is not contained in any of the authorized Address Block(s),
 *   the error character DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED
 *   is printed in place of given Buffer contents and Status Code
 *   DukSTATUS_ERR_ADDRESS is returned.
 *
 * @implementation In order to ease global Debug Trace reading, different
 *  templates may be applied automatically to the printed Debug Trace (e.g.
 *  specific prefix related to previous printed trace, its Nature, ...).
 *
 * @implementation The limitation of DukdbgDEBUG_TRACE_LENGTH_PER_PRINT_MAX
 *  characters to be printed per Debug Trace print does not apply when printing
 *  a Buffer contents. Only the maximum length of the Buffer is limited.
 *
 * @implementation If the given Debug Trace Attribute <dbgtrace_attrib__i> is
 *  invalid, the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 *
 * @implementation If the Buffer length given in <buffer_length16__i> is
 *  strictly greater than DukCONFIG_OPTION_DEBUG_TRACE_BUFFER_PRINTED_LENGTH_MAX
 *  only the error character DukDEBUG_TRACE_ERROR_CHAR_BUFFER_LENGTH_EXCEEDED is
 *  printed in place of the Buffer contents in the Debug Trace.
 *
 * @privileged
 *
 * @param[in] (TukDEBUG_TRACE_ATTRIBUTES)dbgtrace_attrib__i Debug Trace
 *  Attributes associated to the Debug Trace to print.
 * @param[in] (TukADDRESS32)buffer_address32_start__i Start address of the
 *  buffer to print.
 * @param[in] (TukLENGTH16)buffer_length16__i Length in bytes of the buffer
 *  to print.
 *
 * @return (TukSTATUS)Status Code reflecting the execution success of the
 *  C-Function.
 *  If Status Code is of Nature Error, then Buffer is not printed.
 * @retval DukSTATUS_INFO_OK No error.
 * @retval DukSTATUS_WARN_NOT_DONE The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> has led to discard the printing after comparison with
 *  the Debug Trace Filter.
 * @retval DukSTATUS_ERR_PARAM The given Debug Trace Attribute
 *  <dbgtrace_attrib__i> is invalid. Only the error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID is printed in the Debug Trace.
 * @retval DukSTATUS_ERR_ADDRESS The given Buffer is not fully contained in
 *  one of the authorized Address Block(s). The error character
 *  DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED is printed in the
 *  Debug Trace.
 * @retval DukSTATUS_ERR_SIZE The Buffer length given in <buffer_length16__i>
 *  is strictly greater than uKernel Option
 *  DukCONFIG_OPTION_DEBUG_TRACE_BUFFER_PRINTED_LENGTH_MAX. The error
 *  character DukDEBUG_TRACE_ERROR_CHAR_BUFFER_LENGTH_EXCEEDED is printed
 *  in the Debug Trace.
 */
TukSTATUS ukDebugTracePrintBuffer(
                    TukDEBUG_TRACE_ATTRIBUTES   trace_attrib__i,
                    TukADDRESS32                buffer_address32_start__i,
                    TukLENGTH16                 buffer_length16);


#else /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */
/**
 * @brief C-Function not implemented in regards of selected uKernel Features. */
static inline CAukFUNC_INLINE_ALWAYS TukSTATUS ukDebugTracePrint(
    TukDEBUG_TRACE_ATTRIBUTES  dbgtrace_attrib__i     CAukVAR_UNUSED_MAYBE,
    TukNTCSTRING_ADDRESS       dbgtrace_ntstr_addr__i CAukVAR_UNUSED_MAYBE) {
    return(DukSTATUS_WARN_NOT_DONE);
}

/**
 * @brief C-Function not implemented in regards of selected uKernel Features. */
static inline CAukFUNC_INLINE_ALWAYS TukSTATUS ukDebugTracePrintf(
    TukDEBUG_TRACE_ATTRIBUTES  dbgtrace_attrib__i            CAukVAR_UNUSED_MAYBE,
    TukNTCSTRING_ADDRESS       dbgtrace_format_ntstr_addr__i CAukVAR_UNUSED_MAYBE,
    ...) {
    return(DukSTATUS_WARN_NOT_DONE);
}

/**
 * @brief C-Function not implemented in regards of selected uKernel Features. */
static inline CAukFUNC_INLINE_ALWAYS TukSTATUS ukDebugTracePrintBuffer(
    TukDEBUG_TRACE_ATTRIBUTES trace_attrib__i               CAukVAR_UNUSED_MAYBE,
    TukADDRESS32              buffer_address32_start__i     CAukVAR_UNUSED_MAYBE,
    TukLENGTH16               buffer_length16               CAukVAR_UNUSED_MAYBE) {
    return(DukSTATUS_WARN_NOT_DONE);
}
/**
 * @}
 */
#endif /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */


/* //////////////////////////////////////////////////////////////////////// */
#endif /* !defined(__ASSEMBLER__) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_SERVICES_H_INSIDE
#endif /* !defined(UK_SERVICES_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


