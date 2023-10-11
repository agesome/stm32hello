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
 * @file          uk_helpers.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  Helper C-Functions sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target, dedicated to the declarations and definitions relative to the
 *  Helpers C-Functions made available to ease ukApp development, and provide
 *  basis for developing high quality and robust software.
 *
 * The purpose of the uKernel Helpers is to provide common functionalities
 *  related to uKernel interfacing, with their implementation being fine tuned
 *  and fully validated for the used uKernel Target.
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
#if !defined(UK_HELPERS_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_helpers.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_HELPERS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_HELPERS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                      UKERNEL API - HELPERS - C-MACROS                    */
/* ######################################################################## */
/* Hereafter are defined the inlined C-Macros composing the uKernel Helpers of
 *  the uKernel API.
 *
 * @implementation As good coding practice, and to help developing high quality
 *  and robust software, it shall be be kept in mind that the C-Macros defined
 *  hereafter MAY BE further transformed a standard C-Function call, and that
 *  this transformation SHALL NOT have impact on existing code invoking this
 *  function.
 *
 * @implementation Most of uKernel Helpers implementation is composed of code
 *  integrated with ukApp's one during compilation (thus executing as part of
 *  the ukProc execution context).
 *  In case some uKernel Privileges Services are used in their implementation,
 *  it is explicitly stated in their associated documentation.
 */

/* The C-Macros declarations shall not be done when this file is used by
 *  the C-Assembler. */
#if !defined(__ASSEMBLER__)



/* //////////////////////////////////////////////////////////////////////// */
/*                     HELPERS - C-MACROS - STATUS CODE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro testing if given Status Code is valid.
 *
 * This C-Macro tests if the given Status Code value is valid (that is the
 *  structure of its value is compliant with TukSTATUS C-Type).
 *
 * @param[in] (TukSTATUS)status__i Status Code to test.
 *
 * @return (TukBOOL)Boolean value indicating result of the check.
 * @retval DukBOOL_TRUE if given Status Code <status__i> is valid.
 * @retval DukBOOL_FALSE if given Status Code <status__i> is not valid.
 */
#define ukStatusIsValid(status__i)                                            \
  ( ( (((status__i) &                                                         \
      (~(DukSTATUS_REASON_FIELD_MASK | DukSTATUS_NATURE_FIELD_MASK))          \
      ) == 0U) &&                                                             \
      ( MukVAL_BIT_IS_EXACTLY_ONE_SET(                                        \
           (status__i) & DukSTATUS_NATURE_FIELD_MASK) == DukBOOL_TRUE)        \
    ) ? DukBOOL_TRUE : DukBOOL_FALSE                                          \
  )

/**
 * @brief C-Macro testing if given Status Code is of Nature Info.
 *
 * This C-Macro tests if the given Status Code value is of Nature Info.
 *
 * @param[in] (TukSTATUS)status__i Status Code to test.
 *
 * @return (TukBOOL)Boolean value indicating result of the check.
 * @retval DukBOOL_TRUE if given Status Code <status__i> is of Nature Info.
 * @retval DukBOOL_FALSE if given Status Code <status__i> is not of Nature
 *  Info.
 */
#define ukStatusIsInfo(status__i)                                             \
    ( (((status__i) & DukSTATUS_NATURE_INFO_FLAG) != 0U)                      \
      ? DukBOOL_TRUE : DukBOOL_FALSE                                          \
    )

/**
 * @brief C-Macro testing if given Status Code is of Nature Info or Warning.
 *
 * This C-Macro tests if the given Status Code value is of Nature Info or
 *  Warning.
 *
 * @param[in] (TukSTATUS)status__i Status Code to test.
 *
 * @return (TukBOOL)Boolean value indicating result of the check.
 * @retval DukBOOL_TRUE if given Status Code <status__i> is of Nature Info or
 *  Warning.
 * @retval DukBOOL_FALSE if given Status Code <status__i> is neither of Nature
 *  Info nor Warning.
 */
#define ukStatusIsInfoOrWarning(status__i)                                    \
    ( ((status__i) &                                                          \
        (DukSTATUS_NATURE_INFO_FLAG | DukSTATUS_NATURE_WARNING_FLAG) ) != 0U  \
    )

/**
 * @brief C-Macro testing if given Status Code is of Nature Error or Fatal
 *  Error.
 *
 * This C-Macro tests if the given Status Code value is of Nature Error or
 *  Fatal Error.
 *
 * @param[in] (TukSTATUS)status__i Status Code to test.
 *
 * @return (TukBOOL)Boolean value indicating result of the check.
 * @retval DukBOOL_TRUE if given Status Code <status__i> is of Nature Error or
 *  Fatal Error.
 * @retval DukBOOL_FALSE if given Status Code <status__i> is neither of Nature
 *  Error nor Fatal Error.
 */
#define ukStatusIsError(status__i)                                            \
    ( ((status__i) &                                                          \
        (DukSTATUS_NATURE_ERROR_FLAG | DukSTATUS_NATURE_ERROR_FATAL_FLAG)     \
       ) != 0U                                                                \
    )


/**
 * @brief C-Macro testing if given Status Code is of Nature Fatal Error.
 *
 * This C-Macro tests if the given Status Code value is of Nature Fatal Error.
 *
 * @param[in] (TukSTATUS)status__i Status Code to test.
 *
 * @return (TukBOOL)Boolean value indicating result of the check.
 * @retval DukBOOL_TRUE if given Status Code <status__i> is of Nature Fatal
 *  Error.
 * @retval DukBOOL_FALSE if given Status Code <status__i> is not of Nature
 *  Fatal Error.
 */
