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
 * @file          uk_types.h
 * @brief         uKernel API - Main uKernel API Declarations file -
 *  C-Types sub-part.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is a sub-part of the main uKernel API file for a given uKernel
 *  Target dedicated to the definitions of the C-Types.
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
#if !defined(UK_TYPES_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by "uk.h" file.                       */
#if !defined(UK_H_INSIDE)
    #error 'The "uk_types.h" include file shall be included only in the "uk.h" file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_TYPES_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_TYPES_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed for the definition of the Public API
 *  of the uKernel. */

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */


/* ######################################################################## */
/*                            UKERNEL API - C-TYPES                         */
/* ######################################################################## */
/* Hereafter are defined the C-Types used in the uKernel API.
 *
 * @implementation As good coding practice, and to help developing high
 *  quality and robust software, all the meaningful elements of uKernel API
 *  have their own dedicated C-Type (strong typing policy used).
 */

/* The C-Type definitions shall not be done when this file is used by
 *  the C-Assembler. */
#if !defined(__ASSEMBLER__)

/* //////////////////////////////////////////////////////////////////////// */
/*                               C-TYPES - BASIC                            */
/* //////////////////////////////////////////////////////////////////////// */
/* The following basic C-Types definitions are aimed to make definition
 *  of uKernel C-Types that are independent of the C-Compiler and from the
 *  Platform used.
 *
 * NOTE: For sure, the definitions themselves of these basic C-Types used in
 *  the uKernel are C-Compiler dependent ;-).
 */

/* ======================================================================== */
/*                         C-TYPES - UKERNEL - BASIC                        */
/* ======================================================================== */
/* The types used in these definitions are defined by the C standard, starting
 *  with C99. */

/**
 * @brief uKernel C-Type for 8-bit signed value.
 */
typedef int8_t TukINT8;

/**
 * @brief uKernel C-Type for 16-bit signed value.
 */
typedef int16_t TukINT16;

/**
 * @brief uKernel C-Type for 32-bit signed value.
 */
typedef int32_t TukINT32;

/**
 * @brief uKernel C-Type for 64-bit signed value.
 */
typedef int64_t TukINT64;


/**
 * @brief uKernel C-Type for 8-bit unsigned value.
 */
typedef uint8_t  TukUINT8;

/**
 * @brief uKernel C-Type for 16-bit unsigned value.
 */
typedef uint16_t TukUINT16;

/**
 * @brief uKernel C-Type for 32-bit unsigned value.
 */
typedef uint32_t TukUINT32;

/**
 * @brief uKernel C-Type for 64-bit unsigned value.
 */
typedef uint64_t TukUINT64;


/**
 * @brief uKernel C-Type for performance optimized 8-bit unsigned value.
 *
 * @note In function of compiler chosen options, effective bit size of this
 *  C-Type can be more than 8-bit.
 */
typedef uint_fast8_t TukUINTFAST8;

/**
 * @brief uKernel C-Type for performance optimized 16-bit unsigned value.
 *
 * @note In function of compiler chosen options, effective bit size of this
 *  C-Type can be more than 16-bit.
 */
typedef uint_fast16_t TukUINTFAST16;

/**
 * @brief uKernel C-Type for performance optimized 32-bit unsigned value.
 *
 * @note In function of compiler chosen options, effective bit size of this
 *  C-Type can be more than 32-bit.
 */
typedef uint_fast32_t TukUINTFAST32;


/**
 * @brief uKernel C-Type for C 'void'.
 *
 * Definition of the uKernel C-Type for the C language 'void' concept.
 * This uKernel C-Type should be used only:
 *  - In C-Function declaration with no return value.
 *  - In C-Function declaration with no parameter.
 *
 * @note The redefinition of this C-Type is not aiming C-Compiler or
 *  Platform independence; it is only done to have harmonized dedicated
 *  C-Type for uKernel.
 *
 * @usage In the framework of good coding practice and code robustness, as
 *  much as possible the usage of this C-Type shall be avoided in pointer
 *  definition to reference an object of unspecified type.
 *  That's the reason why no specific uKernel C-Type for 'void' pointer has
 *  been defined.
 */
typedef void TukVOID;


/**
 * @brief uKernel C-Type for Boolean value.
 *
 * Definition of the uKernel C-Type for boolean value (true / false).
 * The instantiation of this C-Type is compiler dependent but is guaranteed to
 *  be large enough to store the following literal numerical values:
 *   - DukBOOL_FALSE: boolean 'False'.
 *   - DukBOOL_TRUE: boolean 'True'.
 *
 * @note On GCC ARM C-Compiler, this C-Type is coded on one byte.
 *  Excepting when included in a structure definition ('struct'), where it can
 *   be optimized as 1-bit field.
 *
 * @usage When returning boolean values that may be linked to security,
 *  safety or robustness functionalities, this C-Type SHALL NOT be used, and
 *  the C-Type TukSAFEBOOL SHALL BE used instead.
 */
typedef _Bool TukBOOL;



/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - UKERNEL - GENERIC                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a 8-bit sequential index of an element in an
 *  array.
 *
 * Definition of the uKernel C-Type for a 8-bit index of an element in an
 *  array.
 * The valid values for such an index are in the range of sequential values
 *  between a minimal and maximal value. If no minimal value is defined, then
 *  it is assumed to be null(0).
 *
 * @usage When used as index of a C-Array, the valid range is between 0 up to
 *  the size of the array minus one (i.e. 'sizeof(Array) - 1').
 *
 * @usage This C-Type shall be used for referencing the index of an element in
 *  an array. It shall not be used as address offset (use TukOFFSET32 instead).
 */
typedef TukUINT8 TukIDX8;

/**
 * @brief uKernel C-Type for a 16-bit sequential index of an element in an
 *  array.
 *
 * Definition of the uKernel C-Type for a 16-bit index of an element in an
 *  array.
 * The valid values for such an index are in the range of sequential values
 *  between a minimal and maximal value. If no minimal value is defined, then
 *  it is assumed to be null(0).
 *
 * See TukIDX8 for more details.
 */
typedef TukUINT16 TukIDX16;

/**
 * @brief uKernel C-Type for a 32-bit sequential index of an element in an
 *  array.
 *
 * Definition of the uKernel C-Type for a 32-bit index of an element in an
 *  array.
 * The valid values for such an index are in the range of sequential values
 *  between a minimal and maximal value. If no minimal value is defined, then
 *  it is assumed to be null(0).
 *
 * See TukIDX8 for more details.
 */
typedef TukUINT32 TukIDX32;

/**
 * @brief uKernel C-Type for a Bit Number in a bit field.
 *
 * Definition of the uKernel C-Type for a 8-bit value coding the bit number in
 *  a bit field or in a data word.
 * The valid values for such a number are in the range of sequential values
 *  between null(0) and the size in bits minus one(1) of the bit field.
 *
 * Excepted specified otherwise, the 'LSB 0' notation is used: the bit number
 *  0 is associated to the Less Significant bit (rightmost bit) of the bit
 *  field or of the data word; Then each bit number increment corresponds to
 *  the bit immediately to the left in the value.
 */
typedef TukUINT8 TukBITNUM;


/**
 * @brief uKernel C-Type for a 8-bit count value.
 *
 * Definition of the uKernel C-Type for a 8-bit value coding the count of
 *  objects instances, occurrences of an event or of possibly non-contiguous
 *  elements in a given set or sub-set.
 *
 * @usage This C-Type shall not be used for referencing the index of an element
 *  in a C-array (use TukIDX8 instead) or contiguous elements in a C-Array
 *  or an Address Block (use TukLENGTH8 instead).
 */
typedef TukUINT8 TukCOUNT8;

/**
 * @brief uKernel C-Type for a 16-bit count value.
 *
 * Definition of the uKernel C-Type for a 16-bit value coding the count
 *  objects instances, occurrences of an event or of possibly non-contiguous
 *  elements in a given set or sub-set.
 *
 * See TukCOUNT8 for more details.
 */
typedef TukUINT16 TukCOUNT16;

/**
 * @brief uKernel C-Type for a 32-bit count value.
 *
 * Definition of the uKernel C-Type for a 32-bit value coding the count of
 *  objects instances, occurrences of an event or of possibly non-contiguous
 *  elements in a given set or sub-set.
 *
 * See TukCOUNT8 for more details.
 */
typedef TukUINT32 TukCOUNT32;

/**
 * @brief uKernel C-Type for a 64-bit count value.
 *
 * Definition of the uKernel C-Type for a 64-bit value coding the count of
 *  objects instances, occurrences of an event or of possibly non-contiguous
 *  elements in a given set or sub-set.
 *
 * See TukCOUNT8 for more details.
 */
typedef TukUINT64 TukCOUNT64;


/**
 * @brief uKernel C-Type for a 8-bit length in bytes.
 *
 * Definition of the uKernel C-Type for a 8-bit length value coding the number
 *  of contiguous bytes in a C-Array or in an Address Block (i.e. continuous
 *  memory area).
 *
 * @usage This C-Type shall not be used for counting non contiguous elements
 *  (use TukCOUNT8 instead) or bit number (use TukBITNUM8 instead).
 */
typedef TukUINT8 TukLENGTH8;

/**
 * @brief uKernel C-Type for a 16-bit length in bytes.
 *
 * Definition of the uKernel C-Type for a 16-bit length value coding the number
 *  of contiguous bytes in a C-Array or in an Address Block (i.e. continuous
 *  memory area).
 *
 * See TukLENGTH8 for more details.
 */
typedef TukUINT16 TukLENGTH16;

/**
 * @brief uKernel C-Type for a 32-bit length in bytes.
 *
 * Definition of the uKernel C-Type for a 32-bit length value coding the number
 *  of contiguous bytes in a C-Array or in an Address Block (i.e. continuous
 *  memory area).
 *
 * See TukLENGTH8 for more details.
 */
typedef TukUINT32 TukLENGTH32;


/**
 * @brief uKernel C-Type for a 8-bit bitmask.
 *
 * Definition of the uKernel C-Type for a 8-bit bitmask.
 *
 * A bitmask consists in a set of bits coded in a value, where each bit set
 *  corresponds to the mask to apply to keep only these bits in a value. The
 *  application of the mask is made using a 'AND' logical operation.
 *
 * @implementation The bit 0 of the mask, called its Lsb (Less significant bit)
 *  is the rightmost bit in the value.
 */
typedef TukUINT8 TukBITMASK8;

/**
 * @brief uKernel C-Type for a 16-bit bitmask.
 *
 * Definition of the uKernel C-Type for a 16-bit bitmask.
 *
 * See TukBITMASK8 for more details.
 */
typedef TukUINT16 TukBITMASK16;

/**
 * @brief uKernel C-Type for a 32-bit bitmask.
 *
 * Definition of the uKernel C-Type for a 32-bit bitmask.
 *
 * See TukBITMASK8 for more details.
 */
typedef TukUINT32 TukBITMASK32;


/**
 * @brief uKernel C-Type for a 64-bit bitmask.
 *
 * Definition of the uKernel C-Type for a 64-bit bitmask.
 *
 * See TukBITMASK8 for more details.
 */
typedef TukUINT64 TukBITMASK64;


/**
 * @brief uKernel C-Type for a 32-bit address in MCU addressing space.
 *
 * Definition of the uKernel C-Type for a 32-bit address value, referring
 *  to a memory word or peripheral register in the address space of the MCU.
 *
 * @implementation The current uKernel implementation relies on the fact that
 *  the address space that can be accessed by the MCU (memory space,
 *  peripherals, ...) can be fully addressed using such a 32-bit address.
 *
 * @usage The C-Type 'void *' or 'TukVOID *' shall NOT be used when
 *  manipulating address value. This C-Type shall be used instead.
 *
 * @usage All non specific (i.e. with their one C-Type) C-Constants,
 *  C-Variables and parameters referencing an element in MCU address space
 *  (either memory value address, memory structure address, or peripheral
 *  registers address) should use this C-Type.
 */
typedef TukUINT32 TukADDRESS32;


/**
 * @brief uKernel C-Type for a an Address Block in MCU addressing space.
 *
 * Definition of the uKernel C-Type for an Address Block in MCU addressing
 *  space.
 * An Address Block is a range of continuous addresses in the MCU addressing
 *  space, referring to storage memory (RAM, Flash), or a set of MCU Registers
 *  (MCU Core configuration, Peripherals configuration and management).
 *
 * The structure of the Address Block consists in the following elements:
 *  - (TukADDRESS32)<Start32>: Start address of the Address Block (this
 *   address belongs to the Address Block).
 *  - (TukLENGTH32)<Length32>: Length in bytes of the Address Block.
 *
 * @robustness The last address of an Address Block whose length is not null
 *  (i.e. <Length32> != 0) SHALL BE be computed as this:
 *    MukVAL_ADD_CHECK_OVERFLOW(<Start32>,
 *                              <Length32> - 1),
 *                              &<AddressLast32>)
 *  and the boolean result of the check SHALL BE controlled.
 *
 * @implementation The current uKernel implementation relies on the fact that
 *  the address space that can be accessed by the MCU (memory space,
 *  peripherals, ...) can be fully addressed using such a 32-bit address.
 */
typedef struct {
    TukADDRESS32    Start32;
    TukLENGTH32     Length32;
    } TukADDRESSBLOCK;


/**
 * @brief uKernel C-Type for a an Address Range in MCU addressing space.
 *
 * Definition of the uKernel C-Type for an Address Range in MCU addressing
 *  space.
 * An Address Range is a range of continuous addresses in the MCU addressing
 *  space, referring to storage memory (RAM, Flash), or a set of MCU Registers
 *  (MCU Core configuration, Peripherals configuration and management).
 *
 * The structure of the Address Block consists in the following elements:
 *  - (TukADDRESS32)<Start>: Start address of the Address Range (this
 *   address belongs to the Address Block).
 *  - (TukADDRESS32)<Endp1>: Length in bytes of the Address Block.
 *
 * @implementation The current uKernel implementation relies on the fact that
 *  the address space that can be accessed by the MCU (memory space,
 *  peripherals, ...) can be fully addressed using such a 32-bit address.
 */
typedef struct {
    TukADDRESS32    Start;
    TukLENGTH32     Endp1;
} TukADDRESSRANGE;


/**
 * @brief uKernel C-Type for a 32-bit offset in bytes.
 *
 * Definition of the uKernel C-Type for a 32-bit offset in bytes relative to
 *  a starting base address.
 *
 * @warning  In the framework of good coding practice and code robustness, it
 *  SHALL ALWAYS be enforced that no overflow occurs when adding an offset to
 *  a base address (i.e. for example by checking that resulting address is
 *  bigger than added offset, checking 'Carry' flag in CPU Core ALU condition
 *  register, or using C-Macro MukVAL_ADD_CHECK_OVERFLOW).
 *
 * @usage This C-Type shall be used only in conjunction with an MCU address
 *  (see TukADDRESS32) to build a new MCU address.
 */
typedef TukUINT32 TukOFFSET32;


/**
 * @brief uKernel C-Type for a Safe Boolean value.
 *
 * Definition of the uKernel C-Type for a Safe Boolean value.
 * A Safe Boolean is aiming at providing additional confidence to store a
 *  'True' or 'False' boolean state in case of unexpected code execution
 *  behaviors due to bugs, hardware failure, attacks, ...
 *
 * To provide such additional confidence, a Safe Boolean value is defined
 *  using specific internal coding with numerical literal 16-bit values:
 *   - DukSAFEBOOL_TRUE: 'True' state.
 *   - DukSAFEBOOL_FALSE: 'False' state.
 *   - All other possible 16-bit values: invalid and shall trigger a Fatal
 *    Error in the implementation.
 *
 * @robustness As compared to <TukBOOL>, this C-Type is slightly less efficient
 *  in code/data size, and in performance. But properly implemented, it
 *  increases significantly the robustness of the implementation.
 *
 * @usage It is recommended to use this C-Type rather than the <TukBOOL>
 *  C-Type for manipulating boolean states that are linked to security,
 *  safety or robustness functionalities.
 */
typedef TukUINT32 TukSAFEBOOL;


/**
 * @brief uKernel C-Type for a 32-bit Magic Number value.
 *
 * Definition of the uKernel C-Type for a 32-bit Magic Number value.
 * A Magic Number is a C-Constant value that can be used to (non exhaustive
 *  list):
 *  - Act as a label at a specific offset in memory or array to bring some
 *   good level of confidence on the presence of an expected specific
 *   structure or data set.
 *  - As 'canaries' value to detect unexpected modifications of some memory
 *   area or data set. After being set during initialization or startup phase,
 *   if at some point of execution the Magic Number value set has been
 *   modified, then it implies that some unexpected execution has occurred.
 *
 * @usage A Magic Number can be used to bring some good confidence level in the
 *  validity of some memory area or data set, but it cannot enforce it
 *  alone: additional integrity and/or authenticity values with proper level
 *  of entropy shall be added to effectively enforce validity and robustness
 *  (e.g. duplication of value, signature, ...).
 *
 * @usage This Magic Number has a middle level of entropy, and thus unexpected
 *  random collision with non Magic Number value may still arise with a
 *  non-negligible probability. If almost negligible probability is required,
 *  it is advised to use its 64-bit version (see TukMAGIC64).
 *
 * @usage This C-Type Magic Number SHALL NOT BE used to protect values which
 *  are dynamic at runtime: the checksum C-Type SHALL BE used instead (see
 *  TukCHECKSUM32, TukCHECKSUM64).
 */
typedef TukUINT32 TukMAGIC32;


/**
 * @brief uKernel C-Type for a 64-bit Magic Number value.
 *
 * Definition of the uKernel C-Type for a 64-bit Magic Number value.
 *
 * This C-Type is similar (same purpose/usage) as TukMAGIC32 (see associated
 *  documentation for more details).
 *
 * @usage This Magic Number has a good level of entropy, and thus unexpected
 *  random collision with non Magic Number value may still arise but with a
 *  very low (in general negligible) probability.
 *
 * @usage This C-Type Magic Number SHALL NOT BE used to protect values which
 *  are dynamic at runtime: the checksum C-Type SHALL BE used instead (see
 *  TukCHECKSUM32, TukCHECKSUM64).
 */
typedef TukUINT64 TukMAGIC64;



/**
 * @brief uKernel C-Type for a 32-bit Checksum value.
 *
 * Definition of the uKernel C-Type for a 32-bit Checksum value.
 * A Checksum value can be used to protect sensitive dynamic values (internal
 *  state, credentials, hardware configuration, ...) stored in C-Variables or
 *  memory areas by (non exhaustive list):
 *  - Increasing the level of confidence in its integrity for the values
 *   (due to hardware memory failure, bugs, logical attacks...).
 *  - Increase the robustness against unauthorized execution paths by detecting
 *   inconsistent (non-atomic) modifications due to some part of the
 *   implementation not (yet) executed.
 *
 * @usage A Checksum can be used to bring some good confidence level in the
 *  validity of some dynamic values stored in C-Variables or memory areas.
 *  The level of confidence bought depends of the entropy of the values
 *  protected by the Checksum (it is optimal if the Checksum has the same
 *  number of significant bits than the value protected).
 */
typedef volatile TukUINT32 TukCHECKSUM32;


/**
 * @brief uKernel C-Type for a 64-bit Checksum value.
 *
 * Definition of the uKernel C-Type for a 64-bit Checksum value.
 *
 * This C-Type is similar (same purpose/usage) as TukCHECKSUM32 (see associated
 *  documentation for more details).
 */
typedef volatile TukUINT64 TukCHECKSUM64;


/**
 * @brief uKernel C-Type for a 32-bit Access Key value.
 *
 * Definition of the uKernel C-Type for a 32-bit Access Key value.
 * An Access Key is used to grant access to uKernel Resources (e.g. sensitive
 *  data) or uKernel Privileged Services performing critical operation (e.g.
 *  erasing part of persistent memory).
 *
 * @robustness An Access Key allows to increase implementation robustness by
 *  preventing misuse due to unexpected code execution path (bug in ukApp code,
 *  SFI attacks, ...).
 *
 * @implementation In general, Access Key value is randomly updated upon each
 *  new uKernel Session. For some specific case, it can also be fixed upon
 *  first uKernel Session, or updated after each usage.
 */
typedef TukUINT32 TukACCESSKEY32;


/**
 * @brief uKernel C-Type for CRC32 value based on ISO 3309.
 *
 * Definition of the uKernel C-Type for a 32-bit CRC value computed as
 *  specified in the ISO3309 standards.
 *
 * @usage A CRC32 value can be used to enhance the confidence level in the
 *  integrity of a data set. But this confidence level is limited by the middle
 *  level of entropy of such a value (32-bit only); and thus even a valid CRC32
 *  may not be sufficient in some case to provide proper guarantee of integrity
 *  of a data set.
 *  Also a CRC32 value does not bring any guarantee on the authenticity of a
 *  data set (cryptographic signature shall be used instead).
 */
typedef TukUINT32 TukCRC32;


/**
 * @brief uKernel C-Type for CRC64 value based on ECMA-182.
 *
 * Definition of the uKernel C-Type for a 64-bit CRC value computed as
 *  specified in the ECMA-182 standards.
 *
 * @usage A CRC64 value can be used to enhance the confidence level in the
 *  integrity of a data set. But this confidence level is limited, even if
 *  quite significant due to the level of entropy of such a value (64-bit); and
 *  thus even a valid CRC64 may not be sufficient in some case to provide
 *  proper guarantee of integrity of a data set.
 *  Also a CRC64 value does not bring any guarantee on the authenticity of a
 *  data set (cryptographic signature shall be used instead).
 */
typedef TukUINT64 TukCRC64;


/**
 * @brief uKernel C-Type for a SHA256 Hash value.
 *
 * Definition of the uKernel C-Type for a SHA256 Hash Value (256-bit) computed
 *  as specified in the FIPS 180-4 standard (March 2012).
 *
 * @usage This C-Type is structured as an array of eight 32-bit unsigned words.
 */
typedef TukUINT32 TukHASH_SHA256[8];


/**
 * @brief uKernel C-Type for the Tag field of a TLV-formated data set.
 *
 * Definition of the uKernel C-Type for the 8-bit Tag field value <T> of a TLV
 *  (Tag/Length/Value) formatted data set.
 *
 * The structure of a TLV-formated data set is as follows (length is between
 *  brackets '[ ]' and is given in bytes; the field name is between '< >'):
 *  - [ 1 ] <T>: Tag referencing unambiguously the nature and the internal
 *   structure of the Value <V> field.
 *  - [ 1 ] <L>: Length of the Value <V> field in bytes. A null Length
 *   indicates that no Value <V> field is present. The maximal possible length
 *   is 255 bytes.
 *  - [<L>] <V>: Value. The length of this field is exactly <L> bytes. The
 *   contents of this field shall be ignored if Length <L> field is null.
 */
typedef TukUINT8 TukTLV_TAG;


/**
 * @brief uKernel C-Type for the Length field of a TLV-formated data set.
 *
 * Definition of the uKernel C-Type for the 8-bit Length field value <L> of a
 *  TLV (Tag/Length/Value) formatted data set.
 *
 * See TukTLV_TAG for more details.
 */
typedef TukUINT8 TukTLV_LENGTH;



/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - UKERNEL - BIT VECTOR                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a Bit Number in a Bit Vector.
 *
 * Definition of the uKernel C-Type for a 16-bit value coding the bit number in
 *  a Bit Vector.
 * The valid values for such a number are in the range of sequential values
 *  between null(0) and the size in bits minus one(1) of the Bit Vector.
 * In a Bit Vector, the Bit Number 0 is the leftmost bit of the first C-Array
 *  element of the Bit Vector ('MSB 0' convention).
 *
 * @warning The bit numbering in a Bit Vector ('MSB 0' convention) IS NOT the
 *  same as the one documented in the Bit Number C-Type TukBITNUM, which is
 *  using the classical 'LSB 0' convention.
 */
typedef TukUINT16 TukBITVECTOR_BITNUM;


/**
 * @brief uKernel C-Type of each underlying array element composing a Bit
 *  Vector.
 *
 * Definition of the uKernel C-Type for each underlying array element
 *  composing a Bit Vector.
 * A Bit Vector is a data structure used for storing compactly a set/field
 *  of bits. Each bit can be manipulated individually and is referenced
 *  unambiguously by its sole Bit Number.
 *
 * In order to keep abstraction level on the implementation of a Bit Vector
 *  (as it is as much as possible optimized for each MCU architecture):
 *  - The C-Macro MukBITVECTOR_CTYPE_DEFINE should be used for defining a
 *   C-Type that is structured as a field of bits (i.e. a Bit Vector).
 *  - The following uKernel Helpers should be used to manipulate a C-Variable
 *   with a C-Type defined as a Bit Vector:
 *   + ukBitVectorClear: Clear the whole Bit Vector.
 *   + ukBitVectorSetBit: Set a bit in a Bit Vector.
 *   + ukBitVectorResetBit: Clear a bit in a Bit Vector.
 *   + ukBitVectorInvertBit: Invert a bit in a Bit Vector.
 *   + ukBitVectorTestBit: Test a bit in a Bit Vector.
 *
 * @warning The bit numbering in a Bit Vector ('MSB 0' convention) IS NOT the
 *  same as the one documented in the Bit Number C-Type TukBITNUM, which is
 *  using the classical 'LSB 0' convention.
 *
 * @implementation The choice of having the Bit Number 0 as the leftmost bit of
 *  the first C-Array element of the Bit Vector ('MSB 0' convention) is to keep
 *  a bit numbering independent of the number of bits <n> stored in the Bit
 *  Vector (i.e. if the size of the Bit Vector increase, the first elements
 *  keep the same numbering; this may be important for bit fields related to
 *  configuration items, ...).
 *
 * @implementation A Bit Vector of <n> bits is implemented as a C-Array of <k>
 *  elements, each of this element being a word storing <w> bits, with w=32.
 *  Each C-Type defined as a Bit Vector is indeed a C-Pointer to the start
 *  Address of this C-Array.
 *  The number of elements <k> of the C-Array for storing <n> bits is
 *  <k> = ((<n>+<w>-1) / <w>). It shall be computed using the uKernel Macro
 *  MukBITVECTOR_ELEMENT_COUNT.
 *
 * @implementation The Bit Number numbering is using the 'MSB 0' convention:
 *  the number 0 represents the leftmost bit of the first element (index 0)
 *  of the C-Array composing the Bit Vector. Then each bit number increment
 *  corresponds to the bit immediately to the right in the word, and then as
 *  next index in the C-Array.
 *
 * @implementation This definition is optimized for 32-bit MCU, allowing to
 *  have efficient low level code for manipulating its bits.
 */
