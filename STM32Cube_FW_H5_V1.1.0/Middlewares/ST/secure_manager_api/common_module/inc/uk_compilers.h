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
 * @file          uk_compilers.h
 * @brief         uKernel API - Main uKernel API Declarations file - C-Compiler
 *  sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the declarations and definitions relative to the
 *  C-Compiler used.
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
#if !defined(UK_COMPILERS_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_COMPILERS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_COMPILERS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/* ######################################################################## */
/*                COMPILER  - CHECKS AND SPECIFIC DECLARATIONS              */
/* ######################################################################## */
/* Hereafter are defined the uKernel API Macros helpers allowing abstraction
 *  of the compiler used.
 */

/* Enforce that we are using at least the C11 standard for compiling C.
 *
 * @robustness This check is critical as the implementation is relying on
 *  some rules of the C11 standard:
 *  - Unsigned integer: modulo wrapping is the defined behavior and the term
 *   overflow never applies. */
#if (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L))
    #error "**ERROR:COMPILER** The compiler needs to support C11 standard."
#endif /* (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L)) */


/* //////////////////////////////////////////////////////////////////////// */
/*                                COMPILER - GCC                            */
/* //////////////////////////////////////////////////////////////////////// */

/* Check if the compiler used is the GNU GCC compiler. */
#if (defined(__GNUC__) && !defined(__ARMCC__))

/* ======================================================================== */
/*                        COMPILER - GCC - DEFINITIONS                      */
/* ======================================================================== */
/**
 * @brief Definitions related to GNU ARM GCC usage.
 */
#define GCC_COMPILER 0x00474343

/**
 * @brief Definition of uKernel Compiler used: GNU ARM GCC.
 */
#define UK_COMPILER GCC_COMPILER

/**
 * @brief Definition related to uKernel Compiler version used.
 */
