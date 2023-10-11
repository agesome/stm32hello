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
 * @file          uk_constants.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  C-Constants sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the definitions of the C-Constants.
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
#if !defined(UK_CONSTANTS_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_constants.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_CONSTANTS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONSTANTS_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                          UKERNEL API - C-CONSTANTS                       */
/* ######################################################################## */
/* Hereafter are defined the C-Constants of the uKernel API.
 *
 * NOTE: These definitions are agnostic to the selected Platform and
 *  MCU Device.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                             C-CONSTANTS - GENERIC                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining an invalid value to be used for a 32-bit address
 *  in MCU addressing space.
 *
 * Definition of the C-Constant for the invalid value to be used for a 32-bit
 *  address in MCU addressing space.
 *
 * @implementation It is guaranteed that this value IS NOT equals to null(0)
 *  and not multiple of 8.
 *  Indeed the null(0) address is often a valid address on MCU (address used
 *  during MCU reset), and that's the reason it is not a good choice for
 *  invalid address value.
 *
 * @implementation The 0xFFFFFFFx addresses are not valid address values on
 *  supported MCUs (access triggers a Fatal Error, which is what we want for
 *  an invalid or special address value).
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukADDRESS_INVALID                                                    \
    MukVAL_TYPED(TukADDRESS32, 0xFFFFFFFFUL)


/**
 * @brief C-Constant defining a special value to be used for ignoring a 32-bit
 *  address in MCU addressing space as input parameter.
 *
 * Definition of the C-Constant for a special value to be used for ignoring a
 *  32-bit address in MCU addressing space as input parameter.
 *
 * @implementation The 0xFFFFFFFx addresses are not valid address values on
 *  supported MCUs (access triggers a Fatal Error, which is what we want for
 *  an invalid or special address value).
 *
 * @usage This C-Constant is used to indicate that 32-bit address input shall
 *  be ignored. It may notably be used when we are not interested by the
 *  returned value of C-Function: if the C-Function supports it (it has to be
 *  explicitly indicated in its documentation), then this special value can
 *  be used as return pointer address to indicate that we want to dismiss the
 *  returned value.
 */
#define DukADDRESS_IGNORE                                                     \
    MukVAL_TYPED(TukADDRESS32, 0xFFFFFFFEUL)


/**
 * @brief C-Constant defining a special value to be used for signaling that
 *  the address of a Data Persistent Area is to be found some other way.
 *
 * Definition of the C-Constant for a special value to be used for signaling
 *  that the address of a Data Persistent Area is to be found some other way.
 *
 * @usage This C-Constant is used to indicate that 32-bit address input shall
 *  be found in a target-specific manner. This can be obtained from flash,
 *  from the bootloader, or some other way.
 */
#define DukADDRESS_INVALID_DATA_PERSISTENT                                    \
    MukVAL_TYPED(TukADDRESS32, 0xFFFFFFE0UL)


/* //////////////////////////////////////////////////////////////////////// */
/*                             C-CONSTANTS - BOOLEAN                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the 'false' boolean value.
 *
 * Definition of the C-Constant for the 'false' boolean value used by default
 *  by the C-Compiler (see TukBOOL).
 *
 * @usage This boolean value SHALL NOT be used for processing results linked
 *  to security, safety or robustness functionalities: the C-Type TukSAFEBOOL
 *  and associated C-Constants SHALL BE used instead.
 */
#define DukBOOL_FALSE     MukVAL_TYPED(TukBOOL, false)

/**
 * @brief C-Constant defining the 'true' boolean value.
 *
 * Definition of the C-Constant for the 'true' boolean value used by default
 *  by the C-Compiler (see TukBOOL).
 *
 * @usage This boolean value SHALL NOT be used for processing results linked
 *  to security, safety or robustness functionalities: the C-Type TukSAFEBOOL
 *  and associated C-Constants SHALL BE used instead.
 */
#define DukBOOL_TRUE      MukVAL_TYPED(TukBOOL, true)


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - STATUS CODE STRUCTURE                   */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the LSb of the Reason field in the Status Code
 *  C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Reason
 *  field in the Status Code C-Type (see TukSTATUS).
 */
#define DukSTATUS_REASON_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the MSb of the Reason field in the Status Code
 *  C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Reason
 *  field in the Status Code C-Type (see TukSTATUS).
 */
#define DukSTATUS_REASON_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 4U)

/**
 * @brief C-Constant defining the bitmask for the Reason field in the Status
 *  Code C-Type.
 *
 * Definition of the C-Constant for the bitmask for the Reason field in the
 *  Status Code C-Type.
 */
#define DukSTATUS_REASON_FIELD_MASK        MukVAL_TYPED(TukSTATUS,            \
                        MukVAL_FIELD_BITMASK32(DukSTATUS_REASON_FIELD_LSb,    \
                                             DukSTATUS_REASON_FIELD_MSb))

/**
 * @brief C-Constant defining the LSb of the Nature field in the Status Code
 *  C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Nature
 *  field in the Status Code C-Type (see TukSTATUS).
 */
#define DukSTATUS_NATURE_FIELD_LSb         MukVAL_TYPED(TukBITNUM, 5U)

/**
 * @brief C-Constant defining the MSb of the Nature field in the Status Code
 *  C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Nature
 *  field in the Status Code C-Type (see TukSTATUS).
 */
#define DukSTATUS_NATURE_FIELD_MSb         MukVAL_TYPED(TukBITNUM, 8U)


/**
 * @brief C-Constant defining the bitmask for the Nature field in the Status
 *  Code C-Type.
 *
 * Definition of the C-Constant for the bitmask for the Nature field in the
 *  Status Code C-Type.
 */
#define DukSTATUS_NATURE_FIELD_MASK        MukVAL_TYPED(TukSTATUS,            \
                        MukVAL_FIELD_BITMASK32(DukSTATUS_NATURE_FIELD_LSb,    \
                                             DukSTATUS_NATURE_FIELD_MSb))



/* //////////////////////////////////////////////////////////////////////// */
/*                      C-CONSTANTS - STATUS CODE NATURE                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Information Nature field bit number for
 *  Status Code.
 *
 * Definition of the C-Constant for the Information Nature field bit number for
 *  Status Code.
 */
#define DukSTATUS_NATURE_FIELD_INFO_BITNUM                                    \
                                                MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the Warning Nature field bit number for Status
 *  Code.
 *
 * Definition of the C-Constant for the Warning Nature field bit number for
 *  Status Code.
 */
#define DukSTATUS_NATURE_FIELD_WARNING_BITNUM                                 \
                                                MukVAL_TYPED(TukBITNUM, 1U)

/**
 * @brief C-Constant defining the Error Nature field bit number for Status
 *  Code.
 *
 * Definition of the C-Constant for the Error Nature field bit number for
 *  Status Code.
 */
#define DukSTATUS_NATURE_FIELD_ERROR_BITNUM                                   \
                                                MukVAL_TYPED(TukBITNUM, 2U)

/**
 * @brief C-Constant defining the Fatal Error Nature field bit number for
 *  Status Code.
 *
 * Definition of the C-Constant for the Fatal Error Nature field bit number for
 *  Status Code.
 */
#define DukSTATUS_NATURE_FIELD_FATAL_BITNUM                                   \
                                                MukVAL_TYPED(TukBITNUM, 3U)


/**
 * @brief C-Constant defining the count of different Status Code Natures
 *  supported.
 *
 * Definition of the C-Constant for the count of different Status Code Natures
 *  supported.
 */
#define DukSTATUS_NATURE_COUNT                                                \
                                                MukVAL_TYPED(TukCOUNT8, 4U)


/**
 * @brief C-Constant defining the Information Nature flag for Status Code.
 *
 * Definition of the C-Constant for the Information Nature flag for Status
 *  Code.
 */
#define DukSTATUS_NATURE_INFO_FLAG         MukVAL_TYPED_BF(TukSTATUS,         \
                                    (DukSTATUS_NATURE_FIELD_LSb +             \
                                     DukSTATUS_NATURE_FIELD_INFO_BITNUM))

/**
 * @brief C-Constant defining the Warning Nature flag for Status Code.
 *
 * Definition of the C-Constant for the Warning Nature flag for Status Code.
 */
#define DukSTATUS_NATURE_WARNING_FLAG      MukVAL_TYPED_BF(TukSTATUS,         \
                                    (DukSTATUS_NATURE_FIELD_LSb +             \
                                     DukSTATUS_NATURE_FIELD_WARNING_BITNUM))

/**
 * @brief C-Constant defining the Error Nature flag for Status Code.
 *
 * Definition of the C-Constant for the Error Nature flag for Status Code.
 */
#define DukSTATUS_NATURE_ERROR_FLAG        MukVAL_TYPED_BF(TukSTATUS,         \
                                    (DukSTATUS_NATURE_FIELD_LSb +             \
                                     DukSTATUS_NATURE_FIELD_ERROR_BITNUM))

/**
 * @brief C-Constant defining the Fatal Error Nature flag for Status Code.
 *
 * Definition of the C-Constant for the Fatal Error Nature flag for Status
 *  Code.
 *
 * @usage Any of the Status Code defined with Nature Error
 *  (see DukSTATUS_ERR_xxx) can be converted to Fatal Error Status Code by
 *  clearing DukSTATUS_NATURE_ERROR_FLAG and setting this flag (see
 *  uKernel Helper ukStatusErrorConvertToFatalError()).
 */
#define DukSTATUS_NATURE_ERROR_FATAL_FLAG  MukVAL_TYPED_BF(TukSTATUS,         \
                                    (DukSTATUS_NATURE_FIELD_LSb +             \
                                     DukSTATUS_NATURE_FIELD_FATAL_BITNUM))


/**
 * @brief C-Constant defining the valid bitmask for Nature field of a Status
 * Code.
 *
 * Definition of the C-Constant of the bitmask of valid flags for Nature field
 *  of a Status Code.
 *
 * @note This bitmask is defined in as per whole Status Code structure (see
 *  TukSTATUS C-Type), and not as per the Nature field. Thus this bitmask
 *  definition is shifted of DukSTATUS_NATURE_FIELD_LSb bits.
 *
 * @implementation This bitmask is always included in the bitmask of the
 *  Nature field DukSTATUS_NATURE_FIELD_MASK.
 *
 * @implementation Each bit set (logical 1) in the bitmask corresponds to a
 *  valid flag.
 */
#define DukSTATUS_NATURE_VALID_MASK                                           \
            MukVAL_TYPED(TukSTATUS,                                           \
                         DukSTATUS_NATURE_INFO_FLAG                         | \
                         DukSTATUS_NATURE_WARNING_FLAG                      | \
                         DukSTATUS_NATURE_ERROR_FLAG                        | \
                         DukSTATUS_NATURE_ERROR_FATAL_FLAG                  | \
                         0U)



/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - STATUS CODE                        */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter are defined the C-Constants for the Status Code returned by
 *  uKernel API.
 */


/* ======================================================================== */
/*                                  INFO                                    */
/* ======================================================================== */

/**
 * @brief C-Constant defining the Status Code returned when the requested
 *  action has been performed fully successfully.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 *  action has been performed fully successfully.
 * This Status Code is of Nature Info.
 */
#define DukSTATUS_INFO_OK                   MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_INFO_BITNUM,  1U))


/**
 * @brief C-Constant defining the maximal Reason value for a Status Code of
 *  Nature Info.
 *
 * Definition of the C-Constant for the maximal Reason value for a Status Code
 *  of Nature Info.
 *
 * @implementation The Reason value for a Status Code of Nature Info shall be
 *  in the range [1 ... DukSTATUS_INFO_REASON_MAX].
 */
#define DukSTATUS_INFO_REASON_MAX            MukVAL_TYPED(TukCOUNT8, 1U)


/* ======================================================================== */
/*                                WARNING                                   */
/* ======================================================================== */

/**
 * @brief C-Constant defining the Status Code returned when already done.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action has already been done or processed.
 * This Status Code is of Nature Warning.
 *
 * @note See C-Function documentation for detailed information on the part of
 *  the action done.
 */
#define DukSTATUS_WARN_ALREADY              MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  1U))

/**
 * @brief C-Constant defining the Status Code returned not done.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action has not been done or processed.
 *
 * This Status Code is of Nature Warning.
 */
#define DukSTATUS_WARN_NOT_DONE             MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  2U))

/**
 * @brief C-Constant defining the Status Code returned when done partially.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action has been done only partially (e.g. length truncation, ...).
 * This Status Code is of Nature Warning.
 *
 * @note See C-Function documentation for detailed information on the part of
 *  the action done.
 */
#define DukSTATUS_WARN_PARTIAL              MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  3U))


/**
 * @brief C-Constant defining the Status Code returned when part of the action
 *  result is invalid or unexpected.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action result is invalid or unexpected, but this is still acceptable for
 *  continuing execution in current context.
 * This Status Code is of Nature Warning.
 *
 * @note See C-Function documentation for detailed information on the part of
 *  the action done.
 */
#define DukSTATUS_WARN_INVALID              MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  4U))

/**
 * @brief C-Constant defining the Status Code returned when needed resource is
 *  in use.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action is needing a resource currently used.
 * This Status Code is of Nature Warning.
 *
 * @note See C-Function documentation for detailed information on the part of
 *  the action done.
 */
#define DukSTATUS_WARN_IN_USE               MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  5U))

/**
 * @brief C-Constant defining the Status Code returned when ukApp Configuration
 *  is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when ukApp
 *  Configuration is invalid (e.g. ukApp Code Block integrity check fails), but
 *  still acceptable for continuing execution in current uKernel Configuration
 *  context (e.g. default value is provided, check is not critical for ukProc
 *  execution, ...).
 * This Status Code is of Nature Warning.
 *
 * @note See C-Function documentation for detailed information on the part of
 *  the action done.
 */
#define DukSTATUS_WARN_UKAPP_CONFIG               MukVAL_TYPED(TukSTATUS,     \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_WARNING_BITNUM,  6U))


/**
 * @brief C-Constant defining the maximal Reason value for a Status Code of
 *  Nature Warning.
 *
 * Definition of the C-Constant for the maximal Reason value for a Status Code
 *  of Nature Warning.
 *
 * @implementation The Reason value for a Status Code of Nature Warning shall
 *  be in the range [1 ... DukSTATUS_WARN_REASON_MAX].
 */
#define DukSTATUS_WARN_REASON_MAX            MukVAL_TYPED(TukCOUNT8, 6U)


/* ======================================================================== */
/*                                 ERROR                                    */
/* ======================================================================== */

/**
 * @brief C-Constant defining the Status Code returned when a parameter is
 *  invalid.
 *
 * Definition of the C-Constant for the Status Code returned when a parameter
 *  given for performing requested action is invalid.
 * This Status Code is of Nature Error.
 *
 * @note This is the generic Status Code: some other Status Code are returned
 *  for some specific type of parameters (identifier, address, size, ...).
 */
#define DukSTATUS_ERR_PARAM                 MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  1U))

/**
 * @brief C-Constant defining the Status Code returned when identifier of an
 *  entity, instance or resource is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when identifier
 *  of an entity, instance or resource is invalid.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_IDENTIFIER            MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  2U))

/**
 * @brief C-Constant defining the Status Code returned when used address is
 *  invalid.
 *
 * Definition of the C-Constant for the Status Code returned when used address
 *  or address range for the requested action is invalid or never authorized.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_ADDRESS               MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  3U))

/**
 * @brief C-Constant defining the Status Code returned when used size is
 *  invalid.
 *
 * Definition of the C-Constant for the Status Code returned when used size
 *  or length for the requested action is invalid.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_SIZE                  MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  4U))

/**
 * @brief C-Constant defining the Status Code returned when configuration is
 *  invalid.
 *
 * Definition of the C-Constant for the Status Code returned when configuration
 *  of one of the item needed for requested action is invalid or does not
 *  authorize the requested action.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_CONFIG                MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  5U))

/**
 * @brief C-Constant defining the Status Code returned when needed
 *  precondition(s) not fulfilled.
 *
 * Definition of the C-Constant for the Status Code returned when at least one
 *  precondition (e.g. execution context, referenced item state, ...) is not
 *  as expected for requested action.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_PRECOND               MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  6U))

/**
 * @brief C-Constant defining the Status Code returned when needed
 *  credential(s) not granted.
 *
 * Definition of the C-Constant for the Status Code returned when at least one
 *  credential needed for requested action has not been granted.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_CREDENTIALS           MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  7U))

/**
 * @brief C-Constant defining the Status Code returned when parameter structure
 *  is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when the
 *  parameter structure given or used for requested action is malformed.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_STRUCT                MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  8U))

/**
 * @brief C-Constant defining the Status Code returned when referenced item
 *  is not found.
 *
 * Definition of the C-Constant for the Status Code returned when referenced
 *  item needed for requested action is not found (e.g. non existing label,
 *  identifier).
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_NOT_FOUND             MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  9U))

/**
 * @brief C-Constant defining the Status Code returned when already done.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action has already been done or processed, and cannot be done another
 *  time.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_ALREADY               MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  10U))

/**
 * @brief C-Constant defining the Status Code returned when referenced uKProc
 *  has been terminated.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action cannot be performed as referenced ukProc needed for the requested
 *  action has been terminated (the uKernel has triggered a ukProc Termination
 *  on its ukProc Instance).
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_UKPROC_TERMINATED     MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  11U))

/**
 * @brief C-Constant defining the Status Code returned when a timeout has
 *  occurred.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 * action cannot has not been performed before a timeout expires.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_TIMEOUT               MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  12U))

/**
 * @brief C-Constant defining the Status Code returned when an action is not
 *  supported.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 *  action cannot be performed due to current execution context or
 *  configuration (e.g. uKernel Feature not supported).
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_NOT_SUPPORTED         MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  13U))

/**
 * @brief C-Constant defining the Status Code returned when an action is
 *  forbidden.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 *  action cannot be performed as forbidden (independently of current execution
 *  context or configuration).
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_FORBIDDEN             MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  14U))

/**
 * @brief C-Constant defining the Status Code returned when needed resources
 *  are not available.
 *
 * Definition of the C-Constant for the Status Code returned when a needed
 *  resource for requested action is not available or exhausted.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_NO_RESOURCE             MukVAL_TYPED(TukSTATUS,         \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  15U))


/**
 * @brief C-Constant defining the Status Code returned when the state of needed
 *  resource is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when the state
 *  of needed resource (ukProc, Shared Buffer, ...) does not allow the
 *  requested action.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_STATE_INVALID         MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  16U))

/**
 * @brief C-Constant defining the Status Code returned when needed resource is
 *  in use.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action is needing a resource currently used.
 * This Status Code is of Nature Error.
 *
 * @usage In case of hardware resource, the Status Code DukSTATUS_ERR_HW_IN_USE
 *  shall be used instead.
 */
#define DukSTATUS_ERR_IN_USE                MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  17U))

/**
 * @brief C-Constant defining the Status Code returned when the requested
 *  action processing has meet unexpected conditions.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 *  action has lead to an internal value, state, invocation sequence or
 *  execution context, which shall not be possible in expected execution flow
 *  in regards of code implementation.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_UNEXPECTED            MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  18U))

/**
 * @brief C-Constant defining the Status Code returned upon an invalid
 *  invocation sequence.
 *
 * Definition of the C-Constant for the Status Code returned when an invalid
 *  invocation sequence of C-Function, preventing to perform the request
 *  action.
 * This Status Code is of Nature Error.
 *
 * @usage In case an invocation sequence that shall never append in regards of
 *  code implementation, the Status Code DukSTATUS_ERR_UNEXPECTED shall be
 *  used instead.
 */
#define DukSTATUS_ERR_SEQUENCE                      MukVAL_TYPED(TukSTATUS,   \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  19U))

/**
 * @brief C-Constant defining the Status Code returned when the requested
 *  action has lead to invalid security state.
 *
 * Definition of the C-Constant for the Status Code returned when the requested
 *  action has lead to invalid security state.
 * This Status Code is of Nature Error.
 *
 * @usage This Status Code is a serious condition, and ukProc shall take
 *  immediate actions to protect its sensitive assets.
 */
#define DukSTATUS_ERR_SECURITY_CONSISTENCY  MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  20U))


/**
 * @brief C-Constant defining the Status Code returned when internal uKernel
 *  Configuration is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when internal
 *  uKernel Configuration is invalid.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_UKERNEL_CONFIG           MukVAL_TYPED(TukSTATUS,        \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  21U))

/**
 * @brief C-Constant defining the Status Code returned when ukApp Configuration
 *  is invalid.
 *
 * Definition of the C-Constant for the Status Code returned when ukApp
 *  Configuration is invalid.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_UKAPP_CONFIG           MukVAL_TYPED(TukSTATUS,          \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  22U))


/**
 * @brief C-Constant defining the Status Code returned when an unexpected MCU
 *  reset as occurred during a uKernel Session.
 *
 * Definition of the C-Constant for the Status Code returned when an unexpected
 *  MCU reset as occurred during a uKernel Session.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_MCU_RESET                MukVAL_TYPED(TukSTATUS,        \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  23U))

/**
 * @brief C-Constant defining the Status Code returned upon an unexpected
 *  hardware configuration.
 *
 * Definition of the C-Constant for the Status Code returned when configuration
 *  or value in hardware is not expected by code implementation, making further
 *  hardware use impossible.
 *
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_HW_CONFIG                    MukVAL_TYPED(TukSTATUS,    \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  24U))

/**
 * @brief C-Constant defining the Status Code returned upon an unexpected
 *  hardware state.
 *
 * Definition of the C-Constant for the Status Code returned when state of
 *  hardware is not expected by code implementation (due to hardware failure,
 *  bug, improper version used, ...), making further hardware  use impossible.
 *
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_HW_STATE              MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  25U))


/**
 * @brief C-Constant defining the Status Code returned when needed hardware
 *  resource is in use.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action is needing a hardware resource currently used or not available.
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_HW_IN_USE                MukVAL_TYPED(TukSTATUS,        \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  26U))

/**
 * @brief C-Constant defining the Status Code returned upon non qualified
 *  hardware error.
 *
 * Definition of the C-Constant for the Status Code returned when requested
 *  action has lead to an non qualified or unexpected hardware error.
 *
 * This Status Code is of Nature Error.
 */
#define DukSTATUS_ERR_HW                    MukVAL_TYPED(TukSTATUS,           \
             MukSTATUS_BUILD(DukSTATUS_NATURE_FIELD_ERROR_BITNUM,  27U))



/**
 * @brief C-Constant defining the maximal Reason value for a Status Code of
 *  Nature Error.
 *
 * Definition of the C-Constant for the maximal Reason value for a Status Code
 *  of Nature Error.
 *
 * @implementation The Reason value for a Status Code of Nature Error shall be
 *  in the range [1 ... DukSTATUS_ERR_REASON_MAX].
 */
#define DukSTATUS_ERR_REASON_MAX            MukVAL_TYPED(TukCOUNT8, 27U)



/* //////////////////////////////////////////////////////////////////////// */
/*                           C-CONSTANTS - VERSION                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Major field in Version C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Major field in Version  C-Type (see TukVERSION).
 */
#define DukVERSION_MAJOR_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the Major field in Version C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Major field in Version  C-Type (see TukVERSION).
 */
#define DukVERSION_MAJOR_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 24U)

/**
 * @brief C-Constant defining the MSb of the Minor field in Version C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of Minor
 *  field in Version  C-Type (see TukVERSION).
 */
#define DukVERSION_MINOR_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 23U)

/**
 * @brief C-Constant defining the LSb of the Minor field in Version C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of Minor
 *  field in Version  C-Type (see TukVERSION).
 */
#define DukVERSION_MINOR_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the MSb of the Micro field in Version C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of Micro
 *  field in Version  C-Type (see TukVERSION).
 */
#define DukVERSION_MICRO_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the LSb of the Micro field in Version C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of Micro
 *  field in Version C-Type (see TukVERSION).
 */
#define DukVERSION_MICRO_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                 C-CONSTANTS - RELEASE CUSTOMER CONFIGURATION             */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Customer field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Customer field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_CUSTOMER_FIELD_MSb                                 \
            MukVAL_TYPED(TukBITNUM, 63U)

/**
 * @brief C-Constant defining the LSb of the Customer field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Customer field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_CUSTOMER_FIELD_LSb                                 \
            MukVAL_TYPED(TukBITNUM, 32U)

/**
 * @brief C-Constant defining the MSb of the Project field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Project field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_PROJECT_FIELD_MSb                                  \
            MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the Project field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Project field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_PROJECT_FIELD_LSb                                  \
            MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the MSb of the Revision field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Revision field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_REVISION_FIELD_MSb                                 \
            MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the LSb of the Revision field in uKernel Release
 *  Customer Configuration C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Revision field in uKernel Release Customer Configuration C-Type (see
 *  TukCUSTOMER_CONFIG).
 */
#define DukCUSTOMER_CONFIG_REVISION_FIELD_LSb                                 \
            MukVAL_TYPED(TukBITNUM, 0U)



/* //////////////////////////////////////////////////////////////////////// */
/*                  C-CONSTANTS - UKERNEL CORE dESCRIPTOR                   */
/* //////////////////////////////////////////////////////////////////////// */


/**
* @brief C-Constant defining the Magic Number identifying a uKernel Core
*  Code Descriptor.
*
* Definition of the C-Constant for the 64-bit Magic Number value that has to
*  be used as identification mark of the beginning of a uKernel Core Code
*  Descriptor structure (see TukUKERNEL_CORE_DESCRIPTOR).
*
* @implementation  The used value is the leftmost bytes of SHA256 hash of
*  'UKERNEL_CORE_DESCRIPTOR'.
*/
#define DukUKERNEL_CORE_DESCRIPTOR_MAGIC64                                    \
            MukVAL_TYPED(TukMAGIC64, 0x251074CB09D9B59CULL)



/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - UKERNEL CONFIGURATION                   */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_UKERNEL_CONFIG_CUSTOMIZABLE)

/**
* @brief C-Constant defining the Magic Number identifying a uKernel
*  Configuration Descriptor.
*
* Definition of the C-Constant for the 64-bit Magic Number value that has to
*  be used as identification mark of the beginning of a uKernel Configuration
*  Descriptor structure (see TukUKERNEL_CONFIG_DESCRIPTOR).
*
* @implementation  The used value is the leftmost bytes of SHA256 hash of
*  'UKERNEL_CONFIG_DESCRIPTOR'.
*/
#define DukUKERNEL_CONFIG_DESCRIPTOR_MAGIC64                                  \
            MukVAL_TYPED(TukMAGIC64, 0x216515E87C3651A8ULL)

#endif /* defined(SukCONFIG_FEATURE_UKERNEL_CONFIG_CUSTOMIZABLE) */



/* //////////////////////////////////////////////////////////////////////// */
/*                  C-CONSTANTS - UKERNEL SESSION - CONTEXT                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the uKernel Session Context Flag reporting a Warm
 *  MCU Reset.
 *
 * Definition of the C-Constant for the uKernel Session Context Flag reporting
 *  that a Warm MCU Reset has started the current uKernel Session.
 *
 * @implementation In order to provide reliable information, this flag is
 *  elaborated using internal RAM Magic Number, as well as hardware support in
 *  the selected MCU Device if present.
 *
 * @usage An MCU Warm Reset implies that an MCU Cold Reset (due to an MCU Power
 *  going from Off to On) has occurred previously, but not necessary upon the
 *  previous MCU Reset.
 *
 * @usage If this flag is not set, then the current uKernel Session has been
 *  started by a Cold MCU Reset.
 */
#define DukUKERNEL_SESSION_CONTEXT_MCU_RESET_WARM_FLAG                        \
                        MukVAL_TYPED_BF(TukUKERNEL_SESSION_CONTEXT, 0U)

#define DukUKERNEL_SESSION_CONTEXT_MCU_RESET_SW_FLAG                          \
                        MukVAL_TYPED_BF(TukUKERNEL_SESSION_CONTEXT, 1U)

#define DukUKERNEL_SESSION_CONTEXT_MCU_RESET_PIN_FLAG                         \
                        MukVAL_TYPED_BF(TukUKERNEL_SESSION_CONTEXT, 2U)

#define DukUKERNEL_SESSION_CONTEXT_MCU_RESET_HW_ERROR_FLAG                    \
                        MukVAL_TYPED_BF(TukUKERNEL_SESSION_CONTEXT, 3U)


/* //////////////////////////////////////////////////////////////////////// */
/*                    CONSTANTS - UKERNEL CORE - ATTRIBUTES                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant defining the base value of the Tags associated to uKernel
 *  Core Attributes.
 *
 * This Constant defines the base value of the Tags associated to the uKernel
 *  Core Attributes.
 *
 * @note This constants allows to enforce that there is no collision between
 *  the different Tags values supported by the uKernel.
 */
#define DukUKCORE_ATTRIBUTE_TAG_BASE                                          \
                        MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG, 0x10U)


/**
 * @brief Constant defining the Tag referencing the Release Version Attribute
 *  of the uKernel Core.
 *
 * This Constant defines the Tag referencing the Release Version Attribute (see
 *  TukVERSION) of the uKernel Core.
 * The Release Version of the uKernel Core corresponds to the uKernel Release
 *  Version set upon the compilation of the uKernel Core code of the used
 *  uKernel Release.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukVERSION)).
 *  - [L] V: Value = Release Version of the uKernel Core.
 *   Returned Value has C-Type TukVERSION.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @usage The uKernel Release Version retrieved using this uKernel Core
 *  Attribute SHALL BE equal to the one defined in the uKernel API used for
 *  the compilation of the ukApp (see DukRELEASE_UKERNEL_VERSION). If improper
 *  version is used, the ukApp proper execution cannot be guaranteed. However,
 *  the ukApp security properties, and notably its isolation, remain always
 *  enforced even in case an improper version is used.
 */
#define DukUKCORE_ATTRIBUTE_TAG_RELEASE_VERSION                               \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x01U)

/**
 * @brief C-Constant defining the Tag referencing the uKernel Session Context
 *  Attribute of the uKernel Core.
 *
 * Definition of the C-Constant for the Tag referencing the uKernel Session
 *  Context Attribute of the current uKernel Session executing the uKernel
 *  Core (see TukUKERNEL_SESSION_CONTEXT).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukUKERNEL_SESSION_CONTEXT)).
 *  - [L] V: Value = Value of uKernel Session Context.
 *   Returned Value has C-Type TukUKERNEL_SESSION_CONTEXT.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKERNEL_SESSION_CONTEXT                       \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x02U)

/**
 * @brief Constant defining the Tag referencing the uKernel Core Code Body
 *  SHA256-Hash Attribute of the uKernel Core.
 *
 * This Constant defines the Tag referencing the uKernel Core Code Body
 *  SHA256-Hash Attribute of the uKernel Core.
 * This Attribute consists in the SHA256 hash of the uKernel Core Code Body
 *  SHA256-Hash contained in <UKernelCoreCodeBodyBlockSHA256> field of the
 *  uKernel Core Descriptor (see TukUKERNEL_CORE_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 32 (sizeof(TukHASH_SHA256)).
 *  - [32] V: Value = SHA256-Hash value of the Code of the uKernel Core.
 *   Returned Value has C-Type TukHASH_SHA256.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 */
#define DukUKCORE_ATTRIBUTE_TAG_CODE_BODY_BLOCK_SHA256                        \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x03U)

