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

#if defined(MBEDTLS_CHACHAPOLY_C)

#include "mbedtls/chacha20.h"
#include "mbedtls/chachapoly.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <stddef.h>
#include <string.h>

#include "mbedtls/platform.h"

#if defined(MBEDTLS_CHACHAPOLY_ALT)
  #include "hw_sce_private.h"
  #include "hw_sce_aes_private.h"
  #include "hw_sce_ra_private.h"
  #include "chachapoly_alt.h"
  #include "platform_alt.h"

int mbedtls_internal_chachapoly_update(mbedtls_chachapoly_context * ctx,
                                       const unsigned char      * input,
                                       unsigned char            * output,
                                       size_t                     size)
{
    fsp_err_t ret = MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    uint32_t InData_Key_Type[1] = {change_endian_long(0x00000001)};
    uint32_t InData_Cmd[1] = {0}; /* Encrypt */
    uint32_t init_size[1] = {UINT32_MAX};
    int32_t full_blocks = 0U;
    uint32_t remaining_bytes = (uint32_t) size;
    uint32_t offset_bytes = 0U;
    uint32_t internal_state[CHACHA20_BLOCK_SIZE_WORDS];
    unsigned char input_block[CHACHA20_BLOCK_SIZE_BYTES] = {0};
    unsigned char output_block[CHACHA20_BLOCK_SIZE_BYTES] = {0};

    if (MBEDTLS_CHACHAPOLY_DECRYPT == ctx->mode)
    {
        InData_Cmd[0] = 1U; /* Decrypt */
    }

    switch (ctx->state)
    {
    case CHACHAPOLY_STATE_AAD:
        if (ctx->aad_len == 0U)
        {
            ret = HW_SCE_Chacha20Poly1305InitSub(&InData_Key_Type[0],
                                                NULL,
                                                &ctx->chacha20_ctx.state[4],
                                                &InData_Cmd[0],
                                                &ctx->chacha20_ctx.state[13],
                                                (uint32_t *) &init_size[0],
                                                (uint32_t *) &ctx->aad_len);
            if(FSP_SUCCESS != ret)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
            HW_SCE_Chacha20Poly1305UpdateTransitionSub();
        }
        else
        {
            ret = HW_SCE_Chacha20Poly1305InitSub(&InData_Key_Type[0],
                                                NULL,
                                                &ctx->chacha20_ctx.state[4],
                                                &InData_Cmd[0],
                                                &ctx->chacha20_ctx.state[13],
                                                (uint32_t *) &init_size[0],
                                                (uint32_t *) &ctx->aad_len);
            if(FSP_SUCCESS != ret)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
            HW_SCE_Chacha20Poly1305UpdateAADSub((uint32_t *) &ctx->indata_aad[0], BYTES_TO_WORDS(ctx->aad_len));
            HW_SCE_Chacha20Poly1305UpdateTransitionSub();
        }
        break;
    case CHACHAPOLY_STATE_CIPHERTEXT:
        if(ctx->ciphertext_len % 64 + size <= CHACHA20_BLOCK_SIZE_BYTES)
        {
            ctx->ciphertext_len += (uint32_t) size;
            memcpy(&ctx->chacha20_ctx.keystream8[ctx->internal_state[1]], input, size);
            ret = HW_SCE_Chacha20Poly1305ResumeSub(&InData_Key_Type[0],
                                                    NULL,
                                                    &ctx->chacha20_ctx.state[4],
                                                    &InData_Cmd[0],
                                                    &ctx->chacha20_ctx.state[13],
                                                    &ctx->internal_state[0]);
            if(FSP_ERR_CRYPTO_SCE_PASS_2 != ret)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
            HW_SCE_Chacha20Poly1305UpdateSub((uint32_t *) &ctx->chacha20_ctx.keystream8[0], (uint32_t *) output_block, CHACHA20_BLOCK_SIZE_WORDS);
            memcpy(output, output_block, remaining_bytes);
            HW_SCE_Chacha20Poly1305SuspendSub(&internal_state[0]);
            return 0;
        }
        else
        {
            /* Use leftover keystream bytes */
            offset_bytes = CHACHA20_BLOCK_SIZE_BYTES - (ctx->ciphertext_len % CHACHA20_BLOCK_SIZE_BYTES);
            remaining_bytes -= offset_bytes;
            memcpy(input_block, (uint32_t *) &ctx->chacha20_ctx.keystream8[0], CHACHA20_BLOCK_SIZE_BYTES - offset_bytes);
            memcpy(input_block + CHACHA20_BLOCK_SIZE_BYTES - offset_bytes, input, offset_bytes);

            ret = HW_SCE_Chacha20Poly1305ResumeSub(&InData_Key_Type[0],
                                                    NULL,
                                                    &ctx->chacha20_ctx.state[4],
                                                    &InData_Cmd[0],
                                                    &ctx->chacha20_ctx.state[13],
                                                    &ctx->internal_state[0]);
            if(FSP_ERR_CRYPTO_SCE_PASS_2 != ret)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
            HW_SCE_Chacha20Poly1305UpdateSub((uint32_t *) input_block, (uint32_t *) output_block, CHACHA20_BLOCK_SIZE_WORDS);
            memcpy(output, output_block + CHACHA20_BLOCK_SIZE_BYTES - offset_bytes, offset_bytes);

            ret = HW_SCE_Chacha20Poly1305SuspendSub(&ctx->internal_state[0]);
            if(FSP_SUCCESS != ret)
            {
                return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
            }
            ret = HW_SCE_Chacha20Poly1305ResumeSub(&InData_Key_Type[0],
                                                    NULL,
                                                    &ctx->chacha20_ctx.state[4],
                                                    &InData_Cmd[0],
                                                    &ctx->chacha20_ctx.state[13],
                                                    &ctx->internal_state[0]);
        }
        break;
    default:
        break;
    }

    /* Full blocks process */
    full_blocks = (size - offset_bytes) / CHACHA20_BLOCK_SIZE_BYTES;
    if (full_blocks > 0)
    {
        uint32_t MAX_CNT = 0;
        if (size - offset_bytes > full_blocks * CHACHA20_BLOCK_SIZE_BYTES) {
            MAX_CNT = full_blocks * CHACHA20_BLOCK_SIZE_WORDS;
        } else {
            MAX_CNT = (full_blocks - 1) * CHACHA20_BLOCK_SIZE_WORDS;
        }
        HW_SCE_Chacha20Poly1305UpdateSub((uint32_t *) (input + offset_bytes), (uint32_t *)  (output + offset_bytes), MAX_CNT);
        offset_bytes += MAX_CNT * 4;
        remaining_bytes -= MAX_CNT * 4U;
    }
    /* Prepare last block state */
    ret = HW_SCE_Chacha20Poly1305SuspendSub(&ctx->internal_state[0]);
    if(FSP_SUCCESS != ret)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }
    ret = HW_SCE_Chacha20Poly1305ResumeSub(&InData_Key_Type[0],
                                            NULL,
                                            &ctx->chacha20_ctx.state[4],
                                            &InData_Cmd[0],
                                            &ctx->chacha20_ctx.state[13],
                                            &ctx->internal_state[0]);
    if(FSP_ERR_CRYPTO_SCE_PASS_2 != ret)
    {
        return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    }

    /* Last block process */
    memcpy(input_block, input + offset_bytes, remaining_bytes);
    memset(&ctx->chacha20_ctx.keystream8[0], 0, CHACHA20_BLOCK_SIZE_BYTES);
    memcpy(&ctx->chacha20_ctx.keystream8[0], input + offset_bytes, remaining_bytes);
    HW_SCE_Chacha20Poly1305UpdateSub((uint32_t *) input_block, (uint32_t *)  output_block, CHACHA20_BLOCK_SIZE_WORDS);
    memcpy(output + offset_bytes, output_block, remaining_bytes);
    HW_SCE_Chacha20Poly1305SuspendSub(&internal_state[0]);

    ctx->ciphertext_len += (uint32_t) size;

    return 0;
}

