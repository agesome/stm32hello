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
 * @file          psa_secure_partition.c
 * @brief         File holding the secure partition API implementation
 * @author        Provenrun
 * @maintainer    Provenrun
 * @ingroup       PSA_SECPART
 ******************************************************************************
 * @details      This file intends to implement the different APIs used to
 *               provide for any RoT service the capacity to receive and reply
 *               to incoming PSA APIs
 * @note
 ******************************************************************************
 * @addtogroup  PSA_SECPART
 * @{
 */



/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/*__________________________________________________________________________*/
/* Source the private (and public) API of this Code Module. */
#include "psa_secure_partition_pv.h"
#include "psa/service.h"
#include "psa/error.h"
#include "psa/service_extension.h"
#include "psa/client_extension.h"
/* ######################################################################## */
/*                     COMPILATION CONFIGURATION CHECK                      */
/* ######################################################################## */
/* Consistency and implementation checks of the ukDevices Configuration applied
 *  to this Code Module. */


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
/** @brief C-Array global used to track all incoming and opened connection
 *      This global array can only support up to PSA_SECPART_MAX_CONNECTION connections.
 *
 *      Any RoT service cannot accept more than PSA_SECPART_MAX_CONNECTION simultaneous.
 *
 *      The array of type psa_secpart_handle_t stores several information on the connection.
 *          See psa_secpart_handle_t in psa_secure_partition_pv.h for more info
 * */
MukVAR_DEFINE(
                array_secpart_handle[PSA_SECPART_MAX_CONNECTION],
                psa_secpart_handle_t);

/** @brief Global C-Variable used to track the address of the Exchange Area
 *  used to transmit data from the NSPE to the Secure World and back.
 *
 * Definition of the global C-Variable used to track the address of the NSCall
 *  Exchange Area. This area is used to pass data from the Non-Secure world to
 *  the Secure world.
 *
 * look at the documentation of TukNSCALL_EXCHANGE_AREA for more information
 *
 * */
static MukVAR_DEFINE(nscall_exchange_area, TukNSCALL_EXCHANGE_AREA*);
static MukVAR_DEFINE(nscall_exchange_area_size, TukUINT32);

static struct psa_secpart_irq tab_irq[PSA_MAX_IRQ]= { 0 };
static psa_signal_t psa_pending_signals = 0;


/**
 * @brief C-Variable that allows to store the log level value.
 *
 */
uint8_t sec_part_rot_verbosity_level = 0U;


/* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Functions specific to this Code Module, and part
 *  of its Private API (used only in its internal implementation).
 *
 * NOTE: See the Private API of this module in the 'ukproc_pv.h' include file
 *  for the documentation relative to these C-Functions.
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                     C-FUNCTION - PSA MSG HANDLE MANAGEMENT               */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief This static function does initialize the different size values of an index of array_secpart_handle
 *
 * @usage The array_secpart_handle contains all the information on an opened connection in RoT side.
 *             This function is used in psa_secpart_handle_set() in order to set the invec/outvec value size
 *              and also the offset values for managing the parameters
 *
 * @param[in] (psa_ipc_msg_t*)psa_ipc_msg a pointer to the incoming psa_ipc_msg
 * @param[in] (TukIDX8)index the index of array_secpart_handle to init the values
 *
 * @return void
 */
static void psa_secpart_handle_init_size(psa_ipc_msg_t *psa_ipc_msg, TukIDX8 index)
{
    TukIDX8    counter = PSA_MAX_IOVEC;
    TukUINT32  offset  = 0U;

    for (counter = 0U; counter < PSA_MAX_IOVEC; counter ++)
    {
        array_secpart_handle[index].ipc_msg.in_size[counter]      = psa_ipc_msg->in_size[counter];
        array_secpart_handle[index].ipc_msg.in_offset[counter]    = 0u;
        array_secpart_handle[index].ipc_msg.out_size[counter]     = psa_ipc_msg->out_size[counter];
        array_secpart_handle[index].ipc_msg.out_size_util[counter]= 0U;
        array_secpart_handle[index].ipc_msg.out_offset[counter]   = 0U;

    }

    for (counter = 0U; counter < PSA_MAX_IOVEC; counter ++)
    {
        offset += array_secpart_handle[index].ipc_msg.in_size[counter];
    }

    array_secpart_handle[index].ipc_msg.out_offset[0]= offset;
    offset += array_secpart_handle[index].ipc_msg.out_size[0];
    array_secpart_handle[index].ipc_msg.out_offset[1] = offset;
    offset += array_secpart_handle[index].ipc_msg.out_size[1];
    array_secpart_handle[index].ipc_msg.out_offset[2] = offset;
    offset += array_secpart_handle[index].ipc_msg.out_size[2];
    array_secpart_handle[index].ipc_msg.out_offset[3] = offset;
}


/**
 * @brief This static function add a new connection in the array_secpart_handle
 *
 * @usage The array_secpart_handle contains the information on the opened connection.
 *             This function is used to store a new incoming connection.
 *              This function is called from public API psa_wait()
 *
 * @param[in] (psa_ipc_msg_t*)psa_ipc_msg a pointer to the information on the opened connection to store.
 * @param[in] (TukUKPROC_PUID)client_puid the PUID of the sender (client)
 * @param[out] (psa_signal_t*)signal a pointer to the signal to store the signal of the incoming connection
 * @param[in] (TukINT32)index  the index of the array, if it equals -1 a new connection must be done
 *                              Otherwise it means it is a new request that has been received from an already connection
 *
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed.
 * @retval DukSTATUS_ERR_NO_RESOURCE there is no more room in the array to store the new connection.
 * @retval DukSTATUS_ERR_PARAM  a parameter is invalid.
 * @retval DukSTATUS_INFO_OK The operation was successful.
 */
static TukSTATUS psa_secpart_handle_set(psa_ipc_msg_t *psa_ipc_msg, TukUKPROC_PUID client_puid, psa_signal_t *signal, TukIDX8 index)
{
    TukIDX8        array_psa_msg_index   = PSA_UFALSE;
    TukCOUNT8      array_psa_msg_count   = PSA_UFALSE;
    TukBOOL        free_index            = PSA_UFALSE;
    TukSTATUS      code_status           = DukSTATUS_ERR_UNEXPECTED;
    TukUKAPP_AUID  auid                  = PSA_UFALSE;

    array_psa_msg_count = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);
    if (psa_ipc_msg != NULL)
    {
        if (index == (uint8_t)PSA_SECPART_MAX_CONNECTION_END)
        {
            for (array_psa_msg_index = PSA_UFALSE;
                 array_psa_msg_index < array_psa_msg_count;
                 array_psa_msg_index++)
            {
                if ((array_secpart_handle[array_psa_msg_index].ipc_msg.signal == 0x0U) &&
                    (array_secpart_handle[array_psa_msg_index].ipc_msg.type   == 0x0))
                {
                    free_index = PSA_UTRUE;
                    break;
                }
            }
        }
        else
        {
            free_index = PSA_UTRUE;
            array_psa_msg_index = index;
        }

        if (free_index == PSA_UTRUE)
        {
            array_secpart_handle[array_psa_msg_index].ipc_msg.signal          = psa_ipc_msg->signal;
            array_secpart_handle[array_psa_msg_index].ipc_msg.type            = (int32_t)((uint32_t)psa_ipc_msg->type & PSA_TYPE_MASK);

            if (((uint32_t)psa_ipc_msg->type & PSA_TYPE_MASK) == PSA_TYPE_MASK)
            {
                array_secpart_handle[array_psa_msg_index].ipc_msg.type = PSA_IPC_CONNECT;
            }
            else if (((uint32_t)psa_ipc_msg->type & PSA_TYPE_MASK) == (PSA_TYPE_MASK - 1U))
            {
                array_secpart_handle[array_psa_msg_index].ipc_msg.type = PSA_IPC_DISCONNECT;
            }
            psa_secpart_handle_init_size(psa_ipc_msg, array_psa_msg_index);
            array_secpart_handle[array_psa_msg_index].ipc_msg.block_bundle_id = psa_ipc_msg->block_bundle_id;
            array_secpart_handle[array_psa_msg_index].asserted = PSA_UFALSE;
            array_secpart_handle[array_psa_msg_index].client_puid = client_puid;
            *signal = psa_ipc_msg->signal;
            /*If secure world App*/
            if(((TukUKPROC_PUID)(client_puid) & 0xFFFFFF00U) != ((TukUKPROC_PUID)0xFFFFFF00U))
            {
                if ((index == (uint8_t)PSA_SECPART_MAX_CONNECTION_END) && (ukUKProcGetAttribute(client_puid, DukUKPROC_ATTRIBUTE_TAG_AUID) == DukSTATUS_INFO_OK ))
                {
                    auid = *((TukUINT64 *)&(GVukappUKSVCOutput[4]));
                    array_secpart_handle[array_psa_msg_index].client_id = MukVAL_FIELD_VALUE_GET(
                                                                            DukUKAPP_AUID_ASID_FIELD_LSb,
                                                                            DukUKAPP_AUID_ASID_FIELD_MSb,
                                                                            auid);
                    array_secpart_handle[array_psa_msg_index].ipc_msg.msg_handle = (TukINT32) ((int32_t)(array_psa_msg_index << 16) | array_secpart_handle[array_psa_msg_index].client_id);
                }
                code_status = DukSTATUS_INFO_OK;
            }
            /*If non-secure world App*/
            else
            {
                if (index == (uint8_t)PSA_SECPART_MAX_CONNECTION_END)
                {
                    array_secpart_handle[array_psa_msg_index].client_id = NS_CLIENT_ID;
                    array_secpart_handle[array_psa_msg_index].ipc_msg.msg_handle = NS_CLIENT_HANDLE;
                }
                code_status = DukSTATUS_INFO_OK;
            }
        }
        else
        {
            code_status = DukSTATUS_ERR_NO_RESOURCE;
        }
    }
    else
    {
        code_status = DukSTATUS_ERR_PARAM;
    }
    return code_status;
}