/**
 * @brief Constant defining the Tag referencing the ukApp Code Blocks Total
 *  Size of the uKernel Core.
 *
 * This Constant defines the Tag referencing the ukApp Code Blocks Total
 *  Size of the uKernel Core.
 * The ukApp Code Blocks Total Size is computed as the sum of the sizes of each
 *  ukApps Code Block whose ukApp Descriptor is valid for the uKernel in
 *  current uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukLENGTH32)).
 *  - [4] V: Value = Value containing the ukApp Code Blocks Total Size.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG is set in the
 *    <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 *
 * @usage The ukApp Code Blocks Total Size allows to estimate the size of
 *  ukApps Bundle Code Block required by all the ukApps present in the ukApps
 *  Bundle.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKAPPS_CODE_SIZE_TOTAL                        \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x04U)

/**
 * @brief Constant defining the Tag referencing the ukApp Data Volatile Blocks
 *  Total Size of the uKernel Core.
 *
 * This Constant defines the Tag referencing the ukApp Data Volatile Blocks
 *  Total Size of the uKernel Core.
 * The ukApp Data Volatile Blocks Total Size is computed as the sum of the
 *  sizes of each ukApps Data Volatile Block whose ukApp Descriptor is valid
 *  for the uKernel in current uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukLENGTH32)).
 *  - [4] V: Value = Value containing the ukApp Data Volatile Blocks Total
 *   Size. Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG is set in the
 *    <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 *
 * @usage The ukApp Data Volatile Blocks Total Size allows to estimate the size
 *  of ukApps Bundle Data Volatile Block required by all the ukApps present in
 *  the ukApps Bundle.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKAPPS_DATA_VOLATILE_SIZE_TOTAL               \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x05U)


/**
 * @brief Constant defining the Tag referencing the ukApp Data Persistent
 *  Blocks Total Size of the uKernel Core.
 *
 * This Constant defines the Tag referencing the ukApp Data Persistent Blocks
 *  Total Size of the uKernel Core.
 * The ukApp Data Persistent Blocks Total Size is computed as the sum of the
 *  sizes of each ukApps Data Persistent Block whose ukApp Descriptor is valid
 *  for the uKernel in current uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukLENGTH32)).
 *  - [4] V: Value = Value containing the ukApp Data Persistent Blocks Total
 *   Size.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG is set in the
 *    <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 *
 * @usage The ukApp Data Persistent Blocks Total Size allows to estimate the
 *  size of ukApps Bundle Data Persistent Block required by all the ukApps
 *  present in the ukApps Bundle.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKAPPS_DATA_PERSISTENT_SIZE_TOTAL             \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x06U)

/**
 * @brief Constant defining the Tag referencing the uKernel Image Update
 *  Storage Size Attribute of the uKernel Core.
 *
 * This Constant defines the Tag referencing the uKernel Image Update Storage
 *  Size Attribute of the uKernel Core.
 *
 * The uKernel Image Update Storage Size corresponds to the maximal size of
 *  the uKernel Image Updated part (uKernel Core, ukApp, ukApps Bundle,
 *  uKernel System) that can be written in the uKernel Image Update Storage.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukLENGTH32)).
 *  - [4] V: Value = Value containing the uKernel Image Update Storage Size.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only the ukProc instantiated from the ukApp having the flag
 *  DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG set in its ukApp Profile
 *  (see <Profile> field in ukApp Descriptor).
 *  - Write: Never allowed.
 *
 * @implementation This Tag is supported only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE is supported.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKERNEL_IMAGE_UPDATE_STORAGE_SIZE             \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x07U)


/**
 * @brief Constant defining the Tag referencing the ukApps Count Attribute of
 *  the uKernel Core.
 *
 * This Constant defines the Tag referencing the ukApps Count Attribute of the
 *  uKernel Core.
 * The ukApps Count is defined as the number of ukApp Descriptors that have
 *  been declared valid during uKernel Initialization.
 * The ukApps Count remains fixed during a uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 1 (sizeof(TukCOUNT8)).
 *  - [L] V: Value = Value containing the Count of valid ukApps.
 *   Returned Value has C-Type TukCOUNT8.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG is set in the
 *    <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 *
 * @implementation The returned ukApps Count is always in the range
 *  [ 1 ... DukCONFIG_OPTION_UKAPP_COUNT_MAX ].
 *
 * @usage A ukApp Index (AIDX) value is valid if in the range
 *  [ 0 ... (<ukapps_count> - 1) ], where <ukapps_count> is the value returned
 *  by this uKernel Core Attribute.
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKAPPS_COUNT                                  \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x08U)

/**
 * @brief Constant defining the Tag referencing the ukProcs Count Attribute of
 *  the uKernel Core.
 *
 * This Constant defines the Tag referencing the ukProcs Count Attribute of the
 *  uKernel Core.
 * The ukProcs Count is defined as the current count of ukProcs created (
 *  without counting the virtual ukProc Idle).
 * This count may vary during a uKernel Session, in function of the new ukProcs
 *  created (see ukUKProcInstantiate()) and of the ukProc having been
 *  terminated (see ukProc Termination).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 1 (sizeof(TukCOUNT8)).
 *  - [L] V: Value = Value containing the current count of ukProcs.
 *   Returned Value has C-Type TukCOUNT8.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG is set in the
 *    <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 *
 * @implementation The count returned is never null, as at least the current
 *  ukProc being executed is created ;-).
 *
 * @implementation The returned current count of ukProcs is always in the
 *  range [ 1 ... DukCONFIG_OPTION_UKPROC_COUNT_MAX ].
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKPROCS_COUNT                                 \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x09U)


/**
 * @brief Constant defining the Tag referencing the uKernel Systick Period
 *  Attribute of the uKernel Core.
 *
 * This Constant defines the Tag referencing the uKernel Systick Period
 *  Attribute, in microseconds(us) unit, of the uKernel Core.
 * The uKernel Systick period initial value is defined by the uKernel Option
 *  DukCONFIG_OPTION_UKERNEL_SYSTICK_PERIOD_DEFAULT_us.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukTIME32_us)).
 *  - [L] V: Value = Value of the uKernel Systick Period in microseconds (us).
 *   Returned Value has C-Type TukTIME32_us.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 */
#define DukUKCORE_ATTRIBUTE_TAG_SYSTICK_PERIOD_us                             \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x0A)


/**
 * @brief C-Constant defining the Tag referencing the Platform Attribute Access
 *  Key Attribute of the uKernel Core.
 *
 * Definition of the C-Constant for the Tag referencing the Platform Attribute
 *  Access Key Attribute of the uKernel Core.
 * This Access Key value is required for granting usage of the uKernel
 *  Privileged Service for updating a Platform Attribute (MCU Clocks Set Index
 *  used, changing Platform State, ...).
 * This Access Key value is randomly updated upon each new uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukACCESSKEY32)).
 *  - [L] V: Value = Value of Access Key.
 *   Returned Value has C-Type TukACCESSKEY32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @usage This Key values is required to use the following uKernel Privileged
 *  Services:
 *  - ukPlatformSetAttribute().
 */
#define DukUKCORE_ATTRIBUTE_TAG_PLATFORM_ATTRIBUTE_ACCESSKEY                  \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x0B)


/**
 * @brief C-Constant defining the Tag referencing the MCU Register Access
 *  Key Attribute of the uKernel Core.
 *
 * Definition of the C-Constant for the Tag referencing the MCU Register Access
 *  Key Attribute of the uKernel Core.
 * This Access Key value is required for granting usage of the uKernel
 *  Privileged Services dedicated to MCU Register accesses.
 * This Access Key value is randomly updated upon each new uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukACCESSKEY32)).
 *  - [L] V: Value = Value of Access Key.
 *   Returned Value has C-Type TukACCESSKEY32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @usage This Key values is required to use the following uKernel Privileged
 *  Services:
 *  - ukMCURegisterRead().
 *  - ukMCURegisterWrite().
 */
#define DukUKCORE_ATTRIBUTE_TAG_MCUREGISTER_ACCESSKEY                         \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x0C)

/**
 * @brief C-Constant defining the Tag referencing the Persistent Memory Access
 *  Key Attribute of the uKernel Core.
 *
 * Definition of the C-Constant for the Tag referencing the Persistent Memory
 *  Access Key Attribute of the uKernel Core.
 * This Access Key value is required for granting usage of the uKernel
 *  Privileged Services dedicated to Persistent Memory management.
 * This Access Key value is randomly updated upon each new uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukACCESSKEY32)).
 *  - [L] V: Value = Value of Access Key.
 *   Returned Value has C-Type TukACCESSKEY32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @implementation This Tag is supported only if uKernel Feature
 *  SukCONFIG_FEATURE_UKAPP_DATA_PERSISTENT_BLOCK is supported.
 *
 * @usage This Key values is required to use the following uKernel Privileged
 *  Services:
 *  - ukPersistentDataBlockEraseSector().
 *  - ukPersistentDataBlockRead().
 *  - ukPersistentDataBlockWrite().
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKAPP_DATA_PERSISTENT_BLOCK_ACCESSKEY         \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x0D)

/**
 * @brief C-Constant defining the Tag referencing the uKernel Image Update
 *  Access Key Attribute of the uKernel Core.
 *
 * Definition of the C-Constant for the Tag referencing the uKernel Image
 *  Update Access Key Attribute of the uKernel Core.
 * This Access Key value is required for granting usage of the uKernel
 *  Privileged Services dedicated to uKernel Image Update management.
 * This Access Key value is randomly updated upon each new uKernel Session.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4 (sizeof(TukACCESSKEY32)).
 *  - [L] V: Value = Value of Access Key.
 *   Returned Value has C-Type TukACCESSKEY32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only the ukProc instantiated from the ukApp having the flag
 *  DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG set in its ukApp Profile
 *  (see <Profile> field in ukApp Descriptor).
 *  - Write: Never Allowed.
 *
 * @implementation This Tag is supported only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE is supported.
 *
 * @usage This Key values is required to use the following uKernel Privileged
 *  Services:
 *  - ukUKImageUpdateEraseSector().
 *  - ukUKImageUpdateWrite().
 *  - ukUKImageUpdateRead().
 *  - ukUKImageUpdateOperate().
 */
#define DukUKCORE_ATTRIBUTE_TAG_UKERNEL_IMAGE_UPDATE_ACCESSKEY                \
                            MukVAL_TYPED(TukUKCORE_ATTRIBUTE_TAG,             \
                                         DukUKCORE_ATTRIBUTE_TAG_BASE + 0x0E)


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - MCU IDENTIFIER                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Manufacturer field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Manufacturer field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_MANUFACTURER_FIELD_MSb      MukVAL_TYPED(TukBITNUM, 127U)

/**
 * @brief C-Constant defining the LSb of the Manufacturer field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Manufacturer field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_MANUFACTURER_FIELD_LSb      MukVAL_TYPED(TukBITNUM, 96U)

/**
 * @brief C-Constant defining the MSb of the Family field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant for the MSb (Most Significant bit) of the
 *  Family field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_FAMILY_FIELD_MSb            MukVAL_TYPED(TukBITNUM, 95U)

/**
 * @brief C-Constant defining the LSb of the Family field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant for the LSb (Less Significant bit) of the
 *  Family field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_FAMILY_FIELD_LSb            MukVAL_TYPED(TukBITNUM, 64U)

/**
 * @brief C-Constant defining the MSb of the Reference field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Reference field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_REFERENCE_FIELD_MSb         MukVAL_TYPED(TukBITNUM, 63U)

/**
 * @brief C-Constant defining the LSb of the Reference field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Reference field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_REFERENCE_FIELD_LSb         MukVAL_TYPED(TukBITNUM, 32U)

/**
 * @brief C-Constant defining the MSb of the Revision field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Revision field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_REVISION_FIELD_MSb          MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the Revision field in MCU
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Revision field in MCU Identifier C-Type (see TukMCU_ID_bv).
 */
#define DukMCU_ID_REVISION_FIELD_LSb          MukVAL_TYPED(TukBITNUM, 0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                     C-CONSTANTS - PLATFORM IDENTIFIER                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Designer field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Designer field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_MANUFACTURER_FIELD_MSb      MukVAL_TYPED(TukBITNUM, 127U)

/**
 * @brief C-Constant defining the LSb of the Designer field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Designer field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_MANUFACTURER_FIELD_LSb      MukVAL_TYPED(TukBITNUM, 96U)

/**
 * @brief C-Constant defining the MSb of the Family field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Family field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_FAMILY_FIELD_MSb           MukVAL_TYPED(TukBITNUM, 95U)

/**
 * @brief C-Constant defining the LSb of the Family field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Family field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_FAMILY_FIELD_LSb           MukVAL_TYPED(TukBITNUM, 64U)

/**
 * @brief C-Constant defining the MSb of the Reference field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Reference field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_REFERENCE_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 63U)

/**
 * @brief C-Constant defining the LSb of the Reference field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Reference field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_REFERENCE_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 32U)

/**
 * @brief C-Constant defining the MSb of the Option field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Option field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_OPTION_FIELD_MSb           MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the Option field in Platform
 *  Identifier C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Option field in Platform Identifier C-Type (see TukPLATFORM_ID_bv).
 */
#define DukPLATFORM_ID_OPTION_FIELD_LSb           MukVAL_TYPED(TukBITNUM, 0U)



/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - PLATFORM - STATE                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Nominal Platform State.
 *
 * Definition of the C-Constant for the Nominal Platform State.
 *
 * @implementation The Nominal Platform State corresponds to the default state
 *  for the MCU and peripherals as expected by the developer in regards of
 *  provided execution configuration environment.
 */
#define DukPLATFORM_STATE_NOMINAL                                             \
                        MukVAL_TYPED(TukPLATFORM_STATE, 0x0001UL)


/**
 * @brief C-Constant defining the Platform State request for an MCU Reset.
 *
 * Definition of the C-Constant for the Platform State request for an MCU Reset.
 *
 * @implementation Once an MCU Reset request has been performed, the uKernel
 *  triggers a uKernel Session End, and then an MCU Reset in software.
 *  A new uKernel Session will start immediately afterwards.
 */
#define DukPLATFORM_STATE_REQUEST_MCU_RESET                                   \
                        MukVAL_TYPED(TukPLATFORM_STATE, 0xA000UL)

/**
 * @brief C-Constant defining the Platform State request for an MCU Halt.
 *
 * Definition of the C-Constant for the Platform State request for an MCU Halt.
 *
 * @implementation Once an MCU Halt request has been performed, the uKernel
 *  triggers a uKernel Session End, and then an MCU Halt in software. An
 *  external reset signal sent to the MCU will then be necessary to start a new
 *  uKernel Session. Till then, the MCU will remain halted.
 */
#define DukPLATFORM_STATE_REQUEST_MCU_HALT                                    \
                        MukVAL_TYPED(TukPLATFORM_STATE, 0xC000UL)



/* //////////////////////////////////////////////////////////////////////// */
/*                     C-CONSTANTS - PLATFORM - ATTRIBUTES                  */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the base value of the Tags associated to Hardware
 *  Platform Attributes.
 *
 * This Constant defines the base value of the Tags associated to the Hardware
 *  Platform Attributes.
 *
 * @note This constants allows to enforce that there is no collision between
 *  the different Tags values supported by the uKernel.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_BASE                                        \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG, 0x40U)

/**
 * @brief C-Constant defining the Tag referencing the MCU Identifier Attribute
 *  of the Platform.
 *
 * This Constant defines the Tag referencing the MCU Identifier Attribute (see
 *  TukMCU_ID_bv) of the Platform.
 * The MCU Identifier of the Platform is retrieved during the very
 *  first uKernel Initialization from the production information written by
 *  the chip manufacturer. The uKernel will enforce during its next
 *  initializations that the MCU Identifier stays the same (else it will
 *  trigger a uKernel FATAL Error).
 * The MCU Identifier contains all the information allowing to identify the
 *  manufacturer, the family, the core architecture, and precise reference
 *  of the MCU (see TukMCU_ID_bv for more details).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukMCU_ID_bv).
 *  - [L] V: Value = MCU Identifier on which uKernel is executed.
 *   Returned Value has C-Type TukMCU_ID_bv.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @note If the MCU Identifier is not compatible with the uKernel Release, then
 *  the uKernel will trigger a Fatal Error during its Initialization (and thus
 *  no ukProc will be able to execute and retrieve the value using
 *  this Tag). This is done on purpose to enforce that the uKernel can
 *  guarantee the security property and defined security policy.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_MCU_ID                                      \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x01U)

/**
 * @brief C-Constant defining the Tag referencing the CPU Core Attribute of
 *  the Platform.
 *
 * This Constant defines the Tag referencing the CPU Core Attribute (see
 *  TukCPU_CORE_ID) of the Platform.
 * The CPU Core of the Platform is retrieved during the very
 *  first uKernel Initialization from the production information written by
 *  the chip manufacturer. The uKernel will enforce during its next
 *  initializations that the CPU Core stays the same (else it will
 *  trigger a uKernel FATAL Error).
 * The CPU Core contains all the information allowing to identify the
 *  manufacturer, architecture, and revision of the CPU Core (see
 *  TukCPU_CORE_ID for more details).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukCPU_CORE_ID).
 *  - [L] V: Value = CPU Core Identifier on which uKernel is executed.
 *   Returned Value has C-Type TukCPU_CORE_ID.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_CPU_CORE_ID                                 \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x02U)

/**
 * @brief C-Constant defining the Tag referencing the Platform Identifier
 *  Attribute of the Platform.
 *
 * This Constant defines the Tag referencing the Platform Identifier
 *  Attribute (see TukPLATFORM_ID_bv) of the Platform.
 * The Platform Identifier of the Platform is retrieved
 *  during the very first uKernel Initialization from the production
 *  information written by the chip and board manufacturer. The uKernel will
 *  enforce during its next initializations that the MCU Identifier stays
 *  the same (else it will trigger a uKernel FATAL Error).
 * The Platform Identifier contains all the information allowing to
 *  identify the manufacturer, and precise reference of the board (see
 *  TukPLATFORM_ID_bv for more details).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukPLATFORM_ID_bv).
 *  - [L] V: Value = Platform Identifier.
 *   Returned Value has C-Type TukPLATFORM_ID_bv.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @note If the Platform Identifier is not compatible with the uKernel
 *  Release, then the uKernel will trigger a Fatal Error during its
 *  Initialization (and thus no ukProc will be able to execute and
 *  retrieve the value using this Tag). This is done on purpose to enforce that
 *  the uKernel can guarantee the security property and defined security
 *  policy.
 *
 * @note On some Platform, it may not be possible to retrieve the
 *  necessary information to properly identify the Platform: in that
 *  case, the uKernel Release may have been compiled to allow such situation
 *  and not perform any check on the Platform. The security policy
 *  relies then on the production policy that the right uKernel Release has
 *  been chosen for this Platform.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PLATFORM_ID                                 \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x03U)


/**
 * @brief C-Constant defining the Tag referencing the Serial Number Attribute
 *  of the Platform.
 *
 * This Constant defines the Tag referencing the Serial Number Attribute of
 *  the Platform.
 * The Serial Number of the Platform is retrieved during the very
 *  first uKernel Initialization from the production information written by
 *  the chip and board manufacturer. The uKernel will enforce during its next
 *  initializations that the Serial Number stays the same (else it is a
 *  uKernel FATAL Error).
 * If the Platform does not embed production information which allows
 *  to compute an unique Serial Number, then the uKernel will use a random
 *  value as Serial Number (the 128-bit size of the Serial Number making
 *  collision statistically improbable, and thus providing good guarantee on
 *  the unicity of this random Serial Number). In case no random generator
 *  with enough entropy is present on the Platform, then this
 *  Attribute will be reported as not supported.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 16.
 *  - [16] V: Value = 128-bit Serial Number.
 *   Returned Value has C-Type TukSERIALNUMBER128_bv.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only ukProc whose DukUKAPP_PROFILE_PLATFORM_CONFIG_GET_FLAG is set
 *   in the <Profile> field of the ukApp Descriptor of its ukApp.
 *  - Write: Never Allowed.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_SERIAL_NUMBER                               \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x04U)

/**
 * @brief C-Constant defining the Tag referencing the Persistent Memory Size
 *  Attribute of the Platform.
 *
 * This Constant defines the Tag referencing the Persistent Memory Size
 *  Attribute of the Platform.
 * The Persistent Memory Size Attribute of the Platform corresponds
 *  to the amount of persistent memory (FLASH in general) that may be available
 *  to and fully under control of the uKernel Core on the Hardware Platform.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [4] V: Value = Persistent Memory Size (in bytes) usable by the uKernel
 *   on the Platform.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @note The Persistent Memory returned here is the one that can be used for
 *  storing code and data of the uKernel and of ukApps, and that is fully under
 *  access rights control of the MPU of the MCU used by the uKernel.
 *  In general, the Persistent Memory Size corresponds to the amount of
 *  internal MCU FLASH memory, and is used mainly for storing the Code Blocks
 *  and Data Persistent Blocks. It does not takes into account additional
 *  memory that may be accessible through dedicated I/O interface.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_MEMORY_PERSISTENT_SIZE                      \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x05U)

/**
 * @brief C-Constant defining the Tag referencing the Volatile Memory Size
 *  Attribute of the Platform.
 *
 * This Constant defines the Tag referencing the Volatile Memory Size
 *  Attribute of the Platform.
 * The Volatile Memory Size Attribute of the Platform corresponds to the amount
 *  of volatile memory (RAM in general) that may be available to and fully
 *  under control of the uKernel Core on the Platform.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [4] V: Value = Volatile Memory Size (in bytes) usable by the uKernel
 *   on the Platform.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @note The Volatile Memory returned here is the one that can be used for
 *  storing code and data of the uKernel and of ukApps, and that is fully under
 *  access rights control of the MPU of the MCU used by the uKernel.
 *  In general, the Volatile Memory Size corresponds to the amount of
 *  internal MCU RAM memory, and is used mainly for storing the Data Volatile
 *  Blocks. It does not takes into account additional memory that may be
 *  accessible through dedicated I/O interface.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_MEMORY_VOLATILE_SIZE                        \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x06U)


/**
 * @brief C-Constant defining the Tag referencing the State Attribute of the
 *  Platform.
 *
 * This Constant defines the Tag referencing the State Attribute of the
 *  Platform.
 * The State Attribute of the Platform allows to retrieve information on the
 *  current state of the Platform by reading it, and to perform action on it
 *  by writing it (see TukPLATFORM_STATE for more information).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukPLATFORM_STATE).
 *  - [L] V: Value = (TukPLATFORM_STATE) Platform State.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Only if ukApp has been granted with Platform Attributes Set
 *   Credentials (see DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG).
 *
 * The following conditions apply when writing this Platform Attribute Tag:
 *  - The following Platform States can be set only if the current Platform
 *   State is DukPLATFORM_STATE_NOMINAL
 *     -- DukPLATFORM_STATE_REQUEST_MCU_RESET.
 *     -- DukPLATFORM_STATE_REQUEST_MCU_HALT.
 *  - The following Status Code may be returned when writing this Platform
 *   Attribute Tag:
 *     -- DukSTATUS_WARN_ALREADY The given Platform State is already the
 *       current one.
 *     -- DukSTATUS_ERR_PARAM The given Platform State is invalid.
 *     -- DukSTATUS_ERR_STATE_INVALID The current Platform State is
 *       incompatible with the new one given.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_STATE                                       \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x10U)

/**
 * @brief C-Constant defining the Tag referencing the MCU Clocks Set Index
 *  Attribute used by the Platform.
 *
 * This Constant defines the Tag referencing the MCU Clocks Set Index
 *  Attribute used by the Platform.
 * The MCU Clocks Set Index (see TukMCU_CLOCKS_SET_IDX) corresponds to the
 *  index in the uKernel Configuration list containing the defined MCU Clocks
 *  Set (see DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_LIST for the default one).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukMCU_CLOCKS_SET_IDX).
 *  - [L] V: Value = (TukMCU_CLOCKS_SET_IDX)MCU Clocks Set Index.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Only if ukApp has been granted with Platform Attributes Set
 *   Credentials (see DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG) and if uKernel
 *   Feature SukCONFIG_FEATURE_UKPROC_MCU_CLOCKS_SET_UPDATABLE is supported.
 *
 * The following conditions apply when writing this Platform Attribute Tag:
 *  - The following Status Code may be returned when writing this Platform
 *   Attribute Tag:
 *    + DukSTATUS_WARN_ALREADY The given index <cpu_clock_param_idx__i> is
 *      referencing the MCU Clocks Set already in use.
 *    + DukSTATUS_ERR_PARAM The given index <cpu_clock_param_idx__i> is
 *      invalid (not in range
 *      [0... (DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_COUNT-1)]).
 *    + DukSTATUS_ERR_UKERNEL_CONFIG The new resulting CPU Core Clock
 *      frequency does not allow reconfiguration of hardware to keep current
 *      uKernel Systick period constant.
 *    + DukSTATUS_ERR_UKERNEL_CONFIG The parameters of referenced MCU Clocks
 *      Set are invalid or inconsistent in regards of used MCU and Platform.
 *    + DukSTATUS_ERR_HW_STATE The hardware state after configuration with
 *      referenced MCU Clocks Set is unexpected and prevents the hardware to
 *      support configured uKernel Systick period.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX                          \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x11U)

/**
 * @brief C-Constant defining the Tag referencing the CPU Core Clock Frequency
 *  Attribute of the Platform.
 *
 * This Constant defines the Tag referencing the CPU Core Clock Frequency
 *  Attribute of the Platform.
 * The CPU Core Clock Frequency may be updated by either:
 *  - The uKernel when entering uKernel Low Power Mode.
 *  - A ukProc with Platform Configuration credentials (see
 *   DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukFREQ32_hz).
 *  - [L] V: Value = Frequency of CPU Core Clock in Hertz (Hz).
 *   Returned Value has C-Type TukFREQ32_hz.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 *  - Write: Never allowed.
 *
 * @note The accuracy of the returned value depends of the Platform (some
 *  Platform may not guarantee high accuracy for CPU Core Clock, notably in
 *  regards of temperature variation, usage of external quartz, ...).
 */
#define DukPLATFORM_ATTRIBUTE_TAG_CPU_CLOCK_Hz                                \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x12U)

/**
 * @brief C-Constant defining the Tag referencing the PSA version of the image.
 *
 * This Constant defines the Tag referencing the PSA version of the image.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 8
 *  - [L] V: Value = Copy of the version structure of the MCUBoot header.
 *    - MAJOR (uint8_t)
 *    - MINOR (uint8_t)
 *    - REVISION (uint16_t)
 *    - BUILD NUM (uint32_t)
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_PARTITION_MANAGER_VERSION               \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x14U)

/**
 * @brief C-Constant defining the Tag referencing the PSA version of the
 *  application root of trust images.
 *
 * This Constant defines the Tag referencing the PSA version of the
 *  application root of trust images.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 32
 *  - [L] V: Value = Copy of the version structure of the MCUBoot header.
 *    - MODULE0 MAJOR (uint8_t)
 *    - MODULE0 MINOR (uint8_t)
 *    - MODULE0 REVISION (uint16_t)
 *    - MODULE1 MAJOR (uint8_t)
 *    - MODULE1 MINOR (uint8_t)
 *    - MODULE1 REVISION (uint16_t)
 *      [...]
 *    - MODULE7 MAJOR (uint8_t)
 *    - MODULE7 MINOR (uint8_t)
 *    - MODULE7 REVISION (uint16_t)
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_APPLICATION_ROT_VERSIONS                \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x15U)

/**
 * @brief C-Constant defining the Tag referencing the PSA version of the
 *  non-secure processing environment images.
 *
 * This Constant defines the Tag referencing the PSA version of the non-
 *  secure processing environment images.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 32
 *  - [L] V: Value = Copy of the version structure of the MCUBoot header.
 *    - MODULE0 MAJOR (uint8_t)
 *    - MODULE0 MINOR (uint8_t)
 *    - MODULE0 REVISION (uint16_t)
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Always allowed.
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_NSPE_VERSION                            \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x16U)

/**
 * @brief C-Constant defining the Tag for the PSA Firmware Update Root of
 *  Trust to cause a reboot.
 *
 * This Constant defines the Tag for the PSA Firmware Update Root of Trust
 *  to cause a reboot.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 0
 *  - [L] V: Value = -
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Write: Only allowed for PSA FU RoT
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_FU_REBOOT                               \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x17U)

/**
 * @brief C-Constant defining the Tag for the PSA Firmware Update Root of
 *  Trust to write data to flash.
 *
 * This Constant defines the Tag for the PSA Firmware Update Root of Trust
 *  to write data to flash.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 12
 *  - [L] V: Value = 3 words
 *    - Destination, address in flash
 *    - Source, address within a shared buffer
 *    - Size, in bytes
 *
 * This API only allows writing in secondary slots or within the last 32 bytes
 *  of a primary slot.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Write: Only allowed for PSA FU RoT
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_FU_WRITE                                \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x18U)


/**
 * @brief C-Constant defining the Tag for the PSA Firmware Update Root of
 *  Trust to read data from flash.
 *
 * This Constant defines the Tag for the PSA Firmware Update Root of Trust
 *  to read data from flash.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 12
 *  - [L] V: Value = 3 words
 *    - Destination, address within a shared buffer
 *    - Source, address in flash
 *    - Size, in bytes
 *
 * This API only allows reading in secondary slots or within the last 32 bytes
 *  of a primary slot.
 *
 * The access rights of the Attribute referenced by this Tag are as follows:
 *  - Read: Only allowed for PSA FU RoT
 */
#define DukPLATFORM_ATTRIBUTE_TAG_PSA_FU_READ                                 \
                        MukVAL_TYPED(TukPLATFORM_ATTRIBUTE_TAG,               \
                                     DukPLATFORM_ATTRIBUTE_TAG_BASE + 0x19U)


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - UKAPP DESCRIPTOR                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
* @brief C-Constant defining the Magic Number identifying a ukApp Descriptor.
*
* Definition of the C-Constant for the 64-bit Magic Number value that has to
*  be used as identification mark of the beginning of a ukApp Descriptor
*  structure (see TukUKAPP_DESCRIPTOR).
*
* @implementation  The used value is the leftmost bytes of SHA256 hash of
*  'UKAPP_DESCRIPTOR_ENTRY'.
*/
#define DukUKAPP_DESCRIPTOR_MAGIC64                                           \
            MukVAL_TYPED(TukMAGIC64, 0x0B908057E8E24FD1ULL)

/**
 * @brief C-Constant defining the valid mask of the Version of the uKernel
 *  Release in ukApp Descriptor.
 *
 * Definition of the C-Constant for the valid mask of the Version (see
 *  TukVERSION) of the uKernel Release in ukApp Descriptor given in
 *  <ReleaseuKernelVersion> field.
 * The valid mask allows to check which fields of the Version shall be exactly
 *  the same to validate a ukApp Descriptor.
 *
 * @usage A ukApp Descriptor is valid if the value of its field
 *  <ReleaseuKernelVersion> is as follows:
 *  - Fields <Major> and <Minor> shall be equal to the ones of the Version of
 *   the uKernel Release used.
 *  - Field <Micro> shall be lower or equal to the one of the Version of
 *   the uKernel Release used.
 *
 * @implementation The Version of the uKernel Release used is defined in
 *  DukRELEASE_UKERNEL_VERSION.
 */
#define DukUKAPP_DESCRIPTOR_RELEASE_UKERNEL_VERSION_VALID_MASK                \
    MukVAL_TYPED(TukVERSION,                                                  \
            MukVAL_FIELD_BITMASK32(                                           \
                    DukVERSION_MAJOR_FIELD_LSb,                               \
                    DukVERSION_MAJOR_FIELD_MSb) |                             \
            MukVAL_FIELD_BITMASK32(                                           \
                    DukVERSION_MINOR_FIELD_LSb,                               \
                    DukVERSION_MINOR_FIELD_MSb)                               \
                )


/**
 * @brief C-Constant defining the valid mask of the Customer Configuration of
 *  the uKernel Release in ukApp Descriptor.
 *
 * Definition of the C-Constant for the valid mask of the Customer
 *  Configuration (see TukCUSTOMER_CONFIG) of the uKernel Release in ukApp
 *  Descriptor given in <ReleaseCustomerConfiguration> field.
 * The valid mask allows to check which fields of the Customer Configuration
 *  shall be exactly the same to validate a ukApp Descriptor.
 *
 * @usage A ukApp Descriptor is valid if the value of its field
 *  <ReleaseuKernelVersion> is as follows:
 *  - Fields <Customer> and <Project> shall be equal to the ones of the
 *   Customer Configuration of the uKernel Release used.
 *  - Field <Revision> shall be lower or equal to the one of the Customer
 *   Configuration of the uKernel Release used.
 *
 * @implementation The Customer Configuration of the uKernel Release used is
 *  defined in DukRELEASE_CUSTOMER_CONFIG.
 */