#define UK_COMPILER_VERSION                                                   \
            (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/**
 * @brief Definition for checking minimal required uKernel Compiler version.
 */
#define UK_COMPILER_VERSION_AT_LEAST(major__i, minor__i, patch__i)            \
            ( UK_COMPILER_VERSION >=                                          \
              ((major__i) * 10000 + (minor__i) * 100 + (patch__i)) )


/* ======================================================================== */
/*               COMPILER - GCC - COMPILER ATTRIBUTES - C-TYPE              */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Type.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Type in its
 *  definition.
 *
 * @usage This C-Compiler Attribute has to be placed just after the 'typedef '
 *  C-Compiler keyword.
 */
#define CAukTYPE_DEPRECATED   __attribute__((deprecated))


/* ======================================================================== */
/*            COMPILER - GCC - COMPILER ATTRIBUTES - C-VARIABLES            */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a specific C-Linker Section for
 *  a C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to place a C-Variable in the given C-Linker Section.
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its definition.
 *
 * @param [in] clinker_section_name_string__i Name (ASCII string between double
 *  quotes) of the C-Linker Section to be used.
 */
#define CAukVAR_SECTION(clinker_section_name_string__i)                       \
                __attribute__((section(clinker_section_name_string__i)))

/**
 * @brief C-Compiler Attribute for indicating a possibly unused C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a possibly
 *  unused C-Variable. When this C-Compiler Attribute is present, the
 *  C-Compiler will not generate warning/error if the C-Variable is not used
 *  in the effectively compiled source code associated unit.
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its definition.
 */
#define CAukVAR_UNUSED_MAYBE                    __attribute__((unused))

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Variable in
 *  its definition/declaration.
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its declaration.
 */
#define CAukVAR_DEPRECATED                      __attribute__((deprecated))

/**
 * @brief C-Compiler Attribute for indicating an address alignment condition
 *  for a C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Linker that the memory address of a C-Variable has to be aligned on
 *  (e.g. is a multiple of) the given alignment value (in bytes)
 *  <aligned_on_bytes__i> .
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its definition.
 *
 * @param [in] aligned_on_bytes__i Alignment (in bytes) to be used for the
 *  memory address of the C-Variable.
 */
#define CAukVAR_ALIGNED(aligned_on_bytes__i)                                  \
                __attribute__((aligned(aligned_on_bytes__i)))


/* ======================================================================== */
/*            COMPILER - GCC - COMPILER ATTRIBUTES - C-FUNCTIONS            */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a possibly unused C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a possibly
 *  unused C-Function. When this C-Compiler Attribute is present, the
 *  C-Compiler will not generate warning/error if the C-Function is not used
 *  in the effectively compiled source code associated unit.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_UNUSED_MAYBE   __attribute__((unused))

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Function in
 *  its definition/declaration.
 *
 * @usage This C-Compiler Attribute has to be placed at the end the C-Function
 *  declaration.
 */
#define CAukFUNC_DEPRECATED     __attribute__((deprecated))

/**
 * @brief C-Compiler Attribute for indicating a specific C-Linker Section for
 *  a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to place the C-Function in given C-Linker Section.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 *
 * @param [in] clinker_section_name_string__i Name (ASCII string between double
 *  quotes) of the C-Linker Section to be used.
 */
#define CAukFUNC_SECTION(clinker_section_name_string__i)                      \
                __attribute__ ((section(clinker_section_name_string__i)))

/**
 * @brief C-Compiler Attribute for indicating that the C-Function has to be
 *  kept in final generated binary code.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler and C-Linker to keep the given C-Function in final generated
 *  binary code, even if the C-Function is not referenced in compiled code
 *  when building the calling tree.
 *
 * @usage This C-Compiler Attribute shall be used for C-Function that may be
 *  invoked from calling table or from external code as interface entry point,
 *  in order to ensure that it will not be removed by C-Linker optimizations
 *  from final generated binary code.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_NEEDED_ALWAYS  __attribute__((used))

/**
 * @brief C-Compiler Attribute for indicating to always inline a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to always inline given C-Function.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration after the 'inline' C-Keyword.
 */
#define CAukFUNC_INLINE_ALWAYS   __attribute__((always_inline))

/**
 * @brief C-Compiler Attribute for indicating to never inline a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to never inline given C-Function.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_INLINE_NEVER    __attribute__((noinline))

/**
 * @brief C-Compiler Attribute for indicating that a C-Function never returns.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler that given C-Function never returns.
 *
 * @usage This C-Compiler Attribute should be used for C-Function that never
 *  return (fatal error management, ...) in order to help C-Compiler performing
 *  optimal generated code optimizations.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_RETURN_NEVER    __attribute__((noreturn))

/**
 * @brief C-Compiler Attribute for indicating that returned value from a
 *  C-Function has to be checked.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to verify that the returned value from given C-Function is
 *  checked in the caller code.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_RETURN_VALUE_CHECK    __attribute__((warn_unused_result))


/**
 * @brief C-Compiler Attribute for indicating that a C-Function is pure.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler that given C-Function is pure.
 *
 * @warning This C-Compiler Attribute SHALL BE USED ONLY for C-Function that
 *  do not modify the state of the program that is observable by means other
 *  than inspecting the C-Function's return value. The C-Function can however
 *  safely read any non-volatile objects, and modify the value of objects in
 *  a way that does not affect their return value or the observable state of
 *  the program.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_PURE   __attribute__((pure))


/**
 * @brief C-Compiler Attribute for indicating to C-Compiler not to generate
 *  prologue and epilogue sequences in a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler not to generate prologue and epilogue sequences for the
 *  C-Function (in charge of managing parameters, register saving, ...).
 *
 * @usage This C-Compiler Attribute is useful for C-Function that have assembly
 *  language code, or that are called under specific circumstances (MCU
 *  exception, ...).
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_ASM_NAKED       __attribute__((naked))


/* ======================================================================== */
/*            COMPILER - GCC - C-MACROS - HELPERS FOR C-VARIABLES           */
/* ======================================================================== */
/* As good coding practice, and to enforce high quality and robust software,
 *  the purpose of the C-Macros defined hereafter is:
 *  - To make sure that each definition is done with a dedicated C-Type
 *   (strong typing policy used) and clearly specified initialization
 *   and placement conditions.
 *  - When need be, to ease the usage of specific C-Compiler Attributes to
 *   be applied globally.
 */

/**
 * @brief C-Macro for defining a C-Variable to be placed in a specific C-Linker
 *  section.
 *
 * Definition of the uKernel C-Macro as helper for defining a C-Variable with
 *  the given name <label__i>, of the given C-Type <ctype__i>, with an initial
 *  null value, and that has to be placed in the given C-Linker Section
 *  <clinker_section_name_string__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] clinker_section_name_string__i Name (ASCII string between double quotes)
 *  of the C-Linker Section into which the C-Variable has to be placed.
 */
#define MukVAR_DEFINE_SECTION(label__i, ctype__i, clinker_section_name_string__i)      \
            ctype__i __attribute__((section(clinker_section_name_string__i))) label__i

/**
 * @brief C-Macro for defining a C-Variable to be placed in a specific
 *  C-Linker Section, with an initial value.
 *
 * Definition of the uKernel C-Macro for defining a C-Variable with the given
 *  name <label__i>, of the given C-Type <ctype__i>, with the given initial
 *  value <value__i>, and that has to be placed in the given C-Linker Section
 *  <clinker_section_name_string__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] value__i Initial value of the defined C-Variable.
 * @param[in] clinker_section_name_string__i Name (ASCII string between double quotes)
 *  of the C-Linker Section into which the C-Variable has to be placed.
 */
#define MukVAR_DEFINE_INIT_SECTION(label__i, ctype__i, clinker_section_name_string__i, value__i) \
            ctype__i __attribute__((section(clinker_section_name_string__i))) label__i = (value__i);



/* ======================================================================== */
/*      COMPILER - GCC - C-MACROS - HELPERS FOR CONSTANTS C-VARIABLES       */
/* ======================================================================== */
/* As good coding practice, and to enforce high quality and robust software,
 *  the purpose of the C-Macros defined hereafter is:
 *  - To make sure that each definition is done with a dedicated C-Type
 *   (strong typing policy used) and clearly specified initialization
 *   and placement conditions.
 *  - When need be, to ease the usage of specific C-Compiler Attributes to
 *   be applied globally.
 */

/**
 * @brief C-Macro for declaring a constant typed C-Variable.
 *
 * Definition of the uKernel C-Macro for declaring a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') with the given name
 *  <label__i>, and of the given C-Type <ctype__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 */
#define MukCONST_DECLARE(label__i, ctype__i)                                  \
            static ctype__i const label__i;


/**
 * @brief C-Macro for defining a constant typed C-Variable.
 *
 * Definition of the uKernel C-Macro for defining a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') with the given name
 *  <label__i>, of the given C-Type <ctype__i>, and with the initial given
 *  value <value__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] value__i Value to affect to the constant C-Variable.
 */
#define MukCONST_DEFINE(label__i, ctype__i, value__i)                         \
            static ctype__i const label__i = value__i;

/**
 * @brief C-Macro for defining a constant typed C-Variable with one flag set.
 *
 * Definition of the uKernel C-Macro for defining a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') containing one flag set
 *  (i.e. only one bit is set in its value) with the given name <label__i>
 *  and of the given C-Type <ctype__i>.
 * The bit number of the flag is given in the parameter <bit_number__i> (the
 *  bit number 0 is the rightmost bit).
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] bit_number__i Bit number of the flag to be set to 1 in the
 *  value affected to the constant C-Variable (all other bits of the value are
 *  reset to 0).
 */
#define MukCONST_DEFINE_BF(label__i, ctype__i, bit_number__i)                 \
            static const ctype__i label__i = (1UL<<(bit_number__i));


/**
 * @brief C-Macro as helper for declaring a constant typed C-Structure.
 *
 * Definition of the uKernel C-Macro as helper for the declaration of a
 *  constant typed C-Structure.
 *
 * @usage This C-Macro is the associate of the MukCONST_STRUCT_DEFINE.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  declaration.
 *
 * @param[in] label__i Label to use for naming the declared constant
 *  C-Structure.
 * @param[in] ctype__i C-Type to use for the C-Structure.
 */
#define MukCONST_STRUCT_DECLARE(label__i, ctype__i)                           \
            extern ctype__i const label__i;

/**
 * @brief C-Macro as helper for defining a constant typed C-Structure.
 *
 * Definition of the uKernel C-Macro as helper for defining a constant typed
 *  C-Structure with the given name <label__i>, and of the given C-Type
 *  <ctype__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and SHALL BE followed by:
 *   - An equal sign ('=').
 *   - The contents of the constant C-Structure.
 *   - A semicolon (';') to mark the end of the definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Structure.
 * @param[in] ctype__i C-Type to use for the C-Structure.
 */
#define MukCONST_STRUCT_DEFINE(label__i, ctype__i)                            \
            ctype__i const label__i



/**
 * @brief C-Macro as helper for defining a constant typed C-Structure to be
 *  placed in a specific C-Linker section.
 *
 * Definition of the uKernel C-Macro as helper for defining a constant typed
 *  C-Structure with the given name <label__i>, and of the given C-Type
 *  <ctype__i>, and that has to be placed in the given C-Linker Section
 *  <clinker_section_name_string__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and SHALL BE followed by:
 *   - An equal sign ('=').
 *   - The contents of the constant C-Structure.
 *   - A semicolon (';') to mark the end of the definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Structure.
 * @param[in] ctype__i C-Type to use for the constant C-Structure.
 * @param[in] clinker_section_name_string__i Name (ASCII string between double
 *  quotes) of the C-Linker Section into which the constant C-Structure has to
 *  be placed.
 */
#define MukCONST_STRUCT_DEFINE_SECTION(label__i, ctype__i, clinker_section_name_string__i)      \
            ctype__i const __attribute__((section(clinker_section_name_string__i))) label__i


/**
 * @brief C-Macro as helper for declaring a constant typed C-Array.
 *
 * Definition of the uKernel C-Macro as helper for declaring a constant typed
 *  C-Array with the given name <label__i>, of the given C-Type <ctype__i>, and
 *  with the given <carray_size__i> number of elements.
 *
 * @note This C-Macro is the associate of the MukCONST_ARRAY_DEFINE.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  declaration.
 *
 * @param[in] label__i Label to use for naming the declared C-Array.
 * @param[in] ctype__i C-Type to use for casting each C-Array element.
 * @param[in] carray_size__i Size of the C-Array (number of elements).
 */
#define MukCONST_ARRAY_DECLARE(label__i, ctype__i, carray_size__i)            \
            extern ctype__i const label__i[carray_size__i];


/**
 * @brief C-Macro as helper for defining a constant typed C-Array.
 *
 * Definition of the uKernel C-Macro as helper for defining a constant typed
 *  C-Array with the given name <label__i>, the given C-Type <ctype__i>, and
 *  with the given <carray_size__i> number of elements.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and SHALL BE followed by:
 *   - An equal sign ('=').
 *   - The contents of the constant C-Array.
 *   - A semicolon (';') to mark the end of the definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Array.
 * @param[in] ctype__i C-Type to use for casting each C-Array element.
 * @param[in] carray_size__i Size of the C-Array (number of elements).
 */
#define MukCONST_ARRAY_DEFINE(label__i, ctype__i, carray_size__i)             \
            ctype__i const label__i[carray_size__i]



/* ======================================================================== */
/*              COMPILER - GCC - C-MACROS - HELPERS FOR VALUES              */
/* ======================================================================== */

/**
 * @brief C-Macro for associating a C-Type to a value.
 *
 * Definition of the uKernel C-Macro for associating a C-Type (the term
 *  'value cast' is also often used) given in parameter <ctype__i> to a value
 *  in given parameter <value__i>.
 *
 * @usage The purpose of this C-Macro is to encourage good coding practices by
 *  enforcing that all the values definitions (and notably the numeric
 *  literals) have an explicit C-Type.
 *
 * @param[in] ctype__i C-Type to use to cast the resulting value.
 * @param[in] value__i Value to be casted with given C-Type.
 */
#define MukVAL_TYPED(ctype__i, value__i)                                      \
            ((ctype__i)(value__i))

/**
 * @brief C-Macro for associating a C-Type to a value containing a Flag.
 *
 * Definition of the uKernel C-Macro for associating a C-Type (the term
 *  'value cast' is also often used) given in parameter <ctype__i> to a value
 *  containing a Flag (e.g. one and only one bit set in the value). The bit
 *  number of the flag is given in the parameter <bit_number__i> (the bit
 *  number 0 is the rightmost bit).
 *
 * @usage The purpose of this C-Macro is to encourage good coding practices by
 *  enforcing that all the flag definitions have an explicit C-Type.
 *
 * @param[in] ctype__i C-Type to use to cast the resulting value.
 * @param[in] bit_number__i Bit number of the flag to be set to 1 in the
 *  value to be casted (all other bits of the value are reset to 0).
 */
#define MukVAL_TYPED_BF(ctype__i, bit_number__i)                              \
            ((ctype__i)(1UL<<(bit_number__i)))

/**
 * @brief C-Macro for performing an addition on two values, while checking
 *  if an overflow occurs.
 *
 * This C-Macro performs an addition of two values while checking if an
 *  overflow occurs.
 *
 * The two values and the C-Variable containing the result shall be of the
 *  same C-Type (or of C-Type compatible for the C-Compiler).
 * The result of the operation is returned in the C-Variable referenced by
 *  the given C-Pointer <result_addr__o>.
 *
 * The C-Macro returns a boolean (C-Type TukBOOL):
 *  - DukBOOL_TRUE: An overflows has occurred.
 *  - DukBOOL_FALSE: No overflow has occurred.
 *
 * @param[in] a__i First input parameter.
 * @param[in] b__i Second input parameter.
 * @param[out] result_addr__o Address of the C-Variable containing the result
 *  of <a__i> added with <b__i>.
 *
 * @return (TukBOOL) Boolean value indicating if an overflow has occurred.
 * @retval DukBOOL_TRUE: An overflows has occurred.
 * @retval DukBOOL_FALSE: No overflow has occurred.
 */
#define MukVAL_ADD_CHECK_OVERFLOW(a__i, b__i, result_addr__o) ({              \
            typeof(a__i) __a__i = (a__i);                                     \
            typeof(b__i) __b__i = (b__i);                                     \
            typeof(result_addr__o) __result_addr__o = (result_addr__o);       \
            (void) (&__a__i == &__b__i);                                      \
            (void) (&__a__i == __result_addr__o);                             \
            __builtin_add_overflow(__a__i, __b__i, __result_addr__o);         \
            })

