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
 * @file          secure_manager.h
 * @brief         uKernel NSAPI - Main uKernel NSAPI Declarations file.
 * @author        pierre-julien.bringer@provenrun.com
 * @maintainer    pierre-julien.bringer@provenrun.com
 * @ingroup       uKernelNSAPI
 ******************************************************************************
 * @details
 *
 * This file is the main uKernel Non-Secure API file for a given uKernel
 *  Target.
 * This file contains the public declarations and definitions (types, macros,
 *  constants, functions declarations, ...) that should be used for compiling
 *  a Non-Secure Applications (nsApp) aimed at running on this given uKernel
 *  Target.
 *
 * This file contains notably the following declarations and definitions:
 *  - uKernel NS APIs C-Types and C-Constants.
 *  - uKernel NS APIs C-Functions as uKernel Services Entry Points.
 *  - uKernel NS APIs C-Macros and Helpers.
 *
 * @warning This file is specific to a given uKernel Target.
 * This file SHOULD NOT BE MODIFIED.
 * It should only be used for compiling and linking nsApp aimed at running on
 *  this given uKernel Target.
 * If improper version is used, the nsApp proper execution cannot be
 *  guaranteed. However, the system security properties, and notably its
 *  isolation, remain always enforced even in case an improper version is used.
 *
 * @note In order to enforce consistency, the exact same declarations present
 *  in this file (and associated child files) have been used for compiling the
 *  used uKernel Target. This enforces that all the parts of a uKernel
 *  Image (uKernel Core, uKernel Services, ukApps, ...) are consistent and use
 *  the exact same declarations and definitions.
 *
 ******************************************************************************
 * @addtogroup       uKernelNSAPI
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(SPM_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion).  */
#define  SPM_H

/* Define that we are inside this file (definition is undone at its end). */
#define  SPM_H_INSIDE

/* Source the needed standard C APIs (include files "<stdxxx.h>"). */
#include <stddef.h>
#include <stdint.h>



/* ######################################################################## */
/*                      UKERNEL NS API - CONFIGURATION                      */
/* ######################################################################## */
/* Hereafter are define the C-Macros that make up the configuration of the
 *  kernel for a given uKernel Target (i.e uKernel Target definitions, uKernel
 *  Features defined, uKernel Options values, ...). */


/* ######################################################################## */
/*                         UKERNEL NS API - C-TYPES                         */
/* ######################################################################## */
/* Hereafter are defined the C-Types used in the uKernel NSAPI.
 *
 * @implementation Some types depend on the configuration. The configuration
 *  shall be included before this.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*               UKERNEL NS API - C-TYPES - SPM EXCHANGE AREA               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type of the structure found in the SPM exchange area.
 *
 * Definition of the C-Type of the structure found in the Non-Secure exchange
 *  area. This is the structure expected by the SPM when a call to nscall()
 *  is made.
 */
typedef struct {
    uint32_t sid;
    uint32_t status;
    uint8_t  data[];
} SPM_ExchangeArea_t;


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL NS API - C-TYPES - SPM ENTRY POINTS               */
/* //////////////////////////////////////////////////////////////////////// */

/* Descriptor yielding entry point of the SPM */
typedef struct _SPM_Desc_t (*nsdesc_t)(void);

/* Main entry point of the SPM */
typedef int32_t (*nscall_t)(void);


/* //////////////////////////////////////////////////////////////////////// */
/*                 UKERNEL NS API - C-TYPES - SPM DESCRIPTOR                */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Type describing the SPM interface.
 *
 * Definition of the C-Type describing the SPM interface. This interface is
 *  made for nsApps designed to run on the uKernel.
 */
typedef struct _SPM_Desc_t {
    uint64_t           magic;
    /* Version information */
    uint32_t           desc_version;
    uint32_t           spm_version;
    /* SPM entry points */
    nsdesc_t           nsdesc;
    nscall_t           nscall;
    /* SPM exchange area */
    SPM_ExchangeArea_t*ea_addr;
    size_t             ea_size;
} SPM_Desc_t;



/* ######################################################################## */
/*                       UKERNEL NS API - C-CONSTANTS                       */
/* ######################################################################## */
/* Hereafter are defined the C-Constants of the uKernel NSAPI. */

/* //////////////////////////////////////////////////////////////////////// */
/*              UKERNEL NS API - C-CONSTANTS - MAGIC & VERSION              */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Magic placed as the first field of the SPM Descriptor.
 */
#define SPM_Desc_MAGIC 0xB04949B4E482F94DULL

/**
 * @brief Version number of the descriptor structure.
 */
#define SPM_Desc_DESC_VERSION                                                 \
    /* Major */     (1U  << 24U) |                                            \
    /* Minor */     (0U  <<  8U) |                                            \
    /* Revision */  (0U  <<  0U)

/**
 * @brief Version number of the SPM.
 */
#define SPM_Desc_SPM_VERSION                                                  \
    /* Major */     (1U  << 24U) |                                            \
    /* Minor */     (5U  <<  8U) |                                            \
    /* Revision */  (3U  <<  0U)


/* //////////////////////////////////////////////////////////////////////// */
/*                UKERNEL NS API - C-CONSTANTS - SERVICE MASK               */
/* //////////////////////////////////////////////////////////////////////// */

#define SPM_CALL_BASE       (0xC7670000UL)
#define SPM_CALL_BASE_MASK  (0xFFFF0000UL)


/* //////////////////////////////////////////////////////////////////////// */
/*             UKERNEL NS API - C-CONSTANTS - NSCALL RETURN CODE            */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief NSCall has successfully finished.
 */
#define NSCALL_INFO_OK    ((int32_t)0)

/**
 * @brief NSCall has could not complete, and requires the CPU as soon as
 *  possible.
 */
#define NSCALL_ERR_EAGAIN ((int32_t)-11)

/**
 * @brief NSCall has could not be processed, and some parameter is invalid.
 */
#define NSCALL_ERR_EINVAL ((int32_t)-22)

/**
 * @brief NSCall has could not be processed, and the service has reset.
 */
#define NSCALL_ERR_ECONNRESET ((int32_t)-104)



/* ######################################################################## */
/*           UKERNEL NS API  C-CONSTANTS - UKERNEL SYSTEM SERVICES          */
/* ######################################################################## */
/* Hereafter are defined uKernel API Entry Points (C-Functions) that require
 *  switch to SPM internal code executed with CPU Secure Execution Mode to
 * provide associated uKernel Services. */

/* Descriptor yielding entry point of the SPM */
#define NSDESC_ADDR 0x4201UL
extern const nsdesc_t nsdesc;

/* Main entry point of the SPM */
#define NSCALL_ADDR 0x4203UL
extern const nscall_t nscall;

/*
 * For both of these declarations, there needs to be a corresponding
 * definition, if the constant is to be used. This definition should be
 * as follows:
 *      const nsdesc_t nsdesc = (nsdesc_t) NSDESC_ADDR;
 *      const nscall_t nscall = (nscall_t) NSCALL_ADDR;
 */



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef SPM_H_INSIDE
#endif /* !defined(SPM_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

