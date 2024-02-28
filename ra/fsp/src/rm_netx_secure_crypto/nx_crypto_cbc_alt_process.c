/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
    NX_CRYPTO_AES * aes_ptr          = (NX_CRYPTO_AES *) crypto_metadata;
    UINT            num_rounds       = aes_ptr->nx_crypto_aes_rounds;
    UINT          * w                = aes_ptr->nx_crypto_aes_key_schedule;
    fsp_err_t       ret              = FSP_ERR_ASSERTION;
    uint32_t        total_length    = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(length);
    uint32_t        process_length  = total_length;
    uint32_t        indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION);
    uint32_t        indata_key_type = 0;

    /* total_length is a multiple of block size, ensured by caller */
    switch (num_rounds)
    {
    case 10:
    {
    	ret = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
    			&indata_cmd,
				(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes128EncryptDecryptFinalSub();
    	break;
    }

#if (1U == BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7 || BSP_FEATURE_CRYPTO_HAS_RSIP7)
    case 12:
    {
    	ret = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd,
    			(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes192EncryptDecryptFinalSub();
    	break;
    }
#endif
    case 14:
    {
    	ret = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type,
    			&indata_cmd,
				(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes256EncryptDecryptFinalSub();
    	break;
    }

    default:
    {
    	break;                 /* Will never get here due to the num_rounds check above. */
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
    NX_CRYPTO_AES * aes_ptr          = (NX_CRYPTO_AES *) crypto_metadata;
    UINT            num_rounds       = aes_ptr->nx_crypto_aes_rounds;
    UINT          * w                = aes_ptr->nx_crypto_aes_key_schedule;
    fsp_err_t       ret              = FSP_ERR_ASSERTION;
    uint32_t        total_length    = RM_NETX_SECURE_CRYPTO_BYTES_TO_WORDS(length);
    uint32_t        process_length  = total_length;
    uint32_t        indata_cmd      = change_endian_long(SCE_AES_IN_DATA_CMD_CBC_DECRYPTION);
    uint32_t        indata_key_type = 0;

    switch (num_rounds)
    {
    case 10:
    {
    	ret = HW_SCE_Aes128EncryptDecryptInitSub(&indata_key_type,
    			&indata_cmd,
				(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes128EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes128EncryptDecryptFinalSub();
    	break;
    }

#if (1U == BSP_FEATURE_CRYPTO_HAS_SCE9 || BSP_FEATURE_CRYPTO_HAS_SCE7 || BSP_FEATURE_CRYPTO_HAS_RSIP7)
    case 12:
    {
    	ret = HW_SCE_Aes192EncryptDecryptInitSub(&indata_cmd,
    			(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes192EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes192EncryptDecryptFinalSub();
    	break;
    }
#endif
    case 14:
    {
    	ret = HW_SCE_Aes256EncryptDecryptInitSub(&indata_key_type,
    			&indata_cmd,
				(uint32_t *) w,
				(uint32_t *) cbc_metadata->nx_crypto_cbc_last_block);
    	if (ret == FSP_SUCCESS)
    	{
    		HW_SCE_Aes256EncryptDecryptUpdateSub((uint32_t *) input,
    				(uint32_t *) output,
					process_length);
    	}

    	ret = HW_SCE_Aes256EncryptDecryptFinalSub();
    	break;
    }

    default:
    {
    	break;                 /* Will never get here due to the num_rounds check above. */
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
