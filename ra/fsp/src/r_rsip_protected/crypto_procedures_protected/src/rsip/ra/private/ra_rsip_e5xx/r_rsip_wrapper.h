/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_WRAPPER_H
#define R_RSIP_WRAPPER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/* Primitive function names */
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_128                r_rsip_p07
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_128                r_rsip_wrapper_p6f_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_WRAP            r_rsip_wrapper_p8f_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_UNWRAP          r_rsip_wrapper_p90_aes128
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_128               r_rsip_p2c
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_128         r_rsip_wrapper_p47i_aes128ecb_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_128         r_rsip_wrapper_p47i_aes128ecb_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128         r_rsip_wrapper_p47i_aes128cbc_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128         r_rsip_wrapper_p47i_aes128cbc_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_128             r_rsip_wrapper_p47i_aes128ctr_crypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_128               r_rsip_p47u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_128                r_rsip_p47f
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128                r_rsip_wrapper_p29i_aes128gcm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_128          r_rsip_p29a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_128   r_rsip_p29t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_128              r_rsip_p29u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_128               r_rsip_p29f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128                r_rsip_wrapper_p32i_aes128gcm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_128          r_rsip_p32a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_128   r_rsip_p32t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_128              r_rsip_p32u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_128               r_rsip_p32f
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_128                r_rsip_wrapper_p95i_aes128ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_128              r_rsip_p95u
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_128               r_rsip_wrapper_p95f_aes128ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_128                r_rsip_wrapper_p98i_aes128ccm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_128              r_rsip_p98u
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_128               r_rsip_wrapper_p98f_aes128ccm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_128                   r_rsip_wrapper_p41i_aes128mac
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_128                 r_rsip_p41u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_128         r_rsip_wrapper_p41f_aes128mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_128           r_rsip_wrapper_p41f_aes128mac_verify
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_256                r_rsip_p08
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_256                r_rsip_wrapper_p6f_aes256
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_WRAP            r_rsip_wrapper_p8f_aes256
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_UNWRAP          r_rsip_wrapper_p90_aes256
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_256               r_rsip_p2e
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_256         r_rsip_wrapper_p50i_aes256ecb_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_256         r_rsip_wrapper_p50i_aes256ecb_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256         r_rsip_wrapper_p50i_aes256cbc_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256         r_rsip_wrapper_p50i_aes256cbc_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_256             r_rsip_wrapper_p50i_aes256ctr_crypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_256               r_rsip_p50u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_256                r_rsip_p50f
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256                r_rsip_wrapper_p34i_aes256gcm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_256          r_rsip_p34a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_256   r_rsip_p34t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_256              r_rsip_p34u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_256               r_rsip_p34f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256                r_rsip_wrapper_p36i_aes256gcm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_256          r_rsip_p36a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_256   r_rsip_p36t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_256              r_rsip_p36u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_256               r_rsip_p36f
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_256                r_rsip_wrapper_pa1i_aes256ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_256              r_rsip_pa1u
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_256               r_rsip_pa1f
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_256                r_rsip_wrapper_pa4i_aes256ccm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_256              r_rsip_pa4u
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_256               r_rsip_pa4f
#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_256                    r_rsip_wrapper_p44i_aes256mac
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_256                  r_rsip_p44u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_256          r_rsip_wrapper_p44f_aes256mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_256            r_rsip_wrapper_p44f_aes256mac_verify
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_128            r_rsip_p16
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_128            r_rsip_wrapper_p6f_aes128xts
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_128                r_rsip_pb3i
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_128              r_rsip_pb3u
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_128               r_rsip_pb3f
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_128                r_rsip_pb6i
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_128              r_rsip_pb6u
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_128               r_rsip_pb6f
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_XTS_AES_256            r_rsip_p17
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_256            r_rsip_wrapper_p6f_aes256xts
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_INIT_256                r_rsip_pb9i
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_UPDATE_256              r_rsip_pb9u
#define RSIP_PRV_FUNC_NAME_XTS_AES_ENC_FINAL_256               r_rsip_pb9f
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_INIT_256                r_rsip_pc2i
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_UPDATE_256              r_rsip_pc2u
#define RSIP_PRV_FUNC_NAME_XTS_AES_DEC_FINAL_256               r_rsip_pc2f
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256R1     r_rsip_wrapper_pf4_secp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC   r_rsip_wrapper_p6f_secp256r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE  r_rsip_wrapper_p6f_secp256r1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256R1                r_rsip_wrapper_pf0_secp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256R1              r_rsip_wrapper_pf1_secp256r1
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP384R1     r_rsip_wrapper_pf9_secp384r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC   r_rsip_wrapper_p6f_secp384r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE  r_rsip_wrapper_p6f_secp384r1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP384R1                r_rsip_wrapper_pf5_secp384r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP384R1              r_rsip_wrapper_pf6_secp384r1
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP521R1     r_rsip_wrapper_p13_secp521r1
#define RSIP_PRV_FUNC_NAME_KEY_WRAP_ECC_SECP521R1_PUBLIC       r_rsip_wrapper_p6f_secp521r1_pub
#define RSIP_PRV_FUNC_NAME_KEY_WRAP_ECC_SECP521R1_PRIVATE      r_rsip_wrapper_p6f_secp521r1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP521R1                r_rsip_wrapper_p11_secp521r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP521R1              r_rsip_wrapper_p12_secp521r1
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_2048          r_rsip_wrapper_p2b_rsa2048
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PUBLIC        r_rsip_wrapper_p6f_rsa2048_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_2048_PRIVATE       r_rsip_wrapper_p6f_rsa2048_priv
#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_2048                    r_rsip_p56
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_2048                    r_rsip_p57
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_3072          r_rsip_wrapper_p3a_rsa3072
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PUBLIC        r_rsip_wrapper_p6f_rsa3072_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_3072_PRIVATE       r_rsip_wrapper_p6f_rsa3072_priv
#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_3072                    r_rsip_p79
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_3072                   r_rsip_p7a
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_RSA_4096          r_rsip_wrapper_p3b_rsa4096
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PUBLIC        r_rsip_wrapper_p6f_rsa4096_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_RSA_4096_PRIVATE       r_rsip_wrapper_p6f_rsa4096_priv
#define RSIP_PRV_FUNC_NAME_RSA_ENCRYPT_4096                    r_rsip_p7b
#define RSIP_PRV_FUNC_NAME_RSA_DECRYPT_4096                    r_rsip_p7c
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA256            r_rsip_p0b
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA256            r_rsip_wrapper_p6f_hmacsha256
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA384            r_rsip_p3c
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA384            r_rsip_wrapper_p6f_hmacsha384
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA512            r_rsip_p3d
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA512            r_rsip_wrapper_p6f_hmacsha512
#define RSIP_PRV_FUNC_NAME_RANDOM_NUMBER_GENERATE              r_rsip_p20
#define RSIP_PRV_FUNC_NAME_GHASH_COMPUTE                       r_rsip_p21

