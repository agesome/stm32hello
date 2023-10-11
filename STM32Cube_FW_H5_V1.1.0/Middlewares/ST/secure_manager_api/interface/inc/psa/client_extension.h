/***
 * Some part of this code is derived on BSD-3-Clause TFM/v1.5.0 files
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/**************************************************************************//**
 * @file          client_extension.h
 * @brief         PSA library - extension Public Client API file.
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       PSA
 ******************************************************************************
 * @details This header contains the extended declarations used for
 *          building the different PSA CLient API application.
 *
 *          This file must be included by the applications that embeds the
 *          PSA Client libraries and by the PSA RoT Service. The file declares the
 *          common types of the PSA model.
 *
 *          The header file also defines the Signal and type values that must
 *          be consistent between the client and secure partition API
 *
 * @implementation This file only defines the common constants and types.
 *                Other files such as client/psa_client.h or securepartition/psa_secpart.h
 *                define the public constants and types specific to each library.
 *
 ******************************************************************************
 * @addtogroup    PSA
 * @{
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                                  HEADER                                  */
/* //////////////////////////////////////////////////////////////////////// */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(PSA_H)


/*__________________________________________________________________________*/
/* Define the global C-Preprocessor statements for smart module compilation.*/

/* Define that this include file has been processed (single inclusion). */
#define  PSA_H


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "psa/error.h"

/** @publicsection */

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-CONSTANTS                      */
/* ######################################################################## */
/* Hereafter are defined the C-Constants specific to this Code Module, and part
 *  of its Public API.
 *
 * @implementation As good coding practice, and to enforce high quality and
 *  robust software, each C-Constant HAS TO BE defined with an associated
 *  C-Type (strong typing policy used).
 */


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - PSA GENERIC                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief Definition of different attributes for GNUC compiler
 */
#if  defined ( __GNUC__ )
 #ifndef __weak
 #define __weak   __attribute__((weak))
 #endif /* __weak */

 #ifndef __packed
 #define __packed __attribute__((__packed__))
 #endif /* __packed */
#endif /* __GNUC__ */

/**
 * @brief Definition of different attributes for ARMCC compiler
 */
#define ARMCC_MIN_VERSION  6010050
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= ARMCC_MIN_VERSION)
 #ifndef __weak
 #define __weak  __WEAK
 #endif /* __weak */

 #ifndef __packed
 #define __packed  __PACKED
 #endif /* __packed */
#endif


/**
 * @brief C-Constants used to define an unsigned zeroed-value.
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_UFALSE          0x0U
/**
 * @brief C-Constants used to define an unsigned one value.
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_UTRUE           0x1U

/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - PSA SID                            */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief C-Constants used to declare a SID.
 *        A SID is a unique service identifier used to identify the RoT
 *        service to communicate with.
 *        The implementation is arbitrarily defined as:
 *              - it must be unique
 *              - its type must be uint32_t
 *              - an SID must be associated to an AUID statically in the Client library
 *              - it must not change between upgrades
 *
 *        The PSA_SID_CLIENT is an SID number that refers to a RoT Service
 *        for testing purposes.
 *
 * @usage This constant is only for the Client API: psa_connect().
 *        If the Client library does not statically associate a SID with an AUID
 *        the psa_connect() will return an error
 */
#define PSA_SID_CLIENT 0x1U

/**
 * @brief C-Constants used to declare a SID.
 *        A SID is a unique service identifier used to identify the RoT
 *        service to communicate with.
 *        The implementation is arbitrarily defined as:
 *              - it must be unique
 *              - its type must be uint32_t
 *              - a SID must be associated to an AUID statically in the Client library
 *              - it must not changed between upgrades
 *
 *        The PSA_SID_STORAGE is the SID number that refers to the Storage
 *        RoT Service.
 *
 * @usage This constant is only for the Client API: psa_connect().
 *        If the Client library does not statically associate a SID with an AUID
 *        the psa_connect() will return an error
 */
#define PSA_SID_STORAGE 0x2U

