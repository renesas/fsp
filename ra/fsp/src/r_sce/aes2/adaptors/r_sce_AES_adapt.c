/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "hw_sce_ra_private.h"
#include "bsp_api.h"
#include <stdint.h>

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* Waitting time to make sure calculation is finished
 * Refer to Table 1.3 Numbers of Clock Cycles Required for Processing in the CCM Mode
 * Waiting time for 91 Clock Cycles Required for Processing in the CCM Mode with PCLKB 32MHz
 * Note: waiting for 91 clock cycles is still not enough for encryption of AES-CCM 256 bits key length.
 * Must be to 146 clock cycles.
 * */

#define HW_SCE_AES_CCM_WAITING_CYCLES                  (146U)
#define HW_SCE_FREQUENCY_IN_HZ                         (1000000U)
#define HW_SCE_AES2_MAX_WAIT_USECONDS                  (0xFFFFFFFF) // Set the maximum value for uint32_t
#define HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS    10           // Set a 10 microsecond status check interval

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Imported global variables and functions
 ***********************************************************************************************************************/

extern void HW_SCE_AesCcmEncryptKeyOperation(uint32_t * InData_KeyIndex,
                                             uint32_t   InData_KeyType,
                                             uint32_t * InData_IV,
                                             uint32_t   InData_IVLength);

extern void HW_SCE_AesCcmDecryptKeyOperation(uint32_t * InData_KeyIndex,
                                             uint32_t   InData_KeyType,
                                             uint32_t * InData_IV,
                                             uint32_t   InData_IVLength);

extern void HW_SCE_AesCcmEncryptCounterGenerate(uint32_t InData_TextLength,
                                                uint32_t InData_Hdrlen,
                                                uint32_t InData_MacLength,
                                                uint32_t InData_IVLength);

extern void HW_SCE_AesCcmEncryptInputAssociatedData(uint32_t * InData_Header, uint32_t InData_Hdrlen);

extern void HW_SCE_AesCcmDecryptInputAssociatedData(uint32_t * InData_Header, uint32_t InData_Hdrlen);

extern void HW_SCE_AesCcmEncryptPlaintextInputInit();

extern void HW_SCE_AesCcmEncryptGenerateTag(uint32_t * OutData_MAC);

extern void hw_aes_ccm_decrypt_init(uint32_t indata_cmd);

/***********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

static uint8_t __attribute__((aligned(32))) InputData_DataA[SIZE_AES_GCM_IN_DATA_AAD_LEN_BYTES]     = {0};
static uint8_t __attribute__((aligned(32))) InputData_IV_GCM[SIZE_AES_GCM_IN_DATA_IV_GCM_LEN_BYTES] = {0};
static uint8_t InputData_IV_GCM_LEN_BYTES = 0;

uint32_t change_endian_long (uint32_t a)
{
    return __REV(a);
}

/***********************************************************************************************************************
 * Function Name: hw_aes_set_key
 * Description  : This function move the key from specified address (1st arg "key" to AES peripheral register with define
 *       length (2nd arg "KeyLen")
 * Arguments    :   key     :   key data area
 *                  KeyLen  :   key length in bits
 * Return Value : None
 ***********************************************************************************************************************/
void hw_aes_set_key (uint8_t * key, uint32_t KeyLen)
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
 * Function Name: hw_aes_set_iv
 * Description  : This function move Initialize vector from specified address (1st arg. "iv") to AES register.
 * Arguments    : iv    :   Initialization vector area (16 byte)
 * Return Value : None
 ***********************************************************************************************************************/
void hw_aes_set_iv (uint8_t * initialize_vector)
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
 * Function Name: hw_aes_set_plaintext
 * Description  : This function move input data from specified address(1st arg. "ptext") to AES Data Input register.
 * Arguments    : ptext :   Input data area (block * 16bytes)
 * Return Value : None
 ***********************************************************************************************************************/
static void hw_aes_set_plaintext (uint8_t * ptext)
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
 * Function Name: hw_aes_get_ciphertext
 * Description  : This function move AES register output to specified address (1st arg. "output").
 * Arguments    : output    : output data area (block * 16bytes)
 * Return Value : None
 ***********************************************************************************************************************/
