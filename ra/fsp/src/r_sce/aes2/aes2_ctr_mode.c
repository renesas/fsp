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
