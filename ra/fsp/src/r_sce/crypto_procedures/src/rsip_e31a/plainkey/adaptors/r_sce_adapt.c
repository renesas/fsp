/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "../private/inc/SCE_ProcCommon.h"
#include "hw_sce_ra_private.h"
#include "hw_sce_private.h"
#include "hw_sce_trng_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SCE_RSIP_LITTLE_ENDIAN_MODE    (0x00010001)
#define OEM_KEY_MAX_SIZE_WORDS          SCE_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD

uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];
uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];

uint32_t INST_DATA_SIZE;
uint32_t KEY_INDEX_SIZE;
uint32_t InLen;

/*******************************************************
 * The following are valid SCE lifecycle states:
 *
 * CM1(Lifecycle state)
 *
 * CM2(Lifecycle state)
 *
 * SSD(Lifecycle state)
 *
 * NSECSD(Lifecycle state)
 *
 * DPL(Lifecycle state)
 *
 * LCK_DBG(Lifecycle state)
 *
 * LCK_BOOT(Lifecycle state)
 *
 * RMA_REQ(Lifecycle state)
 *
 * RMA_ACK(Lifecycle state)
 ****************************************************/

#define FSP_SCE_DLMMON_MASK    0x0000000F /* for lcs in stored in R_PSCU->DLMMON */

const uint32_t sce_oem_key_size[SCE_OEM_CMD_NUM] =
{
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES128_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES192_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES256_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES128_XTS_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES256_XTS_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA1024_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA1024_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA2048_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA2048_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA3072_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA3072_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA4096_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP192_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP192_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP224_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP224_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP256_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP256_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP384_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP384_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_HMAC_SHA224_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_HMAC_SHA256_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP256R1_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP256R1_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP384R1_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP384R1_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP512R1_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP512R1_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCSECP256K1_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCSECP256K1_PRIVATE_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP521_PUBLICK_KEY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_ECCP521_PRIVATE_KEY_INST_DATA_WORD,
};

/* Find the lifecycle state load the hardware unique key */
/* returns fsp_err_t                                     */

fsp_err_t HW_SCE_HUK_Load_LCS (void)
{
    uint32_t lc_state = R_PSCU->DLMMON & FSP_SCE_DLMMON_MASK;

    return HW_SCE_LoadHukSub(&lc_state);
}

/* SCE9 specific initialization functions */
/* returns fsp_err_t                      */

fsp_err_t HW_SCE_McuSpecificInit (void)
{
    fsp_err_t iret = FSP_ERR_CRYPTO_SCE_FAIL;

// power on the SCE module 
    HW_SCE_PowerOn();

    HW_SCE_SoftwareResetSub();
    iret = HW_SCE_SelfCheck1Sub();
    if (FSP_SUCCESS == iret)
    {
        /* Change SCE to little endian mode */
        SCE->REG_18H = SCE_RSIP_LITTLE_ENDIAN_MODE;
        SCE->REG_1CH = SCE_RSIP_LITTLE_ENDIAN_MODE;

        /* This check is moved from before the endian setting for the updated fastboot procedures */
        iret = HW_SCE_SelfCheck2Sub();
    }

    if (FSP_SUCCESS == iret)
    {
        iret = HW_SCE_HUK_Load_LCS(/* please try OEM mode when HUK load primitive executing */);
    }

    return iret;
}

