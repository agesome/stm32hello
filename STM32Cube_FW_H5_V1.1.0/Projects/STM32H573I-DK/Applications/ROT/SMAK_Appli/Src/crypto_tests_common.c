/*
 * Copyright (c) 2019-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "crypto_tests_common.h"
#include "crypto_tests_config.h"
#include "psa/error.h"

#define PASS_STRING "TEST PASSED"

#define CIPHER_TEST_KEY_ID (0x1)

#ifdef TEST_CIPHER_PADDED_MODES
void psa_cipher_padded_modes_test(const psa_key_type_t key_type,
                                  const psa_algorithm_t alg,
                                  uint8_t len,
                                  struct test_result_t *ret)
{
  psa_cipher_operation_t handle = psa_cipher_operation_init();
  psa_cipher_operation_t handle_dec = psa_cipher_operation_init();
  psa_status_t status;
  psa_key_handle_t key_handle;
  const uint8_t data[] = "THIS IS MY KEY1";
  const size_t iv_length = PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type);
  const uint8_t iv[] = "012345678901234";
  const uint8_t plain_text[PLAIN_DATA_SIZE_PAD_TEST] =
    "Little text, full!!";
  uint8_t decrypted_data[ENC_DEC_BUFFER_SIZE_PAD_TEST] = {0};
  size_t output_length = 0, total_output_length = 0;
  uint8_t encrypted_data[ENC_DEC_BUFFER_SIZE_PAD_TEST] = {0};
  uint32_t comp_result;
  psa_key_attributes_t key_attributes = psa_key_attributes_init();
  psa_key_usage_t usage = (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
  bool bAbortDecryption = false;
  ret->info_msg = "";

  if (iv_length != sizeof(iv))
  {
    /* Whenever this condition is hit, it's likely the test requires
     * refactoring to remove any hardcoded behaviour
     */
    TEST_FAIL("Hardcoded IV does not match cipher block length");
    return;
  }

  if (len > sizeof(plain_text))
  {
    TEST_FAIL("Requested input length is greater than supported");
    return;
  }

  ret->val = TEST_PASSED;

  /* Setup the key policy */
  psa_set_key_usage_flags(&key_attributes, usage);
  psa_set_key_algorithm(&key_attributes, alg);
  psa_set_key_type(&key_attributes, key_type);

  psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);

  /* Import a key */
  status = psa_import_key(&key_attributes, data, sizeof(data), &key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing a key");
    TEST_STATUS(status);
    return;
  }

  status = psa_get_key_attributes(key_handle, &key_attributes);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error getting key metadata");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (psa_get_key_bits(&key_attributes) != (uint32_t)BIT_SIZE_TEST_KEY)
  {
    TEST_FAIL("The number of key bits is different from expected");
    goto destroy_key;
  }

  if (psa_get_key_type(&key_attributes) != key_type)
  {
    TEST_FAIL("The type of the key is different from expected");
    goto destroy_key;
  }

  /* Setup the encryption object */
  status = psa_cipher_encrypt_setup(&handle, key_handle, alg);
  if (status != PSA_SUCCESS)
  {
    if (status == PSA_ERROR_NOT_SUPPORTED)
    {
      TEST_FAIL("Algorithm NOT SUPPORTED by the implementation");
    }
    else
    {
      TEST_FAIL("Error setting up cipher operation object");
    }
    TEST_STATUS(status);
    goto destroy_key;
  }

  /* Set the IV */
  status = psa_cipher_set_iv(&handle, iv, iv_length);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error setting the IV on the cipher operation object");
    TEST_STATUS(status);
    goto abort;
  }

  /* Encrypt one chunk of information */
  if (len < BYTE_SIZE_CHUNK)
  {
    status = psa_cipher_update(&handle, plain_text,
                               len,
                               encrypted_data,
                               sizeof(encrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* When encrypting less than a block, the output is produced only
     * when performing the following finish operation
     */
    if (output_length != 0U)
    {
      TEST_FAIL("Expected encrypted length is different from expected");
      goto abort;
    }

    status = psa_cipher_finish(&handle, encrypted_data,
                               sizeof(encrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error finalising the cipher operation");
      goto abort;
    }

  }
  else if (len < (2U * BYTE_SIZE_CHUNK))
  {
    status = psa_cipher_update(&handle, plain_text,
                               BYTE_SIZE_CHUNK,
                               encrypted_data,
                               sizeof(encrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* When encrypting one block, the output is produced right away */
    if (output_length != BYTE_SIZE_CHUNK)
    {
      TEST_FAIL("Expected encrypted length is different from expected");
      TEST_STATUS(status);
      goto abort;
    }

    total_output_length += output_length;
    status = psa_cipher_update(&handle, &plain_text[BYTE_SIZE_CHUNK],
                               (uint32_t)len % BYTE_SIZE_CHUNK,
                               &encrypted_data[total_output_length],
                               sizeof(encrypted_data) - total_output_length,
                               &output_length);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* When encrypting less than a block, the output is zero */
    if (output_length != 0U)
    {
      TEST_FAIL("Expected encrypted length is different from expected");
      goto abort;
    }

    /* The output is then produced only when calling finish if the previous
     * update did not produce any output - We need to take padding into
     * account
     */
    total_output_length += output_length;
    status = psa_cipher_finish(&handle, &encrypted_data[total_output_length],
                               sizeof(encrypted_data) - total_output_length,
                               &output_length);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    total_output_length += output_length;
  }

  /* Setup the decryption object */
  status = psa_cipher_decrypt_setup(&handle_dec, key_handle, alg);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error setting up cipher operation object");
    TEST_STATUS(status);
    goto destroy_key;
  }

  /* From now on, in case of failure we want to abort the decryption op */
  bAbortDecryption = true;

  /* Set the IV for decryption */
  status = psa_cipher_set_iv(&handle_dec, iv, iv_length);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error setting the IV for decryption");
    TEST_STATUS(status);
    goto abort;
  }

  /* Reset total output length */
  total_output_length = 0;
  if (len < BYTE_SIZE_CHUNK)
  {
    status = psa_cipher_update(&handle_dec,
                               encrypted_data,
                               BYTE_SIZE_CHUNK,
                               decrypted_data,
                               sizeof(decrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error decrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* Doesn't produce output on the first cipher update */
    if (output_length != 0U)
    {
      TEST_FAIL("Expected decrypted length is different from expected");
      goto abort;
    }

    status = psa_cipher_finish(&handle_dec, decrypted_data,
                               sizeof(decrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error finalising the cipher operation");
      TEST_STATUS(status);
      goto abort;
    }

    if (output_length != len)
    {
      TEST_FAIL("Expected decrypted length is different from expected");
      goto destroy_key;
    }

  }
  else if (len < (2U * BYTE_SIZE_CHUNK))
  {
    status = psa_cipher_update(&handle_dec, encrypted_data,
                               BYTE_SIZE_CHUNK,
                               decrypted_data,
                               sizeof(decrypted_data),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* Doesn't produce output on the first cipher update */
    if (output_length != 0U)
    {
      TEST_FAIL("Expected decrypted length is different from expected");
      goto abort;
    }

    total_output_length += output_length;
    status = psa_cipher_update(&handle_dec,
                               &encrypted_data[BYTE_SIZE_CHUNK],
                               BYTE_SIZE_CHUNK,
                               &decrypted_data[total_output_length],
                               sizeof(decrypted_data) - total_output_length,
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error decrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    /* We now get the output corresponding to the previous block */
    if (output_length != BYTE_SIZE_CHUNK)
    {
      TEST_FAIL("Expected decrypted length is different from expected");
      goto abort;
    }

    total_output_length += output_length;
    status = psa_cipher_finish(&handle_dec,
                               &decrypted_data[total_output_length],
                               sizeof(decrypted_data) - total_output_length,
                               &output_length);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error finalising the cipher operation");
      TEST_STATUS(status);
      goto abort;
    }

    total_output_length += output_length;
    if (total_output_length != len)
    {
      TEST_FAIL("Expected decrypted length is different from expected");
      goto destroy_key;
    }
  }

  /* Check that the plain text matches the decrypted data */
  comp_result = (uint32_t)memcmp(plain_text, decrypted_data, len);
  if (comp_result != 0U)
  {
    TEST_FAIL("Decrypted data doesn't match with plain text");
    goto destroy_key;
  }
  ret->info_msg = PASS_STRING;

  /* Go directly to destroy key from here */
  goto destroy_key;

abort:
  /* Abort the operation */
  status = bAbortDecryption ? psa_cipher_abort(&handle_dec) :
           psa_cipher_abort(&handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error aborting the operation");
    TEST_STATUS(status);
  }
destroy_key:
  /* Destroy the key */
  status = psa_destroy_key(key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error destroying a key");
    TEST_STATUS(status);
  }
}

#endif  /* TEST_CIPHER_PADDED_MODES */

#define LOG_INF(...) printf(__VA_ARGS__)
#define LOG_HEXDUMP_INF(a,b,c)      \
  do {                            \
    LOG_INF(c);            \
    for (int i=0; i<b; i++) {    \
      LOG_INF("0x%x, ", a[i]); \
    }                            \
    printf("\r\n");              \
  }                               \
  while (0)

#ifdef TEST_CIPHER
void psa_cipher_test(const psa_key_type_t key_type,
                     const psa_algorithm_t alg,
                     const uint8_t *key,
                     size_t key_bits,
                     struct test_result_t *ret)
{
  psa_cipher_operation_t handle = psa_cipher_operation_init();
  psa_cipher_operation_t handle_dec = psa_cipher_operation_init();
  psa_status_t status;
  psa_key_handle_t key_handle;
  size_t iv_length = PSA_CIPHER_IV_LENGTH(key_type, alg);
  uint8_t iv[16] = {0};
  size_t data_left;
  bool bIsLagging;
  size_t message_start;
  ret->info_msg = "";

  const uint8_t plain_text[PLAIN_DATA_SIZE] =
    "This is my plaintext to encrypt, 48 bytes long!";

  uint8_t encrypted_data_single_shot[ENC_DEC_BUFFER_SIZE];
  uint8_t decrypted_data[ENC_DEC_BUFFER_SIZE] = {0};
  size_t output_length = 0, total_output_length = 0;
  union
  {
    uint8_t encrypted_data[ENC_DEC_BUFFER_SIZE];
    uint8_t encrypted_data_pad[ENC_DEC_BUFFER_SIZE_PAD_MODES];
  } input = {0};
  uint32_t comp_result;
  psa_key_attributes_t key_attributes = psa_key_attributes_init();
  psa_key_usage_t usage = (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
  bool bAbortDecryption = false;

  if (iv_length > 16U)
  {
    TEST_FAIL("Unexpected IV length greater than 16 for this alg/key type");
    return;
  }

  ret->val = TEST_PASSED;

  /* Setup the key policy */
  psa_set_key_usage_flags(&key_attributes, usage);
  psa_set_key_algorithm(&key_attributes, alg);
  psa_set_key_type(&key_attributes, key_type);

  psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);

  /* Import a key */
  status = psa_import_key(&key_attributes, key, PSA_BITS_TO_BYTES(key_bits),
                          &key_handle);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing a key");
    TEST_STATUS(status);
    return;
  }

  status = psa_get_key_attributes(key_handle, &key_attributes);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error getting key metadata");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (psa_get_key_bits(&key_attributes) != key_bits)
  {
    TEST_FAIL("The number of key bits is different from expected");
    goto destroy_key;
  }

  if (psa_get_key_type(&key_attributes) != key_type)
  {
    TEST_FAIL("The type of the key is different from expected");
    goto destroy_key;
  }

  psa_reset_key_attributes(&key_attributes);

  /* Encrypt single part functions */

  /* Because key is volatile */
#undef  CIPHER_TEST_KEY_ID
#define CIPHER_TEST_KEY_ID key_handle
  status = psa_cipher_encrypt(CIPHER_TEST_KEY_ID, alg, plain_text,
                              sizeof(plain_text),
                              input.encrypted_data_pad,
                              sizeof(input.encrypted_data_pad),
                              &output_length);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error encrypting with the single-shot API");
    TEST_STATUS(status);
    goto destroy_key;
  }

  /* Store a copy of the encrypted data for later checking it against
   * multipart results
   */
#if DOMAIN_NS == 1U
  memcpy(encrypted_data_single_shot, &input.encrypted_data_pad[iv_length],
         output_length - iv_length);
#else
  (void)memcpy(encrypted_data_single_shot, &input.encrypted_data_pad[iv_length],
               output_length - iv_length);
#endif /* DOMAIN_NS == 1U */

  /* Make sure to use the randomly generated IV for the multipart flow */
  for (uint32_t i = 0; i < iv_length; i++)
  {
    iv[i] = input.encrypted_data_pad[i];
  }

  status = psa_cipher_decrypt(CIPHER_TEST_KEY_ID, alg,
                              input.encrypted_data_pad,
                              output_length,
                              decrypted_data, ENC_DEC_BUFFER_SIZE,
                              &output_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error decrypting with the single shot API");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (sizeof(plain_text) != output_length)
  {
    TEST_FAIL("Unexpected output length");
    goto destroy_key;
  }

  /* Check that the plain text matches the decrypted data */
  comp_result = (uint32_t)memcmp(plain_text, decrypted_data, sizeof(plain_text));
  if (comp_result != 0U)
  {
    TEST_FAIL("Decrypted data doesn't match with plain text");
    goto destroy_key;
  }

  /* Clear inputs/outputs before moving to multipart tests */

  /* Clear intermediate buffers for additional single-shot API tests */
  (void)memset(input.encrypted_data_pad, 0, sizeof(input.encrypted_data_pad));
  (void)memset(decrypted_data, 0, sizeof(decrypted_data));

  /* Replicate the same test as above, but now using the multipart APIs */

  /* Setup the encryption object */
  status = psa_cipher_encrypt_setup(&handle, key_handle, alg);
  if (status != PSA_SUCCESS)
  {
    if (status == PSA_ERROR_NOT_SUPPORTED)
    {
      TEST_FAIL("Algorithm NOT SUPPORTED by the implementation");
    }
    else
    {
      TEST_FAIL("Error setting up cipher operation object");
    }
    TEST_STATUS(status);
    goto destroy_key;
  }

  /* Set the IV */
  if (alg != PSA_ALG_ECB_NO_PADDING)
  {
    status = psa_cipher_set_iv(&handle, iv, iv_length);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error setting the IV on the cipher operation object");
      TEST_STATUS(status);
      goto abort;
    }
  }

  data_left = sizeof(plain_text);
  while (data_left)
  {
    /* Encrypt one chunk of information */
    status = psa_cipher_update(&handle, &plain_text[total_output_length],
                               BYTE_SIZE_CHUNK,
                               &input.encrypted_data[total_output_length],
                               ENC_DEC_BUFFER_SIZE - total_output_length,
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error encrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    if (output_length != BYTE_SIZE_CHUNK)
    {
      TEST_FAIL("Expected encrypted length is different from expected");
      goto abort;
    }

    data_left -= BYTE_SIZE_CHUNK;
    total_output_length += output_length;
  }

  /* Finalise the cipher operation */

  status = psa_cipher_finish(&handle,
                             &input.encrypted_data[total_output_length],
                             ENC_DEC_BUFFER_SIZE - total_output_length,
                             &output_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error finalising the cipher operation");
    TEST_STATUS(status);
    goto abort;
  }

  if (alg == PSA_ALG_CBC_PKCS7)
  {
    /* Finalisation produces an output for padded modes, which is the
     * encryption of the padded data added
     */
    if (output_length != BYTE_SIZE_CHUNK)
    {
      TEST_FAIL("Padded mode final output length unexpected");
      goto abort;
    }
  }
  else
  {
    if (output_length != 0U)
    {
      TEST_FAIL("Un-padded mode final output length unexpected");
      goto abort;
    }
  }

  /* Add the last output produced, it might be encrypted padding */
  total_output_length += output_length;

  /* Compare encrypted data produced with single-shot and multipart APIs */
  comp_result = (uint32_t)memcmp(encrypted_data_single_shot,
                                 input.encrypted_data,
                                 total_output_length);
  if (comp_result != 0U)
  {
    TEST_FAIL("Single-shot crypt doesn't match with multipart crypt");
    goto destroy_key;
  }

  /* Setup the decryption object */
  status = psa_cipher_decrypt_setup(&handle_dec, key_handle, alg);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error setting up cipher operation object");
    TEST_STATUS(status);
    goto destroy_key;
  }

  /* From now on, in case of failure we want to abort the decryption op */
  bAbortDecryption = true;

  /* Set the IV for decryption */
  if (alg != PSA_ALG_ECB_NO_PADDING)
  {
    status = psa_cipher_set_iv(&handle_dec, iv, iv_length);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error setting the IV for decryption");
      TEST_STATUS(status);
      goto abort;
    }
  }

  /* Padded mode output is produced one block later */
  bIsLagging = false;
  if (alg == PSA_ALG_CBC_PKCS7)
  {
    bIsLagging = true; /* Padded modes lag by 1 block */
  }

  /* Decrypt - total_output_length considers encrypted padding */
  data_left = total_output_length;
  total_output_length = 0;
  message_start = 0;

  while (data_left)
  {
    status = psa_cipher_update(&handle_dec,
                               &input.encrypted_data[message_start],
                               BYTE_SIZE_CHUNK,
                               &decrypted_data[total_output_length],
                               (ENC_DEC_BUFFER_SIZE - total_output_length),
                               &output_length);

    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error decrypting one chunk of information");
      TEST_STATUS(status);
      goto abort;
    }

    if (!bIsLagging && (output_length != BYTE_SIZE_CHUNK))
    {
      TEST_FAIL("Expected encrypted length is different from expected");
      goto abort;
    }

    message_start += BYTE_SIZE_CHUNK;
    data_left -= BYTE_SIZE_CHUNK;
    total_output_length += output_length;
    bIsLagging = false;
  }

  /* Finalise the cipher operation for decryption (destroys decrypted data) */
  status = psa_cipher_finish(&handle_dec, &decrypted_data[total_output_length],
                             BYTE_SIZE_CHUNK,
                             &output_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error finalising the cipher operation");
    TEST_STATUS(status);
    goto abort;
  }

  /* Finalize the count of output which has been produced */
  total_output_length += output_length;

  /* Check that the decrypted length is equal to the original length */
  if (total_output_length != (3U * BYTE_SIZE_CHUNK))
  {
    TEST_FAIL("After finalising, unexpected decrypted length");
    goto destroy_key;
  }

  /* Check that the plain text matches the decrypted data */
  comp_result = memcmp(plain_text, decrypted_data, sizeof(plain_text));
  if (comp_result != 0U)
  {
    TEST_FAIL("Decrypted data doesn't match with plain text");
  }

  /* Go directly to the destroy_key label at this point */
  ret->info_msg = PASS_STRING;
  goto destroy_key;

abort:
  /* Abort the operation */
  status = bAbortDecryption ? psa_cipher_abort(&handle_dec) :
           psa_cipher_abort(&handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error aborting the operation");
    TEST_STATUS(status);
    goto destroy_key;
  }

destroy_key:
  /* Destroy the key */
  status = psa_destroy_key(key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error destroying a key");
    TEST_STATUS(status);
  }
}

#endif  /* TEST_CIPHER */


/*
 * \brief This is the list of algorithms supported by the current
 *        configuration of the crypto engine used by the crypto
 *        service. In case the crypto engine default capabilities
 *        is changed, this list needs to be updated accordingly
 */


static const psa_algorithm_t hash_alg[] =
{
  PSA_ALG_SHA_224,
  PSA_ALG_SHA_256,
  PSA_ALG_SHA_384,
  PSA_ALG_SHA_512,
  PSA_ALG_SHA_1
};

#ifdef TEST_HASH
static const uint8_t hash_val[][PSA_HASH_LENGTH(PSA_ALG_SHA_512)] =
{
  {
    0x00, 0xD2, 0x90, 0xE2, 0x0E, 0x4E, 0xC1, 0x7E, /*!< SHA-224 */
    0x7A, 0x95, 0xF5, 0x10, 0x5C, 0x76, 0x74, 0x04,
    0x6E, 0xB5, 0x56, 0x5E, 0xE5, 0xE7, 0xBA, 0x15,
    0x6C, 0x23, 0x47, 0xF3
  },
  {
    0x6B, 0x22, 0x09, 0x2A, 0x37, 0x1E, 0xF5, 0x14, /*!< SHA-256 */
    0xF7, 0x39, 0x4D, 0xCF, 0xAD, 0x4D, 0x17, 0x46,
    0x66, 0xCB, 0x33, 0xA0, 0x39, 0xD8, 0x41, 0x4E,
    0xF1, 0x2A, 0xD3, 0x4D, 0x69, 0xC3, 0xB5, 0x3E
  },
  {
    0x64, 0x79, 0x11, 0xBB, 0x47, 0x4E, 0x47, 0x59, /*!< SHA-384 */
    0x3E, 0x4D, 0xBC, 0x60, 0xA5, 0xF9, 0xBF, 0x9C,
    0xC0, 0xBA, 0x55, 0x0F, 0x93, 0xCA, 0x72, 0xDF,
    0x57, 0x1E, 0x50, 0x56, 0xF9, 0x4A, 0x01, 0xD6,
    0xA5, 0x6F, 0xF7, 0x62, 0x34, 0x4F, 0x48, 0xFD,
    0x9D, 0x15, 0x07, 0x42, 0xB7, 0x72, 0x94, 0xB8
  },
  {
    0xB4, 0x1C, 0xA3, 0x6C, 0xA9, 0x67, 0x1D, 0xAD, /*!< SHA-512 */
    0x34, 0x1F, 0xBE, 0x1B, 0x83, 0xC4, 0x40, 0x2A,
    0x47, 0x42, 0x79, 0xBB, 0x21, 0xCA, 0xF0, 0x60,
    0xE4, 0xD2, 0x6E, 0x9B, 0x70, 0x12, 0x34, 0x3F,
    0x55, 0x2C, 0x09, 0x31, 0x0A, 0x5B, 0x40, 0x21,
    0x01, 0xA8, 0x3B, 0x58, 0xE7, 0x48, 0x13, 0x1A,
    0x7E, 0xCD, 0xE1, 0xD2, 0x46, 0x10, 0x58, 0x34,
    0x49, 0x14, 0x4B, 0xAA, 0x89, 0xA9, 0xF5, 0xB1
  },
  {
    0x56, 0x4a, 0x0e, 0x35, 0xf1, 0xc7, 0xbc, 0xd0, /*!< SHA-1 */
    0x7d, 0xcf, 0xb1, 0xbc, 0xc9, 0x16, 0xfa, 0x2e,
    0xf5, 0xbe, 0x96, 0xb2
  }
};

void psa_hash_test(const psa_algorithm_t alg,
                   struct test_result_t *ret)
{
  const char *msg =
    "This is my test message, please generate a hash for this.";
  /* Length of each chunk in the multipart API */
  const size_t msg_size[] = {25, 32};
  const uint32_t msg_num = sizeof(msg_size) / sizeof(msg_size[0]);
  uint32_t idx;
  uint32_t start_idx = 0;
  ret->info_msg = "";

  psa_status_t status;
  psa_hash_operation_t handle = psa_hash_operation_init();

  /* Setup the hash object for the desired hash*/
  status = psa_hash_setup(&handle, alg);

  if (status != PSA_SUCCESS)
  {
    TEST_STATUS(status);
    if (status == PSA_ERROR_NOT_SUPPORTED)
    {
      TEST_FAIL("Algorithm NOT SUPPORTED by the implementation");
      return;
    }

    TEST_FAIL("Error setting up hash operation object");
    return;
  }

  /* Update object with all the chunks of message */
  for (idx = 0; idx < msg_num; idx++)
  {
    status = psa_hash_update(&handle,
                             (const uint8_t *)&msg[start_idx],
                             msg_size[idx]);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error updating the hash operation object");
      TEST_STATUS(status);
      return;
    }
    start_idx += msg_size[idx];
  }

  /* Cycle until idx points to the correct index in the algorithm table */
  for (idx = 0; hash_alg[idx] != alg; idx++) {};

  /* Finalise and verify that the hash is as expected */
  status = psa_hash_verify(&handle, hash_val[idx], PSA_HASH_LENGTH(alg));
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error verifying the hash operation object");
    TEST_STATUS(status);
    return;
  }

  /* Do the same as above with the single shot APIs */
  status = psa_hash_compare(alg,
                            (const uint8_t *)msg, strlen(msg),
                            hash_val[idx], PSA_HASH_LENGTH(alg));
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error using the single shot API");
    TEST_STATUS(status);
    return;
  }

  ret->val = TEST_PASSED;
  ret->info_msg = PASS_STRING;
}
#endif  /* TEST_HASH */

