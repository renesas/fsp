/*
 * Copyright (c) 2017-2019 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tfm_common_config.h"

#include "platform/include/tfm_plat_crypto_keys.h"
#include "platform/include/tfm_attest_hal.h"
#include <stddef.h>
#include "psa/crypto_types.h"

/* FIXME: Functions in this file should be implemented by platform vendor. For
 * the security of the storage system, it is critical to use a hardware unique
 * key. For the security of the attestation, it is critical to use a unique key
 * pair and keep the private key is secret.
 */

#define TFM_KEY_LEN_BYTES    16

static const uint8_t sample_tfm_key[TFM_KEY_LEN_BYTES] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, \
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

extern const psa_ecc_curve_t initial_attestation_curve_type;
extern const uint8_t         initial_attestation_private_key[];
extern const uint32_t        initial_attestation_private_key_size;

/**
 * \brief Copy the key to the destination buffer
 *
 * \param[out]  p_dst  Pointer to buffer where to store the key
 * \param[in]   p_src  Pointer to the key
 * \param[in]   size   Length of the key
 */
static inline void copy_key (uint8_t * p_dst, const uint8_t * p_src, size_t size)
{
    uint32_t i;

    for (i = size; i > 0; i--)
    {
        *p_dst = *p_src;
        p_src++;
        p_dst++;
    }
}

enum tfm_plat_err_t tfm_plat_get_huk_derived_key (const uint8_t * label,
                                                  size_t          label_size,
                                                  const uint8_t * context,
                                                  size_t          context_size,
                                                  uint8_t       * key,
                                                  size_t          key_size)
{
    (void) label;
    (void) label_size;
    (void) context;
    (void) context_size;

    if (key_size > TFM_KEY_LEN_BYTES)
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    copy_key(key, sample_tfm_key, key_size);

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_initial_attest_key (uint8_t          * key_buf,
                                                     uint32_t           size,
                                                     struct ecc_key_t * ecc_key,
                                                     psa_ecc_curve_t  * curve_type)
{
    uint32_t key_size = initial_attestation_private_key_size;
    int      rc;

    if (size < key_size)
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    /* Set the EC curve type which the key belongs to */
    *curve_type = initial_attestation_curve_type;

    /* Copy the private key to the buffer, it MUST be present */
    copy_key(key_buf, initial_attestation_private_key, key_size);
    rc = 0;

    if (rc)
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ecc_key->priv_key      = key_buf;
    ecc_key->priv_key_size = key_size;

    ecc_key->pubx_key      = NULL;
    ecc_key->pubx_key_size = 0;
    ecc_key->puby_key      = NULL;
    ecc_key->puby_key_size = 0;

    return TFM_PLAT_ERR_SUCCESS;
}

