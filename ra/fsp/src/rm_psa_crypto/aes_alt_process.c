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

#if defined(MBEDTLS_AES_C)

 #include <string.h>

 #include "mbedtls/aes.h"
 #include "mbedtls/platform.h"
 #include "mbedtls/platform_util.h"
 #if defined(MBEDTLS_PADLOCK_C)
  #include "mbedtls/padlock.h"
 #endif
 #if defined(MBEDTLS_AESNI_C)
  #include "mbedtls/aesni.h"
 #endif
 #include "hw_sce_aes_private.h"
 #include "hw_sce_private.h"

/*
 * 32-bit integer manipulation macros (little endian)
 */
 #ifndef GET_UINT32_LE
  #define GET_UINT32_LE(n, b, i)                 \
    {                                            \
        (n) = ((uint32_t) (b)[(i)])              \
              | ((uint32_t) (b)[(i) + 1] << 8)   \
              | ((uint32_t) (b)[(i) + 2] << 16)  \
              | ((uint32_t) (b)[(i) + 3] << 24); \
    }
 #endif

 #ifndef PUT_UINT32_LE
  #define PUT_UINT32_LE(n, b, i)                             \
    {                                                        \
        (b)[(i)]     = (unsigned char) (((n)) & 0xFF);       \
        (b)[(i) + 1] = (unsigned char) (((n) >> 8) & 0xFF);  \
        (b)[(i) + 2] = (unsigned char) (((n) >> 16) & 0xFF); \
        (b)[(i) + 3] = (unsigned char) (((n) >> 24) & 0xFF); \
    }
 #endif

/**
 * \brief          This function sets the decryption/decryption key.
 *
 * \param ctx      The AES context to which the key should be bound.
 *                 It must be initialized.
 * \param key      The decryption key.
 *                 This must be a readable buffer of size \p keybits bits.
 * \param keybits  The size of data passed. Valid options are:
 *                 <ul><li>128 bits</li>
 *                 <li>256 bits</li></ul>
 *
 * \return         \c 0 on success.
 * \return         #MBEDTLS_ERR_AES_INVALID_KEY_LENGTH on failure.
 */
 #if defined(MBEDTLS_AES_SETKEY_ENC_ALT) || defined(MBEDTLS_AES_SETKEY_DEC_ALT)
int aes_setkey_generic (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);
    int                   ret            = 0;
    unsigned int          local_keybits  = 0;
    const unsigned char * p_internal_key = key;
  #if BSP_FEATURE_CRYPTO_HAS_SCE9

    /* Create storage to hold the generated OEM key index. Size = Largest key size possible. */
    uint8_t encrypted_aes_key[SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED] = {0};
  #endif
    switch (keybits)
    {
        case SIZE_AES_128BIT_KEYLEN_BITS:
        {
  #if BSP_FEATURE_CRYPTO_HAS_SCE9
            local_keybits = SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED;
            ctx->nr       = 10;
            if (false == (bool) ctx->vendor_ctx)
            {
                p_internal_key = encrypted_aes_key;
                ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                                         SCE_OEM_CMD_AES128,
                                                                         NULL,
                                                                         NULL,
                                                                         key,
                                                                         (uint32_t *) p_internal_key);
                ctx->vendor_ctx = (bool *) true;
            }

  #else
            if (true == (bool) ctx->vendor_ctx)
            {
                local_keybits = SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED;
            }
            else
            {
                local_keybits = keybits;
            }
            ctx->nr = 10;
  #endif
            break;
        }

        case SIZE_AES_192BIT_KEYLEN_BITS:
        {
  #if BSP_FEATURE_CRYPTO_HAS_SCE9
            local_keybits = SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED;
            ctx->nr       = 12;
            if (false == (bool) ctx->vendor_ctx)
            {
                p_internal_key = encrypted_aes_key;
                ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                                         SCE_OEM_CMD_AES192,
                                                                         NULL,
                                                                         NULL,
                                                                         key,
                                                                         (uint32_t *) p_internal_key);
                ctx->vendor_ctx = (bool *) true;
            }

  #else
            if (true == (bool) ctx->vendor_ctx)
            {
                local_keybits = SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED;
            }
            else
            {
                local_keybits = keybits;
            }
            ctx->nr = 12;
  #endif
            break;
        }

        case SIZE_AES_256BIT_KEYLEN_BITS:
        {
  #if BSP_FEATURE_CRYPTO_HAS_SCE9
            local_keybits = SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED;
            ctx->nr       = 14;
            if (false == (bool) ctx->vendor_ctx)
            {
                p_internal_key = encrypted_aes_key;
                ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                                         SCE_OEM_CMD_AES256,
                                                                         NULL,
                                                                         NULL,
                                                                         key,
                                                                         (uint32_t *) p_internal_key);
                ctx->vendor_ctx = (bool *) true;
            }

  #else
            if (true == (bool) ctx->vendor_ctx)
            {
                local_keybits = SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED;
            }
            else
            {
                local_keybits = keybits;
            }
            ctx->nr = 14;
  #endif

            break;
        }

        default:

            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if (0 == ret)
    {
        ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;

        /* Store the encrypted key into the buffer */
        for (uint32_t i = 0; i < (local_keybits >> 5); i++)
        {
            /* buf is large enough to hold AES 192 bit wrapped key
             * (largest key due to 32 bit padding for differentiating it from 256 wrapped key)
             * */
            GET_UINT32_LE(ctx->buf[i], p_internal_key, i << 2);
        }
    }

    return ret;
}

 #endif                                // defined(MBEDTLS_AES_SETKEY_ENC_ALT) || defined(MBEDTLS_AES_SETKEY_DEC_ALT)

/*
 * AES key schedule (encryption)
 */
 #if defined(MBEDTLS_AES_SETKEY_ENC_ALT)