#ifdef TEST_MAC

static const uint8_t cmac_val[16] =
{
  0x17, 0x0f, 0xd0, 0xe1,
  0x5f, 0x1f, 0x0a, 0x9b,
  0xd9, 0xdf, 0x79, 0x31,
  0xaf, 0x26, 0xcb, 0xbc
};

static const uint8_t hmac_val[][PSA_HASH_LENGTH(PSA_ALG_SHA_512)] =
{
  {
    0xc1, 0x9f, 0x19, 0xac, 0x05, 0x65, 0x5f, 0x02, /*!< SHA-224 */
    0x1b, 0x64, 0x32, 0xd9, 0xb1, 0x49, 0xba, 0x75,
    0x05, 0x60, 0x52, 0x4e, 0x78, 0xfa, 0x61, 0xc9,
    0x37, 0x5d, 0x7f, 0x58
  },
  {
    0x94, 0x37, 0xbe, 0xb5, 0x7f, 0x7c, 0x5c, 0xb0, /*!< SHA-256 */
    0x0a, 0x92, 0x4d, 0xd3, 0xba, 0x7e, 0xb1, 0x1a,
    0xdb, 0xa2, 0x25, 0xb2, 0x82, 0x8e, 0xdf, 0xbb,
    0x61, 0xbf, 0x91, 0x1d, 0x28, 0x23, 0x4a, 0x04
  },
  {
    0x94, 0x21, 0x9b, 0xc3, 0xd5, 0xed, 0xe6, 0xee, /*!< SHA-384 */
    0x42, 0x10, 0x5a, 0x58, 0xa4, 0x4d, 0x67, 0x87,
    0x16, 0xa2, 0xa7, 0x6c, 0x2e, 0xc5, 0x85, 0xb7,
    0x6a, 0x4c, 0x90, 0xb2, 0x73, 0xee, 0x58, 0x3c,
    0x59, 0x16, 0x67, 0xf3, 0x6f, 0x30, 0x99, 0x1c,
    0x2a, 0xf7, 0xb1, 0x5f, 0x45, 0x83, 0xf5, 0x9f
  },
  {
    0x8f, 0x76, 0xef, 0x12, 0x0b, 0x92, 0xc2, 0x06, /*!< SHA-512 */
    0xce, 0x01, 0x18, 0x75, 0x84, 0x96, 0xd9, 0x6f,
    0x23, 0x88, 0xd4, 0xf8, 0xcf, 0x79, 0xf8, 0xcf,
    0x27, 0x12, 0x9f, 0xa6, 0x7e, 0x87, 0x9a, 0x68,
    0xee, 0xe2, 0xe7, 0x1d, 0x4b, 0xf2, 0x87, 0xc0,
    0x05, 0x6a, 0xbd, 0x7f, 0x9d, 0xff, 0xaa, 0xf3,
    0x9a, 0x1c, 0xb7, 0xb7, 0xbd, 0x03, 0x61, 0xa3,
    0xa9, 0x6a, 0x5d, 0xb2, 0x81, 0xe1, 0x6f, 0x1f
  },
  {
    0x0d, 0xa6, 0x9d, 0x02, 0x43, 0x17, 0x3e, 0x7e, /*!< SHA-1 */
    0xe7, 0x3b, 0xc6, 0xa9, 0x51, 0x06, 0x8a, 0xea,
    0x12, 0xb0, 0xa7, 0x1d
  }
};

