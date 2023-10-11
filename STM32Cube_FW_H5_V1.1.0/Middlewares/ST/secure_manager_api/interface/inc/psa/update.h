/***
 * Some part of this code is derived on BSD-3-Clause TFM/v1.5.0 files
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/**************************************************************************//**
 * @file          update.h
 * @brief         Public api for firmware upgrade
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup
 ******************************************************************************
* @details This header contains the FWU  public declarations used for
 *          interacting with the FWU APIs.
 *
 *          This file must be included by the ukapp that does use the FWU APIs
 *
 * @implementation This file only defines the common constants,types and APIs
 *                  of the firmware upgrade library.
 ******************************************************************************
 * @addtogroup    PSA_FWU
 * @{
 */


/* ######################################################################## */
/*                                  HEADER                                  */
/* ######################################################################## */
#ifndef PSA_UPDATE_H
#define PSA_UPDATE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "psa/error.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ######################################################################## */
/*                     MODULE PUBLIC API - C-GLOBAL DEFINES                 */
/* ######################################################################## */

/**
 * \brief PSA INITIAL ATTESTATION API version
 *
 * Initial attestation API version is: 0.7.0
 */
#define PSA_FWU_API_VERSION_MAJOR (0)
#define PSA_FWU_API_VERSION_MINOR (7)

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-GLOBAL ERROR                   */
/* ######################################################################## */


#define PSA_ERROR_CORRUPTION_DETECTED  ((psa_status_t)-151)
#define PSA_ERROR_DATA_INVALID         ((psa_status_t)-153)
#define PSA_ERROR_WRONG_DEVICE         ((psa_status_t)-155)
#define PSA_ERROR_ALREADY_INSTALLED    ((psa_status_t)-158)
#define PSA_ERROR_INSTALL_INTERRUPTED  ((psa_status_t)-159)
#define PSA_ERROR_FLASH_ABUSE          ((psa_status_t)-160)
#define PSA_ERROR_INSUFFICIENT_POWER   ((psa_status_t)-161)
#define PSA_ERROR_DECRYPTION_FAILURE   ((psa_status_t)-162)
#define PSA_ERROR_MISSING_MANIFEST     ((psa_status_t)-163)
#define PSA_ERROR_INVALID_IMAGE_HEADER ((psa_status_t)-127)

#define PSA_FWU_MAX_BLOCK_SIZE               1024
#define TFM_FWU_INVALID_IMAGE_ID             0

/* The maximum size of an image digest in bytes. This is dependent
 * on the hash algorithm used.
 */
#define PSA_FWU_MAX_DIGEST_SIZE              32U
#define TFM_IMAGE_INFO_INVALID_DIGEST        0xFF

/* The image ID macros. */
#define FWU_IMAGE_ID_SLOT_POSITION           0U

/* The area where the image is running. */
#define FWU_IMAGE_ID_SLOT_ACTIVE             0x01U

/* The area to stage the image. */
#define FWU_IMAGE_ID_SLOT_STAGE              0x02U
#define FWU_IMAGE_ID_SLOT_MASK               0x00FFU

#define FWU_IMAGE_ID_TYPE_MASK               0xFF00U

#define PSA_FWU_SLOT_ID_ACTIVE               0x1
#define PSA_FWU_SLOT_ID_DL                   0x2

#define PSA_FWU_TYPE_ID_SECURE               0x00U
#define PSA_FWU_TYPE_ID_NONSECURE            0x01U
#define PSA_FWU_TYPE_ID_MODULE_0             0x02U
#define PSA_FWU_TYPE_ID_MODULE_1             0x03U
#define PSA_FWU_TYPE_ID_MODULE_2             0x04U
#define PSA_FWU_TYPE_ID_MODULE_3             0x05U
#define PSA_FWU_TYPE_ID_MODULE_4             0x06U
#define PSA_FWU_TYPE_ID_MODULE_5             0x07U
#define PSA_FWU_TYPE_ID_MODULE_6             0x08U
#define PSA_FWU_TYPE_ID_MODULE_7             0x09U
#define PSA_FWU_TYPE_ID_BL                   0x1FU