#define DukUKAPP_DESCRIPTOR_RELEASE_CUSTOMER_CONFIG_VALID_MASK                \
    MukVAL_TYPED(TukCUSTOMER_CONFIG,                                          \
            MukVAL_FIELD_BITMASK64(                                           \
                    DukCUSTOMER_CONFIG_CUSTOMER_FIELD_LSb,                    \
                    DukCUSTOMER_CONFIG_CUSTOMER_FIELD_MSb) |                  \
            MukVAL_FIELD_BITMASK64(                                           \
                    DukCUSTOMER_CONFIG_PROJECT_FIELD_LSb,                     \
                    DukCUSTOMER_CONFIG_PROJECT_FIELD_MSb)                     \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - UKAPP BLOCK                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Magic Number for a Memory Barrier in a ukApp
 *  Code Block.
 *
 * Definition of the C-Constant for a 32-bit Magic Number value marking a
 *  Memory Barrier (i.e. 'canary') in a ukApp Code Block.
 *
 * @robustness The value of this Magic Number has been chosen to have
 *  statistically low occurrence, either as meaningful or as random value.
 */
#define DukUKAPP_BLOCK_CODE_BARRIER_MAGIC32                                   \
            MukVAL_TYPED(TukMAGIC32, 0xA55A5AA5UL)


/**
 * @brief C-Constant defining the Magic Number for a Memory Barrier in a ukApp
 *  Data Block.
 *
 * Definition of the C-Constant for a 32-bit Magic Number value marking a
 *  Memory Barrier (i.e. 'canary') in a ukApp Data Block.
 *
 * @robustness The value of this Magic Number has been chosen to have
 *  statistically low occurrence, either as meaningful or as random value.
 */
#define DukUKAPP_BLOCK_DATA_BARRIER_MAGIC32                                   \
            MukVAL_TYPED(TukMAGIC32, 0x96696996UL)



/**
 * @brief C-Constant defining the Magic Number for a Memory Barrier for ukApp
 *  Heap Block.
 *
 * Definition of the C-Constant for a 32-bit Magic Number value marking a
 *  Memory Barrier (i.e. 'canary') for ukApp Heap Block.
 *
 * @robustness The value of this Magic Number has been chosen to have
 *  statistically low occurrence, either as meaningful or as random value.
 */
#define DukUKAPP_BLOCK_HEAP_BARRIER_MAGIC32                                   \
            MukVAL_TYPED(TukMAGIC32, 0x1EE11EE1UL)


/**
 * @brief C-Constant defining the Magic Number for a Memory Barrier for ukApp
 *  Stack Block.
 *
 * Definition of the C-Constant for a 32-bit Magic Number value marking a
 *  Memory Barrier (i.e. 'canary') for ukApp Stack Block.
 *
 * @robustness The value of this Magic Number has been chosen to have
 *  statistically low occurrence, either as meaningful or as random value.
 */
#define DukUKAPP_BLOCK_STACK_BARRIER_MAGIC32                                  \
            MukVAL_TYPED(TukMAGIC32, 0xF11FF11FUL)


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - UKAPP ASID                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Developer field in AUID C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Developer field in ukApp Unique Identifier (AUID) C-Type (see
 *  TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_DEVELOPER_FIELD_MSb      MukVAL_TYPED(TukBITNUM, 63U)

/**
 * @brief C-Constant defining the LSb of the Developer field in AUID C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Developer field in ukApp Unique Identifier (AUID) C-Type (see
 *  TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_DEVELOPER_FIELD_LSb      MukVAL_TYPED(TukBITNUM, 48U)

/**
 * @brief C-Constant defining the MSb of the Reference field in AUID C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Reference field in ukApp Unique Identifier (AUID) C-Type (see
 *  TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_REFERENCE_FIELD_MSb      MukVAL_TYPED(TukBITNUM, 47U)

/**
 * @brief C-Constant defining the LSb of the Reference field in AUID C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Reference field in ukApp Unique Identifier (AUID) C-Type (see
 *  TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_REFERENCE_FIELD_LSb      MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the MSb of the ASID field in AUID C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  ASID field in ukApp Unique Identifier (AUID) C-Type (see TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_ASID_FIELD_MSb           MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the LSb of the ASID field in AUID C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  ASID field in ukApp Unique Identifier (AUID) C-Type (see TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_ASID_FIELD_LSb           MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the bitmask for the ASID field in AUID C-Type.
 *
 * Definition of the C-Constant for the bitmask of significant bits of the
 *  ASID field in ukApp Unique Identifier (AUID) C-Type (see TukUKAPP_AUID).
 */
#define DukUKAPP_AUID_ASID_FIELD_MASK                                         \
    MukVAL_TYPED(TukUKAPP_AUID,                                               \
                 MukVAL_FIELD_BITMASK32(DukUKAPP_AUID_ASID_FIELD_LSb,         \
                                      DukUKAPP_AUID_ASID_FIELD_MSb            \
                                 )                                            \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - UKAPP ASID                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the bitmask for the set of special reserved
 *  values for ASID.
 *
 * Definition of the C-Constant for the bitmask identifying the set of ukApp
 *  Short Identifier (ASID) special reserved values.
 *
 * The following ASID special reserved values are supported:
 *  - DukUKAPP_ASID_INVALID
 *  - DukUKAPP_ASID_ANY
 *  - DukUKAPP_ASID_NONE
 *  - DukUKAPP_ASID_UKERNEL
 *
 * @implementation An AUID value is invalid if its ASID field is part of the
 *  set of special reserved values.
 *
 * @usage An ASID value <asid> is part of the set of special reserved values
 *  if the following statement is true:
 *      (<asid> & DukUKAPP_ASID_RESERVED_MASK) == DukUKAPP_ASID_RESERVED_MASK
 */
#define DukUKAPP_ASID_RESERVED_MASK     MukVAL_TYPED(TukUKAPP_ASID, 0xFFF0U)

/**
 * @brief C-Constant defining an invalid value to be used for ASID.
 *
 * Definition of the C-Constant for the invalid value to be used for ukApp
 *  Short Identifier (ASID).
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukUKAPP_ASID_INVALID           MukVAL_TYPED(TukUKAPP_ASID,           \
            DukUKAPP_ASID_RESERVED_MASK | 0xFU)

/**
 * @brief C-Constant defining the special reserved value for ASID to be used
 *  for indicating that any ukApp may be implied.
 *
 * Definition of the C-Constant for the ukApp Short Identifier (ASID) special
 *  reserved value to be used for indicating that any ukApp part of the ukApp
 *  Bundle may be implied.
 */
#define DukUKAPP_ASID_ANY               MukVAL_TYPED(TukUKAPP_ASID,           \
            DukUKAPP_ASID_RESERVED_MASK | 0xEU)

/**
 * @brief C-Constant defining the special reserved value for ASID to be used
 *  for indicating that no ukApp is implied.
 *
 * Definition of the C-Constant for the ukApp Short Identifier (ASID) special
 *  reserved value to be used for indicating that no ukApp is implied or
 *  referenced.
 */
#define DukUKAPP_ASID_NONE              MukVAL_TYPED(TukUKAPP_ASID,           \
            DukUKAPP_ASID_RESERVED_MASK | 0xDU)

/**
 * @brief C-Constant defining the special reserved value for ASID to be used
 *  for indicating that uKernel entity is in charge.
 *
 * Definition of the C-Constant for the ukApp Short Identifier (ASID) special
 *  reserved value to be used for indicating that uKernel entity is in charge.
 */
#define DukUKAPP_ASID_UKERNEL           MukVAL_TYPED(TukUKAPP_ASID,           \
                    DukUKAPP_ASID_RESERVED_MASK | 0xCU)



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - UKAPP INDEX                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the bitmask for the set of special reserved
 *  values for AIDX.
 *
 * Definition of the C-Constant for the bitmask identifying the set of ukApp
 *  Index (AIDX) special reserved values.
 *
 * The following AIDX special reserved values are supported:
 *  - DukUKAPP_AIDX_MYSELF
 *  - DukUKAPP_AIDX_INVALID
 *
 * @usage An AIDX value <aidx> is part of the set of special reserved values
 *  if the following statement is true:
 *      (<aidx> & DukUKAPP_AIDX_RESERVED_MASK) == DukUKAPP_AIDX_RESERVED_MASK
 */
#define DukUKAPP_AIDX_RESERVED_MASK         MukVAL_TYPED(TukUKAPP_AIDX, 0xF0U)

/**
 * @brief C-Constant defining an invalid value to be used for ukApp Index
 *  (AIDX).
 *
 * Definition of the C-Constant for the invalid value to be used for ukApp
 *  Index (AIDX).
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukUKAPP_AIDX_INVALID                                                 \
                        MukVAL_TYPED(TukUKAPP_AIDX,                           \
                                     (DukUKAPP_AIDX_RESERVED_MASK | 0x0FU))

/**
 * @brief C-Constant defining the special reserved value to be used for ukApp
 *  Index (AIDX) for referring current ukApp.
 *
 * Definition of the C-Constant for the special reserved value to be used for
 *  ukApp Index (AIDX) for referring the current ukApp, which is the one from
 *  which is instantiated currently executed ukProc.
 */
#define DukUKAPP_AIDX_MYSELF                                                  \
                        MukVAL_TYPED(TukUKAPP_AIDX,                           \
                                     (DukUKAPP_AIDX_RESERVED_MASK | 0x0BU))



/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - UKAPP PROFILE                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the ukApp Profile flag for an ukProc Creation
 *  upon uKernel Initialization.
 *
 * Definition of the C-Constant flag for the ukApp Profile associated to the
 *  automatic ukProc Creation (i.e. creation of a ukProc Instance from its
 *  ukApp) upon uKernel Initialization.
 *
 * @warning At least one ukApp in a ukApps Bundle shall have this ukApp Profile
 *  flag set, else no ukProc can never be created, and thus the uKernel
 *  Initialization will fail.
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG              \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 0U)


/**
 * @brief C-Constant defining the ukApp Profile flag for ukProc Reincarnation
 *  after ukProc Termination.
 *
 * Definition of the C-Constant flag for the ukApp Profile associated to the
 *  ukProc Reincarnation of a ukProc after a ukProc Termination from its
 *  previous ukProc Instance.
 *
 * If a ukProc Termination (due to a ukProc End or a ukProc Abort) occurs for
 *  a ukProc Instance which has been created by the uKernel from a ukApp with
 *  this Profile flag, the uKernel will re-create automatically a new ukProc
 *  Instance from this ukApp once the ukProc Termination process of previous
 *  ukProc Instance is over.
 *
 * @implementation This ukApp Profile flag is significant only if uKernel
 *  Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED is supported.
 *  Else it is invalid.
 *
 * @implementation If this ukApp Profile flag is set, then the flag
 *  DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG is ignored.
 *
 * @implementation This ukApp Profile flag can be set only if the flag
 *  DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG is also set.
 *
 * @implementation If a uKernel Session End or a uKernel Session Abort has been
 *  triggered, the reincarnation mechanism is disabled to allow the uKernel
 *  Session to be terminated (and thus this ukApp Profile flag is ignored).
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG                       \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 1U)

/**
 * @brief C-Constant defining the ukApp Profile flag for ukProc Reincarnation
 *  after a ukProc Abort.
 *
 * Definition of the C-Constant flag for the ukApp Profile associated to the
 *  ukProc Reincarnation following a ukProc Abort of its previous ukProc
 *  Instance.
 *
 * If a ukProc Abort occurs for a ukProc Instance which has been created by the
 *  uKernel from a ukApp with this Profile flag, the uKernel will re-create
 *  automatically a new ukProc Instance from this ukApp once the ukProc
 *  Termination process of previous ukProc Instance is over. No ukProc
 *  Reincarnation will however occur if ukProc Termination was due to a ukProc
 *  End.
 *
 * @note See ukProc management high level documentation for more details on
 *  erroneous conditions triggering a ukProc Abort.
 *
 * @implementation This ukApp Profile flag is significant only if uKernel
 *  Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED is supported.
 *  Else it is invalid.
 *
 * @implementation This ukApp Profile flag can be set only if the flag
 *  DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG is also set.
 *
 * @implementation If a uKernel Session End or a uKernel Session Abort has been
 *  triggered, the reincarnation mechanism is disabled to allow the uKernel
 *  Session to be terminated (and thus this ukApp Profile flag is ignored).
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG                  \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 2U)

/**
 *
 * @brief C-Constant defining the ukApp Profile flag for using the FPU.
 *
 * Definition of the C-Constant defining the ukApp Profile flag for using the
 *  FPU.
 *
 * If a ukProc requires the use of the FPU, this flag must be set.
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_RESET_ON_ABORT_FLAG                                  \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 3U)

/**
 * @brief C-Constant defining the ukApp Profile flag providing credentials to
 *  the ukProc for retrieving to the whole Platform Attributes.
 *
 * Definition of the C-Constant flag for the ukApp Profile providing
 *  credentials to the ukProc for retrieving the whole Platform Attributes
 *  (see DukPLATFORM_ATTRIBUTE_TAG_xxx).
 *
 * @implementation If this ukApp Profile flag is not set in the <Profile> field,
 *  the ukProc will not be able to retrieve the following Platform Attributes:
 *  - DukPLATFORM_ATTRIBUTE_TAG_SERIAL_NUMBER
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_PLATFORM_CONFIG_GET_FLAG                             \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 4U)

/**
 * @brief C-Constant defining the ukApp Profile flag providing credentials to
 *  the ukProc for writing Platform Attributes.
 *
 * Definition of the C-Constant flag for the ukApp Profile providing
 *  credentials to the ukProc for writing Platform Attributes (see
 *  DukPLATFORM_ATTRIBUTE_TAG_xxx).
 *
 * @implementation If this ukApp Profile flag is not set in the <Profile> field,
 *  the ukProc will not be able to write the following Platform Attributes:
 *  - DukPLATFORM_ATTRIBUTE_TAG_STATE
 *  - DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX
 *
 * @implementation This flag SHALL BE SET for allowing the ukProc to invoke the
 *  uKernel Privileged Service ukPlatformSetAttribute().
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG                             \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 5U)


/**
 * @brief C-Constant defining ukApp Profile flag providing credentials to
 *  the ukProc for retrieving information on whole uKernel System.
 *
 * Definition of the C-Constant flag for the ukApp Profile providing
 *  credentials to the ukProc for retrieving information on whole uKernel
 *  System.
 *
 * @implementation If this ukApp Profile flag is set in the <Profile> field,
 *  the ukProc will be able to access to the following elements part of the
 *  uKernel System:
 *  - The configuration elements of all the ukApps part of the ukApps Bundle
 *   (see DukUKAPP_ATTRIBUTE_TAG_xxx).
 *  - The configuration and information elements of all the ukProcs
 *   (see DukUKPROC_ATTRIBUTE_TAG_xxx, ).
 *  - The configuration and information elements of the uKernel Core
 *   (see DukUKCORE_ATTRIBUTE_TAG_xxx).
 *  - The information elements on any Address Block (Extra Address Block or
 *   Shared Buffer) managed by the uKernel (see ukAddressBlockGetInfo()).
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG                                    \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 6U)


/**
 *
 * @brief C-Constant defining the ukApp Profile flag for using the FPU.
 *
 * Definition of the C-Constant defining the ukApp Profile flag for using the
 *  FPU.
 *
 * If a ukProc requires the use of the FPU, this flag must be set.
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_FPU_FLAG                                             \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 7U)

/**
 * @brief C-Constant defining ukApp Profile flag defining the ukApp that is the
 *  uKernel Image Update Manager.
 *
 * Definition of the C-Constant flag for the ukApp Profile defining the ukApp
 *  that is the uKernel Image Update Manager.
 * The ukProc from the ukApp that has this flag set (it can be set for one and
 *  only one ukApp of the ukApps Bundle) is the one in charge of managing the
 *  uKernel Image Update by being allowed to invoke associated uKernel
 *  Privileged Services.
 *
 * @warning The uKernel enforces during its initialization that this flag is
 *  set in one and only one <Profile> field of the ukApp Descriptor of the
 *  ukApps part of the ukApps Bundle.
 *  Once the uKernel has encountered a ukApp with this flag set in the <Profile>
 *   field of its ukApp Descriptor, all the subsequent ukApp Descriptors
 *   having this flag set are considered as invalid.
 *
 * @implementation This flag is significant only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_UPDATE is supported.
 *  Else it is ignored.
 *
 * @implementation If this ukApp Profile flag is not set in the <Profile> field,
 *  the ukProc is not allowed to access to the following uKernel Privileged
 *  Services (it will trigger a ukProc Fatal Error):
 *   - ukUKImageUpdateEraseSector().
 *   - ukUKImageUpdateRead().
 *   - ukUKImageUpdateWrite().
 *   - ukUKImageUpdateOperate().
 *
 * @usage This ukApp Profile flag shall be used in the <Profile> field of a
 *  ukApp Descriptor.
 */
#define DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG                    \
            MukVAL_TYPED_BF(TukUKAPP_PROFILE, 8U)

/**
 * @brief C-Constant defining the valid bitmask for ukApp Profile.
 *
 * Definition of the C-Constant of the bitmask of valid flags in ukApp Profile
 *  value.
 *
 * @implementation Each bit set (logical 1) in the bitmask corresponds to a
 *  valid flag.
 */
#define DukUKAPP_PROFILE_VALID_MASK                                           \
            MukVAL_TYPED(TukUKAPP_PROFILE,                                    \
                 DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG   | \
                 DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG            | \
                 DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG       | \
                 DukUKAPP_PROFILE_RESET_ON_ABORT_FLAG                       | \
                 DukUKAPP_PROFILE_PLATFORM_CONFIG_GET_FLAG                  | \
                 DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG                  | \
                 DukUKAPP_PROFILE_FPU_FLAG                                  | \
                 DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG                         | \
                 DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG         | \
                 0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - UKAPP ENTRY POINT                    */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the set of uKernel Privileged Services authorized
 *  during a ukProc Exception.
 *
 * Definition of the C-Constant the set of uKernel Privileged Services
 *  authorized during a ukProc Exception, that is in the ukApp Entry Point
 *  ukappException() code.
 *
 * This value is defined as a 64-bit bitmask, where each uKernel Privileged
 *  Service is identified as the bit number corresponding to its uKernel
 *  Service Identifier (see TukSVC_ID8).
 *  If the bit is set to 1, then the corresponding uKernel Privileged Service
 *  is authorized and can be invoked by the ukappException() code.
 *
 * @implementation The following uKernel Privileged Debug Services are always
 *  authorized and do not need to be included in this bitmask value:
 *  - ukDebugTracePrint().
 *  - ukDebugTracePrintf().
 *  - ukDebugTracePrintBuffer().
 *  - ukDebugLEDSetPattern().
 *
 * @implementation This set of uKernel Privileged Services authorized is
 *  applied in addition to the authorized set defined in the
 *  <UKPrivilegedServicesAuthorizedBitMask64> field in ukApp Descriptor of a
 *  ukApp.
 *
 * @usage Any invocation of unauthorized uKernel Privileged Service during
 *  ukApp Entry Point ukappException() is a ukProc Fatal Error: a ukProc Abort
 *  is triggered by the uKernel with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS.
 */
#define DukUKAPP_EXCEPTION_PRIVILEGED_SERVICES_AUTHORIZED_BITMASK64  (        \
    /* ukProc management. */                                                  \
        (1ULL << DukSVC_ID8_ukUKProcExit)                                   | \
        (1ULL << DukSVC_ID8_ukUKProcEntryPointReturn)                       | \
        (1ULL << DukSVC_ID8_ukUKProcYield)                                  | \
    /* Watchdog Management. */                                                \
        (1ULL << DukSVC_ID8_ukWatchdogStart)                                | \
        (1ULL << DukSVC_ID8_ukWatchdogStop)                                 | \
        (1ULL << DukSVC_ID8_ukWatchdogKick)                                 | \
    /* uKernel Core management. */                                            \
        (1ULL << DukSVC_ID8_ukUKCoreGetAttribute)                           | \
    /* Platform management. */                                                \
        (1ULL << DukSVC_ID8_ukPlatformGetAttribute)                         | \
        (1ULL << DukSVC_ID8_ukPlatformSetAttribute)                         | \
    /* ukApp management. */                                                   \
        (1ULL << DukSVC_ID8_ukUKAppGetAIDXFromAUID)                         | \
        (1ULL << DukSVC_ID8_ukUKAppGetAttribute)                            | \
    /* ukProc management. */                                                  \
        (1ULL << DukSVC_ID8_ukUKProcGetPUIDFromAUID)                        | \
        (1ULL << DukSVC_ID8_ukUKProcGetAttribute)                           | \
    /* Time information. */                                                   \
        (1ULL << DukSVC_ID8_ukUptimeGet_us)                                 | \
        (1ULL << DukSVC_ID8_ukSystickGetCount)                              | \
    /* IPC (Inter-Process-Communication) management. */                       \
        (1ULL << DukSVC_ID8_ukIPCSendNotificationToProcess)                 | \
    /* Address Block management. */                                           \
        (1ULL << DukSVC_ID8_ukAddressBlockGetInfo)                          | \
        (1ULL << DukSVC_ID8_ukAddressBlockGetIDFromLabel)                   | \
        (1ULL << DukSVC_ID8_ukAddressBlockGetBundleID)                      | \
    /* Address Block Window management. */                                    \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowMap)                        | \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowUnMap)                      | \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowGetMapped)                  | \
    /* Shared Buffer management. */                                           \
        (1ULL << DukSVC_ID8_ukSharedBufferResetCredentials)                 | \
        (1ULL << DukSVC_ID8_ukSharedBufferAddCredentials)                   | \
        (1ULL << DukSVC_ID8_ukSharedBufferTransfer)                         | \
    /* MCU Register management. */                                            \
        (1ULL << DukSVC_ID8_ukMCURegisterRead)                              | \
        (1ULL << DukSVC_ID8_ukMCURegisterWrite)                             | \
    /* Peripheral IRQ management. */                                          \
        (1ULL << DukSVC_ID8_ukPeripheralIRQGetInfo)                         | \
        (1ULL << DukSVC_ID8_ukPeripheralIRQPerformAction)                   | \
    /* DMA Stream management. */                                              \
        (1ULL << DukSVC_ID8_ukDMAStreamGetIDFromLabel)                      | \
        (1ULL << DukSVC_ID8_ukDMAStreamGetInfo)                             | \
        (1ULL << DukSVC_ID8_ukDMAStreamAssign)                              | \
        (1ULL << DukSVC_ID8_ukDMAStreamUnassign)                            | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferStart)                       | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferStop)                        | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferGetInfo)                     | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferGetState)                    | \
    /* Random generation. */                                                  \
        (1ULL << DukSVC_ID8_ukRandomSetSeed64)                              | \
        (1ULL << DukSVC_ID8_ukRandomGetBytes)                               | \
    0ULL)


/**
 * @brief C-Constant defining the set of uKernel Privileged Services authorized
 *  during ukProc Cleanup.
 *
 * Definition of the C-Constant with the set of uKernel Privileged Services
 *  authorized during ukProc Cleanup, that once the ukApp Entry Point
 *  ukappCleanup() is invoked.
 *
 * This value is defined as a 64-bit bitmask, where each uKernel Privileged
 *  Service is identified as the bit number corresponding to its uKernel
 *  Service Identifier (see TukSVC_ID8).
 *  If the bit is set to 1, then the corresponding uKernel Privileged Service
 *  is authorized and can be invoked by the ukappCleanup() code.
 *
 * @implementation The following uKernel Privileged Debug Services are always
 *  authorized and do not need to be included in this bitmask value:
 *  - ukDebugTracePrint().
 *  - ukDebugTracePrintf().
 *  - ukDebugTracePrintBuffer().
 *  - ukDebugLEDSetPattern().
 *
 * @implementation This set of uKernel Privileged Services authorized is
 *  applied in addition to the authorized set defined in the
 *  <UKPrivilegedServicesAuthorizedBitMask64> field in ukApp Descriptor of a
 *  ukApp.
 *
 * @usage Any invocation of unauthorized uKernel Privileged Service during
 *  ukApp Entry Point ukappCleanup() is a ukProc Fatal Error: the execution of
 *  the ukApp Entry Point ukappCleanup() is stopped, and the ukProc Termination
 *  process is finalized, with the ukProc Cleanup process set as unsuccessful.
 */
#define DukUKAPP_CLEANUP_PRIVILEGED_SERVICES_AUTHORIZED_BITMASK64  (          \
    /* ukProc management. */                                                  \
        (1ULL << DukSVC_ID8_ukUKProcExit)                                   | \
        (1ULL << DukSVC_ID8_ukUKProcEntryPointReturn)                       | \
    /* uKernel Core management. */                                            \
        (1ULL << DukSVC_ID8_ukUKCoreGetAttribute)                           | \
    /* Platform management. */                                                \
        (1ULL << DukSVC_ID8_ukPlatformGetAttribute)                         | \
        (1ULL << DukSVC_ID8_ukPlatformSetAttribute)                         | \
    /* ukApp management. */                                                   \
        (1ULL << DukSVC_ID8_ukUKAppGetAIDXFromAUID)                         | \
        (1ULL << DukSVC_ID8_ukUKAppGetAttribute)                            | \
    /* ukProc management. */                                                  \
        (1ULL << DukSVC_ID8_ukUKProcGetPUIDFromAUID)                        | \
        (1ULL << DukSVC_ID8_ukUKProcGetAttribute)                           | \
    /* Time information. */                                                   \
        (1ULL << DukSVC_ID8_ukUptimeGet_us)                                 | \
        (1ULL << DukSVC_ID8_ukSystickGetCount)                              | \
    /* IPC (Inter-Process-Communication) management. */                       \
        (1ULL << DukSVC_ID8_ukIPCSendNotificationToProcess)                 | \
    /* Address Block management. */                                           \
        (1ULL << DukSVC_ID8_ukAddressBlockGetInfo)                          | \
        (1ULL << DukSVC_ID8_ukAddressBlockGetIDFromLabel)                   | \
        (1ULL << DukSVC_ID8_ukAddressBlockGetBundleID)                      | \
    /* Address Block Window management. */                                    \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowMap)                        | \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowUnMap)                      | \
        (1ULL << DukSVC_ID8_ukAddressBlockWindowGetMapped)                  | \
    /* Shared Buffer management. */                                           \
        (1ULL << DukSVC_ID8_ukSharedBufferResetCredentials)                 | \
        (1ULL << DukSVC_ID8_ukSharedBufferAddCredentials)                   | \
        (1ULL << DukSVC_ID8_ukSharedBufferTransfer)                         | \
    /* MCU Register management. */                                            \
        (1ULL << DukSVC_ID8_ukMCURegisterRead)                              | \
        (1ULL << DukSVC_ID8_ukMCURegisterWrite)                             | \
    /* Peripheral IRQ management. */                                          \
        (1ULL << DukSVC_ID8_ukPeripheralIRQUnregister)                      | \
        (1ULL << DukSVC_ID8_ukPeripheralIRQGetInfo)                         | \
        (1ULL << DukSVC_ID8_ukPeripheralIRQPerformAction)                   | \
    /* DMA Stream management. */                                              \
        (1ULL << DukSVC_ID8_ukDMAStreamGetIDFromLabel)                      | \
        (1ULL << DukSVC_ID8_ukDMAStreamGetInfo)                             | \
        (1ULL << DukSVC_ID8_ukDMAStreamAssign)                              | \
        (1ULL << DukSVC_ID8_ukDMAStreamUnassign)                            | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferStart)                       | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferStop)                        | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferGetInfo)                     | \
        (1ULL << DukSVC_ID8_ukDMAStreamTransferGetState)                    | \
    /* Random generation. */                                                  \
        (1ULL << DukSVC_ID8_ukRandomSetSeed64)                              | \
        (1ULL << DukSVC_ID8_ukRandomGetBytes)                               | \
    0ULL)




/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - UKAPP ATTRIBUTES                    */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * ukApp Attributes high level documentation
 * -----------------------------------------
 *
 * One of the following conditions is necessary for getting the credentials to
 *  retrieve ukApp Attributes from referenced ukApp (see ukUKAppGetAttribute()):
 *  - The referenced ukApp is the one of the current ukProc.
 *  - The current ukProc has the DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the
 *    <Profile> field of its ukApp Descriptor.
 *  - The referenced ukApp has the ukApp of current ukProc set as its Parent
 *   ukApp (see field <ParentASID> in ukApp Descriptor).
 * Additional conditions may exist for some ukApp Attributes (see their
 *  documentation for more details).
 *
 *  The ukApp attributes can only be modified by a ukProc which has the
 *   necessary credentials (see
 *   DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG) for performing an
 *   update of the whole ukApp by using uKernel Image Update.
 */



/**
 * @brief Constant defining the base value of the Tags associated to ukApp
 *  Attributes.
 *
 * This Constant defines the base value of the Tags associated to the ukApp
 *  Attributes.
 *
 * @note This constants allows to enforce that there is no collision between
 *  the different Tags values supported by the uKernel.
 */
#define DukUKAPP_ATTRIBUTE_TAG_BASE                                           \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG, 0x60U)


/**
 * @brief Constant defining the Tag referencing the Name Attribute of a
 *  ukApp.
 *
 * This Constant defines the Tag referencing the Name (Null Terminated
 *  String; see TukNTCSTRING_ADDRESS) of a given ukApp.
 *   Attribute
 * The Name Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'NameNTString' in
 *  TukUKAPP_DESCRIPTOR). The maximal length of the string (including
 *  trailing null byte) is defined by the constant
 *  DukCONFIG_OPTION_UKAPP_NAME_STRING_LENGTH_MAX.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = Length of the Null Terminated String (including trailing
 *   null byte).
 *  - [L] V: Value = Name of the referenced ukApp as a NTString (Null
 *   Terminated String).
 *   Returned Value has C-Type array of TukNTSTRING_CHAR.
 */
#define DukUKAPP_ATTRIBUTE_TAG_NAME_NTSTRING                                  \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x01U)

/**
 * @brief Constant defining the Tag referencing the AUID Attribute of a
 *  ukApp.
 *
 * This Constant defines the Tag referencing the AUID Attribute  (see
 *  TukUKAPP_AUID) of a given ukApp.
 * The AUID Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'AUID' in
 *  TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKAPP_AUID).
 *  - [L] V: Value = AUID of the referenced ukApp.
 *   Returned Value has C-Type TukUKAPP_AUID.
 */
#define DukUKAPP_ATTRIBUTE_TAG_AUID                                           \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x02U)
/**
 * @brief Constant defining the Tag referencing the Version Attribute of a
 *  ukApp.
 *
 * This Constant defines the Tag referencing the Version Attribute (see
 *  TukVERSION) of a given ukApp.
 * The Version Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'Version' in
 *  TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukVERSION).
 *  - [L] V: Value = Version of the referenced ukApp.
 *   Returned Value has C-Type TukVERSION.
 */
#define DukUKAPP_ATTRIBUTE_TAG_VERSION                                        \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x03U)
/**
 * @brief Constant defining the Tag referencing the Profile Attribute of a
 *  ukApp.
 *
 * This Constant defines the Tag referencing the Profile Attribute (see
 *  TukUKAPP_PROFILE) of a given ukApp.
 * The Profile Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'Profile' in
 *  TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKAPP_PROFILE).
 *  - [L] V: Value = Profile of the referenced ukApp.
 *   Returned Value has C-Type TukUKAPP_PROFILE.
 */
#define DukUKAPP_ATTRIBUTE_TAG_PROFILE                                        \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x04U)
/**
 * @brief Constant defining the Tag referencing the Parent ASID Attribute of a
 *  ukApp.
 *
 * This Constant defines the Tag referencing the Parent ASID Attribute (see
 *  Dukapp_config_PARENT_ASID) of a given ukApp.
 * The Parent ASID Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'ParentASID' in
 *  TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKAPP_ASID).
 *  - [L] V: Value = Parent ASID of the referenced ukApp.
 *   Returned Value has C-Type TukUKAPP_ASID.
 */
