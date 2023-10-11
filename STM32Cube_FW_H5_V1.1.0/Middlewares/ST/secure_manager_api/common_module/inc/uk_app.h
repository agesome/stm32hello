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
 * @file          uk_app.h
 * @brief         uKernelAPI - ukApp uKernel Framework declarations.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 * This file contains the declarations part of the ukApp uKernel Framework.
 *
 * The ukApp uKernel Framework contains:
 *  - The declarations and implementation needed by the uKernel for managing
 *   the ukApp and integrating it as part of the ukApps Bundle.
 *  - The declarations and definitions that may be used in the ukApp
 *   implementation by the ukApp Developers to interface with the uKernel.
 *
 * This file contains notably the following declarations and definitions:
 *  - Definitions of the default value for the ukApp Options not defined in
 *   "ukapp_config_options.h" include file (due to older version used).
 *  - Declaration of the C-Variables needed by the uKernel for the interaction
 *   with the ukApp (ukApp Data Volatile Shared uKernel Services Block) and
 *   configuration of the ukApp (ukApp Descriptor).
 *  - Definitions for the C-Constant relative to ukApp Address Blocks imported
 *   from C-Linker values computed in the "ukapp.ld" C-Linker file.
 *  - Definitions of alias (as C-Macro) for easing the code readability.
 *  - Declarations of the C-Functions needed by the uKernel as ukApp Entry
 *   Points.
 *  - Declarations of helpers C-Function for uKernel Privileged Services.
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target.
 * It completes the main uKernel API include file (see "uk.h" file) with
 *  definitions and declarations specific to ukApp implementation.
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Release.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note This file is automatically included by the "uk.h" file.
 ******************************************************************************
 * @addtogroup    uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */

/*__________________________________________________________________________*/
/* Do not compile this module if compiling uKernel Core. */
#if !defined(UKCORE)

/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.            */
#if !defined(UK_APP_H)

/*__________________________________________________________________________*/
/* Enforces that we are included only by main uKernel API include file. */
#if !defined(UK_H_INSIDE)
#error 'The ukApp SDK "uk_app.h" include file shall be included only in the "uk.h" main uKernel API file'
#endif /* !defined(UK_H_INSIDE) */

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_APP_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_APP_H_INSIDE

/*__________________________________________________________________________*/
/* Source the ukApp Configuration files. */
#ifndef _IARCC__
#include "ukapp_config_descriptor.h"
#include "ukapp_config_options.h"

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"
#else
#include "ukapp_config_descriptor.h"
#include "ukapp_config_options.h"

/* Add inclusion of uKernel Public API (only to help IDE parsing). */
#include "uk.h"
#endif
/* ######################################################################## */
/*           UKAPP UKERNEL FRAMEWORK - UKAPP OPTIONS - DEFAULT              */
/* ######################################################################## */
/* Hereafter are defined the default value for ukApp Options (i.e. C-Constant
 *  values of ukApp Configuration internal parameters) to be used for ukApp
 *  Options that have not been defined in "ukapp_config_options.h" include
 *  file.
 *
 * Each of the ukApp Option is defined as a C-Constant value. The definition
 *  is casting the value with the C-Type associated to the nature of the
 *  ukApp Options, excepted when defining a number of supported elements (as
 *  then the value may be used for defining arrays or tables, and typed values
 *  are not supported by C-Compiler in such definitions).
 *
 * NOTE: The definitions hereafter SHALL NOT BE MODIFIED.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                    UKAPP OPTIONS - DEFAULT - NTSTRING                     */
/* //////////////////////////////////////////////////////////////////////// */

#if !defined(DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX)
#define DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX                               \
    MukVAL_TYPED(TukLENGTH32,                                                 \
                 1024)
#endif /* !defined(DukappCONFIG_OPTION_NTSTRING_LENGTH_MAX) */


/* //////////////////////////////////////////////////////////////////////// */
/*                   UKAPP OPTIONS - DEFAULT - DEBUG TRACE                  */
/* //////////////////////////////////////////////////////////////////////// */

#if !defined(DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)
#define DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT                     \
            DukDEBUG_TRACE_VERBOSITY_DEFAULT
#endif /* !defined(DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT) */


/* ######################################################################## */
/*                  UKAPP UKERNEL FRAMEWORK - C-VARIABLES                   */
/* ######################################################################## */
/* Hereafter are declared the C-Variables part of the ukApp uKernel Framework.
 *
 * NOTE: The declarations hereafter SHALL NOT BE MODIFIED.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                       C-VARIABLES - UKAPP SHARED BLOCK                   */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Variable containing the ukApp Data Volatile Shared uKernel Services
 *  Block.
 *
 * This C-Variable contains the whole data of the ukApp Data Volatile Shared
 *  uKernel Services Block (ukAppDVSUKSVC Block) area. It is defined to ease
 *  the access to the different fields of the structure of this area (see
 *  TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC for more details on the structure
 *  of this area).
 *
 * This C-Variable is the sole memory area that can be used by the uKernel
 *  Privileged Services to store their input and output parameters (see
 *  DukappBLOCK_DATA_VOLATILE_ADDRESS_START and
 *  DukappBLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE for more details).
 *  The rest of the memory blocks belonging to the ukApp are made inaccessible
 *  to the uKernel Core code as soon as a switch into the uKernel Core code is
 *  performed
 *
 * @robustness This C-Variable is put in a dedicated C-Linker section as it has
 *  to be placed at the very beginning of the ukApp Data Volatile Block.
 *  As soon as uKernel Core code is executed (SysTick, request of a uKernel
 *  Privileged Service, ...) this C-Variable will be the sole ukProc memory
 *  area accessible to the uKernel Core code. The rest of the ukApp Data
 *  Volatile Block is made inaccessible as soon as entering in the uKernel Core
 *  code.
 *  This architecture allows to enforce that even in case of unexpected
 *  behavior of uKernel Core code due to bug or hardware perturbation, the
 *  ukProc memory cannot be accessed or affected unexpectedly despite the
 *  highest execution privileges of the uKernel Core code.
 *
 * @implementation The stub code of the uKernel Privileged Service will perform
 *  the necessary copies in this C-Variable of the C-Function parameters used
 *  prior invoking the uKernel Privileged Service. Notably all the parameters
 *  that are a reference to an array (pointers) have their referenced contents
 *  be copied first in this C-Variable before invocation.
 *  For the parameters not passed as reference, they are in general not copied
 *  in this C-Variable, but this depends of the number of parameters, and of
 *  the optimization done in the stub code (and thus no assumption shall be
 *  done on this behavior).
 *
 * @usage This C-Variable is strictly private to the ukApp (no access is
 *  allowed from other ukProcs under any circumstances). Its contents is lost
 *  upon each ukProc Creation (i.e. creation of a new ukProc Instance).
 *
 * @usage Some uKernel Privileged Services may require the ukApp developer
 *  itself to perform the copy of some input parameters in fields of this
 *  C-Variable.
 *  The reason of not having the stub code of the uKernel Privileged Service
 *  always performing the copy is to avoid having to deal with too much
 *  parameters, or to perform unneeded copies in some invocations sequence
 *  reusing these same parameters.
 *
 * @usage Excepted indicated otherwise by the documentation of the uKernel
 *  Privileged Service, the unused part of each fields of this C-Variable shall
 *  be considered as modified upon each uKernel Privileged Service invocation
 *  (e.g. if only a few bytes of <ServiceParameter.Input> are used, the
 *  other remaining bytes of this field may also have been possibly altered
 *  after the invocation). Thus no specific assumption shall be done by the
 *  ukApp code on the contents of this C-Variable after a uKernel Privileged
 *  Service invocation for the fields not part of the output parameters.
 *
 * @usage It is recommended that the ukApp code always use the defined
 *  C-function and associated stub code for invoking a uKernel Privileged
 *  Service. However, if this is needed for optimization constraints, nothing
 *  prevent the ukApp code to mimic the operations done in the stub code and
 *  perform itself the proper initialization of this C-Variable, as well as
 *  the setting of the input parameters (parameters put in the CPU registers
 *  as required by the C-Function used by the C-compiler).
 *  In this case, HIGH CARE HAS TO BE TAKEN that the ukApp code imitating the
 *  stub code may need to be updated in function of the uKernel Release used.
 *
 * @usage It is guaranteed that the uKernel will not modify any field of this
 *  C-Variable as long as a uKernel Privileged Service is not invoked.
 *  However some non-privileged uKernel Services may use this C-Variable as
 *  internal buffer (this will then be explicitly specified in their
 *  documentation).
 */
MukVAR_DECLARE(GVukappBlockDataSharedUKSVC,
               TukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC);


