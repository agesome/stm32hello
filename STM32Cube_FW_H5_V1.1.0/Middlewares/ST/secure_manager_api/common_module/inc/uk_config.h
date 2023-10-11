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
 * @file          uk_config.h
 * @brief         uKernel API - uKernel Configuration file.
 * @author        patrice.hameau@provenrun.com
 * @maintainer    patrice.hameau@provenrun.com
 * @ingroup       uKernelAPI
 ******************************************************************************
 * @details
 *
 * This file contains the uKernel Configuration exposed in the uKernel API.
 *
 * This file is part of the ukApp SDK and is specific to a given uKernel
 *  Target.
 *
 * It allows to import all the root definitions of the configurable elements
 *  of a given uKernel Target (i.e uKernel Target definitions, uKernel
 *  Features defined, uKernel Options values, ...).
 *
 * The uKernel Configuration part of uKernel API is composed of the following
 *  definitions that are gathered in this file:
 *  - uKernel Target definitions: It is the different elements allowing
 *   to identify the uKernel Target used.
 *  - uKernel Features: It is the uKernel Configuration part relative to the
 *   definitions of the different optional functional requirements that are
 *   supported or not (example: uKernel Feature for supporting the debug
 *   functionalities). The uKernel Features are not Platform specific (i.e.
 *   they are hardware agnostic).
 *  - uKernel MCU Device definitions: It is the uKernel Configuration part
 *   relative to the MCU Device selected (example: definition for the number
 *   or Peripheral IRQ supported).
 *  - uKernel Options: It is the uKernel Configuration part relative to the
 *   different parameters (values) that have been adjusted for the uKernel
 *   Target used (example: uKernel Option defining the maximum number of
 *   simultaneous ukProcs running).
 *   Some of these parameters may be Platform specifics (example:
 *   uKernel Option defining the default initial CPU Core clock frequency).
 *  - Additional derived uKernel Configuration definitions done in the this
 *   file.
 *   The purpose of these derived definitions is to ease a consistent usage of
 *   the uKernel Configuration part of the uKernel API in the ukApp code.
 *
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHALL NOT BE MODIFIED.
 * It shall be used only for compiling and linking ukApp aiming at running on
 *  this given uKernel Target.
 * If improper version is used, the ukApp proper execution cannot be
 *  guaranteed. However, the ukApp security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @implementation The consistency of the configuration of the uKernel Target
 *  has been checked during its compilation, and thus is guaranteed.
 *  However, there may exist some configuration consistency that may not be
 *  fully verified statically, and may raise error only during the execution
 *  of ukApp.
 *
 * @implementation The definitions of the uKernel Configuration part of uKernel
 *  API are done in dedicated include files for easing their maintenance and
 *  Platform specific dependencies.
 *  These include files are the following for a given uKernel Target:
 *   - "uk_release.h": uKernel Target definitions.
 *   - "uk_config_features.h": uKernel Configuration containing the uKernel
 *    Features supported (Platform agnostic).
 *   - "uk_config_hw_mcu_device.h": uKernel Configuration relative to the
 *    uKernel MCU Device selected.
 *   - "uk_config_options.h": uKernel Configuration containing the uKernel
 *    Options that are Platform agnostic.
 *   - "uk_config_options_hw_mcu_xxx.h": uKernel Configuration containing
 *    uKernel Options that are Platform specific (i.e. MCU Device, MCU Core,
 *    or MCU Family specific).
 *  For a given uKernel target <target> these include files are placed in
 *   the following directories:
 *   - "ukernel_api/target/<target>/uk/include/" for the uKernel Target
 *    definitions.
 *   - "ukernel_api/target/<target>/uk/include/config/" for the uKernel
 *    Configuration that is Platform agnostic.
 *   - "ukernel_api/target/<target>/uk/include/config/hw/mcu/xxx" for the
 *    uKernel Configuration that is Platform specific.
 *
 * @implementation This file contains only C-Preprocessor definitions, checks,
 *  and static assertions verified at compilation time.
 *  It DOES NOT generate any binary code.
 *
 * @usage This file shall not be included directly in ukApp code: it SHALL BE
 *  included only by the file "uk.h".
 ******************************************************************************
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(UK_CONFIG_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  UK_CONFIG_H

/* Define that we are inside this file (definition is undone at its end). */
#define  UK_CONFIG_H_INSIDE


/* ######################################################################## */
/*                       UKERNEL API - UKERNEL RELEASE                      */
/* ######################################################################## */
/* Hereafter is defined the uKernel Target definitions part of the uKernel API
 *  Configuration for the used uKernel Target.
 *
 * @implementation To ease maintenance these definitions are managed in
 *  dedicated includes files.
 *
 * WARNING: The definitions contain in the included files SHALL NOT be modified
 *  and are specific to a given uKernel Target (their modifications require
 *  a new compilation of the uKernel to be taken into account).
 */

/* Source uKernel Target definitions part of the uKernel API.
 * @implementation uKernel Target definitions are not Platform specific. */
#include "uk_release.h"


/* ######################################################################## */
/*                      UKERNEL API - UKERNEL COMPILER                      */
/* ######################################################################## */
/* Hereafter are defined the uKernel API Macros helpers allowing abstraction
 *  of the compiler used.
 */
#include "uk_compilers.h"


/* ######################################################################## */
/*                    UKERNEL API - UKERNEL CONFIGURATION                   */
/* ######################################################################## */
/* Hereafter is defined the uKernel Configuration part of the uKernel API for
 *  the uKernel Target.
 * The uKernel Configuration part of the uKernel API is composed of:
 *  - uKernel Features: Specify the functional requirements supported by the
 *   uKernel Target (e.g. support of ukProc reincarnation feature, ...).
 *  - uKernel Options: Define the values used in the uKernel Target for
 *   its internal parameters (e.g. string maximum length, scheduler parameters,
 *  ...).
 *
 * @implementation To ease maintenance these definitions are managed in
 *  dedicated includes files.
 *
 * WARNING: The definitions contained in the include files SHALL NOT be
 *  modified and are specific to a given uKernel Target (their modifications
 *  require a new compilation of the uKernel to be taken into account).
 */

/* Source uKernel Features part of the uKernel API.
 * @implementation uKernel Features are not Platform specific. */
#include "uk_config_features.h"

/* Source uKernel MCU Device configuration part of the uKernel API.
 * @implementation The uKernel Configuration definitions in this file are used
 *  in the other uKernel Configuration parts to adjust their parameters to the
 *  selected MCU Device. */
#include "uk_config_hw_mcu_device.h"

/* Source uKernel Options part of the uKernel API.
 * @implementation The definition of some uKernel Options may be linked to the
 *  support of associated uKernel Features defined in the include file
 *  "uk_config_features.h".
 * @implementation The Platform specific uKernel Options files are included by
 *  this include file. */
#include "uk_config_options.h"


/* ######################################################################## */
/*      UKERNEL API - UKERNEL CONFIGURATION - DERIVED UKERNEL FEATURES      */
/* ######################################################################## */
/* Hereafter are the definitions of the uKernel Features derived (e.g.
 *  definitions regrouping some set of Features, ...) from the uKernel Features
 *  supported in uKernel Configuration part of uKernel API.
 *
 * @implementation They shall be derived ONLY from the uKernel Features part
 *  of the uKernel API included in this file.
 *
 * @implementation A uKernel Feature named 'FFF' is supported if its
 *  corresponding statement SukCONFIG_FEATURE_<FFF> is effectively defined
 *  using a C-Preprocessor '#define' (no value is associated to the
 *  definition).
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                   DERIVED UKERNEL FEATURES - DEBUG                       */
/* //////////////////////////////////////////////////////////////////////// */
/* Hereafter are the definitions of the uKernel Debug Features derived (e.g.
 *  definitions regrouping some set of Features, ...) from the uKernel Features
 *  supported in uKernel Configuration part of uKernel API.
 *
 * @implementation They shall be derived ONLY from the uKernel Features part
 *  of the uKernel API included in this file.
 *
 * @implementation A uKernel Debug Feature named 'FFF' is supported if its
 *  corresponding statement SukCONFIG_FEATURE_DEBUG_<FFF> is effectively
 *  defined using a C-Preprocessor '#define' (no value is associated to the
 *  definition).
 */

/* ROBUSTNESS: None of the uKernel Debug Features defined hereafter are
 *  supported if the uKernel compilation is aiming a Production Target. */
#if !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE)


#endif /* !defined(SukCONFIG_FEATURE_PRODUCTION_RELEASE) */


/* ######################################################################## */
/*      UKERNEL API - UKERNEL CONFIGURATION - DERIVED UKERNEL OPTIONS       */
/* ######################################################################## */
/* Hereafter are the definitions of the uKernel Options derived (e.g. derived
 *  values computed from option values, ...) from the uKernel Options defined
 *  in uKernel Configuration part of uKernel API.
 *
 * @implementation They shall be derived ONLY from the uKernel Options part
 *  of the uKernel API included in this file.
 *
 * @implementation A uKernel Option named 'OOO' is defined by associating its
 *  corresponding label DukCONFIG_OPTION_<OOO> to the wanted parameter value
 *  using the C-Preprocessor '#define'.
 */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef UK_CONFIG_H_INSIDE
#endif /* !defined(UK_CONFIG_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


