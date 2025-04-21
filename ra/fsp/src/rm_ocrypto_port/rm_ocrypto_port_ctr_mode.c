/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ocrypto_port_aes_helpers.h"
#include "ocrypto_aes_ctr.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
void ocrypto_aes_ctr_init (ocrypto_aes_ctr_ctx * ctx, const uint8_t * key, size_t size, const uint8_t iv[16])
{
    if (key)
    {
        memcpy(ctx->xkey, key, size);
        ctx->key_size = (uint8_t) size;
    }

    if (iv)
    {
        memcpy(ctx->counter, iv, sizeof(ctx->counter));
    }
}

void ocrypto_aes_ctr_update (ocrypto_aes_ctr_ctx * ctx, uint8_t * ct, const uint8_t * pt, size_t pt_len)
{
    uint32_t  sce_cmd   = change_endian_long(SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION);
    uint8_t * p_in      = (uint8_t *) pt;
    uint8_t * p_out     = ct;
    uint32_t  num_loops = 1U;

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if (pt_len == 0)
    {
        return;
    }
#endif

    /* Handle full block size chunks */
    if ((!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &pt[0]) || !OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &ct[0])) &&
        (pt_len >= OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES))
    {
        uint32_t local_out[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t local_in[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS]  = {0U};
        num_loops = pt_len / OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->counter[0]);

        for (uint32_t i = 0; i < num_loops; i++)
        {
            memcpy(local_in, p_in, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            ocrypto_aes_helper_update(ctx->key_size, &local_in[0], &local_out[0], OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS);

            memcpy(p_out, (uint8_t *) local_out, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            p_in  += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
            p_out += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        }
    }
    else if (pt_len >= OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES)
    {
        uint32_t local_len =
            (uint32_t) ((pt_len / OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) * OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->counter[0]);
        ocrypto_aes_helper_update(ctx->key_size, (uint32_t *) &pt[0], (uint32_t *) &ct[0],
                                  OCRYPTO_PORT_BYTES_TO_WORDS(local_len));
    }
    else
    {
        /* Do nothing */
    }

    /* Now handle any remainder data bytes less than a block size */
    uint32_t remainder_length = (pt_len % OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
    if (remainder_length)
    {
        uint32_t local_out[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t local_in[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS]  = {0U};
        uint32_t remainder_index = ((pt_len / OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) * OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
        memcpy(local_in, &pt[remainder_index], remainder_length);
        ocrypto_aes_helper_update(ctx->key_size, &local_in[0], &local_out[0], OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS);
        memcpy(&ct[remainder_index], &local_out[0], remainder_length);
    }
}

void ocrypto_aes_ctr_encrypt (uint8_t       * ct,
                              const uint8_t * pt,
                              size_t          pt_len,
                              const uint8_t * key,
                              size_t          size,
                              const uint8_t   iv[16])
{
    ocrypto_aes_ctr_ctx ctx = {0};
    ocrypto_aes_ctr_init(&ctx, key, size, iv);
    ocrypto_aes_ctr_update(&ctx, ct, pt, pt_len);
}

void ocrypto_aes_ctr_decrypt (uint8_t       * pt,
                              const uint8_t * ct,
                              size_t          ct_len,
                              const uint8_t * key,
                              size_t          size,
                              const uint8_t   iv[16])
{
    ocrypto_aes_ctr_ctx ctx = {0};
    ocrypto_aes_ctr_init(&ctx, key, size, iv);
    ocrypto_aes_ctr_update(&ctx, pt, ct, ct_len);
}