/**
 * @brief C-Variable alias for the <ServiceResult> field of the ukApp Data
 *  Volatile Shared uKernel Services Block.
 *
 * This C-Variable alias refers to the <ServiceResult> field of ukApp Data
 *  Volatile Shared uKernel Services Block contained in the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 *
 * @note This is a C-Variable alias to increase code readability: it does not
 *  declare a new C-Variable, but is only a shortcut to the field of an
 *  already declared C-Variable.
 *
 * @usage This C-Variable alias should be used to increase code readability
 *  when accessing to field of GVukappBlockDataSharedUKSVC C-Variable.
 */
#define GVukappUKSVCResult  GVukappBlockDataSharedUKSVC.ServiceResult


/**
 * @brief C-Variable alias for the <Input> field of the ukApp Data Volatile
 *  Shared uKernel Services Block.
 *
 * This C-Variable alias refers to the <Input> field of the ukApp Data Volatile
 *  Shared uKernel Services Block contained in the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 *
 * @note This is a C-Variable alias to increase code readability: it does not
 *  declare a new C-Variable, but is only a shortcut to the field of an
 *  already declared C-Variable.
 *
 * @usage This C-Variable alias should be used to increase code readability
 *  when accessing to field of GVukappBlockDataSharedUKSVC C-Variable.
 */
#define GVukappUKSVCInput   GVukappBlockDataSharedUKSVC.ServiceParameter.Input


/**
 * @brief C-Variable alias for the <Output> field of the ukApp Data Volatile
 *  Shared uKernel Services Block.
 *
 * This C-Variable alias refers to the <Output> field of the ukApp Data
 *  Volatile Shared uKernel Services Block contained in the C-Variable
 *  GVukappBlockDataSharedUKSVC.
 *
 * @note This is a C-Variable alias to increase code readability: it does not
 *  declare a new C-Variable, but is only a shortcut to the field of an
 *  already declared C-Variable.
 *
 * @usage This C-Variable alias should be used to increase code readability
 *  when accessing to field of GVukappBlockDataSharedUKSVC C-Variable.
 */
#define GVukappUKSVCOutput  GVukappBlockDataSharedUKSVC.ServiceParameter.Output


/* //////////////////////////////////////////////////////////////////////// */
/*                       C-VARIABLES - UKAPP DESCRIPTOR                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Constant C-Variable containing the ukApp Descriptor.
 *
 * This Constant C-Variable contains the ukApp Descriptor structure.
 *
 * The ukApp Descriptor is a structure that regroup all the information for the
 *  identification and configuration of a ukApp.
 *
 * The ukApp Descriptor contains notably the following
 *  information::
 *  - Memory resources(code and data memory area).
 *  - Identification (application unique name, ...).
 *  - uKernel Scheduler parameters (time quantum, priority, ...).
 *  - Authorized IPC recipients list.
 *  - Authorized memory areas access list.
 *  - ...
 * See TukUKAPP_DESCRIPTOR for more details on the ukApp Descriptor structure.
 *
 * @warning The ukApp Descriptor structure definition is generic for all the
 *  ukApps using a given uKernel Release. All its fields are filled in using
 *  the definitions done in the "ukapp_config_descriptor.h" file, and only the
 *  definitions in this file shall be modified by the ukApp Developer.
 *
 * @implementation The ukApp Descriptor structure may depend of the uKernel
 *  Release used. A ukApp can have one, and only one, ukApp Descriptor. The
 *  ukApp Descriptor is always placed at the very beginning of the ukApp Code
 *  Block (it is followed by the ukApp Code Body Block, containing the ukApp
 *  implementation).
 *  The reserved C-Linker section associated to the ukApp Descriptor is
 *  '.ukapp_descriptor'.
 *
 * @implementation The seed value used for <PaddingVariability> field is the
 *  leftmost bytes of SHA256 hash of 'UKAPP_DESCRIPTOR'.
 *
 * @usage A ukProc can access directly to the contents of its ukApp Descriptor,
 *  as it is part of its ukApp Code Block. For portability, it is however
 *  advised to retrieve the information it contains by using the dedicated
 *  uKernel Privileged Services of the uKernel API (see ukUKAppGetAttribute()).
 */
MukCONST_STRUCT_DECLARE(GKukappApplicationDescriptor,
                        TukUKAPP_DESCRIPTOR);


/* ######################################################################## */
/*                   UKAPP UKERNEL FRAMEWORK - C-CONSTANTS                  */
/* ######################################################################## */
/* Hereafter are defined the C-Constants part of the ukApp uKernel Framework.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 *
 * NOTE: The declarations hereafter SHALL NOT BE MODIFIED.
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                        C-CONSTANTS - C-LINKER IMPORTS                    */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter are the definitions, part of the ukApp Framework, of the needed
 *  C-Constant issued by the C-Linker during the linking of the ukApp.
 *
 * See "ukapp.ld" file for more details on the way these constants are computed
 *  by the C-Linker.
 *
 * NOTE: The following naming conventions are used:
 *  - LukUKAPP_xxx: C-Constant computed by the C-Linker during linking
 *   process (their values may change upon each ukApp compilation).
 *  - LDukapp_xxx: C-Constant defined by the ukApp developer in its
 *   "ukapp.ld" file (not depending of ukApp compilation result).
 */

/* C-Linker imported values of the ukApp Code Block. */
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_CODE_ADDRESS_START;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_CODE_SIZE_RESERVED;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_CODE_EXEC_SIZE;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_CODE_CONSTANT_SIZE;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_CODE_VAR_INIT_LOAD_ADDRESS;

/* C-Linker imported values of the ukApp Data Volatile Block. */
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_ADDRESS_START;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_SIZE_RESERVED;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_VAR_INIT_SIZE;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_VAR_NULL_SIZE;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_VOLATILE_HEAP_SIZE;
#ifndef __IARCC__
extern TukLINKER_DEFINITION32 LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED;
#endif
/* C-Linker imported values of the ukApp Data Persistent Block. */
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_PERSISTENT_ADDRESS_START;
extern TukLINKER_DEFINITION32 LukUKAPP_BLOCK_DATA_PERSISTENT_SIZE_RESERVED;


/* //////////////////////////////////////////////////////////////////////// */
/*                    C-CONSTANTS - UKAPP ADDRESS BLOCKS                    */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constant defining the Start Address of the ukApp Code Block.
 *
 * Import from the C-Linker as a C-Constant the Start Address of the ukApp
 *  Code Block.
 * The ukApp Code Block contains the ukApp Descriptor (at its very beginning),
 *  and the whole ukApp implementation (executable code and constant data).
 *
 * The ukApp Code Block is a continuous persistent memory area.
 * It fills the whole C-Linker Memory Region UKAPP_MEMORY_REGION_CODE.
 *
 * The ukApp Code Block is composed of the following contiguous sub-blocks
 *  (in that listed order):
 *  - ukApp Descriptor Block: Area containing the ukApp Descriptor (see
 *   GKukappApplicationDescriptor) of the ukApp.
 *   See the C-Linker section '.ukapp_code_descriptor'.
 *  - ukApp Code Body Block: Area containing the whole ukApp implementation
 *   (executable code, constant data, ...).
 *   It is composed of the following contiguous sub-blocks (in that listed
 *   order):
 *   + ukApp Code Executable Block: Area containing the executable code of the
 *     ukApp.
 *     See the following C-Linker sections:
 *    * '.ukapp_code_exec'.
 *    * '.ukapp_code_linker'.
 *    * '.ukapp_code_mcu_specific'.
 *   + ukApp Code Constant Block: Area containing the constant data needed by
 *     the executable code (constant tables, string, initial non-null values of
 *     the Initialized ukApp C-Variables).
 *     See the following C-Linker sections:
 *    * '.ukapp_code_const_head'.
 *    * '.ukapp_data_volatile_var_init'
 *    * '.ukapp_code_const_tail'
 *   + Unused Block: Area not used and filled with default value to enforce
 *     integrity check consistency.
 *     See the C-Linker section '.ukapp_code_unused'.
 *
 * The Start Address of this area is defined as the Start Address of the
 *  C-Linker Memory Region UKAPP_MEMORY_REGION_CODE.
 * The C-Linker will enforce that the Start Address and Length of this area to
 *  be a multiple of LDukUKAPP_MEMORY_REGION_START_ADDRESS_ALIGNEMENT.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  alignment on its size DukappBLOCK_CODE_SIZE_RESERVED (see
 *  LDukUKAPP_MEMORY_REGION_ADRESS_START_ALIGNED_ON_SIZE_ENFORCED).
 *
 * This area (and sub-areas) are strictly private to this ukApp (notably no
 *  access is allowed from any other ukApp under any circumstances). Its
 *  contents is kept between uKernel Sessions.
 *
 * @robustness The uKernel will enforce during ukApp Descriptor validation the
 *  following constraints for this ukApp Code Block:
 *  - It is fully contained in the ukApps Bundle Code Block defined by the
 *   C-Linker Memory Region UKAPPBUNDLE_MEMORY_REGION_CODE.
 *  - It does not overlap with ukApp Code Blocks of any other ukApps whose
 *   ukApp Descriptors has been already validated during ukApp Descriptor
 *   validation.
 *
 * @robustness The uKernel has access to the ukApp Code Block only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @robustness As an additional protection, the uKernel is configuring this
 *  area to be immutable (no data belonging to this area can be modified)
 *  during uKernel Initialization.
 *  This area may be made again temporary mutable, under strict control of
 *  the uKernel Bootloader, only through the uKernel Image Update mechanisms.
 *
 * @implementation On most Platforms this area is in the MCU internal FLASH.
 *  On some Platforms, this area may however be in RAM memory for fastest
 *  execution, the RAM memory contents having then been copied in it with the
 *  code data stored in persistent memory during the uKernel Initialization.
 */
