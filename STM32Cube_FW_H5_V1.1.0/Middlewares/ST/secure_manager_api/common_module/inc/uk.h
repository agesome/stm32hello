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
 * @file          uk.h
 * @brief         uKernel API - Main uKernel API Declarations file.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file is the main uKernel API file for a given uKernel Target.
 * This file contains the public declarations and definitions (types, macros,
 *  constants, functions declarations, ...) that have to be used for compiling
 *  a uKernel Applications (ukApp) that aims at running on this given uKernel
 *  Target.
 *
 * This file contains notably the following declarations and definitions:
 *  - C-Compiler chain tool root elements.
 *  - uKernel APIs C-Types and C-Constants.
 *  - uKernel APIs C-Functions as uKernel Services Entry Points.
 *  - uKernel APIs C-Macros and Helpers.
 *
 * These uKernel API elements are Platform specific definitions and
 *  declarations, issued from the sourced "uk_hw_mcu_device.h" include file
 *  containing the master definitions relative to the MCU Device selected
 *  for the uKernel Target.
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note In order to enforce consistency, the exact same declarations present
 *  in this file (and associated child files) have been used for compiling the
 *  used uKernel Target. This enforces that all the parts of a uKernel
 *  Image (uKernel Core, uKernel Services, ukApps, ...) are consistent and use
 *  the exact same declarations and definitions.
 *
 * @implementation In order to ease readability and maintenance, the main
 *  uKernel API is defined in the following separate files:
 *  - "uk_compilers.h": Contains all the declaration and definition relative
 *   to the C-Compiler used.
 *
 * @implementation The uKernel API definitions specific to given Platform
 *  elements are defined in separate files. The main entry configuration file
 *  for these definitions is the file "uk_hw_mcu_device.h", containing
 *  the master definitions relative to the MCU Device selected for the uKernel
 *  Target.
 *  This file "uk_hw_mcu_device.h" is selected for inclusion by adding the
 *  following directory in the compiler include files configuration:
 *   "target/<target>/uk/include/config/hw/mcu/device/<vendor>/<family>/<device>"
 *  This directory, which is set only in the configuration of the compiler
 *  include files (no reference in source code), is built using the following
 *  directory definitions (all in lower case):
 *   - <target>: Target Name
 *     Eclipse Build Variable: BVukTARGET_NAME__lc
 *   - <vendor>: Device vendor shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_VENDOR__lc
 *   - <family>: Device family shortname
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_FAMILY__lc
 *   - <device>: Device name
 *     Eclipse Build Variable: BVukTARGET_HW_MCU_DEVICE__lc
 ******************************************************************************
 * @addtogroup       uKernelAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  UK_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_H_INSIDE

/* ######################################################################## */
/*                COMPILER  - CHECKS AND SPECIFIC DECLARATIONS              */
/* ######################################################################## */
/* Hereafter are defined the uKernel API Macros helpers allowing abstraction
 *  of the compiler used.
 */
#include "uk_compilers.h"


/* ######################################################################## */
/*             UKERNEL IMPLEMENTATION - C-CONSTANTS CONSTRAINTS             */
/* ######################################################################## */
/* Hereafter are defined the C-Constants specifying constraints (minimal,
 *  maximal values) of the uKernel Target used.
 *
 * NOTE: These constraints are relative to architecture and internal
 *  implementations choices, either coming from Platform and/or MCU
 *  limitations, or made in the framework of uKernel performances and/or
 *  resources optimizations.
 *
 * @usage These C-Constants are defined at first (even before uKernel C-Type
 *  and C-Macros) as they are are needed for:
 *  - Definition of basic uKernel C-Type, C-Constants and C-Macros (e.g. limit
 *   values, maximal count of elements in array, ...).
 *  - Static compilation checks.
 */
#include "uk_constraints.h"


/* ######################################################################## */
/*                        UKERNEL API - CONFIGURATION                       */
/* ######################################################################## */
/* Hereafter are define the C-Macros that make up the configuration of the
 *  kernel for a given uKernel Target (i.e uKernel Target definitions, uKernel
 *  Features defined, uKernel Options values, ...). */
