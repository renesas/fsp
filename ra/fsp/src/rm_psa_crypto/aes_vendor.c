/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "common.h"

#if defined(MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C)

 #include "aes_vendor.h"

/* Auto-generated values depending on which drivers are registered.
 * ID 0 is reserved for unallocated operations.
 * ID 1 is reserved for the Mbed TLS software driver. */
 #define PSA_CRYPTO_MBED_TLS_DRIVER_ID    (1)

/** Determine standard key size in bits for a vendor type key bit size associated with an elliptic curve.
 *  THis function is invoked during key generation and the user specifies the bits which will be the
 * standard bit size (SIZE_AES_128BIT_KEYLEN_BITS), but the wrapped key has a different size (SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED)
 * so that is returned.
 * This function is also invoked during key import. Since the wrapped key to be imported has a non-standard size,
 * when this key is imported, the bit length with be non standard. This function will account for that case as well.
 *
 * \param[in] type     Key type
 * \param[in] bits     Vendor key size in bits
 * \param[out] raw     Equivalent standard key size in bits
 */

psa_status_t prepare_raw_data_slot_vendor (psa_key_type_t type, size_t bits, struct key_data * key)
{
    (void) type;
    (void) bits;
    (void) key;
    uint32_t   * p_temp_keydata;
    psa_status_t ret = PSA_SUCCESS;

 #if defined(MBEDTLS_AES_ALT)
  #if defined(MBEDTLS_CHECK_PARAMS)
    if (bits % 8 != 0)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
  #endif                               // defined(MBEDTLS_CHECK_PARAMS)

    /* Check if the key is of AES type */
    if (PSA_KEY_TYPE_IS_AES(type))
    {
        /* Check that the bit size is acceptable for the key type */
        switch (bits)
        {
            case SIZE_AES_128BIT_KEYLEN_BITS:
            case SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED:
            {
                key->bytes = SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED;
                break;
            }

            case SIZE_AES_192BIT_KEYLEN_BITS:
            case SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED:
            {
                key->bytes = SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED;
                break;
            }

            case SIZE_AES_256BIT_KEYLEN_BITS:
            case SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED:
            {
                key->bytes = SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED;
                break;
            }

            default:
            {
                ret = PSA_ERROR_NOT_SUPPORTED;
            }
        }
    }
    else
 #endif
    {
        ret = PSA_ERROR_NOT_SUPPORTED;
    }

    if (!ret)
    {
/* Allocate memory for the key */
        p_temp_keydata = mbedtls_calloc((key->bytes / 4), sizeof(uint32_t));
        key->data      = (uint8_t *) p_temp_keydata;
        if (key->data == NULL)
        {
            key->bytes = 0;

            ret = PSA_ERROR_INSUFFICIENT_MEMORY;
        }
    }

    return ret;
}

/*************crypto_accel_driver.h implementations follow***************************/

psa_status_t psa_generate_symmetric_vendor (psa_key_type_t type, size_t bits, uint8_t * output, size_t output_size)
{
    fsp_err_t err = FSP_SUCCESS;
    int       ret = PSA_SUCCESS;

    (void) type;
    (void) bits;
    (void) output;
    (void) output_size;

 #if defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))

    /* Check if the key is of AES type */
    if (PSA_KEY_TYPE_IS_AES(type))
    {
        /* Check that the bit size is acceptable for the key type */
        switch (bits)
        {
            case SIZE_AES_128BIT_KEYLEN_BITS:
            {
                if (output_size != SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED)
                {
                    ret = PSA_ERROR_BUFFER_TOO_SMALL;
                }

                if (!ret)
                {
                    err = HW_SCE_GenerateAes128RandomKeyIndexSub((uint32_t *) output);
                }

                break;
            }

  #ifndef MBEDTLS_AES_ONLY_128_BIT_KEY_LENGTH
   #if BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
                BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED
            case SIZE_AES_192BIT_KEYLEN_BITS:
            {
                if (output_size != SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED)
                {
                    ret = PSA_ERROR_BUFFER_TOO_SMALL;
                }

                if (!ret)
                {
                    err = HW_SCE_GenerateAes192RandomKeyIndexSub((uint32_t *) output);
                }

                break;
            }
   #endif
            case SIZE_AES_256BIT_KEYLEN_BITS:
            {
                if (output_size != SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED)
                {
                    ret = PSA_ERROR_BUFFER_TOO_SMALL;
                }

                if (!ret)
                {
                    err = HW_SCE_GenerateAes256RandomKeyIndexSub((uint32_t *) output);
                }

                break;
            }
  #endif
            default:
            {
                ret = PSA_ERROR_NOT_SUPPORTED;
            }
        }
    }
    else
 #endif                                /* defined(MBEDTLS_AES_ALT) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT))) */
    {
        ret = PSA_ERROR_NOT_SUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (ret == PSA_SUCCESS))
    {
        ret = PSA_ERROR_HARDWARE_FAILURE;
    }

    return ret;
}

void psa_aead_setup_vendor (void * ctx)
{
    (void) ctx;
 #if defined(MBEDTLS_AES_ALT)
    mbedtls_aes_context * context = (mbedtls_aes_context *) ctx;
    context->vendor_ctx = (bool *) true;
 #endif
}

#endif                                 /* MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C */