#define ukStatusIsFatal(status__i)                                            \
    ( (((status__i) & DukSTATUS_NATURE_ERROR_FATAL_FLAG) != 0U )


/**
 * @brief C-Macro converting a Status Code of Nature Error to Nature Fatal
 *  Error.
 *
 * This C-Macro converts a Status Code of Nature Error to Nature Fatal Error.
 *
 * @param[in] (TukSTATUS)status__i Status Code of Nature Error to convert.
 *
 * @return (TukSTATUS)Status Code with same reason but with Nature Fatal Error.
 */
#define ukStatusErrorConvertToFatalError(status__i)                           \
    ((TukSTATUS)                                                              \
       ( ((status__i) & (~DukSTATUS_NATURE_ERROR_FLAG)) |                     \
         DukSTATUS_NATURE_ERROR_FATAL_FLAG)                                   \
       )



/* //////////////////////////////////////////////////////////////////////// */
/*                   HELPERS - C-MACROS - ERROR MANAGEMENT                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Function providing a default implementation for the reporting of
 *  a Fatal Error occurring during a ukProc execution.
 *
 * This C-Function provides a default implementation for the reporting of a
 *  Fatal Error occurring during a ukProc execution, with the reason indicated
 *  by given Status Code <status_code__i>.
 * The given Status Code <status_code__i> shall be of Nature Error or Fatal
 *  Error.
 *
 * @implementation In case an MCU Exception Fault is raised by the execution of
 *  a ukProc (e.g. illegal memory access, ...), or if a uKernel Privileged
 *  Service invocation is not authorized (e.g. without proper credentials),
 *  this C-Function IS NOT invoked by the uKernel.
 *  In such case, a ukProc Fatal Error is triggered, and the uKernel triggers
 *  a ukProc Abortion (see TukUKPROC_TERMINATION_REASON).
 *
 * @implementation The proposed default implementation of this C-Function
 *  invokes the ukUKProcExit() uKernel Privileged Service, with the reporting
 *  of an Exit In Error, and using given Status Code forced to Nature Fatal
 *  Error as ukProc Termination Information.
 *  For sensitive ukApp, it is recommended to replace this default
 *  implementation by a specific one in ukApp code that implements the Security
 *  Policy defined for the ukApp (wiping of sensitive data, ...).
 *
 * @usage The ukApp code SHOULD invoke itself this C-Function to report a
 *  Fatal Error occurring in its own implementation. It is part of good
 *  practice of error management to centralize Fatal Error processing, and be
 *  certain of a consistent behavior of ukApp code in such case.
 *
 * @param[in] (TukSTATUS)status_code__i Status Code of Nature Error or Fatal
 *  Error providing detail on the reason of the Fatal Error having occurred.
 *
 * @post This C-Function never returns.
 */
#if !defined(SukCONFIG_FUNC_UKERRORFATALMANAGE_CUSTOM)
    #define ukErrorFatalManage(status_code__i)                                \
              ukUKProcExit(                                                   \
                  DukBOOL_TRUE,                                               \
                  ukStatusErrorConvertToFatalError(status_code__i));
#else /* !defined(SukCONFIG_FUNC_UKERRORFATALMANAGE_CUSTOM) */
    CAukFUNC_RETURN_NEVER void ukErrorFatalManage(
                                    TukSTATUS status_code__i);
#endif /* !defined(SukCONFIG_FUNC_UKERRORFATALMANAGE_CUSTOM) */

#endif /* !defined(__ASSEMBLER__) */



/* //////////////////////////////////////////////////////////////////////// */
/*                        HELPERS - C-MACROS - UKAPP                        */
/* //////////////////////////////////////////////////////////////////////// */

/** @brief C-Macro extracting the ASID field from an AUID value.
 *
 * This C-Macro extracts the ukApp Short Identifier (ASID) field from the
 *  given ukApp Unique Identifier (AUID) <auid__i>.
 *
 * @implementation No check is done on the validity of the given AUID value.
 *
 * @param[in] (TukUKAPP_AUID)auid__i ukApp Unique Identifier (AUID).
 *
 * @return (TukUKAPP_ASID)Extracted ukApp Short Identifier (ASID) field value
 *  (its LSb is bit 0 of returned value).
 */
#define ukAppAUIDExtractASID(auid__i)    ((TukUKAPP_ASID)                     \
                MukVAL_FIELD_VALUE_GET(DukUKAPP_AUID_ASID_FIELD_LSb,          \
                                       DukUKAPP_AUID_ASID_FIELD_MSb,          \
                                       (auid_i)))


/* //////////////////////////////////////////////////////////////////////// */
/*                         HELPERS - C-MACROS - UKPROC                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro extracting the ukProc Origin Event field from the given
 *  ukProc Origin value.
 *
 * This C-Macro extracts the ukProc Origin Event field (see
 *  TukUKPROC_ORIGIN_EVENT) from the given ukProc Origin value <proc_origin__i>.
 *
 * @implementation No check is done on the validity of the given ukProc Origin
 *  value.
 *
 * @param[in] (TukUKPROC_ORIGIN)ukproc_origin__i ukProc Origin value issued
 *  by the parameter <proc_origin__i> from ukappMain().
 *
 * @return (TukUKPROC_ORIGIN_EVENT)Extracted ukProc Origin Event field value
 *  (its LSb is bit 0 of returned value).
 */