fsp_err_t HW_SCE_RNG_Read (uint32_t * OutData_Text)
{
    if (FSP_SUCCESS != HW_SCE_GenerateRandomNumberSub(OutData_Text))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_GenerateOemKeyIndexPrivate (const sce_oem_key_type_t key_type,
                                             const sce_oem_cmd_t      cmd,
                                             const uint8_t          * encrypted_provisioning_key,
                                             const uint8_t          * iv,
                                             const uint8_t          * encrypted_oem_key,
                                             uint32_t               * key_index)
{    
        uint32_t indata_key_type[1]        = {0};
        uint32_t indata_cmd[1]             = {0};
        uint32_t install_key_ring_index[1] = {0};
        indata_key_type[0]        = key_type;
        indata_cmd[0]             = change_endian_long(cmd);
        install_key_ring_index[0] = 0U;

        INST_DATA_SIZE = sce_oem_key_size[cmd] - 4U;
        KEY_INDEX_SIZE = sce_oem_key_size[cmd] + 1U;

        /* Casting uint32_t pointer is used for address. */
        return HW_SCE_GenerateOemKeyIndexSub(indata_key_type,
                                            indata_cmd,
                                            install_key_ring_index,
                                            (uint32_t *) encrypted_provisioning_key,
                                            (uint32_t *) iv,
                                            (uint32_t *) encrypted_oem_key,
                                            key_index);
}

uint32_t change_endian_long (uint32_t a)
{
    return __REV(a);
}

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    return HW_SCE_Aes128EncryptDecryptInitSub(InData_KeyMode, InData_Cmd, InData_KeyIndex, InData_Key, InData_IV);
}

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    return HW_SCE_Aes256EncryptDecryptInitSub(InData_KeyMode, InData_Cmd, InData_KeyIndex, InData_Key, InData_IV);
}

fsp_err_t HW_SCE_Aes128CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    return HW_SCE_Aes128CmacInitSub(InData_KeyType, InData_KeyIndex, NULL);
}

fsp_err_t HW_SCE_Aes192CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    FSP_PARAMETER_NOT_USED (InData_KeyType);
    FSP_PARAMETER_NOT_USED (InData_KeyIndex);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes256CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    return HW_SCE_Aes256CmacInitSub(InData_KeyType, InData_KeyIndex, NULL);
}

void HW_SCE_Aes128CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes128CmacUpdateSub(InData_Text, MAX_CNT);
}

void HW_SCE_Aes192CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED (InData_Text);
    FSP_PARAMETER_NOT_USED (MAX_CNT);
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

void HW_SCE_Aes256CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes256CmacUpdateSub(InData_Text, MAX_CNT);
}

fsp_err_t HW_SCE_Aes128CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    return HW_SCE_Aes128CmacFinalSub(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
}

fsp_err_t HW_SCE_Aes192CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    FSP_PARAMETER_NOT_USED (InData_Cmd);
    FSP_PARAMETER_NOT_USED (InData_Text);
    FSP_PARAMETER_NOT_USED (InData_DataT);
    FSP_PARAMETER_NOT_USED (InData_DataTLen);
    FSP_PARAMETER_NOT_USED (OutData_DataT);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes256CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    return HW_SCE_Aes256CmacFinalSub(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
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
    return (HW_SCE_Aes128GcmEncryptInitSub (InData_KeyType, InData_KeyIndex, NULL, InData_IV));
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
    return (HW_SCE_Aes128GcmDecryptInitSub (InData_KeyType, InData_KeyIndex, NULL, InData_IV));
}

fsp_err_t HW_SCE_Aes192GcmEncryptInitSub (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, 
        const uint32_t *InData_DataALen, uint32_t *OutData_Text, uint32_t *OutData_DataT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(InData_DataALen);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(OutData_DataT);
    return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes192GcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes192GcmEncryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes192GcmEncryptInitSub(InData_KeyIndex, InData_IV);
}

fsp_err_t HW_SCE_Aes192GcmDecryptInitSubGeneral (uint32_t * InData_KeyType,
                                                 uint32_t * InData_DataType,
                                                 uint32_t * InData_Cmd,
                                                 uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_IV,
                                                 uint32_t * InData_SeqNum)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return HW_SCE_Aes192GcmDecryptInitSub(InData_KeyIndex, InData_IV);
}

void HW_SCE_Aes192GcmEncryptUpdateAADSub(const uint32_t *InData_DataA, const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_DataA);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

void HW_SCE_Aes192GcmEncryptUpdateTransitionSub(void)
{

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
    return HW_SCE_Aes256GcmEncryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV);
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
    return HW_SCE_Aes256GcmDecryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV);
}

