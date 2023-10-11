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
 * @file          uk_hw_mcu_core_arm_cmx.c
 * @brief         uKernel API - Platform MCU Core specific implementation.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *  This file contains the Platform's MCU Core specific part of the C-Code
 *  composing the implementation the uKernel API.
 *
 * This file supports the following Platform MCU Cores:
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
 *  This file SHALL NOT BE MODIFIED.
 *  It shall be used only for compiling and linking ukApp aiming at running on
 *   this given uKernel Target.
 *  If improper version is used, the ukApp proper execution cannot be
 *   guaranteed. However, the ukApp security properties, and notably its
 *   isolation, remain always enforced even in case an improper version is
 *   used.
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
/* Do not compile this file if compiling uKernel Core implementation. */
#if !defined(UKCORE)

/*__________________________________________________________________________*/
/* Source the uKernel Configuration file part of uKernel API used for the
 *  compilation of the given uKernel Target (i.e uKernel Target definitions,
 *  uKernel Features defined, uKernel Options values, ...). */
#ifndef __IARCC__
#include "uk/include/uk_config.h"
#else
#include "uk.h"
#endif

/* Compile the file only if the selected Platform's MCU Core is supported by
 *  this file. */
#if defined(SukCONFIG_HW_MCU_CORE_ARM_CMX)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_HW_MCU_CORE_ARM_CMX_C

/* Define that we are inside a C-file of the module (definition is undone at
 *  its end). */
#define  UK_INMODULE

/*__________________________________________________________________________*/
/* Source the public uKernel API include files. */
#ifndef __IARCC__
#include "uk/include/uk.h"
#else
#include "uk.h"
#endif

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */
#include <stdarg.h>


/* ######################################################################## */
/*         UKAPP UKERNEL FRAMEWORK PRIVATE / MCU CORE - C-FUNCTIONS         */
/* ######################################################################## */
/* Hereafter are defined the C-Functions of the ukApp uKernel Framework, part
 *  of its Private API (used only in its internal implementation), and whose
 *  implementation is depending of the used MCU Core in the selected
 *  Platform.
 * These C-Functions are implementing the sub-functionalities supporting the
 *  implementation of the functionalities provided by the ukApp uKernel
 *  Framework.
 */

/* ======================================================================== */
/*                           ukappEntryPointReturn                          */
/* ======================================================================== */
void ukappEntryPointReturn(void) {

    /* Invoke the uKernel Privileged Service ukUKProcEntryPointReturn(). */
    ukSVC(DukSVC_ID8_ukUKProcEntryPointReturn);

    return;
}


/* ######################################################################## */
/*         UKERNEL API / MCU CORE - UKERNEL UNPRIVILEGED SERVICES           */
/* ######################################################################## */
/* Hereafter are defined the uKernel Unprivileged Service entry points, part
 *  of the uKernel API, and whose implementation is depending of the used MCU
 *  Core in the selected Platform.
 *
 * NOTE: See the uKernel API "uk.h" for the documentation relative to these
 *  C-Functions.
 *
 * @implementation Some of these uKernel Services may be implemented as code
 *  that will be integrated with ukApp source code during compilation, or
 *  as invocation of uKernel Privileged Services, or as a combination of both.
 *  No assumption shall be done on the way this implementation is done (it may
 *  depend of Platform selected, uKernel Target used).
 */

