/***
 * Some part of this code is derived on BSD-3-Clause TFM/v1.5.0 files
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/*****************************************************************************
 * @file          psa_lifecycle.c
 * @brief         The PSA lifecycle API.
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_lifecycle
 ******************************************************************************
 * @details     This file implements the public APIs of the
 *              lifecycle library.
 ******************************************************************************
 * @addtogroup    PSA_lifecycle
 * @{
 */

/* Define the global C-Preprocessor statements for smart module compilation.*/
#include "psa/lifecycle.h"

 /* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */

/* psa_rot_lifecycle_state is not supported
 * this is given as stubbed function */
uint32_t psa_rot_lifecycle_state(void)
{
    return PSA_LIFECYCLE_UNKNOWN;
}