/**
 * @brief C-Macro for performing a subtraction on two values, while checking
 *  if an overflow occurs.
 *
 * This C-Macro performs a subtraction of two values while checking if an
 *  overflow occurs.
 *
 * The two values and the C-Variable containing the result shall be of the
 *  same C-Type (or of C-Type compatible for the C-Compiler).
 * The result of the operation is returned in the C-Variable referenced by
 *  the given C-Pointer <result_addr__o>.
 *
 * The C-Macro returns a boolean (C-Type TukBOOL):
 *  - DukBOOL_TRUE: An overflows has occurred.
 *  - DukBOOL_FALSE: No overflow has occurred.
 *
 * @param[in] a__i First input parameter.
 * @param[in] b__i Second input parameter.
 * @param[out] result_addr__o Address of the C-Variable containing the result
 *  of <a__i> minus <b__i>.
 *
 * @return (TukBOOL) Boolean value indicating if an overflow has occurred.
 * @retval DukBOOL_TRUE: An overflows has occurred.
 * @retval DukBOOL_FALSE: No overflow has occurred.
 */
#define MukVAL_SUB_CHECK_OVERFLOW(a__i, b__i, result_addr__o) ({              \
            typeof(a__i) __a__i = (a__i);                                     \
            typeof(b__i) __b__i = (b__i);                                     \
            typeof(result_addr__o) __result_addr__o = (result_addr__o);       \
            (void) (&__a__i == &__b__i);                                      \
            (void) (&__a__i == __result_addr__o);                             \
            __builtin_sub_overflow(__a__i, __b__i, __result_addr__o);         \
            })