typedef TukUINT32 TukBITVECTOR_ELEMENT;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - CHAR & STRING                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a printable ASCII character.
 *
 * Definition of the uKernel C-Type for a printable ASCII character.
 *
 * @usage If the character is part of a Null Terminated String (NTString), the
 *  C-Type TukNTSTRING_CHAR should be used instead.
 */
typedef char TukCHAR;

/**
 * @brief uKernel C-Type for a printable ASCII character of a Null Terminated
 *  String (NTString).
 *
 * Definition of the uKernel C-Type for a printable ASCII character that is
 *  part of a Null Terminated String (see TukNTCSTRING_ADDRESS).
 *
 * @usage If the character is not part of a Null Terminated String (NTString),
 *  the C-Type TukCHAR should be used instead.
 */
typedef TukCHAR TukNTSTRING_CHAR;

/**
 * @brief uKernel C-Type for the address of a Null Terminated String (NTString).
 *
 * Definition of the uKernel C-Type for the address of a Null Terminated
 *  String (NTString).
 * This C-Type defines the NTString as the start Address of an array whose
 *  elements are printable ASCII characters (see TukNTSTRING_CHAR) and whose
 *  last element is the first null character in the array.
 *
 * @usage The length of a NTString (i.e. the number of printable ASCII
 *  characters from the start address till the first null character) shall
 *  be stored using C-Type TukLENGTH8 or TukLENGTH16.
 */
typedef TukNTSTRING_CHAR const *TukNTCSTRING_ADDRESS;


/* //////////////////////////////////////////////////////////////////////// */
/*                             C-TYPES - LINKER                             */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for Linker values imported as constants in the code.
 *
 * Definition of the uKernel C-Type for importing Linker values as 32-bit
 *  constants in the code.
 * The imported Linker values can be either defined as numerical constants in
 *  a Linker File, or computed dynamically by the Linker during the linking
 *  process.
 *
 * @usage The constants imported with this C-Type in the code shall have the
 *  following prefix:
 *  - '_LD': Linker constant defined as a numeric constant value in a Linker
 *   script.
 *  - '_L': Linker constant generated by the Linker during the linking process.
 *
 * @usage These C-Constants shall be referenced in the source code with a
 *  prefix '&'.
 *
 * @note This type is being considered for deprecation in favor of
 *  TukLINKER_DEFINITION.
 */
typedef TukUINT32 TukLINKER_DEFINITION32;

/**
 *
 * @brief Dummy C-Type for Linker values imported as constants in the code.
 *
 * This is a C forward declaration for a type that SHALL never be declared.
 *  The point is to allow for a type with no special alignment properties, and
 *  whose usage is detected as invalid.
 *
 * @usage The only valid use of this type is through the TukLINKER_DEFINITION
 *  type alias.
 */
struct linker_symbol_t;

/**
 * @brief uKernel C-Type for Linker values imported as constants in the code.
 *
 * Definition of the uKernel C-Type for importing Linker values. The imported
 *  values can either be defined as numerical constants in the Linker File,
 *  or computed by the Linker during the linking process.
 *
 * @usage The constants imported with this C-Type in the code shall have the
 *  following prefix:
 *  - '_LD': Linker constant defined as a numeric constant value in a Linker
 *   script.
 *  - '_L': Linker constant generated by the Linker during the linking process.
 *
 * @usage These C-Constants shall be referenced in the source code with a
 *  prefix '&'. Indeed the value of the variable is generally undefined, only
 *  the variable's address (a 32-bit value) is relevant.
 *
 * @note This type is being considered as replacement for
 *  TukLINKER_DEFINITION32.
 */
typedef struct linker_symbol_t TukLINKER_DEFINITION;


/* //////////////////////////////////////////////////////////////////////// */
/*                C-TYPES - UKERNEL - IDENTIFICATION AND LABEL              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a 128-bit Universally Unique Identifier (UUID).
 *
 * Definition of the uKernel C-Type for a 128-bit Universally Unique Identifier
 *  (UUID).
 * A Universally Unique Identifier (UUID) is an Identifier used to reference
 *  globally a resource (e.g. ukApp, ...) in the complete infrastructure from
 *  which the uKernel Image is part of.
 * The UUID value contents is based on RFC4122 (July 2005). It is a
 *  which is built as proposed by RFC4122 (preferably using time-based option
 *  #4.2 to minimize collision).
 *
 * @implementation The different fields of the UUID structure defined in
 *  RFC4122 are never interpreted by the uKernel.
 *
 * @usage The 128-bit size of the UUID allow enough entropy to be able to
 *  enforce reasonable uniqueness to use it as a reliable Identifier in a
 *  complete infrastructure composed of numerous (up to millions) uKernel
 *  Systems (without full guarantee however).
 *
 * @usage This C-Type is structured as a table of four 32-bit words to
 *  maximize the efficiency of its manipulation by most MCUs.
 */
typedef TukUINT32 TukUUID128[4];

/**
 * @brief uKernel C-Type for a 16-bit Short Label (SLABEL) local to the ukApps
 *  Bundle.
 *
 * Definition of the uKernel C-Type for a 16-bit Short Label.
 * A Short Label (SLABEL) is a 16-bit numerical value used to reference
 *  inside a set of elements of the same nature unambiguously a given element
 *  (or a sub-set of elements).
 * A Short Label is significant only in the current ukApps Bundle. Its value
 *  is constant among the uKernel Sessions.
 *
 * The value of a Short Label is either:
 *  - Developer defined: A Short Label is then used to name a given element of
 *   a ukApp. This name can then be used in the ukApp code when invoking a
 *   uKernel Service to reference this specific element.
 *  - Predefined by the uKernel implementation: it is the case notably for
 *   the Short Label values used for virtually referencing the empty sub-set
 *   or the full set of elements of the same nature.
 *
 * Example: A Short Label can be used inside a ukApp to reference a given
 *  Address Block among its set of Extra Address Blocks defined in its
 *  Descriptor.
 *
 * @implementation The 16-bit size has been chosen to allow to easily keep
 *  unicity and consistency for the developer when naming the elements of a
 *  set, while also limiting the amount of memory used for storing it.
 *
 * @usage A SLABEL value is a reference local to each ukApps Bundle. Thus a
 *  SLABEL shall never be used by a ukApp as a global universal name for
 *  referencing an element outside from the current ukApps Bundle
 *  (e.g. its value shall not be used with online server, etc...). For such
 *  need, an UUID shall be defined for the concerned element (see
 *  TukUUID128).
 *
 * @usage This C-Type should not be used directly but as a basis for defining
 *  other Short Label C-Type dedicated to specific domains or needs (it allows
 *  to keep consistency among definitions).
 */
typedef TukUINT16 TukSLABEL16;


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-TYPES - UKERNEL - VERSION MANAGEMENT                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for defining a Version number.
 *
 * Definition of the uKernel C-Type for a 32-bit Version number value.
 * A Version number is used inside uKernel Image to manage the identification
 *  of a software Release. The identification consists in a specific value
 *  built from the last modified state of the set of used implementations of
 *  the software, and from applied compilation options and configuration.
 * Such a Version number is used notably to identify each part composing the
 *  uKernel Image (uKernel Core and ukApps part of the ukApps Bundle).
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...24] <MM>: Major Version incremented when the set of functionalities
 *   or services implemented in the implementation are modified, and that
 *   these modifications mandate the update of other implementation parts or of
 *   or external services / peripherals relying on it.
 *  - [23...16] <mm>: Minor Version incremented only when the set of
 *   functionalities or services in the implementation are modified, but these
 *   modifications do not mandate the update of other implementation parts or
 *   of external services / peripherals relying on it (e.g. addition of new
 *   functionalities whose usage is not mandatory in legacy code).
 *  - [15...00] <uuuu>: Micro Version incremented upon an update of the
 *   implementation that does not modify any of its functionalities or services
 *   (bug correction, performance improvements, etc...).
 *
 * The C-Type Version is structured as this:
 * |-----------------------|--------------------------------------------------
 * |      Bit number       |                  Description                     |
 * |31...24|23...16|15...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | Major Version <MM> (8-bit)                       |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | Minor Versions <mm> (8-bit)                      |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Micro Version <uuuu> (16-bit)                    |
 * |-------|-------|-------|--------------------------------------------------|
 *
 *
 * @implementation The default uKernel Security Policy upon update of a
 *  resource (uKernel Core implementation, uKernel Configuration, ukApp
 *  implementation) is to enforce that updated resource has a Version value
 *  strictly higher than the current one.
 *
 * @usage A Version value is shall be considered as valid only if <Major> and
 *  <Minor> fields are not both null.
 */
typedef TukUINT32 TukVERSION;



/* //////////////////////////////////////////////////////////////////////// */
/*                             C-TYPES - PLATFORM                           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Identifier of an MCU Device.
 *
 * Definition of the uKernel C-Type for a 128-bit Identifier for an MCU Device.
 * This Identifier allows to reference the Manufacturer, Family, Reference in
 *  the family, and Revision of the MCU used on the Platform.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [127...96] Manufacturer: Value identifying the company that has
 *   manufactured the MCU.
 *  - [95...64] Family: Value identifying the family reference of the MCU for
 *   the given Manufacturer.
 *   NOTE: This value is linked to the given Manufacturer; Interpretation of
 *    Family values are fully disconnected for different Manufacturers.
 *  - [63...32] Reference: Value corresponding to the reference of the MCU for
 *   the given Manufacturer and Family.
 *   NOTE: This value is linked to the given Manufacturer and Family;
 *    Interpretation of Reference values are fully disconnected for different
 *    Manufacturers and Families.
 *  - [31...00] Revision: Revision of the given Reference.
 *
 * The C-Type MCU Device Identifier is structured as this:
 * |-----------------------------------|--------------------------------------|
 * |           Bit number              |              Description             |
 * |127...96| 95...64| 63...32| 31...00|                                      |
 * |:------:|:------:|:------:|:------:|--------------------------------------|
 * |  xxxxx |        |        |        | Manufacturer (32-bit)                |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |  xxxxx |        |        | Family (32-bit)                      |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |  xxxxx |        | Reference in Family (32-bit)         |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |        |  xxxxx | Revision (32-bit)                    |
 * |--------|--------|--------|-----------------------------------------------|
 *
 */
typedef TukBITVECTOR_ELEMENT TukMCU_ID_bv[MukBITVECTOR_ELEMENT_COUNT(128U)];


/**
 * @brief uKernel C-Type for the Identifier of the CPU Core in an MCU Device.
 *
 * Definition of the uKernel C-Type for a 64-bit Identifier for the CPU Core
 *  in an MCU Device.
 * This Identifier allows to reference the Manufacturer, Architecture type,
 *  and Revision of the CPU Core inside the MCU used in the Platform.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [63...32] Manufacturer: Value identifying the company that has
 *   manufactured the CPU Core.
 *  - [31...16] Architecture: Value identifying the architecture reference of
 *   the MCU for the given Manufacturer.
 *   NOTE: This value is linked to the given Manufacturer; Interpretation of
 *    Architecture values are fully disconnected for different Manufacturers.
 *  - [15...00] Revision: Revision of the given Architecture.
 *
 * The C-Type CPU Core Identifier is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |         Bit number    |                   Description                    |
 * |63...32|31...16|15...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | Manufacturer (32-bit)                            |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | Architecture (16-bit)                            |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Revision (16-bit)                                |
 * |-------|-------|-------|--------------------------------------------------|
 *
 */
typedef TukUINT64 TukCPU_CORE_ID;


/**
 * @brief uKernel C-Type for the Identifier of the Platform.
 *
 * Definition of the uKernel C-Type for a 128-bit Identifier for a Platform,
 *  allowing to identify the Designer, Type, Reference for given Type, and
 *  Options for a Platform.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [127...96] Designer: Value identifying the company that
 *   has designed the Platform.
 *  - [95...64] Type: Value identifying the type of the Platform as given by
 *   the company who has designed it (this value shall not be dependent from
 *   the Manufacturer but only from the Designer).
 *  - [63...32] Reference: Value identifying the reference of the Platform as
 *   given by the company who has designed it (this value shall not be
 *   dependent from the Manufacturer but only from the Designer).
 *  - [31...00] Options: Value allowing to indicate some options or
 *   configuration of the given reference (this value is reference dependent).
 *   In case no option or configuration exists for a given reference, null(0)
 *   value shall be returned.
 *
 * The C-Type Platform Identifier is structured as this:
 * |-----------------------------------|--------------------------------------|
 * |           Bit number              |              Description             |
 * |127...96| 95...64| 63...32| 31...00|                                      |
 * |:------:|:------:|:------:|:------:|--------------------------------------|
 * |  xxxxx |        |        |        | Designer (32-bit)                    |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |  xxxxx |        |        | Type (32-bit)                        |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |  xxxxx |        | Reference for Type (32-bit)          |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |        |  xxxxx | Option (32-bit)                      |
 * |--------|--------|--------|-----------------------------------------------|
 *
 */
typedef TukBITVECTOR_ELEMENT TukPLATFORM_ID_bv[MukBITVECTOR_ELEMENT_COUNT(128U)];

/**
 * @brief uKernel C-Type for a 128-bit Serial Number.
 *
 * Definition of the uKernel C-Type for a 128-bit Serial Number.
 *
 * @implementation This C-Type  is structured as an array of BitVector
 *  elements (see TukBITVECTOR_ELEMENT).
 */
typedef TukBITVECTOR_ELEMENT TukSERIALNUMBER128_bv[MukBITVECTOR_ELEMENT_COUNT(128U)];



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - PLATFORM - STATE                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Platform State.
 *
 * Definition of the uKernel C-Type for the current Platform State.
 *
 * The Platform State allows to retrieve information on its current state
 *  (nominal state, state change request ongoing) and to perform action
 *  on it (e.g. state change request to perform an MCU Reset).
 *
 * The Platform State can take the following values:
 *  - DukPLATFORM_STATE_NOMINAL: The Platform is running in a nominal state.
 *  - DukPLATFORM_STATE_REQUEST_MCU_RESET: Request for an MCU Reset (restart).
 *   The uKernel will trigger a uKernel Session End, and then an MCU Reset. A
 *   new uKernel Session will start immediately afterwards.
 *  - DukPLATFORM_STATE_REQUEST_MCU_HALT: Request for an MCU Halt (shutdown).
 *   The uKernel will trigger a uKernel Session End, and then an MCU Halt.
 *   An external reset signal sent to the MCU will then be necessary to start
 *   a new uKernel Session. Till then, the MCU will remain halted.
 *
 * @usage Current Platform State can be retrieved or updated using Platform
 *  Attribute Tag DukPLATFORM_ATTRIBUTE_TAG_STATE and the C-Functions
 *  ukPlatformGetAttribute() and ukPlatformSetAttribute().
 */
typedef TukUINT32 TukPLATFORM_STATE;


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - PLATFORM - ATTRIBUTES                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Tag of a Platform Attribute.
 *
 * Definition of the uKernel C-Type for the Tag of a Platform Attribute.
 * The Tag value allows to reference unambiguously a Platform Attribute, in
 * order to get or set its value (see the C-Functions ukPlatformGetAttribute()
 * and ukPlatformSetAttribute()).
 *
 * A Platform Attribute allows to access to current configuration data of the
 *  Platform hardware onto which the uKernel is running, such as:
 *  - MCU Identification
 *  - Board Identification
 *  - Clock configuration
 *  - Memory resources
 *  - ...
 *
 * The Platform Attributes are always managed as a TLV (Tag/Length/Value)
 *  structure (see TukTLV_TAG for details).
 *
 * The following Platform Attributes are defined (see associated documentation
 *  for the details of their TLV structure):
 * - DukPLATFORM_ATTRIBUTE_TAG_MCU_ID
 * - DukPLATFORM_ATTRIBUTE_TAG_CPU_CORE_ID
 * - DukPLATFORM_ATTRIBUTE_TAG_PLATFORM_ID
 * - DukPLATFORM_ATTRIBUTE_TAG_SERIAL_NUMBER
 * - DukPLATFORM_ATTRIBUTE_TAG_MEMORY_PERSISTENT_SIZE
 * - DukPLATFORM_ATTRIBUTE_TAG_MEMORY_VOLATILE_SIZE
 * - DukPLATFORM_ATTRIBUTE_TAG_STATE
 * - DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX
 * - DukPLATFORM_ATTRIBUTE_TAG_CPU_CLOCK_Hz
 *
 * @implementation Depending of the Platform onto which is running the uKernel
 *  Target, some of the Platform Attributes may not be supported. See
 *  Platform specific documentation of the uKernel Target for details.
 *
 * @usage Most of the Platform Attributes are read only configuration data. See
 *  documentation of each Platform Attribute for indication if it can also be
 *  set.
 */
typedef TukTLV_TAG TukPLATFORM_ATTRIBUTE_TAG;


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-TYPES - UKERNEL - STATUS CODE                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for defining the Status Code returned by a C-Function
 *  or a uKernel Service.
 *
 * Definition of the uKernel C-Type for the Status Code returned by a
 *  C-Function or a uKernel Service. The Status Code allows to indicate the
 *  main level of (un)success of the execution of the requested action, along
 *  with some additional information (when pertinent) on the reason of the
 *  (un)success.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [15...09] RFU
 *  - [08...05] <Nature>: Indicate the main level of (un)success (Information,
 *   Warning, Error, Fatal Error). Each possible Nature value is defined as a
 *   flag. One and only one flag can be set in the Nature field.
 *   The number of Status Code Nature supported is DukSTATUS_NATURE_COUNT.
 *  - [04...00] <Reason>: Value giving more details on the reason why of the
 *   level of (un)success (execution context, parameters, ...). Note that the
 *   interpretation of this reason value depends of the Nature field (i.e.
 *   same Reason value may exist and have different meanings if the Nature
 *   field is different).
 *   The reason null value is invalid.
 *
 * The C-Type Status Code is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |      Bit number       |                  Description                     |
 * |15...09|08...05|04...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | RFU                                              |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |  xxxx |       | Nature field coding the level of (un)success.    |
 * |       |       |       |                                                  |
 * |       |  0001 |       | Information: action done (no error).             |
 * |       |       |       |                                                  |
 * |       |  0010 |       | Warning: action, may have been already or        |
 * |       |       |       |  partially done.                                 |
 * |       |       |       |                                                  |
 * |       |  0100 |       | Error: action not done.                          |
 * |       |       |       |                                                  |
 * |       |  1000 |       | Fatal Error: action not done, and continuing     |
 * |       |       |       |  execution is not be possible.                   |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Reason of (un)success.                           |
 * |-------|-------|-------|--------------------------------------------------|
 *
 *
 * @robustness In application of good coding practices and code maintenance,
 *  and to avoid possible side effects in ukApp code, all the uKernel Services
 *  return either a Status Code, or a literal value when the uKernel Service
 *  is always successful (e.g. retrieving public global information).
 *  IT SHALL NEVER be returned a mix of both in function of the level of
 *  success.
 *
 * @usage Due to different internal structures that may be chosen for the
 *  fields composing a Status Code in function of selected MCU Core for the
 *  uKernel Release, a Status Code value SHALL ALWAYS be built using the
 *  MukSTATUS_BUILD() C-Macro.
 *
 * @usage To guarantee the robustness of its processing, the ukApp code should
 *  always check the Status Code returned upon each invocation of a uKernel
 *  Service.
 *
 * @usage The output parameters resulting from the execution of a uKernel
 *  Service can be considered as meaningful ONLY if the Status Code returned
 *  is of Nature of either Info (see DukSTATUS_NATURE_INFO_FLAG) or
 *  Warning (see DukSTATUS_NATURE_WARNING_FLAG).
 *
 * @usage The following uKernel Helpers are defined to check the Nature of
 *  a returned Status Code:
 *   - ukStatusIsInfo()
 *   - ukStatusIsInfoOrWarning()
 *   - ukStatusIsError()
 *   - ukStatusIsFatal()
 *
 * @usage The uKernel Helper ukStatusErrorConvertToFatalError() can be used to
 *  change the Nature of a Status Code from Error to Fatal Error.
 */
typedef TukUINT16 TukSTATUS;


/* //////////////////////////////////////////////////////////////////////// */
/*                              C-TYPES - TIME                              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a 64-bit time duration expressed in ticks (Clock
 *  Cycle) unit.
 *
 * @usage The 64-bit size allows to manage a time duration up to 5000 years for
 *  a clock running at 100MHz.
 */
typedef TukUINT64 TukTIME64_tick;

/**
 * @brief uKernel C-Type for a 32-bit time duration expressed in ticks (Clock
 *  Cycle) unit.
 *
 * @usage The 32-bit size allows to manage a time duration up to 42 seconds for
 *  a clock running at 100MHz.
 */
typedef TukUINT32 TukTIME32_tick;

/**
 * @brief uKernel C-Type for a 64-bit time duration in microsecond (us).
 *
 * @usage The 64-bit size allows to manage a time duration up to 500K years.
 */
typedef TukUINT64 TukTIME64_us;

/**
 * @brief uKernel C-Type for a 32-bit time duration in microsecond (us).
 *
 * @usage The 32-bit size allows to manage a time duration up to 1,19 hour.
 */
typedef TukUINT32 TukTIME32_us;

/**
 * @brief uKernel C-Type for a 32-bit time duration in milliseconds (ms).
 *
 * @usage The 32-bit size allows to manage a time duration up to 49,7 days.
 */
typedef TukUINT32 TukTIME32_ms;

/**
 * @brief uKernel C-Type for a 32-bit frequency value in Hertz (Hz).
 *
 * @usage The 32-bit size allows to store a frequency up to 4GHz.
 */
typedef TukUINT32 TukFREQ32_hz;

/**
 * @brief uKernel C-Type for a 16-bit frequency value in MegaHertz (Hz).
 *
 * @usage The 16-bit size allows to store a frequency up to 65MHz.
 */
typedef TukUINT16 TukFREQ16_mhz;

/**
 * @brief uKernel C-Type for a baudrate (bit per second) in a transmission.
 *
 * @usage The 32-bit size allows to store a baudrate up to 4Gb/s.
 */
typedef TukUINT32 TukBAUDRATE;


/* //////////////////////////////////////////////////////////////////////// */
/*             C-TYPES - UKERNEL - RELEASE CUSTOMER CONFIGURATION           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Customer Configuration Identifier of a uKernel
 *  Target.
 *
 * Definition of the uKernel C-Type for a 64-bit Identifier for the Customer
 *  Configuration of a uKernel Target.
 * This Identifier allows to trace a uKernel configuration (see uKernel
 *  Features and Options) chosen by a Customer in regards of its needs for a
 *  Project.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [63...32] Customer: Value identifying the Customer.
 *  - [31...16] Project: Value identifying the Project reference for the
 *   Customer needing this configuration.
 *   NOTE: This value is linked to the given Customer; Interpretation of
 *    Project reference values are fully disconnected for different Customers.
 *  - [15...00] Revision: Revision of the Customer configuration.
 *
 * The C-Type Customer Configuration Identifier is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |         Bit number    |                   Description                    |
 * |63...32|31...16|15...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | Customer (32-bit)                                |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | Project (16-bit)                                 |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Revision (16-bit)                                |
 * |-------|-------|-------|--------------------------------------------------|
 *
 * @usage This Identifier is independent of the uKernel Release Version (see
 *  DukRELEASE_UKERNEL_VERSION) used for tracing state of the uKernel Core code
 *  (along with chosen configuration and options) used for the uKernel Release.
 */
typedef TukUINT64 TukCUSTOMER_CONFIG;


