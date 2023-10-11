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
 * @file          psa_client.c
 * @brief         File that implements the different psa client APIs
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_CLIENT
 ******************************************************************************
 * @details This file contains the implementation of the public and private
 *          functions of the Client library.
 *
 *          This file also defines and declares the global array psa_client
 *          which monitors the open connections.
 *
 *          Another global array is used for translating the SID to the AUID
 *          mandatory to convert SID to AUID, which is used to get the PUID.
 *
 *
 *          The client library does rely on ukIPC mechanism in order to
 *          transmit messages between the client application and the RoT Service.
 * @note
 ******************************************************************************
 * @addtogroup    PSA_CLIENT
 * @{
 */

/* Source the uKernel API. */
#ifndef __IARCC__
#include "uk/include/uk.h"
#else
#include "uk.h"
#endif
#include "psa_client_pv.h"
#include "psa/client.h"
#include "psa/client_extension.h"
#include <assert.h>

/* ######################################################################## */
/*                MODULE PRIVATE API - C-VARIABLES GLOBAL                   */
/* ######################################################################## */
/* Hereafter are defined the C-Variables, with global C-Scope, specific to
 *  this Code Module, and part of its Private API (used only in its internal
 *  implementation).
 */

/**
 * @brief C-Struct array that allows to track the connection of a client
 */
static psa_client_t array_psa_client[PSA_CLIENT_MAX_CONNECTION];

/**
 * @brief C-Variable that allows to store the Block bundle ID.
 *
 * Once the label is retrieved by the Client API, it will retrieve the
 * block bundle ID and store it.
 * Only a block (bundle) ID might be used with Ukernel API to do the transfers.
 */
static TukADDRESSBLOCK_ID connexion_block_bundle_id = DukADDRESSBLOCK_ID_INVALID;

/**
 * @brief C-Variable that allows to store the signal number to which RoT service to send the request.
 *
 * The Client must know to which RoT Service the request is for.
 *
 */
static psa_signal_t connexion_signal = 0U;


/**
 * @brief C-Constant array that is used to translate Service ID (SID) to AUID (Ukapp unique ID).
 *
 * The ukernel APIs only works with AUID and SID, a translation must be done.
 *  This variable relates the SID to the AUID.
 *
 * @impl This symbol is weakly defined, and a particular project can override the
 *  definition in order to add another service.

 * At the moment the array is static.
 * The SID number refers to a precise RoT Service, see 'C-CONSTANTS - PSA SID' in psa_client.h for more information
 *
 */
__weak const psa_sid_auid array_sid_auid[4]= {
    {PSA_SID_STORAGE,     0x505254203333A001U},
    {PSA_SID_CRYPTO,      0x505254203333A002U},
    {PSA_SID_ATTESTATION, 0x505254203333A003U},
    {PSA_SID_FW_UPG,      0x505254203334A004U},
};


/**
 * @brief C-Variable that stores the log level value.
 * This value is returned by the client via the public API set_verbosity_level
 */
static uint8_t sec_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;

/* ######################################################################## */
/*                     MODULE PRIVATE API - C-FUNCTIONS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Functions specific to this Code Module, and part
 *  of its Private API (used only in its internal implementation).
 */

/**
 * @brief This static function is a basic memset function.
 *
 * @usage: The caller of this function must guarantee the destination buffer and the size of bytes to set are valid.
 *
 * @param[out] (uint8_t*)dst a pointer to a destination buffer.
 * @param[in] (uint8_t)c a uint8_t value to set.
 * @param[in] (uint32_t)nb_bytes The number in bytes of data to set in the destination buffer
 *
 *
 * @return (void) no value returned.
 */
static void client_memset(uint8_t *dst, uint8_t c, uint32_t nb_bytes)
{
    TukUINT32 index;

    for (index = 0U; index < nb_bytes; index++)
    {
        dst[index] = c;
    }
}


/**
 * @brief This static function is a basic memcpy function.
 *
 * @usage The caller of this function must guarantee the destination buffer, the source buffer and the size of bytes to set are valid.
 *
 * @param[out] (uint8_t*)dst a pointer to a valid destination buffer.
 * @param[in] (const uint8_t*)src a pointer to a valid source buffer.
 * @param[in] (uint32_t)nb_bytes The number in bytes of data to copy from source buffer to destination buffer
 *
 *
 * @return (void) no value returned.
 */
static void client_memcpy(uint8_t *dst, const uint8_t *src, uint32_t nb_bytes)
{
    TukUINT32 index;

    for (index = 0U; index < nb_bytes; index++)
    {
        dst[index] = src[index];
    }
}


/**
 * @brief This static function removes a connection from the array_psa_client array.
 *
 * @usage The array_psa_client stores the handle of the opened connection.
 *         Once the Client API (psa_close() or any error occurred):
 *          The connection is closed and removed from the array_psa_client.
 *
 * @param[in] (TukUINT16)index: the index of the array to delete.
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_OK no error returned
 * @retval DukSTATUS_ERR_PARAM parameter invalid
 */
static TukSTATUS psa_client_free_handle(TukUINT16 index)
{
    TukSTATUS error_status           = DukSTATUS_ERR_PARAM;
    TukCOUNT8 array_psa_client_count;

    array_psa_client_count = (TukCOUNT8)MukARRAY_ELEMENTS_COUNT(array_psa_client);
    if (index < array_psa_client_count)
    {
        array_psa_client[index].msg_handle = 0;
        array_psa_client[index].puid = 0U;

        error_status = DukSTATUS_INFO_OK;
    }
    return error_status;
}


/**
 * @brief This static function checks if a connection is already stored in the array_psa_client.
 *
 * @usage The array_psa_client contains the information on the opened connection.
 *             This function is used to check if the array_psa_client already contains the information on a given connection.
 *
 * @param[in] (psa_client_t*)psa_client: a pointer to a psa_client information.
 *
 * @return (TukIDX8) the index of the array_psa_client, if the connection is found
 *
 * @retval >0  the index of the array
 * @retval 0  error the connection is not present in the array_psa_client
 */
static TukIDX8 psa_client_check_client(psa_client_t *psa_client)
{
    TukIDX8 index;
    TukCOUNT8 array_psa_client_count;
    TukIDX8 exist_index = PSA_UFALSE;

    array_psa_client_count = (TukIDX8)MukARRAY_ELEMENTS_COUNT(array_psa_client);
    for (index = PSA_UFALSE;
                 index < array_psa_client_count;
                 index++)
    {
         if ((array_psa_client[index].msg_handle   == psa_client->msg_handle) &&
             (array_psa_client[index].puid   == psa_client->puid) )
         {
             exist_index = index;
         }
    }
    return exist_index;
}


/**
 * @brief This static function checks if the given handle is stored in the array_psa_client
 *
 * @usage The array_psa_client contains the information on the opened connection.
 *             This function is used to retrieved the index from a given handle.
 *
 * @param[in] (psa_handle_t)handle a connection handle to check
 * @param[out] (TukIDX8*)index a pointer to a uint8_t variable to store the index if found in the array.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_ERROR_DOES_NOT_EXIST the given handle is not stored in the array_psa_client
 * @retval PSA_SUCCESS the given handle has been found.
 */
static psa_status_t psa_client_check_handle(psa_handle_t handle, TukIDX8 *index)
{
    TukIDX8 cpt;
    TukCOUNT8 array_psa_client_count;
    psa_status_t  status              = PSA_ERROR_DOES_NOT_EXIST;
    array_psa_client_count            = (TukCOUNT8)MukARRAY_ELEMENTS_COUNT(array_psa_client);

    for (cpt = PSA_UFALSE;
                 cpt < array_psa_client_count;
                 cpt++)
    {
         if ( array_psa_client[cpt].msg_handle == handle )
         {
             *index = cpt;
             status = PSA_SUCCESS;
             break;
         }
    }
    return status;
}


/**
 * @brief This static function adds the information of a new open connection in the global array_psa_client array.
 *
 * @usage The array_psa_client contains the information on the opened connection.
 *             This function is used to add a new information on the opened connection.
 *
 * @param[in] (psa_client_t*)psa_client a pointer to the information on the opened connection to store.
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED the operation failed
 * @retval DukSTATUS_ERR_NO_RESOURCE there is no more room in the array to store the new connection.
 * @retval DukSTATUS_INFO_OK The operation was successful
 */
static TukSTATUS psa_client_add_to_array(psa_client_t *psa_client)
{
    TukCOUNT8 array_psa_client_count;
    TukIDX8 array_psa_client_index;
    TukUINT8 free_index = PSA_UFALSE;
    TukSTATUS code_status;

    array_psa_client_count = (TukCOUNT8)MukARRAY_ELEMENTS_COUNT(array_psa_client);
    for (array_psa_client_index = PSA_UFALSE;
                 array_psa_client_index < array_psa_client_count;
                 array_psa_client_index++)
    {
         if ((array_psa_client[array_psa_client_index].msg_handle   == 0x0) &&
             (array_psa_client[array_psa_client_index].puid   == 0x0U))
        {
            free_index = PSA_UTRUE;
            break;
        }
    }
    if ((free_index == PSA_UTRUE) && (array_psa_client_index < array_psa_client_count))
    {
        array_psa_client[array_psa_client_index].msg_handle           = psa_client->msg_handle;
        array_psa_client[array_psa_client_index].puid                 = psa_client->puid;
        code_status = DukSTATUS_INFO_OK;
    }
    else
    {
        code_status = DukSTATUS_ERR_NO_RESOURCE;
    }

    return code_status;
}


/**
 * @brief This static function checks if there is one more room in the array_psa_client.
 *
 * @usage The array_psa_client contains the information on the opened connection.
 *             This function is used to check if there is one room free
 *
 *
 * @return (uint32_t) the status of the operation
 *
 * @retval 0  no more room
 * @retval >0  the index of the array of the first available room
 */
static uint32_t psa_client_get_free_member(void)
{
    TukCOUNT8 array_psa_client_count;
    TukIDX8 array_psa_client_index;
    TukUINT32 free_index                = PSA_UFALSE;

    array_psa_client_count = (TukIDX8)MukARRAY_ELEMENTS_COUNT(array_psa_client);
    for (array_psa_client_index = PSA_UFALSE;
                 array_psa_client_index < array_psa_client_count;
                 array_psa_client_index++)
    {
         if ((array_psa_client[array_psa_client_index].msg_handle   == 0x0) &&
             (array_psa_client[array_psa_client_index].puid   == 0x0U))
        {
            free_index++;
        }
    }

    return free_index;
}


/**
 * @brief This static function checks if there is one more room in the array_psa_client.
 *
 * @usage The array_psa_client contains the information on the opened connection.
 *             This function is used to check if there is one room free
 *
 * @param[in] (TukIDX8)index The index to get the information from the arayy : array_psa_client.
 * @param[out] (psa_client_t*)psa_client  a pointer to a psa_client_t that will hold the information contained at the given index.
 *
 * @return (TukSTATUS) the status of the operation
 *
 * @retval DukSTATUS_ERR_UNEXPECTED an error occurred
 * @retval DukSTATUS_INFO_OK the operation was successful
 */
static TukSTATUS psa_client_get_from_index(TukIDX8 index, psa_client_t *psa_client)
{
    TukSTATUS code_status;
    if ((array_psa_client[index].msg_handle   == 0x0) &&
        (array_psa_client[index].puid   == 0x0U) )
    {
        code_status = DukSTATUS_ERR_UNEXPECTED;
    }
    else
    {
        psa_client->msg_handle      = array_psa_client[index].msg_handle;
        psa_client->puid   = array_psa_client[index].puid;
        code_status = DukSTATUS_INFO_OK;
    }

    return code_status;
}

/**
 * @brief This static function provoks a panic, the execution of the current application will stop.
 *
 * @usage This function must be called each time a "PROGRAMMER ERROR" is found
 *          See PSA Client API specification for more details
 *          or read the PSA Client API comments
 *
 * @return void
 *
 */
static void internal_panic(void)
{
     ukUKProcExit(DukBOOL_TRUE, DukUKPROC_TERMINATION_REASON_ABORT_EXIT_IN_ERROR );
}

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                     */
/* ######################################################################## */

void psa_init_label(uint16_t ab_label) {

  TukADDRESSBLOCK_ID connexion_block_id = 0U;

  TukADDRESSBLOCK_LABEL connexion_label = ab_label;
  (void)ukAddressBlockGetIDFromLabel( connexion_label, &connexion_block_id);
  (void)ukAddressBlockGetBundleID(connexion_block_id, &connexion_block_bundle_id);

}

void psa_init_signal(uint32_t signal) {

  connexion_signal = signal;
}
/*
uint32_t psa_version(uint32_t sid) {

    TukSTATUS          status_code;
    TukUKAPP_AUID auid = 0x1234567891011120U;
    TukUKAPP_AIDX aidx = 0U;
    TukUKAPP_ATTRIBUTE_TAG    ukapp_attr = 0U;
    status_code =  ukUKAppGetAIDXFromAUID(auid, &aidx);
    if (status_code == DukSTATUS_INFO_OK) {
       status_code = ukUKAppGetAttribute (aidx, ukapp_attr);
    }
    return status_code;
}
*/


/* The version of the PSA Framework implementation that
 * is providing the runtime services to the caller.
 * The major and minor version are encoded as follows:
 * version[15:8] major version number
 * version[7:0] minor version number
 * */
uint32_t psa_framework_version(void) {

  uint32_t ukcore_release_version;
  uint32_t version_psa;

  ukcore_release_version = ukUKCoreGetReleaseVersion();
  version_psa = ukcore_release_version >> 16;
  return version_psa;
}

psa_status_t set_verbosity_level(uint8_t level_log)
{
    _Static_assert((TFM_PARTITION_LOG_LEVEL_SILENCE == 0), "TFM_PARTITION_LOG_LEVEL_SILENCE definition should be zero");
    if (level_log <= TFM_PARTITION_LOG_LEVEL_DEBUG)
    {
        sec_client_api_rot_verbosity_level = level_log;
        return PSA_SUCCESS;
    }
    else
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
}

psa_status_t get_verbosity_level(uint8_t *level_log)
{
    if (level_log != NULL)
    {
        *level_log = sec_client_api_rot_verbosity_level;
        return PSA_SUCCESS;
    }
    else
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
}


psa_handle_t psa_connect(uint32_t sid, uint32_t version __attribute__((unused))) {

    psa_status_t       psa_status     = PSA_ERROR_GENERIC_ERROR;
    TukUKAPP_AUID      rot_s_auid     = 0U;
    TukUKPROC_PUID     rot_s_puid     = 0U;
    TukSTATUS          status_code;
    TukIPC_MSG         *ipc_msg_addr ;
    psa_ipc_msg_t      *psa_msg;
    psa_client_reply_t *psa_reply;
    psa_handle_t       return_handle;
    TukIDX8            index;
    psa_client_t       client_struct  = {0};
    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - The RoT Service ID is not present.
    *  - The RoT Service version is not supported. (In the current code, the version is not yet managed).
    *  - The caller is not allowed to access the RoT Service. */

    for (index = 0U; index < 4U; index++)
    {
       if (array_sid_auid[index].sid == sid)
        {
            rot_s_auid = array_sid_auid[index].auid;
        }
    }

    if ((rot_s_auid != 0U) && (psa_client_get_free_member()>0U))
    {
        // Retrieve the PUID of the service
        status_code = ukUKProcGetPUIDFromAUID(rot_s_auid, &rot_s_puid);

        if (status_code != DukSTATUS_INFO_OK)
        {
          //PUID could not be retrieved : we generate an ERROR_PROGRAMMER_ERROR
          psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        }

        /* in order to transmit data, we must use the Data Shared UKSVC buffer
         * this is defined by Ukernel mechanism */
        ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);
        psa_msg = (psa_ipc_msg_t * ) &(ipc_msg_addr->Content.UKProcRawData[0]);
        // we can fill the information for the requested message
        psa_msg->signal = connexion_signal;
        /* PSA_IPC_CONNECT is the only type of message in psa_connect() */
        if ( sec_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
        {
          sec_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
        }
        psa_msg->type              = (int32_t)((uint32_t)(sec_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)PSA_IPC_CONNECT & PSA_TYPE_MASK));
        psa_msg->msg_handle        = -1;
        psa_msg->block_bundle_id   =  connexion_block_bundle_id;
        for (index = PSA_UFALSE;
             index < PSA_MAX_IOVEC;
             index++)
        {
            psa_msg->in_size[index]=  0U;
            psa_msg->out_size[index] =  0U;
        }
        (void)ukSharedBufferAddCredentials(psa_msg->block_bundle_id,
                                           rot_s_puid,
                                           (DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG |
                                            DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG) );
        (void)ukSharedBufferTransfer(psa_msg->block_bundle_id, rot_s_puid);
        /* Send the request */
        status_code = ukIPCSendDataToProcess(rot_s_puid,
            (DukIPC_MODE_SEND_BLOCKING_FLAG |
            DukIPC_MODE_TIMEOUT_INFINITE)
        );
        if (status_code == DukSTATUS_INFO_OK)
        {
            /* Then wait for a reply */
            status_code = ukIPCReceive(rot_s_puid,
                (DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG |
                DukIPC_MODE_RECEIVE_BLOCKING_FLAG)
            );
        }
        if (status_code == DukSTATUS_INFO_OK)
        {

           /* receive response */
           ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
           if (ipc_msg_addr != NULL)
           {
                psa_reply = (psa_client_reply_t*) &(ipc_msg_addr->Content.UKProcRawData[0]);
                if (psa_reply != NULL)
                {
                    if (psa_reply->status == PSA_SUCCESS)
                    {
                        return_handle = psa_reply->msg_handle;
                        client_struct.msg_handle = return_handle;
                        client_struct.puid = ipc_msg_addr->SenderPUID;
                        if (psa_client_check_client(&client_struct) == PSA_UFALSE)
                        {
                            (void)psa_client_add_to_array(&client_struct);
                        }
                        /* do not forget to reset the credentials before leaving*/
                        (void)ukSharedBufferResetCredentials(connexion_block_bundle_id);
                        return (return_handle);
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
            else
            {
             psa_status = PSA_ERROR_CONNECTION_REFUSED;
            }
        }
    }
    else if(rot_s_auid == 0U)
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        psa_status = PSA_ERROR_CONNECTION_BUSY;
    }
    /* do not forget to reset the credentials before leaving*/
    (void)ukSharedBufferResetCredentials(connexion_block_bundle_id);

    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
    return 0;
}


void psa_close(psa_handle_t handle) {

    TukIDX8 psa_msg_index             = 0U;
    psa_client_t psa_client           = {0};
    psa_status_t psa_status;
    TukIDX8 index;
    TukUKPROC_PUID rot_s_puid;
    TukIPC_MSG * ipc_msg_addr;
    psa_ipc_msg_t * psa_msg;
    psa_client_reply_t * psa_reply;
    TukSTATUS status_code;


    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - An invalid handle was provided that is not the null handle.
    *  - The connection is currently handling a request.
    * */

    if (handle <= 0) {
      return;
    }
    psa_status = psa_client_check_handle(handle, &psa_msg_index);
    if (psa_status != PSA_SUCCESS) {
      // An invalid handle was provided that is not the null handle.
      psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        client_memset( (uint8_t*)&psa_client, 0, sizeof(psa_client));
        if (psa_client_get_from_index(psa_msg_index, &psa_client) == DukSTATUS_INFO_OK)
        {
            rot_s_puid = psa_client.puid;
            ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);
            if (ipc_msg_addr != NULL)
            {
                psa_msg = (psa_ipc_msg_t *) &(ipc_msg_addr->Content.UKProcRawData[0]);
                if (psa_msg != NULL)
                {
                    /* Fill the information */
                    ipc_msg_addr->Nature = DukIPC_MSG_NATURE_UKPROC_DATA;
                    ipc_msg_addr->SenderTime_us = 0U;
                    /* Fill the psa_ipc_msg info */
                    psa_msg->signal = connexion_signal;
                    /* PSA_IPC_DISCONNECT is the only type of request to send in psa_close()*/
                    if ( sec_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
                    {
                      sec_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
                    }
                    psa_msg->type              = (int32_t)((uint32_t)(sec_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)PSA_IPC_DISCONNECT & PSA_TYPE_MASK));
                    psa_msg->msg_handle      = handle;
                    psa_msg->block_bundle_id = connexion_block_bundle_id;
                    for (index = PSA_UFALSE; index < PSA_MAX_IOVEC; index++)
                    {
                        psa_msg->in_size[index] = 0U;
                        psa_msg->out_size[index] = 0U;
                    }
                    (void)ukSharedBufferAddCredentials(psa_msg->block_bundle_id,
                                                       rot_s_puid,
                                                       (DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG |
                                                        DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG) );
                    (void)ukSharedBufferTransfer(psa_msg->block_bundle_id, rot_s_puid);

                    /* Send the close request to the RoT Service */
                    status_code = ukIPCSendDataToProcess(rot_s_puid,
                        (DukIPC_MODE_SEND_BLOCKING_FLAG |
                        DukIPC_MODE_TIMEOUT_INFINITE)
                    );
                    if (status_code == DukSTATUS_INFO_OK)
                    {
                        /* Wait for the reply */
                        status_code = ukIPCReceive(rot_s_puid,
                            (DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG |
                            DukIPC_MODE_RECEIVE_BLOCKING_FLAG)
                        );
                    }
                    if (status_code == DukSTATUS_INFO_OK)
                    {
                        /* receive response */
                        ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                        if (ipc_msg_addr != NULL)
                        {
                            psa_reply = (psa_client_reply_t * ) &(ipc_msg_addr->Content.UKProcRawData[0]);
                            if (psa_reply != NULL)
                            {
                                /* Remove the connection from the global array
                                 * As this connection is now closed*/
                                (void)psa_client_free_handle(psa_msg_index);
                                if (psa_reply->status == PSA_SUCCESS)
                                {
                                    psa_status = PSA_SUCCESS;
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
                        else
                        {
                            psa_status = PSA_ERROR_PROGRAMMER_ERROR;
                        }
                    }
                    else
                    {
                        psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                    }
               }
            }
        }
    }
    /* do not forget to reset the credentials before leaving*/
    (void)ukSharedBufferResetCredentials(connexion_block_bundle_id);
    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
}

psa_status_t psa_call(psa_handle_t handle, int32_t type,
    const psa_invec * in_vec, size_t in_len, psa_outvec * out_vec, size_t out_len) {

    TukUINT32 out_n_elments                  = 0U;
    TukUINT32 size                           = 0U;
    TukUINT8 is_mapped                       = 0U;
    TukIDX8 index                            = 0U;
    psa_client_t psa_client                  = {0};
    psa_status_t psa_status;
    TukUKPROC_PUID rot_s_puid;
    TukIPC_MSG * ipc_msg_addr;
    psa_ipc_msg_t * psa_msg;
    psa_client_reply_t * psa_reply;
    TukSTATUS status_code;
    TukADDRESSBLOCK_INFO *bundle_info_addr;
    TukLENGTH32 bundle_size;
    TukADDRESS32 bundle_addr_start;
    const psa_invec *invec_ptr;
    psa_outvec *outvec_ptr;
    TukUINT32 written_bytes;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - An invalid handle was passed.
    *  - The connection is already handling a request.
    *  - type < 0
    *  - An invalid memory reference was provided.
    *  - in_len + out_len > PSA_MAX_IOVEC
    *  - The message is unrecognized by the RoT Service or incorrectly formatted.
    * */

    if ((handle <= 0) || (type < 0) || ((in_len + out_len) > PSA_MAX_IOVEC))
    {
        psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
    }
    else if ((((in_len == 0U) && (in_vec != NULL)) || ((out_len == 0U) && (out_vec != NULL)))
           || (((in_len != 0U) && (in_vec == NULL)) || ((out_len != 0U) && (out_vec == NULL))))
    {
        psa_status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        // Get the PUID from the handle
        psa_status = psa_client_check_handle(handle, &index);
        if (psa_status != PSA_SUCCESS)
        {
            // An invalid handle was provided
            psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
        }
        else
        {
            client_memset( (uint8_t*)&psa_client, 0, sizeof(psa_client));
            if (psa_client_get_from_index(index, &psa_client) != DukSTATUS_INFO_OK)
            {
                // puid and handle are equal to 0
                psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
            }
            else
            {
                rot_s_puid = psa_client.puid;

                // Map the shared buffer
                if (ukAddressBlockWindowMap(1, connexion_block_bundle_id) == DukSTATUS_INFO_OK)
                {
                    is_mapped = 1U;
                    //   we check the Block Info of the shared buffer to retrieve buffer size and buffer address
                    if (ukAddressBlockGetInfo(connexion_block_bundle_id) == DukSTATUS_INFO_OK)
                    {
                        bundle_info_addr = (TukADDRESSBLOCK_INFO *)&(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                        bundle_addr_start = bundle_info_addr->AddressBlockStart;
                        bundle_size = bundle_info_addr->AddressBlockSize;

                        if ((in_vec != NULL) && (in_len > 0U))
                        {
                            invec_ptr = in_vec;
                            for (index = 0U; index <= (TukUINT8)(in_len - 1U); index++)
                            {
                                size += invec_ptr->len;
                                invec_ptr ++;
                            }
                        }
                        if ((out_vec != NULL) && (out_len > 0U))
                        {
                            outvec_ptr = out_vec;
                            for (index = 0U; index <= (out_len - 1U); index++)
                            {
                                size += outvec_ptr->len;
                                outvec_ptr++;
                            }
                        }
                        if (size <= bundle_size)
                        {
                            invec_ptr = in_vec;
                            if ((in_len > 0U) && (in_vec != NULL))
                            {
                                written_bytes = 0U;
                                for (index = 0 ; index < in_len; index++)
                                {
                                    client_memcpy((uint8_t*)(bundle_addr_start+written_bytes),
                                                  (const uint8_t*)invec_ptr->base,
                                                  invec_ptr->len);
                                    written_bytes += invec_ptr->len;
                                    invec_ptr++;
                                }
                            }
                            //prepare the TukIPC_MSG
                            ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Input[0]);
                            if (ipc_msg_addr == NULL)
                            {
                                psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                            }
                            else {
                                ipc_msg_addr->Nature = DukIPC_MSG_NATURE_UKPROC_DATA;
                                ipc_msg_addr->SenderTime_us = 0U;
                                // prepare the psa_ipc_msg_t
                                psa_msg = ((psa_ipc_msg_t * ) &ipc_msg_addr->Content.UKProcRawData[0]);
                                if (psa_msg == NULL) {
                                    psa_status =   PSA_ERROR_GENERIC_ERROR;
                                }
                                else {
                                    /* Fill the psa_ipc_msg information */
                                    psa_msg->signal          = connexion_signal;
                                    if ( sec_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
                                    {
                                      sec_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
                                    }
                                    psa_msg->type            = (int32_t)((uint32_t)(sec_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)type & PSA_TYPE_MASK));
                                    psa_msg->msg_handle      = handle;
                                    psa_msg->block_bundle_id = connexion_block_bundle_id;
                                    invec_ptr = in_vec;
                                    outvec_ptr = out_vec;
                                    /* Reset the in/out sizes */
                                    for (index = 0U; index < PSA_MAX_IOVEC; index++)
                                    {
                                        psa_msg->in_size[index] = 0U;
                                        psa_msg->out_size[index] = 0U;
                                    }
                                    /* set the in/out size according to the given parameters */
                                    for (index = 0U; index < in_len; index++)
                                    {
                                        psa_msg->in_size[index] = invec_ptr->len;
                                        invec_ptr++;
                                    }
                                    for (index = 0U; index < out_len; index++)
                                    {
                                        psa_msg->out_size[index] = outvec_ptr->len;
                                        outvec_ptr++;
                                    }
                                    /* Unmap the buffer before Transferring the Shared buffer to the RoT service */
                                    (void)ukAddressBlockWindowUnMap(1);
                                    is_mapped = 0U;
                                    status_code = ukSharedBufferAddCredentials(psa_msg->block_bundle_id,
                                                                 rot_s_puid,
                                                                 (DukADDRESSBLOCK_ATTRIBUTES_CONFIG_READ_FLAG |
                                                                  DukADDRESSBLOCK_ATTRIBUTES_CONFIG_WRITE_FLAG) );
                                    if (status_code == DukSTATUS_INFO_OK)
                                    {
                                        status_code = ukSharedBufferTransfer(psa_msg->block_bundle_id, rot_s_puid);
                                    }

                                    if (status_code == DukSTATUS_INFO_OK)
                                    {
                                     /* Send the request to the RoT */
                                     status_code = ukIPCSendDataToProcess(rot_s_puid,
                                                                         ( DukIPC_MODE_SEND_BLOCKING_FLAG |
                                                                           DukIPC_MODE_TIMEOUT_INFINITE));
                                    }

                                    if (status_code == DukSTATUS_INFO_OK)
                                    {
                                        /* Wait for a reply */
                                        status_code = ukIPCReceive(rot_s_puid,
                                                                    (DukIPC_MODE_RECEIVE_BLOCKING_FLAG |
                                                                     DukIPC_MODE_RECEIVING_FILTER_UKPROC_DATA_FLAG));
                                    }
                                    /* Map the shared buffer */
                                    (void)ukAddressBlockWindowMap(1, connexion_block_bundle_id);
                                    is_mapped = 1U;
                                    if (status_code == DukSTATUS_INFO_OK) {
                                        /* receive response */
                                        ipc_msg_addr = (TukIPC_MSG * ) &(GVukappBlockDataSharedUKSVC.ServiceParameter.Output[0]);
                                        if (ipc_msg_addr != NULL)
                                        {
                                            psa_reply = (psa_client_reply_t * ) &(ipc_msg_addr->Content.UKProcRawData[0]);
                                            if (psa_reply != NULL)
                                            {
                                                if ((psa_reply->status == PSA_SUCCESS) || (psa_reply->status == PSA_ERROR_DEPENDENCY_NEEDED))
                                                {
                                                    for (index = 0U; index < PSA_MAX_IOVEC; index++)
                                                    {
                                                        if(psa_reply->out_size[index] > 0U)
                                                        {
                                                            out_n_elments++;
                                                        }
                                                    }
                                                    if (out_n_elments <= out_len)
                                                    {
                                                        /* copy the returned output data from RoT service
                                                         * to the outvec parameters */
                                                        for (index=0; index< out_len; index++ )
                                                        {
                                                            if ((out_vec[index].base != NULL) && (psa_reply->out_size[index]!=0U))
                                                            {
                                                                client_memcpy((uint8_t*)(out_vec[index].base),
                                                                              (const uint8_t*)(bundle_addr_start + psa_reply->out_offset[index]),
                                                                                  psa_reply->out_size[index]);
                                                            }
                                                            out_vec[index].len = psa_reply->out_size[index];
                                                        }
                                                        psa_status = psa_reply->status;
                                                    }
                                                    else
                                                    {
                                                        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
                                                    }
                                                }
                                                else
                                                {
                                                    psa_status = psa_reply->status;
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
                                    else
                                    {
                                        psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                                    }
                                }
                            }
                        }
                        else
                        {
                            psa_status =  PSA_ERROR_INSUFFICIENT_MEMORY;
                        }
                    }
                    else
                    {
                        psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
                    }
                }
                else
                {
                    psa_status = PSA_ERROR_GENERIC_ERROR;
                }
            }
        }
    }
    if (is_mapped == 1U)
    {
        (void)ukAddressBlockWindowUnMap(1);
    }
    /* do not forget to reset the credentials before leaving*/
    (void)ukSharedBufferResetCredentials(connexion_block_bundle_id);
    /* If a PROGRAMMER ERROR has been detected
     * go into panic */
    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
    return psa_status;
}