#define DukappBLOCK_CODE_ADDRESS_START                                        \
        MukVAL_TYPED(                                                         \
            TukADDRESS32,                                                     \
            &LukUKAPP_BLOCK_CODE_ADDRESS_START)

/**
 * @brief C-Constant defining the Size of the ukApp Code Block.
 *
 * Import from the C-Linker as a C-Constant the size (in bytes) of the ukApp
 *  Code Block.
 *
 * The Size of this area is defined as the Size of the C-Linker Memory Region
 *  UKAPP_MEMORY_REGION_CODE.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  that this Size be a power of two(2) (see
 *  LDukUKAPP_MEMORY_REGION_SIZE_POWER_OF_TWO_ENFORCED).
 *
 * See LukUKAPP_BLOCK_CODE_ADDRESS_START for more details on this area.
 *
 * @implementation If no ukApp Data Persistent Block is required for this ukApp
 *  then its Size is set to null(0).
 */
#define DukappBLOCK_CODE_SIZE_RESERVED                                        \
        MukVAL_TYPED(                                                         \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_CODE_SIZE_RESERVED)

/**
 * @brief C-Constant defining the Start Address of the ukApp Code C-Variables
 *  Initialized Block.
 *
 * Import from the C-Linker as a C-Constant the Start Address of the ukApp
 *  Code C-Variables Initialized Block.
 * It contains the initial values of the C-Variables that have a non-null value
 *  upon each start of execution of the ukappMain() Entry Point.
 *
 * The ukApp Code C-Variables Initialized Block area is a continuous persistent
 *  memory area, sub-area of the ukApp Code Block.
 * It is placed just after the ukApp executable code and constant.
 *
 * The Start Address of this area is defined as the first address multiple of
 *  8 after the end of the ukApp executable code and constant.
 * The Size of this area is the same as the one of the ukApp Data Volatile
 *  C-Variables Initialized Block (see DukappBLOCK_DATA_VOLATILE_VAR_INIT_SIZE).
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is kept between
 *  uKernel Sessions.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile Heap Block
 *  only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @robustness The uKernel will enforce during ukApp Descriptor validation that
 *  the ukApp Code C-Variables Initialized Block is fully contained in the
 *  ukApp Code Block.
 *
 * @implementation The exact same structure as the ukApp Data Volatile
 *  C-Variables Initialized Block has to be generated by the C-Linker for this
 *  area. The reason why is that a simple copy process between these both areas
 *  is used by uKernel upon start of execution of the ukappMain() Entry Point
 *  to initialize these C-Variable values.
 *  It also guarantees that these both areas have the same size ;-).
 *
 * @usage The ukApp C-Variables with a null initial value are not part of this
 *  area. Their values are placed in the ukApp Data Volatile C-Variables Null
 *  Block (see DukappBLOCK_DATA_VOLATILE_VAR_NULL_SIZE) and separately reset
 *  by uKernel code upon start of execution of the ukappMain() Entry Point.
 *
 * @usage This area is used for initializing the contents of the ukApp Data
 *  Volatile C-Variables Initialized Block (see
 *  DukappBLOCK_DATA_VOLATILE_VAR_INIT_SIZE) upon start of execution of the
 *  ukappMain() Entry Point.
 *
 * @usage:
 *  The C-Compiler sections associated to this area are:
 *   - '.data_begin'
 *   - '.data'
 *   - '.data_end'
 */
#define DukappBLOCK_CODE_VAR_INIT_ADDRESS                                     \
        MukVAL_TYPED(                                                         \
            TukADDRESS32,                                                     \
            &LukUKAPP_BLOCK_CODE_VAR_INIT_LOAD_ADDRESS)

/**
 * @brief C-Constant defining the Start Address of the ukApp Data Volatile
 *  Block.
 *
 * Import from the C-Linker as a C-Constant the Start Address of the ukApp
 *  Data Volatile Block.
 * It contains the whole volatile data of the ukApp (C-Variables, internal
 *  buffers, CPU Stack)
 *
 * The ukApp Data Volatile Block is a continuous volatile memory area.
 * It fills the whole C-Linker Memory Region UKAPP_MEMORY_REGION_DATA_VOLATILE.
 *
 * The ukApp Data Volatile Block is composed of the following contiguous
 *  sub-blocks (in that listed order):
 *  - ukApp Data Volatile Shared uKernel Services Block (ukAppDVSUKSVC Block):
 *   Area where are placed the data exchanged between the uKernel and the
 *   ukProc upon invocation of a uKernel Privileged Service.
 *   See the C-Linker section '.ukapp_data_volatile_shared_uksvc'.
 *  - ukApp Data Volatile C-Variables Initialized Block: Area containing the
 *   C-Variables of the ukApp code having a non-null initial value.
 *   See the C-Linker section '.ukapp_data_volatile_var_init'.
 *  - ukApp Data Volatile C-Variables Null Block: Area containing the
 *   C-Variables of the ukApp code having a null initial value.
 *   See the C-Linker section '.ukapp_data_volatile_var_null'.
 *  - ukApp Data Volatile Heap Block: Area at the disposal of the ukApp code as
 *   volatile data memory block (e.g. can be used to implement memory allocator,
 *   internal buffers, ...).
 *   See the C-Linker section '.ukapp_data_volatile_heap'.
 *  - ukApp Data Volatile Stack Block: Area containing the CPU Stack used
 *   during execution of the ukProc.
 *   See the C-Linker section '.ukapp_data_volatile_stack'.
 *
 * The Start Address of this area is defined as the Start Address of the
 *  C-Linker Memory Region UKAPP_MEMORY_REGION_DATA_VOLATILE.
 * The C-Linker will enforce it to be a multiple of
 *  LDukUKAPP_MEMORY_REGION_START_ADDRESS_ALIGNEMENT.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  alignment on its size LukUKAPP_BLOCK_DATA_VOLATILE_SIZE_RESERVED (see
 *  LDukUKAPP_MEMORY_REGION_ADRESS_START_ALIGNED_ON_SIZE_ENFORCED).
 *
 * This area (and sub-areas) are strictly private to this ukApp (notably no
 *  access is allowed from any other ukApp under any circumstances). Its
 *  contents is loss between uKernel Sessions and re-initialized with constant
 *  fixed values upon start of execution of the ukappMain() Entry Point.
 *
 * @robustness The uKernel will enforce during ukApp Descriptor validation that
 *  this ukApp Data Volatile Block is fully contained in ukApps Bundle Memory
 *  Region UKAPPBUNDLE_MEMORY_REGION_DATA_VOLATILE, and does not overlap with
 *  any other ukApp Data Volatile Block of ukApp Descriptors already validated.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile Block during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *  Additionally, it has access of the ukApp Data Volatile Shared uKernel
 *   Services Block, sub-area of the ukApp Data Volatile Block, each time
 *   the uKernel Core code is invoked.
 *
 * @implementation On most Platforms this area is in the MCU internal RAM.
 */
#define DukappBLOCK_DATA_VOLATILE_ADDRESS_START                               \
        MukVAL_TYPED(                                                         \
            TukADDRESS32,                                                     \
            &LukUKAPP_BLOCK_DATA_VOLATILE_ADDRESS_START)

/**
 * @brief C-Constant defining the Size of the ukApp Data Volatile Block.
 *
 * Import from the C-Linker as a C-Constant the size (in bytes) of the ukApp
 *  Data Volatile Block.
 *
 * The Size of this area is defined as the Size of the C-Linker Memory Region
 *  UKAPP_MEMORY_REGION_DATA_VOLATILE.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  that this Size be a power of two(2) (see
 *  LDukUKAPP_MEMORY_REGION_SIZE_POWER_OF_TWO_ENFORCED).
 *
 * See LukUKAPP_BLOCK_DATA_VOLATILE_ADDRESS_START for more details on this area.
 */
#define DukappBLOCK_DATA_VOLATILE_SIZE_RESERVED                               \
        MukVAL_TYPED(                                                         \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_VOLATILE_SIZE_RESERVED)

/**
 * @brief C-Constant defining the size of the ukApp Data Volatile Shared
 *  uKernel Service Block.
 *
 * Import from the C-Linker as a C-Constant the size (in bytes) of the
 *  ukApp Data Volatile Shared uKernel Service Block (ukAppDVSUKSVC Block).
 * See uKernel Option
 *  DukCONFIG_OPTION_UKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE
 *  for more details on this area.
 *
 * @robustness The size of this area is fixed and depends only of the uKernel
 *  Release used. Its value is however retrieved from the C-Linker in order to
 *  check during uKernel Initialization that the one defined during the
 *  compilation of the ukApp is the same as the one defined for the uKernel
 *  Release used.
 */
