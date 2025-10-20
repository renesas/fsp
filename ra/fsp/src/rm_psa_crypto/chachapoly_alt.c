/**
 * \file chachapoly_alt.c
 *
 * \brief ChaCha20-Poly1305 AEAD construction based on RFC 7539.
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#include "common.h"

#if defined(MBEDTLS_CHACHAPOLY_C)

#include "mbedtls/chachapoly.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"
#include "mbedtls/constant_time.h"

#include <string.h>

#include "mbedtls/platform.h"

#ifdef MBEDTLS_CHACHAPOLY_ALT
#include "mbedtls/chacha20.h"
#include "chachapoly_alt.h"

/**
 * \brief           Adds nul bytes to pad the AAD for Poly1305.
 *
 * \param ctx       The ChaCha20-Poly1305 context.
 */
static int chachapoly_pad_aad(mbedtls_chachapoly_context *ctx)
{
    uint32_t partial_block_len = (uint32_t) (ctx->aad_len % 16U);
    unsigned char zeroes[15];

    if (partial_block_len == 0U) {
        return 0;
    }

    memset(zeroes, 0, sizeof(zeroes));

    return mbedtls_poly1305_update(&ctx->poly1305_ctx,
                                   zeroes,
                                   16U - partial_block_len);
}

/**
 * \brief           Adds nul bytes to pad the ciphertext for Poly1305.
 *
 * \param ctx       The ChaCha20-Poly1305 context.
 */
static int chachapoly_pad_ciphertext(mbedtls_chachapoly_context *ctx)
{
    uint32_t partial_block_len = (uint32_t) (ctx->ciphertext_len % 16U);
    unsigned char zeroes[15];

    if (partial_block_len == 0U) {
        return 0;
    }

    memset(zeroes, 0, sizeof(zeroes));
    return mbedtls_poly1305_update(&ctx->poly1305_ctx,
                                   zeroes,
                                   16U - partial_block_len);
}

void mbedtls_chachapoly_init(mbedtls_chachapoly_context *ctx)
{
    mbedtls_chacha20_init(&ctx->chacha20_ctx);
    mbedtls_poly1305_init(&ctx->poly1305_ctx);
    mbedtls_platform_zeroize(ctx->internal_state, sizeof(ctx->internal_state));
    ctx->aad_len        = 0U;
    ctx->ciphertext_len = 0U;
    ctx->state          = CHACHAPOLY_STATE_INIT;
    ctx->mode           = MBEDTLS_CHACHAPOLY_ENCRYPT;

    /*Internal initialization*/
    memset(ctx->indata_aad, 0 , sizeof(ctx->indata_aad));
}

void mbedtls_chachapoly_free(mbedtls_chachapoly_context *ctx)
{
    if (ctx == NULL) {
        return;
    }

    mbedtls_chacha20_free(&ctx->chacha20_ctx);
    mbedtls_poly1305_free(&ctx->poly1305_ctx);
    ctx->aad_len        = 0U;
    ctx->ciphertext_len = 0U;
    ctx->state          = CHACHAPOLY_STATE_INIT;
    ctx->mode           = MBEDTLS_CHACHAPOLY_ENCRYPT;

    /*Internal initialization*/
    memset(ctx->indata_aad, 0 , sizeof(ctx->indata_aad));
}

int mbedtls_chachapoly_setkey(mbedtls_chachapoly_context *ctx,
                              const unsigned char key[32])
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    ret = mbedtls_chacha20_setkey(&ctx->chacha20_ctx, key);

    return ret;
}

int mbedtls_chachapoly_starts(mbedtls_chachapoly_context *ctx,
                              const unsigned char nonce[12],
                              mbedtls_chachapoly_mode_t mode)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    unsigned char poly1305_key[64];

    /* Set counter = 0, will be update to 1 when generating Poly1305 key */
    ret = mbedtls_chacha20_starts(&ctx->chacha20_ctx, nonce, 0U);
    if (ret != 0) {
        goto cleanup;
    }

    /* Generate the Poly1305 key by getting the ChaCha20 keystream output with
     * counter = 0.  This is the same as encrypting a buffer of zeroes.
     * Only the first 256-bits (32 bytes) of the key is used for Poly1305.
     * The other 256 bits are discarded.
     */
    memset(poly1305_key, 0, sizeof(poly1305_key));
        ret = mbedtls_chacha20_update(&ctx->chacha20_ctx, sizeof(poly1305_key),
                                  poly1305_key, poly1305_key);
    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_poly1305_starts(&ctx->poly1305_ctx, poly1305_key);

    if (ret == 0) {
        ctx->aad_len        = 0U;
        ctx->ciphertext_len = 0U;
        ctx->state          = CHACHAPOLY_STATE_AAD;
        ctx->mode           = mode;
    }

cleanup:
    mbedtls_platform_zeroize(poly1305_key, 64U);
    return ret;
}