#define ukUKProcOriginExtractEvent(ukproc_origin__i)                          \
            ((TukUKPROC_ORIGIN_EVENT)                                         \
             MukVAL_FIELD_VALUE_GET(DukUKPROC_ORIGIN_EVENT_FIELD_LSb,         \
                                    DukUKPROC_ORIGIN_EVENT_FIELD_MSb,         \
                                    (ukproc_origin__i)))

/**
 * @brief C-Macro extracting the ukProc Origin Info field from the given
 *  ukProc Origin value.
 *
 * This C-Macro extracts the ukProc Origin Info field (see
 *  TukUKPROC_ORIGIN_INFO) from the given ukProc Origin value <proc_origin__i>.
 *
 * @implementation No check is done on the validity of the given ukProc Origin
 *  value.
 *
 * @param[in] (TukUKPROC_ORIGIN)ukproc_origin__i ukProc Origin value issued
 *  by the parameter <proc_origin__i> from ukappMain().
 *
 * @return (TukUKPROC_ORIGIN_INFO)Extracted ukProc Origin Info field value
 *  (its LSb is bit 0 of returned value).
 */
#define ukUKProcOriginExtractInfo(ukproc_origin__i)                           \
        ((TukUKPROC_ORIGIN_INFO)                                              \
         MukVAL_FIELD_VALUE_GET(DukUKPROC_ORIGIN_INFO_FIELD_LSb,              \
                                DukUKPROC_ORIGIN_INFO_FIELD_MSb,              \
                                (ukproc_origin__i)))


/**
 * @brief C-Macro extracting the ukProc Origin Context field from the given
 *  ukProc Origin value.
 *
 * This C-Macro extracts the ukProc Origin Context field (see
 *  TukUKPROC_ORIGIN_CONTEXT) from the given ukProc Origin value
 *  <proc_origin__i>.
 *
 * @implementation No check is done on the validity of the given ukProc Origin
 *  value.
 *
 * @param[in] (TukUKPROC_ORIGIN)ukproc_origin__i ukProc Origin value issued
 *  by the parameter <proc_origin__i> from ukappMain().
 *
 * @return (TukUKPROC_ORIGIN_CONTEXT)Extracted ukProc Origin Context field
 *  value (its LSb is bit 0 of returned value).
 */
#define ukUKProcOriginExtractContext(ukproc_origin__i)                        \
        ((TukUKPROC_ORIGIN_CONTEXT)                                           \
         MukVAL_FIELD_VALUE_GET(DukUKPROC_ORIGIN_CONTEXT_FIELD_LSb,           \
                                DukUKPROC_ORIGIN_CONTEXT_FIELD_MSb,           \
                                (ukproc_origin__i)))



/** @brief C-Macro extracting the PIDX field from a PUID value.
 *
 * This C-Macro extracts the ukProc Index (PIDX) field from the given ukProc
 *  Unique Identifier (PUID) <puid__i>.
 *
 * @implementation No check is done on the validity of the given PUID value.
 *
 * @param[in] (TukUKPROC_PUID)puid__i ukProc Unique Identifier (PUID).
 *
 * @return (TukUKPROC_PIDX)Extracted ukProc Index (PIDX) field value (its LSb
 *  is bit 0 of returned value).
 */
#define ukAppPUIDExtractPIDX(puid__i)    ((TukUKPROC_PIDX)                    \
                MukVAL_FIELD_VALUE_GET(DukUKPROC_PUID_PIDX_FIELD_LSb,         \
                                       DukUKPROC_PUID_PIDX_FIELD_MSb,         \
                                       (puid__i)))



/* ######################################################################## */
/*                    UKERNEL API - HELPERS - C-FUNCTIONS                   */
/* ######################################################################## */
/* Hereafter are declared the C-Functions composing the uKernel Helpers of
 *  the uKernel API.
 *
 * @implementation Most of uKernel Helpers implementation is composed of code
 *  integrated with ukApp's one during compilation (thus executing as part of
 *  the ukProc execution context).
 *  In case some uKernel Privileges Services are used in their implementation,
 *  it is explicitly stated in their associated documentation.
 */

/* The C-Functions declarations shall not be done when this file is used by
 *  the C-Assembler. */
#if !defined(__ASSEMBLER__)


/* //////////////////////////////////////////////////////////////////////// */
/*                      HELPERS - C-FUNCTIONS - RANDOM                      */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(UKCORE)

/**
 * @brief C-Function generating a 32-bit random value using a local XorShift32
 *  PRNG.
 *
 * This C-Function generates a 32-bit random value using a local (e.g. no
 *  systematic uKernel Privileged Service invocation) and private XorShift32
 *  Pseudo Random Generator (PRNG).
 *
 * @warning This C-Function SHALL NOT be used to generate random values
 *  for sensitive operations, such as cryptographic operations (the quality of
 *  the random being generated not fitting the level needed for such usage).
 *
 * @implementation The PRNG is seeded regularly (every ~64K generations) with
 *  additional entropy provided by uKernel Privileged Service
 *  ukRandomGetBytes().
 *
 * @implementation This C-Function uses a local static variable to store the
 *  PRNG internal state.
 *
 * @usage This C-Function aims to be used in ukApp code when pseudo-random
 *  values with low entropy level need to be generated quickly (e.g. buffer
 *  wiping, software counter-measures, ...).
 *
 * @return (TukUINT32)32-bit pseudo random generated value using XorShift32
 *  PRNG algorithm.
 */
