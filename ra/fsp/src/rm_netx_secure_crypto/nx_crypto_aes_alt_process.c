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
 * File Name    : nx_crypto_aes_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_AES_ALT)
 #include "rm_netx_secure_crypto.h"
 #include "hw_sce_aes_private.h"
 #include "nx_crypto_aes.h"
 #include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * AES ECB Encryption
 * @retval NX_CRYPTO_SUCCESS              AES encryption using SCE was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       AES encryption using SCE failed.
 **********************************************************************************************************************/
UINT sce_nx_crypto_aes_encrypt (NX_CRYPTO_AES * aes_ptr, UCHAR * input, UCHAR * output, UINT length)
{
    UINT       num_rounds       = aes_ptr->nx_crypto_aes_rounds;
    fsp_err_t  ret              = FSP_ERR_ASSERTION;
    UINT     * w                = aes_ptr->nx_crypto_aes_key_schedule;
    uint32_t * p_aligned_input  = NULL;
    uint32_t * p_aligned_output = NULL;
    uint32_t   aligned_input_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)]  = {0};
    uint32_t   aligned_output_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)] = {0};
    bool       misaligned      = false;
    uint32_t   dummy_iv[4]     = {0};
    uint32_t   indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION);
    uint32_t   indata_key_type = 0;

    if (length != NX_CRYPTO_AES_BLOCK_SIZE)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* Alignment Check */
    if (RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(input) || RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(output))
    {
        p_aligned_input  = aligned_input_buffer;
        p_aligned_output = aligned_output_buffer;

        /* Setup the cipher block */
        NX_CRYPTO_MEMCPY((uint8_t *) p_aligned_input, input, NX_CRYPTO_AES_BLOCK_SIZE);
        misaligned = true;
    }
    else
    {
        p_aligned_input  = (uint32_t *) input;
        p_aligned_output = (uint32_t *) output;
    }

    switch (num_rounds)
    {
        case 10:
        {
            ret = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
            break;
        }

 #if (1U == BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7)
        case 12:
        {
            ret = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();

            break;
        }
 #endif
        case 14:
        {
            ret = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
            break;
        }

        default:
        {
            break;                     /* Will never get here due to the num_rounds check by the caller. */
        }
    }

    /* Return immediately in case of error */
    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

    if (misaligned)
    {
        NX_CRYPTO_MEMCPY(output, (uint8_t *) p_aligned_output, NX_CRYPTO_AES_BLOCK_SIZE);

        /* Clear out local buffers */
        NX_CRYPTO_MEMSET((uint8_t *) p_aligned_output, 0, NX_CRYPTO_AES_BLOCK_SIZE);
        NX_CRYPTO_MEMSET((uint8_t *) p_aligned_input, 0, NX_CRYPTO_AES_BLOCK_SIZE);
    }

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * AES ECB Decryption
 * @retval NX_CRYPTO_SUCCESS              AES decryption using SCE was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       AES decryption using SCE failed.
 **********************************************************************************************************************/
