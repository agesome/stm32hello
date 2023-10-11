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
 * @file          ns_macros.h
 * @brief         NS_CLIENT API C-Macros Declarations file 
 * @author        provenrun
 * @maintainer    provenrun
 * @ingroup       NS_PSA_CLIENT_API
 ******************************************************************************
 * @details
 * 
 *******************************************************************************
 * @addtogroup    NS_PSA_CLIENT_API
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(NS_MACROS_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "ns.h" file.                       */
#if !defined(NS_H_INSIDE)
    #error 'The "ns_macros.h" include file shall be included only in the "ns.h" file'
#endif /* !defined(NS_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  NS_MACROS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  NS_MACROS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the NS_CLIENT. */

/* Add inclusion of NS_CLIENT Public API (only to help IDE parsing). */
#include "ns.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                     NS_CLIENT API - C-MACROS DEFINITIONS                   */
/* ######################################################################## */
/* Hereafter are defined the C-Macros of the NS_CLIENT API provided as helper
 *  for being used in nsApp source code.
 *
 * @usage When convenient, the usage of these C-Macros is strongly
 *  recommended in nsApp source code in order to ease maintenance and
 *  portability upon new NS_CLIENT Release.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                           C-MACROS - BIT VECTOR                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for computing the number of array elements needed for a
 *  Bit Vector from given size in bits.
 *
 * This C-Macro computes the number of elements needed in the array of a
 *  Bit Vector to be able to store at least the number of given bits
 *  <bits_count__i>.
 *
 * @param[in] bits_count__i Number of bits to be stored in the Bit Vector.
 *
 * @return Number of array elements needed in the Bit Vector.
 */
#define MnsBITVECTOR_ELEMENT_COUNT(bits_count__i)                             \
         ( ((bits_count__i) + (sizeof(TnsBITVECTOR_ELEMENT) * 8) - 1) /       \
           (sizeof(TnsBITVECTOR_ELEMENT) * 8) )                               \

/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - C-ARRAY GENERIC       +++               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for counting the number of elements in a C-Array.
 *
 * This C-Macro counts the number of elements in a C-Array.
 *
 * @usage The given C-Array shall be the array itself and not a pointer, else
 *  this C-Macro will not return proper result.
 *
 * @usage The returned value has no attributed C-Type (it shall be casted when
 *  invoking this C-Macro).
 *
 * @param[in] array__i C-Array for which we want to count the number of
 *  elements.
 *
 * @return Number of elements in the given C-Array.
 */
#define MnsARRAY_ELEMENTS_COUNT(array__i)                                     \
          ( sizeof(array__i) /                                                \
            sizeof(array__i[0])                                               \
          )

/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef NS_MACROS_H_INSIDE
#endif /* !defined(NS_MACROS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