TukUINT32 ukRandomXorShift32Generate(void);


#endif /* !defined(UKCORE) */


/* //////////////////////////////////////////////////////////////////////// */
/*                 HELPERS - C-FUNCTIONS - BUFFER MANAGEMENT                */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(UKCORE)

/**
 * @brief C-Function clearing a buffer.
 *
 * This C-Function clears a buffer (reset all its bytes to null (0) value).
 *
 * The buffer to clear is referenced by its given starting address
 *  <buffer_addr__i>.
 * The length to clear in bytes is given by <buffer_length32__i>.
 *
 * @robustness A sensitive buffer SHALL NEVER be filled with a constant value
 *  (and notably not the null(0) one). A sensitive buffer HAS TO be wiped
 *  (see ukrootBufferWipe), that is filled with (pseudo)random data in order to
 *  prevent an attacker of predicting its contents, either before and/or after
 *  its usage. Also, as the number of bits flipped for each byte is
 *  unpredictable when wiping, it lowers the information leaked from the
 *  previous buffer contents.
 *
 * @implementation This C-Function is implemented with MCU Core specific code
 *  for optimizing performances.
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given buffer.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @usage No specific constraint is applying on buffers start address or
 *  length, but generally performance is better if buffer start address is
 *  aligned on 32-bit (i.e. multiple of 4).
 *
 * @param[in] (TukADDRESS32)buffer_addr__i Start address of the buffer.
 * @param[in] (TukLENGTH32)buffer_length32__i Length (in bytes) of the buffer
 *  to clear from its given start address. If null, then nothing is done.
 */
void ukBufferClear(TukADDRESS32  buffer_addr__i,
                      TukLENGTH32   buffer_length32__i);

/**
 * @brief C-Function copying a buffer to another buffer.
 *
 * This C-Function copy a buffer source into a buffer destination.
 *
 * The buffer source is referenced by its given starting address
 *   <buffer_src_addr__i>.
 * The buffer destination is referenced by its given starting address
 *   <buffer_dest_addr__i>.
 * The length to copy in bytes is given by <buffer_length32__i>.
 *
 * @implementation This C-Function is implemented with MCU Core specific code
 *  for optimizing performances.
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given buffer.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @usage No specific constraint is applying on buffers start addresses or
 *  length, but generally performance is better if buffer start addresses are
 *  aligned on 32-bit (i.e. multiple of 4).
 *
 * @param[in] (TukADDRESS32)buffer_src_addr__i Start address of the buffer
 *  source.
 * @param[in] (TukADDRESS32)buffer_dest_addr__i Start address of the buffer
 *  destination.
 * @param[in] (TukLENGTH32)buffer_length32__i Length (in bytes) of the buffer
 *  source to copy to buffer destination (the copy starting from given start
 *  addresses). If null, nothing is done.
 */
void ukBufferCopy(TukADDRESS32   buffer_src_addr__i,
                     TukADDRESS32   buffer_dest_addr__i,
                     TukLENGTH32    buffer_length32__i);

/**
 * @brief C-Function comparing a buffer with another buffer.
 *
 * This C-Function compares quickly the contents of a first buffer with the
 *  contents of a second buffer.
 * The quick comparison algorithm used implies that the comparison stops as
 *  soon as there is a difference spotted between both buffers (comparison
 *  starts from the start address of each buffer).
 *
 * The first buffer is referenced by its given starting address
 *   <buffer1_src_addr__i>.
 * The second buffer is referenced by its given starting address
 *   <buffer2_src_addr__i>.
 * The length to compare in bytes is given by <buffer_length32__i>.
 *
 * @implementation This C-Function is implemented with MCU Core specific code
 *  for optimizing performances.
 *
 * @usage No specific constraint is applying on buffer start addresses or
 *  length, but generally performance is better if buffer start addresses are
 *  aligned on 32-bit (i.e. multiple of 4).
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given buffers.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @param[in] (TukADDRESS32)buffer1_src_addr__i Start address of the first
 *  buffer.
 * @param[in] (TukADDRESS32)buffer2_src_addr__i Start address of the second
 *  buffer.
 * @param[in] (TukLENGTH32)buffer_length32__i Length (in bytes) to compare
 *  in the given buffers (the comparison starting from given start addresses).
 *  If null, nothing is done and DukBOOL_TRUE is returned.
 *
 * @return (TukBOOL) Boolean value indicating the result of the comparison of
 *  both buffer contents.
 * @retval DukBOOL_TRUE The contents compared, defined by the given number of
 *  bytes form given start addresses, is identical.
 * @retval DukBOOL_FALSE The contents compared, defined by the given number of
 *  bytes form given start addresses, is different.
 */
TukBOOL ukBufferCompareQuick(TukADDRESS32   buffer1_src_addr__i,
                             TukADDRESS32   buffer2_src_addr__i,
                             TukLENGTH32    buffer_length32__i);

