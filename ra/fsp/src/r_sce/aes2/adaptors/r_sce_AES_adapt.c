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
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "hw_sce_ra_private.h"
#include "tinycrypt/gcm_mode.h"
#include <tinycrypt/utils.h>
#include "bsp_api.h"
#include <stdint.h>

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Imported global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

static uint8_t InputData_DataA[SIZE_AES_GCM_IN_DATA_AAD_LEN_BYTES];
static uint8_t InputData_IV_GCM[SIZE_AES_GCM_IN_DATA_IV_GCM_LEN_BYTES];

uint32_t change_endian_long (uint32_t a)
{
    return __REV(a);
}

/***********************************************************************************************************************
 * Function Name: tc_aes_set_key
 * Description  : This function move the key from specified address (1st arg "key" to AES peripheral register with define
 *       length (2nd arg "KeyLen")
 * Arguments    :   key     :   key data area
 *                  KeyLen  :   key length in bits
 * Return Value : None
 ***********************************************************************************************************************/
void tc_aes_set_key (uint8_t * key, uint32_t KeyLen)
{
    uint16_t * ptr = (uint16_t *) key;

    if (KeyLen > SIZE_AES_192BIT_KEYLEN_BYTES)
    {
        R_AES_B->AESKEY7.AESKEYH = *ptr;
        R_AES_B->AESKEY7.AESKEYL = *(ptr + 1);
        R_AES_B->AESKEY6.AESKEYH = *(ptr + 2);
        R_AES_B->AESKEY6.AESKEYL = *(ptr + 3);
        ptr += 4;
    }

    if (KeyLen > SIZE_AES_128BIT_KEYLEN_BYTES)
    {
        R_AES_B->AESKEY5.AESKEYH = *ptr;
        R_AES_B->AESKEY5.AESKEYL = *(ptr + 1);
        R_AES_B->AESKEY4.AESKEYH = *(ptr + 2);
        R_AES_B->AESKEY4.AESKEYL = *(ptr + 3);
        ptr += 4;
    }

    R_AES_B->AESKEY3.AESKEYH = *ptr;
    R_AES_B->AESKEY3.AESKEYL = *(ptr + 1);
    R_AES_B->AESKEY2.AESKEYH = *(ptr + 2);
    R_AES_B->AESKEY2.AESKEYL = *(ptr + 3);
    R_AES_B->AESKEY1.AESKEYH = *(ptr + 4);
    R_AES_B->AESKEY1.AESKEYL = *(ptr + 5);
    R_AES_B->AESKEY0.AESKEYH = *(ptr + 6);
    R_AES_B->AESKEY0.AESKEYL = *(ptr + 7);
}

/***********************************************************************************************************************
 * Function Name: tc_aes_set_iv
 * Description  : This function move Initialize vector from specified address (1st arg. "iv") to AES register.
 * Arguments    : iv    :   Initialization vector area (16 byte)
 * Return Value : None
 ***********************************************************************************************************************/
void tc_aes_set_iv (uint8_t * initialize_vector)
{
    uint16_t * p_in = (uint16_t *) initialize_vector;

    R_AES_B->AESIV3.AESIVH = *p_in;
    R_AES_B->AESIV3.AESIVL = *(p_in + 1);
    R_AES_B->AESIV2.AESIVH = *(p_in + 2);
    R_AES_B->AESIV2.AESIVL = *(p_in + 3);
    R_AES_B->AESIV1.AESIVH = *(p_in + 4);
    R_AES_B->AESIV1.AESIVL = *(p_in + 5);
    R_AES_B->AESIV0.AESIVH = *(p_in + 6);
    R_AES_B->AESIV0.AESIVL = *(p_in + 7);
}

/***********************************************************************************************************************
 * Function Name: tc_aes_set_plaintext
 * Description  : This function move input test from specified address(1st arg. "ptext") to AES Data Input register.
 * Arguments    : ptext :   Input data area (block * 16bytes)
 * Return Value : None
 ***********************************************************************************************************************/
static void tc_aes_set_plaintext (uint8_t * ptext)
{
    uint16_t * p_in = (uint16_t *) ptext;

    R_AES_B->AESIDAT3.AESIDATH = *p_in;
    R_AES_B->AESIDAT3.AESIDATL = *(p_in + 1);
    R_AES_B->AESIDAT2.AESIDATH = *(p_in + 2);
    R_AES_B->AESIDAT2.AESIDATL = *(p_in + 3);
    R_AES_B->AESIDAT1.AESIDATH = *(p_in + 4);
    R_AES_B->AESIDAT1.AESIDATL = *(p_in + 5);
    R_AES_B->AESIDAT0.AESIDATH = *(p_in + 6);
    R_AES_B->AESIDAT0.AESIDATL = *(p_in + 7);
}

/***********************************************************************************************************************
 * Function Name: tc_aes_get_ciphertext
 * Description  : This function move AES register output to specified address (1st arg. "output").
 * Arguments    : output    : output data area (block * 16bytes)
 * Return Value : None
 ***********************************************************************************************************************/