static const uint8_t long_key_hmac_val[PSA_HASH_LENGTH(PSA_ALG_SHA_224)] =
{
  0x47, 0xa3, 0x42, 0xb1, 0x2f, 0x52, 0xd3, 0x8f, /*!< SHA-224 */
  0x1e, 0x02, 0x4a, 0x46, 0x73, 0x0b, 0x77, 0xc1,
  0x5e, 0x93, 0x31, 0xa9, 0x3e, 0xc2, 0x81, 0xb5,
  0x3d, 0x07, 0x6f, 0x31
};

#define MAC_TEST_KEY_ID (0x1)

void psa_mac_test(const psa_algorithm_t alg,
                  const uint8_t *key,
                  size_t key_bits,
                  struct test_result_t *ret)
{
  const char *msg =
    "This is my test message, please generate a hmac for this.";
  /* Length of each chunk in the multipart API */
  const size_t msg_size[] = {25, 32};
  const uint32_t msg_num = sizeof(msg_size) / sizeof(msg_size[0]);
  uint32_t idx;
  uint32_t start_idx = 0;
  uint8_t *hmac_res;
  uint8_t computed_result[64];
  uint8_t output_length;
  uint32_t output_len;
  uint32_t comp_result;
  psa_key_type_t key_type;
  ret->info_msg = "";

