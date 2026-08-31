/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/* UNCRUSTIFY-OFF */

#include "common.h"

#if defined(MBEDTLS_CHACHA20_C)

#include "mbedtls/chacha20.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <stddef.h>
#include <string.h>

#include "mbedtls/platform.h"

#if defined(MBEDTLS_CHACHA20_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "chacha20_alt.h"
  #include "platform_alt.h"

/*
 * 32-bit integer manipulation macros (little endian)
 */
  #ifndef GET_UINT32_LE
#define GET_UINT32_LE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ]       )             \
        | ( (uint32_t) (b)[(i) + 1] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 2] << 16 )             \
        | ( (uint32_t) (b)[(i) + 3] << 24 );            \
    }
  #endif

int mbedtls_internal_chacha20_setkey(mbedtls_chacha20_context *ctx,
                                     const unsigned char key[HW_SCE_CHACHA20_KEY_BYTE_SIZE])
{
    FSP_ASSERT(ctx);
    FSP_ASSERT(key);
    int ret = 0;
    const unsigned char * p_internal_key = key;

    /* Create storage to hold the generated OEM key index. Size = Largest key size possible. */
    uint8_t encrypted_chacha20_key[SIZE_CHACHA20_256BIT_KEYLEN_BITS_WRAPPED] = {0};

    p_internal_key = encrypted_chacha20_key;
    ret            = (int) HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                                             SCE_OEM_CMD_CHACHA20_POLY_1305,
                                                             NULL,
                                                             NULL,
                                                             key,
                                                             (uint32_t *) p_internal_key);
    if (0 == ret)
    {
        /* Store the encrypted key into the state */
        for (uint32_t i = 0; i < SIZE_CHACHA20_256BIT_KEYLEN_WORDS_WRAPPED; i++)
        {
            GET_UINT32_LE(ctx->internal_key[i], p_internal_key, i << 2);
        }
    }

    return ret;
}

int mbedtls_internal_chacha20_update(mbedtls_chacha20_context * ctx,
                                     const unsigned char * input,
                                     unsigned char * output,
                                     size_t size)
{
    fsp_err_t err                = FSP_SUCCESS;
    uint32_t indata_key_type[1] = {0x00000000};

    err = HW_SCE_Chacha20InitSub(indata_key_type,
                                 &ctx->internal_key[0],
                                 NULL,
                                 &ctx->state[12],
                                 &ctx->state[13],
                                 (uint32_t const *) &size);
    if(FSP_SUCCESS != err)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    HW_SCE_Chacha20UpdateSub(NULL, (uint32_t *)  output, 0);

    err = HW_SCE_Chacha20FinalSub((uint32_t *) input, (uint32_t *) output, BYTES_TO_WORDS(size));

    return err;
}

#endif /* MBEDTLS_CHACHA20_ALT */
#endif /* !MBEDTLS_CHACHA20_C */
