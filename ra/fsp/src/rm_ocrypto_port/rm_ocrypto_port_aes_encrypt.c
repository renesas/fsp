/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ocrypto_port_aes_helpers.h"
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
 * External Functions
 **********************************************************************************************************************/

/* Function called internally to libocrypto. Function declaration exists in a private header file ocrypto_aes.h */
extern void ocrypto_aes_key_schedule(uint32_t * xkey, const uint8_t * key, size_t size);
extern void ocrypto_aes_encrypt_block(uint8_t ct[16], const uint8_t pt[16], const uint32_t * xkey, size_t size);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
void ocrypto_aes_key_schedule (uint32_t * xkey, const uint8_t * key, size_t size)
{
    uint32_t sce_cmd = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t dummy_iv[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0};
    memcpy(xkey, key, size);
    ocrypto_aes_helper_init(size, &sce_cmd, xkey, dummy_iv);
}

void ocrypto_aes_encrypt_block (uint8_t ct[16], const uint8_t pt[16], const uint32_t * xkey, size_t size)
{
    FSP_PARAMETER_NOT_USED(xkey);
    uint32_t * p_pt = (uint32_t *) pt;
    uint32_t * p_ct = (uint32_t *) ct;
    uint32_t   local_ct[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};
    uint32_t   local_pt[OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS] = {0U};

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

    ocrypto_aes_helper_update(size, p_pt, p_ct, OCRYPTO_PORT_AES_BLOCK_SIZE_WORDS);

    if (p_ct == local_ct)
    {
        memcpy(ct, local_ct, OCRYPTO_PORT_AES_BLOCK_SIZE_BYTES);
    }
}