#define FWU_IMAGE_ID_TYPE_POSITION           8U
#define FWU_IMAGE_ID_SPECIFIC_ID_POSITION    16U

#define FWU_CALCULATE_IMAGE_ID(slot, type, specific_id)             \
                             ((slot & FWU_IMAGE_ID_SLOT_MASK) |     \
                             (type << FWU_IMAGE_ID_TYPE_POSITION) | \
                             (specific_id << FWU_IMAGE_ID_SPECIFIC_ID_POSITION))

#define FWU_IMAGE_ID_GET_TYPE(image_id) ((image_id & FWU_IMAGE_ID_TYPE_MASK) >> FWU_IMAGE_ID_TYPE_POSITION)
#define FWU_IMAGE_ID_GET_SLOT(image_id) (image_id & FWU_IMAGE_ID_SLOT_MASK)

/* Image state macros. */
#define PSA_IMAGE_UNDEFINED            0U
#define PSA_IMAGE_CANDIDATE            1U
#define PSA_IMAGE_INSTALLED            2U
#define PSA_IMAGE_REJECTED             3U
#define PSA_IMAGE_PENDING_INSTALL      4U
#define PSA_IMAGE_REBOOT_NEEDED        5U


/* unsupported defines but required by PSA specification */
#define PSA_IMAGE_FLAG_VOLATILE_STAGING (0x00000001)
#define PSA_IMAGE_FLAG_ENCRYPTION       (0x00000002)
typedef uint32_t psa_fwu_iterator_t;

/* ######################################################################## */
/*                     MODULE PUBLIC API - C-GLOBAL TYPES                   */
/* ######################################################################## */
/**
 * @brief declaration of psa_image_id_t
 *
 * A psa_image_id_t is a unsigned 32 bit integer.
 *
 * The client application must use the psa_image_id in order to indicate the
 * FWU RoT on which image the API must perform.
 * The RoT service is based on TFM, therefore the bits of the psa_image_id_t is used as follow
 *
 * ----------------------------------------------------------------
 * | 16 MSB = Unused   | 8bits = Type ID     |  8 LSB = Slot ID   |
 * ----------------------------------------------------------------
 * @usage check @PSA_FWU_SLOT_ID_DL and @PSA_FWU_SLOT_ID_ACTIVE for more details
 * @usage check @PSA_FWU_TYPE_ID_SECURE, @PSA_FWU_TYPE_ID_NONSECURE, @PSA_FWU_TYPE_ID_MODULE0,
 * @PSA_FWU_TYPE_ID_MODULE1, @PSA_FWU_TYPE_ID_MODULE2, @PSA_FWU_TYPE_ID_MODULE3,
 * @PSA_FWU_TYPE_ID_MODULE4, @PSA_FWU_TYPE_ID_MODULE5, @PSA_FWU_TYPE_ID_MODULE6
 * @PSA_FWU_TYPE_ID_MODULE7 for more details
 */
typedef uint32_t psa_image_id_t;

typedef struct tfm_image_version_s {
    uint8_t iv_major;
    uint8_t iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
} psa_image_version_t;

typedef struct psa_hash_s {
    uint8_t value[PSA_FWU_MAX_DIGEST_SIZE];
} psa_hash_t;

typedef struct psa_uuid_t {
uint32_t uuid[4];
} psa_uuid_t;

typedef struct psa_staging_info_t {
uint8_t flags;
uint8_t metadata_format;
size_t max_size;
psa_hash_t key_id;
} psa_staging_info_t;

typedef struct tfm_image_info_s {
    psa_image_id_t image_id;
    psa_uuid_t vendor_id;
    psa_uuid_t class_id;
    psa_image_version_t version;
    uint8_t state;
    psa_staging_info_t staging;
    uint32_t error;
    uint8_t digest[PSA_FWU_MAX_DIGEST_SIZE];
} psa_image_info_t;

typedef struct tlv_type {
    uint16_t type;
    uint16_t length;
    uint8_t *value;
} tlv_type_t;

