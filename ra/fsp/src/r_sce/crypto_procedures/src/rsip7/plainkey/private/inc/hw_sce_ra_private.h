/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "r_sce_if.h"
#include "SCE_ProcCommon.h"

#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/* Return code */
#define FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT      (0x10100)      ///< Hardware resource is busy
#define FSP_ERR_CRYPTO_RSIP_FATAL                  (0x10101)      ///< Hardware fatal error or unexpected return
#define FSP_ERR_CRYPTO_RSIP_FAIL                   (0x10102)      ///< Internal error
#define FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL           (0x10103)      ///< Input key type is illegal
#define FSP_ERR_CRYPTO_RSIP_AUTHENTICATION         (0x10104)      ///< Authentication failed

/* Version Number of API. */
#define SCE_VERSION_MAJOR    (1U)
#define SCE_VERSION_MINOR    (9U)

/* Various information. */
#define HW_SCE_SRAM_WORD_SIZE   (32U)
#define HW_SCE_SINST_WORD_SIZE  (140U)
#define HW_SCE_SINST2_WORD_SIZE (16U)
#define HW_SCE_SHEAP_WORD_SIZE  (1504U)
#define HW_SCE_MAC_SIZE         (16U)



// TODO: Replace these in the code
#define SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED    (HW_SCE_AES128_KEY_INDEX_WORD_SIZE)
#define SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED     (SIZE_AES_128BIT_KEYLEN_WORDS_WRAPPED * 32U)
#define SIZE_AES_128BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED) / 8U)

#define SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED    (HW_SCE_AES192_KEY_INDEX_WORD_SIZE + 1U) /* Added 32 bits here to differentiate 192 wrapped key from 256 wrapped key in the psa_crypto stack. */
#define SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED     (SIZE_AES_192BIT_KEYLEN_WORDS_WRAPPED * 32U) 
#define SIZE_AES_192BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED) / 8U)

#define SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED    (HW_SCE_AES256_KEY_INDEX_WORD_SIZE)
#define SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED     (SIZE_AES_256BIT_KEYLEN_WORDS_WRAPPED * 32U)
#define SIZE_AES_256BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED) / 8U)

#define SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED     (416)
#define SIZE_AES_XTS_128BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_XTS_128BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_XTS_128BIT_KEYLEN_BITS_WRAPPED) / 32)

#define SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED     (672)
#define SIZE_AES_XTS_256BIT_KEYLEN_BYTES_WRAPPED    ((SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED) / 8)
#define SIZE_AES_XTS_256BIT_KEYLEN_WORDS_WRAPPED    ((SIZE_AES_XTS_256BIT_KEYLEN_BITS_WRAPPED) / 32)

 /** Return RSA wrapped private key size in bytes from the specified RSA modulus size in bits */
 #define RSA_WRAPPED_PRIVATE_KEY_SIZE_BYTES(RSA_SIZE_BITS)    (800U)

/** Return RSA CRT private key size in bytes from the specified RSA modulus size in bits */
 #define RSA_PLAIN_TEXT_CRT_KEY_SIZE_BYTES(RSA_SIZE_BITS)     (((uint32_t) 5 * ((uint32_t) RSA_SIZE_BITS)) / 16U)

/** Return size of any additional info generated by HW for the specified RSA modulus size in bits */
 #define RSA_ADDITIONAL_KEY_INFO_SIZE_BYTES(RSA_SIZE_BITS)    RSA_PLAIN_TEXT_CRT_KEY_SIZE_BYTES(RSA_SIZE_BITS)

/** Return RSA domain parameter size in bytes from the specified RSA modulus size in bits 
 * This is just a dummy value since we only support wrapped keys going forward and these parameters
 * do not exist for wrapped keys. This is just used to pass the mbedTLS export checks. 
*/
 #define RSA_PARAMETERS_SIZE_BYTES(RSA_SIZE_BITS)             (24)

