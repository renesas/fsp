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
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sce_private.h"

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
static lifecycle_t gs_lifecycle;

/***********************************************************************************************************************
 * Global variables
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
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_AES256_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
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
    SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD,
    SCE_OEM_KEY_SIZE_HMAC_SHA256_INST_DATA_WORD,
};

uint32_t        g_private_id_counter;
extern uint32_t g_aes128ecbenc_private_id;
extern uint32_t g_aes128ecbdec_private_id;
extern uint32_t g_aes256ecbenc_private_id;
extern uint32_t g_aes256ecbdec_private_id;
extern uint32_t g_aes128cbcenc_private_id;
extern uint32_t g_aes128cbcdec_private_id;
extern uint32_t g_aes256cbcenc_private_id;
extern uint32_t g_aes256cbcdec_private_id;
extern uint32_t g_aes128cmacgen_private_id;
extern uint32_t g_aes128cmacver_private_id;
extern uint32_t g_aes256cmacgen_private_id;
extern uint32_t g_aes256cmacver_private_id;
extern uint32_t g_aes128gcmenc_private_id;
extern uint32_t g_aes128gcmdec_private_id;
extern uint32_t g_aes256gcmenc_private_id;
extern uint32_t g_aes256gcmdec_private_id;
extern uint32_t g_aes128ccmenc_private_id;
extern uint32_t g_aes128ccmdec_private_id;
extern uint32_t g_aes256ccmenc_private_id;
extern uint32_t g_aes256ccmdec_private_id;
extern uint32_t g_sha256_private_id;
extern uint32_t g_sha256hmacgen_private_id;
extern uint32_t g_sha256hmacver_private_id;
extern uint32_t g_ecdh256_private_id;

const sce_api_t g_sce_protected_on_sce =
{
    .open                                              = R_SCE_Open,
    .close                                             = R_SCE_Close,
    .softwareReset                                     = R_SCE_SoftwareReset,
    .randomNumberGenerate                              = R_SCE_RandomNumberGenerate,
    .AES128_WrappedKeyGenerate                         = R_SCE_AES128_WrappedKeyGenerate,
    .AES256_WrappedKeyGenerate                         = R_SCE_AES256_WrappedKeyGenerate,
    .AES128_EncryptedKeyWrap                           = R_SCE_AES128_EncryptedKeyWrap,
    .AES256_EncryptedKeyWrap                           = R_SCE_AES256_EncryptedKeyWrap,
    .AES128_RFC3394KeyWrap                             = R_SCE_AES128_RFC3394KeyWrap,
    .AES256_RFC3394KeyWrap                             = R_SCE_AES256_RFC3394KeyWrap,
    .AES128_RFC3394KeyUnwrap                           = R_SCE_AES128_RFC3394KeyUnwrap,
    .AES256_RFC3394KeyUnwrap                           = R_SCE_AES256_RFC3394KeyUnwrap,
    .AES128ECB_EncryptInit                             = R_SCE_AES128ECB_EncryptInit,
    .AES128ECB_EncryptUpdate                           = R_SCE_AES128ECB_EncryptUpdate,
    .AES128ECB_EncryptFinal                            = R_SCE_AES128ECB_EncryptFinal,
    .AES128ECB_DecryptInit                             = R_SCE_AES128ECB_DecryptInit,
    .AES128ECB_DecryptUpdate                           = R_SCE_AES128ECB_DecryptUpdate,
    .AES128ECB_DecryptFinal                            = R_SCE_AES128ECB_DecryptFinal,
    .AES256ECB_EncryptInit                             = R_SCE_AES256ECB_EncryptInit,
    .AES256ECB_EncryptUpdate                           = R_SCE_AES256ECB_EncryptUpdate,
    .AES256ECB_EncryptFinal                            = R_SCE_AES256ECB_EncryptFinal,
    .AES256ECB_DecryptInit                             = R_SCE_AES256ECB_DecryptInit,
    .AES256ECB_DecryptUpdate                           = R_SCE_AES256ECB_DecryptUpdate,
    .AES256ECB_DecryptFinal                            = R_SCE_AES256ECB_DecryptFinal,
    .AES128CBC_EncryptInit                             = R_SCE_AES128CBC_EncryptInit,
    .AES128CBC_EncryptUpdate                           = R_SCE_AES128CBC_EncryptUpdate,
    .AES128CBC_EncryptFinal                            = R_SCE_AES128CBC_EncryptFinal,
    .AES128CBC_DecryptInit                             = R_SCE_AES128CBC_DecryptInit,
    .AES128CBC_DecryptUpdate                           = R_SCE_AES128CBC_DecryptUpdate,
    .AES128CBC_DecryptFinal                            = R_SCE_AES128CBC_DecryptFinal,
    .AES256CBC_EncryptInit                             = R_SCE_AES256CBC_EncryptInit,
    .AES256CBC_EncryptUpdate                           = R_SCE_AES256CBC_EncryptUpdate,
    .AES256CBC_EncryptFinal                            = R_SCE_AES256CBC_EncryptFinal,
    .AES256CBC_DecryptInit                             = R_SCE_AES256CBC_DecryptInit,
    .AES256CBC_DecryptUpdate                           = R_SCE_AES256CBC_DecryptUpdate,
    .AES256CBC_DecryptFinal                            = R_SCE_AES256CBC_DecryptFinal,
    .AES128GCM_EncryptInit                             = R_SCE_AES128GCM_EncryptInit,
    .AES128GCM_EncryptUpdate                           = R_SCE_AES128GCM_EncryptUpdate,
    .AES128GCM_EncryptFinal                            = R_SCE_AES128GCM_EncryptFinal,
    .AES128GCM_DecryptInit                             = R_SCE_AES128GCM_DecryptInit,
    .AES128GCM_DecryptUpdate                           = R_SCE_AES128GCM_DecryptUpdate,
    .AES128GCM_DecryptFinal                            = R_SCE_AES128GCM_DecryptFinal,
    .AES256GCM_EncryptInit                             = R_SCE_AES256GCM_EncryptInit,
    .AES256GCM_EncryptUpdate                           = R_SCE_AES256GCM_EncryptUpdate,
    .AES256GCM_EncryptFinal                            = R_SCE_AES256GCM_EncryptFinal,
    .AES256GCM_DecryptInit                             = R_SCE_AES256GCM_DecryptInit,
    .AES256GCM_DecryptUpdate                           = R_SCE_AES256GCM_DecryptUpdate,
    .AES256GCM_DecryptFinal                            = R_SCE_AES256GCM_DecryptFinal,
    .AES128CCM_EncryptInit                             = R_SCE_AES128CCM_EncryptInit,
    .AES128CCM_EncryptUpdate                           = R_SCE_AES128CCM_EncryptUpdate,
    .AES128CCM_EncryptFinal                            = R_SCE_AES128CCM_EncryptFinal,
    .AES128CCM_DecryptInit                             = R_SCE_AES128CCM_DecryptInit,
    .AES128CCM_DecryptUpdate                           = R_SCE_AES128CCM_DecryptUpdate,
    .AES128CCM_DecryptFinal                            = R_SCE_AES128CCM_DecryptFinal,
    .AES256CCM_EncryptInit                             = R_SCE_AES256CCM_EncryptInit,
    .AES256CCM_EncryptUpdate                           = R_SCE_AES256CCM_EncryptUpdate,
    .AES256CCM_EncryptFinal                            = R_SCE_AES256CCM_EncryptFinal,
    .AES256CCM_DecryptInit                             = R_SCE_AES256CCM_DecryptInit,
    .AES256CCM_DecryptUpdate                           = R_SCE_AES256CCM_DecryptUpdate,
    .AES256CCM_DecryptFinal                            = R_SCE_AES256CCM_DecryptFinal,
    .AES128CMAC_GenerateInit                           = R_SCE_AES128CMAC_GenerateInit,
    .AES128CMAC_GenerateUpdate                         = R_SCE_AES128CMAC_GenerateUpdate,
    .AES128CMAC_GenerateFinal                          = R_SCE_AES128CMAC_GenerateFinal,
    .AES128CMAC_VerifyInit                             = R_SCE_AES128CMAC_VerifyInit,
    .AES128CMAC_VerifyUpdate                           = R_SCE_AES128CMAC_VerifyUpdate,
    .AES128CMAC_VerifyFinal                            = R_SCE_AES128CMAC_VerifyFinal,
    .AES256CMAC_GenerateInit                           = R_SCE_AES256CMAC_GenerateInit,
    .AES256CMAC_GenerateUpdate                         = R_SCE_AES256CMAC_GenerateUpdate,
    .AES256CMAC_GenerateFinal                          = R_SCE_AES256CMAC_GenerateFinal,
    .AES256CMAC_VerifyInit                             = R_SCE_AES256CMAC_VerifyInit,
    .AES256CMAC_VerifyUpdate                           = R_SCE_AES256CMAC_VerifyUpdate,
    .AES256CMAC_VerifyFinal                            = R_SCE_AES256CMAC_VerifyFinal,
    .SHA256_Init                                       = R_SCE_SHA256_Init,
    .SHA256_Update                                     = R_SCE_SHA256_Update,
    .SHA256_Final                                      = R_SCE_SHA256_Final,
    .RSA1024_WrappedKeyPairGenerate                    = R_SCE_RSA1024_WrappedKeyPairGenerate,
    .RSA2048_WrappedKeyPairGenerate                    = R_SCE_RSA2048_WrappedKeyPairGenerate,
    .RSA1024_EncryptedPublicKeyWrap                    = R_SCE_RSA1024_EncryptedPublicKeyWrap,
    .RSA1024_EncryptedPrivateKeyWrap                   = R_SCE_RSA1024_EncryptedPrivateKeyWrap,
    .RSA2048_EncryptedPublicKeyWrap                    = R_SCE_RSA2048_EncryptedPublicKeyWrap,
    .RSA2048_EncryptedPrivateKeyWrap                   = R_SCE_RSA2048_EncryptedPrivateKeyWrap,
    .RSA3072_EncryptedPublicKeyWrap                    = R_SCE_RSA3072_EncryptedPublicKeyWrap,
    .RSA4096_EncryptedPublicKeyWrap                    = R_SCE_RSA4096_EncryptedPublicKeyWrap,
    .RSASSA_PKCS1024_SignatureGenerate                 = R_SCE_RSASSA_PKCS1024_SignatureGenerate,
    .RSASSA_PKCS2048_SignatureGenerate                 = R_SCE_RSASSA_PKCS2048_SignatureGenerate,
    .RSASSA_PKCS1024_SignatureVerify                   = R_SCE_RSASSA_PKCS1024_SignatureVerify,
    .RSASSA_PKCS2048_SignatureVerify                   = R_SCE_RSASSA_PKCS2048_SignatureVerify,
    .RSASSA_PKCS3072_SignatureVerify                   = R_SCE_RSASSA_PKCS3072_SignatureVerify,
    .RSASSA_PKCS4096_SignatureVerify                   = R_SCE_RSASSA_PKCS4096_SignatureVerify,
    .RSAES_PKCS1024_Encrypt                            = R_SCE_RSAES_PKCS1024_Encrypt,
    .RSAES_PKCS2048_Encrypt                            = R_SCE_RSAES_PKCS2048_Encrypt,
    .RSAES_PKCS3072_Encrypt                            = R_SCE_RSAES_PKCS3072_Encrypt,
    .RSAES_PKCS4096_Encrypt                            = R_SCE_RSAES_PKCS4096_Encrypt,
    .RSAES_PKCS1024_Decrypt                            = R_SCE_RSAES_PKCS1024_Decrypt,
    .RSAES_PKCS2048_Decrypt                            = R_SCE_RSAES_PKCS2048_Decrypt,
    .SHA256HMAC_EncryptedKeyWrap                       = R_SCE_SHA256HMAC_EncryptedKeyWrap,
    .SHA256HMAC_GenerateInit                           = R_SCE_SHA256HMAC_GenerateInit,
    .SHA256HMAC_GenerateUpdate                         = R_SCE_SHA256HMAC_GenerateUpdate,
    .SHA256HMAC_GenerateFinal                          = R_SCE_SHA256HMAC_GenerateFinal,
    .SHA256HMAC_VerifyInit                             = R_SCE_SHA256HMAC_VerifyInit,
    .SHA256HMAC_VerifyUpdate                           = R_SCE_SHA256HMAC_VerifyUpdate,
    .SHA256HMAC_VerifyFinal                            = R_SCE_SHA256HMAC_VerifyFinal,
    .ECC_secp192r1_WrappedKeyPairGenerate              = R_SCE_ECC_secp192r1_WrappedKeyPairGenerate,
    .ECC_secp224r1_WrappedKeyPairGenerate              = R_SCE_ECC_secp224r1_WrappedKeyPairGenerate,
    .ECC_secp256r1_WrappedKeyPairGenerate              = R_SCE_ECC_secp256r1_WrappedKeyPairGenerate,
    .ECC_secp384r1_WrappedKeyPairGenerate              = R_SCE_ECC_secp384r1_WrappedKeyPairGenerate,
    .ECC_secp192r1_EncryptedPublicKeyWrap              = R_SCE_ECC_secp192r1_EncryptedPublicKeyWrap,
    .ECC_secp224r1_EncryptedPublicKeyWrap              = R_SCE_ECC_secp224r1_EncryptedPublicKeyWrap,
    .ECC_secp256r1_EncryptedPublicKeyWrap              = R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap,
    .ECC_secp384r1_EncryptedPublicKeyWrap              = R_SCE_ECC_secp384r1_EncryptedPublicKeyWrap,
    .ECC_secp192r1_EncryptedPrivateKeyWrap             = R_SCE_ECC_secp192r1_EncryptedPrivateKeyWrap,
    .ECC_secp224r1_EncryptedPrivateKeyWrap             = R_SCE_ECC_secp224r1_EncryptedPrivateKeyWrap,
    .ECC_secp256r1_EncryptedPrivateKeyWrap             = R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap,
    .ECC_secp384r1_EncryptedPrivateKeyWrap             = R_SCE_ECC_secp384r1_EncryptedPrivateKeyWrap,
    .ECDSA_secp192r1_SignatureGenerate                 = R_SCE_ECDSA_secp192r1_SignatureGenerate,
    .ECDSA_secp224r1_SignatureGenerate                 = R_SCE_ECDSA_secp224r1_SignatureGenerate,
    .ECDSA_secp256r1_SignatureGenerate                 = R_SCE_ECDSA_secp256r1_SignatureGenerate,
    .ECDSA_secp384r1_SignatureGenerate                 = R_SCE_ECDSA_secp384r1_SignatureGenerate,
    .ECDSA_secp192r1_SignatureVerify                   = R_SCE_ECDSA_secp192r1_SignatureVerify,
    .ECDSA_secp224r1_SignatureVerify                   = R_SCE_ECDSA_secp224r1_SignatureVerify,
    .ECDSA_secp256r1_SignatureVerify                   = R_SCE_ECDSA_secp256r1_SignatureVerify,
    .ECDSA_secp384r1_SignatureVerify                   = R_SCE_ECDSA_secp384r1_SignatureVerify,
    .ECDH_secp256r1_Init                               = R_SCE_ECDH_secp256r1_Init,
    .ECDH_secp256r1_PublicKeySign                      = R_SCE_ECDH_secp256r1_PublicKeySign,
    .ECDH_secp256r1_PublicKeyVerify                    = R_SCE_ECDH_secp256r1_PublicKeyVerify,
    .ECDH_secp256r1_SharedSecretCalculate              = R_SCE_ECDH_secp256r1_SharedSecretCalculate,
    .ECDH_secp256r1_KeyDerivation                      = R_SCE_ECDH_secp256r1_KeyDerivation,
    .ECDH_secp256r1_PublicKeyReadWithoutSignature      = R_SCE_ECDH_secp256r1_PublicKeyReadWithoutSignature,
    .TLS_RootCertificateRSA2048PublicKeyInstall        = R_SCE_TLS_RootCertificateRSA2048PublicKeyInstall,
    .TLS_ECC_secp256r1_EphemeralWrappedKeyPairGenerate = R_SCE_TLS_ECC_secp256r1_EphemeralWrappedKeyPairGenerate,
    .TLS_RootCertificateVerify                         = R_SCE_TLS_RootCertificateVerify,
    .TLS_CertificateVerify                             = R_SCE_TLS_CertificateVerify,
    .TLS_PreMasterSecretGenerateForRSA2048             = R_SCE_TLS_PreMasterSecretGenerateForRSA2048,
    .TLS_MasterSecretGenerate                          = R_SCE_TLS_MasterSecretGenerate,
    .TLS_PreMasterSecretEncryptWithRSA2048             = R_SCE_TLS_PreMasterSecretEncryptWithRSA2048,
    .TLS_SessionKeyGenerate                            = R_SCE_TLS_SessionKeyGenerate,
    .TLS_VerifyDataGenerate                            = R_SCE_TLS_VerifyDataGenerate,
    .TLS_ServerKeyExchangeVerify                       = R_SCE_TLS_ServerKeyExchangeVerify,
    .TLS_PreMasterSecretGenerateForECC_secp256r1       = R_SCE_TLS_PreMasterSecretGenerateForECC_secp256r1
};

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables use of SCE functionality.
 *
 * @param[in] p_ctrl Pointer to control structure.
 * @param[in] p_cfg Pointer to pin configuration structure.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              The error-detection self-test failed to terminate normally.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_RETRY             Indicates that an entropy evaluation failure occurred.
 *                                              Run the function again.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *
 * @note The valid pre-run state is SCE disabled.
 *       The pre-run state is SCE Disabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Open (sce_ctrl_t * const p_ctrl, sce_cfg_t const * const p_cfg)
{
    fsp_err_t error_code = FSP_SUCCESS;

    sce_instance_ctrl_t * p_instance_ctrl = (sce_instance_ctrl_t *) p_ctrl;
    p_instance_ctrl->open = 1;
    gs_lifecycle          = p_cfg->lifecycle;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    MSTP_SECURITY = 0U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
    R_SCE_SoftwareReset();
    error_code = R_SCE_SelfCheck1Private();

#ifndef __ARMEB__                      /* Little endian */
    /* Casting structure pointer is used for address. */
    const uint32_t register_value = 0x0000ffff;
    SCE->REG_1D4H = register_value;