/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL UNPRIVILEGED SERVICES - RANDOM HELPERS               */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                        ukRandomXorShift32Generate                        */
/* ======================================================================== */
TukUINT32 ukRandomXorShift32Generate(void) {
static TukUINT32 prng_state = 0;

/* ROBUSTNESS: Please note that the XorShift32 generator is NOT A SAFE TRUE
 *  RANDOM GENERATOR. It shall be used only for testing or when low quality
 *  pseudo random numbers are needed (e.g. wiping buffer, ...).
 * @implementation In order to keep proper entropy level of the XorShift32
 *  generator, while keeping good performance level, we seed the generator with
 *  true random value on a period of around 64K random values generated.
 * The 64K period is evaluated statistically (thus not fully accurate) by
 *  checking if the 16 LSB bits of the internal state of the XorShift32 PRNG
 *  are null.
 * Upon very first generation, the 16 LSB bits are null, and a seed is thus
 *  automatically retrieved.
 */
    if ((prng_state & 0xFFFFUL) == 0) {
        /* The internal state of the XorShift-32bit PRNG needs to be seeded.
         * We retrieve a 64-bit random value (only 'Standard' quality needed)
         *  using uKernel Service. */
        ukRandomGetBytes(DukRNG_ID_PRNG, 8);
        prng_state = *((TukUINT32 *)
                (GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    }

/* Generate next XorShift32 PRNG 32-bit value.
 * The new internal state is computed using XorShift32 Georges MARSAGLIA
 *  coefficients '13, 17, 5'. */
    prng_state ^= prng_state << 13;
    prng_state ^= prng_state >> 17;
    prng_state ^= prng_state << 5;

/* Return the 32-bit generated random value from XorShift32 PRNG */
    return(prng_state);
}


/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL UNPRIVILEGED SERVICES - BUFFER MANAGEMENT HELPERS         */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                               ukBufferClear                              */
/* ======================================================================== */
void ukBufferClear(TukADDRESS32 buffer_addr__i,
                      TukLENGTH32  buffer_length32__i) {

    /* Clear the buffer using 32-bit words to achieve best performance.
     * NOTE: On some chip, even best performance may be achieved if the buffer
     *  address is 32-bit aligned. But as we want this function be core generic,
     *  we do not perform any specific optimization for handling the case where
     *  it is not aligned (only a recommendation is done in the documentation).
     */
    while (buffer_length32__i >= 4) {
        *((TukUINT32 *)buffer_addr__i) = 0UL;
        buffer_addr__i += 4;
        buffer_length32__i -= 4;
    }

    /* Check if some remaining bytes to be cleared remain after having processed
     *  the buffer using 32-bit words. */
    if (buffer_length32__i != 0) {
      /* Clear the remaining bytes in the buffer. */
      while (buffer_length32__i > 0) {
          *((TukUINT8 *)buffer_addr__i) = 0;
          buffer_addr__i += 1;
          buffer_length32__i -= 1;
      }
    }

    return;
}


/* ======================================================================== */
/*                                ukBufferCopy                              */
/* ======================================================================== */
void ukBufferCopy(TukADDRESS32 buffer_src_addr__i,
                     TukADDRESS32 buffer_dest_addr__i,
                     TukLENGTH32  buffer_length32__i) {

    /* Copy the buffer using 32-bit words to achieve best performance.
     * NOTE: On some chip, even best performance may be achieved if the buffer
     *  address is 32-bit aligned. But as we want this function be core generic,
     *  we do not perform any specific optimization for handling the case where
     *  it is not aligned (only a recommendation is done in the documentation).
     */
    while (buffer_length32__i >= 4) {
        *((TukUINT32 *)buffer_dest_addr__i) =
                *((TukUINT32 *)buffer_src_addr__i);
        buffer_src_addr__i += 4;
        buffer_dest_addr__i += 4;
        buffer_length32__i -= 4;
    }

    /* Check if some remaining bytes to be cleared remain after having processed
     *  the buffer using 32-bit words. */
    if (buffer_length32__i != 0) {
        /* Clear the remaining bytes in the buffer. */
        while (buffer_length32__i > 0) {
            *((TukUINT8 *)buffer_dest_addr__i) =
                    *((TukUINT8 *)buffer_src_addr__i);
            buffer_src_addr__i += 1;
            buffer_dest_addr__i += 1;
            buffer_length32__i -= 1;
        }
    }

    return;
}


/* ======================================================================== */
/*                           ukBufferCompareQuick                           */
/* ======================================================================== */
TukBOOL ukBufferCompareQuick(TukADDRESS32 buffer1_src_addr__i,
                             TukADDRESS32 buffer2_src_addr__i,
                             TukLENGTH32  buffer_length32__i) {

  /* Compare the buffer using 32-bit words to achieve best performance.
   * NOTE: On some chip, even best performance may be achieved if the buffer
   *  address is 32-bit aligned. But as we want this function be core generic,
   *  we do not perform any specific optimization for handling the case where
   *  it is not aligned (only a recommendation is done in the documentation).
   */
    while (buffer_length32__i >= 4) {
        if ( *((TukUINT32 *)buffer1_src_addr__i) !=
             *((TukUINT32 *)buffer2_src_addr__i) ) {
            return(DukBOOL_FALSE);
        }
        buffer1_src_addr__i += 4;
        buffer2_src_addr__i += 4;
        buffer_length32__i -= 4;
    }

    /* Check if some remaining bytes to be compared remain after having processed
     *  the buffer using 32-bit words. */
    if (buffer_length32__i != 0) {
        /* Compare the remaining bytes in the buffer. */
        while (buffer_length32__i > 0) {
            if ( *((TukUINT8 *)buffer1_src_addr__i) !=
                 *((TukUINT8 *)buffer2_src_addr__i) ) {
                return(DukBOOL_FALSE);
            }
            buffer1_src_addr__i += 1;
            buffer2_src_addr__i += 1;
            buffer_length32__i -= 1;
        }
    }

    /* Both buffer have the same contents. */
    return(DukBOOL_TRUE);
}


/* ======================================================================== */
/*                              ukBufferCompare                             */
/* ======================================================================== */
TukSAFEBOOL ukBufferCompare(
                    TukADDRESS32 buffer1_src_addr__i,
                    TukADDRESS32 buffer2_src_addr__i,
                    TukLENGTH32  buffer_length32__i) {
TukLENGTH32 buffer_length_remaining32;
TukCOUNT32 buffer_diff_count;
TukCOUNT32 buffer_equal_count;

    /* Compare the buffer using 32-bit words to achieve best performance.
     * NOTE: On some chip, even best performance may be achieved if the buffer
     *  address is 32-bit aligned. But as we want this function be core generic,
     *  we do not perform any specific optimization for handling the case where
     *  it is not aligned (only a recommendation is done in the documentation).
     */
    buffer_length_remaining32 = buffer_length32__i;
    buffer_diff_count = 0;
    buffer_equal_count = 0;
    while (buffer_length_remaining32 >= 4) {
        if ( *((TukUINT32 *)buffer1_src_addr__i) !=
             *((TukUINT32 *)buffer2_src_addr__i) ) {
            buffer_diff_count += 4;
        } else {
            buffer_equal_count += 4;
        }
        buffer1_src_addr__i += 4;
        buffer2_src_addr__i += 4;
        buffer_length_remaining32 -= 4;
    }

    /* Check if some remaining bytes to be compared remain after having
     *  processed the buffer using 32-bit words. */
    while (buffer_length_remaining32 > 0) {
        if ( *((TukUINT8 *)buffer1_src_addr__i) !=
           *((TukUINT8 *)buffer2_src_addr__i) ) {
            buffer_diff_count++;
        } else {
            buffer_equal_count++;
        }
        buffer1_src_addr__i += 1;
        buffer2_src_addr__i += 1;
        buffer_length_remaining32 -= 1;
    }

    /* Check if the both buffers have same contents. */
    if ((buffer_diff_count == 0) &&
        (buffer_equal_count == buffer_length32__i) ) {
        /* Both buffer have the same contents. */
        return(DukSAFEBOOL_TRUE);
    }

    /* Enforce that the whole contents of the buffer has been checked. */
    if ((buffer_equal_count + buffer_diff_count) == buffer_length32__i) {
        return(DukSAFEBOOL_FALSE);
    }

    /* Fatal Error: the whole contents of the buffer has not been properly
     *  checked. */
    ukErrorFatalManage(DukSTATUS_ERR_UNEXPECTED);
    return(DukSAFEBOOL_FALSE);
}

/* ======================================================================== */
/*                              ukBufferWipe                                */
/* ======================================================================== */
void ukBufferWipe(TukADDRESS32 buffer_addr__i,
                     TukLENGTH32  buffer_length32__i) {
TukUINT32 prng_value32;

    /* Wipe the buffer using 32-bit words to achieve best performance.
     * @implementation On some MCU, best performance are achieved if the buffer
     *  start address is 32-bit aligned. But as we want this function be
     *  generic, we do not perform any specific optimization for handling the
     *  case where it is not aligned (only a recommendation is done in the
     *  documentation).
     */
    while (buffer_length32__i > 3) {
        prng_value32 = ukRandomXorShift32Generate();
        *((TukUINT32 *)buffer_addr__i) = prng_value32;
        buffer_addr__i += 4;
        buffer_length32__i -= 4;
    }

    /* Check if some remaining bytes to be wiped remain after having processed
     *  the buffer using 32-bit words. */
    if (buffer_length32__i != 0) {
        /* Some remaining bytes (up to 3) need to be wiped in the buffer. */
        prng_value32 = ukRandomXorShift32Generate();
        while (buffer_length32__i > 0) {
            *((TukUINT8 *)buffer_addr__i) = (TukUINT8)prng_value32;
            buffer_addr__i += 1;
            buffer_length32__i -= 1;
            prng_value32 = (TukUINT32)(prng_value32 >> 8);
        }
    }

    return;
}


/* //////////////////////////////////////////////////////////////////////// */
/*        UKERNEL UNPRIVILEGED SERVICES - STRING MANAGEMENT HELPERS         */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                             ukNTStringGetLength8                         */
/* ======================================================================== */
TukLENGTH8 ukNTStringGetLength8(TukNTCSTRING_ADDRESS ntstring_addr__i) {
TukLENGTH8 ntstring_length8;

    /* Check if given NTString Address is invalid or has to be ignored. */
    if ( (ntstring_addr__i == (TukNTCSTRING_ADDRESS)DukADDRESS_INVALID) ||
         (ntstring_addr__i == (TukNTCSTRING_ADDRESS)DukADDRESS_IGNORE)  ||
         (ntstring_addr__i == (TukNTCSTRING_ADDRESS)NULL) ) {
        /* We return a null(0) value to prevent access to the NTString
         *  address. */
        return(0U);
    }

    /* Compute the length of given string by seeking up to a null character.
     * @robustness If the length is strictly bigger than 255, then we consider
     *  that the given string is invalid and we return a null length. */
    ntstring_length8 = 0;
    while(ntstring_addr__i[ntstring_length8] != 0) {
      if (ntstring_length8 >= 255) {
        ntstring_length8 = 0;
        break;
      }
      ntstring_length8++;
    }

    return(ntstring_length8);
}


/* ======================================================================== */
/*                           ukNTStringGetLength16                          */
/* ======================================================================== */
TukLENGTH16 CAukFUNC_RETURN_VALUE_CHECK ukNTStringGetLength16(
                            TukNTCSTRING_ADDRESS ntstring_addr__i,
                            TukLENGTH16          ntstring_length_max16__i) {
TukLENGTH16 ntstring_length16;

    /* Check if given NTString Address is invalid or has to be ignored. */
    if ( (ntstring_addr__i == (TukNTCSTRING_ADDRESS)DukADDRESS_INVALID) ||
         (ntstring_addr__i == (TukNTCSTRING_ADDRESS)DukADDRESS_IGNORE)  ||
         (ntstring_addr__i == (TukNTCSTRING_ADDRESS)NULL) ) {
        /* We return a null(0) value to prevent access to the NTString
         *  address. */
        return(0U);
    }

#if defined(DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX)
    /* Enforce that given NTString length is valid. */
    if (ntstring_length_max16__i > DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX) {
        ukErrorFatalManage(DukSTATUS_ERR_PARAM);
    }
#endif /* defined(DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX) */

    /* Compute the length of given string by seeking up to a null character.
     * @robustness If the length is strictly bigger than given maximum length
     * <ntstring_length_max16__i>, then we consider that the given string is
     * invalid and we return <ntstring_length_max16__i>+1 (returning this value
     * will limit the impact in case of no proper checking of the NTString
     * length). */
    ntstring_length16 = 0UL;
    while(ntstring_addr__i[ntstring_length16] != 0UL) {
      if (ntstring_length16 > ntstring_length_max16__i) {
        break;
      }
      ntstring_length16++;
    }

    /* Return computed 16-bit NTString length. */
    return(ntstring_length16);
}


/* ######################################################################## */
/*          UKERNEL API / MCU CORE - UKERNEL PRIVILEGED SERVICES            */
/* ######################################################################## */
/* Hereafter are defined the uKernel Privileged Services Entry Points.
 * @implementation A uKernel Privileges Service Entry Point is requiring
 *  specific privileges reserved to some uKernel code parts to provide
 *  associated service. The corresponding C-Function implementing the service
 *  uses specific MCU instructions to switch to such uKernel privileged code
 *  part. Note that such a switch needs a certain amount of time, depending
 *  of the MCU Core used (in general a few hundred of CPU cycles). */


/* //////////////////////////////////////////////////////////////////////// */
/*              UKERNEL PRIVILEGED SERVICES - UKPROC MANAGEMENT             */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                                ukUKProcExit                              */
/* ======================================================================== */

void ukUKProcExit(TukBOOL                    is_exit_in_error__i         CAukVAR_UNUSED_MAYBE,
                     TukUKPROC_TERMINATION_INFO ukproc_termination_info__i  CAukVAR_UNUSED_MAYBE) {
    ukSVC(DukSVC_ID8_ukUKProcExit);
    return;
}


/* ======================================================================== */
/*                          ukUKProcEntryPointReturn                        */
/* ======================================================================== */
void ukUKProcEntryPointReturn(void) {

    ukSVC(DukSVC_ID8_ukUKProcEntryPointReturn);
    return;
}


/* ======================================================================== */
/*                                ukUKProcYield                             */
/* ======================================================================== */
TukSTATUS ukUKProcYield(TukTIME32_tick yield_delay_systick__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKProcYield, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


#if defined(SukCONFIG_FEATURE_UKAPP_ADMINISTRATION_FINE)
/* ======================================================================== */
/*                              ukUKProcInstantiate                         */
/* ======================================================================== */
TukSTATUS ukUKProcInstantiate(TukUKAPP_AUID   ukapp_auid__i CAukVAR_UNUSED_MAYBE,
                              TukUKPROC_PUID *ukproc_puid__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKProcInstantiate, status_code);
    *ukproc_puid__o = *((TukUKPROC_PUID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}
#endif /* defined(SukCONFIG_FEATURE_UKAPP_ADMINISTRATION_FINE) */



/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL PRIVILEGED SERVICES - WATCHDOG MANAGEMENT             */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC)

/* ======================================================================== */
/*                              ukWatchdogStart                             */
/* ======================================================================== */

TukSTATUS ukWatchdogStart(
        TukWATCHDOG_ATTRIBUTES  wtdg_attr__i                            CAukVAR_UNUSED_MAYBE,
        TukTIME32_tick          wtdg_timer_scheduled_period_systick__i  CAukVAR_UNUSED_MAYBE,
        TukTIME32_tick          wtdg_timer_uptime_period_systick__i     CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukWatchdogStart, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                              ukWatchdogStop                              */
/* ======================================================================== */
TukSTATUS ukWatchdogStop(void) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukWatchdogStop, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                              ukWatchdogKick                              */
/* ======================================================================== */
TukSTATUS ukWatchdogKick(void) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukWatchdogKick, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_WATCHDOG_UKPROC) */


/* //////////////////////////////////////////////////////////////////////// */
/*           UKERNEL PRIVILEGED SERVICES - UKERNEL CORE MANAGEMENT          */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                           ukUKCoreGetAttribute                           */
/* ======================================================================== */
TukSTATUS ukUKCoreGetAttribute(TukUKCORE_ATTRIBUTE_TAG ukcore_attr_tag__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKCoreGetAttribute, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}



/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL PRIVILEGED SERVICES - PLATFORM MANAGEMENT            */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                          ukPlatformGetAttribute                          */
/* ======================================================================== */
TukSTATUS ukPlatformGetAttribute(TukPLATFORM_ATTRIBUTE_TAG platform_attr_tag__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPlatformGetAttribute, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                          ukPlatformSetAttribute                          */
/* ======================================================================== */
TukSTATUS ukPlatformSetAttribute(TukPLATFORM_ATTRIBUTE_TAG platform_attr_tag__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPlatformSetAttribute, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL PRIVILEGED SERVICES - UKAPP MANAGEMENT               */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                         ukUKAppGetAIDXFromAUID                           */
/* ======================================================================== */
TukSTATUS ukUKAppGetAIDXFromAUID(TukUKAPP_AUID  app_auid__i CAukVAR_UNUSED_MAYBE,
                                 TukUKAPP_AIDX *app_aidx__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKAppGetAIDXFromAUID, status_code);
    *app_aidx__o = *((TukUKAPP_AIDX *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                              ukUKAppGetAttribute                         */
/* ======================================================================== */
TukSTATUS ukUKAppGetAttribute(TukUKAPP_AIDX app_aidx__i CAukVAR_UNUSED_MAYBE,
                            TukUKAPP_ATTRIBUTE_TAG app_attr_tag__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKAppGetAttribute, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL PRIVILEGED SERVICES - UKPROC INFORMATION             */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                           ukUKProcGetPUIDFromAUID                        */
/* ======================================================================== */
TukSTATUS ukUKProcGetPUIDFromAUID(TukUKAPP_AUID   ukapp_auid__i CAukVAR_UNUSED_MAYBE,
                                TukUKPROC_PUID *ukproc_puid__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKProcGetPUIDFromAUID, status_code);
    *ukproc_puid__o = *((TukUKPROC_PUID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                            ukUKProcGetAttribute                          */
/* ======================================================================== */
TukSTATUS ukUKProcGetAttribute(TukUKPROC_PUID             ukproc_puid__i CAukVAR_UNUSED_MAYBE,
                             TukUKPROC_ATTRIBUTE_TAG    ukproc_attr_tag__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKProcGetAttribute, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL PRIVILEGED SERVICES - TIME INFORMATION               */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                                ukUptimeGet_us                            */
/* ======================================================================== */
TukTIME64_us ukUptimeGet_us(void){
TukTIME64_us return_value;

    ukSVC_RETURN64(DukSVC_ID8_ukUptimeGet_us, return_value);
    return(return_value);
}

/* ======================================================================== */
/*                              ukSystickGetCount                           */
/* ======================================================================== */
TukTIME64_tick ukSystickGetCount(void){
TukTIME64_tick return_value;

    ukSVC_RETURN64(DukSVC_ID8_ukSystickGetCount, return_value);
    return(return_value);
}



/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL PRIVILEGED SERVICES - IPC MANAGEMENT               */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                       ukIPCSendNotificationToProcess                     */
/* ======================================================================== */
TukSTATUS ukIPCSendNotificationToProcess(TukUKPROC_PUID proc_notified_puid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukIPCSendNotificationToProcess, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                           ukIPCSendDataToProcess                         */
/* ======================================================================== */
TukSTATUS ukIPCSendDataToProcess(TukUKPROC_PUID proc_to_puid__i CAukVAR_UNUSED_MAYBE,
                                 TukIPC_MODE     ipc_mode__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukIPCSendDataToProcess, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                                ukIPCReceive                              */
/* ======================================================================== */
TukSTATUS ukIPCReceive(TukUKPROC_PUID proc_from_puid__i CAukVAR_UNUSED_MAYBE,
                       TukIPC_MODE     ipc_mode__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukIPCReceive, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                        ukIPCSendReceiveDataToProcess                     */
/* ======================================================================== */
TukSTATUS ukIPCSendReceiveDataToProcess(TukUKPROC_PUID proc_tofrom_puid__i CAukVAR_UNUSED_MAYBE,
                                        TukIPC_MODE     ipc_mode__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukIPCSendReceiveDataToProcess, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC(status_code, __FUNCTION__);
    return(status_code);
}


/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL PRIVILEGED SERVICES - ADDRESS BLOCK MANAGEMENT          */
/* //////////////////////////////////////////////////////////////////////// */


/* ======================================================================== */
/*                          ukAddressBlockGetInfo                           */
/* ======================================================================== */
TukSTATUS ukAddressBlockGetInfo(TukADDRESSBLOCK_ID              abid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockGetInfo, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                      ukAddressBlockGetIDFromLabel                        */
/* ======================================================================== */
TukSTATUS ukAddressBlockGetIDFromLabel(TukADDRESSBLOCK_LABEL ab_label__i CAukVAR_UNUSED_MAYBE,
                                       TukADDRESSBLOCK_ID   *abid__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockGetIDFromLabel, status_code);
    *abid__o = *((TukADDRESSBLOCK_ID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                       ukAddressBlockGetBundleID                          */
/* ======================================================================== */
TukSTATUS ukAddressBlockGetBundleID(TukADDRESSBLOCK_ID             abid__i CAukVAR_UNUSED_MAYBE,
                                    TukADDRESSBLOCK_ID            *abid_bundle__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockGetBundleID, status_code);
    *abid_bundle__o = *((TukADDRESSBLOCK_ID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* //////////////////////////////////////////////////////////////////////// */
/*      UKERNEL PRIVILEGED SERVICES - ADDRESS BLOCK WINDOW MANAGEMENT       */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                          ukAddressBlockWindowMap                         */
/* ======================================================================== */
TukSTATUS ukAddressBlockWindowMap(TukADDRESSBLOCKWINDOW_IDX     abwidx__i CAukVAR_UNUSED_MAYBE,
                                  TukADDRESSBLOCK_ID             abid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockWindowMap, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                          ukAddressBlockWindowUnMap                       */
/* ======================================================================== */
TukSTATUS ukAddressBlockWindowUnMap(TukADDRESSBLOCKWINDOW_IDX   abwidx__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockWindowUnMap, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                         ukAddressBlockWindowGetMapped                    */
/* ======================================================================== */
TukSTATUS ukAddressBlockWindowGetMapped(TukADDRESSBLOCKWINDOW_IDX abwidx__i CAukVAR_UNUSED_MAYBE,
                                        TukADDRESSBLOCK_ID        *abid__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukAddressBlockWindowGetMapped, status_code);
    *abid__o = *((TukADDRESSBLOCK_ID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* //////////////////////////////////////////////////////////////////////// */
/*          UKERNEL PRIVILEGED SERVICES - SHARED BUFFER MANAGEMENT          */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_SHARED_BUFFERS)

/* ======================================================================== */
/*                        ukSharedBufferResetCredentials                    */
/* ======================================================================== */
TukSTATUS ukSharedBufferResetCredentials(TukADDRESSBLOCK_ID shbuf_abid_bundle__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukSharedBufferResetCredentials, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                         ukSharedBufferAddCredentials                     */
/* ======================================================================== */
TukSTATUS ukSharedBufferAddCredentials(TukADDRESSBLOCK_ID           shbuf_abid_bundle__i CAukVAR_UNUSED_MAYBE,
                                       TukUKPROC_PUID               ukproc_to_puid__i CAukVAR_UNUSED_MAYBE,
                                       TukADDRESSBLOCK_ATTRIBUTES   shbuf_proc_attr__i CAukVAR_UNUSED_MAYBE)  {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukSharedBufferAddCredentials, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                           ukSharedBufferTransfer                         */
/* ======================================================================== */
TukSTATUS ukSharedBufferTransfer(TukADDRESSBLOCK_ID shbuf_abid_bundle__i CAukVAR_UNUSED_MAYBE,
                                 TukUKPROC_PUID proc_to_puid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukSharedBufferTransfer, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_SHARED_BUFFERS) */


/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL PRIVILEGED SERVICES - PERIPHERAL IRQ MANAGEMENT          */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ)

/* ======================================================================== */
/*                            ukPeripheralIRQRegister                       */
/* ======================================================================== */
TukSTATUS ukPeripheralIRQRegister(
        TukPIRQ_MCU_IDX PIRQ_hw_id__i CAukVAR_UNUSED_MAYBE,
        TukPIRQ_ATTRIBUTES PIRQ_state_process__i CAukVAR_UNUSED_MAYBE,
        TukPIRQ_REGISTRATION_ID *PIRQ_reg_id__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPeripheralIRQRegister, status_code);
    *PIRQ_reg_id__o = *((TukPIRQ_REGISTRATION_ID *)
            (GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                          ukPeripheralIRQUnregister                       */
/* ======================================================================== */
TukSTATUS ukPeripheralIRQUnregister(
        TukPIRQ_REGISTRATION_ID PIRQ_reg_id__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPeripheralIRQUnregister, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                            ukPeripheralIRQGetInfo                        */
/* ======================================================================== */
TukSTATUS ukPeripheralIRQGetInfo(
        TukPIRQ_REGISTRATION_ID PIRQ_reg_id__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPeripheralIRQGetInfo, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                        ukPeripheralIRQPerformAction                      */
/* ======================================================================== */
TukSTATUS ukPeripheralIRQPerformAction(
        TukPIRQ_REGISTRATION_ID pirq_reg_id__i CAukVAR_UNUSED_MAYBE,
        TukPIRQ_ACTION pirq_action__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPeripheralIRQPerformAction, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}
#endif /* defined(SukCONFIG_FEATURE_PERIPHERAL_IRQ) */


/* //////////////////////////////////////////////////////////////////////// */
/*            UKERNEL API - PRIVILEGED - MCU REGISTERS MANAGEMNET           */
/* //////////////////////////////////////////////////////////////////////// */

/* ======================================================================== */
/*                             ukMCURegisterRead                            */
/* ======================================================================== */
TukSTATUS ukMCURegisterRead(void) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukMCURegisterRead, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                            ukMCURegisterWrite                            */
/* ======================================================================== */
TukSTATUS ukMCURegisterWrite(void) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukMCURegisterWrite, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL PRIVILEGED SERVICES - DMA STREAM                  */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_MCU_DMA)

/* ======================================================================== */
/*                        ukDMAStreamGetIDFromLabel                         */
/* ======================================================================== */
TukSTATUS ukDMAStreamGetIDFromLabel(
                TukDMAS_LABEL     dmas_label__i  CAukVAR_UNUSED_MAYBE,
                TukDMAS_ID       *dmas_id__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamGetIDFromLabel, status_code);
    *dmas_id__o = *((TukDMAS_ID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                             ukDMAStreamGetInfo                           */
/* ======================================================================== */
TukSTATUS ukDMAStreamGetInfo(
                TukDMAS_IID       dmas_iid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamGetInfo, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                             ukDMAStreamAssign                            */
/* ======================================================================== */
TukSTATUS ukDMAStreamAssign(
                TukDMAS_ID        dmas_id__i CAukVAR_UNUSED_MAYBE,
                TukDMAS_IID      *dmas_iid__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamAssign, status_code);
    *dmas_iid__o = *((TukDMAS_IID *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                            ukDMAStreamUnassign                           */
/* ======================================================================== */
TukSTATUS ukDMAStreamUnassign(
                TukDMAS_IID       dmas_iid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamUnassign, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                        ukDMAStreamTransferStart                          */
/* ======================================================================== */
TukSTATUS ukDMAStreamTransferStart(
                TukDMAS_IID             dmas_iid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamTransferStart, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                         ukDMAStreamTransferStop                          */
/* ======================================================================== */
TukSTATUS ukDMAStreamTransferStop(
                TukDMAS_IID       dmas_iid__i CAukVAR_UNUSED_MAYBE,
                TukLENGTH32      *dmas_transfer_count_current32__o CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamTransferStop, status_code);
    *dmas_transfer_count_current32__o = *((TukCOUNT32 *)(&GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                       ukDMAStreamTransferGetInfo                         */
/* ======================================================================== */
TukSTATUS ukDMAStreamTransferGetInfo(
                TukDMAS_IID       dmas_iid__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamTransferGetInfo, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                       ukDMAStreamTransferGetState                        */
/* ======================================================================== */
TukSTATUS ukDMAStreamTransferGetState(
                TukDMAS_IID       dmas_iid__i CAukVAR_UNUSED_MAYBE,
                TukDMAS_STATE    *dmas_state__o,
                TukLENGTH32      *dmas_count_current32__o,
                TukLENGTH32      *dmas_count_total32__o) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukDMAStreamTransferGetState, status_code);
    *dmas_state__o = *((TukDMAS_STATE *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    *dmas_count_current32__o = *((TukCOUNT32 *)(&GVukappBlockDataSharedUKSVC.ServiceParameter.Output[4]));
    *dmas_count_total32__o = *((TukCOUNT32 *)(&GVukappBlockDataSharedUKSVC.ServiceParameter.Output[8]));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_MCU_DMA) */

/* //////////////////////////////////////////////////////////////////////// */
/*         UKERNEL PRIVILEGED SERVICES - DATA PERSISTENT MANAGEMENT         */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK)

/* ======================================================================== */
/*                       ukPersistentDataBlockEraseSector                   */
/* ======================================================================== */
TukSTATUS ukPersistentDataBlockEraseSector(
    TukACCESSKEY32  ukappdpb_accesskey32__i     CAukVAR_UNUSED_MAYBE,
    TukOFFSET32     ukappdpb_sector_offset32__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPersistentDataBlockEraseSector, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                          ukPersistentDataBlockRead                       */
/* ======================================================================== */
TukSTATUS ukPersistentDataBlockRead(
    TukACCESSKEY32  ukappdpb_accesskey32__i     CAukVAR_UNUSED_MAYBE,
    TukOFFSET32     ukappdpb_offset32__i        CAukVAR_UNUSED_MAYBE,
    TukCOUNT16      ukappdpb_access_length16__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPersistentDataBlockRead, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                          ukPersistentDataBlockWrite                      */
/* ======================================================================== */
TukSTATUS ukPersistentDataBlockWrite(
    TukACCESSKEY32  ukappdpb_accesskey32__i     CAukVAR_UNUSED_MAYBE,
    TukOFFSET32     ukappdpb_offset32__i        CAukVAR_UNUSED_MAYBE,
    TukCOUNT16      ukappdpb_access_length16__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukPersistentDataBlockWrite, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}
#endif /* defined(SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK) */


/* //////////////////////////////////////////////////////////////////////// */
/*           UKERNEL PRIVILEGED SERVICES - UKERNEL IMAGE UPDATE             */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE)

/* ======================================================================== */
/*                          ukUKImageUpdateEraseSector                      */
/* ======================================================================== */
TukSTATUS ukUKImageUpdateEraseSector(
    TukACCESSKEY32              ukimgupd_accesskey32__i     CAukVAR_UNUSED_MAYBE,
    TukOFFSET32                 ukimgupd_sector_offset32__i CAukVAR_UNUSED_MAYBE,
    TukLENGTH32                *ukimgupd_sector_length32__o CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKImageUpdateEraseSector, status_code);
    *ukimgupd_sector_length32__o = *((TukLENGTH32 *)(GVukappBlockDataSharedUKSVC.ServiceParameter.Output));
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                             ukUKImageUpdateWrite                         */
/* ======================================================================== */
TukSTATUS ukUKImageUpdateWrite(
    TukACCESSKEY32      ukimgupd_accesskey32__i         CAukVAR_UNUSED_MAYBE,
    TukOFFSET32         ukimgupd_storage_offset32__i    CAukVAR_UNUSED_MAYBE,
    TukCOUNT16          ukimgupd_access_length16__i     CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKImageUpdateWrite, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

/* ======================================================================== */
/*                              ukUKImageUpdateRead                         */
/* ======================================================================== */
TukSTATUS ukUKImageUpdateRead(
    TukACCESSKEY32      ukimgupd_accesskey32__i         CAukVAR_UNUSED_MAYBE,
    TukOFFSET32         ukimgupd_storage_offset32__i    CAukVAR_UNUSED_MAYBE,
    TukCOUNT16          ukimgupd_access_length16__i     CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKImageUpdateRead, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}


/* ======================================================================== */
/*                              ukUKImageUpdateOperate                      */
/* ======================================================================== */
TukSTATUS ukUKImageUpdateOperate(
    TukACCESSKEY32                      ukimgupd_accesskey32__i         CAukVAR_UNUSED_MAYBE,
    TukUKERNEL_IMAGE_UPDATE_OPERATION   ukimgupd_operation__i           CAukVAR_UNUSED_MAYBE,
    TukUKERNEL_IMAGE_UPDATE_ATTRIBUTES  ukimgupd_attrib__i              CAukVAR_UNUSED_MAYBE,
    TukLENGTH32                         ukimgupd_storage_length32__i    CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukUKImageUpdateOperate, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE) */


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL PRIVILEGED SERVICES - RANDOM GENERATION              */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_RNG_UKPROC)

/* ======================================================================== */
/*                               ukRandomGetBytes                           */
/* ======================================================================== */
TukSTATUS ukRandomGetBytes(TukRNG_ID          rng_id__i CAukVAR_UNUSED_MAYBE,
                           TukCOUNT16         random_bytes_count16__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukRandomGetBytes, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}



/* ======================================================================== */
/*                               ukRandomSetSeed64                          */
/* ======================================================================== */
TukSTATUS ukRandomSetSeed64(TukRNG_ID           rng_id__i CAukVAR_UNUSED_MAYBE,
                            TukUINT64           random_seed64__i CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_ID8_ukRandomSetSeed64, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_RNG_UKPROC) */


/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL API - PRIVILEGED - DEBUG - DEBUG TRACE             */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC)

/* ======================================================================== */
/*                             ukDebugTracePrint                            */
/* ======================================================================== */
TukSTATUS ukDebugTracePrint(TukDEBUG_TRACE_ATTRIBUTES   trace_attrib__i CAukVAR_UNUSED_MAYBE,
                            TukNTCSTRING_ADDRESS        trace_str_ptr__i CAukVAR_UNUSED_MAYBE)
{
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_DEBUG_ID8_ukDebugTracePrint, status_code);
    return(status_code);
}


/* ======================================================================== */
/*                         uk_DebugTracePrintfVAList                        */
/* ======================================================================== */
/**
 * @brief Static private C-Function for printing the processed Format NTString
 *  (similar format as printf() C11) on ukProc Debug Trace without variable
 *  list of arguments.
 *
 * This static private C-Function prints on ukProc Debug Trace the string built
 *  by processing the given Format NTString <dbgtrace_format_ntstr_addr__i>
 *  (similar format as printf() C11 standard) without variable list of
 *  arguments.
 * The reference to the variable list of arguments required is given in
 *  <trace_format_va_list__i> as the address of the 'va_list' used by the
 *  C-compiler.
 *
 * @usage This C-Function shall be used only by uKernel Privileged Service
 *  ukDebugTracePrintf(). It SHALL NOT BE USED by ukApp code.
 */
static CAukFUNC_INLINE_NEVER TukSTATUS uk_DebugTracePrintfVAList(
        TukDEBUG_TRACE_ATTRIBUTES trace_attrib__i          CAukVAR_UNUSED_MAYBE,
        TukNTCSTRING_ADDRESS      trace_format_str_ptr__i  CAukVAR_UNUSED_MAYBE,
        va_list                  *trace_format_va_list__i  CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_DEBUG_ID8_ukDebugTracePrintf, status_code);
    return(status_code);
}


/* ======================================================================== */
/*                             ukDebugTracePrintf                           */
/* ======================================================================== */
TukSTATUS ukDebugTracePrintf(
        TukDEBUG_TRACE_ATTRIBUTES trace_attrib__i          CAukVAR_UNUSED_MAYBE,
        TukNTCSTRING_ADDRESS      trace_format_str_ptr__i  CAukVAR_UNUSED_MAYBE,
        ...)
{
va_list trace_format_va_list__i;
TukSTATUS status_code;

    va_start(trace_format_va_list__i, trace_format_str_ptr__i);
    status_code = uk_DebugTracePrintfVAList(
            trace_attrib__i,
            trace_format_str_ptr__i,
            &trace_format_va_list__i);
    va_end(trace_format_va_list__i);
    return(status_code);
}


/* ======================================================================== */
/*                           ukDebugTracePrintBuffer                        */
/* ======================================================================== */
TukSTATUS ukDebugTracePrintBuffer(
        TukDEBUG_TRACE_ATTRIBUTES trace_attrib__i           CAukVAR_UNUSED_MAYBE,
        TukADDRESS32              buffer_address32_start__i CAukVAR_UNUSED_MAYBE,
        TukLENGTH16               buffer_length16__i        CAukVAR_UNUSED_MAYBE)
{
TukSTATUS status_code;
    ukSVC_RETURN_STATUSCODE(DukSVC_DEBUG_ID8_ukDebugTracePrintBuffer, status_code);
    return(status_code);
}

#endif /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL API - PRIVILEGED - DEBUG - DEBUG LED              */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(SukCONFIG_FEATURE_DEBUG_LED)
/* ======================================================================== */
/*                             ukDebugLEDSetPattern                         */
/* ======================================================================== */
TukSTATUS ukDebugLEDSetPattern(
    TukDEBUG_LED_IDX     led_idx__i                                     CAukVAR_UNUSED_MAYBE,
    TukDEBUG_LED_PATTERN led_pattern__i                                 CAukVAR_UNUSED_MAYBE,
    TukCOUNT8            transient_duration_blinking_period_count8__i   CAukVAR_UNUSED_MAYBE) {
TukSTATUS status_code;

    ukSVC_RETURN_STATUSCODE(DukSVC_DEBUG_ID8_ukDebugLEDSetPattern, status_code);
    ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code, __FUNCTION__);
    return(status_code);
}
#endif /* defined(SukCONFIG_FEATURE_DEBUG_LED) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_INMODULE
#undef UK_HW_MCU_CORE_ARM_CMX_C

#endif /* defined(SukCONFIG_HW_MCU_CORE_ARM_CMX) */
#endif /* !defined(UKCORE) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