static void hw_aes_get_ciphertext (uint8_t * output)
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

fsp_err_t hw_aes_start (uint8_t * input, uint8_t * output, uint32_t block)
{
    uint8_t * ptr;
    uint8_t * ptr_out;
    uint32_t  block_ctr           = 0;
    uint32_t  wait_count_useconds = HW_SCE_AES2_MAX_WAIT_USECONDS;

    ptr       = input;
    ptr_out   = output;
    block_ctr = 0;
    do
    {
        hw_aes_set_plaintext(ptr);
        R_AES_B->AESDCNTL |= R_AES_AESDCNTL_CALCULATE_START;

        while (((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0) && (wait_count_useconds > 0U))
        {
            R_BSP_SoftwareDelay(HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS, BSP_DELAY_UNITS_MICROSECONDS);
            wait_count_useconds -= HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS;
        }

        if (0 == wait_count_useconds)
        {
            return FSP_ERR_TIMEOUT;
        }

        if ((R_AES_B->AESSTSL & R_AES_AESSTSL_CALCULATE_COMPLETED) != 0)
        {
            hw_aes_get_ciphertext(ptr_out);
            R_AES_B->AESSTSCL = R_AES_AESSTSCL_DATA_CLEAN;
            R_AES_B->AESDCNTL = 0;
        }

        ptr     += 16;
        ptr_out += 16;
        block_ctr++;
    } while (block_ctr < block);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * Function Name: hw_aes_ccm_mode_start
 * Description  : This function move input data from specified address(1st arg. "input") to AES Data Input register
 * and move AES register output to specified address(2nd arg. "output").
 *                In case 1st arg. "input" is NULL, this function move AES register output to "output" only.
 *                In case 2nd arg. "output" is NULL, this function move input data from "input" to AES Data Input register only.
 * Arguments    :   input : Input data area (block * 16bytes)
 *                  output: Output data area (block * 16bytes)
 * Return Value : None
 ***********************************************************************************************************************/
void hw_aes_ccm_mode_start (uint8_t * input, uint8_t * output, uint32_t block)
{
    uint32_t block_ctr;
    uint32_t pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / HW_SCE_FREQUENCY_IN_HZ;
    uint32_t iclk_mhz  = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK) / HW_SCE_FREQUENCY_IN_HZ;
    uint8_t  ratio     = 0U;

    while (iclk_mhz > pclkb_mhz)
    {
        iclk_mhz = iclk_mhz >> 1U;
        ratio++;
    }

    for (block_ctr = 0U; block_ctr < block; block_ctr++)
    {
        if (NULL != input)
        {
            hw_aes_set_plaintext(input);
            R_AES_B->AESDCNTL |= R_AES_AESDCNTL_CALCULATE_START;
            bsp_prv_software_delay_loop(BSP_DELAY_LOOPS_CALCULATE(HW_SCE_AES_CCM_WAITING_CYCLES << ratio));
        }

        if (NULL != output)
        {
            hw_aes_get_ciphertext(output);
            output += SIZE_AES_BLOCK_BYTES;
        }

        input += SIZE_AES_BLOCK_BYTES;
    }
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

    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    hw_aes_set_iv((uint8_t *) InData_IV);
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
    hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    uint32_t wait_count_useconds = HW_SCE_AES2_MAX_WAIT_USECONDS;

    while (((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0) && (wait_count_useconds > 0U))
    {
        R_BSP_SoftwareDelay(HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS, BSP_DELAY_UNITS_MICROSECONDS);
        wait_count_useconds -= HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS;
    }

    if (0 == wait_count_useconds)
    {
        return FSP_ERR_TIMEOUT;
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

    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    hw_aes_set_iv((uint8_t *) InData_IV);
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
    hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    uint32_t wait_count_useconds = HW_SCE_AES2_MAX_WAIT_USECONDS;

    while (((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0) && (wait_count_useconds > 0U))
    {
        R_BSP_SoftwareDelay(HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS, BSP_DELAY_UNITS_MICROSECONDS);
        wait_count_useconds -= HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS;
    }

    if (0 == wait_count_useconds)
    {
        return FSP_ERR_TIMEOUT;
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

    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    hw_aes_set_iv((uint8_t *) InData_IV);
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
    hw_aes_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    uint32_t wait_count_useconds = HW_SCE_AES2_MAX_WAIT_USECONDS;

    while (((R_AES_B->AESSTSL & R_AES_AESSTSL_BIT_5) != 0) && (wait_count_useconds > 0U))
    {
        R_BSP_SoftwareDelay(HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS, BSP_DELAY_UNITS_MICROSECONDS);
        wait_count_useconds -= HW_SCE_AES2_AESSTSL_CHECK_INTERVAL_USECONDS;
    }

    if (0 == wait_count_useconds)
    {
        return FSP_ERR_TIMEOUT;
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
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes128GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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
    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_128_DEC;
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_128BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes128GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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

    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
                                &InputData_DataA[0],
                                *InData_DataALen);
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
            memset(OutData_Text, 0, *InData_TextLen);

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes192GcmEncryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_192_ENC;
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes192GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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
    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes192GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_192_DEC;
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_192BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes192GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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

    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
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
            memset(OutData_Text, 0, *InData_TextLen);

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256GcmEncryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_256_ENC;
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy(&InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes256GcmEncryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy(&InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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
    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                (uint8_t *) OutData_DataT,
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
                                &InputData_DataA[0],
                                *InData_DataALen);

    return status;
}

fsp_err_t HW_SCE_Aes256GcmDecryptInitSub (uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    R_AES_B->AESCNTL = R_AES_AESCNTL_GCM_256_DEC;
    hw_aes_set_key((uint8_t *) InData_KeyIndex, SIZE_AES_256BIT_KEYLEN_BYTES);
    R_AES_B->AESDCNTL          = R_AES_AESDCNTL_BIT_2_3_MODE_1;
    InputData_IV_GCM_LEN_BYTES = (uint8_t) *((unsigned int *) InData_KeyIndex + SCE_AES_GCM_IN_DATA_IV_LEN_LOC);
    memcpy((uint8_t *) &InputData_IV_GCM[0], (uint8_t *) InData_IV, InputData_IV_GCM_LEN_BYTES);

    return FSP_SUCCESS;
}

void HW_SCE_Aes256GcmDecryptUpdateAADSub (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(MAX_CNT);
    if (InData_DataA != 0)
    {
        memcpy((uint8_t *) &InputData_DataA[0], (uint8_t *) InData_DataA, sizeof(InputData_DataA));
    }
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

    status = hw_gcm_calculation((uint8_t *) InData_Text,
                                (uint8_t *) OutData_Text,
                                *InData_TextLen,
                                &Tag[0],
                                &InputData_IV_GCM[0],
                                InputData_IV_GCM_LEN_BYTES,
                                InputData_DataA,
                                *InData_DataALen);
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
            memset(OutData_Text, 0, *InData_TextLen);

            return FSP_ERR_CRYPTO_UNKNOWN;
        }
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    uint32_t InData_IVLen  = InData_Cmd[0];
    uint32_t InData_MACLen = InData_Cmd[1];

    /* Apply key operations */
    HW_SCE_AesCcmEncryptKeyOperation((uint32_t *) InData_KeyIndex,
                                     SIZE_AES_128BIT_KEYLEN_BYTES,
                                     (uint32_t *) InData_IV,
                                     InData_IVLen);

    /* Formatting function and counter generation function */
    HW_SCE_AesCcmEncryptCounterGenerate(*InData_TextLen, Header_Len, InData_MACLen, InData_IVLen);

    /* Apply formating function with associated data */
    HW_SCE_AesCcmEncryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);

    /* Plaintext input initialization */
    HW_SCE_AesCcmEncryptPlaintextInputInit();

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes192CcmEncryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    uint32_t InData_IVLen  = InData_Cmd[0];
    uint32_t InData_MACLen = InData_Cmd[1];

    /* Apply key operations */
    HW_SCE_AesCcmEncryptKeyOperation((uint32_t *) InData_KeyIndex,
                                     SIZE_AES_192BIT_KEYLEN_BYTES,
                                     (uint32_t *) InData_IV,
                                     InData_IVLen);

    /* Formatting function and counter generation function */
    HW_SCE_AesCcmEncryptCounterGenerate(*InData_TextLen, Header_Len, InData_MACLen, InData_IVLen);

    /* Apply formating function with associated data */
    HW_SCE_AesCcmEncryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);

    /* Plaintext input initialization */
    HW_SCE_AesCcmEncryptPlaintextInputInit();

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256CcmEncryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    uint32_t InData_IVLen  = InData_Cmd[0];
    uint32_t InData_MACLen = InData_Cmd[1];

    /* Apply key operations */
    HW_SCE_AesCcmEncryptKeyOperation((uint32_t *) InData_KeyIndex,
                                     SIZE_AES_256BIT_KEYLEN_BYTES,
                                     (uint32_t *) InData_IV,
                                     InData_IVLen);

    /* Formatting function and counter generation function */
    HW_SCE_AesCcmEncryptCounterGenerate(*InData_TextLen, Header_Len, InData_MACLen, InData_IVLen);

    /* Apply formating function with associated data */
    HW_SCE_AesCcmEncryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);

    /* Plaintext input initialization */
    HW_SCE_AesCcmEncryptPlaintextInputInit();

    return FSP_SUCCESS;
}

void HW_SCE_Aes128CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    hw_aes_ccm_mode_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

void HW_SCE_Aes192CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    hw_aes_ccm_mode_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

void HW_SCE_Aes256CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    hw_aes_ccm_mode_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           uint32_t OutData_MAC[])
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);

    /* Generate tag */
    HW_SCE_AesCcmEncryptGenerateTag(OutData_MAC);

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           uint32_t OutData_MAC[])
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);

    /* Generate tag */
    HW_SCE_AesCcmEncryptGenerateTag(OutData_MAC);

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           uint32_t OutData_MAC[])
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);

    /* Generate tag */
    HW_SCE_AesCcmEncryptGenerateTag(OutData_MAC);

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes128CcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MACLength[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    uint32_t InData_IVLen = InData_Cmd[0];

    if (*InData_DataType == 0)
    {
        FSP_PARAMETER_NOT_USED(InData_Header);

        /* Apply key operations */
        uint8_t A_InData_IV[SIZE_AES_BLOCK_BYTES] = {0};
        memcpy(&A_InData_IV[SIZE_AES_BLOCK_BYTES - InData_IVLen], InData_IV, InData_IVLen);
        HW_SCE_AesCcmDecryptKeyOperation((uint32_t *) InData_KeyIndex,
                                         *InData_KeyType,
                                         (uint32_t *) A_InData_IV,
                                         SIZE_AES_128BIT_KEYLEN_BYTES);

        /* Formatting function and counter generation function */
        HW_SCE_AesCcmDecryptCounterGenerate((*InData_TextLen - *InData_MACLength),
                                            Header_Len,
                                            *InData_MACLength,
                                            InData_IVLen);
    }
    else
    {
        FSP_PARAMETER_NOT_USED(InData_TextLen);
        FSP_PARAMETER_NOT_USED(InData_MACLength);
        FSP_PARAMETER_NOT_USED(InData_KeyIndex);
        FSP_PARAMETER_NOT_USED(InData_IV);

        /* Apply formating function with associated data */
        HW_SCE_AesCcmDecryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes192CcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MACLength[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    uint32_t InData_IVLen = InData_Cmd[0];

    if (*InData_DataType == 0)
    {
        FSP_PARAMETER_NOT_USED(InData_Header);

        /* Apply key operations */
        uint8_t A_InData_IV[SIZE_AES_BLOCK_BYTES] = {0};
        memcpy(&A_InData_IV[SIZE_AES_BLOCK_BYTES - InData_IVLen], InData_IV, InData_IVLen);
        HW_SCE_AesCcmDecryptKeyOperation((uint32_t *) InData_KeyIndex,
                                         *InData_KeyType,
                                         (uint32_t *) A_InData_IV,
                                         SIZE_AES_128BIT_KEYLEN_BYTES);

        /* Formatting function and counter generation function */
        HW_SCE_AesCcmDecryptCounterGenerate((*InData_TextLen - *InData_MACLength),
                                            Header_Len,
                                            *InData_MACLength,
                                            InData_IVLen);
    }
    else
    {
        FSP_PARAMETER_NOT_USED(InData_TextLen);
        FSP_PARAMETER_NOT_USED(InData_MACLength);
        FSP_PARAMETER_NOT_USED(InData_KeyIndex);
        FSP_PARAMETER_NOT_USED(InData_IV);

        /* Apply formating function with associated data */
        HW_SCE_AesCcmDecryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_Aes256CcmDecryptInitSub (const uint32_t InData_KeyType[],
                                          const uint32_t InData_DataType[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_TextLen[],
                                          const uint32_t InData_MACLength[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_IV[],
                                          const uint32_t InData_Header[],
                                          const uint32_t InData_SeqNum[],
                                          const uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    uint32_t InData_IVLen = InData_Cmd[0];

    if (*InData_DataType == 0)
    {
        FSP_PARAMETER_NOT_USED(InData_Header);

        /* Apply key operations */
        uint8_t A_InData_IV[SIZE_AES_BLOCK_BYTES] = {0};
        memcpy(&A_InData_IV[SIZE_AES_BLOCK_BYTES - InData_IVLen], InData_IV, InData_IVLen);
        HW_SCE_AesCcmDecryptKeyOperation((uint32_t *) InData_KeyIndex,
                                         InData_KeyType[0],
                                         (uint32_t *) A_InData_IV,
                                         SIZE_AES_128BIT_KEYLEN_BYTES);

        /* Formatting function and counter generation function */
        HW_SCE_AesCcmDecryptCounterGenerate((*InData_TextLen - *InData_MACLength),
                                            Header_Len,
                                            *InData_MACLength,
                                            InData_IVLen);
    }
    else
    {
        FSP_PARAMETER_NOT_USED(InData_TextLen);
        FSP_PARAMETER_NOT_USED(InData_MACLength);
        FSP_PARAMETER_NOT_USED(InData_KeyIndex);
        FSP_PARAMETER_NOT_USED(InData_IV);

        /* Apply formating function with associated data */
        HW_SCE_AesCcmDecryptInputAssociatedData((uint32_t *) InData_Header, Header_Len);
    }

    return FSP_SUCCESS;
}

void HW_SCE_Aes128CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    /* CTR decryption */
    hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_DEC_CTR_DECRYPT);
    hw_aes_ccm_mode_start((uint8_t *) InData_Text, (uint8_t *) OutData_Text, MAX_CNT / 4);
}

void HW_SCE_Aes192CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes128CcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);
}

void HW_SCE_Aes256CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes128CcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);
}

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    fsp_err_t err           = FSP_SUCCESS;
    bool      mac_unaligned = !HW_32BIT_ALIGNED((uint32_t) &InData_Text[0]);
    bool      dst_unaligned = !HW_32BIT_ALIGNED((uint32_t) &OutData_Text[0]);
    uint32_t  payload_len   = *InData_TextLen - *InData_MACLength;
    uint32_t  block_num     = HW_AES_DATA_FIT_TO_BLOCK_SIZE(payload_len) /
                              SIZE_AES_BLOCK_BYTES;
    uint32_t payload_remain                   = HW_AES_DATA_GET_LAST_REMAINS(payload_len);
    uint8_t  Yr[SIZE_AES_BLOCK_BYTES]         = {0};
    uint8_t  Tag[SIZE_AES_BLOCK_BYTES]        = {0};
    uint8_t  LSB_C_Tlen[SIZE_AES_BLOCK_BYTES] = {0};

    FSP_PARAMETER_NOT_USED(InData_Text);

    /* Formatting function for payload */
    /* SCE AES hardware configuration for formatting function for payload */
    hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_DEC_FORMAT_PAYLOAD);
    if ((true == dst_unaligned) || (true == mac_unaligned))
    {
        uint32_t  data_tmp[SIZE_AES_BLOCK_BYTES / 4];
        uint8_t * p_buf_in   = (uint8_t *) OutData_Text;
        uint8_t * p_local_in = (uint8_t *) data_tmp;
        uint32_t  index;

        for (index = 0; index < block_num; index++)
        {
            memset(p_local_in, 0, SIZE_AES_BLOCK_BYTES);
            memcpy(p_local_in, p_buf_in, SIZE_AES_BLOCK_BYTES);
            hw_aes_ccm_mode_start(p_local_in, NULL, SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);
            p_buf_in += SIZE_AES_BLOCK_BYTES;
        }

        if (payload_remain)
        {
            p_local_in = (uint8_t *) data_tmp;
            memset(p_local_in, 0, SIZE_AES_BLOCK_BYTES);
            memcpy(p_local_in, p_buf_in, payload_remain);
            hw_aes_ccm_mode_start(p_local_in, NULL, SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);
        }

        hw_aes_ccm_mode_start(NULL, &Yr[0], SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);

        if (true == mac_unaligned)
        {
            p_local_in = (uint8_t *) data_tmp;
            memset(p_local_in, 0, SIZE_AES_BLOCK_BYTES);
            memcpy(p_local_in, (uint8_t *) InData_MAC, *InData_MACLength);
            memcpy(&LSB_C_Tlen[0], p_local_in, *InData_MACLength);
        }
        else
        {
            memcpy(&LSB_C_Tlen[0], InData_MAC, *InData_MACLength);
        }
    }
    else
    {
        /* Out is uint32_t aligned */
        uint8_t * p_buf_in = (uint8_t *) OutData_Text;
        if (block_num)
        {
            hw_aes_ccm_mode_start((uint8_t *) p_buf_in, (uint8_t *) NULL, block_num);
            p_buf_in += block_num * SIZE_AES_BLOCK_BYTES;
        }

        if (payload_remain)
        {
            uint32_t InOut_DataTmp[SIZE_AES_BLOCK_BYTES / sizeof(uint32_t)];
            memset(InOut_DataTmp, 0, SIZE_AES_BLOCK_BYTES);
            memcpy(InOut_DataTmp, p_buf_in, payload_remain);
            hw_aes_ccm_mode_start((uint8_t *) InOut_DataTmp,
                                  (uint8_t *) NULL,
                                  SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);
        }

        hw_aes_ccm_mode_start(NULL, &Yr[0], SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);

        memcpy(&LSB_C_Tlen[0], InData_MAC, *InData_MACLength);
    }

    /* SCE AES hardware configuration for TAG generation */
    hw_aes_ccm_decrypt_init(SCE_AES_IN_DATA_CMD_CCM_DEC_GENERATE_TAG);
    hw_aes_ccm_mode_start((uint8_t *) &LSB_C_Tlen[0], (uint8_t *) &Tag[0], SIZE_AES_BLOCK_BYTES / SIZE_AES_BLOCK_BYTES);

    if (0 != memcmp(Tag, Yr, *InData_MACLength))
    {
        err = FSP_ERR_CRYPTO_SCE_VERIFY_FAIL;
    }

    return err;
}

fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    fsp_err_t err = FSP_SUCCESS;
    err = HW_SCE_Aes128CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);

    return err;
}

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    fsp_err_t err = FSP_SUCCESS;
    err = HW_SCE_Aes128CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);

    return err;
}

fsp_err_t HW_SCE_Aes128GcmEncryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes128GcmEncryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes128GcmDecryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes128GcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes192GcmEncryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes192GcmEncryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes192GcmDecryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes192GcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes256GcmEncryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes256GcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV);
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

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_KeyIndex[],
                                                     const uint32_t InData_Key[],
                                                     const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_Key);

    return HW_SCE_Aes256EncryptDecryptInitSub(InData_KeyMode, InData_Cmd, InData_KeyIndex, InData_IV);
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