UINT sce_nx_crypto_aes_decrypt (NX_CRYPTO_AES * aes_ptr, UCHAR * input, UCHAR * output, UINT length)
{
    UINT       num_rounds       = aes_ptr->nx_crypto_aes_rounds;
    fsp_err_t  ret              = FSP_ERR_ASSERTION;
    UINT     * w                = aes_ptr->nx_crypto_aes_key_schedule;
    uint32_t * p_aligned_input  = NULL;
    uint32_t * p_aligned_output = NULL;
    uint32_t   aligned_input_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)]  = {0};
    uint32_t   aligned_output_buffer[RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE)] = {0};
    bool       misaligned      = false;
    uint32_t   dummy_iv[4]     = {0};
    uint32_t   indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_ECB_DECRYPTION);
    uint32_t   indata_key_type = 0;

    if (length != NX_CRYPTO_AES_BLOCK_SIZE)
    {
        return NX_CRYPTO_SIZE_ERROR;
    }

    /* Alignment Check */
    if (RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(input) || RM_NETX_SECURE_CRYPTO_NONALIGNMENT_CHECK(output))
    {
        p_aligned_input  = aligned_input_buffer;
        p_aligned_output = aligned_output_buffer;

        /* Setup the cipher block */
        NX_CRYPTO_MEMCPY((uint8_t *) p_aligned_input, input, NX_CRYPTO_AES_BLOCK_SIZE);
        misaligned = true;
    }
    else
    {
        p_aligned_input  = (uint32_t *) input;
        p_aligned_output = (uint32_t *) output;
    }

    switch (num_rounds)
    {
        case 10:
        {
            ret = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
            break;
        }

 #if (1U == BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7)
        case 12:
        {
            ret = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();

            break;
        }
 #endif
        case 14:
        {
            ret = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type, &indata_cmd, (uint32_t *) w, dummy_iv);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) p_aligned_input,
                                                     (uint32_t *) p_aligned_output,
                                                     RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(NX_CRYPTO_AES_BLOCK_SIZE));
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
            break;
        }

        default:
        {
            break;                     /* Will never get here due to the num_rounds check by the caller. */
        }
    }

    /* Return immediately in case of error */
    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

    if (misaligned)
    {
        NX_CRYPTO_MEMCPY(output, (uint8_t *) p_aligned_output, NX_CRYPTO_AES_BLOCK_SIZE);

        /* Clear out local buffers */
        NX_CRYPTO_MEMSET((uint8_t *) p_aligned_output, 0, NX_CRYPTO_AES_BLOCK_SIZE);
        NX_CRYPTO_MEMSET((uint8_t *) p_aligned_input, 0, NX_CRYPTO_AES_BLOCK_SIZE);
    }

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * AES Key Set - Converts input plain key into wrapped key and stores it in the operation context.
 * @retval NX_CRYPTO_SUCCESS              AES set key operation was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       Failed to convert plain key into wrapped key.
 **********************************************************************************************************************/
UINT sce_nx_crypto_aes_key_set (NX_CRYPTO_AES * aes_ptr, UCHAR * key, UINT key_size)
{
    sce_oem_cmd_t cmd = SCE_OEM_CMD_NUM;

    /* Set the AES key size (should be in 32-bit *words*). */
    UINT      key_length = key_size;
    fsp_err_t ret        = FSP_SUCCESS;

    UCHAR * user_key = (UCHAR *) aes_ptr->nx_crypto_aes_key_schedule;

    /* Based on the key size, determine the number of rounds.
     * NX_CRYPTO_AES_KEY_SIZE_<size>_BITS specifies key length in Words.
     */
    switch (key_length)
    {
        /* Cannot use fall-through as it would generates warnings. */
        case NX_CRYPTO_AES_KEY_SIZE_128_BITS:
        {
            key_length = (USHORT) SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS;
            cmd        = SCE_OEM_CMD_AES128;
            aes_ptr->nx_crypto_aes_rounds = 10;
            break;
        }

        case SCE_NX_CRYPTO_AES_KEY_SIZE_128_WRAPPED_WORDS:
        {
            aes_ptr->nx_crypto_aes_rounds = 10;
            break;
        }

        case NX_CRYPTO_AES_KEY_SIZE_192_BITS:
        {
            key_length = (USHORT) SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS;
            cmd        = SCE_OEM_CMD_AES192;
            aes_ptr->nx_crypto_aes_rounds = 12;
            break;
        }

        case SCE_NX_CRYPTO_AES_KEY_SIZE_192_WRAPPED_WORDS:
        {
            aes_ptr->nx_crypto_aes_rounds = 12;
            break;
        }

        case NX_CRYPTO_AES_KEY_SIZE_256_BITS:
        {
            key_length = (USHORT) SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS;
            cmd        = SCE_OEM_CMD_AES256;
            aes_ptr->nx_crypto_aes_rounds = 14;
            break;
        }

        case SCE_NX_CRYPTO_AES_KEY_SIZE_256_WRAPPED_WORDS:
        {
            aes_ptr->nx_crypto_aes_rounds = 14;
            break;
        }

        default:
        {
            ret = FSP_ERR_ASSERTION;
            break;
        }
    }

    /* Check if we found a valid key */
    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);
    aes_ptr->nx_crypto_aes_key_size = (USHORT) key_length;
    if (cmd == SCE_OEM_CMD_NUM)
    {
        /* Copy the key into the beginning of the expanded key buffer. */
        NX_CRYPTO_MEMCPY(user_key, key, (key_length << 2));
    }
    else
    {
        ret =
            HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN, cmd, NULL, NULL, key, (uint32_t *) user_key);
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
