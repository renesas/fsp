/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
typedef struct st_rsip_func_subset_aes_mac
{
    rsip_ret_t (* p_init)(const uint32_t * InData_KeyIndex);
    void (* p_update)(const uint32_t * InData_Text, uint32_t MAX_CNT);
    rsip_ret_t (* p_generateFinal)(const uint32_t * InData_Text, uint32_t * OutData_DataT, const uint32_t all_msg_len);
    rsip_ret_t (* p_verifyFinal)(const uint32_t * InData_Text, const uint32_t * InData_DataT,
                                 const uint32_t * InData_DataTLen, const uint32_t all_msg_len);
} rsip_func_subset_aes_mac_t;

/* HMAC */
typedef rsip_ret_t (* rsip_func_hmac_single_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[],
                                               const uint32_t InData_Msg[], const uint32_t InData_MsgLen[],
                                               const uint32_t InData_MAC[],
                                               const uint32_t InData_length[], uint32_t MAX_CNT,
                                               uint32_t OutData_MAC[]);
typedef rsip_ret_t (* rsip_func_hmac_multi_t)(const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[],
                                              const uint32_t InData_Msg[], const uint32_t InData_MsgLen[],
                                              const uint32_t InData_MAC[],
                                              const uint32_t InData_length[], const uint32_t InData_State[],
                                              uint32_t MAX_CNT, uint32_t OutData_MAC[],
                                              uint32_t OutData_State[]);

/*
 * Private/Primitive function subsets
 */