/** DER encoded size for wrapped RSA key */
 #define RSA_WRAPPED_1024_EXPORTED_DER_SIZE_BYTES    (1600U)
 #define RSA_WRAPPED_2048_EXPORTED_DER_SIZE_BYTES    (1600U)
 #define RSA_WRAPPED_3072_EXPORTED_DER_SIZE_BYTES    (1500U)
 #define RSA_WRAPPED_4096_EXPORTED_DER_SIZE_BYTES    (1700U)

 #define ECC_256_FORMATTED_PUBLIC_KEY_LENGTH_WORDS              (24U)
 #define ECC_384_FORMATTED_PUBLIC_KEY_LENGTH_WORDS              (32U)
 #define ECC_521_FORMATTED_PUBLIC_KEY_LENGTH_WORDS              (45U)

 #define ECC_256_PRIVATE_KEY_HRK_LENGTH_WORDS                   (13U)
 #define ECC_256_PRIVATE_KEY_HRK_LENGTH_BITS                    (416U)

 #define ECC_384_PRIVATE_KEY_HRK_LENGTH_WORDS                   (17U)
 #define ECC_384_PRIVATE_KEY_HRK_LENGTH_BITS                    (544U)

 #define ECC_521_PRIVATE_KEY_HRK_LENGTH_WORDS                   (25U)
 #define ECC_521_PRIVATE_KEY_HRK_LENGTH_BITS                    (800U)

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/
extern uint32_t const S_FLASH2[];
extern uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
extern uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];
extern uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
extern uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];
extern uint32_t const DomainParam_NIST_P192[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_P192];
extern uint32_t const DomainParam_NIST_P224[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_P224];
extern uint32_t const DomainParam_NIST_P256[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_P256];
extern uint32_t const DomainParam_NIST_P384[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_P384];
extern uint32_t const DomainParam_NIST_P521[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_P521];
extern uint32_t const DomainParam_NIST_Ed25519[RSIP_PRV_WORD_SIZE_DOMAINPARAM_NIST_ED25519];
extern uint32_t const DomainParam_Brainpool_256r1[RSIP_PRV_WORD_SIZE_DOMAINPARAM_BRAINPOOL_256R1];
extern uint32_t const DomainParam_Brainpool_384r1[RSIP_PRV_WORD_SIZE_DOMAINPARAM_BRAINPOOL_384R1];
extern uint32_t const DomainParam_Brainpool_512r1[RSIP_PRV_WORD_SIZE_DOMAINPARAM_BRAINPOOL_512R1];
extern uint32_t const DomainParam_Koblitz_secp256k1[RSIP_PRV_WORD_SIZE_DOMAINPARAM_KOBLITZ_SECP256K1];

extern uint32_t INST_DATA_SIZE;
extern uint32_t KEY_INDEX_SIZE;