/* //////////////////////////////////////////////////////////////////////// */
/*                     C-TYPES - UKERNEL CORE DESCRIPTOR                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the structure of the uKernel Core Descriptor.
 *
 * Definition of the uKernel C-Type for the uKernel Core Descriptor.
 * This C-Type defines the structure that is used by the uKernel Bootloader to
 *  identify and retrieve the information required on the uKernel Release to
 *  boot the current uKernel Release or perform a uKernel Image Update.
 *
 * The uKernel Core Descriptor contains the following fields:
 *  - (TukMAGIC64)<UKernelCoreDescriptorMagicStart64>: 64-bit Magic Number to
 *   indicate the presence of a uKernel Core Code Descriptor structure. It
 *   shall be equal to DukUKERNEL_CORE_DESCRIPTOR_MAGIC64.
 *  - (TukVERSION)<UKernelCoreDescriptorVersion>: Version of the uKernel Core
 *   Descriptor used.
 *  - (TukUINT32)<PaddingVariability[]>: Random value to enforce the non
 *   predicatability and non traceability of the integrity or signature values
 *   computed on the uKernel Core Descriptor.
 *
 *  - (TukVERSION)<UKernelCoreReleaseUKernelVersion>: Version of this uKernel
 *   Release.
 *  - (TukCUSTOMER_CONFIG)<UKernelCoreReleaseCustomerConfiguration64>: Customer
 *   Configuration of this uKernel Release.
 *  - (TukCPU_CORE_ID)<UKernelCoreReleaseCPUCoreIdentifier64>: Identifier for
 *   the CPU Core for which this uKernel Release has been compiled for.
 *  - (TukMCU_ID_bv)<UKernelCoreReleaseMCUDeviceIdentifier128_bv>: Identifier
 *   for the MCU Device for which this uKernel Release has been compiled for.
 *  - (TukPLATFORM_ID_bv)<UKernelCoreReleasePlatformIdentifier128_bv>:
 *   Identifier for the Platform for which this uKernel Release has been
 *   compiled for.
 *
 *   - (TukVERSION)<UKernelCoreReleaseUKAppDescriptorVersion> Version of the
 *    ukApp Descriptor (see TukUKAPP_DESCRIPTOR) supported by this uKernel
 *    Release.
 *
 *  - (TukADDRESS32)<UKernelCoreCodeBlockAddressStart>: Start Address of the
 *   uKernel Core Code Block. It shall be equal to the start address of this
 *   uKernel Core Code Descriptor.
 *  - (TukLENGTH32)<UKernelCoreCodeBlockSize>: Length (in bytes) of the uKernel
 *   Core Code Block.
 *
 *  - (TukADDRESS32)<UKernelCoreEntryPointMCUExceptionHandlerReset>: Address of
 *   the C-Function to invoke to start the uKernel Core execution following an
 *   MCU Reset.
 *
 *  - (TukCOUNT8)<UKernelImageUpdateStorageAddressBlockCount>: Count of valid
 *   Address Blocks in the field <UKernelImageUpdateStorageAddressBlockList[]>.
 *   This count shall be in the range:
 *    [0 ... DukCONSTRAINT_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT_MAX]
 *  - (TukADDRESSBLOCK)<UKernelImageUpdateStorageAddressBlockList[]>: C-Array
 *   containing the list of Address Blocks to use for the uKernel Image Update
 *   Storage.
 *   Each entry in the list defines an Address Block (as a range of continuous
 *   addresses in MCU addressing space). Each Address Block shall not overlap
 *   with other entries in this list and shall have its Start Address greater
 *   than the previous entry.
 *   The number of entries is <UKernelImageUpdateStorageAddressBlockCount>.
 *
 *  - (TukADDRESS32)<GVukUKernelImageUpdateStorageOperationAddress>: Address
 *   of the C-Variable containing the information for managing a uKernel Image
 *   Storage operation.
 *
 *  - (TukUINT32)<Reserved>: Reserved fields for future usage. They shall be
 *   set to Null(0).
 *
 *  - (TukHASH_SHA256)<UKernelCoreCodeBodyBlockSHA256>: SHA256 which shall be
 *   equal to the SHA256 computed on the uKernel Core Code Body Block defined
 *   as the following Address Block:
 *   [ (<UKernelCoreCodeBlockAddressStart> +
 *      sizeof(TukUKERNEL_CORE_DESCRIPTOR)) ...
 *     (UKernelCoreCodeBlockAddressStart + <UKernelCoreCodeBlockSize> - 1) ].
 *  - (TukHASH_SHA256)<UKernelCoreDescriptorSHA256>: SHA256 value computed
 *   on whole uKernel Core Descriptor contents, from its start up to this
 *   field (not included).
 *
 * @usage The structured contents defined by this C-Type shall be at the very
 *  beginning of the uKernel Image Update Storage when updating the uKernel
 *  Core.
 */
typedef const struct {
    TukMAGIC64              UKernelCoreDescriptorMagicStart64;
    TukVERSION              UKernelCoreDescriptorVersion;
    TukUINT32               PaddingVariability[2];

    TukVERSION              UKernelCoreReleaseUKernelVersion;
    TukUINT64               UKernelCoreReleaseUKernelFeatures64;
    TukCUSTOMER_CONFIG      UKernelCoreReleaseCustomerConfiguration64;
    TukCPU_CORE_ID          UKernelCoreReleaseCPUCoreIdentifier64;
    TukMCU_ID_bv            UKernelCoreReleaseMCUDeviceIdentifier128_bv;
    TukPLATFORM_ID_bv       UKernelCoreReleasePlatformIdentifier128_bv;

    TukVERSION              UKernelCoreReleaseUKAppDescriptorVersion;

    TukADDRESS32            UKernelCoreCodeBlockAddressStart;
    TukLENGTH32             UKernelCoreCodeBlockSize;
    TukLENGTH32             UKernelCoreCodeBlockSizeEffective;
    TukADDRESS32            UKernelCoreDataVolatileBlockAddressStart;
    TukLENGTH32             UKernelCoreDataVolatileBlockSize;

    TukVERSION              UKernelCoreConfigurationDescriptorVersion;
    TukADDRESS32            UKernelCoreConfigurationBlockAddressStart;
    TukLENGTH32             UKernelCoreConfigurationBlockSize;

    TukADDRESS32            UKAppsBundleCodeBlockAddressStart;
    TukLENGTH32             UKAppsBundleCodeBlockSize;
    TukADDRESS32            UKAppsBundleDataVolatileBlockAddressStart;
    TukLENGTH32             UKAppsBundleDataVolatileBlockSize;
    TukADDRESS32            UKAppsBundleDataVolatileSharedBlockAddressStart;
    TukLENGTH32             UKAppsBundleDataVolatileSharedBlockSize;
    TukADDRESS32            UKAppsBundleDataPersistentBlockAddressStart;
    TukLENGTH32             UKAppsBundleDataPersistentBlockSize;

    TukADDRESS32            UKernelCoreEntryPointMCUExceptionHandlerReset;

    TukCOUNT8               UKernelImageUpdateStorageAddressBlockCount;
    TukADDRESSBLOCK         UKernelImageUpdateStorageAddressBlockList[
        DukCONSTRAINT_UKERNEL_IMAGE_UPDATE_STORAGE_ADDRESSBLOCK_COUNT_MAX];
    TukADDRESS32            GVukUKernelImageUpdateStorageOperationAddress;

    TukUINT32               Reserved[4];

    TukHASH_SHA256          UKernelCoreCodeBodyBlockSHA256  CAukVAR_ALIGNED(0x20);

    TukHASH_SHA256          UKernelCoreDescriptorSHA256     CAukVAR_ALIGNED(0x20);
} TukUKERNEL_CORE_DESCRIPTOR;


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-TYPES - UKERNEL SESSION - CONTEXT                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the uKernel Session Context.
 *
 * Definition of the uKernel C-Type for the uKernel Session Context.
 *
 * The uKernel Session Context allows to retrieve information on the context
 *  of execution of the current uKernel Session (event having triggered its
 *  state, current execution state, ...).
 *
 * The uKernel Session Context is composed of the following flags:
 *  - DukUKERNEL_SESSION_CONTEXT_MCU_RESET_WARM_FLAG: The uKernel Session has
 *   been started following a Warm MCU Reset.
 *
 * @usage The uKernel Session Context can be retrieved uKernel Core Attribute
 *  Tag DukUKCORE_ATTRIBUTE_TAG_UKERNEL_SESSION_CONTEXT and the C-Function
 *  ukPlatformGetAttribute().
 */
typedef TukUINT32 TukUKERNEL_SESSION_CONTEXT;


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - UKERNEL - ATTRIBUTES                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Tag of a uKernel Core Attribute.
 *
 * Definition of the uKernel C-Type for the Tag of a uKernel Core Attribute.
 * The Tag value allows to reference unambiguously a uKernel Core Attribute, in
 * order to get its value (see the C-Function ukUKCoreGetAttribute()).
 *
 * A uKernel Core Attribute  allows to access to current configuration data and
 *  state of the uKernel Core currently executed, such as:
 *  - uKernel identification (version, ...)
 *  - uKernel SysTick configuration
 *  - ukApps & ukProcs count
 *  - uKernel used Memory resources
 *  - ...
 *
 * The uKernel Core Attributes are always managed as a TLV (Tag/Length/Value)
 *  structure (see TukTLV_TAG for details).
 *
 * The following uKernel Core Attributes are defined (see associated
 *  documentation for the details of their TLV structure):
 * - DukUKCORE_ATTRIBUTE_TAG_RELEASE_VERSION
 * - DukUKCORE_ATTRIBUTE_TAG_UKERNEL_SESSION_CONTEXT
 * - DukUKCORE_ATTRIBUTE_TAG_CODE_BODY_BLOCK_SHA256
 * - DukUKCORE_ATTRIBUTE_TAG_UKAPPS_CODE_SIZE_TOTAL
 * - DukUKCORE_ATTRIBUTE_TAG_UKAPPS_DATA_VOLATILE_SIZE_TOTAL
 * - DukUKCORE_ATTRIBUTE_TAG_UKAPPS_DATA_PERSISTENT_SIZE_TOTAL
 * - DukUKCORE_ATTRIBUTE_TAG_UKERNEL_IMAGE_UPDATE_STORAGE_SIZE
 * - DukUKCORE_ATTRIBUTE_TAG_UKAPPS_COUNT
 * - DukUKCORE_ATTRIBUTE_TAG_UKPROCS_COUNT
 * - DukUKCORE_ATTRIBUTE_TAG_SYSTICK_PERIOD_us
 * - DukUKCORE_ATTRIBUTE_TAG_MCUREGISTER_ACCESSKEY
 * - DukUKCORE_ATTRIBUTE_TAG_UKAPP_DATA_PERSISTENT_BLOCK_ACCESSKEY
 * - DukUKCORE_ATTRIBUTE_TAG_UKERNEL_IMAGE_UPDATE_ACCESSKEY
 *
 * @usage All the uKernel Core Attributes are read only.
 */
typedef TukTLV_TAG TukUKCORE_ATTRIBUTE_TAG;


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-TYPES - UKAPP IDENTIFIERS                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Application Unique Identifier (AUID)
 *  associated to each ukApp.
 *
 * Definition of the uKernel C-Type for the ukApp Unique Identifier (AUID),
 *  that is a 64-bit Identifier identifying unambiguously a given ukApp, and
 *  whose uniqueness is enforced in a given ukApps Bundle.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 * - [63...48] Developer: This Developer value allows to identify the ukApp
 *  Developer (i.e. the entity in charge of the development of the ukApp). The
 *  value to be used for each ukApp Developer has to be attributed by the
 *  entity in charge of packaging the ukApps Bundle. It is recommended to use a
 *  value containing a shortname of the Developer entity composed of 2 ASCII
 *  characters. This value is not linked to any specific constraints (i.e.
 *  unicity in the ukApps Bundle, forbidden reserved value).
 * - [47...16] Reference: This Reference value allows to identify the ukApp
 *  among the other ones developed by the same ukApp Developer (see
 *  <Developer> field). The value to be used for each Reference has to be
 *  attributed by the ukApp Developer. It is recommended to use a value
 *  containing a shortname of the ukApp composed of 4 ASCII characters.
 *  This value is not linked to any specific constraints (i.e. unicity in the
 *  ukApps Bundle, forbidden reserved value).
 *  NOTE: This value is linked to the given Developer; Interpretation of
 *    Reference values are fully disconnected for different Developers.
 * - [15...0] ASID: Application Short Identifier (ASID) (see TukUKAPP_ASID).
 *  The ASID value shall be unique among the ukApp Descriptors part of a ukApp
 *  Bundle. A set of special reserved ASID values, with specific meanings, is
 *  defined (see DukUKAPP_ASID_RESERVED_MASK) and cannot be used as part of the
 *  ASID field in an AUID.
 *
 * The C-Type AUID is structured as this:
 * |---------------|----------------------------------------------------------|
 * |      Bit number       |                  Description                     |
 * |63...48|47...16|15...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | Developer (16-bit)                               |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | Reference (32-bit).                              |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | ASID (16-bit).                                   |
 * |-------|-------|-------|--------------------------------------------------|
 *
 * @implementation During uKernel Initialization, the uKernel performs for each
 *  ukApp Descriptor validation the following checks on the ASID field value
 *  of the AUID:
 *   - The ASID value is not a special reserved ASID value (see
 *    DukUKAPP_ASID_RESERVED_MASK).
 *   - The ASID value is unique among the ASID field in the AUIDs of the ukApp
 *    Descriptors already found valid in the ukApps Bundle.
 *
 * @usage The AUID of a ukApp allows a ukProc to:
 *  - Initiate interactions with other ukProc by unambiguously referencing the
 *   ukApp with which we want to interact with, and then
 *   retrieving the PUID of the ukProc instantiated from it (see
 *   ukUKProcGetPUIDFromAUID()) to perform interactions.
 *  - Retrieve AIDX of a ukApp in order to retrieve information on it (see
 *   ukUKAppGetAIDXFromAUID()).
 *
 * @usage The AUID has to be chosen by the ukApp Developer when starting the
 *  development of a ukApp. Its ASID field shall be unique among all the
 *  other possible ukApps that may be part of the ukApps Bundle (including
 *  upon future uKernel Image updates).
 *  Once chosen, the AUID shall not be modified for a given ukApp. Notably,
 *  the change of the Version of a ukApp SHALL NOT imply a modification of its
 *  AUID value.
 */
typedef TukUINT64 TukUKAPP_AUID;


/**
 * @brief uKernel C-Type for a 16-bit Short Label (SLABEL) local to a ukApp.
 *
 * Definition of the uKernel C-Type for a 16-bit Short Label local to a ukApp.
 *
 * This ukApp Short Label is used in a ukApp Descriptor to reference
 *  unambiguously a given element (or a sub-set of elements) among a set of
 *  elements of the same nature belonging to the ukApp. As thus, a each value
 *  for a set of elements of the same nature shall be unique in an ukApp
 *  Descriptor (same value can however be reused in another ukApp Descriptor).
 *
 * @usage This Short Label is used for defining:
 *  - Address Block Label (see TukADDRESSBLOCK_LABEL).
 *  - DMA stream Label (see TukDMAS_LABEL).
 */
typedef TukSLABEL16 TukUKAPP_LABEL_LOCAL;


/**
 * @brief C-Type defining a ukApp Short Identifier (ASID) value used to a
 *  reference a given ukApp.
 *
 * Definition of the uKernel C-Type for a ukApp Short Identifier (ASID).
 * The ASID value is used to reference unambiguously a ukApp among the other
 *  ones present in the ukApps Bundle (and thus shall be unique among each
 *  ukApp present).
 *
 * The following special ASID values are reserved by the uKernel:
 *  - DukUKAPP_ASID_UKERNEL
 *  - DukUKAPP_ASID_NONE
 *  - DukUKAPP_ASID_ANY
 *  - DukUKAPP_ASID_INVALID
 *
 * @implementation During uKernel Initialization, the uKernel performs the
 *  following checks on these fields of each ukApp Descriptor validation:
 *   - <AUID>:
 *     -- The ASID value shall not already be present in the AUID of
 *       another ukApp Descriptor already found valid in the ukApps Bundle.
 *     -- The ASID value shall no be part of ASID reserved values ranges (see
 *       DukUKAPP_ASID_RESERVED_MASK).
 *   - <ParentASID>: The ASID value references the ukApp Parent that can
 *    administrate this ukApp. Among the special reserved ASID values, only
 *    DukUKAPP_ASID_NONE can be used to indicate that there is no ukApp Parent.
 *   - <IPCSendToASIDAuthorizedList>: Each ASID in this list references another
 *    ukApp to which this ukApp can send IPC messages. Among the special
 *    reserved ASID values, only the following ones can be used:
 *     -- DukUKAPP_ASID_NONE: As first element, to indicate that no IPC message
 *      can be sent.
 *     -- DukUKAPP_ASID_ANY: As first element, to indicate that IPC message
 *      can be sent to any ukApp part of the ukApps Bundle.
 *
 * @usage The ASID value of a ukApp is not defined directly: it is defined
 *  through the <ASID> field of the AUID value (see TukUKAPP_AUID) defined for
 *  the ukApp (see <AUID> field in ukApp Descriptor).
 *
 * @usage The ASID value is used in the following fields of a ukApp Descriptor
 *  to reference other ukApps part of the ukApps Bundle:
 *  - <ParentASID>
 *  - <IPCSendToASIDAuthorizedList>
 *
 * @usage The ASID value SHALL NOT be used as a global identifier for
 *  referencing a ukApp when managing ukApps Bundles or uKernel Images (the
 *  AUID value of the ukApp shall be used instead in order to guarantee unicity
 *  of the naming).
 *
 * @usage An ASID value referencing a ukApp part of the ukApps Bundle shall
 *  be in the range [0 ... (DukUKAPP_ASID_RESERVED_MASK - 1)].
 *  Additional special reserved values, out of this range, may also be used or
 *  returned (see DukUKAPP_ASID_xxx C-Constants).
 */
typedef TukSLABEL16 TukUKAPP_ASID;


/**
 * @brief uKernel C-Type defining the ukApp Index (AIDX) associated to a ukApp.
 *
 * Definition of the uKernel C-Type for the ukApp Index (AIDX).
 * The AIDX value is a sequential index (starting from 0) used to reference
 * Unambiguously each valid ukApp part of the ukApps Bundle. Its value is fixed
 * for each ukApp during a whole uKernel Session (it is independent of the
 * current set of ukProcs present).
 *
 * The following AIDX special reserved values are defined:
 *  - DukUKAPP_AIDX_MYSELF
 *  - DukUKAPP_AIDX_INVALID
 *
 * @warning An AIDX value is attributed to each valid ukApp part of the
 *  ukApps Bundle during uKernel Initialization. There is however NO GUARANTEE
 *  that same AIDX value will be attributed to a same ukApp among different
 *  uKernel Sessions (and thus a ukProc shall not store an AIDX value, but
 *  retrieve it upon each new uKernel Session).
 *
 * @implementation If a ukApp Descriptor has been declared as invalid during
 *  uKernel Initialization, no AIDX value is attributed to it (and thus the
 *  associated ukApp cannot be instantiated nor its information retrieved).
 *
 * @usage The AIDX value of a ukApp can be retrieved only from its AUID value
 *  using the uKernel Privileged Service ukUKAppGetAIDXFromAUID().
 *
 * @usage The AIDX value is used as index to reference each valid ukApp part
 *  of the ukApps Bundle. It allows a ukProc to perform a walk through on valid
 *  ukApps by incrementing the index from 0 till an error is returned
 *  indicating that no ukApp is found with given index.
 *
 * @usage An AIDX value referencing a ukApp part of the ukApps Bundle shall
 *  be in the range [0 ... (DukCONFIG_OPTION_UKAPP_COUNT_MAX - 1)].
 *  Additional special reserved values, out of this range, may also be used or
 *  returned (see DukUKAPP_AIDX_xxx).
 */
typedef TukIDX8   TukUKAPP_AIDX;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - UKAPP PROFILE                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the Profile of a ukApp.
 *
 * Definition of the uKernel C-Type for the Profile of a ukApp.
 * The ukApp Profile value is a set of flags describing the main high level
 *  characteristics and credentials attributed to a ukApp, such as:
 *  - Lifecycle: automatic creation of a ukProc during initialization,
 *   reincarnation policy, ...
 *  - uKernel System Roles: Platform administration, ukApp update management,
 *   ...
 *  - uKernel System Credentials: auditing
 *
 * The following flags are defined for a ukApp Profile:
 * - DukUKAPP_PROFILE_UKPROC_INSTANTIATE_ON_UKERNEL_INIT_FLAG
 * - DukUKAPP_PROFILE_UKPROC_REINCARNATE_ALWAYS_FLAG
 * - DukUKAPP_PROFILE_UKPROC_REINCARNATE_AFTER_ABORT_FLAG
 * - DukUKAPP_PROFILE_RESET_ON_ABORT_FLAG
 * - DukUKAPP_PROFILE_PLATFORM_CONFIG_GET_FLAG
 * - DukUKAPP_PROFILE_PLATFORM_CONFIG_SET_FLAG
 * - DukUKAPP_PROFILE_SYSTEM_AUDIT_FLAG
 * - DukUKAPP_PROFILE_FPU_FLAG
 * - DukUKAPP_PROFILE_UKERNEL_IMAGE_UPDATE_MANAGER_FLAG
 *
 * @usage The ukApp Profile value is part of the ukApp Descriptor (see
 *  <Profile> field).
 */
typedef TukUINT32 TukUKAPP_PROFILE;


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - UKAPP ATTRIBUTES                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Tag of a ukApp Attribute.
 *
 * Definition of the uKernel C-Type for the Tag of a ukApp Attribute.
 * The Tag value allows to reference unambiguously a ukApp Attribute, in order
 * to get its value (see the C-Function ukUKAppGetAttribute()).
 *
 * A ukApp Attribute allows to access to some configuration elements defined in
 *  its ukApp Descriptor, such as:
 *  - AUID
 *  - Version
 *  - String Name
 *  - Memory sizes
 *  - ...
 *
 * The ukApp Attributes are always managed as a TLV (Tag/Length/Value)
 *  structure (see TukTLV_TAG for details).
 *
 * The following ukApp Attributes are defined (see associated documentation for
 *  the details of their TLV structure):
 * - DukUKAPP_ATTRIBUTE_TAG_NAME_NTSTRING
 * - DukUKAPP_ATTRIBUTE_TAG_AUID
 * - DukUKAPP_ATTRIBUTE_TAG_VERSION
 * - DukUKAPP_ATTRIBUTE_TAG_PROFILE
 * - DukUKAPP_ATTRIBUTE_TAG_PARENT_ASID
 * - DukUKAPP_ATTRIBUTE_TAG_CODE_SIZE
 * - DukUKAPP_ATTRIBUTE_TAG_DATA_VOLATILE_SIZE
 * - DukUKAPP_ATTRIBUTE_TAG_DATA_PERSISTENT_SIZE
 * - DukUKAPP_ATTRIBUTE_TAG_CODE_BODY_BLOCK_SHA256
 * - DukUKAPP_ATTRIBUTE_TAG_DESCRIPTOR_SHA256
 *
 * @usage All of the ukApp Attributes are read only.
 */
typedef TukTLV_TAG TukUKAPP_ATTRIBUTE_TAG;


/* //////////////////////////////////////////////////////////////////////// */
/*               C-TYPES - UKAPP DATA VOLATILE SHARED BLOCK                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the Result field structure in the ukApp Data
 *  Volatile Shared uKernel Services Block
 *
 * Definition of the uKernel C-Type for the Result field in the ukApp Data
 *  Volatile Shared uKernel Services Block that is used for the returned value
 *  following execution of a uKernel Privileged Services.
 *
 * The structure of the ukApp Data Volatile Shared uKernel Services Block
 *  Result field is defined as the union of the following fields:
 *  - (TukSTATUS)<StatusCode>: Field to be used for a Status Code
 *   returned, indicating the level of success of the invocation (see
 *   TukSTATUS for more details).
 *  - (TukUINT32)<Value32>: Field to be used for a returned computed
 *   32-bit value.
 *  - (TukUINT64)<Value64>: Field to be used for a returned computed
 *   64-bit value.
 *
 * @usage This C-Type aims at being used only as an helper for defining the
 *  TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC C-Type.
 */
typedef union  {
            TukSTATUS    StatusCode;
            TukUINT32    Value32;
            TukUINT64    Value64;
              } TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT;


/**
 * @brief uKernel C-Type defining the C-Array containing the data accessed
 *  during a uKernel Privileged Service invocation.
 *
 * Definition of the uKernel C-Type for the C-Array of bytes containing the
 *  data accessed during a uKernel Privileged Service invocation.
 *
 * @implementation The size of this C-Array is defined for covering the whole
 *  area of the ukApp Data Volatile Shared uKernel Services Block: its size in
 *  bytes is equal to:
 *   (DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE -
 *    sizeof(TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT)).
 *
 * @implementation The size of this C-Array is always guaranteed to be a
 *  multiple of 8 (i.e. 64-bit words).
 *
 * @usage This C-Type aims at being used only as an helper for the definition
 *  of the C-Type TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC.
 */
typedef TukUINT8    TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA[
                DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE -
                sizeof(TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT)];


/**
 * @brief uKernel C-Type defining the structure of the ukApp Data Volatile
 *  Shared uKernel Services Block (ukAppDVSUKSVC Block).
 *
 * Definition of the uKernel C-Type for the ukApp Data Volatile Shared uKernel
 *  Services Block (ukAppDVSUKSVC Block).
 * This C-Type defines the structure of the Address Block containing the sole
 *  data of the ukProc accessed and modified during the invocation of a uKernel
 *  Privileged Service.
 *
 * The structure of the ukApp Data Volatile Shared uKernel Services Block is as
 *  follows:
 *  - (TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT)<ServiceResult>:
 *   C-Union containing the different types of returned value following
 *   execution of uKernel Privileged Service (see
 *   TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT for more details).
 *  - <ServiceParameter>: C-Union containing the input and output parameters
 *   associated to the uKernel Privileged Service invocation. The way the
 *   parameters are structured is specific to each of the uKernel Privileged
 *   Service (see their documentation for details). Notably the whole field may
 *   be unused (and in that case unused contents shall be considered as
 *   unpredictable data which may depend on uKernel Target).
 *   This C-Union contains the following fields:
 *   + (TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA)<Input>: Field defined
 *    as a C-Array to be used for input parameters (computation input(s)).
 *   + (TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA)<Output>: Field defined
 *    as a C-Array to be used for output parameters (computed result(s)).
 *
 * @implementation This C-Type is defined for covering the whole area of the
 *  ukApp Data Volatile Shared uKernel Services Block (thus the size in bytes
 *  of this C-Type is equal to
 *  DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE).
 *
 * @implementation Defining C-Union for this structure aims at being helpers
 *  for clarifying the nature of the data manipulated upon the invocation of a
 *  uKernel Privileged Service. Notably, even if the <Input> and <Output>
 *  fields share the same memory area, it brings more clarity to contents to
 *  be addressed in case the same contents be present as input and output.
 *
 * @usage This C-Type aims at being used only for the definition of the
 *  C-Variable GVukappBlockDataSharedUKSVC. This C-Variable allows then easy
 *  access for the ukApp code to the different fields of the ukApp Data
 *  Volatile Shared uKernel Services Block.
 */
typedef struct {
    TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_RESULT ServiceResult;
    union {
        TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA   Input;
        TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA   Output;
        } ServiceParameter;
    } TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC;


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - NSCALL EXCHANGE AREA                     */
/* //////////////////////////////////////////////////////////////////////// */

