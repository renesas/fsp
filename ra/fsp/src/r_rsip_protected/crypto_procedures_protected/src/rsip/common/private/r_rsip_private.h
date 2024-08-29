/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_PRIVATE_H
#define R_RSIP_PRIVATE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip.h"
#include "r_rsip_err.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*
 * Private/Primitive functions
 */

/* Random number generation */
typedef rsip_ret_t (* rsip_func_rng_t)(uint32_t OutData_Text[]);

/* Key generation */
typedef rsip_ret_t (* rsip_func_key_generate_t)(uint32_t OutData_KeyIndex[]);

/* Key pair generation */
typedef rsip_ret_t (* rsip_func_key_pair_generate_t)(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);

/* Encrypted key wrap */
typedef rsip_ret_t (* rsip_func_encrypted_key_wrap_t)(const uint32_t InData_IV[], const uint32_t InData_InstData[],
                                                      uint32_t OutData_KeyIndex[]);

/* RFC3394 Key Wrap */
typedef rsip_ret_t (* rsip_func_rfc3394_key_wrap_t)(const uint32_t InData_KeyIndex[], const rsip_key_type_t key_type,
                                                    const uint32_t InData_WrappedKeyIndex[], uint32_t OutData_Text[]);

/* RFC3394 Key Unwrap */
typedef rsip_ret_t (* rsip_func_rfc3394_key_unwrap_t)(const uint32_t InData_KeyIndex[], const rsip_key_type_t key_type,
                                                      const uint32_t InData_Text[], uint32_t OutData_KeyIndex[]);

/* AES-ECB/CBC/CTR */
typedef rsip_ret_t (* rsip_func_aes_cipher_init_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
typedef rsip_ret_t (* rsip_func_ghash_t)(const uint32_t InData_HV[], const uint32_t InData_IV[],
                                         const uint32_t InData_Text[], uint32_t OutData_DataT[], uint32_t MAX_CNT);

/* ECC */
typedef rsip_ret_t (* rsip_func_ecdsa_sign_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[],
                                              uint32_t OutData_Signature[]);
typedef rsip_ret_t (* rsip_func_ecdsa_verify_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_Signature[]);

/* RSA */
typedef rsip_ret_t (* rsip_func_rsa_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[],
                                       uint32_t OutData_Text[]);
/* OTF */
typedef rsip_ret_t (* rsip_func_otf_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);

/*
 * Private/Primitive function subsets
 */

/* AES-ECB/CBC/CTR */
typedef struct st_rsip_func_subset_aes_cipher
{
    rsip_func_aes_cipher_init_t p_init_ecb_enc;
    rsip_func_aes_cipher_init_t p_init_ecb_dec;
    rsip_func_aes_cipher_init_t p_init_cbc_enc;
    rsip_func_aes_cipher_init_t p_init_cbc_dec;
    rsip_func_aes_cipher_init_t p_init_ctr;
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)();
} rsip_func_subset_aes_cipher_t;

/* AES-XTS */
typedef struct st_rsip_func_subset_aes_xts
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_final)(const uint32_t * InData_TextBitLen, const uint32_t * InData_Text, uint32_t * OutData_Text);
} rsip_func_subset_aes_xts_t;

/* AES-GCM */
typedef struct st_rsip_func_subset_aes_gcm
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
    void (* p_updateAad)(const uint32_t * InData_DataA, uint32_t MAX_CNT);
    void (* p_updateTransition)();
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_encryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataALen,
                                  const uint32_t * InData_TextLen, uint32_t * OutData_Text, uint32_t * OutData_DataT);
    rsip_ret_t (* p_decryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataT,
                                  const uint32_t * InData_DataALen, const uint32_t * InData_TextLen,
                                  const uint32_t * InData_DataTLen,
                                  uint32_t * OutData_Text);
} rsip_func_subset_aes_gcm_t;

