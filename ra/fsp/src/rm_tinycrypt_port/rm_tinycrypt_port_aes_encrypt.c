/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
        memcpy(&(s->words[0]), k, TC_AES_KEY_SIZE);
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
    uint32_t   indata_cmd      = change_endian_long((uint32_t)SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
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

        err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) &s->words[0], dummy_iv);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub(p_in, p_out, TC_AES_BLOCK_SIZE / 4U);
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

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
