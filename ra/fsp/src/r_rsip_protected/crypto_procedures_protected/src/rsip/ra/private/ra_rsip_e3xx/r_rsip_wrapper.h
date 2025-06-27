/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_WRAPPER_H
#define R_RSIP_WRAPPER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Primitive function names */
#define RSIP_PRV_FUNC_NAME_RANDOM_NUMBER_GENERATE                           r_rsip_p20

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_128                             r_rsip_p07
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_128                             r_rsip_wrapper_p6f_aes128

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_128                      r_rsip_wrapper_p47i_ecb_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_128                      r_rsip_wrapper_p47i_ecb_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128                      r_rsip_wrapper_p47i_cbc_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128                      r_rsip_wrapper_p47i_cbc_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128_WRAPPED_IV           r_rsip_wrapper_p47i_cbc_enc_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128_WRAPPED_IV           r_rsip_wrapper_p47i_cbc_dec_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_128                          r_rsip_wrapper_p47i_ctr
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_128                            r_rsip_p47u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_128                             r_rsip_p47f

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128                             r_rsip_wrapper_p29i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128_WRAPPED_IV                  r_rsip_wrapper_p29i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_128                       r_rsip_p29a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_128                r_rsip_p29t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_128                           r_rsip_p29u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_128                            r_rsip_p29f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128                             r_rsip_wrapper_p32i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128_WRAPPED_IV                  r_rsip_wrapper_p32i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_128                       r_rsip_p32a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_128                r_rsip_p32t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_128                           r_rsip_p32u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_128                            r_rsip_p32f

#define RSIP_PRV_FUNC_NAME_GHASH_COMPUTE                                    r_rsip_p21

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_128                                r_rsip_p41i
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_128                              r_rsip_p41u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_128                      r_rsip_wrapper_p41f_aes128mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_128                        r_rsip_wrapper_p41f_aes128mac_verify

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_256                             r_rsip_p08
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_256                             r_rsip_wrapper_p6f_aes256

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_256                      r_rsip_wrapper_p50i_ecb_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_256                      r_rsip_wrapper_p50i_ecb_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256                      r_rsip_wrapper_p50i_cbc_enc
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256                      r_rsip_wrapper_p50i_cbc_dec
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256_WRAPPED_IV           r_rsip_wrapper_p50i_cbc_enc_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256_WRAPPED_IV           r_rsip_wrapper_p50i_cbc_dec_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_256                          r_rsip_wrapper_p50i_ctr
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_256                            r_rsip_p50u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_256                             r_rsip_p50f

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256                             r_rsip_wrapper_p34i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256_WRAPPED_IV                  r_rsip_wrapper_p34i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_256                       r_rsip_p34a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_256                r_rsip_p34t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_256                           r_rsip_p34u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_256                            r_rsip_p34f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256                             r_rsip_wrapper_p36i_plain_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256_WRAPPED_IV                  r_rsip_wrapper_p36i_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_256                       r_rsip_p36a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_256                r_rsip_p36t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_256                           r_rsip_p36u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_256                            r_rsip_p36f

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_256                                r_rsip_p44i
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_256                              r_rsip_p44u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_256                      r_rsip_wrapper_p44f_aes256mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_256                        r_rsip_wrapper_p44f_aes256mac_verify

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256R1                  r_rsip_wrapper_pf4_secp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC                r_rsip_wrapper_p6f_secp256r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE               r_rsip_wrapper_p6f_secp256r1_priv

#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256R1                             r_rsip_wrapper_pf0_secp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256R1                           r_rsip_wrapper_pf1_secp256r1

#define RSIP_PRV_FUNC_NAME_ECDH_WRAPPED_SECP256R1                           r_rsip_wrapper_pe2_wrapped
#define RSIP_PRV_FUNC_NAME_ECDH_PLAIN_SECP256R1                             r_rsip_wrapper_pe2_plain

#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_INIT_SECP256R1                  r_rsip_wrapper_peei
#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_FINAL_SECP256R1                 r_rsip_peef
#define RSIP_PRV_FUNC_NAME_PKI_CERT_KEY_IMPORT_ECC_SECP256R1                r_rsip_wrapper_pe1_secp256r1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP384R1                  r_rsip_wrapper_pf9_secp384r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PUBLIC                r_rsip_wrapper_p6f_secp384r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP384R1_PRIVATE               r_rsip_wrapper_p6f_secp384r1_priv

#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP384R1                             r_rsip_wrapper_pf5_secp384r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP384R1                           r_rsip_wrapper_pf6_secp384r1

#define RSIP_PRV_FUNC_NAME_ECDH_WRAPPED_SECP384R1                           r_rsip_wrapper_p4e_wrapped
#define RSIP_PRV_FUNC_NAME_ECDH_PLAIN_SECP384R1                             r_rsip_wrapper_p4e_plain

