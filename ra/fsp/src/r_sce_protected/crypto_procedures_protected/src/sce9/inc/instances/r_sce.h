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

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

#ifndef R_SCE_H
#define R_SCE_H

#include "bsp_api.h"
#include "r_sce_cfg.h"
#include "r_sce_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Various information. */
#define HW_SCE_SRAM_WORD_SIZE           (32U)
#define HW_SCE_SINST_WORD_SIZE          (140U)
#define HW_SCE_SINST2_WORD_SIZE         (16U)
#define HW_SCE_SHEAP_WORD_SIZE          (1504U)
#define HW_SCE_MAC_SIZE                 (16U)

/* ECC curve types. */
#define SCE_ECC_CURVE_TYPE_NIST         (0)
#define SCE_ECC_CURVE_TYPE_BRAINPOOL    (1)
#define SCE_ECC_CURVE_TYPE_KOBLITZ      (2)

/* ECC curve size */
#define SCE_ECC_KEY_LENGTH_256          (0)
#define SCE_ECC_KEY_LENGTH_224          (1)
#define SCE_ECC_KEY_LENGTH_192          (2)

/* For AES operation. */
#define SCE_KEYWRAP_AES128              (0U)
#define SCE_KEYWRAP_AES256              (1U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* key index type */
typedef enum
{
    SCE_KEY_INDEX_TYPE_INVALID = 0U,
    SCE_KEY_INDEX_TYPE_AES128,
    SCE_KEY_INDEX_TYPE_AES256,
    SCE_KEY_INDEX_TYPE_TDES,
    SCE_KEY_INDEX_TYPE_HMAC_SHA1,
    SCE_KEY_INDEX_TYPE_HMAC_SHA256,
    SCE_KEY_INDEX_TYPE_RSA1024_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA1024_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA3072_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA3072_PRIVATE,
    SCE_KEY_INDEX_TYPE_RSA4096_PUBLIC,
    SCE_KEY_INDEX_TYPE_RSA4096_PRIVATE,
    SCE_KEY_INDEX_TYPE_AES128_FOR_TLS,
    SCE_KEY_INDEX_TYPE_AES192_FOR_TLS,
    SCE_KEY_INDEX_TYPE_AES256_FOR_TLS,
    SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS,
    SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS,
    SCE_KEY_INDEX_TYPE_UPDATE_KEY_RING,
    SCE_KEY_INDEX_TYPE_TLS_CA_CERTIFICATION_PUBLIC_KEY,
    SCE_KEY_INDEX_TYPE_TLS_P256_ECC_KEY,
    SCE_KEY_INDEX_TYPE_ECC_P192_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P224_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P384_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P192_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P224_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P384_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P256R1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P384R1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_P256R1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_P384R1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECC_SECP256K1_PUBLIC,
    SCE_KEY_INDEX_TYPE_ECC_SECP256K1_PRIVATE,
    SCE_KEY_INDEX_TYPE_ECDH_SHARED_SECRET,
    SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH,
    SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH,
    SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_ECDH,
    SCE_KEY_INDEX_TYPE_AES128_GCM_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES256_GCM_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES128_KEY_WRAP_FOR_DLMS_COSEM,
    SCE_KEY_INDEX_TYPE_AES128_GCM_WITH_IV,
} SCE_KEY_INDEX_TYPE;

/* OEM Command */
typedef enum e_sce_oem_cmd
{
    SCE_OEM_CMD_AES128 = 5,
    SCE_OEM_CMD_AES256 = 7,
    SCE_OEM_CMD_RSA1024_PUBLIC = 10,
    SCE_OEM_CMD_RSA1024_PRIVATE,
    SCE_OEM_CMD_RSA2048_PUBLIC,
    SCE_OEM_CMD_RSA2048_PRIVATE,
    SCE_OEM_CMD_RSA3072_PUBLIC,
    SCE_OEM_CMD_RSA3072_PRIVATE,
    SCE_OEM_CMD_RSA4096_PUBLIC,
    SCE_OEM_CMD_RSA4096_PRIVATE,
    SCE_OEM_CMD_ECC_P192_PUBLIC,
    SCE_OEM_CMD_ECC_P192_PRIVATE,
    SCE_OEM_CMD_ECC_P224_PUBLIC,
    SCE_OEM_CMD_ECC_P224_PRIVATE,
    SCE_OEM_CMD_ECC_P256_PUBLIC,
    SCE_OEM_CMD_ECC_P256_PRIVATE,
    SCE_OEM_CMD_ECC_P384_PUBLIC,
    SCE_OEM_CMD_ECC_P384_PRIVATE,
    SCE_OEM_CMD_HMAC_SHA256 = 27,
    SCE_OEM_CMD_NUM
} sce_oem_cmd_t;

