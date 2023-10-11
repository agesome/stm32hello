/***
 * Some part of this code is derived on BSD-3-Clause TFM/v1.5.0 files
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/*****************************************************************************
 * @file          psa_fwu.c
 * @brief         The PSA Firmware Upgrade API.The library which
 *  aims to communicate with the RoT FWU service to update an image stored
 * in the STuRoT
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_FWU
 ******************************************************************************
 * @details     This file implements the public and private APIs of the
 *              Firmware Upgrade Client library.
 *
 *              The public APIs implemented in this file must be used
 *              by any FWU Client application (by including the public header file)
 * @note
 ******************************************************************************
 * @addtogroup    PSA_FWU
 * @{
 */

/* Define the global C-Preprocessor statements for smart module compilation.*/
#include "psa/update.h"
#include "psa_client_pv.h"


#define PSA_FWU_WRITE_INPUT_ARRAY_SIZE           (uint32_t)3U
#define PSA_FWU_INSTALL_INPUT_ARRAY_SIZE         (uint32_t)1U
#define PSA_FWU_INSTALL_OUTPUT_ARRAY_SIZE        (uint32_t)2U
#define PSA_FWU_ABORT_INPUT_ARRAY_SIZE           (uint32_t)1U
#define PSA_FWU_QUERY_INOUT_ARRAY_SIZE           (uint32_t)1U
#define PSA_FWU_ACCEPT_INPUT_ARRAY_SIZE          (uint32_t)1U

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

psa_status_t psa_fwu_write(uint32_t image_id,
                           size_t block_offset,
                           const void *block,
                           size_t block_size)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0;
    psa_invec invec[PSA_FWU_WRITE_INPUT_ARRAY_SIZE];
    uint32_t cpt = 0U;

    if (block == NULL)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    for (cpt = 0; cpt < PSA_FWU_WRITE_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);

    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    invec[0].base = &image_id;
    invec[0].len  = sizeof(psa_image_id_t);

    invec[1].base = &block_offset;
    invec[1].len  = sizeof(size_t);

    invec[2].base = block;
    invec[2].len  = block_size;

    status = psa_call(handle, PSA_TYPE_FWU_WRITE, (const psa_invec *)&invec, PSA_FWU_WRITE_INPUT_ARRAY_SIZE, NULL, 0);

    psa_close(handle);

    return status;
}

psa_status_t psa_fwu_install(psa_image_id_t image_id, psa_image_id_t *dependency_uuid, psa_image_version_t *dependency_version)
{
    psa_status_t status   = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0U;
    psa_invec  invec[PSA_FWU_INSTALL_INPUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_FWU_INSTALL_OUTPUT_ARRAY_SIZE];
    uint32_t cpt        = 0U;

    if ((dependency_uuid == NULL) || (dependency_version == NULL))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    for (cpt = 0; cpt < PSA_FWU_INSTALL_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;
    }

    for (cpt = 0; cpt < PSA_FWU_INSTALL_OUTPUT_ARRAY_SIZE; cpt++)
    {
        outvec[cpt].base = NULL;
        outvec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);
    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    invec[0].base  = &image_id;
    invec[0].len   = sizeof(image_id);

    outvec[0].base = dependency_uuid;
    outvec[0].len  = sizeof(psa_image_id_t);

    outvec[1].base = dependency_version;
    outvec[1].len  = sizeof(psa_image_version_t);

    status = psa_call(handle, PSA_TYPE_FWU_INSTALL, (const psa_invec *)&invec, PSA_FWU_INSTALL_INPUT_ARRAY_SIZE,
                                                     (psa_outvec *)&outvec, PSA_FWU_INSTALL_OUTPUT_ARRAY_SIZE);

    psa_close(handle);

    return status;
}