/**
 * @brief C-Macro for performing a multiplication on two values, while checking
 *  if an overflow occurs.
 *
 * This C-Macro performs a multiplication of two values while checking if an
 *  overflow occurs.
 *
 * The two values and the C-Variable containing the result shall be of the
 *  same C-Type (or of C-Type compatible for the C-Compiler).
 * The result of the operation is returned in the C-Variable referenced by
 *  the given C-Pointer <result_addr__o>.
 *
 * The C-Macro returns a boolean (C-Type TukBOOL):
 *  - DukBOOL_TRUE: An overflows has occurred.
 *  - DukBOOL_FALSE: No overflow has occurred.
 *
 * @param[in] a__i First input parameter.
 * @param[in] b__i Second input parameter.
 * @param[out] result_addr__o Address of the C-Variable containing the result
 *  of <a__i> multiplied with <b__i>.
 *
 * @return (TukBOOL) Boolean value indicating if an overflow has occurred.
 * @retval DukBOOL_TRUE: An overflows has occurred.
 * @retval DukBOOL_FALSE: No overflow has occurred.
 */
#define MukVAL_MUL_CHECK_OVERFLOW(a__i, b__i, result_addr__o) ({              \
            typeof(a__i) __a__i = (a__i);                                     \
            typeof(b__i) __b__i = (b__i);                                     \
            typeof(result_addr__o) __result_addr__o = (result_addr__o);       \
            (void) (&__a__i == &__b__i);                                      \
            (void) (&__a__i == __result_addr__o);                             \
            __builtin_mul_overflow(__a__i, __b__i, __result_addr__o);         \
            })