#define DukUKAPP_ATTRIBUTE_TAG_PARENT_ASID                                    \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x05U)
/**
 * @brief Constant defining the Tag referencing the Code Size Attribute of
 *  a ukApp.
 *
 * This Constant defines the Tag referencing the Code Size Attribute of a
 *  given ukApp.
 * The Code Size Attribute is retrieved from the ukApp Descriptor
 *  of the given ukApp (see 'MemoryRegionCodeSize' in
 *  TukUKAPP_DESCRIPTOR). Its value is defined in the 'ukapp.ld' linker
 *  file used to compile the ukApp.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [4] V: Value = Code Size (in bytes) of the referenced ukApp.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * @note The returned size corresponds to the one that is reserved by the
 *  uKernel for the exclusive usage of the given ukApp. The
 *  effective size used by the ukApp may be lower.
 */
#define DukUKAPP_ATTRIBUTE_TAG_CODE_SIZE                                      \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x06U)
/**
 * @brief Constant defining the Tag referencing the Data Volatile Size
 *  Attribute of a ukApp.
 *
 * This Constant defines the Tag referencing the Data Volatile Size Attribute
 *  of a given ukApp.
 * The Data Volatile Size Attribute is retrieved from the ukApp
 *  Descriptor of the given ukApp (see 'MemoryRegionDataVolatileSize' in
 *  TukUKAPP_DESCRIPTOR).
 *  Its value is defined in the 'ukapp.ld' linker file used to compile the
 *  ukApp.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [4] V: Value = Data Volatile Size (in bytes) of the referenced ukApp.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * @note The returned size corresponds to the one that is reserved by the
 *  uKernel for the exclusive usage of the given ukApp. The
 *  effective size used by the ukApp may be lower.
 */
#define DukUKAPP_ATTRIBUTE_TAG_DATA_VOLATILE_SIZE                             \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x07U)
/**
 * @brief Constant defining the Tag referencing the Data Persistent Size
 *  Attribute of a ukApp.
 *
 * This Constant defines the Tag referencing the Data Persistent Size
 *  Attribute of a given ukApp.
 * The Data Persistent Size Attribute is retrieved from the ukApp
 *  Descriptor of the given ukApp (see
 *  'DataPersistentBlockLength' in TukUKAPP_DESCRIPTOR).
 *  Its value is defined in the 'ukapp.ld' linker file used to compile the
 *  ukApp.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [4] V: Value = Data Persistent Size (in bytes) of the referenced ukApp.
 *   Returned Value has C-Type TukLENGTH32.
 *
 * @note The returned size corresponds to the one that is reserved by the
 *  uKernel for the exclusive usage of the given ukApp. The
 *  effective size used by the ukApp may be lower.
 */
#define DukUKAPP_ATTRIBUTE_TAG_DATA_PERSISTENT_SIZE                           \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x08U)
/**
 * @brief Constant defining the Tag referencing the ukApp Code Body Block
 *  SHA256-Hash Attribute of a ukApp.
 *
 * This Constant defines the Tag referencing the ukApp Code Body Block
 *  SHA256-Hash Attribute of a given ukApp.
 * This Attribute consists in the SHA256 hash of the ukApp Code Body Block of
 *  the referenced ukApp contained in <UKAppCodeBodyBlockSHA256> field of its
 *  ukApp Descriptor.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukHASH_SHA256).
 *  - [32] V: Value = SHA256 hash of the ukApp Code Body Block of the
 *   referenced ukApp.
 *   Returned Value has C-Type TukHASH_SHA256.
 */
#define DukUKAPP_ATTRIBUTE_TAG_CODE_BODY_BLOCK_SHA256                         \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x09U)

/**
 * @brief Constant defining the Tag referencing the ukApp Descriptor
 *  SHA256-Hash Attribute of a ukApp.
 *
 * This Constant defines the Tag referencing the ukApp Descriptor SHA256-Hash
 *  Attribute of a given ukApp.
 * This Attribute consists in the SHA256 hash of the ukApp Descriptor of
 *  referenced ukApp contained in <UKAppDescriptorSHA256> field of its ukApp
 *  Descriptor.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukHASH_SHA256).
 *  - [32] V: Value = SHA256 hash of the ukApp Descriptor of the referenced
 *   ukApp.
 *   Returned Value has C-Type TukHASH_SHA256.
 */
#define DukUKAPP_ATTRIBUTE_TAG_DESCRIPTOR_SHA256                              \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x0A)

/**
 * @brief Constant defining the Tag referencing the ukProc Termination Context
 *  of the last ukProc Instance from referenced ukApp.
 *
 * This Constant defines the Tag referencing the ukProc Termination Context
 *  of the last ukProc Instance from referenced ukApp.
 * If the ukProc Instance is the first one created from a given ukApp in
 *  current uKernel Session, then the field <TerminationReason> in the returned
 *  ukProc Termination Context is set with DukUKPROC_TERMINATION_REASON_INVALID,
 *  and its other fields are not significant.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKPROC_TERMINATION_CONTEXT).
 *  - [L] V: Value = ukProc Termination Context of the last ukProc Instance
 *   from referenced ukApp.
 *   Returned Value has C-Type TukUKPROC_TERMINATION_CONTEXT.
 *
 * @implementation This Tag is supported only if uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_ALLOWED is supported.
 */
#define DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST                \
                        MukVAL_TYPED(TukUKAPP_ATTRIBUTE_TAG,                  \
                                     DukUKAPP_ATTRIBUTE_TAG_BASE + 0x0B)


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - UKPROC PIDX                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximal PIDX value for an Instantiated ukProc.
 *
 * Definition of the C-Constant for the maximal PIDX value for an Instantiated
 *  ukProc, that is a ukProc that has been created from a ukApp (ukProc Idle
 *  is not counted as such ukProc).
 *
 * @implementation The maximal PIDX value for an Instantiated ukProc shall be
 *  in the range [1 ... (DukCONSTRAINT_UKPROC_COUNT_MAX - 1)].
 */
#define DukUKPROC_PIDX_INSTANTIATED_MAX                                       \
            MukVAL_TYPED(TukUKPROC_PIDX,                                      \
                         (DukCONFIG_OPTION_UKPROC_COUNT_MAX - 1U))

/**
 * @brief C-Constant defining the base value for the special reserved values
 *  for PIDX.
 *
 * Definition of the C-Constant for the base value for the special reserved
 *  values for PIDX.
 *
 * @usage The special reserved PIDX values are used for encoding the special
 *  reserved values of PUID.
 *
 * @usage A PIDX value <pidx> is part of the set of special reserved values
 *  if the following statement is true:
 *      (<pidx> & DukUKPROC_PIDX_SPECIAL_BASE) == DukUKPROC_PIDX_SPECIAL_BASE
 */
#define DukUKPROC_PIDX_SPECIAL_BASE     MukVAL_TYPED(TukUKPROC_PIDX, 0xF0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - UKPROC PUID                       */
/* //////////////////////////////////////////////////////////////////////// */

 /**
  * @brief C-Constant defining the MSb of the Counter field in PUID C-Type.
  *
  * Definition of the C-Constant of the MSb (Most Significant bit) of the
  *  Counter field in ukProc Unique Identifier (PUID) C-Type (see
  *  TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_COUNTER_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 31U)

 /**
  * @brief C-Constant defining the LSb of the Counter field in PUID C-Type.
  *
  * Definition of the C-Constant of the LSb (Less Significant bit) of the
  *  Counter field in ukProc Unique Identifier (PUID) C-Type (see
  *  TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_COUNTER_FIELD_LSb        MukVAL_TYPED(TukBITNUM,  8U)

 /**
  * @brief C-Constant defining the bitmask for the Counter field in PUID C-Type.
  *
  * Definition of the C-Constant for the bitmask of significant bits of the
  *  Counter field in ukProc Unique Identifier (PUID) C-Type (see
  *  TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_COUNTER_FIELD_MASK                                     \
     MukVAL_TYPED(TukUKPROC_PUID,                                             \
                  MukVAL_FIELD_BITMASK32(DukUKPROC_PUID_COUNTER_FIELD_LSb,    \
                                       DukUKPROC_PUID_COUNTER_FIELD_MSb       \
                                  )                                           \
                 )

 /**
  * @brief C-Constant defining the MSb of the PIDX field in PUID C-Type.
  *
  * Definition of the C-Constant of the MSb (Most Significant bit) of the
  *  PIDX field in ukProc Unique Identifier (PUID) C-Type (see TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_PIDX_FIELD_MSb           MukVAL_TYPED(TukBITNUM,  7U)

 /**
  * @brief C-Constant defining the LSb of the PIDX field in PUID C-Type.
  *
  * Definition of the C-Constant of the LSb (Less Significant bit) of the
  *  PIDX field in ukProc Unique Identifier (PUID) C-Type (see TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_PIDX_FIELD_LSb           MukVAL_TYPED(TukBITNUM,  0U)

 /**
  * @brief C-Constant defining the bitmask for the PIDX field in PUID C-Type.
  *
  * Definition of the C-Constant for the bitmask of significant bits of the
  *  PIDX field in ukProc Unique Identifier (PUID) C-Type (see TukUKPROC_PUID).
  */
#define DukUKPROC_PUID_PIDX_FIELD_MASK                                        \
     MukVAL_TYPED(TukUKPROC_PUID,                                             \
                  MukVAL_FIELD_BITMASK32(DukUKPROC_PUID_PIDX_FIELD_LSb,       \
                                       DukUKPROC_PUID_PIDX_FIELD_MSb          \
                                  )                                           \
                 )


/**
 * @brief C-Constant defining the Counter field for the set of special reserved
 *  values for PUID.
 *
 * Definition of the C-Constant for the Counter field for the set of ukProc
 *  Unique Identifier (PUID) special reserved values.
 *
 * The following PUID special reserved values are supported:
 *  - DukUKPROC_PUID_INVALID
 *  - DukUKPROC_PUID_ANY
 *  - DukUKPROC_PUID_NONE
 *  - DukUKPROC_PUID_UKERNEL
 *  - DukUKPROC_PUID_MYSELF
 *  - DukUKPROC_PUID_OWNER
 *
 * @usage A PUID value <puid> is part of the set of special reserved values
 *  if the following statement is true:
 *      (<puid> & DukUKPROC_PIDX_SPECIAL_BASE) == DukUKPROC_PIDX_SPECIAL_BASE
 */
#define DukUKPROC_PUID_COUNTER_FIELD_SPECIAL                                  \
     MukVAL_TYPED(TukUKPROC_PUID,                                             \
                  MukVAL_FIELD_BITMASK32(DukUKPROC_PUID_COUNTER_FIELD_LSb,    \
                                       DukUKPROC_PUID_COUNTER_FIELD_MSb       \
                                  )                                           \
                 )


/**
 * @brief C-Constant defining an invalid value to be used for PUID.
 *
 * Definition of the C-Constant for the invalid value to be used for ukProc
 *  Unique Identifier (PUID).
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukUKPROC_PUID_INVALID                                                \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xFU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))

/**
 * @brief C-Constant defining the special reserved value for PUID referring any
 *  of the ukProcs.
 *
 * Definition of the C-Constant for the ukProc Unique Identifier (PUID) special
 *  reserved value to be used for referring any of ukProcs currently executable.
 */
#define DukUKPROC_PUID_ANY                                                    \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xEU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))

/**
 * @brief C-Constant defining the special reserved value for PUID to be used
 *  for indicating that no ukProc Instance is implied.
 *
 * Definition of the C-Constant for the ukProc Unique Identifier (PUID) special
 *  reserved value to be used for indicating that no ukProc Instance is implied
 *  or referenced.
 */
#define DukUKPROC_PUID_NONE                                                   \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xDU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))


/**
 * @brief C-Constant defining the special reserved value for PUID referring the
 *  uKernel entity.
 *
 * Definition of the C-Constant for the ukProc Unique Identifier (PUID) special
 *  reserved value to be used for referring the uKernel entity.
 */
#define DukUKPROC_PUID_UKERNEL                                                \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xCU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))


/**
 * @brief C-Constant defining the special reserved value for PUID referring the
 *  current ukProc Instance.
 *
 * Definition of the C-Constant for the ukProc Unique Identifier (PUID) special
 *  reserved value to be used for referring the current ukProc Instance .
 */
#define DukUKPROC_PUID_MYSELF                                                 \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xBU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))

/**
 * @brief C-Constant defining the special reserved value for PUID referring the
 *  ukProc Owner Instance of a uKernel resource.
 *
 * Definition of the C-Constant for the ukProc Unique Identifier (PUID) special
 *  reserved value to be used for referring the ukProc Owner Instance of a
 *  uKernel resource.
 */
#define DukUKPROC_PUID_OWNER                                                  \
            MukVAL_TYPED(TukUKPROC_PUID,                                      \
                         DukUKPROC_PUID_COUNTER_FIELD_SPECIAL |               \
                         ((DukUKPROC_PIDX_SPECIAL_BASE + 0xAU) <<             \
                          DukUKPROC_PUID_PIDX_FIELD_LSb))



/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - UKPROC ORIGIN                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the ukProc Origin Event field in
 *  ukProc Origin C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  ukProc Origin Event field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
 */
#define DukUKPROC_ORIGIN_EVENT_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the ukProc Origin Event field in
 *  ukProc Origin C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  ukProc Origin Event field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
 */
#define DukUKPROC_ORIGIN_EVENT_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 24U)

/**
 * @brief C-Constant defining the MSb of the ukProc Origin Info field in
 *  ukProc Origin C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  ukProc Origin Info field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
 */
#define DukUKPROC_ORIGIN_INFO_FIELD_MSb        MukVAL_TYPED(TukBITNUM, 23U)

/**
 * @brief C-Constant defining the LSb of the ukProc Origin Info field in
 *  ukProc Origin C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  ukProc Origin Info field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
 */
#define DukUKPROC_ORIGIN_INFO_FIELD_LSb        MukVAL_TYPED(TukBITNUM, 8U)


 /**
  * @brief C-Constant defining the MSb of the ukProc Origin Context field in
  *  ukProc Origin C-Type.
  *
  * Definition of the C-Constant of the MSb (Most Significant bit) of the
  *  ukProc Origin Context field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
  */
 #define DukUKPROC_ORIGIN_CONTEXT_FIELD_MSb    MukVAL_TYPED(TukBITNUM, 7U)

 /**
  * @brief C-Constant defining the LSb of the ukProc Origin Context field in
  *  ukProc Origin C-Type.
  *
  * Definition of the C-Constant of the LSb (Less Significant bit) of the
  *  ukProc Origin Context field in ukProc Origin (see C-Type TukUKPROC_ORIGIN).
  */
 #define DukUKPROC_ORIGIN_CONTEXT_FIELD_LSb    MukVAL_TYPED(TukBITNUM, 0U)


/**
 * @brief C-Constant defining the ukProc Origin Event flag associated to a
 *  ukProc Creation by uKernel upon uKernel Initialization.
 *
 * Definition of the C-Constant for the ukProc Origin Event flag associated to
 *  a ukProc Creation (i.e. creation of a ukProc Instance) by the uKernel upon
 *  uKernel Initialization.
 *
 * Having this flag set in ukProc Origin Event value implies that:
 *  - uKernel Initialization was just over (thus a new uKernel Session has just
 *   started).
 *  - The ukApp Profile field <Profile> in the ukApp Descriptor of the ukProc
 *   has the flag DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG set.
 *
 * The field <Info> (see TukUKPROC_ORIGIN_INFO) of the parameter
 *  <proc_origin__i> of the ukApp Entry Point ukappMain() contains the value:
 *  - Null(0).
 *
 * @implementation If this flag is set in ukProc Origin Event value, then the
 *  following flags are always reset:
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKPROC_PARENT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_AFTER_ABORT_FLAG
 */
#define DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKERNEL_INIT_FLAG                  \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_EVENT,                            \
                           0U)

/**
 * @brief C-Constant defining the ukProc Origin Event flag associated to a
 *  ukProc Creation requested its ukProc Parent.
 *
 * Definition of the C-Constant for the ukProc Origin Event flag associated to
 *  a ukProc Creation (i.e. creation of a new ukProc Instance) requested by its
 *  ukProc Parent.
 * The ukProc Parent is the ukProc instantiated from the ukApp referenced by
 *  the ASID given in the <ParentASID> field of the ukApp Descriptor of the
 *  ukProc having been created.
 *
 * The field <Info> (see TukUKPROC_ORIGIN_INFO) of the parameter
 *  <proc_origin__i> of the ukApp Entry Point ukappMain() contains the value:
 *  - Null(0).
 *
 * @implementation Having this flag set in ukProc Origin Event value implies
 *  that:
 *  - The ukProc Instance created has the <ParentASID> field in its ukApp
 *   Descriptor set with a valid ASID value.
 *  - The ukProc instantiated from the ukApp with this ASID value has just
 *   invoked the ukUKProcInstantiate() privileged uKernel Service with the AUID
 *   of the ukApp of the ukProc Instance being created.
 *
 * @implementation When the newly created ukProc Instance created starts its
 *  execution (see ukApp Entry Point ukappMain()), there is no guarantee that
 *  its ukProc Parent having invoked ukUKProcInstantiate() for its creation has
 *  not been terminated in the meantime.
 *
 * @implementation The PUID of the ukProc Parent of a ukProc can be retrieved
 *  using the ukProc Attribute Tag DukUKPROC_ATTRIBUTE_TAG_UKPROC_PARENT_PUID.
 *
 * @implementation If this flag is set in ukProc Origin Event value, then the
 *  following flags are always reset:
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKERNEL_INIT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_AFTER_ABORT_FLAG
 */
#define DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKPROC_PARENT_FLAG                 \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_EVENT,                            \
                           1U)

/**
 * @brief C-Constant defining the ukProc Origin Event flag associated to the
 *  ukProc Reincarnation after a ukProc Termination.
 *
 * Definition of the C-Constant for the ukProc Origin Event flag associated to
 *  a ukProc Reincarnation after a ukProc Termination (i.e. a ukProc End or a
 *  ukProc Abort).
 *
 * The field <Info> (see TukUKPROC_ORIGIN_INFO) of the parameter
 *  <proc_origin__i> of the ukApp Entry Point ukappMain() contains the value:
 *  - Null(0).
 *
 * @implementation Having this flag set in ukProc Origin Event value implies
 *  that:
 *  - The ukApp Profile field <Profile> in the ukApp Descriptor of the ukProc
 *   has one of the flag DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG or
 *   DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG set.
 *  - The uKernel has triggered a ukProc Termination during the execution of
 *   previous ukProc Instance from same ukApp.
 *
 * @implementation If this flag is set in ukProc Origin Event value, then the
 *  following flags are always reset:
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKERNEL_INIT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKPROC_PARENT_FLAG
 *
 * @implementation Having this flag set in ukProc Origin Event value implies
 *  that the ukApp Profile field <Profile> in the ukApp Descriptor of the
 *  ukProc has the DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG flag and/or
 *  DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG flag set.
 *
 * @usage The ukProc Origin Event flag
 *  DukUKPROC_ORIGIN_EVENT_REINCARNATION_AFTER_ABORT_FLAG can be used to
 *  determine if the ukProc Termination is issued from a ukProc End or a ukProc
 *  Abort.
 */
#define DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG                  \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_EVENT,                            \
                           2U)

/**
 * @brief C-Constant defining the ukProc Origin Event flag associated to the
 *  ukProc Reincarnation after a ukProc Abort of previous ukProc Instance.
 *
 * Definition of the C-Constant for the ukProc Origin Event flag associated to
 *  a ukProc Reincarnation after a ukProc Abort of its previous ukProc Instance.
 *
 * This flag is significant only if the flag
 *  DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG is set (else it is
 *  always reset and shall be ignored).
 * If this flag is set, the ukProc Termination was due to a ukProc Abort
 *  triggered during the execution of previous ukProc Instance from same ukApp.
 * Else, it was due to a ukProc End.
 *
 * The field <Info> (see TukUKPROC_ORIGIN_INFO) of the parameter
 *  <proc_origin__i> of the ukApp Entry Point ukappMain() contains the value:
 *  - Null(0).
 *
 * @implementation If this flag is set in ukProc Origin Event value, then the
 *  following flags are always set:
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG
 *  And the following flags are always reset:
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKERNEL_INIT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKPROC_PARENT_FLAG
 *
 * @implementation Having this flag set in ukProc Origin Event value implies
 *  that the ukApp Profile field <Profile> in the ukApp Descriptor of the
 *  ukProc has the DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG flag and/or
 *  DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG flag set.
 */
#define DukUKPROC_ORIGIN_EVENT_REINCARNATION_AFTER_ABORT_FLAG                 \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_EVENT,                            \
                           3U)



 /**
  * @brief C-Constant defining the ukProc Origin Context flag reporting that
  *  the ukProc Instance is the first in this uKernel Session.
  *
  * Definition of the C-Constant for the ukProc Context flag reporting that
  *  the ukProc Instance is the first one instantiated from its ukApp in this
  *  uKernel Session.
  *
  * @implementation If a ukProc Termination (ukProc End or ukProc Abort) occurs
  *  for the ukProc Instance of a given ukApp, then all the subsequent ukProc
  *  instantiated from this ukApp will not have this flag set in current
  *  uKernel Session.
  *
  * @usage If this flag is not set, then information on the ukProc Termination
  *  of previous ukProc Instance can be retrieved by getting the last ukProc
  *  Termination Context of its ukApp (see ukApp Attribute
  *  DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST).
  */
 #define DukUKPROC_ORIGIN_CONTEXT_INSTANCE_FIRST_IN_UKERNEL_SESSION_FLAG      \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_CONTEXT,                          \
                           0U)


 /**
  * @brief C-Constant defining the ukProc Origin Context flag reporting an
  *  update of the uKernel Image.
  *
  * Definition of the C-Constant for the ukProc Context flag reporting an
  *  update of the uKernel Image (whole or partial).
  */
 #define DukUKPROC_ORIGIN_CONTEXT_UKERNEL_IMAGE_UPDATED_FLAG                  \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_CONTEXT,                          \
                           4U)


 /**
  * @brief C-Constant defining the ukProc Origin Context flag indicating that a
  *  Debugger can be connected.
  *
  * Definition of the C-Constant for the ukProc Context flag indicating that
  *  a Debugger can be connected to debug the ukProc.
  */
 #define DukUKPROC_ORIGIN_CONTEXT_DEBUGGER_ALLOWED_FLAG                       \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_CONTEXT,                          \
                           6U)


 /**
  * @brief C-Constant defining the ukProc Origin Context flag indicating that a
  *  Debugger Connection has occurred.
  *
  * Definition of the C-Constant for the ukProc Context flag indicating that
  *  a Debugger Connection has occurred since the start of current uKernel
  *  Session
  *
  * @usage If this flag is set, a Debugger may or may not still be connected
  *  (this flag only indicates that the connection of a Debugger has been
  *  detected since the start of the uKernel Session).
  */
 #define DukUKPROC_ORIGIN_CONTEXT_DEBUGGER_CONNECTION_FLAG                    \
           MukVAL_TYPED_BF(TukUKPROC_ORIGIN_CONTEXT,                          \
                           7U)


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - UKPROC TERMINATION                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc End.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc End.
 *
 * A ukProc End is occurring when a ukProc is requesting the halt of the
 *  execution of its current ukProc Instance after successful operations (i.e
 *  without reporting any error).
 * It is triggered by the ukProc by the invocation of the uKernel Privileged
 *  Service ukUKProcExit() in ukApp Entry Point ukappMain() or ukappException()
 *  without reporting any error upon exit (i.e. its parameter
 *  <is_exit_in_error__i> is set to DukBOOL_FALSE).
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - (TukUKPROC_TERMINATION_INFO) Value of the <ukproc_termination_info__i>
 *   parameter given when invoking ukUKProcExit().
 */
#define DukUKPROC_TERMINATION_REASON_END                                      \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x01U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  upon an Exit In Error.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  upon an Exit In Error.
 *
 * Such a ukProc Abort is occurring when a ukProc is requesting the halt of the
 *  execution of its current ukProc Instance after an erroneous internal
 *  condition.
 * It is triggered by the ukProc by:
 *  - Invoking the uKernel Privileged Service ukUKProcExit(), in any of its
 *   ukApp Entry Points, with reporting of an error upon exit (i.e. its
 *   parameter <is_exit_in_error__i> is not set to DukBOOL_FALSE).
 *  - Invoking the uKernel Privileged Service ukUKProcEntryPointReturn() in
 *   its ukApp Entry Point ukappMain().
 *  - Returning (using standard 'return()' C-Keyword) from its ukApp Entry
 *   Point ukappMain().
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - (TukUKPROC_TERMINATION_INFO) Value of the <ukproc_termination_info__i>
 *   parameter used when invoking ukUKProcExit().
 *  - Null(0) If ukUKProcExit() was not used for the exit.
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR                      \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x10U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  upon an Illegal Access.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  due to an illegal access performed by a uKernel Privileged Service invoked
 *  by the ukProc.
 *
 * Such a ukProc Abort due to an Illegal Access is triggered by the ukProc by
 *  one of the following events upon invocation of a uKernel Privileged
 *  Service:
 *  - Access not granted due to insufficient credentials in ukApp Profile (see
 *  <Profile> field of the ukApp Descriptor).
 *  - Improper presentation of an Access Key.
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - (TukSVC_ID8) Identifier referencing uKernel Privileged Service having
 *   raised the illegal access.
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS                     \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x11U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  due to an MCU Exception Fault.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  due to an MCU Exception Fault that has been triggered by the execution of
 *  the ukProc code.
 *
 * Such a ukProc Abort due to an MCU Exception Fault is triggered by the ukProc
 *  by one of the following events:
 *  - Invalid CPU opcode executed.
 *  - Illegal CPU operation performed (e.g. division by zero).
 *  - Access to an undefined memory address in MCU memory map.
 *  - Access to a memory address not mapped by the uKernel for the ukProc.
 *  - Direct access to an MCU Register whose access is restricted to CPU
 *   Privileged Execution Mode.
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - (TukADDRESS32) ukApp Code Block address having triggered the MCU
 *   Exception Fault.
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT                          \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x12U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  due to ukProc Invalid State.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  due to ukProc Invalid State.
 *
 * Such a ukProc Abort due to ukProc Invalid State is triggered by the ukProc
 *  by one of the following events:
 *  - Expiration of the Scheduling Time Quantum set when entering in a ukApp
 *   Entry Point (see ukappCleanup() and ukappException()).
 *  - The ukProc CPU Stack Pointer is invalid, or an overflow/underflow has
 *   been detected in the ukProc CPU Stack.
 *  - Robustness checks performed on the ukProc Execution Context have failed.
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - Null(0).
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_INVALID_STATE                      \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x13U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  due to expiration of a ukProc Watchdog.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  due to the expiration of one of the ukProc Watchdogs started by the ukProc
 *  (see ukWatchdogStart()).
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - Null(0).
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_WATCHDOG                           \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x14U)


/**
 * @brief C-Constant defining the ukProc Termination Reason for a ukProc Abort
 *  due to the triggering of a uKernel Session End.
 *
 * This C-Constant defines the ukProc Termination Reason for a ukProc Abort
 *  due to the triggering of a uKernel Session End.
 *
 * The triggering of a uKernel Session End may be due to the following events:
 *  - Request from a ukProc (see DukPLATFORM_ATTRIBUTE_TAG_STATE).
 *  - No ukProc Instance remains.
 *  - Limit reached for some uKernel resources (e.g. maximal uKernel Uptime).
 *
 * @implementation Upon the triggering of uKernel Session End, the uKernel
 *  triggers a ukProc Abort on all the ukProcs with this ukProc Termination
 *  Reason value. The uKernel Session is effectively ended only after all the
 *  ukProc Abort have been finalized, that is when:
 *  - If uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   supported: the invocation of the ukApp Entry Point ukappCleanup() of
 *   each ukProc is over.
 *  - Each ukProc has finalized its termination process:
 *   + The wiping of their ukApp Data Volatile Block is over.
 *   + Their ukProc Instance has been deleted.
 *
 * The ukProc Termination Information associated to this Reason contains the
 *  value:
 *  - Null(0).
 */
#define DukUKPROC_TERMINATION_REASON_ABORT_UKERNEL_SESSION_END                \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0x20U)


/**
 * @brief C-Constant defining an invalid value for a ukProc Termination Reason
 *  value.
 *
 * Definition of the C-Constant for the invalid value to be used for a ukProc
 *  Termination Reason.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukUKPROC_TERMINATION_REASON_INVALID                                  \
                                MukVAL_TYPED(TukUKPROC_TERMINATION_REASON,    \
                                             0xFFUL)





/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - UKPROC ATTRIBUTES                  */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * ukProc Attributes high level documentation
 * ------------------------------------------
 *
 * One of the following conditions is necessary for getting the credentials to
 *  retrieve ukProc Attributes from referenced ukProc (see
 *  ukUKProcGetAttribute()):
 *  - The referenced ukProc is the current ukProc.
 *  - The current ukProc has the DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG set in the
 *    <Profile> field of its ukApp Descriptor.
 *  - The referenced ukProc has the ukApp of current ukProc set as its Parent
 *   ukApp (see field <ParentASID> in ukApp Descriptor).
 * Additional conditions may exist for some ukProc Attributes (see their
 *  documentation for more details).
 *
 *  The ukProc attributes can never be modified by a ukProc.
 */


/**
 * @brief Constant defining the base value of the Tags associated to ukProc
 *  Attributes.
 *
 * This Constant defines the base value of the Tags associated to the ukProc
 *  Attributes.
 *
 * @note This constants allows to enforce that there is no collision between
 *  the different Tags values supported by the uKernel.
 */
#define DukUKPROC_ATTRIBUTE_TAG_BASE     MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, 0x80U)


/**
 * @brief Constant defining the Tag referencing the AUID Attribute of a
 *  ukProc.
 *
 * This Constant defines the Tag referencing the AUID Attribute (see
 *  TukUKAPP_AUID) associated to a given ukProc.
 * The AUID Attribute is retrieved from the ukApp Descriptor
 *  of the ukApp from which the given ukProc is
 *  instantiated (see 'Version' in TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKAPP_AUID).
 *  - [L] V: Value = AUID of the ukApp from which is instantiated
 *   the referenced ukProc.
 *   Returned Value has C-Type TukUKAPP_AUID.
 */
#define DukUKPROC_ATTRIBUTE_TAG_AUID        MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x01U)

/**
 * @brief Constant defining the Tag referencing the Stack Free Size Attribute
 *  of the ukProc.
 *
 * This Constant defines the Tag referencing the current Stack Free Size
 *  Attribute of a given ukProc.
 * The Stack Free Size corresponds to remaining number of bytes on the CPU
 *  Stack dedicated to the ukProc (it is placed at the end of its
 *  Data Volatile Block). The number of free bytes reported is the one
 *  that can effectively used by the ukProc code (the amount of
 *  bytes needed to invoke a uKernel Service has already been subtracted to
 *  it).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [L] V: Value = Current Stack Free Size (in bytes) of the referenced
 *   ukProc.
 *   Returned Value has C-Type TukLENGTH32.
 */
#define DukUKPROC_ATTRIBUTE_TAG_STACK_FREE_SIZE      MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x02U)

/**
 * @brief Constant defining the Tag referencing the Heap Start Address
 *  Attribute of the ukProc.
 *
 * This Constant defines the Tag referencing the Heap Start Address
 *  Attribute of the given ukProc. *
 * The Heap Start Address corresponds to the first address of the Heap Block
 *  that can be used by a ukProc for its own needs (the Heap Block is a
 *  continuous volatile memory area, placed between the C-Variables and the CPU
 *  Stack of the ukProc).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [L] V: Value = Start Address of the Heap of the referenced ukProc.
 *   Returned Value has C-Type TukADDRESS32.
 *
 * @implementation Only the current ukProc can read its own Heap Address
 *  (access to Heap Address of other ukProcs is forbidden).
 */
#define DukUKPROC_ATTRIBUTE_TAG_HEAP_ADDRESS_START    MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x03U)

