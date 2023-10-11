/**
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This file was modified by ProvenRun
 * Copyright (c) 2023, ProvenRun. All rights reserved.
 *
 */
/*****************************************************************************
 * @file          psa_ia.c
 * @brief         The PSA Initial Attestation API. The library which
 *  aims to communicate with the RoT IA service to get the EAT
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_IA
 ******************************************************************************
 * @details     This file implements the public and private APIs of the
 *              Initial attestation Client library.
 *
 *              The public APIs implemented in this file must be used
 *              by any IA Client application (by including the public header file)
 * @note
 ******************************************************************************
 * @addtogroup    PSA_IA
 * @{
 */

/* Define the global C-Preprocessor statements for smart module compilation.*/
#include "psa/initial_attestation.h"
#include "psa_client_pv.h"

#define PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE             (uint32_t)1U
#define PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE        (uint32_t)1U

/* ######################################################################## */
/*                MODULE PRIVATE API - C-VARIABLES GLOBAL                   */
/* ######################################################################## */
/* Hereafter are defined the C-Variables, with global C-Scope, specific to
 *  this Code Module, and part of its Private API (used only in its internal
 *  implementation).
 *
 * NOTE: See the Private API of this Code Module in the "ukdev_gpio_pv.h"
 *  include file for the documentation relative to these C-Variables.
 */

static psa_status_t check_handle_is_valid(psa_handle_t handle)
{
    if (handle == -1 || handle > 0)
    {
      return PSA_SUCCESS;
    }
    return PSA_ERROR_INVALID_HANDLE;
}

 /* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Functions specific to this Code Module, and part
 *  of its Private API (used only in its internal implementation).
 *
 * NOTE: See the Private API of this module in the 'ukproc_pv.h' include file
 *  for the documentation relative to these C-Functions.
 */

psa_status_t
psa_initial_attest_get_token(const uint8_t *auth_challenge,
                             size_t         challenge_size,
                             uint8_t       *token_buf,
                             size_t         token_buf_size,
                             size_t        *token_size)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0U;
    psa_invec   invec[PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE];
    uint32_t cpt = 0U;

    if ((auth_challenge == NULL) || (token_buf == NULL) || (token_size == NULL))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    for (cpt = 0; cpt < PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE; cpt++)
    {
      invec[cpt].base = NULL;
      invec[cpt].len  = 0U;

      outvec[cpt].base = NULL;
      outvec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_ATTESTATION);

    handle = psa_connect(PSA_SID_ATTESTATION, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
      return status;
    }

    invec[0].base  = auth_challenge;
    invec[0].len   = challenge_size;

    outvec[0].base = token_buf;
    outvec[0].len  = token_buf_size;


    status = psa_call(handle, PSA_TYPE_IA_GET_TOKEN, invec,  PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE,
                      outvec, PSA_IA_GET_TOKEN_INOUT_ARRAY_SIZE);

    if (status == PSA_SUCCESS)
    {
      *token_size = outvec[0].len;
    }

    psa_close(handle);

    return status;
}


psa_status_t psa_initial_attest_get_token_size(size_t challenge_size, size_t *token_size)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0U;
    psa_invec  invec[PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE];
    uint32_t cpt = 0U;

    if (token_size == NULL)
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    for (cpt = 0; cpt < PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE; cpt++)
    {
      invec[cpt].base = NULL;
      invec[cpt].len  = 0U;

      outvec[cpt].base = NULL;
      outvec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_ATTESTATION);

    handle = psa_connect(PSA_SID_ATTESTATION, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
      return status;
    }

    invec[0].base  = &challenge_size;
    invec[0].len   = sizeof(challenge_size);

    outvec[0].base = token_size;
    outvec[0].len  = sizeof(size_t);


    status = psa_call(handle, PSA_TYPE_IA_GET_TOKEN_SIZE, invec,  PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE,
                      outvec, PSA_IA_GET_TOKEN_SIZE_INOUT_ARRAY_SIZE);

    psa_close(handle);


    return status;
}
