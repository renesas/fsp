/*
 * This file is a copy of the sha3.c file from mbedCrypto
 * It has been modified to work with Renesas Secure Crypto Engine.
 *  \file sha3_alt.c
 *  FIPS-202 compliant SHA3 implementation
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

/*
 *  The SHA-3 Secure Hash Standard was published by NIST in 2015.
 *
 *  https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.202.pdf
 */

/* UNCRUSTIFY-OFF */

#include "common.h"

#if defined(MBEDTLS_SHA3_C)

#include "mbedtls/sha3.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <string.h>

#if defined(MBEDTLS_SHA3_ALT)

void mbedtls_sha3_init(mbedtls_sha3_context *ctx)
{
    memset(ctx, 0, sizeof(mbedtls_sha3_context));
}

void mbedtls_sha3_free(mbedtls_sha3_context *ctx)
{
    if (ctx == NULL) {
        return;
    }

    mbedtls_platform_zeroize(ctx, sizeof(mbedtls_sha3_context));
}

void mbedtls_sha3_clone(mbedtls_sha3_context *dst,
                        const mbedtls_sha3_context *src)
{
    *dst = *src;
}

/*
 * SHA-3 context setup
 */
int mbedtls_sha3_starts(mbedtls_sha3_context *ctx, mbedtls_sha3_id id)
{
    switch (id) {
        case MBEDTLS_SHA3_224:
            ctx->olen = 224 / 8;
            ctx->max_block_size = 1152 / 8;
            ctx->sha3_type = MBEDTLS_SHA3_224;
            break;
        case MBEDTLS_SHA3_256:
            ctx->olen = 256 / 8;
            ctx->max_block_size = 1088 / 8;
            ctx->sha3_type = MBEDTLS_SHA3_256;
            break;
        case MBEDTLS_SHA3_384:
            ctx->olen = 384 / 8;
            ctx->max_block_size = 832 / 8;
            ctx->sha3_type = MBEDTLS_SHA3_384;
            break;
        case MBEDTLS_SHA3_512:
            ctx->olen = 512 / 8;
            ctx->max_block_size = 576 / 8;
            ctx->sha3_type = MBEDTLS_SHA3_512;
            break;
        default:
            return MBEDTLS_ERR_SHA3_BAD_INPUT_DATA;
    }

    ctx->total[0] = 0;
    ctx->total[1] = 0;
    memset(ctx->state, 0, sizeof(ctx->state));
    ctx->index = 0;
    ctx->sce_operation_state = SCE_OEM_CMD_HASH_INIT_TO_SUSPEND;

    return 0;
}

/*
 * SHA-3 process buffer
 */
int mbedtls_sha3_update(mbedtls_sha3_context *ctx,
    const uint8_t *input,
    size_t ilen)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t fill;
    unsigned int left;
    uint32_t     sha3_block_size;
    uint32_t     sha3_block_aligned_size;
    uint32_t     sha3_block_aligned_size_mod;

    if (ilen == 0) {
        return 0;
    }

    left = (unsigned int) (ctx->total[0] % ctx->max_block_size);
    fill = ctx->max_block_size - left;
    ctx->total[0] += (uint32_t) ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint64_t) ilen) {
        ctx->total[1]++;
    }

    if (left && ilen >= fill) {
        memcpy((void *) (ctx->buffer + left), input, fill);

        input += fill;
        ilen  -= fill;
        left   = 0;

        /* If there is data in the rsip_buffer that must be processed first before the ctx buffer. */
        if ((1U == ctx->use_rsip_buffer) && (0U == ctx->rsip_buffer_processed))
        {
            if ((ret =
                     mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer,
                        ctx->max_block_size)) != 0)
            {
                return ret;
            }

            ctx->rsip_buffer_processed = 1U;
            ctx->use_rsip_buffer       = 0U;
        }

        /* Process the data in the ctx buffer. */
        if ((ret =
                 mbedtls_internal_sha3_process_ext(ctx, ctx->buffer, ctx->max_block_size)) != 0)
        {
            return ret;
        }
    }

    if (ilen >= ctx->max_block_size)
    {
        sha3_block_aligned_size_mod = ilen / ctx->max_block_size;
        sha3_block_aligned_size     = sha3_block_aligned_size_mod;
        ilen = ilen - (sha3_block_aligned_size_mod * ctx->max_block_size);

        /* Check to see if there will be unaligned data to be buffered.
         * If there is no unaligned data to be buffered, then in case of the RSIP_E51A,
         * 128 bytes (SHA512 block size) of data will be buffered and processed when the finish() is called. */

        /* If all the data is aligned, copy over the final 128 bytes for later processing. */
        if (ilen > 0)
        {
            /* If there was previously buffered data in this buffer, process that first. */
            if ((1U == ctx->use_rsip_buffer) && (0U == ctx->rsip_buffer_processed))
            {
                if ((ret =
                         mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer,
                            ctx->max_block_size)) != 0)
                {
                    return ret;
                }

                ctx->rsip_buffer_processed = 1U;
                ctx->use_rsip_buffer       = 0U;
            }

            ctx->rsip_buffer_processed = 1U;
            ctx->use_rsip_buffer       = 0U;
        }
        else
        {
            if ((1U == ctx->use_rsip_buffer) && (0U == ctx->rsip_buffer_processed))
            {
                if ((ret =
                         mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer,
                            ctx->max_block_size)) != 0)
                {
                    return ret;
                }

                ctx->rsip_buffer_processed = 1U;
                ctx->use_rsip_buffer       = 0U;
            }

            uint32_t final_block_start = (sha3_block_aligned_size_mod * ctx->max_block_size) -
            ctx->max_block_size;
            memcpy(ctx->rsip_buffer, input + final_block_start, ctx->max_block_size);
            sha3_block_aligned_size_mod -= 1U;
            ctx->use_rsip_buffer           = 1U;
            ctx->rsip_buffer_processed     = 0U;
        }

        if ((ilen > ctx->max_block_size) || (sha3_block_aligned_size_mod > 0U))
        {
            if ((ret =
                     mbedtls_internal_sha3_process_ext(ctx,
                                                         input,
                                                         sha3_block_aligned_size_mod *
                                                         ctx->max_block_size)) != 0)
            {
                return ret;
            }

            input += (sha3_block_aligned_size * ctx->max_block_size);
        }
    }

    if (ilen > 0)
    {
        memcpy((void *) (ctx->buffer + left), input, ilen);
    }

    return 0;
}

