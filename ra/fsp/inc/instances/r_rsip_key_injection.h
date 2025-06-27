/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RSIP_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_KEY_INJECTION_H
#define R_RSIP_KEY_INJECTION_H

#include "bsp_api.h"
#include "r_rsip_key_injection_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Key types */
typedef enum e_rsip_key_type
{
    RSIP_KEY_TYPE_INVALID                     = 0,           // Invalid key
    RSIP_KEY_TYPE_AES_128                     = 1,           // AES-128
    RSIP_KEY_TYPE_AES_192                     = 2,           // AES-192
    RSIP_KEY_TYPE_AES_256                     = 3,           // AES-256
    RSIP_KEY_TYPE_AES_128_XTS                 = 4,           // AES-128 XTS
    RSIP_KEY_TYPE_AES_256_XTS                 = 5,           // AES-256 XTS
    RSIP_KEY_TYPE_CHACHA20                    = 34,          // ChaCha20
    RSIP_KEY_TYPE_RSA_2048_PRIVATE            = 7,           // RSA-2048 private key
    RSIP_KEY_TYPE_RSA_3072_PRIVATE            = 9,           // RSA-3072 private key
    RSIP_KEY_TYPE_RSA_4096_PRIVATE            = 11,          // RSA-4096 private key
    RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE       = 13,          // secp256r1 private key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE       = 15,          // secp384r1 private key (also known as NIST P-384, prime384v1)
    RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE       = 17,          // secp521r1 private key (also known as NIST P-521, prime521v1)
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE = 19,          // brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE = 21,          // brainpool384r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE = 23,          // brainpool512r1 private key
    RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE       = 25,          // secp256k1 private key
    RSIP_KEY_TYPE_ECC_ED25519_PRIVATE         = 27,          // Ed25519 private key
    RSIP_KEY_TYPE_HMAC_SHA224                 = 28,          // hmac sha 224
    RSIP_KEY_TYPE_HMAC_SHA256                 = 29,          // hmac sha 256
    RSIP_KEY_TYPE_HMAC_SHA384                 = 30,          // hmac sha 384
    RSIP_KEY_TYPE_HMAC_SHA512                 = 31,          // hmac sha 512
    RSIP_KEY_TYPE_HMAC_SHA512_224             = 32,          // hmac sha 512/224
    RSIP_KEY_TYPE_HMAC_SHA512_256             = 33,          // hmac sha 512/256
    RSIP_KEY_TYPE_MAKE_ENUM_LONG              = 0xFFFFFFFFUL // Make this enum 32-bit data
} rsip_key_type_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rsip_key_injection_api_t g_rsip_key_injection_on_rsip;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_RSIP_AES128_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES192_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES256_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                       uint8_t const * const           p_wrapped_user_factory_programming_key,
                                       uint8_t const * const           p_initial_vector,
                                       uint8_t const * const           p_user_key,
                                       rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES128_XTS_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                           uint8_t const * const           p_wrapped_user_factory_programming_key,
                                           uint8_t const * const           p_initial_vector,
                                           uint8_t const * const           p_user_key,
                                           rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_AES256_XTS_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                           uint8_t const * const           p_wrapped_user_factory_programming_key,
                                           uint8_t const * const           p_initial_vector,
                                           uint8_t const * const           p_user_key,
                                           rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_ChaCha20_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                         uint8_t const * const               p_wrapped_user_factory_programming_key,
                                         uint8_t const * const               p_initial_vector,
                                         uint8_t const * const               p_user_key,
                                         rsip_chacha20_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA2048_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa2048_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA3072_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa3072_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_RSA4096_InitialPrivateKeyWrap(rsip_key_injection_type_t const            key_injection_type,
                                               uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                      p_initial_vector,
                                               uint8_t const * const                      p_user_key,
                                               rsip_rsa4096_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp384r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp521r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_secp256k1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                     uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                  p_initial_vector,
                                                     uint8_t const * const                  p_user_key,
                                                     rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                           uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                  p_initial_vector,
                                                           uint8_t const * const                  p_user_key,
                                                           rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP384r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                           uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                  p_initial_vector,
                                                           uint8_t const * const                  p_user_key,
                                                           rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_brainpoolP512r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                           uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                  p_initial_vector,
                                                           uint8_t const * const                  p_user_key,
                                                           rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_ECC_Ed25519_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                   uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                   uint8_t const * const                  p_initial_vector,
                                                   uint8_t const * const                  p_user_key,
                                                   rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA224_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                            uint8_t const * const               p_wrapped_user_factory_programming_key,
                                            uint8_t const * const               p_initial_vector,
                                            uint8_t const * const               p_user_key,
                                            rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA256_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                            uint8_t const * const               p_wrapped_user_factory_programming_key,
                                            uint8_t const * const               p_initial_vector,
                                            uint8_t const * const               p_user_key,
                                            rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA384_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                            uint8_t const * const               p_wrapped_user_factory_programming_key,
                                            uint8_t const * const               p_initial_vector,
                                            uint8_t const * const               p_user_key,
                                            rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA512_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                            uint8_t const * const               p_wrapped_user_factory_programming_key,
                                            uint8_t const * const               p_initial_vector,
                                            uint8_t const * const               p_user_key,
                                            rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA512_224_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                                uint8_t const * const               p_wrapped_user_factory_programming_key,
                                                uint8_t const * const               p_initial_vector,
                                                uint8_t const * const               p_user_key,
                                                rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_HMAC_SHA512_256_InitialKeyWrap(rsip_key_injection_type_t const     key_injection_type,
                                                uint8_t const * const               p_wrapped_user_factory_programming_key,
                                                uint8_t const * const               p_initial_vector,
                                                uint8_t const * const               p_user_key,
                                                rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_RSIP_KEY_INJECTION_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION)
 **********************************************************************************************************************/