/**
 * @brief This static function returns the associated psa_msg of an index of the array
 *
 * @usage The array_secpart_handle contains the information on the opened connection.
 *             This function is used to retrieve the psa_msg of an index
 *
 * @param[in] (TukINT32)index  the index of the array to retrieve the information
 * @param[out] (psa_msg_t*)psa_msg A pointer to the psa_msg to return
 *
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed.
 * @retval DukSTATUS_INFO_OK The operation was successful.
 */
static TukSTATUS psa_secpart_msg_get(TukIDX8 index, psa_msg_t *psa_msg)
{
    TukSTATUS code_status = DukSTATUS_INFO_OK;

    if (index >= (uint8_t)PSA_SECPART_MAX_CONNECTION)
    {
      code_status = DukSTATUS_ERR_PARAM;
    }
    else
    {
        if ((array_secpart_handle[index].ipc_msg.signal == 0x0U) &&
            (array_secpart_handle[index].ipc_msg.type   == 0x0))
        {
            code_status = DukSTATUS_ERR_UNEXPECTED;
        }
        else
        {
            psa_msg->type        = array_secpart_handle[index].ipc_msg.type;
            psa_msg->handle      = array_secpart_handle[index].ipc_msg.msg_handle;
            psa_msg->client_id   = array_secpart_handle[index].client_id;
            psa_msg->rhandle     = array_secpart_handle[index].rhandle;
            psa_msg->in_size[0]  = array_secpart_handle[index].ipc_msg.in_size[0];
            psa_msg->in_size[1]  = array_secpart_handle[index].ipc_msg.in_size[1];
            psa_msg->in_size[2]  = array_secpart_handle[index].ipc_msg.in_size[2];
            psa_msg->in_size[3]  = array_secpart_handle[index].ipc_msg.in_size[3];
            psa_msg->out_size[0] = array_secpart_handle[index].ipc_msg.out_size[0];
            psa_msg->out_size[1] = array_secpart_handle[index].ipc_msg.out_size[1];
            psa_msg->out_size[2] = array_secpart_handle[index].ipc_msg.out_size[2];
            psa_msg->out_size[3] = array_secpart_handle[index].ipc_msg.out_size[3];
            code_status = DukSTATUS_INFO_OK;
        }
    }

    return code_status;
}


/**
 * @brief This static function returns the associated psa_msg from a signal
 *
 * @usage The array_secpart_handle contains the information on the opened connection.
 *             This function is used to retrieve the psa_msg of a signal which has not been yet asserted.
 *
 * @param[in] (psa_signal_t)signal  the signal to get the associated psa_msg
 * @param[out] (psa_msg_t*)psa_msg A pointer to the psa_msg to return
 *
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed.
 * @retval DukSTATUS_ERR_NOT_FOUND no matching non-asserted signal has been found
 * @retval DukSTATUS_INFO_OK The operation was successful.
 */
static TukSTATUS psa_secpart_handle_get(psa_signal_t signal, psa_msg_t *psa_msg)
{
    TukIDX8    array_handle_index    = PSA_UFALSE;
    TukCOUNT8  array_handle_count    = PSA_UFALSE;
    TukIDX8    found_index           = PSA_UFALSE;
    TukSTATUS  code_status           = DukSTATUS_ERR_UNEXPECTED;

    if ((psa_msg != NULL) && (signal > 0U))
    {
        array_handle_count = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);
        for (array_handle_index = PSA_UFALSE;
             array_handle_index < array_handle_count;
             array_handle_index++)
        {
            if ((array_secpart_handle[array_handle_index].ipc_msg.signal   == signal) &&
                (array_secpart_handle[array_handle_index].asserted == PSA_UFALSE))
            {
                array_secpart_handle[array_handle_index].asserted = PSA_UTRUE;
                found_index = PSA_UTRUE;
                break;
            }
        }
        if (found_index == PSA_UTRUE)
        {
            code_status = psa_secpart_msg_get(array_handle_index, psa_msg);
        }
        else
        {
            code_status = DukSTATUS_ERR_NOT_FOUND;
        }
    }
    else
    {
        code_status = DukSTATUS_ERR_PARAM;
    }

    return code_status;
}