/**
 * @brief C-Constants used to declare a SID.
 *        A SID is a unique service identifier used to identify the RoT
 *        service to communicate with.
 *        The implementation is arbitrarily defined as:
 *              - it must be unique
 *              - its type must be uint32_t
 *              - a SID must be associated to an AUID statically in the Client library
 *              - it must not changed between upgrades
 *
 *        The PSA_SID_CRYPTO is the SID number that refers to the Crypto RoT Service
 *
 * @usage This constant is only for the Client API: psa_connect().
 *        If the Client library does not statically associate a SID with an AUID
 *        the psa_connect() will return an error
 */
#define PSA_SID_CRYPTO 0x3U

/**
 * @brief C-Constants used to declare a SID.
 *        A SID is a unique service identifier used to identify the RoT
 *        service to communicate with.
 *        The implementation is arbitrarily defined as:
 *              - it must be unique
 *              - its type must be uint32_t
 *              - a SID must be associated to an AUID statically in the Client library
 *              - it must not changed between upgrades
 *
 *        The PSA_SID_FW_UPG is the SID number that refers to the Firmware
 *        Upgrade RoT Service.
 *
 * @usage This constant is only for the Client API: psa_connect().
 *        If the Client library does not statically associate a SID with an AUID
 *        the psa_connect() will return an error
 */
#define PSA_SID_FW_UPG 0x4U

/**
 * @brief C-Constants used to declare a SID.
 *        A SID is a unique service identifier used to identify the RoT
 *        service to communicate with.
 *        The implementation is arbitrarily defined as:
 *              - it must be unique
 *              - its type must be uint32_t
 *              - a SID must be associated to an AUID statically in the Client library
 *              - it must not changed between upgrades
 *
 *        The PSA_SID_ATTESTATION is the SID number that refers to the
 *        Attestation RoT Service.
 *
 * @usage This constant is only for the Client API: psa_connect().
 *        If the Client library does not statically associate a SID with an AUID
 *        the psa_connect() will return an error
 */
#define PSA_SID_ATTESTATION 0x5U


/* //////////////////////////////////////////////////////////////////////// */
/*                         C-CONSTANTS - PSA SIGNALS                        */
/* //////////////////////////////////////////////////////////////////////// */

/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x1 is PSA _Reserved_
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 *        This signal will return an error if used by psa_connect or psa_wait.
 */
#define PSA_SIGNAL_RESERVED1      0x00000001U
/**
 * @brief C-Constants used to declare a Signal value.
 *        The signal value 0x2 is PSA _Reserved_
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 *        This signal will return an error if used by psa_connect or psa_wait.
 */
#define PSA_SIGNAL_RESERVED2      0x00000002U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x4 is PSA _Reserved_
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 *        This signal will return an error if used by psa_connect or psa_wait.
 */
#define PSA_SIGNAL_RESERVED3      0x00000004U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x8 is for generating a PSA Doorbell.
 *        The PSA Doorbell does not request a specific services to a RoT Service
 *        it allows to ping a RoT Service and check if the RoT Service is still alive.
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 *        This signal will return an error if used by psa_connect or psa_wait.
 */
#define PSA_SIGNAL_DOORBELL       0x00000008U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x10 is for requesting a service to the Storage RoT Service
 *        The PSA Storage signal signals a request, the type of request is specified by
 *        the type field in psa_call() API.
 *        The type of message is PSA_IPC_CONNECT for psa_connect(),
 *        and PSA_IPC_DISCONNECT for psa_close()
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_SIGNAL_STORAGE            0x00000010U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x20 is for requesting a service to the Crypto RoT Service
 *        The PSA Crypto signal signals a request, the type of request is specified by
 *        the type field in psa_call() API.
 *        The type of message is PSA_IPC_CONNECT for psa_connect(),
 *        and PSA_IPC_DISCONNECT for psa_close()
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_SIGNAL_CRYPTO         0x00000020U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x80 is for requesting a service to the Firmware Upgrade RoT Service
 *        The PSA Firmware Upgrade signal signals a request, the type of request is specified by
 *        the type field in psa_call() API.
 *        The type of message is PSA_IPC_CONNECT for psa_connect(),
 *        and PSA_IPC_DISCONNECT for psa_close()
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_SIGNAL_FW_UPG         0x00000080U
/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x100 is for requesting a service to the Signal Attestation RoT Service
 *        The PSA Attestation signal signals a request, the type of request is specified by
 *        the type field in psa_call() API.
 *        The type of message is PSA_IPC_CONNECT for psa_connect(),
 *        and PSA_IPC_DISCONNECT for psa_close()
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_SIGNAL_ATTESTATION    0x00000100U