#if !defined(UKCORE) || defined(UKNSC_INMODULE)
/**
 * @brief uKernel C-Type defining the structure of the NSCall Exchange Area
 *  used to transmit data from the NSPE to the Secure World and back.
 *
 * Definition of the uKernel C-Type for the NSCall Exchange Area. This area is
 *  used to pass data from the Non-Secure world to the Secure world.
 *
 * The structure of the NSCall Exchange Area is as follows:
 *  - (TukUINT32)<ServiceID>: Containing the identifier of the targeted
 *   service.
 *  - (TukUINT32)<ServiceResult>: Containing the result of the NSCall to
 *   the secure side.
 *  - <ServiceParameter>: C-Union containing the input and output parameters
 *   associated to the uKernel NSCall invocation. The way the parameters are
 *   structured is specific to each of the uKernel NSCall (see their
 *   documentation for details). Notably the whole field may be unused (and
 *   in that case unused contents shall be considered as unpredictable data
 *   which may depend on uKernel Target).
 *   This C-Union contains the following fields:
 *   + (TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA)<Input>: Field defined
 *    as a C-Array to be used for input parameters (computation input(s)).
 *   + (TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA)<Output>: Field defined
 *    as a C-Array to be used for output parameters (computed result(s)).
 *
 * @usage This C-Type aims at being used only for the definition of the
 *  C-Variable GVukNSCallSharedBlockData.
 */
typedef struct {
    TukUINT32 ServiceID;
    TukUINT32 ServiceResult;
    TukUINT8  Data[];
} TukNSCALL_EXCHANGE_AREA;
#endif /* !defined(UKCORE) || defined(UKNSC_INMODULE) */


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - UKPROC - IDENTIFIERS                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the ukProc Unique Identifier (PUID)
 *  associated to a ukProc.
 *
 * Definition of the uKernel C-Type for the ukProc Unique Identifier (PUID)
 *  associated to a ukProc.
 *
 * The PUID is an identifier value allowing to reference unambiguously an
 *  instantiated ukProc during a uKernel Session.
 * A new PUID value is generated upon each ukProc Creation (i.e. creation of a
 *  new instance from its ukApp), and is guaranteed to be unique for each
 *  ukProc Instance created from any of the ukApps part of the ukApps Bundle
 *  during the uKernel Session.
 * Also, the generated PUID value is guaranteed to be different upon:
 *  - ukProc Creation from same ukApp (previous ukProc Instance having been
 *   terminated, as only one ukProc Instance is allowed by ukApp).
 *  - ukProc Reincarnation by the uKernel.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...08] Counter: Field containing a 24-bit counter, whose value depends
 *   of the PIDX field nature:
 *    + PIDX referencing an instantiated ukProc: The value of this counter is
 *     guaranteed to be unique per uKernel Session for a given PIDX value.
 *     The counter value is updated using random value to prevent its
 *     predictability.
 *    + PIDX special reserved value: The counter value is set to
 *     DukUKPROC_PUID_COUNTER_FIELD_SPECIAL.
 *  - [07...00] PIDX: Field of C-Type TukUKPROC_PIDX containing either:
 *   + A value referencing an instantiated ukProc: The value is guaranteed to
 *    be in the range [0 ... 31] (and thus is strictly lower than the
 *    C-Constant DukUKPROC_PIDX_SPECIAL_BASE).
 *   + A special reserved value: The value is then greater than the C-Constant
 *     DukUKPROC_PIDX_SPECIAL_BASE (see DukUKPROC_PIDX_SPECIAL_xxx C-Constants
 *     definition for the special reserved values supported).
 *
 * The C-Type PUID is structured as this:
 * |-------------------|------------------------------------------------------|
 * |     Bit number    |                    Description                       |
 * |31...08|  07...00  |                                                      |
 * |:-----:|:---------:|------------------------------------------------------|
 * | xxxxx |           | Counter randomized value (24-bit)                    |
 * |       |           |                                                      |
 * | 1...1 |           |  - Counter value used when PIDX field is a special   |
 * |       |           |     reserved value (see C-Constant                   |
 * |       |           |     DukUKPROC_PUID_COUNTER_FIELD_SPECIAL).           |
 * |-------|-----------|------------------------------------------------------|
 * |       |  xxxxxxxx | PIDX value (8-bit)                                   |
 * |       |           |                                                      |
 * |       |  000xxxxx |  - PIDX value referencing an instantiated ukProc.    |
 * |       |           |                                                      |
 * |       |  1111xxxx |  - PIDX special reserved value (see C-Constant       |
 * |       |           |     DukUKPROC_PIDX_SPECIAL_BASE).                    |
 * |-------|-----------|------------------------------------------------------|
 *
 * The following PUID special reserved values are defined:
 *  - DukUKPROC_PUID_INVALID
 *  - DukUKPROC_PUID_ANY
 *  - DukUKPROC_PUID_NONE
 *  - DukUKPROC_PUID_UKERNEL
 *  - DukUKPROC_PUID_MYSELF
 *  - DukUKPROC_PUID_OWNER
 *
 * @robustness If the uKernel cannot guarantee anymore the unicity of a PUID
 *  value when creating a new ukProc (i.e. the Counter field has exhausted
 *  available unique values set), then it triggers a uKernel FATAL Error.
 *
 * @implementation The uKernel enforces the unicity of each PUID value
 *  referencing an instantiated ukProc per uKernel Session.
 */
typedef TukUINT32 TukUKPROC_PUID;


/**
 * @brief uKernel C-Type defining the ukProc Index (PIDX).
 *
 * Definition of the uKernel C-Type for the ukProc Index (PIDX).
 * The PIDX is an index allowing to reference a ukProc instantiated among all
 *  the ukProcs currently instantiated by the uKernel at a given time.
 *
 * @warning A PIDX value DOES NOT identify unambiguously a given ukProc
 *  Instance during a uKernel Session. During a same uKernel Session, at
 *  various times, a PIDX value can reference different ukProcs Instances from
 *  same or different ukApps (A same PIDX value can be reassigned by the
 *  uKernel upon the creation of a new ukProc Instance from the same or from a
 *  different ukApp of the ukApps Bundle). Only the PUID value attached to a
 *  ukProc Instance is guaranteed to be unique during a uKernel Session: that's
 *  the reason why the PUID of a ukProc is always used by uKernel Services to
 *  reference unambiguously a ukProc (it allows notably to the detect a ukProc
 *  Instance having been terminated).
 *
 * @implementation In regards of uKernel implementation constraints, no more
 *  than 32 ukProcs can be present simultaneously (see C-Constant
 *  DukCONSTRAINT_UKPROC_COUNT_MAX), and thus a PIDX value
 *  is always in the range [0 ... 31].
 *
 * @usage The PIDX value of a ukProc can be retrieved only from the PUID value
 *  associated to the ukProc Instance. The Helper ukUKProcOriginExtractInfo()
 *  should be used to retrieve the PIDX field from a PUID value.
 *
 * @usage The PIDX value is used as bit number in bitmask to reference a ukProc
 *  (notably for IPC notification).
 *
 * @usage A PIDX value referencing a ukProc shall be in the range
 *   [0 ... DukUKPROC_PIDX_INSTANTIATED_MAX].
 *  Additional special reserved values, out of this range and greater than
 *  DukUKPROC_PIDX_SPECIAL_BASE, may also be used in the PIDX field of a PUID
 *  value for specific usages.
 */
typedef TukIDX8   TukUKPROC_PIDX;



/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - UKPROC - ORIGIN                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the ukProc Origin Event informing on the
 *  event having triggered the ukProc Creation.
 *
 * Definition of the uKernel C-Type for the ukProc Origin Event value informing
 *  on the event having triggered the ukProc Creation (i.e. the creation of its
 *  current ukProc Instance).
 *
 * The ukProc Origin Event value is a set of flags giving information on:
 *  - The event having triggered the ukProc Creation (e.g. automatic creation
 *   upon uKernel Initialization, reincarnation, ...).
 *  - Upon a ukProc Reincarnation, the ukProc Termination execution context of
 *   the previous ukProc Instance of the same ukApp.
 *
 * The following ukProc Origin Event Flags are supported:
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKERNEL_INIT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_CREATION_BY_UKPROC_PARENT_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_BY_UKERNEL_FLAG
 *  - DukUKPROC_ORIGIN_EVENT_REINCARNATION_AFTER_ABORT_FLAG
 * Only one of these flags can be set in the ukProc Origin Event value.
 *
 * @usage The ukProc Origin Event value is a field of the ukProc Origin value
 *  (see TukUKPROC_ORIGIN for details).
 */
typedef TukUINT8 TukUKPROC_ORIGIN_EVENT;

/**
 * @brief uKernel C-Type defining the ukProc Origin Info value providing
 *  additional information on the ukProc Creation.
 *
 * Definition of the uKernel C-Type for the ukProc Origin Info value.
 * The ukProc Origin Info value contains additional information (e.g.
 *  event having triggered a ukProc reincarnation, ...) in the specific context
 *  of the event having triggered the ukProc Creation (i.e. the creation of its
 *  current ukProc Instance).
 *
 * @usage The interpretation of the value contained in this C-Type is dependent
 *  of the Origin Event value: see description of each defined ukProc Origin
 *  Event C-Constant DukUKPROC_ORIGIN_EVENT_xxx for more details on the
 *  contents and the way to interpret its value.
 *
 * @usage The ukProc Origin Info value is a field of the ukProc Origin value
 *  (see DukUKPROC_ORIGIN_EVENT_xxx for details).
 */
typedef TukUINT16 TukUKPROC_ORIGIN_INFO;

/**
 * @brief uKernel C-Type defining the ukProc Origin Context value providing
 *  information on the Execution Context upon ukProc Creation.
 *
 * Definition of the uKernel C-Type for the ukProc Origin Context value.
 * The ukProc Origin Context value contains information (e.g. Debugger
 *  connected) on the Execution Context upon ukProc Creation (i.e. at the
 *  moment when the ukProc Instance has been created).
 *
 * The following ukProc Origin Context flags are supported:
 *  - DukUKPROC_ORIGIN_CONTEXT_DEBUGGER_ALLOWED_FLAG
 *  - DukUKPROC_ORIGIN_CONTEXT_UKERNEL_IMAGE_UPDATED_FLAG
 *  - DukUKPROC_ORIGIN_CONTEXT_INSTANCE_FIRST_IN_UKERNEL_SESSION_FLAG
 *
 * @usage The ukProc Origin Context value is a field of the ukProc Origin value
 *  (see TukUKPROC_ORIGIN for details).
 */
typedef TukUINT8 TukUKPROC_ORIGIN_CONTEXT;

/**
 * @brief uKernel C-Type defining the ukProc Origin value informing on the
 *  origin of a ukProc Creation.
 *
 * Definition of the uKernel C-Type for the ukProc Origin value.
 * The ukProc Origin value contains the information relative to the event
 *  having triggered the creation of the ukProc (e.g. the ukProc created during
 *  uKernel Initialization, or by the ukProc instantiated from its ukApp
 *  Parent, ...), and its current context of execution (e.g. Debugger connected, ...).
 *
 * The ukProc Origin value is transmitted to the ukProc upon the starting of
 *  its execution through the parameter <proc_origin__i> of its ukApp Entry
 *  Point ukappMain().
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [24...31] <Event>: This 8-bit field contains the ukProc Origin
 *   Event value that provides information on the trigger(s) having led to the
 *   instantiation of the ukProc (see TukUKPROC_ORIGIN_EVENT).
 *   This field can be extracted using ukUKProcOriginExtractEvent().
 *  - [23...08] <Info>: This 16-bit field contains the ukProc Origin
 *   Info value, whose interpretation shall be done in function of the
 *   Origin Event value field (see DukUKPROC_ORIGIN_EVENT_xxx for more details).
 *   This field can be extracted using ukUKProcOriginExtractInfo().
 *  - [00...07] <Context>: This 8-bit field contains flags providing
 *   information on the Execution Context upon ukProc Creation.
 *
 * The C-Type ukProc Origin is structured as this:
 * |-----------------------|--------------------------------------------------
 * |      Bit number       |                  Description                     |
 * |31...24|23...08|07...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | <Event> (8-bit)                                  |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | <Info> (16-bit)                                  |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | <Context> (8-bit)                                |
 * |-------|-------|-------|--------------------------------------------------|
 *
 * @usage The purpose of providing the ukProc Origin Event value is to allow
 *  the ukApp code to react accordingly in function of the nature of the
 *  event having triggered its instantiation as ukProc. Notably, it allows to
 *  implement some specific behavior that may be required by used Security
 *  Policy in ukApp implementation when error-related events are reported (e.g.
 *  following a ukProc Abort of its previous ukProc Instance): restriction of
 *  some services provided to other ukApp, online reporting of error,
 *  additional internal security checks, ...
 */
typedef TukUINT32 TukUKPROC_ORIGIN;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - UKPROC TERMINATION                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the ukProc Termination Reason providing
 *  details on the event having triggered the ukProc Termination.
 *
 * Definition of the uKernel C-Type for the ukProc Termination Reason providing
 *  details on the event (e.g. ukProc End, ukProc illegal access, ...) having
 *  triggered the ukProc Termination.
 *
 * The following ukProc Termination Reason values are supported:
 *  - DukUKPROC_TERMINATION_REASON_END
 *  - DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR
 *  - DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS
 *  - DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT
 *  - DukUKPROC_TERMINATION_REASON_ABORT_INVALID_STATE
 *  - DukUKPROC_TERMINATION_REASON_ABORT_WATCHDOG
 *  - DukUKPROC_TERMINATION_REASON_ABORT_UKERNEL_SESSION_END
 *
 * @usage The ukProc Termination Reason value can be retrieved in:
 *  - The parameter <ukproc_termination_reason__i> of ukApp Entry Point
 *   ukappCleanup().
 *  - The field <TerminationReason> of the ukProc Termination Context (see
 *   TukUKPROC_TERMINATION_CONTEXT).
 */
typedef TukIDX8 TukUKPROC_TERMINATION_REASON;


/**
 * @brief uKernel C-Type defining the ukProc Termination Info value providing
 *  additional information on the termination of a ukProc.
 *
 * Definition of the uKernel C-Type for the ukProc Termination Info value.
 * The ukProc Termination Info value contains additional information (e.g.
 *  address in ukProc code having triggered a ukProc Fatal Error, ...) in the
 *  specific context of the Reason having triggered the ukProc Termination
 *  (see TukUKPROC_TERMINATION_REASON).
 *
 * @usage The interpretation of the value contained in this C-Type is dependent
 *  of the ukProc Termination Reason value: see description of each defined
 *  ukProc Termination Reason C-Constant DukUKPROC_TERMINATION_REASON_xxx
 *  for more details on the contents and the way to interpret this value.
 *
 * @usage The ukProc Termination Info value can be retrieved in:
 *  - The parameter <ukproc_termination_info__i> of ukApp Entry Point
 *   ukappCleanup().
 *  - The field <TerminationInfo> of the ukProc Termination Context (see
 *   TukUKPROC_TERMINATION_CONTEXT).
 */
typedef TukUINT32 TukUKPROC_TERMINATION_INFO;


/**
 * @brief uKernel C-Type for the ukProc Termination Context of a ukProc
 *  Instance.
 *
 * Definition of the uKernel C-Type for the ukProc Termination Context of the
 *  a ukProc Instance from a given ukApp.
 *
 * The ukProc Termination Context consists in the following elements:
 *  - (TukUKPROC_TERMINATION_REASON)<TerminationReason>: ukProc Termination
 *   Reason providing details on the event having triggered the ukProc
 *   Termination of the ukProc Instance.
 *   If uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   supported, this field contains the same value as the one set in parameter
 *   <ukproc_termination_reason__i> upon last invocation of ukApp Entry Point
 *   ukappCleanup().
 *  - (TukUKPROC_TERMINATION_INFO)<TerminationInfo>: ukProc Termination Info
 *   value providing additional information on the termination of the ukProc
 *   Instance.
 *   If uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   supported, this field contains the same value as the one set in parameter
 *   <ukproc_termination_info__i> upon last invocation of ukApp Entry Point
 *   ukappCleanup().
 *  - (TukBOOL)<IsUKProcCleanupInError>: Boolean indicating if the execution of
 *   the ukApp Entry Point ukappCleanup() invoked at the beginning of the
 *   ukProc Termination process of the ukProc Instance has been successful
 *   (and thus has been properly finalized) or has reported or triggered an
 *   error.
 *   If uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   not supported, this field is always set to DukBOOL_FALSE.
 *  - (TukTIME64_us)<TerminationUptime_us>: uKernel Uptime in microseconds(us)
 *   when the ukProc Termination of the ukProc Instance has been triggered.
 *
 *  @usage If the field <TerminationReason> is set to
 *   DukUKPROC_TERMINATION_REASON_INVALID, then the other fields of this C-Type
 *   are not significant.
 *
 *  @usage The ukProc Termination Context of the last ukProc Instance from a
 *   given ukApp can be retrieved using the ukApp Attribute Tag
 *   DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST.
 */
typedef struct {
        TukUKPROC_TERMINATION_REASON    TerminationReason;
        TukUKPROC_TERMINATION_INFO      TerminationInfo;
        TukTIME64_us                    TerminationUptime_us;
        TukBOOL                         IsUKProcCleanupInError;
    } TukUKPROC_TERMINATION_CONTEXT;


/* //////////////////////////////////////////////////////////////////////// */
/*                           C-TYPES - UKPROC ATTRIBUTES                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Tag of a ukProc Attribute.
 *
 * Definition of the uKernel C-Type for the Tag of a ukProc Attribute.
 * The Tag value allows to reference unambiguously a ukProc Attribute, in order
 * to get its value (see the C-Function ukUKProcGetAttribute()).
 *
 * A ukProc Attribute allows to access to current configuration and state of a
 *  ukProc, such as:
 *  - AUID of its ukApp
 *  - Stack and Heap information
 *  - Scheduling Priority, Scheduling Time Quantum, Scheduling ukProc State
 *  - Statistic information
 *  - ...
 *
 * The ukProc Attributes are always managed as a TLV (Tag/Length/Value)
 *  structure (see TukTLV_TAG for details).
 *
 * The following ukProc Attributes are defined (see associated documentation
 *  for the details of their TLV structure):
 * - DukUKPROC_ATTRIBUTE_TAG_AUID
 * - DukUKPROC_ATTRIBUTE_TAG_STACK_FREE_SIZE
 * - DukUKPROC_ATTRIBUTE_TAG_HEAP_ADDRESS_START
 * - DukUKPROC_ATTRIBUTE_TAG_HEAP_ADDRESS_SIZE
 * - DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_PRIORITY_BASE
 * - DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_TIME_QUANTUM_ALLOCATED
 * - DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_TIME_QUANTUM_REMAINING
 * - DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_STATE
 * - DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_STATISTICS
 *
 * @usage All of the ukProc Attributes are read only.
 */
typedef TukTLV_TAG TukUKPROC_ATTRIBUTE_TAG;


/* //////////////////////////////////////////////////////////////////////// */
/*                            C-TYPES - SCHEDULING                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Scheduling Priority of a ukProc.
 *
 * Definition of the uKernel C-Type for the Scheduling Priority of a ukProc.
 * The Scheduling Priority allows the ukScheduler (uKernel Scheduler) to
 *  determine which ukProc will be scheduled first among several schedulable
 *  ukProcs.
 *
 * @implementation The effective Scheduling Priority rating considered for
 *  electing a ukProc by the ukScheduler is based on the inverse of its
 *  numerical value: the schedulable ukProc with the Highest Scheduling
 *  Priority in Active Scheduling Window, that is with the lowest Scheduling
 *  Priority value, will be scheduled in first place (it has the highest
 *  precedence in the ukScheduler for being elected as the new Scheduled
 *  ukProc).
 *
 * @implementation If several schedulable ukProcs have the same Scheduling
 *  Priority in the ukScheduler, there is no guarantee that the first ukProc
 *  to be scheduled is the one that has been scheduled the longest time ago.
 *  The reasons why are due to:
 *   - Algorithm optimization used by the ukScheduler.
 *   - uKernel Security Policy using randomness to prevent scheduling
 *    predictability (help to increase attack complexity).
 *
 * @usage By default, mid-range Scheduling Priorities should be used for most
 *  ukProcs. Only the ukProcs having some sensitivity to time deadline should
 *  use the highest Scheduling Priorities. The background ukProcs (i.e. on
 *  demand services) should have use the lowest Scheduling Priorities.
 *
 * @usage The Highest Scheduling Priority allowed for a ukProc is defined in
 *  the <SchedulingPriorityBase> field of the ukApp Descriptor of its ukApp
 *  (see TukUKAPP_DESCRIPTOR).
 *
 * @usage The Scheduling Priority values shall be in the range
 *  [0 ... DukCONFIG_OPTION_SCHEDULING_PRIORITY_MAX].
 *  The lower is the Scheduling Priority value of a Schedulable ukProc, the
 *  higher is its precedence for being elected as the new Scheduled ukProc.
 */
typedef TukUINT8 TukSCHEDULING_PRIORITY;


/**
 * @brief uKernel C-Type for the Scheduling Time Quantum of a ukProc.
 *
 * Definition of the uKernel C-Type for the Scheduling Time Quantum of a ukProc.
 *
 * A Scheduling Time Quantum represents a time slice, in uKernel SysTick unit,
 *  during which a ukProc can be scheduled (i.e. it is the one currently
 *  executed by the CPU) by the ukScheduler (uKernel Scheduler).
 *
 * The following Scheduling Time Quantum values are used by the ukScheduler for
 *  the management of the scheduling of each ukProc:
 *  - Scheduling Time Quantum Allocated: Maximal count of uKernel SysTicks
 *   during which the ukProc can remain the Scheduled ukProc (i.e. the one
 *   currently executed by the MCU) in a Scheduling Window before being
 *   preempted by the ukScheduler to elect another Scheduled ukProc.
 *   This count is fixed and defined by the
 *   <SchedulingTimeQuantumAllocated_systick> field of the ukApp Descriptor of
 *   the ukProc.
 *  - Scheduling Time Quantum Remaining: Current count of uKernel SysTicks
 *   during which the ukProc can still remain the Scheduled ukProc (i.e. the
 *   one currently executed by the MCU) in the Active Scheduling Windows before
 *   being preempted by the ukScheduler to elect another Scheduled ukProc.
 *   This count is reset upon each change of Active Scheduling Window with
 *   the Scheduling Time Quantum Allocated value (and thus its value is always
 *   lower or equal to it).
 *
 * The ukScheduler is using the Scheduling Time Quantum values of each ukProc
 *  as follows:
 *  - Each time a uKernel Systick occurs, the Scheduled ukProc (i.e. the one
 *   that is currently executed on the MCU) has its Scheduling Time Quantum
 *   Remaining value decremented. If it reaches null(0):
 *    + The ukScheduler preempts the Scheduled ukProc (i.e. its execution
 *     state is frozen). It will not not be scheduled anymore in the Active
 *     Scheduling Window, as its Scheduling Time Quantum Remaining value will
 *     remain null(0) during this Active Scheduling Window.
 *    + It triggers the election of another Scheduled ukProc among the
 *     Schedulable ukProcs (i.e. ready to be executed), or enter in ukScheduler
 *     Idle mode if there is no Schedulable ukProcs.
 *  - When all the schedulable ukProcs have their Scheduling Time Quantum
 *   Remaining value having reached null(0) (which is guaranteed to happen
 *   after a maximal fixed duration in the Active Scheduling Window as the
 *   Scheduling Time Quantum Remaining value of the schedulable ukProcs is
 *   always decreasing):
 *    + A new Scheduling Window is started.
 *    + The Scheduling Quantum Remaining value of each ukProc is reloaded with
 *     its Scheduling Time Quantum Allocated value.
 *     Note that the reloading does not affect the fact that a ukProc is
 *     schedulable or not (its schedulable state is not modified).
 *    + The ukScheduler elects a new Scheduled ukProc from the just started
 *     Scheduling Window (which is now the Active Scheduling Window).
 *  - If ukProc Exception is supported (see uKernel Feature
 *   SukCONFIG_FEATURE_UKPROC_EXCEPTION):
 *    + When a ukProc Exception is raised, the Scheduling Time Quantum In
 *      Exception is reset before entering in its ukApp Entry Point
 *      ukappException()).
 *    + While the ukProc is the Scheduled ukProc and remains in the ukApp
 *      Entry Point ukappException():
 *     --- The Scheduling Time Quantum In Exception is incremented upon each
 *        uKernel Systick.
 *     --- If the Scheduling Time Quantum Allocated for ukProc Exception defined
 *        in the field <UKProcExceptionSchedulingTimeQuantumAllocated_systick>
 *        in ukApp Descriptor is exhausted, then it is a ukProc Fatal Error,
 *        and the uKernel triggers a ukProc Abort with ukProc Termination Reason
 *        DukUKPROC_TERMINATION_REASON_ABORT_INVALID_STATE.
 *
 * @usage When attributing the Scheduling Time Quantum Allocated value to a
 *  ukProc, the following elements should be considered:
 *   - The Scheduling Algorithm used by the ukScheduler.
 *   - The Scheduling Priority of the ukProc.
 *   - The maximal number of ukProcs that may be executable at the same time.
 *   - The mean execution time of each ukProc.
 *  As rough indication, the Scheduling Time Quantum Allocated values chosen
 *   should:
 *   - Not be too disparate.
 *   - Be roughly linear in inverse of the Scheduling Priority of each
 *    ukProc: ukProcs with Highest Scheduling Priorities should have smaller
 *    Scheduling Time Quantum Allocated value. The reason why is that they are
 *    normally dedicated to serve urgent requests (e.g. peripheral driver), and
 *    this serving should not take too much time in order to allow the serving
 *    of other similar urgent requests (e.g. other peripheral drivers).
 *
 * @usage The Scheduling Time Quantum Allocated value of a ukProc is defined in
 *  the <SchedulingTimeQuantumAllocated_systick> field of the ukApp Descriptor
 *  of its ukApp (see TukUKAPP_DESCRIPTOR).
 *
 * @usage A Scheduling Time Quantum value shall be in the range
 *  [DukSCHEDULING_TIME_QUANTUM_MIN_systick ...
 *   DukSCHEDULING_TIME_QUANTUM_MAX_systick].
 */
