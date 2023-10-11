/**
 * @copyright
 * COPYRIGHT NOTICE:
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 * **************************************************************************
 * @file          helper_function.h
 * @brief         File that implements the CRYPTO functionality
 * @author        ProvenRun
 * @maintainer    ProvenRun
 * @ingroup       CRYPTO
 ******************************************************************************
 *
 */

#ifndef HELPER_FUNCTION_H
#define HELPER_FUNCTION_H

#include "psa/error.h"

uint8_t check_buffer_overlap(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);

uint8_t check_buffer_overlap_and_randomize(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);

uint8_t check_and_randomize_buffer(uint8_t*buffer, size_t buffer_size);

uint32_t check_scalar(int s, int min, int max);

#endif