typedef struct st_rsip_func
{
    rsip_func_key_generate_t p_key_generate_aes[RSIP_KEY_AES_NUM];
    rsip_func_key_generate_t p_key_generate_xts_aes[RSIP_KEY_AES_NUM];
    rsip_func_key_generate_t p_key_generate_chacha[RSIP_KEY_CHACHA_NUM];
    rsip_func_key_generate_t p_key_generate_hmac[RSIP_KEY_HMAC_NUM];

    rsip_func_key_pair_generate_t p_key_pair_generate_ecc[RSIP_KEY_ECC_NUM];
    rsip_func_key_pair_generate_t p_key_pair_generate_rsa[RSIP_KEY_RSA_NUM];

    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_aes[RSIP_KEY_AES_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_xts_aes[RSIP_KEY_AES_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_chacha[RSIP_KEY_CHACHA_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_ecc_pub[RSIP_KEY_ECC_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_ecc_priv[RSIP_KEY_ECC_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_rsa_pub[RSIP_KEY_RSA_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_rsa_priv[RSIP_KEY_RSA_NUM];
    rsip_func_encrypted_key_wrap_t p_encrypted_key_wrap_hmac[RSIP_KEY_HMAC_NUM];

    rsip_func_subset_aes_cipher_t p_aes_cipher[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_xts_t    p_aes_xts_enc[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_xts_t    p_aes_xts_dec[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_gcm_t    p_aes_gcm_enc[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_gcm_t    p_aes_gcm_dec[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_ccm_t    p_aes_ccm_enc[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_ccm_t    p_aes_ccm_dec[RSIP_KEY_AES_NUM];
    rsip_func_subset_aes_mac_t    p_aes_mac[RSIP_KEY_AES_NUM];

    rsip_func_ecdsa_sign_t   p_ecdsa_sign[RSIP_KEY_ECC_NUM];
    rsip_func_ecdsa_verify_t p_ecdsa_verify[RSIP_KEY_ECC_NUM];

    rsip_func_rsa_t p_rsa_public[RSIP_KEY_RSA_NUM];
    rsip_func_rsa_t p_rsa_private[RSIP_KEY_RSA_NUM];

    rsip_func_hmac_single_t p_hmac_single[RSIP_KEY_HMAC_NUM];
    rsip_func_hmac_multi_t  p_hmac_multi[RSIP_KEY_HMAC_NUM];

    rsip_func_rng_t   p_rng;
    rsip_func_ghash_t p_ghash_compute;
} rsip_func_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern const bool g_sha_enabled[RSIP_HASH_TYPE_NUM];
extern const bool g_hmac_enabled[RSIP_KEY_HMAC_NUM];

extern const rsip_func_t g_func;

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
 * Stores input Key Update Key (KUK).
 *
 * @param[in] p_key_update_key_value KUK value.
 **********************************************************************************************************************/
void r_rsip_kuk_store(const uint8_t * p_key_update_key_value);

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

rsip_ret_t r_rsip_sha1sha2_init_update(rsip_hash_type_t hash_type,
                                       const uint8_t  * p_message,
                                       uint64_t         message_length,
                                       uint32_t       * internal_state);
rsip_ret_t r_rsip_sha1sha2_resume_update(rsip_hash_type_t hash_type,
                                         const uint8_t  * p_message,
                                         uint64_t         message_length,
                                         uint32_t       * internal_state);
rsip_ret_t r_rsip_sha1sha2_update(rsip_hash_type_t hash_type,
                                  const uint8_t  * p_message,
                                  uint64_t         message_length,
                                  uint32_t       * internal_state);
rsip_ret_t r_rsip_sha1sha2_suspend(uint32_t * internal_state);
rsip_ret_t r_rsip_sha1sha2_init_final(rsip_hash_type_t hash_type,
                                      const uint8_t  * p_message,
                                      uint64_t         message_length,
                                      uint8_t        * p_digest);
rsip_ret_t r_rsip_sha1sha2_resume_final(rsip_hash_type_t hash_type,
                                        const uint8_t  * p_message,
                                        uint64_t         message_length,
                                        uint64_t         total_message_length,
                                        uint8_t        * p_digest,
                                        uint32_t       * internal_state);
rsip_ret_t r_rsip_sha1sha2_final(rsip_hash_type_t hash_type,
                                 const uint8_t  * p_message,
                                 uint64_t         message_length,
                                 uint64_t         total_message_length,
                                 uint8_t        * p_digest,
                                 uint32_t       * internal_state);

rsip_ret_t r_rsip_hmac_init_update(const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_resume_update(const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_update(const rsip_wrapped_key_t * p_wrapped_key,
                              const uint8_t            * p_message,
                              uint64_t                   message_length,
                              uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_suspend(uint32_t * internal_state);
rsip_ret_t r_rsip_hmac_init_final(const rsip_wrapped_key_t * p_wrapped_key,
                                  const uint8_t            * p_message,
                                  uint64_t                   message_length,
                                  uint8_t                  * p_mac);
rsip_ret_t r_rsip_hmac_resume_final(const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint64_t                   total_message_length,
                                    uint8_t                  * p_mac,
                                    uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_final(const rsip_wrapped_key_t * p_wrapped_key,
                             const uint8_t            * p_message,
                             uint64_t                   message_length,
                             uint64_t                   total_message_length,
                             uint8_t                  * p_mac,
                             uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_init_verify(const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   const uint8_t            * p_mac,
                                   uint32_t                   mac_length);
rsip_ret_t r_rsip_hmac_resume_verify(const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint64_t                   total_message_length,
                                     const uint8_t            * p_mac,
                                     uint32_t                   mac_length,
                                     uint32_t                 * internal_state);
rsip_ret_t r_rsip_hmac_verify(const rsip_wrapped_key_t * p_wrapped_key,
                              const uint8_t            * p_message,
                              uint64_t                   message_length,
                              uint64_t                   total_message_length,
                              const uint8_t            * p_mac,
                              uint32_t                   mac_length,
                              uint32_t                 * internal_state);

/*******************************************************************************************************************//**
 * Converts byte data to word (4-byte) and rounds up it.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_word_convert (const uint32_t bytes)
{
    return (bytes + 3) >> 2;
}

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns upper 3 digits.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_bit_convert_upper (const uint64_t bytes)
{
    return (uint32_t) (bytes >> 29);
}

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns lower 32 digits.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t r_rsip_byte_to_bit_convert_lower (const uint64_t bytes)
{
    return (uint32_t) (bytes << 3);
}

#endif                                 /* R_RSIP_PRIVATE_H */