typedef TukUINT8 TukSCHEDULING_TIME_QUANTUM_systick;


/**
 * @brief uKernel C-Type for the Scheduling ukProc State.
 *
 * Definition of the uKernel C-Type for the Scheduling ukProc State in the
 *  ukScheduler (uKernel Scheduler).
 * The Scheduling ukProc State allows to determine the way the ukProc is
 *  managed by the ukScheduler to:
 *  - Be elected as the new Scheduled ukProc.
 *  - Manage timeout and deadline for some actions performed by the ukProc.
 *
 * The following Scheduling ukProc State flags are defined (see associated
 *  documentation for the details on their meaning):
 *  - DukSCHEDULING_STATE_READY_FLAG
 *  - DukSCHEDULING_STATE_INTERRUPT_FLAG
 *  - DukSCHEDULING_STATE_BLOCKED_FLAG
 *  - DukSCHEDULING_STATE_YIELDED_FLAG
 *  - DukSCHEDULING_STATE_HALTING_FLAG
 *  - DukSCHEDULING_STATE_HALTED_FLAG
 *
 * @implementation The Scheduling ukProc State is defined as a set of flags in
 *  order to ease and speed the testing of high level state when managing the
 *  ukProc.
 *  Note however that some flags are not independent and can never be set
 *  together (see DukSCHEDULING_STATE_xxx_FLAG documentation).
 *
 * @implementation The Scheduling ukProc State of a ukProc is affected by the
 *  following events:
 *   - Actions performed by the ukProc itself.
 *    Example: The ukProc is requesting yielding (see ukUKProcYield()), it
 *     triggers a ukProc Fatal Error, ...
 *   - Actions performed by other ukProcs.
 *    Example: Another ukProc is sending an IPC message expected by the ukProc.
 *   - Actions performed by hardware events.
 *    Example: Triggering of a PIRQ (Peripheral IRQ) expected by a ukProc.
 *   - Actions performed by the uKernel for uKernel Session management.
 *    Example: uKernel Session End triggering a ukProc Abort for all the
 *     ukProcs.
 *
 * @usage The following terminology is used for Scheduling ukProc State in the
 *  ukScheduler:
 *  - Ready: A ukProc is said to be Ready when it is a schedulable ukProc, that
 *   is it can be elected, or is currently, the Scheduled ukProc in the
 *   ukScheduler (i.e. the one currently executed by the CPU).
 *   A ukProc is Ready if it has the flag DukSCHEDULING_STATE_READY_FLAG set
 *   in its Scheduling ukProc State.
 *  - Blocked: A ukProc is said to be Blocked when it is expecting an external
 *   event to occur (e.g. sending of an IPC Message by another ukProc,
 *   triggering of a Peripheral IRQ, ...).
 *   As long as a ukProc is Blocked, the ukProc is unschedulable and cannot be
 *   elected as the Scheduled ukProc by the ukScheduler. The ukProc is not
 *   Blocked anymore (and switch back to Ready) as soon as one of the event it
 *   expects occurs.
 *   A ukProc which is Blocked can switch temporarily into Scheduling ukProc
 *   State Interrupted; as soon as the management of the interrupt is over, it
 *   switches back to Blocked.
 *   A ukProc is Blocked if it has the flag DukSCHEDULING_STATE_BLOCKED_FLAG
 *   set in its Scheduling ukProc State.
 *  - Yielded: A ukProc is said to be Yielded if a Yield Delay has been applied
 *   to the ukProc (see ukUKProcYield()).
 *   As long as a ukProc is Yielded, the ukProc is unschedulable and cannot be
 *   elected as the Scheduled ukProc by the ukScheduler. The ukProc is not
 *   Yielded anymore (and switch back to Ready) as soon as the Yield Delay is
 *   over.
 *   A ukProc is Yielded if it has the flag DukSCHEDULING_STATE_YIELDED_FLAG
 *   set in its Scheduling ukProc State.
 *  - Interrupted: A ukProc is said Interrupted during the time to perform the
 *   processing of a ukProc Exception that has been triggered.
 *   If the uKernel Feature SukCONFIG_FEATURE_UKPROC_EXCEPTION is
 *   supported, then a ukProc is Interrupted during the whole invocation of
 *   the ukApp Entry Point ukappException().
 *   A ukProc is Interrupted if it has the flag
 *   DukSCHEDULING_STATE_INTERRUPT_FLAG set in its Scheduling ukProc State.
 *  - Halting: A ukProc is said Halting during the time it performs its ukProc
 *   Cleanup before transitioning definitively to the Scheduling ukProc State
 *   Halted.
 *   If the uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   supported, then a ukProc is Halting during the whole invocation of
 *   the ukApp Entry Point ukappCleanup().
 *   A ukProc is Halting if it has the flag DukSCHEDULING_STATE_HALTING_FLAG
 *   set in its Scheduling ukProc State.
 *  - Halted: A ukProc is said Halted when it can never be elected as the
 *   Scheduled ukProc again (and thus never be executed again).
 *   A ukProc is Halted if it has the flag DukSCHEDULING_STATE_HALTED_FLAG set
 *   in its Scheduling ukProc State.
 *
 * @usage The Scheduling ukProc State of a ukProc can be retrieved using the
 *  ukProc Attribute DukUKPROC_ATTRIBUTE_TAG_SCHEDULING_STATE (see
 *  ukUKProcGetAttribute()).
 */
typedef TukUINT32 TukSCHEDULING_UKPROC_STATE;


/**
 * @brief uKernel C-Type for the Scheduling Statistics of a ukProc.
 *
 * Definition of the uKernel C-Type for the Scheduling Statistics of a ukProc
 *  produced by the ukScheduler (uKernel Scheduler).
 *
 * The ukScheduler statistics consists in the following elements:
 *  - (TukCOUNT64)<ScheduledCount>: Number of times that the ukProc has been
 *   elected as the new Scheduled ukProc (i.e the one currently executed), the
 *   previously Scheduled ukProc being another ukProc.
 *   As long as there is only one schedulable ukProc, then the counter of this
 *   schedulable ukProc stays constant (as previous Scheduled ukProc is itself).
 *  - (TukCOUNT64)<PreemptedCount>: Number of times that the ukProc has been
 *   preempted (i.e. its execution has been paused because its Scheduling
 *   Time Quantum Remaining has reached null(0)).
 *   If the ukProc has been set in Scheduling ukProc State Blocked or Yielded
 *   (e.g. following the invocation of a uKernel Privileged Service, as the
 *   sending of an IPC Message in Blocking Mode), it is not counted as being
 *   preempted and this counter is not incremented. Thus this counter is always
 *   smaller than the counter in <ScheduledCount> field.
 *  - (TukTIME64_tick)<ScheduledTimeTotal_systick>: Total count of uKernel
 *   SysTicks during which the ukProc has been the Scheduled ukProc.
 *  - (TukTIME64_us)<ScheduledTimeTotal_us>: Total amount of time, in
 *   microseconds(us) unit, during which the ukProc has been the Scheduled
 *   ukProc.
 */
typedef struct {
        TukCOUNT64        ScheduledCount;
        TukCOUNT64        PreemptedCount;
        TukTIME64_tick    ScheduledTimeTotal_systick;
        TukTIME64_us      ScheduledTimeTotal_us;
    } TukSCHEDULING_UKPROC_STATISTICS;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - PERIPHERAL IRQ                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the Index of a Peripheral Interrupt Request.
 *
 * Definition of the uKernel C-Type for the Index of a Peripheral Interrupt
 *  Request (PIRQ).
 * This index is used for the registration of the PIRQ by a ukProc to
 *  reference one of the Peripheral Interrupt Request supported by the
 *  selected Platform.
 *
 * The PIRQ Index valid values are Platform dependent, and are in the range
 *  [0 ... DukPIRQ_IDX_MAX].
 *
 * @warning A Peripheral Interrupt Request referenced by a PIRQ Index is
 *  Platform dependent and depends of the selected Platform.
 *
 * @implementation The MCU Exception (bus fault, division by zero, ...) are
 *  managed internally by the uKernel code and thus cannot be referenced by
 *  this PIRQ Index.
 *
 * @implementation On most architectures (ARM Cortex-M, ...) the PIRQ Index
 *  corresponds to the IRQ vector number in the MCU interrupt controller.
 */
typedef TukUINT8 TukPIRQ_MCU_IDX;

/**
 * @brief Type for the Registered Identifier (REGID) of a Peripheral IRQ
 *  registered by a ukProc.
 *
 * This type defines a Registered Identifier (REGID) provided by the uKernel
 *  to identify a registration of a given Peripheral IRQ by a given ukProc
 *  (see ukPeripheralIRQRegister).
 * This Registered Identifier is used to manage the Peripheral IRQ through
 *  uKernel API.
 *
 * The Registered Identifier valid values are in the range [0 ...
 *  DukPIRQ_REGISTRATION_ID_MAX].
 *
 * @note The Registered Identifier value of a given Peripheral IRQ by a given
 *  ukProc is not guaranteed to be the same between two uKernel sessions.
 */
typedef TukUINT16 TukPIRQ_REGISTRATION_ID;

/**
 * @brief Type for the Attributes of a Peripheral IRQ.
 *
 * This types defines the current State for a ukProc of a Registered
 *  Peripheral IRQ that is the combination (ORing) of its specific ukProc
 *  registration state and of its Platform state (common to all ukProcs).
 *
 * Parts of the Peripheral IRQ Attributes that describe its configuration
 *  upon its registration (this part is fixed till unregistered):
 *  - DukPIRQ_ATTRIBUTES_CONFIG_ACKAUTO_FLAG: When set, the uKernel
 *   automatically and immediately acknowledges the PIRQ for the ukProc.
 *
 * Parts of the Peripheral IRQ Attributes that contain its current state in
 *  relation to a given ukProc:
 *  - DukPIRQ_ATTRIBUTES_UKPROC_ENABLED_FLAG: When set, the PIRQ is enabled
 *   for the ukProc.
 *  - DukPIRQ_ATTRIBUTES_UKPROC_ACKPENDING_FLAG: When set, the uKernel is
 *   expecting the ukProc to manually acknowledge a given PIRQ (the PIRQ will
 *   be enabled again in MCU interrupt controller only when this flag is reset
 *   in any of the ukProcs that have registered this PIRQ). This flag must not
 *   be set on level-sensitive IRQs. This flag is highly recommended for edge-
 *   triggered IRQs.
 *
 * Parts of the Peripheral IRQ Attributes that contain its current state in
 *  relation to the Platform:
 *  - DukPIRQ_ATTRIBUTES_PLATFORM_REGISTERED_FLAG: When set, the PIRQ is
 *   registered by at least one ukProc.
 *  - DukPIRQ_ATTRIBUTES_PLATFORM_ENABLED_FLAG: When set, the PIRQ is enabled
 *   in the interruption controller of the MCU.
 */
typedef TukUINT16 TukPIRQ_ATTRIBUTES;


/**
 * @brief Type for the Action to be performed on a Peripheral IRQ registered
 *  by a ukProc.
 *
 * This type defines an Action to be performed on a given Peripheral IRQ (or
 *  a set of Peripheral IRQ) that has been registered by a given ukProc.
 * The following Action values are defined for a Peripheral IRQ:
 *  - DukPIRQ_ACTION_ACKNOWLEDGE: Acknowledge the Peripheral IRQ, allowing
 *   the uKernel to enable it again at Hardware level. This action may clear
 *   the pending state of the IRQ. Therefore for edge-triggered IRQs that
 *   do not use DukPIRQ_ATTRIBUTES_UKPROC_ACKPENDING_FLAG, it must be called
 *   before accessing the hardware that triggered the PIRQ. For level-sensitive
 *   IRQs this should be called after handling the hardware in order to avoid
 *   potential spurious interrupts.
 *  - DukPIRQ_ACTION_ENABLE: Enable the Peripheral IRQ for the given
 *   ukProc (does not affect Enable/Disable state at Hardware level
 *   for other registered ukProcs).
 *  - DukPIRQ_ACTION_DISABLE: Disable the Peripheral IRQ for the given
 *   ukProc (does not affect Enable/Disable state at Hardware level
 *   for other registered ukProcs).
 */
typedef TukUINT8 TukPIRQ_ACTION;

/**
 * @brief Type for the Registered Peripheral IRQ Information.
 *
 * This type defines the Information that can be retrieved from a given
 *  Registered Peripheral IRQ.
 * The information are the following:
 *  - (TukUKPROC_PUID)<UKProcPUID>: PUID (see TukUKPROC_PUID) of the ukProc
 *   that has done the registration of this Peripheral IRQ.
 *   The value DukPUID_INVALID is set if the retrieved information is not
 *   significant.
 *  - (TukPIRQ_ATTRIBUTES)<PIRQAttributes>: Attributes of the Registered
 *   Peripheral IRQ in the context of the ukProc to which it has
 *   been registered (see TukPIRQ_ATTRIBUTES for details).
 *   The value DukPIRQ_ATTRIBUTES_INVALID is used if the retrieved information
 *   is not significant.
 *  - (TukPIRQ_MCU_IDX)<PIRQMCUIndex>: MCU Index of the registered Peripheral
 *   IRQ (see TukPIRQ_MCU_IDX for details).
 *   The value DukPIRQ_IDX_INVALID is used if the retrieved information is
 *   not significant.
 */
typedef struct {
    TukUKPROC_PUID            UKProcPUID;
    TukPIRQ_ATTRIBUTES        PIRQAttributes;
    TukPIRQ_MCU_IDX           PIRQMCUIndex;
    unsigned char             pad_PIRQMCUIndex[1];
} TukPIRQ_REGISTERED_INFO;
MukASSERT_STATIC(
    sizeof(TukUKPROC_PUID) +
    sizeof(TukPIRQ_ATTRIBUTES) +
    sizeof(TukPIRQ_MCU_IDX) + 1 ==
    sizeof(TukPIRQ_REGISTERED_INFO),
    "The structured type TukPIRQ_REGISTERED_INFO has some implicit padding "
    "and is thus not suitable for exchange via service calls.");
MukASSERT_STATIC(
    sizeof(TukPIRQ_REGISTERED_INFO) <=
    sizeof(TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_DATA),
    "The structured type TukPIRQ_REGISTERED_INFO is larger than the size "
    "of the parameter area of the service block.")

/**
 * @brief Type defining a Bitmask associated to all the registered PIRQs.
 *
 * This type defines a Bitmask associated to all the registered PIRQs (
 *  Peripheral IRQs).
 *
 * Each bit set in the bitmask corresponds to a registered Peripheral IRQ.
 * The bit number corresponds to the Registered Identifier value of the
 *  Peripheral IRQ (see TukPIRQ_REGISTRATION_ID). The bit number 0 is the
 *  leftmost bit in the structure.
 *
 * @note If more than one triggering is occurring for the same PIRQ before,
 *  subsequent ones are ignored (no counting is done).
 */
typedef TukBITMASK32 TukPIRQ_REGISTERED_BITMASK[(DukCONFIG_OPTION_PIRQ_SUPPORTED_COUNT_MAX + 32U - 1U) / 32U];



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - UKERNEL SIGNAL                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the Identifier of a uKernel Signal.
 *
 * Definition of the uKernel C-Type for the Identifier of a uKernel Signal.
 *
 * A uKernel Signal allows the uKernel to report a significant event during the
 *  execution of a ukProc (illegal memory access, abnormal race conditions,
 *  security alert, ...) that needs immediate attention from the ukProc.
 *
 * The way the uKernel will process the triggered uKernel Signal depends of
 *  the uKernel Feature SukCONFIG_FEATURE_UKPROC_EXCEPTION:
 *  - SUPPORTED: The uKernel will halt immediately the execution of the ukProc
 *   and invoke the ukApp Entry Point ukappException().
 *  - NOT SUPPORTED: The uKernel will send an IPC of Nature uKernel Signal to
 *    the ukProc (see TukUKSIGNAL_NOTIFIED_BITMASK). This uKernel
 *    Signal will be the first IPC received as soon as any IPC reception is
 *    performed by the ukProc (whatever other pending IPCs are ready to be
 *    received by the ukProc).
 *
 * @implementation If a uKernel Signal is sent to a ukProc that is in
 *  Scheduling ukProc State Blocked (e.g. while waiting for an IPC message in
 *  Blocking Mode), the sending of the uKernel Signal will set it back
 *  immediately in the Scheduling ukProc State Ready to allow it to receive and
 *  process the uKernel Signal.
 *  However, no change is done on ukScheduler (uKernel Scheduler) election
 *  process: it will be elected only after the other schedulable ukProcs with
 *  higher Scheduling Priority (i.e. with lower Scheduling Priority value) have
 *  been elected.
 *
 * @implementation Only the uKernel can send a uKernel Signal to a ukProc.
 *
 * @usage A uKernel Signal Identifier value shall be in the range
 *      [0 ... DukSIGNAL_ID_MAX].
 */
typedef TukIDX16    TukSIGNAL_ID;


/* //////////////////////////////////////////////////////////////////////// */
/*                              C-TYPES - IPC                               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Type for the mode used for sending / receiving an IPC message.
 *
 * This type defines the mode to be used for a ukProc sending or
 *  receiving an IPC message.
 * The mode allows to adjust the way of sending/receiving IPC message:
 *  polling (immediate sending/receiving), timeout (if sending/receiving not
 *  performed up to a given time), filtering which message are accepted in
 *  reception.
 *
 * The IPC Mode structure has the following flags and fields:
 *  - IPC SEND Flag:
 *   + DukIPC_MODE_SEND_BLOCKING_FLAG:
 *    * If this flag is set: SEND BLOCKING mode
 *      If the Recipient ukProc is not expecting the IPC Message sent,the
 *      Sending ukProc is Blocked. Once the expected IPC Message is
 *      received by the Recipient ukProc (without waiting for the Recipient
 *      ukProc being the Scheduled ukProc), the Sending ukProc is not Blocked
 *      anymore, and the uKernel Privileged Service invoked for sending the IPC
 *      Message will return with the status of the sending operation.
 *      If the Recipient ukProc was already expecting the IPC Message of the
 *      Sending ukProc (i.e. it is in reception with proper parameters
 *      for 'From' and 'Receive Filter' for accepting the IPC message), then
 *      the IPC Message is transferred immediately to the Recipient ukProc, and
 *      the uKernel Privileged Service invoked for sending the IPC Message
 *      returns immediately with the status of the sending operation.
 *      The sending will be aborted only if the Recipient ukProc is terminated
 *      (even if reincarnated afterwards), or if the IPC Timeout has expired (a
 *      null IPC Timeout is equivalent to an infinite timeout).
 *    * If this flag is not set: SEND POLLING mode
 *      If the Recipient ukProc is expecting the IPC Message of the
 *      Sending ukProc (i.e. it is in reception with proper parameters
 *      for 'From' and 'Receive Filter' for accepting the IPC), then the IPC
 *      Message is transferred immediately to the Recipient ukProc, and the
 *      Recipient ukProc is marked to be awaken.
 *      If the Recipient ukProc is not expecting the IPC Message, then the
 *      sending is aborted.
 *      The uKernel Service sending function always returns immediately (the
 *      Sending ukProc is never put asleep in this mode).
 *      The timeout value is ignored in this mode.
 *
 *  - IPC RECEIVE Flag:
 *   + DukIPC_MODE_RECEIVE_BLOCKING_FLAG:
 *    * If this flag is set: RECEIVING BLOCKING mode
 *      If no IPC Message among the ones expected by the Recipient ukProc is
 *      available, the Recipient ukProc is Blocked. Once an expected IPC
 *      Message is sent by the uKernel or another ukProc to the Recipient
 *      ukProc, the Recipient ukProc is not Blocked anymore, and the uKernel
 *      Privileged Service invoked for receiving the IPC Message will return
 *      with the status of the receiving operation and the received IPC Message.
 *      If an IPC Message among the expected ones is already available (i.e.
 *      an IPC message of one of the expected IPC Message Nature has been sent
 *      by the uKernel or another ukProc to the Recipient ukProc), then the
 *      uKernel Privileged Service invoked for receiving the IPC Message returns
 *      immediately with the status of the receiving operation and the received
 *      IPC Message.
 *      The reception will be aborted only if the expected Sender ukProc is
 *      terminated (even if reincarnated afterwards), or if the IPC Timeout has
 *      expired (a null IPC Timeout is equivalent to an infinite timeout).
 *    * If this flag is not set: RECEIVING POLLING mode
 *      If an IPC Message corresponding to the expectation of the Receiving
 *      ukProc is available (i.e. compatible parameters for 'From'
 *      and 'Receiving Filters'), then the IPC Message is received immediately.
 *      If no IPC Message is available, then the reception is aborted.
 *      This mode will never put the Reception ukProc asleep (invoked uKernel
 *      Service reception function will always return immediately).
 *      The timeout value is ignored in this mode.
 *
 *  - IPC RECEIVING FILTERS:
 *   The Receiving Filters allows to specify the Nature of the IPC Message that
 *    are accepted to be received for the current Reception.
 *   + DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG: Raw data sent by another
 *     ukProc referenced as 'From' to the Recipient. The 'From' allows
 *     to specify a specific ukProc, or any ukProc (with
 *     proper credentials for sending to this Recipient).
 *   + DukIPC_MODE_RECEIVING_FILTER_PERIPHERAL_IRQ_FLAG: Notification (simple flag
 *    of one bit) that at least one Registered Peripheral IRQ(s) has triggered.
 *   + DukIPC_MODE_RECEIVING_FILTER_UKPROC_NOTIFICATION_FLAG: Notification (simple
 *    flag of one bit) that at least one other ukProc has notified
 *    this ukProc.
 *   The IPC Receiving Filters defined above can be mixed altogether.
 *   Note that it is not possible to filter IPC uKernel Signal sent by the
 *   the uKernel (they are always authorized, and will always trigger the
 *   reception).
 *
 * - TIMEOUT (see DukIPC_MODE_TIMEOUT_MASK): The duration, in uKernel SysTicks
 *  unit, before aborting a Sending or Receiving operation.
 *  The Timeout duration value is taken into account only when the BLOCKING
 *  mode is used for Sending or Receiving. A Timeout value of 0 corresponds
 *  to an infinite timeout (see DukIPC_MODE_TIMEOUT_INFINITE).
 *  If the uKernel Service for atomic Send / Receive is used, the same timeout
 *  value is used for both operation.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...28] <BlockinggMode>: This 4-bit field contains the flag relative
 *   to the blocking mode being used when sending or receiving IPC Messages.
 *  - [27...24] <ReceivingNature>: This 4-bit field contains the flag relative
 *   to nature of IPC Messages that can be received.
 *  - [23...00] <Timeout>: Timeout value, in uKernel Systicks unit, for the
 *   sending or receiving an IPC Message.
 *
 * The C-Type IPC Mode is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |      Bit number       |                  Description                     |
 * |31...28|27...24|23...00|                                                  |
 * | flag  |filter |timeout|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * |  xxx1 |       |       | Send Blocking mode selected.                     |
 * |  xx1x |       |       | Receiving Blocking mode selected.                |
 * |-------|------ |-------|--------------------------------------------------|
 * |       |  xxx1 |       | Can receive ukProc Message                       |
 * |       |  xx1x |       | Can receive Peripheral IRQ Notification          |
 * |       |  x1xx |       | Can receive ukProc Notification                  |
 * |       |  0xxx |       | RFU (shall be 0)                                 |
 * |-------|------ |-------|--------------------------------------------------|
 * |       |       |xxxxxxx| Timeout value (0 value for infinite timeout) if  |
 * |       |       |       |  Send Blocking or Receiving Blocking mode        |
 * |       |       |       |  selected.                                       |
 * |-------|-------|-------|--------------------------------------------------|
 */
typedef TukUINT32 TukIPC_MODE;


/**
 * @brief Type defining the Nature of the contents of an IPC Message.
 *
 * The Nature of an IPC message defines the origin and structure of the
 *  received IPC Message Contents (see TukIPC_MSG_CONTENT).
 *
 * The following Natures of IPC Message are defined:
 *  - DukIPC_MSG_NATURE_UKPROC_DATA: Raw data sent by another ukProc.
 *  - DukIPC_MSG_NATURE_PIRQ_TRIGGERED: Notification of Peripheral IRQ
 *   having triggered.
 *  - DukIPC_MSG_NATURE_UKPROC_NOTIFICATION: Notification sent by other
 *   of ukProcs.
 *  - DukIPC_MSG_NATURE_UKSIGNAL_NOTIFIED: Notification of uKernel Signals of
 *   Nature Information.
 *
 * The Nature is part of the received IPC Message Structure (see TukIPC_MSG).
 *
 * @note A received IPC Message can have only one Nature. If a ukProc has
 *  several IPC Messages of different Natures pending, then a reception
 *  operation will be needed for each Nature of IPC Message (with proper
 *  Receiving Filter) to receive all the pending IPC Messages of different
 *  Natures.
 */
typedef TukUINT16 TukIPC_MSG_NATURE;

/**
 * @brief Type defining a Label to describe an IPC Message.
 *
 * This type defines a 16-bit Label value that allows the Sender of the IPC
 *  Message to provide through this value additional information on the
 *  contents of the IPC Message sent. The meaning of this Label value has
 *  to be agreed between the Sender and the Recipient (this value is not used,
 *  neither interpreted, by the uKernel).
 *
 * The Label is part of the received IPC Message Structure (see TukIPC_MSG).
 */
typedef TukUINT16 TukIPC_MSG_LABEL;

/**
 * @brief Type defining IPC Message Contents for raw data sent by another
 *  ukProc.
 *
 * This type defines the IPC Message Content when the Nature of the IPC Message
 *  is raw data sent by another ukProc (see
 *  ukIPC_MSG_NATURE_UKPROC_DATA).
 *
 * The raw data contents consists in an array of 8-bit words.
 *
 * @note The raw data are not used, neither interpreted by the uKernel.
 *
 * @note The structure of the raw data has to be agreed between the Sender and
 *  the Recipient.
 */