  psa_key_handle_t key_handle;
  if (alg == PSA_ALG_CMAC)
  {
    key_type = PSA_KEY_TYPE_AES;
    output_length = 16;
  }
  else
  {
    key_type = PSA_KEY_TYPE_HMAC;
    output_length = PSA_HASH_LENGTH(PSA_ALG_HMAC_GET_HASH(alg));
  }

  psa_status_t status;
  psa_mac_operation_t handle = psa_mac_operation_init();
  psa_key_attributes_t key_attributes = psa_key_attributes_init();
  psa_key_attributes_t retrieved_attributes = psa_key_attributes_init();
  psa_key_usage_t usage = PSA_KEY_USAGE_VERIFY_MESSAGE | PSA_KEY_USAGE_SIGN_MESSAGE ;

  ret->val = TEST_PASSED;

  /* Setup the key policy */
  psa_set_key_usage_flags(&key_attributes, usage);
  psa_set_key_algorithm(&key_attributes, alg);
  psa_set_key_type(&key_attributes, key_type);
  /* With volatile key */
  psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);

  /* Import key */
  status = psa_import_key(&key_attributes, key, PSA_BITS_TO_BYTES(key_bits),
                          &key_handle);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing a key");
    TEST_STATUS(status);
    return;
  }

  status = psa_get_key_attributes(key_handle, &retrieved_attributes);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error getting key metadata");
    TEST_STATUS(status);
    goto destroy_key_mac;
  }

  if (psa_get_key_bits(&retrieved_attributes) != key_bits)
  {
    TEST_FAIL("The number of key bits is different from expected");
    goto destroy_key_mac;
  }

  if (psa_get_key_type(&retrieved_attributes) != key_type)
  {
    TEST_FAIL("The type of the key is different from expected");
    goto destroy_key_mac;
  }

  psa_reset_key_attributes(&retrieved_attributes);

  /* Setup the mac object for hmac */
  status = psa_mac_verify_setup(&handle, key_handle, alg);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error setting up mac operation object");
    TEST_STATUS(status);
    goto destroy_key_mac;
  }

  /* Update object with all the chunks of message */
  for (idx = 0; idx < msg_num; idx++)
  {
    status = psa_mac_update(&handle,
                            (const uint8_t *)&msg[start_idx],
                            msg_size[idx]);
    if (status != PSA_SUCCESS)
    {
      TEST_FAIL("Error during mac operation");
      TEST_STATUS(status);
      goto destroy_key_mac;
    }
    start_idx += msg_size[idx];
  }

  /* Cycle until idx points to the correct index in the algorithm table */
  if (alg == PSA_ALG_CMAC)
  {
    hmac_res = (uint8_t *)cmac_val;
  }
  else
  {
    for (idx = 0; hash_alg[idx] != PSA_ALG_HMAC_GET_HASH(alg); idx++) {};
    if (key_bits == BIT_SIZE_TEST_LONG_KEY)
    {
      hmac_res = (uint8_t *)long_key_hmac_val;
    }
    else
    {
      hmac_res = (uint8_t *)hmac_val[idx];
    }
  }

  /* Finalise and verify the mac value */
  status = psa_mac_verify_finish(&handle, hmac_res, output_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error during finalising the mac operation");
    TEST_STATUS(status);
    goto destroy_key_mac;
  }

  /* Do the same as above with the single shot APIs */

  status = psa_mac_verify(key_handle, alg,
                          (const uint8_t *)msg, strlen(msg),
                          hmac_res, output_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error using the single shot API");
    TEST_STATUS(status);
    goto destroy_key_mac;
  }

  /* Test hmac computation through psa_mac_compute */
  status = psa_mac_compute(key_handle, alg,
                           (const uint8_t *)msg, strlen(msg),
                           computed_result, output_length,
                           (size_t *)&output_len);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error using psa_mac_compute API");
    TEST_STATUS(status);
    goto destroy_key_mac;
  }
  /* Compare with correct result */
  comp_result = memcmp(computed_result, hmac_res, output_length);
  if (comp_result != 0U)
  {
    TEST_FAIL("Computed HMAC does not match reference data");
    goto destroy_key_mac;
  }

  ret->info_msg = PASS_STRING;
