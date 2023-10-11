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
 * @file          uk_macros.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  C-Preprocessor Macros sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the declarations and definitions of the
 *  C-Preprocessors C-Macros made available to ease ukApp development, and
 *  provide basis for developing high quality and robust software.
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
#if !defined(UK_MACROS_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_macros.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_MACROS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_MACROS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                     UKERNEL API - C-MACROS DEFINITIONS                   */
/* ######################################################################## */
/* Hereafter are defined the C-Macros of the uKernel API provided as helper
 *  for being used in ukApp source code.
 *
 * @usage When convenient, the usage of these C-Macros is strongly
 *  recommended in ukApp source code in order to ease maintenance and
 *  portability upon new uKernel Target.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - VALUES GENERIC                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for swapping the values of two parameters.
 *
 * This C-Macro swaps the value of its two input parameters. After its
 *  execution:
 *  - Output value of 1st parameter = Input Value in 2nd parameter.
 *  - Output value of 2nd parameter = Input Value in 1st parameter.
 *
 * @param[in] x__io First input parameter.
 * @param[in] y__io Second input parameter.
 * @param[out] x__io Equal to the input parameter value in <y__io>.
 * @param[out] y__io Equal to the input parameter value in <x__io>.
 *
 */
#define MukVAL_SWAP(x__io, y__io)                                             \
          ({                                                                  \
            typeof(x__io) _x = (x__io);                                       \
            typeof(y__io) _y = (y__io);                                       \
            x__io = _y;                                                       \
            y__io = _x;                                                       \
          })

/**
 * @brief C-Macro computing the absolute numerical value from input parameter.
 *
 * This C-Macro computes the absolute numerical value of the given input
 *  parameter.
 *
 * @param[in] numval__i Input parameter from which absolute numerical value has
 *  to be computed.
 * @return (typeof(numval__i))Absolute numerical value of given parameter
 *  <numval__i>.
 */
#define MukVAL_ABS(numval__i) ({                                              \
            typeof(numval__i) _x = (numval__i);                               \
            (((_x) < 0) ? -(_x) : (_x));                                      \
          })

/**
 * @brief C-Macro returning the maximum numerical value from both input
 *  parameters.
 *
 * This C-Macro returns the maximum numerical value from both given input
 *  parameters.
 *
 * @param[in] numval1__i First input parameter.
 * @param[in] numval2__i Second input parameter.
 * @return Value <numval1__i> if <numval1__i> is greater than <numval2__i>, or
 *  value <numval2__i> else.
 */
#define MukVAL_MAX(numval1__i, numval2__i)  ({                                \
            typeof(numval1__i) _a = (numval1__i);                             \
            typeof(numval2__i) _b = (numval2__i);                             \
            (((_a) < (_b)) ?  (_b) : (_a));                                   \
          })

/**
 * @brief C-Macro returning the minimum numerical value from both input
 *  parameters.
 *
 * This C-Macro returns the minimum numerical value from both given input
 *  parameters.
 *
 * @param[in] numval1__i First input parameter.
 * @param[in] numval2__i Second input parameter.
 * @return Value <numval1__i> if <numval1__i> is lower than <numval2__i>, or
 *  value <numval2__i> else.
 */
#define MukVAL_MIN(numval1__i, numval2__i)  ({                                \
            typeof(numval1__i) _a = (numval1__i);                             \
            typeof(numval2__i) _b = (numval2__i);                             \
            (((_a) < (_b)) ?  (_a) : (_b));                                   \
          })


/* //////////////////////////////////////////////////////////////////////// */
/*                     C-MACROS - VALUES BIT MANIPULATION                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for testing if given value has exactly one bit set.
 *
 * This C-Macro tests if the given value has exactly one bit set.
 *
 * @param[in] value__i Value to be tested
 *
 * @return (TukBOOL)Boolean value indicating the result of test.
 * @retval DukBOOL_TRUE Exactly one bit is set in given value.
 * @retval DukBOOL_FALSE None or more than one bit is set in given value.
 */
