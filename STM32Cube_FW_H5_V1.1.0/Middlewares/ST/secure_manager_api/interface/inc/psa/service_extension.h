/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 */
/**************************************************************************//**
 * @file          service_extension.h
 * @brief         SERVICE extension library - Public API file
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       service_extension
 ******************************************************************************
 * @details This header contains the public declaration of Service extension of the PSA Secure partition API
 *

 ******************************************************************************
 * @addtogroup    service_extension
 * @{
 */

/* ######################################################################## */
/*                                  HEADER                                  */
/* ######################################################################## */
/*__________________________________________________________________________*/
/* Verify that this include file has not been already processed. */
#if !defined(SERVICE_EXT_H)

/* Define that this include file has been processed (single inclusion). */
#define  SERVICE_EXT_H

/* Define that we are inside this file (definition is undone at its end). */
#define  SERVICE_EXT_H_INSIDE

/*__________________________________________________________________________*/
/* Source all the include files needed by the Public API of this code
 *  module.*/

/* Source the uKernel API. */
#include "psa/error.h"


/**
 * @brief C-Variable that allows to store the log level value.
 * The Secure Partition log levels retrieve from a
 * communication with the PSA Client Api.
 */
extern uint8_t sec_part_rot_verbosity_level;


/**
 * \brief Register and enable a Peripheral IRQ to the current
 *
 * \param[in] pirq_mcu_idx_i        The MCU Index of the Peripheral IRQ to be enabled by the current ukProc.
 * \param[in] signal_id_i           The signal IRQ (PSA_SIGNAL_IRQxx) associated to Peripheral IRQ o be enabled by the current ukProc.
 *
 * \retval PSA_SUCCESS                Success.
 * \retval PSA_ERROR_ALREADY_EXISTS   The pirq_mcu_idx_i is already registered by the ukProc.
 * \retval PSA_ERROR_ALREADY_EXISTS   The pirq_reg_id__i is already registered by the ukProc.
 * \retval PSA_ERROR_INVALID_ARGUMENT The pirq_mcu_idx_i is invalid.
 * \retval PSA_ERROR_INVALID_ARGUMENT The pirq_reg_id__i is invalid.
 * \retval PSA_ERROR_NOT_SUPPORTED    The array tab_irq is already full.
 * \retval PSA_ERROR_PROGRAMMER_ERROR An unspecified internal error has occurred.
 */
psa_status_t uk_enable_irq (TukPIRQ_MCU_IDX pirq_mcu_idx_i , uint32_t signal_id_i);

/**
 * \brief Disable and unregister a Peripheral IRQ to the current
 *
 * \param[in] signal_id_i           The signal IRQ (PSA_SIGNAL_IRQxx) associated to Peripheral IRQ o be disabled by the current ukProc.
 *
 * \retval PSA_SUCCESS                Success.
 * \retval PSA_ERROR_INVALID_ARGUMENT The signal_id_i is invalid.
 * \retval PSA_ERROR_PROGRAMMER_ERROR An unspecified internal error has occurred.
 */
psa_status_t uk_disable_irq (uint32_t signal_id_i);


#ifdef EXT_FOR_ITS_ROT
/**
 * @brief This function  is not part of the PSA suite APIs
 *
 * This API allows a RoT to retrieve the block bundle id associated to a psa handle.
 *
 *
 *
 *
 * @return psa_status_t
 * @retval PSA_SUCCESS the block_bundle_id is properly found and updated
 * @retval PSA_ERROR_GENERIC_ERROR is returned when any error is found
 */
psa_status_t secpart_get_block_bundle_id(psa_handle_t msg_handle, uint32_t *block_bundle_id);

/**
 * @brief This function  is not part of the PSA suite APIs
 *
 * This API allows a RoT to retrieve the block bundle id associated to a psa handle.
 *
 *
 *
 *
 * @return psa_status_t
 * @retval PSA_SUCCESS the block_bundle_id is properly found and updated
 * @retval PSA_ERROR_GENERIC_ERROR is returned when any error is found
 */
psa_status_t secpart_update_size_in(psa_handle_t msg_handle, uint8_t in_index, uint32_t num_bytes);

/**
 * @brief This function  is not part of the PSA suite APIs
 *
 * This API allows a RoT to check if the handle is coming from the nsworld or not
 *
 *
 *
 *
 * @return psa_status_t
 * @retval PSA_SUCCESS the block_bundle_id
 * @retval PSA_ERROR_GENERIC_ERROR is returned when any error is found
 */
psa_status_t secpart_is_handle_from_nsworld(psa_handle_t msg_handle, uint8_t *is_nsworld, TukADDRESSBLOCK *nsea);

#endif
/* ######################################################################## */
/*                                  FOOTER                                  */
/* ######################################################################## */
#undef SERVICE_EXT_H_INSIDE
#endif /* !defined(PSA_SECPART_EXT_H) */
/** @} */
/* ------------------------------End-Of-File------------------------------- */