/**
 * @brief This static function returns the array of the index containing the given handle
 *
 * @usage The array_secpart_handle contains the information on the opened connection.
 *             This function is used to retrieve the index of the array_secpart_handle from a matching given handle.
 *
 * @implementation the psa_handle_t is structured in the following
 *                              the 16LSB contains the ASID (short unique ID of the client)
 *                              the 16MSB contains the index number in the array_secpart_handle
 *
 * @param[in] (psa_handle_t)handle the handle to find in the array
 * @param[out] (TukINT16*)index A pointer to a uint16_t index
 *
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed.
 * @retval DukSTATUS_ERR_IDENTIFIER the index contained in the handle 16MSB is invalid
 * @retval DukSTATUS_ERR_NOT_FOUND no matching non-asserted signal has been found
 * @retval DukSTATUS_INFO_OK The operation was successful.
 */
static TukSTATUS psa_secpart_check_handle(psa_handle_t handle, TukIDX8 *index)
{
    TukSTATUS  status_code           = DukSTATUS_ERR_UNEXPECTED;
    TukUINT32  index_array           = 0U;
    TukIDX8    array_handle_index    = PSA_UFALSE;
    TukCOUNT8  array_handle_count    = PSA_UFALSE;

    if (((handle <= 0) && (handle != -1)) || (index == NULL))
    {
        status_code = DukSTATUS_ERR_PARAM;
    }
    else
    {
        *index = PSA_SECPART_MAX_CONNECTION_END;
        if (handle == NS_CLIENT_HANDLE)
        {
            // we need to find in the array the appropriate index
            // because it can only have only one non secure handle at a time.
            array_handle_count = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);
            for (array_handle_index = PSA_UFALSE;
                 array_handle_index < array_handle_count;
                 array_handle_index++)
            {
                if (array_secpart_handle[array_handle_index].ipc_msg.msg_handle == NS_CLIENT_HANDLE)
                {
                    *index = array_handle_index;
                    break;
                }
            }
            if (*index == (uint8_t)PSA_SECPART_MAX_CONNECTION_END)
            {
                status_code = DukSTATUS_ERR_NOT_FOUND;
            }
            else
            {
                status_code = DukSTATUS_INFO_OK;
            }
        }
        else
        {
            index_array = MukVAL_FIELD_VALUE_GET(16u,
                                                 31u,
                                                (TukUINT32)handle);

            if (index_array >= MukARRAY_ELEMENTS_COUNT(array_secpart_handle)) {
                status_code = DukSTATUS_ERR_IDENTIFIER;
            }
            else
            {
                if(array_secpart_handle[index_array].ipc_msg.msg_handle == handle)
                {
                    *index = (TukIDX8)(index_array&0xFFU);
                    status_code = DukSTATUS_INFO_OK;
                }
                else
                {
                    status_code = DukSTATUS_ERR_NOT_FOUND;
                }
            }
        }
    }
    return status_code;
}


/**
 * @brief This static function is a basic memcpy helper
 *
 * @usage This function helper is a very basic memcpy helper.
 *
 * @implementation it is up to the caller to guarantee the buffers are valid.
 *
 * @param[out] (void*)dst a pointer to a valid destination buffer
 * @param[in]  (void*)src a pointer to a valid source buffer
 * @param[in]  (uint32_t)nb_bytes the number of bytes to cppy from source buffer to destination buffer
 *
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_SUCCESS the operation was a success
 */
static psa_status_t secpart_memcpy(void *dst, void *src, uint32_t nb_bytes)
{
    TukCHAR   *cdst  = (TukCHAR*)dst;
    TukCHAR   *csrc  = (TukCHAR*)src;
    TukUINT32  index = 0U;

    for (index = 0; index < nb_bytes; index++)
    {
        cdst[index] = csrc[index];
    }

    return PSA_SUCCESS;
}


/**
 * @brief This static function is used to fill a psa_secpart_reply_t message
 *
 * @usage: The public api psa_reply() used sub-functions to reply to an incoming request.
 *              This function is an helper to fill a reply_msg.
 *
 * @param[out] (psa_secpart_reply_t*)reply_msg: a pointer to a psa_secpart_reply_t to fill
 * @param[in]  (TukINT16)index: the index of the associated connection to reply
 * @param[in]  (psa_status_t)psa_status: the psa_status to reply to the client
 *
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed.
 * @retval DukSTATUS_ERR_IDENTIFIER the index contained in the handle 16MSB is invalid
 * @retval DukSTATUS_INFO_OK The operation was successful.
 */
static TukSTATUS psa_secpart_fill_reply(psa_secpart_reply_t *reply_msg, TukIDX8 index, psa_status_t psa_status)
{
    TukSTATUS error_status             = DukSTATUS_ERR_UNEXPECTED;
    TukCOUNT8 array_psa_msg_count      = 0U;
    TukIDX8 inoutvec_index             = 0U;
    array_psa_msg_count                = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);

    if ((index < array_psa_msg_count) && (index < (uint8_t)PSA_SECPART_MAX_CONNECTION_END))
    {
        reply_msg->msg_handle = array_secpart_handle[index].ipc_msg.msg_handle;
        for (inoutvec_index = 0; inoutvec_index < PSA_MAX_IOVEC; inoutvec_index++)
        {
            reply_msg->out_size[inoutvec_index] = array_secpart_handle[index].ipc_msg.out_size_util[inoutvec_index];
            if (array_secpart_handle[index].ipc_msg.out_size_util[inoutvec_index] == 0U)
            {
                reply_msg->out_offset[inoutvec_index] = 0;
            }
            else
            {
                reply_msg->out_offset[inoutvec_index] = array_secpart_handle[index].ipc_msg.out_offset[inoutvec_index];
            }
            error_status = DukSTATUS_INFO_OK;
        }
        reply_msg->status = psa_status;
    }
    else
    {
        error_status = DukSTATUS_ERR_IDENTIFIER;
    }
    return error_status;
}


/**
 * @brief This static function is used to free a room in the array_secpart_handle
 *
 * @usage: Once a connection is closed, the information stored in the array_secpart_handle must be freed
 *
 * @param[in] (TukINT16)index: the index of the connection to remove.
 *
 *
 * @return (void)
 */
static void psa_secpart_free_handle(TukIDX8 index)
{
    TukCOUNT8  array_psa_msg_count  = 0U;
    TukIDX8    inoutvec_index       = 0U;

    array_psa_msg_count = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);
    if ((index < array_psa_msg_count) && (index < (uint8_t)PSA_SECPART_MAX_CONNECTION_END))
    {
        array_secpart_handle[index].client_id = 0U;
        array_secpart_handle[index].rhandle = 0U;
        array_secpart_handle[index].asserted = 0U;
        array_secpart_handle[index].client_puid = 0U;
        array_secpart_handle[index].ipc_msg.signal = 0U;
        array_secpart_handle[index].ipc_msg.type = 0U;
        array_secpart_handle[index].ipc_msg.msg_handle = 0U;
        array_secpart_handle[index].ipc_msg.block_bundle_id = 0U;
        for (inoutvec_index = 0; inoutvec_index < PSA_MAX_IOVEC; inoutvec_index++)
        {
            array_secpart_handle[index].ipc_msg.in_size[inoutvec_index] = 0U;
            array_secpart_handle[index].ipc_msg.in_offset[inoutvec_index] = 0U;
            array_secpart_handle[index].ipc_msg.out_offset[inoutvec_index] = 0U;
            array_secpart_handle[index].ipc_msg.out_size[inoutvec_index] = 0U;
            array_secpart_handle[index].ipc_msg.out_size_util[inoutvec_index] = 0U;
        }
    }
}

