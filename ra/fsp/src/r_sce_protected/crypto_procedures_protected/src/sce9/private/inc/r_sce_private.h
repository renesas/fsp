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

#ifndef R_SCE_PRIVATE_HEADER_FILE
#define R_SCE_PRIVATE_HEADER_FILE

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_sce.h"
#include "SCE_ProcCommon.h"
#include "r_sce_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern uint32_t const S_FLASH2[];

extern uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
extern uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];
extern uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
extern uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];

extern uint32_t       INST_DATA_SIZE;
extern const uint32_t sce_oem_key_size[SCE_OEM_CMD_NUM];

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/* --------------------- SCE driver wrapper layer ---------------------- */

fsp_err_t R_SCE_SelfCheck1Private(void);
fsp_err_t R_SCE_SelfCheck2Private(void);
fsp_err_t R_SCE_SelfCheck3Private(void);
fsp_err_t R_SCE_LoadHukPrivate(lifecycle_t lifecycle);
fsp_err_t R_SCE_FwIntegrityCheckPrivate(void);

fsp_err_t R_SCE_UpdateOemKeyIndexPrivate(lifecycle_t   lifecycle,
                                         sce_oem_cmd_t key_type,
                                         uint8_t     * iv,
                                         uint8_t     * encrypted_oem_key,
                                         uint32_t    * key_index);

fsp_err_t R_SCE_Aes128EcbEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes128EcbEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128EcbEncryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes128EcbDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes128EcbDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128EcbDecryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes128CbcEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes128CbcEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CbcEncryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes128CbcDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes128CbcDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CbcDecryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);

fsp_err_t R_SCE_Aes256EcbEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes256EcbEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256EcbEncryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes256EcbDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes256EcbDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256EcbDecryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes256CbcEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes256CbcEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CbcEncryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);
fsp_err_t R_SCE_Aes256CbcDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes256CbcDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CbcDecryptFinalPrivate(uint32_t * OutData_Text, uint32_t * OutData_length);

fsp_err_t R_SCE_Aes128GcmEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes128GcmEncryptUpdateAadPrivate(uint32_t * InData_DataA, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128GcmEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes128GcmEncryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_DataALen,
                                             uint32_t * InData_TextLen,
                                             uint32_t * OutData_Text,
                                             uint32_t * OutData_DataT);
fsp_err_t R_SCE_Aes128GcmDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes128GcmDecryptUpdateAadPrivate(uint32_t * InData_DataA, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128GcmDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes128GcmDecryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_DataT,
                                             uint32_t * InData_DataALen,
                                             uint32_t * InData_TextLen,
                                             uint32_t * InData_DataTLen,
                                             uint32_t * OutData_Text);

fsp_err_t R_SCE_Aes256GcmEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes256GcmEncryptUpdateAadPrivate(uint32_t * InData_DataA, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256GcmEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes256GcmEncryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_DataALen,
                                             uint32_t * InData_TextLen,
                                             uint32_t * OutData_Text,
                                             uint32_t * OutData_DataT);
fsp_err_t R_SCE_Aes256GcmDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV);
fsp_err_t R_SCE_Aes256GcmDecryptUpdateAadPrivate(uint32_t * InData_DataA, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256GcmDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes256GcmDecryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_DataT,
                                             uint32_t * InData_DataALen,
                                             uint32_t * InData_TextLen,
                                             uint32_t * InData_DataTLen,
                                             uint32_t * OutData_Text);

void R_SCE_Aes128GcmEncryptUpdateTransitionPrivate(void);
void R_SCE_Aes128GcmDecryptUpdateTransitionPrivate(void);
void R_SCE_Aes256GcmEncryptUpdateTransitionPrivate(void);
void R_SCE_Aes256GcmDecryptUpdateTransitionPrivate(void);

fsp_err_t R_SCE_Aes128CcmEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex,
                                            uint32_t              * InData_IV,
                                            uint32_t              * InData_Header,
                                            uint32_t                Header_Len);