typedef TukUINT8 TukIPC_MSG_CONTENT_UKPROC_DATA[44];


/**
 * @brief Type defining IPC Message Contents for a set of ukProc
 *  Notifications.
 *
 * This type defines the IPC Message Contents when the Nature of the IPC
 *  Message is a set of Notification of other ukProcs (see
 *  DukIPC_MSG_NATURE_UKPROC_NOTIFICATION).
 *
 * The Contents consists in a Bitmask, where each bit set corresponds to a
 *  ukProc having sent at least one Notification to the Recipient
 *  ukProc.
 * The bit number corresponds to the ukProc Index (PIDX) value of the
 *  ukProc having sent the Notification (see TukUKPROC_PIDX). The bit
 *  number 0 is the leftmost bit in the structure.
 *
 * @note If more than one Notification is sent by the same ukProc
 *  before being received by the Recipient ukProc, then subsequent
 *  ones are ignored (no counting is done).
 */
typedef TukBITMASK32 TukUKPROC_IPC_NOTIFICATION_BITMASK;


/**
 * @brief Type defining IPC Message Contents for a set of uKernel Signals
 *  Notifications.
 *
 * This type defines the IPC Message Contents when the Nature of the IPC
 *  Message is a set of Notification of uKernel Signals of Nature Information
 *  (see DukIPC_MSG_NATURE_UKSIGNAL_NOTIFIED).
 *
 * The Contents consists in a Bitmask, where each bit set corresponds to a
 *  uKernel Signal having being sent by the uKernel to the Recipient ukProc.
 * The bit number corresponds to the uKernel Signal Identifier (see
 *  TukSIGNAL_ID). The bit number 0 is the leftmost bit in the structure.
 *
 * @note If the same uKernel Signal is sent more than one time by the uKernel
 *  to the Recipient ukProc, then subsequent ones are ignored (no
 *  counting of the number of sending is done).
 *
 * @note Only the uKernel Signals of Nature Information are received as IPC
 *  Message.
 */
typedef TukBITMASK32 TukUKSIGNAL_NOTIFIED_BITMASK;

/**
 * @brief Type defining an IPC Message Contents.
 *
 * This type is a generic type defining the IPC Message Contents field in IPC
 *  Message structure.
 * It is defined as the union of the IPC Message Content Types corresponding to
 *  the supported Natures of an IPC Message.
 *
 * The following IPC Message Contents can be accessed from this generic type in
 *  function of IPC Message Nature:
 *  - (TukIPC_MSG_CONTENT_UKPROC_DATA)<UKProcRawData>: Raw data (not
 *   interpreted by the uKernel) written by the Sender of the IPC Message.
 *  - (TukPIRQ_REGISTERED_BITMASK)<PIRQTriggeredBitmask>:
 *   Bit Vector containing the registered Peripheral IRQ having triggered.
 *  - (TukUKPROC_IPC_NOTIFICATION_BITMASK)<UKProcIPCNotificationBitmask>:
 *   Bit Vector containing the other ukProcs having sent a Notification
 *   to the Receiving ukProc.
 *  - (TukUKSIGNAL_NOTIFIED_BITMASK)<UKSignalNotifiedBitmask>:
 *   Bit Vector containing the uKernel Signals of Nature Information sent by
 *   the uKernel to the Receiving ukProc.
 */
typedef union {
        TukIPC_MSG_CONTENT_UKPROC_DATA              UKProcRawData;
        TukPIRQ_REGISTERED_BITMASK                  PIRQTriggeredBitmask;
        TukUKPROC_IPC_NOTIFICATION_BITMASK          UKProcIPCNotificationBitmask;
        TukUKSIGNAL_NOTIFIED_BITMASK                UKSignalNotifiedBitmask;
    } TukIPC_MSG_CONTENT;


/**
 * @brief Type defining the IPC Message Structure.
 *
 * This type defines the IPC Message Structure that is used by the uKernel
 *  Services for storing the information and contents associated to the
 *  Sending or Receiving IPC Messages.
 * The same IPC Message Structure is used for Sending or Receiving an IPC
 *  Message.
 *
 * This IPC Message Structure is used by a ukProc for Sending an IPC
 *  Message of Nature TukIPC_MSG_NATURE_UKPROC_DATA (all the other Natures of
 *  IPC Message can only be sent by the uKernel). Only the following
 *  fields need to be filled by the ukProc for the Sending (the other
 *  fields will be filled in by the uKernel):
 *   - 'SenderLabel': Label for helping the Receiving ukProc to identify the
 *    IPC Message.
 *   - 'Content': Raw data to be sent to the Receiving ukProc (see
 *    TukIPC_MSG_CONTENT_UKPROC_DATA).
 *
 * This IPC Message Structure is the one retrieved upon the Reception of an
 *  IPC Message by a ukProc. Its fields contain the following
 *  information:
 *    - 'Nature': The Nature allows to identify the type of IPC Message,
 *     its sender (uKernel or ukProc), and the structure of its
 *     'Content' field (see TukIPC_MSG_NATURE).
 *    - 'SenderLabel': Label set by the Sender for helping the Receiving
 *     ukProc to identify the contents of the IPC Message.
 *     If the sender is the uKernel, then a null value is used.
 *    - 'SenderPUID':  ukProc Unique Identifier (PUID) of the Sending
 *     ukProc. If the sender is the uKernel, the special value
 *     DukUKPROC_PUID_UKERNEL is used.
 *    - 'SenderTime_us': Uptime in microseconds at which the IPC Message has
 *     been sent.
 *    - 'Content': Contents (payload) of the IPC message. Its structure
 *     depends of the value in the 'Nature' field (see TukIPC_MSG_CONTENT).
 */
typedef struct {
        TukIPC_MSG_NATURE  Nature;
        TukIPC_MSG_LABEL   SenderLabel;
        TukUKPROC_PUID     SenderPUID;
        TukTIME64_us       SenderTime_us;
        TukIPC_MSG_CONTENT Content;
    } TukIPC_MSG;


/**
 * @brief Type defining the IPC Message Structure in the case of an NSCall.
 *
 * This type defines the IPC Message Structure that is used by the uKernel
 *  Services for storing the information and contents associated to the
 *  receiving of IPC Message for NSCalls.
 *
 * This IPC Message structure is used similarly to the main IPC Message
 *  Structure. The receiving ukApp can cast the TukIPC_MSG type to this
 *  type after having checked the Nature field of the TukIPC_MSG is
 *  DukIPC_MSG_NATURE_NSWORLD_REQUEST.
 *
 * It comes with two additional fields:
 *   - 'Start32': The start address of the exchange area.
 *   - 'Length32': The size (in bytes) of the exchange area.
 */
typedef struct {
    TukIPC_MSG ipc_msg;
    TukADDRESS32 Start32;
    TukLENGTH32 Length32;
} TukIPC_MSG_NSCall;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - UKPROC EXCEPTION                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the ukProc Exception Event Nature.
 *
 * Definition of the uKernel C-Type for the ukProc Exception Event Nature.
 * The ukProc Exception Event Nature allows to identify the nature of the
 *  event (e.g. Peripheral IRQ, ...) having triggered a ukProc Exception.
 *
 * The following ukProc Exception Event Nature flags are defined:
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_PIRQ_TRIGGERED_FLAG: At least a ukProc
 *  Registered PIRQ has triggered.
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_UKPROC_IPC_NOTIFICATION_FLAG: At least
 *  one other ukProc has sent an IPC Notification to the ukProc.
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_UKSIGNAL_NOTIFIED_FLAG: At least one
 *  uKernel Signal has been notified to the ukProc.
 *
 * @implementation Always one and only one flag (i.e. bit logically set to 1)
 *  is set in a ukProc Exception Event Nature value.
 *
 * @implementation A ukProc Exception is aimed at managing only one ukProc
 *  Exception Event Nature at a time. If at a given time several events of
 *  different nature can lead to trigger a ukProc Exception, then the uKernel
 *  will trigger a different invocation of ukProc Exception for each ukProc
 *  Exception Event Nature.
 *
 * @usage The ukProc Exception Event Nature of the event having triggered a
 *  ukProc Exception is given in parameter <ukproc_exception_event_nature__i>
 *  of ukApp Entry Point ukappException().
 */
typedef TukUINT16 TukUKPROC_EXCEPTION_EVENT_NATURE;


/**
 * @brief uKernel C-Type defining the ukProc Exception Event Source.
 *
 * Definition of the uKernel C-Type for the ukProc Exception Event Source.
 * The ukProc Exception Event Source value contains a bitmask allowing to
 *  identify unambiguously the source(s) of the event (.e.g. which Registered
 *  PIRQ has triggered, ...) having triggered the ukProc Exception.
 *
 * The set of sources defined in the bitmask depends of the ukProc Exception
 *  Event Nature value:
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_PIRQ_TRIGGERED_FLAG: Each bit set in the
 *  bitmask indicates that a ukProc Registered PIRQ (Peripheral IRQ) has
 *  triggered (see TukPIRQ_REGISTERED_BITMASK).
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_UKPROC_IPC_NOTIFICATION_FLAG: Each bit
 *  set in the bitmask refers to a ukProc having sent an IPC Notification to
 *  the ukProc (see TukUKPROC_IPC_NOTIFICATION_BITMASK).
 * - DukUKPROC_EXCEPTION_EVENT_NATURE_UKSIGNAL_NOTIFIED_FLAG: Each bit set in
 *  the bitmask refers to a uKernel Signal having been sent to the ukProc (see
 *  TukUKSIGNAL_NOTIFIED_BITMASK).
 *
 * @usage The interpretation of the bitmask contained in this C-Type is
 *  dependent of the ukProc Exception Event Nature: see description of each
 *  defined ukProc Exception Event Nature C-Constant
 *  DukUKPROC_EXCEPTION_EVENT_NATURE_xxx for more details on the contents and
 *  the way to interpret it.
 *
 * @usage The ukProc Exception Event Source of the event having triggered a
 *  ukProc Exception is given in parameter <ukproc_exception_event_source_bm__i>
 *  of ukApp Entry Point ukappException().
 */
typedef TukBITMASK32 TukUKPROC_EXCEPTION_EVENT_SOURCE;


/* //////////////////////////////////////////////////////////////////////// */
/*                           C-TYPES - ADDRESS BLOCK                        */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @doc See "Address Block Definition" in "uk_services.h" for documentation
 *  on Address Blocks.
 */

/**
 * @brief C-Type for the Address Block Label.
 *
 * Definition of the uKernel C-Type for the Address Block Label.
 *
 * An Address Block Label allows to reference unambiguously an Address Block
 *  in the ukApp where it is defined. It is present in each Address Block
 *  Descriptor entry defined in ukApp Descriptor (see TukUKAPP_DESCRIPTOR).
 *
 * @implementation The uKernel checks during its initialization that all the
 *  Address Block Label values set in the Extra Address Blocks and Shared
 *  Buffers defined in the ukApp are unique (a ukApp cannot have several
 *  Address Blocks defined with the same label; same label can however be
 *  reused in other ukApps). If the check fails, the ukApp Descriptor is
 *  considered as invalid.
 *
 * @usage The advantage of using an Address Block Label is that it allows to
 *  reference unambiguously an Address Block defined in a ukApp even in case
 *  of change (upon ukApp updates or evolutions) of its Address Block
 *  Descriptor index in ukApp Descriptor.
 *
 * @usage In the Owner ukProc of an Address Block (which is the ukProc
 *  instantiated from the ukApp where the Address Block is defined), the
 *  Address Block Identifier of the Address Block can be retrieved from its
 *  Address Block Label by using ukAddressBlockGetIDFromLabel().
 */
typedef TukUKAPP_LABEL_LOCAL TukADDRESSBLOCK_LABEL;


/**
 * @brief C-Type for the Address Block Identifier.
 *
 * Definition of the uKernel C-Type for the Address Block Identifier.
 * An Address Block Identifier is used to unambiguously reference an Address
 *  Block defined in one of the ukApp of the ukApps Bundle.
 *
 * An Address Block Identifier supports the referencing of an Address Block:
 *  - Either locally, in the context of its Owner ukProc (that is the ukProc
 *   instantiated from the ukApp where the Address Block has been defined).
 *  - Or globally, in the context of any ukProc of the ukApps Bundle.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...16] Tag: This field contains the Address Block Identifier Tag
 *   used to prevent misuse of this value (see DukADDRESSBLOCK_ID_TAG).
 *  - [15...08] Nature: This field contains the Nature of the Identifier
 *   Reference field, that is how to interpret the value given as reference to
 *   identify the Address Block (see TukADDRESSBLOCK_ID_NATURE).
 *  - [07...00] Reference: This field contains the reference (index, uKernel
 *   identifier) used to identify the Address Block. The way to interpret this
 *   reference depends of the <Nature> field.
 *
 * The C-Type Address Block Identifier is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |      Bit number       |                   Description                    |
 * |31...16|15...08|07...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | ttttt |       |       | Tag (16-bit)                                     |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | Nature (8-bit)                                   |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Reference (8-bit)                                |
 * |-------|-------|----------------------------------------------------------|
 *
 * @usage An Address Block Identifier should be built only from:
 *  - MukADDRESSBLOCK_ID_BUILD().
 *  - ukAddressBlockGetIDFromLabel().
 *  - ukAddressBlockGetBundleID().
 */
typedef TukUINT32 TukADDRESSBLOCK_ID;


/**
 * @brief C-Type for the Nature of an Address Block Identifier.
 *
 * Definition of the uKernel C-Type for the Nature of an Address Block
 *  Identifier.
 * The Nature allows to define the kind of reference present in the Reference
 *  field of the Address Block Identifier (see TukADDRESSBLOCK_ID).
 *
 * The following Nature values are defined for an Address Block Identifier:
 * - DukADDRESSBLOCK_ID_NATURE_EXTRA_IDX: The Reference field is an index
 *  referencing an Extra Address Block. This index is significant only in the
 *  context of its Owner ukProc.
 *  The index references the entry of the Extra Address Block Descriptor in
 *  the Address Block Descriptor List of the ukApp Descriptor (see
 *  <AddressBlockExtraDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  This index value shall be in the range
 *   [0 ... (<AddressBlockExtraDescriptorCount> - 1)].
 * - DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX: The Reference field is an
 *  index referencing a Shared Buffer. This index is significant only in the
 *  context of its Owner ukProc.
 *  The index references the entry of the Shared Buffer Descriptor in the
 *  Shared Buffer Descriptor List of the ukApp Descriptor (see
 *  <SharedBufferDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  This index value shall be in the range
 *   [0 ... (<SharedBufferDescriptorCount> - 1)].
 * - DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_BUNDLE_ID: The Reference field is
 *  a uKernel identifier referencing a Shared Buffer. This uKernel identifier
 *  is global to all the ukApps part of the ukApps Bundle and is significant
 *  in the Owner ukProc or in the Managing ukProc of the Shared Buffer.
 *  Its value remains fixed during a uKernel Session (it is independent of
 *  the current set of ukProcs present).
 *  This uKernel identifier can be retrieved using ukAddressBlockGetBundleID()
 *  from the Address Block Identifier of Nature
 *  DukADDRESSBLOCK_ID_NATURE_SHAREDBUFFER_IDX.
 */
typedef TukUINT8 TukADDRESSBLOCK_ID_NATURE;


/**
 * @brief C-Type for the Address Block Attributes.
 *
 * Definition of the uKernel C-Type for the Address Block Attributes.
 * The Address Block Attributes allows to define the access policy and usage
 *  restrictions of an Address Block.
 *
 * The Address Block Attributes is composed as a set of the following flags:
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_PRIVATE_FLAG: This flag applies only
 *   on Extra Address Block Descriptor. When set, the range of addresses
 *   defined in the Address Block is private to the ukApp and cannot overlap
 *   with any other Address Blocks of ukApps in the uApps Bundle.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG: Read access allowed in the
 *   range of addresses defined in the Address Block.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG: Write access allowed in the
 *   range of addresses defined in the Address Block.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_MAP_OPTIONAL_FLAG: Access is allowed
 *   in the range of addresses defined in the Address Block without being
 *   explicitly mapped. The MCU Exception Fault mechanism is then used (much
 *   more slower in performance than using mapping).
 *   #NOTYETSUPPORTED
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG: When this flag is
 *   set, it is possible to add Attributes on this Address Block for being
 *   accessed by other ukProcs. However, the Attributes of the Owner or of the
 *   Managing ukProc of the Address Block cannot be modified.
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG: The Managing ukProc of
 *   the Address Block can transfer it to another ukProc that will become
 *   the new Managing ukProc (the one doing the transfer losing its managing
 *   rights, along with its access rights if it is not the Owner ukProc).
 */
typedef TukUINT16 TukADDRESSBLOCK_ATTRIBUTES;


/**
 * @brief C-Type for the Address Block State.
 *
 * Definition of the uKernel C-Type for the current State of the Address Block
 *  in its managing ukProc.
 *
 * The Address Block State contains information (mapped status, ...) on the
 *  Address Block in the context of its Managing ukProc (that is either the
 *  ukProc to which it has been transferred to, or its owner ukProc if it has
 *  not been transferred).
 *
 * The Address Block State is composed as a set of the following flags:
 *  - DukADDRESSBLOCK_STATE_MAPPED_OWNER_FLAG: The Address Block has
 *   been mapped in an Address Block Window of its Owner ukProc.
 *  - DukADDRESSBLOCK_STATE_MAPPED_MANAGING_FLAG: The Address
 *   Block has been mapped in an Address Block Window of its Managing ukProc.
 *  - DukADDRESSBLOCK_STATE_TRANSFERRED_FLAG: The Address Block has been
 *   transferred to a ukProc which is not its Owner ukProc.
 *  - DukADDRESSBLOCK_STATE_MEANINGFUL_FLAG: This flag shall be equals to 1
 *   for the other flags to be meaningful.
 *
 * @note Both flags DukADDRESSBLOCK_STATE_MAPPED_OWNER_FLAG and
 *  DukADDRESSBLOCK_STATE_MAPPED_MANAGING_FLAG can be set if the Address
 *  Block is mapped at the same time in its Owner ukProc and in another ukProc
 *  to which it has been transferred to.
 */
typedef TukUINT16 TukADDRESSBLOCK_STATE;


/**
 * @brief C-Type for the Address Block Information.
 *
 * Definition of the uKernel C-Type for the Information associated to an
 *  Address Block.
 *
 * The information provided are the following:
 *  - AddressBlockOwnerLabel: If the current ukProc is its Owner ukProc, this
 *   field contains the Address Block Label set in the Address Block Descriptor
 *   entry defining the Address Block in the ukApp Descriptor.
 *   Else, if the current ukProc is not its Owner ukProc, the value
 *   DukADDRESSBLOCK_LABEL_INVALID is set in this field.
 *  - AddressBlockAttributesManagingUKProc: Attributes of the Address Block in
 *   the context of its Managing ukProc (see TukADDRESSBLOCK_ATTRIBUTES).
 *  - AddressBlockState: State of the Address Block in the context of its
 *   Managing ukProc (see TukADDRESSBLOCK_STATE).
 *  - AddressBlockStart: Start address of the Address Block.
 *  - AddressBlockSize: Length in bytes of the Address Block.
 *  - AddressBlockOwnerPUID: PUID (see TukUKPROC_PUID) of its Owner ukProc.
 *   If the Address Block has no Owner ukProc (because no ukProc is
 *   instantiated from the ukApp defining the Address Block), then the
 *   C-Constant value DukUKPROC_PUID_INVALID is set in this field.
 *  - AddressBlockManagingPUID: PUID (see TukUKPROC_PUID) of its Managing
 *   ukProc. The Managing ukProc of an Address Block is the ukProc to which it
 *   has been transferred to (see ukSharedBufferTransfer()), or its Owner ukProc
 *   if it has not been transferred.
 *   If the Address Block has no Managing ukProc (sole possible case being that
 *   it has not been transferred and its Owner ukProc is not instantiated) then
 *   the C-Constant value DukUKPROC_PUID_INVALID is set in this field.
 */
typedef struct {
    TukADDRESSBLOCK_LABEL               AddressBlockOwnerLabel;
    TukADDRESSBLOCK_ATTRIBUTES          AddressBlockAttributesManagingUKProc;
    TukADDRESSBLOCK_STATE               AddressBlockState;
    TukADDRESS32                        AddressBlockStart;
    TukLENGTH32                         AddressBlockSize;
    TukUKPROC_PUID                      AddressBlockOwnerPUID;
    TukUKPROC_PUID                      AddressBlockManagingPUID;
} TukADDRESSBLOCK_INFO;


/* //////////////////////////////////////////////////////////////////////// */
/*                     C-TYPES - ADDRESS BLOCK DESCRIPTOR                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the Extra Address Block Descriptor.
 *
 * Definition of the uKernel C-Type for the Extra Address Block Descriptor.
 * An Extra Address Block Descriptor allows to fully define the characteristics
 *  of an Extra Address Block.
 *
 * An Address Block Extra Descriptor contains the following fields:
 *  - (TukADDRESSBLOCK_LABEL)<AddressBlockLabel>: Address Block Label associated
 *   to the defined Address Block. This label value shall be unique among all
 *   Address Blocks defined in the ukApp (but same value can be shared by
 *   different ukApps). This unicity allows this label to be used to reference
 *   an Extra Address Block unambiguously in the ukApp, and to use it to
 *   retrieve its Address Block Identifier (see ukAddressBlockGetIDFromLabel()).
 *  - (TukADDRESSBLOCK_ATTRIBUTES)<AddressBlockAttributes>: Attributes defining
 *   the Access Policy to the range of addresses defined by the Address Block.
 *   Only the flags set in the mask
 *   DukADDRESSBLOCK_ATTRIBUTES_EXTRA_DESCRIPTOR_MASK can be set in this value.
 *  - (TukADDRESS32)<AddressBlockStart>: Start address of the Address Block.
 *   The start address shall respects the following constraints:
 *    + It shall be a multiple of 32.
 *    + On most Platform based on ARM v7-M architecture (i.e. with
 *      uKernel Configuration SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V7M defined),
 *      it shall be a multiple of its length.
 *  - (TukLENGTH32)<AddressBlockSize>: Length of the Address Block (in bytes).
 *   The length shall respects the following constraints:
 *    + It shall be a multiple of 32.
 *    + It shall be in the range:
 *      [ DukCONFIG_OPTION_HW_ADDRESSBLOCK_SIZE_MIN ...
 *        DukCONFIG_OPTION_HW_ADDRESSBLOCK_SIZE_MAX ]
 *    + On most Platform based on ARM v7-M architecture (i.e. with
 *      uKernel Configuration SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V7M defined),
 *      it shall be a power of 2.
 *    + The resulting address range shall be fully contained in one of the
 *      entry of allowed address range for Extra Address Blocks
 *      (see DukCONFIG_OPTION_HW_ADDRESSBLOCK_EXTRA_AUTHORIZED_LIST).
 *
 * @robustness In order to enforce uKernel security properties and policy,
 *  Extra Address Block SHALL NOT be used for sharing data between ukProcs
 *  through internal or external memory areas (Shared Buffers Address Block
 *  HAVE TO BE USED for this purpose). The uKernel will perform checks during
 *  its initialization but cannot prevent all the possible misuses.
 *
 * @implementation An Extra Address Block can be accessed only by the ukProc
 *  instantiated from the ukApp into which it has been defined.
 *
 * @usage All the Extra Address Blocks defined in a ukApp are set in a fixed
 *  size list of Extra Address Block Descriptors.
 *  This list is part of the ukApp Descriptor (see field
 *  <AddressBlockExtraDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  The maximum number of elements in this list, corresponding to the maximum
 *  number of Extra Address Blocks that can be defined for a ukApp, is
 *  DukCONFIG_OPTION_UKAPP_ADDRESSBLOCK_EXTRA_DESCRIPTOR_COUNT_MAX.
 */
typedef struct {
        TukADDRESSBLOCK_LABEL                     AddressBlockExtraLabel;
        TukADDRESSBLOCK_ATTRIBUTES                AddressBlockExtraAttributes;
        TukADDRESS32                              AddressBlockExtraStart;
        TukLENGTH32                               AddressBlockExtraSize;
    } TukADDRESSBLOCK_EXTRA_DESCRIPTOR;


/**
 * @brief C-Type for the Shared Buffer Descriptor.
 *
 * Definition of the uKernel C-Type for the Shared Buffer Descriptor.
 * A Shared Buffer Descriptor allows to fully define the characteristics of a
 *  Shared Buffer.
 *
 * A Shared Buffer Descriptor contains the following fields:
 *  - (TukADDRESSBLOCK_LABEL)<SharedBufferLabel>: Address Block Label associated
 *   to the defined Shared Buffer. This label value shall be unique among all
 *   Address Blocks defined in a ukApp (but same value can be shared by
 *   different ukApps). This unicity allows this label to be used to reference
 *   the Shared Buffer unambiguously in the ukApp, and to use it to retrieve
 *   its Address Block Identifier (see ukAddressBlockGetIDFromLabel()).
 *  - (TukLENGTH16)<SharedBufferLength>: Length of the Shared Buffer (in bytes).
 *   The length of a Shared Buffer shall respects the following constraints:
 *    + It shall be a multiple of 32.
 *    + It shall be in the range:
 *      [ DukCONFIG_OPTION_HW_SHAREDBUFFER_SIZE_MIN ...
 *        DukCONFIG_OPTION_HW_SHAREDBUFFER_SIZE_MAX ]
 *    + On most Platform based on ARM v7-M architecture (i.e. with
 *      uKernel Configuration SukCONFIG_HW_MCU_CORE_ARM_CMX_ARCHI_V7M defined),
 *      it shall be a power of 2.
 *
 * @implementation A Shared Buffer has the following Attributes fixed in the
 *  context of its Owner ukProc:
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_ADD_CREDENTIALS_FLAG
 *  - DukADDRESSBLOCK_ATTRIBUTES_CONFIG_TRANSFER_FLAG
 *
 * @usage All the Shared Buffers defined in a ukApp are set in a fixed size
 *  list of Shared Buffer Descriptors.
 *  This list is part of the ukApp Descriptor (see field
 *  <SharedBufferDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  The maximum number of elements in this list, corresponding to the maximum
 *  number of Shared Buffers that can be defined for a ukApp, is
 *  DukCONFIG_OPTION_SHAREDBUFFER_COUNT_MAX.
 */