/**
 * @brief This static function is used to reply to an incoming request.
 *
 * @usage: The public api psa_reply() used sub-functions to reply to an incoming request.
 *              This function is an helper to reply the incoming request.
 *
 * @param[out] (psa_secpart_reply_t*)reply_msg: a pointer to a psa_secpart_reply_t to fill
 * @param[in]  (TukINT16)index: the index of the associated connection to reply
 * @param[in]  (psa_status_t)psa_status: the psa_status to reply to the client
 *
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_SUCCESS the operation was a success
 * @retval PSA_ERROR_GENERIC_ERROR The operation was successful.
 */
static psa_status_t psa_secpart_reply(TukIDX8 index, psa_status_t status)
{
    TukSTATUS            status_code       = DukSTATUS_ERR_UNEXPECTED;
    psa_status_t         psa_status        = PSA_ERROR_GENERIC_ERROR;
    TukIPC_MSG          *ipc_msg_addr      = NULL;
    TnsPSA_MSG          *ns_ipc_msg_addr   = NULL;
    psa_secpart_reply_t *reply_msg         = NULL;


    /*If reply to secure world*/
    if (array_secpart_handle[index].client_id != NS_CLIENT_ID)
    {
        ipc_msg_addr = (TukIPC_MSG *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);
        reply_msg = (psa_secpart_reply_t*) &(ipc_msg_addr->Content.UKProcRawData[0]);
        status_code = psa_secpart_fill_reply(reply_msg, index, status);
        if (status_code == DukSTATUS_INFO_OK)
        {
            status_code = ukSharedBufferTransfer(array_secpart_handle[index].ipc_msg.block_bundle_id, DukUKPROC_PUID_OWNER);
            (void)ukIPCSendDataToProcess(array_secpart_handle[index].client_puid,
                        (DukIPC_MODE_SEND_BLOCKING_FLAG |
                            DukIPC_MODE_TIMEOUT_INFINITE ));
        }
    }
    /*If reply to non-secure world*/
    else
    {
        nscall_exchange_area->ServiceID = 0xFFFFFFFFU;
        ns_ipc_msg_addr = (TnsPSA_MSG *)&(nscall_exchange_area->Data);
        reply_msg       = (psa_secpart_reply_t *)&(ns_ipc_msg_addr->ns_ipc_msg);
        status_code     = psa_secpart_fill_reply(reply_msg, index, status);

        /* Discard the address in nscall_exchange_area to prevent reuse. */
        nscall_exchange_area = NULL;
        nscall_exchange_area_size = 0U;

        /** To let the NS world know that the reply is ready.
         * filtering everything means that we can't receive any messages
         */
        status_code = ukIPCReceive(DukUKPROC_PUID_ANY, 0);

    }

    if (status_code == DukSTATUS_INFO_OK)
    {
        psa_status = PSA_SUCCESS;
    }
    else
    {
        psa_status = PSA_ERROR_GENERIC_ERROR;
    }
    return psa_status;
}


/**
 * @brief This static function is used to check the signal given in parameter of psa_wait() is correct
 *
 *
 * @param[in] (psa_signal_t)psa_signal: the psa_signal to check
 *
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval 0  The signal is not a RoT Service signal
 * @retval 1  The signal is a valid RoT Service signal
 */
static psa_status_t isRoTServiceSignal(psa_signal_t psa_signal)
{
    psa_status_t status = PSA_ERROR_DOES_NOT_EXIST;
    psa_signal_t signal_supported = ( PSA_SIGNAL_STORAGE
                                 | PSA_SIGNAL_CRYPTO
                                 | PSA_SIGNAL_FW_UPG
                                 | PSA_SIGNAL_ATTESTATION
                                 | PSA_SIGNAL_SKELETON );

    if ((psa_signal & signal_supported) != PSA_UFALSE)
    {
        status = PSA_SUCCESS;
    }
    return status;
}


/**
 * @brief This static function is used to check the Type of Message is a RoT service
 *
 *
 * @usage : this function will - with the given index parameter -  check the Type Message requested is valid
 *
 * @param[in] (TukINT16)index : the index of the array holding the information of the connection
 *
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval 0  The signal is not a RoT Service signal
 * @retval 1  The signal is a valid RoT Service signal
 */
static psa_status_t isRoTServiceType(TukIDX8 index)
{
    psa_status_t type_is_rotservice    = PSA_ERROR_GENERIC_ERROR;
    TukCOUNT8 array_psa_msg_count      = 0U;
    array_psa_msg_count                = MukARRAY_ELEMENTS_COUNT(array_secpart_handle);
    if ((index < array_psa_msg_count) && (index < (uint8_t)PSA_SECPART_MAX_CONNECTION_END))
    {
        if((PSA_IPC_CONNECT == array_secpart_handle[index].ipc_msg.type)
         ||(PSA_IPC_DISCONNECT == array_secpart_handle[index].ipc_msg.type))
         {
            type_is_rotservice = PSA_UFALSE;
        }
        else
        {
            type_is_rotservice = PSA_UTRUE;
        }
    }
    else
    {
        type_is_rotservice = PSA_UFALSE;
    }

    return type_is_rotservice;
}

/**
 * @brief This static function is used to check if the call comes from non-secure world
 *
 *
 * @usage : This function will  check if the call comes from non-secure world
 *          It should only be used after receiving a message with the ukIPCReceive function
 *
 * @param[out] (TukADDRESSBLOCK*)nsea_ab: a pointer to the incoming NS Exchange Area.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_UFALSE   The call comes from secure World
 * @retval PSA_UTRUE    The call comes from non-secure World
 *
 *
 */
static psa_status_t isNSCALL(TukADDRESSBLOCK *nsea_ab)
{
    psa_status_t is_nscall   = PSA_UFALSE;
    TukIPC_MSG *ipc_msg_addr = NULL;

    ipc_msg_addr = (TukIPC_MSG *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);

    if (ipc_msg_addr->Nature == DukIPC_MSG_NATURE_NSWORLD_REQUEST)
    {
        /* The received IPC Message is an NSCall */
        is_nscall = PSA_UTRUE;
        /* Cast the structure to a sub-type */
        TukIPC_MSG_NSCall *ipc_msg_nscall_addr = (void*) ipc_msg_addr;
        /* Fill the output parameter */
        nsea_ab->Start32  = ipc_msg_nscall_addr->Start32;
        nsea_ab->Length32 = ipc_msg_nscall_addr->Length32;
    }

    return is_nscall;
}