/* Key update inst data word */
#define RSIP_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                        (0)
#define RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD                       (8)
#define RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD                       (12)
#define RSIP_OEM_KEY_SIZE_AES128_XTS_INST_DATA_WORD                   (12)
#define RSIP_OEM_KEY_SIZE_AES256_XTS_INST_DATA_WORD                   (20)

#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD     (20)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD    (12)
#define RSIP_OEM_KEY_SIZE_ECC_SECP384R1_PUBLIC_KEY_INST_DATA_WORD     (28)
#define RSIP_OEM_KEY_SIZE_ECC_SECP384R1_PRIVATE_KEY_INST_DATA_WORD    (16)
#define RSIP_OEM_KEY_SIZE_ECC_SECP521R1_PUBLIC_KEY_INST_DATA_WORD     (44)
#define RSIP_OEM_KEY_SIZE_ECC_SECP521R1_PRIVATE_KEY_INST_DATA_WORD    (24)

#define RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD              (12)
#define RSIP_OEM_KEY_SIZE_HMAC_SHA384_KEY_INST_DATA_WORD              (16)
#define RSIP_OEM_KEY_SIZE_HMAC_SHA512_KEY_INST_DATA_WORD              (20)

#define RSIP_OEM_KEY_SIZE_RSA2048_PUBLIC_KEY_INST_DATA_WORD           (72)
#define RSIP_OEM_KEY_SIZE_RSA2048_PRIVATE_KEY_INST_DATA_WORD          (132)
#define RSIP_OEM_KEY_SIZE_RSA3072_PUBLIC_KEY_INST_DATA_WORD           (104)
#define RSIP_OEM_KEY_SIZE_RSA3072_PRIVATE_KEY_INST_DATA_WORD          (196)
#define RSIP_OEM_KEY_SIZE_RSA4096_PUBLIC_KEY_INST_DATA_WORD           (136)
#define RSIP_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD          (260)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_ecc_curve_type
{
    RSIP_ECC_CURVE_TYPE_NIST
} rsip_ecc_type_t;