/** SCE private control block. DO NOT MODIFY. Initialization occurs when R_SCE_Open() is called. */
typedef struct st_sce_instance_ctrl
{
    uint32_t open;                     // Indicates whether the open() API has been successfully
} sce_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sce_api_t g_sce_protected_on_sce;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_SCE_Open(sce_ctrl_t * const p_ctrl, sce_cfg_t const * const p_cfg);
fsp_err_t R_SCE_Close(sce_ctrl_t * const p_ctrl);
fsp_err_t R_SCE_SoftwareReset(void);

fsp_err_t R_SCE_AES128_WrappedKeyGenerate(sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256_WrappedKeyGenerate(sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA1024_WrappedKeyPairGenerate(sce_rsa1024_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_RSA2048_WrappedKeyPairGenerate(sce_rsa2048_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_ECC_secp192r1_WrappedKeyPairGenerate(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_ECC_secp224r1_WrappedKeyPairGenerate(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_ECC_secp256r1_WrappedKeyPairGenerate(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_ECC_secp384r1_WrappedKeyPairGenerate(sce_ecc_wrapped_pair_key_t * wrapped_pair_key);
fsp_err_t R_SCE_RandomNumberGenerate(uint32_t * random);

fsp_err_t R_SCE_AES128_EncryptedKeyWrap(uint8_t               * initial_vector,
                                        uint8_t               * encrypted_key,
                                        sce_key_update_key_t  * key_update_key,
                                        sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256_EncryptedKeyWrap(uint8_t               * initial_vector,
                                        uint8_t               * encrypted_key,
                                        sce_key_update_key_t  * key_update_key,
                                        sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES128_RFC3394KeyWrap(sce_aes_wrapped_key_t * master_key,
                                      uint32_t                target_key_type,
                                      sce_aes_wrapped_key_t * target_key,
                                      uint32_t              * rfc3394_wrapped_key);
fsp_err_t R_SCE_AES256_RFC3394KeyWrap(sce_aes_wrapped_key_t * master_key,
                                      uint32_t                target_key_type,
                                      sce_aes_wrapped_key_t * target_key,
                                      uint32_t              * rfc3394_wrapped_key);
fsp_err_t R_SCE_AES128_RFC3394KeyUnwrap(sce_aes_wrapped_key_t * master_key,
                                        uint32_t                target_key_type,
                                        uint32_t              * rfc3394_wrapped_key,
                                        sce_aes_wrapped_key_t * target_key);
fsp_err_t R_SCE_AES256_RFC3394KeyUnwrap(sce_aes_wrapped_key_t * master_key,
                                        uint32_t                target_key_type,
                                        uint32_t              * rfc3394_wrapped_key,
                                        sce_aes_wrapped_key_t * target_key);
fsp_err_t R_SCE_SHA256HMAC_EncryptedKeyWrap(uint8_t                    * initial_vector,
                                            uint8_t                    * encrypted_key,
                                            sce_key_update_key_t       * key_update_key,
                                            sce_hmac_sha_wrapped_key_t * wrapped_key);

fsp_err_t R_SCE_RSA1024_EncryptedPublicKeyWrap(uint8_t                          * initial_vector,
                                               uint8_t                          * encrypted_key,
                                               sce_key_update_key_t             * key_update_key,
                                               sce_rsa1024_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA1024_EncryptedPrivateKeyWrap(uint8_t                           * initial_vector,
                                                uint8_t                           * encrypted_key,
                                                sce_key_update_key_t              * key_update_key,
                                                sce_rsa1024_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA2048_EncryptedPublicKeyWrap(uint8_t                          * initial_vector,
                                               uint8_t                          * encrypted_key,
                                               sce_key_update_key_t             * key_update_key,
                                               sce_rsa2048_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA2048_EncryptedPrivateKeyWrap(uint8_t                           * initial_vector,
                                                uint8_t                           * encrypted_key,
                                                sce_key_update_key_t              * key_update_key,
                                                sce_rsa2048_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA3072_EncryptedPublicKeyWrap(uint8_t                          * initial_vector,
                                               uint8_t                          * encrypted_key,
                                               sce_key_update_key_t             * key_update_key,
                                               sce_rsa3072_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSA4096_EncryptedPublicKeyWrap(uint8_t                          * initial_vector,
                                               uint8_t                          * encrypted_key,
                                               sce_key_update_key_t             * key_update_key,
                                               sce_rsa4096_public_wrapped_key_t * wrapped_key);

fsp_err_t R_SCE_ECC_secp192r1_EncryptedPublicKeyWrap(uint8_t                      * initial_vector,
                                                     uint8_t                      * encrypted_key,
                                                     sce_key_update_key_t         * key_update_key,
                                                     sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp224r1_EncryptedPublicKeyWrap(uint8_t                      * initial_vector,
                                                     uint8_t                      * encrypted_key,
                                                     sce_key_update_key_t         * key_update_key,
                                                     sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap(uint8_t                      * initial_vector,
                                                     uint8_t                      * encrypted_key,
                                                     sce_key_update_key_t         * key_update_key,
                                                     sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp384r1_EncryptedPublicKeyWrap(uint8_t                      * initial_vector,
                                                     uint8_t                      * encrypted_key,
                                                     sce_key_update_key_t         * key_update_key,
                                                     sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp192r1_EncryptedPrivateKeyWrap(uint8_t                       * initial_vector,
                                                      uint8_t                       * encrypted_key,
                                                      sce_key_update_key_t          * key_update_key,
                                                      sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp224r1_EncryptedPrivateKeyWrap(uint8_t                       * initial_vector,
                                                      uint8_t                       * encrypted_key,
                                                      sce_key_update_key_t          * key_update_key,
                                                      sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap(uint8_t                       * initial_vector,
                                                      uint8_t                       * encrypted_key,
                                                      sce_key_update_key_t          * key_update_key,
                                                      sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECC_secp384r1_EncryptedPrivateKeyWrap(uint8_t                       * initial_vector,
                                                      uint8_t                       * encrypted_key,
                                                      sce_key_update_key_t          * key_update_key,
                                                      sce_ecc_private_wrapped_key_t * wrapped_key);

fsp_err_t R_SCE_AES128ECB_EncryptInit(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES128ECB_EncryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES128ECB_EncryptFinal(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);
fsp_err_t R_SCE_AES128ECB_DecryptInit(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES128ECB_DecryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES128ECB_DecryptFinal(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);
fsp_err_t R_SCE_AES256ECB_EncryptInit(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256ECB_EncryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES256ECB_EncryptFinal(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);
fsp_err_t R_SCE_AES256ECB_DecryptInit(sce_aes_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256ECB_DecryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES256ECB_DecryptFinal(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

fsp_err_t R_SCE_AES128CBC_EncryptInit(sce_aes_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector);
fsp_err_t R_SCE_AES128CBC_EncryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES128CBC_EncryptFinal(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);
fsp_err_t R_SCE_AES128CBC_DecryptInit(sce_aes_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector);
fsp_err_t R_SCE_AES128CBC_DecryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES128CBC_DecryptFinal(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);
fsp_err_t R_SCE_AES256CBC_EncryptInit(sce_aes_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector);
fsp_err_t R_SCE_AES256CBC_EncryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES256CBC_EncryptFinal(sce_aes_handle_t * handle, uint8_t * cipher, uint32_t * cipher_length);
fsp_err_t R_SCE_AES256CBC_DecryptInit(sce_aes_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector);
fsp_err_t R_SCE_AES256CBC_DecryptUpdate(sce_aes_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES256CBC_DecryptFinal(sce_aes_handle_t * handle, uint8_t * plain, uint32_t * plain_length);

fsp_err_t R_SCE_AES128GCM_EncryptInit(sce_gcm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector,
                                      uint32_t                initial_vector_length);
fsp_err_t R_SCE_AES128GCM_EncryptUpdate(sce_gcm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_data_length,
                                        uint8_t          * aad,
                                        uint32_t           aad_length);
fsp_err_t R_SCE_AES128GCM_EncryptFinal(sce_gcm_handle_t * handle,
                                       uint8_t          * cipher,
                                       uint32_t         * cipher_data_length,
                                       uint8_t          * atag);
fsp_err_t R_SCE_AES128GCM_DecryptInit(sce_gcm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector,
                                      uint32_t                initial_vector_length);
fsp_err_t R_SCE_AES128GCM_DecryptUpdate(sce_gcm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_data_length,
                                        uint8_t          * aad,
                                        uint32_t           aad_length);
fsp_err_t R_SCE_AES128GCM_DecryptFinal(sce_gcm_handle_t * handle,
                                       uint8_t          * plain,
                                       uint32_t         * plain_data_length,
                                       uint8_t          * atag,
                                       uint32_t           atag_length);

fsp_err_t R_SCE_AES256GCM_EncryptInit(sce_gcm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector,
                                      uint32_t                initial_vector_length);
fsp_err_t R_SCE_AES256GCM_EncryptUpdate(sce_gcm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_data_length,
                                        uint8_t          * aad,
                                        uint32_t           aad_length);
fsp_err_t R_SCE_AES256GCM_EncryptFinal(sce_gcm_handle_t * handle,
                                       uint8_t          * cipher,
                                       uint32_t         * cipher_data_length,
                                       uint8_t          * atag);
fsp_err_t R_SCE_AES256GCM_DecryptInit(sce_gcm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * initial_vector,
                                      uint32_t                initial_vector_length);
fsp_err_t R_SCE_AES256GCM_DecryptUpdate(sce_gcm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_data_length,
                                        uint8_t          * aad,
                                        uint32_t           aad_length);
fsp_err_t R_SCE_AES256GCM_DecryptFinal(sce_gcm_handle_t * handle,
                                       uint8_t          * plain,
                                       uint32_t         * plain_data_length,
                                       uint8_t          * atag,
                                       uint32_t           atag_length);

fsp_err_t R_SCE_AES128CCM_EncryptInit(sce_ccm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * nonce,
                                      uint32_t                nonce_length,
                                      uint8_t               * adata,
                                      uint8_t                 adata_length,
                                      uint32_t                payload_length,
                                      uint32_t                mac_length);
fsp_err_t R_SCE_AES128CCM_EncryptUpdate(sce_ccm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES128CCM_EncryptFinal(sce_ccm_handle_t * handle,
                                       uint8_t          * cipher,
                                       uint32_t         * cipher_length,
                                       uint8_t          * mac,
                                       uint32_t           mac_length);
fsp_err_t R_SCE_AES128CCM_DecryptInit(sce_ccm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * nonce,
                                      uint32_t                nonce_length,
                                      uint8_t               * adata,
                                      uint8_t                 adata_length,
                                      uint32_t                payload_length,
                                      uint32_t                mac_length);
fsp_err_t R_SCE_AES128CCM_DecryptUpdate(sce_ccm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES128CCM_DecryptFinal(sce_ccm_handle_t * handle,
                                       uint8_t          * plain,
                                       uint32_t         * plain_length,
                                       uint8_t          * mac,
                                       uint32_t           mac_length);

fsp_err_t R_SCE_AES256CCM_EncryptInit(sce_ccm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * nonce,
                                      uint32_t                nonce_length,
                                      uint8_t               * adata,
                                      uint8_t                 adata_length,
                                      uint32_t                payload_length,
                                      uint32_t                mac_length);
fsp_err_t R_SCE_AES256CCM_EncryptUpdate(sce_ccm_handle_t * handle,
                                        uint8_t          * plain,
                                        uint8_t          * cipher,
                                        uint32_t           plain_length);
fsp_err_t R_SCE_AES256CCM_EncryptFinal(sce_ccm_handle_t * handle,
                                       uint8_t          * cipher,
                                       uint32_t         * cipher_length,
                                       uint8_t          * mac,
                                       uint32_t           mac_length);
fsp_err_t R_SCE_AES256CCM_DecryptInit(sce_ccm_handle_t      * handle,
                                      sce_aes_wrapped_key_t * wrapped_key,
                                      uint8_t               * nonce,
                                      uint32_t                nonce_length,
                                      uint8_t               * adata,
                                      uint8_t                 adata_length,
                                      uint32_t                payload_length,
                                      uint32_t                mac_length);
fsp_err_t R_SCE_AES256CCM_DecryptUpdate(sce_ccm_handle_t * handle,
                                        uint8_t          * cipher,
                                        uint8_t          * plain,
                                        uint32_t           cipher_length);
fsp_err_t R_SCE_AES256CCM_DecryptFinal(sce_ccm_handle_t * handle,
                                       uint8_t          * plain,
                                       uint32_t         * plain_length,
                                       uint8_t          * mac,
                                       uint32_t           mac_length);

fsp_err_t R_SCE_AES128CMAC_GenerateInit(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES128CMAC_GenerateUpdate(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_AES128CMAC_GenerateFinal(sce_cmac_handle_t * handle, uint8_t * mac);
fsp_err_t R_SCE_AES128CMAC_VerifyInit(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES128CMAC_VerifyUpdate(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_AES128CMAC_VerifyFinal(sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length);
fsp_err_t R_SCE_AES256CMAC_GenerateInit(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256CMAC_GenerateUpdate(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_AES256CMAC_GenerateFinal(sce_cmac_handle_t * handle, uint8_t * mac);
fsp_err_t R_SCE_AES256CMAC_VerifyInit(sce_cmac_handle_t * handle, sce_aes_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_AES256CMAC_VerifyUpdate(sce_cmac_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_AES256CMAC_VerifyFinal(sce_cmac_handle_t * handle, uint8_t * mac, uint32_t mac_length);

fsp_err_t R_SCE_SHA256_Init(sce_sha_md5_handle_t * handle);
fsp_err_t R_SCE_SHA256_Update(sce_sha_md5_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_SHA256_Final(sce_sha_md5_handle_t * handle, uint8_t * digest, uint32_t * digest_length);

fsp_err_t R_SCE_SHA256HMAC_GenerateInit(sce_hmac_sha_handle_t * handle, sce_hmac_sha_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_SHA256HMAC_GenerateUpdate(sce_hmac_sha_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_SHA256HMAC_GenerateFinal(sce_hmac_sha_handle_t * handle, uint8_t * mac);
fsp_err_t R_SCE_SHA256HMAC_VerifyInit(sce_hmac_sha_handle_t * handle, sce_hmac_sha_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_SHA256HMAC_VerifyUpdate(sce_hmac_sha_handle_t * handle, uint8_t * message, uint32_t message_length);
fsp_err_t R_SCE_SHA256HMAC_VerifyFinal(sce_hmac_sha_handle_t * handle, uint8_t * mac, uint32_t mac_length);

fsp_err_t R_SCE_RSASSA_PKCS1024_SignatureGenerate(sce_rsa_byte_data_t               * message_hash,
                                                  sce_rsa_byte_data_t               * signature,
                                                  sce_rsa1024_private_wrapped_key_t * wrapped_key,
                                                  uint8_t                             hash_type);
fsp_err_t R_SCE_RSASSA_PKCS1024_SignatureVerify(sce_rsa_byte_data_t              * signature,
                                                sce_rsa_byte_data_t              * message_hash,
                                                sce_rsa1024_public_wrapped_key_t * wrapped_key,
                                                uint8_t                            hash_type);
fsp_err_t R_SCE_RSASSA_PKCS2048_SignatureGenerate(sce_rsa_byte_data_t               * message_hash,
                                                  sce_rsa_byte_data_t               * signature,
                                                  sce_rsa2048_private_wrapped_key_t * wrapped_key,
                                                  uint8_t                             hash_type);
fsp_err_t R_SCE_RSASSA_PKCS2048_SignatureVerify(sce_rsa_byte_data_t              * signature,
                                                sce_rsa_byte_data_t              * message_hash,
                                                sce_rsa2048_public_wrapped_key_t * wrapped_key,
                                                uint8_t                            hash_type);
fsp_err_t R_SCE_RSASSA_PKCS3072_SignatureVerify(sce_rsa_byte_data_t              * signature,
                                                sce_rsa_byte_data_t              * message_hash,
                                                sce_rsa3072_public_wrapped_key_t * wrapped_key,
                                                uint8_t                            hash_type);
fsp_err_t R_SCE_RSASSA_PKCS4096_SignatureVerify(sce_rsa_byte_data_t              * signature,
                                                sce_rsa_byte_data_t              * message_hash,
                                                sce_rsa4096_public_wrapped_key_t * wrapped_key,
                                                uint8_t                            hash_type);

fsp_err_t R_SCE_RSAES_PKCS1024_Encrypt(sce_rsa_byte_data_t              * plain,
                                       sce_rsa_byte_data_t              * cipher,
                                       sce_rsa1024_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSAES_PKCS1024_Decrypt(sce_rsa_byte_data_t               * cipher,
                                       sce_rsa_byte_data_t               * plain,
                                       sce_rsa1024_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSAES_PKCS2048_Encrypt(sce_rsa_byte_data_t              * plain,
                                       sce_rsa_byte_data_t              * cipher,
                                       sce_rsa2048_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSAES_PKCS2048_Decrypt(sce_rsa_byte_data_t               * cipher,
                                       sce_rsa_byte_data_t               * plain,
                                       sce_rsa2048_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSAES_PKCS3072_Encrypt(sce_rsa_byte_data_t              * plain,
                                       sce_rsa_byte_data_t              * cipher,
                                       sce_rsa3072_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_RSAES_PKCS4096_Encrypt(sce_rsa_byte_data_t              * plain,
                                       sce_rsa_byte_data_t              * cipher,
                                       sce_rsa4096_public_wrapped_key_t * wrapped_key);

fsp_err_t R_SCE_ECDSA_secp192r1_SignatureGenerate(sce_ecdsa_byte_data_t         * message_hash,
                                                  sce_ecdsa_byte_data_t         * signature,
                                                  sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp224r1_SignatureGenerate(sce_ecdsa_byte_data_t         * message_hash,
                                                  sce_ecdsa_byte_data_t         * signature,
                                                  sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp256r1_SignatureGenerate(sce_ecdsa_byte_data_t         * message_hash,
                                                  sce_ecdsa_byte_data_t         * signature,
                                                  sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp384r1_SignatureGenerate(sce_ecdsa_byte_data_t         * message_hash,
                                                  sce_ecdsa_byte_data_t         * signature,
                                                  sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp192r1_SignatureVerify(sce_ecdsa_byte_data_t        * signature,
                                                sce_ecdsa_byte_data_t        * message_hash,
                                                sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp224r1_SignatureVerify(sce_ecdsa_byte_data_t        * signature,
                                                sce_ecdsa_byte_data_t        * message_hash,
                                                sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp256r1_SignatureVerify(sce_ecdsa_byte_data_t        * signature,
                                                sce_ecdsa_byte_data_t        * message_hash,
                                                sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDSA_secp384r1_SignatureVerify(sce_ecdsa_byte_data_t        * signature,
                                                sce_ecdsa_byte_data_t        * message_hash,
                                                sce_ecc_public_wrapped_key_t * wrapped_key);

fsp_err_t R_SCE_ECDH_secp256r1_Init(sce_ecdh_handle_t * handle, uint32_t key_type, uint32_t use_key_id);
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeySign(sce_ecdh_handle_t             * handle,
                                             sce_ecc_public_wrapped_key_t  * ecc_public_wrapped_key,
                                             sce_ecc_private_wrapped_key_t * ecc_private_wrapped_key,
                                             uint8_t                       * public_key,
                                             sce_ecdsa_byte_data_t         * signature,
                                             sce_ecc_private_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeyVerify(sce_ecdh_handle_t            * handle,
                                               sce_ecc_public_wrapped_key_t * ecc_public_wrapped_key,
                                               uint8_t                      * public_key_data,
                                               sce_ecdsa_byte_data_t        * signature,
                                               sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDH_secp256r1_PublicKeyReadWithoutSignature(sce_ecdh_handle_t            * handle,
                                                             uint8_t                      * public_key_data,
                                                             sce_ecc_public_wrapped_key_t * wrapped_key);
fsp_err_t R_SCE_ECDH_secp256r1_SharedSecretCalculate(sce_ecdh_handle_t             * handle,
                                                     sce_ecc_public_wrapped_key_t  * ecc_public_wrapped_key,
                                                     sce_ecc_private_wrapped_key_t * ecc_private_wrapped_key,
                                                     sce_ecdh_wrapped_key_t        * shared_secret_wrapped_key);
fsp_err_t R_SCE_ECDH_secp256r1_KeyDerivation(sce_ecdh_handle_t          * handle,
                                             sce_ecdh_wrapped_key_t     * shared_secret_wrapped_key,
                                             uint32_t                     key_type,
                                             uint32_t                     kdf_type,
                                             uint8_t                    * other_info,
                                             uint32_t                     other_info_length,
                                             sce_hmac_sha_wrapped_key_t * salt_wrapped_key,
                                             sce_aes_wrapped_key_t      * wrapped_key);

fsp_err_t R_SCE_TLS_RootCertificateRSA2048PublicKeyInstall(uint8_t *encrypted_provisioning_key, uint8_t *initial_vector,
        uint8_t *encrypted_key, sce_tls_ca_certification_public_wrapped_key_t *wrapped_key);
fsp_err_t R_SCE_TLS_ECC_secp256r1_EphemeralWrappedKeyPairGenerate(sce_tls_p256_ecc_wrapped_key_t *tls_p256_ecc_wrapped_key,
        uint8_t *ephemeral_ecdh_public_key);
fsp_err_t R_SCE_TLS_RootCertificateVerify(uint32_t public_key_type, uint8_t *certificate,
        uint32_t certificate_length, uint32_t public_key_n_start_position, uint32_t public_key_n_end_position,
        uint32_t public_key_e_start_position, uint32_t public_key_e_end_position, uint8_t *signature,
        uint32_t *encrypted_root_public_key);
fsp_err_t R_SCE_TLS_CertificateVerify(uint32_t public_key_type, uint32_t *encrypted_input_public_key,
        uint8_t *certificate, uint32_t certificate_length, uint8_t *signature, uint32_t public_key_n_start_position,
        uint32_t public_key_n_end_position, uint32_t public_key_e_start_position, uint32_t public_key_e_end_position,
        uint32_t *encrypted_output_public_key);
fsp_err_t R_SCE_TLS_PreMasterSecretEncryptWithRSA2048(uint32_t *encrypted_public_key,
        uint32_t *sce_pre_master_secret, uint8_t *encrypted_pre_master_secret);
fsp_err_t R_SCE_TLS_PreMasterSecretGenerateForRSA2048(uint32_t *sce_pre_master_secret);
fsp_err_t R_SCE_TLS_MasterSecretGenerate (uint32_t select_cipher_suite, uint32_t *sce_pre_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint32_t *sce_master_secret);
fsp_err_t R_SCE_TLS_SessionKeyGenerate(uint32_t select_cipher_suite, uint32_t *sce_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint8_t* nonce_explicit,
        sce_hmac_sha_wrapped_key_t *client_mac_wrapped_key, sce_hmac_sha_wrapped_key_t *server_mac_wrapped_key,
        sce_aes_wrapped_key_t *client_crypto_wrapped_key, sce_aes_wrapped_key_t *server_crypto_wrapped_key,
        uint8_t *client_initial_vector, uint8_t *server_initial_vector);
fsp_err_t R_SCE_TLS_VerifyDataGenerate(uint32_t select_verify_data, uint32_t *sce_master_secret,
        uint8_t *hand_shake_hash, uint8_t *verify_data);
fsp_err_t R_SCE_TLS_ServerKeyExchangeVerify(uint32_t public_key_type, uint8_t *client_random,
        uint8_t *server_random, uint8_t *server_ephemeral_ecdh_public_key, uint8_t *server_key_exchange_signature,
        uint32_t *encrypted_public_key, uint32_t *encrypted_ephemeral_ecdh_public_key);
fsp_err_t R_SCE_TLS_PreMasterSecretGenerateForECC_secp256r1(uint32_t *encrypted_public_key,
    sce_tls_p256_ecc_wrapped_key_t *tls_p256_ecc_wrapped_key, uint32_t *sce_pre_master_secret);

uint32_t SCE_USER_SHA_384_FUNCTION(uint8_t * message, uint8_t * digest, uint32_t message_length);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SCE_H

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/
