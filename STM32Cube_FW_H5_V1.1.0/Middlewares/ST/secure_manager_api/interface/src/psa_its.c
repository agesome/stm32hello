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
 * @file          psa_its.c
 * @brief         The PSA Internal Trusted Storage API.The library which
 *  aims to communicate with the RoT ITS service to save, recover or
 * delete critical data.
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_ITS
 ******************************************************************************
 * @details     This file implements the public and private APIs of the
 *              ITS Client library.
 *
 *              The public APIs implemented in this file must be used
 *              by any ITS Client application (by including the public header file)
 * @note
 ******************************************************************************
 * @addtogroup    PSA_ITS
 * @{
 */

/* Define the global C-Preprocessor statements for smart module compilation.*/
#include "psa/client.h"
#include "psa/client_extension.h"
#include "psa/internal_trusted_storage.h"

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
#define PSA_ITS_SET_GET_INPUT_ARRAY_SIZE      (uint32_t)3
#define PSA_ITS_GET_INFO_INOUT_ARRAY_SIZE     (uint32_t)1
#define PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE     (uint32_t)1
#define PSA_ITS_REMOVE_INPUT_ARRAY_SIZE       (uint32_t)1

 /* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Functions specific to this Code Module, and part
 *  of its Private API (used only in its internal implementation).
 *
 * NOTE: See the Private API of this module in the 'ukproc_pv.h' include file
 *  for the documentation relative to these C-Functions.
 */

/**
 * @brief C-Function Check if one or more of the flags provided in flags
 * is not supported or is not valid.
 * @param[in] (psa_storage_create_flags_t)flags flag.
 * @implementation entered flag has to be checked if it's valid or not;
 * It's compared with the list of flags already defined:
 *  - PSA_STORAGE_FLAG_NONE
 *  - PSA_STORAGE_FLAG_WRITE_ONCE
 *  - PSA_STORAGE_FLAG_NO_CONFIDENTIALITY
 *  - PSA_STORAGE_FLAG_NO_REPLAY_PROTECTION
 *  - PSA_STORAGE_SUPPORT_SET_EXTENDED
 * @return (psa_status_t)Status Code reflecting the execution success of the
 *  C-Function.
 * @retval PSA_SUCCESS The flag is valid.
 * @retval PSA_ERROR_NOT_SUPPORTED The operation failed because one or more
 * of the flags provided in flags is not supported or is not valid.
 */

/*
static psa_status_t is_valid_flag(psa_storage_create_flags_t flags)
{
    psa_status_t psa_status = PSA_SUCCESS;
    psa_storage_create_flags_t flag_mask = (PSA_STORAGE_FLAG_WRITE_ONCE
                                           | PSA_STORAGE_FLAG_NO_CONFIDENTIALITY
                                           | PSA_STORAGE_FLAG_NO_REPLAY_PROTECTION
                                           | PSA_STORAGE_FLAG_NONE);

    if (flags <= flag_mask)
    {
        psa_status = PSA_SUCCESS;
    }
    else
    {
        psa_status = PSA_ERROR_NOT_SUPPORTED;
    }

    return psa_status;
}
*/

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                     */
/* ######################################################################## */


psa_status_t psa_its_set(psa_storage_uid_t uid, size_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags)
{
    psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0;
    psa_invec invec[PSA_ITS_SET_GET_INPUT_ARRAY_SIZE];
    uint32_t cpt = 0U;
    if  ((p_data == NULL) && (data_length != 0))
    {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    for (cpt = 0; cpt < PSA_ITS_SET_GET_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len = 0U;
    }

    /* Open a connection with ITS RoT Service.*/
    psa_init_signal(PSA_SIGNAL_STORAGE);
    handle = psa_connect(PSA_SID_STORAGE, 0);
    if (handle > 0 || handle == -1)
    {
      invec[0].base = &uid;
      invec[0].len = sizeof(psa_storage_uid_t);

      invec[1].base = p_data;
      invec[1].len = data_length;

      invec[2].base = &create_flags;
      invec[2].len = sizeof(psa_storage_create_flags_t);
      /* Send data to the ITS RoT Service by calling the psa_call() API*/
      psa_status = psa_call(handle, PSA_TYPE_ITS_SET_PRIVATE_DATA,
                            (const psa_invec *)&invec,
                            PSA_ITS_SET_GET_INPUT_ARRAY_SIZE, NULL, 0);

      /* Close the connection. */
      psa_close(handle);
    }
    else
    {
      psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
    }

    return psa_status;
}


psa_status_t psa_its_get(psa_storage_uid_t uid, size_t data_offset,
                          size_t data_size, void *p_data,
                          size_t *p_data_length)
{
    psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0;
    psa_invec invec[PSA_ITS_SET_GET_INPUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE];
    uint32_t cpt = 0;
    for (cpt = 0; cpt < PSA_ITS_SET_GET_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;
    }
    for (cpt = 0; cpt < PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE; cpt++)
    {
        outvec[cpt].base = NULL;
        outvec[cpt].len  = 0U;
    }
    /* Check the input parameters.*/
    if ((uid <= 0) || (p_data_length == NULL))
    {
        psa_status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        if (data_size == 0)
        {
            *p_data_length = 0;
        }
        /* Open a connection with ITS RoT Service.*/
        psa_init_signal(PSA_SIGNAL_STORAGE);
        handle = psa_connect(PSA_SID_STORAGE, 0);
        if (handle > 0 || handle == -1)
        {
          invec[0].base  = &uid;
          invec[0].len   = sizeof(psa_storage_uid_t);

          invec[1].base  = &data_offset;
          invec[1].len   = sizeof(size_t);

          outvec[0].base = p_data;
          outvec[0].len  = (size_t)data_size;

          /* Send data to the ITS RoT Service by calling the psa_call() Client API*/
          psa_status     = psa_call(handle, PSA_TYPE_ITS_GET_PRIVATE_DATA,
                                   (const psa_invec *)&invec,
                                   PSA_ITS_SET_GET_INPUT_ARRAY_SIZE,
                                   (psa_outvec *) &outvec,
                                   PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE);
          *p_data_length = outvec[0].len;

          /* Close the connection. */
          psa_close(handle);
        }
        else
        {
          psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
        }
    }
    return psa_status;
}


psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info)
{
    psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0;
    psa_invec invec[PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE];

    /* Check the input parameters.*/
    if ((uid <= 0) || (p_info == NULL))
    {
      psa_status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
      /* Open a connection with ITS RoT Service.*/
      psa_init_signal(PSA_SIGNAL_STORAGE);
      handle = psa_connect(PSA_SID_STORAGE, 0);
      if (handle > 0 || handle == -1)
      {
        invec[0].base    = &uid;
        invec[0].len     = sizeof(psa_storage_uid_t);
        outvec[0].base   = p_info;
        outvec[0].len    = sizeof(struct psa_storage_info_t);

        /* Send data to the ITS RoT Service by calling the psa_call() Client API*/
        psa_status = psa_call(handle, PSA_TYPE_ITS_RETRIEVE_INFO,
                              (const psa_invec *)&invec,
                              PSA_ITS_GET_INFO_INOUT_ARRAY_SIZE,
                              (psa_outvec *) &outvec,
                              PSA_ITS_GET_INFO_INOUT_ARRAY_SIZE);
        /* Close the connection. */
        psa_close(handle);
      }
      else
      {
        psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
      }

    }
    return psa_status;
}


psa_status_t psa_its_remove(psa_storage_uid_t uid)
{
    psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0;
    psa_invec invec[PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE];
    uint32_t cpt = 0;
    for (cpt = 0; cpt < PSA_ITS_SET_GET_OUTPUT_ARRAY_SIZE; cpt++)
    {
      invec[0].base = NULL;
      invec[0].len  = 0U;
    }

    /* Check the input parameters.*/
    if (uid <= 0)
    {
      psa_status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
      /* Open a connection with ITS RoT Service.*/
      psa_init_signal(PSA_SIGNAL_STORAGE);
      handle = psa_connect(PSA_SID_STORAGE, 0);
      if (handle > 0 || handle == -1)
      {
        invec[0].base = &uid;
        invec[0].len = sizeof(psa_storage_uid_t);

        /* Send data to the ITS RoT Service by calling the psa_call() Client API*/
        psa_status = psa_call(handle, PSA_TYPE_ITS_REMOVE_DATA,
                              (const psa_invec *)&invec,
                              PSA_ITS_REMOVE_INPUT_ARRAY_SIZE, NULL, 0);

        /* Close the connection. */
        psa_close(handle);
      }
      else
      {
        psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
      }
    }
    return psa_status;
}