psa_status_t uk_enable_irq (TukPIRQ_MCU_IDX pirq_mcu_idx_i , uint32_t signal_id_i)
{
    TukSTATUS status_code = DukSTATUS_ERR_PARAM;
    size_t index = 0;

    if ( (signal_id_i > PSA_MASK_IRQ) || (signal_id_i & (signal_id_i-1U)) )
    {
        MukappDBGT_ERR_PFNL("uk_enable_irq invalid IRQ signal ID %#8x ",
                            signal_id_i);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ( pirq_mcu_idx_i > DukPIRQ_IDX_MAX )
    {
        MukappDBGT_ERR_PFNL("uk_enable_irq invalid Index of a Peripheral Interrupt Request %#8x ",
                            pirq_mcu_idx_i);
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    for (index = 0; index < PSA_MAX_IRQ ; index++)
    {
        if (tab_irq[index].signal_id == signal_id_i)
        {
            MukappDBGT_ERR_PFNL("uk_enable_irq the IRQ signal ID %#8x was already registered",
                                signal_id_i);
            return PSA_ERROR_ALREADY_EXISTS;
        }
        if (tab_irq[index].pirq_mcu_idx == pirq_mcu_idx_i)
        {
            MukappDBGT_ERR_PFNL("uk_enable_irq the Index of a Peripheral Interrupt Request %#8x was already registered",
                                pirq_mcu_idx_i);
            return PSA_ERROR_ALREADY_EXISTS;
        }
    }

    index = 0;
    while(index < PSA_MAX_IRQ)
    {
        if (tab_irq[index].signal_id == 0U)
        {

            status_code = ukPeripheralIRQRegister(pirq_mcu_idx_i ,0, &(tab_irq[index].pirq_reg_id));
            if (status_code != DukSTATUS_INFO_OK)
            {
                MukappDBGT_ERR_PFNL("uk_enable_irq internal error on kernel registration of the index MCU %#8x, got status %Ks",
                                    pirq_mcu_idx_i,status_code);
                return PSA_ERROR_PROGRAMMER_ERROR;

            }
            status_code = ukPeripheralIRQPerformAction(tab_irq[index].pirq_reg_id, DukPIRQ_ACTION_ENABLE);
            if (status_code != DukSTATUS_INFO_OK)
            {
                MukappDBGT_ERR_PFNL("uk_enable_irq internal error on kernel registration of the index MCU %#8x, got status %Ks",
                                    pirq_mcu_idx_i,status_code);
                return PSA_ERROR_PROGRAMMER_ERROR;

            }
            tab_irq[index].pirq_mcu_idx = pirq_mcu_idx_i;
            tab_irq[index].signal_id    = signal_id_i;
            return PSA_SUCCESS;
        }
        else
        {
            index++;
        }
    }
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t uk_disable_irq (uint32_t signal_id_i)
{
    TukSTATUS status_code = DukSTATUS_ERR_PARAM;
    size_t index = 0;

    if ( signal_id_i > PSA_MASK_IRQ )
    {
        MukappDBGT_ERR_PFNL("uk_disable_irq invalid IRQ signal ID %#8x ",
                            signal_id_i);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    for (index = 0; index < PSA_MAX_IRQ ; index++)
    {
        if (tab_irq[index].signal_id & signal_id_i)
        {
            status_code = ukPeripheralIRQUnregister(tab_irq[index].pirq_reg_id);
            if (status_code != DukSTATUS_INFO_OK)
            {
                MukappDBGT_ERR_PFNL("uk_disable_irq internal error on kernel unregistration of the index MCU %#8x and signal IRQ %#8x, got status %Ks",
                                    tab_irq[index].pirq_mcu_idx,tab_irq[index].signal_id,status_code);
                return PSA_ERROR_PROGRAMMER_ERROR;
            }
            tab_irq[index].pirq_reg_id   = 0;
            tab_irq[index].pirq_mcu_idx  = 0;
            tab_irq[index].signal_id     = 0;
        }
    }
    return PSA_SUCCESS;
}



/* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Functions specific to this Code Module, and part
 *  of its Private API (used only in its internal implementation).
 *
 * NOTE: See the Private API of this Code Module in the "ukdev_gpio_pv.h"
 *  include file for the documentation relative to these C-Functions.
 */

 void psa_panic(void)
{
     ukUKProcExit(DukBOOL_TRUE, DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR);
}


void psa_eoi(psa_signal_t irq_signal)
{
    TukSTATUS       status_code     = DukSTATUS_ERR_PARAM;
    size_t i = 0;

    if((psa_pending_signals & irq_signal) == 0U) {
        MukappDBGT_ERR_PFNL("psa_eoi invalid signal %#8x",
                             irq_signal);
        psa_panic();
    }

    if ( (irq_signal < PSA_SIGNAL_IRQ1) || (irq_signal > PSA_MASK_IRQ) )
    {
        MukappDBGT_ERR_PFNL("psa_eoi invalid IRQ signal %#8x ",
                            irq_signal);
        psa_panic();
    }

    for (i=0 ; i<PSA_MAX_IRQ ;i++)
    {
        if( tab_irq[i].signal_id & irq_signal )
        {
            status_code = ukPeripheralIRQPerformAction((tab_irq[i].pirq_reg_id), DukPIRQ_ACTION_ACKNOWLEDGE);
            if (status_code != DukSTATUS_INFO_OK)
            {
                MukappDBGT_ERR_PFNL("psa_eoi internal error %Ks doing eoi on signal %#8x",
                                     status_code, irq_signal);
                psa_panic();
            }
            psa_pending_signals &= ~ tab_irq[i].signal_id;
        }
    }
    return;
}



// timeout is not yet implemented
psa_signal_t psa_wait(psa_signal_t signal_mask, uint32_t timeout)
{
    (void)          timeout;
    TukSTATUS       status_code     = DukSTATUS_ERR_PARAM;
    TukIPC_MSG     *ipc_msg_addr    = NULL;
    TnsPSA_MSG     *ns_ipc_msg_addr = NULL;
    TukUKPROC_PUID  ipc_sender_puid = 0x0U;
    TukIDX8         index           = PSA_SECPART_MAX_CONNECTION_END;
    TukADDRESSBLOCK nsea_ab         = {0};

    psa_ipc_msg_t *psa_ipc_msg_addr = NULL;
    psa_signal_t signal             = 0x0U;
    psa_status_t psa_status         = PSA_ERROR_GENERIC_ERROR;

    TukBITMASK32 irqmask = 0;
    size_t i = 0;  /* index used for iterating on PIRQTriggeredBitmask */
    uint8_t j = 0;  /* index used for iterating on PIRQTriggeredBitmask */
    size_t idx = 0U;  /* index used for iterating on tab_irq */


    if (signal_mask == 0U)
    {
        MukappDBGT_ERR_PFNL("psa_wait PROGRAMMER ERROR %#8x is an invalid signal mask",
                             signal_mask);
        psa_panic();
    }

    while((psa_pending_signals & signal_mask) == 0U)
    {

        status_code = ukIPCReceive(DukUKPROC_PUID_ANY ,
                    (DukIPC_MODE_RECEIVE_BLOCKING_FLAG |
                     DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG |
                     DukIPC_MODE_RECEIVING_FILTER_PERIPHERAL_IRQ_FLAG));


        if (status_code == DukSTATUS_INFO_OK) {
            ipc_msg_addr = (TukIPC_MSG *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);
            if (ipc_msg_addr == NULL)
            {
                MukappDBGT_ERR_PFNL("psa_wait internal error, invalid value of ipc_msg_addr: %p",
                                     ipc_msg_addr);
                psa_panic();
            }
            ipc_sender_puid = ipc_msg_addr->SenderPUID;

            if (ipc_sender_puid == DukUKPROC_PUID_UKERNEL && ipc_msg_addr->Nature == DukIPC_MSG_NATURE_PIRQ_TRIGGERED)
            {
                /* If we received an IRQ notification */
                for (i = 0 ; i < DukCONFIG_OPTION_PIRQ_SUPPORTED_COUNT_MAX/32U ; i++)
                {
                    irqmask = ipc_msg_addr->Content.PIRQTriggeredBitmask[i];
                    j = 0;
                    while ((irqmask != 0U) || (j<32U))
                    {
                        if((irqmask & (1U << j)) != 0U) {
                            irqmask &= ~ ( 1U << j);
                            for (idx = 0 ; idx < PSA_MAX_IRQ ; idx++ )
                            {
                                if ( (tab_irq[idx].pirq_mcu_idx) == (i * 32U + j) )
                                {
                                    psa_pending_signals |= (tab_irq[idx].signal_id);
                                }
                            }
                        }
                        j++;
                    }
                }
            }
            else if(isNSCALL(&nsea_ab))
            {
                /* If called from non-secure world */
                /* Retrieve and store the address of the exchange area */
                nscall_exchange_area = (void*)nsea_ab.Start32;
                nscall_exchange_area_size = nsea_ab.Length32;
                ns_ipc_msg_addr = (TnsPSA_MSG *)&(nscall_exchange_area->Data);
                if (ns_ipc_msg_addr != NULL)
                {
                    psa_ipc_msg_addr = (psa_ipc_msg_t *)&(ns_ipc_msg_addr->ns_ipc_msg);
                    if (psa_ipc_msg_addr != NULL)
                    {
                        sec_part_rot_verbosity_level =(uint8_t) (((uint32_t)psa_ipc_msg_addr->type & TYPE_VERBOSITY_LEVEL_MASK) >> TYPE_VERBOSITY_LEVEL_POS);

                        if (((psa_ipc_msg_addr->signal & signal_mask) != PSA_UFALSE)
                            && ((psa_ipc_msg_addr->signal != 0U)
                            && ((psa_ipc_msg_addr->signal & (psa_ipc_msg_addr->signal -1U)) == 0U) ))
                        {
                            if ((psa_ipc_msg_addr->msg_handle != 0) && (psa_secpart_check_handle(psa_ipc_msg_addr->msg_handle, &index) == DukSTATUS_INFO_OK))
                            {
                                status_code = psa_secpart_handle_set(psa_ipc_msg_addr, ipc_sender_puid, &signal, index);
                            }
                            else
                            {
                                status_code = psa_secpart_handle_set(psa_ipc_msg_addr, ipc_sender_puid, &signal, PSA_SECPART_MAX_CONNECTION_END);
                            }
                        }
                        else
                        {
                            status_code = DukSTATUS_ERR_IDENTIFIER;
                            psa_status = PSA_ERROR_GENERIC_ERROR;
                        }
                    }
                    else
                    {
                        status_code = DukSTATUS_ERR_UNEXPECTED;
                        psa_status = PSA_ERROR_GENERIC_ERROR;
                    }
                }
                else
                {
                    status_code = DukSTATUS_ERR_UNEXPECTED;
                    psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                }
                if (status_code == DukSTATUS_INFO_OK)
                {
                    return signal;
                }
                else
                {
                    if (status_code == DukSTATUS_ERR_NO_RESOURCE)
                    {
                        psa_status = PSA_ERROR_CONNECTION_BUSY;
                    }
                    (void)psa_secpart_reply(index, psa_status);
                    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
                    {
                        MukappDBGT_ERR_PFNL("psa_wait internal error on the sub-functions psa_secpart_reply, got status %Ks",
                                             status_code);
                        psa_panic();
                    }
                    return 0U; // no signal asserted
                }

            }
            else if(ipc_msg_addr->Nature == DukIPC_MSG_NATURE_UKPROC_DATA)
            {
                ipc_msg_addr = (TukIPC_MSG *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                if (ipc_msg_addr != NULL)
                {
                    psa_ipc_msg_addr = (psa_ipc_msg_t *)&(ipc_msg_addr->Content.UKProcRawData[0]);
                    if (psa_ipc_msg_addr != NULL)
                    {
                        sec_part_rot_verbosity_level =(uint8_t) (((uint32_t)psa_ipc_msg_addr->type & TYPE_VERBOSITY_LEVEL_MASK) >> TYPE_VERBOSITY_LEVEL_POS);

                        if (((psa_ipc_msg_addr->signal & signal_mask) != PSA_UFALSE)
                            && ((psa_ipc_msg_addr->signal != 0U)
                            && ((psa_ipc_msg_addr->signal & (psa_ipc_msg_addr->signal -1U)) == 0U) ))
                        {
                            if ((psa_ipc_msg_addr->msg_handle != 0) && (psa_secpart_check_handle(psa_ipc_msg_addr->msg_handle, &index) == DukSTATUS_INFO_OK))
                            {
                                status_code = psa_secpart_handle_set(psa_ipc_msg_addr, ipc_sender_puid, &signal, index);
                            }
                            else
                            {
                                status_code = psa_secpart_handle_set(psa_ipc_msg_addr, ipc_sender_puid, &signal, PSA_SECPART_MAX_CONNECTION_END);
                            }
                        }
                        else
                        {
                            status_code = DukSTATUS_ERR_IDENTIFIER;
                            psa_status = PSA_ERROR_GENERIC_ERROR;
                        }
                    }
                    else
                    {
                        status_code = DukSTATUS_ERR_UNEXPECTED;
                        psa_status = PSA_ERROR_GENERIC_ERROR;
                    }
                }
                else
                {
                    status_code = DukSTATUS_ERR_UNEXPECTED;
                    psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                }
                if (status_code == DukSTATUS_INFO_OK)
                {
                    return signal;
                }
                else
                {
                    if (status_code == DukSTATUS_ERR_NO_RESOURCE)
                    {
                        psa_status = PSA_ERROR_CONNECTION_BUSY;
                    }
                    (void)psa_secpart_reply(index, psa_status);
                    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
                    {
                        MukappDBGT_ERR_PFNL("psa_wait internal error on the sub-functions psa_secpart_reply, got status %Ks",
                                             status_code);
                        psa_panic();
                    }
                    return 0U; // no signal asserted
                }
            }
        }
        else
        {
            MukappDBGT_ERR_PFNL("psa_wait internal error on kernel receive, got status %Ks",
                                 status_code);
            psa_panic();
        }
    }

    return psa_pending_signals;
}

psa_status_t psa_get(psa_signal_t signal, psa_msg_t *msg)
{
    psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
    TukSTATUS    ukstatus   = DukSTATUS_ERR_UNEXPECTED;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - The msg pointer provided is not a valid memory reference.
    *  - signal has more than a single bit set
    *  - The msg pointer provided is not a valid memory reference.
    *  - The RoT Service signal is not currently asserted  : (not supported in this implementation)*/

    if ((msg == NULL)
       ||((signal & (signal-1U))        != PSA_UFALSE)
       ||(isRoTServiceSignal(signal) == PSA_ERROR_DOES_NOT_EXIST))
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        psa_panic();
    }
    else
    {
        ukstatus = psa_secpart_handle_get(signal, msg);
        if (ukstatus == DukSTATUS_INFO_OK)
        {
            psa_status = PSA_SUCCESS;
        }
        else
        {
            psa_status = PSA_ERROR_DOES_NOT_EXIST;
        }
    }

    return psa_status;
}

size_t psa_read(psa_handle_t msg_handle, uint32_t invec_idx, void *buffer, size_t num_bytes)
{
    TukIDX8               index                   = PSA_SECPART_MAX_CONNECTION_END;
    TukINT16               is_maped               = 0;
    TukADDRESSBLOCK_ID     block_bundle_id        = 0U;
    psa_status_t           psa_status             = 0;
    TukIDX16               accessor               = 0U;
    TukUINT32              offset                 = 0U;
    TukADDRESSBLOCK_INFO  *bundle_info_addr       = NULL;
    TnsPSA_MSG            *ns_ipc_msg_addr        = NULL;
    TukADDRESS32           data_addr_start        = 0U;
    TukLENGTH32            data_container_size    = 0U;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - The msg_handle is invalid.
    *  - invec_idx is equal to, or greater than, PSA_MAX_IOVEC .
    *  - The memory reference for buffer is invalid or not writable.
    *  - The msg_handle does not refer to a request message. */
    if ((psa_secpart_check_handle(msg_handle, &index) != DukSTATUS_INFO_OK)
      ||(invec_idx >= PSA_MAX_IOVEC)
      ||(buffer == NULL))
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        if (num_bytes == 0x0U)
        {
            // nothing to read - PSA API does not consider this as a PROGRAMMER ERROR
            psa_status = PSA_ERROR_INVALID_ARGUMENT;
        }
        else if (isRoTServiceType(index) == (int32_t)PSA_UFALSE)
        {
            // The type of the current handle does not allow read or write psa calls
            psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        }
        else
        {
            //firstly we need to determine what is the offset to read
            if (invec_idx > 0U)
            {
                //first input vector is always at offset 0
                //other input vector needs to be computed according to the size of the previous input vectors
                invec_idx--;
                for (accessor = 0; accessor <= invec_idx; accessor++)
                {
                    offset += array_secpart_handle[index].ipc_msg.in_size[accessor];
                }
                invec_idx++;
            }
            else
            {
                offset = 0U;
            }

            /* If read from secure world*/
            if (array_secpart_handle[index].client_id != NS_CLIENT_ID)
            {
                // before reading, we need to map the shared buffer
                block_bundle_id = array_secpart_handle[index].ipc_msg.block_bundle_id;

                if (ukAddressBlockWindowMap(1, block_bundle_id) == DukSTATUS_INFO_OK)
                {
                    // flag to check before unmap
                    is_maped = 1;
                    //once mapped, we check the Block Info of the shared buffer to retrieve buffer size and buffer address
                    if (ukAddressBlockGetInfo(block_bundle_id) == DukSTATUS_INFO_OK)
                    {
                        bundle_info_addr = (TukADDRESSBLOCK_INFO *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                        data_addr_start = bundle_info_addr->AddressBlockStart;
                        data_container_size = bundle_info_addr->AddressBlockSize;
                    }
                    else
                    {
                        psa_status = PSA_ERROR_GENERIC_ERROR;
                    }
                }
                else
                {
                    psa_status = PSA_ERROR_GENERIC_ERROR;
                }
            }
            /*If read from non-secure world*/
            else
            {
                /* For non-secure we read/write from/to Exchange Area */
                ns_ipc_msg_addr = (TnsPSA_MSG *)&(nscall_exchange_area->Data);
                if (ns_ipc_msg_addr != NULL)
                {
                    data_addr_start = (TukADDRESS32)&(ns_ipc_msg_addr->ns_ipc_data[0]);
                    data_container_size = (nscall_exchange_area_size - sizeof(psa_ipc_msg_t));
                }
                else
                {
                    psa_status = PSA_ERROR_GENERIC_ERROR;
                }
            }

            // now we check the length to read does not exceed buffer size and also input vector' size
            if ((num_bytes > data_container_size) || (offset > data_container_size) || (offset+num_bytes > data_container_size))
            {
                psa_status = PSA_ERROR_INVALID_ARGUMENT;
            }
            else
            {
                if ((array_secpart_handle[index].ipc_msg.in_offset[invec_idx] + num_bytes) >=
                    array_secpart_handle[index].ipc_msg.in_size[invec_idx])
                {
                    num_bytes = array_secpart_handle[index].ipc_msg.in_size[invec_idx] -
                                array_secpart_handle[index].ipc_msg.in_offset[invec_idx];
                }
                if (num_bytes > 0U)
                {
                    psa_status = secpart_memcpy((void*)buffer, (void*)(data_addr_start+offset+array_secpart_handle[index].ipc_msg.in_offset[invec_idx]), num_bytes);
                    array_secpart_handle[index].ipc_msg.in_offset[invec_idx] += num_bytes;
                }
                else
                {
                    // no more byte to read
                    psa_status = PSA_ERROR_GENERIC_ERROR;
                }
            }

            if(is_maped)
            {
                ukAddressBlockWindowUnMap(1);
            }
        }
    }

    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        psa_panic();
    }

    return num_bytes;
}


void psa_write(psa_handle_t msg_handle, uint32_t outvec_idx, const void *buffer, size_t num_bytes)
{
    psa_status_t           psa_status             = DukSTATUS_ERR_UNEXPECTED;
    TukIDX8                index                  = PSA_SECPART_MAX_CONNECTION_END;
    TukINT16               is_maped               = 0;
    TukADDRESSBLOCK_ID     block_bundle_id        = 0U;
    TukUINT32              offset                 = 0U;
    TukADDRESSBLOCK_INFO  *bundle_info_addr       = NULL;
    TnsPSA_MSG            *ns_ipc_msg_addr        = NULL;
    TukADDRESS32           data_addr_start        = 0U;
    TukLENGTH32            data_container_size    = 0U;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - msg_handle is invalid.
    *  - msg_handle does not refer to a request message.
    *  - outvec_idx is equal to, or greater than, PSA_MAX_IOVEC .
    *  - The memory reference for buffer is invalid.
    *  - The call attempts to write data past the end of the client output vector. */
    if ((buffer == NULL) || (outvec_idx >= PSA_MAX_IOVEC))
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        if (psa_secpart_check_handle(msg_handle, &index) == DukSTATUS_INFO_OK)
        {
            if (isRoTServiceType(index) == (int32_t)PSA_UTRUE)
            {
                offset = array_secpart_handle[index].ipc_msg.out_offset[outvec_idx];
                offset+= array_secpart_handle[index].ipc_msg.out_size_util[outvec_idx];

                /* If write for secure world*/
                if (array_secpart_handle[index].client_id != NS_CLIENT_ID)
                {
                    block_bundle_id = array_secpart_handle[index].ipc_msg.block_bundle_id;
                    if (ukAddressBlockWindowMap(1, block_bundle_id) == DukSTATUS_INFO_OK)
                    {
                        // flag to check before unmap
                        is_maped = 1;
                        if (ukAddressBlockGetInfo(block_bundle_id) == DukSTATUS_INFO_OK)
                        {
                            bundle_info_addr = (TukADDRESSBLOCK_INFO *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                            data_addr_start = bundle_info_addr->AddressBlockStart;
                            data_container_size = bundle_info_addr->AddressBlockSize;
                        }
                        else
                        {
                            psa_status = PSA_ERROR_GENERIC_ERROR;
                        }
                    }
                    else
                    {
                        psa_status = PSA_ERROR_GENERIC_ERROR;
                    }
                }
                /*If write for non-secure world*/
                else
                {
                    /* For non-secure we read/write from/to Exchange Area */
                    ns_ipc_msg_addr = (TnsPSA_MSG *)&(nscall_exchange_area->Data);
                    if (ns_ipc_msg_addr != NULL)
                    {
                        data_addr_start = (TukADDRESS32)&(ns_ipc_msg_addr->ns_ipc_data);
                        data_container_size = nscall_exchange_area_size - sizeof(psa_ipc_msg_t);

                    }
                    else
                    {
                        psa_status = PSA_ERROR_GENERIC_ERROR;
                    }
                }

                if ((num_bytes > data_container_size) || (offset > data_container_size)
                    || (array_secpart_handle[index].ipc_msg.out_size_util[outvec_idx]+num_bytes > array_secpart_handle[index].ipc_msg.out_size[outvec_idx]))
                {
                    psa_status = PSA_ERROR_PROGRAMMER_ERROR;
                }
                else
                {
                    psa_status = secpart_memcpy((void*)(data_addr_start+offset), (void*)buffer, num_bytes);
                    array_secpart_handle[index].ipc_msg.out_size_util[outvec_idx]+=num_bytes;
                }

                if(is_maped)
                {
                    ukAddressBlockWindowUnMap(1);
                }
            }
            else
            {
                psa_status = PSA_ERROR_PROGRAMMER_ERROR;
            }
        }
        else
        {
            psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        }
    }

    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        psa_panic();
    }
}


void psa_reply(psa_handle_t msg_handle, psa_status_t status)
{
    TukIDX8 index          = PSA_SECPART_MAX_CONNECTION_END;
    psa_status_t psa_status = PSA_SUCCESS;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - msg_handle is invalid.
    *  - An invalid status code is specified for the type of message :
    *        A status code must be specified, which will normally be sent to the client.
    *        For a connection message, the status codes must conform to:
    *           - PSA_SUCCESS
    *           - PSA_ERROR_CONNECTION_REFUSED
    *           - PSA_ERROR_CONNECTION_BUSY
    *        Using any other status codes is a PROGRAMMER ERROR.*/
    if (psa_secpart_check_handle(msg_handle, &index) != DukSTATUS_INFO_OK)
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        if (array_secpart_handle[index].ipc_msg.type == PSA_IPC_CONNECT
            &&((status != PSA_ERROR_CONNECTION_REFUSED)
            && (status != PSA_ERROR_CONNECTION_BUSY)
            && (status != PSA_SUCCESS)) )
        {
            psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        }

        (void)psa_secpart_reply(index, status);

        if ((array_secpart_handle[index].ipc_msg.type == PSA_IPC_DISCONNECT)
            || (status != PSA_SUCCESS))
        {
            psa_secpart_free_handle(index);
        }
    }

    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        psa_panic();
    }
}