#define DukappBLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE                           \
        MukVAL_TYPED(                                                         \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_VOLATILE_SHARED_UKSVC_SIZE)

/**
 * @brief C-Constant defining the Size of the ukApp Data Volatile C-Variables
 *  Initialized Block.
 *
 * Import from the C-Linker as a C-Constant the Size (in bytes) of the ukApp
 *  Data Volatile C-Variables Initialized Block.
 * It contains the C-Variables that have a non-null value upon each start of
 *  execution of the ukappMain() Entry Point.
 *
 * The ukApp Data Volatile C-Variables Initialized Block area is a continuous
 *  volatile memory area, sub-area of the ukApp Data Volatile Block.
 * It is placed just after the ukApp Data Volatile Shared uKernel Services
 *  Block.
 *
 * The Start Address of this area is defined as the first address multiple of
 *  8 after the end of the ukApp Data Volatile Shared uKernel Services Block.
 * The Size of this area is adjusted automatically by the C-Linker in function
 *  of the number C-Variables that have a non-null initial value in the ukApp
 *  code.
 *  The C-Linker will enforce it to be a multiple of 8 (unused padded data are
 *  added at the end if necessary).
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is loss between
 *  uKernel Sessions.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile C-Variables
 *  Initialized Block only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @implementation This area is for initialized with the contents of the ukApp
 *  Code Block C-Variables Initialized (see
 *  LukUKAPP_BLOCK_CODE_VAR_INIT_LOAD_ADDRESS) upon start of execution of the
 *  ukappMain() Entry Point.
 *
 * @usage:
 *  The C-Linker section associated to this area is:
 *   - "ukapp_data_volatile_var_init"
 *  The C-Compiler sections associated to this area are:
 *   - '.data_begin'
 *   - '.data'
 *   - '.data_end'
 */
#define DukappBLOCK_DATA_VOLATILE_VAR_INIT_SIZE                               \
        MukVAL_TYPED(                                                         \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_VOLATILE_VAR_INIT_SIZE)

/**
 * @brief C-Constant defining the Size of the ukApp Data Volatile C-Variables
 *  Null Block.
 *
 * Import from the C-Linker as a C-Constant the Size (in bytes) of the ukApp
 *  Data Volatile C-Variables Null Block.
 * It contains the C-Variables that have a null value upon each start of
 *  execution of the ukappMain() Entry Point.
 *
 * The ukApp Data Volatile C-Variables Null Block area is a continuous
 *  volatile memory area, sub-area of the ukApp Data Volatile Block.
 * It is placed just after the ukApp Data Volatile C-Variables Initialized
 *  Block.
 *
 * The Start Address of this area is defined as the first address multiple of
 *  8 after the end of the ukApp Data Volatile C-Variables Initialized Block.
 * The Size of this area is adjusted automatically by the C-Linker in function
 *  of the number C-Variables that have a null initial value in the ukApp code.
 *  The C-Linker will enforce it to be a multiple of 8 (unused padded data are
 *  added at the end if necessary).
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is loss between
 *  uKernel Sessions.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile C-Variables
 *  Null Block only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @implementation This area is for sure initialized with null value upon start
 *  of execution of the ukappMain() Entry Point ;-).
 *
 * @usage:
 *  The C-Linker section associated to this area is:
 *   - 'ukapp_data_volatile_var_null'
 *  The C-Compiler sections associated to this area are:
 *   - '.bss_begin'
 *   - '.bss'
 *   - '.bss_end'
 */
#define DukappBLOCK_DATA_VOLATILE_VAR_NULL_SIZE                               \
        MukVAL_TYPED(                                                         \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_VOLATILE_VAR_NULL_SIZE)


/**
 * @brief C-Constant defining the Size of the ukApp Data Volatile Heap Block.
 *
 * Import from the C-Linker as a C-Constant the Size (in bytes) of the ukApp
 *  Data Volatile Heap Block.
 * It is at the disposal of the ukApp for storing volatile data (e.g. can be
 *  used to implement a memory allocator, internal storage buffers, ...).
 *
 * The ukApp Data Volatile Heap Block area is a continuous volatile memory
 *  area, sub-area of the ukApp Data Volatile Block.
 * It is placed just after the ukApp Data Volatile C-Variables Null Block.
 *
 * The Start Address of this area is defined as the first address multiple of
 *  8 after the end of the ukApp Data Volatile C-Variables Null Block.
 * The Size of this area is adjusted automatically by the C-Linker in function
 *  of the remaining space available in the ukApp Data Volatile Block after
 *  having allocated all the other sub-areas composing it (see
 *  LukUKAPP_BLOCK_DATA_VOLATILE_ADDRESS_START for more details on the
 *  different sub-areas). The C-Linker will enforce it to be a multiple of 8.
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is loss between
 *  uKernel Sessions.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile Heap Block
 *  only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @implementation A minimum Size for this area may be required by the ukApp
 *  Developer (see LDukUKAPP_BLOCK_DATA_VOLATILE_HEAP_SIZE_MIN in C-Linker
 *  script file "ukapp_memory_mapping_hw_mcu_device_xxx.ld").
 *  If the resulting Size is below the minimum required, an assertion in the
 *  C-Linker script used for ukApp (see "ukapp.ld" file) will fail.
 *
 * @implementation When starting execution of the ukappMain() Entry Point, this
 *  area has been initialized with a specific pattern value. In order to
 *  enforce best robustness, the chosen pattern may vary in function of the
 *  uKernel Release and Platform (and thus ukApp code SHALL NOT rely on a given
 *  value for this pattern).
 *
 * @usage This area is fully at the disposal to ukApp Developer usage for any
 *  purpose it may need (large internal buffer, memory allocator heap, ...).
 */
#define DukappBLOCK_DATA_VOLATILE_HEAP_SIZE                                   \
         MukVAL_TYPED(                                                        \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_VOLATILE_HEAP_SIZE)

/**
 * @brief C-Constant defining the Size of the ukApp Data Volatile Stack Block.
 *
 * Import from the C-Linker as a C-Constant the Size (in bytes) of the ukApp
 *  Data Volatile Stack Block.
 * It contains the CPU Stack used when executing the ukProc code.
 *
 * The ukApp Data Volatile Stack Block area is a continuous volatile memory
 *  area, sub-area of the ukApp Data Volatile Block.
 * It is placed at the very end of the ukApp Data Volatile Block.
 *
 * The Start Address of this area is computed by using its Size from the last
 *  address of the ukApp Data Volatile Block. It is a multiple of 8.
 * The Size of this area is defined by the ukApp Developer (see the C-Linker
 *  Constant LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED in C-Linker
 *  script file "ukapp_memory_mapping_hw_mcu_device_xxx.ld"). The C-Linker will
 *  enforce it to be a multiple of 8.
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is loss between
 *  uKernel Sessions.
 *
 * @warning A minimum size for this area is necessary for the uKernel to drive
 *  the execution of a ukProc (see
 *  LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_MINIMAL in C-Linker
 *  script file "ukapp_memory_mapping_hw_mcu_device_xxx.ld").
 *  This minimum size depends of Platform used (the set of data stacked upon
 *  events depending of the MCU core), and of the uKernel Release. If this
 *  given size is below the required minimum, the linking of the ukApp will
 *  fail with error.
 *
 * @robustness If the uKernel detects that during ukProc execution that its CPU
 *  Stack has reached an address outside of this area, then it is a ukProc
 *  Fatal Error, and the uKernel triggers a ukProc Abort with ukProc
 *  Termination Reason DukUKPROC_TERMINATION_REASON_ABORT_ILLEGAL_ACCESS.
 *
 * @robustness The uKernel has access to the ukApp Data Volatile Stack Block
 *  only during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - If uKernel Feature for ukProc Debug Trace
 *   SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC is enabled, the uKernel Core kept
 *   access to this whole area once ukProc execution has started.
 *
 * @implementation When starting execution of the ukappMain() Entry Point, this
 *  area has been initialized with a specific pattern value. In order to
 *  enforce best robustness, the chosen pattern may vary in function of the
 *  uKernel Release and Platform (and thus ukApp code SHALL NOT rely on a given
 *  value for this pattern).
 *
 * @usage The CPU will automatically stack data in this area upon an MCU
 *  Exception to save the current execution context before switching to
 *  uKernel Core code.
 *  An MCU Exception may be due to:
 *   - Invocation of uKernel Privileged Services
 *   - uKernel Systick period over
 *   - Peripheral IRQ triggering.
 *   - CPU execution fault (address illegal access , division by zero, ...).
 */