/**
 * @brief C-Constants used to declare a Signal value.
 *        A signal value must be a power of 2.
 *        The signal value 0x2000 is for requesting a service to the Skeleton RoT Service
 *        The PSA Skeleton signal signals a request, the type of request is specified by
 *        the type field in psa_call() API.
 *        The type of message is PSA_IPC_CONNECT for psa_connect(),
 *        and PSA_IPC_DISCONNECT for psa_close()
 *
 * @usage This constant is used for Client API and SecurePartition API
 *        and shall not be inconsistent between both.
 */
#define PSA_SIGNAL_SKELETON   0x2000U

/* //////////////////////////////////////////////////////////////////////// */
/*           C-CONSTANTS -  Internal trusted storage MESSAGE TYPES          */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief C-Constants used to declare a Type message.
 *        A type message is a int32_t value.
 *        The ITS set Private DATA is a specific request for the ITS RoT service
 *
 *        It allows to request to the RoT Service to store private data.
 *
 *        This is the message type used in psa_its_set()
 *
 * @usage This constant is used for ITS library and Storage RoT Service
 *        and shall not be inconsistent between both.
 */
#define PSA_TYPE_ITS_SET_PRIVATE_DATA            1001


/**
 * @brief C-Constants used to declare a Type message.
 *        A type message is a int32_t value.
 *        The ITS Get Private DATA is a specific request for the ITS RoT service
 *
 *        It allows to request to the RoT Service to retrieve private data from a storage identifier.
 *
 *        This is the message type used in psa_its_get()
 *
 * @usage This constant is used for ITS library and Storage RoT Service
 *        and shall not be inconsistent between both.
 */
#define PSA_TYPE_ITS_GET_PRIVATE_DATA            1002


/**
 * @brief C-Constants used to declare a Type message.
 *        A type message is a int32_t value.
 *        The ITS Remove Private DATA is a specific request for the ITS RoT service
 *
 *        It allows to request to the RoT Service to remove private data from a storage identifier.
 *
 *        This is the message type used in psa_its_remove()
 *
 * @usage This constant is used for ITS library and Storage RoT Service
 *        and shall not be inconsistent between both.
 */
#define PSA_TYPE_ITS_REMOVE_DATA                 1004


/**
 * @brief C-Constants used to declare a Type message.
 *        A type message is a int32_t value.
 *        The ITS Get Private DATA is a specific request for the ITS RoT service
 *
 *        It allows to request to the RoT Service to retrieve private data information from a storage identifier.
 *
 *        This is the message type used in psa_its_get_info()
 *
 * @usage This constant is used for ITS library and Storage RoT Service
 *        and shall not be inconsistent between both.
 */
#define PSA_TYPE_ITS_RETRIEVE_INFO               1003


/* //////////////////////////////////////////////////////////////////////// */
/*           C-CONSTANTS -  Initial attestation MESSAGE TYPES               */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief the value of the message type for the psa_initial_attestation_get_token API
 *
 * This value must be equal to the one defined in the IA RoT.
 */
#define PSA_TYPE_IA_GET_TOKEN           1001

/**
 * @brief the value of the message type for the psa_initial_attestation_get_token API
 *
 * This value must be equal to the one defined in the IA RoT.
 */
#define PSA_TYPE_IA_GET_TOKEN_SIZE      1002