/**
 * @brief Constant defining the Tag referencing the Heap Size Attribute of
 *  the ukProc.
 *
 * This Constant defines the Tag referencing the Heap Size (in bytes)
 *  Attribute of the given ukProc (see DukUKPROC_ATTRIBUTE_TAG_HEAP_ADDRESS_START
 *  for more details).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = 4.
 *  - [L] V: Value = Length of the Heap of the referenced uKproc.
 *   Returned Value has C-Type TukLENGTH32.
 */
#define DukUKPROC_ATTRIBUTE_TAG_HEAP_ADDRESS_SIZE    MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x4U)

/**
 * @brief Constant defining the Tag referencing the PUID of the ukProc Parent
 *  of the ukProc.
 *
 * This Constant defines the Tag referencing the PUID of ukProc Parent of the
 *  ukProc.
 *
 * The returned PUID value may be part of the special reserved PUID values:
 *  - DukUKPROC_PUID_UKERNEL: The ukProc Instance has been created by the
 *   uKernel. If this value is returned, it implies that the ukApp Profile of
 *   the ukProc has the DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG
 *   flag set.
 *  - DukUKPROC_PUID_INVALID: The ukProc Instance has been created by a ukProc
 *   Parent instantiated from the ukApp set as its ukApp Parent (see field
 *   <ParentASID> in ukApp Descriptor), but the ukProc Instance of this ukProc
 *   Parent has been terminated.
 * If returned PUID value is not part of the special reserved PUID values, then
 *  the ukProc Instance has been created by its ukProc Parent instantiated from
 *  the ukApp set as its ukApp Parent (see field <ParentASID> in ukApp
 *  Descriptor), and the returned PUID references this ukProc Parent.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukUKPROC_PUID).
 *  - [L] V: Value = PUID of the ukProc Parent of the ukProc.
 *   Returned Value has C-Type TukUKPROC_PUID.
 */
#define DukUKPROC_ATTRIBUTE_TAG_UKPROC_PARENT_PUID                            \
            MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG,                             \
                         DukUKPROC_ATTRIBUTE_TAG_BASE + 0x5U)

/**
 * @brief Constant defining the Tag referencing the Scheduling Priority Base
 *  Attribute of a ukProc.
 *
 * This Constant defines the Tag referencing the Scheduling Priority Base
 *  Attribute (see TukSCHEDULING_PRIORITY) of a given ukProc.
 *
 * The returned Scheduling Priority Base value is the one defined in the
 *  <SchedulingPriorityBase> field of the ukApp Descriptor of the ukApp
 *  (see TukUKAPP_DESCRIPTOR) of the ukProc.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukSCHEDULING_PRIORITY).
 *  - [L] V: Value = Scheduling Priority Base of the referenced ukProc.
 *   Returned Value has C-Type TukSCHEDULING_PRIORITY.
 */
#define DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_PRIORITY_BASE    MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x10U)

/**
 * @brief Constant defining the Tag referencing the Scheduling Quantum
 *  Allocated Attribute of the ukProc.
 *
 * This Constant defines the Tag referencing the Scheduling Quantum Allocated
 *  Attribute (see TukSCHEDULING_TIME_QUANTUM_systick) of a given ukProc.
 *
 * The returned Scheduling Time Quantum Allocated value is the one defined in
 *  the <SchedulingTimeQuantumAllocated_systick> field of the ukApp Descriptor
 *  of its ukApp (see TukUKAPP_DESCRIPTOR).
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukSCHEDULING_TIME_QUANTUM_systick).
 *  - [L] V: Value = Scheduling Time Quantum Allocated (unit is uKernel
 *   SysTicks) of the referenced ukProc.
 *   Returned Value has C-Type TukSCHEDULING_TIME_QUANTUM_systick.
 */
#define DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_TIME_QUANTUM_ALLOCATED       MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x11U)

/**
 * @brief Constant defining the Tag referencing the Scheduling Quantum
 *  Remaining Attribute of the ukProc.
 *
 * This Constant defines the Tag referencing the Scheduling Quantum Remaining
 *  Attribute (see TukSCHEDULING_TIME_QUANTUM_systick) of a given ukProc.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukSCHEDULING_TIME_QUANTUM_systick).
 *  - [L] V: Value = Scheduling Time Quantum Remaining (unit is uKernel
 *   SysTicks), of the referenced ukProc.
 *   Returned Value has C-Type TukSCHEDULING_TIME_QUANTUM_systick.
 */
#define DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_TIME_QUANTUM_REMAINING       MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x12U)

/**
 * @brief Constant defining the Tag referencing the Scheduling ukProc State
 *  Attribute of the ukProc.
 *
 * This Constant defines the Tag referencing the Scheduling ukProc State
 *  Attribute (see TukSCHEDULING_UKPROC_STATE) of a given ukProc.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukSCHEDULING_UKPROC_STATE).
 *  - [L] V: Value = Scheduling ukProc State of the referenced ukProc.
 *   Returned Value has C-Type TukSCHEDULING_UKPROC_STATE.
 */
#define DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_STATE       MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x13U)

/**
 * @brief Constant defining the Tag referencing the Scheduling Statistics
 *  Attribute of the ukProc.
 *
 * This Constant defines the Tag referencing the Scheduling Statistics
 *  Attribute (see TukSCHEDULING_UKPROC_STATISTICS) of a given uKernel
 *  Process.
 * The Scheduling Statistics are maintained by the uKernel Scheduler and are
 *  updated only when the given ukProc is scheduled.
 *
 * The TLV structure for this Tag is as follows (length in bytes of each
 *  field is given between brackets):
 *  - [1] T: Tag.
 *  - [1] L: Length = sizeof(TukSCHEDULING_UKPROC_STATISTICS).
 *  - [L] V: Value = Scheduling Statistics of referenced ukProc.
 *   + [8] TukCOUNT64      ScheduledCount;
 *   + [8] TukCOUNT64      PreemptedCount;
 *   + [8] TukTIME64_tick  ScheduledTimeTotal_systick;
 *   + [8] TukTIME64_us    ScheduledTimeTotal_us;
 *   Returned Value has C-Type TukSCHEDULING_UKPROC_STATISTICS.
 */
#define DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_STATISTICS       MukVAL_TYPED(TukUKPROC_ATTRIBUTE_TAG, \
    DukUKPROC_ATTRIBUTE_TAG_BASE + 0x14U)


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - SCHEDULING TIME QUANTUM                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the minimal value for a Scheduling Time Quantum.
 *
 * Definition of the C-Constant for the minimal value for a Scheduling Time
 *  Quantum (see TukSCHEDULING_TIME_QUANTUM_systick), in uKernel Systick unit.
 */
#define DukSCHEDULING_TIME_QUANTUM_MIN_systick                                \
          MukVAL_TYPED(TukSCHEDULING_TIME_QUANTUM_systick, 1U)

/**
 * @brief C-Constant defining the maximal value for a Scheduling Time Quantum.
 *
 * Definition of the C-Constant for the maximal value for a Scheduling Time
 *  Quantum (see TukSCHEDULING_TIME_QUANTUM_systick), in uKernel Systick unit.
 */
#define DukSCHEDULING_TIME_QUANTUM_MAX_systick                                \
          MukVAL_TYPED(TukSCHEDULING_TIME_QUANTUM_systick, 32U)


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - SCHEDULING DELAY                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the maximal Scheduling Delay.
 *
 * Definition of the C-Constant for the maximal value for a Scheduling Delay,
 *  in uKernel Systicks unit, in the ukScheduler (uKernel Scheduler).
 *
 * @usage The maximal Scheduling Delay is used in the following case:
 *   - As maximal allowed Yield Delay (see ukUKProcYield()).
 */
#define DukSCHEDULING_DELAY_MAX_systick                                       \
                                      MukVAL_TYPED(TukTIME32_tick, 10000UL)



/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - SCHEDULING UKPROC STATE                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Ready Flag in the Scheduling ukProc State.
 *
 * Definition of the C-Constant for the Ready Flag in the Scheduling ukProc
 * State (see TukSCHEDULING_UKPROC_STATE).
 * The Ready Flag indicates that the ukProc is in ukProc Schedulable State
 *  Ready: it can be elected as a Scheduled ukProc in the ukScheduler or is
 *  currently the Scheduled ukProc (i.e. the one currently executed by the MCU;
 *  in this case the flag DukSCHEDULING_STATE_RUNNING_FLAG is also set).
 *
 * @note When this flag is set, the ukProc is said to be a schedulable ukProc.
 *
 * @implementation When this flag is set, the following flag(s) are never set:
 *  - DukSCHEDULING_STATE_BLOCKED_FLAG
 *  - DukSCHEDULING_STATE_INTERRUPT_FLAG
 *  - DukSCHEDULING_STATE_HALTED_FLAG
 */
#define DukSCHEDULING_STATE_READY_FLAG                                        \
                            MukVAL_TYPED_BF(TukSCHEDULING_UKPROC_STATE, 4U)


/**
 * @brief C-Constant defining the Interrupted Flag in the Scheduling ukProc
 *  State.
 *
 * Definition of the C-Constant for the Interrupted Flag in the Scheduling
 *  ukProc State (see TukSCHEDULING_UKPROC_STATE).
 * The Interrupted Flag indicates that the ukProc is in ukProc Schedulable
 *  State Interrupted.
 * It implies that:
 *  - A ukProc Exception has been raised while in its ukApp Entry Point
 *   ukappMain().
 *  - The ukappMain() code execution has been suspended.
 *  - The ukApp Entry Point ukappException() has been invoked, and its
 *   invocation is not yet over (its code is the one executed when the ukProc
 *   is the Scheduled ukProc).
 *
 *  This flag is reset as soon as the invocation of the ukApp Entry Point
 *   ukappException() is over (either by exiting it properly using uKernel
 *   Privileged Service ukUKProcEntryPointReturn(), or because of a ukProc
 *   Fatal Error).
 *
 * @implementation The Scheduling Time Quantum Allocated for ukProc Exception
 *  defines the maximum duration, in uKernel Systicks unit, of the invocation
 *  of the ukApp Entry Point ukappException(). It is defined in the field
 *  <UKProcExceptionSchedulingTimeQuantumAllocated_systick> of the ukApp
 *  Descriptor.
 *
 * @implementation When this flag is set, the following flag(s) are never set:
 *  - DukSCHEDULING_STATE_BLOCKED_FLAG
 *  - DukSCHEDULING_STATE_HALTED_FLAG
 *  And the following flag(s) are always set:
 *  - DukSCHEDULING_STATE_READY_FLAG
 *
 * @implementation This flag is set and significant only if the uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_EXCEPTION is supported.
 */
#define DukSCHEDULING_STATE_INTERRUPT_FLAG                                    \
                            MukVAL_TYPED_BF(TukSCHEDULING_UKPROC_STATE, 5U)


/**
 * @brief C-Constant defining the Blocked Flag in the Scheduling ukProc State.
 *
 * Definition of the C-Constant for the Blocked Flag in the Scheduling ukProc
 *  State (see TukSCHEDULING_UKPROC_STATE).
 * The Blocked Flag indicates that the ukProc is in Scheduling ukProc State
 *  Blocked.
 * As long as this flag is set, the ukProc is unschedulable and cannot be
 *  elected as the Scheduled ukProc by the ukScheduler.
 * The Scheduling ukProc State Blocked will stay until an expected event occurs
 *  (e.g. sending of an IPC Message by another ukProc, triggering of a
 *  Peripheral IRQ, ...).
 *
 * @note When this flag is set, the ukProc is said to be an unschedulable
 *  ukProc.
 *
 * @implementation When this flag is set, the following flag(s) are never set:
 *  - DukSCHEDULING_STATE_READY_FLAG
 *  - DukSCHEDULING_STATE_INTERRUPT_FLAG
 *  - DukSCHEDULING_STATE_HALTED_FLAG
 */
#define DukSCHEDULING_STATE_BLOCKED_FLAG                                      \
                            MukVAL_TYPED_BF(TukSCHEDULING_UKPROC_STATE, 6U)


/**
 * @brief C-Constant defining the Halted Flag in the Scheduling ukProc State.
 *
 * Definition of the C-Constant for the Halted Flag in the Scheduling ukProc
 *  State (see TukSCHEDULING_UKPROC_STATE).
 * The Halted Flag indicates that the ukProc is in Scheduling ukProc State
 *  Halted, and thus that the ukProc is permanently unschedulable (i.e. it can
 *  never be elected again as the Scheduled ukProc, and thus never be executed).
 *
 * @implementation When this flag is set, the following flag(s) are reset:
 *  - DukSCHEDULING_STATE_READY_FLAG
 *  - DukSCHEDULING_STATE_INTERRUPT_FLAG
 *  - DukSCHEDULING_STATE_BLOCKED_FLAG
 *
 * @implementation Once this flag is set, it can never be reset.
 *
 * @implementation This flag is set as soon as the invocation of the ukApp
 *  Entry Point ukappCleanup() is over if the uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported. If not supported,
 *  this flag is set as soon as the ukProc Termination process is triggered.
 */
#define DukSCHEDULING_STATE_HALTED_FLAG                                       \
                            MukVAL_TYPED_BF(TukSCHEDULING_UKPROC_STATE, 7U)


/**
 * @brief C-Constant defining the Running Flag in the Scheduling ukProc State.
 *
 * Definition of the C-Constant for the Running Flag in the Scheduling ukProc
 * State (see TukSCHEDULING_UKPROC_STATE).
 * The Running Flag indicates that the ukProc is in ukProc Schedulable State
 *  Running: it is the currently Scheduled ukProc (i.e. the one currently
 *  executed by the MCU).;
 *  in this case the flag DukSCHEDULING_STATE_RUNNING_FLAG is also set).
 *
 * @note When this flag is set, the ukProc is said to be the Scheduled ukProc.
 *
 * @implementation When this flag is set, the following flag(s) are never set:
 *  - DukSCHEDULING_STATE_BLOCKED_FLAG
 *  - DukSCHEDULING_STATE_HALTED_FLAG
 *  And the following flag(s) are always set:
 *  - DukSCHEDULING_STATE_READY_FLAG
 */
#define DukSCHEDULING_STATE_RUNNING_FLAG                                      \
                            MukVAL_TYPED_BF(TukSCHEDULING_UKPROC_STATE, 8U)



/* //////////////////////////////////////////////////////////////////////// */
/*                            CONSTANTS - IPC MODE                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant defining the Blocking flag while Sending in IPC Message Mode.
 *
 * This constant defines the Blocking flag in IPC Message Mode for enforcing
 *  that the Sending operation waits till the Recipient ukProc is
 *  accepting the reception of the sent IPC Message.
 * If this flag is not set, the Sending operation returns immediately even if
 *  the Recipient has not accepted the reception of the IPC Message.
 */
#define DukIPC_MODE_SEND_BLOCKING_FLAG           MukVAL_TYPED_BF(TukIPC_MODE, 28U)


/**
 * @brief Constant defining the Blocking flag while Receiving in IPC Message
 *  Mode.
 *
 * This constant defines the Blocking flag in IPC Message Mode for enforcing
 *  that the Receiving operation waits till an IPC Message fulfilling the
 *  filters conditions is received.
 * If this flag is not set, the Receiving operation returns immediately even if
 *  no IPC Message has been received.
 */
#define DukIPC_MODE_RECEIVE_BLOCKING_FLAG        MukVAL_TYPED_BF(TukIPC_MODE, 29U)


/**
 * @brief Constant defining the Filter value in IPC Message Mode for accepting
 *  the reception of IPC Message sent by other ukProc.
 *
 * This constant defines the Filter value in IPC Message Mode for accepting
 *  while in reception Raw Data IPC Message sent by other ukProc
 *  (see DukIPC_MSG_NATURE_UKPROC_DATA).
 */
#define DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG            MukVAL_TYPED_BF(TukIPC_MODE, 24U)


/**
 * @brief Constant defining the Filter value in IPC Message Mode for accepting
 *  the reception of IPC Notifications upon PIRQ triggering.
 *
 * This constant defines the Filter value in IPC Message Mode for accepting
 *  while in reception IPC Notification sent by uKernel upon registered
 *  Peripheral IRQ having triggered (see DukIPC_MSG_NATURE_PIRQ_TRIGGERED).
 */
#define DukIPC_MODE_RECEIVING_FILTER_PERIPHERAL_IRQ_FLAG          MukVAL_TYPED_BF(TukIPC_MODE, 25U)


/**
 * @brief Constant defining the Filter value in IPC Message Mode for accepting
 *  the reception of IPC Notification sent by other ukProc.
 *
 * This constant defines the Filter value in IPC Message Mode for accepting
 *  while in reception IPC Notification sent by other ukProcs (see
 *  DukIPC_MSG_NATURE_UKPROC_NOTIFICATION).
 */
#define DukIPC_MODE_RECEIVING_FILTER_UKPROC_NOTIFICATION_FLAG    MukVAL_TYPED_BF(TukIPC_MODE, 26U)


/**
 * @brief Constant defining the Mask of Filter field in uKernel IPC Mode.
 *
 * This Constant defines the Mask value to be applied on IPC Mode to retrieve
 *  the Filter field associated to the Sending and/or Receiving.
 */
#define DukIPC_MODE_RECEIVING_FILTER_MASK        MukVAL_TYPED(TukIPC_MODE,    \
    DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG                           | \
    DukIPC_MODE_RECEIVING_FILTER_PERIPHERAL_IRQ_FLAG                        | \
    DukIPC_MODE_RECEIVING_FILTER_UKPROC_NOTIFICATION_FLAG                    )

/**
 * @brief Constant defining the Mask of Timeout field in uKernel IPC Mode.
 *
 * This Constant defines the Mask value to be applied on IPC Mode to retrieve
 *  the IPC Timeout associated to the Sending and/or Receiving.
 */
#define DukIPC_MODE_TIMEOUT_MASK        MukVAL_TYPED(TukIPC_MODE, 0xFFFFFFUL)

/**
 * @brief Constant defining the IPC Timeout value for indicating it is infinite.
 *
 * This constant defines the IPC Timeout value that has to be used in the IPC
 *  Mode to indicate that the IPC Timeout associated to the Sending and/or
 *  Receiving is infinite.
 */
#define DukIPC_MODE_TIMEOUT_INFINITE    MukVAL_TYPED(TukIPC_MODE, 0U)



/* //////////////////////////////////////////////////////////////////////// */
/*                          CONSTANTS - IPC MESSAGE                         */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief Constant defining the IPC Message Nature value when IPC Message
 *  contents is raw data provided by the Sender.
 *
 * This constant defines the IPC Message Nature value when the IPC Message
 *  Contents exchanged between two ukProcs is raw data provided by
 *  the Sender (see TukIPC_MSG_CONTENT_UKPROC_DATA).
 *
 * @note The uKernel does not use, neither interpret, the contents of the IPC
 *  Message of this Nature.
 */
#define DukIPC_MSG_NATURE_UKPROC_DATA        MukVAL_TYPED_BF(TukIPC_MSG_NATURE, 0U)

/**
 * @brief Constant defining the IPC Message Nature value when IPC Message
 *  Contents is a set of Peripheral IRQs having triggered.
 *
 * This constant defines the IPC Message Nature value when the IPC Message
 *  Contents is a set of Peripheral IRQs registered by the Recipient ukProc
 *  that have triggered (see TukPIRQ_REGISTERED_BITMASK).
 *
 */
#define DukIPC_MSG_NATURE_PIRQ_TRIGGERED      MukVAL_TYPED_BF(TukIPC_MSG_NATURE, 1U)


/**
 * @brief Constant defining the IPC Message Nature value when IPC Message
 *  Contents is a set of Notification sent by other ukProcs.
 *
 * This constant defines the IPC Message Nature value when the IPC Message
 *  Contents is a set of Notifications (simple flag of one bit) sent by other
 *  ukProcs to the Recipient ukProc (see TukUKPROC_IPC_NOTIFICATION_BITMASK).
 *
 */
#define DukIPC_MSG_NATURE_UKPROC_NOTIFICATION  MukVAL_TYPED_BF(TukIPC_MSG_NATURE, 2U)

/**
 * @brief Constant defining the IPC Message Nature value when IPC Message
 *  Contents is a set of uKernel Signal.
 *
 * This constant defines the IPC Message Nature value when the IPC Message
 *  Contents is a set of uKernel Signals sent by the uKernel to the
 *  Recipient ukProc (see TukUKSIGNAL_NOTIFIED_BITMASK).
 *
 * @note Only the uKernel Signals of Nature Information can be received as IPC
 *  Message.
 */
#define DukIPC_MSG_NATURE_UKSIGNAL_NOTIFIED    MukVAL_TYPED_BF(TukIPC_MSG_NATURE, 3U)



#if defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_ENABLED)
/**
 * @brief Constant defining the IPC Message Nature value when IPC Message
 *  Contents is issued from a service request from Non-Secure World.
 *
 * This constant defines the IPC Message Nature value when the IPC Message
 *  Contents is issued from a service request from Non-Secure World.
 *
 * @implementation This IPC Message Nature is supported only if TrustZone is
 *  enabled.
 */
#define DukIPC_MSG_NATURE_NSWORLD_REQUEST     MukVAL_TYPED_BF(TukIPC_MSG_NATURE, 4U)
#endif /* defined(SukCONFIG_HW_MCU_CORE_ARM_CMX_TRUSTZONE_ENABLED)*/


/**
 * @brief C-Constant defining an invalid value to be used for IPC Message
 *  Nature.
 *
 * Definition of the C-Constant for the invalid value to be used for IPC
 *  Message Nature.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukIPC_MSG_NATURE_INVALID             MukVAL_TYPED(TukIPC_MSG_NATURE, 0U)



/* //////////////////////////////////////////////////////////////////////// */
/*                      C-CONSTANTS - UKPROC EXCEPTION                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the ukProc Exception Event Nature Flag for ukProc
 *  Registered PIRQ.
 *
 * This C-Constant defines the ukProc Exception Event Nature Flag for ukProc
 *  Registered PIRQ (Peripheral IRQ).
 *
 * The ukProc Exception Event Source associated to this Nature contains the
 *  value:
 *  - (TukPIRQ_REGISTERED_BITMASK) Each bit set in the bitmask indicates that
 *  a ukProc Registered PIRQ (Peripheral IRQ) has triggered.
 *  The bit number corresponds to the Registered Identifier value of the
 *  Peripheral IRQ (see TukPIRQ_REGISTRATION_ID). The bit number 0 is the
 *  leftmost bit in the structure.
 */
#define DukUKPROC_EXCEPTION_EVENT_NATURE_PIRQ_TRIGGERED_FLAG                  \
                        MukVAL_TYPED_BF(TukUKPROC_EXCEPTION_EVENT_NATURE, 1U)


/**
 * @brief C-Constant defining the ukProc Exception Event Nature Flag for ukProc
 *  IPC Notification.
 *
 * This C-Constant defines the ukProc Exception Event Nature Flag for ukProc
 *  IPC Notification.
 *
 * The ukProc Exception Event Source associated to this Nature contains the
 *  value:
 *  - (TukUKPROC_IPC_NOTIFICATION_BITMASK) Each bit set in the bitmask refers
 *  to a ukProc having sent an IPC Notification to the ukProc (see
 *  TukUKPROC_IPC_NOTIFICATION_BITMASK).
 * The bit number corresponds to the ukProc Index (PIDX) value of the
 *  ukProc having sent the Notification (see TukUKPROC_PIDX). The bit
 *  number 0 is the leftmost bit in the structure.
 */
#define DukUKPROC_EXCEPTION_EVENT_NATURE_UKPROC_IPC_NOTIFICATION_FLAG         \
                        MukVAL_TYPED_BF(TukUKPROC_EXCEPTION_EVENT_NATURE, 2U)


/**
 * @brief C-Constant defining the ukProc Exception Event Nature Flag for ukProc
 *  Registered PIRQ.
 *
 * This C-Constant defines the ukProc Exception Event Nature Flag for ukProc
 *  Registered PIRQ (Peripheral IRQ).
 *
 * The ukProc Exception Event Source associated to this Nature contains the
 *  value:
 *  - (TukUKSIGNAL_NOTIFIED_BITMASK) Each bit set in
 *  the bitmask refers to a uKernel Signal having been sent to the ukProc (see
 *  TukUKSIGNAL_NOTIFIED_BITMASK).
 *  The bit number corresponds to the uKernel Signal Identifier (see
 *  TukSIGNAL_ID). The bit number 0 is the leftmost bit in the structure.
 */
#define DukUKPROC_EXCEPTION_EVENT_NATURE_UKSIGNAL_NOTIFIED_FLAG               \
                        MukVAL_TYPED_BF(TukUKPROC_EXCEPTION_EVENT_NATURE, 3U)




/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - UKERNEL SIGNALS                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Identifier of a uKernel Signal when a ukProc
 *  Child has been terminated.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to the ukProc
 *  ukProc when one of the ukProc Child Instance of which it has previously
 *  triggered the creation (see ukUKProcInstantiate()) has been terminated .
 *
 * @usage Following the reception of this uKernel Signal, the behavior of the
 *  ukProc Parent depends of ukApp Security Policy:
 *   - It can consider that the termination of the ukProc Child is expected and
 *    normal.
 *   - It can try to trigger the creation of a new ukProc Child Instance to
 *    ensure continuity of provided services.
 *   - It can decide to take action at the Platform level (e.g. MCU reset to
 *    start a new uKernel Session).
 */
#define DukSIGNAL_ID_UKPROC_CHILD_TERMINATED    MukVAL_TYPED(TukSIGNAL_ID, 0U)


/**
 * @brief C-Constant defining the Identifier of a uKernel Signal when its
 *  ukProc Parent has been terminated.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to the ukProc
 *  Child when the ukProc Parent Instance having created it (see
 *  ukUKProcInstantiate()) has been terminated.
 *
 * @usage Following the reception of this uKernel Signal, the behavior of the
 *  ukProc Child depends of ukApp Security Policy:
 *   - It can consider that the termination of the ukProc Parent is expected
 *    and normal.
 *   - It can decide to take action at the Platform level (e.g. MCU reset to
 *    start a new uKernel Session).
 */
#define DukSIGNAL_ID_UKPROC_PARENT_TERMINATED   MukVAL_TYPED(TukSIGNAL_ID, 1U)



/**
 * @brief C-Constant defining the Identifier of a uKernel Signal informing a
 *  ukProc that it will be updated.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to a ukProc
 *  to inform it that its ukApp code is going to be updated.
 *
 * @usage The behavior of the ukProc upon this uKernel Signal is ukApp policy
 *  dependent, but it may:
 *  - Copy its internal data that need to be preserved during the update in
 *   persistent memory (the structure of these data is ukApp proprietary).
 *  - Erase all its internal sensitive data considering that a new
 *   personalization of its internal data will occur after the update.
 */
#define DukSIGNAL_ID_UKPROC_UPDATE_PLANNED      MukVAL_TYPED(TukSIGNAL_ID, 2U)


/**
 * @brief C-Constant defining the Identifier of a uKernel Signal informing that
 *  a ukProc Abort has occurred.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to all the
 *  ukProcs to inform that a ukProc Abort has occurred.
 *
 * @usage A ukProc Abort shall in most of the implementation never happen:
 *  receiving such uKernel Signal shall thus be considered as a serious issue
 *  (unspotted bug, unexpected code behavior, security issue due to external
 *  attacks, hardware platform malfunction) that may affect the expected
 *  behavior of all the ukProcs.
 *  On the reception of such a uKernel Signal, it is recommended for the
 *  ukProcs having the proper credentials to:
 *   - Stop sensitive action and wipe sensitive information.
 *   - Log the ukProc Abort internally; if possible send information on the
 *    ukProc Abort to external system.
 *   - Trigger a uKernel Session End (see DukPLATFORM_ATTRIBUTE_TAG_STATE).
 */
#define DukSIGNAL_ID_UKPROC_ABORT_OCCURED       MukVAL_TYPED(TukSIGNAL_ID, 3U)


/**
 * @brief C-Constant defining the Identifier of a uKernel Signal informing that
 *  a ukProc Cleanup process has been unsuccessful.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to all the
 *  ukProcs to inform that a ukProc Cleanup process has been unsuccessful.
 *
 * @usage A ukProc Cleanup process SHOULD NEVER fail: receiving such uKernel
 *  Signal shall thus be considered as a serious issue (security issue due to
 *  external attacks, hardware platform malfunction) that may affect the
 *  expected behavior of all the ukProcs.
 *  On the reception of such a uKernel Signal, it is recommended for the
 *  ukProcs having the proper credentials to:
 *   - Stop sensitive action and wipe sensitive information.
 *   - Log the ukProc Abort internally; if possible send information on the
 *    ukProc Abort to external system.
 *   - Trigger a uKernel Session End (see DukPLATFORM_ATTRIBUTE_TAG_STATE).
 */
#define DukSIGNAL_ID_UKPROC_CLEANUP_IN_ERROR    MukVAL_TYPED(TukSIGNAL_ID, 4U)


/**
 * @brief C-Constant defining the Identifier of a uKernel Signal for a
 *  Peripheral IRQ not acknowledged in time by a ukProc.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to a ukProc
 *  to indicate that a Peripheral IRQ to which the ukProc has registered has
 *  not been acknowledged in time by itself.
 *
 * @implementation In addition to the sending of this uKernel Signal, the
 *  uKernel has set the Peripheral IRQ as Disabled for the ukProc, and
 *  performed in its place to the acknowledge of the Peripheral IRQ.
 */
#define DukSIGNAL_ID_PIRQ_ACK_TIMEOUT           MukVAL_TYPED(TukSIGNAL_ID, 5U)



/**
 * @brief C-Constant defining the Identifier of a uKernel Signal sent upon a
 *  security Alert.
 *
 * This C-Constant defines the uKernel Signal sent by the uKernel to a ukProc
 *  to indicate that possible security issue has been detected at uKernel
 *  system level.
 *
 * @note The ukProc shall takes the minimum time possible to manage this
 *  uKernel Signal in order to let the other ukProcs manage it also as soon as
 *  possible.
 *
 * @usage The response to this Signal is ukApp Security Policy dependent, but
 *  it should:
 *  - Wipe its sensitive volatile data present in memory.
 *  - Decide to log the security alert information for further audit.
 */
#define DukSIGNAL_ID_SECURITY_ALERT             MukVAL_TYPED(TukSIGNAL_ID, 6U)


/**
 * @brief C-Constant defining the Identifier of a uKernel Signal sent upon
 *  a change in used MCU Clocks set.
 *
 * This C-Constant defines the Identifier of the uKernel Signal sent upon a
 *  change in used MCU Clocks set (and thus probably of CPU Core Clock
 *  frequency).
 */
#define DukSIGNAL_ID_MCU_ClOCKS_UPDATED         MukVAL_TYPED(TukSIGNAL_ID, 7U)

/**
 * @brief C-Constant defining the maximum value of the Identifier of a
 *  uKernel Signal.
 *
 * Definition of the C-Constant for the maximum value of the Identifier of a
 *  uKernel Signal (see TukSIGNAL_ID).
 */
#define DukSIGNAL_ID_MAX                                                      \
            MukVAL_TYPED(TukSIGNAL_ID, DukSIGNAL_ID_MCU_ClOCKS_UPDATED)



/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - PERIPHERAL IRQ INDEX                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the count of Peripheral IRQ supported.
 *
 * Definition of the C-Constant for the count of Peripheral IRQ supported
 *  by the uKernel for the given MCU family.
 *
 * @note This value may be less than the number of IRQs supported by the
 *  hardware interruption controller of the MCU family (some Peripherals
 *  may not be aimed to be used by uKernel).
 *
 * @implementation This value is MCU Device specific.
 */
#define DukPIRQ_IDX_COUNT  MukVAL_TYPED(TukCOUNT8, (DukPIRQ_IDX_MAX + 1U))

/**
 * @brief C-Constant defining an invalid value to be used for Peripheral IRQ
 *  MCU Index.
 *
 * Definition of the C-Constant for the invalid value to be used for Peripheral
 *  IRQ MCU Index.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukPIRQ_IDX_INVALID MukVAL_TYPED(TukPIRQ_MCU_IDX, 0xFFU)


/* //////////////////////////////////////////////////////////////////////// */
/*                CONSTANTS - PERIPHERAL IRQ REGISTRATION ID                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant defining the minimal Peripheral IRQ Registered Identifier
 *  value.
 *
 * This constant defines the minimal Registered Identifier valid value for
 *  referencing a Peripheral IRQ registered by a ukProc.
 */
