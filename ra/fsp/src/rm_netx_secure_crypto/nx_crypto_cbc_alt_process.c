/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : nx_crypto_cbc_alt_process.c
 * Description  : Functions interfacing with SCE
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "rm_netx_secure_crypto_cfg.h"
#if (1U == NETX_SECURE_CRYPTO_NX_CRYPTO_METHODS_AES_ALT)
 #include "rm_netx_secure_crypto.h"
 #include "nx_crypto_aes.h"
 #include "nx_crypto_cbc.h"
 #include "hw_sce_aes_private.h"
 #include "hw_sce_ra_private.h"
 #include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * @addtogroup RM_NETX_SECURE_CRYPTO
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
 #define AES_BLOCK_SIZE_WORDS    (4U)
 #define AES_BLOCK_SIZE_BYTES    (AES_BLOCK_SIZE_WORDS * 4U)

/***********************************************************************************************************************
 * AES CBC Encryption
 * @retval NX_CRYPTO_SUCCESS              AES encryption using SCE was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       AES encryption using SCE failed.
 **********************************************************************************************************************/
UINT sce_nx_crypto_cbc_encrypt (VOID          * crypto_metadata,
                                NX_CRYPTO_CBC * cbc_metadata,
                                UCHAR         * input,
                                UCHAR         * output,
                                UINT            length)
{
    NX_CRYPTO_AES * aes_ptr         = (NX_CRYPTO_AES *) crypto_metadata;
    UINT            num_rounds      = aes_ptr->nx_crypto_aes_rounds;
    UINT          * w               = aes_ptr->nx_crypto_aes_key_schedule;
    fsp_err_t       ret             = FSP_ERR_ASSERTION;
    uint32_t        total_length    = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(length);
    uint32_t        process_length  = total_length;
    uint32_t        indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION);
    uint32_t        indata_key_type = 0;

    /* total_length is a multiple of block size, ensured by caller */
    switch (num_rounds)
    {
        case 10:
        {
            ret =
                HW_SCE_Aes128EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
            break;
        }

 #if (1U == BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || \
      BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED ||                                     \
      BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
        case 12:
        {
            ret =
                HW_SCE_Aes192EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();
            break;
        }
 #endif
        case 14:
        {
            ret =
                HW_SCE_Aes256EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
            break;
        }

        default:
        {
            break;                     /* Will never get here due to the num_rounds check above. */
        }
    }

    /* Return immediately in case of error */
    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

    NX_CRYPTO_MEMCPY((uint8_t *) cbc_metadata->nx_crypto_cbc_last_block,
                     (uint8_t *) &output[(length - AES_BLOCK_SIZE_BYTES)], AES_BLOCK_SIZE_BYTES);

    return NX_CRYPTO_SUCCESS;
}

/***********************************************************************************************************************
 * AES CBC Decryption
 * @retval NX_CRYPTO_SUCCESS              AES decryption using SCE was successful.
 * @retval NX_CRYPTO_NOT_SUCCESSFUL       AES decryption using SCE failed.
 **********************************************************************************************************************/
UINT sce_nx_crypto_cbc_decrypt (VOID          * crypto_metadata,
                                NX_CRYPTO_CBC * cbc_metadata,
                                UCHAR         * input,
                                UCHAR         * output,
                                UINT            length)
{
    NX_CRYPTO_AES * aes_ptr         = (NX_CRYPTO_AES *) crypto_metadata;
    UINT            num_rounds      = aes_ptr->nx_crypto_aes_rounds;
    UINT          * w               = aes_ptr->nx_crypto_aes_key_schedule;
    fsp_err_t       ret             = FSP_ERR_ASSERTION;
    uint32_t        total_length    = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(length);
    uint32_t        process_length  = total_length;
    uint32_t        indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_DECRYPTION);
    uint32_t        indata_key_type = 0;

    switch (num_rounds)
    {
        case 10:
        {
            ret =
                HW_SCE_Aes128EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes128EncryptDecryptFinalSub();
            break;
        }

 #if (1U == BSP_FEATURE_RSIP_SCE9_SUPPORTED || BSP_FEATURE_RSIP_SCE7_SUPPORTED || \
      BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED ||                                     \
      BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
        case 12:
        {
            ret =
                HW_SCE_Aes192EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes192EncryptDecryptFinalSub();
            break;
        }
 #endif
        case 14:
        {
            ret =
                HW_SCE_Aes256EncryptDecryptInitSubAdaptor(&indata_key_type, &indata_cmd, (uint32_t *) w, NULL,
                                                          (uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
            if (ret == FSP_SUCCESS)
            {
                HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) input, (uint32_t *) output, process_length);
            }

            ret = HW_SCE_Aes256EncryptDecryptFinalSub();
            break;
        }

        default:
        {
            break;                     /* Will never get here due to the num_rounds check above. */
        }
    }

    /* Return immediately in case of error */
    FSP_ERROR_RETURN((FSP_SUCCESS == ret), NX_CRYPTO_NOT_SUCCESSFUL);

    NX_CRYPTO_MEMCPY((uint8_t *) cbc_metadata->nx_crypto_cbc_last_block,
                     (uint8_t *) &input[(length - AES_BLOCK_SIZE_BYTES)], AES_BLOCK_SIZE_BYTES);

    return NX_CRYPTO_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_NETX_SECURE_CRYPTO)
 **********************************************************************************************************************/

#endif