/**
 * @brief C-Function comparing fully a buffer with another buffer.
 *
 * This C-Function compares fully the contents of a first buffer with the
 *  contents of a second buffer.
 * The full comparison algorithm used implies that the comparison is performed
 *  on both buffers up to the given length, even if during the check a
 *  difference is spotted between both buffers (comparison starts from the
 *  start address of each buffer).
 *
 * The first buffer is referenced by its given starting address
 *   <buffer1_src_addr__i>.
 * The second buffer is referenced by its given starting address
 *   <buffer2_src_addr__i>.
 * The length to compare in bytes is given by <buffer_length32__i>.
 *
 * @robustness If an inconsistency has been detected during the comparison
 *  (code has not been executed as expected), then it is a ukProc Fatal Error
 *  and ukErrorFatalManage() is invoked with Status Code
 *  DukSTATUS_ERR_UNEXPECTED.
 *
 * @implementation This C-Function is implemented with MCU Core specific code
 *  for optimizing performances.
 *
 * @usage No specific constraint is applying on buffer start addresses or
 *  length, but generally performance is better if buffer start addresses are
 *  aligned on 32-bit (i.e. multiple of 4).
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given buffers.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @param[in] (TukADDRESS32)buffer1_src_addr__i Start address of the first
 *  buffer.
 * @param[in] (TukADDRESS32)buffer2_src_addr__i Start address of the second
 *  buffer.
 * @param[in] (TukLENGTH32)buffer_length32__i Length (in bytes) to compare
 *  in the given buffers (the comparison starting from given start addresses).
 *  If null, nothing is done and DukSAFEBOOL_TRUE is returned.
 *
 * @return (TukSAFEBOOL) Safe Boolean value indicating the result of the
 *  comparison of both buffer contents.
 * @retval DukSAFEBOOL_TRUE The contents compared, defined by the given number
 *  of bytes form given start addresses, is identical.
 * @retval DukSAFEBOOL_FALSE The contents compared, defined by the given number
 *  of bytes form given start addresses, is different.
 */
TukSAFEBOOL ukBufferCompare(
                    TukADDRESS32 buffer1_src_addr__i,
                    TukADDRESS32 buffer2_src_addr__i,
                    TukLENGTH32  buffer_length32__i);

/**
 * @brief C-Function wiping a buffer with pseudo-random values.
 *
 * This C-Function wipes a volatile data buffer using pseudo-random values.
 *
 * The buffer is referenced by its given starting address <buffer_addr__i>.
 * The length to wipe in bytes is given by <buffer_length32__i>.
 *
 * @robustness A sensitive buffer SHALL NEVER be filled with a constant value
 *  (and notably the null(0) value). A sensitive buffer HAS TO be filled with
 *  (pseudo)random data in order to prevent an attacker of predicting its
 *  contents, either before and/or after its usage. Also, as the number of
 *  bits flipped for each byte is unpredictable when wiping, it lowers the
 *  information leaked from the previous buffer contents.
 *
 * @implementation This C-Function uses an efficient implementation for
 *  providing quite good performance for wiping the buffer, by using a ukApp
 *  local and private XorShift32 Random Generator (see
 *  ukRandomXorShift32Generate()).
 *
 * @usage No specific constraint is applying on buffers start address or
 *  length, but generally performance is better if buffer start address is
 *  aligned on 32-bit (i.e. multiple of 4).
 *
 * @usage This C-Function SHALL BE used to enforce that a buffer used for
 *  storing sensitive or secret data does not contain predictable data for an
 *  attacker. It SHALL BE invoked before and after the use of any buffer
 *  containing sensitive or secret data.
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given buffers.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @param[in] (TukADDRESS32)buffer_addr__i Start address of the buffer.
 * @param[in] (TukLENGTH32)buffer_length32__i Length (in bytes) of the buffer
 *  to wipe from the given start address. If null, nothing is done.
 */
void ukBufferWipe(TukADDRESS32   buffer_addr__i,
                     TukLENGTH32    buffer_length32__i);

#endif /* !defined(UKCORE) */


/* //////////////////////////////////////////////////////////////////////// */
/*                 HELPERS - C-FUNCTIONS - STRING MANAGEMENT                */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(UKCORE)

/**
 * @brief C-Function retrieving the 8-bit length of a given NTString.
 *
 * This C-Function retrieves the 8-bit length of a given NTString.
 *
 * The NTString is referenced by its given starting address <ntstring_addr__i>.
 *
 * The returned length is computed by counting the number of characters from
 *  this starting address up to a null character '\0'.
 *
 * @robustness In order to prevent unexpected behavior from malformed NTString,
 *  if the computed length is strictly greater than 255, then null(0) length is
 *  returned.
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given NTString contents.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @param[in] (TukNTCSTRING_ADDRESS)ntstring_addr__i Start address of the
 *  NTString.
 *
 * @return (TukLENGTH8)NTString 8-bit length.
 * @retval 0 The given NTString start address <ntstring_addr__i> is equal to
 *  one of the value in { DukADDRESS_INVALID, DukADDRESS_IGNORE, NULL }.
 * @retval 0 The NTString length is strictly greater than 255.
 */
TukLENGTH8 CAukFUNC_RETURN_VALUE_CHECK ukNTStringGetLength8(
                                    TukNTCSTRING_ADDRESS ntstring_addr__i);