typedef struct tlv_bl2_header_area {
    uint16_t magic;
    uint16_t length;
} tlv_header_area_t;

typedef struct tfm_fwu_ctx_s {
    psa_image_id_t image_id;
    uint8_t image_state;
    bool in_use;
} tfm_fwu_ctx_t;



/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS                      */
/* ######################################################################## */
/**
 * \brief Writes an image to its staging area.
 *
 * Writes the image data 'block' with length 'block_size' to its staging area.
 * If the image size is less than or equal to PSA_FWU_MAX_BLOCK_SIZE, the
 * caller can send the entire image in one call.
 * If the image size is greater than PSA_FWU_MAX_BLOCK_SIZE, the caller must
 * send parts of the image by calling this API multiple times with different
 * data blocks.
 *
 * \param[in] image_id        The identifier of the image
 * \param[in] block_offset    The offset of the block being passed into block,
 *                            in bytes
 * \param[in] block           A buffer containing a block of image data. This
 *                            might be a complete image or a subset.
 * \param[in] block_size      Size of block. The size must not be greater than
 *                            PSA_FWU_MAX_BLOCK_SIZE.
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                     The data in block has been
 *                                         successfully stored.
 * \retval PSA_ERROR_INVALID_ARGUMENT      One of the following error
 *                                         conditions occurred:
 *                                         The parameter size is greater than
 *                                         PSA_FWU_MAX_BLOCK_SIZE;
 *                                         The parameter size is 0;
 *                                         The combination of offset and size
 *                                         is out of bounds.
 *
 * \retval PSA_ERROR_INSUFFICIENT_MEMORY   There is not enough memory to
 *                                         process the update
 * \retval PSA_ERROR_INSUFFICIENT_STORAGE  There is not enough storage to
 *                                         process the update
 * \retval PSA_ERROR_GENERAL_ERROR         A fatal error occurred
 * \retval PSA_ERROR_CURRENTLY_INSTALLING        The image is currently locked for
 *                                         writing.
 */
psa_status_t psa_fwu_write(psa_image_id_t image_id,
                           size_t block_offset,
                           const void *block,
                           size_t block_size);


/**
 * \brief Starts the installation of an image.
 *
 * The authenticity and integrity of the image is checked during installation.
 * If a reboot is required to complete installation then the implementation
 * can choose to defer the authenticity checks to that point.
 *
 * \param[in] image_id            The identifier of the image to install
 * \param[out] dependency_uuid    If PSA_ERROR_DEPENDENCY_NEEDED is returned,
 *                                this parameter is filled with dependency
 *                                information
 * \param[out] dependency_version If PSA_ERROR_DEPENDENCY_NEEDED is returned,
 *                                this parameter is filled with the minimum
 *                                required version for the dependency
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                     The image was successfully
 *                                         installed. The platform does not
 *                                         require a reboot.
 * \retval PSA_SUCCESS_REBOOT              A system reboot is needed to finish
 *                                         installation.
 * \retval PSA_ERROR_INVALID_ARGUMENT      Bad input parameter
 * \retval PSA_ERROR_INVALID_SIGNATURE     The signature is incorrect
 * \retval PSA_ERROR_GENERAL_ERROR         A fatal error occurred
 * \retval PSA_ERROR_DEPENDENCY_NEEDED     A different image requires
 *                                         installation first
 * \retval PSA_ERROR_STORAGE_FAILURE       Some persistent storage could not be
 *                                         read or written by the
 *                                         implementation
 */
psa_status_t psa_fwu_install(psa_image_id_t image_id,
                             psa_image_id_t *dependency_uuid,
                             psa_image_version_t *dependency_version);

/**
 * \brief Aborts an ongoing installation and erases the staging area of the
 *        image.
 *
 * \param[in] image_id      The identifier of the image to abort installation
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                    Installation of the provided image_id
 *                                        has been aborted
 * \retval PSA_ERROR_INVALID_ARGUMENT     No image with the provided image_id
 *                                        is currently being installed
 * \retval PSA_ERROR_NOT_PERMITTED        The caller is not authorized to
 *                                        abort an installation
 */