#define MukVAL_BIT_IS_EXACTLY_ONE_SET(value__i)                               \
          (                                                                   \
            (((value__i) != 0U) && (((value__i) & ((value__i)-1U)) == 0U))    \
            ? DukBOOL_TRUE : DukBOOL_FALSE                                    \
          )

/**
 * @brief C-Macro for testing if given value has at most one bit set.
 *
 * This C-Macro tests if the given value has at most one bit set.
 *
 * @param[in] value__i Value to be tested
 *
 * @return (TukBOOL) Boolean value indicating the result of test.
 * @retval DukBOOL_TRUE At most one bit is set in given value.
 * @retval DukBOOL_FALSE More than one bit is set in given value.
 */
#define MukVAL_BIT_IS_AT_MOST_ONE_SET(value__i)                               \
          (                                                                   \
            (((value__i) & ((value__i)-1)) == 0)                              \
            ? DukBOOL_TRUE : DukBOOL_FALSE                                    \
          )


/* //////////////////////////////////////////////////////////////////////// */
/*                 C-MACROS - VALUES BIT FIELD MANIPULATION                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for computing the bitmask for the field in a 32-bit value.
 *
 * This C-Macro computes the bitmask for the field in a 32-bit value.
 * The bitmask of the field is defined as an unsigned value with all its
 *  bits set between the LSb (Less Significant bit) and MSb (Most Significant
 *  bit) defining the field.
 *
 * @usage The returned value has no attributed C-Type (it shall be casted when
 *  invoking this C-Macro).
 *
 * @param[in] lsb__i LSb (Less Significant bit) of the field inside the 32-bit
 *  value. It shall be in the range [0 ... 31].
 * @param[in] msb__i MSb (Most Significant bit) of the field inside the 32-bit
 *  value. It shall be in the range [0 ... 31].
 *
 * @return Bitmask of the field.
 */
#define MukVAL_FIELD_BITMASK32(lsb__i, msb__i)                                \
          (                                                                   \
            ( (1UL << (1UL + (msb__i) - (lsb__i)) ) - 1UL) << (lsb__i)        \
          )


/**
 * @brief C-Macro for computing the bitmask for the field in a 64-bit value.
 *
 * This C-Macro computes the bitmask for the field in a 64-bit value.
 * The bitmask of the field is defined as an unsigned value with all its
 *  bits set between the LSb (Less Significant bit) and MSb (Most Significant
 *  bit) defining the field.
 *
 * @usage The returned value has no attributed C-Type (it shall be casted when
 *  invoking this C-Macro).
 *
 * @param[in] lsb__i LSb (Less Significant bit) of the field inside the 64-bit
 *  value. It shall be in the range [0 ... 63].
 * @param[in] msb__i MSb (Most Significant bit) of the field inside the 64-bit
 *  value. It shall be in the range [0 ... 63].
 *
 * @return Bitmask of the field.
 */
#define MukVAL_FIELD_BITMASK64(lsb__i, msb__i)                                \
          (                                                                   \
            ( (1ULL << (1UL + (msb__i) - (lsb__i)) ) - 1UL) << (lsb__i)       \
          )


/**
 * @brief C-Macro for retrieving a field from a given value.
 *
 * This C-Macro retrieves the field from a given value structured with several
 *  fields.
 * The retrieved field value is right shifted in order to have its LSb on the
 *  bit 0 (rightmost).
 *
 * @usage The returned value has no attributed C-Type (it shall be casted when
 *  invoking this C-Macro).
 *
 * @param[in] lsb__i LSb (Less Significant bit) of the field inside the value.
 * @param[in] msb__i MSb (Most Significant bit) of the field inside the value.
 * @param[in] value_struct__i Value containing the sub-field to retrieve.
 *
 * @return Retrieved field value right shifted (its LSb is bit 0, i.e. the
 *  rightmost, of returned value).
 */