fsp_err_t HW_SCE_Aes128CcmEncryptInitSubGeneral (uint32_t InData_KeyType[],
                                                 uint32_t InData_DataType[],
                                                 uint32_t InData_Cmd[],
                                                 uint32_t InData_TextLen[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_IV[],
                                                 uint32_t InData_Header[],
                                                 uint32_t InData_SeqNum[],
                                                 uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    return (HW_SCE_Aes128CcmEncryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV, InData_Header, Header_Len));
}

fsp_err_t HW_SCE_Aes192GcmDecryptInitSub(uint32_t *InData_KeyIndex, uint32_t *InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);
    return FSP_ERR_UNSUPPORTED;
}

 fsp_err_t HW_SCE_Aes192CcmEncryptInitSubGeneral (uint32_t InData_KeyType[],
                                                  uint32_t InData_DataType[],
                                                  uint32_t InData_Cmd[],
                                                  uint32_t InData_TextLen[],
                                                  uint32_t InData_KeyIndex[],
                                                  uint32_t InData_IV[],
                                                  uint32_t InData_Header[],
                                                  uint32_t InData_SeqNum[],
                                                  uint32_t Header_Len)
 {
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);
    FSP_PARAMETER_NOT_USED(InData_Header);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    FSP_PARAMETER_NOT_USED(Header_Len);
    return FSP_ERR_UNSUPPORTED;
 }

 void HW_SCE_Aes192CcmEncryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT)
 {
     FSP_PARAMETER_NOT_USED(InData_Text);
     FSP_PARAMETER_NOT_USED(OutData_Text);
     FSP_PARAMETER_NOT_USED(MAX_CNT);
 }

 void HW_SCE_Aes192CcmDecryptUpdateSub(const uint32_t *InData_Text, uint32_t *OutData_Text, const uint32_t MAX_CNT)
 {
     FSP_PARAMETER_NOT_USED(InData_Text);
     FSP_PARAMETER_NOT_USED(OutData_Text);
     FSP_PARAMETER_NOT_USED(MAX_CNT);
 }

 fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_MAC)
 {
     FSP_PARAMETER_NOT_USED(InData_TextLen);
     FSP_PARAMETER_NOT_USED(InData_Text);
     FSP_PARAMETER_NOT_USED(OutData_Text);
     FSP_PARAMETER_NOT_USED(OutData_MAC);
     return FSP_ERR_UNSUPPORTED;
 }

 fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub(const uint32_t *InData_Text, const uint32_t *InData_TextLen, const uint32_t *InData_MAC, const uint32_t *InData_MACLength, uint32_t *OutData_Text)
 {
     FSP_PARAMETER_NOT_USED(InData_Text);
     FSP_PARAMETER_NOT_USED(InData_TextLen);
     FSP_PARAMETER_NOT_USED(InData_MAC);
     FSP_PARAMETER_NOT_USED(InData_MACLength);
     FSP_PARAMETER_NOT_USED(OutData_Text);
     return FSP_ERR_UNSUPPORTED;
 }

fsp_err_t HW_SCE_Aes256CcmEncryptInitSubGeneral (uint32_t InData_KeyType[],
                                                 uint32_t InData_DataType[],
                                                 uint32_t InData_Cmd[],
                                                 uint32_t InData_TextLen[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_IV[],
                                                 uint32_t InData_Header[],
                                                 uint32_t InData_SeqNum[],
                                                 uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    return (HW_SCE_Aes256CcmEncryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV, InData_Header, Header_Len));
}

fsp_err_t HW_SCE_Aes128CcmDecryptInitSubGeneral (uint32_t InData_KeyType[],
                                                 uint32_t InData_DataType[],
                                                 uint32_t InData_Cmd[],
                                                 uint32_t InData_TextLen[],
                                                 uint32_t InData_MACLength[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_IV[],
                                                 uint32_t InData_Header[],
                                                 uint32_t InData_SeqNum[],
                                                 uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_MACLength);
    return (HW_SCE_Aes128CcmDecryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV, InData_Header, Header_Len));
}

 fsp_err_t HW_SCE_Aes192CcmDecryptInitSubGeneral (uint32_t InData_KeyType[],
                                                  uint32_t InData_DataType[],
                                                  uint32_t InData_Cmd[],
                                                  uint32_t InData_TextLen[],
                                                  uint32_t InData_MACLength[],
                                                  uint32_t InData_KeyIndex[],
                                                  uint32_t InData_IV[],
                                                  uint32_t InData_Header[],
                                                  uint32_t InData_SeqNum[],
                                                  uint32_t Header_Len)
 {
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_MACLength);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);
    FSP_PARAMETER_NOT_USED(InData_Header);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    FSP_PARAMETER_NOT_USED(Header_Len);
    return FSP_ERR_UNSUPPORTED;
 }

