/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include <tinycrypt/aes.h>
#include <tinycrypt/utils.h>
#include <tinycrypt/constants.h>
#include "hw_sce_aes_private.h"
#include "hw_sce_ra_private.h"
#include "rm_tinycrypt_port_cfg.h"

int tc_aes128_set_encrypt_key (TCAesKeySched_t s, const uint8_t * k)
{
    int ret = TC_CRYPTO_SUCCESS;

    if ((s == (TCAesKeySched_t) 0) || (k == NULL))
    {
        ret = TC_CRYPTO_FAIL;
    }
    else
    {
        memcpy(&(s->words[0]), k, SIZE_AES_128BIT_KEYLEN_BYTES);
        s->key_size = SIZE_AES_128BIT_KEYLEN_BYTES;
    }

    return ret;
}

int tc_aes_set_encrypt_key_extended (TCAesKeySched_t s, const uint8_t * k, unsigned int key_size)
{
    int ret = TC_CRYPTO_SUCCESS;

    if ((s == (TCAesKeySched_t) 0) ||
        (k == NULL) ||
        ((key_size != SIZE_AES_128BIT_KEYLEN_BYTES) && (key_size != SIZE_AES_192BIT_KEYLEN_BYTES) &&
         (key_size != SIZE_AES_256BIT_KEYLEN_BYTES)))
    {
        ret = TC_CRYPTO_FAIL;
    }
    else
    {
        memcpy(&(s->words[0]), k, key_size);
        s->key_size = key_size;
    }

    return ret;
}

int tc_aes_encrypt (uint8_t * out, const uint8_t * in, const TCAesKeySched_t s)
{
    fsp_err_t  err       = FSP_ERR_CRYPTO_UNKNOWN;
    int        tc_return = TC_CRYPTO_SUCCESS;
    uint32_t * p_in;
    uint32_t * p_out;
    uint32_t   local_out[TC_AES_BLOCK_SIZE / 4U] = {0U};
    uint32_t   local_in[TC_AES_BLOCK_SIZE / 4U]  = {0U};
    uint32_t   dummy_iv[4]     = {0};
    uint32_t   indata_cmd      = change_endian_long((uint32_t) SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t   indata_key_type = 0;

#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((out == (uint8_t *) 0) || (in == (const uint8_t *) 0) || (s == (TCAesKeySched_t) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif
    if (TC_CRYPTO_FAIL != tc_return)
    {
        /* If input and output buffers are not 32-bit aligned,
         * copy the data to a 32 bit aligned local buffer and
         * use that since the hardware operates on 32-bit data only.
         * */
        if (((uint32_t) &in[0]) & 0x3)
        {
            memcpy((uint8_t *) local_in, in, TC_AES_BLOCK_SIZE);
            p_in = local_in;
        }
        else
        {
            p_in = (uint32_t *) in;
        }

        if (((uint32_t) &out[0]) & 0x3)
        {
            p_out = local_out;
        }
        else
        {
            p_out = (uint32_t *) out;
        }

        if (SIZE_AES_192BIT_KEYLEN_BYTES == (*s).key_size)
        {
            err = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, (uint32_t *) &s->words[0], dummy_iv);
            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub(p_in, p_out, TC_AES_BLOCK_SIZE / 4U);
            }

            err = HW_SCE_Aes192EncryptDecryptFinalSub();
        }
        else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*s).key_size)
        {
            err =
                HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) &s->words[0], dummy_iv);
            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub(p_in, p_out, TC_AES_BLOCK_SIZE / 4U);
            }

            err = HW_SCE_Aes256EncryptDecryptFinalSub();
        }
        else
        {
            err =
                HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) &s->words[0], dummy_iv);
            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub(p_in, p_out, TC_AES_BLOCK_SIZE / 4U);
            }

            err = HW_SCE_Aes128EncryptDecryptFinalSub();
        }

        if (FSP_SUCCESS == err)
        {
            tc_return = TC_CRYPTO_SUCCESS;
            if (p_out == local_out)
            {
                memcpy(out, local_out, TC_AES_BLOCK_SIZE);
            }
        }
        else
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }

    return tc_return;
}