size_t psa_skip(psa_handle_t msg_handle, uint32_t invec_idx, size_t num_bytes)
{
    TukIDX8     index       = PSA_SECPART_MAX_CONNECTION_END;
    psa_status_t status     = PSA_ERROR_GENERIC_ERROR;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - msg_handle is invalid.
    *  - msg_handle does not refer to a request message.
    *  - invec_idx is equal to or greater than PSA_MAX_IOVEC */

    if ((psa_secpart_check_handle(msg_handle, &index) != DukSTATUS_INFO_OK)
       || (invec_idx >= PSA_MAX_IOVEC))
    {
        status = PSA_ERROR_PROGRAMMER_ERROR;
        num_bytes = 0;
    }
    else
    {
        if (isRoTServiceType(index) == (int32_t)PSA_UTRUE)
        {
            if ((num_bytes + array_secpart_handle[index].ipc_msg.in_offset[invec_idx]) >= (array_secpart_handle[index].ipc_msg.in_size[invec_idx]))
            {
                num_bytes = (array_secpart_handle[index].ipc_msg.in_size[invec_idx] - array_secpart_handle[index].ipc_msg.in_offset[invec_idx]);
            }
            array_secpart_handle[index].ipc_msg.in_offset[invec_idx] += num_bytes;
        }
        else
        {
            status = PSA_ERROR_PROGRAMMER_ERROR;
        }
    }

    if (status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        psa_panic();
    }
    return num_bytes;
}