fsp_err_t HW_SCE_Aes256CcmDecryptInitSubGeneral (uint32_t InData_KeyType[],
                                                 uint32_t InData_DataType[],
                                                 uint32_t InData_Cmd[],
                                                 uint32_t InData_TextLen[],
                                                 uint32_t InData_MACLength[],
                                                 uint32_t InData_KeyIndex[],
                                                 uint32_t InData_IV[],
                                                 uint32_t InData_Header[],
                                                 uint32_t InData_SeqNum[],
                                                 uint32_t Header_Len)
{
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_MACLength);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    return (HW_SCE_Aes256CcmDecryptInitSub(InData_KeyType, InData_KeyIndex, NULL, InData_IV, InData_Header, Header_Len));
}

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSubGeneral (const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_MAC)
{
    return (HW_SCE_Aes128CcmEncryptFinalSub(InData_Text, InData_TextLen, OutData_Text, OutData_MAC));
}

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
		                                             const uint32_t InData_Cmd[],
		                                             const uint32_t InData_KeyIndex[],
		                                             const uint32_t InData_Key[],
		                                             const uint32_t InData_IV[])
{
    FSP_PARAMETER_NOT_USED(InData_KeyMode);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_Key);
    FSP_PARAMETER_NOT_USED(InData_IV);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSubGeneral(const uint32_t *InData_Text, 
                                                 const uint32_t *InData_TextLen, 
                                                 const uint32_t *InData_MAC, 
                                                 const uint32_t *InData_MACLength, 
                                                 uint32_t *OutData_Text)
{
    return (HW_SCE_Aes128CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text));
}

fsp_err_t HW_SCE_Aes128XtsEncryptInitSubGeneral (const uint32_t InData_KeyMode[],
                                                 const uint32_t InData_KeyIndex[],
                                                 const uint32_t InData_Key[],
                                                 const uint32_t InData_IV[])
{
	return HW_SCE_Aes128XtsEncryptInitSub(InData_KeyMode, InData_KeyIndex, InData_Key, InData_IV);
}

fsp_err_t HW_SCE_Aes128XtsDecryptInitSubGeneral (const uint32_t InData_KeyMode[],
                                                 const uint32_t InData_KeyIndex[],
                                                 const uint32_t InData_Key[],
                                                 const uint32_t InData_IV[])
{
    return HW_SCE_Aes128XtsDecryptInitSub(InData_KeyMode, InData_KeyIndex, InData_Key, InData_IV);
}

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    uint32_t indata_key_type = 0;
    return (HW_SCE_Ecc256ScalarMultiplicationSub(InData_CurveType, &indata_key_type, InData_KeyIndex, NULL, InData_PubKey, InData_DomainParam, OutData_R));
}

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    return (HW_SCE_Ecc384ScalarMultiplicationSub(InData_CurveType, InData_Cmd, InData_KeyIndex, NULL, InData_PubKey, InData_DomainParam, OutData_R));
}