destroy_key_mac:
  /* Destroy the key */
  status = psa_destroy_key(key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error destroying the key");
    TEST_STATUS(status);
  }
}

#endif  /* TEST_MAC */

#if defined(TFM_CRYPTO_TEST_ALG_CCM) || defined (TFM_CRYPTO_TEST_ALG_GCM)
void psa_aead_test(const psa_key_type_t key_type,
                   const psa_algorithm_t alg,
                   const uint8_t *key,
                   size_t key_bits,
                   struct test_result_t *ret)
{
  psa_status_t status;
  psa_key_handle_t key_handle;
  const size_t nonce_length = 12;
  const uint8_t nonce[] = "01234567890";
  const uint8_t plain_text[MAX_PLAIN_DATA_SIZE_AEAD] =
    "This is my plaintext message and it's made of 68 characters...!1234";
  const uint8_t associated_data[] =
    "This is my associated data to authenticate";
  uint8_t decrypted_data[MAX_PLAIN_DATA_SIZE_AEAD] = {0};
  uint8_t encrypted_data[ENC_DEC_BUFFER_SIZE_AEAD] = {0};
  size_t encrypted_data_length = 0, decrypted_data_length = 0;
  uint32_t comp_result;
  psa_key_attributes_t key_attributes = psa_key_attributes_init();
  psa_key_attributes_t retrieved_attributes = psa_key_attributes_init();
  psa_key_usage_t usage = (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);

