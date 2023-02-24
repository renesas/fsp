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
 * File Name    : nx_crypto_gcm_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#include "rm_netx_secure_crypto.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_AES_ALT) && (((BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7) == 1) || \
    (BSP_FEATURE_CRYPTO_HAS_SCE5B == 1))
 #include "nx_crypto_aes.h"
 #include "hw_sce_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_aes_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define RM_NETX_SECURE_CRYPTO_SCE9_AES_GCM_KEY_TYPE_GENERAL       (0)
 #define RM_NETX_SECURE_CRYPTO_FINAL_DONE_FLAG                     (0x47434d4649) /* ASCII: GCMF */
 #define RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS                (NX_CRYPTO_GCM_BLOCK_SIZE >> 2U)
 #define RM_NETX_SECURE_CRYPTO_BIT_FIELD_SIZE_BYTES                (8U)
 #define RM_NETX_SECURE_CRYPTO_DATA_SIZE_BIT_FIELD_OFFSET_WORDS    (2U)

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

static UINT sce_nx_crypto_gcm_encrypt_final(NX_CRYPTO_AES * aes_ctx,
                                            uint32_t      * bit_size,
                                            uint32_t      * input,
                                            uint32_t      * output,
                                            uint32_t      * tag);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Generate GHASH
 * @retval NX_CRYPTO_SUCCESS              GHASH generation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to generate GHASH.
 **********************************************************************************************************************/
UINT sce_nx_crypto_gcm_ghash_update (UCHAR * hkey, UCHAR * input, UINT input_length, UCHAR * output)
{
    fsp_err_t err         = FSP_SUCCESS;
    uint32_t  length_rest = input_length % NX_CRYPTO_GCM_BLOCK_SIZE;

    if (NX_CRYPTO_GCM_BLOCK_SIZE <= input_length)
    {
        /* Generate GHASH for all complete blocks within input_length */
        err =
            HW_SCE_Ghash((uint32_t *) hkey,
                         (uint32_t *) output,
                         (uint32_t *) input,
                         (uint32_t *) output,
                         (input_length / NX_CRYPTO_GCM_BLOCK_SIZE) *
                         RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_GCM_BLOCK_SIZE));
    }

    /* Generate GHASH for all remaining partial IV block. Pad with 0 to create complete block. */
    if ((0U != length_rest) && (FSP_SUCCESS == err))
    {
        uint32_t tmp[4] = {0};
        NX_CRYPTO_MEMCPY(tmp, input + (input_length - length_rest), length_rest);
        err =
            HW_SCE_Ghash((uint32_t *) hkey,
                         (uint32_t *) output,
                         tmp,
                         (uint32_t *) output,
                         RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_GCM_BLOCK_SIZE));
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * GCM Init - initialize and set AAD for encryption
 * @retval NX_CRYPTO_SUCCESS              GCM initialization was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to perform GCM initialization.
 * @retval NX_CRYPTO_UNSUPPORTED_KEY_SIZE Invalid Key size
 **********************************************************************************************************************/
UINT sce_nx_crypto_gcm_encrypt_init (NX_CRYPTO_AES * aes_ctx,
                                     UCHAR         * hashed_ivec,
                                     VOID          * additional_data,
                                     UINT            additional_len)
{
    fsp_err_t  err              = FSP_SUCCESS;
    uint32_t   key_type[1]      = {RM_NETX_SECURE_CRYPTO_SCE9_AES_GCM_KEY_TYPE_GENERAL};
    uint32_t   length_remaining = 0;
    uint32_t   input_length     = additional_len;
    uint8_t    work_buffer[NX_CRYPTO_GCM_BLOCK_SIZE] = {0};
    uint32_t * aad = (uint32_t *) additional_data;
    length_remaining = additional_len % NX_CRYPTO_GCM_BLOCK_SIZE;
    input_length    -= length_remaining;

    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes128GcmEncryptInitSub(key_type,
                                             (uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                             (uint32_t *) hashed_ivec);
        if (FSP_SUCCESS == err)
        {
            HW_SCE_Aes128GcmEncryptUpdateAADSub(aad, RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
            if (length_remaining > 0)
            {
                /* Pad the last incomplete block of aad data with zeroes to create a complete block */
                NX_CRYPTO_MEMCPY(work_buffer, &aad[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length)],
                                 length_remaining);
                HW_SCE_Aes128GcmEncryptUpdateAADSub((uint32_t *) work_buffer,
                                                    RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_GCM_BLOCK_SIZE));
            }

            HW_SCE_Aes128GcmEncryptUpdateTransitionSub();
        }
    }

 #if ((BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes192GcmEncryptInitSub((uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                             (uint32_t *) hashed_ivec);
        if (FSP_SUCCESS == err)
        {
            HW_SCE_Aes192GcmEncryptUpdateAADSub(aad, RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
            if (length_remaining > 0)
            {
                /* Pad the last incomplete block of aad data with zeroes to create a complete block */
                NX_CRYPTO_MEMCPY(work_buffer, &aad[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length)],
                                 length_remaining);
                HW_SCE_Aes192GcmEncryptUpdateAADSub((uint32_t *) work_buffer,
                                                    RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_GCM_BLOCK_SIZE));
            }

            HW_SCE_Aes192GcmEncryptUpdateTransitionSub();
        }
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes256GcmEncryptInitSub(key_type,
                                             (uint32_t *) (aes_ctx->nx_crypto_aes_key_schedule),
                                             (uint32_t *) hashed_ivec);
        if (FSP_SUCCESS == err)
        {
            HW_SCE_Aes256GcmEncryptUpdateAADSub(aad, RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
            if (length_remaining > 0)
            {
                /* Pad the last incomplete block of aad data with zeroes to create a complete block */
                NX_CRYPTO_MEMCPY(work_buffer, &aad[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length)],
                                 length_remaining);
                HW_SCE_Aes256GcmEncryptUpdateAADSub((uint32_t *) work_buffer,
                                                    RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_GCM_BLOCK_SIZE));
            }

            HW_SCE_Aes256GcmEncryptUpdateTransitionSub();
        }
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * GCM Encrypt Update
 * @retval NX_CRYPTO_SUCCESS              GCM initialization was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to perform GCM initialization.
 * @retval NX_CRYPTO_UNSUPPORTED_KEY_SIZE Invalid Key size
 **********************************************************************************************************************/
UINT sce_nx_crypto_gcm_encrypt_update (NX_CRYPTO_AES * aes_ctx, UCHAR * input, UCHAR * output, UINT length)
{
    UINT     err              = NX_CRYPTO_SUCCESS;
    uint32_t input_length     = length;
    uint32_t length_remaining = length % NX_CRYPTO_GCM_BLOCK_SIZE;
    input_length -= length_remaining;

    /* Handle full/complete block(s) */
    if (0 != input_length)
    {
        if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes128GcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }

 #if ((BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7) == 1)
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes192GcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
 #endif
        else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
        {
            HW_SCE_Aes256GcmEncryptUpdateSub((uint32_t *) input,
                                             (uint32_t *) output,
                                             RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(input_length));
        }
        else
        {
            return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
        }
    }

    /* Handle partial block.
     * Since a partial block is passed to this function, this is the last block.
     * Call final to handle the partial block and generate the authentication tag.
     */
    if (length_remaining > 0)
    {
        uint32_t        partial_block_input[RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS]  = {0};
        uint32_t        partial_block_output[RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS] = {0};
        NX_CRYPTO_GCM * p_gcm_metadata  = &(aes_ctx->nx_crypto_aes_mode_context.gcm);
        uint32_t      * final_done_flag = (uint32_t *) p_gcm_metadata->nx_crypto_gcm_counter;
        uint32_t        total_len       = p_gcm_metadata->nx_crypto_gcm_input_total_length + length;
        uint32_t        aad_len         = p_gcm_metadata->nx_crypto_gcm_additional_data_len;

        /* Store the tag in the context buffer */
        uint8_t * tag = p_gcm_metadata->nx_crypto_gcm_s;
        uint32_t  aligned_tag[RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS] = {0};
        uint32_t  bit_size[4] = {0};
        NX_CRYPTO_MEMSET(tag, 0, NX_CRYPTO_GCM_BLOCK_SIZE);

        /* Pad the last incomplete block of plaintext/cipher data with zeroes to create a complete block */
        NX_CRYPTO_MEMCPY((uint8_t *) partial_block_input, &input[input_length], length_remaining);

        /* Set up bit sizes for AAD and plaintext */
        /* Store carry in word 0 if the aad_len is larger than 2^29 */
        bit_size[0] = change_endian_long((aad_len & 0xe000000U) >> 29U);
        bit_size[1] = change_endian_long(aad_len << 3U);

        /* Store carry in word 0 if the length is larger than 2^29 */
        bit_size[2] = change_endian_long((total_len & 0xe000000U) >> 29U);
        bit_size[3] = change_endian_long(total_len << 3U);
        err         = sce_nx_crypto_gcm_encrypt_final(aes_ctx,
                                                      bit_size,
                                                      partial_block_input,
                                                      partial_block_output,
                                                      aligned_tag);
        if (NX_CRYPTO_SUCCESS != err)
        {
            return err;
        }

        NX_CRYPTO_MEMCPY(&output[input_length], (uint8_t *) partial_block_output, length_remaining);
        NX_CRYPTO_MEMCPY(tag, (uint8_t *) aligned_tag, NX_CRYPTO_GCM_BLOCK_SIZE);

        /* Store final done status in context */
        final_done_flag[0] = (uint32_t) RM_NETX_SECURE_CRYPTO_FINAL_DONE_FLAG;
    }

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * GCM Decrypt Update
 * @retval NX_CRYPTO_SUCCESS              GCM initialization was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to perform GCM initialization.
 * @retval NX_CRYPTO_UNSUPPORTED_KEY_SIZE Invalid Key size
 **********************************************************************************************************************/
