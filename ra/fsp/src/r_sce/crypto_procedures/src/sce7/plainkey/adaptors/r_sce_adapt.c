/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "SCE_ProcCommon.h"
#include "hw_sce_ra_private.h"
#include "hw_sce_private.h"
#include "hw_sce_trng_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];
uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];

uint32_t INST_DATA_SIZE;



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
};

/* Dummy domain parameter structure create for all RSIP devices to allow using the same API for all engines. */

uint32_t const DomainParam_NIST_P256[ECC_DUMMY_DOMAIN_PARAM_SIZE] = {0};
uint32_t const DomainParam_NIST_P384[ECC_DUMMY_DOMAIN_PARAM_SIZE] = {0};
uint32_t const DomainParam_Brainpool_256r1[ECC_DUMMY_DOMAIN_PARAM_SIZE] = {0};
uint32_t const DomainParam_Brainpool_384r1[ECC_DUMMY_DOMAIN_PARAM_SIZE] = {0};
uint32_t const DomainParam_Koblitz_secp256k1[ECC_DUMMY_DOMAIN_PARAM_SIZE] = {0};

/* SCE7 specific initialization functions */
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
        SCE->REG_1D4H = 0x0000ffff;

        if (FSP_SUCCESS == iret)
        {
            /* This check is moved from before the endian setting for the updated fastboot procedures */
            iret = HW_SCE_SelfCheck2Sub();
        }
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
    indata_cmd[0]             = (cmd);
    install_key_ring_index[0] = 0U;

    INST_DATA_SIZE = sce_oem_key_size[cmd] - 4U;

    fsp_err_t ret = FSP_SUCCESS;

    if (key_type == SCE_OEM_KEY_TYPE_PLAIN)
    {
        if (cmd == SCE_OEM_CMD_AES128)
        {
            ret = HW_SCE_GenerateAes128KeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_AES192)
        {
            ret = HW_SCE_GenerateAes192KeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_AES256)
        {
            ret = HW_SCE_GenerateAes256KeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_AES128_XTS)
        {
            ret = HW_SCE_GenerateAes128XtsKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_RSA2048_PUBLIC)
        {
            ret = HW_SCE_GenerateRsa2048PublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_RSA2048_PRIVATE)
        {
            ret = HW_SCE_GenerateRsa2048PrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_ECC_P192_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 2 ;
            ret = HW_SCE_GenerateEccPublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_ECC_P224_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 1 ;
            ret = HW_SCE_GenerateEccPublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P256_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_SECP256K1_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_KOBLITZ;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P256R1_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P384_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;            
            ret = HW_SCE_GenerateEccP384PublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, (uint32_t *) iv,  (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P384R1_PUBLIC)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            ret = HW_SCE_GenerateEccP384PublicKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, (uint32_t *) iv,  (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P192_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 2 ;
            ret = HW_SCE_GenerateEccPrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_ECC_P224_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 1 ;
            ret = HW_SCE_GenerateEccPrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P256_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_SECP256K1_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_KOBLITZ;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P256R1_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            indata_cmd[0]             = 0 ;
            ret = HW_SCE_GenerateEccPrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, indata_cmd, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

        }
        else if (cmd == SCE_OEM_CMD_ECC_P384_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_NIST;
            ret = HW_SCE_GenerateEccP384PrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else if (cmd == SCE_OEM_CMD_ECC_P384R1_PRIVATE)
        {
            uint32_t curve_type = SCE_ECC_CURVE_TYPE_BRAINPOOL;
            ret = HW_SCE_GenerateEccP384PrivateKeyIndexSub(indata_key_type, install_key_ring_index, (uint32_t *) encrypted_provisioning_key, &curve_type, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);
        }
        else
        {
            ret = FSP_ERR_ASSERTION;
        }
    }

    return ret;

}

fsp_err_t HW_SCE_GhashSub (uint32_t *InData_HV, 
                           uint32_t *InData_IV, 
                           uint32_t *InData_Text, 
                           uint32_t *OutData_DataT, 
                           uint32_t MAX_CNT)
{
    return HW_SCE_Ghash(InData_HV, InData_IV, InData_Text, OutData_DataT, MAX_CNT);
} 

fsp_err_t HW_SCE_ShaGenerateMessageDigestSub(const uint32_t InData_HashType[],
                                             const uint32_t InData_Cmd[],
                                             const uint32_t InData_Msg[],
                                             const uint32_t InData_MsgLen[],
                                             const uint32_t InData_State[],
                                             uint32_t OutData_MsgDigest[],
                                             uint32_t OutData_State[],
                                             const uint32_t MAX_CNT)
{   
    FSP_PARAMETER_NOT_USED(InData_HashType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(OutData_State);
    FSP_PARAMETER_NOT_USED(MAX_CNT);

    return HW_SCE_Sha224256GenerateMessageDigestSub(InData_State,
                                                    InData_Msg,
                                                    InData_MsgLen[0],
                                                    OutData_MsgDigest);
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

fsp_err_t HW_SCE_Aes128CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    return HW_SCE_Aes128CmacInitSub((uint32_t *)InData_KeyType, (uint32_t *)InData_KeyIndex);
}

fsp_err_t HW_SCE_Aes192CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes256CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[])
{
    return HW_SCE_Aes256CmacInitSub((uint32_t *)InData_KeyType, (uint32_t *)InData_KeyIndex);
}

void HW_SCE_Aes128CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes128CmacUpdateSub((uint32_t *)InData_Text, (uint32_t)MAX_CNT);
}