/* //////////////////////////////////////////////////////////////////////// */
/*           C-CONSTANTS -  Firmware update MESSAGE TYPES                   */
/* //////////////////////////////////////////////////////////////////////// */
/**
 * @brief the value of the message type for the psa_fwu_write API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_WRITE               0x8


/**
 * @brief the value of the message type for the psa_fwu_install API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_INSTALL             0x10


/**
 * @brief the value of the message type for the psa_fwu_abort API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_ABORT               0x20


/**
 * @brief the value of the message type for the psa_fwu_query API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_QUERY                0x40


/**
 * @brief the value of the message type for the psa_fwu_request_reboot API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_REQUEST_REBOOT       0x80


/**
 * @brief the value of the message type for the psa_fwu_accept API
 *
 * This value must be equal to the one defined in the FWU RoT.
 */
#define PSA_TYPE_FWU_ACCEPT              0x100



/* //////////////////////////////////////////////////////////////////////// */
/*                          C-CONSTANTS -  IRQ                              */
/* //////////////////////////////////////////////////////////////////////// */


#define PSA_MAX_IRQ        12U
#define PSA_MASK_IRQ       0x03FFC000U

#define PSA_SIGNAL_IRQ1    0x00004000U

#define PSA_SIGNAL_IRQ2    0x00008000U

#define PSA_SIGNAL_IRQ3    0x00010000U

#define PSA_SIGNAL_IRQ4    0x00020000U

#define PSA_SIGNAL_IRQ5    0x00040000U

#define PSA_SIGNAL_IRQ6    0x00080000U

#define PSA_SIGNAL_IRQ7    0x00100000U

#define PSA_SIGNAL_IRQ8    0x00200000U

#define PSA_SIGNAL_IRQ9    0x00400000U

#define PSA_SIGNAL_IRQ10   0x00800000U

#define PSA_SIGNAL_IRQ11   0x01000000U

#define PSA_SIGNAL_IRQ12   0x02000000U



/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                      */
/* ######################################################################## */
/**
 * @brief  Initialize the shared buffer label inside the Client library
 *
 * This function sets the label of the shared buffer inside the Client
 *   library.
 *
 *   This is a mandatory initialization to perform before using
 *      psa_connect() / psa_call() / psa_close()
 *
 * An application or a PSA library that implements the Client API
 *  in order to communicate with a RoT Service must declare a shared buffer
 *  in the ukAPP descriptor file and give as parameter the associated label.
 *
 * This label will be used in psa_call() in order to map the shared buffer
 *  in the Window Map index 1.
 *
 * @note By using the Client library, the window map index 1 can no longer
 *  be used at the same time that a psa_call() is done.
 *
 * @note An action can be performed only on a Peripheral IRQ currently
 *  registered by the current ukProc.
 *
 * @implementation This function stores the label inside a private
 *  global variable and it will use it at each call of psa_call().
 *
 *
 * @return void
 */
void psa_init_label(uint16_t ab_label);


/**
 * @brief  Initialize the signal value in the Client library
 *
 * This function sets the Signal value that will be used in
 *  psa_connect() / psa_call() and psa_close().
 *
 * An application or a PSA library that implements the Client API
 *  in order to communicate with a RoT Service must call this API to
 *  indicate which signal will be used to request a RoT Service.
 *
 * The Signal value must be one of the hardcoded constants value found in client.h.
 * PSA_SIGNAL_XXXX
 *
 * @implementation This function stores the signal inside a private
 *  global variable and it will use it at each call of psa_call().
 *
 *
 * @return void
 */
void psa_init_signal(uint32_t signal);

/**
 * @brief  Get the verbosity level set in RoT Services
 *
 * @note
 * @param[out] (uint8_t *)level_log: to store the value of the log level
 *
 * @return (psa_status_t) status code returned by the API
 */
psa_status_t get_verbosity_level(uint8_t *level_log);


/**
 * @brief  Set the verbosity level for RoT Services
 *
 * @param[in] (uint8_t)level_log: the value to be set in the log level
 * It must be one of these value:
 *   - TFM_PARTITION_LOG_LEVEL_SILENCE  0
 *   - TFM_PARTITION_LOG_LEVEL_ERROR    1
 *   - TFM_PARTITION_LOG_LEVEL_INFO     2
 *   - TFM_PARTITION_LOG_LEVEL_DEBUG    3
 * @return (psa_status_t) status code returned by the API
 */
psa_status_t set_verbosity_level(uint8_t level_log);

/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#endif /* !defined(PSA_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */


