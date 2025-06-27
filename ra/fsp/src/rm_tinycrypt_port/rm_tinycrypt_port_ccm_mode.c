/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include <tinycrypt/constants.h>
#include <tinycrypt/ccm_mode.h>
#include <tinycrypt/utils.h>
#include "hw_sce_aes_private.h"
#include "hw_sce_private.h"
#include "hw_sce_ra_private.h"
#include "rm_tinycrypt_port_cfg.h"

#define MAC_SIZE_MIN_IN_BYTE      (4)
#define MAC_SIZE_MAX_IN_BYTE      (16)

#define NONCE_SIZE_MIN_IN_BYTE    (7)
#define NONCE_SIZE_MAX_IN_BYTE    (13)

#define TC_32BIT_ALIGNED(x)     (!((x) & 0x03))
#define TC_NUMSIZE_IS_ODD(x)    ((x) & 0x1)

int tc_ccm_config (TCCcmMode_t c, TCAesKeySched_t sched, uint8_t * nonce, unsigned int nlen, unsigned int mlen)
{
    int tc_return = TC_CRYPTO_SUCCESS;
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((c == NULL) || (sched == NULL) || (nonce == NULL))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
    else if ((NONCE_SIZE_MIN_IN_BYTE > nlen) || (NONCE_SIZE_MAX_IN_BYTE < nlen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
    else if ((MAC_SIZE_MIN_IN_BYTE > mlen) || (MAC_SIZE_MAX_IN_BYTE < mlen) || TC_NUMSIZE_IS_ODD(mlen))
    {
        tc_return = TC_CRYPTO_FAIL;
    }
    else
    {
        ;
    }
#endif

    if (TC_CRYPTO_SUCCESS == tc_return)
    {
        c->mlen  = mlen;
        c->nlen  = nlen;
        c->sched = sched;
        c->nonce = nonce;
    }

    return tc_return;
}

int tc_ccm_generation_encryption (uint8_t       * out,
                                  unsigned int    olen,
                                  const uint8_t * associated_data,
                                  unsigned int    alen,
                                  const uint8_t * payload,
                                  unsigned int    plen,
                                  TCCcmMode_t     c)
{
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((out == NULL) ||
        (c == NULL) ||
        ((plen > 0) && (payload == NULL)) ||
        ((alen > 0) && (associated_data == NULL)) ||
        (alen >= TC_CCM_AAD_MAX_BYTES) ||     // associated data size unsupported
        (plen >= TC_CCM_PAYLOAD_MAX_BYTES) || // payload size unsupported
        (olen < (plen + c->mlen)))            // invalid output buffer size
    {
        return TC_CRYPTO_FAIL;
    }

#else
    FSP_PARAMETER_NOT_USED(olen);
#endif
    fsp_err_t err = FSP_SUCCESS;

    const uint32_t   InData_KeyType[]  = {c->sched->key_size};
    const uint32_t   InData_DataType[] = {0};
    const uint32_t   InData_TextLen[]  = {plen};
    const uint32_t * InData_KeyIndex   = (const uint32_t *) c->sched->words;
    const uint32_t * InData_IV         = (const uint32_t *) c->nonce;
    const uint32_t * InData_Header     = (const uint32_t *) associated_data;
    const uint32_t   InData_SeqNum[]   = {0};
    const uint32_t   Header_Len        = alen;
    const uint32_t * InData_Text       = (const uint32_t *) payload;

    uint32_t   OutData_MAC[TC_AES_BLOCK_SIZE / sizeof(uint32_t)];
    uint32_t * OutData_Text = (uint32_t *) out;

    bool src_unaligned = !TC_32BIT_ALIGNED((uint32_t) payload);
    bool dst_unaligned = !TC_32BIT_ALIGNED((uint32_t) out);

    uint8_t * p_payload = (uint8_t *) payload;
    uint8_t * p_out     = out;

    uint32_t work_buffer[2] = {c->nlen, c->mlen};

    if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes128CcmEncryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             work_buffer,
                                             InData_TextLen,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes192CcmEncryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             work_buffer,
                                             InData_TextLen,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else
    {
        /* Key size is 256bits */
        err = HW_SCE_Aes256CcmEncryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             work_buffer,
                                             InData_TextLen,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }

    if (FSP_SUCCESS == err)
    {
        if ((true == src_unaligned) || (true == dst_unaligned))
        {
            uint32_t  local_data_tmp[TC_AES_BLOCK_SIZE / 4];
            uint8_t * p_buf_in  = p_payload;
            uint8_t * p_buf_out = p_out;
            uint8_t * p_local_in;
            uint8_t * p_local_out;

            if (true == src_unaligned)
            {
                p_local_in = (uint8_t *) local_data_tmp;
            }
            else
            {
                p_local_in = p_buf_in;
            }

            if (true == dst_unaligned)
            {
                p_local_out = (uint8_t *) local_data_tmp;
            }
            else
            {
                p_local_out = p_buf_out;
            }

            uint32_t block_max = HW_AES_DATA_FIT_TO_BLOCK_SIZE(plen) / TC_AES_BLOCK_SIZE;
            uint32_t index;
            for (index = 0; index < block_max; index++)
            {
                if (true == src_unaligned)
                {
                    memset(p_local_in, 0, TC_AES_BLOCK_SIZE);
                    memcpy(p_local_in, p_buf_in, TC_AES_BLOCK_SIZE);
                }

                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                if (true == dst_unaligned)
                {
                    memcpy(p_buf_out, p_local_out, TC_AES_BLOCK_SIZE);
                    p_buf_out += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_local_out += TC_AES_BLOCK_SIZE;
                }

                if (true == src_unaligned)
                {
                    p_buf_in += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_local_in += TC_AES_BLOCK_SIZE;
                }
            }

            uint32_t payload_remain = HW_AES_DATA_GET_LAST_REMAINS(plen);
            if (0 < payload_remain)
            {
                if (false == src_unaligned)
                {
                    p_buf_in  += block_max * TC_AES_BLOCK_SIZE;
                    p_local_in = (uint8_t *) local_data_tmp;
                }

                if (false == dst_unaligned)
                {
                    p_buf_out  += block_max * TC_AES_BLOCK_SIZE;
                    p_local_out = (uint8_t *) local_data_tmp;
                }

                memset(p_local_in, 0, TC_AES_BLOCK_SIZE);
                memcpy(p_local_in, p_buf_in, payload_remain);

                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmEncryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                memcpy(p_buf_out, p_local_out, payload_remain);
            }
        }
        else
        {
            /* Both payload and out is uint32_t aligned */
            uint32_t  block_cnt = HW_AES_DATA_FIT_TO_BLOCK_SIZE(plen) / TC_AES_BLOCK_SIZE;
            uint8_t * p_buf_in  = p_payload;
            uint8_t * p_buf_out = p_out;

            if (0 < block_cnt)
            {
                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmEncryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmEncryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmEncryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }

                p_buf_in  += block_cnt * TC_AES_BLOCK_SIZE;
                p_buf_out += block_cnt * TC_AES_BLOCK_SIZE;
            }

            uint32_t payload_remain = HW_AES_DATA_GET_LAST_REMAINS(plen);
            if (0 < payload_remain)
            {
                uint32_t local_data_tmp[TC_AES_BLOCK_SIZE / 4];

                memset(local_data_tmp, 0, TC_AES_BLOCK_SIZE);
                memcpy(local_data_tmp, p_buf_in, payload_remain);
                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmEncryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmEncryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmEncryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                memcpy(p_buf_out, local_data_tmp, payload_remain);
            }
        }
    }

    if (FSP_SUCCESS == err)
    {
        if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
        {
            err = HW_SCE_Aes128CcmEncryptFinalSub(InData_Text, OutData_Text, OutData_MAC);
        }
        else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
        {
            err = HW_SCE_Aes128CcmEncryptFinalSub(InData_Text, OutData_Text, OutData_MAC);
        }
        else
        {
            /* Key size is 256bits */
            err = HW_SCE_Aes128CcmEncryptFinalSub(InData_Text, OutData_Text, OutData_MAC);
        }
    }

    /* Append tag to ciphertext */
    memcpy((p_out + plen), OutData_MAC, c->mlen);

    if (FSP_SUCCESS != err)
    {
        return TC_CRYPTO_FAIL;
    }

    return TC_CRYPTO_SUCCESS;
}

int tc_ccm_decryption_verification (uint8_t       * out,
                                    unsigned int    olen,
                                    const uint8_t * associated_data,
                                    unsigned int    alen,
                                    const uint8_t * payload,
                                    unsigned int    plen,
                                    TCCcmMode_t     c)
{
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((out == (uint8_t *) 0) ||
        (c == (TCCcmMode_t) 0) ||
        ((plen > 0) && (payload == (uint8_t *) 0)) ||
        ((alen > 0) && (associated_data == (uint8_t *) 0)) ||
        (alen >= TC_CCM_AAD_MAX_BYTES) ||     // associated data size unsupported
        (plen >= TC_CCM_PAYLOAD_MAX_BYTES) || // payload size unsupported
        (olen < plen - c->mlen))
    {

        /* invalid output buffer size */
        return TC_CRYPTO_FAIL;
    }

#else
    FSP_PARAMETER_NOT_USED(olen);
#endif
    fsp_err_t err = FSP_SUCCESS;

    uint32_t         InData_DataType[]  = {0};
    const uint32_t   InData_KeyType[]   = {c->sched->key_size};
    const uint32_t   InData_Cmd[]       = {c->nlen};
    const uint32_t   InData_TextLen[]   = {plen};
    const uint32_t   InData_MACLength[] = {c->mlen};
    const uint32_t * InData_KeyIndex    = (const uint32_t *) c->sched->words;
    const uint32_t * InData_IV          = (const uint32_t *) c->nonce;
    const uint32_t * InData_Header      = (const uint32_t *) associated_data;
    const uint32_t   InData_SeqNum[]    = {0};
    const uint32_t   Header_Len         = alen;
    const uint32_t * InData_Text        = (const uint32_t *) payload;
    uint8_t        * p_InData_MAC       = (uint8_t *) (payload + InData_TextLen[0] - InData_MACLength[0]);
    uint32_t       * OutData_Text       = (uint32_t *) out;

    bool src_unaligned = !TC_32BIT_ALIGNED((uint32_t) payload);
    bool dst_unaligned = !TC_32BIT_ALIGNED((uint32_t) out);

    uint8_t * p_payload = (uint8_t *) payload;
    uint8_t * p_out     = out;

    if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes128CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes192CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else
    {
        /* Key size is 256bits */
        err = HW_SCE_Aes256CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }

    if (FSP_SUCCESS == err)
    {
        if ((true == src_unaligned) || (true == dst_unaligned))
        {
            uint32_t  local_data_tmp[TC_AES_BLOCK_SIZE / 4];
            uint8_t * p_buf_in  = p_payload;
            uint8_t * p_buf_out = p_out;
            uint8_t * p_local_in;
            uint8_t * p_local_out;

            if (true == src_unaligned)
            {
                p_local_in = (uint8_t *) local_data_tmp;
            }
            else
            {
                p_local_in = p_buf_in;
            }

            if (true == dst_unaligned)
            {
                p_local_out = (uint8_t *) local_data_tmp;
            }
            else
            {
                p_local_out = p_buf_out;
            }

            uint32_t block_max = HW_AES_DATA_FIT_TO_BLOCK_SIZE((InData_TextLen[0] - InData_MACLength[0])) /
                                 TC_AES_BLOCK_SIZE;
            uint32_t index;
            for (index = 0; index < block_max; index++)
            {
                if (true == src_unaligned)
                {
                    memset(p_local_in, 0, TC_AES_BLOCK_SIZE);
                    memcpy(p_local_in, p_buf_in, TC_AES_BLOCK_SIZE);
                }

                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                if (true == dst_unaligned)
                {
                    memcpy(p_buf_out, p_local_out, TC_AES_BLOCK_SIZE);
                    p_buf_out += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_local_out += TC_AES_BLOCK_SIZE;
                }

                if (true == src_unaligned)
                {
                    p_buf_in += TC_AES_BLOCK_SIZE;
                }
                else
                {
                    p_local_in += TC_AES_BLOCK_SIZE;
                }
            }

            uint32_t payload_remain = HW_AES_DATA_GET_LAST_REMAINS((InData_TextLen[0] - InData_MACLength[0]));
            if (0 < payload_remain)
            {
                if (false == src_unaligned)
                {
                    p_buf_in  += block_max * TC_AES_BLOCK_SIZE;
                    p_local_in = (uint8_t *) local_data_tmp;
                }

                if (false == dst_unaligned)
                {
                    p_buf_out  += block_max * TC_AES_BLOCK_SIZE;
                    p_local_out = (uint8_t *) local_data_tmp;
                }

                memset(p_local_in, 0, TC_AES_BLOCK_SIZE);
                memcpy(p_local_in, p_buf_in, payload_remain);

                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmDecryptUpdateSub((uint32_t *) p_local_in,
                                                     (uint32_t *) p_local_out,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                memcpy(p_buf_out, p_local_out, payload_remain);
            }
        }
        else
        {
            /* Both payload and out is uint32_t aligned */
            uint32_t block_cnt = HW_AES_DATA_FIT_TO_BLOCK_SIZE((InData_TextLen[0] - InData_MACLength[0])) /
                                 TC_AES_BLOCK_SIZE;
            uint8_t * p_buf_in  = p_payload;
            uint8_t * p_buf_out = p_out;

            if (0 < block_cnt)
            {
                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmDecryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmDecryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmDecryptUpdateSub((uint32_t *) p_buf_in, (uint32_t *) p_buf_out,
                                                     block_cnt * (TC_AES_BLOCK_SIZE / sizeof(uint32_t)));
                }

                p_buf_in  += block_cnt * TC_AES_BLOCK_SIZE;
                p_buf_out += block_cnt * TC_AES_BLOCK_SIZE;
            }

            uint32_t payload_remain = HW_AES_DATA_GET_LAST_REMAINS((InData_TextLen[0] - InData_MACLength[0]));
            if (0 < payload_remain)
            {
                uint32_t local_data_tmp[TC_AES_BLOCK_SIZE / 4];

                memset(local_data_tmp, 0, TC_AES_BLOCK_SIZE);
                memcpy(local_data_tmp, p_buf_in, payload_remain);
                if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes128CcmDecryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
                {
                    HW_SCE_Aes192CcmDecryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }
                else
                {
                    /* Key size is 256bits */
                    HW_SCE_Aes256CcmDecryptUpdateSub(local_data_tmp,
                                                     local_data_tmp,
                                                     TC_AES_BLOCK_SIZE / sizeof(uint32_t));
                }

                memcpy(p_buf_out, local_data_tmp, payload_remain);
            }
        }
    }

    /* Apply formating function with associated data */
    InData_DataType[0] = 1;

    if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes128CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
    {
        err = HW_SCE_Aes192CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }
    else
    {
        /* Key size is 256bits */
        err = HW_SCE_Aes256CcmDecryptInitSub(InData_KeyType,
                                             InData_DataType,
                                             InData_Cmd,
                                             InData_TextLen,
                                             InData_MACLength,
                                             InData_KeyIndex,
                                             InData_IV,
                                             InData_Header,
                                             InData_SeqNum,
                                             Header_Len);
    }

    if (FSP_SUCCESS == err)
    {
        if (SIZE_AES_128BIT_KEYLEN_BYTES == c->sched->key_size)
        {
            err = HW_SCE_Aes128CcmDecryptFinalSub(InData_Text,
                                                  InData_TextLen,
                                                  (uint32_t *) p_InData_MAC,
                                                  InData_MACLength,
                                                  OutData_Text);
        }
        else if (SIZE_AES_192BIT_KEYLEN_BYTES == c->sched->key_size)
        {
            err = HW_SCE_Aes192CcmDecryptFinalSub(InData_Text,
                                                  InData_TextLen,
                                                  (uint32_t *) p_InData_MAC,
                                                  InData_MACLength,
                                                  OutData_Text);
        }
        else
        {
            /* Key size is 256bits */
            err = HW_SCE_Aes256CcmDecryptFinalSub(InData_Text,
                                                  InData_TextLen,
                                                  (uint32_t *) p_InData_MAC,
                                                  InData_MACLength,
                                                  OutData_Text);
        }
    }

    if (FSP_SUCCESS != err)
    {
        return TC_CRYPTO_FAIL;
    }

    return TC_CRYPTO_SUCCESS;
}
