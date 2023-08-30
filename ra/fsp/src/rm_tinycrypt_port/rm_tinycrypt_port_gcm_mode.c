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
#include <tinycrypt/utils.h>
#include "hw_sce_aes_private.h"
#include "hw_sce_private.h"
#include "hw_sce_ra_private.h"
#include "rm_tinycrypt_port_cfg.h"
#include "rm_tinycrypt_port.h"
#include <tinycrypt/gcm_mode.h>

#if (2 == BSP_FEATURE_CRYPTO_AES_IP_VERSION)
 #if (RM_TINYCRYPT_PORT_GCM_HW_ACCELERATION_ENABLED == 1)

  #define TC_GCM_T_LEN_128_IN_BYTE    16
  #define TC_GCM_T_LEN_120_IN_BYTE    15
  #define TC_GCM_T_LEN_112_IN_BYTE    14
  #define TC_GCM_T_LEN_104_IN_BYTE    13
  #define TC_GCM_T_LEN_96_IN_BYTE     12
  #define TC_GCM_T_LEN_64_IN_BYTE     8
  #define TC_GCM_T_LEN_32_IN_BYTE     4

int tc_gcm_config (TCGcmMode_t context, TCAesKeySched_t sched, uint8_t tlen)
{
    int tc_return = TC_CRYPTO_SUCCESS;

    /* input sanity check: */
    if ((context == (TCGcmMode_t) 0) || (sched == (TCAesKeySched_t) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
    else if ((tlen != TC_GCM_T_LEN_128_IN_BYTE) && (tlen != TC_GCM_T_LEN_120_IN_BYTE) &&
             (tlen != TC_GCM_T_LEN_112_IN_BYTE) && (tlen != TC_GCM_T_LEN_104_IN_BYTE) &&
             (tlen != TC_GCM_T_LEN_96_IN_BYTE) &&
             (tlen != TC_GCM_T_LEN_64_IN_BYTE) && (tlen != TC_GCM_T_LEN_32_IN_BYTE))
    {
        tc_return = TC_CRYPTO_FAIL;    /* The allowed mac sizes are: 128, 120, 112, 104, 96, 64, 32*/
    }
    else
    {
        context->tlen  = tlen;
        context->sched = sched;
    }

    return tc_return;
}

int tc_gcm_encryption_init (const TCAesKeySched_t sched, uint8_t * iv, uint8_t * aad, uint32_t additional_len)
{
    fsp_err_t err       = FSP_SUCCESS;
    int       tc_return = TC_CRYPTO_SUCCESS;
  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((sched == (TCAesKeySched_t) 0) ||
        (iv == (uint8_t *) 0) ||
        (aad == (uint8_t *) 0) ||
        (additional_len == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err = HW_SCE_Aes192GcmEncryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes192GcmEncryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes192GcmEncryptUpdateTransitionSub();
            }
        }
        else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err = HW_SCE_Aes256GcmEncryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes256GcmEncryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes256GcmEncryptUpdateTransitionSub();
            }
        }
        else
        {
            err = HW_SCE_Aes128GcmEncryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes128GcmEncryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes128GcmEncryptUpdateTransitionSub();
            }
        }

        if (FSP_SUCCESS != err)
        {
            tc_return = TC_CRYPTO_FAIL;
        }
    }

    return tc_return;
}