UINT sce_nx_crypto_gcm_encrypt_calculate (NX_CRYPTO_AES * aes_ctx, UCHAR * bit_size, UINT icv_len, UCHAR * tag)
{
    NX_CRYPTO_GCM * p_gcm_metadata  = &(aes_ctx->nx_crypto_aes_mode_context.gcm);
    uint32_t      * final_done_flag = (uint32_t *) p_gcm_metadata->nx_crypto_gcm_counter;
    if ((uint32_t) RM_NETX_SECURE_CRYPTO_FINAL_DONE_FLAG == final_done_flag[0])
    {
        uint8_t * tag_computed_in_update = p_gcm_metadata->nx_crypto_gcm_s;
        NX_CRYPTO_MEMCPY(tag, tag_computed_in_update, icv_len);
    }
    else
    {
        uint32_t aligned_tag[RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS]      = {0};
        uint32_t aligned_bit_size[RM_NETX_SECURE_CRYPTO_GCM_BLOCK_SIZE_WORDS] = {0};
        NX_CRYPTO_MEMCPY((uint8_t *) aligned_bit_size, bit_size, NX_CRYPTO_GCM_BLOCK_SIZE);
        UINT err = sce_nx_crypto_gcm_encrypt_final(aes_ctx, aligned_bit_size, NULL, NULL, aligned_tag);
        if (NX_CRYPTO_SUCCESS != err)
        {
            return err;
        }

        NX_CRYPTO_MEMCPY(tag, (uint8_t *) aligned_tag, icv_len);
    }

    return NX_CRYPTO_SUCCESS;
}

static UINT sce_nx_crypto_gcm_encrypt_final (NX_CRYPTO_AES * aes_ctx,
                                             uint32_t      * bit_size,
                                             uint32_t      * input,
                                             uint32_t      * output,
                                             uint32_t      * tag)
{
    fsp_err_t err              = FSP_SUCCESS;
    uint32_t  aad_bit_size[2]  = {0};
    uint32_t  data_bit_size[2] = {0};
    NX_CRYPTO_MEMCPY(aad_bit_size, bit_size, RM_NETX_SECURE_CRYPTO_BIT_FIELD_SIZE_BYTES);
    NX_CRYPTO_MEMCPY(data_bit_size,
                     &bit_size[RM_NETX_SECURE_CRYPTO_DATA_SIZE_BIT_FIELD_OFFSET_WORDS],
                     RM_NETX_SECURE_CRYPTO_BIT_FIELD_SIZE_BYTES);
    if (SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes128GcmEncryptFinalSub(input, aad_bit_size, data_bit_size, output, tag);
    }

 #if ((BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7) == 1)
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes192GcmEncryptFinalSub(input, aad_bit_size, data_bit_size, output, tag);
    }
 #endif
    else if (SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS == aes_ctx->nx_crypto_aes_key_size)
    {
        err = HW_SCE_Aes256GcmEncryptFinalSub(input, aad_bit_size, data_bit_size, output, tag);
    }
    else
    {
        return NX_CRYPTO_UNSUPPORTED_KEY_SIZE;
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/
#endif
