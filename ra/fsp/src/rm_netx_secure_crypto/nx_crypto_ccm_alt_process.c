/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : nx_crypto_ccm_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#include "rm_netx_secure_crypto.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_AES_ALT) && ((BSP_FEATURE_RSIP_SCE9_SUPPORTED ||      \
                                                              BSP_FEATURE_RSIP_SCE7_SUPPORTED ||      \
                                                              BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
                                                              BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
                                                              BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED || \
                                                              BSP_FEATURE_RSIP_RSIP_E11A_SUPPORTED || \
                                                              BSP_FEATURE_RSIP_SCE5_SUPPORTED ||      \
                                                              BSP_FEATURE_RSIP_SCE5B_SUPPORTED) == 1)
 #include "nx_crypto_aes.h"
 #include "hw_sce_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_aes_private.h"

 #define SCE9_AES_CCM_KEY_TYPE_GENERAL    (0)
 #define ROUNDOFF_TO_BLOCK_SIZE(BLOCK_SIZE, DATA_SIZE)    (BLOCK_SIZE * ((DATA_SIZE + (BLOCK_SIZE - 1)) / BLOCK_SIZE))

static UINT ccm_block_format (NX_CRYPTO_CCM * ccm_metadata,
                              UCHAR         * a_data,
                              UINT            a_len,
                              UINT            m_len,
                              UCHAR         * iv,
                              UINT            block_size,
                              UCHAR         * b_format_buffer,
                              UINT          * format_buffer_length)
{
    UINT   header_size          = 0;
    UINT   header_data_expected = 0;
    UCHAR  Flags                = 0;
    UCHAR  L = (UCHAR) (15 - iv[0]);
    USHORT M = ccm_metadata->nx_crypto_ccm_icv_length;

    /* Check the block size. */
    /* Accroding to RFC 3610, valid values of L range between 2 octets and 8 octets, iv[0] range between 7 octets and 13 octets. */
    if ((block_size != NX_CRYPTO_CCM_BLOCK_SIZE) || (iv[0] > 13) || (iv[0] < 7))
    {
        return NX_CRYPTO_PTR_ERROR;
    }

    NX_CRYPTO_MEMSET(b_format_buffer, 0, HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE);
    NX_CRYPTO_MEMSET(&ccm_metadata->nx_crypto_ccm_A[0], 0, sizeof(ccm_metadata->nx_crypto_ccm_A));
    ccm_metadata->nx_crypto_ccm_A[0] = (UCHAR) (L - 1);
    NX_CRYPTO_MEMCPY(&ccm_metadata->nx_crypto_ccm_A[1], &iv[1], (UINT) (15 - L));

    header_data_expected += HW_SCE_AES_BLOCK_BYTE_SIZE;
    header_data_expected += ROUNDOFF_TO_BLOCK_SIZE(HW_SCE_AES_BLOCK_BYTE_SIZE, (2U + a_len));

    if (header_data_expected > HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* Create Flag for B(0).  */
    if (a_len > 0)
    {
        Flags = 1 << 6;
    }
    else
    {
        Flags = 0;
    }

    Flags |= (UCHAR) (((M - 2) >> 1) << 3);
    Flags |= (UCHAR) (L - 1);

    *b_format_buffer = Flags;
    NX_CRYPTO_MEMCPY((b_format_buffer + 1), &iv[1], (UINT) 15 - L);
    b_format_buffer[14] = (UCHAR) (m_len >> 8);
    b_format_buffer[15] = (UCHAR) (m_len);

    header_size += HW_SCE_AES_BLOCK_BYTE_SIZE;
    b_format_buffer[header_size] = (UCHAR) (a_len >> 8);
    header_size++;
    b_format_buffer[header_size] = (UCHAR) (a_len);
    header_size++;
    NX_CRYPTO_MEMCPY(&b_format_buffer[header_size], a_data, a_len);

    header_size += a_len;
    header_size  = ROUNDOFF_TO_BLOCK_SIZE(HW_SCE_AES_BLOCK_BYTE_SIZE, header_size);

    /* Header size to be specified in words. */
    *format_buffer_length = header_size >> 2;

    return 0;
}

UINT sce_nx_crypto_ccm_encrypt_init (NX_CRYPTO_AES * aes_ctx,
                                     VOID          * additional_data,
                                     UINT            additional_len,
                                     UINT            length,
                                     UCHAR         * iv,
                                     USHORT          icv_len,
                                     USHORT          block_size)
{
    fsp_err_t       err               = FSP_SUCCESS;
    UINT            ret               = NX_CRYPTO_NOT_SUCCESSFUL;
    UINT            header_length     = 0;
    uint32_t        key_type[1]       = {SCE9_AES_CCM_KEY_TYPE_GENERAL};
    uint32_t        indata_cmd[1]     = {0};
    uint32_t        indata_type[1]    = {0};
    uint32_t        indata_seqnum[1]  = {0};
    uint32_t        indata_textlen[1] = {0};
    uint8_t         work_buffer[HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE] = {0};
    NX_CRYPTO_CCM * p_ccm_metadata = &aes_ctx->nx_crypto_aes_mode_context.ccm;

    indata_textlen[0] = change_endian_long(length);

    /* The memory allocated by the NetX Secure stack to store the metadata is not fully
     * required for the crypto processing when sce engines are used. Thus the same space has
     * been used to accomodate the context info of sce engines. The allocated space for
     * processing buffer 'nx_crypto_ccm_X' is utilized for storing the input data length
     * in big endian form */
    NX_CRYPTO_MEMSET(p_ccm_metadata->nx_crypto_ccm_X, 0, sizeof(p_ccm_metadata->nx_crypto_ccm_X));
    NX_CRYPTO_MEMCPY(p_ccm_metadata->nx_crypto_ccm_X, indata_textlen, sizeof(indata_textlen));

    p_ccm_metadata->nx_crypto_ccm_icv_length = icv_len;

    NX_CRYPTO_MEMSET(work_buffer, 0, sizeof(work_buffer));

    if ((ret =
             ccm_block_format(p_ccm_metadata, (UCHAR *) additional_data, additional_len, length, iv, (UINT) block_size,
                              work_buffer, &header_length)) != 0U)
    {
        return ret;
    }

    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes128CcmEncryptInitSubGeneral(key_type,
                                                  indata_type,
                                                  indata_cmd,
                                                  indata_textlen,
                                                  (uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                                  (uint32_t *) p_ccm_metadata->nx_crypto_ccm_A,
                                                  (uint32_t *) work_buffer,
                                                  indata_seqnum,
                                                  header_length);
    }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes192CcmEncryptInitSubGeneral(key_type,
                                                  indata_type,
                                                  indata_cmd,
                                                  indata_textlen,
                                                  (uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                                  (uint32_t *) p_ccm_metadata->nx_crypto_ccm_A,
                                                  (uint32_t *) work_buffer,
                                                  indata_seqnum,
                                                  header_length);
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes256CcmEncryptInitSubGeneral(key_type,
                                                  indata_type,
                                                  indata_cmd,
                                                  indata_textlen,
                                                  (uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                                  (uint32_t *) p_ccm_metadata->nx_crypto_ccm_A,
                                                  (uint32_t *) work_buffer,
                                                  indata_seqnum,
                                                  header_length);
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    if (FSP_SUCCESS != err)
    {
        return NX_CRYPTO_NOT_SUCCESSFUL;
    }

    return NX_CRYPTO_SUCCESS;
}

UINT sce_nx_crypto_ccm_encrypt_update (NX_CRYPTO_AES * aes_ctx, UCHAR * input, UCHAR * output, UINT length)
{
    fsp_err_t       err              = FSP_SUCCESS;
    uint32_t        input_length     = length;
    uint32_t        length_remaining = length % NX_CRYPTO_CCM_BLOCK_SIZE;
    uint8_t         work_buffer[NX_CRYPTO_CCM_BLOCK_SIZE] = {0};
    uint32_t        indata_textlen[1] = {0};
    NX_CRYPTO_CCM * p_ccm_metadata    = &aes_ctx->nx_crypto_aes_mode_context.ccm;

    NX_CRYPTO_MEMCPY(indata_textlen, p_ccm_metadata->nx_crypto_ccm_X, sizeof(indata_textlen));

    input_length -= length_remaining;

    /* Handle full/complete block(s) */
    if (0 != input_length)
    {
        if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes128CcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes192CcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
 #endif
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes256CcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
        else
        {
            return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
        }
    }

    NX_CRYPTO_MEMSET(work_buffer, 0, sizeof(work_buffer));
    NX_CRYPTO_MEMSET(p_ccm_metadata->nx_crypto_ccm_X, 0, sizeof(p_ccm_metadata->nx_crypto_ccm_X));
    if (0 != length_remaining)
    {
        NX_CRYPTO_MEMCPY(work_buffer, &input[input_length], length_remaining);
    }

    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes128CcmEncryptFinalSubGeneral((uint32_t *) work_buffer,
                                                   indata_textlen,
                                                   (uint32_t *) &output[input_length],
                                                   (uint32_t *) p_ccm_metadata->nx_crypto_ccm_X);
    }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes192CcmEncryptFinalSub(indata_textlen,
                                            (uint32_t *) work_buffer,
                                            (uint32_t *) &output[input_length],
                                            (uint32_t *) p_ccm_metadata->nx_crypto_ccm_X);
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err =
            HW_SCE_Aes256CcmEncryptFinalSub(indata_textlen,
                                            (uint32_t *) work_buffer,
                                            (uint32_t *) &output[input_length],
                                            (uint32_t *) p_ccm_metadata->nx_crypto_ccm_X);
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    if (FSP_SUCCESS != err)
    {
        return NX_CRYPTO_NOT_SUCCESSFUL;
    }

    return NX_CRYPTO_SUCCESS;
}

UINT sce_nx_crypto_ccm_encrypt_final (NX_CRYPTO_AES * aes_ctx, UCHAR * output)
{
    NX_CRYPTO_CCM * p_ccm_metadata = &aes_ctx->nx_crypto_aes_mode_context.ccm;

    NX_CRYPTO_MEMCPY(output, p_ccm_metadata->nx_crypto_ccm_X, p_ccm_metadata->nx_crypto_ccm_icv_length);

    return NX_CRYPTO_SUCCESS;
}

UINT sce_nx_crypto_ccm_decrypt_init (NX_CRYPTO_AES * crypto_metadata,
                                     NX_CRYPTO_CCM * ccm_metadata,
                                     VOID          * additional_data,
                                     UINT            additional_len,
                                     UINT            length,
                                     UCHAR         * iv,
                                     USHORT          icv_len,
                                     USHORT          block_size)
{
    fsp_err_t err           = FSP_SUCCESS;
    UINT      ret           = NX_CRYPTO_NOT_SUCCESSFUL;
    UINT      header_length = 0;
    uint8_t   work_buffer[HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE] = {0};
    uint32_t  key_type[1]         = {SCE9_AES_CCM_KEY_TYPE_GENERAL};
    uint32_t  indata_cmd[1]       = {0};
    uint32_t  indata_type[1]      = {0};
    uint32_t  indata_seqnum[1]    = {0};
    uint32_t  indata_textlen[1]   = {0};
    uint32_t  indata_maclength[1] = {0};

    indata_textlen[0] = change_endian_long(length);
    NX_CRYPTO_MEMSET(ccm_metadata->nx_crypto_ccm_X, 0, sizeof(ccm_metadata->nx_crypto_ccm_X));
    NX_CRYPTO_MEMCPY(ccm_metadata->nx_crypto_ccm_X, indata_textlen, sizeof(indata_textlen));

    indata_maclength[0] = change_endian_long((uint32_t) icv_len);
    ccm_metadata->nx_crypto_ccm_icv_length = icv_len;

    NX_CRYPTO_MEMSET(work_buffer, 0, sizeof(work_buffer));

    if ((ret =
             ccm_block_format(ccm_metadata, additional_data, additional_len, length, iv, block_size, work_buffer,
                              &header_length)) != 0U)
    {
        return ret;
    }

    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes128CcmDecryptInitSubGeneral(key_type,
                                                    indata_type,
                                                    indata_cmd,
                                                    indata_textlen,
                                                    (uint32_t *) indata_maclength,
                                                    (uint32_t *) (crypto_metadata->nx_crypto_aes_key_schedule),
                                                    (uint32_t *) ccm_metadata->nx_crypto_ccm_A,
                                                    (uint32_t *) work_buffer,
                                                    indata_seqnum,
                                                    header_length);
    }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes192CcmDecryptInitSubGeneral(key_type,
                                                    indata_type,
                                                    indata_cmd,
                                                    indata_textlen,
                                                    (uint32_t *) indata_maclength,
                                                    (uint32_t *) (crypto_metadata->nx_crypto_aes_key_schedule),
                                                    (uint32_t *) ccm_metadata->nx_crypto_ccm_A,
                                                    (uint32_t *) work_buffer,
                                                    indata_seqnum,
                                                    header_length);
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes256CcmDecryptInitSubGeneral(key_type,
                                                    indata_type,
                                                    indata_cmd,
                                                    indata_textlen,
                                                    (uint32_t *) indata_maclength,
                                                    (uint32_t *) (crypto_metadata->nx_crypto_aes_key_schedule),
                                                    (uint32_t *) ccm_metadata->nx_crypto_ccm_A,
                                                    (uint32_t *) work_buffer,
                                                    indata_seqnum,
                                                    header_length);
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    if (FSP_SUCCESS != err)
    {
        return NX_CRYPTO_NOT_SUCCESSFUL;
    }

    return NX_CRYPTO_SUCCESS;
}

UINT sce_nx_crypto_ccm_decrypt_update (NX_CRYPTO_AES * crypto_metadata,
                                       UCHAR         * input,
                                       UCHAR         * output,
                                       UINT            length,
                                       UINT            block_size)
{
    uint32_t input_length     = length;
    uint32_t length_remaining = length % NX_CRYPTO_CCM_BLOCK_SIZE;

    /* Check the block size.  */
    if (block_size != NX_CRYPTO_CCM_BLOCK_SIZE)
    {
        return NX_CRYPTO_PTR_ERROR;
    }

    if (length_remaining)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* Handle full/complete block(s) */
    if (0 != input_length)
    {
        if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes128CcmDecryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes192CcmDecryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
 #endif
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes256CcmDecryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
        else
        {
            return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
        }
    }

    return NX_CRYPTO_SUCCESS;
}

UINT sce_nx_crypto_ccm_decrypt_final (NX_CRYPTO_AES * crypto_metadata,
                                      NX_CRYPTO_CCM * ccm_metadata,
                                      UCHAR         * icv,
                                      UINT            block_size)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   work_buffer[NX_CRYPTO_CCM_BLOCK_SIZE] = {0};
    uint32_t  indata_maclength[1] = {0};
    uint32_t  indata_textlen[1]   = {0};

    /* Check the block size.  */
    if (block_size != NX_CRYPTO_CCM_BLOCK_SIZE)
    {
        return NX_CRYPTO_PTR_ERROR;
    }

    NX_CRYPTO_MEMCPY(indata_textlen, ccm_metadata->nx_crypto_ccm_X, sizeof(indata_textlen));
    indata_maclength[0] = change_endian_long(ccm_metadata->nx_crypto_ccm_icv_length);
    NX_CRYPTO_MEMSET(ccm_metadata->nx_crypto_ccm_X, 0, sizeof(ccm_metadata->nx_crypto_ccm_X));

    NX_CRYPTO_MEMSET(work_buffer, 0, sizeof(work_buffer));

    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes128CcmDecryptFinalSubGeneral((uint32_t *) work_buffer,
                                                     indata_textlen,
                                                     (uint32_t *) icv,
                                                     indata_maclength,
                                                     (uint32_t *) work_buffer);
    }

 #if ((BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
       BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes192CcmDecryptFinalSub((uint32_t *) work_buffer,
                                              indata_textlen,
                                              (uint32_t *) icv,
                                              indata_maclength,
                                              (uint32_t *) work_buffer);
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == crypto_metadata->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes256CcmDecryptFinalSub((uint32_t *) work_buffer,
                                              indata_textlen,
                                              (uint32_t *) icv,
                                              indata_maclength,
                                              (uint32_t *) work_buffer);
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    if (FSP_SUCCESS != err)
    {

        /* Authentication failed.  */
        return NX_CRYPTO_AUTHENTICATION_FAILED;
    }

    return NX_CRYPTO_SUCCESS;
}

#endif