/**
 * @brief C-Function retrieving the length of a given NTString, up to a
 *  given maximal length.
 *
 * This C-Function retrieves the length on 16-bit of a NTString referenced by
 *  its given starting address <ntstring_addr__i>. The length is computed up
 *  to the given maximum length <ntstring_length_max__i>.
 *
 * The returned length is computed by counting the number of character from
 *  this starting address up to a null character '\0'.
 * If the computed length is strictly greater than given maximal length
 *  <ntstring_length_max16__i>, then the value (<ntstring_length_max16__i> + 1)
 *  is returned.
 *
 * @implementation If ukApp Option DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX is
 *  defined, then it is enforced that given maximal length
 *  <ntstring_length_max16__i> is lower or equal to it. Else a ukProc Fatal
 *  Error is triggered (see ukErrorFatalManage()).
 *
 * @usage When invoked from a ukProc this C-Function does not perform any check
 *  on the access rights granted to the ukProc on the given NTString contents.
 *  In case access is not authorized, an illegal access fault will be
 *  triggered by the MCU (MCU Exception fault), and the uKernel will trigger
 *  a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 *
 * @param[in] (TukNTCSTRING_ADDRESS)ntstring_addr__i Start address of the
 *  NTString.
 * @param[in] (TukLENGTH16)ntstring_length_max16__i Maximal length authorized
 *  for the NTString.
 *
 * @return (TukLENGTH16)NTString 16-bit length.
 * @retval 0 The given NTString start address <ntstring_addr__i> is equal to
 *  one of the value in { DukADDRESS_INVALID, DukADDRESS_IGNORE, NULL }.
 * @retval (<ntstring_length_max__i> + 1) The NTString length is strictly
 *  greater than <ntstring_length_max__i>.
 */
TukLENGTH16 CAukFUNC_RETURN_VALUE_CHECK ukNTStringGetLength16(
                                TukNTCSTRING_ADDRESS ntstring_addr__i,
                                TukLENGTH16          ntstring_length_max16__i);


#endif /* !defined(UKCORE) */


#endif /* !defined(__ASSEMBLER__) */


/* ######################################################################## */
/*                  UKERNEL API - HELPERS - INLINED C-FUNCTIONS             */
/* ######################################################################## */
/* Hereafter are defined the inlined C-Functions composing the uKernel
 *  Helpers of the uKernel API.
 * These inlined C-Functions are implementing the small processing supporting
 *  the implementation of the functionalities provided by the uKernel API.
 *
 * @implementation Most of uKernel Helpers implementation is composed of code
 *  integrated with ukApp's one during compilation (thus executing as part of
 *  the ukProc execution context).
 *  In case some uKernel Privileges Services are used in their implementation,
 *  it is explicitly stated in their associated documentation.
 */

/* The Inlined C-Functions declarations shall not be done when this file is
 *  used by the C-Assembler. */
#if !defined(__ASSEMBLER__)


/* //////////////////////////////////////////////////////////////////////// */
/*  HELPERS - INLINED C-FUNCTIONS - COMPILER DEPENDENT - BIT MANIPULATIONS  */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                                  ukVAL_CLZ32                             */
/* ======================================================================== */
/**
 * @brief Inlinable C-Function as helper for counting the number of leading
 *  zero bits in a 32-bit value.
 *
 * This inlinable C-Function counts the number of leading zero bits in the
 *  given 32-bit value.
 * If the given value is null(0), then value 32 is returned.
 *
 * Example:
 *     value32__i  |  returned value
 *  - 0x00000000   |         32
 *  - 0x00000001   |         31
 *  - 0x0000001F   |         27
 *  - 0x100000AA   |         03
 *  - 0x8000BBBB   |         00
 *
 * @impl __CLZ is defined by CMSIS.
 */
static inline CAukFUNC_INLINE_ALWAYS TukIDX8 ukVAL_CLZ32(
                                                  TukUINT32 value32__i)  {
    return (TukIDX8)__CLZ(value32__i);
}


/* //////////////////////////////////////////////////////////////////////// */
/*          HELPERS - INLINED C-FUNCTIONS - CHARACTER MANAGEMENT            */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                                ukCharToUpper                             */
/* ======================================================================== */
/**
 * @brief C-Function converting given character to upper case.
 *
 * This C-Function converts given character to upper case.
 *
 * If given character is not in ['a' ... 'z'] then returned character is
 *  unchanged.
 *
 * @param[in] (TukCHAR)char__i Character to convert to upper case.
 *
 * @return (TukCHAR)Character converted to upper case.
 */
static inline CAukFUNC_INLINE_ALWAYS TukCHAR ukCharToUpper(TukCHAR char__i) {
    /* Check if given character is lower alphabetic. */
    if ( (char__i <= 'z') && (char__i >= 'a')) {
        /* Given character is lower alphabetic: we convert it to upper one. */
        char__i = (TukCHAR)(char__i - 0x20);
    }

    return(char__i);
}


/* //////////////////////////////////////////////////////////////////////// */
/*                HELPERS - INLINED C-FUNCTIONS - BIT VECTOR                */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(UKCORE)

/* ======================================================================== */
/*                               ukBitVectorClear                           */
/* ======================================================================== */
/** @brief C-Function clearing a Bit Vector.
 *
 * This C-Function clears the given Bit Vector (resets all its bits to 0).
 *
 * @implementation See TukBITVECTOR_ELEMENT C-Type for the structure of a Bit
 *  Vector.
 *
 * @param[in] (TukBITVECTOR_ELEMENT *)bitvector__i Bit Vector to be cleared
 *  (i.e. Address of the first Bit Vector Element entry composing the array
 *  representing the Bit Vector).
 * @param[in] (TukCOUNT16)bitvector_bitcount16__i Count of bits in the Bit
 *  Vector.
 */
