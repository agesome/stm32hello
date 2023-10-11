/***
 * Some part of this code is derived on BSD-3-Clause TFM/v1.5.0 files
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/**************************************************************************//**
 * @file          psa_its.h
 * @brief         Code Module UKPSA - SECURE STORAGE sub-Module - Public API file.
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup
 ******************************************************************************
* @details This header contains the ITS  public declarations used for
 *          interacting with the ITS APIs.
 *
 *          This file must be included by the RoT Services that embed the
 *          ITS APIs.
 *
 * @implementation This file only defines the Secure partition common constants,types and APIs
 *                  of the Secure Partition library.
 ******************************************************************************
 * @addtogroup    PSA_secure_storage
 * @{
 */

/* ######################################################################## */
/*                                  HEADER                                  */
/* ######################################################################## */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed.            */
#if !defined(PSA_ITS_H)

/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  PSA_ITS_H

/* Define that we are inside this file (definition is undone at its end). */
#define  PSA_ITS_H_INSIDE


#include "psa/error.h"
#include "psa/storage_common.h"
#include <stddef.h>
/** @privatesection */

/* ######################################################################## */
/*                      MODULE PRIVATE API - C-TYPES                        */
/* ######################################################################## */
/* Hereafter are defined the C-Types specific to this Code Module, and part of
 *  of its Private API (used only in its internal implementation).
 *
 * @implementation The C-Types defined SHALL use only the base C-Types defined
 *  either in the uKernel Public API defined in UK module, or in the public
 *  API of this Code Module.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, a dedicated C-Type HAS TO BE defined for each meaningful
 *  elements of internal data of this Code Module (strong typing policy used).
 */
/* ######################################################################## */
/*                          C-CONSTANTS -  VERSION                          */
/* ######################################################################## */

#define PSA_ITS_API_VERSION_MAJOR  1  /**< The major version number of the
                                       * PSA ITS API
                                       */
#define PSA_ITS_API_VERSION_MINOR  0  /**< The minor version number of the
                                       * PSA ITS API
                                       */
/* ######################################################################## */
/*                          C-CONSTANTS -  SERVICE ERROR                    */
/* ######################################################################## */
/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA invalid signature is a standardized value it must be equal to -149.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that a signature, MAC
 *          or hash is incorrect.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INVALID_SIGNATURE     ((psa_status_t)-149)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA error data corrupt is a standardized value it must be equal to -152.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that a data is corrupted
 *            in the its filesystem.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_DATA_CORRUPT     ((psa_status_t)-152)

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates the data associated to the storage identifier are corrupted.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_DATA_CORRUPT          -10

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates an internal error found that cannot be recovered.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_INTERNAL_ERROR        -11

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates an CRC32 compute failed.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_INTERNAL_BAD_CRC       -12


/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates the connection is refused
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_CONNECTION_REFUSED     -13


/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates the ITS memory area is full
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_FULL                  -14

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates a write once flag has been detected.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ITS_FLAG_WRITE_ONCE_DETECTED    -15

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates the data to set/get are not aligned on 16 bytes.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_UNALIGNED_DATA        -16

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_NOT_A_VALID_BLOCK        -17

/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates the counter has reached its max value
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ERROR_ITS_MAX_COUNTER        -17


/* ######################################################################## */
/*                          C-CONSTANTS -  SERVICE INFO STATUS              */
/* ######################################################################## */
/**
 * @brief C-Constants used to declare a service specific error
 *        A service error is a psa_status_t value.
 *
 *        This error is specific to the ITS API and Storage RoT service.
 *        It indicates a compactage operation must be done.
 *
 * @usage This constant can be returned by the RoT Service to the ITS library.
 */
#define PSA_ITS_COMPACTAGE_POSSIBLE       10


/* ######################################################################## */
/*                       C-TYPES - PSA ITS CLIENT INSTANCE                  */
/* ######################################################################## */
/**
 * @brief C-Constants used to declare the mask for the valid flags for ITS operation
 *
 * @usage This constant is used to set the storage flag mask
 */
#define PSA_STORAGE_FLAG_MAX_MASK (uint32_t)(0x7)

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                      */
/* ######################################################################## */
/* Hereafter are declared the C-Functions implemented in this Code Module, and
 *  part of its Public API.
 *
 * @robustness In order to provide high level of robustness, all the defined
 *  C-Functions in the Public API SHALL have a Status Code (TukSTATUS) as
 *  return value. The sole exceptions are if the execution context of the
 *  C-Function makes impossible for the provided functionality to fail, or
 *  if the failure leads systematically to a uKernel Fatal Error (e.g.
 *  assertion of unexpected parameter value, execution context in regards
 *  of uKernel architecture, ...).
 */
