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
 * @file          check_parameters.c
 * @brief         File that implements the CRYPTO functionality
 * @author        Gilles Piret <gilles.piret@provenrun.com>
 * @maintainer    Gilles Piret <gilles.piret@provenrun.com>
 * @ingroup       CRYPTO
 ******************************************************************************
 *
 * Implements two functions:
 * - randomize_output_buffer
 * - randomize_buffer
 * Other functions are present that will be deprecated soon.
 */

//*************** Includes
#include <stdint.h>
#include <stdlib.h>
#include "psa/crypto.h"

//*************** Defines
#define CRYPTO_OK        0x55

#define CRYPTO_NOK       PSA_ERROR_NOT_PERMITTED
#define CRYPTO_SECURITY  PSA_ERROR_CORRUPTION_DETECTED

//*************** Prototypes
uint8_t randomize_output_buffer(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);
// Was previously:
uint8_t check_buffer_overlap_and_randomize(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);


uint8_t randomize_buffer(uint8_t*buffer, size_t buffer_size);
// Was previously:
uint8_t check_and_randomize_buffer(uint8_t*buffer, size_t buffer_size);

// Deprecated:
uint8_t check_buffer_overlap(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);

// Internal subfunction:
uint8_t check_buffer_overlap_internal(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size);

extern psa_status_t RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length);

//****************************************************************************************************
//******     randomize_output_buffer
//******----------------------------------------------------------------------------------------------
//******     DESCRIPTION
//******        Checks if input and output buffer overlap or not.
//******        If they do not, randomize output buffer.
//******
//******     RETURN STATUS
//******        - CRYPTO_OK        if all is fine
//******        - CRYPTO_SECURITY  in case of problem in random generation
//****************************************************************************************************

uint8_t randomize_output_buffer(uint8_t * input, size_t input_size,
                                uint8_t * output, size_t output_size)
{
	uint8_t status;

	status= check_buffer_overlap_internal(input, input_size, output, output_size);
	if (status==CRYPTO_OK)     // If no overlap, we can randomize output buffer
	{
        return(randomize_buffer(output, output_size));
	}
	return(CRYPTO_OK);
}

uint8_t check_buffer_overlap_and_randomize(uint8_t * input, size_t input_size,
                                           uint8_t * output, size_t output_size)
{
	return(randomize_output_buffer(input, input_size, output, output_size));
}

//****************************************************************************************************
//******     check_randomize_buffer
//****************************************************************************************************

uint8_t randomize_buffer(uint8_t*buffer, size_t buffer_size)
{
	uint8_t status;
	

// Randomize
#ifdef DukappCONFIG_NAMESPACE
    size_t out_size_check;
    status= RNG_GetBytes(buffer, buffer_size, &out_size_check);
    if ((buffer_size==out_size_check) && (status==0))
    {
        return(status+CRYPTO_OK);
    }
#else
    status= psa_generate_random(buffer, buffer_size);
    if (status==0)
    {
      return(status+CRYPTO_OK);
    }
#endif  // DukappCONFIG_NAMESPACE
    return (uint8_t)CRYPTO_SECURITY;
}

uint8_t check_and_randomize_buffer(uint8_t*buffer, size_t buffer_size)
{
	return(randomize_buffer(buffer, buffer_size));
}

//****************************************************************************************************
//******     check_buffer_overlap_internal
//******----------------------------------------------------------------------------------------------
//******     DESCRIPTION
//******        This function tests whether two buffers a,b overlap.
//******     RETURN STATUS
//******        - CRYPTO_OK        if no overlap
//******        - CRYPTO_NOK       in case of overlap
//******        - CRYPTO_SECURITY  in case of fault injection.
//****************************************************************************************************

uint8_t check_buffer_overlap_internal(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size)
{
    uint32_t in_l, in_h,out_l,out_h;

//***************** Cast addresses to 32 bits
    in_l  = (uint32_t) input;
    in_h  = in_l + (uint32_t) input_size;
    out_l = (uint32_t) output;
    out_h = out_l + (uint32_t) output_size;

//***************** Check overlap
    if (((out_l <  in_l)  || (out_l >= in_h))   &&
        ((out_h <= in_l)  || (out_h >= in_h))   &&
        ((in_l  <  out_l) || (in_l  >= out_h))  &&
        ((in_h  <= out_l) || (in_h  >= out_h)))
    {
        return(CRYPTO_OK);
    }

    return((uint8_t)CRYPTO_NOK);
}

//****************************************************************************************************
//******     check_buffer_overlap
//******----------------------------------------------------------------------------------------------
//******     DESCRIPTION
//******        This function check buffer sizes.
//******        Its name and useless parameters are there for retro-compatibility reasons.
//******     RETURN STATUS
//******        - CRYPTO_OK        if all is fine.
//******        - CRYPTO_NOK       if at least one verification failed.
//******        - CRYPTO_SECURITY  in case of fault injection.
//****************************************************************************************************

uint8_t check_buffer_overlap(uint8_t * input, size_t input_size, uint8_t * output, size_t output_size)
{
    (void) input;
    (void) input_size;
    (void) output;
    (void) output_size;

    return(CRYPTO_OK);   // Deprecated
}
