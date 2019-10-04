/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
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

/* AES key lengths defined for SCE operations. */
#define SIZE_AES_128BIT_KEYLEN_BITS     (128)
#define SIZE_AES_128BIT_KEYLEN_BYTES    ((SIZE_AES_128BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_128BIT_KEYLEN_WORDS    ((SIZE_AES_128BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_192BIT_KEYLEN_BITS     (192)
#define SIZE_AES_192BIT_KEYLEN_BYTES    ((SIZE_AES_192BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_192BIT_KEYLEN_WORDS    ((SIZE_AES_192BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_256BIT_KEYLEN_BITS     (256)
#define SIZE_AES_256BIT_KEYLEN_BYTES    ((SIZE_AES_256BIT_KEYLEN_BITS) / 8)
#define SIZE_AES_256BIT_KEYLEN_WORDS    ((SIZE_AES_256BIT_KEYLEN_BITS) / 32)

#define SIZE_AES_BLOCK_BITS             (128)
#define SIZE_AES_BLOCK_WORDS            ((SIZE_AES_BLOCK_BITS) / 32)
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

/*
 * AES key schedule (encryption)
 */
#if defined(MBEDTLS_AES_SETKEY_ENC_ALT)
int mbedtls_aes_setkey_enc (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);

    switch (keybits)
    {
    case SIZE_AES_128BIT_KEYLEN_BITS:
    {
        ctx->nr = 10;
        break;
    }

    case SIZE_AES_192BIT_KEYLEN_BITS:
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    case SIZE_AES_256BIT_KEYLEN_BITS:
    {
        ctx->nr = 14;
        break;
    }

    default:

        return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }

    /*Store the key into the buffer*/
    for (uint32_t i = 0; i < (keybits >> 5); i++)
    {
        GET_UINT32_LE(ctx->buf[i], key, i << 2);
    }

    return 0;
}

#endif                                /* !MBEDTLS_AES_SETKEY_ENC_ALT */

/*
 * AES key schedule (decryption)
 */
#if defined(MBEDTLS_AES_SETKEY_DEC_ALT)
int mbedtls_aes_setkey_dec (mbedtls_aes_context * ctx, const unsigned char * key, unsigned int keybits)
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);

    switch (keybits)
    {
    case SIZE_AES_128BIT_KEYLEN_BITS:
    {
        ctx->nr = 10;
        break;
    }

    case SIZE_AES_192BIT_KEYLEN_BITS:
    {
        return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
    }

    case SIZE_AES_256BIT_KEYLEN_BITS:
    {
        ctx->nr = 14;
        break;
    }

    default:

        return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }

    /*Store the key into the buffer*/
    for (uint32_t i = 0; i < (keybits >> 5); i++)
    {
        GET_UINT32_LE(ctx->buf[i], key, i << 2);
    }

    return 0;
}

#if defined(MBEDTLS_CIPHER_MODE_XTS)
#error "XTS not supported currently in hardware"
#endif

#endif                                /* !MBEDTLS_AES_SETKEY_DEC_ALT */

#if defined(MBEDTLS_AES_ENCRYPT_ALT)
int mbedtls_internal_aes_encrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;
    if (ctx->nr == 10)
    {
        err = HW_SCE_AES_128EcbEncrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0], (uint32_t *) &output[0]);
    }
    else if (ctx->nr == 14)
    {
        err = HW_SCE_AES_256EcbEncrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0], (uint32_t *) &output[0]);;
    }
    else
    {
        // ctx->nr == 12 : 192 bit case
        return (MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED);
    }

    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    return (0);
}

#endif                                /* !MBEDTLS_AES_ENCRYPT_ALT */

/*
 * AES-ECB block decryption
 */
#if defined(MBEDTLS_AES_DECRYPT_ALT)
int mbedtls_internal_aes_decrypt (mbedtls_aes_context * ctx, const unsigned char input[16], unsigned char output[16])
{
    fsp_err_t err = FSP_ERR_CRYPTO_UNKNOWN;

    if (ctx->nr == 10)
    {
        err = HW_SCE_AES_128EcbDecrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0], (uint32_t *) &output[0]);
    }
    else if (ctx->nr == 14)
    {
        err = HW_SCE_AES_256EcbDecrypt(ctx->buf, SIZE_AES_BLOCK_WORDS, (uint32_t *) &input[0], (uint32_t *) &output[0]);
    }
    else
    {
        // ctx->nr == 12 : 192 bit case
        return (MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED);
    }
    if (FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    return (0);
}

#endif                                /* !MBEDTLS_AES_DECRYPT_ALT */

#endif                                 /* MBEDTLS_AES_C */