/* --------------------- SCE control procedure related ---------------------- */
void HW_SCE_p_func008_r1(void);
void HW_SCE_p_func012(void);
void HW_SCE_p_func013(void);
void HW_SCE_p_func016(uint32_t ARG1);
void HW_SCE_p_func017(uint32_t ARG1);
void HW_SCE_p_func027_r2(const uint32_t ARG1[]);
void HW_SCE_p_func028_r2(const uint32_t ARG1[]);
void HW_SCE_p_func031_r1(const uint32_t ARG1[]);
void HW_SCE_p_func043_r1(void);
void HW_SCE_p_func044_r1(void);
void HW_SCE_p_func048_r1(const uint32_t ARG1[]);
void HW_SCE_p_func049_r1(const uint32_t ARG1[]);
void HW_SCE_p_func052(void);
void HW_SCE_p_func053(void);
void HW_SCE_p_func054(void);
void HW_SCE_p_func055(void);
void HW_SCE_p_func057_r1(const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[]);
void HW_SCE_p_func058_r1(const uint32_t ARG1[], uint32_t ARG2);
void HW_SCE_p_func059_r1(void);
void HW_SCE_p_func061(const uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func062(const uint32_t ARG1, uint32_t ARG2[]);
void HW_SCE_p_func063(const uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func065(const uint32_t ARG1, uint32_t ARG2[]);
void HW_SCE_p_func068_r1(void);
void HW_SCE_p_func070_r2(const uint32_t ARG1[]);
void HW_SCE_p_func071_r2(const uint32_t ARG1[]);
void HW_SCE_p_func073_r2(const uint32_t ARG1[]);
void HW_SCE_p_func074_r1(void);
void HW_SCE_p_func075_r1(void);
void HW_SCE_p_func076_r1(void);
void HW_SCE_p_func077_r1(void);
void HW_SCE_p_func078_r2(const uint32_t ARG1[]);
void HW_SCE_p_func079_r2(const uint32_t ARG1[]);
void HW_SCE_p_func081_r1(void);
void HW_SCE_p_func082_r1(void);
void HW_SCE_p_func086_r2(const uint32_t ARG1[]);
void HW_SCE_p_func087_r2(const uint32_t ARG1[]);
void HW_SCE_p_func088_r1(void);
void HW_SCE_p_func089_r1(void);
void HW_SCE_p_func090_r1(void);
void HW_SCE_p_func091_r1(void);
void HW_SCE_p_func092_r1(void);
void HW_SCE_p_func093_r1(const uint32_t ARG1[], uint32_t ARG2[]);
void HW_SCE_p_func094(uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func095(uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func103(void);
void HW_SCE_p_func202(void);
void HW_SCE_p_func209(void);
void HW_SCE_p_func214(void);
void HW_SCE_p_func215(void);
void HW_SCE_p_func216(void);
void HW_SCE_p_func302(void);
void HW_SCE_p_func303(void);
void HW_SCE_p_func304(void);
void HW_SCE_p_func305(void);
void HW_SCE_p_func310(void);
void HW_SCE_p_func311(void);
void HW_SCE_p_func312(void);
void HW_SCE_p_func313(void);
void HW_SCE_p_func314(void);
void HW_SCE_p_func315(void);
void HW_SCE_p_func316(void);
void HW_SCE_p_func317(void);
void HW_SCE_p_func318(void);
void HW_SCE_p_func319(void);
void HW_SCE_p_func320(void);
void HW_SCE_p_func321(void);
void HW_SCE_p_func322(void);
void HW_SCE_p_func323(void);
void HW_SCE_p_func324(void);
void HW_SCE_p_func401_r1(const uint32_t ARG1[]);
void HW_SCE_p_func402_r1(void);
void HW_SCE_p_func403(void);
void HW_SCE_p_func404(void);
void HW_SCE_p_func405(void);
void HW_SCE_p_func406_r1(const uint32_t ARG1[]);
void HW_SCE_SoftwareResetSub (void);
void HW_SCE_Aes128GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes128GcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes128GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes192GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes256GcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes256GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes128CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_SeqNum[]);
fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_SeqNum[]);
fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes256GcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_LoadHukSub(const uint32_t InData_LC[]);
fsp_err_t HW_SCE_Aes128CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes128CmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes128CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes256CmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes256CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes128EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSubAdaptor (const uint32_t InData_KeyMode[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_Key[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_GenerateRandomNumberSub (uint32_t OutData_Text[]);
fsp_err_t HW_SCE_GenerateOemKeyIndexSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_SharedKeyIndex[], const uint32_t InData_SessionKey[], const uint32_t InData_IV[], const uint32_t InData_InstData[], uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateOemKeyIndexPrivate (const sce_oem_key_type_t key_type, const sce_oem_cmd_t cmd, const uint8_t *encrypted_provisioning_key, const uint8_t *iv, const uint8_t *encrypted_oem_key, uint32_t *key_index);
fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_SelfCheck1Sub (void);
fsp_err_t HW_SCE_SelfCheck2Sub(void);
void HW_SCE_Aes192GcmEncryptUpdateAADSub(const uint32_t InData_DataA[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes192GcmEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192GcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes192CmacInitSub(const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes192CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);

fsp_err_t HW_SCE_Aes128CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_KeyIndex[], uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[], uint32_t InData_KeyIndex[],uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmEncryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[], uint32_t InData_KeyIndex[],uint32_t InData_IV[],
        uint32_t InData_Header[], uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmDecryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_MACLength[], uint32_t InData_KeyIndex[],
        uint32_t InData_IV[], uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes192CcmDecryptInitSubGeneral (uint32_t InData_KeyType[], uint32_t InData_DataType[],
        uint32_t InData_Cmd[], uint32_t InData_TextLen[], uint32_t InData_MACLength[], uint32_t InData_KeyIndex[],
        uint32_t InData_IV[], uint32_t InData_Header[], uint32_t InData_SeqNum[], uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmDecryptInitSubGeneral (uint32_t InData_KeyType[],uint32_t InData_DataType[],
        uint32_t InData_Cmd[],uint32_t InData_TextLen[],uint32_t InData_MACLength[],uint32_t InData_KeyIndex[],
        uint32_t InData_IV[],uint32_t InData_Header[],uint32_t InData_SeqNum[],uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmEncryptFinalSubGeneral (const uint32_t *InData_Text, const uint32_t *InData_TextLen,
        uint32_t *OutData_Text, uint32_t *OutData_MAC);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalSubGeneral(const uint32_t *InData_Text, const uint32_t *InData_TextLen, 
        const uint32_t *InData_MAC, const uint32_t *InData_MACLength, uint32_t *OutData_Text);       

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes128CcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_TextLen[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t InData_SeqNum[], const uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_MAC[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_TextLen[], const uint32_t InData_MACLength[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t InData_SeqNum[], const uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes256CcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes256CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256CcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes256CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes192CcmEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes192CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes192CcmDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes192CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128XtsEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128XtsEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128XtsDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128XtsDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256XtsEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256XtsEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256XtsDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256XtsDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GctrFinalSub(void);
fsp_err_t HW_SCE_Aes128GctrInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GctrFinalSub(void);
fsp_err_t HW_SCE_Aes256GctrInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GctrFinalSub(void);
fsp_err_t HW_SCE_Aes192GctrInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_GhashSub (const uint32_t InData_HV[], const uint32_t InData_IV[], const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_ShaGenerateMessageDigestSub (const uint32_t InData_HashType[], const uint32_t InData_Cmd[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_State[], uint32_t OutData_MsgDigest[], uint32_t OutData_State[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_ShaGenerateMessageDigest_SingleOpSub (const uint32_t InData_HashType[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], uint32_t OutData_MsgDigest[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_Rsa1024ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa1024ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa3072ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa4096ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_EcdsaSignatureGenerateSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaSignatureGenerateSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaSignatureVerificationSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_EcdsaSignatureVerificationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_Ecc521ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EccEd25519ScalarMultiplicationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EcdsaP512SignatureGenerateSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP512SignatureVerificationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_Ecc512ScalarMultiplicationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EcdsaP521SignatureGenerateSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP521SignatureGenerateSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP521SignatureVerificationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_EcdsaP521SignatureVerificationSubAdaptor(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[]);
fsp_err_t HW_SCE_Ecc521ScalarMultiplicationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], const uint32_t InData_DomainParam[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_DomainParam[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSubAdaptor(const uint32_t *InData_CurveType, const uint32_t *InData_Cmd, const uint32_t *InData_KeyType, const uint32_t InData_DomainParam[], uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub(const uint32_t InData_CurveType[], const uint32_t InData_DomainParam[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSubAdaptor(const uint32_t *InData_CurveType, const uint32_t *InData_KeyType, const uint32_t InData_DomainParam[], uint32_t *OutData_PubKeyIndex, uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
fsp_err_t HW_SCE_GenerateEccP512RandomKeyIndexSub(const uint32_t InData_DomainParam[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccP521RandomKeyIndexSub(const uint32_t InData_DomainParam[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccEd25519RandomKeyIndexSub(const uint32_t InData_KeyMode[], const uint32_t InData_DomainParam[], uint32_t OutData_PubKey[], uint32_t OutData_PrivKeyIndex[], uint32_t OutData_PrivKey[]);
fsp_err_t HW_SCE_Sha256HmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[], const uint32_t InData_MsgLen[]);
void HW_SCE_Sha256HmacUpdateSub(const uint32_t InData_Msg[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Sha224HmacInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgLen[]);
void HW_SCE_Sha224HmacUpdateSub(const uint32_t InData_Msg[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha224HmacFinalSub (const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Sha224HmacMessageDigest(const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t InData_State[], uint32_t OutData_MAC[], uint32_t OutData_State[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacMessageDigest(const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t InData_State[], uint32_t OutData_MAC[], uint32_t OutData_State[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_EddsaSignatureGenerateSub(const uint32_t InData_PrivKeyIndex[], const uint32_t InData_PubKeyIndex[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_EddsaSignatureVerificationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Ed25519ScalarMultiplicationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_XYZ[], const uint32_t InData_DomainParam[], uint32_t OutData_XYZ[]);
fsp_err_t HW_SCE_Aes128OutputKeyForDotfSub(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_Aes192OutputKeyForDotfSub(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_Aes256OutputKeyForDotfSub(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_Aes128OutputKeyForDotfSubAdaptor(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_Aes192OutputKeyForDotfSubAdaptor(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_Aes256OutputKeyForDotfSubAdaptor(uint32_t InData_KeyIndex[], uint32_t InData_DOTFSEED[]);
fsp_err_t HW_SCE_RSA2048_KeyPairGenerateSub(const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_RSA3072_KeyPairGenerateSub(const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_RSA4096_KeyPairGenerateSub(const uint32_t InData_KeyMode[], const uint32_t MAX_CNT, uint32_t OutData_PubKey[], uint32_t OutData_PrivKeyIndex[], uint32_t OutData_PrivKey[]);
fsp_err_t HW_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t MAX_CNT, uint32_t *InData_KeyType, uint32_t *OutData_PubKeyIndex,
        uint32_t *OutData_PubKey, uint32_t *OutData_PrivKeyIndex, uint32_t *OutData_PrivKey);
uint32_t change_endian_long (uint32_t data);

fsp_err_t HW_SCE_Aes128CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes192CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes256CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes128CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes192CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes256CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes128GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType, 
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType, 
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes192GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);
fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral (uint32_t *InData_KeyType, uint32_t *InData_DataType,
        uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, uint32_t *InData_IV, uint32_t *InData_SeqNum);

#endif /* HW_SCE_RA_PRIVATE_HEADER_FILE */