fsp_err_t HW_SCE_Ecc521ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    FSP_PARAMETER_NOT_USED(InData_CurveType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_PubKey);
    FSP_PARAMETER_NOT_USED(InData_DomainParam);
    FSP_PARAMETER_NOT_USED(OutData_R);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_EcdsaSignatureGenerateSubAdaptor(const uint32_t InData_CurveType[],
                                                  const uint32_t InData_Cmd[],
                                                  const uint32_t InData_KeyIndex[],
                                                  const uint32_t InData_MsgDgst[],
                                                  const uint32_t InData_DomainParam[],
                                                  uint32_t OutData_Signature[])
{
    if (SCE_OEM_KEY_TYPE_PLAIN == *InData_Cmd)
    {
        return (HW_SCE_EcdsaSignatureGenerateSub(InData_CurveType, InData_Cmd, NULL, InData_KeyIndex ,InData_MsgDgst, InData_DomainParam, OutData_Signature));
    }
    else
    {
        return (HW_SCE_EcdsaSignatureGenerateSub(InData_CurveType, InData_Cmd, InData_KeyIndex, NULL ,InData_MsgDgst, InData_DomainParam, OutData_Signature));
    }
}

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_MsgDgst[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_Signature[])
{
    uint32_t indata_key_mode[1] = {0};
    indata_key_mode[0] = SCE_OEM_KEY_TYPE_ENCRYPTED;
    return HW_SCE_EcdsaP384SignatureGenerateSub(InData_CurveType,
                                                indata_key_mode,
                                                InData_KeyIndex,
                                                NULL,
                                                InData_MsgDgst,
                                                InData_DomainParam,
                                                OutData_Signature);
}

fsp_err_t HW_SCE_EcdsaP521SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_MsgDgst[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_Signature[])
{
    FSP_PARAMETER_NOT_USED(InData_CurveType);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_MsgDgst);
    FSP_PARAMETER_NOT_USED(InData_DomainParam);
    FSP_PARAMETER_NOT_USED(OutData_Signature);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_EcdsaSignatureVerificationSubAdaptor(const uint32_t InData_CurveType[],
                                                  const uint32_t InData_Cmd[],
                                                  const uint32_t InData_KeyIndex[],
                                                  const uint32_t InData_Key[],
                                                  const uint32_t InData_MsgDgst[],
                                                  const uint32_t InData_Signature[],
                                                  const uint32_t InData_DomainParam[])
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    return (HW_SCE_EcdsaSignatureVerificationSub(InData_CurveType, InData_Key, InData_MsgDgst, InData_Signature, InData_DomainParam));
}

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSubAdaptor(const uint32_t InData_CurveType[],
                                                          const uint32_t InData_KeyIndex[],
                                                          const uint32_t InData_Key[],
                                                          const uint32_t InData_MsgDgst[],
                                                          const uint32_t InData_Signature[],
                                                          const uint32_t InData_DomainParam[])
{
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    return HW_SCE_EcdsaP384SignatureVerificationSub(InData_CurveType,
                                                    InData_Key,
                                                    InData_MsgDgst,
                                                    InData_Signature,
                                                    InData_DomainParam);
}

fsp_err_t HW_SCE_EcdsaP521SignatureVerificationSubAdaptor(const uint32_t InData_CurveType[],
                                                          const uint32_t InData_KeyIndex[],
                                                          const uint32_t InData_MsgDgst[],
                                                          const uint32_t InData_Signature[],
                                                          const uint32_t InData_DomainParam[])
{
    FSP_PARAMETER_NOT_USED(InData_CurveType);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_MsgDgst);
    FSP_PARAMETER_NOT_USED(InData_Signature);
    FSP_PARAMETER_NOT_USED(InData_DomainParam);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSubAdaptor(const uint32_t *InData_CurveType,
                                                     const uint32_t *InData_Cmd,
                                                     const uint32_t *InData_KeyType,
                                                     const uint32_t InData_DomainParam[],
                                                     uint32_t *OutData_PubKeyIndex,
                                                     uint32_t *OutData_PubKey,
                                                     uint32_t *OutData_PrivKeyIndex,
                                                     uint32_t *OutData_PrivKey)
{
    FSP_PARAMETER_NOT_USED (InData_Cmd);
    FSP_PARAMETER_NOT_USED(OutData_PubKeyIndex);
    return (HW_SCE_GenerateEccRandomKeyIndexSub(InData_KeyType, InData_CurveType, InData_DomainParam, OutData_PubKey, OutData_PrivKeyIndex, OutData_PrivKey));
}

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSubAdaptor(const uint32_t *InData_CurveType,
                                                         const uint32_t *InData_KeyType,
                                                         const uint32_t InData_DomainParam[],
                                                         uint32_t *OutData_PubKeyIndex,
                                                         uint32_t *OutData_PubKey,
                                                         uint32_t *OutData_PrivKeyIndex,
                                                         uint32_t *OutData_PrivKey)
{
    FSP_PARAMETER_NOT_USED(OutData_PubKeyIndex);

    return HW_SCE_GenerateEccP384RandomKeyIndexSub(InData_KeyType,
                                                   InData_CurveType,
                                                   InData_DomainParam,
                                                   OutData_PubKey,
                                                   OutData_PrivKeyIndex,
                                                   OutData_PrivKey);
}

fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           const uint32_t InData_DataT[],
                                           const uint32_t InData_DataTLen[],
                                           uint32_t       OutData_Text[])
{
	FSP_PARAMETER_NOT_USED (InData_Text);
	FSP_PARAMETER_NOT_USED (InData_TextLen);
	FSP_PARAMETER_NOT_USED (InData_DataALen);
	FSP_PARAMETER_NOT_USED (InData_DataT);
	FSP_PARAMETER_NOT_USED (InData_DataTLen);
	FSP_PARAMETER_NOT_USED (OutData_Text);

	return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes192GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
	FSP_PARAMETER_NOT_USED(InData_DataA);
	FSP_PARAMETER_NOT_USED(MAX_CNT);
}

void HW_SCE_Aes192GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
	FSP_PARAMETER_NOT_USED (InData_Text);
	FSP_PARAMETER_NOT_USED (OutData_Text);
	FSP_PARAMETER_NOT_USED (MAX_CNT);
}

void HW_SCE_Aes192GcmDecryptUpdateTransitionSub (void)
{
}

fsp_err_t HW_SCE_EccEd25519ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    FSP_PARAMETER_NOT_USED(InData_CurveType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_PubKey);
    FSP_PARAMETER_NOT_USED(InData_DomainParam);
    FSP_PARAMETER_NOT_USED(OutData_R);
    return FSP_ERR_UNSUPPORTED;
}
fsp_err_t HW_SCE_ShaGenerateMessageDigestSubGeneral (const uint32_t InData_HashType[],
                                                     const uint32_t InData_Cmd[],
                                                     const uint32_t InData_Msg[],
                                                     const uint32_t InData_MsgLen[],
                                                     const uint32_t InData_State[],
                                                     uint32_t OutData_MsgDigest[],
                                                     uint32_t OutData_State[],
                                                     const uint32_t MAX_CNT,
                                                     const uint32_t InData_InitVal[])
{
    FSP_PARAMETER_NOT_USED(InData_InitVal);
    switch (InData_Cmd[0])
    {
    case SCE_OEM_CMD_HASH_ONESHOT:
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestInitSub(InData_HashType, InData_MsgLen))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        return (HW_SCE_ShaGenerateMessageDigestFinalSub(InData_Msg, OutData_MsgDigest, MAX_CNT));
        break;
    case SCE_OEM_CMD_HASH_INIT_TO_SUSPEND:
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestInitSub(InData_HashType, InData_MsgLen))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestUpdateSub(InData_Msg, MAX_CNT))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        return (HW_SCE_ShaGenerateMessageDigestSuspendSub(OutData_State));
        break;
    case SCE_OEM_CMD_HASH_RESUME_TO_SUSPEND:
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestResumeSub(InData_HashType, InData_State))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestUpdateSub(InData_Msg, MAX_CNT))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        return (HW_SCE_ShaGenerateMessageDigestSuspendSub(OutData_State));
        break;
    case SCE_OEM_CMD_HASH_RESUME_TO_FINAL:
        if (FSP_SUCCESS != HW_SCE_ShaGenerateMessageDigestResumeSub(InData_HashType, InData_State))
        {
            return FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        return (HW_SCE_ShaGenerateMessageDigestFinalSub(InData_Msg, OutData_MsgDigest, MAX_CNT));
        break;
    default:
        return FSP_ERR_CRYPTO_RSIP_FAIL;
        break;
    }
}