#define MukVAL_FIELD_VALUE_GET(lsb__i, msb__i, value_struct__i)               \
          (                                                                   \
            ((value_struct__i) & MukVAL_FIELD_BITMASK32(lsb__i, msb__i))      \
            >> (lsb__i)                                                       \
          )

/**
 * @brief C-Macro for retrieving a field from a given value.
 *
 * This is a 64-bit version of MukVAL_FIELD_VALUE_GET.
 */
#define MukVAL_FIELD_64_VALUE_GET(lsb__i, msb__i, value_struct__i)            \
          (                                                                   \
            ((value_struct__i) & MukVAL_FIELD_BITMASK64(lsb__i, msb__i))      \
            >> (lsb__i)                                                       \
          )


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-MACROS - PADDING GENERATION                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro as helper for generating a 32-bit Padding value.
 *
 * This C-Macro is an helper for generating a 32-bit Padding value when
 *  compiling code for different uKernel Targets.
 * The generated Padding value is using the given Padding Seed <padding_seed__i>
 *  to increase the variability.
 *
 * @implementation As variability base, the generation of the Padding is using
 *  the following Target definition values (see include file "uk_release.h"):
 *   - DukRELEASE_UKERNEL_VERSION
 *   - DukRELEASE_CUSTOMER_CONFIG
 *
 * @usage The given Padding Seed <padding_seed__i> should be base on a
 *  C-Constant specific to the structure into which the padding is used.
 *  Optionally, variability may be added by mixing it with compilation
 *  information (e.g. Date and Time of the compilation).
 *
 * @param[in] (TukUINT32)padding_seed__i Seed to use for providing the Padding
 *  Variability.
 *
 * @return (TukUINT32) 32-bit generated Padding value.
 */
#define MukPADDING_GENERATE32(padding_seed__i)                                \
    ((TukUINT32)                                                              \
     (                                                                        \
      ((padding_seed__i)       *                                              \
        (DukRELEASE_UKERNEL_VERSION)) +                                       \
      (((padding_seed__i) + 1UL) *                                            \
        (DukRELEASE_CUSTOMER_CONFIG & 0xFFFFFFFFULL)) +                       \
      (((padding_seed__i) - 1UL) *                                            \
        (DukRELEASE_CUSTOMER_CONFIG >> 32U))                                  \
     )                                                                        \
    )


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
#define MukBITVECTOR_ELEMENT_COUNT(bits_count__i)                             \
         ( ((bits_count__i) + (sizeof(TukBITVECTOR_ELEMENT) * 8U) - 1UL) /    \
           (sizeof(TukBITVECTOR_ELEMENT) * 8U) )                              \

/**
 * @brief C-Macro as helper for the definition of a C-Type containing a Bit
 *  Vector.
 *
 * This C-Macro is an helper for the definition of a C-Type containing a Bit
 *  Vector:
 *  - The C-Type defined will be named with the input parameter
 *   <ctype_bitvector_name__i>.
 *  - The C-Type is defined as an array of Bit Vector Elements (see
 *   TukBITVECTOR_ELEMENT). The number of Bit Vector Elements is computed
 *   using the MukBITVECTOR_ELEMENT_COUNT() C-Macro from the given number of
 *   bits <bits_count__i>.
 *
 * @note See TukBITVECTOR_ELEMENT for more details on a Bit Vector.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] ctype_bitvector_name__i Name of the C-Type containing the Bit
 *  Vector.
 * @param[in] bits_count__i Number of bits to be stored in the Bit Vector. It
 *  shall be a constant expression, that can be fully evaluated when this
 *  C-Macro is processed by the C-Compiler.
 */
