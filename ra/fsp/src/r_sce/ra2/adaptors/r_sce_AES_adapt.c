/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 05.10.2020 1.00        First Release.
 *         : 02.12.2020 1.01        Added new functions such as the Brainpool curve.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static uint32_t InputData_KeyType;
static uint32_t InputData_Cmd;
static uint32_t InputData_KeyIndex[44] /*[SIZE_AES_256BIT_KEYLEN_BYTES]*/;
static uint32_t InputData_IV[16];

uint32_t change_endian_long (uint32_t a)
{
    return __REV(a);
}

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);

    return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    InputData_KeyType = *(InData_KeyType);

    if (InputData_KeyType != 0U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    InputData_Cmd = *(InData_Cmd);

    memcpy(InputData_KeyIndex, InData_KeyIndex, sizeof(InputData_KeyIndex[0]) * 16U);

    memcpy(InputData_IV, InData_IV, sizeof(InputData_IV));

    return FSP_SUCCESS;
}

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    switch (change_endian_long(InputData_Cmd))
    {
        case SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION:
        {
            HW_SCE_AES_128EcbEncrypt((uint32_t *) &InputData_KeyIndex[0], MAX_CNT, InData_Text, OutData_Text);
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_DECRYPTION:
        {
            HW_SCE_AES_128EcbDecrypt((uint32_t *) &InputData_KeyIndex[0], MAX_CNT, InData_Text, OutData_Text);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION:
        {
            HW_SCE_AES_128CbcEncrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_DECRYPTION:
        {
            HW_SCE_AES_128CbcDecrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION:
        {
            HW_SCE_AES_128CtrEncrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }
    }
}

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    memset(InputData_KeyIndex, 0U, sizeof(InputData_KeyIndex));
    memset(InputData_IV, 0U, sizeof(InputData_IV));

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    InputData_KeyType = *(InData_KeyType);
    if (InputData_KeyType != 0U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    InputData_Cmd = *(InData_Cmd);

    memcpy(InputData_KeyIndex, InData_KeyIndex, sizeof(InputData_KeyIndex[0]) * 32U);
    memcpy(InputData_IV, InData_IV, sizeof(InputData_IV));

    return FSP_SUCCESS;
}

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    switch (change_endian_long(InputData_Cmd))
    {
        case SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION:
        {
            HW_SCE_AES_256EcbEncrypt((uint32_t *) &InputData_KeyIndex[0], MAX_CNT, InData_Text, OutData_Text);
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_DECRYPTION:
        {
            HW_SCE_AES_256EcbDecrypt((uint32_t *) &InputData_KeyIndex[0], MAX_CNT, InData_Text, OutData_Text);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION:
        {
            HW_SCE_AES_256CbcEncrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_DECRYPTION:
        {
            HW_SCE_AES_256CbcDecrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }

        case SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION:
        {
            HW_SCE_AES_256CtrEncrypt((uint32_t *) &InputData_KeyIndex[0],
                                     &InputData_IV[0],
                                     MAX_CNT,
                                     InData_Text,
                                     OutData_Text,
                                     &InputData_IV[0]);
            break;
        }
    }
}

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    memset(InputData_KeyIndex, 0U, sizeof(InputData_KeyIndex));
    memset(InputData_IV, 0U, sizeof(InputData_IV));

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_KeyIndex[],
                                                     const uint32_t InData_Key[],
                                                     const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_Key);

    return HW_SCE_Aes128EncryptDecryptInitSub(InData_KeyMode, InData_Cmd, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_KeyIndex[],
                                                     const uint32_t InData_Key[],
                                                     const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_KeyMode);
    FSP_PARAMETER_NOT_USED(InData_Key);

    return HW_SCE_Aes192EncryptDecryptInitSub(InData_Cmd, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_KeyIndex[],
                                                     const uint32_t InData_Key[],
                                                     const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_Key);

    return HW_SCE_Aes256EncryptDecryptInitSub(InData_KeyMode, InData_Cmd, InData_KeyIndex, InData_IV);
}
