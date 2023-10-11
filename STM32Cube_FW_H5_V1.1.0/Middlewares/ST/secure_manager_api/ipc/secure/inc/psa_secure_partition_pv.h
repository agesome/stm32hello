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
 * @file          psa_secure_partition_pv.h
 * @brief         Private header of secure partition
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA_SECPART_PV
 ******************************************************************************
 * @details      This private header contains the declarations and definitions
 *               of private structures used only for the psa_secure_partition.c file.
 *
 * @note         This header shall not be public. The usage of this header is
 *                  strictly private to the psa_secure_partition.c file
 ******************************************************************************
 * @addtogroup    PSA_SECPART_PV
 * @{
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.            */
#if !defined(PSA_SECPART_PV_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  PSA_SECPART_PV_H

/* Define that we are inside this file (definition is undone at its end). */
#define  PSA_SECPART_PV_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed by the implementation of this code
 *  module.*/




/* Source the needed standard C APIs (include files "<stdxxx.h>"). */
/* Source the needed Public API of other uKernel Modules (include files
 *  "ukxxxx.h"). */

/* Source the uKernel API. */
#ifdef __IARCC__
#include "uk.h"
#else
#include "uk/include/uk.h"
#endif
/* Source the needed standard C APIs (include files "<stdxxx.h>"). */
#include "psa/service.h"



/** @privatesection */

/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS -  CONFIGURATION                    */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief C-Constant defining a maximum value used in Secure partition library
 *
 * Definition of the C-Constant a maximum number of connection in
 *   Secure partition
 *
 * @usage This C-Constant is used to define number of index in the
 *   Secure Partition connections array
 */
#define PSA_SECPART_MAX_CONNECTION    0x00000014U
#define PSA_SECPART_MAX_CONNECTION_END PSA_SECPART_MAX_CONNECTION+1U
#if PSA_SECPART_MAX_CONNECTION_END > UINT8_MAX
    #error "PSA_SECPART_MAX_CONNECTION_END cannot be higher than UINT8_MAX"
#endif

/**
 * @brief C-Constant defining a maximum value of PSA non-secure
 * message struct data field
 *
 * @usage This C-Constant is used to define the size in bytes of
 * PSA non-secure message struct data field
 */
#define NS_DATA_SIZE 0x00000BC8

#define NS_CLIENT_ID  (TukINT32)(-1)

#define NS_CLIENT_HANDLE  (TukINT32)(-1)

#define PSA_TYPE_MASK                0x1FFFFFFFU
#define TYPE_VERBOSITY_LEVEL_MASK    0x60000000U
#define TYPE_VERBOSITY_LEVEL_POS     29U
/* //////////////////////////////////////////////////////////////////////// */
/*                        C-TYPES - SECURE PARTITION PSA INSTANCE           */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief PSA Internal IPC message C-Type
 *
 * A PSA Internal IPC message is the structure that is used to store the information
 *  of the received message inside the Secure partition library.
 *
 * This structure is only used in the psa_secpart_handle_t structure.
 *
 * The structure of a PSA internal ipc Message consists in the following elements:
 *      - (psa_signal_t)signal: The signal to request
 *      - (int32_t)type : the Type of message
 *      - (psa_handle_t)msg_handle : The message handle
 *      - (uint32_t)in_size[PSA_MAX_IOVEC] : list of size of the received input vectors
 *      - (uint32_t)int_offest[PSA_MAX_IOVEC]: list of offset inside the shared buffer of the received input vectors
 *      - (uint32_t)out_size[PSA_MAX_IOVEC]: list of the maximum size of the received output vectors
 *      - (uint32_t)out_size_util[PSA_MAX_IOVEC]: list of the bytes copied inside the output vectors
 *      - (uint32_t)out_offset[PSA_MAX_IOVEC]: list of the offsets inside the shared buffer of each output vectors
 *      - (TukADDRESSBLOCK_ID)block_bundle_id: the ID of the shared buffer transmitted by the client
 *
 * @usage This structure is part of the pas_secpart_handle_t structure
 */
typedef struct {
    psa_signal_t                            signal;
    int32_t                                 type;
    psa_handle_t                            msg_handle;
    uint32_t                                in_size[PSA_MAX_IOVEC];
    uint32_t                                in_offset[PSA_MAX_IOVEC];
    uint32_t                                out_size[PSA_MAX_IOVEC];
    uint32_t                                out_size_util[PSA_MAX_IOVEC];
    uint32_t                                out_offset[PSA_MAX_IOVEC];
    TukADDRESSBLOCK_ID                      block_bundle_id;
} psa_internal_ipc_msg_t;


/**
 * @brief PSA secpart handle C-Type
 *
 * A PSA secpart handle is the structure that is used to declare
 *  the global array that allows to store and record the opened connections
 *  inside the secure library partition
 *  of the received message inside the Secure partition library.
 *
 * This structure is only used in the psa_secpart_handle_t structure.
 *
 * The structure of a PSA Internal IPC Message consists in the following elements:
 *      - (psa_internal_ipc_msg_t)ipc_msg: contains the information of the received request.
 *      - (int32_t)client_id : The ASID value of the client
 *      - (void*)rhandle: not yet supported
 *      - (TukBOOL)asserted: used for monitoring the connection between psa_wait() and psa_get()
 *      - (TukUKPROC_PUID): the PUID of the application that send the request.
 *
 *
 * @usage This structure is used as type of a global array. The array is used in almost each APIs:
 *      psa_wait(), psa_get(), psa_read(), psa_write(), psa_skip(), psa_reply(), etc
 */
typedef struct {
    psa_internal_ipc_msg_t                  ipc_msg;
    int32_t                                 client_id;
    void*                                   rhandle;
    TukBOOL                                 asserted;
    TukUKPROC_PUID                          client_puid;
} psa_secpart_handle_t;



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
    psa_signal_t                            signal;
    int32_t                                 type;
    psa_handle_t                            msg_handle;
    uint32_t                                in_size[PSA_MAX_IOVEC];
    uint32_t                                out_size[PSA_MAX_IOVEC];
    TukADDRESSBLOCK_ID                      block_bundle_id;
} psa_ipc_msg_t;