#define DukPIRQ_REGISTRATION_ID_MIN   MukVAL_TYPED(TukPIRQ_REGISTRATION_ID,\
                                                      0U)

/**
 * @brief Constant defining the maximal Peripheral IRQ Registered Identifier
 *  value.
 *
 * This constant defines the maximal Registered Identifier valid value for
 *  referencing a Peripheral IRQ registered by a ukProc.
 */
#define DukPIRQ_REGISTRATION_ID_MAX     MukVAL_TYPED(                         \
            TukPIRQ_REGISTRATION_ID,                                          \
            (DukCONFIG_OPTION_UKAPP_PIRQ_REGISTERED_COUNT_MAX - 1U)           \
                                                    )

/**
 * @brief Constant defining the Peripheral IRQ Registered Identifier
 *  special value for referencing the set of all the Peripheral IRQs
 *  registered by a ukProc.
 *
 * This constant defines the Peripheral IRQ Registered Identifier special
 *  value for referencing all the Peripheral IRQs registered by a uKernel
 *  Process.
 */
#define  DukPIRQ_REGISTRATION_ID_UKPROC_ALL    MukVAL_TYPED(TukPIRQ_REGISTRATION_ID, 0x00FF)


/**
 * @brief C-Constant defining an invalid value to be used for Peripheral IRQ
 *  Registered Identifier.
 *
 * Definition of the C-Constant for the invalid value to be used for Peripheral
 *  IRQ Registered Identifier.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukPIRQ_REGISTRATION_ID_INVALID                                       \
            MukVAL_TYPED(TukPIRQ_REGISTRATION_ID, 0xFFFFUL)


/* //////////////////////////////////////////////////////////////////////// */
/*                  CONSTANTS - PERIPHERAL IRQ ATTRIBUTES                   */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief Policy for uKernel automatic acknowledge of a triggered Peripheral IRQ.
 *
 *  When this flag is not set, the a Peripheral IRQ notified to a ukProc will
 *  require to be specifically acknowledged by the ukProc before being active
 *  again (see ukirqmPIRQ_STATE_ACK_PENDING_FLAG below). If this flag is set, the
 *  acknowledge is automatic (no specific action needed from the Process).
 */
#define DukPIRQ_ATTRIBUTES_CONFIG_ACKAUTO_FLAG       MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 2U)


/**
 * @brief Enable the Peripheral IRQ for the given Process.
 *
 * When this flag is set, the Peripheral IRQ is enabled for the ukProc and an
 *  IPC notification will be sent by the uKernel to the ukProc when the
 *  Peripheral IRQ is triggered.
 */
#define DukPIRQ_ATTRIBUTES_UKPROC_ENABLED_FLAG   MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 4U)


/**
 * @brief Indicates that the Peripheral IRQ is waiting to be acknowledged.
 *
 *  When this flag is set, the Peripheral IRQ has been triggered and the uKernel
 *  is waiting for its acknowledge. The acknowledge shall be done by using
 *  the ukirqmPeripheralIRQAck function.
 *  This flag is never set if the ukirqmPIRQ_STATE_ACK_AUTO_BIT is set.
 */
#define DukPIRQ_ATTRIBUTES_UKPROC_ACKPENDING_FLAG   MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 5U)


/**
* @brief Indicates if the Peripheral IRQ is registered by at least one Process.
*
* When this flag is set, the Peripheral IRQ is registered by at least one Process.
*/
#define DukPIRQ_ATTRIBUTES_PLATFORM_REGISTERED_FLAG   MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 8U)


/**
* @brief Indicates if the Peripheral IRQ is enabled in the platform hardware
* interruption controller.
*
* When this flag is set, the Peripheral IRQ is enabled in the platform hardware
* interruption controller. If this flag is not set, it means that the uKernel
* is waiting for the acknowledge of a registered ukProc for this Peripheral IRQ.
*/
#define DukPIRQ_ATTRIBUTES_PLATFORM_ENABLED_FLAG   MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 9U)

/**
 * @brief Indicates that the Peripheral IRQ Attribute value is meaningful.
 *
 * If this flag is not set, then the Peripheral IRQ Attribute value is
 *  not meaningful, and the value of the other flags is not significant.
 *
 * @note In case there is no error, uKernel Services always returns an
 *  Attribute value with this flag set.
 *
 * @note When using Attribute for configuration, this flag is ignored by
 *  the uKernel.
 */
#define DukPIRQ_ATTRIBUTES_MEANINGFUL_FLAG    MukVAL_TYPED_BF(TukPIRQ_ATTRIBUTES, 15U)


/**
 * @brief C-Constant defining an invalid value to be used for Peripheral IRQ
 *  Attribute.
 *
 * Definition of the C-Constant for the invalid value to be used for Peripheral
 *  IRQ Attribute.
 *
 * @note The DukPIRQ_ATTRIBUTES_MEANINGFUL_FLAG is for sure reset in this
 *   value!
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukPIRQ_ATTRIBUTES_INVALID       MukVAL_TYPED(TukPIRQ_ATTRIBUTES, 0x0000U)


/**
 * @brief C-Constant defining the mask of valid flags for Peripheral IRQ
 *  Configuration Attributes.
 *
 * Definition of the C-Constant of the mask of valid flags for Peripheral IRQ
 *  Configuration Attributes value.
 */
#define DukPIRQ_ATTRIBUTES_CONFIG_VALID_MASK                                  \
    MukVAL_TYPED(TukPIRQ_ATTRIBUTES,                                          \
                 DukPIRQ_ATTRIBUTES_UKPROC_ENABLED_FLAG                     | \
                 DukPIRQ_ATTRIBUTES_CONFIG_ACKAUTO_FLAG                     | \
                 0U                                                           \
                )

/* //////////////////////////////////////////////////////////////////////// */
/*                    CONSTANTS - PERIPHERAL IRQ ACTIONS                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant defining the Action value for Acknowledging a Peripheral IRQ
 *  registered in a ukProc.
 *
 * This constant defines the Action value for Acknowledging a Peripheral IRQ
 *  in a ukProc, reporting to the uKernel that the management of
 *  Peripheral IRQ is finalized for the given ukProc.
 *
 * It is possible to apply the 'Acknowledging' Action to all the Peripheral
 *  IRQs registered to the ukProc by using the special value
 *  DukPIRQ_REGISTRATION_ID_UKPROC_ALL.
 *
 * @note A Peripheral IRQ will be enabled again in the Platform (
 *  at hardware interruption controller level) only when all the uKernel
 *  Processes having this Peripheral IRQ Registered and Enabled have
 *  acknowledged it (no ukProc will receive new triggering
 *  notification from the uKernel till then).
 *
 * @note The ukProcs that have the ukPIRQ_STATE_PROC_ACK_AUTO
 *  flag set for a given Peripheral IRQ have the Acknowledging Action performed
 *  automatically by the uKernel (and thus do not need to invoke this
 *  function for the Peripheral IRQ that have this flag). The automatic
 *  Acknowledging is performed just before notifying the ukProc of the
 *  triggering.
 *
 * @note If a Peripheral IRQ has triggered several times before being
 *  effectively processed by a ukProc (either by the effective
 *  reception of the IPC notification or the invocation of the 'ukappPIRQ'
 *  Entry Point), then only one triggering will be considered by the uKernel
 *  for the ukProc (i.e. no several IPC notifications or invocations
 *  of the Entry Point will be done). New triggering will be taken into account
 *  for this ukProc only after the starting of the processing of the
 *  current triggering of the Peripheral IRQ.
 *
 * @note If a Peripheral IRQ is being disabled or unregistered of a uKernel
 *  Process, then the uKernel will automatically acknowledge it for this
 *  ukProc while performing one of this action.
 */
#define DukPIRQ_ACTION_ACKNOWLEDGE                                            \
    MukVAL_TYPED(TukPIRQ_ACTION, 0U)


/**
 * @brief Constant defining the Action value for Enabling a Peripheral IRQ
 *  registered in a ukProc.
 *
 * This constant defines the Action value for Enabling a Peripheral IRQ
 *  in a ukProc.
 * When a Peripheral IRQ is enabled, then the uKernel will upon triggering
 *  of the Peripheral IRQ either send an IPC notification (see
 *  DukIPC_MSG_NATURE_PIRQ_TRIGGERED) or invoke the Entry Point 'ukappPIRQ'
 *  of the ukProc.
 *
 * It is possible to apply the 'Enabling' Action to all the Peripheral IRQs
 *  registered to the ukProc by using the special value
 *  DukPIRQ_REGISTRATION_ID_UKPROC_ALL.
 *
 * @note This Action enables the Peripheral IRQ only for the given uKernel
 *  Process. It has no effect on the Peripheral IRQ state of other uKernel
 *  Processes.
 *
 * @note The uKernel enables the Peripheral IRQ at Platform level
 *  only if the Peripheral IRQ is enabled in at least on ukProc.
 */
#define DukPIRQ_ACTION_ENABLE                                                 \
    MukVAL_TYPED(TukPIRQ_ACTION, 1U)

/**
 * @brief Constant defining the Action value for Disabling a Peripheral IRQ
 *  registered in a ukProc.
 *
 * This constant defines the Action value for Disabling a Peripheral IRQ
 *  in a ukProc.
 * When a Peripheral IRQ is disabled, then the uKernel will ignore the
 *  triggering of the Peripheral IRQ for the ukProc.
 *
 * It is possible to apply the 'Disabling' Action to all the Peripheral IRQs
 *  registered to the ukProc by using the special value
 *  DDukPIRQ_REGISTRATION_ID_UKPROC_ALL.
 *
 * @note In case Acknowledgment by the ukProc was pending for the
 *  Peripheral IRQ, the uKernel will automatically perform this Acknowledgment
 *  while Disabling the Peripheral IRQ.
 *
 * @note This Action disables the Peripheral IRQ only for the given uKernel
 *  Process. It has no effect on the Peripheral IRQ state of other uKernel
 *  Processes.
 *
 * @note The uKernel disables the Peripheral IRQ at Platform level
 *  only if the Peripheral IRQ is disabled in all the ukProcs that
 *  have registered it.
 */
#define DukPIRQ_ACTION_DISABLE                                                \
    MukVAL_TYPED(TukPIRQ_ACTION, 2U)



/* //////////////////////////////////////////////////////////////////////// */
/*                 C-CONSTANTS - ADDRESS BLOCK IDENTIFIERS                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the LSb of the Reference field in Address
 *  Block Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Reference field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_REFERENCE_LSb                                      \
    MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the MSb of the Reference field in Address Block
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Reference field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_REFERENCE_MSb                                      \
    MukVAL_TYPED(TukBITNUM, 7U)

/**
 * @brief C-Constant defining the Mask for the Reference field in Address
 *  Block Identifier.
 *
 * Definition of the C-Constant for the Mask of significant bits of the
 *  Reference field in Address Block Identifier (ABID).
 */
#define DukADDRESSBLOCK_ID_REFERENCE_MASK                                     \
    MukVAL_TYPED(TukADDRESSBLOCK_ID,                                          \
                 MukVAL_FIELD_BITMASK32(DukADDRESSBLOCK_ID_REFERENCE_LSb,     \
                                      DukADDRESSBLOCK_ID_REFERENCE_MSb        \
                                 )                                            \
                )

/**
 * @brief C-Constant defining the LSb of the Nature field in Address Block
 *  Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Nature
 *  field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_NATURE_LSb                                         \
    MukVAL_TYPED(TukBITNUM, 8U)

/**
 * @brief C-Constant defining the MSb of the Nature field in Address Block
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Nature
 *  field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_NATURE_MSb                                         \
    MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the Mask for the Address Block Nature field.
 *
 * Definition of the C-Constant for the Mask of significant bits of the Nature
 *  field in the Address Block Identifier (ABID).
 */
#define DukADDRESSBLOCK_ID_NATURE_MASK                                        \
    MukVAL_TYPED(TukADDRESSBLOCK_ID,                                          \
                 MukVAL_FIELD_BITMASK32(DukADDRESSBLOCK_ID_NATURE_LSb,        \
                                      DukADDRESSBLOCK_ID_NATURE_MSb           \
                                 )                                            \
                )

/**
 * @brief C-Constant defining the LSb of the Tag field in Address Block
 *  Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Tag
 *  field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_TAG_LSb                                            \
    MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the MSb of the Tag field in Address Block
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Tag
 *  field in Address Block Identifier C-Type internal structure.
 */
#define DukADDRESSBLOCK_ID_TAG_MSb                                            \
    MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the Mask for the Address Block Identifier Tag
 *  field.
 *
 * Definition of the C-Constant for the Mask of significant bits of the Tag
 *  field in the Address Block Identifier (ABID).
 */
#define DukADDRESSBLOCK_ID_TAG_MASK                                           \
    MukVAL_TYPED(TukADDRESSBLOCK_ID,                                          \
                 MukVAL_FIELD_BITMASK32(DukADDRESSBLOCK_ID_TAG_LSb,           \
                                      DukADDRESSBLOCK_ID_TAG_MSb              \
                                 )                                            \
                )

/**
 * @brief C-Constant defining the Nature value for referencing an Extra Address
 *  Block using its Descriptor entry index.
 *
 * Definition of the C-Constant for the Nature value for referencing an Extra
 *  Address Block using its Descriptor entry index.
 *
 * This index corresponds to the entry index of its Extra Address Block
 *  Descriptor in the Extra Address Block Descriptor List present in the ukApp
 *  Descriptor (see field <AddressBlockExtraDescriptorList> in
 *  TukUKAPP_DESCRIPTOR).
 * The first entry in the list has a null(0) index.
 *
 * @note An Address Block Identifier of this Nature cannot be transformed in
 *  an Address Block Bundle Identifier.
 *
 * @usage An Address Block Identifier of this Nature can be used only locally
 *  in the Owner ukProc of the Extra Address Block. If used in other ukProc,
 *  it will be interpreted in the local context of the other ukProc, and thus,
 *  if valid, will reference a different Extra Address Block belonging to the
 *  other ukProc.
 *
 * @usage The Reference field of an Address Block Identifier of this Nature
 *  shall be in the range
 *  [0 ... (<AddressBlockExtraDescriptorCount>-1)].
 */
#define DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX                                   \
    MukVAL_TYPED(TukADDRESSBLOCK_ID_NATURE, 0x80UL)

/**
 * @brief C-Constant defining the Nature value for referencing a Shared Buffer
 *  using its Descriptor entry index.
 *
 * Definition of the C-Constant for the Nature value for referencing a Shared
 *  Buffer using its Descriptor entry index.
 *
 * This index corresponds to the entry index of its Shared Buffer Descriptor
 *  in the Shared Buffer Descriptor List present in the ukApp Descriptor (see
 *  field <SharedBufferDescriptorList> in TukUKAPP_DESCRIPTOR).
 * The first entry in the list has a null(0) index.
 *
 * @usage An Address Block Identifier of this Nature can be used only locally
 *  in the Owner ukProc of the Shared Buffer. If used in other ukProc,
 *  it will be interpreted in the local context of the other ukProc, and thus,
 *  if valid, will reference a different Shared Buffer belonging to the other
 *  ukProc.
 *
 * @usage An Address Block Identifier of this Nature can be transformed using
 *  ukAddressBlockGetBundleID() in an Address Block Bundle Identifier (see
 *  DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID).
 *
 * @usage The Reference field of an Address Block Identifier of this Nature
 *  shall be in the range [0 ... (<SharedBufferDescriptorCount>-1)].
 */
#define DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX                            \
    MukVAL_TYPED(TukADDRESSBLOCK_ID_NATURE, 0x90UL)


/**
 * @brief C-Constant defining the Nature value for referencing a Shared Buffer
 *  using its Bundle Identifier.
 *
 * Definition of the C-Constant for the Nature value for referencing a Shared
 *  Buffer using its Bundle Identifier.
 * A Bundle Identifier is a uKernel identifier that is unique for each Shared
 *  Buffer defined in all the ukApps present in the ukApps Bundle. It allows
 *  to reference unambiguously a Shared Buffer even when the current ukProc
 *  is not its Owner ukProc, and thus has to be used for referencing Shared
 *  Buffer transferred to other ukProcs.
 *
 * @robustness It is possible for the current ukProc to forge a Bundle
 *  Identifier and create an Address Block Identifier of this Nature to try
 *  to access to other Shared Buffers. However, as the access to a Shared
 *  Buffer is allowed only once its Owner ukProc has granted some credentials
 *  for the current ukProc AND has transferred the Shared Buffer to it, no
 *  unauthorized access can occur.
 *
 * @implementation The Bundle Identifier value associated to each Shared Buffer
 *  is fixed during a whole uKernel Session. Its value is thus independent of
 *  the various set of ukProcs present during the uKernel Session.
 *
 * @usage An Address Block Identifier of Nature Shared Buffer Bundle Identifier
 *  can be obtained either:
 *  - By using ukAddressBlockGetBundleID() on an Address Block Identifier
 *   of Nature DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX.
 *  - By receiving it from another ukProc (through IPC, ...) when this other
 *   ukProc aims at transferring the referenced Shared Buffer.
 *
 * @usage An Address Block Identifier of this Nature (Bundle Identifier) has to
 *  be used for all the uKernel Privileged Services managing Shared Buffer:
 *  ukSharedBufferResetCredentials(), ukSharedBufferAddCredentials(),
 *  ukSharedBufferTransfer().
 *
 * @usage The Reference field of an Address Block Identifier this Nature shall
 *  be in the range [0 ... (DukCONFIG_OPTION_SHAREDBUFFER_COUNT_MAX-1)]
 */
#define DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID                      \
    MukVAL_TYPED(TukADDRESSBLOCK_ID_NATURE, 0xD1UL)

/**
 * @brief C-Constant defining the tag value to be used for Address Block
 *  Identifier.
 *
 * Definition of the C-Constant for the tag value to be used for Address Block
 *  Identifier.
 *
 * @implementation The used value is the leftmost bytes of SHA256 hash of
 *  'ADDRESSBLOCK_ID'.
 *
 * @usage This C-Constant is used to populate the Tag field of an identifier
 *  in order to prevent misuse of its value for other purposes.
 */
#define DukADDRESSBLOCK_ID_TAG                                                \
    MukVAL_TYPED(TukADDRESSBLOCK_ID, 0x19E0UL)

/**
 * @brief C-Constant defining an invalid value to be used for Address Block
 *  Identifier.
 *
 * Definition of the C-Constant for the invalid value to be used for Address
 *  Block Identifier.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukADDRESSBLOCK_ID_INVALID                                            \
            MukVAL_TYPED(TukADDRESSBLOCK_ID, 0xFFFFFFFFUL)



/* //////////////////////////////////////////////////////////////////////// */
/*                     C-CONSTANTS - ADDRESS BLOCK LABEL                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining an invalid value to be used for Address Block
 *  Label.
 *
 * Definition of the C-Constant for the invalid value to be used for Address
 *  Block Label.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukADDRESSBLOCK_LABEL_INVALID                                         \
    MukVAL_TYPED(TukADDRESSBLOCK_LABEL, 0UL)


/* //////////////////////////////////////////////////////////////////////// */
/*                  C-CONSTANTS - ADDRESS BLOCK ATTRIBUTES                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant defining the Private Flag in Address Block Attributes.
 *
 * This constant defines the Attribute Flag for declaring an Address Block
 *  as Private to a ukApp.
 * When an Address Block is Private, the corresponding area can be declared in
 *  one and only one ukApp Descriptor, and only the corresponding ukApp can
 *  get access to this area.
 *
 * @implementation The uKernel enforces during its initialization that one and
 *  only one Private Flag is attached to a given Address Block, and that no
 *  other Address Blocks overlap with it.
 *  Else the ukApp Descriptor structure is considered as invalid.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_PRIVATE_FLAG                        \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 0U)

/**
 * @brief Constant defining the Mapped Exclusive Configuration Flag in Address
 *  Block Attributes.
 *
 * This constant defines the Attribute Flag for declaring an Address Block
 *  that can be mapped only in one ukProc at a time.
 *
 * @usage If a ukProc tries to get access to an Address Block that is already
 *  mapped in another ukProc, then the mapping will fail (the ukProc should
 *  retry later or synchronize using IPC with the other ukProc).
 *
 * @implementation #NOTYETSUPPORTED
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_EXCLUSIVE_FLAG                  \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 1U)

/**
 * @brief Constant defining the Non Mapped Configuration Flag in Address Block
 *  Attributes.
 *
 * This constant defines the Attribute Flag for declaring an Address Block
 *  that can be accessed even when not mapped.
 * When Non Mapped access is allowed, access (read / write) to an Address
 *  Block will not trigger a Fatal Error if it is not currently mapped in the
 *  ukProc. Instead, the access will trigger an MCU Exception Fault: the
 *  access will be properly conducted by the uKernel code, and execution will
 *  then resume in the ukProc code (without triggering a ukProc Abort). Note
 *  that such an access using MCU Exception Fault mechanism is quite slow (in
 *  general a few hundred CPU cycles to perform the read / write access).
 *
 * @implementation #NOTYETSUPPORTED
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_OPTIONAL_FLAG                   \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 2U)

/**
 * @brief Constant defining the Read Access Flag in Address Block Attributes
 *  for Address Block configuration.
 *
 * This constant defines the Attribute Flag for configuring an Address Block
 *  with Read access allowed for the given ukApp/Process.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG                           \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 4U)

/**
 * @brief Constant defining the Write Access Flag in Address Block Attributes
 *  for Address Block configuration.
 *
 * This constant defines the Attribute Flag for configuring an Address Block
 *  with Write access allowed for the given ukApp/Process.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG                          \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 5U)

/**
 * @brief Constant defining the Add Credentials Flag in Address Block
 *  Attributes for Address Block configuration.
 *
 * This constant defines the Attribute Flag for configuring an Address Block
 *  to allow onto which Credentials can be added
 *
 * Only Shared Buffers support this Attribute Flag.
 *
 *  ukProc can Setup Accesses for other ukProcs on this
 *  Address Block (see ukSharedBufferAddCredentials).
 * The Setup Accesses can be set only once for a given ukProc, and
 *  cannot be set for current ukProc or the ukProc that is
 *  the Owner of the Shared Buffer. The current ukProc can however
 *  perform the setup for several other ukProcs.
 *
 * Only the following Attribute Flags can be setup for another ukProc
 *  (see DukADDRESSBLOCK_ATTRIBUTES_SHAREDBUFFER_MASK):
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG
 *
 * @note If the ukProc to which a Shared Buffer has been transferred to
 *  is terminated, then all the accesses setup for other ukProcs are
 *  removed, and the Shared Buffer is automatically transferred back to its
 *  Owner.
 *
 * @note If the Owner ukProc of a Shared Buffer that has been transferred to
 *  another uKproc is terminated, it will not affect the credentials setup on
 *  the Shared Buffers, neither its usage. However, if the Shared Buffer has
 *  not been transferred, then all its credentials are reset.
 *
 * @note Only the Address Block of type Shared Buffer can be transferred to
 *  another ukProc.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG                \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 6U)

/**
 * @brief Constant defining the Transfer Flag in Address Block Attributes
 *  for Address Block configuration.
 *
 * This constant defines the Attribute Flag for configuring an Address
 *  Block with transfer capability for the given ukProc.
 * Only Address Block of type Shared Buffers supports this Attribute Flag
 *  and can be transferred.
 * Once the Address Block is transferred, the Managing ukProc having done the
 *  transfer loses all its Credentials on the Address Block (any access to it
 *  will raise a Fatal Error).
 *
 * The Attribute Flag DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG is set
 *  if the current ukProc is granted to transfer the given Shared
 *  Buffer.
 *
 * @note It is up to the sender and recipient of the Shared Buffer to
 *  synchronize for the transfer, for example by exchanging the ABID of the
 *  Address Block through IPC.
 *
 * @note If the ukProc to which a Shared Buffer has been transferred to
 *  is terminated, then the Shared Buffer is automatically transferred back to
 *  its Owner, and the credentials for other ukProcs are reset.
 *
 * @note If the Owner of a Shared Buffer is terminated, it does not prevent
 *  ukProc with this flag to perform transfer of the Shared Buffer.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG                       \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_ATTRIBUTES, 7U)



/**
 * @brief C-Constant defining an invalid value to be used for Address Block
 *  Attribute.
 *
 * Definition of the C-Constant for the invalid value to be used for Address
 *  Block Attribute.
 *
 * @note The DukADDRESSBLOCK_ATTRIBUTES_VALID_FLAG is for sure reset in this
 *   value!
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukADDRESSBLOCK_ATTRIBUTES_INVALID                                    \
            MukVAL_TYPED(TukADDRESSBLOCK_ATTRIBUTES, 0x0000U)


/**
 * @brief Constant helper combining the Read and Write Access Flags in Address
 *  Block Attributes.
 *
 * This constant helper combines the Attribute Flags for configuration an
 *  Address Block with Read and Write access allowed.
 */
#define DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READWRITE_FLAGS                     \
            MukVAL_TYPED(TukADDRESSBLOCK_ATTRIBUTES,                          \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG |                 \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG)



/**
 * @brief Constant defining the Mask for the Address Block Attributes value
 *  that can be used for definition in ukApp Descriptor.
 *
 * This constant defines the Mask of significant bits in the Address Block
 *  Attributes value (i.e. each bit that corresponds to a valid flag is set
 *  in the mask) that are valid for the definition of an Address Block in
 *  ukApp Descriptor (see TukADDRESSBLOCK_EXTRA_DESCRIPTOR).
 */
#define DukADDRESSBLOCK_ATTRIBUTES_EXTRA_DESCRIPTOR_MASK                      \
            MukVAL_TYPED(TukADDRESSBLOCK_ATTRIBUTES,                          \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_PRIVATE_FLAG              | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_EXCLUSIVE_FLAG        | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_OPTIONAL_FLAG         | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG                 | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG                | \
                0U)

/**
 * @brief Constant defining the Mask for the Address Block Attributes of a
 *  Shared Buffer.
 *
 * This constant defines the Mask of Flags in the Address Block Attributes
 *  value of a Shared Buffer (see
 *  DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG and
 *  ukSharedBufferAddCredentials()).
 */