psa_status_t psa_fwu_abort(psa_image_id_t image_id);

/**
 * \brief Returns information for an image of a particular image_id.
 *
 * \param[in] image_id         The image_id of the image to query
 *
 * \param[out] info            Output parameter for image information
 *                             related to the image_id
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                     Image information has been returned
 * \retval PSA_ERROR_NOT_PERMITTED         The caller is not authorized to
 *                                         access platform version information
 */
psa_status_t psa_fwu_query(psa_image_id_t image_id,
                           psa_image_info_t *info);

/**
 * \brief Requests the platform to reboot. On success, the platform initiates
 *        a reboot, and might not return to the caller.
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                   The platform will reboot soon
 * \retval PSA_ERROR_NOT_PERMITTED       The caller is not authorized to
 *                                       reboot the platform
 */
psa_status_t psa_fwu_request_reboot(void);

/**
 * \brief Indicates to the implementation that the upgrade was successful.
 *
 * \param[in] image_id         The image_id of the image to query
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                  The image and its dependencies have
 *                                      transitioned into a PSA_IMAGE_INSTALLED
 *                                      state
 * \retval PSA_ERROR_NOT_SUPPORTED      The implementation does not support a
 *                                      PSA_IMAGE_PENDING_INSTALL state
 * \retval PSA_ERROR_NOT_PERMITTED      The caller is not permitted to make
 *                                      this call
 */
psa_status_t psa_fwu_accept(psa_image_id_t image_id);

/**
 * \brief Stores a manifest object and associates it with a particular image ID.
 *
 * \param[in] image_id            The identifier of the image
 *
 * \param[in] manifest            A pointer to a buffer containing a manifest
 *                                object
 *
 * \param[in] manifest_size       The size of the manifest parameter
 *
 * \param[in] manifest_dependency Output parameter containing the hash of a
 *                                required manifest when
 *                                PSA_ERROR_DEPENDENCY_NEEDED is returned
 *
 * \return A status indicating the success/failure of the operation
 *
 * \retval PSA_SUCCESS                     The manifest is persisted
 * \retval PSA_ERROR_NOT_PERMITTED         The manifest is too old to be
 *                                         installed
 * \retval PSA_ERROR_WRONG_DEVICE          The manifest is not intended for this
 *                                         device
 * \retval PSA_ERROR_INVALID_SIGNATURE     The manifest signature is not valid
 * \retval PSA_ERROR_DEPENDENCY_NEEDED     A different manifest is needed
 * \retval PSA_ERROR_INVALID_ARGUMENT      Parameter size is 0 or a pointer
 *                                         parameter is NULL
 * \retval PSA_ERROR_COMMUNICATION_FAILURE The system could not communicate with
 *                                         the installer
 * \retval PSA_ERROR_NOT_SUPPORTED         This function is not implemented
 * \retval PSA_ERROR_CURRENTLY_INSTALLING  An existing manifest for image ID is
 *                                         currently being installed and is
 *                                         locked from writing
 * \retval PSA_ERROR_GENERIC_ERROR         A fatal error occurred
 */
psa_status_t psa_fwu_set_manifest(psa_image_id_t image_id,
                                  const void *manifest,
                                  size_t manifest_size,
                                  psa_hash_t *manifest_dependency);



/* ######################################################################## */
/*                     MODULE PUBLIC API - C-FUNCTIONS not supported        */
/* ######################################################################## */
/**
 * Unsupported list of API
 * but required to be exposed according to PSA API specification
 */

psa_status_t psa_fwu_request_rollback(uint32_t error);
void         psa_fwu_get_image_id_iterator(psa_fwu_iterator_t *iterator);
bool         psa_fwu_get_image_id_next(psa_fwu_iterator_t *iterator);
bool         psa_fwu_get_image_id_valid(psa_fwu_iterator_t *iterator);
psa_status_t psa_fwu_get_image_id(psa_fwu_iterator_t *iterator, psa_image_id_t *image_id);


#ifdef __cplusplus
}
#endif
#endif /* PSA_UPDATE_H */
/** @} */