int mbedtls_sha3_finish(mbedtls_sha3_context *ctx,
     uint8_t *output, size_t olen)
{
    int      ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    unsigned used;

    used = ctx->total[0] % ctx->max_block_size;

    /* If there is no unaligned data in the context buffer. */
    if (0 == used)
    {
        /* If there is aligned data buffered in the rsip buffer, process that.*/
        if ((1U == ctx->use_rsip_buffer) && (0U == ctx->rsip_buffer_processed))
        {
            if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == ctx->sce_operation_state)
            {
                ctx->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
            }
            else if (SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND == ctx->sce_operation_state)
            {
                ctx->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_FINAL;
            }

            if ((ret =
                     mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer,
                        ctx->max_block_size)) != 0)
            {
                goto exit;
            }

            ctx->rsip_buffer_processed = 1U;
            ctx->use_rsip_buffer       = 0U;
        }
        else
        {
            /* If there is no data in the unaligned ctx buffer and no data in the aligned buffer
             * then this is case of 0 total length passed in. */
            ctx->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
            if ((ret = mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer, 0)) != 0)
            {
                goto exit;
            }
        }
    }
    else
    {
        if ((1U == ctx->use_rsip_buffer) && (0U == ctx->rsip_buffer_processed))
        {
            if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND != ctx->sce_operation_state)
            {
                ctx->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND;
            }

            if ((ret =
                     mbedtls_internal_sha3_process_ext(ctx, ctx->rsip_buffer,
                        ctx->max_block_size)) != 0)
            {
                goto exit;
            }

            ctx->rsip_buffer_processed = 1U;
            ctx->use_rsip_buffer       = 0U;
        }

        if (SCE_OEM_CMD_HASH_INIT_TO_SUSPEND == ctx->sce_operation_state)
        {
            ctx->sce_operation_state = SCE_OEM_CMD_HASH_ONESHOT;
        }
        else
        {
            ctx->sce_operation_state = SCE_OEM_CMD_HASH_RESUME_TO_FINAL;
        }

        if ((ret = mbedtls_internal_sha3_process_ext(ctx, ctx->buffer, used)) != 0)
        {
            goto exit;
        }
    }

    /*
     * Output final state
     */
    switch (ctx->sha3_type)
    {
        case MBEDTLS_SHA3_512:
        {
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[7])) + 4)), output, 60);
            MBEDTLS_PUT_UINT32_BE(ctx->state[7], output, 56);
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[6])) + 4)), output, 52);
            MBEDTLS_PUT_UINT32_BE(ctx->state[6], output, 48);
        }

        case MBEDTLS_SHA3_384:
        {
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[5])) + 4)), output, 44);
            MBEDTLS_PUT_UINT32_BE(ctx->state[5], output, 40);
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[4])) + 4)), output, 36);
            MBEDTLS_PUT_UINT32_BE(ctx->state[4], output, 32);
        }

        case MBEDTLS_SHA3_256:
        {
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[3])) + 4)), output, 28);
        }

        case MBEDTLS_SHA3_224:
        {
            MBEDTLS_PUT_UINT32_BE(ctx->state[3], output, 24);
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[2])) + 4)), output, 20);
            MBEDTLS_PUT_UINT32_BE(ctx->state[2], output, 16);
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[1])) + 4)), output, 12);
            MBEDTLS_PUT_UINT32_BE(ctx->state[1], output, 8);
            MBEDTLS_PUT_UINT32_BE(*((uint32_t *)(((uint8_t *)&(ctx->state[0])) + 4)), output, 4);
            MBEDTLS_PUT_UINT32_BE(ctx->state[0], output, 0);

            break;
        }

        default:

            ret = MBEDTLS_ERR_SHA3_BAD_INPUT_DATA;
            goto exit;
    }

    ret = 0;

exit:
    mbedtls_sha3_free(ctx);
    return ret;
}

/*
 * output = SHA-3( input buffer )
 */
int mbedtls_sha3(mbedtls_sha3_id id, const uint8_t *input,
                 size_t ilen, uint8_t *output, size_t olen)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_sha3_context ctx;

    mbedtls_sha3_init(&ctx);

    /* Sanity checks are performed in every mbedtls_sha3_xxx() */
    if ((ret = mbedtls_sha3_starts(&ctx, id)) != 0) {
        goto exit;
    }

    if ((ret = mbedtls_sha3_update(&ctx, input, ilen)) != 0) {
        goto exit;
    }

    if ((ret = mbedtls_sha3_finish(&ctx, output, olen)) != 0) {
        goto exit;
    }

exit:
    mbedtls_sha3_free(&ctx);

    return ret;
}
#endif /* MBEDTLS_SHA3_ALT */
#endif /* MBEDTLS_SHA3_C */
