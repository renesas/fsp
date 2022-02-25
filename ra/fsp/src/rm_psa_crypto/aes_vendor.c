/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#if !defined(MBEDTLS_CONFIG_FILE)
 #include "mbedtls/config.h"
#else
 #include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C)

 #include "aes_vendor.h"

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
                    err = HW_SCE_AES_128CreateEncryptedKey((uint32_t *) output);
                }

                break;
            }

  #if BSP_FEATURE_CRYPTO_HAS_SCE9
            case SIZE_AES_192BIT_KEYLEN_BITS:
            {
                if (output_size != SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED)
                {
                    ret = PSA_ERROR_BUFFER_TOO_SMALL;
                }

                if (!ret)
                {
                    err = HW_SCE_AES_192CreateEncryptedKey((uint32_t *) output);
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
                    err = HW_SCE_AES_256CreateEncryptedKey((uint32_t *) output);
                }

                break;
            }

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

psa_status_t psa_cipher_setup_vendor (psa_cipher_operation_t * operation,
                                      psa_key_slot_t *         slot,
                                      psa_algorithm_t          alg,
                                      mbedtls_operation_t      cipher_operation)
{
    (void) operation;
    (void) slot;
    (void) alg;
    (void) cipher_operation;
    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;
 #if defined(MBEDTLS_AES_ALT)
    int              ret  = 0;
    (void) alg;
    size_t key_bits = 0;
    const mbedtls_cipher_info_t * cipher_info = NULL;

    /* The mbedcrypto implementation obtains the list of methods based on the keybit size.
     * Since the wrapped keybit size does not correspond to the raw key size i.e the
     * AES256 raw bit size is 256 but the wrapped size is 416 bytes, provide the 256 bit value
     * to mbedcrypto so that the right methods are invoked.
     * Since AES192 wrapped size is also 416, there is an addition of 32 dummy bits in the end to make it 448 bits.
     * This helps to differentiate between the 256 and 192 wrapped keys.
     * */
    status = vendor_bitlength_to_raw_bitlength(slot->attr.type, slot->attr.bits, &key_bits);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* Strip out the vendor flag from the key type since the PSA code does not recognize it*/
    cipher_info = mbedtls_cipher_info_from_psa(alg, (psa_key_type_t)(slot->attr.type & ~PSA_KEY_TYPE_VENDOR_FLAG), key_bits, NULL);
    if (cipher_info == NULL)
    {
        status = PSA_ERROR_NOT_SUPPORTED;
        goto exit;
    }

    ret = mbedtls_cipher_setup(&operation->ctx.cipher, cipher_info);
    if (ret != 0)
    {
        goto exit;
    }

    if (PSA_KEY_TYPE_IS_AES(slot->attr.type) && (PSA_KEY_TYPE_IS_VENDOR_DEFINED(slot->attr.type)))
    {
        mbedtls_aes_context * p_aes_ctx = NULL;

        /* Setup the vendor context flag.
         * Even though vendor_ctx is a void pointer since we only need true/false info
         * we are using the pointer as a bool instead */
        p_aes_ctx             = (mbedtls_aes_context *) operation->ctx.cipher.cipher_ctx;
        p_aes_ctx->vendor_ctx = (bool *) true;

        operation->iv_size = SIZE_AES_BLOCK_BYTES;
    }
    else
    {
        status = PSA_ERROR_NOT_SUPPORTED;
        goto exit;
    }

  #if defined(MBEDTLS_DES_C)
    if ((slot->attr.type == PSA_KEY_TYPE_DES) && (key_bits == 128))
    {
        /* Two-key Triple-DES is 3-key Triple-DES with K1=K3 */
        uint8_t keys[24];
        memcpy(keys, slot->data.raw.data, 16);
        memcpy(keys + 16, slot->data.raw.data, 8);
        ret = mbedtls_cipher_setkey(&operation->ctx.cipher, keys, 192, cipher_operation);
    }
    else
  #endif
    {
        ret = mbedtls_cipher_setkey(&operation->ctx.cipher, slot->data.key.data, (int) key_bits, cipher_operation);
    }

    if (ret != 0)
    {
        goto exit;
    }

  #if defined(MBEDTLS_CIPHER_MODE_WITH_PADDING)
    switch (alg)
    {
        case PSA_ALG_CBC_NO_PADDING:
        {
            ret = mbedtls_cipher_set_padding_mode(&operation->ctx.cipher, MBEDTLS_PADDING_NONE);
            break;
        }

        case PSA_ALG_CBC_PKCS7:
        {
            ret = mbedtls_cipher_set_padding_mode(&operation->ctx.cipher, MBEDTLS_PADDING_PKCS7);
            break;
        }

        default:
        {
            /* The algorithm doesn't involve padding. */
            ret = 0;
            break;
        }
    }

    if (ret != 0)
    {
        goto exit;
    }
  #endif                                                                              // MBEDTLS_CIPHER_MODE_WITH_PADDING

    operation->key_set    = 1;
    operation->block_size = (uint8_t) (PSA_ALG_IS_STREAM_CIPHER(alg) ? 1 :
                                       PSA_BLOCK_CIPHER_BLOCK_SIZE(slot->attr.type)); // NOLINT(readability-uppercase-literal-suffix)
    if (alg & PSA_ALG_CIPHER_FROM_BLOCK_FLAG)
    {
        operation->iv_size = (uint8_t) PSA_BLOCK_CIPHER_BLOCK_SIZE(slot->attr.type);  // NOLINT(readability-uppercase-literal-suffix)
    }

  #if defined(MBEDTLS_CHACHA20_C)
    else if (alg == PSA_ALG_CHACHA20)
    {
        operation->iv_size = 12;
    }
  #endif
exit:
    if (status == 0)
    {
        status = mbedtls_to_psa_error(ret);
    }

    if (status != 0)
    {
        psa_cipher_abort(operation);
    }
 #endif                                // defined(MBEDTLS_AES_ALT)
    return status;
}

#endif                                 /* MBEDTLS_PSA_CRYPTO_ACCEL_DRV_C */
