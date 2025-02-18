/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

#include "bsp_api.h"
#include "hw_sce_aes_private.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Global variables and functions
 ***********************************************************************************************************************/

fsp_err_t HW_SCE_AES_128CtrEncrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    fsp_err_t iret = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(OutData_IV);
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0) || (num_words == 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_128_ENC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_128BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}

fsp_err_t HW_SCE_AES_192CtrEncrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    fsp_err_t iret = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(OutData_IV);
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0) || (num_words == 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_192_ENC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_192BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}

fsp_err_t HW_SCE_AES_256CtrEncrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    fsp_err_t iret = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(OutData_IV);
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0) || (num_words == 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_256_ENC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_256BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}

fsp_err_t HW_SCE_AES_128CtrDecrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    fsp_err_t iret = FSP_SUCCESS;
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_128_DEC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_128BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}

fsp_err_t HW_SCE_AES_192CtrDecrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    fsp_err_t iret = FSP_SUCCESS;
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_192_DEC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_192BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}

fsp_err_t HW_SCE_AES_256CtrDecrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    fsp_err_t iret = FSP_SUCCESS;
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Key == (const uint32_t *) 0) ||
        ((InData_IV == (const uint32_t *) 0) || (InData_Text == (const uint32_t *) 0)) ||
        (OutData_Text == (const uint32_t *) 0))
    {
        iret = FSP_ERR_INVALID_ARGUMENT;
    }
#endif

    R_AES_B->AESCNTL = R_AES_AESCNTL_CTR_256_DEC;
    hw_aes_set_key((uint8_t *) InData_Key, SIZE_AES_256BIT_KEYLEN_BYTES);

    if (FSP_SUCCESS == iret)
    {
        hw_aes_set_iv((uint8_t *) InData_IV);
        R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
        hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, num_words);
    }

    return iret;
}