typedef struct {
        TukADDRESSBLOCK_LABEL                   SharedBufferLabel;
        TukLENGTH16                             SharedBufferLength;
    } TukSHAREDBUFFER_DESCRIPTOR;



/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - ADDRESS BLOCK WINDOW                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the Index of an Address Block Window in a ukProc.
 *
 * Definition of the uKernel C-Type for the Index of an Address Block Window
 *  in a ukProc.
 *
 * The following kind of Address Block can be mapped by the current ukProc in
 *  an Address Block Window:
 *  - Extra Address Block: if Owner ukProc is the current ukProc.
 *  - Shared Buffer: if Managing ukProc is the current ukProc.
 *
 * When an Address Block Window is mapped, the ukProc is allowed to perform
 *  read, and optionally write, operations in the range of address defined
 *  in the Address Block.
 *
 * @implementation As an Address Block Window relies on hardware feature, the
 *  number of Address Block Windows that can be mapped simultaneously is
 *  dependent of the MCU used (and in general directly of the number of memory
 *  regions supported by the MPU in the MCU). This MCU dependent maximum number
 *  is defined in DukADDRESSBLOCKWINDOW_COUNT_MAX.
 *
 * @usage In order to increase ukApp code robustness, it is advised to map an
 *  Address Block Window only during the sequence of code that need to have
 *  access to the mapped Address Block (i.e. perform the mapping just before
 *  the sequence, and releasing the mapping just after).
 *
 * @usage The Index of an Address Block Window shall be in the range:
 *      [0... DukADDRESSBLOCKWINDOW_IDX_MAX].
 */
typedef TukIDX8 TukADDRESSBLOCKWINDOW_IDX;


/* //////////////////////////////////////////////////////////////////////// */
/*                           C-TYPES - MCU REGISTER                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the MCU Register Descriptor.
 *
 * Definition of the uKernel C-Type for the MCU Register Descriptor.
 * This descriptor allows to fully define the characteristics of the access
 *  which can be performed on an MCU Register: the MCU Register address and
 *  which bits in this MCU Register supporting read and write accesses.
 *
 * An MCU Register Descriptor contains the following fields:
 *  - (TukADDRESS32)<MCURegisterAddress>: 32-bit address of the MCU Register.
 *  - (TukBITMASK32)<MCURegisterReadBitmask32>: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be read from the MCU Register.
 *  - (TukBITMASK32)<MCURegisterWriteBitmask32>: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be written in the MCU Register.
 *
 * @usage The access to an MCU Register defined in an MCU Register Descriptor
 *  can be performed through the following uKernel Privileged Services:
 * - ukMCURegisterRead()
 * - ukMCURegisterWrite()
 *
 * @usage All the MCU Registers to which ukApp code can access using dedicated
 *  MCU Register uKernel Privileged Services are predefined in a fixed size
 *  list of MCU Register Descriptors.
 *  This list is part of the ukApp Descriptor (see field
 *  <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR) of the ukApp.
 *  The maximum number of elements in this list is
 *   DukCONFIG_OPTION_UKAPP_MCUREGISTER_DESCRIPTOR_COUNT_MAX.
 *
 * @usage The sole way to have ukApp code access an MCU Register whose access
 *  is restricted to CPU Privileged Execution Mode, is to have it defined in a
 *  MCU Register Descriptor.
 *  A direct access to such MCU Register from ukApp code will trigger an MCU
 *  Exception Fault as ukProcs are running in CPU User Execution Mode: it is a
 *  ukProc Fatal Error, and the uKernel triggers a ukProc Abort with ukProc
 *  Termination Reason DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 */
typedef struct {
        TukADDRESS32    MCURegisterAddress;
        TukBITMASK32    MCURegisterReadBitmask32;
        TukBITMASK32    MCURegisterWriteBitmask32;
    } TukMCUREGISTER_DESCRIPTOR;


/**
 * @brief C-Type for the MCU Register Range Descriptor.
 *
 * Definition of the uKernel C-Type for the MCU Register Range Descriptor.
 * This descriptor allows to fully define the characteristics of the access
 *  which can be performed on the MCU Register which are part of a range: the
 *  first MCU Register address, the last MCU Register address, and which bits
 *  in these MCU Registers support read and write accesses.
 *
 * An MCU Register Descriptor contains the following fields:
 *  - (TukADDRESS32)<MCURegRangeFirstAddress>: 32-bit address of the first
 *   MCU Register in the range.
 *  - (TukADDRESS32)<MCURegRangeLastAddress>: 32-bit address of the last
 *   MCU Register in the range.
 *  - (TukBITMASK32)<MCURegisterReadBitmask32>: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be read from the MCU Registers.
 *  - (TukBITMASK32)<MCURegisterWriteBitmask32>: 32-bit bitmask where each bit
 *   set to 1 corresponds to a bit allowed to be written in the MCU Registers.
 *
 * @usage The access to an MCU Register defined in an MCU Register Descriptor
 *  can be performed through the following uKernel Privileged Services:
 * - ukMCURegisterRead()
 * - ukMCURegisterWrite()
 *
 * @usage All the MCU Registers to which ukApp code can access using dedicated
 *  MCU Register uKernel Privileged Services are predefined in a fixed size
 *  list of MCU Register Descriptors.
 *  This list is part of the ukApp Descriptor (see field
 *  <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR) of the ukApp.
 *  The maximum number of elements in this list is
 *   DukCONFIG_OPTION_UKAPP_MCUREGISTER_DESCRIPTOR_COUNT_MAX.
 *
 * @usage The sole way to have ukApp code access an MCU Register whose access
 *  is restricted to CPU Privileged Execution Mode, is to have it defined in an
 *  MCU Register Descriptor.
 *  A direct access to such MCU Register from ukApp code will trigger an MCU
 *  Exception Fault as ukProcs are running in CPU User Execution Mode: it is a
 *  ukProc Fatal Error, and the uKernel triggers a ukProc Abort with ukProc
 *  Termination Reason DukUKPROC_TERMINATION_REASON_ABORT_MCU_FAULT.
 */
typedef struct {
        TukADDRESS32    MCURegRangeFirstAddress;
        TukADDRESS32    MCURegRangeLastAddress;
        TukBITMASK32    MCURegisterReadBitmask32;
        TukBITMASK32    MCURegisterWriteBitmask32;
    } TukMCUREGRANGE_DESCRIPTOR;


/**
 * @brief C-Type for the MCU Register Access Entry.
 *
 * Definition of the uKernel C-Type for the MCU Register Access Entry.
 * An MCU Register Access Entry contains the information for performing a read
 *  or write access on an MCU Register: the MCU Register address, and the bits
 *  to be read or written, and the value associated to the access.
 *
 * An MCU Register Access Entry contains the following fields:
 *  - (TukADDRESS32)<MCURegisterAddress>: 32-bit address of the MCU Register
 *   to be accessed. This address shall correspond to one of an MCU Register
 *   Descriptor entry in the MCU Register Descriptors list in the ukApp
 *   Descriptor (see field <MCURegisterDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  - (TukBITMASK32)<MCURegisterValueBitmask32>: 32-bit bitmask filtering the
 *   bits accessed in the value of the MCU Register. The contents of this
 *   bitmask depends of the nature of the access:
 *    + Read: Upon a read access, only the bits set in this bitmask will be
 *      significant in the returned value in field <MCURegisterValue32>. The
 *      other bits shall be ignored and are set to null(0).
 *      All the bit(s) set in this bitmask shall also be set in the field
 *      <MCURegisterReadBitmask32> of the MCU Register Descriptor (see
 *      TukMCUREGISTER_DESCRIPTOR) corresponding to the address accessed, else
 *      the read access will be canceled.
 *    + Write: Upon a write access, only the bits set in this bitmask will be
 *      written in the MCU Register by using the corresponding bits in the
 *      given value in field <MCURegisterValue32>. The other bits are ignored
 *      and will not be modified in MCU Register upon the write access.
 *      All the bit(s) set in this bitmask shall also be set in the field
 *      <MCURegisterWriteBitmask32> of the MCU Register Descriptor (see
 *      TukMCUREGISTER_DESCRIPTOR) corresponding to the address accessed, else
 *      the write access will be canceled.
 *  - (TukUINT32)<MCURegisterValue32>: 32-bit value from/to the MCU Register.
 *   The contents of this value depends of the nature of the access:
 *    + Read: This value will be set with the effective contents of the MCU
 *      Register. Only the bit(s) set to 1 in <MCURegisterValueBitmask32> field
 *      are significant, the other bits being set to null(0).
 *      The value returned in this field is computed as this:
 *          <MCURegisterValue32> =
 *              (*MCURegisterAddress) & <MCURegisterValueBitmask32>.
 *    + Write: This value will be used to write in the contents of the MCU
 *      Register. Only the bit(s) set to 1 in <MCURegisterValueBitmask32> field
 *      are effectively written, the other bits remaining unmodified.
 *      The value of the MCU Register is computed as this:
 *          (*MCURegisterAddress) =
 *              ((*MCURegisterAddress) & (~<MCURegisterValueBitmask32>)) |
 *              (<MCURegisterValue32> & <MCURegisterValueBitmask32>).
 *
 * @usage An MCU Register Access Entry is used in the field
 *  <MCURegisterAccessEntryList> of the C-Type TukMCUREGISTER_ACCESS_SET.
 */
typedef struct {
        TukADDRESS32    MCURegisterAddress;
        TukBITMASK32    MCURegisterValueBitmask32;
        TukUINT32       MCURegisterValue32;
    } TukMCUREGISTER_ACCESS_ENTRY;



/**
 * @brief C-Type for the MCU Register Access Set.
 *
 * Definition of the uKernel C-Type for the MCU Register Access Set.
 * An MCU Register Access Set contains the information for performing a read
 *  or write access on a set of MCU Registers: the count of MCU Registers to
 *  access, the array of MCU Register Access Entry describing each access to be
 *  performed.
 *
 * An MCU Register Access Set contains the following fields:
 *  - (TukCOUNT32)<MCURegisterCount32>: 32-bit count of MCU Registers to access.
 *   This count corresponds to the number of MCU Register Access Entry
 *   populated in the <MCURegisterAccessEntryList> field. It shall not exceed
 *   DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX.
 *  - (TukACCESSKEY32)<MCURegisterAccessKey32>: 32-bit Access Key used to
 *   prevent MCU Register access from misuse in ukApp code. It shall be equal
 *   to the value retrieved using uKernel Core Tag Attribute
 *   DukUKCORE_ATTRIBUTE_TAG_MCUREGISTER_ACCESSKEY.
 *  - (TukMCUREGISTER_ACCESS_ENTRY[])<MCURegisterAccessEntryList>: List as a
 *   C-Array of MCU Register Access Entries. Each entry contains the
 *   information for performing the access to a referenced MCU Register. This
 *   List shall contain <MCURegisterCount32> entries.
 *
 * @usage An MCU Register Access Set is used by the uKernel Privileged Services
 *  ukMCURegisterRead() and ukMCURegisterWrite().
 */
typedef struct {
        TukACCESSKEY32                  MCURegisterAccessKey32;
        TukCOUNT32                      MCURegisterCount32;
        TukMCUREGISTER_ACCESS_ENTRY     MCURegisterAccessEntryList[
                                           DukCONSTRAINT_MCUREGISTER_ACCESS_COUNT_MAX];
    } TukMCUREGISTER_ACCESS_SET;



/* //////////////////////////////////////////////////////////////////////// */
/*                              C-TYPES - DMA STREAM                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the DMA Stream Label.
 *
 * Definition of the uKernel C-Type for the DMA Stream Label.
 *
 * A DMA Stream Label allows to reference unambiguously a DMA Stream in the
 *  ukApp where it is defined. It is present in each DMA Stream Descriptor
 *  entry defined in ukApp Descriptor (see TukDMAS_DESCRIPTOR).
 *
 * @implementation The uKernel checks during its initialization that all the
 *  DMA Stream Label values set in the DMA Stream defined in the ukApp are
 *  unique (a ukApp cannot have several DMA Stream defined with the same
 *  label; same label can however be reused in other ukApps). If the check
 *  fails, the ukApp Descriptor is considered as invalid.
 *
 * @usage The advantage of using a DMA Stream Label is that it allows to
 *  reference unambiguously a DMA Stream defined in a ukApp even in case
 *  of change (upon ukApp updates or evolutions) of its DMA Stream Descriptor
 *  index in ukApp Descriptor.
 *
 * @usage In the Owner ukProc of a DMA Stream (which is the ukProc instantiated
 *  from the ukApp where the DMA Stream is defined), the DMA Stream Identifier
 *  of the DMA Stream can be retrieved from its DMA Stream Label by using
 *  ukDMAStreamGetIDFromLabel().
 */
typedef TukUKAPP_LABEL_LOCAL TukDMAS_LABEL;

/**
 * @brief C-Type for the DMA Stream Identifier.
 *
 * Definition of the uKernel C-Type for the DMA Stream Identifier.
 * A DMA Stream Identifier is used to reference unambiguously a DMA Stream
 *  defined in the ukApp of the current ukProc.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...16] Tag: This field contains the DMA Stream Identifier Tag
 *   used to prevent misuse of this value (see DukDMAS_ID_TAG).
 *  - [07...00] Reference: This field contains the reference (index) used to
 *   identify the DMA Stream.
 *
 * The C-Type DMA Stream Identifier is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |      Bit number       |                   Description                    |
 * |31...16|15...08|07...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | ttttt |       |       | Tag (16-bit)                                     |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |   0   |       | RFU (8-bit)                                      |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | Reference (8-bit)                                |
 * |-------|-------|----------------------------------------------------------|
 *
 * @note All the DMA Stream defined in a ukApp are set in a fixed size list
 *  of DMA Stream Descriptors. This list is part of the ukApp Descriptor (see
 *  field <DMAStreamDescriptorList> in TukUKAPP_DESCRIPTOR).
 *
 * @usage A DMA Stream Identifier should be built only from:
 *  - MukDMAS_ID_BUILD().
 *  - ukDMAStreamGetIDFromLabel().
 */
typedef TukUINT32 TukDMAS_ID;

/**
 * @brief C-Type for the DMA Stream Attributes.
 *
 * Definition of the uKernel C-Type for the DMA Stream Attributes.
 * The DMA Stream Attributes allow to define the characteristics of the DMA
 *  transfer that have to be configured in the DMA Engine in regards of the
 *  DMA Stream defined.
 *
 * A DMA Stream Attributes contains the following fields:
 *  - DMA Stream Priority
 *
 * #NOTYETSUPPORTED (null value shall be used).
 */
typedef TukUINT32 TukDMAS_ATTRIBUTES;


/* //////////////////////////////////////////////////////////////////////// */
/*                          C-TYPES - DMA DESCRIPTOR                        */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief C-Type for the Hardware Identifier of an DMA Engine.
 *
 * Definition of the uKernel C-Type for the Hardware Identifier of a DMA Engine.
 * A DMA Engine is the sub-part of a DMA Controller Peripheral that is in
 *  charge of processing the selected DMA Stream (it is sometimes named also a
 *  'DMA Channel').
 *
 * This Hardware Identifier allows to refer a DMA Engine in the MCU, by
 *  selecting the following elements:
 *  - The DMA Controller Peripheral, when several are present.
 *  - The DMA Engine inside the selected controller.
 *
 * @implementation The number of DMA Engines supported in the DMA Controllers
 *  is Platform specific and depends of the MCU Family used (see Platform's
 *  MCU Family specific documentation).
 *
 * @implementation This identifier is Platform's MCU Family specific.
 *  In general, this identifier corresponds to the suffix number of the
 *  DMA Engine Hardware Peripheral used in the MCU documentation.
 *
 * @usage This identifier is used only in the C-Type structure
 *  TukDMAS_DESCRIPTOR.
 */
typedef TukUINT16 TukDMAS_ENGINE_HW_ID;

/**
 * @brief C-Type for the Hardware Identifier of a DMA Request used by a DMA
 *  Stream.
 *
 * Definition of the uKernel C-Type for the Hardware Identifier of a DMA
 *  Request used by a DMA Stream.
 *
 * This Hardware Identifier allows to select the origin of the MCU internal
 *  event that will trigger each DMA transfer request:
 *  - For a DMA transfer request implying an Hardware Peripheral inside the
 *  MCU, the DMA transfer request shall be synchronized with the Hardware
 *  Peripheral for reading or writing data. This synchronization is made by
 *  using for the triggering a specific DMA Request event attached to the
 *  used Hardware Peripheral. The value to use for selecting the proper DMA
 *  Request event attached to the given Hardware Peripheral is defined by the
 *  MCU vendor. This value may sometimes also depend of the DMA Controller and
 *  of its DMA Stream Engine used.
 *  - For a DMA transfer from internal memory to internal memory, no
 *   additional synchronization is need: the special reserved value
 *   DukDMAS_REQUEST_HW_ID_NONE shall be used.
 *
 * @implementation This identifier is Platform's MCU Family specific.
 *  The value to use for this identifier has to be found in the MCU
 *  documentation (often in a table whose name should be something like
 *  'DMA Channel Matrix').
 *
 * @usage This identifier is used only in the C-Type structure
 *  TukDMAS_DESCRIPTOR.
 */
typedef TukUINT8 TukDMAS_REQUEST_HW_ID;


/**
 * @brief C-Type for the DMA Stream Descriptor.
 *
 * Definition of the uKernel C-Type for the DMA Stream Descriptor.
 * This descriptor allows to fully define the characteristics of a DMA Stream
 *  that can be used by a ukApp.
 *
 * A DMA Stream Descriptor contains the following fields:
 *  - (TukDMAS_LABEL)<DMAStreamDescriptorLabel>: DMA Stream Label associated to
 *   the defined DMA Stream. This label value shall be unique among all DMA
 *   Streams defined in a ukApp (but same value can be shared by different
 *   ukApps). This unicity allows this label to be used to reference a DMA
 *   Stream unambiguously in the ukApp, and to use it to retrieve its DMA
 *   Stream Identifier (see ukDMAStreamGetIDFromLabel()).
 *  - (TukDMAS_ATTRIBUTES)<DMAStreamAttributes>: Attributes defining the usage
 *   policy for the DMA Stream (see TukDMAS_ATTRIBUTES for details).
 *  - (TukDMAS_ENGINE_HW_ID)<DMAStreamEngineHWIdentifier>: DMA Engine Hardware
 *   Identifier to use for the DMA Stream. This Identifier allows to select
 *   which DMA controller and which of its DMA Stream Engine to use.
 *  - (TukDMAS_REQUEST_HW_ID)<DMAStreamSourceRequestHWIdentifier>: DMA Request
 *   HW Identifier to use for the source of the DMA Stream. This Identifier
 *   allows to select the origin of the MCU internal event that will trigger
 *   each DMA transfer request when reading data.
 *  - (TukDMAS_REQUEST_HW_ID)<DMAStreamDestinationRequestHWIdentifier>: DMA
 *   Request HW Identifier to use for the destination of the DMA Stream. This
 *   Identifier allows to select the origin of the MCU internal event that will
 *   trigger each DMA transfer request when writing data.
 *  - (TukADDRESSBLOCK_LABEL)<DMAStreamSourceAddressBlockLabel>: Address Block
 *   Label referencing the Address Block source of the DMA Stream. The memory
 *   range from which are read data by the DMA Stream shall be fully contained
 *   in this Address Block.
 *  - (TukADDRESSBLOCK_LABEL)<DMAStreamDestinationAddressBlockLabel>: Address
 *   Block Label referencing the Address Block destination of the DMA Stream.
 *   The memory range from which are written data by the DMA Stream shall be
 *   fully contained in this Address Block.
 *
 * @usage All the DMA Streams that a ukProc can instantiate are predefined
 *  as a fixed size list of DMA Stream Descriptors.
 *  This list is part of its ukApp Descriptor (see field
 *  <DMAStreamDescriptorList> in TukUKAPP_DESCRIPTOR).
 *  The maximum number of elements in this list, corresponding to the maximum
 *  number of DMA Streams that can be predefined by a ukApp, is
 *  DukCONFIG_OPTION_UKAPP_DMAS_DESCRIPTOR_COUNT_MAX.
 */
typedef struct {
        TukDMAS_LABEL                 DMAStreamLabel;
        TukDMAS_ATTRIBUTES            DMAStreamAttributes;
        TukDMAS_ENGINE_HW_ID          DMAStreamEngineHWIdentifier;
        TukDMAS_REQUEST_HW_ID         DMAStreamSourceRequestHWIdentifier;
        TukDMAS_REQUEST_HW_ID         DMAStreamDestinationRequestHWIdentifier;
        TukADDRESSBLOCK_LABEL         DMAStreamSourceAddressBlockLabel;
        TukADDRESSBLOCK_LABEL         DMAStreamDestinationAddressBlockLabel;
    } TukDMAS_DESCRIPTOR;


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-TYPES - DMA STREAM INSTANCE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type for the DMA Stream Instance Identifier (DMAS IID).
 *
 * Definition of the uKernel C-Type for the DMA Stream Instance Identifier
 *  (or DMAS IID).
 *
 * An DMA Stream Instance Identifier is a value returned upon the hardware
 *  setup of a DMA Stream in a DMA Controller (see
 *  ukdevDMAStreamInstanceCreate()).
 *  This value has then to be used to reference this DMA Stream Instance when
 *  performing actions on the DMA Stream.
 *
 * @implementation At a given moment, only one DMA Stream Instance can be
 *  created for the selected DMA Engine in DMA Stream Descriptor (see
 *  <DMAStreamEngineHWIdentifier> field in TukDMAS_DESCRIPTOR).
 */
typedef TukUINT32 TukDMAS_IID;


/**
 * @brief C-Type for the current State of an DMA Stream.
 *
 * Definition of the uKernel C-Type for the State of an DMA Stream.
 *
 * The state of an DMA Stream allows to check notably if:
 *  - The DMA Stream Instance has been created and properly configured.
 *  - A transfer has been started and is finished.
 *  - An error has occurred during the last transfer started.
 *
 * @implementation The special value DukDMAS_STATE_MEANINGLESS is
 *  returned in case of error.
 *
 * @usage See C-Constants DukDMAS_STATE_xxxx for defined state values.
 *
 * @usage A State value shall be interpreted ONLY if the flag
 *  DukDMAS_STATE_MEANINGFUL_FLAG is set.
 */
typedef TukUINT32 TukDMAS_STATE;


/**
 * @brief C-Type for the DMA Stream Transfer Mode.
 *
 * Definition of the uKernel C-Type for the DMA Stream Transfer Mode.
 * A DMA Stream Transfer Mode is used to setup a transfer, by allowing to
 *  configure the source and destination streams (auto-increment, data size)
 *  and the transfer engine behavior (circular, ...).
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [24...16] Tag: This field contains setup information for the transfer
 *   engine of the DMA Stream.
 *  - [15...08] Destination: This field contains the setup information
 *   (auto-increment, data size) for the destination of the DMA Stream.
 *  - [07...00] Source: This field contains the setup information
 *   (auto-increment, data size) for the source of the DMA Stream.
 *
 * The C-Type DMA Stream Transfer Mode is structured as this:
 * |-----------------------------------|--------------------------------------|
 * |           Bit number              |              Description             |
 * | 31...24| 23...16| 15...08| 07...00|                                      |
 * |:------:|:------:|:------:|:------:|--------------------------------------|
 * |  xxxxx |        |        |        | RFU (8-bit)                          |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |  xxxxx |        |        | Engine (8-bit)                       |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |  xxxxx |        | Destination (8-bit)                  |
 * |--------|--------|--------|--------|--------------------------------------|
 * |        |        |        |  xxxxx | Source (8-bit)                       |
 * |--------|--------|--------|-----------------------------------------------|
 */
typedef TukUINT32 TukDMAS_TRANSFER_MODE;


/**
 *
 * @brief C-Type for the DMA Stream Instance Information.
 *
 * Definition of the uKernel C-Type for the Information associated to an
 *  DMA Stream Instance.
 *
 * The information provided are the following:
 *  - DMAStreamState: Current DMA Stream State (see TukDMAS_STATE).
 *  - DMAStreamTransferMode: Attributes of the Address Block in
 *   the context of its Managing ukProc (see TukDMAS_TRANSFER_MODE).
 *  - DMAStreamTransferSourceAddress: Source Address that has been given upon
 *   last invocation of ukDMAStreamInstanceTransferSetup(). The value of this
 *   address is not affected by the count of data transferred.
 *  - DMAStreamTransferDestinationAddress: Destination Address that has been
 *   given upon last invocation of ukDMAStreamInstanceTransferSetup(). The
 *   value of this address is not affected by the count of data transferred.
 *  - DMAStreamTransferCountCurrent: Current count (in bytes) of data
 *   transferred during the current or last DMA Stream transfer.
 *  - DMAStreamTransferCountCumulated: Current cumulated count (in bytes) of
 *   all DMA Stream transfers. This count is computed by adding the count of
 *   previous DMA Stream transfer that have been over to the one currently
 *   ongoing (if there is one).
 */
typedef struct {
    TukDMAS_STATE             DMAStreamState;
    TukDMAS_TRANSFER_MODE     DMAStreamTransferMode;
    TukADDRESS32              DMAStreamTransferSourceAddress;
    TukADDRESS32              DMAStreamTransferDestinationAddress;
    TukLENGTH32               DMAStreamTransferCountCurrent;
    TukLENGTH32               DMAStreamTransferCountCumulated;
} TukDMAS_TRANSFER_INFO;


