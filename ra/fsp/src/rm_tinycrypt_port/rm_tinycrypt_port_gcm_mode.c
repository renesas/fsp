/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
        (iv == (uint8_t *) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
        {
            err = HW_SCE_Aes192GcmEncryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes192GcmEncryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes192GcmEncryptUpdateTransitionSub();
            }
        }
        else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
    if ((sched == (TCAesKeySched_t) 0))
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
            if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
            {
                HW_SCE_Aes192GcmEncryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
        (tag == (uint8_t *) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
        {
            err =
                HW_SCE_Aes192GcmEncryptFinalSub((uint32_t *) input, &aad_len, &input_len, (uint32_t *) output,
                                                (uint32_t *) tag);
        }
        else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
        (iv == (uint8_t *) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
        {
            err = HW_SCE_Aes192GcmDecryptInitSub((uint32_t *) &sched, (uint32_t *) &sched->words[0], (uint32_t *) iv);
            if (FSP_SUCCESS == err)
            {
                HW_SCE_Aes192GcmDecryptUpdateAADSub((uint32_t *) aad, additional_len);
                HW_SCE_Aes192GcmDecryptUpdateTransitionSub();
            }
        }
        else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
    if (sched == (TCAesKeySched_t) 0)
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
            if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
            {
                HW_SCE_Aes192GcmDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, length);
            }
            else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
        (tag == (uint8_t *) 0))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL == tc_return)
    {
    }
    else
    {
        if (SIZE_AES_192BIT_KEYLEN_BYTES == (*sched).key_size)
        {
            err =
                HW_SCE_Aes192GcmDecryptFinalSub((uint32_t *) input,
                                                (uint32_t *) tag,
                                                &aad_len,
                                                &input_len,
                                                (uint32_t *) &tag_len,
                                                (uint32_t *) output);
        }
        else if (SIZE_AES_256BIT_KEYLEN_BYTES == (*sched).key_size)
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
        ((plen > 0) && (payload == (uint8_t *) 0)) ||
        ((ivlen > 0) && (iv == (uint8_t *) 0)) ||
        (olen != plen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL != tc_return)
    {
        memcpy(&(g->sched->words[SCE_AES_GCM_IN_DATA_IV_LEN_LOC]), &ivlen, sizeof(unsigned int));
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
        ((plen > 0) && (payload == (uint8_t *) 0)) ||
        ((ivlen > 0) && (iv == (uint8_t *) 0)) ||
        (olen != plen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
#endif

    if (TC_CRYPTO_FAIL != tc_return)
    {
        memcpy(&(g->sched->words[SCE_AES_GCM_IN_DATA_IV_LEN_LOC]), &ivlen, sizeof(unsigned int));
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