/* ======================================================================== */
/*             COMPILER - GCC - C-MACROS - MARKING EXTERNAL CODE            */
/* ======================================================================== */

/**
 * @brief C-Macro used to mark the beginning of external code.
 *
 * This C-Macro is used to mark the beginning of external code.
 *
 * As external code may not satisfy the same requirements as internal code
 *  warnings produced by compilers and other analysis tools may not be
 *  relevant. We mark required header files as external code for this reason.
 */
#if !(defined DukGCC_EXTERNAL_DIAGNOSTIC)
    #define MukGCC_EXTERNAL_DIAGNOSTIC
#else
    #define Mukxstr(s) Mukstr(s)
    #define Mukstr(s) #s
    #define MukGCC_EXTERNAL_DIAGNOSTIC _Pragma(Mukxstr(DukGCC_EXTERNAL_DIAGNOSTIC))
#endif
#define MukBEGIN_EXTERNAL_CODE                                                \
    _Pragma("GCC diagnostic push")                                            \
    MukGCC_EXTERNAL_DIAGNOSTIC

/**
 * @brief C-Macro used to mark the beginning of external code.
 *
 * This C-Macro is used to mark the beginning of external code.
 *
 * As external code may not satisfy the same requirements as internal code
 *  warnings produced by compilers and other analysis tools may not be
 *  relevant. We mark required header files as external code for this reason.
 */
#define MukEND_EXTERNAL_CODE                                                  \
    _Pragma("GCC diagnostic pop")

/* //////////////////////////////////////////////////////////////////////// */
/*                                COMPILER - IAR                            */
/* //////////////////////////////////////////////////////////////////////// */

/* @note To reliably use IAR, it should use the extended language mode, set
 *  with the command line option -e, or equivalently the "Standard with IAR
 *  extensions" option in the IDE. There doesn't seem to be a check for this
 *  but it will be quite visible as IAR supports GCC style attributes in this
 *  mode, and not when using a stricter mode.
 */

#elif defined(__IAR_SYSTEMS_ICC__)

/* Enforce that we are using at least the C11 standard for compiling with
 *  IAR.
 *
 * @note IAR calls "Standard C", the latest version of C, as opposed to C89.
 *
 * @note This macro may be defined by the C standard.
 */
#if (__STDC__ != 1)
    #error "**ERROR:COMPILER** The compiler needs to support C11 standard."
#endif /* (__STDC__ != 1) */

/* ======================================================================== */
/*                        COMPILER - IAR - DEFINITIONS                      */
/* ======================================================================== */

/**
 * @brief Definitions related to GNU ARM GCC usage.
 */
#define IAR_COMPILER 0x00494152

/**
 * @brief Definition of uKernel Compiler used: GNU ARM GCC.
 */
#define UK_COMPILER IAR_COMPILER

/* ======================================================================== */
/*               COMPILER - IAR - COMPILER ATTRIBUTES - C-TYPE              */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Type.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Type in its
 *  definition.
 *
 * @usage This C-Compiler Attribute has to be placed just after the 'typedef '
 *  C-Compiler keyword.
 */
#define CAukTYPE_DEPRECATED   __attribute__((deprecated))


/* ======================================================================== */
/*            COMPILER - IAR - COMPILER ATTRIBUTES - C-VARIABLES            */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a possibly unused C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a possibly
 *  unused C-Variable. When this C-Compiler Attribute is present, the
 *  C-Compiler will not generate warning/error if the C-Variable is not used
 *  in the effectively compiled source code associated unit.
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its definition.
 */
#define CAukVAR_UNUSED_MAYBE                    __attribute__((unused))

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Variable in
 *  its definition/declaration.
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its declaration.
 */
#define CAukVAR_DEPRECATED                      __attribute__((deprecated))

/**
 * @brief C-Compiler Attribute for indicating an address alignment condition
 *  for a C-Variable.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Linker that the memory address of a C-Variable has to be aligned on
 *  (e.g. is a multiple of) the given alignment value (in bytes)
 *  <aligned_on_bytes__i> .
 *
 * @usage This C-Compiler Attribute has to be placed just after the name of
 *  the C-Variable in its definition.
 *
 * @param [in] aligned_on_bytes__i Alignment (in bytes) to be used for the
 *  memory address of the C-Variable.
 */