psa_status_t psa_fwu_abort(psa_image_id_t image_id)
{
    psa_status_t status   = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle   = 0U;
    psa_invec  invec[PSA_FWU_ABORT_INPUT_ARRAY_SIZE];
    uint32_t cpt          = 0U;

    for (cpt = 0; cpt < PSA_FWU_ABORT_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);
    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    invec[0].base = &image_id;
    invec[0].len  = sizeof(psa_image_id_t);

    status = psa_call(handle, PSA_TYPE_FWU_ABORT,  (const psa_invec *)&invec, PSA_FWU_ABORT_INPUT_ARRAY_SIZE, NULL, 0);

    psa_close(handle);

    return status;
}


psa_status_t psa_fwu_query(psa_image_id_t image_id, psa_image_info_t *info)
{
    psa_status_t status   = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle   = 0U;
    psa_invec   invec[PSA_FWU_QUERY_INOUT_ARRAY_SIZE];
    psa_outvec outvec[PSA_FWU_QUERY_INOUT_ARRAY_SIZE];
    uint32_t cpt          = 0U;

        if (info == NULL)
        {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

    for (cpt = 0; cpt < PSA_FWU_QUERY_INOUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;

        outvec[cpt].base = NULL;
        outvec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);
    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    invec[0].base  = &image_id;
    invec[0].len   = sizeof(psa_image_id_t);

    outvec[0].base = info;
    outvec[0].len  = sizeof(psa_image_info_t);

    status = psa_call(handle, PSA_TYPE_FWU_QUERY,  (const psa_invec *)&invec,  PSA_FWU_QUERY_INOUT_ARRAY_SIZE
                                                ,  (psa_outvec *)&outvec, PSA_FWU_QUERY_INOUT_ARRAY_SIZE);

    psa_close(handle);

    return status;
}


psa_status_t psa_fwu_request_reboot(void)
{
    psa_status_t status   = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle   = 0U;

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);
    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    status = psa_call(handle, PSA_TYPE_FWU_REQUEST_REBOOT, NULL, 0, NULL, 0);

    psa_close(handle);


    return status;
}


psa_status_t psa_fwu_accept(psa_image_id_t image_id)
{
    psa_status_t status   = PSA_ERROR_GENERIC_ERROR;
    psa_handle_t handle = 0U;
    psa_invec   invec[PSA_FWU_ACCEPT_INPUT_ARRAY_SIZE];
    uint32_t cpt        = 0U;

    for (cpt = 0; cpt < PSA_FWU_ACCEPT_INPUT_ARRAY_SIZE; cpt++)
    {
        invec[cpt].base = NULL;
        invec[cpt].len  = 0U;
    }

    (void)psa_init_signal(PSA_SIGNAL_FW_UPG);
    handle = psa_connect(PSA_SID_FW_UPG, 0);
    status = check_handle_is_valid(handle);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    invec[0].base  = &image_id;
    invec[0].len   = sizeof(psa_image_id_t);

    status = psa_call(handle, PSA_TYPE_FWU_ACCEPT, (const psa_invec *)&invec, PSA_FWU_ACCEPT_INPUT_ARRAY_SIZE, NULL, 0);

    psa_close(handle);


    return status;
}

/* ######################################################################## */
/*                     MODULE PRIVATE API - C-UNSUPPORTED FUNCTIONS         */
/* ######################################################################## */

psa_status_t psa_fwu_request_rollback(uint32_t error)
{
    (void) error;
    return PSA_ERROR_NOT_SUPPORTED;
}

void psa_fwu_get_image_id_iterator(psa_fwu_iterator_t *iterator)
{
    (void) iterator;
    return;
}

bool psa_fwu_get_image_id_next(psa_fwu_iterator_t *iterator)
{
    (void) iterator;
    return PSA_ERROR_NOT_SUPPORTED;
}

bool psa_fwu_get_image_id_valid(psa_fwu_iterator_t *iterator)
{
    (void) iterator;
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t psa_fwu_get_image_id(psa_fwu_iterator_t *iterator, psa_image_id_t *image_id)
{
    (void) iterator;
    (void) image_id;
    return PSA_ERROR_NOT_SUPPORTED;
}