int mbedtls_internal_chachapoly_finish(mbedtls_chachapoly_context * ctx,
                                       unsigned char mac[16])
{
    fsp_err_t ret = MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
    uint32_t InData_Key_Type[1] = {change_endian_long(0x00000001)};
    uint32_t InData_Cmd[1] = {0};
    uint32_t InData_TextLen[1] = {CHACHA20_BLOCK_SIZE_BYTES};
    uint32_t internal_block[CHACHA20_BLOCK_SIZE_WORDS] = {0};
    uint32_t internal_mac[CHACHA20_BLOCK_SIZE_WORDS] = {0};

    ctx->internal_state[1] = (uint32_t) ctx->ciphertext_len % 64;
    ctx->internal_state[8] = (uint32_t) ctx->ciphertext_len;

    if(MBEDTLS_CHACHAPOLY_DECRYPT == ctx->mode)
    {
        InData_Cmd[0] = 1U; /* Decrypt */
        HW_SCE_Chacha20Poly1305ResumeSub (&InData_Key_Type[0],
                                          NULL,
                                          &ctx->chacha20_ctx.state[4],
                                          &InData_Cmd[0],
                                          &ctx->chacha20_ctx.state[13],
                                          &ctx->internal_state[0]);
        ret = HW_SCE_Chacha20Poly1305FinalSub((uint32_t *) &ctx->chacha20_ctx.keystream8[0],
                                          	  (uint32_t *) mac,
                                              &internal_block[0],
                                              &internal_mac[0], change_endian_long(BYTES_TO_WORDS(ctx->internal_state[1])));
        if(FSP_SUCCESS != ret)
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }
    else
    {
        InData_Cmd[0] = 0U; /* Encrypt */
        HW_SCE_Chacha20Poly1305ResumeSub (&InData_Key_Type[0],
                                          NULL,
                                          &ctx->chacha20_ctx.state[4],
                                          &InData_Cmd[0],
                                          &ctx->chacha20_ctx.state[13],
                                          &ctx->internal_state[0]);
        ret = HW_SCE_Chacha20Poly1305FinalSub((uint32_t *) &ctx->chacha20_ctx.keystream8[0],
                                              &internal_mac[0],
                                              &internal_block[0],
                                              (uint32_t *) mac, change_endian_long(BYTES_TO_WORDS(ctx->internal_state[1])));
        if(FSP_SUCCESS != ret)
        {
            return MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
        }
    }

    return 0;
}
#endif /* MBEDTLS_CHACHAPOLY_ALT */
#endif /* !MBEDTLS_CHACHAPOLY_C */