fsp_err_t R_SCE_Aes128CcmEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CcmEncryptFinalPrivate(uint32_t * InData_TextLen,
                                             uint32_t * InData_Text,
                                             uint32_t * OutData_Text,
                                             uint32_t * OutData_MAC);
fsp_err_t R_SCE_Aes128CcmDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex,
                                            uint32_t              * InData_IV,
                                            uint32_t              * InData_Header,
                                            uint32_t                Header_Len);
fsp_err_t R_SCE_Aes128CcmDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CcmDecryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_TextLen,
                                             uint32_t * InData_MAC,
                                             uint32_t * InData_MACLength,
                                             uint32_t * OutData_Text);

fsp_err_t R_SCE_Aes256CcmEncryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex,
                                            uint32_t              * InData_IV,
                                            uint32_t              * InData_Header,
                                            uint32_t                Header_Len);
fsp_err_t R_SCE_Aes256CcmEncryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CcmEncryptFinalPrivate(uint32_t * InData_TextLen,
                                             uint32_t * InData_Text,
                                             uint32_t * OutData_Text,
                                             uint32_t * OutData_MAC);
fsp_err_t R_SCE_Aes256CcmDecryptInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex,
                                            uint32_t              * InData_IV,
                                            uint32_t              * InData_Header,
                                            uint32_t                Header_Len);
