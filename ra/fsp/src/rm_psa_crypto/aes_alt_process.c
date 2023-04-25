/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include "common.h"

#if defined(MBEDTLS_AES_C)

 #if defined(MBEDTLS_AES_ALT)

  #include <string.h>

  #include "mbedtls/aes.h"
  #include "mbedtls/platform.h"
  #include "mbedtls/platform_util.h"
  #include "mbedtls/error.h"
  #if defined(MBEDTLS_PADLOCK_C)
   #include "mbedtls/padlock.h"
  #endif
  #if defined(MBEDTLS_AESNI_C)
   #include "mbedtls/aesni.h"
  #endif
  #include "hw_sce_aes_private.h"
  #include "hw_sce_private.h"
  #include "hw_sce_ra_private.h"

/*
 * 32-bit integer manipulation macros (little endian)
 */
  #ifndef GET_UINT32_LE
   #define GET_UINT32_LE(n, b, i)                \
    {                                            \
        (n) = ((uint32_t) (b)[(i)])              \
              | ((uint32_t) (b)[(i) + 1] << 8)   \
              | ((uint32_t) (b)[(i) + 2] << 16)  \
              | ((uint32_t) (b)[(i) + 3] << 24); \
    }
  #endif

  #ifndef PUT_UINT32_LE
   #define PUT_UINT32_LE(n, b, i)                            \
    {                                                        \
        (b)[(i)]     = (unsigned char) (((n)) & 0xFF);       \
        (b)[(i) + 1] = (unsigned char) (((n) >> 8) & 0xFF);  \
        (b)[(i) + 2] = (unsigned char) (((n) >> 16) & 0xFF); \
        (b)[(i) + 3] = (unsigned char) (((n) >> 24) & 0xFF); \
    }
  #endif

  #if defined(MBEDTLS_CIPHER_MODE_XTS)
   #if !(BSP_FEATURE_BSP_HAS_SCE_ON_RA2)
int aes_xts_setkey_generic (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);
    int                   ret            = 0;
    unsigned int          local_keybits  = 0;
    const unsigned char * p_internal_key = key;

    /* Create storage to hold the generated OEM key index. Size = Largest key size possible. */
    uint8_t encrypted_aes_key[SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED] = {0};

    switch (keybits)
    {
        case HW_SCE_AES128XTS_KEY_BIT_SIZE:
        {
            local_keybits = SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED;
            ctx->nr       = 10;
            if (false == (bool) ctx->vendor_ctx)
            {
                p_internal_key = encrypted_aes_key;
                ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                                         SCE_OEM_CMD_AES128_XTS,
                                                                         NULL,
                                                                         NULL,
                                                                         key,
                                                                         (uint32_t *) p_internal_key);
                ctx->vendor_ctx = (bool *) true;
            }

            break;
        }

        case HW_SCE_AES256XTS_KEY_BIT_SIZE:
        {
            local_keybits = SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED;
            ctx->nr       = 14;
            if (false == (bool) ctx->vendor_ctx)
            {
                p_internal_key = encrypted_aes_key;
                ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                                         SCE_OEM_CMD_AES256_XTS,
                                                                         NULL,
                                                                         NULL,
                                                                         key,
                                                                         (uint32_t *) p_internal_key);
                ctx->vendor_ctx = (bool *) true;
            }

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

   #endif
  #endif                               // defined(MBEDTLS_AES_SETKEY_ENC_ALT) || defined(MBEDTLS_AES_SETKEY_DEC_ALT)

  #if defined(MBEDTLS_AES_SETKEY_ENC_ALT) || defined(MBEDTLS_AES_SETKEY_DEC_ALT)