/*psa_set rhandle is stubbed */
void psa_set_rhandle(psa_handle_t msg_handle, void *rhandle)
{
    (void) msg_handle;
    (void) rhandle;

    return;
}

#ifdef EXT_FOR_ITS_ROT
psa_status_t secpart_get_block_bundle_id(psa_handle_t msg_handle, uint32_t *block_bundle_id)
{
    TukIDX8     index   = PSA_SECPART_MAX_CONNECTION_END;
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;

    if ((psa_secpart_check_handle(msg_handle, &index) == DukSTATUS_INFO_OK)
    && (block_bundle_id != NULL))
    {
        *block_bundle_id = array_secpart_handle[index].ipc_msg.block_bundle_id;
        status = PSA_SUCCESS;
    }
    return status;
}


/** special api - to use with care **/
psa_status_t secpart_update_size_in(psa_handle_t msg_handle, uint8_t in_index, uint32_t num_bytes)
{
    TukIDX8     index      = PSA_SECPART_MAX_CONNECTION_END;
    psa_status_t status    = PSA_ERROR_GENERIC_ERROR;

    if (psa_secpart_check_handle(msg_handle, &index) == DukSTATUS_INFO_OK)
    {
        array_secpart_handle[index].ipc_msg.in_size[in_index] = num_bytes;
        status = PSA_SUCCESS;
    }
    return status;
}

psa_status_t secpart_is_handle_from_nsworld(psa_handle_t msg_handle, uint8_t *is_nsworld, TukADDRESSBLOCK* nsea)
{
    psa_status_t status = PSA_ERROR_GENERIC_ERROR;
    TukIDX8      index  = PSA_SECPART_MAX_CONNECTION_END;
    if ((is_nsworld == NULL) || (nsea == NULL))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (psa_secpart_check_handle(msg_handle, &index) == DukSTATUS_INFO_OK)
    {
        if (array_secpart_handle[index].client_id == NS_CLIENT_ID)
        {
            *is_nsworld = 1U;
            if (nscall_exchange_area != NULL)
            {
                nsea->Start32  = (TukADDRESS32)nscall_exchange_area;
                nsea->Length32 = nscall_exchange_area_size;
            }
            status = SUCCESS;
        }
        else{
            *is_nsworld = 0U;
            status = SUCCESS;
        }
    }

    return status;
}
#endif
 /** @} */
