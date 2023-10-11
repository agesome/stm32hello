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
 * @file          psa_client_pv.h
 * @brief         Private header of Client library
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_CLIENT_PV
 ******************************************************************************
 * @details      This private header contains the declarations and definitions
 *               of private structures used only for the psa_client.c file.
 *
 *
 *
 * @note         This header shall not be public. The usage of this header is
 *                  strictly private to the psa_client.c file
 ******************************************************************************
 * @addtogroup    PSA_CLIENT_PV
 * @{
 */

/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#ifndef PSA_CLIENT_PV_H
/* Define that this include file has been processed (single inclusion). */
#define PSA_CLIENT_PV_H

/* Source the uKernel API. */
#ifndef __IARCC__
#include "uk/include/uk.h"
#else
#include "uk.h"
#endif
#include "psa/client.h"
#include "psa/error.h"
#include "psa/service.h"

/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - PSA client MAX Connections         */
/* //////////////////////////////////////////////////////////////////////// */
/**
 *  C-Constants that defines the maximum number of connection supported
 *     by the client library
*/
#define PSA_CLIENT_MAX_CONNECTION    0x00000014U

/**
 *  The type consists of two parts:
 *      - 2 MSB bits: The level log for debug traces chosen by the customer
 *      - 30 bit LSB: The psa type msg field to communicate to the RoT Service
 * */

#define PSA_TYPE_MASK                0x1FFFFFFFU
#define TYPE_VERBOSITY_LEVEL_MASK    0x60000000U
#define TYPE_VERBOSITY_LEVEL_POS     29U

/**
 * @brief C-Constants used to declare a verbosity log
 *        level none:
 *        All log APIs are suppressed
 *
 *        This value is set/get by the set_verbosity_level() and
 *        get_verbosity_level()  publics functions.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them.
 */
#define TFM_PARTITION_LOG_LEVEL_SILENCE     0U
/**
 * @brief C-Constants used to declare a verbosity log
 *        level error:
 *        Only LOG_ERRFMT APIs output.
 *
 *        This value is set/get by the set_verbosity_level() and
 *        get_verbosity_level()  publics functions.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them.
 */
#define TFM_PARTITION_LOG_LEVEL_ERROR    1U
/**
 * @brief C-Constants used to declare a verbosity log
 *        level info:
 *        All log APIs output except LOG_DBGFMT
 *
 *        This value is set/get by the set_verbosity_level() and
 *        get_verbosity_level()  publics functions.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them.
 */
#define TFM_PARTITION_LOG_LEVEL_INFO     2U
/**
 * @brief C-Constants used to declare a verbosity log
 *        level debug:
 *        All log APIs output
 *
 *        This value is set/get by the set_verbosity_level() and
 *        get_verbosity_level()  publics functions.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them.
 */
#define TFM_PARTITION_LOG_LEVEL_DEBUG    3U


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-TYPES - PSA Internal structure                 */
/* //////////////////////////////////////////////////////////////////////// */


/**
 * @brief PSA IPC message C-Type
 *
 * A PSA IPC message is the structure that is used to exchange information
 *  between the Client library and the Secure partition library via ukIPC mechanism.
 *
 * This structure is only used in the direction Client to RoT service.
 *
 * The structure of a PSA IPC Message consists in the following elements:
 *      - (psa_signal_t)signal: The signal to request
 *      - (int32_t)type : the Type of message
 *  The type consists of:
 * |-----------------------|---------------------------------------
 * |      Bit number       |                   Description         |
 * |31     |30...29|28...00|                                       |
 * |:-----:|:-----:|:-----:|---------------------------------------|
 * | xxxxx |       |       | The sign                              |
 * |-------|-------|-------|---------------------------------------|
 * |       | xxxxx |       | The level log for debug traces chosen |
 * |       |       |       | by the customer (2-bit)               |
 * |-------|-------|-------|---------------------------------------|
 * |       |       | xxxxx | The psa type msg field to communicate |
 * |       |       |       | to the RoT Service (29-bit)           |
 * |-------|-------|-------|---------------------------------------|
 *
 *      - (psa_handle_t)msg_handle : The message handle (optional for a connect message)
 *      - (uint32_t)in_size[PSA_MAX_IOVEC] : list of size of the input vector (zeroed for a connect and disconnect message)
 *      - (uint32_t)out_size[MAX_PSA_IOVEC]: list of size of the output vector (zeroed for a connect and disconnect message)
 *      - (TukADDRESSBLOCK_ID)block_bundle_id: the id of the block bundle
 *
 *
 * @usage This structure is used inside psa_connect() / psa_call() and psa_close()
 *        it has no purpose to be public.
 *        the Secure partition must also respect this structure.
 */
typedef struct {
    psa_signal_t            signal;
    int32_t                 type;
    psa_handle_t            msg_handle;
    uint32_t                in_size[PSA_MAX_IOVEC];
    uint32_t                out_size[PSA_MAX_IOVEC];
    TukADDRESSBLOCK_ID      block_bundle_id;
} psa_ipc_msg_t;


/**
 * @brief PSA Client C-Type
 *
 * A psa client structure is used by psa_connect() / psa_call and psa_close()
 *      in order to track and record the puid (used by ukIPC APIs) and the msg_handle.
 *
 * The structure of a PSA clientconsists in the following elements:
 *      - (psa_handle_t)msg_handle: The handle of the message
 *      - (TukUKPROC_PUID)puid: the puid of the targeted RoT Service.
 *
 * @usage This structure is used inside Client library to initialize
 *      an array of client connection. It stores the opened connection
 *      and allows to remember the RoT PUID associated to the message handler.
 *
 */
typedef struct {
    psa_handle_t            msg_handle;
    TukUKPROC_PUID          puid;
} psa_client_t;


/**
 * @brief PSA Client Reply C-Type
 *
 * A PSA Client reply is the structure that is used to exchange information
 *  between the Client library and the Secure partition library via ukIPC mechanism.
 *
 * This structure is only used in the direction RoT service to Client.
 *
 * The structure of a PSA reply Message consists in the following elements:
 *      - (psa_handle_t)msg_handle: The message handle associated to the structure
 *      - (uint32_t)out_size[PSA_MAX_IOVEC]: the actual bytes copied inside each output vector (zeroed for a reply of a connect/disconnect message)
 *      - (uint32_t)out_size[PSA_MAX_IOVEC]: the offset (in bytes) inside the shared buffer of the starting position of the output vector.
 *      - (psa_status_t)status : the status returned in reply of a request send by the client
 *
 *
 * @usage This structure is used inside psa_connect() / psa_call() and psa_close()
 *        it has no purpose to be public.
 *        the Secure partition must also respect this structure.
 */
typedef struct {
    psa_handle_t            msg_handle;
    uint32_t                out_size[PSA_MAX_IOVEC];
    uint32_t                out_offset[PSA_MAX_IOVEC];
    psa_status_t            status;
} psa_client_reply_t;



/**
 * @brief PSA SID AUID C-Type
 *
 * A PSA sid auid is a structure used to keep the translation
 *  between a SID ROT service and its actual AUID.
 *
 * This structure is only used as a global array defined at build time.
 *
 * @usage The global array is only used in psa_connect().
 */
typedef struct{
    uint32_t                sid;
    uint64_t                auid;
} psa_sid_auid;



/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#endif /* !defined(PSA_CLIENT_PV_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