static inline CAukFUNC_INLINE_ALWAYS void ukBitVectorClear(
                            TukBITVECTOR_ELEMENT   *bitvector__i,
                            const TukCOUNT16        bitvector_bitcount16__i) {

TukUINT32 bv_idx32;
   /* Clear the bitmap by putting null value in each of its elements. */
   for (bv_idx32 = 0;
        bv_idx32 < MukBITVECTOR_ELEMENT_COUNT(bitvector_bitcount16__i);
        bv_idx32++) {
        bitvector__i[bv_idx32]= 0;
   }

   return;
}


/* ======================================================================== */
/*                              ukBitVectorSetBit                           */
/* ======================================================================== */
/** @brief C-Function setting a bit in a Bit Vector.
 *
 * This C-Function sets (put to 1) a bit referenced by given bit number
 *  <bit_number__i> (the bit number 0 is the leftmost bit) in the given Bit
 *  Vector.
 *
 * @implementation See TukBITVECTOR_ELEMENT C-Type for the structure of a Bit
 *  Vector.
 *
 * @param[in] (TukBITVECTOR_ELEMENT *)bitvector__i Bit Vector to operate on
 *  (i.e. address of the first Bit Vector Element entry composing the array
 *  representing the Bit Vector).
 * @param[in] (TukCOUNT16)bitvector_bitcount16__i Count of bits in the Bit
 *  Vector.
 * @param[in] (TukBITVECTOR_BITNUM)bitvector_bitnum__i Bit number to be set
 *  (the bit number 0 is the leftmost bit).
 */
static inline CAukFUNC_INLINE_ALWAYS void ukBitVectorSetBit(
                            TukBITVECTOR_ELEMENT       *bitvector__i,
                            const TukCOUNT16            bitvector_bitcount16__i,
                            const TukBITVECTOR_BITNUM   bitvector_bitnum__i) {
    /* ROBUSTNESS: Check that the parameter <bitvector_bitnum__i> is not exceeding the
     *  number of bits <bitvector_bits_count__i> stored in the Bit Vector. */
    if (bitvector_bitnum__i > bitvector_bitcount16__i ) {
        ukErrorFatalManage(DukSTATUS_ERR_PARAM);
    } else {
        /* Set (put at 1) the bit at the position 'bitvector_bitnum__i' in the Bit Vector
         *  (the bit number 0 is the leftmost bit). */
        bitvector__i[bitvector_bitnum__i >> 5] |=
                (TukBITVECTOR_ELEMENT)(1UL << (31U - (bitvector_bitnum__i & 0x1FU)));
    }

    return;
}


/* ======================================================================== */
/*                            ukBitVectorResetBit                           */
/* ======================================================================== */
/** @brief C-Function resetting a bit in a Bit Vector.
 *
 * This C-Function resets (put to 0) a bit referenced by given bit number
 *  <bit_number__i> (the bit number 0 is the leftmost bit) in the given Bit
 *  Vector.
 *
 * @implementation See TukBITVECTOR_ELEMENT C-Type for the structure of a Bit
 *  Vector.
 *
 * @param[in] (TukBITVECTOR_ELEMENT *)bitvector__i Bit Vector to operate on
 *  (i.e. address of the first Bit Vector Element entry composing the array
 *  representing the Bit Vector).
 * @param[in] (TukCOUNT16)bitvector_bitcount16__i Count of bits in the Bit
 *  Vector.
 * @param[in] (TukBITVECTOR_BITNUM)bitvector_bitnum__i Bit number to be reset
 *  (the bit number 0 is the leftmost bit).
 */
static inline CAukFUNC_INLINE_ALWAYS void ukBitVectorResetBit(
                            TukBITVECTOR_ELEMENT       *bitvector__i,
                            const TukCOUNT16            bitvector_bitcount16__i,
                            const TukBITVECTOR_BITNUM   bitvector_bitnum__i) {
    /* ROBUSTNESS: Check that the parameter <bitvector_bitnum__i> is not exceeding the
     *  number of bits <bitvector_bits_count__i> stored in the Bit Vector. */
    if (bitvector_bitnum__i > bitvector_bitcount16__i ) {
        ukErrorFatalManage(DukSTATUS_ERR_PARAM);
    } else {
        /* Reset (put at 0) the bit at the position 'bitvector_bitnum__i' in the Bit
         *  Vector (the bit number 0 is the leftmost bit). */
        bitvector__i[bitvector_bitnum__i >> 5] &=
                (TukBITVECTOR_ELEMENT)(~(1UL << (31U - (bitvector_bitnum__i & 0x1FU))));
    }

    return;
}


/* ======================================================================== */
/*                            ukBitVectorInvertBit                          */
/* ======================================================================== */
/** @brief C-Function inverting a bit in a Bit Vector.
 *
 * This C-Function inverts (change 0 to 1, and 1 to 0) a bit referenced by its
 *  by given bit number <bit_number__i> (the bit number 0 is the leftmost bit)
 *  in the given Bit Vector.
 *
 * @implementation See TukBITVECTOR_ELEMENT C-Type for the structure of a Bit
 *  Vector.
 *
 * @param[in] (TukBITVECTOR_ELEMENT *)bitvector__i Bit Vector to operate on
 *  (i.e. address of the first Bit Vector Element entry composing the array
 *  representing the Bit Vector).
 * @param[in] (TukCOUNT16)bitvector_bitcount16__i Count of bits in the Bit
 *  Vector.
 * @param[in] (TukBITVECTOR_BITNUM)bitvector_bitnum__i Bit number to be inverted
 *  (the bit number 0 is the leftmost bit).
 */