#define DukADDRESSBLOCK_ATTRIBUTES_SHAREDBUFFER_MASK                          \
            MukVAL_TYPED(TukADDRESSBLOCK_ATTRIBUTES,                          \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG                 | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG                | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG      | \
                DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG             | \
                0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                      CONSTANTS - ADDRESS BLOCK STATE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Address Block State flag for Address Block
 *  being currently mapped in its Owner ukProc.
 *
 * Definition of the C-Constant the Address Block State flag indicating that
 *  the Address Block is currently mapped in its Owner ukProc.
 */
#define DukADDRESSBLOCK_STATE_MAPPED_OWNER_FLAG                               \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_STATE, 0U)

/**
 * @brief C-Constant defining the Address Block State flag for Address Block
 *  being currently mapped in its Managing ukProc.
 *
 * Definition of the C-Constant the Address Block State flag indicating that
 *  the Address Block is currently mapped in its Managing ukProc.
 *
 * @note Both flags DukADDRESSBLOCK_STATE_MAPPED_OWNER_FLAG and
 *  DukADDRESSBLOCK_STATE_MAPPED_MANAGING_FLAG can be set if:
 *   - Its Owner ukProc is also the Managing ukProc. In that case the flag
 *    DukADDRESSBLOCK_STATE_TRANSFERRED_FLAG is not set.
 *   - The Address Block is mapped at the same time in its Owner ukProc and
 *    in its Managing ukProc (which is not its Owner ukProc). In that case
 *    the flag DukADDRESSBLOCK_STATE_TRANSFERRED_FLAG is also set.
 */
#define DukADDRESSBLOCK_STATE_MAPPED_MANAGING_FLAG                            \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_STATE, 1U)


/**
 * @brief C-Constant defining the Address Block State flag for Address Block
 *  being currently transferred to a ukProc.
 *
 * Definition of the C-Constant the Address Block State flag indicating that
 *  the Address Block has been transferred to a ukProc which is not its Owner
 *  ukProc.
 */
#define DukADDRESSBLOCK_STATE_TRANSFERRED_FLAG                                \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_STATE, 4U)


/**
 * @brief C-Constant defining the flag stating that an Address Block State
 *  value is meaningful.
 *
 * Definition of the C-Constant for the flag stating that an Address Block
 *  State value is meaningful.
 *
 * @note In case there is no error, uKernel Services always returns an
 *  Address Block State value with this flag set.
 *
 * @usage If this flag is not set, then an Address Block State value is not
 *  meaningful, and the state of the other flags is not significant.
 */
#define DukADDRESSBLOCK_STATE_MEANINGFUL_FLAG                                 \
            MukVAL_TYPED_BF(TukADDRESSBLOCK_STATE, 7U)


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - ADDRESS BLOCK WINDOW                     */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the maximal value for the Index of an Address
 *  Block Window.
 *
 * Definition of the C-Constant of the maximal value for the Index of an
 *  Address Block Window.
 *
 * @note This value is Platform AND uKernel Release dependent.
 */
#define DukADDRESSBLOCKWINDOW_IDX_MAX                                         \
            MukVAL_TYPED(TukADDRESSBLOCKWINDOW_IDX,                           \
                         (DukADDRESSBLOCKWINDOW_COUNT_MAX - 1U))


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - MCU REGISTER                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Magic Number used as key to allow the reading
 *  of a set of MCU Registers.
 *
 * Definition of the C-Constant for the Magic Number used as key to allow the
 *  reading of a set of MCU Registers (see ukMCURegisterRead()).
 *
 * @implementation The used value is the leftmost bytes of SHA256 hash of
 *  'MCUREGISTER_READ'.
 */
#define DukMCUREGISTER_READ_MAGIC32                                           \
                    MukVAL_TYPED(TukMAGIC32, 0xCD2CE1E9UL)


/**
 * @brief C-Constant defining the Magic Number used as key to allow the writing
 *  of a set of MCU Registers.
 *
 * Definition of the C-Constant for the Magic Number used as key to allow the
 *  writing of a set of MCU Registers (see ukMCURegisterWrite()).
 *
 * @implementation The used value is the leftmost bytes of SHA256 hash of
 *  'MCUREGISTER_WRITE'.
 */
#define DukMCUREGISTER_WRITE_MAGIC32                                          \
                    MukVAL_TYPED(TukMAGIC32, 0xAD535619UL)



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - DMA STREAM                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the LSb of the Reference field in DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Reference field in DMA Stream Identifier C-Type internal structure.
 */
#define DukDMAS_ID_REFERENCE_LSb                                              \
    MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the MSb of the Reference field in DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Reference field in DMA Stream Identifier C-Type internal structure.
 */
#define DukDMAS_ID_REFERENCE_MSb                                              \
    MukVAL_TYPED(TukBITNUM, 8U)

/**
 * @brief C-Constant defining the Mask for the DMA Stream Identifier Reference
 *  field.
 *
 * Definition of the C-Constant for the Mask of significant bits of the
 *  Reference field in the DMA Stream Identifier (DMAID).
 */
#define DukDMAS_ID_REFERENCE_MASK                                             \
    MukVAL_TYPED(TukDMAS_ID,                                                  \
                 MukVAL_FIELD_BITMASK32(DukDMAS_ID_REFERENCE_LSb,             \
                                      DukDMAS_ID_REFERENCE_MSb                \
                                 )                                            \
                )

/**
 * @brief C-Constant defining the LSb of the Tag field in DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Tag
 *  field in DMA Stream Identifier C-Type internal structure.
 */
#define DukDMAS_ID_TAG_LSb                                                    \
    MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the MSb of the Tag field in DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Tag
 *  field in DMA Stream Identifier C-Type internal structure.
 */
#define DukDMAS_ID_TAG_MSb                                                    \
    MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the Mask for the DMA Stream Identifier Tag
 *  field.
 *
 * Definition of the C-Constant for the Mask of significant bits of the Tag
 *  field in the DMA Stream Identifier (DMAID).
 */
#define DukDMAS_ID_TAG_MASK                                                   \
    MukVAL_TYPED(TukDMAS_ID,                                                  \
                 MukVAL_FIELD_BITMASK32(DukDMAS_ID_TAG_LSb,                   \
                                      DukDMAS_ID_TAG_MSb                      \
                                 )                                            \
                )


/**
 * @brief C-Constant defining the tag value to be used for DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant for the tag value to be used for DMA Stream
 *  Identifier.
 *
 * @implementation The used value is the leftmost bytes of SHA256 hash of
 *  'DMA_STREAM_ID'.
 *
 * @usage This C-Constant is used to populate the Tag field of an identifier
 *  in order to prevent misuse of its value for other purposes.
 */
#define DukDMAS_ID_TAG                                                        \
    MukVAL_TYPED(TukDMAS_ID, 0xDC08UL)


/**
 * @brief C-Constant defining an invalid value to be used for DMA Stream
 *  Identifier.
 *
 * Definition of the C-Constant for the invalid value to be used for DMA Stream
 *  Identifier.
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukDMAS_ID_INVALID                                                    \
            MukVAL_TYPED(TukDMAS_ID, 0xFFFFFFFFUL)


/**
 * @brief C-Constant defining the DMA Channel Hardware Identifier to use
 *  when no trigger is needed.
 *
 * Definition of the C-Constant for the DMA Channel Hardware Identifier to use
 *  when no trigger is needed.
 *
 * @usage This Identifier value has to be used for DMA transfer from internal
 *  memory to internal memory.
 */
#define DukDMAS_REQUEST_HW_ID_NONE                                            \
    MukVAL_TYPED(TukDMAS_REQUEST_HW_ID, 0xFFU)




/* //////////////////////////////////////////////////////////////////////// */
/*                     C-CONSTANTS - DMA STREAM INSTANCE                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining an invalid value to be used for DMA Stream
 *  Instance Identifier.
 *
 * Definition of the C-Constant for the invalid value to be used for DMA Stream
 *  Instance Identifier (DMAS IID).
 *
 * @usage This C-Constant is used to indicate that the value is invalid or not
 *  significant (due to processing error, unused field or parameter, ...).
 */
#define DukDMAS_IID_INVALID                                                   \
    MukVAL_TYPED(TukDMAS_IID, 0xFFFFFFFFUL)



/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - DMA STREAM STATE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Meaningless DMA Stream State.
 *
 * Definition of the C-Constant for the Meaningless DMA Stream State.
 * This value is returned by C-Function when an error has occurred, either
 *  from DMA Stream configuration, or from the DMA Engine hardware.
 *
 * @usage This C-Constant SHALL NOT be used for testing meaningless returned
 *  DMA Stream State. Instead, check SHALL BE done on the flag
 *  DukDMAS_STATE_MEANINGFUL_FLAG.
 */
#define DukDMAS_STATE_MEANINGLESS                                             \
                    MukVAL_TYPED(TukDMAS_STATE, 0U)

/**
 * @brief C-Constant defining the Configured flag in DMA Stream State.
 *
 * Definition of the C-Constant for the Configured flag in DMA Stream State.
 * This flag is set when the DMA Stream Instance has been properly configured.
 *
 * This flag is set if last invocation of ukDMAStreamInstanceTransferSetup()
 *  is successful.
 */
#define DukDMAS_STATE_CONFIGURED_FLAG                                         \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 0U)

/**
 * @brief C-Constant defining the Transfer Active flag in DMA Stream State.
 *
 * Definition of the C-Constant for the Transfer Active flag in DMA Stream
 *  State.
 *
 * This flag is set as soon as a DMA Stream transfer has been started.
 *
 * It remains set until the DMA Stream transfer is properly finished or is
 *  aborted.
 */
#define DukDMAS_STATE_TRANSFER_ACTIVE_FLAG                                    \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 4U)

/**
 * @brief C-Constant defining the Transfer Done flag in DMA Stream State.
 *
 * Definition of the C-Constant for the Transfer Done flag in DMA Stream
 *  State.
 *
 * This flag is set as soon as a started DMA Stream transfer has finished
 *  as expected after transferring the requested count of data.
 *
 * It remains set until the invocation of ukDMAStreamInstanceTransferSetup()
 *  or ukDMAStreamInstanceTransferStart().
 */
#define DukDMAS_STATE_TRANSFER_DONE_FLAG                                      \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 5U)

/**
 * @brief C-Constant defining the Aborted Error flag in DMA Stream State.
 *
 * Definition of the C-Constant for the Aborted Error flag in DMA Stream State.
 *
 * This flag is set when a started DMA Stream transfer has been aborted before
 *  reaching the given count of data to transfer.
 * The abortion may be cause by the following events:
 *  - Error occurring at hardware level during the transfer. In that case the
 *   flag DukDMAS_STATE_ERROR_TRANSFER_HW_FLAG is also set.
 *  - The DMA Stream transfer has been stopped before being completed by an
 *   invocation of ukDMAStreamInstanceTransferStop().
 *
 * It remains set until the invocation of ukDMAStreamInstanceTransferSetup()
 *  or ukDMAStreamInstanceTransferStart().
 */
#define DukDMAS_STATE_ERROR_ABORTED_FLAG                                      \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 8U)

/**
 * @brief C-Constant defining the hardware Transfer Error flag in DMA Stream
 *  State.
 *
 * Definition of the C-Constant for the hardware Transfer Error flag in DMA
 *  Stream State.
 *
 * This flag is set when an error has been reported at hardware level during
 *  the transfer by the DMA Engine.
 *
 * It remains set until the invocation of ukDMAStreamInstanceTransferSetup()
 *  or ukDMAStreamInstanceTransferStart().
 *
 * @note As an hardware transfer error aborts the current transfer,
 *  the flag DukDMAS_STATE_ERROR_ABORTED_FLAG is always set when this flag is
 *  set.
 */
#define DukDMAS_STATE_ERROR_TRANSFER_HW_FLAG                                  \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 10U)

/**
 * @brief C-Constant defining the Meaningful flag in DMA Stream State.
 *
 * Definition of the C-Constant for the Meaningful flag in DMA Stream State.
 *
 * @usage The other flags contained in the DMA Stream State SHALL BE
 *  interpreted only if this flag is set.
 */
#define DukDMAS_STATE_MEANINGFUL_FLAG                                         \
                    MukVAL_TYPED_BF(TukDMAS_STATE, 15U)

/**
 * @brief C-Constant defining the mask of error flags in DMA Stream State.
 *
 * Definition of the C-Constant of the mask of error flags in DMA Stream
 *  State.
 *
 * @note The error flags remain set until the invocation of
 *  ukDMAStreamInstanceTransferSetup() or ukDMAStreamInstanceTransferStart().
 */
#define DukDMAS_STATE_ERROR_MASK                                              \
    MukVAL_TYPED(TukDMAS_STATE,                                               \
                 DukDMAS_STATE_ERROR_ABORTED_FLAG                           | \
                 DukDMAS_STATE_ERROR_TRANSFER_HW_FLAG                       | \
                 0U                                                           \
                )

/* //////////////////////////////////////////////////////////////////////// */
/*                  C-CONSTANTS - DMA STREAM TRANSFER MODE                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the Source field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 * Source field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_SOURCE_FIELD_MSb                                \
    MukVAL_TYPED(TukBITNUM, 7U)

/**
 * @brief C-Constant defining the LSb of the Source field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 * Source field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_SOURCE_FIELD_LSb                                \
    MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the bitmask of the Source field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Source field in DMA
 *  Stream Transfer Mode C-Type (see TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_SOURCE_FIELD_MASK                               \
    MukVAL_TYPED(                                                             \
        TukDMAS_TRANSFER_MODE,                                                \
        MukVAL_FIELD_BITMASK32(                                               \
            DukDMAS_TRANSFER_MODE_SOURCE_FIELD_LSb,                           \
            DukDMAS_TRANSFER_MODE_SOURCE_FIELD_MSb)                           \
                            )


/**
 * @brief C-Constant defining the MSb of the Destination field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 * Destination field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_MSb                           \
    MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the LSb of the Destination field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 * Destination field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_LSb                           \
    MukVAL_TYPED(TukBITNUM, 8U)

/**
 * @brief C-Constant defining the bitmask of the Destination field in DMA
 *  Stream Transfer Mode C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Destination field in DMA
 *  Stream Transfer Mode C-Type (see TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_MASK                          \
    MukVAL_TYPED(                                                             \
        TukDMAS_TRANSFER_MODE,                                                \
        MukVAL_FIELD_BITMASK32(                                               \
            DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_LSb,                      \
            DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_MSb)                      \
                            )

/**
 * @brief C-Constant defining the MSb of the Engine field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 * Engine field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_ENGINE_FIELD_MSb                                \
    MukVAL_TYPED(TukBITNUM, 23U)

/**
 * @brief C-Constant defining the LSb of the Engine field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 * Engine field in DMA Stream Transfer Mode C-Type (see
 * TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_ENGINE_FIELD_LSb                                \
    MukVAL_TYPED(TukBITNUM, 16U)

/**
 * @brief C-Constant defining the bitmask of the Engine field in DMA Stream
 *  Transfer Mode C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Engine field in DMA
 *  Stream Transfer Mode C-Type (see TukDMAS_TRANSFER_MODE).
 */
#define DukDMAS_TRANSFER_MODE_ENGINE_FIELD_MASK                               \
    MukVAL_TYPED(                                                             \
        TukDMAS_TRANSFER_MODE,                                                \
        MukVAL_FIELD_BITMASK32(                                               \
            DukDMAS_TRANSFER_MODE_ENGINE_FIELD_LSb,                           \
            DukDMAS_TRANSFER_MODE_ENGINE_FIELD_MSb)                           \
                            )


#define DukDMAS_TRANSFER_MODE_SOURCE_FIELD_SETUP                              \
                MukVAL_TYPED_BF(TukDMAS_TRANSFER_MODE, 7U)

#define DukDMAS_TRANSFER_MODE_DESTINATION_FIELD_SETUP                         \
                MukVAL_TYPED_BF(TukDMAS_TRANSFER_MODE, 15U)

#define DukDMAS_TRANSFER_MODE_ENGINE_FIELD_SETUP                              \
                MukVAL_TYPED_BF(TukDMAS_TRANSFER_MODE, 23U)

/**
 * @brief C-Constant defining the No Increment sub-field in DMA Stream Transfer
 *  Mode.
 *
 * Definition of the C-Constant for the No Increment sub-field in DMA Stream
 *  Transfer Mode.
 *
 * When this value is used, no increment on the Source or Destination address
 *  is done after each data transferred by the DMA Stream.
 */
#define DukDMAS_TRANSFER_MODE_INCREMENT_NO                                    \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b10UL << 0U)

#define DukDMAS_TRANSFER_MODE_INCREMENT_AUTO                                  \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b11UL << 0U)

#define DukDMAS_TRANSFER_MODE_INCREMENT_MASK                                  \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b11UL << 0U)

#define DukDMAS_TRANSFER_MODE_DATA_WIDTH_1                                    \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b100UL << 2U)

#define DukDMAS_TRANSFER_MODE_DATA_WIDTH_2                                    \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b101UL << 2U)

#define DukDMAS_TRANSFER_MODE_DATA_WIDTH_4                                    \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b110UL << 2U)

#define DukDMAS_TRANSFER_MODE_DATA_WIDTH_MASK                                 \
                MukVAL_TYPED(TukDMAS_TRANSFER_MASK, 0b111UL << 2U)

#define DukDMAS_TRANSFER_MODE_BUFFER_FLAT                                     \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b10 << 16U)

#define DukDMAS_TRANSFER_MODE_BUFFER_CIRCULAR                                 \
                MukVAL_TYPED(TukDMAS_TRANSFER_MODE, 0b11 << 16U)


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - DMA STREAM ATTRIBUTES                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the valid bitmask for DMA Stream Attributes.
 *
 * Definition of the C-Constant of the bitmask of valid flags in DMA Stream
 *  Attributes value.
 *
 * @implementation Each bit set (logical 1) in the bitmask corresponds to a
 *  valid flag.
 */
#define DukDMAS_ATTRIBUTES_VALID_MASK                                         \
            MukVAL_TYPED(TukDMAS_ATTRIBUTES,                                  \
                         0U)

/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS - WATCHDOG                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Stoppable flag in Watchdog Attributes
 *  Configuration.
 *
 * Definition of the C-Constant for the Stoppable flag in Watchdog Attributes.
 * When this flag is set(logical 1), the Watchdog can be stopped by its ukProc
 *  Owner (see ukWatchdogStop()).
 *
 * @robustness The Watchdog can be stopped only by its ukProc Owner.
 *
 * @usage Once the Watchdog is stopped, it can be restarted with a different
 *  configuration using ukWatchdogStart().
 */
#define DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG                          \
    MukVAL_TYPED_BF(TukWATCHDOG_ATTRIBUTES, 0U)


/**
 * @brief C-Constant defining the valid bitmask for the Configuration field in
 *  Watchdog Attributes C-Type.
 *
 * Definition of the C-Constant for the bitmask of the valid flags for the
 *  Configuration field in Watchdog Attributes C-Type (see
 *  TukWATCHDOG_ATTRIBUTES).
 *
 * @implementation Each bit set (logical 1) in the bitmask corresponds to a
 *  valid flag.
 */
#define DukWATCHDOG_ATTRIBUTES_CONFIG_MASK                                    \
    MukVAL_TYPED(TukWATCHDOG_ATTRIBUTES,                                      \
                 DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG               | \
                 0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-CONSTANTS - RANDOM GENERATOR                     */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the LSb of the Reference field in Random
 *  Generator Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Tag
 *  field in Random Generator Identifier C-Type internal structure.
 */
#define DukRNG_ID_REFERENCE_LSb                                               \
    MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the MSb of the Reference field in Random
 *  Generator Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Tag
 *  field in Random Generator Identifier C-Type internal structure.
 */
#define DukRNG_ID_REFERENCE_MSb                                               \
    MukVAL_TYPED(TukBITNUM, 7U)

/**
 * @brief C-Constant defining the Mask for the Reference field in Random
 *  Generator Identifier.
 *
 * Definition of the C-Constant for the Mask of significant bits of the
 *  Reference field in Random Generator Identifier.
 */
#define DukRNG_ID_REFERENCE_MASK                                              \
    MukVAL_TYPED(TukRNG_ID,                                                   \
                 MukVAL_FIELD_BITMASK32(DukRNG_ID_REFERENCE_LSb,              \
                                      DukRNG_ID_REFERENCE_MSb                 \
                                 )                                            \
                )


/**
 * @brief C-Constant defining the LSb of the Tag field in Random Generator
 *  Identifier.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Tag
 *  field in Random Generator Identifier C-Type internal structure.
 */
#define DukRNG_ID_TAG_LSb                                                     \
    MukVAL_TYPED(TukBITNUM, 8U)

/**
 * @brief C-Constant defining the MSb of the Tag field in Random Generator
 *  Identifier.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Tag
 *  field in Random Generator Identifier C-Type internal structure.
 */
#define DukRNG_ID_TAG_MSb                                                     \
    MukVAL_TYPED(TukBITNUM, 31U)


/**
 * @brief C-Constant defining the Mask for the Tag field in Random Generator
 *  Identifier.
 *
 * Definition of the C-Constant for the Mask of significant bits of the Tag
 *  field in Random Generator Identifier.
 */
#define DukRNG_ID_TAG_MASK                                                    \
    MukVAL_TYPED(TukRNG_ID,                                                   \
                 MukVAL_FIELD_BITMASK32(DukRNG_ID_TAG_LSb,                    \
                                      DukRNG_ID_TAG_MSb                       \
                                 )                                            \
                )

/**
 * @brief C-Constant defining the tag value used for Random Generator
 *  Identifier definition.
 *
 * Definition of the C-Constant for the tag value used for Random Generator
 *  Identifier definition.
 *
 * @implementation The used value is the leftmost bytes of SHA256 hash of
 *  'RNG_ID'.
 *
 * @usage This C-Constant is used to populate the Tag field of an identifier
 *  in order to prevent misuse of its value for other purposes.
 */
#define DukRNG_ID_TAG                                                         \
    MukVAL_TYPED(TukRNG_ID, 0x0C5EA6UL)


/**
 * @brief C-Constant defining the Random Generator Identifier for a PRNG.
 *
 * Definition of the C-Constant for the Random Generator Identifier for a PRNG
 *  (Pseudo Random Generator).
 * The PRNG algorithm used is: PCG32 algorithm.
 *
 * @note See "http://www.pcg-random.org/" for a description of the
 *  PCG32 PRNG algorithm.
 *
 * @robustness There is no full guarantee on the entropy level of PCG32 PRNG,
 *  even if it passes the random quality tests TestU01's in most flavor
 *  (BigCrush, Crush, SmallCrush).
 *
 * @implementation The PRNG initial entropy source depends of the support of
 *  the TRNG (see uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED):
 *  - SUPPORTED: The TRNG is used to provide initial entropy to the PRNG.
 *  - NOT SUPPORTED: The following entropy elements from the MCU are used to
 *   initialize the PRNG entropy:
 *   + uKernel Release data.
 *   + ukApps Bundle data.
 *   + MCU Identifier and Serial Number.
 *   + uKernel Uptime
 *
 * @usage The PRNG is always available. There is however no full guarantee on
 *  its entropy level.
 *
 * @usage The PRNG SHALL NOT be used for sensitive operations (use instead
 *  DukRNG_ID_TRNG_AIS31 and DukRNG_ID_CPRNG) or for cryptographic operations
 *  (use instead DukRNG_ID_RNGFC).
 */
#define DukRNG_ID_PRNG                       MukVAL_TYPED(TukRNG_ID,          \
                                ((DukRNG_ID_TAG << DukRNG_ID_TAG_LSb)       | \
                                ( 0x01UL        << DukRNG_ID_REFERENCE_LSb)))

/**
 * @brief C-Constant defining the Random Generator Identifier for a TRNG.
 *
 * Definition of the C-Constant for the Random Generator Identifier for a TRNG
 *  (True Random Generator).
 *
 * @robustness See MCU documentation for the effective entropy level provided
 *  by the TRNG peripheral present in the MCU, and the random official tests
 *  passed.
 *
 * @implementation The TRNG is supported only if uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED is defined.
 *
 * @usage If the TRNG is supported, it SHALL BE used instead of the PRNG, and
 *  also in general instead of CPRNG.
 *
 * @usage In order to enhance the TRNG entropy, and prevents possible failure,
 *  it may be useful to mix the random values retrieved with the ones provided
 *  by the PRNG.
 *
 * @usage The TRNG SHALL NOT be used for sensitive operations (use instead
 *  DukRNG_ID_TRNG_AIS31 and DukRNG_ID_CPRNG) or for cryptographic operations
 *  (use instead DukRNG_ID_RNGFC).
 */
#define DukRNG_ID_TRNG                       MukVAL_TYPED(TukRNG_ID,          \
                                ((DukRNG_ID_TAG << DukRNG_ID_TAG_LSb)       | \
                                ( 0x02UL        << DukRNG_ID_REFERENCE_LSb)))

/**
 * @brief C-Constant defining the Random Generator Identifier for a TRNG
 *  compliant with AIS31.
 *
 * Definition of the C-Constant for the Random Generator Identifier for a TRNG
 *  (True Random Generator) compliant with AIS31 standard.
 *
 * @note See BSI web site (https://www.bsi.bund.de/) for more information on
 *  AIS31 standard.
 *
 * @robustness See MCU documentation for the effective entropy level provided
 *  by the AIS31 TRNG peripheral present in the MCU, and the random official
 *  tests passed.
 *
 * @implementation The AIS31 TRNG is supported only if uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_AIS31_SUPPORTED is defined. If it is
 *  supported, then TRNG (see DukRNG_ID_TRNG) is also supported.
 *
 * @usage If the AIS31 TRNG is supported, it SHALL BE used instead of the TRNG
 *  for sensitive operations (the TRNG can still be used when only a quick
 *  random is required, as for wiping, seeding PRNG, ...).
 *
 * @usage The AIS31 TRNG SHALL NOT be used cryptographic operations if
 *  DukRNG_ID_RNGFC is supported.
 */
#define DukRNG_ID_TRNG_AIS31                 MukVAL_TYPED(TukRNG_ID,          \
                                ((DukRNG_ID_TAG << DukRNG_ID_TAG_LSb)       | \
                                ( 0x03UL        << DukRNG_ID_REFERENCE_LSb)))

/**
 * @brief C-Constant defining the Random Generator Identifier for a CPRNG.
 *
 * Definition of the C-Constant for the Random Generator Identifier for a CPRNG
 *  (Cryptographic Pseudo Random Generator).
 * The CPRNG algorithm used is: HMAC-DBRG (compliant with NIST SP 800-90A)
 *  using SHA256 hash function.
 *
 * @warning The CPRNG needs to write upon each new uKernel Session some data
 *  in persistent memory, which is often Flash memory. Even if the uKernel
 *  will do its best to improve the lifetime of Flash memory, the number of
 *  uKernel Sessions will then be limited by the Flash endurance performance
 *  (See specific information on MCU Flash in MCU documentation and uKernel
 *   Release documentation for more details).
 *
 * @note See NIST web site
 * (https://csrc.nist.gov/publications/detail/sp/800-90a/rev-1/final) for NIST
 *  SP 800-90A standard.
 *
 * @robustness The effective entropy level provided by HMAC-DBRG is high,
 *  has some mathematical proof, and passes most of the official tests for
 *  random quality (TestU01, ...).
 *  This effective entropy level is however depending of the initial seeding,
 *  and thus is really high if the TRNG is supported (see uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED)
 *
 * @implementation The CPRNG initial entropy source depends of the support of
 *  the TRNG (see uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED):
 *  - SUPPORTED: The TRNG is used to provide initial entropy to the CPRNG.
 *  - NOT SUPPORTED: The following entropy elements from the MCU are used to
 *   initialize the CPRNG entropy:
 *   + Previous state of CPRNG (stored in persistent memory)
 *   + uKernel Release data.
 *   + ukApps Bundle data.
 *   + MCU Identifier and Serial Number.
 *   + uKernel Uptime
 *
 * @usage If the CPRNG is supported, it SHALL BE used instead of the PRNG
 *  for sensitive operations (the PRNG can still be used when only a quick
 *  random is required, as for wiping, ...).
 *
 * @usage The CPRNG SHALL NOT be used cryptographic operations if
 *  DukRNG_ID_RNGFC is supported.
 */
#define DukRNG_ID_CPRNG                      MukVAL_TYPED(TukRNG_ID,          \
                                ((DukRNG_ID_TAG << DukRNG_ID_TAG_LSb)       | \
                                ( 0x04UL        << DukRNG_ID_REFERENCE_LSb)))


/**
 * @brief C-Constant defining the Random Generator Identifier for a RNGFC
 *  dedicated to cryptographic operations.
 *
 * Definition of the C-Constant for the Random Generator Identifier for a RNGFC
 *  (Random Generator For Cryptography) dedicated to cryptographic operations.
 *
 * This RNG is using a mix of Random Generators in order to generate random with
 *  the quality needed for performing cryptographic operations. The reason why
 *  a TRNG alone is not used is to bear with some temporary or permanent
 *  hardware weakness or failure of the TRNG. Also, some statistical are
 *  performed on the output in order to detect possible failure in the
 *  generation (repeating sequences, ...).
 *
 * The Random Generators used are:
 *  - CPRNG
 *  AND
 *  - AIS31 TRNG if supported, else TRNG if supported.
 *
 * @warning If both TRNG and AIS31 TRNG are not supported, a proper entropy
 *  level of the random generated for cryptographic operations is not
 *  guaranteed without proper seeding of this Random Generator with external
 *  high quality entropy sources.
 *
 * @robustness The effective entropy level provided by the RNGFC is quite high
 *  if TRNG or AIS31 TRNG is supported (see uKernel Configuration
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_SUPPORTED and
 *  SukCONFIG_HW_MCU_PERIPHERALS_TRNG_AIS31_SUPPORTED). Else, it heavily
 *  depends of its seeding by external entropy source kept unknown from an
 *  attacker.
 *
 * @usage If the RNGFC is supported, it SHALL BE used for cryptographic
 *  operations.
 */
#define DukRNG_ID_RNGFC                      MukVAL_TYPED(TukRNG_ID,          \
                                ((DukRNG_ID_TAG << DukRNG_ID_TAG_LSb)       | \
                                ( 0x05UL        << DukRNG_ID_REFERENCE_LSb)))

/* //////////////////////////////////////////////////////////////////////// */
/*               C-CONSTANTS - UKERNEL IMAGE UPDATE STORAGE                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the value of which shall be multiple the length of
 *  the Address Block used by a uKernel Image Update Operation.
 *
 * Definition of the C-Constant for the value of which shall be multiple the
 *  length (in bytes) of the Address Block in uKernel Image Update Storage used
 *  by a uKernel Image Update Operation.
 *
 * @implementation This value is always a multiple of the MCU Flash Access
 *  Block Size (see DukCONFIG_HW_MCU_DEVICE_FLASH_ACCESS_BLOCK_SIZE).
 *
 * @usage This value applies for the following uKernel Image Update Operations:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_ADDRESS_BLOCK_LENGTH_MULTIPLE       \
            MukVAL_TYPED(TukLENGTH32, 4096U)


/**
 * @brief C-Constant defining the minimal length of the Address Block used by a
 *  uKernel Image Update Operation on uKernel Core.
 *
 * Definition of the C-Constant for the minimal length (in bytes) of the Address
 *  Block in uKernel Image Update Storage used by a uKernel Image Update
 *  Operation on uKernel Core.
 *
 * @implementation This value is a multiple of
 *  DukUKERNEL_IMAGE_UPDATE_OPERATION_ADDRESS_BLOCK_LENGTH_MULTIPLE.
 *
 * @usage This value applies for the following uKernel Image Update Operations:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 */
#define DukUKERNEL_IMAGE_UPDATE_UKERNEL_CORE_ADDRESS_BLOCK_LENGTH_MIN\
            MukVAL_TYPED(TukLENGTH32, 16384U)


/**
 * @brief C-Constant defining the minimal length of the Address Block used by a
 *  uKernel Image Update Operation on a ukApp or on a ukApps Bundle.
 *
 * Definition of the C-Constant for the minimal length (in bytes) of the Address
 *  Block in uKernel Image Update Storage used by a uKernel Image Update
 *  Operation on a ukApp or on ukApps Bundle.
 *
 * @implementation This value is a multiple of
 *  DukUKERNEL_IMAGE_UPDATE_OPERATION_ADDRESS_BLOCK_LENGTH_MULTIPLE.
 *
 * @usage This value applies for the following uKernel Image Update Operations:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 */
#define DukUKERNEL_IMAGE_UPDATE_UKAPP_ADDRESS_BLOCK_LENGTH_MIN      \
            MukVAL_TYPED(TukLENGTH32, 4096U)