#define CAukVAR_ALIGNED(aligned_on_bytes__i)                                  \
                __attribute__((aligned(aligned_on_bytes__i)))


/* ======================================================================== */
/*            COMPILER - IAR - COMPILER ATTRIBUTES - C-FUNCTIONS            */
/* ======================================================================== */

/**
 * @brief C-Compiler Attribute for indicating a possibly unused C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a possibly
 *  unused C-Function. When this C-Compiler Attribute is present, the
 *  C-Compiler will not generate warning/error if the C-Function is not used
 *  in the effectively compiled source code associated unit.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_UNUSED_MAYBE   __attribute__((unused))

/**
 * @brief C-Compiler Attribute for indicating a deprecated C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating a deprecated
 *  (e.g. that shall not be used anymore in any new source code) C-Function in
 *  its definition/declaration.
 *
 * @usage This C-Compiler Attribute has to be placed at the end the C-Function
 *  declaration.
 */
#define CAukFUNC_DEPRECATED     __attribute__((deprecated))

/**
 * @brief C-Compiler Attribute for indicating that the C-Function has to be
 *  kept in final generated binary code.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler and C-Linker to keep the given C-Function in final generated
 *  binary code, even if the C-Function is not referenced in compiled code
 *  when building the calling tree.
 *
 * @usage This C-Compiler Attribute shall be used for C-Function that may be
 *  invoked from calling table or from external code as interface entry point,
 *  in order to ensure that it will not be removed by C-Linker optimizations
 *  from final generated binary code.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_NEEDED_ALWAYS  __attribute__((used))

/**
 * @brief C-Compiler Attribute for indicating to always inline a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to always inline given C-Function.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration after the 'inline' C-Keyword.
 */
#define CAukFUNC_INLINE_ALWAYS

/**
 * @brief C-Compiler Attribute for indicating to never inline a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to never inline given C-Function.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_INLINE_NEVER    __attribute__((noinline))

/**
 * @brief C-Compiler Attribute for indicating that a C-Function never returns.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler that given C-Function never returns.
 *
 * @usage This C-Compiler Attribute should be used for C-Function that never
 *  return (fatal error management, ...) in order to help C-Compiler performing
 *  optimal generated code optimizations.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_RETURN_NEVER    __attribute__((noreturn))

/**
 * @brief C-Compiler Attribute for indicating that returned value from a
 *  C-Function has to be checked.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler to verify that the returned value from given C-Function is
 *  checked in the caller code.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 *
 * @impl IAR doesn't support this feature.
 */
#define CAukFUNC_RETURN_VALUE_CHECK

/**
 * @brief C-Compiler Attribute for indicating that a C-Function is pure.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler that given C-Function is pure.
 *
 * @warning This C-Compiler Attribute SHALL BE USED ONLY for C-Function that
 *  do not modify the state of the program that is observable by means other
 *  than inspecting the C-Function's return value. The C-Function can however
 *  safely read any non-volatile objects, and modify the value of objects in
 *  a way that does not affect their return value or the observable state of
 *  the program.
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_PURE   __attribute__((pure))

/**
 * @brief C-Compiler Attribute for indicating to C-Compiler not to generate
 *  prologue and epilogue sequences in a C-Function.
 *
 * Definition of the uKernel C-Compiler Attribute for indicating to the
 *  C-Compiler not to generate prologue and epilogue sequences for the
 *  C-Function (in charge of managing parameters, register saving, ...).
 *
 * @usage This C-Compiler Attribute is useful for C-Function that have assembly
 *  language code, or that are called under specific circumstances (MCU
 *  exception, ...).
 *
 * @usage This C-Compiler Attribute has to be placed at the very beginning of
 *  the C-Function declaration.
 */
#define CAukFUNC_ASM_NAKED       __attribute__((naked))


/* ======================================================================== */
/*      COMPILER - IAR - C-MACROS - HELPERS FOR CONSTANTS C-VARIABLES       */
/* ======================================================================== */

#define MukVAR_DEFINE_SECTION(label__i, ctype__i, clinker_section_name_string__i)      \
            ctype__i label__i
#define MukCONST_STRUCT_DEFINE_SECTION(label__i, ctype__i, clinker_section_name_string__i)      \
            ctype__i const label__i

/* ======================================================================== */
/*             COMPILER - IAR - C-MACROS - MARKING EXTERNAL CODE            */
/* ======================================================================== */

/**
 * @brief C-Macro used to mark the beginning of external code.
 *
 * This C-Macro is used to mark the beginning of external code.
 *
 * As external code may not satisfy the same requirements as internal code
 *  warnings produced by compilers and other analysis tools may not be
 *  relevant. We mark required header files as external code for this reason.
 */
#define MukBEGIN_EXTERNAL_CODE

/**
 * @brief C-Macro used to mark the beginning of external code.
 *
 * This C-Macro is used to mark the beginning of external code.
 *
 * As external code may not satisfy the same requirements as internal code
 *  warnings produced by compilers and other analysis tools may not be
 *  relevant. We mark required header files as external code for this reason.
 */
#define MukEND_EXTERNAL_CODE

#endif /* Compiler identification */