/* AES-CCM */
typedef struct st_rsip_func_subset_aes_ccm
{
    rsip_ret_t (* p_encryptInit)(const uint32_t * InData_KeyIndex, const uint32_t * InData_TextLen,
                                 const uint32_t * InData_IV, const uint32_t * InData_Header, uint32_t Header_Len);
    rsip_ret_t (* p_decryptInit)(const uint32_t * InData_KeyIndex, const uint32_t * InData_TextLen,
                                 const uint32_t * InData_MACLength, const uint32_t * InData_IV,
                                 const uint32_t * InData_Header, uint32_t Header_Len);
    void (* p_update)(const uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_encryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                  uint32_t * OutData_Text, uint32_t * OutData_MAC);
    rsip_ret_t (* p_decryptFinal)(const uint32_t * InData_Text, const uint32_t * InData_TextLen,
                                  const uint32_t * InData_MAC, const uint32_t * InData_MACLength,
                                  uint32_t * OutData_Text);
} rsip_func_subset_aes_ccm_t;

/* AES-CMAC */
typedef struct st_rsip_func_subset_aes_cmac
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex);
    void (* p_update)(const uint32_t * InData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_generateFinal)(const uint32_t * InData_Text, uint32_t * OutData_DataT, const uint32_t all_msg_len);
    rsip_ret_t (* p_verifyFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataT,
                                 const uint32_t * InData_DataTLen, const uint32_t all_msg_len);
} rsip_func_subset_aes_cmac_t;


/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern const bool g_sha_enabled[RSIP_HASH_TYPE_NUM];
extern const bool g_hmac_enabled[RSIP_KEY_HMAC_NUM];

