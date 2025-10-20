/**
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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

#ifdef MBEDTLS_CHACHA20_ALT
#include "chacha20_alt.h"

void mbedtls_chacha20_init(mbedtls_chacha20_context *ctx)
{
    mbedtls_platform_zeroize(ctx->state, sizeof(ctx->state));
    mbedtls_platform_zeroize(ctx->keystream8, sizeof(ctx->keystream8));
    mbedtls_platform_zeroize(ctx->internal_state, sizeof(ctx->internal_state));

    /* Initially, there's no keystream bytes available */
    ctx->keystream_bytes_used = CHACHA20_BLOCK_SIZE_BYTES;
}

void mbedtls_chacha20_free(mbedtls_chacha20_context *ctx)
{
    if (ctx != NULL) {
        mbedtls_platform_zeroize(ctx, sizeof(mbedtls_chacha20_context));
    }
}

int mbedtls_chacha20_setkey(mbedtls_chacha20_context *ctx,
                            const unsigned char key[32])
{
    /* ChaCha20 constants - the string "expand 32-byte k" */
    ctx->state[0] = 0x61707865;
    ctx->state[1] = 0x3320646e;
    ctx->state[2] = 0x79622d32;
    ctx->state[3] = 0x6b206574;

    /* Set key */
    ctx->state[4]  = MBEDTLS_GET_UINT32_LE(key, 0);
    ctx->state[5]  = MBEDTLS_GET_UINT32_LE(key, 4);
    ctx->state[6]  = MBEDTLS_GET_UINT32_LE(key, 8);
    ctx->state[7]  = MBEDTLS_GET_UINT32_LE(key, 12);
    ctx->state[8]  = MBEDTLS_GET_UINT32_LE(key, 16);
    ctx->state[9]  = MBEDTLS_GET_UINT32_LE(key, 20);
    ctx->state[10] = MBEDTLS_GET_UINT32_LE(key, 24);
    ctx->state[11] = MBEDTLS_GET_UINT32_LE(key, 28);

    return 0;
}

int mbedtls_chacha20_starts(mbedtls_chacha20_context *ctx,
                            const unsigned char nonce[12],
                            uint32_t counter)
{
    /* Counter */
    ctx->state[12] = counter;

    /* Nonce */
    ctx->state[13] = MBEDTLS_GET_UINT32_BE(nonce, 0);
    ctx->state[14] = MBEDTLS_GET_UINT32_BE(nonce, 4);
    ctx->state[15] = MBEDTLS_GET_UINT32_BE(nonce, 8);
    mbedtls_platform_zeroize(ctx->keystream8, sizeof(ctx->keystream8));

    /* Initially, there's no keystream bytes available */
    ctx->keystream_bytes_used = CHACHA20_BLOCK_SIZE_BYTES;

    return 0;
}

int mbedtls_chacha20_update(mbedtls_chacha20_context *ctx,
                            size_t size,
                            const unsigned char *input,
                            unsigned char *output)
{
    int ret = MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    
    if (size == 0) {
        return 0;
    }
    
    size_t offset = CHACHA20_BLOCK_SIZE_BYTES - ctx->keystream_bytes_used;
    size_t remain_bytes = 0;
    size_t processed = 0;
    
    /* Use leftover keystream bytes */
    if (ctx->keystream_bytes_used < CHACHA20_BLOCK_SIZE_BYTES && size > 0) {
        size_t copy_size = (size < offset) ? size : offset;
        
        unsigned char input_tmp[CHACHA20_BLOCK_SIZE_BYTES] = {0};
        unsigned char output_tmp[CHACHA20_BLOCK_SIZE_BYTES] = {0};
        
        memcpy(input_tmp, ctx->keystream8, ctx->keystream_bytes_used);
        memcpy(input_tmp + ctx->keystream_bytes_used, input, copy_size);
        
        ret = mbedtls_internal_chacha20_update(ctx, input_tmp, output_tmp, CHACHA20_BLOCK_SIZE_BYTES);
        if (ret != 0) {
            return ret;
        }
        
        memcpy(output, output_tmp + ctx->keystream_bytes_used, copy_size);
        processed = copy_size;
        
        // Reset keystream
        if (copy_size == offset) {
            ctx->keystream_bytes_used = 0;
            ctx->state[12] += 1;
        } else {
            ctx->keystream_bytes_used += copy_size;
            return 0;
        }
    }
    
    size_t remaining_size = size - processed;
    
    /* Process full blocks */
    if (remaining_size >= CHACHA20_BLOCK_SIZE_BYTES) {
        size_t full_blocks_size = (remaining_size / CHACHA20_BLOCK_SIZE_BYTES) * CHACHA20_BLOCK_SIZE_BYTES;
        
        ret = mbedtls_internal_chacha20_update(ctx, 
                                             input + processed, 
                                             output + processed, 
                                             full_blocks_size);
        if (ret != 0) {
            return ret;
        }
        
        ctx->state[12] += (uint32_t)(full_blocks_size / CHACHA20_BLOCK_SIZE_BYTES);
        processed += full_blocks_size;
        remaining_size -= full_blocks_size;
    }
    
    /* Last (partial) block */
    if (remaining_size > 0) {
        unsigned char output_tmp[CHACHA20_BLOCK_SIZE_BYTES] = {0};
        
        ret = mbedtls_internal_chacha20_update(ctx, 
                                             input + processed, 
                                             output_tmp, 
                                             CHACHA20_BLOCK_SIZE_BYTES);
        if (ret != 0) {
            return ret;
        }
        
        memcpy(output + processed, output_tmp, remaining_size);
        memset(&ctx->keystream8[0], 0, CHACHA20_BLOCK_SIZE_BYTES);
        memcpy(ctx->keystream8, input + processed, remaining_size);
        ctx->keystream_bytes_used = remaining_size;
    }
    
    return 0;
}

int mbedtls_chacha20_crypt(const unsigned char key[32],
                           const unsigned char nonce[12],
                           uint32_t counter,
                           size_t data_len,
                           const unsigned char *input,
                           unsigned char *output)
{
    mbedtls_chacha20_context ctx;
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    mbedtls_chacha20_init(&ctx);

    ret = mbedtls_chacha20_setkey(&ctx, key);
    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_chacha20_starts(&ctx, nonce, counter);
    if (ret != 0) {
        goto cleanup;
    }

    ret = mbedtls_chacha20_update(&ctx, data_len, input, output);

cleanup:
    mbedtls_chacha20_free(&ctx);
    return ret;
}

#endif /* MBEDTLS_CHACHA20_ALT */
#endif /* !MBEDTLS_CHACHA20_C */
