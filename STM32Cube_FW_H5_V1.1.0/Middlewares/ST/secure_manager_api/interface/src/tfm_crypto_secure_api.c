/**
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This file was modified by ProvenRun
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 * https://www.provenrun.com/
 */
//*******************************************************************
//* NOTE: This file has checkparameters.c as a dependence
//*******************************************************************

#include "array.h"
#include "tfm_crypto_defs.h"
#include "psa/crypto.h"

#ifdef TFM_PSA_API
#include "psa/client.h"
#include "helper_function.h"
#include "psa/crypto.h"
#include "psa/client_extension.h"
//#include "sid.h"
#else
#include "tfm_veneers.h"
#endif

/****
 * Modified by Provenrun
 ***/
/****
 * Modification
 ***/

uint8_t randomize_output_buffer(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);


uint8_t randomize_buffer(uint8_t*buffer, size_t buffer_size);

/****
 * End of Modification
 ****/

#ifdef TFM_PSA_API

#define API_DISPATCH(sfn_name, sfn_id)                         \
    psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL,                  \
        in_vec, ARRAY_SIZE(in_vec),                            \
        out_vec, ARRAY_SIZE(out_vec))

#define API_DISPATCH_NO_OUTVEC(sfn_name, sfn_id)               \
    psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL,                  \
        in_vec, ARRAY_SIZE(in_vec),                            \
        (psa_outvec *)NULL, 0)

/****
 * Modified by Provenrun
 ***/
/****
 * Modification
 ***/
#define API_DISPATCH_HDL(sfn_name, sfn_id, hdl)                \
    psa_call(hdl, PSA_IPC_CALL,                                \
        in_vec, ARRAY_SIZE(in_vec),                            \
        out_vec, ARRAY_SIZE(out_vec))

#define API_DISPATCH_NO_OUTVEC_HDL(sfn_name, sfn_id, hdl)      \
    psa_call(hdl, PSA_IPC_CALL,                                \
        in_vec, ARRAY_SIZE(in_vec),                            \
        (psa_outvec *)NULL, 0)

#define CRYPTO_OK       0x55
#define CRYPTO_NOK      0x5A
#define CRYPTO_SECURITY 0xA5
/****
 * End of Modification
 ***/


#else
#define API_DISPATCH(sfn_name, sfn_id)                         \
    sfn_name##_veneer(                                         \
        in_vec, ARRAY_SIZE(in_vec),                            \
        out_vec, ARRAY_SIZE(out_vec))

#define API_DISPATCH_NO_OUTVEC(sfn_name, sfn_id)               \
    sfn_name##_veneer(                                         \
        in_vec, ARRAY_SIZE(in_vec),                            \
        NULL, 0)
#endif /* TFM_PSA_API */

psa_status_t psa_crypto_init(void)
{
    /* Service init is performed during TFM boot up,
     * so application level initialisation is empty
     */
    return PSA_SUCCESS;
}

psa_status_t psa_open_key(psa_key_id_t id,
                          psa_key_id_t *key_id)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_OPEN_KEY_SID
,
    };
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = &id, .len = sizeof(psa_key_id_t)},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = &id;
    in_vec[1].len = sizeof(psa_key_id_t);
    iov.sfn_id = TFM_CRYPTO_OPEN_KEY_SID;
/****
 * End of Modification
 ****/

    psa_outvec out_vec[] = {
        {.base = key_id, .len = sizeof(psa_key_id_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_open_key,
                          TFM_CRYPTO_OPEN_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_open_key,
                          TFM_CRYPTO_OPEN_KEY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_close_key(psa_key_id_t key)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CLOSE_KEY_SID,
        .key_id = key_id,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id =  TFM_CRYPTO_CLOSE_KEY_SID;
    iov.key_id = key;
/****
 * End of Modification
 ****/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_close_key,
                                    TFM_CRYPTO_CLOSE_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_close_key,
                                    TFM_CRYPTO_CLOSE_KEY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_import_key(const psa_key_attributes_t *attributes,
                            const uint8_t *data,
                            size_t data_length,
                            psa_key_id_t *key_id)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_IMPORT_KEY_SID,
    };
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
        {.base = data, .len = data_length}
    };
*/
/****
 * Modification
 ****/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_IMPORT_KEY_SID;

    psa_invec in_vec[3];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = attributes;
    in_vec[1].len = sizeof(psa_key_attributes_t);
    in_vec[2].base = data;
    in_vec[2].len = data_length;
/****
 * End of Modification
 ****/

    psa_outvec out_vec[] = {
        {.base = key_id, .len = sizeof(psa_key_id_t)}
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_import_key,
                          TFM_CRYPTO_IMPORT_KEY);
*/
/****
 * Modification
 ***/
     status = API_DISPATCH_HDL(tfm_crypto_import_key,
                          TFM_CRYPTO_IMPORT_KEY, hdl);
     psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_destroy_key(psa_key_id_t key_id)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_DESTROY_KEY_SID,
        .key_id = key_id,
    };
*/
/****
 * Modification
 ***/
     psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_DESTROY_KEY_SID;
     iov.key_id = key_id;
/***
 * End of Modification
 ***/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_destroy_key,
                                    TFM_CRYPTO_DESTROY_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_destroy_key,
                                    TFM_CRYPTO_DESTROY_KEY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_get_key_attributes(psa_key_id_t key,
                                    psa_key_attributes_t *attributes)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_GET_KEY_ATTRIBUTES_SID,
        .key_id = key_id,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_GET_KEY_ATTRIBUTES_SID;
        iov.key_id = key;
/****
 * End of Modification
 ****/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_get_key_attributes,
                          TFM_CRYPTO_GET_KEY_ATTRIBUTES);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_get_key_attributes,
                          TFM_CRYPTO_GET_KEY_ATTRIBUTES, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

void psa_reset_key_attributes(psa_key_attributes_t *attributes)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_RESET_KEY_ATTRIBUTES_SID,
    };
*/
/****
 * Modification
 ***/
    psa_init_signal(PSA_SIGNAL_CRYPTO);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_RESET_KEY_ATTRIBUTES_SID;
/****
 * End of Modification
 ****/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    (void)API_DISPATCH(tfm_crypto_reset_key_attributes,
                       TFM_CRYPTO_RESET_KEY_ATTRIBUTES);