int tc_gcm_encryption_update (const TCAesKeySched_t sched, const uint8_t * input, uint8_t * output, uint32_t length)
{
    int tc_return = TC_CRYPTO_SUCCESS;
  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((sched == (TCAesKeySched_t) 0) ||
        (input == (uint8_t *) 0) ||
        (output == (uint8_t *) 0) ||
        (length == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (0 != length)
        {
            if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
            {
                HW_SCE_Aes192GcmEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
            {
                HW_SCE_Aes256GcmEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else
            {
                HW_SCE_Aes128GcmEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
        }
    }

    return tc_return;
}

int tc_gcm_encryption_final (const TCAesKeySched_t sched,
                             uint8_t             * input,
                             uint32_t              input_len,
                             uint32_t              aad_len,
                             uint8_t             * output,
                             uint8_t             * tag)
{
    fsp_err_t err       = FSP_SUCCESS;
    int       tc_return = TC_CRYPTO_SUCCESS;

  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */

    if ((sched == (TCAesKeySched_t) 0) ||
        (input == (uint8_t *) 0) ||
        (output == (uint8_t *) 0) ||
        (tag == (uint8_t *) 0) ||
        (input_len == 0) ||
        (aad_len == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err =
                HW_SCE_Aes192GcmEncryptFinalSub((uint32_t *) input, &aad_len, &input_len, (uint32_t *) output,
                                                (uint32_t *) tag);
        }
        else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err =
                HW_SCE_Aes256GcmEncryptFinalSub((uint32_t *) input, &aad_len, &input_len, (uint32_t *) output,
                                                (uint32_t *) tag);
        }
        else
        {
            err =
                HW_SCE_Aes128GcmEncryptFinalSub((uint32_t *) input, &aad_len, &input_len, (uint32_t *) output,
                                                (uint32_t *) tag);
        }
    }

    if (FSP_SUCCESS != err)
    {
        tc_return = TC_CRYPTO_FAIL;
    }

    return tc_return;
}

int tc_gcm_decryption_init (const TCAesKeySched_t sched, uint8_t * iv, uint8_t * aad, uint32_t additional_len)
{
    fsp_err_t err       = FSP_SUCCESS;
    int       tc_return = TC_CRYPTO_SUCCESS;

  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((sched == (TCAesKeySched_t) 0) ||
        (iv == (uint8_t *) 0) ||
        (aad == (uint8_t *) 0) ||
        (additional_len == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err = HW_SCE_Aes192GcmDecryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes192GcmDecryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes192GcmDecryptUpdateTransitionSub();
            }
        }
        else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err = HW_SCE_Aes256GcmDecryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes256GcmDecryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes256GcmDecryptUpdateTransitionSub();
            }
        }
        else
        {
            err = HW_SCE_Aes128GcmDecryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes128GcmDecryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes128GcmDecryptUpdateTransitionSub();
            }
        }
    }

    if (FSP_SUCCESS != err)
    {
        tc_return = TC_CRYPTO_FAIL;
    }

    return tc_return;
}