typedef enum e_rsip_ecc_cmd_type
{
    RSIP_ECC_CMD_P256
} rsip_ecc_cmd_type_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
rsip_ret_t r_rsip_wrapper_pf0_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf4_secp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf5_secp384r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf6_secp384r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf9_secp384r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p11_secp521r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_p12_secp521r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_p13_secp521r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p2b_rsa2048(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p3a_rsa3072(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p3b_rsa4096(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes128(const uint32_t InData_IV[],
                                     const uint32_t InData_InstData[],
                                     uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes256(const uint32_t InData_IV[],
                                     const uint32_t InData_InstData[],
                                     uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes128xts(const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes256xts(const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256r1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256r1_priv(const uint32_t InData_IV[],
                                             const uint32_t InData_InstData[],
                                             uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp384r1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp384r1_priv(const uint32_t InData_IV[],
                                             const uint32_t InData_InstData[],
                                             uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp521r1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp521r1_priv(const uint32_t InData_IV[],
                                             const uint32_t InData_InstData[],
                                             uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa2048_pub(const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa2048_priv(const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa3072_pub(const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa3072_priv(const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa4096_pub(const uint32_t InData_IV[],
                                          const uint32_t InData_InstData[],
                                          uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_rsa4096_priv(const uint32_t InData_IV[],
                                           const uint32_t InData_InstData[],
                                           uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_hmacsha256(const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_hmacsha384(const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_hmacsha512(const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p75i (const rsip_wrapped_key_t * p_wrapped_key,
                                const uint32_t InData_HashType[],
                                const uint32_t InData_MsgLen[]);
rsip_ret_t r_rsip_wrapper_p75r (const rsip_wrapped_key_t * p_wrapped_key,
                                const uint32_t InData_HashType[],
                                const uint32_t InData_State[]);
rsip_ret_t r_rsip_wrapper_p8f_aes128 (const uint32_t        InData_KeyIndex[],
                                      const rsip_key_type_t key_type,
                                      const uint32_t        InData_WrappedKeyIndex[],
                                      uint32_t              OutData_Text[]);
rsip_ret_t r_rsip_wrapper_p8f_aes256 (const uint32_t        InData_KeyIndex[],
                                      const rsip_key_type_t key_type,
                                      const uint32_t        InData_WrappedKeyIndex[],
                                      uint32_t              OutData_Text[]);
rsip_ret_t r_rsip_wrapper_p90_aes128 (const uint32_t        InData_KeyIndex[],
                                      const rsip_key_type_t key_type,
                                      const uint32_t        InData_Text[],
                                      uint32_t              OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p90_aes256 (const uint32_t        InData_KeyIndex[],
                                      const rsip_key_type_t key_type,
                                      const uint32_t        InData_Text[],
                                      uint32_t              OutData_KeyIndex[]);

/* AES-ECB/CBC/CTR */
rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128ctr_crypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ctr_crypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
rsip_ret_t r_rsip_wrapper_p29i_aes128gcm_encrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_aes128gcm_decrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_aes256gcm_encrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_aes256gcm_decrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);

/* AES-CCM */
rsip_ret_t r_rsip_wrapper_p95i_aes128ccm_encrypt(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_TextLen,
                                                 const uint32_t * InData_IV,
                                                 const uint32_t * InData_Header,
                                                 uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_p95f_aes128ccm_encrypt(const uint32_t * InData_Text,
                                                 const uint32_t * InData_TextLen,
                                                 uint32_t       * OutData_Text,
                                                 uint32_t       * OutData_MAC);
rsip_ret_t r_rsip_wrapper_p98i_aes128ccm_decrypt(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_TextLen,
                                                 const uint32_t * InData_MACLength,
                                                 const uint32_t * InData_IV,
                                                 const uint32_t * InData_Header,
                                                 uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_p98f_aes128ccm_decrypt(const uint32_t * InData_Text,
                                                 const uint32_t * InData_TextLen,
                                                 const uint32_t * InData_MAC,
                                                 const uint32_t * InData_MACLength,
                                                 uint32_t       * OutData_Text);

rsip_ret_t r_rsip_wrapper_pa1i_aes256ccm_encrypt(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_TextLen,
                                                 const uint32_t * InData_IV,
                                                 const uint32_t * InData_Header,
                                                 uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_pa4i_aes256ccm_decrypt(const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_TextLen,
                                                 const uint32_t * InData_MACLength,
                                                 const uint32_t * InData_IV,
                                                 const uint32_t * InData_Header,
                                                 uint32_t         Header_Len);

/* AES-MAC */
rsip_ret_t r_rsip_wrapper_p41i_aes128mac(const uint32_t * InData_KeyIndex);
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_generate(const uint32_t * InData_Text,
                                                  uint32_t       * OutData_DataT,
                                                  const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44i_aes256mac(const uint32_t * InData_KeyIndex);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_generate(const uint32_t * InData_Text,
                                                  uint32_t       * OutData_DataT,
                                                  const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);

#endif                                 /* R_RSIP_WRAPPER_H */