int aes_setkey_generic (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);
    int                   ret            = 0;
    unsigned int          local_keybits  = 0;
    const unsigned char * p_internal_key = key;
   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE5B || BSP_FEATURE_CRYPTO_HAS_SCE5 || \
    BSP_FEATURE_CRYPTO_HAS_SCE7

    /* Create storage to hold the generated OEM key index. Size = Largest key size possible. */
    uint8_t encrypted_aes_key[SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED] = {0};
   #endif
    switch (keybits)
    {
        case SIZE_AES_128BIT_KEYLEN_BITS:
        {
   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE5B || BSP_FEATURE_CRYPTO_HAS_SCE5 || \
            BSP_FEATURE_CRYPTO_HAS_SCE7
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
   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE5B || BSP_FEATURE_CRYPTO_HAS_SCE5 || \
            BSP_FEATURE_CRYPTO_HAS_SCE7
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
   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE5B || BSP_FEATURE_CRYPTO_HAS_SCE5 || \
            BSP_FEATURE_CRYPTO_HAS_SCE7
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

  #endif

/*
 * AES key schedule (encryption)
 */
  #if defined(MBEDTLS_AES_SETKEY_ENC_ALT)
int mbedtls_aes_setkey_enc (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    return aes_setkey_generic(ctx, key, keybits);
}

  #endif                               /* !MBEDTLS_AES_SETKEY_ENC_ALT */

/*
 * AES key schedule (decryption)
 */
  #if defined(MBEDTLS_AES_SETKEY_DEC_ALT)
int mbedtls_aes_setkey_dec (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    return aes_setkey_generic(ctx, key, keybits);
}

  #endif                               /* !MBEDTLS_AES_SETKEY_DEC_ALT */

  #if defined(MBEDTLS_CIPHER_MODE_XTS)

   #if BSP_FEATURE_BSP_HAS_SCE_ON_RA2
static int mbedtls_aes_xts_decode_keys (const unsigned char  * key,
                                        unsigned int           keybits,
                                        const unsigned char ** key1,
                                        unsigned int         * key1bits,
                                        const unsigned char ** key2,
                                        unsigned int         * key2bits)
{
    const unsigned int half_keybits  = keybits / 2;
    const unsigned int half_keybytes = half_keybits / 8;

    switch (keybits)
    {
        case HW_SCE_AES128XTS_KEY_BIT_SIZE:
        {}
        break;

        case HW_SCE_AES256XTS_KEY_BIT_SIZE:
        {}
        break;

        default:

            return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }

    *key1bits = half_keybits;
    *key2bits = half_keybits;
    *key1     = &key[0];
    *key2     = &key[half_keybytes];

    return 0;
}

   #endif

int mbedtls_aes_xts_setkey_enc (mbedtls_aes_xts_context * ctx, const unsigned char * key, unsigned int keybits)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    (void) ctx;
    (void) key;
    (void) keybits;

   #if !(BSP_FEATURE_BSP_HAS_SCE_ON_RA2)
    ret = aes_xts_setkey_generic(&ctx->tweak, key, keybits);
    if (ret != 0)
    {
        return ret;
    }
   #endif

   #if BSP_FEATURE_BSP_HAS_SCE_ON_RA2
    const unsigned char * key1;
    const unsigned char * key2;
    unsigned int          key1bits;
    unsigned int          key2bits;

    ret = mbedtls_aes_xts_decode_keys(key, keybits, &key1, &key1bits, &key2, &key2bits);
    if (ret != 0)
    {
        return ret;
    }

    /* Set the tweak key. Always set tweak key for the encryption mode. */
    ret = mbedtls_aes_setkey_enc(&ctx->tweak, key2, key2bits);
    if (ret != 0)
    {
        return ret;
    }

    /* Set crypt key for encryption. */
    ret = mbedtls_aes_setkey_enc(&ctx->crypt, key1, key1bits);
   #endif

    return ret;
}

int mbedtls_aes_xts_setkey_dec (mbedtls_aes_xts_context * ctx, const unsigned char * key, unsigned int keybits)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    (void) ctx;
    (void) key;
    (void) keybits;

   #if !(BSP_FEATURE_BSP_HAS_SCE_ON_RA2)
    ret = aes_xts_setkey_generic(&ctx->tweak, key, keybits);
    if (ret != 0)
    {
        return ret;
    }
   #endif

   #if BSP_FEATURE_BSP_HAS_SCE_ON_RA2
    const unsigned char * key1;
    const unsigned char * key2;
    unsigned int          key1bits;
    unsigned int          key2bits;

    ret = mbedtls_aes_xts_decode_keys(key, keybits, &key1, &key1bits, &key2, &key2bits);
    if (ret != 0)
    {
        return ret;
    }

    /* Set the tweak key. Always set tweak key for encryption. */
    ret = mbedtls_aes_setkey_enc(&ctx->tweak, key2, key2bits);
    if (ret != 0)
    {
        return ret;
    }

    /* Set crypt key for decryption. */
    ret = mbedtls_aes_setkey_dec(&ctx->crypt, key1, key1bits);
   #endif

    return ret;
}

  #endif                               /* MBEDTLS_CIPHER_MODE_XTS */

  #if defined(MBEDTLS_AES_ENCRYPT_ALT)