#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_INIT_SECP384R1                  r_rsip_wrapper_p51i
#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_FINAL_SECP384R1                 r_rsip_p51f
#define RSIP_PRV_FUNC_NAME_PKI_CERT_KEY_IMPORT_ECC_SECP384R1                r_rsip_wrapper_pe1_secp384r1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256K1                  r_rsip_wrapper_pf4_secp256k1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256K1_PUBLIC                r_rsip_wrapper_p6f_secp256k1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256K1_PRIVATE               r_rsip_wrapper_p6f_secp256k1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256K1                             r_rsip_wrapper_pf0_secp256k1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256K1                           r_rsip_wrapper_pf1_secp256k1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_BRAINPOOLP256R1            r_rsip_wrapper_pf4_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC          r_rsip_wrapper_p6f_brainpoolp256r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE         r_rsip_wrapper_p6f_brainpoolp256r1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_BRAINPOOLP256R1                       r_rsip_wrapper_pf0_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_BRAINPOOLP256R1                     r_rsip_wrapper_pf1_brainpoolp256r1

#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_BRAINPOOLP384R1            r_rsip_wrapper_pf9_brainpoolp384r1
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP384R1_PUBLIC          r_rsip_wrapper_p6f_brainpoolp384r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP384R1_PRIVATE         r_rsip_wrapper_p6f_brainpoolp384r1_priv
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_BRAINPOOLP384R1                       r_rsip_wrapper_pf5_brainpoolp384r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_BRAINPOOLP384R1                     r_rsip_wrapper_pf6_brainpoolp384r1

#define RSIP_PRV_FUNC_NAME_KDF_SHA_ECDH_SECRET_MSG_WRAP_SHA256              r_rsip_wrapper_pe3_sha256
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA256_AES_128        r_rsip_wrapper_pe7_sha256_aes128
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA256_AES_256        r_rsip_wrapper_pe7_sha256_aes256
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_IV_WRAP_SHA256_AES               r_rsip_wrapper_pe7_sha256_iv_aes

#define RSIP_PRV_FUNC_NAME_KDF_SHA_ECDH_SECRET_MSG_WRAP_SHA384              r_rsip_wrapper_pe3_sha384
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA384_AES_128        r_rsip_wrapper_pe7_sha384_aes128
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA384_AES_256        r_rsip_wrapper_pe7_sha384_aes256
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_IV_WRAP_SHA384_AES               r_rsip_wrapper_pe7_sha384_iv_aes

#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_WRAP                         r_rsip_wrapper_p8f_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_UNWRAP                       r_rsip_wrapper_p90_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_WRAP                         r_rsip_wrapper_p8f_aes256
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_UNWRAP                       r_rsip_wrapper_p90_aes256

#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_128                            NULL
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_256                            NULL
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_128                            NULL
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_256                            NULL

/* Key update inst data word */
#define RSIP_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                              (0)
#define RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD                             (8)
#define RSIP_OEM_KEY_SIZE_AES192_INST_DATA_WORD                             (12)
#define RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD                             (12)

#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD           (20)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD          (12)
#define RSIP_OEM_KEY_SIZE_ECC_SECP384R1_PUBLIC_KEY_INST_DATA_WORD           (28)
#define RSIP_OEM_KEY_SIZE_ECC_SECP384R1_PRIVATE_KEY_INST_DATA_WORD          (16)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256K1_PUBLIC_KEY_INST_DATA_WORD           (20)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256K1_PRIVATE_KEY_INST_DATA_WORD          (12)
#define RSIP_OEM_KEY_SIZE_ECC_BRAINPOOLP256R1_PUBLIC_KEY_INST_DATA_WORD     (20)
#define RSIP_OEM_KEY_SIZE_ECC_BRAINPOOLP256R1_PRIVATE_KEY_INST_DATA_WORD    (12)
#define RSIP_OEM_KEY_SIZE_ECC_BRAINPOOLP384R1_PUBLIC_KEY_INST_DATA_WORD     (28)
#define RSIP_OEM_KEY_SIZE_ECC_BRAINPOOLP384R1_PRIVATE_KEY_INST_DATA_WORD    (16)

#define RSIP_PRV_PKI_HASH_TYPE_SHA1                                         (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA224                                       (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA256                                       (1U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA384                                       (4U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512                                       (5U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_224                                   (2U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_256                                   (3U)

typedef enum e_rsip_ecc_curve_type
{
    RSIP_ECC_CURVE_TYPE_NIST,
    RSIP_ECC_CURVE_TYPE_BRAINPOOL,
    RSIP_ECC_CURVE_TYPE_KOBLITZ
} rsip_ecc_type_t;