/**
 *
 * @brief C-Type for the DMA Stream Instance Information.
 *
 * Definition of the uKernel C-Type for the Information associated to an
 *  DMA Stream Instance.
 *
 * The information provided are the following:
 *  - DMAStreamLabel: DMA Stream Label set in the DMA Stream Descriptor.
 *  - DMAStreamSourceAddress: Source address of the Address Block referenced as
 *   DMA Stream source in the DMA Stream Descriptor.
 *  - DMAStreamSourceSize: Source size of the Address Block referenced as
 *   DMA Stream source in the DMA Stream Descriptor.
 *  - DMAStreamDestinationAddress: Destination address of the Address Block
 *   referenced as DMA Stream destination in the DMA Stream Descriptor.
 *  - DMAStreamDestinationSize: Destination size of the Address Block
 *   referenced as DMA Stream destination in the DMA Stream Descriptor.
 */
typedef struct {
    TukDMAS_LABEL             DMAStreamLabel;
    TukADDRESS32              DMAStreamSourceAddress;
    TukLENGTH32               DMAStreamSourceSize;
    TukADDRESS32              DMAStreamDestinationAddress;
    TukLENGTH32               DMAStreamDestinationSize;
} TukDMAS_INFO;


/* //////////////////////////////////////////////////////////////////////// */
/*                             C-TYPES - WATCHDOG                           */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Watchdog Attributes.
 *
 * Definition of the uKernel C-Type for the Watchdog Attributes.
 * The Watchdog attributes allow to define when started various elements in its
 *  configuration (stoppable, ...) and behaviours.
 *
 * The Watchdog Attributes contains the following flags for its configuration:
 *  - DukWATCHDOG_ATTRIBUTES_CONFIG_STOPPABLE_FLAG: The Watchdog can be stopped
 *   (and then restarted with a different configuration).
 */
typedef TukUINT8 TukWATCHDOG_ATTRIBUTES;


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - RANDOM GENERATION                      */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for a Random Generator Identifier.
 *
 * Definition of the uKernel C-Type for a Random Generator Identifier.
 * A Random Generator Identifier allows to select the nature (entropy level,
 *  recommended usages, ...) of Random Generator to be used for generating
 *  random values.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...08] <Tag>: This field contains the Random Generator Identifier Tag
 *   used to prevent misuse of this value (see DukRNG_ID_TAG).
 *  - [07...00] <Reference>: This field contains the reference used to identify
 *   the Random Generator.
 *
 * The C-Type Random Generator Identifier is structured as this:
 * |----------------|---------------------------------------------------------|
 * |     Bit number |                       Description                       |
 * |31...08| 07...00|                                                         |
 * |:-----:|:------:|---------------------------------------------------------|
 * | xxxxx |        | Tag (24-bit)                                            |
 * |-------|--------|---------------------------------------------------------|
 * |       | xxxxx  | Reference (8-bit)                                       |
 * |-------|--------|---------   ---------------------------------------------|
 *
 * The following Random Identifier are defined:
 *  - DukRNG_ID_PRNG: Pseudo Random Number Generator.
 *  - DukRNG_ID_TRNG: True Random Number Generator.
 *  - DukRNG_ID_TRNG_AIS31: True Random Number Generator compliant AIS31.
 *  - DukRNG_ID_CPRNG: Cryptographic Pseudo Random Number Generator
 *  - DukRNG_ID_RNGFC: Random Number Generator For Cryptography.
 *
 * @warning The performance of a Random Generator (entropy, quality tests
 *  passed, generation tile) depends of the algorithm and/or the hardware
 *  part(s) in the MCU and the Platform used for performing the generation.
 *  Thus the nature of the Random Generator used shall be carefully selected by
 *  the ukApp Developer in regards of targeted usage and level of security
 *  required.
 *
 * @implementation All the defined Random Generator may not be supported: some
 *  Random Generator are based on the presence of specific hardware part(s)
 *  that may not be present in used MCUs or Platform. See uKernel Target
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
 */
typedef TukUINT32   TukRNG_ID;

/**
 * @brief uKernel C-Type for a 64-bit Random Value.
 *
 * Definition of the uKernel C-Type for a 64-bit Random Value.
 *
 * @implementation The 64-bit size has been chosen to provide a good level of
 *  entropy for most security related usages, while still taking a reasonable
 *  amount of time to be generated.
 */
typedef TukUINT64   TukRANDOM_VALUE64;



/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - MCU CLOCKS MANAGEMENT                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Index of a set of MCU Clocks.
 *
 * Definition of the uKernel C-Type for the Index of a set of MCU Clocks.
 * The MCU clock configuration can be configured only from a predefined list of
 *  sets defined in the configuration of a uKernel Target. This index allows
 *  to select which set to use among this list (see
 *  DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_LIST).
 *
 * @implementation The entry index 0 is the default one used during uKernel
 *  Initialization. To change MCU Clocks configuration, another entry index
 *  can afterwards be selected by a ukProc with the appropriate credentials
 *  using uKernel Services (see ukPlatformSetAttribute() and
 *  DukPLATFORM_ATTRIBUTE_TAG_MCU_CLOCKS_SET_IDX).
 *
 * @usage The Index of a set of MCU Clocks shall be in the range:
 *      [0... (DukCONFIG_OPTION_HW_MCU_CLOCKS_SET_COUNT - 1)].
 */
typedef TukIDX8 TukMCU_CLOCKS_SET_IDX;



/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - UKERNEL IMAGE UPDATE                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the uKernel Image Update Operation.
 *
 * Definition of the uKernel C-Type for the uKernel Image Update Operation.
 * The uKernel Image Update Operation allows to:
 *  - Specify which part of the uKernel Image has to be updated.
 *  - Report that the updated part is validated (i.e. it behaves properly).
 *  - Unlock the uKernel Image Update Storage for allowing a new update.
 *
 * The uKernel Image Update Operation supports the following values:
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPP.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKAPPS_BUNDLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_UKERNEL_CORE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_REPLACE_WHOLE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_VALIDATE.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_ROLLBACK.
 *  - DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE.
 *
 * @implementation In function of the uKernel Image Update Operation, some
 *  additional parameters may be required (see documentation of
 *  DukUKERNEL_IMAGE_UPDATE_NATURE_xxx for details).
 *
 * @usage A uKernel Image Update Operation is performed by using
 *  ukUKImageUpdateOperate().
 */
typedef TukUINT32 TukUKERNEL_IMAGE_UPDATE_OPERATION;


/**
 * @brief uKernel C-Type for the uKernel Image Update Attributes.
 *
 * Definition of the uKernel C-Type for the uKernel Image Update Attributes.
 * The uKernel Image Update Attributes allows to define the policy to use
 *  for performing the update (check of integrity of the provided image,
 *  keeping previous version to allow roll-back if necessary).
 *
 * The uKernel Image Update Attributes is composed as a set of the following
 *  flags:
 *  - DukUKERNEL_IMAGE_UPDATE_ATTRIBUTES_IMAGE_CHECK_SHA256_FLAG: Before
 *   swapping to the updated uKernel Image, a SHA256 computed on uKernel Image
 *   Update Storage area to use for the operation and is verified against a
 *   given expected value.
 *  - DukUKERNEL_IMAGE_UPDATE_ATTRIBUTES_IMAGE_KEEP_PREVIOUS_FLAG: The current
 *   image of the updated part is swapped with the new one in the uKernel Image
 *   Update Storage. The current image becomes then the previous image, and is
 *   kept protected in the uKernel Image Update Storage till a request to
 *   remove it is done (see DukUKERNEL_IMAGE_UPDATE_OPERATION_UNLOCK_STORAGE).
 */
typedef TukUINT16 TukUKERNEL_IMAGE_UPDATE_ATTRIBUTES;


/* //////////////////////////////////////////////////////////////////////// */
/*                            C-TYPES - DEBUG TRACE                         */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Attributes associated to a Debug Trace.
 *
 * Definition of the uKernel C-Type for the Attributes value associated to
 *  a Debug Trace.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [15...08] <Nature>: Field of C-Type TukDEBUG_TRACE_NATURE
 *   indicating the nature (information, configuration, error, ...) of the
 *   Debug Trace.
 *  - [07...04] <Mode>: Field of C-Type TukDEBUG_TRACE_MODE
 *   indicating the mode to use for printing the Debug Trace (automatic adding
 *   of newline, etc...).
 *  - [03...00] <Verbosity>: Field of C-Type TukDEBUG_TRACE_VERBOSITY
 *   indicating the level of verbosity of the Debug Trace.
 *
 * The C-Type Debug Trace Attributes is structured as this:
 * |-----------------------|--------------------------------------------------|
 * |      Bit number       |                   Description                    |
 * |15...08|07...04|03...00|                                                  |
 * |:-----:|:-----:|:-----:|--------------------------------------------------|
 * | xxxxx |       |       | <Nature> (8-bit)                                 |
 * |-------|-------|-------|--------------------------------------------------|
 * |       | xxxxx |       | <Mode> (4-bit)                                   |
 * |-------|-------|-------|--------------------------------------------------|
 * |       |       | xxxxx | <Verbosity> (4-bit)                              |
 * |-------|-------|----------------------------------------------------------|
 *
 * @usage The Debug Trace Attributes value is used when printing a Debug Trace
 *  using a uKernel Service to qualify the kind and level of detail of the
 *  information contained in the Debug Trace, as well as the way to print it.
 *
 * @usage The C-Macro MukDEBUG_TRACE_ATTRIBUTES_BUILD should be used for
 *  building a Debug Trace Attributes value.
 */
typedef TukUINT16 TukDEBUG_TRACE_ATTRIBUTES;


/**
 * @brief uKernel C-Type for the Nature of a Debug Trace.
 *
 * Definition of the uKernel C-Type for the Nature of a Debug Trace.
 * The Nature of a Debug Trace allows to specify the kind of information
 *  reported by the Debug Trace (statistics, configuration, error, ...).
 *
 * @note The following Debug Trace Nature flags are defined:
 *  - DukDEBUG_TRACE_NATURE_INFO_FLAG: Various information on current execution.
 *  - DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG: Diagnostic information on internal
 *   intermediate computation or state.
 *  - DukDEBUG_TRACE_NATURE_CONFIG_FLAG: Configuration information.
 *  - DukDEBUG_TRACE_NATURE_STAT_FLAG: Statistical information.
 *  - DukDEBUG_TRACE_NATURE_WARNING_FLAG: Warning spotted during execution
 *  (possible inconsistency, ...).
 *  - DukDEBUG_TRACE_NATURE_ERROR_FLAG: Error during execution.
 *  - DukDEBUG_TRACE_NATURE_ACTIVITY_FLAG: Activity occurring in ukProc or
 *   uKernel.
 *
 * @usage The Debug Trace Nature can be used either:
 *  - As part of Debug Trace Attributes value when printing a Debug Trace using
 *   a uKernel Service. It allows then to define the kind of information
 *   contained in the printed Debug Trace. Note that a printed Debug Trace can
 *   be defined as being of one and only one kind, and thus only one Nature
 *   flag (see DukDEBUG_TRAC_NATURE_xxx_FLAG) can be set there (else it will be
 *   considered as invalid).
 *  - As part of the ukApp configuration (see field <DebugTraceNatureFilter> in ukApp
 *   Descriptor). It defines there the different kinds of information allowed
 *   to be printed for the given ukApp, each corresponding Nature flags being
 *   set for each kind allowed (see DukDEBUG_TRACE_NATURE_xxx_FLAG). The Nature
 *   field value acts here as a filter mask: upon a printing request of a Debug
 *   Trace, only the ones with a Nature flag (provided in the associated Debug
 *   Trace Attributes parameter given to the uKernel Service), which is also
 *   set in the ukApp configuration Nature field, will be printed by the
 *   uKernel (if not printed, the printing request is silently discarded).
 */
typedef TukUINT8 TukDEBUG_TRACE_NATURE;


/**
 * @brief uKernel C-Type for the Mode of a Debug Trace.
 *
 * Definition of the uKernel C-Type for the Mode of a Debug Trace.
 * The Mode of a Debug Trace allows to specify some additional treatments to
 *  apply when printing the Debug Trace (automatic new line at the end of a
 *  print, adding time stamped prefix, ...).
 *
 * @note The following Debug Trace Mode flags are defined:
 *  - DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG: A new line character ('\n') is
 *   added at the end of the printed Debug Trace.
 *  - DukDEBUG_TRACE_MODE_TIMESTAMP_PREFIX_FLAG: A time stamp, corresponding to
 *   the uKernel Uptime of when the Debug Trace is printed before the printing
 *   of the Debug Trace.
 *
 * @usage The Debug Trace Mode can be used to ease the management and
 *  readability of printed Debug Traces, by spacing and adding information of
 *  the resulting print.
 */
typedef TukUINT8 TukDEBUG_TRACE_MODE;


/**
 * @brief uKernel C-Type for the Verbosity of a Debug Trace.
 *
 * Definition of the uKernel C-Type for the Verbosity of a Debug Trace.
 * The Verbosity of a Debug Trace is a level giving an estimation on the
 *  quantity of details provided:
 *   - When printing a Debug Trace, the more detailed information it contains,
 *    the higher this level has to be.
 *   - In ukApp configuration: The higher is the level, the more detailed
 *    information will be allowed to be printed (and thus the amount of printed
 *    data will be important).
 *
 * @note The following Debug Trace Verbosity levels are defined:
 *  - DukDEBUG_TRACE_VERBOSITY_DISABLED
 *  - DukDEBUG_TRACE_VERBOSITY_DEFAULT
 *  - DukDEBUG_TRACE_VERBOSITY_FINE
 *  - DukDEBUG_TRACE_VERBOSITY_FINER
 *  - DukDEBUG_TRACE_VERBOSITY_FINEST
 *
 * @usage The Debug Trace Verbosity level can be used either:
 *  - When printing a Debug Trace using a uKernel Service, as part of Debug
 *   Trace Attributes value. It allows then to specify the level of Verbosity,
 *   which corresponds to the level of details contained in the information
 *   provided by the Debug Trace to print.
 *  - In ukApp configuration (see field <DebugTraceVerbosityFilter> in
 *   ukApp Descriptor). It defines there the maximal level of Verbosity allowed
 *   to be printed for each ukApp (i.e. the maximum level of details to be
 *   printed). Upon a printing request of a Debug Trace, only a Debug Trace
 *   printing request with a Verbosity level (provided in the given Debug
 *   Trace Attributes parameter) that is lower or equal to the level set in
 *   the ukApp configuration Verbosity field will be printed by the uKernel
 *   (if not printed the request is silently discarded).
 *
 * @usage In the documentation of the C-Constant definitions of Debug Trace
 *  Verbosity (DukDEBUG_TRACE_VERBOSITY_xxx), indications are given on the
 *  possible associated usage in the ukApp code. These are only
 *  recommendations and it is up to each ukApp Developer to decide how to
 *  manage the different levels of Debug Trace Verbosity in function of the
 *  information it wants to trace when debugging.
 *
 * @usage The Debug Trace Verbosity values shall be in the range
 *  [DukDEBUG_TRACE_VERBOSITY_DISABLED...DukDEBUG_TRACE_VERBOSITY_MAX].
 */
typedef TukUINT8 TukDEBUG_TRACE_VERBOSITY;


/**
 * @brief uKernel C-Type for the Debug Trace Cursor Position.
 *
 * Definition of the uKernel C-Type for the Debug Trace Cursor Position.
 * This C-Type allows to retrieve the current cursor position of all the
 *  information printed on the Debug Trace since the start of the current
 *  uKernel Session.
 *
 * This C-Type is a combined C-type, built from the following fields (bit
 *  ranges of each field is indicated between brackets '[]'):
 *  - [31...10] <LineNumber>: Field containing the current line number of the
 *   cursor in the Debug Trace since the start of the current uKernel Session.
 *   First line number is 1.
 *  - [09...00] <Column>: Field containing the current column position of the
 *   cursor on the current line in the Debug Trace.
 *   The column is in the range
 *      [1 ... DukCONFIG_OPTION_DEBUG_TRACE_LINE_COLUMN_WRAP].
 *
 * The C-Type Debug Trace Cursor Position is structured as this:
 * |---------------|----------------------------------------------------------|
 * |  Bit number   |                       Description                        |
 * |31...10|09...00|                                                          |
 * |:-----:|:-----:|----------------------------------------------------------|
 * | xxxxx |       | <LineNumber> (22-bit)                                    |
 * |-------|-------|----------------------------------------------------------|
 * |       | xxxxx | <Column> (10-bit)                                        |
 * |-------|-------|----------------------------------------------------------|
 *
 * @usage The Debug Trace Cursor Position can be used to ease the printing of
 *  specific format (table), or to detect if other information have been
 *  printed on the Debug Trace by another uKernel Entity.
 *
 * @usage The C-Macro MukVAL_FIELD_VALUE_GET should be used for retrieving the
 *  fields composing the Debug Trace Cursor Position.
 */
typedef TukUINT32 TukDEBUG_TRACE_CURSOR_POSITION;


/* //////////////////////////////////////////////////////////////////////// */
/*                             C-TYPES - DEBUG LED                          */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type for the Debug LED Index.
 *
 * Definition of the uKernel C-Type for the Index referencing a Debug LED.
 * The Debug LED Index allows to select which one from the available Debug LED
 * has to be used for reporting debug information using a chosen blinking
 * pattern.
 *
 * @note The way Debug LED are connected to the Platform and to which LED of
 *  the board or LED display dedicated extension board they correspond is
 *  specific to the chosen Platform and to the uKernel Target (see uKernel
 *  Target dedicated documentation for more information).
 *
 * @usage The Debug LED Index values shall be in the range
 *  [0... (DukCONFIG_OPTION_HW_DEBUG_LED_COUNT - 1)].
 */
typedef TukIDX8   TukDEBUG_LED_IDX;

/**
 * @brief uKernel C-Type for the blinking Pattern of a Debug LED.
 *
 * Definition of the uKernel C-Type for the blinking Pattern of a Debug LED.
 * The blinking Pattern allows to define the sequence of blinking of a Debug
 *  LED.
 *
 * The Debug LED blinking pattern is applied as follows:
 *  - Each time a blinking period is over, the uKernel blinking counter
 *   (internal uKernel value global to all ukProcs) is incremented modulo 32
 *   (thus its range is [0 ... 31]). Its value is set to null upon the start
 *   of a uKernel Session.
 *  - The uKernel blinking counter is then used as bit number in the Debug
 *   LED blinking Pattern value (counter value 0 corresponds to the rightmost
 *   bit of the pattern value) to retrieve the active bit for the Debug LED.
 *  - The active bit retrieved is used for setting the Debug LED state
 *    (0: off; 1: on).
 *
 * Example:
 *  0b1111...1111: Debug LED always ON
 *  0b0000...0000: Debug LED always OFF
 *  0b0101...0101: Debug LED blinking at fast speed
 *  0b0011...0011: Debug LED blinking at medium speed
 *  0b0000...0001: Debug LED with single Flash and long dark period
 *
 * @note The following Debug LED blinking Pattern values are predefined:
 *  - DukDEBUG_LED_PATTERN_ON: Debug LED always ON
 *  - DukDEBUG_LED_PATTERN_OFF: Debug LED always OFF
 *  - DukDEBUG_LED_PATTERN_BLINK_FAST: Debug LED blinking at fast speed
 *  - DukDEBUG_LED_PATTERN_BLINK_MEDIUM: Debug LED blinking at medium speed.
 *  - DukDEBUG_LED_PATTERN_BLINK_SLOW: Debug LED blinking at slow speed.
 *  - DukDEBUG_LED_PATTERN_FLASH_SHORT: Debug LED emitting one short flash.
 *  - DukDEBUG_LED_PATTERN_FLASH_LONG: Debug LED emitting one long flash.
 * The predefined Debug LED blinking Pattern listed above have been defined
 *  only for convenience. The ukApp developer can build its own desired Debug
 *  LED blinking Pattern by setting accordingly the bits in the blinking
 *  pattern.
 *
 * @implementation The blinking period value is defined by uKernel Option
 *  DukCONFIG_OPTION_DEBUG_LED_BLINKING_PERIOD_us. The blinking period is
 *  checked to be over only upon each uKernel SysTick.
 */
typedef TukUINT32 TukDEBUG_LED_PATTERN;


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - UKAPP DESCRIPTOR                       */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief uKernel C-Type defining the structure of a ukApp Descriptor.
 *
 * Definition of the uKernel C-Type for a ukApp Descriptor.
 * This C-Type defines the structure that is used by the uKernel during its
 *  Initialization to identify, initialize and configure a ukApp part of the
 *  ukApps Bundle.
 *
 * See "ukapp/include/config/ukapp_config_descriptor.h" include file in a ukApp
 *  project for a description of the contents of each field.
 *
 * @usage A constant C-Variable GKukappApplicationDescriptor, strictly private
 *  to each ukApp, is defined with this C-Type structure. This constant
 *  C-Variable is placed at the very beginning of the ukApp Code Block.
 *  It allows the uKernel during initialization to spot the presence of a valid
 *  ukApp inside the ukApps Bundle Address Block.
 */
typedef const struct {
    TukMAGIC64                          UKAppDescriptorMagicStart64;

    TukVERSION                          UKAppDescriptorVersion;

    TukUINT32                           PaddingVariability[2];

    TukVERSION                          ReleaseuKernelVersion;
    TukCUSTOMER_CONFIG                  ReleaseCustomerConfiguration;
    TukMCU_ID_bv                        ReleaseMCUDeviceIdentifier;

    TukADDRESS32                        MemoryRegionCodeAddressStart;
    TukLENGTH32                         MemoryRegionCodeSize;
    TukLENGTH32                         MemoryRegionCodeExecutableSize;
    TukLENGTH32                         MemoryRegionCodeConstantSize;
    TukADDRESS32                        MemoryRegionDataVolatileAddressStart;
    TukLENGTH32                         MemoryRegionDataVolatileSize;
    TukLENGTH32                         MemoryRegionDataVolatileSharedUKSVCSize;
    TukLENGTH32                         MemoryRegionDataVolatileVarInitSize;
    TukADDRESS32                        MemoryRegionDataVolatileVarInitLoadAddress;
    TukLENGTH32                         MemoryRegionDataVolatileVarNullSize;
    TukLENGTH32                         MemoryRegionDataVolatileStackSize;
    TukADDRESS32                        MemoryRegionDataPersistentAddressStart;
    TukLENGTH32                         MemoryRegionDataPersistentSize;

    TukADDRESS32                        UKAppEntryPointMainAddress;
    TukADDRESS32                        UKAppEntryPointCleanupAddress;
    TukADDRESS32                        UKAppEntryPointExceptionAddress;
    TukADDRESS32                        UKAppEntryPointReturnAddress;
    TukADDRESS32                        UKAppEntryPointUKernelManager;

    TukNTSTRING_CHAR                    NameNTString[DukCONFIG_OPTION_UKAPP_NAME_STRING_LENGTH_MAX + 1U];
    TukUKAPP_AUID                       AUID;
    TukVERSION                          Version;

    TukUKAPP_PROFILE                    Profile;

    TukUKAPP_ASID                       ParentASID;

    TukSCHEDULING_PRIORITY              SchedulingPriorityBase;
    TukSCHEDULING_TIME_QUANTUM_systick  SchedulingTimeQuantumAllocated_systick;
    TukSCHEDULING_PRIORITY              UKProcExceptionSchedulingPriority;
    TukSCHEDULING_TIME_QUANTUM_systick  UKProcExceptionSchedulingTimeQuantumAllocated_systick;

    TukBITMASK64                        UKPrivilegedServicesAuthorizedBitMask64;

    TukCOUNT8                           PIRQMCUIndexAuthorizedCount;
    TukPIRQ_MCU_IDX                     PIRQMCUIndexAuthorizedList[DukCONFIG_OPTION_UKAPP_PIRQ_REGISTERED_COUNT_MAX];

    TukCOUNT8                           IPCSendToASIDAuthorizedCount;
    TukUKAPP_ASID                       IPCSendToASIDAuthorizedList[DukCONFIG_OPTION_UKAPP_IPC_SEND_TO_COUNT_MAX];

    TukCOUNT8                           SharedBufferDescriptorCount;
    TukSHAREDBUFFER_DESCRIPTOR          SharedBufferDescriptorList[DukCONFIG_OPTION_UKAPP_SHAREDBUFFER_DESCRIPTOR_COUNT_MAX];

    TukCOUNT8                           AddressBlockExtraDescriptorCount;
    TukADDRESSBLOCK_EXTRA_DESCRIPTOR    AddressBlockExtraDescriptorList[DukCONFIG_OPTION_UKAPP_ADDRESSBLOCK_EXTRA_DESCRIPTOR_COUNT_MAX];

    TukCOUNT8                           MCURegisterDescriptorCount;
    TukMCUREGISTER_DESCRIPTOR           MCURegisterDescriptorList[DukCONFIG_OPTION_UKAPP_MCUREGISTER_DESCRIPTOR_COUNT_MAX];

    TukCOUNT8                           DMAStreamDescriptorCount;
    TukDMAS_DESCRIPTOR                  DMAStreamDescriptorList[DukCONFIG_OPTION_UKAPP_DMAS_DESCRIPTOR_COUNT_MAX];

    TukDEBUG_TRACE_NATURE               DebugTraceNatureFilter;
    TukDEBUG_TRACE_VERBOSITY            DebugTraceVerbosityFilter;
#ifdef __IARCC__ /* There doesn't seem to be a way to set members alignment */
    TukHASH_SHA256                      UKAppCodeBodyBlockSHA256;

    TukHASH_SHA256                      UKAppDescriptorSHA256;
#else
    TukHASH_SHA256                      UKAppCodeBodyBlockSHA256    CAukVAR_ALIGNED(0x20);

    TukHASH_SHA256                      UKAppDescriptorSHA256       CAukVAR_ALIGNED(0x20);
#endif
} TukUKAPP_DESCRIPTOR;

#endif /* !defined(__ASSEMBLER__) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_TYPES_H_INSIDE
#endif /* !defined(UK_TYPES_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

