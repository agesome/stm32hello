/**
  ******************************************************************************
  * @file    crypto_tests_config.h
  * @author  MCD Application Team
  * @brief   Crypto configuration file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CRYPTO_TESTS_CONFIG_H
#define CRYPTO_TESTS_CONFIG_H


#define TEST_HASH
#define TFM_CRYPTO_TEST_ALG_SHA_512

#define TEST_MAC
#define TFM_CRYPTO_TEST_ALG_CMAC
#define TFM_CRYPTO_TEST_ALG_CCM
#define TFM_CRYPTO_TEST_ALG_GCM

#define TEST_ECC

#define TFM_CRYPTO_TEST_ASYM_ENCRYPT
#define TEST_RSA

#define TEST_CIPHER
#define TEST_DES
#define TFM_CRYPTO_TEST_ALG_CBC
#define TFM_CRYPTO_TEST_ALG_CFB
#define TFM_CRYPTO_TEST_ALG_CTR
#define TFM_CRYPTO_TEST_ALG_OFB
#define TFM_CRYPTO_TEST_ALG_ECB
#define TEST_CIPHER_PADDED_MODES


#endif /* CRYPTO_TESTS_CONFIG_H */