  ret->info_msg = "";
  ret->val = TEST_FAILED;

  /* Setup the key policy */
  psa_set_key_usage_flags(&key_attributes, usage);
  psa_set_key_algorithm(&key_attributes, alg);
  psa_set_key_type(&key_attributes, key_type);

  /* Import a key */
  status = psa_import_key(&key_attributes, key, PSA_BITS_TO_BYTES(key_bits),
                          &key_handle);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing a key\r\n");
    TEST_STATUS(status);
    return;
  }

  status = psa_get_key_attributes(key_handle, &retrieved_attributes);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error getting key metadata");
    TEST_STATUS(status);
    goto destroy_key_aead;
  }

  if (psa_get_key_bits(&retrieved_attributes) != key_bits)
  {
    TEST_FAIL("The number of key bits is different from expected");
    goto destroy_key_aead;
  }

  if (psa_get_key_type(&retrieved_attributes) != key_type)
  {
    TEST_FAIL("The type of the key is different from expected");
    goto destroy_key_aead;
  }

  psa_reset_key_attributes(&retrieved_attributes);

  /* Perform AEAD encryption */
  status = psa_aead_encrypt(key_handle, alg, nonce, nonce_length,
                            associated_data,
                            sizeof(associated_data),
                            plain_text,
                            sizeof(plain_text),
                            encrypted_data,
                            sizeof(encrypted_data),
                            &encrypted_data_length);

  if (status != PSA_SUCCESS)
  {
    TEST_STATUS(status);
    if (status == PSA_ERROR_NOT_SUPPORTED)
    {
      TEST_FAIL("Algorithm NOT SUPPORTED by the implementation");
      goto destroy_key_aead;
    }

    TEST_FAIL("Error performing AEAD encryption");
    goto destroy_key_aead;
  }

  if (encrypted_data_length
      != PSA_AEAD_ENCRYPT_OUTPUT_SIZE(key_type, alg, sizeof(plain_text)))
  {
    TEST_FAIL("Encrypted data length is different than expected");
    goto destroy_key_aead;
  }

  /* Perform AEAD decryption */
  status = psa_aead_decrypt(key_handle, alg, nonce, nonce_length,
                            associated_data,
                            sizeof(associated_data),
                            encrypted_data,
                            encrypted_data_length,
                            decrypted_data,
                            sizeof(decrypted_data),
                            &decrypted_data_length);

  if (status != PSA_SUCCESS)
  {
    if (status == PSA_ERROR_NOT_SUPPORTED)
    {
      TEST_FAIL("Algorithm NOT SUPPORTED by the implementation");
    }
    else
    {
      TEST_FAIL("Error performing AEAD decryption");
    }
    TEST_STATUS(status);

    goto destroy_key_aead;
  }

  if (sizeof(plain_text) != decrypted_data_length)
  {
    TEST_FAIL("Decrypted data length is different from plain text");
    goto destroy_key_aead;
  }

  /* Check that the decrypted data is the same as the original data */
  comp_result = memcmp(plain_text, decrypted_data, sizeof(plain_text));
  if (comp_result != 0U)
  {
    TEST_FAIL("Decrypted data doesn't match with plain text");
    goto destroy_key_aead;
  }
  ret->info_msg = PASS_STRING;

destroy_key_aead:
  /* Destroy the key */
  status = psa_destroy_key(key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error destroying a key");
    TEST_STATUS(status);
  }

}

#endif  /* defined(TFM_CRYPTO_TEST_ALG_CCM) || defined (TFM_CRYPTO_TEST_ALG_GCM) */


/* An example of a 32 bytes / 256 bits ECDSA private key */
static const uint8_t ecdsa_private_key[] =
{
  0x11, 0xb5, 0x73, 0x7c, 0xf9, 0xd9, 0x3f, 0x17,
  0xc0, 0xcb, 0x1a, 0x84, 0x65, 0x5d, 0x39, 0x95,
  0xa0, 0x28, 0x24, 0x09, 0x7e, 0xff, 0xa5, 0xed,
  0xd8, 0xee, 0x26, 0x38, 0x1e, 0xb5, 0xd6, 0xc3
};
/* Buffer to hold the peer key of the key agreement process */

#define RAW_AGREEMENT_TEST_KEY_ID (0x1)