#include "uk_config.h"


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
#include "uk_macros.h"


/* ######################################################################## */
/*                            UKERNEL API - C-TYPES                         */
/* ######################################################################## */
/* Hereafter are defined the C-Types used in the uKernel API.
 *
 * @implementation As good coding practice, and to help developing high
 *  quality and robust software, all the meaningful elements of uKernel API
 *  have their own dedicated C-Type (strong typing policy used).
 *
 * @implementation Some types depend on the configuration. The configuration
 *  shall be included before this.
 */
#include "uk_types.h"


/* ######################################################################## */
/*                      UKERNEL API / MCU DEVICE SPECIFIC                   */
/* ######################################################################## */
/* Hereafter are sourced the definitions of the uKernel Core Options relative
 *  to the MCU Device selected.
 *
 * NOTE: To ease uKernel Configuration definition and maintenance for several
 *  MCU Devices, these definitions are managed in a dedicated include file
 *  for each MCU Device.
 */
#include "uk_hw_mcu_device.h"


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
#include "uk_constants.h"


/* ######################################################################## */
/*                  UKERNEL API - UKERNEL PRIVILEGED SERVICES               */
/* ######################################################################## */
/* Hereafter are defined uKernel API Entry Points (C-Functions) that require
 *  switch to uKernel internal code executed with CPU Privileged Execution Mode
 *  to provide associated uKernel Services. */
#include "uk_services.h"


/* ######################################################################## */
/*                        UKERNEL API - UKAPP SPECIFICS                     */
/* ######################################################################## */
/* Hereafter are the definitions and declarations only needed for the
 *  compilation of a ukApp.
 *
 * NOTE: To ease maintenance, these definitions and declarations are managed
 *  in a dedicated include file "uk/include/app/uk_app.h".
 */

/*__________________________________________________________________________*/
/* Source additional specific include files if we are compiling a ukApp. */
#if !defined(UKCORE)
#include "uk_app.h"
#endif /* !defined(UKCORE) */


/* ######################################################################## */
/*                           UKERNEL API - HELPERS                          */
/* ######################################################################## */
/* Hereafter are defined the C-Functions and C-Macros composing the uKernel
 *  Helpers of the uKernel API.
 * The purpose of the uKernel Helpers is to provide to ukApp code common
 *  functionalities related to uKernel interfacing, with their implementation
 *  being validated for the used uKernel Target.
 *
 * NOTE: Most of uKernel Helpers implementation is composed of code integrated
 *  with ukApp's one during compilation (thus executing as part of the ukProc
 *  context). They may also used declarations and definitions specific to the
 *  ukApp code compiled.
 *  In case some uKernel Services are used in their implementation, it is
 *  stated in their associated documentation.
 */
#include "uk_helpers.h"


/* ######################################################################## */
/*                   UKERNEL API - UKERNEL CORE SPECIFICS                   */
/* ######################################################################## */
/* Hereafter are the definitions and declarations only needed for the
 *  compilation of the uKernel Core implementation.
 *
 * NOTE: To ease maintenance, these definitions and declarations are managed
 *  in a dedicated include file "uk/include/uk_ukcore.h", which is not part
 *  of uKernel API (and thus not delivered with it).
 */

/*__________________________________________________________________________*/
/* Source additional specific include files if we are compiling uKernel Core
 *  implementation.*/
#if defined(UKCORE)
#include "uk_ukcore.h"
#endif /* defined(UKCORE) */


/* ######################################################################## */
/*                     UKERNEL API - UKERNEL DOCUMENTATION                  */
/* ######################################################################## */
/* Hereafter are the definitions and declarations required by the system used
 *  for building the uKernel Documentation.
 *
 * NOTE: To ease maintenance, these definitions and declarations are managed
 *  in dedicated include files in directory "uk/doc/".
 */

/*__________________________________________________________________________*/
/* Source additional specific include files required by the uKernel
 *  Documentation system.*/
#include "doc_uk_services.h"


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_H_INSIDE
#endif /* !defined(UK_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