*/
/****
 * Modification
 ***/
    (void)API_DISPATCH_HDL(tfm_crypto_reset_key_attributes,
                       TFM_CRYPTO_RESET_KEY_ATTRIBUTES,hdl);
     psa_close(hdl);
/****
 * End of Modification
 ****/
    return;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_export_key(psa_key_id_t key_id,
                            uint8_t *data,
                            size_t data_size,
                            size_t *data_length)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_EXPORT_KEY_SID,
        .key_id = key_id,
    };
*/
/*****
 * Modification
 ****/
       psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

       struct tfm_crypto_pack_iovec iov;
       iov.sfn_id = TFM_CRYPTO_EXPORT_KEY_SID;
       iov.key_id = key_id;
/***
 * End of Modification
 ****/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = data, .len = data_size}
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_export_key,
                          TFM_CRYPTO_EXPORT_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_export_key,
                          TFM_CRYPTO_EXPORT_KEY, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *data_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_export_public_key(psa_key_id_t key_id,
                                   uint8_t *data,
                                   size_t data_size,
                                   size_t *data_length)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_EXPORT_PUBLIC_KEY_SID,
        .key_id = key_id,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_EXPORT_PUBLIC_KEY_SID;
    iov.key_id = key_id;
/****
 * End of Modification
 ***/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = data, .len = data_size}
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_export_public_key,
                          TFM_CRYPTO_EXPORT_PUBLIC_KEY);
*/
/****
 * Modification
 ***/
     status = API_DISPATCH_HDL(tfm_crypto_export_public_key,
                          TFM_CRYPTO_EXPORT_PUBLIC_KEY, hdl);
     psa_close(hdl);
/****
 * End of Modification
 ****/

    *data_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_purge_key(psa_key_id_t key_id)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_PURGE_KEY_SID,
        .key_id = key_id,
    };
*/
/****
 * Modification
 ****/
        psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

        struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_PURGE_KEY_SID;
        iov.key_id = key_id;
/***
 * End of Modification
 ***/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_purge_key,
                                    TFM_CRYPTO_PURGE_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_purge_key,
                                    TFM_CRYPTO_PURGE_KEY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_copy_key(psa_key_id_t source_key_id,
                          const psa_key_attributes_t *attributes,
                          psa_key_id_t *target_key_id)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_COPY_KEY_SID,
        .key_id = source_key_id,
    };
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
    };
    */
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
        psa_invec in_vec[2];
        in_vec[0].base = &iov;
        in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
        in_vec[1].base = attributes;
        in_vec[1].len = sizeof(psa_key_attributes_t);
        iov.sfn_id = TFM_CRYPTO_COPY_KEY_SID;
        iov.key_id = source_key_id;