#define DukappBLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED                         \
         MukVAL_TYPED(                                                        \
            TukLENGTH32,                                                      \
            &LDukUKAPP_BLOCK_DATA_VOLATILE_STACK_SIZE_RESERVED)


/**
 * @brief C-Constant defining the Start Address of the ukApp Data Persistent
 *  Block.
 *
 * Import from the C-Linker as a C-Constant the Start Address of the ukApp
 *  Data Persistent Block.
 * It contains the persistent data of the ukApp.
 *
 * The ukApp Data Persistent Block is a continuous persistent memory area.
 * It fills the whole C-Linker Memory Region
 *  UKAPP_MEMORY_REGION_DATA_PERSISTENT.
 *
 * The Start Address of this area is defined as the Start Address of the
 *  C-Linker Memory Region UKAPP_MEMORY_REGION_DATA_PERSISTENT.
 * The C-Linker will enforce it to be a multiple of
 *  LDukUKAPP_MEMORY_REGION_START_ADDRESS_ALIGNEMENT.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  alignment on its size LukUKAPP_BLOCK_DATA_VOLATILE_SIZE_RESERVED (see
 *  LDukUKAPP_MEMORY_REGION_ADRESS_START_ALIGNED_ON_SIZE_ENFORCED).
 *
 * This area is strictly private to this ukApp (notably no access is allowed
 *  from any other ukApp under any circumstances). Its contents is kept between
 *  uKernel Sessions.
 *
 * @robustness The uKernel will enforce during ukApp Descriptor validation that
 *  this ukApp Data Persistent Block is fully contained in ukApps Bundle Memory
 *  Region UKAPPBUNDLE_MEMORY_REGION_DATA_PERSISTENT, and does not overlap with
 *  any other ukApp Data Persistent Block of ukApp Descriptors already
 *  validated.
 *
 * @robustness The uKernel has access to the ukApp Data Persistent Block only
 *  during:
 *  - ukProc Creation (i.e. creation of a new ukProc Instance from its ukApp).
 *  - Usage of uKernel Privileged Services dedicated to the access to ukApp
 *   Data Persistent Blocks.
 *
 * @implementation On most Platforms this area is in the MCU internal FLASH.
 *
 * @implementation If no ukApp Data Persistent Block is required for this ukApp
 *  then its Start Address is set to the Start Address of the ukApps Bundle
 *  Data Persistent Block.
 */
#define DukappBLOCK_DATA_PERSISTENT_ADDRESS_START                             \
            MukVAL_TYPED(TukADDRESS32,                                        \
            &LukUKAPP_BLOCK_DATA_PERSISTENT_ADDRESS_START)

/**
 * @brief C-Constant defining the Size of the ukApp Data Persistent Block.
 *
 * Import from the C-Linker as a C-Constant the size (in bytes) of the ukApp
 *  Data Persistent Block.
 *
 * The Size of this area is defined as the Size of the C-Linker Memory Region
 *  UKAPP_MEMORY_REGION_DATA_PERSISTENT.
 * Additional constraints may arise in function of the uKernel Release and
 *  MCU Device selected. Notably the MPU of some MCU Cores will require
 *  that this Size be a power of two(2) (see
 *  LDukUKAPP_MEMORY_REGION_SIZE_POWER_OF_TWO_ENFORCED).
 *
 * See DukappBLOCK_DATA_PERSISTENT_ADDRESS_START for more details on this area.
 *
 * @implementation If no ukApp Data Persistent Block is required for this ukApp
 *  then its Size is set to null(0).
 */
#define DukappBLOCK_DATA_PERSISTENT_SIZE_RESERVED                             \
         MukVAL_TYPED(                                                        \
            TukLENGTH32,                                                      \
            &LukUKAPP_BLOCK_DATA_PERSISTENT_SIZE_RESERVED)


/* ######################################################################## */
/*                   UKAPP UKERNEL FRAMEWORK - C-MACROS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Macros part of the ukApp uKernel Framework.
 *
 * NOTE: The declarations hereafter SHALL NOT BE MODIFIED.
 *
 * @implementation Some of the C-Macros may need the definition of some
 *  constant parameters to tune their behavior. When such parameters are
 *  needed, they are defined as ukApp Configuration Options (see file
 *  "ukapp/include/config/ukapp_config_options.h").
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                        C-MACROS - DEBUG TRACE ALIAS                      */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Information
 *  using a printf() alike format.
 *
 * This C-Macro alias prints a Debug Trace of Nature Information by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf() for more details).
 *
 * @implementation The Debug Trace Nature used is
 *  DukDEBUG_TRACE_NATURE_INFO_FLAG.
 *
 * @implementation The Debug Trace Verbosity level used is defined by the ukApp
 *  Option DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT (see file
 *  "ukapp_config_options.h").
 *
 * @usage This C-Macro does not return the Status Code relative to the
 *  printing of the Debug Trace.
 */
#define MukappDBGT_INFO_PF(dbgtrace_format_ntstr_addr__i, ...)                \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_INFO_FLAG,                      \
                        0,                                                    \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Information
 *  using a printf() alike format, followed by a newline.
 *
 * This C-Macro alias prints a Debug Trace of Nature Information by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf()), followed by a
 *  newline.
 *
 * @implementation See MukappDBGT_INFO_PF for more details.
 */
#define MukappDBGT_INFO_PFNL(dbgtrace_format_ntstr_addr__i, ...)              \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_INFO_FLAG,                      \
                        DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG,              \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature
 *  Configuration using a printf() alike format.
 *
 * This C-Macro alias prints a Debug Trace of Nature Configuration by
 *  processing given printf() alike Format string
 *  <dbgtrace_format_ntstr_addr__i> and associated variables arguments (see
 *  ukDebugTracePrintf()).
 *
 * @implementation The Debug Trace Nature used is
 *  DukDEBUG_TRACE_NATURE_CONFIG_FLAG.
 *
 * @implementation The Debug Trace Verbosity level used is defined by the ukApp
 *  Option DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT (see file
 *  "ukapp_config_options.h").
 *
 * @usage This C-Macro does not return the Status Code relative to the
 *  printing of the Debug Trace.
 */
#define MukappDBGT_CFG_PF(dbgtrace_format_ntstr_addr__i, ...)                 \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_CONFIG_FLAG,                    \
                        0,                                                    \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature
 *  Configuration using a printf() alike format, followed by a newline.
 *
 * This C-Macro alias prints a Debug Trace of Nature Configuration by
 *  processing given printf() alike Format string
 *  <dbgtrace_format_ntstr_addr__i> and associated variables arguments (see
 *  ukDebugTracePrintf()), followed by a newline.
 *
 * @implementation See MukappDBGT_CFG_PF for more details.
 */
#define MukappDBGT_CFG_PFNL(dbgtrace_format_ntstr_addr__i, ...)               \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_CONFIG_FLAG,                    \
                        DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG,              \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Warning
 *  using a printf() alike format.
 *
 * This C-Macro alias prints a Debug Trace of Nature Warning by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf()).
 *
 * @implementation The Debug Trace Nature used is
 *  DukDEBUG_TRACE_NATURE_WARNING_FLAG.
 *
 * @implementation The Debug Trace Verbosity level used is defined by the ukApp
 *  Option DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT (see file
 *  "ukapp_config_options.h").
 *
 * @usage This C-Macro does not return the Status Code relative to the
 *  printing of the Debug Trace.
 */
#define MukappDBGT_WARN_PF(dbgtrace_format_ntstr_addr__i, ...)                \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_WARNING_FLAG,                   \
                        0,                                                    \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Warning
 *  using a printf() alike format, followed by a newline.
 *
 * This C-Macro alias prints a Debug Trace of Nature Warning by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf()), followed by a
 *  newline.
 *
 * @implementation See MukappDBGT_WARN_PF for more details.
 */
#define MukappDBGT_WARN_PFNL(dbgtrace_format_ntstr_addr__i, ...)              \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_WARNING_FLAG,                   \
                        DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG,              \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Error
 *  using a printf() alike format.
 *
 * This C-Macro alias prints a Debug Trace of Nature Error by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf()).
 *
 * @implementation The Debug Trace Nature used is
 *  DukDEBUG_TRACE_NATURE_ERROR_FLAG.
 *
 * @implementation The Debug Trace Verbosity level used is defined by the ukApp
 *  Option DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT (see file
 *  "ukapp_config_options.h").
 *
 * @usage This C-Macro does not return the Status Code relative to the
 *  printing of the Debug Trace.
 */
#define MukappDBGT_ERR_PF(dbgtrace_format_ntstr_addr__i, ...)                 \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_ERROR_FLAG,                     \
                        0,                                                    \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

/**
 * @brief C-Macro alias for printing a ukProc Debug Trace of Nature Error
 *  using a printf() alike format, followed by a newline.
 *
 * This C-Macro alias prints a Debug Trace of Nature Error by processing
 *  given printf() alike Format string <dbgtrace_format_ntstr_addr__i> and
 *  associated variables arguments (see ukDebugTracePrintf()), followed by a
 *  newline.
 *
 * @implementation See MukappDBGT_ERR_PF for more details.
 */