/*
 * AES-ECB block encryption
 * NOTE: The return code from this function is not checked by the mbedCrypto implementation,
 * so a failure here wont show up in the calling layer.
 */
int mbedtls_internal_aes_encrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    (void) output;
    fsp_err_t err             = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret             = 0;
    uint32_t  dummy_iv[4]     = {0};
    uint32_t  indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t  indata_key_type = 0;

    FSP_PARAMETER_NOT_USED(dummy_iv);
    FSP_PARAMETER_NOT_USED(indata_cmd);
    FSP_PARAMETER_NOT_USED(input);
    FSP_PARAMETER_NOT_USED(indata_key_type);

    if (ctx->nr == 10)
    {
        err =
            HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();
    }

   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7
    else if (ctx->nr == 12)
    {
        err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes192EncryptDecryptFinalSub();
    }
   #endif
    else if (ctx->nr == 14)
    {
        err = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes256EncryptDecryptFinalSub();
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

int mbedtls_internal_aes_encrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    (void) output;
    fsp_err_t err             = FSP_SUCCESS;
    int       ret             = 0;
    uint32_t  indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION);
    uint32_t  indata_key_type = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
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

   #if !(BSP_FEATURE_BSP_HAS_SCE_ON_RA2)
int mbedtls_internal_aes_encrypt_xts (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      const unsigned char * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    (void) length;
    (void) input;
    (void) output;
    fsp_err_t err = FSP_SUCCESS;
    int       ret = 0;

    uint32_t bitlen          = 0;
    uint32_t text_bitlen     = length * 8;
    uint32_t input_data_size = 0;
    uint32_t copy_size       = 0;
    uint8_t  local_input[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];
    uint8_t  local_output[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128XtsEncryptInitSub(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        if ((text_bitlen % HW_SCE_AES_BLOCK_BIT_SIZE) == 0)
        {
            HW_SCE_Aes128XtsEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, length >> 2);

            bitlen = change_endian_long(0U);

            err = HW_SCE_Aes128XtsEncryptFinalSub(&bitlen, (uint32_t *) input, (uint32_t *) output);
            if (err == 0U)
            {
                /* Once final is successful, change operation state back to SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT to allow same AES key to
                 * be used for subsequent operations */
                ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;
            }
            else
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
        }
        else
        {
            if (text_bitlen < HW_SCE_AES_BLOCK_BIT_SIZE)
            {
                input_data_size = 0;
                memcpy(local_input, input, length);
                bitlen = change_endian_long(HW_SCE_AES_BLOCK_BIT_SIZE);
            }
            else if (text_bitlen > (HW_SCE_AES_BLOCK_BIT_SIZE * 2))
            {
                copy_size = length % HW_SCE_AES_BLOCK_BYTE_SIZE;
                if (copy_size == 0)
                {
                    copy_size = HW_SCE_AES_BLOCK_BYTE_SIZE;
                }

                memcpy(local_input,
                       input + ((text_bitlen / HW_SCE_AES_BLOCK_BIT_SIZE - 1) * HW_SCE_AES_BLOCK_BYTE_SIZE),
                       copy_size + HW_SCE_AES_BLOCK_BYTE_SIZE);

                input_data_size = text_bitlen / HW_SCE_AES_BLOCK_BIT_SIZE - 1;

                HW_SCE_Aes128XtsEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, input_data_size << 2);

                bitlen = change_endian_long(text_bitlen - (input_data_size * HW_SCE_AES_BLOCK_BIT_SIZE));
            }
            else
            {
                input_data_size = 0;
                memcpy(local_input, input, length);
                bitlen = change_endian_long(text_bitlen);
            }

            err = HW_SCE_Aes128XtsEncryptFinalSub(&bitlen, (uint32_t *) local_input, (uint32_t *) local_output);
            if (err == 0U)
            {
                /* Once final is successful, change operation state back to SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT to allow same AES key to
                 * be used for subsequent operations */
                ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;
                memcpy((output + (input_data_size * HW_SCE_AES_BLOCK_BYTE_SIZE)), local_output, length);
            }
            else
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
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

   #endif
  #endif                               /* !MBEDTLS_AES_ENCRYPT_ALT */

/*
 * AES-ECB block decryption
 * NOTE: The return code from this function is not checked by the mbedCrypto implementation,
 * so a failure here wont show up in the calling layer.
 */
  #if defined(MBEDTLS_AES_DECRYPT_ALT)

int mbedtls_internal_aes_decrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    fsp_err_t err             = FSP_ERR_CRYPTO_UNKNOWN;
    int       ret             = 0;
    uint32_t  dummy_iv[4]     = {0};
    uint32_t  indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_DECRYPTION);
    uint32_t  indata_key_type = 0;

    FSP_PARAMETER_NOT_USED(dummy_iv);
    FSP_PARAMETER_NOT_USED(indata_cmd);
    FSP_PARAMETER_NOT_USED(input);
    FSP_PARAMETER_NOT_USED(output);
    FSP_PARAMETER_NOT_USED(indata_key_type);

    if (ctx->nr == 10)
    {
        err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();
    }

   #if BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7
    else if (ctx->nr == 12)
    {
        err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes192EncryptDecryptFinalSub();
    }
   #endif
    else if (ctx->nr == 14)
    {
        err = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], SIZE_AES_BLOCK_WORDS);
        }

        err = HW_SCE_Aes256EncryptDecryptFinalSub();
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