int mbedtls_aes_setkey_enc (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    return aes_setkey_generic(ctx, key, keybits);
}

 #endif                                /* !MBEDTLS_AES_SETKEY_ENC_ALT */

/*
 * AES key schedule (decryption)
 */
 #if defined(MBEDTLS_AES_SETKEY_DEC_ALT)
int mbedtls_aes_setkey_dec (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    return aes_setkey_generic(ctx, key, keybits);
}

 #endif                                /* !MBEDTLS_AES_SETKEY_DEC_ALT */

 #if defined(MBEDTLS_AES_ENCRYPT_ALT)

/*
 * AES-ECB block encryption
 * NOTE: The return code from this function is not checked by the mbedCrypto implementation,
 * so a failure here wont show up in the calling layer.
 */

int mbedtls_internal_aes_encrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    (void) output;
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
  #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_128EcbEncryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
  #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  #endif                               /* (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT))) */
        }
        else
        {
            err =
                HW_SCE_AES_128EcbEncrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }

  #if BSP_FEATURE_CRYPTO_HAS_SCE9
    else if (ctx->nr == 12)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_192EcbEncryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_192EcbEncrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }
  #endif
    else if (ctx->nr == 14)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
  #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_256EcbEncryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
  #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  #endif
        }
        else
        {
            err =
                HW_SCE_AES_256EcbEncrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }
    else
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #if BSP_FEATURE_CRYPTO_HAS_SCE9

int mbedtls_internal_aes_encrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    (void) output;
    fsp_err_t err = FSP_SUCCESS;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128CbcEncryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192CbcEncryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256CbcEncryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #else

int mbedtls_internal_aes_encrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    (void) output;
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_128CbcEncryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif                              /* (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT))) */
        }
        else
        {
            err =
                HW_SCE_AES_128CbcEncrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else if (ctx->nr == 14)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_256CbcEncryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_256CbcEncrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #endif                               /* BSP_FEATURE_CRYPTO_HAS_SCE9 */
 #endif                                /* !MBEDTLS_AES_ENCRYPT_ALT */

/*
 * AES-ECB block decryption
 * NOTE: The return code from this function is not checked by the mbedCrypto implementation,
 * so a failure here wont show up in the calling layer.
 */
 #if defined(MBEDTLS_AES_DECRYPT_ALT)

int mbedtls_internal_aes_decrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
  #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_128EcbDecryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
  #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  #endif
        }
        else
        {
            err =
                HW_SCE_AES_128EcbDecrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }

  #if BSP_FEATURE_CRYPTO_HAS_SCE9
    else if (ctx->nr == 12)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_192EcbDecryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_192EcbDecrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }
  #endif
    else if (ctx->nr == 14)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
  #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_256EcbDecryptUsingEncryptedKey(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0]);
  #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  #endif
        }
        else
        {
            err =
                HW_SCE_AES_256EcbDecrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0],
                                         (uint32_t *) &output[0]);
        }
    }
    else
    {
        ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (0 == ret))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #if BSP_FEATURE_CRYPTO_HAS_SCE9

int mbedtls_internal_aes_decrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    fsp_err_t err = FSP_SUCCESS;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128CbcDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192CbcDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256CbcDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else
    {
        ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (0 == ret))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #else

int mbedtls_internal_aes_decrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_128CbcDecryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_128CbcDecrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else if (ctx->nr == 14)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_256CbcDecryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_256CbcDecrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else
    {
        ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (0 == ret))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #endif                               /* BSP_FEATURE_CRYPTO_HAS_SCE9 */
 #endif                                /* !MBEDTLS_AES_DECRYPT_ALT */

 #if defined(MBEDTLS_AES_DECRYPT_ALT) || defined(MBEDTLS_AES_ENCRYPT_ALT)

  #if BSP_FEATURE_CRYPTO_HAS_SCE9
int mbedtls_internal_aes_encrypt_decrypt_ctr (mbedtls_aes_context * ctx,
                                              unsigned int          length,
                                              unsigned char       * iv,
                                              const unsigned char * input,
                                              unsigned char       * output)
{
    fsp_err_t err = FSP_SUCCESS;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128CtrEncryptDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192CtrEncryptDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256CtrEncryptDecryptInitSubGeneral(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdate((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else
    {
        ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (0 == ret))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #else
int mbedtls_internal_aes_encrypt_decrypt_ctr (mbedtls_aes_context * ctx,
                                              unsigned int          length,
                                              unsigned char       * iv,
                                              const unsigned char * input,
                                              unsigned char       * output)
{
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret = 0;

    if (ctx->nr == 10)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_128CtrEncryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_128CtrEncrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else if (ctx->nr == 14)
    {
        if (true == (bool) ctx->vendor_ctx)
        {
   #if (1 == BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED) && \
            ((PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(PSA_CRYPTO_CFG_AES_FORMAT)))
            err =
                HW_SCE_AES_256CtrEncryptUsingEncryptedKey(ctx->buf,
                                                          (uint32_t *) &iv[0],
                                                          (length / 4U),
                                                          (uint32_t *) &input[0],
                                                          (uint32_t *) &output[0],
                                                          (uint32_t *) &iv[0]);
   #else
            ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
   #endif
        }
        else
        {
            err =
                HW_SCE_AES_256CtrEncrypt(ctx->buf, (uint32_t *) &iv[0], (length / 4U), (uint32_t *) &input[0],
                                         (uint32_t *) &output[0], (uint32_t *) &iv[0]);
        }
    }
    else
    {
        ret = MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    if ((FSP_SUCCESS != err) && (0 == ret))
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    return ret;
}

  #endif
 #endif                                /* !MBEDTLS_AES_DECRYPT_ALT */

#endif                                 /* MBEDTLS_AES_C */