static void tc_aes_get_ciphertext (uint8_t * output)
{
    uint16_t * ptr;
    ptr = (uint16_t *) output;

    *ptr       = R_AES_B->AESODAT3.AESODATH;
    *(ptr + 1) = R_AES_B->AESODAT3.AESODATL;
    *(ptr + 2) = R_AES_B->AESODAT2.AESODATH;
    *(ptr + 3) = R_AES_B->AESODAT2.AESODATL;
    *(ptr + 4) = R_AES_B->AESODAT1.AESODATH;
    *(ptr + 5) = R_AES_B->AESODAT1.AESODATL;
    *(ptr + 6) = R_AES_B->AESODAT0.AESODATH;
    *(ptr + 7) = R_AES_B->AESODAT0.AESODATL;
}

void tc_aes_start (uint8_t * input, uint8_t * output, uint32_t block)
{
    uint8_t * ptr;
    uint8_t * ptr_out;
    uint32_t  block_ctr = 0;

    ptr       = input;
    ptr_out   = output;
    block_ctr = 0;
    do
    {
        tc_aes_set_plaintext(ptr);
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_CALCULATE_START;

        while ((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0)
        {
            ;
        }

        if ((R_AES_B->AESSTSL & R_AES_AESSTSL_CALCULATE_COMPLETED) != 0)
        {
            tc_aes_get_ciphertext(ptr_out);
            R_AES_B->AESSTSCL = R_AES_AESSTSCL_DATA_CLEAN;
            R_AES_B->AESDCNTL = 0;
        }

        ptr     += 16;
        ptr_out += 16;
        block_ctr++;
    } while (block_ctr < block);
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
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Cmd == (const uint32_t *) 0) ||
        (InData_KeyIndex == (const uint32_t *) 0) ||
        (InData_IV == (const uint32_t *) 0))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
#endif

    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    tc_aes_set_iv((uint8_t *) InData_IV);
    switch (change_endian_long(*InData_Cmd))
    {
        case SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CTR_192_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_192_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_192_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_192_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_192_DEC;
            break;
        }
    }

    return FSP_SUCCESS;
}

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    tc_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    while ((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0)
    {
        ;
    }

    if ((R_AES_B->AESSTSL & R_AES_AESSTSL_CALCULATE_COMPLETED) != 0)
    {
        R_AES_B->AESSTSCL = R_AES_AESSTSCL_DATA_CLEAN;
        R_AES_B->AESDCNTL = 0;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Cmd == (const uint32_t *) 0) ||
        (InData_KeyIndex == (const uint32_t *) 0) ||
        (InData_IV == (const uint32_t *) 0))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