int mbedtls_internal_aes_decrypt_cbc (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      unsigned char       * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    fsp_err_t err             = FSP_SUCCESS;
    int       ret             = 0;
    uint32_t  indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_DECRYPTION);
    uint32_t  indata_key_type = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
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

   #if !(BSP_FEATURE_BSP_HAS_SCE_ON_RA2)
int mbedtls_internal_aes_decrypt_xts (mbedtls_aes_context * ctx,
                                      unsigned int          length,
                                      const unsigned char * iv,
                                      const unsigned char * input,
                                      unsigned char       * output)
{
    fsp_err_t err = FSP_SUCCESS;
    int       ret = 0;

    uint32_t bitlen          = 0;
    uint32_t text_bitlen     = length * 8;
    uint32_t input_data_size = 0;
    uint32_t copy_size       = 0;
    uint8_t  local_input[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];
    uint8_t  local_output[HW_SCE_AES_BLOCK_BYTE_SIZE * 2];

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128XtsDecryptInitSub(ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        if ((text_bitlen % HW_SCE_AES_BLOCK_BIT_SIZE) == 0)
        {
            HW_SCE_Aes128XtsDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, length >> 2);

            bitlen = change_endian_long(0);
            err    = HW_SCE_Aes128XtsDecryptFinalSub(&bitlen, (uint32_t *) input, (uint32_t *) output);
            if (err == 0U)
            {
                /* Once final is successful, change operation state back to SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT to allow same AES key to
                 * be used for subsequent operations */
                ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;
            }
            else
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
        }
        else
        {
            if (text_bitlen < HW_SCE_AES_BLOCK_BIT_SIZE)
            {
                input_data_size = 0;
                memcpy(local_input, input, HW_SCE_AES_BLOCK_BYTE_SIZE);
                bitlen = change_endian_long(HW_SCE_AES_BLOCK_BIT_SIZE);
            }
            else if (text_bitlen > (HW_SCE_AES_BLOCK_BIT_SIZE * 2))
            {
                copy_size = length % HW_SCE_AES_BLOCK_BYTE_SIZE;
                if (copy_size == 0)
                {
                    copy_size = HW_SCE_AES_BLOCK_BYTE_SIZE;
                }

                memcpy(local_input,
                       input + ((text_bitlen / HW_SCE_AES_BLOCK_BIT_SIZE - 1) * HW_SCE_AES_BLOCK_BYTE_SIZE),
                       copy_size + HW_SCE_AES_BLOCK_BYTE_SIZE);

                input_data_size = text_bitlen / HW_SCE_AES_BLOCK_BIT_SIZE - 1;

                HW_SCE_Aes128XtsDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, input_data_size << 2);

                bitlen = change_endian_long(text_bitlen - (input_data_size * HW_SCE_AES_BLOCK_BIT_SIZE));
            }
            else
            {
                input_data_size = 0;
                memcpy(local_input, input, HW_SCE_AES_BLOCK_BYTE_SIZE * 2);
                bitlen = change_endian_long(text_bitlen);
            }

            err = HW_SCE_Aes128XtsDecryptFinalSub(&bitlen, (uint32_t *) local_input, (uint32_t *) local_output);
            if (err == 0U)
            {
                /* Once final is successful, change operation state back to SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT to allow same AES key to
                 * be used for subsequent operations */
                ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;
                memcpy((output + (input_data_size * HW_SCE_AES_BLOCK_BYTE_SIZE)), local_output, length);
            }
            else
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
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

   #endif
  #endif                               /* !MBEDTLS_AES_DECRYPT_ALT */

  #if defined(MBEDTLS_AES_DECRYPT_ALT) || defined(MBEDTLS_AES_ENCRYPT_ALT)

int mbedtls_internal_aes_encrypt_decrypt_ctr (mbedtls_aes_context * ctx,
                                              unsigned int          length,
                                              unsigned char       * iv,
                                              const unsigned char * input,
                                              unsigned char       * output)
{
    fsp_err_t err             = FSP_SUCCESS;
    int       ret             = 0;
    uint32_t  indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION);
    uint32_t  indata_key_type = 0;

    if (ctx->nr == 10)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 12)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
    }
    else if (ctx->nr == 14)
    {
        if (SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT == ctx->state)
        {
            err = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, ctx->buf, (uint32_t *) &iv[0]);
            if (FSP_SUCCESS != err)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }

            ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_UPDATE;
        }

        HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) &input[0], (uint32_t *) &output[0], (length / 4U));
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

int mbedtls_internal_aes_crypt_ctr_finish (mbedtls_aes_context * ctx)
{
    fsp_err_t ret        = FSP_SUCCESS;
    int       key_rounds = ctx->nr;

    if (10 == key_rounds)
    {
        ret = HW_SCE_Aes128EncryptDecryptFinalSub();
    }
    else if (12 == key_rounds)
    {
        ret = HW_SCE_Aes192EncryptDecryptFinalSub();
    }
    else if (14 == key_rounds)
    {
        ret = HW_SCE_Aes256EncryptDecryptFinalSub();
    }
    else
    {
        return -1;
    }

    if (FSP_SUCCESS != ret)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    /* Once final is successful, change operation state back to SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT to allow same AES key to
     * be used for subsequent operations */
    ctx->state = SCE_MBEDTLS_CIPHER_OPERATION_STATE_INIT;

    return 0;
}

  #endif                               /* !MBEDTLS_AES_DECRYPT_ALT */
 #endif /* MBEDTLS_AES_ALT */
#endif                                 /* MBEDTLS_AES_C */