/* //////////////////////////////////////////////////////////////////////// */
/*               C-CONSTANTS - UKERNEL IMAGE UPDATE OPERATION               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the uKernel Image Update Operation for replacing
 *  a single ukApp.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  replacing a single ukApp in the ukApps Bundle.
 *
 * The uKernel Image Update Storage shall contains at its start (offset
 *  null(0)) the start of the new ukApp Code Block (i.e. the first byte of its
 *  ukApp Descriptor) of the new ukApp version.
 * The uKernel Image Update Operation length shall be greater or equal to
 *  DukUKERNEL_IMAGE_UPDATE_UKAPP_ADDRESS_BLOCK_LENGTH_MIN.
 *
 * To be valid, the new ukApp shall be compliant with the following
 *  constraints:
 *  - Its ukApp Code Block shall be fully disjointed of all the other ukApp
 *   Code Block present in the ukApps Bundle. Its start address and its length
 *   may however be different from the one it replaces.
 *  - Its ukApp Code Block shall be genuine, that is the values in the fields
 *   <UKAppCodeBodyBlockSHA256> and <UKAppDescriptorSHA256> shall correspond to
 *   the SHA256 values computed by the uKernel BootLoader (ukBootLoader).
 *  - The following fields in its ukApp Descriptor shall be the same than the
 *   ones defined in the current ukApp present in ukApps Bundle:
 *   + <NameNTString>
 *   + <AUID>
 *  - The field <ReleaseMCUDeviceIdentifier> in the ukApp Descriptor of the
 *   new ukApp shall be equal to the one defined in uKernel Release used.
 *  - The field <ReleaseuKernelVersion> in the ukApp Descriptor of the new
 *   ukApp shall be as follows:
 *   + Fields <Major> and <Minor> shall be equal to the ones defined in the
 *     current uKernel Release used.
 *   + Field <Micro> shall be lower or equal to the one defined in the current
 *     uKernel Release used.
 *  - The field <ReleaseCustomerConfiguration> in the ukApp Descriptor of the
 *   new ukApp shall be as follows:
 *   + Fields <Customer> and <Project> shall be equal to the ones defined in
 *     the current uKernel Release used.
 *   + Field <Revision> shall be lower or equal to the one defined in the
 *     current uKernel Release used.
 *  - The field <Version> in the ukApp Descriptor of the new ukApp shall be the
 *   strictly higher than the one defined in the current ukApp updated.
 *
 * Additional parameters: None.
 *
 * @implementation If the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported, after such a
 *  uKernel Image Update Operation, the uKernel Image Update Storage stays
 *  locked and cannot be accessed for storing a new uKernel Image part for
 *  update as long as:
 *   - The new uKernel Image part updated has not been validated (see
 *    DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE).
 *   - And then that the uKernel Image Update Storage has not been unlocked
 *    (see DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE).
 *
 * @usage The new ukApp can have a ukApp Code Block placed at a different
 *  address and of a different length (smaller or bigger) than the current one
 *  present in ukApps Bundle.
 *
 *
 * @implementation #NOTYETSUPPORTED
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP                       \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x521052EFUL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for replacing
 *  the ukApps Bundle.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  replacing the ukApps Bundle.
 * When updating a ukApps Bundle, the ukApps already present in current ukApps
 *  Bundle can be updated or removed, and new ukApps can also be added.
 *
 * The uKernel Image Update Storage shall contains at its start (offset
 *  null(0)) the start the new ukApps Bundle Code Block.
 * The uKernel Image Update Operation Length parameter shall be:
 *  - Greater or equal to
 *   DukUKERNEL_IMAGE_UPDATE_UKAPP_ADDRESS_BLOCK_LENGTH_MIN.
 *  - Lower or equal to uKernel Option
 *   DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_UKAPPSBUNDLE_CODE_ADDRESS_BLOCK_LENGTH.
 *
 * To be valid, the new ukApps Bundle shall be compliant with the following
 *  constraints:
 *  - All the ukApps in the new ukApps Bundle already present in the current
 *   ukApps Bundle shall follow the constraints applying on individual ukApp
 *   update (see DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP).
 *  - The ukApp managing the uKernel Image Update (see
 *   DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG) shall still be present.
 *
 * Additional parameters: None.
 *
 * @implementation If the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported, after such a
 *  uKernel Image Update Operation, the uKernel Image Update Storage stays
 *  locked and cannot be accessed for storing a new uKernel Image part for
 *  update as long as:
 *   - The new uKernel Image part updated has not been validated (see
 *    DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE).
 *   - And then that the uKernel Image Update Storage has not been unlocked
 *    (see DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE).
 *
 * @usage The new ukApps Bundle version can have a different count of ukApps
 *  than the current one, as the ukApps contained in the new ukApps Bundle
 *  version may be different from the current one (some may be added, other
 *  updated, other removed).
 *
 * @implementation #NOTYETSUPPORTED
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE               \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x5290526FUL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for replacing
 *  the uKernel Core.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  replacing the uKernel Core only (the ukApps Bundle is not updated).
 *
 * The uKernel Image Update Storage shall contains at its start (offset
 *  null(0)) the start of the uKernel Core Code Block (i.e. the first byte
 *  of its uKernel Core Descriptor) of the new uKernel Core version.
 * The uKernel Image Update Operation Length parameter shall be:
 *  - Greater or equal to
 *   DukUKERNEL_IMAGE_UPDATE_UKERNEL_CORE_ADDRESS_BLOCK_LENGTH_MIN.
 *  - Lower or equal to uKernel Option
 *   DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_UKCORE_CODE_ADDRESS_BLOCK_LENGTH.
 *
 * To be valid, the new uKernel Core shall be compliant with the following
 *  constraints:
 *  - Its uKernel Core Code Block shall have the same start address than the
 *   current uKernel Core version.
 *  - Its uKernel Core Code Block shall be genuine, that is the values in the
 *   fields <UKernelCoreCodeBodyBlockSHA256> and <UKernelCoreDescriptorSHA256>
 *   shall correspond to the SHA256 values computed by the uKernel BootLoader
 *   (ukBootLoader).
 *  - The following fields in the uKernel Core Descriptor (see
 *   DukRELEASE_UKERNEL_CORE_CODE_DESCRIPTOR) of the new uKernel Core shall be
 *   the same than the ones defined in the current uKernel Core:
 *   + <UKernelCoreReleaseCPUCoreIdentifier64>
 *   + <UKernelCoreReleaseMCUDeviceIdentifier128_bv>
 *   + <UKernelCoreReleasePlatformIdentifier128_bv>
 *   + <UKernelCoreConfigurationDescriptorVersion>
 *  - The field <ReleaseuKernelVersion> in the uKernel Core Descriptor of the
 *   new uKernel Core shall be strictly higher than the one defined in the
 *   current uKernel Core.
 *  - The field <ReleaseCustomerConfiguration> in the uKernel Core Descriptor
 *   of the new uKernel Core shall be as follows:
 *   + Fields <Customer> and <Project> shall be equal to the ones defined in
 *     the current uKernel Core.
 *   + Field <Revision> shall be higher or equal to the one defined in the
 *     current uKernel Core.
 *
 * @implementation If the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported, after such a
 *  uKernel Image Update Operation, the uKernel Image Update Storage stays
 *  locked and cannot be accessed for storing a new uKernel Image part for
 *  update as long as:
 *   - The new uKernel Image part updated has not been validated (see
 *    DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE).
 *   - And then that the uKernel Image Update Storage has not been unlocked
 *    (see DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE).
 *
 * @usage In case the uKernel Core Code Block length is not known, it is
 *  recommend to use the maximal allowed length given in uKernel Option
 *  DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_UKCORE_CODE_ADDRESS_BLOCK_LENGTH for
 *  the uKernel Image Update Operation Length.
 *
 * Additional parameters: None.
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE                \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x520152FEUL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for replacing
 *  whole uKernel Image.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  replacing the whole uKernel Image (that is the uKernel Core and the ukApps
 *  Bundle).
 *
 * The uKernel Image Update Storage shall contains:
 *  - At its start (offset null(0)) the start of the uKernel Core Code Block
 *   (i.e. the first byte of its uKernel Core Descriptor) of the new uKernel
 *   Core version.
 *  - At the offset corresponding to the size reserved for the uKernel Core
 *   Code Block (see DukcoreCONFIG_OPTION_HW_UKCORE_CODE_BLOCK_SIZE_RESERVED)
 *   the new ukApps Bundle Code Block containing the new ukApp versions.
 * The uKernel Image Update Operation Length parameter shall be:
 *  - Greater or equal to
 *   (DukCONFIG_OPTION_HW_UKERNEL_IMAGE_UPDATE_UKCORE_CODE_ADDRESS_BLOCK_LENGTH +
 *    DukUKERNEL_IMAGE_UPDATE_UKAPP_ADDRESS_BLOCK_LENGTH_MIN)
 *
 * To be valid, the new whole uKernel Image shall be compliant with the
 *  following constraints:
 *  - Constraints when replacing the uKernel Core (see
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE).
 *  - Constraints when replacing the ukApps Bundle (see
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE).
 *
 * Additional parameters: None.
 *
 * @implementation If the uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported, after such a
 *  uKernel Image Update Operation, the uKernel Image Update Storage stays
 *  locked and cannot be accessed for storing a new uKernel Image part for
 *  update as long as:
 *   - The new uKernel Image part updated has not been validated (see
 *    DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE).
 *   - And then that the uKernel Image Update Storage has not been unlocked
 *    (see DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE).
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE                       \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x52995266UL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for validating
 *  the new uKernel Image part updated.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  validating the new uKernel Image part updated.
 *
 * If the uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is
 *  supported, after a uKernel Image Update Operation for replacement has been
 *  performed (see DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_xxx):
 *   - This uKernel Image Update Operation shall be invoked in order to
 *    validate that the new uKernel Image part updated is behaving properly
 *    and let the system usable.
 *   - As long as this uKernel Image Update Operation has not been invoked, the
 *    uKernel Image Update Storage stays locked and cannot be accessed for
 *    storing a new uKernel Image part for update.
 *   - If this uKernel Image Update Operation is not invoked during a number of
 *    consecutive uKernel Sessions defined in
 *    DukCONFIG_OPTION_UKERNEL_IMAGE_UPDATE_VALIDATE_SESSION_COUNT_MAX, then
 *    the previous version of the uKernel Image part updated is used to perform
 *    a roll-back of the update. The roll-back is performed by the ukBootLoader
 *    (uKernel Bootloader) just after MCU Reset before the start of the uKernel
 *    Core code.
 *
 * @implementation After this uKernel Image Update Operation being performed,
 *  the uKernel Image Update Storage is still locked (see uKernel Image Update
 *  Operation DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE to unlock it).
 *
 * @implementation This uKernel Image Update Operation is supported only if
 *  uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported.
 *
 * Additional parameters: None.
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE                            \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x560156FEUL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for performing
 *  a roll-back of the uKernel Image part updated.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  performing a roll-back of the uKernel Image part updated.
 *
 * If the uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is
 *  supported, after a uKernel Image Update Operation for replacement has been
 *  performed (see DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_xxx), and as long
 *  the uKernel Image Update Storage has not been unlocked (see
 *  DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE), this uKernel Image
 *  Update Operation can be invoked to roll-back to the previous version of the
 *  uKernel Image part updated stored in the uKernel Image Update Storage.
 *  The roll-back is performed by the ukBootLoader (uKernel Bootloader) just
 *  after MCU Reset before the start of the uKernel Core code.
 *
 * @implementation After this uKernel Image Update Operation being performed,
 *  the uKernel Image Update Storage is unlocked.
 *
 * @implementation This uKernel Image Update Operation is supported only if
 *  uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported.
 *
 * Additional parameters: None.
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_ROLLBACK                            \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x50FE5001UL)

/**
 * @brief C-Constant defining the uKernel Image Update Operation for unlocking
 *  the new uKernel Image part updated.
 *
 * Definition of the C-Constant for the uKernel Image Update Operation for
 *  unlocking the new uKernel Image part updated.
 *
 * If the uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is
 *  supported, after a uKernel Image Update Operation for replacement has been
 *  performed (see DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_xxx), the uKernel
 *  Image Update Storage stays locked and cannot be accessed for storing a
 *  new uKernel Image part for update as long as:
 *   - The new uKernel Image part updated has not been validated (see
 *    DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE)
 *   - And then that the uKernel Image Update Storage has not been unlocked
 *    using this uKernel Image Update Operation.
 *
 * @implementation This uKernel Image Update Operation is supported only if
 *  uKernel Feature SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported.
 *
 * Additional parameters: None.
 */
#define DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE                      \
                MukVAL_TYPED(TukUKERNEL_IMAGE_UPDATE_OPERATION, 0x550155FEUL)



/* //////////////////////////////////////////////////////////////////////// */
/*              C-CONSTANTS - UKERNEL IMAGE UPDATE ATTRIBUTES               */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Constant defining the SHA256 check Flag in uKernel Image
 *  Attributes.
 *
 * Definition of the C-Constant for the SHA256 check Flag in uKernel Image
 *  Attributes.
 *
 * If this Flag is set, before performing the requested uKernel Image Update
 *  Operation, a check on the uKernel Image part to replace is done as follows:
 *  - Compute a SHA256 on the uKernel Image part stored in the uKernel Image
 *  Update Storage part used for the operation.
 *  - Verify the computed value against the one set at the offset 8 in the
 *  <ServiceParameter.Input> field of the C-Variable
 *  GVukappBlockDataSharedUKSVC. If the verification fails, the operation is
 *  canceled and Status Code DukSTATUS_ERR_SECURITY_CONSISTENCY is returned.
 *
 * @usage This flag can be used for the following uKernel Image Update
 *  Operations:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 */
#define DukUKERNEL_IMAGE_UPDATE_ATTRIBUTES_IMAGE_CHECK_SHA256_FLAG            \
                MukVAL_TYPED_BF(TukUKERNEL_IMAGE_UPDATE_ATTRIBUTES, 1U)


/**
 * @brief C-Constant defining the Keep Previous Flag in uKernel Image
 *  Attributes.
 *
 * Definition of the C-Constant for the Keep Previous Flag in uKernel Image
 *  Attributes.
 *
 * If this Flag is set, the current version of the uKernel Image updated part
 *  is swapped during the replacement operation with the one in the uKernel
 *  Image Update Storage. And thus the uKernel Image Update Storage will
 *  contain after the replacement its previous (i.e. 'n-1') version.
 *
 * The previous version is kept in the uKernel Image Update Storage up to one
 *  of the following events occur:
 *  - The maximal consecutive count of uKernel Sessions without performing the
 *   validation of the new uKernel Image has been reached (see
 *   DukCONFIG_OPTION_UKERNEL_IMAGE_UPDATE_VALIDATE_SESSION_COUNT_MAX).
 *   The validation of the new uKernel Image is done using the uKernel Image
 *   Update Operation DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE.
 *  - The uKernel Image Update Operation
 *   DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE is performed.
 * The uKernel Image Update Storage is locked, and cannot be used for storing
 *  a new uKernel Image part, as long as the previous version is kept into it.
 *
 * @usage This flag can be used only if uKernel Feature
 *  SukCONFIG_FEATURE_UKERNEL_IMAGE_KEEP_PREVIOUS is supported.
 *  Else it is invalid.
 *
 * @usage This flag can be used for the following uKernel Image Update
 *  Operations:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 *
 * @implementation #NOTYETSUPPORTED
 */
#define DukUKERNEL_IMAGE_UPDATE_ATTRIBUTES_IMAGE_KEEP_PREVIOUS_FLAG           \
                MukVAL_TYPED_BF(TukUKERNEL_IMAGE_UPDATE_ATTRIBUTES, 2U)



/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - DEBUG TRACE - NATURE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Nature Information for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is generic information on the ukProc execution.
 *
 * @usage This Nature value should be used for printing generic information on
 *  significant events occurring during the ukProc execution.
 *  Note that it should not be used for reporting persistent configuration
 *  elements, errors, or statistics as other dedicated Nature values are
 *  defined for this.
 *
 * Example: Internal lifecycle of the ukApp (initialization phase, ...),
 *  internal value or state for easing debugging, ...
 */
#define DukDEBUG_TRACE_NATURE_INFO_FLAG                                       \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 0U)

/**
 * @brief C-Constant defining the Nature Configuration for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is configuration information of the ukProc.
 *
 * @usage This Nature value should be used for printing information relative
 *  to the current internal configuration of the ukProc and of its execution
 *  environment.
 *
 * Example: Compilation options, personalization, internal persistent data
 *  used, field values from its Descriptor, ukApps Bundle and Platform
 *  configuration elements, ...
 */
#define DukDEBUG_TRACE_NATURE_CONFIG_FLAG                                     \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 1U)

/**
 * @brief C-Constant defining the Nature Diagnostic for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is diagnostic information of the ukProc.
 *
 * @usage This Nature value should be used for printing information relative
 *  to the main processing elements of the ukProc in order to allow
 *  external checks on ukProc execution expectations.
 *
 * Example: Intermediate internal computation values, summary of output data
 *  sent outside the ukProc, timing of events,...
 */
#define DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG                                 \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 2U)

/**
 * @brief C-Constant defining the Nature Statistics for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is statistics information of the ukProc execution(s).
 *
 * @usage This Nature value should be used only for printing information
 *  relative to statistics relative to current ukProc execution. These
 *  information may be statistics already computed inside the ukProc, or raw
 *  data allowing external statistics computation.
 *
 * Example: Statistics on processed data, occurrence of received events
 *  (IPC, PIRQ, ...), amount of data processed, ...
 */
#define DukDEBUG_TRACE_NATURE_STAT_FLAG                                       \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 3U)

/**
 * @brief C-Constant defining the Nature Warning for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is warning information issued from noticed unexpected conditions or events
 *  during ukProc execution that do not prevent the current processing to
 *  be performed.
 *
 * @note A warning is defined there as an internal state, value or event inside
 *  the ukProc that is not expected to happen in nominal execution. The warning
 *  condition does not cause immediate internal error or unmanaged state, but
 *  may lead to further errors or unexpected behaviors during execution.
 *
 * @usage This Nature value should be used only for printing information
 *  relative to warning occurring during current ukProc execution.
 *
 * Example: Low memory resources, unexpected unused bit set in used value,
 *  ...
 */
#define DukDEBUG_TRACE_NATURE_WARNING_FLAG                                    \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 4U)

/**
 * @brief C-Constant defining the Nature Error for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of a Debug Trace whose contents
 *  is error information issued from unexpected conditions or events during
 *  ukProc execution that make the current processing impossible to perform
 *  as defined.
 *
 * @note An error is defined there as an internal state, value or event inside
 *  the ukProc that shall never happen in nominal execution as it is not
 *  handled by the ukProc implementation (because of constraints on initial
 *  value, chosen algorithm, protocol, resources constraints, optimizations,
 *  ...).
 *
 * @usage This Nature value should be used only for printing information
 *  relative to errors occurring during current ukProc execution.
 *
 * Example: Illegal or inconsistent internal state, not enough memory
 *  resources, unexpected received event, invalid input value,  ...
 */
#define DukDEBUG_TRACE_NATURE_ERROR_FLAG                                      \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 5U)



/**
 * @brief C-Constant defining the Nature Activity for a Debug Trace.
 *
 * Definition of the C-Constant for the Nature of an Activity Trace whose
 *  contents is reporting information on ukProc or uKernel specific activity
 *  during execution.
 *
 * @implementation As difference with other Debug Trace Natures, when this
 *  Nature is used, it will not trigger the display of a banner if the entity
 *  printing the Debug Trace is not the one having printed the previous Debug
 *  Trace. Thus, proper information in the Debug Trace printed shall be
 *  included in order to identify the entity reporting it.
 *
 * Example: Internal state change, finalization of execution sequence, ...
 */
#define DukDEBUG_TRACE_NATURE_ACTIVITY_FLAG                                   \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_NATURE, 6U)


/**
 * @brief C-Constant defining the valid bitmask for Debug Trace Nature.
 *
 * Definition of the C-Constant of the bitmask of valid flags in Debug Trace
 *  Nature value.
 *
 * @implementation This bitmask is always included in the bitmask of the
 *  Nature field DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_MASK.
 *
 * @implementation Each bit set (logical 1) in the bitmask corresponds to a
 *  valid flag.
 */
#define DukDEBUG_TRACE_NATURE_VALID_MASK                                      \
    MukVAL_TYPED(TukDEBUG_TRACE_NATURE,                                       \
                 DukDEBUG_TRACE_NATURE_INFO_FLAG                            | \
                 DukDEBUG_TRACE_NATURE_CONFIG_FLAG                          | \
                 DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG                      | \
                 DukDEBUG_TRACE_NATURE_STAT_FLAG                            | \
                 DukDEBUG_TRACE_NATURE_WARNING_FLAG                         | \
                 DukDEBUG_TRACE_NATURE_ERROR_FLAG                           | \
                 DukDEBUG_TRACE_NATURE_ACTIVITY_FLAG                        | \
                 0U                                                           \
                )

/**
 * @brief C-Constant defining the MSb of the Nature field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the Nature
 *  field in Debug Trace Attribute  C-Type (see TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_MSb                            \
    MukVAL_TYPED(TukBITNUM, 15U)

/**
 * @brief C-Constant defining the LSb of the Nature field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the Nature
 *  field in Debug Trace Attribute C-Type (see TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_LSb                            \
    MukVAL_TYPED(TukBITNUM, 8U)

/**
 * @brief C-Constant defining the bitmask of the Nature field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Nature field in Debug
 *  Trace Attribute C-Type (see TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_MASK                           \
    MukVAL_TYPED(                                                             \
        TukDEBUG_TRACE_ATTRIBUTES,                                            \
        MukVAL_FIELD_BITMASK32(DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_LSb,    \
                             DukDEBUG_TRACE_ATTRIBUTES_NATURE_FIELD_MSb)      \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                      C-CONSTANTS - DEBUG TRACE - MODE                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Mode of a Debug Trace for adding a newline
 *  suffix.
 *
 * Definition of the C-Constant for the Mode of a Debug Trace for adding
 *  automatically a newline at the end of a Debug Trace (i.e a character '\n'
 *  is appended at the end of Debug Trace).
 */
#define DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG                               \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_MODE, 0U)
#define DukDEBUG_TRACE_MODE_NEWLINE_POSTFIX_FLAG                              \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_MODE, 0U)     /* #DEPRECATED */


/**
 * @brief C-Constant defining the Mode of a Debug Trace for prefixing it with
 *  a time stamp.
 *
 * Definition of the C-Constant for the Mode of a Debug Trace for prefixing
 *  automatically its printing with a time stamp, corresponding to the uKernel
 *  Uptime where the printing has been requested.
 */
#define DukDEBUG_TRACE_MODE_TIMESTAMP_PREFIX_FLAG                             \
    MukVAL_TYPED_BF(TukDEBUG_TRACE_MODE, 1U)


/**
 * @brief C-Constant defining the MSb of the Mode field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Mode field in Debug Trace Attribute C-Type (see
 *  TukDEBUG_TRACE_MODE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_MSb                              \
    MukVAL_TYPED(TukBITNUM, 7U)

/**
 * @brief C-Constant defining the LSb of the Mode field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Mode field in the Debug Trace Attribute C-Type (see
 *  TukDEBUG_TRACE_MODE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_LSb                              \
    MukVAL_TYPED(TukBITNUM, 4U)


/**
 * @brief C-Constant defining the bitmask of the Mode field in Debug
 *  Trace Attribute C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Mode field in
 *  Debug Trace Attribute C-Type (see TukDEBUG_TRACE_MODE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_MASK                             \
    MukVAL_TYPED(                                                             \
        TukDEBUG_TRACE_ATTRIBUTES,                                            \
        MukVAL_FIELD_BITMASK32(DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_LSb,      \
                             DukDEBUG_TRACE_ATTRIBUTES_MODE_FIELD_MSb)        \
                )


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - DEBUG TRACE - VERBOSITY                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the disabled Verbosity level for a Debug Trace.
 *
 * Definition of the C-Constant for the Verbosity level of a Debug Trace to
 *  indicate it is disabled.
 *
 * @implementation This level SHALL have a null(0) value.
 *
 * @usage This Verbosity level can be used in Debug Trace Attributes parameter
 *  of Debug Trace uKernel Privileged Service for disabling the printing of
 *  the Debug Trace.
 *
 * @usage When this Debug Trace Verbosity level is used as Debug Trace Verbosity
 *  Filter for a ukApp (see field <DebugTraceVerbosityFilter> in ukApp
 *  Descriptor), no Debug Trace will be printed for this ukApp.
 */
#define DukDEBUG_TRACE_VERBOSITY_DISABLED                                     \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY, 0U)

/**
 * @brief C-Constant defining the default Verbosity level for a Debug Trace.
 *
 * Definition of the C-Constant for the default Verbosity level of a Debug
 *  Trace.
 *
 * @usage This Verbosity level should be used in Debug Trace Attributes
 *  parameter of Debug Trace uKernel Privileged Service for the traces relative
 *  to:
 *   - Significant internal information and events
 *   - Errors.
 *
 * @usage When this Debug Trace Verbosity level is used as Debug Trace Verbosity
 *  Filter for a ukApp (see field <DebugTraceVerbosityFilter> in ukApp
 *  Descriptor), only the Debug Traces with the following level(s) in the Debug
 *  Trace Attributes parameter passed to Debug Trace uKernel Privileged
 *  Services will be effectively printed:
 *  - DukDEBUG_TRACE_VERBOSITY_DEFAULT.
 */
#define DukDEBUG_TRACE_VERBOSITY_DEFAULT                                      \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY, 1U)

/**
 * @brief C-Constant defining the fine Verbosity level for a Debug Trace.
 *
 * Definition of the C-Constant for the fine Verbosity level of a Debug
 *  Trace.
 *
 * @usage This Verbosity level should be used in Debug Trace Attributes
 *  parameter of Debug Trace uKernel Privileged Service for the traces relative
 *  to:
 *   - Internal information and events.
 *   - Configuration.
 *   - Warning.
 *
 * @usage When this Debug Trace Verbosity level is used as Debug Trace Verbosity
 *  Filter for a ukApp (see field <DebugTraceVerbosityFilter> in ukApp
 *  Descriptor), only the Debug Traces with the following level(s) in the Debug
 *  Trace Attributes parameter passed to Debug Trace uKernel Privileged
 *  Services will be effectively printed:
 *  - DukDEBUG_TRACE_VERBOSITY_DEFAULT.
 *  - DukDEBUG_TRACE_VERBOSITY_FINE.
 */
#define DukDEBUG_TRACE_VERBOSITY_FINE                                         \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY, 2U)

/**
 * @brief C-Constant defining the finer Verbosity level for a Debug Trace.
 *
 * Definition of the C-Constant for the finer Verbosity level of a Debug
 *  Trace.
 *
 * @usage This Verbosity level should be used in Debug Trace Attributes
 *  parameter of Debug Trace uKernel Privileged Service for the traces relative
 *  to:
 *   - Detailed information and events.
 *   - Statistics.
 *
 * @usage When this Debug Trace Verbosity level is used as Debug Trace Verbosity
 *  Filter for a ukApp (see field <DebugTraceVerbosityFilter> in ukApp
 *  Descriptor), only the Debug Traces with the following level(s) in the Debug
 *  Trace Attributes parameter passed to Debug Trace uKernel Privileged
 *  Services will be effectively printed:
 *  - DukDEBUG_TRACE_VERBOSITY_DEFAULT.
 *  - DukDEBUG_TRACE_VERBOSITY_FINE.
 *  - DukDEBUG_TRACE_VERBOSITY_FINER.
 */
#define DukDEBUG_TRACE_VERBOSITY_FINER                                        \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY, 3U)

/**
 * @brief C-Constant defining the finest Verbosity level for a Debug Trace.
 *
 * Definition of the C-Constant for the finest Verbosity level of a Debug
 *  Trace.
 *
 * @usage This Verbosity level should be used in Debug Trace Attributes
 *  parameter of Debug Trace uKernel Privileged Service for the traces relative
 *  to:
 *   - Detailed statistics.
 *   - Diagnostics.
 *
 * @usage When this Debug Trace Verbosity level is used as Debug Trace Verbosity
 *  Filter for a ukApp (see field <DebugTraceVerbosityFilter> in ukApp
 *  Descriptor), only the Debug Traces with the following level(s) in the Debug
 *  Trace Attributes parameter passed to Debug Trace uKernel Privileged
 *  Services will be effectively printed:
 *  - DukDEBUG_TRACE_VERBOSITY_DEFAULT.
 *  - DukDEBUG_TRACE_VERBOSITY_FINE.
 *  - DukDEBUG_TRACE_VERBOSITY_FINER.
 *  - DukDEBUG_TRACE_VERBOSITY_FINEST.
 */
#define DukDEBUG_TRACE_VERBOSITY_FINEST                                       \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY, 4U)

/**
 * @brief C-Constant defining the maximum valid level value for a Debug Trace
 *  Verbosity.
 *
 * Definition of the C-Constant for the maximum valid level value for
 *  Debug Trace Verbosity.
 *
 * @implementation The minimum valid level is the null(0) level (see
 *  DukDEBUG_TRACE_VERBOSITY_DISABLED).
 */
#define DukDEBUG_TRACE_VERBOSITY_MAX                                          \
    MukVAL_TYPED(TukDEBUG_TRACE_VERBOSITY,                                    \
                 DukDEBUG_TRACE_VERBOSITY_FINEST                              \
                )

/**
 * @brief C-Constant defining the MSb of the Verbosity field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  Verbosity field in Debug Trace Attribute C-Type (see
 *  TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_MSb                         \
    MukVAL_TYPED(TukBITNUM, 3U)

/**
 * @brief C-Constant defining the LSb of the Verbosity field in Debug Trace
 *  Attribute C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  Verbosity field in the Debug Trace Attribute C-Type (see
 *  TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_LSb                         \
    MukVAL_TYPED(TukBITNUM, 0U)

/**
 * @brief C-Constant defining the bitmask of the Verbosity field in Debug
 *  Trace Attribute C-Type.
 *
 * Definition of the C-Constant for the bitmask of the Verbosity field in
 *  Debug Trace Attribute C-Type (see TukDEBUG_TRACE_NATURE).
 */
#define DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_MASK                        \
    MukVAL_TYPED(                                                             \
        TukDEBUG_TRACE_ATTRIBUTES,                                            \
        MukVAL_FIELD_BITMASK32(DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_LSb, \
                             DukDEBUG_TRACE_ATTRIBUTES_VERBOSITY_FIELD_MSb)   \
                )



/* //////////////////////////////////////////////////////////////////////// */
/*               C-CONSTANTS - DEBUG TRACE - CURSOR POSITION                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the MSb of the <LineNumber> field in Debug Trace
 *  Cursor Position C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  <LineNumber> field in Debug Trace Cursor Position C-Type (see
 *  TukDEBUG_TRACE_CURSOR_POSITION).
 */
#define DukDEBUG_TRACE_CURSOR_POSITION_LINE_NUMBER_FIELD_MSb                  \
    MukVAL_TYPED(TukBITNUM, 31U)

/**
 * @brief C-Constant defining the LSb of the <LineNumber> field in Debug Trace
 *  Cursor Position C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  <LineNumber> field in Debug Trace Cursor Position C-Type (see
 *  TukDEBUG_TRACE_CURSOR_POSITION).
 */
#define DukDEBUG_TRACE_CURSOR_POSITION_LINE_NUMBER_FIELD_LSb                  \
    MukVAL_TYPED(TukBITNUM, 10U)

/**
 * @brief C-Constant defining the MSb of the <Column> field in Debug Trace
 *  Cursor Position C-Type.
 *
 * Definition of the C-Constant of the MSb (Most Significant bit) of the
 *  <Column> field in Debug Trace Cursor Position C-Type (see
 *  TukDEBUG_TRACE_CURSOR_POSITION).
 */
#define DukDEBUG_TRACE_CURSOR_POSITION_COLUMN_FIELD_MSb                       \
    MukVAL_TYPED(TukBITNUM, 9U)

/**
 * @brief C-Constant defining the LSb of the <Column> field in Debug Trace
 *  Cursor Position C-Type.
 *
 * Definition of the C-Constant of the LSb (Less Significant bit) of the
 *  <Column> field in Debug Trace Cursor Position C-Type (see
 *  TukDEBUG_TRACE_CURSOR_POSITION).
 */
#define DukDEBUG_TRACE_CURSOR_POSITION_COLUMN_FIELD_LSb                       \
    MukVAL_TYPED(TukBITNUM, 0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-CONSTANTS - DEBUG TRACE - ERROR CHAR                 */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  upon invalid Debug Trace Attributes.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace upon invalid Debug Trace Attributes.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_ATTRIBUTE_INVALID             MukVAL_TYPED( \
          TukCHAR,                                                            \
          '!')

/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  when an NTString is exceeding maximal allowed length.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace when an NTString is exceeding maximal allowed length.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_NTSTRING_LENGTH_EXCEEDED      MukVAL_TYPED( \
          TukCHAR,                                                            \
          '#')

/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  when a Buffer is exceeding maximal allowed length.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace when a Buffer is exceeding maximal allowed length.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_BUFFER_LENGTH_EXCEEDED        MukVAL_TYPED( \
          TukCHAR,                                                            \
          '#')

/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  when a numerical value is exceeding allowed length.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace when when a numerical value is exceeding allowed length.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_NUMERIC_LENGTH_EXCEEDED       MukVAL_TYPED( \
          TukCHAR,                                                            \
          '#')

/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  when accessing a non authorized Address Block.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace when accessing a non authorized Address Block.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_ADDRESS_BLOCK_NOT_AUTHORIZED  MukVAL_TYPED( \
          TukCHAR,                                                            \
          '~')

/**
 * @brief C-Constant defining the specific character printed on Debug Trace
 *  upon error in Format NTString parsing.
 *
 * Definition of the C-Constant for the specific character printed on Debug
 *  Trace upon error in Format NTString parsing.
 */
#define DukDEBUG_TRACE_ERROR_CHAR_FORMAT_PARSING                MukVAL_TYPED( \
          TukCHAR,                                                            \
          '?')

/**
* @brief C-Constant defining the specific character printed on Debug Trace
*  when maximal length per print on a Debug Trace is reached.
*
* Definition of the C-Constant for the specific character printed on Debug
*  Trace when maximal length per print on a Debug Trace is reached (see
*  DukCONFIG_OPTION_DEBUG_TRACE_LENGTH_PER_PRINT_MAX).
*/
#define DukDEBUG_TRACE_ERROR_CHAR_TRACE_LENGTH_EXCEEDED         MukVAL_TYPED( \
          TukCHAR,                                                            \
          '^')


/* //////////////////////////////////////////////////////////////////////// */
/*                            C-CONSTANTS - DEBUG LED                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the ON Debug LED blinking pattern .
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  the LED fully ON (no blinking).
 */
#define DukDEBUG_LED_PATTERN_ON                                               \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0xFFFFFFFFUL                                                 \
                )

/**
 * @brief C-Constant defining the OFF Debug LED blinking pattern .
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  the LED fully OFF (no blinking).
 */
#define DukDEBUG_LED_PATTERN_OFF                                              \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x00000000UL                                                 \
                )

/**
 * @brief C-Constant defining the fast speed blink Debug LED blinking
 *  pattern.
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  a fast speed blinking (i.e. 50% duty-cycle blinking with short period).
 */
#define DukDEBUG_LED_PATTERN_BLINK_FAST                                       \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x55555555UL                                                 \
                )

/**
 * @brief C-Constant defining the medium speed blink Debug LED blinking
 *  pattern.
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  a medium speed blinking (i.e. 50% duty-cycle blinking with medium period).
 */
#define DukDEBUG_LED_PATTERN_BLINK_MEDIUM                                     \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x33333333UL                                                 \
                )

/**
 * @brief C-Constant defining the slow speed blink Debug LED blinking pattern.
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  a slow speed blinking (i.e. 50% duty-cycle blinking with long period).
 */
#define DukDEBUG_LED_PATTERN_BLINK_SLOW                                       \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x0F0F0F0FUL                                                 \
                )

/**
 * @brief C-Constant defining the short flash Debug LED blinking pattern.
 *
 * Definition of the C-Constant of the Debug LED blinking pattern for having
 *  a short flash (i.e. a short flash ON, and then OFF the rest of the
 *  pattern).
 */
#define DukDEBUG_LED_PATTERN_FLASH_SHORT                                      \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x00000003UL                                                 \
                )

  /**
   * @brief C-Constant defining the long flash Debug LED blinking pattern.
   *
   * Definition of the C-Constant of the Debug LED blinking pattern for having
   *  a long flash (i.e. a long flash ON, and then OFF the rest of the pattern).
   */
#define DukDEBUG_LED_PATTERN_FLASH_LONG                                       \
    MukVAL_TYPED(TukDEBUG_LED_PATTERN,                                        \
                 0x000000FFUL                                                 \
                )

/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONSTANTS_H_INSIDE
#endif /* !defined(UK_CONSTANTS_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