#define MukBITVECTOR_CTYPE_DEFINE(ctype_bitvector_name__i, bits_count__i)     \
         typedef TukBITVECTOR_ELEMENT ctype_bitvector_name__i[                \
           MukBITVECTOR_ELEMENT_COUNT(bits_count__i)                          \
                                                             ];



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - C-ARRAY GENERIC                      */
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
#define MukARRAY_ELEMENTS_COUNT(array__i)                                     \
          ( sizeof(array__i) /                                                \
            sizeof(array__i[0])                                               \
          )


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - STATUS CODE                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro as helper for building a Status Code value.
 *
 * This C-Macro is an helper for building a Status Code value from the fields
 *  composing its C-Type (see TukSTATUS) internal structure.
 *
 * @implementation The Status Code value is built as per the structure defined
 *  in the uKernel C-Type TukSTATUS. No check is done on the validity of given
 *  fields for the building.
 *
 * @param[in] (TukSTATUS)status_nature_bitnum__i Bit number of the Nature of
 *  the Status Code in Nature field. It shall be in the range
 *  [ 0 ... (DukSTATUS_NATURE_COUNT - 1) ]
 * @param[in] (TukSTATUS)status_reason_field__i Reason of the (un)success.
 *  The Null(0) value is invalid.
 *
 * @return (TukSTATUS)Built Status Code value.
 */
#define MukSTATUS_BUILD(status_nature_bitnum__i, status_reason_field__i)      \
          ((TukSTATUS)                                                        \
           ( (1U <<                                                           \
              ((status_nature_bitnum__i) + DukSTATUS_NATURE_FIELD_LSb)) |     \
             ((status_reason_field__i) << DukSTATUS_REASON_FIELD_LSb) )       \
          )                                                                   \


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - ADDRESS BLOCK                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro as helper for building an Address Block Identifier value
 *  from its Address Block Descriptor entry index.
 *
 * This C-Macro is an helper for building an Address Block Identifier value
 *  (see C-Type TukADDRESSBLOCK_ID) from its Address Block Descriptor entry
 *  index.
 *
 * The index corresponds to the entry index of its Address Block Descriptor in
 *  the Address Block Descriptor List present in the ukApp Descriptor:
 *  - Extra Address Block: field <AddressBlockExtraDescriptorList>.
 *  - Shared Buffer:  <SharedBufferDescriptorList>.
 *
 * @implementation The Address Block Identifier value is built as per the
 *  structure defined in the uKernel C-Type TukADDRESSBLOCK_ID. No check is
 *  done on the validity of given fields for the building.
 *
 * @usage The given Nature <abid_nature__i> of the Address Block Identifier
 *  to build SHALL BE in the following list:
 *  - DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX
 *  - DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX
 *
 * @usage The built Address Block Identifier value can be used only locally
 *  in the Owner ukProc of the Address Block. If used in other ukProc, it will
 *  be interpreted in the local context of the other ukProc, and thus, if
 *  valid, will reference a different Address Block belonging to the other
 *  ukProc.
 *
 * @param[in] (TukADDRESSBLOCK_ID_NATURE) abid_nature__i Nature of the
 *  identifier of the Address Block.
 * @param[in] (TukIDX8) abid_ref__i Reference of the Address Block, which is
 *  the entry index of its Address Block Descriptor in the list defined in
 *  the ukApp Descriptor.
 *
 * @return (TukADDRESSBLOCK_ID)Built Address Block Identifier value.
 */
#define MukADDRESSBLOCK_ID_BUILD(abid_nature__i,                              \
                                 abid_desc_idx__i)                            \
    ((TukADDRESSBLOCK_ID)(                                                    \
            (DukADDRESSBLOCK_ID_TAG << DukADDRESSBLOCK_ID_TAG_LSb)          | \
            ((TukADDRESSBLOCK_ID)(abid_nature__i)                             \
                << DukADDRESSBLOCK_ID_NATURE_LSb)                           | \
            ((TukADDRESSBLOCK_ID)(abid_desc_idx__i)                           \
                << DukADDRESSBLOCK_ID_REFERENCE_LSb)                          \
                         )                                                    \
    )


