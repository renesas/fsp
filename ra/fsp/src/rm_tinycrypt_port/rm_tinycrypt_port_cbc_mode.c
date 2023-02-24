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

#include <tinycrypt/cbc_mode.h>
#include <tinycrypt/constants.h>
#include <tinycrypt/utils.h>
#include "hw_sce_aes_private.h"
#include "hw_sce_private.h"
#include "hw_sce_ra_private.h"
#include "rm_tinycrypt_port_cfg.h"

int tc_cbc_mode_encrypt (uint8_t             * out,
                         unsigned int          outlen,
                         const uint8_t       * in,
                         unsigned int          inlen,
                         const uint8_t       * iv,
                         const TCAesKeySched_t sched)
{
    int       tc_return = TC_CRYPTO_SUCCESS;
    uint8_t * p_in      = (uint8_t *) in;
    uint8_t * p_out     = out;
    uint32_t  local_out[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  local_in[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  local_iv[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  num_loops = 1U;
    fsp_err_t err       = FSP_SUCCESS;

    uint32_t indata_cmd      = change_endian_long((uint32_t)SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION);
    uint32_t indata_key_type = 0;

#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((out == (uint8_t *) 0) ||
        (in == (const uint8_t *) 0) ||
        (sched == (TCAesKeySched_t) 0) ||
        (inlen == 0) ||
        (outlen == 0) ||
        ((inlen % TC_AES_BLOCK_SIZE) != 0) ||
        ((outlen % TC_AES_BLOCK_SIZE) != 0) ||
        (outlen != inlen + TC_AES_BLOCK_SIZE) ||
        (((uint32_t) &iv[0]) & 0x3))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif
    FSP_PARAMETER_NOT_USED(outlen);
    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    /*TinyCrypt software implementation expects IV to be prepended to the output buffer */
    else if (TC_CRYPTO_FAIL == _copy(out, TC_AES_BLOCK_SIZE, iv, TC_AES_BLOCK_SIZE))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
    /* copy the data to a 32 bit aligned local buffer and
     * use that since the hardware operates on 32-bit data only.
     * Call the CBC operation in a loop. */
    else if ((((uint32_t) &in[0]) & 0x3) || (((uint32_t) &out[0]) & 0x3))
    {
        num_loops = inlen / TC_AES_BLOCK_SIZE;
        memcpy((uint8_t *) local_iv, (uint8_t *) iv, TC_AES_BLOCK_SIZE);

        err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                                 &indata_cmd,
                                                 (uint32_t *) &sched->words[0],
                                                 &local_iv[0]);

        /* Offset the output buffer by iv size since the iv was previously
         * prepended to the output buffer as expected by the TinyCrypt API.  */
        p_out += TC_AES_BLOCK_SIZE;

        for (uint32_t i = 0; i < num_loops; i++)
        {
            memcpy(local_in, p_in, TC_AES_BLOCK_SIZE);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub(&local_in[0], &local_out[0], (TC_AES_BLOCK_SIZE / 4U));
            }

            if (FSP_SUCCESS != err)
            {
                tc_return = TC_CRYPTO_FAIL;
            }
            else
            {
                memcpy(p_out, (uint8_t *) local_out, TC_AES_BLOCK_SIZE);

                // memcpy((uint8_t *) &local_iv[0], (uint8_t *) local_out, TC_AES_BLOCK_SIZE);
                p_in  += TC_AES_BLOCK_SIZE;
                p_out += TC_AES_BLOCK_SIZE;
            }

            if (tc_return == TC_CRYPTO_FAIL)
            {
                break;
            }
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }
    else
    {
        memcpy((uint8_t *) local_iv, (uint8_t *) iv, TC_AES_BLOCK_SIZE);

        err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                                 &indata_cmd,
                                                 (uint32_t *) &sched->words[0],
                                                 &local_iv[0]);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &in[0], (uint32_t *) &out[TC_AES_BLOCK_SIZE],
                                                 (inlen / 4U));
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }

    return tc_return;
}

int tc_cbc_mode_decrypt (uint8_t             * out,
                         unsigned int          outlen,
                         const uint8_t       * in,
                         unsigned int          inlen,
                         const uint8_t       * iv,
                         const TCAesKeySched_t sched)
{
    int       tc_return = TC_CRYPTO_SUCCESS;
    uint8_t * p_in      = (uint8_t *) in;
    uint8_t * p_out     = out;
    uint32_t  local_out[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  local_in[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  local_iv[TC_AES_BLOCK_SIZE / 4U];
    uint32_t  num_loops = 1U;
    fsp_err_t err       = FSP_SUCCESS;

    uint32_t indata_cmd      = change_endian_long((uint32_t)SCE_AES_IN_DATA_CMD_CBC_DECRYPTION);
    uint32_t indata_key_type = 0;

#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* sanity check the inputs */
    if ((out == (uint8_t *) 0) ||
        (in == (const uint8_t *) 0) ||
        (sched == (TCAesKeySched_t) 0) ||
        (inlen == 0) ||
        (outlen == 0) ||
        ((inlen % TC_AES_BLOCK_SIZE) != 0) ||
        ((outlen % TC_AES_BLOCK_SIZE) != 0) ||
        (outlen != inlen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif
    FSP_PARAMETER_NOT_USED(outlen);
    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    /* If input or output buffers are not 32-bit aligned,
     * copy the data to a 32 bit aligned local buffer and
     * use that since the hardware operates on 32-bit data only.
     * Call the CBC operation in a loop. */
    else if ((((uint32_t) &in[0]) & 0x3) || (((uint32_t) &out[0]) & 0x3))
    {
        /* The input buffer will have the iv prepended to it
         * so remove that size from the length of data to be decrypted. */
        num_loops = ((inlen - TC_AES_BLOCK_SIZE) / TC_AES_BLOCK_SIZE);
        memcpy((uint8_t *) local_iv, (uint8_t *) iv, TC_AES_BLOCK_SIZE);

        err = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                                 &indata_cmd,
                                                 (uint32_t *) &sched->words[0],
                                                 &local_iv[0]);

        for (uint32_t i = 0; i < num_loops; i++)
        {
            memcpy(local_in, p_in, TC_AES_BLOCK_SIZE);

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub(&local_in[0], &local_out[0], (TC_AES_BLOCK_SIZE / 4U));
            }

            if (FSP_SUCCESS != err)
            {
                tc_return = TC_CRYPTO_FAIL;
            }
            else
            {
                memcpy(p_out, local_out, TC_AES_BLOCK_SIZE);
                p_in  += TC_AES_BLOCK_SIZE;
                p_out += TC_AES_BLOCK_SIZE;
            }

            if (tc_return == TC_CRYPTO_FAIL)
            {
                break;
            }
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }
    else
    {
        err =
            HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                               &indata_cmd,
                                               (uint32_t *) &sched->words[0],
                                               (uint32_t *) &iv[0]);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) &in[0], (uint32_t *) &out[0], (inlen / 4U));
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }

    return tc_return;
}