int mbedtls_chachapoly_update_aad(mbedtls_chachapoly_context *ctx,
                                  const unsigned char *aad,
                                  size_t aad_len)
{
    if (ctx->state != CHACHAPOLY_STATE_AAD) {
        return MBEDTLS_ERR_CHACHAPOLY_BAD_STATE;
    }

    if (0 != mbedtls_poly1305_update(&ctx->poly1305_ctx, aad, aad_len))
    {
        return MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    }

    if ((aad == NULL) || (aad_len == 0)) {
        return 0;
    }

    if (ctx->aad_len + aad_len > SIZE_CHACHAPOLY_IN_DATA_AAD_LEN_BYTES) {
        return MBEDTLS_ERR_CHACHAPOLY_BAD_STATE;
    }

    uint32_t offset = (uint32_t) ctx->aad_len;
    uint32_t word_idx = offset >> 2;
    uint32_t words = (uint32_t) (aad_len >> 2);

    for (uint32_t i = 0; i < words; i++)
    {
        uint32_t w = MBEDTLS_GET_UINT32_LE(aad, (size_t)(i << 2));
        ((uint32_t *) ctx->indata_aad)[word_idx + i] = w;
    }

    ctx->aad_len += aad_len;

    return 0;
}

int mbedtls_chachapoly_update(mbedtls_chachapoly_context *ctx,
                              size_t len,
                              const unsigned char *input,
                              unsigned char *output)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    if ((ctx->state != CHACHAPOLY_STATE_AAD) &&
        (ctx->state != CHACHAPOLY_STATE_CIPHERTEXT)) {
        return MBEDTLS_ERR_CHACHAPOLY_BAD_STATE;
    }

    ret = mbedtls_internal_chachapoly_update(ctx, input , output, len);
    if (ret != 0) {
    	return ret;
    }

    if (ctx->state == CHACHAPOLY_STATE_AAD) {
        ctx->state = CHACHAPOLY_STATE_CIPHERTEXT;
    }

    return ret;
}

int mbedtls_chachapoly_finish(mbedtls_chachapoly_context *ctx,
                              unsigned char mac[16])
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    unsigned char len_block[16];

    if (ctx->state == CHACHAPOLY_STATE_INIT) {
        return MBEDTLS_ERR_CHACHAPOLY_BAD_STATE;
    }

    if (ctx->state == CHACHAPOLY_STATE_AAD) {
        ret = chachapoly_pad_aad(ctx);
        if (ret != 0) {
            return ret;
        }
    } else if (ctx->state == CHACHAPOLY_STATE_CIPHERTEXT) {
        ret = chachapoly_pad_ciphertext(ctx);
        if (ret != 0) {
            return ret;
        }
    }

    /* The lengths of the AAD and ciphertext are processed by
     * Poly1305 as the final 128-bit block, encoded as little-endian integers.
     */
    MBEDTLS_PUT_UINT64_LE(ctx->aad_len, len_block, 0);
    MBEDTLS_PUT_UINT64_LE(ctx->ciphertext_len, len_block, 8);

    if (ctx->state == CHACHAPOLY_STATE_CIPHERTEXT)
    {
        ret = mbedtls_internal_chachapoly_finish(ctx, mac);
    }
    else
    {
        ret = mbedtls_poly1305_update(&ctx->poly1305_ctx, len_block, 16U);
        if (ret != 0) {
            return ret;
        }

        ret = mbedtls_poly1305_finish(&ctx->poly1305_ctx, mac);
    }
    
    ctx->state = CHACHAPOLY_STATE_FINISHED;

    return ret;
}

static int chachapoly_crypt_and_tag(mbedtls_chachapoly_context *ctx,
                                    mbedtls_chachapoly_mode_t mode,
                                    size_t length,
                                    const unsigned char nonce[12],
                                    const unsigned char *aad,
                                    size_t aad_len,
                                    const unsigned char *input,
                                    unsigned char *output,
                                    unsigned char tag[16])
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    ret = mbedtls_chachapoly_starts(ctx, nonce, mode);
    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_chachapoly_update_aad(ctx, aad, aad_len);

    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_chachapoly_update(ctx, length, input, output);
    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_chachapoly_finish(ctx, tag);

cleanup:
    return ret;
}

int mbedtls_chachapoly_encrypt_and_tag(mbedtls_chachapoly_context *ctx,
                                       size_t length,
                                       const unsigned char nonce[12],
                                       const unsigned char *aad,
                                       size_t aad_len,
                                       const unsigned char *input,
                                       unsigned char *output,
                                       unsigned char tag[16])
{
    return chachapoly_crypt_and_tag(ctx, MBEDTLS_CHACHAPOLY_ENCRYPT,
                                    length, nonce, aad, aad_len,
                                    input, output, tag);
}

int mbedtls_chachapoly_auth_decrypt(mbedtls_chachapoly_context *ctx,
                                    size_t length,
                                    const unsigned char nonce[12],
                                    const unsigned char *aad,
                                    size_t aad_len,
                                    const unsigned char tag[16],
                                    const unsigned char *input,
                                    unsigned char *output)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    if ((ret = chachapoly_crypt_and_tag(ctx,
                                        MBEDTLS_CHACHAPOLY_DECRYPT, length, nonce,
                                        aad, aad_len, input, output, (unsigned char *) tag)) != 0) {
        return ret;
    }


    return 0;
}

#endif /* MBEDTLS_CHACHAPOLY_ALT */
#endif /* MBEDTLS_CHACHAPOLY_C */