/* //////////////////////////////////////////////////////////////////////// */
/*                            C-MACROS - DMA STREAM                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro as helper for building a DMA Stream Identifier value from
 *  its  DMA Stream Descriptor entry index.
 *
 * This C-Macro is an helper for building a DMA Stream Identifier value (see
 *  C-Type TukDMAS_ID) from its DMA Stream Descriptor entry index.
 *
 * The index corresponds to the entry index of its DMA Stream Descriptor in
 *  the DMA Stream Descriptor List present in the ukApp Descriptor (see field
 *  <DMAStreamDescriptorList> in TukUKAPP_DESCRIPTOR).
 *
 * @implementation The DMA Stream Identifier value is built as per the
 *  structure defined in the uKernel C-Type TukDMAS_ID. No check is
 *  done on the validity of given fields for the building.
 *
 * @usage The built DMA Stream Identifier value can be used only locally
 *  in the Owner ukProc of the DMA Stream. If used in other ukProc, it will
 *  be interpreted in the local context of the other ukProc, and thus, if
 *  valid, will reference a different DMA Stream belonging to the other
 *  ukProc.
 *
 * @param[in] (TukIDX8) dmas_desc_idx__i Reference of the DMA Stream, which
 *  is the entry index of its DMA Stream Descriptor in the list defined in
 *  the ukApp Descriptor.
 *
 * @return (TukDMAS_ID)Built DMA Stream Identifier value.
 */
#define MukDMAS_ID_BUILD(dmas_desc_idx__i)                                    \
    (                                                                         \
        ((TukDMAS_ID) (DukDMAS_ID_TAG)   << DukDMAS_ID_TAG_LSb)     |         \
        ((TukDMAS_ID) (dmas_desc_idx__i) << DukDMAS_ID_REFERENCE_LSb)         \
    )


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-MACROS - DEBUG TRACE                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro as helper for building a Debug Trace Attributes value.
 *
 * This C-Macro is an helper for building the Debug Trace Attributes value to
 *  be used for printing a Debug Trace.
 *
 * @implementation The Debug Trace Attributes value is built as per the
 *  structure defined in the uKernel C-Type TukDEBUG_TRACE_ATTRIBUTES. No check
 *  is done on the validity of given fields for the building.
 *
 * @usage When building a Debug Trace Attribute for printing a Debug Trace,
 *  one and only one flag in its <Nature> field shall be set.
 *
 * @param[in] (TukDEBUG_TRACE_NATURE) debug_trace_nature__i <Nature> field of
 *  the Debug Trace Attributes.
 * @param[in] (TukDEBUG_TRACE_MODE) debug_trace_mode__i <Mode> field of the
 *  Debug Trace Attributes.
 * @param[in] (TukDEBUG_TRACE_VERBOSITY) debug_trace_verbosity__i <Verbosity>
 *  field of the Debug Trace Attributes.
 *
 * @return (TukDEBUG_TRACE_ATTRIBUTES)Built Debug Trace Attributes value.
 */
#define MukDEBUG_TRACE_ATTRIBUTES_BUILD(debug_trace_nature__i,                \
                                        debug_trace_mode__i,                  \
                                        debug_trace_verbosity__i)             \
    ((TukDEBUG_TRACE_ATTRIBUTES)                                              \
     (                                                                        \
      (((TukDEBUG_TRACE_ATTRIBUTES)(debug_trace_verbosity__i)                 \
            << DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_LSb))              | \
      (((TukDEBUG_TRACE_ATTRIBUTES)(debug_trace_mode__i)                      \
            << DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_LSb))                   | \
      (((TukDEBUG_TRACE_ATTRIBUTES)(debug_trace_nature__i)                    \
            << DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_LSb))                   \
     )                                                                        \
    )



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_MACROS_H_INSIDE
#endif /* !defined(UK_MACROS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

