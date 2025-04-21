/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ocrypto_port_aes_helpers.h"
#include "ocrypto_aes_cbc.h"
#include "ocrypto_constant_time.h"
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
void ocrypto_aes_cbc_init_enc (ocrypto_aes_cbc_ctx * ctx, const uint8_t * key, size_t size, const uint8_t iv[16])
{
    if (key)
    {
        memcpy(ctx->xkey, key, size);
        ctx->key_size = (uint8_t) size;
    }

    if (iv)
    {
        memcpy(ctx->iv, iv, sizeof(ctx->iv));
    }
}

void ocrypto_aes_cbc_init_dec (ocrypto_aes_cbc_ctx * ctx, const uint8_t * key, size_t size, const uint8_t iv[16])
{
    if (key)
    {
        memcpy(ctx->xkey, key, size);
        ctx->key_size = (uint8_t) size;
    }

    if (iv)
    {
        memcpy(ctx->iv, iv, sizeof(ctx->iv));
    }
}

void ocrypto_aes_cbc_update_enc (ocrypto_aes_cbc_ctx * ctx, uint8_t * ct, const uint8_t * pt, size_t pt_len)
{
    uint32_t  sce_cmd = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION);
    uint8_t * p_pt    = (uint8_t *) pt;
    uint8_t * p_ct    = ct;

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (ct == NULL) || (pt == NULL) || (pt_len == 0) ||
        ((pt_len % OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) != 0))
    {
        return;
    }
#endif

    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &pt[0]) || !OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &ct[0]))
    {
        uint32_t local_ct[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t local_pt[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t num_loops = pt_len / OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->iv[0]);

        for (uint32_t i = 0; i < num_loops; i++)
        {
            memcpy(local_pt, p_pt, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            ocrypto_aes_helper_update(ctx->key_size, &local_pt[0], &local_ct[0], OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS);

            memcpy(p_ct, (uint8_t *) local_ct, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            p_pt += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
            p_ct += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        }
    }
    else
    {
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->iv[0]);
        ocrypto_aes_helper_update(ctx->key_size, (uint32_t *) &pt[0], (uint32_t *) &ct[0],
                                  OCRYPTO_PORT_BYTES_TO_WORDS(pt_len));
    }

    // save last output block
    ocrypto_constant_time_copy(ctx->iv, &ct[pt_len - OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES], sizeof(ctx->iv));
}

void ocrypto_aes_cbc_update_dec (ocrypto_aes_cbc_ctx * ctx, uint8_t * pt, const uint8_t * ct, size_t ct_len)
{
    uint32_t  sce_cmd = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_DECRYPTION);
    uint8_t * p_pt    = pt;
    uint8_t * p_ct    = (uint8_t *) ct;

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (pt == NULL) || (ct == NULL) || (ct_len == 0) ||
        ((ct_len % OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) != 0))
    {
        return;
    }
#endif

    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &pt[0]) || !OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &ct[0]))
    {
        uint32_t local_ct[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t local_pt[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
        uint32_t num_loops = ct_len / OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->iv[0]);

        for (uint32_t i = 0; i < num_loops; i++)
        {
            memcpy(local_ct, p_ct, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            ocrypto_aes_helper_update(ctx->key_size, &local_ct[0], &local_pt[0], OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS);

            memcpy(p_pt, (uint8_t *) local_pt, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
            p_ct += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
            p_pt += OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES;
        }
    }
    else
    {
        ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, (uint32_t *) &ctx->iv[0]);
        ocrypto_aes_helper_update(ctx->key_size, (uint32_t *) &ct[0], (uint32_t *) &pt[0],
                                  OCRYPTO_PORT_BYTES_TO_WORDS(ct_len));
    }

    // save last output block
    ocrypto_constant_time_copy(ctx->iv, &pt[ct_len - OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES], sizeof(ctx->iv));
}

void ocrypto_aes_cbc_encrypt (uint8_t       * ct,
                              const uint8_t * pt,
                              size_t          pt_len,
                              const uint8_t * key,
                              size_t          size,
                              const uint8_t   iv[16])
{
    ocrypto_aes_cbc_ctx ctx = {0};
    ocrypto_aes_cbc_init_enc(&ctx, key, size, iv);
    ocrypto_aes_cbc_update_enc(&ctx, ct, pt, pt_len);
}

void ocrypto_aes_cbc_decrypt (uint8_t       * pt,
                              const uint8_t * ct,
                              size_t          ct_len,
                              const uint8_t * key,
                              size_t          size,
                              const uint8_t   iv[16])
{
    ocrypto_aes_cbc_ctx ctx = {0};
    ocrypto_aes_cbc_init_dec(&ctx, key, size, iv);
    ocrypto_aes_cbc_update_dec(&ctx, pt, ct, ct_len);
}