#define MukappDBGT_ERR_PFNL(dbgtrace_format_ntstr_addr__i, ...)               \
            ukDebugTracePrintf(                                               \
                MukVAL_TYPED(                                                 \
                    TukDEBUG_TRACE_ATTRIBUTES,                                \
                    MukDEBUG_TRACE_ATTRIBUTES_BUILD(                          \
                        DukDEBUG_TRACE_NATURE_ERROR_FLAG,                     \
                        DukDEBUG_TRACE_MODE_NEWLINE_SUFFIX_FLAG,              \
                        DukappCONFIG_OPTION_DEBUG_TRACE_VERBOSITY_DEFAULT)),  \
                dbgtrace_format_ntstr_addr__i,                                \
                ## __VA_ARGS__)

#else /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */
/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_INFO_PF(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_INFO_PFNL(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_CFG_PF(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_CFG_PFNL(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_WARN_PF(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_WARN_PFNL(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_ERR_PF(dbgtrace_format_ntstr_addr__i, ...)

/**
 * @brief C-Macro not implemented in regards of selected uKernel Features. */
#define MukappDBGT_ERR_PFNL(dbgtrace_format_ntstr_addr__i, ...)

#endif /* defined(SukCONFIG_FEATURE_DEBUG_TRACE_UKPROC) */



/* //////////////////////////////////////////////////////////////////////// */
/*                       C-MACROS - DEBUG - SVC DEBUG TRACE                 */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Macro for printing a Debug Trace upon uKernel Privileged Service
 *  returned Status Code.
 *
 * Definition of the uKernel C-Macro for the printing of a Debug Trace when
 *  the Status Code of an invoked uKernel Privileged Service has a Nature flag
 *  (see TukSTATUS) that is part of the ones defined in ukApp Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES.
 *
 * @implementation This C-Macro does nothing (no printing of Debug Trace) if
 *  the ukApp Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES is not
 *  defined.
 *
 * @usage It is advised to use the C-Compiler predefined C-Macro
 *  "__FUNCTION__" as parameter <svc_name_ntstring__i> when invoking this
 *  C-Macro.
 *
 * @param[in] (TukSTATUS)status_code Status Code returned by the uKernel
 *  Privileged Service invoked.
 * @param[in] (TukNTCSTRING_ADDRESS)svc_name_ntstring_addr__i Address of the
 *  Null Terminated String (NTString) containing the name of the uKernel
 *  Privileged Service.
 */
#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES)
    #define ukSVC_DEBUG_TRACE_STATUS_CHECK(status_code__i,                    \
                                           svc_name_ntstring_addr__i)         \
        {                                                                     \
            uk_appSVCDebugTraceStatusPrint(                                   \
                                    status_code__i,                           \
                                    svc_name_ntstring_addr__i);               \
        }
#else /* DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES */
    #define ukSVC_DEBUG_TRACE_STATUS_CHECK(svc_name_ntstring__i, status_code)
#endif /* DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES */

/**
 * @brief C-Macro for printing a Debug Trace upon uKernel Privileged Service
 *  returned Status Code, used for IPC-related Services.
 *
 * Definition of the uKernel C-Macro for the printing of a Debug Trace when
 *  the Status Code of an invoked uKernel Privileged Service has a Nature flag
 *  (see TukSTATUS) that is part of the ones defined in ukApp Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES.
 *
 * @implementation This C-Macro does nothing (no printing of Debug Trace) if
 *  the ukApp Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES is not
 *  defined.
 *
 * @usage It is advised to use the C-Compiler predefined C-Macro
 *  "__FUNCTION__" as parameter <svc_name_ntstring__i> when invoking this
 *  C-Macro.
 *
 *  This macro defaults to ukSVC_DEBUG_TRACE_STATUS_CHECK if
 *  DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL is not set.
 *
 * @param[in] (TukSTATUS)status_code Status Code returned by the uKernel
 *  Privileged Service invoked.
 * @param[in] (TukNTCSTRING_ADDRESS)svc_name_ntstring_addr__i Address of the
 *  Null Terminated String (NTString) containing the name of the uKernel
 *  Privileged Service.
 */
#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) && \
    defined(DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL)

    #define ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC(status_code__i,                    \
                                           svc_name_ntstring_addr__i)         \
        {                                                                     \
            uk_appSVCDebugTraceIPCStatusPrint(                                \
                                    status_code__i,                           \
                                    svc_name_ntstring_addr__i);               \
        }
#else /* DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL */
    #define ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC ukSVC_DEBUG_TRACE_STATUS_CHECK
#endif /* DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL */

/* ######################################################################## */
/*                  UKAPP UKERNEL FRAMEWORK - C-FUNCTIONS                   */
/* ######################################################################## */
/* Hereafter are defined the C-Functions part of the ukApp uKernel Framework.
 *
 * NOTE: The declarations hereafter SHALL NOT BE MODIFIED.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                       C-FUNCTIONS - ENTRY POINTS                         */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * =========================================================================
 * DOCUMENTATION: UKAPP ENTRY POINTS
 * =========================================================================
 *
 * A ukApp Entry Point is a C-Function which is needed by the uKernel to drive
 *  the execution of a ukProc. It has to be implemented in the code of the
 *  ukApp.
 *
 * The ukApp Entry Point(s) used by the uKernel are the following C-Functions:
 *  - ukappMain(): ukApp Entry Point invoked by the uKernel for starting the
 *   execution of a newly created ukProc Instance.
 *   It contains the main ukApp code for performing its operations and services.
 *   It has always to be defined in ukApp code.
 *
 *  - ukappCleanup(): ukApp Entry Point invoked at the start of a ukProc
 *   Termination (either due to a ukProc End or a ukProc Abort) process.
 *   It shall contain dedicated ukApp code for performing its cleanup (e.g.
 *   wiping of sensitive data, resetting of some peripherals, ...) before being
 *   effectively terminated by the uKernel.
 *   If defined in ukApp code, it will be invoked only if uKernel Feature
 *   SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported.
 *
 *  - ukappException(): ukApp Entry Point invoked upon a ukProc Exception.
 *   It contains dedicated ukApp code for reacting immediately (indeed in a
 *   fixed maximal latency) to some critical events (e.g. triggering of
 *   Peripheral IRQ, MCU Clocks Set change, uKernel Security Alert, ...).
 *   If defined in ukApp code, it will be invoked only if uKernel Feature
 *   SukCONFIG_FEATURE_UKPROC_EXCEPTION is supported.
 *   #NOTYETSUPPORTED
 *
 * The invocation of a ukApp Entry Point may be done directly by other ukApp
 *  code parts (its invocation is not reserved to the uKernel).
 */


/**
 * @brief C-Function used as ukApp Entry Point by the uKernel for starting the
 *   execution of a newly created ukProc Instance.
 *
 * This C-Function is invoked as ukApp Entry Point by the uKernel for starting
 *  the execution of a newly created ukProc Instance.
 *
 * @robustness The uKernel Initialization enforces that the address of this
 *  ukApp Entry Point is part of the ukApp Code Block. Else the ukApp Descriptor
 *  is considered as invalid.
 *
 * @implementation This ukApp Entry Point is a standard C-Function that shall
 *  be part of the ukApp code.
 *
 * @implementation At any moment, only one ukProc Instance can be created from
 *  a given ukApp, and thus a ukApp code cannot be executed by several ukProc
 *  Instances at the same time (no need to consider re-entrance in the ukApp
 *  implementation).
 *
 * @implementation Upon each ukProc Creation, a new ukProc Instance is created
 *  from the ukApp.
 *  The whole data and execution context from previous ukProc Instance is
 *  lost, excepting its ukProc Termination Context (see
 *  DukUKAPP_ATTRIBUTE_TAG_UKPROC_TERMINATION_CONTEXT_LAST).
 *  In order to differentiate a new ukProc Instance from the previous one of
 *  the same ukApp, the uKernel will enforce that the new ukProc Instance has a
 *  different PUID (see TukUKPROC_PUID). This enforces that other ukProcs are
 *  able to detect that a new ukProc Instance has been created form this ukApp,
 *  and react accordingly.
 *
 * @implementation No notification is done by the uKernel to other ukProcs that
 *  a ukProc Creation has occurred: it is up to the newly created ukProc
 *  Instance to use IPC message to announce its creation to the other ukProcs.
 *
 * @implementation The definition of the C-Function for this Entry Point SHALL
 *  BE MADE in ukApp code (belonging to the ukApp Code Block), else the
 *  compilation of the ukApp will fail.
 *
 * @implementation If this C-Function returns, the uKernel Privileged Service
 *  ukUKProcEntryPointReturn() is invoked (through the C-Function
 *  ukappEntryPointReturn() which is invoked automatically upon return of any
 *  ukApp Entry Point). It is a ukProc Fatal Error, and the uKernel will then
 *  trigger a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR.
 *
 * @usage This C-Function SHALL exit by invoking the uKernel Privileged
 *  Service ukUKProcExit().
 *
 * @param[in] auid__i Application Unique Identifier (AUID) of the ukApp used
 *  to instantiate the ukProc (as defined in its ukApp Descriptor).
 * @param[in] ukapp_version__i Version of the ukApp (as defined in its ukApp
 *  Descriptor).
 * @param[in] ukproc_origin__i Origin of ukProc Creation (i.e. which event has
 *  lead to the triggering of the creation of a new ukProc Instance from this
 *  ukApp).
 *
 * @return Status code containing the reason of the exit of the ukProc.
 */
void CAukFUNC_NEEDED_ALWAYS ukappMain(
    TukUKAPP_AUID     auid__i           CAukVAR_UNUSED_MAYBE,
    TukVERSION        ukapp_version__i  CAukVAR_UNUSED_MAYBE,
    TukUKPROC_ORIGIN  ukproc_origin__i  CAukVAR_UNUSED_MAYBE);


#if defined(SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP)
/**
 * @brief C-Function used as ukApp Entry Point by the uKernel for the ukProc
 *  Cleanup.
 *
 * This C-Function is invoked as ukApp Entry Point by the uKernel for the
 *  ukProc Cleanup upon the start of the ukProc Termination (either due to a
 *  ukProc End or a ukProc Abort) process.
 * The ukProc Cleanup purpose is to let the dedicated ukProc code perform its
 *  internal cleanup before the ukProc being effectively terminated by the
 *  uKernel.
 *
 * Before invoking this ukApp Entry Point, the following actions are performed
 *  by the uKernel:
 *  - If the ukProc is the Scheduled ukProc, the execution of the ukApp Code
 *   currently executed is stopped.
 *  - The ukProc Watchdog, if started (see ukWatchdogStart()), is stopped.
 *  - The ukProc CPU Stack contents is reset.
 *  - The Scheduling ukProc State is set to Halting (even if it was previously
 *   set to Blocked) and the ukProc Instance is schedulable by the ukScheduler
 *   (uKernel Scheduler).
 *
 * The ukProc Cleanup is successful if this C-Function ends from one of the
 *  following events:
 *  - Returning (with C-Statement 'return').
 *  - Invoking the uKernel Privileged Service ukUKProcEntryPointReturn().
 *  - Invoking the uKernel Privileged Service ukUKProcExit() with its
 *   boolean parameter <is_exit_in_error__i> set to DukBOOL_FALSE).
 * All the other events leading to the end of this C-Function (ukProc Fatal
 * Error, ...) make the ukProc Cleanup as unsuccessful.
 * If the ukProc Cleanup is unsuccessful, the uKernel Signal
 *  DukSIGNAL_ID_UKPROC_CLEANUP_IN_ERROR is sent to all the other ukProcs. The
 *  ukProc Termination Reason set upon the triggering of the ukProc
 *  Termination process is however not modified, even in case of ukProc Fatal
 *  Error during the ukProc Cleanup.
 *
 * @robustness If the uKernel Feature
 *  SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is supported, the uKernel
 *  enforces during its initialization that the address of this ukApp Entry
 *  Point is part of the ukApp Code Block. Else the ukApp Descriptor is
 *  considered as invalid.
 *
 * @implementation This ukApp Entry Point is a standard C-Function that shall
 *  be part of the ukApp code.
 *
 * @implementation The definition of the C-Function for this ukApp Entry Point
 *  is optional. If defined, it SHALL BE MADE in ukApp code (belonging to the
 *  ukApp Code Block), else the compilation of the ukApp will fail.
 *  The ukProc Cleanup will be triggered only if the following both conditions
 *   are fulfilled:
 *  - The uKernel Feature SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP is
 *   supported.
 *  - The C-Function for this ukApp Entry Point is defined in the ukApp code.
 *  - The C-Function for this ukApp Entry Point has not already been invoked
 *   (a ukProc Fatal Error during the execution of this C-Function will not
 *   trigger a new invocation of this C-Function).
 *
 * @implementation During the invocation of this ukApp Entry Point, the
 *  Scheduling ukProc State is set to Current Interrupt. Once the invocation
 *  of this ukApp Entry Point is over, the Scheduling ukProc State will be set
 *  to Halted definitively, and thus the ukProc Instance cannot be executed
 *  anymore.
 *
 * @implementation The execution time allocated by the ukScheduler (uKernel
 *  Scheduler) to a ukProc Instance to perform its cleanup is limited: the
 *  invocation of the ukApp Entry Point ukappCleanup() shall be over before the
 *  end of the Scheduling Time Quantum defined by uKernel Option
 *  DukCONFIG_OPTION_SCHEDULING_TIME_QUANTUM_UKPROC_CLEANUP_systick.
 *  If this Scheduling Time Quantum, which is set as the Scheduling Time
 *  Quantum Allocated during the ukProc Cleanup, is expired, then the execution
 *  of the ukApp Entry Point ukappCleanup() is stopped, and the ukProc
 *  Termination process is finalized, with the ukProc Cleanup process set as
 *  unsuccessful.
 *
 * @implementation The ukApp Entry Point ukappCleanup() has a restricted set
 *  of uKernel Privileged Services which can be invoked (see
 *  DukUKAPP_CLEANUP_PRIVILEGED_SERVICES_AUTHORIZED_BITMASK64). If a
 *  unauthorized uKernel Privileged Services is invoked, it is a ukProc Fatal
 *  Error: the execution of the ukApp Entry Point ukappCleanup() is stopped,
 *  and the ukProc Termination process is finalized, with the ukProc Cleanup
 *  set as unsuccessful.
 *
 * @usage The ukApp Developer SHALL enforce that the implementation of this
 *  C-Function always executes with enough margin in less uKernel Systicks than
 *  the value set for the Scheduling Time Quantum for a ukProc Cleanup (see
 *  uKernel Option
 *  DukCONFIG_OPTION_SCHEDULING_TIME_QUANTUM_UKPROC_CLEANUP_systick).
 *  Else the ukProc Cleanup will be unsuccessful.
 *
 * @usage The success of the ukProc Cleanup is reported in the field
 *  <IsUKProcCleanupInError> in the ukProc Termination Context (see
 *  TukUKPROC_TERMINATION_CONTEXT). The field is set to DukBOOL_FALSE if the
 *  ukProc Cleanup process is successful, else it is set to DukBOOL_TRUE.
 *
 * @param[in] (TukUKPROC_TERMINATION_REASON)ukproc_termination_reason__i ukProc
 *  Termination Reason providing details on the event (e.g. ukProc End, ukProc
 *  Fatal Error due to lack of credentials, ...) having triggered the ukProc
 *  Termination.
 * @param[in] (TukUKPROC_TERMINATION_INFO)ukproc_termination_info__i ukProc
 *  Termination Info value contains additional information (e.g. address in
 *  ukProc code having triggered a ukProc Fatal Error, ...) in the specific
 *  context of the Reason having triggered the ukProc Termination (see
 *  DukUKPROC_TERMINATION_REASON_xxx for details).
 */
void CAukFUNC_NEEDED_ALWAYS ukappCleanup(
    TukUKPROC_TERMINATION_REASON    ukproc_termination_reason__i    CAukVAR_UNUSED_MAYBE,
    TukUKPROC_TERMINATION_INFO      ukproc_termination_info__i      CAukVAR_UNUSED_MAYBE);
#endif /* defined(SukCONFIG_FEATURE_UKPROC_TERMINATION_CLEANUP) */



#if defined(SukCONFIG_FEATURE_UKPROC_EXCEPTION)
/**
 * @brief C-Function used as Entry Point by the uKernel for a ukProc Exception.
 *
 * This C-Function is invoked as Entry Point by the uKernel when a ukProc
 *  Exception has been raised for the ukProc.
 *
 * The ukProc Exception purpose is to have dedicated ukApp code in charge of
 *  reacting immediately (similarly to the CPU interrupt mechanism) to a
 *  uKernel Signal (see DukSIGNAL_ID_xxx) raised by the uKernel for the ukProc
 *  (rather than using the IPC mechanism).
 *
 * Before invoking this ukApp Entry Point, the following actions are performed
 *  by the uKernel:
 *  - The execution of the ukApp Code currently executed by the ukProc Instance
 *   is suspended (it will be resumed when the management of the ukProc
 *   Exception is over).
 *  - The Scheduling ukProc State is set to Interrupted (even if it was
 *   previously set to Blocked): the ukProc Instance is then schedulable by the
 *   ukScheduler (uKernel Scheduler).
 *  - As soon as the ukProc is the Scheduled ukProc, the execution of this
 *   ukApp Entry Point is started.
 *
 * @implementation The execution time allocated by the ukScheduler (uKernel
 *  Scheduler) to a ukProc Instance to perform the processing of the ukProc
 *  Exception is limited: the invocation of the ukApp Entry Point
 *  ukappException() shall be over before the end of the Scheduling Time Quantum
 *  Allocated for ukProc Exception defined in the field
 *  <UKProcExceptionSchedulingTimeQuantumAllocated_systick> of its ukApp
 *  Descriptor.
 *  If this Scheduling Time Quantum is exhausted, then it is a ukProc Fatal
 *  Error, the execution of the ukApp Entry Point ukappException() is stopped,
 *  and the uKernel triggers a ukProc Abort with ukProc Termination Reason
 *  DukUKPROC_TERMINATION_REASON_ABORT_INVALID_STATE.
 *
 * @robustness If the uKernel Feature SukCONFIG_FEATURE_UKPROC_EXCEPTION is
 *  supported, the uKernel enforces during its initialization that the address
 *  of this ukApp Entry Point is part of the ukApp Code Block. Else the ukApp
 *  Descriptor is considered as invalid.
 *
 * @warning Upon invocation of this ukApp Entry Point, no backup of the ukApp
 *  Data Volatile Shared uKernel Services Block (ukAppDVSUKSVC Block) is
 *  performed. As upon the invocation the ukApp Entry Point ukappMain() may be
 *  in the process of using significant data in it, the whole data in this
 *  area SHALL BE SAVED before being used (and notably before invoking a
 *  uKernel Privileged Service), and then restored before leaving this ukApp
 *  Entry Point. This saving IS NOT performed automatically by the uKernel.
 *
 * @implementation This ukApp Entry Point is a standard C-Function that shall
 *  be part of the ukApp code.
 *
 * @implementation If the uKernel Feature SukCONFIG_FEATURE_UKPROC_EXCEPTION is
 *  supported, the definition of the C-Function for this Entry Point SHALL BE
 *  MADE in ukApp code (belonging to the ukApp Code Block), else the
 *  compilation of the ukApp will fail.
 *  If this uKernel Feature is not supported, then no definition of this
 *  C-Functions is required in ukApp code (if still defined, the definition is
 *  ignored and never invoked by the uKernel).
 *
 * @implementation As during the invocation of this ukApp Entry Point, the
 *  Scheduling ukProc State is set to Interrupted (even if it was previously
 *  set to Blocked), the ukProc Instance is schedulable by the ukScheduler
 *  (uKernel Scheduler). Once the invocation of this ukApp Entry Point is over,
 *  the Scheduling ukProc State is restored to its previous state.
 *
 * @usage If the ukProc Exception has finalized its processing without any
 *  errors, this ukApp Entry Point SHOULD END by either returning (using
 *  standard 'return()' C-Keyword), or by invoking the uKernel Privileged Service
 *  ukUKProcEntryPointReturn().
 *  The ukProc Instance can also be terminated from this ukApp Entry Point by
 *  invoking the uKernel Privileged Service ukUKProcExit(). In that case, the
 *  report of an error during the ukProc Exception processing can be done by
 *  setting its boolean parameter <is_exit_in_error__i> to DukBOOL_TRUE.
 *
 * @usage The ukApp Developer SHALL enforce that the implementation of this
 *  C-Function always executes with enough margin in less uKernel Systicks than
 *  the value set for the Scheduling Time Quantum Allocated for ukProc
 *  Exception (see field <UKProcExceptionSchedulingTimeQuantumAllocated_systick>
 *  in ukApp Descriptor).
 *  Else the ukProc Exception will trigger a ukProc Fatal Error.
 *
 * @param[in] (TukUKPROC_EXCEPTION_EVENT_NATURE)
 *  ukproc_exception_event_nature__i ukProc Exception Event Nature having
 *  triggered the ukProc Exception (see DukUKPROC_EXCEPTION_EVENT_NATURE_xxx
 *  for supported natures).
 * @param[in] (TukUKPROC_EXCEPTION_EVENT_SOURCE)
 *  ukproc_exception_event_source_bm__i ukProc Exception Event Source bitmask
 *  allowing to identify unambiguously the source(s) of the event (see
 *  TukUKPROC_EXCEPTION_EVENT_SOURCE for details).
 *
 * @implementation #NOTYETSUPPORTED
 */
void CAukFUNC_NEEDED_ALWAYS ukappException(
    TukUKPROC_EXCEPTION_EVENT_NATURE    ukproc_exception_event_nature__i    CAukVAR_UNUSED_MAYBE,
    TukUKPROC_EXCEPTION_EVENT_SOURCE    ukproc_exception_event_source_bm__i CAukVAR_UNUSED_MAYBE);
#endif /* defined(SukCONFIG_FEATURE_UKPROC_EXCEPTION) */



/* ######################################################################## */
/*             UKAPP UKERNEL FRAMEWORK PRIVATE - C-FUNCTIONS                */
/* ######################################################################## */
/* Hereafter are declared the C-Functions of the ukApp uKernel Framework, part
 *  of its Private API (used only in its internal implementation).
 * These C-Functions are implementing the sub-functionalities supporting the
 *  implementation of the functionalities provided by the ukApp uKernel
 *  Framework.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                      C-FUNCTIONS - UKPROC MANAGEMENT                     */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Function invoked upon the return of a ukApp Entry Point.
 *
 * This C-Function is a stub invoked automatically upon the return of any of
 *  the ukApp Entry Point part of ukApp code.
 *
 * @implementation This C-Function invokes the uKernel Privileged Service
 *  ukUKProcEntryPointReturn().
 *
 * @usage This C-Function is private to ukApp uKernel Framework and SHALL NOT
 *  BE invoked directly in ukApp code.
 */
void ukappEntryPointReturn(void);


/* //////////////////////////////////////////////////////////////////////// */
/*                   C-FUNCTIONS - DEBUG - SVC DEBUG TRACE                  */
/* //////////////////////////////////////////////////////////////////////// */

#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES)
/**
 * @brief C-Function printing the Status Code returned by a uKernel Privileged
 *  Service on the ukProc Debug Trace.
 *
 * This C-Function prints the Status Code returned by a uKernel Privileged
 *  Service on the ukProc Debug Trace.
 *
 * The Status Code returned by the uKernel Privileged Service is printed only
 *  if its Nature field has its bit set in the ukProc Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES.
 *
 * The ukProc Debug Trace is printed with the following Debug Trace Attributes:
 *  - Nature: DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG.
 *  - Verbosity: DukDEBUG_TRACE_VERBOSITY_FINER.
 *
 * @usage This C-Function SHALL BE used only by the C-Macro
 *  ukSVC_DEBUG_TRACE_STATUS_CHECK().
 *
 * @param[in] (TukSTATUS)status_code__i Status Code returned by the uKernel
 *  Privileged Service.
 * @param[in] (TukNTCSTRING_ADDRESS)svc_name_ntstring_addr__i Address of the
 *  NTString containing the name of the uKernel Privileged Service.
 */
void uk_appSVCDebugTraceStatusPrint(
                TukSTATUS            status_code__i,
                TukNTCSTRING_ADDRESS svc_name_ntstring_addr__i);


#if defined(DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL)
/**
 * @brief C-Function printing the Status Code returned by a uKernel Privileged
 *  Service on the ukProc Debug Trace. This variant is used by IPC functions
 *
 * This C-Function prints the Status Code returned by a uKernel Privileged
 *  Service on the ukProc Debug Trace, except for errors that can be expected
 *  when using a less strict IPC model. This function won't log as error
 *  DukSTATUS_ERR_TIMEOUT and DukSTATUS_ERR_PRECOND, but instead as INFO.
 *
 * The Status Code returned by the uKernel Privileged Service is printed only
 *  if its Nature field has its bit set in the ukProc Option
 *  DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES.
 *
 * The ukProc Debug Trace is printed with the following Debug Trace Attributes:
 *  - Nature: DukDEBUG_TRACE_NATURE_DIAGNOSTIC_FLAG.
 *  - Verbosity: DukDEBUG_TRACE_VERBOSITY_FINER.
 *
 * @usage This C-Function SHALL BE used only by the C-Macro
 *  ukSVC_DEBUG_TRACE_STATUS_CHECK_IPC().
 *
 * @param[in] (TukSTATUS)status_code__i Status Code returned by the uKernel
 *  Privileged Service.
 * @param[in] (TukNTCSTRING_ADDRESS)svc_name_ntstring_addr__i Address of the
 *  NTString containing the name of the uKernel Privileged Service.
 */
void uk_appSVCDebugTraceIPCStatusPrint(
                TukSTATUS            status_code__i,
                TukNTCSTRING_ADDRESS svc_name_ntstring_addr__i);

#endif /* defined(DukappCONFIG_OPTION_DEBUG_TRACE_IPC_ALLOW_LAX_MODEL) */
#endif /* defined(DukappCONFIG_OPTION_DEBUG_TRACE_UKERNEL_SERVICE_STATUS_NATURES) */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_APP_H_INSIDE
#endif /* !defined(UK_APP_H) */
#endif /* !defined(UKCORE) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