#endif

    if (FSP_SUCCESS == error_code)
    {
        error_code = R_SCE_LoadHukPrivate(p_cfg->lifecycle);
    }

    if (FSP_SUCCESS == error_code)
    {
        error_code = R_SCE_FwIntegrityCheckPrivate();
    }

#if (0 == SCE_USER_FAST_BOOT)
    if (FSP_SUCCESS == error_code)
    {
        error_code = R_SCE_SelfCheck2Private();
    }
#endif 

    if (FSP_SUCCESS == error_code)
    {
        error_code = R_SCE_SelfCheck3Private();
    }

    g_private_id_counter       = 0;
    g_aes128ecbenc_private_id  = 0;
    g_aes128ecbdec_private_id  = 0;
    g_aes256ecbenc_private_id  = 0;
    g_aes256ecbdec_private_id  = 0;
    g_aes128cbcenc_private_id  = 0;
    g_aes128cbcdec_private_id  = 0;
    g_aes256cbcenc_private_id  = 0;
    g_aes256cbcdec_private_id  = 0;
    g_aes128cmacgen_private_id = 0;
    g_aes128cmacver_private_id = 0;
    g_aes256cmacgen_private_id = 0;
    g_aes256cmacver_private_id = 0;
    g_aes128gcmenc_private_id  = 0;
    g_aes128gcmdec_private_id  = 0;
    g_aes256gcmenc_private_id  = 0;
    g_aes256gcmdec_private_id  = 0;
    g_aes128ccmenc_private_id  = 0;
    g_aes128ccmdec_private_id  = 0;
    g_aes256ccmenc_private_id  = 0;
    g_aes256ccmdec_private_id  = 0;
    g_sha256_private_id        = 0;
    g_sha256hmacgen_private_id = 0;
    g_sha256hmacver_private_id = 0;
    g_ecdh256_private_id       = 0;

    return error_code;
}

