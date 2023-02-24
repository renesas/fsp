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

#include <tinycrypt/constants.h>
#include <tinycrypt/ctr_mode.h>
#include <tinycrypt/utils.h>
#include "hw_sce_aes_private.h"
#include "hw_sce_private.h"
#include "hw_sce_ra_private.h"
#include "rm_tinycrypt_port_cfg.h"

#define TC_32BIT_ALIGNED(x)    !(x & 0x03)

int tc_ctr_mode (uint8_t             * out,
                 unsigned int          outlen,
                 const uint8_t       * in,
                 unsigned int          inlen,
                 uint8_t             * ctr,
                 uint32_t            * blk_off,
                 const TCAesKeySched_t sched)
{
    int       tc_return     = TC_CRYPTO_SUCCESS;
    fsp_err_t err           = FSP_SUCCESS;
    bool      src_unaligned = !TC_32BIT_ALIGNED((uint32_t) &in[0]);
    bool      dst_unaligned = !TC_32BIT_ALIGNED((uint32_t) &out[0]);

    uint32_t indata_cmd      = change_endian_long((uint32_t)SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION);
    uint32_t indata_key_type = 0;

#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((out == (uint8_t *) 0) ||
        (in == (uint8_t *) 0) ||
        (ctr == (uint8_t *) 0) ||
        (sched == (TCAesKeySched_t) 0) ||
        (inlen == 0) ||
        (outlen == 0) ||
        (outlen != inlen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif
    FSP_PARAMETER_NOT_USED(outlen);
    FSP_PARAMETER_NOT_USED(blk_off);
    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else if ((src_unaligned || dst_unaligned) && (inlen >= TC_AES_BLOCK_SIZE))
    {
        uint8_t * buf_in    = (uint8_t *) in;
        uint8_t * buf_out   = out;
        uint8_t * p_in      = (uint8_t *) in;
        uint8_t * p_out     = out;
        uint32_t  num_loops = 1U;
        num_loops = inlen / TC_AES_BLOCK_SIZE;
        uint8_t local_in[TC_AES_BLOCK_SIZE];
        uint8_t local_out[TC_AES_BLOCK_SIZE];

        if (src_unaligned)
        {
            _set(local_in, 0, sizeof(local_in));
            p_in = &local_in[0];
        }

        if (dst_unaligned)
        {
            p_out = &local_out[0];
        }

        err =
            HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                               &indata_cmd,
                                               (uint32_t *) &sched->words[0],
                                               (uint32_t *) &ctr[0]);

        for (uint32_t i = 0; i < num_loops; i++)
        {
            if (src_unaligned)
            {
                _copy(&local_in[0], sizeof(local_in), &buf_in[0], TC_AES_BLOCK_SIZE);
            }

            if (err == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t const *) &p_in[0], (uint32_t *) &p_out[0],
                                                     (TC_AES_BLOCK_SIZE / 4U));
            }

            if (FSP_SUCCESS != err)
            {
                tc_return = TC_CRYPTO_FAIL;
            }
            else
            {
                if (dst_unaligned)
                {
                    _copy(&buf_out[0], TC_AES_BLOCK_SIZE, &p_out[0], TC_AES_BLOCK_SIZE);
                    buf_out += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_out += TC_AES_BLOCK_SIZE;
                }

                if (src_unaligned)
                {
                    buf_in += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_in += TC_AES_BLOCK_SIZE;
                }
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
    else if (inlen >= TC_AES_BLOCK_SIZE)
    {
        uint32_t local_inlen;
        local_inlen = (uint32_t) ((inlen / TC_AES_BLOCK_SIZE) * TC_AES_BLOCK_SIZE);
        err         =
            HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                               &indata_cmd,
                                               (uint32_t *) &sched->words[0],
                                               (uint32_t *) &ctr[0]);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t const *) &in[0], (uint32_t *) &out[0], (local_inlen / 4U));
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();
        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }
    else
    {
        /* Do nothing */
    }

    if (((inlen % TC_AES_BLOCK_SIZE) != 0U) && (TC_CRYPTO_SUCCESS == tc_return))
    {
        uint8_t local_in[TC_AES_BLOCK_SIZE];
        uint8_t local_out[TC_AES_BLOCK_SIZE];

        _set(local_in, 0, sizeof(local_in));
        _copy(&local_in[0], sizeof(local_in), &in[((inlen / TC_AES_BLOCK_SIZE) * TC_AES_BLOCK_SIZE)],
              (inlen % TC_AES_BLOCK_SIZE));

        err =
            HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                               &indata_cmd,
                                               (uint32_t *) &sched->words[0],
                                               (uint32_t *) &ctr[0]);
        if (err == FSP_SUCCESS)
        {
            HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t const *) &local_in[0], (uint32_t *) &local_out[0],
                                                 (TC_AES_BLOCK_SIZE / 4U));
        }

        err = HW_SCE_Aes128EncryptDecryptFinalSub();

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
        else
        {
            _copy(&out[((inlen / TC_AES_BLOCK_SIZE) * TC_AES_BLOCK_SIZE)], (inlen % TC_AES_BLOCK_SIZE), &local_out[0],
                  (inlen % TC_AES_BLOCK_SIZE));
        }
    }

    return tc_return;
}
