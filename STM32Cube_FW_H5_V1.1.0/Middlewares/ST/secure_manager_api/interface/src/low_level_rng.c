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
 * @file          our_low_level_rng.c
 * @brief         File that implements the CRYPTO functionality
 * @author        Gilles Piret <gilles.piret@provenrun.com>
 * @maintainer    Gilles Piret <gilles.piret@provenrun.com>
 * @ingroup       CRYPTO
 ******************************************************************************
 *
 *         Low Level Interface module to obtain random from kernel.
 *         This file provides mbed-crypto random generataor.
 *         Mainly a wrapper.
 *
 */
#include "psa/error.h"
#include <stddef.h>
#ifdef DukappCONFIG_NAMESPACE
#ifndef __IARCC__
#include "uk/include/uk.h"
#else
#include "uk.h"
#endif
#endif
void RNG_Init(void);
psa_status_t RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length);

void RNG_Init(void)

{
   return;          // Initialization is handled by kernel
}


psa_status_t RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length)
{
#ifdef DukappCONFIG_NAMESPACE
#define RNG_ID DukRNG_ID_PRNG
uint8_t try = 0;
#else
#define RNG_ID  0
#endif
  uint8_t ret = 0;
  *output_length = 0;

  if (length==0)
  {
      return(PSA_SUCCESS);
  }

#ifdef DukappCONFIG_NAMESPACE
  while ((*output_length < length) && (ret == 0))
  {
    if (ukRandomGetBytes(RNG_ID, 4) != DukSTATUS_INFO_OK)
    {
      // retry when random numbers are not immediately available
      if (try < 3)
      {
        try++;
      }
      else
      {
        ret = -1;
      }
    }
    else
    {
      for (uint8_t i = 0; (i < 4) && (*output_length < length) ; i++)
      {
        *output++ = GVukappUKSVCOutput[i];
        *output_length += 1;
        GVukappUKSVCOutput[i] = 0;
      }
    }
  }
#else
  while ((*output_length < length) && (ret == 0))
  {
      for (uint8_t i = 0; (i < 4) && (*output_length < length) ; i++)
      {
        *output++ = 0xFF;
        *output_length += 1;
      }
  }
#endif
  if (ret==0)
  {
     return(ret+PSA_SUCCESS);
  }
  *output_length = 0;
  return(PSA_ERROR_HARDWARE_FAILURE);
}