/*******************************************************************************************************************//**
 * Stops supply of power to the SCE.
 *
 * @param[in] p_ctrl Pointer to control structure.
 *
 * @retval FSP_SUCCESS              Normal termination
 *
 * @note The pre-run state is any state.
 *       After the function runs the state transitions to SCE Disabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Close (sce_ctrl_t * const p_ctrl)
{
    sce_instance_ctrl_t * p_instance_ctrl = (sce_instance_ctrl_t *) p_ctrl;
    p_instance_ctrl->open = 0;
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    MSTP_SECURITY = 1U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Software reset to SCE.
 *
 * Reverts the state to the SCE initial state.
 *
 * @retval FSP_SUCCESS              Normal termination
 *
 * @note The pre-run state is any state.
 *       After the function runs the state transitions to SCE Disabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SoftwareReset (void)
{
    R_SCE_SoftwareResetSub();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This API can generate 4 words random number.
 *
 * @param[in,out] random Stores 4words (16 bytes) random data.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RandomNumberGenerate (uint32_t * random)
{
    return R_SCE_GenerateRandomNumberSub(random);
}

/*******************************************************************************************************************//**
 * This API outputs 128-bit AES wrapped key from a random number.
 *
 * This API generates a wrapped key from a random number in the SCE. Accordingly, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.
 *
 * @param[in,out] wrapped_key 128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Disabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_WrappedKeyGenerate (sce_aes_wrapped_key_t * wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
    error_code = R_SCE_GenerateAes128RandomKeyIndexSub(wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128;
    }
    else if (FSP_SUCCESS == FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    else
    {
        /* not used */
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API outputs 256-bit AES wrapped key from a random number.
 *
 * This API generates a wrapped key from a random number in the SCE. Accordingly, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.
 *
 * @param[in,out] wrapped_key 256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Disabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_WrappedKeyGenerate (sce_aes_wrapped_key_t * wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
    error_code = R_SCE_GenerateAes256RandomKeyIndexSub(wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 128-bit AES key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_EncryptedKeyWrap (uint8_t               * initial_vector,
                                         uint8_t               * encrypted_key,
                                         sce_key_update_key_t  * key_update_key,
                                         sce_aes_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_AES128;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 256-bit AES key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_EncryptedKeyWrap (uint8_t               * initial_vector,
                                         uint8_t               * encrypted_key,
                                         sce_key_update_key_t  * key_update_key,
                                         sce_aes_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_AES256;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 128-bit AES key within the user routine.
 * @param[in]  master_key          AES-128 key used for wrapping.
 * @param[in]  target_key_type     Selects key to be wrapped.
 * @param[in]  target_key          Key to be wrapped.
 * @param[out] rfc3394_wrapped_key Wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_RFC3394KeyWrap (sce_aes_wrapped_key_t * master_key,
                                       uint32_t target_key_type,
                                       sce_aes_wrapped_key_t * target_key,
                                       uint32_t * rfc3394_wrapped_key)
{
    return R_SCE_Aes128KeyWrapPrivate(
            /* Casting uint32_t pointer is used for address. */
            (uint32_t*)&master_key->value, &target_key_type, (uint32_t*)&target_key->value, rfc3394_wrapped_key);
}

/*******************************************************************************************************************//**
 * This API wraps 256-bit AES key within the user routine.
 * @param[in]  master_key          AES-256 key used for wrapping.
 * @param[in]  target_key_type     Selects key to be wrapped.
 * @param[in]  target_key          Key to be wrapped.
 * @param[out] rfc3394_wrapped_key Wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_RFC3394KeyWrap (sce_aes_wrapped_key_t * master_key,
                                       uint32_t target_key_type,
                                       sce_aes_wrapped_key_t * target_key,
                                       uint32_t * rfc3394_wrapped_key)
{
    return R_SCE_Aes256KeyWrapPrivate(
            /* Casting uint32_t pointer is used for address. */
            (uint32_t*)&master_key->value, &target_key_type, (uint32_t*)&target_key->value, rfc3394_wrapped_key);
}

/*******************************************************************************************************************//**
 * This API unwraps 128-bit AES key within the user routine.
 * @param[in]  master_key          AES-128 key used for unwrapping.
 * @param[in]  target_key_type     Selects key to be unwrapped.
 * @param[in]  rfc3394_wrapped_key Wrapped key.
 * @param[out] target_key          Key to be unwrapped.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_RFC3394KeyUnwrap (sce_aes_wrapped_key_t * master_key,
                                         uint32_t target_key_type,
                                         uint32_t * rfc3394_wrapped_key,
                                         sce_aes_wrapped_key_t * target_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

    error_code = R_SCE_Aes128KeyUnWrapPrivate(master_key, &target_key_type, rfc3394_wrapped_key, target_key->value);
    if (FSP_SUCCESS == error_code)
    {
        if (SCE_KEYWRAP_AES128 == target_key_type)
        {
            target_key->type = SCE_KEY_INDEX_TYPE_AES128;
        }
        else    /* if (SCE_KEYWRAP_AES128 == target_key_type) */
        {
            target_key->type =SCE_KEY_INDEX_TYPE_AES256;
        }
    }
    else
    {
        target_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * This API unwraps 256-bit AES key within the user routine.
 * @param[in]  master_key          AES-256 key used for unwrapping.
 * @param[in]  target_key_type     Selects key to be unwrapped.
 * @param[in]  rfc3394_wrapped_key Wrapped key.
 * @param[out] target_key          Key to be unwrapped.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_RFC3394KeyUnwrap (sce_aes_wrapped_key_t * master_key,
                                         uint32_t target_key_type,
                                         uint32_t * rfc3394_wrapped_key,
                                         sce_aes_wrapped_key_t * target_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

    error_code = R_SCE_Aes256KeyUnWrapPrivate(master_key, &target_key_type, rfc3394_wrapped_key, target_key->value);
    if (FSP_SUCCESS == error_code)
    {
        if (SCE_KEYWRAP_AES128 == target_key_type)
        {
            target_key->type = SCE_KEY_INDEX_TYPE_AES128;
        }
        else    /* if (SCE_KEYWRAP_AES128 == target_key_type) */
        {
            target_key->type =SCE_KEY_INDEX_TYPE_AES256;
        }
    }
    else
    {
        target_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps HMAC-SHA256 key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   HMAC-SHA256 wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_SHA256HMAC_EncryptedKeyWrap (uint8_t                    * initial_vector,
                                             uint8_t                    * encrypted_key,
                                             sce_key_update_key_t       * key_update_key,
                                             sce_hmac_sha_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_HMAC_SHA256;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA256;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API outputs a wrapped key pair for a 1024-bit RSA public key and private key pair. These keys are generated
 * from a random value produced internally by the SCE. Consequently, there is no need to input a user key.
 * Dead copying of data can be prevented by encrypting the data using the wrapped key output by this API.
 * A public wrapped key is generated by wrapped_pair_key->pub_key, and a private wrapped key is generated by
 * wrapped_pair_key->priv_key. As the public key exponent, only 0x00010001 is generated.
 *
 * @param [in,out] wrapped_pair_key User key index for RSA 1024-bit public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred. Key generation failed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA1024_WrappedKeyPairGenerate (sce_rsa1024_wrapped_pair_key_t * wrapped_pair_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
    error_code = R_SCE_GenerateRsa1024RandomKeyIndexSub(SCE_RSA_RETRY_COUNT_FOR_RSA_KEY_GENERATION,
                                       /* Casting uint32_t pointer is used for address. */
                                                         (uint32_t *) &wrapped_pair_key->pub_key.value,
                                                         (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_RSA1024_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_RSA1024_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API outputs a wrapped key pair for a 2048-bit RSA public key and private key pair. These keys are generated
 * from a random value produced internally by the SCE. Consequently, there is no need to input a user key.
 * Dead copying of data can be prevented by encrypting the data using the wrapped key output by this API.
 * A public wrapped key is generated by wrapped_pair_key->pub_key, and a private wrapped key is generated by
 * wrapped_pair_key->priv_key. As the public key exponent, only 0x00010001 is generated.
 *
 * @param [in,out] wrapped_pair_key User key index for RSA 2048-bit public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal end
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred. Key generation failed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_WrappedKeyPairGenerate (sce_rsa2048_wrapped_pair_key_t * wrapped_pair_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
    error_code = R_SCE_GenerateRsa2048RandomKeyIndexSub(SCE_RSA_RETRY_COUNT_FOR_RSA_KEY_GENERATION,
                                       /* Casting uint32_t pointer is used for address. */
                                                         (uint32_t *) &wrapped_pair_key->pub_key.value,
                                                         (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 1024-bit RSA public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   1024-bit RSA public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA1024_EncryptedPublicKeyWrap (uint8_t                          * initial_vector,
                                                uint8_t                          * encrypted_key,
                                                sce_key_update_key_t             * key_update_key,
                                                sce_rsa1024_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA1024_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA1024_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 1024-bit RSA private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   1024-bit RSA private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA1024_EncryptedPrivateKeyWrap (uint8_t                           * initial_vector,
                                                 uint8_t                           * encrypted_key,
                                                 sce_key_update_key_t              * key_update_key,
                                                 sce_rsa1024_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA1024_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA1024_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 2048-bit RSA public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   1024-bit RSA public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_EncryptedPublicKeyWrap (uint8_t                          * initial_vector,
                                                uint8_t                          * encrypted_key,
                                                sce_key_update_key_t             * key_update_key,
                                                sce_rsa2048_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA2048_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 2048-bit RSA private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   2048-bit RSA private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_EncryptedPrivateKeyWrap (uint8_t                           * initial_vector,
                                                 uint8_t                           * encrypted_key,
                                                 sce_key_update_key_t              * key_update_key,
                                                 sce_rsa2048_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA2048_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 3072-bit RSA public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   3072-bit RSA public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA3072_EncryptedPublicKeyWrap (uint8_t                          * initial_vector,
                                                uint8_t                          * encrypted_key,
                                                sce_key_update_key_t             * key_update_key,
                                                sce_rsa3072_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA3072_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA3072_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 4096-bit RSA public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   1024-bit RSA public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA4096_EncryptedPublicKeyWrap (uint8_t                          * initial_vector,
                                                uint8_t                          * encrypted_key,
                                                sce_key_update_key_t             * key_update_key,
                                                sce_rsa4096_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_RSA4096_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA4096_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This is an API for outputting a wrapped key pair for secp192r1 public key and private key pair. These keys are generated
 * from a random number value internally within the SCE.
 * There is therefore no need to input user keys. It is possible to prevent dead copying of data by using the
 * wrapped key output by this API to encrypt the data. The public key index is generated in wrapped_pair_key->pub_key,
 * and the private key index is generated in wrapped_pair_key->priv_key.
 *
 * @param[in,out] wrapped_pair_key Wrapped pair key for secp192r1 public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp192r1_WrappedKeyPairGenerate (sce_ecc_wrapped_pair_key_t * wrapped_pair_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_192);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_GenerateEccRandomKeyIndexSub(&curvetype,
                                       /* Casting uint32_t pointer is used for address. */
                                                     &indata_cmd,
                                                     (uint32_t *) &wrapped_pair_key->pub_key.value,
                                                     (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_ECC_P192_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_ECC_P192_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This is an API for outputting a wrapped key pair for secp224r1 public key and private key pair. These keys are generated
 * from a random number value internally within the SCE.
 * There is therefore no need to input user keys. It is possible to prevent dead copying of data by using the
 * wrapped key output by this API to encrypt the data. The public key index is generated in wrapped_pair_key->pub_key,
 * and the private key index is generated in wrapped_pair_key->priv_key.
 *
 * @param[in,out] wrapped_pair_key Wrapped pair key for secp224r1 public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp224r1_WrappedKeyPairGenerate (sce_ecc_wrapped_pair_key_t * wrapped_pair_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_224);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_GenerateEccRandomKeyIndexSub(&curvetype,
                                       /* Casting uint32_t pointer is used for address. */
                                                     &indata_cmd,
                                                     (uint32_t *) &wrapped_pair_key->pub_key.value,
                                                     (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_ECC_P224_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_ECC_P224_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This is an API for outputting a wrapped key pair for secp256r1 public key and private key pair. These keys are generated
 * from a random number value internally within the SCE.
 * There is therefore no need to input user keys. It is possible to prevent dead copying of data by using the
 * wrapped key output by this API to encrypt the data. The public key index is generated in wrapped_pair_key->pub_key,
 * and the private key index is generated in wrapped_pair_key->priv_key.
 *
 * @param[in,out] wrapped_pair_key Wrapped pair key for secp256r1 public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_WrappedKeyPairGenerate (sce_ecc_wrapped_pair_key_t * wrapped_pair_key)
{
    uint32_t  indata_cmd;
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;

    indata_cmd = change_endian_long(SCE_ECC_KEY_LENGTH_256);
    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_GenerateEccRandomKeyIndexSub(&curvetype,
                                       /* Casting uint32_t pointer is used for address. */
                                                     &indata_cmd,
                                                     (uint32_t *) &wrapped_pair_key->pub_key.value,
                                                     (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This is an API for outputting a wrapped key pair for secp384r1 public key and private key pair. These keys are generated
 * from a random number value internally within the SCE.
 * There is therefore no need to input user keys. It is possible to prevent dead copying of data by using the
 * wrapped key output by this API to encrypt the data. The public key index is generated in wrapped_pair_key->pub_key,
 * and the private key index is generated in wrapped_pair_key->priv_key.
 *
 * @param[in,out] wrapped_pair_key Wrapped pair key for secp384r1 public key and private key pair
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp384r1_WrappedKeyPairGenerate (sce_ecc_wrapped_pair_key_t * wrapped_pair_key)
{
    uint32_t  curvetype;
    fsp_err_t error_code = FSP_SUCCESS;

    curvetype  = change_endian_long(SCE_ECC_CURVE_TYPE_NIST);
    error_code = R_SCE_GenerateEccP384RandomKeyIndexSub(
        /* Casting uint32_t pointer is used for address. */
        &curvetype,
        (uint32_t *) &wrapped_pair_key->pub_key.value,
        (uint32_t *) &wrapped_pair_key->priv_key.value);
    if (FSP_SUCCESS == error_code)
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_ECC_P384_PUBLIC;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_ECC_P384_PRIVATE;
    }
    else
    {
        wrapped_pair_key->pub_key.type  = SCE_KEY_INDEX_TYPE_INVALID;
        wrapped_pair_key->priv_key.type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp192r1 public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp192r1 public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp192r1_EncryptedPublicKeyWrap (uint8_t                      * initial_vector,
                                                      uint8_t                      * encrypted_key,
                                                      sce_key_update_key_t         * key_update_key,
                                                      sce_ecc_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P192_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P192_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp224r1 public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp224r1 public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp224r1_EncryptedPublicKeyWrap (uint8_t                      * initial_vector,
                                                      uint8_t                      * encrypted_key,
                                                      sce_key_update_key_t         * key_update_key,
                                                      sce_ecc_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P224_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P224_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp256r1 public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp256r1 public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap (uint8_t                      * initial_vector,
                                                      uint8_t                      * encrypted_key,
                                                      sce_key_update_key_t         * key_update_key,
                                                      sce_ecc_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P256_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp384r1 public key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp384r1 public wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp384r1_EncryptedPublicKeyWrap (uint8_t                      * initial_vector,
                                                      uint8_t                      * encrypted_key,
                                                      sce_key_update_key_t         * key_update_key,
                                                      sce_ecc_public_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P384_PUBLIC;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P384_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp192r1 private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp192r1 private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp192r1_EncryptedPrivateKeyWrap (uint8_t                       * initial_vector,
                                                       uint8_t                       * encrypted_key,
                                                       sce_key_update_key_t          * key_update_key,
                                                       sce_ecc_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P192_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P192_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp224r1 private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp224r1 private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp224r1_EncryptedPrivateKeyWrap (uint8_t                       * initial_vector,
                                                       uint8_t                       * encrypted_key,
                                                       sce_key_update_key_t          * key_update_key,
                                                       sce_ecc_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P224_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P224_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp256r1 private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp256r1 private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap (uint8_t                       * initial_vector,
                                                       uint8_t                       * encrypted_key,
                                                       sce_key_update_key_t          * key_update_key,
                                                       sce_ecc_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P256_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps secp384r1 private key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   secp384r1 private wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp384r1_EncryptedPrivateKeyWrap (uint8_t                       * initial_vector,
                                                       uint8_t                       * encrypted_key,
                                                       sce_key_update_key_t          * key_update_key,
                                                       sce_ecc_private_wrapped_key_t * wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    lifecycle_t   lifecycle  = gs_lifecycle;
    sce_oem_cmd_t key_type   = SCE_OEM_CMD_ECC_P384_PRIVATE;

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = R_SCE_UpdateOemKeyIndexPrivate(lifecycle,
                                                key_type,
                                                initial_vector,
                                                encrypted_key,
                                                (uint32_t *) &wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P384_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * Generate TLS RSA Public key index data
 *
 * @param[in]     encrypted_provisioning_key the provisioning key includes encrypted CBC/CBC-MAC key for user key
 * @param[in]     initial_vector             the initial_vector for user key CBC encrypt
 * @param[in]     encrypted_key              the user key encrypted with AES128-ECB mode
 * @param[out]    wrapped_key                the user Key Generation Information (141 words) of RSA2048 bit
 * 
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 * 
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_RootCertificateRSA2048PublicKeyInstall(uint8_t *encrypted_provisioning_key, uint8_t *initial_vector,
        uint8_t *encrypted_key, sce_tls_ca_certification_public_wrapped_key_t *wrapped_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    uint32_t install_key_ring_index = SCE_INSTALL_KEY_RING_INDEX;
    error_code = R_SCE_GenerateTlsRsaInstallDataSub(&install_key_ring_index,
        /* Casting uint32_t pointer is used for address. */
        (uint32_t*)encrypted_provisioning_key, (uint32_t*)initial_vector, (uint32_t*)encrypted_key, wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        memcpy(S_INST, wrapped_key->value, sizeof(wrapped_key->value));
        wrapped_key->type = SCE_KEY_INDEX_TYPE_TLS_CA_CERTIFICATION_PUBLIC_KEY;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * Generate TLS ECC key pair
 *
 * @param[in] tls_p256_ecc_wrapped_key    P256 ECC key index for TLS
 * @param[in] ephemeral_ecdh_public_key ephemeral ECDH public key
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_ECC_secp256r1_EphemeralWrappedKeyPairGenerate(sce_tls_p256_ecc_wrapped_key_t *tls_p256_ecc_wrapped_key,
        uint8_t *ephemeral_ecdh_public_key)
{
    fsp_err_t     error_code = FSP_SUCCESS;
    error_code = R_SCE_GenerateTlsP256EccKeyIndexSub(tls_p256_ecc_wrapped_key->value,
        /* Casting uint32_t pointer is used for address. */
        (uint32_t*)ephemeral_ecdh_public_key);
    if (FSP_SUCCESS == error_code)
    {
        tls_p256_ecc_wrapped_key->type = SCE_KEY_INDEX_TYPE_TLS_P256_ECC_KEY;
    }
    else
    {
        tls_p256_ecc_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API Loads Hardware Unique Key.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              self-test1 fail
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_LoadHukPrivate (lifecycle_t lifecycle)
{
    uint32_t LC[1];
    LC[0] = lifecycle;

    return R_SCE_LoadHukSub(LC);
}

/*******************************************************************************************************************//**
 * Self check No1
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              self-test1 fail
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_SelfCheck1Private (void)
{
    return R_SCE_SelfCheck1Sub();
}

/*******************************************************************************************************************//**
 * Self check No2
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RETRY             self-test2 fail
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_SelfCheck2Private (void)
{
    return R_SCE_SelfCheck2Sub();
}

/*******************************************************************************************************************//**
 * Self check No3
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RETRY             self-test3 fail
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_SelfCheck3Private (void)
{
    return R_SCE_SelfCheck3Sub();
}

/*******************************************************************************************************************//**
 * Firmware integrity check
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_FwIntegrityCheckPrivate (void)
{
    return R_SCE_FwIntegrityCheckSub();
}

/*******************************************************************************************************************//**
 * This API Updates OEM key index (wrapped key).
 *
 * @retval FSP_SUCCESS
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT
 * @retval FSP_ERR_CRYPTO_SCE_FAIL
 **********************************************************************************************************************/
fsp_err_t R_SCE_UpdateOemKeyIndexPrivate (lifecycle_t   lifecycle,
                                          sce_oem_cmd_t key_type,
                                          uint8_t     * iv,
                                          uint8_t     * encrypted_oem_key,
                                          uint32_t    * key_index)
{
    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t  CMD[1]     = {0};
    uint32_t  LC[1]      = {0};
    CMD[0] = key_type;
    LC[0]  = lifecycle;

    INST_DATA_SIZE = sce_oem_key_size[key_type];

    error_code = R_SCE_UpdateOemKeyIndexSub(LC, CMD, (uint32_t *) iv, (uint32_t *) encrypted_oem_key, key_index);

    return error_code;
}
