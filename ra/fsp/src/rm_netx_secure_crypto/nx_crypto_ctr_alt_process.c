/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * File Name    : nx_crypto_ctr_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_AES_ALT)
 #include "rm_netx_secure_crypto.h"
 #include "nx_crypto_aes.h"
 #include "nx_crypto_ctr.h"
 #include "hw_sce_aes_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_private.h"

 #define AES_CTR_KEY_SIZE_128_ROUNDS    10
 #define AES_CTR_KEY_SIZE_192_ROUNDS    12
 #define AES_CTR_KEY_SIZE_256_ROUNDS    14
 #define AES_BLOCK_SIZE_WORDS           (4U)
 #define AES_BLOCK_SIZE_BYTES           (AES_BLOCK_SIZE_WORDS * 4U)

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * AES CTR Encryption
 * @retval NX_CRYPTO_SUCCESS              AES encryption using SCE was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       AES encryption using SCE failed.
 **********************************************************************************************************************/
UINT sce_nx_crypto_ctr_encrypt (VOID          * crypto_metadata,
                                NX_CRYPTO_CTR * ctr_metadata,
                                UCHAR         * input,
                                UCHAR         * output,
                                UINT            length)
{
    NX_CRYPTO_AES * aes_ptr          = (NX_CRYPTO_AES *) crypto_metadata;
    uint32_t      * p_aligned_input  = NULL;
    uint32_t      * p_aligned_output = NULL;
    uint8_t       * p_local_input    = input;
    uint8_t       * p_local_output   = output;
    uint32_t        aligned_input_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)]  = {0};
    uint32_t        aligned_output_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)] = {0};
    uint32_t        num_blocks       = length / NX_CRYPTO_CTR_BLOCK_SIZE;
    uint32_t        total_length     = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS((num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE));
    uint32_t        process_length   = total_length;
    bool            misaligned       = false;
    bool            incomplete_block = false;
    fsp_err_t       status;
    uint32_t        bytes_remaining = length % NX_CRYPTO_CTR_BLOCK_SIZE;
    uint32_t        indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION);
    uint32_t        indata_key_type = 0;

    /* Alignment Check */
    if (RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(input) || RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(output))
    {
        p_aligned_input  = aligned_input_buffer;
        p_aligned_output = aligned_output_buffer;
        process_length   = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE);

        /* Setup the first block */
        NX_CRYPTO_MEMCPY((uint8_t *) p_aligned_input, p_local_input, NX_CRYPTO_AES_BLOCK_SIZE);
        misaligned = true;
    }
    else
    {
        p_aligned_input  = (uint32_t *) input;
        p_aligned_output = (uint32_t *) output;
    }

    /* total_length is a multiple of block size */
    while ((total_length != 0U) || (0U != bytes_remaining))
    {
        /* Select the correct method based on the key type and size. */
        switch (aes_ptr->nx_crypto_aes_rounds)
        {
            case AES_CTR_KEY_SIZE_128_ROUNDS:
            {
                status = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
                                                            &indata_cmd,
                                                            (uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                                            (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
                FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t const *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     process_length);
                status = HW_SCE_Aes128EncryptDecryptFinalSub();
                break;
            }

 #if (1U == BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7)
            case AES_CTR_KEY_SIZE_192_ROUNDS:
            {
                status = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd,
                                                            (uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                                            (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
                FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t const *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     process_length);
                status = HW_SCE_Aes192EncryptDecryptFinalSub();
                break;
            }
 #endif
            case AES_CTR_KEY_SIZE_256_ROUNDS:
            {
                status = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type,
                                                            &indata_cmd,
                                                            (uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                                            (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
                FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t const *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     process_length);
                status = HW_SCE_Aes256EncryptDecryptFinalSub();
                break;
            }

            default:
            {
                return NX_CRYPTO_INVALID_PARAMETER;
            }
        }

        FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);

        uint8_t * out_iv = (uint8_t *) ctr_metadata->nx_crypto_ctr_counter_block;
        for (uint32_t i = 0; i < (process_length / sizeof(uint32_t)); i++)
        {
            for (uint32_t j = 16; j > 0; j--)
            {
                if (++out_iv[j - 1] != 0)
                {
                    break;
                }
            }
        }

        if (misaligned)
        {
            NX_CRYPTO_MEMCPY(p_local_output, (uint8_t *) p_aligned_output, NX_CRYPTO_AES_BLOCK_SIZE);

            /* Clear out local buffers */
            NX_CRYPTO_MEMSET((uint8_t *) p_aligned_output, 0, NX_CRYPTO_AES_BLOCK_SIZE);
            NX_CRYPTO_MEMSET((uint8_t *) p_aligned_input, 0, NX_CRYPTO_AES_BLOCK_SIZE);
            total_length -= RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE);

            /* Check if all the misaligned AES blocks are consumed. */
            if (0 != total_length)
            {
                p_local_output += NX_CRYPTO_AES_BLOCK_SIZE;
                p_local_input  += NX_CRYPTO_AES_BLOCK_SIZE;

                /* Setup the next block */
                NX_CRYPTO_MEMCPY((uint8_t *) p_aligned_input, p_local_input, NX_CRYPTO_AES_BLOCK_SIZE);
                continue;
            }
        }
        else
        {
            /* Buffers were aligned, all the encryption with AES block multiples was done in a single call.
             * We still need to check for remaining bytes below. */
            total_length = 0;
        }

        /* Check for remaining bytes. */
        if ((total_length == 0) && (0U != bytes_remaining) && (false == incomplete_block))
        {
            /* If there are bytes remaining, then the last block of data was not a full block. */
            NX_CRYPTO_MEMSET(aligned_input_buffer, 0, sizeof(aligned_input_buffer));
            NX_CRYPTO_MEMSET(aligned_output_buffer, 0, sizeof(aligned_output_buffer));

            /* Copy the remaining data into an aligned buffer. */
            NX_CRYPTO_MEMCPY(aligned_input_buffer, input + num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE, bytes_remaining);
            p_aligned_input  = aligned_input_buffer;
            p_aligned_output = aligned_output_buffer;
            process_length   = NX_CRYPTO_CTR_BLOCK_SIZE / sizeof(uint32_t);
            incomplete_block = true;

            /* We are now only dealing with bytes less than AES blocks. We no longer want to handle misaligned AES blocks if any. */
            misaligned = false;
        }
        else
        {
            break;
        }
    }

    if (true == incomplete_block)
    {
        /* Copy the remaining encrypted data into the provided output buffer. */
        NX_CRYPTO_MEMCPY(output + num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE, aligned_output_buffer, bytes_remaining);
    }

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