/**
 * @brief PSA Secure partition Reply C-Type
 *
 * A PSA Secpart reply is the structure that is used to exchange information
 *  between the Client library and the Secure partition library via ukIPC mechanism.
 *
 * This structure is only used in the direction RoT service to Client.
 *
 * The structure of a PSA SecPart Message consists in the following elements:
 *      - (psa_handle_t)msg_handle: The message handle associated to the structure
 *      - (uint32_t)out_size[PSA_MAX_IOVEC]: the actual bytes copied inside each output vector (zeroed for a reply of a connect/disconnect message)
 *      - (uint32_t)out_size[PSA_MAX_IOVEC]: the offset (in bytes) inside the shared buffer of the starting position of the output vector.
 *      - (psa_status_t)status : the status returned in reply of a request send by the client
 *
 *
 * @usage This structure is used inside psa_connect() / psa_call() and psa_close()
 *        it has no purpose to be public.
 *        the Client library must also respect this structure.
 */
typedef struct {
    psa_handle_t                            msg_handle;
    uint32_t                                out_size[PSA_MAX_IOVEC];
    uint32_t                                out_offset[PSA_MAX_IOVEC];
    psa_status_t                            status;
} psa_secpart_reply_t;


struct psa_secpart_irq
{
    TukPIRQ_REGISTRATION_ID        pirq_reg_id; //TukPIRQ_REGISTRATION_ID
    TukPIRQ_MCU_IDX                pirq_mcu_idx;
    uint32_t                       signal_id;
};

/* //////////////////////////////////////////////////////////////////////// */
/*                       C-TYPES - NS_CLIENT MSG structure                  */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief PSA non-secure message C-Type
 *
 * A non-secure message is the structure that is used to exchange information
 *  between the non-secure Client library and the Secure partition library via ukIPC mechanism.
 *
 * This structure is only used in the direction RoT service to non-secure Client.
 *
 * The structure of a PSA non-secure message consists in the following elements:
 *      - (psa_ipc_msg_t)ns_ipc_msg: see the description above psa_ipc_msg_t
 *      - (uint8_t)ns_ipc_data[NS_DATA_SIZE]: the data send by non-secure client
 *
 * @usage This structure is used inside psa_connect() / psa_call() and psa_close()
 *        it has no purpose to be public.
 *        the Client library must also respect this structure.
 */
typedef struct{
    psa_ipc_msg_t            ns_ipc_msg;
    uint8_t                  ns_ipc_data[];
} TnsPSA_MSG;

/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
 /** @} */
#endif