/* //////////////////////////////////////////////////////////////////////// */
/*                         COMPILER - NOT SUPPORTED                         */
/* //////////////////////////////////////////////////////////////////////// */
/* Check if at least one C-Compiler has been found as supported.
 * If not then raise a FATAL COMPILATION ERROR.  */
#if !defined(UK_COMPILER)
#error 'No C-Compiler supported by uKernel C API has been found'
#endif /* !defined(UK_COMPILER) */


/* ======================================================================== */
/*                 COMPILER - C-MACROS - COMPILATION CHECKS                 */
/* ======================================================================== */

/**
 * @brief C-Macro for performing a Static Assertion at compilation time.
 *
 * Definition of the uKernel C-Macro for performing a Static Assertion in
 *  compiled C-Code.
 *
 * The C-Compiler shall be capable of evaluating the given <assertion__i>
 *  as a constant at compilation time:
 *  - If the resulting evaluated constant is equal to null numerical value,
 *   it is considered as a compile-time error (compilation is considered as
 *   having failed) and the C-Compiler displays the given <error_message__i>
 *   message.
 *  - Else the C-Compiler continues the compilation with the next line in
 *   source code.
 *
 * @note Pedantically, it's the C-Preprocessor.
 *
 * @note This macro is deprecated. There is no need to define
 *
 * @implementation A Static Assertion never generates any executable code (and
 *  thus does not affect performances or compiled binary code size).
 *
 * @usage For readability, a semicolon (';') mark has to be added at the end of
 *  this C-Macro.
 */
#define MukASSERT_STATIC(assertion__i, error_message__i)                      \
            _Static_assert(assertion__i, error_message__i);


/* ======================================================================== */
/*               COMPILER - C-MACROS - HELPERS FOR C-VARIABLES              */
/* ======================================================================== */
/* As good coding practice, and to enforce high quality and robust software,
 *  the purpose of the C-Macros defined hereafter is:
 *  - To make sure that each definition is done with a dedicated C-Type
 *   (strong typing policy used) and clearly specified initialization
 *   and placement conditions.
 *  - When need be, to ease the usage of specific C-Compiler Attributes to
 *   be applied globally.
 */

/**
 * @brief C-Macro for declaring a C-Variable.
 *
 * Definition of the uKernel C-Macro as helper for declaring a C-Variable
 *  with the given name <label__i> and of the given C-Type <ctype__i>.
 *
 * @usage This C-Macro is the associate of the MukVAR_DEFINE and
 *  MukVAR_DEFINE_INIT C-Macros.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  declaration.
 *
 * @param[in] label__i Label to use for naming the declared C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 */
#define MukVAR_DECLARE(label__i, ctype__i)                                    \
            extern ctype__i label__i;

/**
 * @brief C-Macro for defining a C-Variable with null initial value.
 *
 * Definition of the uKernel C-Macro as helper for defining a C-Variable with
 *  the given name <label__i>, of the given C-Type <ctype__i>, and with a null
 *  initial value.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 */
#define MukVAR_DEFINE(label__i, ctype__i)                                     \
            ctype__i label__i;

/**
 * @brief C-Macro for defining a C-Variable with specific initial value.
 *
 * Definition of the uKernel C-Macro as helper for defining a C-Variable with
 *  the given name <label__i>, of the given C-Type <ctype__i>, and with the
 *  given initial value <value__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] value__i Initial value of the defined C-Variable.
 */
#define MukVAR_DEFINE_INIT(label__i, ctype__i, value__i)                      \
            ctype__i label__i = (value__i);


/* ======================================================================== */
/*          COMPILER - C-MACROS - HELPERS FOR CONSTANTS C-VARIABLES         */
/* ======================================================================== */
/* As good coding practice, and to enforce high quality and robust software,
 *  the purpose of the C-Macros defined hereafter is:
 *  - To make sure that each definition is done with a dedicated C-Type
 *   (strong typing policy used) and clearly specified initialization
 *   and placement conditions.
 *  - When need be, to ease the usage of specific C-Compiler Attributes to
 *   be applied globally.
 */

/**
 * @brief C-Macro for declaring a constant typed C-Variable.
 *
 * Definition of the uKernel C-Macro for declaring a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') with the given name
 *  <label__i>, and of the given C-Type <ctype__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 */
#define MukCONST_DECLARE(label__i, ctype__i)                                  \
            static ctype__i const label__i;


/**
 * @brief C-Macro for defining a constant typed C-Variable.
 *
 * Definition of the uKernel C-Macro for defining a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') with the given name
 *  <label__i>, of the given C-Type <ctype__i>, and with the initial given
 *  value <value__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] value__i Value to affect to the constant C-Variable.
 */
#define MukCONST_DEFINE(label__i, ctype__i, value__i)                         \
            static ctype__i const label__i = value__i;

/**
 * @brief C-Macro for defining a constant typed C-Variable with one flag set.
 *
 * Definition of the uKernel C-Macro for defining a constant typed C-Variable
 *  (using the C-Compiler keyword 'static const') containing one flag set
 *  (i.e. only one bit is set in its value) with the given name <label__i>
 *  and of the given C-Type <ctype__i>.
 * The bit number of the flag is given in the parameter <bit_number__i> (the
 *  bit number 0 is the rightmost bit).
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  definition.
 *
 * @param[in] label__i Label to use for naming the defined constant C-Variable.
 * @param[in] ctype__i C-Type to use for casting the C-Variable.
 * @param[in] bit_number__i Bit number of the flag to be set to 1 in the
 *  value affected to the constant C-Variable (all other bits of the value are
 *  reset to 0).
 */