static inline CAukFUNC_INLINE_ALWAYS void ukBitVectorInvertBit(
                            TukBITVECTOR_ELEMENT       *bitvector__i,
                            const TukCOUNT16            bitvector_bitcount16__i,
                            const TukBITVECTOR_BITNUM   bitvector_bitnum__i) {
    /* ROBUSTNESS: Check that the parameter <bitvector_bitnum__i> is not exceeding the
     *  number of bits <bitvector_bits_count__i> stored in the Bit Vector. */
    if (bitvector_bitnum__i > bitvector_bitcount16__i ) {
        ukErrorFatalManage(DukSTATUS_ERR_PARAM);
    } else {
        /* Invert the bit at the position 'bitvector_bitnum__i' in the Bit Vector
         *  (the bit number 0 is the leftmost bit). */
        bitvector__i[bitvector_bitnum__i >> 5] ^=
                (TukBITVECTOR_ELEMENT)(1UL << (31U - (bitvector_bitnum__i & 0x1FU)));
    }

    return;
}


/* ======================================================================== */
/*                             ukBitVectorTestBit                           */
/* ======================================================================== */
/** @brief C-Function testing a bit in a Bit Vector.
 *
 * This C-Function tests if a bit referenced by given bit number
 *  <bit_number__i> (the bit number 0 is the leftmost bit) in the given Bit
 *  Vector is set (equals to 1).
 *
 * @implementation See TukBITVECTOR_ELEMENT C-Type for the structure of a Bit
 *  Vector.
 *
 * @param[in] (TukBITVECTOR_ELEMENT *)bitvector__i Bit Vector to operate on
 *  (i.e. address of the first Bit Vector Element entry composing the array
 *  representing the Bit Vector).
 * @param[in] (TukCOUNT16)bitvector_bitcount16__i Count of bits in the Bit
 *  Vector.
 * @param[in] (TukBITVECTOR_BITNUM)bitvector_bitnum__i Bit number to be tested
 *  (the bit number 0 is the leftmost bit).
 *
 * @return (TukBOOL)Boolean value indicating the result of test.
 * @retval DukBOOL_TRUE The referenced bit is set (equals to 1).
 * @retval DukBOOL_FALSE The referenced bit is at (equals to 0).
 */
static inline CAukFUNC_INLINE_ALWAYS TukBOOL ukBitVectorTestBit(
                            TukBITVECTOR_ELEMENT       *bitvector__i,
                            const TukCOUNT16            bitvector_bitcount16__i,
                            const TukBITVECTOR_BITNUM   bitvector_bitnum__i) {
    /* ROBUSTNESS: Check that the parameter <bitvector_bitnum__i> is not exceeding the
     *  number of bits <bitvector_bits_count__i> stored in the Bit Vector. */
    if (bitvector_bitnum__i > bitvector_bitcount16__i ) {
        ukErrorFatalManage(DukSTATUS_ERR_PARAM);
        return(DukBOOL_FALSE);
    } else {
        /* Test the bit at the position 'bitvector_bitnum__i' in the Bit Vector
         *  (the bit number 0 is the leftmost bit). */
        return ( ( ( bitvector__i[bitvector_bitnum__i >> 5] &
                   (TukBITVECTOR_ELEMENT)(1UL << (31U - (bitvector_bitnum__i & 0x1FU)))
                 ) != 0U
               ) ? DukBOOL_TRUE : DukBOOL_FALSE
             );
    }
}

#endif /* !defined(UKCORE) */


/* //////////////////////////////////////////////////////////////////////// */
/*              HELPERS - INLINED C-FUNCTIONS - UKCORE VERSION              */
/* //////////////////////////////////////////////////////////////////////// */
#if !defined(UKCORE)

/* ======================================================================== */
/*                          ukUKCoreGetReleaseVersion                       */
/* ======================================================================== */
/** @brief C-Function returning the Version of the uKernel Core code used for
 *  the uKernel Release
 *
 * This C-Function returns the Version of the uKernel Core code used for the
 *  uKernel Release.
 *
 * @warning This C-Function uses the uKernel Privileged Service
 *  ukUKCoreGetAttribute() to retrieve the Version of the uKernel Core
 *  code used for the uKernel Release. Thus it modifies the
 *  <ServiceParameter.Output> field of the C-Variable
 *  GVukappBlockDataSharedUKSVC of the ukApp.
 *
 * @return(TukVERSION) Version of the uKernel Core code used for the uKernel
 *  Release.
 *
 * @fatal DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR The retrieved
 *  Version of the uKernel Core code used for the uKernel Release is not
 *  consistent with the one defined in C-Constant DukRELEASE_UKERNEL_VERSION
 *  of uKernel API used for compiling the ukApp code.
 */
static inline CAukFUNC_INLINE_ALWAYS TukVERSION ukUKCoreGetReleaseVersion(
                            void) {

TukVERSION ukcore_release_version;
    /* Retrieve the uKernel Release Version. */
    (void)ukUKCoreGetAttribute(DukUKCORE_ATTRIBUTE_TAG_RELEASE_VERSION);
    ukcore_release_version = *((TukVERSION *)&(GVukappUKSVCOutput[4]));

   return(ukcore_release_version);
}

#endif /* !defined(UKCORE) */


#endif /* !defined(__ASSEMBLER__) */


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_HELPERS_H_INSIDE
#endif /* !defined(UK_HELPERS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