#endif

    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    tc_aes_set_iv((uint8_t *) InData_IV);
    switch (change_endian_long(*InData_Cmd))
    {
        case SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CTR_128_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_128_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_128_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_128_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_128_DEC;
            break;
        }
    }

    return FSP_SUCCESS;
}

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    tc_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    while ((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0)
    {
        ;
    }

    if ((R_AES_B->AESSTSL & R_AES_AESSTSL_CALCULATE_COMPLETED) != 0)
    {
        R_AES_B->AESSTSCL = R_AES_AESSTSCL_DATA_CLEAN;
        R_AES_B->AESDCNTL = 0;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
#if RM_TINYCRYPT_PORT_CFG_PARAM_CHECKING_ENABLE
    if ((InData_Cmd == (const uint32_t *) 0) ||
        (InData_KeyIndex == (const uint32_t *) 0) ||
        (InData_IV == (const uint32_t *) 0))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
#endif

    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    tc_aes_set_iv((uint8_t *) InData_IV);
    switch (change_endian_long(*InData_Cmd))
    {
        case SCE_AES_IN_DATA_CMD_CTR_ENCRYPTION_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CTR_256_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_256_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_ECB_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_ECB_256_DEC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_ENCRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_256_ENC;
            break;
        }

        case SCE_AES_IN_DATA_CMD_CBC_DECRYPTION:
        {
            R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_2;
            R_AES_B->AESCNTL  = R_AES_AESCNTL_CBC_256_DEC;
            break;
        }
    }

    return FSP_SUCCESS;
}

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    tc_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    while ((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0)
    {
        ;
    }

    if ((R_AES_B->AESSTSL & R_AES_AESSTSL_CALCULATE_COMPLETED) != 0)
    {
        R_AES_B->AESSTSCL = R_AES_AESSTSCL_DATA_CLEAN;
        R_AES_B->AESDCNTL = 0;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_128_ENC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes128GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes128GcmEncryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes128GcmEncryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * OutData_Text,
                                           uint32_t * OutData_DataT)
{
    fsp_err_t status;
    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                (uint8_t) *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                16 * 8,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_128_DEC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes128GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes128GcmDecryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes128GcmDecryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataT,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * InData_DataTLen,
                                           uint32_t * OutData_Text)
{
    uint8_t   Tag[16];
    uint8_t   temp;
    fsp_err_t status;
    uint8_t   Target_Tag[16] = {0};
    memcpy(&Target_Tag[0], InData_DataT, (uint8_t) *InData_DataTLen);

    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                (uint8_t) *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                16 * 8,
                                &InputData_DataA[0],
                                (uint8_t) *InData_DataALen);
    if (status != FSP_SUCCESS)
    {
        return FSP_ERR_CRYPTO_UNKNOWN;
    }

    /* Athentication Tag Verification*/
    if ((uint8_t) *InData_DataTLen != 0)
    {
        for (uint8_t iLoop = 0; iLoop < (uint8_t) *InData_DataTLen; iLoop++)
        {
            temp = Target_Tag[iLoop];
            if (temp != Tag[iLoop])
            {
                status = FSP_ERR_INVALID_ARGUMENT;
                break;
            }
        }

        if (status == FSP_ERR_INVALID_ARGUMENT)
        {
            for (uint32_t iLoop = 0; iLoop < (uint8_t) *InData_TextLen; iLoop++)
            {
                *((uint8_t *) OutData_Text + iLoop) = 0;
            }

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes192GcmEncryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_192_ENC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes192GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes192GcmEncryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes192GcmEncryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * OutData_Text,
                                           uint32_t * OutData_DataT)
{
    fsp_err_t status;
    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                (uint8_t) *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                16 * 8,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes192GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_192_DEC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes192GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes192GcmDecryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes192GcmDecryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataT,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * InData_DataTLen,
                                           uint32_t * OutData_Text)
{
    uint8_t   Tag[16];
    uint8_t   temp;
    fsp_err_t status;
    uint8_t   Target_Tag[16] = {0};
    memcpy(&Target_Tag[0], InData_DataT, (uint8_t) *InData_DataTLen);

    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                16 * 8,
                                &InputData_DataA[0],
                                *InData_DataALen);
    if (status != FSP_SUCCESS)
    {
        return FSP_ERR_CRYPTO_UNKNOWN;
    }

    /* Athentication Tag Verification*/
    if (*InData_DataTLen != 0)
    {
        for (uint32_t iLoop = 0; iLoop < (uint8_t) *InData_DataTLen; iLoop++)
        {
            temp = Target_Tag[iLoop];
            if (temp != Tag[iLoop])
            {
                status = FSP_ERR_INVALID_ARGUMENT;
                break;
            }
        }

        if (status == FSP_ERR_INVALID_ARGUMENT)
        {
            for (uint32_t iLoop = 0; iLoop < (uint8_t) *InData_TextLen; iLoop++)
            {
                *((uint8_t *) OutData_Text + iLoop) = 0;
            }

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_256_ENC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes256GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes256GcmEncryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes256GcmEncryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * OutData_Text,
                                           uint32_t * OutData_DataT)
{
    fsp_err_t status;
    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                (uint8_t) *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                16 * 8,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes256GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);

    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_256_DEC;
    tc_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    memcpy((uint8_t *) &InputData_IV_GCM[0], (uint8_t *) InData_IV, sizeof(InputData_IV_GCM));

    return FSP_SUCCESS;
}

void HW_SCE_Aes256GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    memcpy((uint8_t *) &InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
}

void HW_SCE_Aes256GcmDecryptUpdateTransitionSub (void)
{
}

void HW_SCE_Aes256GcmDecryptUpdateSub (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub (uint32_t * InData_Text,
                                           uint32_t * InData_DataT,
                                           uint32_t * InData_DataALen,
                                           uint32_t * InData_TextLen,
                                           uint32_t * InData_DataTLen,
                                           uint32_t * OutData_Text)
{
    uint8_t   Tag[16];
    uint8_t   temp;
    fsp_err_t status;
    uint8_t   Target_Tag[16] = {0};
    memcpy(&Target_Tag[0], InData_DataT, (uint8_t) *InData_DataTLen);

    status = tc_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                (uint8_t) *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                16 * 8,
                                InputData_DataA,
                                (uint8_t) *InData_DataALen);
    if (status != 0)
    {
        return FSP_ERR_CRYPTO_UNKNOWN;
    }

    /* Athentication Tag Verification*/
    if (*InData_DataTLen != 0)
    {
        for (uint32_t iLoop = 0; iLoop < (uint8_t) *InData_DataTLen; iLoop++)
        {
            temp = Target_Tag[iLoop];
            if (temp != Tag[iLoop])
            {
                status = FSP_ERR_INVALID_ARGUMENT;
                break;
            }
        }

        if (status == FSP_ERR_INVALID_ARGUMENT)
        {
            for (uint32_t iLoop = 0; iLoop < (uint8_t) *InData_TextLen; iLoop++)
            {
                *((uint8_t *) OutData_Text + iLoop) = 0;
            }

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}