/**
 * @brief C-Function psa_its_set stores data in the internal storage:
 * @implementation The function uses the psa_client library to communicate
 * with the ITS RoT service, first by establishing a connection via psa_call,
 * then sending messages via psa_connect, and finally psa_close to disconnect.
 * The goal is to ask the ITS Rot Service to save the data communicated
 * via the psa_client library.
 * @param[in] (psa_storage_uid_t)uid : The identifier for the data.
 * @param[in] (size_t)data_length : The size in bytes of the data in
 * p_data .
 * @param[in] (const void*)p_data : A buffer containing the data.
 * @param[in] (psa_storage_create_flags_t) create_flags : The flags
 * that the data will be stored with.
 * @return (psa_status_t)Status: a status indicating the success/failure
 *  of the operation:
 * @retval PSA_SUCCESS The operation completed successfully.
 * @retval PSA_ERROR_NOT_PERMITTED The operation failed because the provided
 * uid value was already created with PSA_STORAGE_FLAG_WRITE_ONCE .
 * @retval PSA_ERROR_NOT_SUPPORTED The operation failed because one or more
 * of the flags provided in create_flags is not supported or is not valid.
 * @retval PSA_ERROR_INSUFFICIENT_STORAGE The operation failed because there
 * was insufficient space on the storage medium.
 * @retval PSA_ERROR_STORAGE_FAILURE The operation failed because the physical
 *  storage has failed (Fatal error).
 * @retval PSA_ERROR_INVALID_ARGUMENT The operation failed because one of
 * the provided pointers ( p_data ) is invalid, for example is NULL or
 * references memory the caller cannot access.
 * @retval PSA_ERROR_COMMUNICATION_FAILURE When communication fails between
 * the client and the ITS Rot Service.
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,size_t data_length,const void *p_data,psa_storage_create_flags_t create_flags);


/**
 * @brief C-Function psa_its_get retrieves data associated with a
 * provided UID. Retrieves up to data_size bytes of the data associated
 * with uid, starting at data_offset bytes from the beginning of the data.
 * Upon successful completion, the data will be placed in the p_data
 * buffer, which must be at least data_size bytes in size.
 * The length of the data returned will be in p_data_length.
 * If data_size is 0, the contents of p_data_length will be set to zero.
 * @implementation The function uses the psa_client library to communicate
 * with the ITS RoT service, first by establishing a connection via
 * psa_call, then sending messages via psa_connect, and finally psa_close to disconnect.
 * The goal is to retrieve from the ITS Rot Service the data saved
 * according to the UID via the communication mechanism of the
 * psa_client library.
 * @param[in] (psa_storage_uid_t)uid The uid value.
 * @param[in] (size_t)data_offset The starting offset of the data requested.
 * @param[in] (size_t)data_size The amount of data requested.
 * @param[in] (void *)p_data On success, the buffer where the data will be
 * placed.
 * @param[in] (size_t *)p_data_length On success, this will contain size of the data
 * placed in p_data
 * @return (psa_status_t)Status a status indicating the success/failure of the
 *  operation.
 * @retval PSA_SUCCESS The operation completed successfully.
 * @retval PSA_ERROR_DOES_NOT_EXIST The operation failed because the
 * provided uid value was not found in the storage.
 * @retval PSA_ERROR_STORAGE_FAILURE The operation failed because the
 * physical storage has failed (Fatal error).
 * @retval PSA_ERROR_INVALID_ARGUMENT The operation failed because one of
 * the provided arguments( p_data , p_data_length ) is invalid,
 * for example is NULL or references memory the caller cannot access.
 * In addition, this can also happen if data_offset is larger than the
 * size of the data associated with uid .
 */
psa_status_t psa_its_get(psa_storage_uid_t uid,size_t data_offset,size_t data_size,void *p_data,size_t *p_data_length);


/**
 * @brief C-Function psa_its_get_info, retrieves the metadata about the
 * provided uid. Retrieves the metadata stored for a given uid as a
 * psa_storage_info_t structure.
 * @implementation The function uses the psa_client library to
 * communicate with the ITS RoT service, first by establishing a
 * connection via psa_call, then sending messages via psa_connect,
 * and finally psa_close to disconnect.
 * The goal is to retrieve from the ITS Rot Service the information
 * relating to the UID via the communication mechanism of the
 * psa_client library.
 * @param[in] (psa_storage_uid_t)uid The uid value.
 * @param[in] (struct psa_storage_info_t *) p_info A pointer to the
 * psa_storage_info_t struct that will be populated with the metadata.
 * @return (psa_status_t) a status indicating the success/failure
 * of the operation.
 * @retval PSA_SUCCESS The operation completed successfully.
 * @retval PSA_ERROR_DOES_NOT_EXIST The operation failed because the
 * provided uid value was not found in the storage.
 * @retval PSA_ERROR_STORAGE_FAILURE The operation failed because the
 * physical storage has failed (Fatal error).
 * @retval PSA_ERROR_INVALID_ARGUMENT The operation failed because one of
 * the provided pointers ( p_info ) is invalid, for example is NULL or
 * references memory the caller cannot access.
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,struct psa_storage_info_t *p_info);


/**
 * @brief C-Function psa_its_remove, removes the provided key and its
 * associated data from the storage.
 * Deletes the data from internal storage.
 * @implementation The function uses the psa_client library to
 * communicate with the ITS RoT service, first by establishing a
 * connection via psa_call, then sending messages via psa_connect,
 * and finally psa_close to close the connection.
 * The goal is to delete all the data saved in the ITS RoT Service
 * relating to a specific UID.
 * @param[in] (psa_storage_uid_t)uid The uid value.
 * @return (psa_status_t) a status indicating the success/failure
 * of the operation.
 * @retval PSA_SUCCESS The operation completed successfully.
 * @retval PSA_ERROR_INVALID_ARGUMENT The operation failed because one or
 * more of the given arguments were invalid (null pointer, wrong flags and so on).
 * @retval PSA_ERROR_DOES_NOT_EXIST The operation failed because the
 * provided key value was not found in the storage.
 * @retval PSA_ERROR_NOT_PERMITTED The operation failed because the provided
*  key value was created with PSA_STORAGE_FLAG_WRITE_ONCE .
 * @retval PSA_ERROR_STORAGE_FAILURE The operation failed because the
 * physical storage has failed (Fatal error).
 * */
psa_status_t psa_its_remove(psa_storage_uid_t uid);


/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
 /** @} */
#undef PSA_ITS_H_INSIDE
#endif
