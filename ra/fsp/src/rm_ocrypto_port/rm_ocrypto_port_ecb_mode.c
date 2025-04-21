/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_ocrypto_port_aes_helpers.h"
#include "ocrypto_aes_ecb.h"
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
void ocrypto_aes_ecb_init_enc (ocrypto_aes_ecb_ctx * ctx, const uint8_t * key, size_t size)
{
#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (key == NULL) ||
        ((size != SIZE_AES_128BIT_KEYLEN_BYTES) && (size != SIZE_AES_256BIT_KEYLEN_BYTES)))
    {
        return;
    }
#endif

    memcpy(ctx->xkey, key, size);
    ctx->key_size = (uint8_t) size;
}

void ocrypto_aes_ecb_init_dec (ocrypto_aes_ecb_ctx * ctx, const uint8_t * key, size_t size)
{
#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (key == NULL) ||
        ((size != SIZE_AES_128BIT_KEYLEN_BYTES) && (size != SIZE_AES_256BIT_KEYLEN_BYTES)))
    {
        return;
    }
#endif

    memcpy(ctx->xkey, key, size);
    ctx->key_size = (uint8_t) size;
}

void ocrypto_aes_ecb_update_enc (ocrypto_aes_ecb_ctx * ctx, uint8_t * ct, const uint8_t * pt, size_t pt_len)
{
    uint32_t   sce_cmd = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t   dummy_iv[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0};
    uint32_t * p_pt = (uint32_t *) pt;
    uint32_t * p_ct = (uint32_t *) ct;
    uint32_t   local_ct[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
    uint32_t   local_pt[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (ct == NULL) || (pt == NULL) || (pt_len == 0) ||
        ((pt_len % OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) != 0))
    {
        return;
    }
#endif

    /* If plaintext and ciphertext buffers are not 32-bit aligned,
     * copy the data to a 32 bit aligned local buffer and
     * use that since the hardware operates on 32-bit data only.
     * */
    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &pt[0]))
    {
        memcpy((uint8_t *) local_pt, pt, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
        p_pt = local_pt;
    }

    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &ct[0]))
    {
        p_ct = local_ct;
    }

    ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, dummy_iv);
    ocrypto_aes_helper_update(ctx->key_size, p_pt, p_ct, OCRYPTO_PORT_BYTES_TO_WORDS(pt_len));

    if (p_ct == local_ct)
    {
        memcpy(ct, local_ct, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
    }
}

void ocrypto_aes_ecb_update_dec (ocrypto_aes_ecb_ctx * ctx, uint8_t * pt, const uint8_t * ct, size_t ct_len)
{
    uint32_t   sce_cmd = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_DECRYPTION);
    uint32_t   dummy_iv[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0};
    uint32_t * p_pt = (uint32_t *) pt;
    uint32_t * p_ct = (uint32_t *) ct;
    uint32_t   local_ct[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
    uint32_t   local_pt[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};

#if RM_OCRYPTO_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((ctx == NULL) || (pt == NULL) || (ct == NULL) || (ct_len == 0) ||
        ((ct_len % OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES) != 0))
    {
        return;
    }
#endif

    /* If plaintext and ciphertext buffers are not 32-bit aligned,
     * copy the data to a 32 bit aligned local buffer and
     * use that since the hardware operates on 32-bit data only.
     * */
    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &ct[0]))
    {
        memcpy((uint8_t *) local_ct, ct, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
        p_ct = local_ct;
    }

    if (!OCRYPTO_PORT_AES_32BIT_ALIGNED((uint32_t) &pt[0]))
    {
        p_pt = local_pt;
    }

    ocrypto_aes_helper_init(ctx->key_size, &sce_cmd, ctx->xkey, dummy_iv);
    ocrypto_aes_helper_update(ctx->key_size, p_ct, p_pt, OCRYPTO_PORT_BYTES_TO_WORDS(ct_len));

    if (p_pt == local_pt)
    {
        memcpy(pt, local_pt, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
    }
}

void ocrypto_aes_ecb_encrypt (uint8_t * ct, const uint8_t * pt, size_t pt_len, const uint8_t * key, size_t size)
{
    ocrypto_aes_ecb_ctx ctx = {0};
    ocrypto_aes_ecb_init_enc(&ctx, key, size);
    ocrypto_aes_ecb_update_enc(&ctx, ct, pt, pt_len);
}

void ocrypto_aes_ecb_decrypt (uint8_t * pt, const uint8_t * ct, size_t ct_len, const uint8_t * key, size_t size)
{
    ocrypto_aes_ecb_ctx ctx = {0};
    ocrypto_aes_ecb_init_dec(&ctx, key, size);
    ocrypto_aes_ecb_update_dec(&ctx, pt, ct, ct_len);
}
