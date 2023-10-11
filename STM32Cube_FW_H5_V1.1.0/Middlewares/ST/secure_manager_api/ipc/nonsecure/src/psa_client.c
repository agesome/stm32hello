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
 * @brief         File that implements the different PSA Client APIs
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       NS_PSA_CLIENT
 ******************************************************************************
 * @details This file contains the implementation of the Public and private
 *          functions of the psa Client library.
 *
 *          it also define and declare the global array psa_client
 *          which monitors the open connections.
 *
 *          Another global array is used for translating the SID to the AUID
 *          mandatory to convert SID to AUID, which is used to get the PUID.
 *
 *
 *          The client library does rely on nscall() mechanism in order to
 *          transmit messages between the client application and the RoT Service.
 * @note
 ******************************************************************************
 * @addtogroup    NS_PSA_CLIENT
 * @{
 */

/* Source the NS_CLIENT API. */
#include "psa_client_pv.h"
#include "psa/client.h"
#include "psa/client_extension.h"

#include "secure_manager.h"
#include "tfm_ns_interface.h"
#include "tfm_psa_call_pack.h"

/* ######################################################################## */
/*                     MODULE PRIVATE API - C-CONSTANTS                     */
/* ######################################################################## */
/* Hereafter are defined the C-Constants, with global C-Scope, specific to
 *  this Code Module, and part of its Private API (used only in its internal
 *  implementation).
 */

const nsdesc_t nsdesc = (nsdesc_t) NSDESC_ADDR;
const nscall_t nscall = (nscall_t) NSCALL_ADDR;


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
psa_client_t array_psa_client[PSA_CLIENT_MAX_CONNECTION];


/**
 * @brief C-Variable that allows to store the signal number to which RoT service to send the request.
 *
 * The Client must know to which RoT Service the request is for.
 *
 */
psa_signal_t connexion_signal = 0U;


/**
 * @brief C-Constant array that is used keep all Services ASIDs (last part of UkApp unique ID).
 *
 * At the moment the array is static.
 * The ASID number refers to a precise RoT Service, see 'C-CONSTANTS - PSA ASID'
 * in psa_client.h for more information.
 *
 * @impl This symbol is weakly defined, and a particular project can override the
 *  definition in order to add another service.
 */
__weak const psa_sid_asid array_sid_asid[5]= {
    {PSA_SID_CLIENT,      PSA_ASID_CLIENT     },
    {PSA_SID_STORAGE,     PSA_ASID_ITS        },
    {PSA_SID_CRYPTO,      PSA_ASID_CRYPTO     },
    {PSA_SID_FW_UPG,      PSA_ASID_FW_UPG     },
    {PSA_SID_ATTESTATION, PSA_ASID_ATTESTATION},
};

/**
 * @brief C-Global Variable to allow sending and receiving between the secure
 * and non-secure worlds using the nscall() function
 *
 */
static SPM_ExchangeArea_t* GVExchangeAreaAddr;

/**
 * @brief C-Global Variable to allow sending and receiving between the secure
 * and non-secure worlds using the nscall() function
 *
 */
static size_t GVExchangeAreaSize;

/**
 * @brief C-Variable that stores the log level value.
 * This value is returned by the client via the public API set_verbosity_level
 */
static uint8_t ns_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;

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
 * @param[out] (void*)dst a pointer to a destination buffer.
 * @param[in] (uint8_t)c a uint8_t value to set.
 * @param[in] (uint32_t)nb_bytes the number in bytes of data to set in the destination buffer
 *
 *
 * @return (void) no value returned.
 */
static void client_memset(void *dst, uint8_t c, uint32_t nb_bytes)
{
    uint8_t *cdst = (uint8_t*)dst;
    uint32_t index;

    for (index = 0U; index < nb_bytes; index++)
    {
        cdst[index] = c;
    }
}


/**
 * @brief This static function is a basic memcpy function.
 *
 * @usage: The caller of this function must guarantee the destination buffer, the source buffer and the size of bytes to set are valid.
 *
 * @param[out] (void*)dst a pointer to a valid destination buffer.
 * @param[in] (void*)src a pointer to a valid source buffer.
 * @param[in] (uint32_t)nb_bytes the number in bytes of data to copy from source buffer to destination buffer
 *
 *
 * @return (void) no value returned.
 */
static void client_memcpy(void *dst, void *src, uint32_t nb_bytes)
{
    uint8_t *cdst  = (uint8_t*)dst;
    uint8_t *csrc  = (uint8_t*)src;
    uint32_t index;

    for (index = 0U; index < nb_bytes; index++)
    {
        cdst[index] = csrc[index];
    }
}

/**
 * @brief This static function gets and stores the SPM exchange area.
 *
 * @usage This function only needs to be called once, as it stores its
 *  results in global variables, which only need to be set once.
 *
 * @return (void) no value returned.
 */
static void get_SPM_exchange_area(void) {
    SPM_Desc_t spm_desc = nsdesc();
    GVExchangeAreaAddr = spm_desc.ea_addr;
    GVExchangeAreaSize = spm_desc.ea_size;
}

/**
 * @brief This static function gets and caches the SPM exchange area address.
 *
 * @return (SPM_ExchangeArea_t*) The address of the SPM exchange area
 */
static SPM_ExchangeArea_t* SPM_exchange_area_addr(void) {
    /* Check if the exchange area has been obtained yet. */
    if (GVExchangeAreaAddr == NULL) {
        /* It hasn't so we go and get it. */
        get_SPM_exchange_area();
    }

    return GVExchangeAreaAddr;
}

/**
 * @brief This static function gets and caches the SPM exchange area address.
 *
 * @return (SPM_ExchangeArea_t*) The address of the SPM exchange area
 */
static size_t SPM_exchange_area_size(void) {
    /* Check if the exchange area has been obtained yet. */
    if (GVExchangeAreaAddr == NULL) {
        /* It hasn't so we go and get it. */
        get_SPM_exchange_area();
    }

    return GVExchangeAreaSize;
}

/**
 * @brief This static function removes a connection from the array_psa_client array.
 * 
 * @usage: The array_psa_client stores the handle of the opened connection.
 *         Once the Client API (psa_close() or any error occurred):
 *          The connection is closed and removed from the array_psa_client.
 *
 * @param[in] (uint16_t)index: the index of the array to delete.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_UTRUE no error returned
 * @retval PSA_ERROR_INVALID_ARGUMENT parameter invalid
 */
static psa_status_t psa_client_free_handle(uint16_t index)
{
    psa_status_t error_status         = PSA_ERROR_INVALID_ARGUMENT;
    uint8_t array_psa_client_count    = 0U;

    array_psa_client_count = MnsARRAY_ELEMENTS_COUNT(array_psa_client);
    if (index < array_psa_client_count)
    {
        array_psa_client[index].msg_handle = 0;
        array_psa_client[index].asid = 0U;
        
        error_status = PSA_UTRUE;
    }
    return error_status;
}


/**
 * @brief This static function checks if a connection is already stored in the array_psa_client.
 *
 * @usage: The array_psa_client contains the information on the opened connection.
 *             This function is used to check if the array_psa_client already contains the information on a given connection.
 *
 * @param[in] (psa_client_t*)psa_client: a pointer to a psa_client information.
 *
 * @return (uint8_t) the index of the array_psa_client, if the connection is found
 *
 * @retval >0 : the index of the array
 * @retval 0 : error the connection is not present in the array_psa_client
 */
static uint8_t psa_client_check_client(psa_client_t *psa_client)
{
    uint8_t   index                  = 0U;
    uint8_t   array_psa_client_count = PSA_UFALSE;
    uint8_t   exist_index            = PSA_UFALSE;

    array_psa_client_count = MnsARRAY_ELEMENTS_COUNT(array_psa_client);
    for (index = PSA_UFALSE;
                 index < array_psa_client_count;
                 index++)
    {
         if ((array_psa_client[index].msg_handle   == psa_client->msg_handle) &&
             (array_psa_client[index].asid   == psa_client->asid) )
         {
             exist_index = index;
         }
    }
    return exist_index;
}


/**
 * @brief This static function checks if the given handle is stored in the array_psa_client
 *
 * @usage: The array_psa_client contains the information on the opened connection.
 *             This function is used to retrieved the index from a given handle.
 *
 * @param[in] (psa_handle_t)handle: a connection handle to check
 * @param[out] (uint8_t*)index a pointer to a uint8_t variable to store the index if found in the array.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_ERROR_DOES_NOT_EXIST the given handle is not stored in the array_psa_client
 * @retval PSA_SUCCESS: the given handle has been found.
 */
static psa_status_t psa_client_check_handle(psa_handle_t handle, uint8_t *index)
{
    uint8_t       cpt                    = PSA_UFALSE;
    uint8_t       array_psa_client_count = PSA_UFALSE;
    psa_status_t  status                 = PSA_ERROR_DOES_NOT_EXIST;

    array_psa_client_count = MnsARRAY_ELEMENTS_COUNT(array_psa_client);
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
 * @usage: The array_psa_client contains the information on the opened connection.
 *             This function is used to add a new information on the opened connection.
 *
 * @param[in] (psa_client_t*)psa_client: a pointer to the information on the opened connection to store.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_ERROR_NOT_SUPPORTED the operation failed
 * @retval PSA_ERROR_INSUFFICIENT_STORAGE there is no more room in the array to store the new connection.
 * @retval PSA_UTRUE The operation was successful
 */
static psa_status_t psa_client_add_to_array(psa_client_t *psa_client)
{
    uint8_t   array_psa_client_count   = PSA_UFALSE;
    uint8_t   array_psa_client_index   = PSA_UFALSE;
    bool      free_index               = PSA_UFALSE;
    psa_status_t code_status           = PSA_ERROR_NOT_SUPPORTED;

    array_psa_client_count = MnsARRAY_ELEMENTS_COUNT(array_psa_client);
    for (array_psa_client_index = PSA_UFALSE;
                 array_psa_client_index < array_psa_client_count;
                 array_psa_client_index++)
    {
         if ((array_psa_client[array_psa_client_index].msg_handle   == 0x0U) &&
             (array_psa_client[array_psa_client_index].asid   == 0x0U))
        {
            free_index = PSA_UTRUE;
            break;
        }
    }
    if (free_index == PSA_UTRUE)
    {
        array_psa_client[array_psa_client_index].msg_handle           = psa_client->msg_handle;
        array_psa_client[array_psa_client_index].asid                 = psa_client->asid;
        code_status = PSA_UTRUE;
    }
    else
    {
        code_status = PSA_ERROR_INSUFFICIENT_STORAGE;
    }

    return code_status;
}


/**
 * @brief This static function checks if there is one more room in the array_psa_client.
 *
 * @usage: The array_psa_client contains the information on the opened connection.
 *             This function is used to check if there is one room free
 *
 *
 * @return (uint32_t) the status of the operation
 *
 * @retval 0 : no more room
 * @retval >0 : the index of the array of the first available room
 */
static uint32_t psa_client_get_free_member(void)
{
    uint8_t   array_psa_client_count   = PSA_UFALSE;
    uint8_t   array_psa_client_index   = PSA_UFALSE;
    uint8_t   free_index               = PSA_UFALSE;

    array_psa_client_count = MnsARRAY_ELEMENTS_COUNT(array_psa_client);
    for (array_psa_client_index = PSA_UFALSE;
                 array_psa_client_index < array_psa_client_count;
                 array_psa_client_index++)
    {
         if ((array_psa_client[array_psa_client_index].msg_handle   == 0x0U) &&
             (array_psa_client[array_psa_client_index].asid   == 0x0U))
        {
            free_index++;
        }
    }

    return free_index;
}


/**
 * @brief This static function checks if there is one more room in the array_psa_client.
 *
 * @usage: The array_psa_client contains the information on the opened connection.
 *             This function is used to check if there is one room free
 *
 * @param[in] (uint8_t)index to get the information from the array array_psa_client.
 * @param[out] (psa_client_t*)psa_client : a pointer to a psa_client_t that will hold the information contained at the given index.
 *
 * @return (psa_status_t) the status of the operation
 *
 * @retval PSA_ERROR_NOT_SUPPORTED an error occurred
 * @retval PSA_UTRUE the operation was successful
 */
static psa_status_t psa_client_get_from_index(uint8_t index, psa_client_t *psa_client)
{
    psa_status_t code_status           = PSA_ERROR_NOT_SUPPORTED;

    if ((array_psa_client[index].msg_handle   == 0x0U) &&
        (array_psa_client[index].asid   == 0x0U) )
    {
        code_status = PSA_ERROR_NOT_SUPPORTED;
    }
    else
    {
        psa_client->msg_handle      = array_psa_client[index].msg_handle;
        psa_client->asid   = array_psa_client[index].asid;
        code_status = PSA_UTRUE;
    }

    return code_status;
}

/**
 * @brief This static function provoks a panic, the execution of the current application will stop.
 *
 * @usage: This function must be called each time a "PROGRAMMER ERROR" is found
 *          See PSA Client API specification for more details
 *          or read the PSA Client API comments
 *
 * @return void
 *
 */
static void internal_panic(void)
{
     return;
}
/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                     */
/* ######################################################################## */


static void veener_psa_init_signal(uint32_t signal) {

  connexion_signal = signal;
}



/**
 * Not yet implemented
 *
 * */

static uint32_t veener_psa_version(uint32_t sid __attribute__((unused))) {
    return PSA_UFALSE;
}


/**
 * The version of the PSA Framework implementation that
 * is providing the runtime services to the caller.
 * The major and minor version are encoded as follows:
 * version[15:8] major version number
 * version[7:0] minor version number
 * */

static psa_status_t veener_set_verbosity_level(uint32_t arg0 , 
                                             uint32_t arg1  __attribute__((unused)), 
                                             uint32_t arg2  __attribute__((unused)), 
                                             uint32_t arg3  __attribute__((unused))) 
{
    uint8_t level_log = (uint8_t) arg0; 

    _Static_assert((TFM_PARTITION_LOG_LEVEL_SILENCE == 0), "TFM_PARTITION_LOG_LEVEL_SILENCE definition should be zero");
    if (level_log <= TFM_PARTITION_LOG_LEVEL_DEBUG)
    {
        ns_client_api_rot_verbosity_level = level_log;
        return PSA_SUCCESS;
    }
    else
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
}
static psa_status_t veener_get_verbosity_level(uint32_t arg0 , 
                                             uint32_t arg1  __attribute__((unused)), 
                                             uint32_t arg2  __attribute__((unused)), 
                                             uint32_t arg3  __attribute__((unused))) 
{
    uint8_t *level_log           = (uint8_t *) arg0;

    if (level_log != NULL)
    {
        *level_log = ns_client_api_rot_verbosity_level;
        return PSA_SUCCESS;
    }
    else
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
}

/**
 * Not yet implemented
 *
 * */
static uint32_t veener_psa_framework_version(uint32_t arg0  __attribute__((unused)), 
                                             uint32_t arg1  __attribute__((unused)), 
                                             uint32_t arg2  __attribute__((unused)), 
                                             uint32_t arg3  __attribute__((unused))) 
{

  return PSA_UFALSE;
}

static psa_handle_t veener_psa_connect(uint32_t arg0 , 
                                       uint32_t arg1  __attribute__((unused)), 
                                       uint32_t arg2  __attribute__((unused)), 
                                       uint32_t arg3  __attribute__((unused))) 
{

    psa_status_t       psa_status          = PSA_ERROR_GENERIC_ERROR;
    psa_status_t       nscall_status       = PSA_ERROR_GENERIC_ERROR;
    uint16_t           rot_s_asid          = 0x0;
    SPM_ExchangeArea_t *exchange_area_addr = NULL;
    TnsPSA_MSG         *ns_ipc_msg_addr    = NULL;
    psa_ipc_msg_t      *psa_msg            = NULL;
    psa_client_reply_t *psa_reply          = NULL;
    psa_handle_t       return_handle       = 0;
    uint8_t            index               = PSA_UFALSE;
    psa_client_t       client_struct       = {0};
    uint32_t           sid                = arg0;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - The RoT Service ID is not present.
    *  - The RoT Service version is not supported. (In the current code, the version is not yet managed).
    *  - The caller is not allowed to access the RoT Service. */

    /** Test if SID existe in array_sid_asid
     *  and initialize the corresponding ASID
     */
    if(sid > 0){
        for (index = 0; index < 5; index++)
        {
            if (array_sid_asid[index].sid == sid)
            {
                rot_s_asid = array_sid_asid[index].asid;
            }
        }
    }


    if ((rot_s_asid != 0) && (psa_client_get_free_member()>0))
    {
        /** in order to transmit data, we must use the ExchangeArea buffer
         *  this is defined by Ukernel mechanism
         */
        // fill destination RoT secure SID known by uKernel
        exchange_area_addr = SPM_exchange_area_addr();
        exchange_area_addr->sid = SPM_CALL_BASE | rot_s_asid;
        ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);
        psa_msg = &(ns_ipc_msg_addr->ns_ipc_msg);

        if (ns_ipc_msg_addr != NULL)
        {
            // we can now fill the information for the requested message
            psa_msg->signal = connexion_signal;
            /* PSA_IPC_CONNECT is the only type of message in psa_connect() */
            if ( ns_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
            {
              ns_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
            }
            psa_msg->type            = (int32_t)((uint32_t)(ns_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)PSA_IPC_CONNECT & PSA_TYPE_MASK));
            psa_msg->msg_handle      = NS_CLIENT_HANDLE;
            psa_msg->block_bundle_id = 0;
            for (index = PSA_UFALSE;
                    index < PSA_MAX_IOVEC;
                    index++)
            {
                psa_msg->in_size[index]=  0U;
                psa_msg->out_size[index] =  0U;
            }
            // Send MSG from NS to RoT
            do {
                nscall_status = nscall();
            } while(nscall_status == NSCALL_ERR_EAGAIN);

            if(nscall_status != NSCALL_ERR_EINVAL)
            {

                /* receive response */
                ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);
                if (ns_ipc_msg_addr != NULL)
                {
                    psa_reply = (psa_client_reply_t*) &(ns_ipc_msg_addr->ns_ipc_msg);
                    if (psa_reply != NULL)
                    {
                        if (psa_reply->status == PSA_SUCCESS)
                        {
                            return_handle = psa_reply->msg_handle;
                            client_struct.msg_handle = return_handle;
                            client_struct.asid = rot_s_asid;
                            if (psa_client_check_client(&client_struct) == PSA_UFALSE)
                            {
                                psa_client_add_to_array(&client_struct);
                            }
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
            /* if incorrect sid */
            else
            {
                psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
            }
        }
        else
        {
           psa_status = PSA_ERROR_PROGRAMMER_ERROR;
        }
    }
    else if(rot_s_asid == 0)
    {
        psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }

    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
    return 0;
}


static void veener_psa_close (uint32_t arg0,
                              uint32_t arg1  __attribute__((unused)), 
                              uint32_t arg2  __attribute__((unused)), 
                              uint32_t arg3  __attribute__((unused))) 
{

    psa_status_t         psa_status         = PSA_ERROR_GENERIC_ERROR;
    psa_status_t         nscall_status      = PSA_ERROR_GENERIC_ERROR;
    uint8_t              index              = 0U;
    uint8_t              psa_msg_index      = 0U;
    psa_client_t         psa_client         = {0};
    uint16_t             rot_s_asid         = 0U;
    SPM_ExchangeArea_t  *exchange_area_addr = NULL;
    TnsPSA_MSG          *ns_ipc_msg_addr    = NULL;
    psa_ipc_msg_t       *psa_msg            = NULL;
    psa_client_reply_t  *psa_reply          = NULL;
    psa_handle_t         handle           = (psa_handle_t)arg0;

    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - An invalid handle was provided that is not the null handle.
    *  - The connection is currently handling a request.
    * */

    if ((handle <= 0)  && (handle != NS_CLIENT_HANDLE)) {
      return;
    }
    psa_status = psa_client_check_handle(handle, &psa_msg_index);
    if (psa_status != PSA_SUCCESS) {
      // An invalid handle was provided that is not the null handle.
      psa_status = PSA_ERROR_PROGRAMMER_ERROR;
    }
    else
    {
        client_memset( &psa_client, 0, sizeof(psa_client));
        if (psa_client_get_from_index(psa_msg_index, &psa_client) == PSA_UTRUE)
        {
            rot_s_asid = psa_client.asid;

            // fill destination RoT secure SID known by uKernel
            exchange_area_addr = SPM_exchange_area_addr();
            exchange_area_addr->sid = SPM_CALL_BASE | rot_s_asid;
            ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);
            if (ns_ipc_msg_addr != NULL)
            {

                psa_msg = &(ns_ipc_msg_addr->ns_ipc_msg);
                if (psa_msg != NULL)
                {
                    /* Fill the psa_ipc_msg info */
                    psa_msg->signal = connexion_signal;
                    /* PSA_IPC_DISCONNECT is the only type of request to send in psa_close()*/
                    if ( ns_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
                    {
                      ns_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
                    }
                    psa_msg->type       = (int32_t)((uint32_t)(ns_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)PSA_IPC_DISCONNECT & PSA_TYPE_MASK));
                    psa_msg->msg_handle = handle;
                    psa_msg->block_bundle_id = 0;
                    for (index = PSA_UFALSE; index < PSA_MAX_IOVEC; index++)
                    {
                        psa_msg->in_size[index] = 0U;
                        psa_msg->out_size[index] = 0U;
                    }
                    /* Send the close request to the RoT Service and wait for the reply*/
                    do {
                        nscall_status = nscall();
                    } while(nscall_status == NSCALL_ERR_EAGAIN);

                    /* if incorrect sid */
                    if(nscall_status != NSCALL_ERR_EINVAL)
                    {
                        /* receive response */
                        ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);
                        if (ns_ipc_msg_addr != NULL)
                        {
                            psa_reply = (psa_client_reply_t * ) &(ns_ipc_msg_addr->ns_ipc_msg);
                            if (psa_reply != NULL)
                            {
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
    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
    /* Remove the connection from the global array
     * As this connection is now closed */
    psa_client_free_handle(0U);
}

static psa_status_t veener_psa_call (uint32_t arg0, 
                                     uint32_t arg1, 
                                     uint32_t arg2, 
                                     uint32_t arg3 ) 
{
    
    psa_status_t        psa_status         = PSA_ERROR_GENERIC_ERROR;
    psa_status_t        nscall_status      = PSA_ERROR_GENERIC_ERROR;;
    uint8_t             index              = 0U;
    psa_client_t        psa_client         = {0};
    uint16_t            rot_s_asid         = 0U;
    size_t              exchange_area_size = 0U;
    SPM_ExchangeArea_t *exchange_area_addr = NULL;
    TnsPSA_MSG         *ns_ipc_msg_addr    = NULL;
    psa_ipc_msg_t      *psa_msg            = NULL;
    psa_client_reply_t *psa_reply          = NULL;
    uint32_t            out_n_elments      = 0U;
    psa_invec          *invec_ptr          = NULL;
    psa_outvec         *outvec_ptr         = NULL;
    uint32_t            size               = 0U;
    uint32_t            written_bytes      = 0U; 
    
    
    // Retrieve args 
    psa_handle_t     handle      = (psa_handle_t) arg0; 
    int32_t          type        = (uint32_t) ((arg1 & 0xFFFF0000) >> 16);
    psa_invec        *in_vec     = (psa_invec *) arg2;
    size_t           in_len      = (size_t) ((arg1 & 0xFF00) >> 8);
    psa_outvec       *out_vec    = (psa_outvec *) arg3;  
    size_t           out_len     = (size_t) (arg1 & 0xFF);
     
    /* The call is a PSA_ERROR_PROGRAMMER_ERROR if one or more of the following are true:
    *  - An invalid handle was passed.
    *  - The connection is already handling a request.
    *  - type < 0
    *  - An invalid memory reference was provided.
    *  - in_len + out_len > PSA_MAX_IOVEC
    *  - The message is unrecognized by the RoT Service or incorrectly formatted.
    * */

    if (((handle <= 0) && (handle != NS_CLIENT_HANDLE)) || (type < 0) || ((in_len + out_len) > PSA_MAX_IOVEC))
    {
        psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
    }
    else if ((((in_len == 0) && (in_vec != NULL)) || ((out_len == 0) && (out_vec != NULL)))
           || (((in_len != 0) && (in_vec == NULL)) || ((out_len != 0) && (out_vec == NULL))))
    {
        psa_status = PSA_ERROR_INVALID_ARGUMENT;
    }
    else
    {
        // Get the ASID with handle
        psa_status = psa_client_check_handle(handle, &index);
        if (psa_status == PSA_SUCCESS)
        {
            client_memset( &psa_client, 0, sizeof(psa_client));
            if (psa_client_get_from_index(index, &psa_client) == PSA_UTRUE)
            {
                rot_s_asid = psa_client.asid;

                if ((in_vec != NULL) && (in_len > 0))
                {
                    invec_ptr = (psa_invec *)in_vec;
                    for (index = 0U; index <= in_len - 1; index++)
                    {
                        size += invec_ptr->len;
                        invec_ptr ++;
                    }
                }
                if ((out_vec != NULL) && (out_len > 0))
                {
                    outvec_ptr = out_vec;
                    for (index = 0U; index <= out_len - 1; index++)
                    {
                        size += outvec_ptr->len;
                        outvec_ptr++;
                    }
                }

                // fill destination RoT secure SID known by uKernel
                exchange_area_addr = SPM_exchange_area_addr();
                exchange_area_size = SPM_exchange_area_size();
                exchange_area_addr->sid = SPM_CALL_BASE | rot_s_asid;
                //prepare the TnsPSA_MSG
                ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);

                /* Both the exchange_area and ns_ipc_msg have a flexible array
                 * member. Their size doesn't include their payload. The area
                 * available is used for the exchange area, directly followed
                 * by the ns_ipc_msg, directly followed by the data we are
                 * trying to write.
                 *
                 * +---------------+----------------+-----------------------+
                 * | exchange area | ns ipc message |        payload        |
                 * | non-flexible  |  non-flexible  |                       |
                 * +---------------+----------------+-----------------------+
                 *
                 * All of this has to fit exchange_area_size bytes.
                 * */
                if (sizeof(*exchange_area_addr) + sizeof(*ns_ipc_msg_addr)
                                                + size <= exchange_area_size)
                {
                    invec_ptr = (psa_invec *)in_vec;
                    if ((in_len > 0) && (in_vec != NULL))
                    {
                        written_bytes = 0U;
                        for (index = 0 ; index < in_len; index++)
                        {
                            client_memcpy((void*)((ns_ipc_msg_addr->ns_ipc_data)+written_bytes), (void*)invec_ptr->base, invec_ptr->len);
                            written_bytes += invec_ptr->len;
                            invec_ptr++;
                        }
                    }

                    if (ns_ipc_msg_addr != NULL)
                    {
                        // prepare the psa_ipc_msg_t
                        psa_msg = &(ns_ipc_msg_addr->ns_ipc_msg);
                        if (psa_msg != NULL)
                        {
                            /* Fill the psa_ipc_msg information */
                            psa_msg->signal = connexion_signal;
                            if ( ns_client_api_rot_verbosity_level > TFM_PARTITION_LOG_LEVEL_DEBUG)
                            {
                              ns_client_api_rot_verbosity_level = TFM_PARTITION_LOG_LEVEL_SILENCE;
                            }
                            psa_msg->type       = (int32_t)((uint32_t)(ns_client_api_rot_verbosity_level << TYPE_VERBOSITY_LEVEL_POS) |  ((uint32_t)type & PSA_TYPE_MASK));
                            psa_msg->msg_handle = handle;
                            psa_msg->block_bundle_id = 0;
                            invec_ptr = (psa_invec *)in_vec;
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
                            /* Send the data to the RoT Service and wait for the reply*/
                            do {
                                nscall_status = nscall();
                            } while(nscall_status == NSCALL_ERR_EAGAIN);

                            /* if incorrect sid */
                            if(nscall_status != NSCALL_ERR_EINVAL)
                            {
                                /* receive response */
                                ns_ipc_msg_addr = (TnsPSA_MSG * ) &(exchange_area_addr->data[0]);
                                if (ns_ipc_msg_addr != NULL)
                                {
                                    psa_reply = (psa_client_reply_t * ) &(ns_ipc_msg_addr->ns_ipc_msg);
                                    if (psa_reply != NULL)
                                    {
                                        if ((psa_reply->status == PSA_SUCCESS) || (psa_reply->status == PSA_ERROR_DEPENDENCY_NEEDED))
                                        {
                                            for (index = 0U; index < PSA_MAX_IOVEC; index++)
                                            {
                                                if(psa_reply->out_size[index] > 0)
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
                                                    if ((out_vec[index].base != NULL) && (psa_reply->out_size[index]!=0))
                                                    {
                                                        client_memcpy((void*)(out_vec[index].base),
                                                                      (void*)(ns_ipc_msg_addr->ns_ipc_data + psa_reply->out_offset[index]),
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
                                psa_status = PSA_ERROR_PROGRAMMER_ERROR;
                            }
                        }
                        else
                        {
                            psa_status =   PSA_ERROR_GENERIC_ERROR;
                        }
                    }
                    else
                    {
                        psa_status = PSA_ERROR_COMMUNICATION_FAILURE;
                    }
                }
                else
                {
                    // the DATA is too big to send
                    psa_status =  PSA_ERROR_INSUFFICIENT_MEMORY;
                } 
            }
            else
            {
                // asid and handle are equal to 0
                psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
            }
        }
        else
        {
            // An invalid handle was provided
            psa_status =  PSA_ERROR_PROGRAMMER_ERROR;
        }
    }
    if (psa_status == PSA_ERROR_PROGRAMMER_ERROR)
    {
        internal_panic();
    }
    return psa_status;
}


/**** API functions ****/

uint32_t psa_framework_version(void)
{
    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_psa_framework_version,
                                0,
                                0,
                                0,
                                0);
}

uint32_t psa_version(uint32_t sid)
{
    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_psa_version,
                                sid,
                                0,
                                0,
                                0);
}
psa_status_t set_verbosity_level(uint8_t level_log)
{
    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_set_verbosity_level,
                                level_log,
                                0,
                                0,
                                0);

}

psa_status_t get_verbosity_level(uint8_t *level_log)
{
    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_get_verbosity_level,
                                (uint32_t)level_log,
                                0,
                                0,
                                0);

}
psa_handle_t psa_connect(uint32_t sid, uint32_t version)
{
    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_psa_connect,
                                sid,
                                version,
                                0,
                                0);
}

psa_status_t psa_call(psa_handle_t handle, int32_t type,
                      const psa_invec *in_vec,
                      size_t in_len,
                      psa_outvec *out_vec,
                      size_t out_len)
{
    if ((type > INT16_MAX) ||
        (type < INT16_MIN) ||
        (in_len > UINT8_MAX) ||
        (out_len > UINT8_MAX)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }

    return tfm_ns_interface_dispatch(
                                (veneer_fn)veener_psa_call,
                                (uint32_t)handle,
                                PARAM_PACK(type, in_len, out_len),
                                (uint32_t)in_vec,
                                (uint32_t)out_vec);
}

void psa_close(psa_handle_t handle)
{
    (void)tfm_ns_interface_dispatch(
                         (veneer_fn)veener_psa_close,
                         (uint32_t)handle,
                         0,
                         0,
                         0);
                         
    const ns_ipc_seq_info_t info = {.signal = connexion_signal};
    ns_ipc_seq_end(&info);
}

void psa_init_signal(uint32_t signal)
{
    const ns_ipc_seq_info_t info = {.signal = signal};
    ns_ipc_seq_begin(&info);
    
    (void)tfm_ns_interface_dispatch(
                         (veneer_fn)veener_psa_init_signal,
                         (uint32_t)signal,
                         0,
                         0,
                         0);
}