void HW_SCE_Aes192CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

void HW_SCE_Aes256CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    HW_SCE_Aes256CmacUpdateSub((uint32_t *)InData_Text, (uint32_t)MAX_CNT);
}

fsp_err_t HW_SCE_Aes128CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    return HW_SCE_Aes128CmacFinalSub((uint32_t *)InData_Cmd, (uint32_t *)InData_Text, (uint32_t *)InData_DataT,
                                     (uint32_t *)InData_DataTLen, OutData_DataT);
}

fsp_err_t HW_SCE_Aes192CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(InData_DataT);
    FSP_PARAMETER_NOT_USED(InData_DataTLen);
    FSP_PARAMETER_NOT_USED(OutData_DataT);
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes256CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[])
{
    return HW_SCE_Aes256CmacFinalSub((uint32_t *)InData_Cmd, (uint32_t *)InData_Text, (uint32_t *)InData_DataT,
                                     (uint32_t *)InData_DataTLen, OutData_DataT);
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
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return (HW_SCE_Aes128CcmEncryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV, InData_Header, Header_Len));
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
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return (HW_SCE_Aes192CcmEncryptInitSub(InData_KeyIndex, InData_IV, InData_Header, Header_Len));
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
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return (HW_SCE_Aes256CcmEncryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV, InData_Header, Header_Len));
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
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_MACLength);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return (HW_SCE_Aes128CcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV, InData_Header, Header_Len));
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
    FSP_PARAMETER_NOT_USED(InData_SeqNum);

    return (HW_SCE_Aes192CcmDecryptInitSub(InData_KeyIndex, InData_IV, InData_Header, Header_Len));
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
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_DataType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_TextLen);
    FSP_PARAMETER_NOT_USED(InData_MACLength);
    FSP_PARAMETER_NOT_USED(InData_SeqNum);
    return (HW_SCE_Aes256CcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV, InData_Header, Header_Len));
}

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSubGeneral (const uint32_t *InData_Text, const uint32_t *InData_TextLen, uint32_t *OutData_Text, uint32_t *OutData_MAC)
{
    return (HW_SCE_Aes128CcmEncryptFinalSub(InData_TextLen, InData_Text, OutData_Text, OutData_MAC));
}