#define MukCONST_DEFINE_BF(label__i, ctype__i, bit_number__i)                 \
            static const ctype__i label__i = (1UL<<(bit_number__i));


/**
 * @brief C-Macro as helper for declaring a constant typed C-Structure.
 *
 * Definition of the uKernel C-Macro as helper for the declaration of a
 *  constant typed C-Structure.
 *
 * @usage This C-Macro is the associate of the MukCONST_STRUCT_DEFINE.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  declaration.
 *
 * @param[in] label__i Label to use for naming the declared constant
 *  C-Structure.
 * @param[in] ctype__i C-Type to use for the C-Structure.
 */
#define MukCONST_STRUCT_DECLARE(label__i, ctype__i)                           \
            extern ctype__i const label__i;

/**
 * @brief C-Macro as helper for defining a constant typed C-Structure.
 *
 * Definition of the uKernel C-Macro as helper for defining a constant typed
 *  C-Structure with the given name <label__i>, and of the given C-Type
 *  <ctype__i>.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and SHALL BE followed by:
 *   - An equal sign ('=').
 *   - The contents of the constant C-Structure.
 *   - A semicolon (';') to mark the end of the definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Structure.
 * @param[in] ctype__i C-Type to use for the C-Structure.
 */
#define MukCONST_STRUCT_DEFINE(label__i, ctype__i)                            \
            ctype__i const label__i



/**
 * @brief C-Macro as helper for declaring a constant typed C-Array.
 *
 * Definition of the uKernel C-Macro as helper for declaring a constant typed
 *  C-Array with the given name <label__i>, of the given C-Type <ctype__i>, and
 *  with the given <carray_size__i> number of elements.
 *
 * @note This C-Macro is the associate of the MukCONST_ARRAY_DEFINE.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and followed for readability by a semicolon (';') to mark the end of the
 *  declaration.
 *
 * @param[in] label__i Label to use for naming the declared C-Array.
 * @param[in] ctype__i C-Type to use for casting each C-Array element.
 * @param[in] carray_size__i Size of the C-Array (number of elements).
 */
#define MukCONST_ARRAY_DECLARE(label__i, ctype__i, carray_size__i)            \
            extern ctype__i const label__i[carray_size__i];


/**
 * @brief C-Macro as helper for defining a constant typed C-Array.
 *
 * Definition of the uKernel C-Macro as helper for defining a constant typed
 *  C-Array with the given name <label__i>, the given C-Type <ctype__i>, and
 *  with the given <carray_size__i> number of elements.
 *
 * @usage This C-Macro has to be placed at the very beginning of the line,
 *  and SHALL BE followed by:
 *   - An equal sign ('=').
 *   - The contents of the constant C-Array.
 *   - A semicolon (';') to mark the end of the definition.
 *
 * @param[in] label__i Label to use for naming the defined C-Array.
 * @param[in] ctype__i C-Type to use for casting each C-Array element.
 * @param[in] carray_size__i Size of the C-Array (number of elements).
 */
#define MukCONST_ARRAY_DEFINE(label__i, ctype__i, carray_size__i)             \
            ctype__i const label__i[carray_size__i]



/* ======================================================================== */
/*                 COMPILER - C-MACROS - HELPERS FOR VALUES                 */
/* ======================================================================== */

/**
 * @brief C-Macro for associating a C-Type to a value.
 *
 * Definition of the uKernel C-Macro for associating a C-Type (the term
 *  'value cast' is also often used) given in parameter <ctype__i> to a value
 *  in given parameter <value__i>.
 *
 * @usage The purpose of this C-Macro is to encourage good coding practices by
 *  enforcing that all the values definitions (and notably the numeric
 *  literals) have an explicit C-Type.
 *
 * @param[in] ctype__i C-Type to use to cast the resulting value.
 * @param[in] value__i Value to be casted with given C-Type.
 */
#define MukVAL_TYPED(ctype__i, value__i)                                      \
            ((ctype__i)(value__i))

/**
 * @brief C-Macro for associating a C-Type to a value containing a Flag.
 *
 * Definition of the uKernel C-Macro for associating a C-Type (the term
 *  'value cast' is also often used) given in parameter <ctype__i> to a value
 *  containing a Flag (e.g. one and only one bit set in the value). The bit
 *  number of the flag is given in the parameter <bit_number__i> (the bit
 *  number 0 is the rightmost bit).
 *
 * @usage The purpose of this C-Macro is to encourage good coding practices by
 *  enforcing that all the flag definitions have an explicit C-Type.
 *
 * @param[in] ctype__i C-Type to use to cast the resulting value.
 * @param[in] bit_number__i Bit number of the flag to be set to 1 in the
 *  value to be casted (all other bits of the value are reset to 0).
 */
#define MukVAL_TYPED_BF(ctype__i, bit_number__i)                              \
            ((ctype__i)(1UL<<(bit_number__i)))



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_COMPILERS_H_INSIDE
#endif /* !defined(UK_COMPILERS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

