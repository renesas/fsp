/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 #include "hw_sce_private.h"

 #define AES_CTR_KEY_SIZE_128_ROUNDS    10
 #define AES_CTR_KEY_SIZE_192_ROUNDS    12
 #define AES_CTR_KEY_SIZE_256_ROUNDS    14

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
    NX_CRYPTO_AES * aes_ptr = (NX_CRYPTO_AES *) crypto_metadata;

    fsp_err_t (* aes_ctr_method)(const uint32_t *, const uint32_t *, const uint32_t, const uint32_t *, uint32_t *,
                                 uint32_t *) = NULL;

    /* Select the correct method based on the key type and size. */
    switch (aes_ptr->nx_crypto_aes_rounds)
    {
        case AES_CTR_KEY_SIZE_128_ROUNDS:
        {
 #if (BSP_FEATURE_CRYPTO_HAS_SCE9 == 0)
            if (aes_ptr->nx_crypto_aes_reserved != (UCHAR) SCE_OEM_KEY_TYPE_ENCRYPTED)
            {
                aes_ctr_method = HW_SCE_AES_128CtrEncrypt;
            }
            else
 #endif
            {
                aes_ctr_method = HW_SCE_AES_128CtrEncryptUsingEncryptedKey;
            }

            break;
        }

 #if (BSP_FEATURE_CRYPTO_HAS_SCE9 == 1)
        case AES_CTR_KEY_SIZE_192_ROUNDS:
        {
            aes_ctr_method = HW_SCE_AES_192CtrEncryptUsingEncryptedKey;
            break;
        }
 #endif
        case AES_CTR_KEY_SIZE_256_ROUNDS:
        {
 #if (BSP_FEATURE_CRYPTO_HAS_SCE9 == 0)
            if (aes_ptr->nx_crypto_aes_reserved != (UCHAR) SCE_OEM_KEY_TYPE_ENCRYPTED)
            {
                aes_ctr_method = HW_SCE_AES_256CtrEncrypt;
            }
            else
 #endif
            {
                aes_ctr_method = HW_SCE_AES_256CtrEncryptUsingEncryptedKey;
            }

            break;
        }

        default:
        {
            return NX_CRYPTO_INVALID_PARAMETER;
        }
    }

    uint32_t num_blocks      = length / NX_CRYPTO_CTR_BLOCK_SIZE;
    uint32_t bytes_remaining = length - num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE;

    fsp_err_t status;

    if (RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(input) || RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(output))
    {
        /* If the input or output buffer is unaligned, then the data must be copied into an aligned buffer before
         * it can be encrypted using hardware acceleration. */
        uint8_t aligned_input_buffer[NX_CRYPTO_CTR_BLOCK_SIZE]  = {0};
        uint8_t aligned_output_buffer[NX_CRYPTO_CTR_BLOCK_SIZE] = {0};

        for (uint32_t i = 0; i < num_blocks; i++)
        {
            uint32_t buffer_offset = i * NX_CRYPTO_CTR_BLOCK_SIZE;

            /* Copy the next block of data into the aligned buffer. */
            NX_CRYPTO_MEMCPY(aligned_input_buffer, input + buffer_offset, NX_CRYPTO_CTR_BLOCK_SIZE);

            /* Encrypt/Decrypt the next block of data. */
            status = aes_ctr_method((uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                    (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block,
                                    NX_CRYPTO_CTR_BLOCK_SIZE / sizeof(uint32_t),
                                    (uint32_t const *) aligned_input_buffer,
                                    (uint32_t *) aligned_output_buffer,
                                    (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
            FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);

            /* Copy the encrypted block into the provided output buffer. */
            NX_CRYPTO_MEMCPY(output + buffer_offset, aligned_output_buffer, NX_CRYPTO_CTR_BLOCK_SIZE);
        }
    }
    else if (num_blocks > 0)
    {
        /* If the input and output buffers are aligned, then the data can be encrypted/decrypted in one call. */
        status = aes_ctr_method((uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block,
                                num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE / sizeof(uint32_t),
                                (uint32_t *) input,
                                (uint32_t *) output,
                                (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
        FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);
    }

    if (0U != bytes_remaining)
    {
        /* If there are bytes remaining, then the last block of data was not a full block. */
        uint8_t last_input_block[NX_CRYPTO_CTR_BLOCK_SIZE]  = {0};
        uint8_t last_output_block[NX_CRYPTO_CTR_BLOCK_SIZE] = {0};

        /* Copy the remaining data into an aligned buffer. */
        NX_CRYPTO_MEMCPY(last_input_block, input + num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE, bytes_remaining);

        /* Encrypt/decrypt the remaining data. */
        status = aes_ctr_method((uint32_t *) aes_ptr->nx_crypto_aes_key_schedule,
                                (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block,
                                NX_CRYPTO_CTR_BLOCK_SIZE / sizeof(uint32_t),
                                (uint32_t const *) last_input_block,
                                (uint32_t *) last_output_block,
                                (uint32_t *) ctr_metadata->nx_crypto_ctr_counter_block);
        FSP_ERROR_RETURN((FSP_SUCCESS == status), NX_CRYPTO_NOT_SUCCESSFUL);

        /* Copy the remaining encrypted data into the provided output buffer. */
        NX_CRYPTO_MEMCPY(output + num_blocks * NX_CRYPTO_CTR_BLOCK_SIZE, last_output_block, bytes_remaining);
    }

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