fsp_err_t R_SCE_Aes256CcmDecryptUpdatePrivate(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CcmDecryptFinalPrivate(uint32_t * InData_Text,
                                             uint32_t * InData_TextLen,
                                             uint32_t * InData_MAC,
                                             uint32_t * InData_MACLength,
                                             uint32_t * OutData_Text);

fsp_err_t R_SCE_Aes128CmacGenerateInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes128CmacGenerateUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CmacGenerateFinalPrivate(uint32_t All_Msg_Len, uint32_t * InData_Text, uint32_t * OutData_DataT);
fsp_err_t R_SCE_Aes128CmacVerifyInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes128CmacVerifyUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes128CmacVerifyFinalPrivate(uint32_t   All_Msg_Len,
                                             uint32_t * InData_Text,
                                             uint32_t * InData_DataT,
                                             uint32_t * InData_DataTLen);

fsp_err_t R_SCE_Aes256CmacGenerateInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes256CmacGenerateUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CmacGenerateFinalPrivate(uint32_t All_Msg_Len, uint32_t * InData_Text, uint32_t * OutData_DataT);
fsp_err_t R_SCE_Aes256CmacVerifyInitPrivate(sce_aes_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Aes256CmacVerifyUpdatePrivate(uint32_t * InData_Text, uint32_t MAX_CNT);
fsp_err_t R_SCE_Aes256CmacVerifyFinalPrivate(uint32_t   All_Msg_Len,
                                             uint32_t * InData_Text,
                                             uint32_t * InData_DataT,
                                             uint32_t * InData_DataTLen);

fsp_err_t R_SCE_Sha256InitPrivate(sce_sha_md5_handle_t * handle);
fsp_err_t R_SCE_Sha256UpdatePrivate(sce_sha_md5_handle_t * handle, uint32_t * InData_PaddedMsg, uint32_t MAX_CNT);
fsp_err_t R_SCE_Sha256FinalPrivate(sce_sha_md5_handle_t * handle,
                                   uint32_t             * InData_PaddedMsg,
                                   uint32_t               MAX_CNT,
                                   uint32_t             * OutData_MsgDigest,
                                   uint32_t             * OutData_Length);

fsp_err_t R_SCE_Sha256HmacGenerateInitPrivate(sce_hmac_sha_handle_t      * handle,
                                              sce_hmac_sha_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Sha256HmacGenerateUpdatePrivate(sce_hmac_sha_handle_t * handle,
                                                uint32_t              * InData_PaddedMsg,
                                                uint32_t                MAX_CNT);
fsp_err_t R_SCE_Sha256HmacGenerateFinalPrivate(sce_hmac_sha_handle_t * handle, uint32_t * OutData_Mac);
fsp_err_t R_SCE_Sha256HmacVerifyInitPrivate(sce_hmac_sha_handle_t      * handle,
                                            sce_hmac_sha_wrapped_key_t * InData_KeyIndex);
fsp_err_t R_SCE_Sha256HmacVerifyUpdatePrivate(sce_hmac_sha_handle_t * handle,
                                              uint32_t              * InData_PaddedMsg,
                                              uint32_t                MAX_CNT);
fsp_err_t R_SCE_Sha256HmacVerifyFinalPrivate(sce_hmac_sha_handle_t * handle,
                                             uint32_t              * InData_Mac,
                                             uint32_t              * InData_length);

fsp_err_t R_SCE_Rsa1024ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Rsa1024ModularExponentDecryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Rsa2048ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Rsa2048ModularExponentDecryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Rsa3072ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Rsa4096ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_Text,
                                                     uint32_t * OutData_Text);

fsp_err_t R_SCE_EcdhReadPublicKeyPrivate(uint32_t * InData_Cmd,
                                         uint32_t * InData_KeyIndex,
                                         uint32_t * InData_data,
                                         uint32_t * InData_Signature,
                                         uint32_t * OutData_KeyIndex);
fsp_err_t R_SCE_EcdhReadPublicKeyWithoutSignaturePrivate(uint32_t * InData_Cmd,
                                                         uint32_t * InData_data,
                                                         uint32_t * OutData_KeyIndex);
fsp_err_t R_SCE_EcdhMakePublicKeyPrivate(uint32_t * InData_Cmd,
                                         uint32_t * InData_KeyType,
                                         uint32_t * InData_PubKeyIndex,
                                         uint32_t * InData_PrivKeyIndex,
                                         uint32_t * InData_key_id,
                                         uint32_t * OutData_data,
                                         uint32_t * OutData_Signature,
                                         uint32_t * OutData_KeyIndex);
fsp_err_t R_SCE_EcdhCalculateSharedSecretIndexPrivate(uint32_t * InData_KeyType,
                                                      uint32_t * InData_PubKeyIndex,
                                                      uint32_t * InData_PrivKeyIndex,
                                                      uint32_t * OutData_KeyIndex);
fsp_err_t R_SCE_EcdhKeyDerivationPrivate(uint32_t * InData_KeyIndexType,
                                         uint32_t * InData_KeyIndex,
                                         uint32_t * InData_KDFType,
                                         uint32_t * InData_PaddedMsg,
                                         uint32_t   MAX_CNT,
                                         uint32_t * InData_SaltKeyIndex,
                                         uint32_t * OutData_KeyIndex);
fsp_err_t R_SCE_Aes128KeyWrapPrivate(uint32_t * InData_KeyIndex,
                                     uint32_t * InData_WrappedKeyType,
                                     uint32_t * InData_WrappedKeyIndex,
                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes256KeyWrapPrivate(uint32_t * InData_KeyIndex,
                                     uint32_t * InData_WrappedKeyType,
                                     uint32_t * InData_WrappedKeyIndex,
                                     uint32_t * OutData_Text);
fsp_err_t R_SCE_Aes128KeyUnWrapPrivate(sce_aes_wrapped_key_t  * InData_MasterKey,
                                       uint32_t               * InData_WrappedKeyType,
                                       uint32_t               * InData_Text,
                                       uint32_t               * OutData_KeyIndex);
fsp_err_t R_SCE_Aes256KeyUnWrapPrivate(sce_aes_wrapped_key_t  * InData_MasterKey,
                                       uint32_t               * InData_WrappedKeyType,
                                       uint32_t               * InData_Text,
                                       uint32_t               * OutData_KeyIndex);
/* --------------------- SCE control procedure related ---------------------- */

void R_SCE_SoftwareResetSub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_SelfCheck1Sub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_RETRY **/
fsp_err_t R_SCE_SelfCheck2Sub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_RETRY **/
fsp_err_t R_SCE_SelfCheck3Sub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_LoadHukSub(uint32_t * InData_LC);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_FwIntegrityCheckSub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_UpdateOemKeyIndexSub(uint32_t * InData_LC,
                                     uint32_t * InData_Cmd,
                                     uint32_t * InData_IV,
                                     uint32_t * InData_InstData,
                                     uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_GenerateAes128RandomKeyIndexSub(uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_GenerateAes256RandomKeyIndexSub(uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateRsa1024RandomKeyIndexSub(uint32_t   MAX_CNT,
                                                 uint32_t * OutData_PubKeyIndex,
                                                 uint32_t * OutData_PrivKeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateRsa2048RandomKeyIndexSub(uint32_t   MAX_CNT,
                                                 uint32_t * OutData_PubKeyIndex,
                                                 uint32_t * OutData_PrivKeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateTlsRsaInstallDataSub(uint32_t *InData_SharedKeyIndex,
                                             uint32_t *InData_SessionKey,
                                             uint32_t *InData_IV,
                                             uint32_t *InData_InstData,
                                             uint32_t *OutData_InstData);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateTlsP256EccKeyIndexSub(uint32_t *OutData_KeyIndex, uint32_t *OutData_PubKey);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateEccRandomKeyIndexSub(uint32_t * InData_CurveType,
                                             uint32_t * InData_Cmd,
                                             uint32_t * OutData_PubKeyIndex,
                                             uint32_t * OutData_PrivKeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_GenerateEccP384RandomKeyIndexSub(uint32_t * InData_CurveType,
                                                 uint32_t * OutData_PubKeyIndex,
                                                 uint32_t * OutData_PrivKeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_GenerateRandomNumberSub(uint32_t * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                            const uint32_t * InData_Cmd,
                                            const uint32_t * InData_KeyIndex,
                                            const uint32_t * InData_IV);
void R_SCE_Aes128EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                         uint32_t       * OutData_Text,
                                         const uint32_t   MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128EncryptDecryptFinalSub(void);


/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256EncryptDecryptInitSub(const uint32_t * InData_KeyType,
                                            const uint32_t * InData_Cmd,
                                            const uint32_t * InData_KeyIndex,
                                            const uint32_t * InData_IV);
void R_SCE_Aes256EncryptDecryptUpdateSub(const uint32_t * InData_Text,
                                         uint32_t       * OutData_Text,
                                         const uint32_t   MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256EncryptDecryptFinalSub(void);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_Ghash(uint32_t * InData_HV,
                      uint32_t * InData_IV,
                      uint32_t * InData_Text,
                      uint32_t * OutData_DataT,
                      uint32_t   MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes128GcmEncryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      R_SCE_Aes128GcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128GcmEncryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_DataALen,
                                         uint32_t * InData_TextLen,
                                         uint32_t * OutData_Text,
                                         uint32_t * OutData_DataT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes128GcmDecryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      R_SCE_Aes128GcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION **/
fsp_err_t R_SCE_Aes128GcmDecryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_DataT,
                                         uint32_t * InData_DataALen,
                                         uint32_t * InData_TextLen,
                                         uint32_t * InData_DataTLen,
                                         uint32_t * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256GcmEncryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      R_SCE_Aes256GcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256GcmEncryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_DataALen,
                                         uint32_t * InData_TextLen,
                                         uint32_t * OutData_Text,
                                         uint32_t * OutData_DataT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256GcmDecryptInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t * InData_IV);
void      R_SCE_Aes256GcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION **/
fsp_err_t R_SCE_Aes256GcmDecryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_DataT,
                                         uint32_t * InData_DataALen,
                                         uint32_t * InData_TextLen,
                                         uint32_t * InData_DataTLen,
                                         uint32_t * OutData_Text);

void R_SCE_Aes128GcmDecryptUpdateTransitionSub(void);
void R_SCE_Aes128GcmEncryptUpdateTransitionSub(void);
void R_SCE_Aes256GcmDecryptUpdateTransitionSub(void);
void R_SCE_Aes256GcmEncryptUpdateTransitionSub(void);
void R_SCE_Aes128GcmEncryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void R_SCE_Aes128GcmDecryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void R_SCE_Aes256GcmEncryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);
void R_SCE_Aes256GcmDecryptUpdateAADSub(uint32_t * InData_DataA, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes128CcmEncryptInitSub(uint32_t * InData_KeyType,
                                        uint32_t * InData_KeyIndex,
                                        uint32_t * InData_IV,
                                        uint32_t * InData_Header,
                                        uint32_t   Header_Len);
void R_SCE_Aes128CcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128CcmEncryptFinalSub(uint32_t * InData_TextLen,
                                         uint32_t * InData_Text,
                                         uint32_t * OutData_Text,
                                         uint32_t * OutData_MAC);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes128CcmDecryptInitSub(uint32_t * InData_KeyType,
                                        uint32_t * InData_KeyIndex,
                                        uint32_t * InData_IV,
                                        uint32_t * InData_Header,
                                        uint32_t   Header_Len);
void R_SCE_Aes128CcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128CcmDecryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_TextLen,
                                         uint32_t * InData_MAC,
                                         uint32_t * InData_MACLength,
                                         uint32_t * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes256CcmEncryptInitSub(uint32_t * InData_KeyType,
                                        uint32_t * InData_KeyIndex,
                                        uint32_t * InData_IV,
                                        uint32_t * InData_Header,
                                        uint32_t   Header_Len);
void R_SCE_Aes256CcmEncryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256CcmEncryptFinalSub(uint32_t * InData_TextLen,
                                         uint32_t * InData_Text,
                                         uint32_t * OutData_Text,
                                         uint32_t * OutData_MAC);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Aes256CcmDecryptInitSub(uint32_t * InData_KeyType,
                                        uint32_t * InData_KeyIndex,
                                        uint32_t * InData_IV,
                                        uint32_t * InData_Header,
                                        uint32_t   Header_Len);
void R_SCE_Aes256CcmDecryptUpdateSub(uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256CcmDecryptFinalSub(uint32_t * InData_Text,
                                         uint32_t * InData_TextLen,
                                         uint32_t * InData_MAC,
                                         uint32_t * InData_MACLength,
                                         uint32_t * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes128CmacInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex);
void      R_SCE_Aes128CmacUpdateSub(uint32_t * InData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION **/
fsp_err_t R_SCE_Aes128CmacFinalSub(uint32_t * InData_Cmd,
                                   uint32_t * InData_Text,
                                   uint32_t * InData_DataT,
                                   uint32_t * InData_DataTLen,
                                   uint32_t * OutData_DataT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Aes256CmacInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex);
void      R_SCE_Aes256CmacUpdateSub(uint32_t * InData_Text, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION **/
fsp_err_t R_SCE_Aes256CmacFinalSub(uint32_t * InData_Cmd,
                                   uint32_t * InData_Text,
                                   uint32_t * InData_DataT,
                                   uint32_t * InData_DataTLen,
                                   uint32_t * OutData_DataT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_Sha224256GenerateMessageDigestSub(const uint32_t * InData_InitVal,
                                                  const uint32_t * InData_PaddedMsg,
                                                  const uint32_t   MAX_CNT,
                                                  uint32_t       * OutData_MsgDigest);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_Sha256HmacInitSub(uint32_t * InData_KeyType, uint32_t * InData_KeyIndex, uint32_t LEN);
void      R_SCE_Sha256HmacUpdateSub(uint32_t * InData_PaddedMsg, uint32_t MAX_CNT);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_Sha256HmacFinalSub(uint32_t * InData_Cmd,
                                   uint32_t * InData_MAC,
                                   uint32_t * InData_length,
                                   uint32_t * OutData_MAC);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsRootCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType,
                                                  uint32_t *InData_Certificates,
                                                  uint32_t *InData_CertificatesLength,
                                                  uint32_t *InData_Signature,
                                                  uint32_t *InData_CertificatesInfo,
                                                  uint32_t length,
                                                  uint32_t *OutData_PubKey);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsCertificateVerificationSub(uint32_t *InData_Sel_PubKeyType,
                                              uint32_t *InData_PubKey,
                                              uint32_t *InData_TBSCertificate,
                                              uint32_t *InData_TBSCertificateLength,
                                              uint32_t *InData_Signature,
                                              uint32_t *InData_TBSCertificateInfo,
                                              uint32_t length,
                                              uint32_t *OutData_PubKey);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsEncryptPreMasterSecretSub(uint32_t *InData_PubKey,
                                             uint32_t *InData_PreMasterSecret,
                                             uint32_t *OutData_PreMasterSecret);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_TlsGeneratePreMasterSecretSub(uint32_t *OutData_PreMasterSecret);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsGenerateMasterSecretSub(uint32_t *InData_Sel_CipherSuite,
                                           uint32_t *InData_PreMasterSecret,
                                           uint32_t *InData_ClientRandom,
                                           uint32_t *InData_ServerRandom,
                                           uint32_t *OutData_MasterSecret);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsGenerateSessionKeySub(uint32_t *InData_Sel_CipherSuite,
                                         uint32_t *InData_MasterSecret,
                                         uint32_t *InData_ClientRandom,
                                         uint32_t *InData_ServerRandom,
                                         uint32_t *InData_NonceExplicit,
                                         uint32_t *OutData_ClientMACKeyOperationCode,
                                         uint32_t *OutData_ServerMACKeyOperationCode,
                                         uint32_t *OutData_ClientEncKeyOperationCode,
                                         uint32_t *OutData_ServerEncKeyOperationCode,
                                         uint32_t OutLen);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsGenerateVerifyDataSub(uint32_t *InData_Sel_VerifyData,
                                         uint32_t *InData_MasterSecret,
                                         uint32_t *InData_HandShakeHash,
                                         uint32_t *OutData_VerifyData);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsServersEphemeralEcdhPublicKeyRetrievesSub(uint32_t *InData_Sel_PubKeyType,
                                                             uint32_t *InData_ClientRandom,
                                                             uint32_t *InData_ServerRandom,
                                                             uint32_t *InData_Sel_CompressType,
                                                             uint32_t *InData_SKE_Message,
                                                             uint32_t *InData_SKE_Signature,
                                                             uint32_t *InData_PubKey,
                                                             uint32_t *OutData_EphemeralPubKey);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_TlsGeneratePreMasterSecretWithEccP256KeySub(uint32_t *InData_PubKey,
                                                            uint32_t *InData_KeyIndex,
                                                            uint32_t *OutData_PreMasterSecretIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa1024ModularExponentEncryptSub(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_Text,
                                                 uint32_t       * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa1024ModularExponentDecryptSub(uint32_t       * InData_KeyIndex,
                                                 const uint32_t * InData_Text,
                                                 uint32_t       * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_Text,
                                                 uint32_t       * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa2048ModularExponentDecryptSub(uint32_t       * InData_KeyIndex,
                                                 const uint32_t * InData_Text,
                                                 uint32_t       * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa3072ModularExponentEncryptSub(uint32_t * InData_KeyIndex,
                                                 uint32_t * InData_Text,
                                                 uint32_t * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t * InData_KeyIndex,
                                                 uint32_t       * InData_Text,
                                                 uint32_t       * OutData_Text);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_EcdsaSignatureGenerateSub(uint32_t * InData_CurveType,
                                          uint32_t * InData_Cmd,
                                          uint32_t * InData_KeyIndex,
                                          uint32_t * InData_MsgDgst,
                                          uint32_t * OutData_Signature);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_EcdsaP384SignatureGenerateSub(uint32_t * InData_CurveType,
                                              uint32_t * InData_KeyIndex,
                                              uint32_t * InData_MsgDgst,
                                              uint32_t * OutData_Signature);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_EcdsaSignatureVerificationSub(uint32_t * InData_CurveType,
                                              uint32_t * InData_Cmd,
                                              uint32_t * InData_KeyIndex,
                                              uint32_t * InData_MsgDgst,
                                              uint32_t * InData_Signature);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_EcdsaNistP256SignatureVerificationSub(uint32_t *InData_KeyIndex,
                                                      uint32_t *InData_MsgDgst,
                                                      uint32_t *InData_Signature);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_EcdsaP384SignatureVerificationSub(uint32_t * InData_CurveType,
                                                  uint32_t * InData_KeyIndex,
                                                  uint32_t * InData_MsgDgst,
                                                  uint32_t * InData_Signature);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_DlmsCosemQeuSignatureVerificationSub(uint32_t * InData_Cmd,
                                                     uint32_t * InData_KeyIndex,
                                                     uint32_t * InData_data,
                                                     uint32_t * InData_Signature,
                                                     uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT **/
fsp_err_t R_SCE_EcdhP256QeuOutputSub(uint32_t *InData_Cmd,
                                     uint32_t *InData_data,
                                     uint32_t *OutData_KeyIndex);
/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_DlmsCosemQevSignatureGenerationSub(uint32_t * InData_Cmd,
                                                   uint32_t * InData_KeyType,
                                                   uint32_t * InData_PubKeyIndex,
                                                   uint32_t * InData_PrivKeyIndex,
                                                   uint32_t * InData_key_id,
                                                   uint32_t * OutData_data,
                                                   uint32_t * OutData_Signature,
                                                   uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_FAIL @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_DlmsCosemCalculateZSub(uint32_t * InData_KeyType,
                                       uint32_t * InData_PubKeyIndex,
                                       uint32_t * InData_PrivKeyIndex,
                                       uint32_t * OutData_KeyIndex);

/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL **/
fsp_err_t R_SCE_DlmsCosemCalculateKekSub(uint32_t *InData_KeyIndexType,
                                         uint32_t * InData_KeyIndex,
                                         uint32_t * InData_KDFType,
                                         uint32_t * InData_PaddedMsg,
                                         uint32_t   MAX_CNT,
                                         uint32_t * InData_SaltKeyIndex,
                                         uint32_t * OutData_KeyIndex);
/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_AesKeyWrapSub(uint32_t * InData_Cmd,
                              uint32_t * InData_KeyIndex,
                              int32_t    KEY_INDEX_SIZE,
                              uint32_t * InData_WrappedKeyType,
                              uint32_t * InData_WrappedKeyIndex,
                              uint32_t   WRAPPED_KEY_SIZE,
                              uint32_t * OutData_Text);
/** @retval FSP_SUCCESS @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL @retval FSP_ERR_CRYPTO_SCE_FAIL **/
fsp_err_t R_SCE_AesKeyUnwrapSub(uint32_t * InData_KeyType,
                                uint32_t * InData_Cmd,
                                uint32_t * InData_KeyIndex,
                                uint32_t   KEY_INDEX_SIZE,
                                uint32_t * InData_WrappedKeyType,
                                uint32_t * InData_Text,
                                uint32_t   WRAPPED_KEY_SIZE,
                                uint32_t * OutData_KeyIndex);

void R_SCE_SelfCheck1SubSub(void);
void R_SCE_TlsRootCertificateVerificationSubSub(void);
void R_SCE_TlsGenerateSubSub(void);

void R_SCE_func000(uint32_t * InData_PaddedMsg, int32_t MAX_CNT);
void R_SCE_func001(void);
void R_SCE_func002(void);
void R_SCE_func003_r1(uint32_t* ARG1);
void R_SCE_func004_r1(uint32_t ARG1);
void R_SCE_func005_r1(uint32_t ARG1);
void R_SCE_func006(void);
void R_SCE_func007(void);
void R_SCE_func008(void);
void R_SCE_func009(void);
void R_SCE_func010_r1(uint32_t ARG1);
void R_SCE_func011(uint32_t * ARG1);
void R_SCE_func022(void);
void R_SCE_func023(void);
void R_SCE_func025_r1(uint32_t ARG1);
void R_SCE_func027_r2(uint32_t ARG1);
void R_SCE_func028_r2(uint32_t ARG1);
void R_SCE_func030(void);
void R_SCE_func040(void);
void R_SCE_func043(void);
void R_SCE_func044(void);
void R_SCE_func048(uint32_t * ARG1);
void R_SCE_func049(uint32_t * ARG1);
void R_SCE_func050(uint32_t ARG1);
void R_SCE_func051(void);
void R_SCE_func052(uint32_t ARG1);
void R_SCE_func053(uint32_t ARG1);
void R_SCE_func054(uint32_t ARG1, uint32_t ARG2);
void R_SCE_func057_r3(uint32_t * ARG1, uint32_t * ARG2, uint32_t * ARG3);
void R_SCE_func059(void);
void R_SCE_func060(void);
void R_SCE_func061(uint32_t ARG1, uint32_t * ARG2);
void R_SCE_func062(uint32_t ARG1, uint32_t * ARG2);
void R_SCE_func063(uint32_t ARG1, uint32_t * ARG2);
void R_SCE_func064(uint32_t ARG1, uint32_t * ARG2);
void R_SCE_func068(void);
void R_SCE_func069(uint32_t* ARG1, uint32_t ARG2);
void R_SCE_func070_r2(uint32_t ARG1);
void R_SCE_func071_r2(uint32_t ARG1);
void R_SCE_func073_r2(uint32_t ARG1);
void R_SCE_func074_r1(void);
void R_SCE_func075_r1(void);
void R_SCE_func076(void);
void R_SCE_func077(void);
void R_SCE_func080(void);
void R_SCE_func081(void);
void R_SCE_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void R_SCE_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void R_SCE_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void R_SCE_func103(void);
void R_SCE_func200(void);
void R_SCE_func202(void);
void R_SCE_func205(void);
void R_SCE_func206(void);
void R_SCE_func207(void);
void R_SCE_func300(void);
void R_SCE_func301(void);
void R_SCE_func302(void);
void R_SCE_func303(void);
void R_SCE_func304(void);
void R_SCE_func305(void);
void R_SCE_func307(void);
void R_SCE_func308(void);
void R_SCE_func309(void);
void R_SCE_func310(void);
void R_SCE_func311(void);
void R_SCE_func312(uint32_t ARG1);
void R_SCE_func313(uint32_t ARG1);
void R_SCE_func314(uint32_t ARG1);
void R_SCE_func315(uint32_t ARG1);
void R_SCE_func316(void);
void R_SCE_func317(void);
void R_SCE_func318(void);
void R_SCE_func319(uint32_t ARG1);
void R_SCE_func320(uint32_t ARG1);
void R_SCE_func321(uint32_t ARG1);
void R_SCE_func322(uint32_t ARG1);
void R_SCE_func323(void);
void R_SCE_func324(void);
void R_SCE_func325(void);

uint32_t change_endian_long(uint32_t data);

#endif                                 /* R_SCE_PRIVATE_HEADER_FILE */