/****
* End of Modification
 ****/


    psa_outvec out_vec[] = {
        {.base = target_key_id, .len = sizeof(psa_key_id_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_copy_key,
                          TFM_CRYPTO_COPY_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_copy_key,
                          TFM_CRYPTO_COPY_KEY, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_cipher_generate_iv(psa_cipher_operation_t *operation,
                                    unsigned char *iv,
                                    size_t iv_size,
                                    size_t *iv_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_GENERATE_IV_SID,
        .op_handle = operation->handle,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_CIPHER_GENERATE_IV_SID;
    iov.op_handle = operation->handle;
/****
 * End of Modification
 ***/
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
/*    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
        {.base = iv, .len = iv_size},
    };
*/

    psa_outvec out_vec[2];
    out_vec[0].base = &(operation->handle);
    out_vec[0].len = sizeof(uint32_t);
    out_vec[1].base = iv;
    out_vec[1].len = iv_size;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    status = API_DISPATCH(tfm_crypto_cipher_generate_iv,
                          TFM_CRYPTO_CIPHER_GENERATE_IV);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_generate_iv,
                          TFM_CRYPTO_CIPHER_GENERATE_IV, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *iv_length = out_vec[1].len;

    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_set_iv(psa_cipher_operation_t *operation,
                               const unsigned char *iv,
                               size_t iv_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_SET_IV_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = iv, .len = iv_length},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/


    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_CIPHER_SET_IV_SID;
    iov.op_handle = operation->handle;
    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = iv;
    in_vec[1].len = iv_length;

        psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_set_iv,
                          TFM_CRYPTO_CIPHER_SET_IV);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_set_iv,
                          TFM_CRYPTO_CIPHER_SET_IV, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_encrypt_setup(psa_cipher_operation_t *operation,
                                      psa_key_id_t key_id,
                                      psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_ENCRYPT_SETUP_SID,
        .key_id = key_id,
        .alg = alg,
        .op_handle = operation->handle,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_CIPHER_ENCRYPT_SETUP_SID;
     iov.key_id = key_id;
     iov.alg = alg;
     iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_encrypt_setup,
                          TFM_CRYPTO_CIPHER_ENCRYPT_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_encrypt_setup,
                          TFM_CRYPTO_CIPHER_ENCRYPT_SETUP, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_decrypt_setup(psa_cipher_operation_t *operation,
                                      psa_key_id_t key_id,
                                      psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_DECRYPT_SETUP_SID,
        .key_id = key_id,
        .alg = alg,
        .op_handle = operation->handle,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_CIPHER_DECRYPT_SETUP_SID;
        iov.key_id = key_id;
        iov.alg = alg;
        iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_decrypt_setup,
                          TFM_CRYPTO_CIPHER_DECRYPT_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_decrypt_setup,
                          TFM_CRYPTO_CIPHER_DECRYPT_SETUP, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_update(psa_cipher_operation_t *operation,
                               const uint8_t *input,
                               size_t input_length,
                               unsigned char *output,
                               size_t output_size,
                               size_t *output_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_UPDATE_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
        {.base = output, .len = output_size}
    };
*/
 /****
 * Modification
 ***/
    randomize_output_buffer((uint8_t*)input, input_length, output, output_size);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_CIPHER_UPDATE_SID;
    iov.op_handle = operation->handle;

    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;
    psa_outvec out_vec[2];
    out_vec[0].base = &(operation->handle);
    out_vec[0].len = sizeof(uint32_t);
    out_vec[1].base = output;
    out_vec[1].len = output_size;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_update,
                          TFM_CRYPTO_CIPHER_UPDATE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_update,
                          TFM_CRYPTO_CIPHER_UPDATE, hdl);

    psa_close(hdl);

/****
 * End of Modification
 ****/

    *output_length = out_vec[1].len;
    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_abort(psa_cipher_operation_t *operation)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_ABORT_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_CIPHER_ABORT_SID;
     iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_abort,
                          TFM_CRYPTO_CIPHER_ABORT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_abort,
                          TFM_CRYPTO_CIPHER_ABORT, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_finish(psa_cipher_operation_t *operation,
                               uint8_t *output,
                               size_t output_size,
                               size_t *output_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

    randomize_buffer(output, output_size);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_FINISH_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/



    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

  struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_CIPHER_FINISH_SID;
        iov.op_handle = operation->handle;

/*
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

        psa_outvec out_vec[2];
        out_vec[0].base = &(operation->handle);
        out_vec[0].len = sizeof(uint32_t);
        out_vec[1].base = output;
        out_vec[1].len = output_size;
*/
    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len  = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = output;
    in_vec[1].len  = output_size;


    psa_outvec out_vec[2];
    out_vec[0].base = &(operation->handle);
    out_vec[0].len = sizeof(uint32_t);
    out_vec[1].base = output;
    out_vec[1].len =  output_size;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_cipher_finish,
                          TFM_CRYPTO_CIPHER_FINISH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_finish,
                              TFM_CRYPTO_CIPHER_FINISH, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    *output_length = out_vec[1].len;

    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_hash_setup(psa_hash_operation_t *operation,
                            psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_SETUP_SID,
        .alg = alg,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_HASH_SETUP_SID;
        iov.alg = alg;
        iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_hash_setup,
                          TFM_CRYPTO_HASH_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_setup,
                          TFM_CRYPTO_HASH_SETUP, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_update(psa_hash_operation_t *operation,
                             const uint8_t *input,
                             size_t input_length)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_UPDATE_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

        struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_HASH_UPDATE_SID;
        iov.op_handle = operation->handle;

        psa_invec in_vec[2];
        in_vec[0].base = &iov;
        in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
        in_vec[1].base = input;
        in_vec[1].len = input_length;

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_hash_update,
                          TFM_CRYPTO_HASH_UPDATE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_update,
                          TFM_CRYPTO_HASH_UPDATE, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_finish(psa_hash_operation_t *operation,
                             uint8_t *hash,
                             size_t hash_size,
                             size_t *hash_length)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_FINISH_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_HASH_FINISH_SID;
    iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
/*    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
        {.base = hash, .len = hash_size},
    };
*/
      psa_outvec out_vec[2];
      out_vec[0].base = &(operation->handle);
      out_vec[0].len = sizeof(uint32_t);
      out_vec[1].base = hash;
      out_vec[1].len = hash_size;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_hash_finish,
                          TFM_CRYPTO_HASH_FINISH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_finish,
                          TFM_CRYPTO_HASH_FINISH, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *hash_length = out_vec[1].len;

    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_verify(psa_hash_operation_t *operation,
                             const uint8_t *hash,
                             size_t hash_length)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_VERIFY_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = hash, .len = hash_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

        struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_HASH_VERIFY_SID;
        iov.op_handle = operation->handle;

        psa_invec in_vec[2];
        in_vec[0].base = &iov;
        in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
        in_vec[1].base = hash;
        in_vec[1].len = hash_length;

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    status = API_DISPATCH(tfm_crypto_hash_verify,
                          TFM_CRYPTO_HASH_VERIFY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_verify,
                          TFM_CRYPTO_HASH_VERIFY, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_abort(psa_hash_operation_t *operation)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_ABORT_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_HASH_ABORT_SID;
    iov.op_handle = operation->handle;


    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_hash_abort,
                          TFM_CRYPTO_HASH_ABORT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_abort,
                          TFM_CRYPTO_HASH_ABORT, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_clone(const psa_hash_operation_t *source_operation,
                            psa_hash_operation_t *target_operation)
{
#ifdef TFM_CRYPTO_HASH_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_CLONE_SID,
        .op_handle = source_operation->handle,
    };
  */

 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_HASH_CLONE_SID;
        iov.op_handle = source_operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = target_operation, .len = sizeof(psa_hash_operation_t)},
    };

    if (target_operation && (target_operation->handle != 0)) {
        return PSA_ERROR_BAD_STATE;
    }

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
//    status = API_DISPATCH(tfm_crypto_hash_clone,
//                          TFM_CRYPTO_HASH_CLONE);
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_clone,
                          TFM_CRYPTO_HASH_CLONE, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_compute(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *hash,
                              size_t hash_size,
                              size_t *hash_length)
{
#if (TFM_CRYPTO_HASH_MODULE_DISABLED != 0)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);


/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_COMPUTE_SID,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_HASH_COMPUTE_SID;
    iov.alg = alg;
    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;

    psa_outvec out_vec[] = {
        {.base = hash, .len = hash_size}
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
//    status = API_DISPATCH(tfm_crypto_hash_compute,
//                          TFM_CRYPTO_HASH_COMPUTE);
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_hash_compute,
                          TFM_CRYPTO_HASH_COMPUTE, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    *hash_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_hash_compare(psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              const uint8_t *hash,
                              size_t hash_length)
{
#if (TFM_CRYPTO_HASH_MODULE_DISABLED != 0)
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_HASH_COMPARE_SID,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
        {.base = hash, .len = hash_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

       struct tfm_crypto_pack_iovec iov;
       iov.sfn_id = TFM_CRYPTO_HASH_COMPARE_SID;
       iov.alg = alg;

       psa_invec in_vec[3];
        in_vec[0].base = &iov;
        in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
        in_vec[1].base = input;
        in_vec[1].len = input_length;
        in_vec[2].base = hash;
        in_vec[2].len = hash_length;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_hash_compare,
                                    TFM_CRYPTO_HASH_COMPARE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_hash_compare,
                                    TFM_CRYPTO_HASH_COMPARE,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_HASH_MODULE_DISABLED */
}

psa_status_t psa_mac_sign_setup(psa_mac_operation_t *operation,
                                psa_key_id_t key_id,
                                psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_SIGN_SETUP_SID,
        .key_id = key_id,
        .alg = alg,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

        struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_MAC_SIGN_SETUP_SID;
        iov.key_id = key_id;
        iov.alg = alg;
        iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_sign_setup,
                          TFM_CRYPTO_MAC_SIGN_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_sign_setup,
                          TFM_CRYPTO_MAC_SIGN_SETUP, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_verify_setup(psa_mac_operation_t *operation,
                                  psa_key_id_t key_id,
                                  psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_VERIFY_SETUP_SID,
        .key_id = key_id,
        .alg = alg,
        .op_handle = operation->handle,
    };
  */
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_MAC_VERIFY_SETUP_SID;
    iov.key_id = key_id;
    iov.alg = alg;
    iov.op_handle = operation->handle;


    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_verify_setup,
                          TFM_CRYPTO_MAC_VERIFY_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_verify_setup,
                          TFM_CRYPTO_MAC_VERIFY_SETUP,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_update(psa_mac_operation_t *operation,
                            const uint8_t *input,
                            size_t input_length)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_UPDATE_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/

 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_MAC_UPDATE_SID;
    iov.op_handle = operation->handle;
    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_update,
                          TFM_CRYPTO_MAC_UPDATE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_update,
                          TFM_CRYPTO_MAC_UPDATE,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_sign_finish(psa_mac_operation_t *operation,
                                 uint8_t *mac,
                                 size_t mac_size,
                                 size_t *mac_length)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_SIGN_FINISH_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_MAC_SIGN_FINISH_SID;
    iov.op_handle = operation->handle;


    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
 /*   psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
        {.base = mac, .len = mac_size},
    };
*/
      psa_outvec out_vec[2];
      out_vec[0].base = &(operation->handle);
      out_vec[0].len = sizeof(uint32_t);
      out_vec[1].base = mac;
      out_vec[1].len = mac_size;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_sign_finish,
                          TFM_CRYPTO_MAC_SIGN_FINISH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_sign_finish,
                          TFM_CRYPTO_MAC_SIGN_FINISH,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *mac_length = out_vec[1].len;

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_verify_finish(psa_mac_operation_t *operation,
                                   const uint8_t *mac,
                                   size_t mac_length)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_VERIFY_FINISH_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = mac, .len = mac_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_MAC_VERIFY_FINISH_SID;
     iov.op_handle = operation->handle;
     psa_invec in_vec[2];
      in_vec[0].base = &iov;
      in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
      in_vec[1].base = mac;
      in_vec[1].len = mac_length;

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_verify_finish,
                          TFM_CRYPTO_MAC_VERIFY_FINISH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_verify_finish,
                          TFM_CRYPTO_MAC_VERIFY_FINISH,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_abort(psa_mac_operation_t *operation)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_ABORT_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_MAC_ABORT_SID;
    iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_mac_abort,
                          TFM_CRYPTO_MAC_ABORT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_abort,
                          TFM_CRYPTO_MAC_ABORT,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_aead_encrypt(psa_key_id_t key_id,
                              psa_algorithm_t alg,
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *plaintext,
                              size_t plaintext_length,
                              uint8_t *ciphertext,
                              size_t ciphertext_size,
                              size_t *ciphertext_length)
{
#ifdef TFM_CRYPTO_AEAD_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_AEAD_ENCRYPT_SID,
        .key_id = key_id,
        .alg = alg,
        .aead_in = {.nonce = {0}, .nonce_length = nonce_length}
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_AEAD_ENCRYPT_SID;
    iov.key_id = key_id;
    iov.alg = alg;
    for (int cpt = 0; cpt < TFM_CRYPTO_MAX_NONCE_LENGTH; cpt++)
    {
      iov.aead_in.nonce[cpt] = 0;
    }
    iov.aead_in.nonce_length = nonce_length;

    /* Sanitize the optional input */
    if ((additional_data == NULL) && (additional_data_length != 0)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    size_t idx = 0;
/*    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = plaintext, .len = plaintext_length},
        {.base = additional_data, .len = additional_data_length},
    };
*/
     psa_invec in_vec[3];
     in_vec[0].base = &iov;
     in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
     in_vec[1].base = plaintext;
     in_vec[1].len = plaintext_length;
     in_vec[2].base = additional_data;
     in_vec[2].len = additional_data_length;

    psa_outvec out_vec[] = {
        {.base = ciphertext, .len = ciphertext_size},
    };

    if (nonce_length > TFM_CRYPTO_MAX_NONCE_LENGTH) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (nonce != NULL) {
        for (idx = 0; idx < nonce_length; idx++) {
            iov.aead_in.nonce[idx] = nonce[idx];
        }
    }

#ifdef TFM_PSA_API
/*
    size_t in_len = ARRAY_SIZE(in_vec);
    if (additional_data == NULL) {
        in_len--;
    }
    status = psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec, in_len,
                      out_vec, ARRAY_SIZE(out_vec));
*/

    status = API_DISPATCH_HDL(tfm_crypto_aead_encrypt,
                          TFM_CRYPTO_AEAD_ENCRYPT, hdl);
    psa_close(hdl);

#else
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_aead_encrypt,
                          TFM_CRYPTO_AEAD_ENCRYPT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_aead_encrypt,
                          TFM_CRYPTO_AEAD_ENCRYPT, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
#endif

    *ciphertext_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_AEAD_MODULE_DISABLED */
}

psa_status_t psa_aead_decrypt(psa_key_id_t key_id,
                              psa_algorithm_t alg,
                              const uint8_t *nonce,
                              size_t nonce_length,
                              const uint8_t *additional_data,
                              size_t additional_data_length,
                              const uint8_t *ciphertext,
                              size_t ciphertext_length,
                              uint8_t *plaintext,
                              size_t plaintext_size,
                              size_t *plaintext_length)
{
#ifdef TFM_CRYPTO_AEAD_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_AEAD_DECRYPT_SID,
        .key_id = key_id,
        .alg = alg,
        .aead_in = {.nonce = {0}, .nonce_length = nonce_length}
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_AEAD_DECRYPT_SID;
        iov.key_id = key_id;
        iov.alg = alg;
        for (int cpt = 0; cpt < TFM_CRYPTO_MAX_NONCE_LENGTH; cpt++)
        {
            iov.aead_in.nonce[cpt] = 0;
        }
        iov.aead_in.nonce_length = nonce_length;

    /* Sanitize the optional input */
    if ((additional_data == NULL) && (additional_data_length != 0)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    size_t idx = 0;
 /*   psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = ciphertext, .len = ciphertext_length},
        {.base = additional_data, .len = additional_data_length},
    };*/
      psa_invec in_vec[3];
      in_vec[0].base = &iov;
      in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
      in_vec[1].base = ciphertext;
      in_vec[1].len = ciphertext_length;
      in_vec[2].base = additional_data;
      in_vec[2].len = additional_data_length;


    psa_outvec out_vec[] = {
        {.base = plaintext, .len = plaintext_size},
    };

    if (nonce_length > TFM_CRYPTO_MAX_NONCE_LENGTH) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (nonce != NULL) {
        for (idx = 0; idx < nonce_length; idx++) {
            iov.aead_in.nonce[idx] = nonce[idx];
        }
    }

#ifdef TFM_PSA_API
/*
    size_t in_len = ARRAY_SIZE(in_vec);
    if (additional_data == NULL) {
        in_len--;
    }
    status = psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec, in_len,
                      out_vec, ARRAY_SIZE(out_vec));
                      * */

    status = API_DISPATCH_HDL(tfm_crypto_aead_decrypt,
                          TFM_CRYPTO_AEAD_DECRYPT,hdl);
    psa_close(hdl);

#else
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_aead_decrypt,
                          TFM_CRYPTO_AEAD_DECRYPT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_aead_decrypt,
                          TFM_CRYPTO_AEAD_DECRYPT,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
#endif

    *plaintext_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_AEAD_MODULE_DISABLED */
}

psa_status_t psa_sign_message(psa_key_id_t key_id,
                              psa_algorithm_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *signature,
                              size_t signature_size,
                              size_t *signature_length)
{
#ifdef TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_SIGN_MESSAGE_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/

/****
 * Modification
 ***/
    randomize_output_buffer((uint8_t*)input, input_length, signature, signature_size);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_SIGN_MESSAGE_SID;
        iov.key_id = key_id;
        iov.alg = alg;

        psa_invec in_vec[2];
        in_vec[0].base = &iov;
        in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
        in_vec[1].base = input;
        in_vec[1].len = input_length;

    psa_outvec out_vec[] = {
        {.base = signature, .len = signature_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    status = API_DISPATCH(tfm_crypto_sign_message,
                          TFM_CRYPTO_SIGN_MESSAGE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_sign_message,
                          TFM_CRYPTO_SIGN_MESSAGE,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    if (status == PSA_SUCCESS) {
        *signature_length = out_vec[0].len;
    }

    return status;
#endif /* TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED */
}

psa_status_t psa_verify_message(psa_key_id_t key_id,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                const uint8_t *signature,
                                size_t signature_length)
{
#ifdef TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
   /*
    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_VERIFY_MESSAGE_SID,
        .key_id = key_id,
        .alg = alg
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
        {.base = signature, .len = signature_length}
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_VERIFY_MESSAGE_SID;
        iov.key_id = key_id;
        iov.alg = alg;

    psa_invec in_vec[3];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;
    in_vec[2].base = signature;
    in_vec[2].len = signature_length;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_verify_message,
                                    TFM_CRYPTO_VERIFY_MESSAGE);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_verify_message,
                                    TFM_CRYPTO_VERIFY_MESSAGE,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED */
}

psa_status_t psa_sign_hash(psa_key_id_t key,
                           psa_algorithm_t alg,
                           const uint8_t *hash,
                           size_t hash_length,
                           uint8_t *signature,
                           size_t signature_size,
                           size_t *signature_length)
{
	psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
#ifdef TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_SIGN_HASH_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = hash, .len = hash_length},
    };
*/

/****
 * Modification
 ***/
    psa_init_signal(PSA_SIGNAL_CRYPTO);
    randomize_output_buffer((uint8_t*)hash, hash_length, signature, signature_size);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_SIGN_HASH_SID;
     iov.key_id = key;
     iov.alg = alg;

     psa_invec in_vec[2];
     in_vec[0].base = &iov;
     in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
     in_vec[1].base = hash;
     in_vec[1].len = hash_length;


    psa_outvec out_vec[] = {
        {.base = signature, .len = signature_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_sign_hash,
                          TFM_CRYPTO_SIGN_HASH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_sign_hash,
                          TFM_CRYPTO_SIGN_HASH,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *signature_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED */
}

psa_status_t psa_verify_hash(psa_key_id_t key,
                             psa_algorithm_t alg,
                             const uint8_t *hash,
                             size_t hash_length,
                             const uint8_t *signature,
                             size_t signature_length)
{
#ifdef TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_VERIFY_HASH_SID,
        .key_id = key_id,
        .alg = alg
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = hash, .len = hash_length},
        {.base = signature, .len = signature_length}
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_VERIFY_HASH_SID;
     iov.key_id = key;
     iov.alg = alg;

     psa_invec in_vec[3];
     in_vec[0].base = &iov,
     in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
     in_vec[1].base = hash;
     in_vec[1].len = hash_length;
     in_vec[2].base = signature;
     in_vec[2].len = signature_length;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_verify_hash,
                                    TFM_CRYPTO_VERIFY_HASH);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_verify_hash,
                                    TFM_CRYPTO_VERIFY_HASH,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    return status;
#endif /* TFM_CRYPTO_ASYM_SIGN_MODULE_DISABLED */
}

psa_status_t psa_asymmetric_encrypt(psa_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length)
{
#ifdef TFM_CRYPTO_ASYM_ENCRYPT_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
   /* struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_ASYMMETRIC_ENCRYPT_SID,
        .key_id = key_id,
        .alg = alg
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_ASYMMETRIC_ENCRYPT_SID;
    iov.key_id = key;
    iov.alg = alg;

    /* Sanitize the optional input */
    if ((salt == NULL) && (salt_length != 0)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

   /* psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
        {.base = salt, .len = salt_length}
    };
  */
    psa_invec in_vec[3];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;
    in_vec[2].base = salt;
    in_vec[2].len = salt_length;


    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

#ifdef TFM_PSA_API
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/

/*
    size_t in_len = ARRAY_SIZE(in_vec);
    if (salt == NULL) {
        in_len--;
    }
    status = psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec, in_len,
                      out_vec, ARRAY_SIZE(out_vec));
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_asymmetric_encrypt,
                          TFM_CRYPTO_ASYMMETRIC_ENCRYPT,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

#else
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_asymmetric_encrypt,
                          TFM_CRYPTO_ASYMMETRIC_ENCRYPT);
*/
/****
 * End of Modification
 ****/
#endif

    *output_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_ASYM_ENCRYPT_MODULE_DISABLED */
}

psa_status_t psa_asymmetric_decrypt(psa_key_id_t key,
                                    psa_algorithm_t alg,
                                    const uint8_t *input,
                                    size_t input_length,
                                    const uint8_t *salt,
                                    size_t salt_length,
                                    uint8_t *output,
                                    size_t output_size,
                                    size_t *output_length)
{
#ifdef TFM_CRYPTO_ASYM_ENCRYPT_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_ASYMMETRIC_DECRYPT_SID,
        .key_id = key_id,
        .alg = alg
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_ASYMMETRIC_DECRYPT_SID;
     iov.key_id = key;
     iov.alg = alg;

    /* Sanitize the optional input */
    if ((salt == NULL) && (salt_length != 0)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
/*
    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
        {.base = salt, .len = salt_length}
    };
*/
    psa_invec in_vec[3];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;
    in_vec[2].base = salt;
    in_vec[2].len = salt_length;

    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

#ifdef TFM_PSA_API


/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/

/*
    size_t in_len = ARRAY_SIZE(in_vec);
    if (salt == NULL) {
        in_len--;
    }
    status = psa_call(TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec, in_len,
                      out_vec, ARRAY_SIZE(out_vec));
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_asymmetric_decrypt,
                          TFM_CRYPTO_ASYMMETRIC_DECRYPT,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

#else
/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_asymmetric_decrypt,
                          TFM_CRYPTO_ASYMMETRIC_DECRYPT);
*/
/****
 * End of Modification
 ****/
#endif

    *output_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_ASYM_ENCRYPT_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_get_capacity(
                                const psa_key_derivation_operation_t *operation,
                                size_t *capacity)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_GET_CAPACITY_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_GET_CAPACITY_SID;
     iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

    psa_outvec out_vec[] = {
        {.base = capacity, .len = sizeof(size_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_key_derivation_get_capacity,
                          TFM_CRYPTO_KEY_DERIVATION_GET_CAPACITY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_get_capacity,
                          TFM_CRYPTO_KEY_DERIVATION_GET_CAPACITY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_output_bytes(
                                      psa_key_derivation_operation_t *operation,
                                      uint8_t *output,
                                      size_t output_length)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_OUTPUT_BYTES_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_OUTPUT_BYTES_SID;
    iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

    psa_outvec out_vec[] = {
        {.base = output, .len = output_length},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
    status = API_DISPATCH(tfm_crypto_key_derivation_output_bytes,
                          TFM_CRYPTO_KEY_DERIVATION_OUTPUT_BYTES);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_output_bytes,
                          TFM_CRYPTO_KEY_DERIVATION_OUTPUT_BYTES, hdl);

    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_input_key(
                                      psa_key_derivation_operation_t *operation,
                                      psa_key_derivation_step_t step,
                                      psa_key_id_t key)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
    /* struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_INPUT_KEY_SID,
        .key_id = key_id,
        .step = step,
        .op_handle = operation->handle,
    };
  */
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

        struct tfm_crypto_pack_iovec iov;
        iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_INPUT_KEY_SID;
        iov.key_id = key;
        iov.step = step;
        iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_key_derivation_input_key,
                                    TFM_CRYPTO_KEY_DERIVATION_INPUT_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_key_derivation_input_key,
                                    TFM_CRYPTO_KEY_DERIVATION_INPUT_KEY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_abort(psa_key_derivation_operation_t *operation)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
   /* struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_ABORT_SID,
        .op_handle = operation->handle,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_ABORT_SID;
    iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
//    status = API_DISPATCH(tfm_crypto_key_derivation_abort,
//                          TFM_CRYPTO_KEY_DERIVATION_ABORT);
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_abort,
                          TFM_CRYPTO_KEY_DERIVATION_ABORT, hdl);

    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_key_agreement(
                                      psa_key_derivation_operation_t *operation,
                                      psa_key_derivation_step_t step,
                                      psa_key_id_t private_key,
                                      const uint8_t *peer_key,
                                      size_t peer_key_length)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_KEY_AGREEMENT_SID,
        .key_id = private_key,
        .step = step,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = peer_key, .len = peer_key_length},
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_KEY_AGREEMENT_SID;
    iov.key_id = private_key;
    iov.step = step;
    iov.op_handle = operation->handle;

    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = peer_key;
    in_vec[1].len = peer_key_length;

    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
//    status = API_DISPATCH(tfm_crypto_key_derivation_key_agreement,
//                          TFM_CRYPTO_KEY_DERIVATION_KEY_AGREEMENT);
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_key_agreement,
                          TFM_CRYPTO_KEY_DERIVATION_KEY_AGREEMENT, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_generate_random(uint8_t *output,
                                 size_t output_size)
{
#ifdef TFM_CRYPTO_RNG_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*    struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_GENERATE_RANDOM_SID,
    };
*/
 /****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_GENERATE_RANDOM_SID;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

    if (output_size == 0) {
        return PSA_SUCCESS;
    }

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 //   status = API_DISPATCH(tfm_crypto_generate_random,
 //                         TFM_CRYPTO_GENERATE_RANDOM);
/****
 * Modification
 ***/
     status = API_DISPATCH_HDL(tfm_crypto_generate_random,
                           TFM_CRYPTO_GENERATE_RANDOM, hdl);

     psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_RNG_MODULE_DISABLED */
}

psa_status_t psa_generate_key(const psa_key_attributes_t *attributes,
                              psa_key_id_t *key)
{
#ifdef TFM_CRYPTO_KEY_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
 /****
 * Original
 ****/

/*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_GENERATE_KEY_SID,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_GENERATE_KEY_SID;

    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = attributes;
    in_vec[1].len = sizeof(psa_key_attributes_t);


    psa_outvec out_vec[] = {
        {.base = key, .len = sizeof(psa_key_id_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_generate_key,
                          TFM_CRYPTO_GENERATE_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_generate_key,
                          TFM_CRYPTO_GENERATE_KEY, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ***/


    return status;
#endif /* TFM_CRYPTO_KEY_MODULE_DISABLED */
}

psa_status_t psa_aead_update_ad(psa_aead_operation_t *operation,
                                const uint8_t *input,
                                size_t input_length)
{
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
    (void) operation;
    (void) input;
    (void) input_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_finish(psa_aead_operation_t *operation,
                             uint8_t *ciphertext,
                             size_t ciphertext_size,
                             size_t *ciphertext_length,
                             uint8_t *tag,
                             size_t tag_size,
                             size_t *tag_length)
{
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

    (void) operation;
    (void) ciphertext;
    (void) ciphertext_size;
    (void) ciphertext_length;
    (void) tag;
    (void) tag_size;
    (void) tag_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_verify(psa_aead_operation_t *operation,
                             uint8_t *plaintext,
                             size_t plaintext_size,
                             size_t *plaintext_length,
                             const uint8_t *tag,
                             size_t tag_length)
{
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
    (void) operation;
    (void) plaintext;
    (void) plaintext_size;
    (void) plaintext_length;
    (void) tag;
    (void) tag_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_abort(psa_aead_operation_t *operation)
{
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);
    (void) operation;
    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_mac_compute(psa_key_id_t key_id,
                             psa_algorithm_t alg,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *mac,
                             size_t mac_size,
                             size_t *mac_length)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_COMPUTE_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
      iov.sfn_id = TFM_CRYPTO_MAC_COMPUTE_SID,
      iov.key_id = key_id;
      iov.alg = alg;

       psa_invec in_vec[2];
       in_vec[0].base = &iov;
       in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
       in_vec[1].base = input;
       in_vec[1].len = input_length;

    psa_outvec out_vec[] = {
        {.base = mac, .len = mac_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
//  status = API_DISPATCH(tfm_crypto_mac_compute,
//                        TFM_CRYPTO_MAC_COMPUTE);
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_mac_compute,
                          TFM_CRYPTO_MAC_COMPUTE,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    if (status == PSA_SUCCESS) {
        *mac_length = out_vec[0].len;
    }

    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_mac_verify(psa_key_id_t key_id,
                            psa_algorithm_t alg,
                            const uint8_t *input,
                            size_t input_length,
                            const uint8_t *mac,
                            const size_t mac_length)
{
#ifdef TFM_CRYPTO_MAC_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_MAC_VERIFY_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
        {.base = mac, .len = mac_length},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_MAC_VERIFY_SID;
    iov.key_id = key_id;
    iov.alg = alg;

    psa_invec in_vec[3];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;
    in_vec[2].base = mac;
    in_vec[2].len = mac_length;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_mac_verify,
                                    TFM_CRYPTO_MAC_VERIFY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_mac_verify,
                                    TFM_CRYPTO_MAC_VERIFY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_MAC_MODULE_DISABLED */
}

psa_status_t psa_cipher_encrypt(psa_key_id_t key_id,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);


/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/

    /*struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_ENCRYPT_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/

/****
 * Modification
 ***/
    randomize_output_buffer((uint8_t*)input, input_length, output, output_size);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);

/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_CIPHER_ENCRYPT_SID;
    iov.key_id = key_id;
    iov.alg = alg;

    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = input;
    in_vec[1].len = input_length;


    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
     status = API_DISPATCH(tfm_crypto_cipher_encrypt,
                          TFM_CRYPTO_CIPHER_ENCRYPT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_encrypt,
                          TFM_CRYPTO_CIPHER_ENCRYPT, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ***/


    if (status == PSA_SUCCESS) {
        *output_length = out_vec[0].len;
    }

    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_cipher_decrypt(psa_key_id_t key_id,
                                psa_algorithm_t alg,
                                const uint8_t *input,
                                size_t input_length,
                                uint8_t *output,
                                size_t output_size,
                                size_t *output_length)
{
#ifdef TFM_CRYPTO_CIPHER_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_CIPHER_DECRYPT_SID,
        .key_id = key_id,
        .alg = alg,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = input, .len = input_length},
    };
*/
/****
 * Modification
 ***/
    randomize_output_buffer((uint8_t*)input, input_length, output, output_size);
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
      iov.sfn_id = TFM_CRYPTO_CIPHER_DECRYPT_SID;
      iov.key_id = key_id;
      iov.alg = alg;
      psa_invec in_vec[2];
      in_vec[0].base = &iov;
      in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
      in_vec[1].base = input;
      in_vec[1].len = input_length;


    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*
     status = API_DISPATCH(tfm_crypto_cipher_decrypt,
                          TFM_CRYPTO_CIPHER_DECRYPT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_cipher_decrypt,
                          TFM_CRYPTO_CIPHER_DECRYPT, hdl);

    psa_close(hdl);
/****
 * End of Modification
 ***/

    if (status == PSA_SUCCESS) {
        *output_length = out_vec[0].len;
    }

    return status;
#endif /* TFM_CRYPTO_CIPHER_MODULE_DISABLED */
}

psa_status_t psa_raw_key_agreement(psa_algorithm_t alg,
                                   psa_key_id_t private_key,
                                   const uint8_t *peer_key,
                                   size_t peer_key_length,
                                   uint8_t *output,
                                   size_t output_size,
                                   size_t *output_length)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_RAW_KEY_AGREEMENT_SID,
        .alg = alg,
        .key_id = private_key
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = peer_key, .len = peer_key_length},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

    struct tfm_crypto_pack_iovec iov;
    iov.sfn_id = TFM_CRYPTO_RAW_KEY_AGREEMENT_SID;
    iov.alg = alg;
    iov.key_id = private_key;

    psa_invec in_vec[2];
    in_vec[0].base = &iov;
    in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
    in_vec[1].base = peer_key;
    in_vec[1].len = peer_key_length;

    psa_outvec out_vec[] = {
        {.base = output, .len = output_size},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_raw_key_agreement,
                          TFM_CRYPTO_RAW_KEY_AGREEMENT);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_raw_key_agreement,
                          TFM_CRYPTO_RAW_KEY_AGREEMENT,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/

    *output_length = out_vec[0].len;

    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_setup(psa_key_derivation_operation_t *operation,
                                      psa_algorithm_t alg)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_SETUP_SID,
        .alg = alg,
        .op_handle = operation->handle,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

     struct tfm_crypto_pack_iovec iov;
     iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_SETUP_SID;
     iov.alg = alg;
     iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };
    psa_outvec out_vec[] = {
        {.base = &(operation->handle), .len = sizeof(uint32_t)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_key_derivation_setup,
                          TFM_CRYPTO_KEY_DERIVATION_SETUP);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_setup,
                          TFM_CRYPTO_KEY_DERIVATION_SETUP,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_set_capacity(
                                      psa_key_derivation_operation_t *operation,
                                      size_t capacity)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
 /*   struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_SET_CAPACITY_SID,
        .capacity = capacity,
        .op_handle = operation->handle,
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
      iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_SET_CAPACITY_SID;
      iov.capacity = capacity;
      iov.op_handle = operation->handle;

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_key_derivation_set_capacity,
                                    TFM_CRYPTO_KEY_DERIVATION_SET_CAPACITY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_key_derivation_set_capacity,
                                    TFM_CRYPTO_KEY_DERIVATION_SET_CAPACITY,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_input_bytes(
                                      psa_key_derivation_operation_t *operation,
                                      psa_key_derivation_step_t step,
                                      const uint8_t *data,
                                      size_t data_length)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_INPUT_BYTES_SID,
        .step = step,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = data, .len = data_length},
    };
  */
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
      iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_INPUT_BYTES_SID;
      iov.step = step;
      iov.op_handle = operation->handle;

      psa_invec in_vec[2];
      in_vec[0].base = &iov;
      in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
      in_vec[1].base = data;
      in_vec[1].len = data_length;

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH_NO_OUTVEC(tfm_crypto_key_derivation_input_bytes,
                                    TFM_CRYPTO_KEY_DERIVATION_INPUT_BYTES);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_NO_OUTVEC_HDL(tfm_crypto_key_derivation_input_bytes,
                                    TFM_CRYPTO_KEY_DERIVATION_INPUT_BYTES,hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_key_derivation_output_key(
                                      const psa_key_attributes_t *attributes,
                                      psa_key_derivation_operation_t *operation,
                                      psa_key_id_t *key)
{
#ifdef TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status;
    psa_init_signal(PSA_SIGNAL_CRYPTO);

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
  /*  struct tfm_crypto_pack_iovec iov = {
        .sfn_id = TFM_CRYPTO_KEY_DERIVATION_OUTPUT_KEY_SID,
        .op_handle = operation->handle,
    };

    psa_invec in_vec[] = {
        {.base = &iov, .len = sizeof(struct tfm_crypto_pack_iovec)},
        {.base = attributes, .len = sizeof(psa_key_attributes_t)},
    };
*/
/****
 * Modification
 ***/
    psa_handle_t hdl = psa_connect(PSA_SID_CRYPTO, 0);
/****
 * End of Modification
 ***/

      struct tfm_crypto_pack_iovec iov;
      iov.sfn_id = TFM_CRYPTO_KEY_DERIVATION_OUTPUT_KEY_SID;
      iov.op_handle = operation->handle;
      psa_invec in_vec[2];
      in_vec[0].base = &iov;
      in_vec[0].len = sizeof(struct tfm_crypto_pack_iovec);
      in_vec[1].base = attributes;
      in_vec[1].len = sizeof(psa_key_attributes_t);

    psa_outvec out_vec[] = {
        {.base = key, .len = sizeof(psa_key_id_t)}
    };

/****
 * Modified by Provenrun
 ***/
/****
 * Original
 ****/
/*
    status = API_DISPATCH(tfm_crypto_key_derivation_output_key,
                          TFM_CRYPTO_KEY_DERIVATION_OUTPUT_KEY);
*/
/****
 * Modification
 ***/
    status = API_DISPATCH_HDL(tfm_crypto_key_derivation_output_key,
                          TFM_CRYPTO_KEY_DERIVATION_OUTPUT_KEY, hdl);
    psa_close(hdl);
/****
 * End of Modification
 ****/
    return status;
#endif /* TFM_CRYPTO_KEY_DERIVATION_MODULE_DISABLED */
}

psa_status_t psa_aead_encrypt_setup(psa_aead_operation_t *operation,
                                    psa_key_id_t key_id,
                                    psa_algorithm_t alg)
{
    psa_status_t status;
    (void) operation;
    (void) key_id;
    (void) alg;
    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_decrypt_setup(psa_aead_operation_t *operation,
                                    psa_key_id_t key_id,
                                    psa_algorithm_t alg)
{
    psa_status_t status;
    (void) operation;
    (void) key_id;
    (void) alg;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_generate_nonce(psa_aead_operation_t *operation,
                                     uint8_t *nonce,
                                     size_t nonce_size,
                                     size_t *nonce_length)
{
    psa_status_t status;
    (void) operation;
    (void) nonce;
    (void) nonce_size;
    (void) nonce_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_set_nonce(psa_aead_operation_t *operation,
                                const uint8_t *nonce,
                                size_t nonce_length)
{
    psa_status_t status;
    (void) operation;
    (void) nonce;
    (void) nonce_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_set_lengths(psa_aead_operation_t *operation,
                                  size_t ad_length,
                                  size_t plaintext_length)
{
    psa_status_t status;
    (void) operation;
    (void) ad_length;
    (void) plaintext_length;
    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}

psa_status_t psa_aead_update(psa_aead_operation_t *operation,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *output,
                             size_t output_size,
                             size_t *output_length)
{
    psa_status_t status;
    (void) operation;
    (void) input;
    (void) input_length;
    (void) output;
    (void) output_size;
    (void) output_length;

    status = PSA_ERROR_NOT_SUPPORTED;

    return status;
}