/**********************************************************************************************************************
 * Public Function Prototypes
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
rsip_ret_t r_rsip_wrapper_pf0_secp256k1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_secp256k1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf4_secp256k1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf0_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf4_brainpoolp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf5_brainpoolp384r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf6_brainpoolp384r1(const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_MsgDgst[],
                                              const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf9_brainpoolp384r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes128(const uint32_t InData_IV[],
                                     const uint32_t InData_InstData[],
                                     uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes256(const uint32_t InData_IV[],
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
rsip_ret_t r_rsip_wrapper_p6f_secp256k1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256k1_priv(const uint32_t InData_IV[],
                                             const uint32_t InData_InstData[],
                                             uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_pub(const uint32_t InData_IV[],
                                                  const uint32_t InData_InstData[],
                                                  uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_priv(const uint32_t InData_IV[],
                                                   const uint32_t InData_InstData[],
                                                   uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp384r1_pub(const uint32_t InData_IV[],
                                                  const uint32_t InData_InstData[],
                                                  uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp384r1_priv(const uint32_t InData_IV[],
                                                   const uint32_t InData_InstData[],
                                                   uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p8f_aes128(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_WrappedKeyIndex[],
                                     uint32_t       OutData_Text[],
                                     uint32_t       KEY_INDEX_SIZE,
                                     uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_wrapper_p8f_aes256(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_WrappedKeyIndex[],
                                     uint32_t       OutData_Text[],
                                     uint32_t       KEY_INDEX_SIZE,
                                     uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_wrapper_p90_aes128(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_Text[],
                                     uint32_t       OutData_KeyIndex[],
                                     uint32_t       WRAPPED_KEY_SIZE,
                                     uint32_t       KEY_INDEX_SIZE);
rsip_ret_t r_rsip_wrapper_p90_aes256(const uint32_t InData_KeyIndex[],
                                     const uint32_t InData_WrappedKeyType[],
                                     const uint32_t InData_Text[],
                                     uint32_t       OutData_KeyIndex[],
                                     uint32_t       WRAPPED_KEY_SIZE,
                                     uint32_t       KEY_INDEX_SIZE);

/* AES-ECB/CBC/CTR */
rsip_ret_t r_rsip_wrapper_p47i_ecb_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_ecb_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_cbc_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_cbc_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_cbc_enc_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_cbc_dec_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_ctr(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ecb_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ecb_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_enc(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_dec(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_enc_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_cbc_dec_wrapped_iv(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_ctr(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
rsip_ret_t r_rsip_wrapper_p29i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p29i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_plain_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_wrapped_iv(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);

/* AES-MAC */
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_generate(const uint32_t * InData_Text,
                                                  uint32_t       * OutData_DataT,
                                                  const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_generate(const uint32_t * InData_Text,
                                                  uint32_t       * OutData_DataT,
                                                  const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);

/* ECDH */
rsip_ret_t r_rsip_wrapper_pe2_wrapped(const uint32_t InData_PubKey[],
                                      const uint32_t InData_KeyIndex[],
                                      uint32_t       OutData_EncSecret[]);

rsip_ret_t r_rsip_wrapper_pe2_plain(const uint32_t InData_PubKey[],
                                    const uint32_t InData_KeyIndex[],
                                    uint32_t       OutData_EncSecret[]);

rsip_ret_t r_rsip_wrapper_p4e_wrapped(const uint32_t InData_PubKey[],
                                      const uint32_t InData_KeyIndex[],
                                      uint32_t       OutData_EncSecret[]);

rsip_ret_t r_rsip_wrapper_p4e_plain(const uint32_t InData_PubKey[],
                                    const uint32_t InData_KeyIndex[],
                                    uint32_t       OutData_EncSecret[]);

/* PKI */
rsip_ret_t r_rsip_wrapper_peei(const uint32_t InData_KeyIndex[],
                               const uint32_t InData_MsgDgst[],
                               const uint32_t InData_Signature[]);

rsip_ret_t r_rsip_wrapper_p51i(const uint32_t InData_KeyIndex[],
                               const uint32_t InData_MsgDgst[],
                               const uint32_t InData_Signature[]);

rsip_ret_t r_rsip_wrapper_pe1_secp256r1(const uint32_t InData_HashType[],
                                        const uint32_t InData_Certificate[],
                                        const uint32_t InData_CertificateLength[],
                                        const uint32_t InData_CertificatePubKey[],
                                        const uint32_t InData_EncCertificateInfo[],
                                        uint32_t       OutData_KeyIndex[]);

rsip_ret_t r_rsip_wrapper_pe1_secp384r1(const uint32_t InData_HashType[],
                                        const uint32_t InData_Certificate[],
                                        const uint32_t InData_CertificateLength[],
                                        const uint32_t InData_CertificatePubKey[],
                                        const uint32_t InData_EncCertificateInfo[],
                                        uint32_t       OutData_KeyIndex[]);

/* KDF */
rsip_ret_t r_rsip_wrapper_pe3_sha256(const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_wrapper_pe3_sha384(const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            const uint32_t InData_SeqNum[],
                                            uint32_t       OutData_EncIV[]);
rsip_ret_t r_rsip_wrapper_pe7_sha384_aes128(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha384_aes256(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha384_iv_aes(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            const uint32_t InData_SeqNum[],
                                            uint32_t       OutData_EncIV[]);

#endif                                 /* R_RSIP_WRAPPER_H */
