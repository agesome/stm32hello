/*
 * Copyright (c) 2019-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/**
 * \file psa/error.h
 * \brief Standard error codes for the SPM and RoT Services
 */

#ifndef __PSA_ERROR_H__
#define __PSA_ERROR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* If #PSA_SUCCESS is already defined, it means that #psa_status_t
 * is also defined in an external header, so prevent its multiple
 * definition.
 */
#ifndef PSA_SUCCESS
typedef int32_t psa_status_t;
#endif

/* ######################################################################## */
/*                         C-CONSTANTS - PSA COMMON ERRORS                  */
/* ######################################################################## */
/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA success is a standardized value it must be equal to 0.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs the operation was
 *        a success. Refer to each API's documentation in order to be sure.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_SUCCESS                     ((psa_status_t)0)

/**
 * @brief C-Constants used to declare a psa success
 *        A type message is a int32_t value.
 *        The PSA success reboot is a standardized value it must be equal to 1.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs the operation was
 *        a success reboot. Refer to each API's documentation in order to be sure.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_SUCCESS_REBOOT              ((psa_status_t)1)

/**
 * @brief C-Constants used to declare a psa success
 *        A type message is a int32_t value.
 *        The PSA success restart is a standardized value it must be equal to 2.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs the operation was
 *        a success restart. Refer to each API's documentation in order to be sure.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_SUCCESS_RESTART             ((psa_status_t)2)

/**
 * @brief C-Constants used to declare a psa success
 *        A type message is a int32_t value.
 *        The PSA success restart is a standardized value it must be equal to 3.
 *        This define may be used to set a psa_status_t type.
 *
 *         The action was completed successfully and requires the installation of a dependency to complete
 *          installation.
 *
 * @usage this success code is not currently supported.
 *        it is present only to respect PSA specification.
 */
#define PSA_SUCCESS_DEPENDENCY_NEEDED ((psa_status_t)+3)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA PSA_ERROR_PROGRAMMER_ERROR is a standardized value it must be equal to -129.
 *        This define may be used to set a psa_status_t type.
 *
 *        This value informs an infraction done in the PSA Client API or PSA Secure Partition API
 *        mentioned in the PSA Firmware Framework Reference manual.
 *        If these APIs encounters a programmer error, a psa_panic() will be triggered.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_PROGRAMMER_ERROR      ((psa_status_t)-129)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA Error connection refused is a standardized value it must be equal to -130.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs the caller cannot connect to a RoT Service.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_CONNECTION_REFUSED    ((psa_status_t)-130)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA connection busy error is a standardized value it must be equal to -131.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs the caller cannot connect to a RoT Service
 *        because the RoT Service is actually busy.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_CONNECTION_BUSY       ((psa_status_t)-131)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA error generic error is a standardized value it must be equal to -132.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs of an arror that does not
 *          correspond to any defined failure case.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_GENERIC_ERROR         ((psa_status_t)-132)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA not permitted is a standardized value it must be equal to -133.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that the requested action
 *          is denied by a policy.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_NOT_PERMITTED         ((psa_status_t)-133)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA not supported error is a standardized value it must be equal to -134.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that the requested operation or
 *          a parameter is not supported.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */

#define PSA_ERROR_NOT_SUPPORTED         ((psa_status_t)-134)

 /**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA invalid argument error is a standardized value it must be equal to -135.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that the parameters
 *          passed to the RoT Service are invalid.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INVALID_ARGUMENT      ((psa_status_t)-135)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA invalid handle is a standardized value it must be equal to -136.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that a handle parameter
 *          is not valid.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INVALID_HANDLE        ((psa_status_t)-136)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA bad status is a standardized value it must be equal to -137
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that the requested
 *          action cannot be performed in the current state.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_BAD_STATE             ((psa_status_t)-137)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA buffer too small error is a standardized value it must be equal to -138.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that an output
 *          buffer parameter is too small.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_BUFFER_TOO_SMALL      ((psa_status_t)-138)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA already exists error is a standardized value it must be equal to -139.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that an identifier
 *          or index is already in use.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_ALREADY_EXISTS        ((psa_status_t)-139)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA does not exist is a standardized value it must be equal to -140.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that an identified
 *          resource does not exist.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_DOES_NOT_EXIST        ((psa_status_t)-140)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA insufficient memory error is a standardized value it must be equal to -141.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that there is not enough runtime
 *          memory.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INSUFFICIENT_MEMORY   ((psa_status_t)-141)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA insufficient storage is a standardized value it must be equal to -142.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that there
 *          is not enough persistent storage.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INSUFFICIENT_STORAGE  ((psa_status_t)-142)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA insufficient data is a standardized value it must be equal to -143.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that a data source has insufficient capacity left.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_INSUFFICIENT_DATA     ((psa_status_t)-143)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA service failure error is a standardized value it must be equal to -144.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs that there is an
 *          error within the RoT Service.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_SERVICE_FAILURE       ((psa_status_t)-144)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA communication failure is a standardized value it must be equal to -145.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs a communication
 *          failure between the RoT Service and another service or client application.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_COMMUNICATION_FAILURE ((psa_status_t)-145)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA storage failure error is a standardized value it must be equal to -146.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs a storage failure
 *          that may have led to data loss.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_STORAGE_FAILURE       ((psa_status_t)-146)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA hardware failure error is a standardized value it must be equal to -147.
 *        This define may be used to set a psa_status_t type.
 *
 *        If this value is returned by a PSA API, it informs a hardware failure was detected.
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_HARDWARE_FAILURE      ((psa_status_t)-147)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA dependency neededis a standardized value it must be equal to -156.
 *        This define may be used to set a psa_status_t type.
 *
 *        This value is returned by psa_fwu_install ind inform a dependency is required before installing the image
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_DEPENDENCY_NEEDED     ((psa_status_t)-156)

/**
 * @brief C-Constants used to declare a psa error
 *        A type message is a int32_t value.
 *        The PSA dependency neededis a standardized value it must be equal to -157.
 *        This define may be used to set a psa_status_t type.
 *
 *        This value is returned by RoT FWU to inform the image is already in installation
 *
 * @usage This constant is used by each PSA library and RoT Service.
 *        It shall be consistent between them
 */
#define PSA_ERROR_CURRENTLY_INSTALLING  ((psa_status_t)-157)


#ifdef __cplusplus
}
#endif

#endif /* __PSA_ERROR_H__ */