extern const rsip_func_key_generate_t gp_func_key_generate_aes[RSIP_KEY_AES_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_xts_aes[RSIP_KEY_AES_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_chacha[RSIP_KEY_CHACHA_NUM];
extern const rsip_func_key_generate_t gp_func_key_generate_hmac[RSIP_KEY_HMAC_NUM];

extern const rsip_func_key_pair_generate_t gp_func_key_pair_generate_ecc[RSIP_KEY_ECC_NUM];
extern const rsip_func_key_pair_generate_t gp_func_key_pair_generate_rsa[RSIP_KEY_RSA_NUM];

extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_aes[RSIP_KEY_AES_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_xts_aes[RSIP_KEY_AES_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_chacha[RSIP_KEY_CHACHA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_pub[RSIP_KEY_ECC_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_ecc_priv[RSIP_KEY_ECC_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_pub[RSIP_KEY_RSA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_rsa_priv[RSIP_KEY_RSA_NUM];
extern const rsip_func_encrypted_key_wrap_t gp_func_encrypted_key_wrap_hmac[RSIP_KEY_HMAC_NUM];

extern const rsip_func_subset_aes_cipher_t gp_func_aes_cipher[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_xts_t    gp_func_aes_xts_enc[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_xts_t    gp_func_aes_xts_dec[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_gcm_t    gp_func_aes_gcm_enc[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_gcm_t    gp_func_aes_gcm_dec[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_ccm_t    gp_func_aes_ccm_enc[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_ccm_t    gp_func_aes_ccm_dec[RSIP_KEY_AES_NUM];
extern const rsip_func_subset_aes_cmac_t   gp_func_aes_cmac[RSIP_KEY_AES_NUM];

extern const rsip_func_ecdsa_sign_t   gp_func_ecdsa_sign[RSIP_KEY_ECC_NUM];
extern const rsip_func_ecdsa_verify_t gp_func_ecdsa_verify[RSIP_KEY_ECC_NUM];

extern const rsip_func_rsa_t gp_func_rsa_public[RSIP_KEY_RSA_NUM];
extern const rsip_func_rsa_t gp_func_rsa_private[RSIP_KEY_RSA_NUM];

extern const rsip_func_rfc3394_key_wrap_t gp_func_rfc3394_key_wrap[RSIP_KEY_AES_NUM];
extern const rsip_func_rfc3394_key_unwrap_t gp_func_rfc3394_key_unwrap[RSIP_KEY_AES_NUM];

extern const rsip_func_otf_t gp_func_otf[RSIP_OTF_CHANNEL_NUM][RSIP_KEY_AES_NUM];

extern const rsip_func_rng_t   gp_func_rng;
extern const rsip_func_ghash_t gp_func_ghash_compute;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the RSIP engine.
 *
 * @return The return value of the internally called primitive functions.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_open(void);

/*******************************************************************************************************************//**
 * Finalizes the RSIP engine.
 *
 * @return The return value of the internally called primitive functions.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_close(void);

/*******************************************************************************************************************//**
 * Sets Key Update Key (KUK).
 *
 * @param[in] p_key_update_key_value KUK value.
 **********************************************************************************************************************/
void r_rsip_kuk_set(const uint8_t * p_key_update_key_value);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     hash_type      Generating hash type.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_init_update(rsip_hash_type_t hash_type,
                                       const uint8_t  * p_message,
                                       uint64_t         message_length,
                                       uint32_t       * internal_state);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     hash_type      Generating hash type.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_resume_update(rsip_hash_type_t hash_type,
                                         const uint8_t  * p_message,
                                         uint64_t         message_length,
                                         uint32_t       * internal_state);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     hash_type      Generating hash type.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_update(rsip_hash_type_t hash_type,
                                  const uint8_t  * p_message,
                                  uint64_t         message_length,
                                  uint32_t       * internal_state);

/*******************************************************************************************************************//**
 * Suspend hash operation.
 *
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_suspend(uint32_t * internal_state);

/*******************************************************************************************************************//**
 * 1. Initialize hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note This function allows empty message.
 *
 * @param[in]     hash_type      Generating hash type.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_init_final(rsip_hash_type_t hash_type,
                                      const uint8_t  * p_message,
                                      uint64_t         message_length,
                                      uint8_t        * p_digest);

/*******************************************************************************************************************//**
 * 1. Resume hash operation.
 * 2. Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     hash_type            Generating hash type.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[out]    p_digest             Pointer to destination of message digest. The length depends on hash type.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_resume_final(rsip_hash_type_t hash_type,
                                        const uint8_t  * p_message,
                                        uint64_t         message_length,
                                        uint64_t         total_message_length,
                                        uint8_t        * p_digest,
                                        uint32_t       * internal_state);

/*******************************************************************************************************************//**
 * Input the remaining message and finalize hash operation.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     hash_type            Generating hash type.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[out]    p_digest             Pointer to destination of message digest. The length depends on hash type.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_final(rsip_hash_type_t hash_type,
                                 const uint8_t  * p_message,
                                 uint64_t         message_length,
                                 uint64_t         total_message_length,
                                 uint8_t        * p_digest,
                                 uint32_t       * internal_state);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_update(const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_update(const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * Input block message in block length.
 *
 * @note Message length must be at least 1 block.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_update(const rsip_wrapped_key_t * p_wrapped_key,
                              const uint8_t            * p_message,
                              uint64_t                   message_length,
                              uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * Suspend HMAC operation.
 *
 * @param[in,out] internal_state Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_suspend(uint32_t * internal_state);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note This function allows empty message.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_final(const rsip_wrapped_key_t * p_wrapped_key,
                                  const uint8_t            * p_message,
                                  uint64_t                   message_length,
                                  uint8_t                  * p_mac);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     p_wrapped_key        Pointer to wrapped key of HMAC key.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[out]    p_mac                Pointer to destination of message digest. The length depends on MAC type.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_final(const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint64_t                   total_message_length,
                                    uint8_t                  * p_mac,
                                    uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * 1. Input the remaining message and finalize HMAC operation.
 * 2. Output MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     p_wrapped_key        Pointer to wrapped key of HMAC key.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[out]    p_mac                Pointer to destination of message digest. The length depends on MAC type.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_final(const rsip_wrapped_key_t * p_wrapped_key,
                             const uint8_t            * p_message,
                             uint64_t                   message_length,
                             uint64_t                   total_message_length,
                             uint8_t                  * p_mac,
                             uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * 1. Initialize HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Verify MAC.
 *
 * @note This function allows empty message.
 *
 * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message.
 * @param[in]     p_mac          Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length     Byte length of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_init_verify(const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   const uint8_t            * p_mac,
                                   uint32_t                   mac_length);

/*******************************************************************************************************************//**
 * 1. Resume HMAC operation.
 * 2. Input the remaining message and finalize HMAC operation.
 * 3. Verify MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     p_wrapped_key        Pointer to wrapped key of HMAC key.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[in]     p_mac                Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length           Byte length of MAC.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_resume_verify(const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint64_t                   total_message_length,
                                     const uint8_t            * p_mac,
                                     uint32_t                   mac_length,
                                     uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * 1. Input the remaining message and finalize HMAC operation.
 * 2. Verify MAC.
 *
 * @note Message length must be at least 1 byte.
 *
 * @param[in]     p_wrapped_key        Pointer to wrapped key of HMAC key.
 * @param[in]     p_message            Pointer to message. The length is message_length.
 * @param[in]     message_length       Byte length of message.
 * @param[in]     total_message_length Byte length of total message length.
 * @param[in]     p_mac                Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length           Byte length of MAC.
 * @param[in,out] internal_state       Buffer of internal state.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_verify(const rsip_wrapped_key_t * p_wrapped_key,
                              const uint8_t            * p_message,
                              uint64_t                   message_length,
                              uint64_t                   total_message_length,
                              const uint8_t            * p_mac,
                              uint32_t                   mac_length,
                              uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * Computes SHA-1 or SHA-2 message digest in single-part operation.
 *
 * @param[in]  in_data_msg         Big-endian message.
 * @param[out] out_data_msg_digest Big-endian message digest.
 * @param[in]  hash_type           Generating hash type.
 * @param[in]  message_length      Byte size of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_sha1sha2_compute_single(const uint32_t   in_data_msg[],
                                          uint32_t         out_data_msg_digest[],
                                          rsip_hash_type_t hash_type,
                                          uint32_t         message_length);
#if 0
/*******************************************************************************************************************//**
 * Computes HMAC message digest in single-part operation.
 *
 * @param[in]  InData_Msg     Big-endian message.
 * @param[out] OutData_MAC    Big-endian MAC.
 * @param[in]  p_func         Private/Primitive function.
 * @param[in]  p_wrapped_key  Wrapped HMAC key.
 * @param[in]  message_length Byte size of message.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_compute_single(const uint32_t                InData_Msg[],
                                      uint32_t                      OutData_MAC[],
                                      const rsip_func_hmac_single_t p_func,
                                      const rsip_wrapped_key_t    * p_wrapped_key,
                                      uint32_t                      message_length);

/*******************************************************************************************************************//**
 * Verifies HMAC message digest in single-part operation.
 *
 * @param[in] InData_Msg     Big-endian message.
 * @param[in] p_mac          Big-endian MAC.
 * @param[in] p_func         Private/Primitive function.
 * @param[in] p_wrapped_key  Wrapped HMAC key.
 * @param[in] message_length Byte size of message.
 * @param[in] mac_length     Byte size of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_verify_single(const uint32_t                InData_Msg[],
                                     const uint8_t               * p_mac,
                                     const rsip_func_hmac_single_t p_func,
                                     const rsip_wrapped_key_t    * p_wrapped_key,
                                     uint32_t                      message_length,
                                     uint32_t                      mac_length);
#endif
/*******************************************************************************************************************//**
 * Computes or Verifies HMAC in multi-part operation.
 *
 * @param[in,out] p_ctrl         Pointer to control block.
 * @param[in]     p_message      Big-endian message.
 * @param[in]     message_length Byte size of message.
 * @param[in,out] p_mac          Big-endian MAC. For computation finalization, it is output data;
 *                               for verification finalization, it is input data.
 * @param[in]     mac_length     Byte size of MAC. This value is input only verification finalization.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
rsip_ret_t r_rsip_hmac_calc_multi(rsip_ctrl_t * const p_ctrl,
                                  const uint8_t     * p_message,
                                  uint32_t            message_length,
                                  uint8_t           * p_mac,
                                  uint32_t            mac_length);


/*******************************************************************************************************************//**
 * Converts byte data to word (4-byte) and rounds up it.
 *
 * @param[in] bytes Byte length
 *
 * @return Word length

 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_word_convert (const uint32_t bytes)
{
    return (bytes + 3) >> 2;
}

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns upper 3 digits.
 *
 * @param[in] bytes Byte length
 *
 * @return Bit length (upper 3 digits)
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_bit_convert_upper (const uint64_t bytes)
{
    return (uint32_t) (bytes >> 29);
}

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns lower 32 digits.
 *
 * @param[in] bytes Byte length
 *
 * @return Bit length (lower 32 digits)
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_bit_convert_lower (const uint64_t bytes)
{
    return (uint32_t) (bytes << 3);
}

#endif                                 /* R_RSIP_PRIVATE_H */