#ifdef TEST_RSA
static const uint8_t rsa_key_pair_2048[] =
  /* RSA-2048 OpenSSL generated */
  "-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAnkAVGBnBTceorbPTUKwueMHIGPflUNgLqbuLDuDwc8J9kTjp\
X0yBrpdJnZ02/mMHt5HLolq/K9xGJDVSkAK4UcjriwXhyI3MR3OLhohSEKSdYK2o\
HtIMbZunuURh9XLBlUJBAGQxC7itJBI7zFpxZjwLs49xOKk4uW76wkl+ZvzLyTOh\
5Wh1bYmEXzCx8yyC2Yg+JtGVIszh5CJOXUlUiHkEOzlf4RxMzN28FORRKAf4/MIs\
gX8DbFB65L/HBO3daTe7j4N9cPwknrkSaPyDWYdH1k37qhcniFA/voGXjnnag57o\
gc7yZV+ukw4xa14rnHprDnfMBHjmCNyCwmqi+QIDAQABAoIBABbyVdyzx1re66+c\
VrTo8qgh+UDdmUvat/45qpVSuqsedZS8OuLNtjQ5zbvkExhaBcFxi6SUIgpbG3Se\
osUtD8sUJkt3Y+Dv5sIpl/6+/59YL1XYeHtXm+O84Vo09ztfE4DwJXrIDHCVq82C\
M1eTecQISu4Ti6haqVYCKKxJeeG25fEjvs+HPZkiaUJIhDyyVF/bumbxtQFtIDKi\
vPSsQjFIn/0MiZK5Pqpn8O4+L/KVPpCULugO2tJ2Ja92gtiutt817T4G98Lqkhgw\
mYAGsZd8VFRBQM3IAhCTCW1MlJvnW7Kn4RmkvemOV8w33URRgvd/FPZ+wAxdv00V\
x3Vnfd0CgYEA0JjzpuBRyHuJKi8Klj8O6YH/42OtJvX4DbpomDYLX7kXdf8R0QWF\
fD7OBjOIOExD2KtpreZZflmKwlq58Riw4lgeCdI8RYHfP/j7pvhg1I/wmWYufiNF\
z1xdGPpMTIhJtro/MpURv+PZx7bWNxsd0AJLPy5DpVjofJBozSm2UfMCgYEAwjY2\
OuJxniVR1O4FHvwAC47BKV1/wSSqVFFM47kHhDfND69bnTWK+l+aOJUsaQH8uIbv\
EdjsflSBBdZV1fHMqF3T4i06/nMatfgE+kehAADXos/EaJE4odVyRqBFg0JsmfCp\
gLTYXRaYiLGcSPhUND6QWrve9Ksjeu5xKZcdxmMCgYAvKTWFGBhFbHCxgdsx5uXX\
M1YIMgP22AuSBwAY0bc2mCFOwzFjAY2Rbp2j10jH+a4pMW/+KiM3psTxdhOuB7gO\
JH/+FnMb/+Xaj89Ni8BQro5mEC0YxZ7F6AsAV66iavnHf0pEhGFz8e7N8W9zHAVc\
fvhGO459tqExcHDRWcnnswKBgQCddPJ2v0y6mStFZUzFmC45MJ4u+V0wrJdkER4z\
qroLWmppAxVV2ik5YPVaVqdQ44mP2eZOI/9pVP3eS63/7TCueJPm1iD0V0IasmDm\
wdgodoZdu/FTjhnKK5Gg7SQujVYbYOEsNnMM1dsJSGabSqqKSQckaRkUaQQ1EMiy\
nZBIXQKBgF+38gB0O0VIQOMyn+dMWC7C5MLql2rr1aKkfUPW7YO/bPjsuwUNSD9y\
eFRzW2h7YWC28cnIBK9SFLYAFn7+Ay6D4XlD/z3okAaprsxxC6AeXXxyfU1qXJIv\
Or59NX9iJqLIGXIBCtUuihgOQIHBa+oF1B6kqt4m9wB8HfC/IHUb\
-----END RSA PRIVATE KEY-----\0";

static const uint8_t rsa_key_pair_3072[] =
  /* RSA-3072 OpenSSL generated */
  "-----BEGIN RSA PRIVATE KEY-----\n\
MIIG4gIBAAKCAYEAtm8vsglpl+lQH0u5Nwau2gMkMJjO3Lw3Xp4xlu/R/wuhvg1z\
Je/Ese32Xx3gAdkCzPX2S7hyfI7TVBHRAzvMiuEcr6dih3Wc0Q8XisTZvJEnaEr6\
NkN8CFZsMH2M+9tUcjvtgq0hUlYCFPsPCc+3BpPxtyO0AHElCW3/BjSLb8YYSaUR\
+qz41kzwzVQGvkqMNQzSmqy6xrco27CX4b1GgxPGOlne8FvF39Pec9XDYqA28ohm\
GxSvAHIOhX6P1wR/0/BonRWfzY8Llg4BU1YyG/71Sc8ppYRXw5uVdnjQReyqJXqJ\
WhZTxFhNFppV+L28+45zVnv2dsRy2EMuPHI3/qPxPQ1LFSJxGvUETOmgGZ01+Gp0\
JDnSA+qh6mY1rB0sRdWeJ7dzGvq4cowr8UtgOLqyEtLTuHk5gqwwrclclGLNEdIY\
gOlOF6+95DzBTLtUPyLQL4Xj/Lv43p4KastP24KCGQKpIFHMhUrDl6h5NY1MtfsK\
B73rz4ybKm/LllMBAgMBAAECggGAQj8BvM66L1WjqJmguiCNIdF+NL9obrNSD+O1\
8i9HvCuHIjJUG/SDInFcw5FfpIwe/jpao4ho2l4q0x5dHaV7UvsHpalMmA/XT/sA\
+30b6+NxwedoEIhU49ouEzWkGli8w3aLeqZPsUxWGTRJc7Cfr53NaklmtbpgTppI\
vwIZmA8BBs0QSEzDV149GvJmOHdtjl4Ho+8RK9Oa3Ju1q11F25c0pj+4OuO4aNzQ\
rJN1Db1L9qodGbxbB/hi2YrpxJR3EZRnrbn6zSe3AJPHSxN1oKKAfbShPVEe2b7n\
ctdGJuTFXUOaeOiSZDB0Seg4VbGhPK+Tmg7+7qNd5oIABDAUYj4Ogfpn7xTi1YBc\
fy9mpppn0Z0Cmsr1lrqgfZQJRTNYEIslo8jxC4reg1/TD8i0JFjGhfiZmfdC19/s\
SLHE8TA0YD07lxpdrAJzJXXqWiUMFEMIVb1ihKLcUX2dQWoBR3VkI2deTZ/wr/Dw\
DPewPWwsNIrwfNnfg8E462plQd25AoHBANnBLCp08iM7fR8Vw1hniMhPy46/09qC\
hGgdBq9EpbTJAUvlOnHT0OD0y0EZQgZKnjJZxXqvBIoE7gWFTfb0Vx40R6MwJFuj\
G3qhkWKsRtpvhSAU1qP71j0WyFOiQzGdqk4JPDfU9uMDRvxazcFbIxx5QQdWur5C\
S9arhPtQuUhXKUG0N7TnThyedNItub4DU78jZhTYB2IdCnHVFkgDupcgCZfW0EiS\
7cTXXt4EwpREUN90i42BrpGGaZkNT/fWkwKBwQDWeeuuZfs77i3MHYcpvVJBzeqg\
bzx4mmHskZXLaa73AAdnyHjrXkA6eE50JWGB6H4tbsPUKBHFIwnpp9b0JQoNRHma\
HLownSeER6MyvotgFYwOIhB54Oh1x8nsmi23RQoXQsvBpNvo1mV/PyzsaD81Hc3q\
IBXEAq7F5dGp1+hZF6ZNyV8PttH6l8f2qNEKET3HzQVzlGhL/glK7Akfc+114dGh\
VzOk+A1U7P41wks9WKD0EuhUpU/KrXB9ns1T+JsCgcB7C+5SG31MLWx5qUmWZgLj\
9js3cexb2E7LqkNBvQ/KBZ9m7KRG+ANbatiD86rcdUPJffLabZWqDDkYA4jX2KB1\
3+LvMuAIrDV16WCHGoR7IHNgeoYDaeZY5MvUfqdrnQVETXGqtvu/sfVl2kXUUhSY\
HWiCph6mLj4+kvN1M9tPJnmYuCaWYfJAt8WZkt8XoTeslWs0shIR/gkN4/RQQ1Mn\
3KGvHGLb77LN/UmNObFeKPBuJKRLFRG5B/QZ2WzrxmMCgcBuefLarJFS94cDoxoi\
d/DNEKKQ7Xt6rBtQ3lUIqHGFrbAi13Lh2nS/KYVP8oldf0KvaGTa/aDZqQjMILZq\
oEGjP+hbZ/zIWcsnKjd4RgpI/hBcn1NZVG6pbLYod+qggqGGBdQq9R6JuxYhC4u6\
YqBcXfPZa5mKk88vBQiQsjRu3+28F8QttgBHUrOf7KlwxBzMtGDgfkuTCVIEE71H\
RFHG7QEsWFyz10oWutTfICvdd6/AyZR/NX/6aIiPTKN7Y40CgcA0LHG61cdN3lAY\
pmpWblXkIEtbsp+qPWyizoHhblbJfv4qOiwGJWzvszF9wWzIm7Kz1ksUUAdM87kO\
LKws0yypb3shvsigQWqD2Cu7vSAaZCccMhaulgiYEtoXPtg7MbW+LVt2aKFnNorH\
zKrktB9n4v+z9f9l/AMPe43wO0XBOVUM8JjP3ax+LT70MqwZO1cZyjPVmJ0Xfx/q\
+tyvwz9VyWFtQLCdRHimPwh6s9eanCXmFMK1/RvrfAuxvzwcfZ0=\
-----END RSA PRIVATE KEY-----\0";