int tc_gcm_decryption_update (const TCAesKeySched_t sched, const uint8_t * input, uint8_t * output, uint32_t length)
{
    int tc_return = TC_CRYPTO_SUCCESS;
  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((sched == (TCAesKeySched_t) 0) ||
        (input == (uint8_t *) 0) ||
        (output == (uint8_t *) 0) ||
        (length == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (0 != length)
        {
            if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
            {
                HW_SCE_Aes192GcmDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
            {
                HW_SCE_Aes256GcmDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else
            {
                HW_SCE_Aes128GcmDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
        }
    }

    return tc_return;
}

int tc_gcm_decryption_final (const TCAesKeySched_t sched,
                             uint8_t             * input,
                             uint8_t             * tag,
                             uint32_t              aad_len,
                             uint32_t              input_len,
                             uint8_t               tag_len,
                             uint8_t             * output)

{
    fsp_err_t err       = FSP_SUCCESS;
    int       tc_return = TC_CRYPTO_SUCCESS;

  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((sched == (TCAesKeySched_t) 0) ||
        (input == (uint8_t *) 0) ||
        (output == (uint8_t *) 0) ||
        (tag == (uint8_t *) 0) ||
        (input_len == 0) ||
        (aad_len == 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err =
                HW_SCE_Aes192GcmDecryptFinalSub((uint32_t *) input,
                                                (uint32_t *) tag,
                                                &aad_len,
                                                &input_len,
                                                (uint32_t *) &tag_len,
                                                (uint32_t *) output);
        }
        else if (SIZE_AES_256BIT_KEYLEN_BITS == (*sched).key_size)
        {
            err =
                HW_SCE_Aes256GcmDecryptFinalSub((uint32_t *) input,
                                                (uint32_t *) tag,
                                                &aad_len,
                                                &input_len,
                                                (uint32_t *) &tag_len,
                                                (uint32_t *) output);
        }
        else
        {
            err =
                HW_SCE_Aes128GcmDecryptFinalSub((uint32_t *) input,
                                                (uint32_t *) tag,
                                                &aad_len,
                                                &input_len,
                                                (uint32_t *) &tag_len,
                                                (uint32_t *) output);
        }
    }

    if (FSP_SUCCESS != err)
    {
        tc_return = TC_CRYPTO_FAIL;
    }

    return tc_return;
}

int tc_gcm_generation_encryption (uint8_t       * out,
                                  unsigned int    olen,
                                  uint8_t       * tag,
                                  const uint8_t * aad,
                                  unsigned int    alen,
                                  const uint8_t * iv,
                                  unsigned int    ivlen,
                                  const uint8_t * payload,
                                  unsigned int    plen,
                                  TCGcmMode_t     g)
{
    int     tc_return = TC_CRYPTO_SUCCESS;
    uint8_t temp_tag[TC_AES_BLOCK_SIZE] = {0};

  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((g == (TCGcmMode_t) 0) ||
        (out == (uint8_t *) 0) ||
        ((plen > 0) && (payload == (uint8_t *) 0)) ||
        ((alen > 0) && (aad == (uint8_t *) 0)) ||
        ((ivlen > 0) && (iv == (uint8_t *) 0)) ||
        (olen != plen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif
    FSP_PARAMETER_NOT_USED(ivlen);
    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return = tc_gcm_encryption_init(g->sched, (uint8_t *) iv, (uint8_t *) aad, (uint32_t) alen);
    }

    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return = tc_gcm_encryption_update(g->sched, payload, out, (uint32_t) olen);
    }

    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return =
            tc_gcm_encryption_final(g->sched, (uint8_t *) payload, (uint32_t) plen, (uint32_t) alen, out, temp_tag);
    }

    if (TC_CRYPTO_FAIL != tc_return)
    {
        memcpy(tag, temp_tag, g->tlen);
    }

    return tc_return;
}

int tc_gcm_decryption_verification (uint8_t       * out,
                                    unsigned int    olen,
                                    uint8_t       * tag,
                                    const uint8_t * aad,
                                    unsigned int    alen,
                                    const uint8_t * iv,
                                    unsigned int    ivlen,
                                    const uint8_t * payload,
                                    unsigned int    plen,
                                    TCGcmMode_t     g)
{
    int tc_return = TC_CRYPTO_SUCCESS;

  #if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE

    /* input sanity check: */
    if ((g == (TCGcmMode_t) 0) ||
        (out == (uint8_t *) 0) ||
        ((plen > 0) && (payload == (uint8_t *) 0)) ||
        ((alen > 0) && (aad == (uint8_t *) 0)) ||
        ((ivlen > 0) && (iv == (uint8_t *) 0)) ||
        (olen != plen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
  #endif
    FSP_PARAMETER_NOT_USED(ivlen);
    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return = tc_gcm_decryption_init(g->sched, (uint8_t *) iv, (uint8_t *) aad, (uint32_t) alen);
    }

    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return = tc_gcm_decryption_update(g->sched, payload, out, (uint32_t) olen);
    }

    if (TC_CRYPTO_FAIL != tc_return)
    {
        tc_return =
            tc_gcm_decryption_final(g->sched,
                                    (uint8_t *) payload,
                                    tag,
                                    (uint32_t) alen,
                                    (uint32_t) plen,
                                    (uint8_t) g->tlen,
                                    out);
    }
    else
    {
        /* Do nothing */
    }

    return tc_return;
}

 #endif
#endif