fsp_err_t HW_SCE_Aes128CcmDecryptFinalSubGeneral(const uint32_t *InData_Text, 
                                                 const uint32_t *InData_TextLen, 
                                                 const uint32_t *InData_MAC, 
                                                 const uint32_t *InData_MACLength, 
                                                 uint32_t *OutData_Text)
{
    return (HW_SCE_Aes128CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text));
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

    return (HW_SCE_Aes128GcmEncryptInitSub (InData_KeyType, InData_KeyIndex, InData_IV));
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

    return (HW_SCE_Aes128GcmDecryptInitSub(InData_KeyType, InData_KeyIndex, InData_IV));
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

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    return (HW_SCE_Ecc256ScalarMultiplicationSub(InData_CurveType, InData_Cmd, InData_KeyIndex, InData_PubKey,  OutData_R));
}

fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_Cmd[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_PubKey[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_R[])
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_Ecc384ScalarMultiplicationSub(InData_CurveType, InData_KeyIndex, InData_PubKey, OutData_R));
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

fsp_err_t HW_SCE_EcdsaSignatureGenerateSubAdaptor(const uint32_t InData_CurveType[],
                                                  const uint32_t InData_Cmd[],
                                                  const uint32_t InData_KeyIndex[],
                                                  const uint32_t InData_MsgDgst[],
                                                  const uint32_t InData_DomainParam[],
                                                  uint32_t OutData_Signature[])
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_EcdsaSignatureGenerateSub(InData_CurveType, InData_Cmd, InData_KeyIndex, InData_MsgDgst, OutData_Signature));
}

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[],
                                                      const uint32_t InData_KeyIndex[],
                                                      const uint32_t InData_MsgDgst[],
                                                      const uint32_t InData_DomainParam[],
                                                      uint32_t OutData_Signature[])
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_EcdsaP384SignatureGenerateSub(InData_CurveType, InData_KeyIndex, InData_MsgDgst, OutData_Signature));
}

fsp_err_t HW_SCE_EcdsaSignatureVerificationSubAdaptor(const uint32_t InData_CurveType[],
                                                  const uint32_t InData_Cmd[],
                                                  const uint32_t InData_KeyIndex[],
                                                  const uint32_t InData_MsgDgst[],
                                                  const uint32_t InData_Signature[],
                                                  const uint32_t InData_DomainParam[])
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_EcdsaSignatureVerificationSub(InData_CurveType, InData_Cmd, InData_KeyIndex, InData_MsgDgst, InData_Signature));
}

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSubAdaptor(const uint32_t InData_CurveType[],
                                                          const uint32_t InData_KeyIndex[],
                                                          const uint32_t InData_MsgDgst[],
                                                          const uint32_t InData_Signature[],
                                                          const uint32_t InData_DomainParam[])
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_EcdsaP384SignatureVerificationSub(InData_CurveType, InData_KeyIndex, InData_MsgDgst, InData_Signature));
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
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_GenerateEccRandomKeyIndexSub(InData_CurveType, InData_Cmd, InData_KeyType, OutData_PubKeyIndex, OutData_PubKey, OutData_PrivKeyIndex, OutData_PrivKey));
}

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSubAdaptor(const uint32_t *InData_CurveType,
                                                         const uint32_t *InData_KeyType,
                                                         const uint32_t InData_DomainParam[],
                                                         uint32_t *OutData_PubKeyIndex,
                                                         uint32_t *OutData_PubKey,
                                                         uint32_t *OutData_PrivKeyIndex,
                                                         uint32_t *OutData_PrivKey)
{
    FSP_PARAMETER_NOT_USED (InData_DomainParam);
    
    return (HW_SCE_GenerateEccP384RandomKeyIndexSub(InData_CurveType, InData_KeyType, OutData_PubKeyIndex, OutData_PubKey, OutData_PrivKeyIndex, OutData_PrivKey));
}