#define PLAIN_TEXT_SIZE 16

void psa_asymmetric_encryption_test(psa_algorithm_t alg,
                                    struct test_result_t *ret, uint32_t rsa_key_size)
{
  psa_status_t status;
  psa_key_handle_t key_handle = 0x0u;
  const uint8_t plain_text[] = "This is a test.";
  uint8_t encrypted_data[PSA_ASYMMETRIC_ENCRYPT_OUTPUT_MAX_SIZE] = {0};
  size_t encrypted_size;
  size_t encrypted_length = 0;
  uint8_t decrypted_data[PLAIN_TEXT_SIZE] = {0};
  size_t decrypted_size = PLAIN_TEXT_SIZE;
  size_t decrypted_length = 0;
  const uint8_t *key_pair;
  size_t key_size;
  uint32_t comp_result;
  ret->info_msg = "";

  /*        key_pair = rsa_key_pair_1024;
            key_size = sizeof(rsa_key_pair_1024); */
  if (rsa_key_size == 1024U)
  {
    TEST_FAIL("Key length unsupported by test suite");
    return;
  }
  else if (rsa_key_size == 2048U)
  {
    key_pair = rsa_key_pair_2048;
    key_size = sizeof(rsa_key_pair_2048);
  }
  else if (rsa_key_size == 3072U)
  {
    key_pair = rsa_key_pair_3072;
    key_size = sizeof(rsa_key_pair_3072);
  }
  else
  {
    TEST_FAIL("Key length unsupported by test suite");
    return;
  }

  psa_key_attributes_t key_attributes = psa_key_attributes_init();

  /* Setup key attributes */
  psa_set_key_usage_flags(&key_attributes,
                          PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
  psa_set_key_algorithm(&key_attributes, alg);

  if (PSA_ALG_IS_RSA_OAEP(alg) || alg == PSA_ALG_RSA_PKCS1V15_CRYPT)
  {
    psa_set_key_type(&key_attributes, PSA_KEY_TYPE_RSA_KEY_PAIR);
    encrypted_size = rsa_key_size >> 3;
  }
  else
  {
    TEST_FAIL("Unsupported asymmetric encryption algorithm");
    return;
  }

  status = psa_import_key(&key_attributes, key_pair, key_size, &key_handle);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing a key");
    TEST_STATUS(status);
    return;
  }

  status = psa_asymmetric_encrypt(key_handle, alg, plain_text,
                                  sizeof(plain_text), NULL, 0, encrypted_data,
                                  encrypted_size, &encrypted_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error encrypting the plaintext");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (encrypted_size != encrypted_length)
  {
    TEST_FAIL("Unexpected encrypted length");
    goto destroy_key;
  }

  status = psa_asymmetric_decrypt(key_handle, alg, encrypted_data,
                                  encrypted_size, NULL, 0, decrypted_data,
                                  decrypted_size, &decrypted_length);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error during asymmetric decryption");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (decrypted_size != decrypted_length)
  {
    TEST_FAIL("Unexpected decrypted length");
    goto destroy_key;
  }

  /* Check that the plain text matches the decrypted data */
  comp_result = memcmp(plain_text, decrypted_data, sizeof(plain_text));
  if (comp_result != 0U)
  {
    TEST_FAIL("Decrypted data doesn't match with plain text");
    goto destroy_key;
  }

  ret->val = TEST_PASSED;
  ret->info_msg = PASS_STRING;
destroy_key:
  /* Destroy the key */
  status = psa_destroy_key(key_handle);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error destroying a key");
    TEST_STATUS(status);
  }
}

#endif /* TEST_RSA */

#define SIGNATURE_BUFFER_SIZE (PSA_ECDSA_SIGNATURE_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS))

#define SIGNING_TEST_KEY_ID key_handle
/*  No manually set KEY_ID because key is volatile */

void psa_sign_verify_message_test(psa_algorithm_t alg,
                                  struct test_result_t *ret)
{
  psa_status_t status;
  psa_key_handle_t key_handle = 0;
  psa_key_type_t key_type;
  psa_key_attributes_t input_key_attr = PSA_KEY_ATTRIBUTES_INIT;
  const uint8_t message[] =
    "This is the message that I would like to sign";
  uint8_t signature[SIGNATURE_BUFFER_SIZE] = {0};
  size_t signature_length = 0;
  ret->info_msg = "";

  /* Set attributes and import key */
  psa_set_key_usage_flags(&input_key_attr,
                          PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
  psa_set_key_algorithm(&input_key_attr, alg);
  key_type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
  psa_set_key_type(&input_key_attr, key_type);

  status = psa_import_key(&input_key_attr, ecdsa_private_key,
                          sizeof(ecdsa_private_key), &key_handle);

  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Error importing the private key");
    TEST_STATUS(status);
    return;
  }


  status = psa_sign_message(SIGNING_TEST_KEY_ID, alg,
                            message, sizeof(message) - 1U,
                            signature, SIGNATURE_BUFFER_SIZE,
                            &signature_length);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL("Message signing failed!");
    TEST_STATUS(status);
    goto destroy_key;
  }

  if (signature_length != PSA_ECDSA_SIGNATURE_SIZE(
        PSA_BYTES_TO_BITS(
          sizeof(ecdsa_private_key))))
  {
    TEST_FAIL("Unexpected signature length");
    goto destroy_key;
  }

  status = psa_verify_message(SIGNING_TEST_KEY_ID, alg,
                              message, sizeof(message) - 1U,
                              signature, signature_length);
  if (status != PSA_SUCCESS)
  {
    TEST_FAIL(("Signature verification failed!"));
    TEST_STATUS(status);
    goto destroy_key;
  }

  ret->val = TEST_PASSED;
  ret->info_msg = PASS_STRING;
destroy_key:
  (void)psa_destroy_key(key_handle);

  return;
}
