/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_H
#define R_RSIP_H

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_rsip_api.h"
#include "r_rsip_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Version Number of Module. */
#define FSP_R_RSIP_PROTECTED_VERSION_MAJOR    (2U)
#define FSP_R_RSIP_PROTECTED_VERSION_MINOR    (0U)
#define FSP_R_RSIP_PROTECTED_VERSION_PATCH    (0U)

/** Returns the plain key size formatted for RSIP driver of the key type. */
#define RSIP_BYTE_SIZE_PLAIN_KEY(key_type)          (RSIP_PRV_KEY_TYPE_VAL_PLAIN_WORDS(key_type) << 2)

/** Returns the encrypted key size of the key type. */
#define RSIP_BYTE_SIZE_ENCRYPTED_KEY(key_type)      (RSIP_PRV_BYTE_SIZE_ENCRYPTED_DATA(RSIP_PRV_KEY_TYPE_VAL_PLAIN_WORDS( \
                                                                                           key_type)))

/** Returns the wrapped key size of the key type. */
#define RSIP_BYTE_SIZE_WRAPPED_KEY(key_type)        (RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(RSIP_PRV_KEY_TYPE_VAL_PLAIN_WORDS( \
                                                                                         key_type)))

/* data size */
#define RSIP_PRV_BYTE_SIZE_ENCRYPTED_DATA(words)    (((words) + RSIP_CFG_WORD_SIZE_ENCRYPTED_KEY_OVERHEAD) << 2)
#define RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(words)      (((words) + RSIP_CFG_WORD_SIZE_WRAPPED_KEY_OVERHEAD) << 2)

/* Wrapped ECDH secret size */
#define RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_256      RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(8)
#define RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_384      RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(12)
#define RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_521      RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(20)

/* Buffer size for SHA and HMAC */
#define RSIP_PRV_WORD_SIZE_SHA_INTERNAL_STATE_BUF       (20U)
#define RSIP_PRV_WORD_SIZE_HMAC_INTERNAL_STATE_BUF      (20U)

/* Buffer size for SHA */
#if RSIP_CFG_SHA512_ENABLE || RSIP_CFG_SHA512_224_ENABLE || RSIP_CFG_SHA512_256_ENABLE || RSIP_CFG_SHA384_ENABLE
 #define RSIP_PRV_BYTE_SIZE_SHA_BLOCK_BUF               (128U * RSIP_CFG_SHA_BUF_BLOCKS)
#else
 #define RSIP_PRV_BYTE_SIZE_SHA_BLOCK_BUF               (64U * RSIP_CFG_SHA_BUF_BLOCKS)
#endif

/* Buffer size for KDF SHA */
#if RSIP_CFG_KDF_SHA384_ENABLE
 #define RSIP_PRV_BYTE_SIZE_KDF_SHA_BLOCK_BUF           (128U)
#else
 #define RSIP_PRV_BYTE_SIZE_KDF_SHA_BLOCK_BUF           (64U)
#endif

/* Buffer sizes for HMAC */
#if RSIP_CFG_HMAC_SHA512_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA512)
 #define RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF              (128U * RSIP_CFG_SHA_BUF_BLOCKS)
#elif RSIP_CFG_HMAC_SHA384_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA384)
 #define RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF              (128U * RSIP_CFG_SHA_BUF_BLOCKS)
#elif RSIP_CFG_HMAC_SHA256_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA256)
 #define RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF              (64U * RSIP_CFG_HMAC_BUF_BLOCKS)
#elif RSIP_CFG_HMAC_SHA224_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA224)
 #define RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF              (64U * RSIP_CFG_HMAC_BUF_BLOCKS)
#else
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA1)
 #define RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF              (64U * RSIP_CFG_HMAC_BUF_BLOCKS)
#endif

/* Buffer size for ECDH */
#if RSIP_CFG_ECC_SECP521R1_ENABLE
 #define  RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_BUF    RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_521
#elif RSIP_CFG_ECC_SECP384R1_ENABLE
 #define  RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_BUF    RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_384
#else
 #define  RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_BUF    RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_256
#endif

/* Buffer size for KDF */
#if RSIP_CFG_ECC_SECP521R1_ENABLE
 #define RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF         RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_521
#elif RSIP_CFG_KDF_HMAC_SHA512_ENABLE
 #define RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF         RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA512
#elif RSIP_CFG_ECC_SECP384R1_ENABLE
 #define RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF         RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_384
#elif RSIP_CFG_KDF_HMAC_SHA384_ENABLE
 #define RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF         RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA384
#else
 #define RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF         RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA256
#endif

/* Buffer sizes for KDF HMAC */
#if RSIP_CFG_KDF_HMAC_SHA512_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_BUF    RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA512)
 #define RSIP_PRV_BYTE_SIZE_KDF_HMAC_BLOCK_BUF          (128U)
#elif RSIP_CFG_KDF_HMAC_SHA384_ENABLE
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_BUF    RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA384)
 #define RSIP_PRV_BYTE_SIZE_KDF_HMAC_BLOCK_BUF          (128U)
#else
 #define RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_BUF    RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA256)
 #define RSIP_PRV_BYTE_SIZE_KDF_HMAC_BLOCK_BUF          (64U)
#endif

/* Buffer sizes for PKI */
#if RSIP_CFG_ECC_SECP521R1_ENABLE
 #define  RSIP_PRV_BYTE_SIZE_PKI_ENC_CERT_INFO          RSIP_BYTE_SIZE_WRAPPED_KEY(16)
#elif RSIP_CFG_ECC_SECP384R1_ENABLE
 #define  RSIP_PRV_BYTE_SIZE_PKI_ENC_CERT_INFO          RSIP_BYTE_SIZE_WRAPPED_KEY(12)
#else
 #define  RSIP_PRV_BYTE_SIZE_PKI_ENC_CERT_INFO          RSIP_BYTE_SIZE_WRAPPED_KEY(8)
#endif

/* Constants */
#define RSIP_PRV_BYTE_SIZE_AES_BLOCK                    (16U)
#define RSIP_PRV_BYTE_SIZE_CCM_NONCE_MAX                (13U)
#define RSIP_PRV_BYTE_SIZE_CCM_AAD_MAX                  (110U)

/* Return code for SB-Lib */
#define FSP_ERR_SB_INTERNAL_FAIL                        (0x00030000UL) ///< An internal failure
#define FSP_ERR_SB_INVALID_ARG                          (0x00030001UL) ///< An invalid argument was entered
#define FSP_ERR_SB_UNSUPPORTED_FUNCTION                 (0x00030002UL) ///< Unsupported function executed
#define FSP_ERR_SB_INVALID_ALIGNMENT                    (0x00030003UL) ///< Data entered with incorrect alignment
#define FSP_ERR_SB_SAME_IMAGE_VERSION                   (0x00030004UL) ///< Same image version
#define FSP_ERR_SB_LOWER_IMAGE_VERSION                  (0x00030005UL) ///< Lower image version
#define FSP_ERR_SB_MANI_INVALID_MAGIC                   (0x00031000UL) ///< An invalid magic number is set
#define FSP_ERR_SB_MANI_UNSUPPORTED_VERSION             (0x00031001UL) ///< Unsupported version is set
#define FSP_ERR_SB_MANI_OUT_OF_RANGE_LEN                (0x00031002UL) ///< Out of range TLV Length is set
#define FSP_ERR_SB_MANI_TLV_FIELD_ERR                   (0x00031003UL) ///< Missing required TLV field
#define FSP_ERR_SB_MANI_TLV_INVALID_LEN                 (0x00031004UL) ///< The length exceeding the end of the manifest is specified in length of the TLV field
#define FSP_ERR_SB_MANI_INVALID_IMAGE_LEN               (0x00031005UL) ///< An invalid image length is set
#define FSP_ERR_SB_MANI_MISMATCH_SIGN_ALGORITHM         (0x00031006UL) ///< There is a wrong combination of signature algorithms
#define FSP_ERR_SB_MANI_UNSUPPORTED_ALGORITHM           (0x00031007UL) ///< An algorithm was specified that the manifest does not support
#define FSP_ERR_SB_CRYPTO_FAIL                          (0x00032000UL) ///< Cryptographic processing failure
#define FSP_ERR_SB_CRYPTO_AUTH_FAIL                     (0x00032001UL) ///< Verification failed
#define FSP_ERR_SB_CRYPTO_UNSUPPORTED_ALGORITHM         (0x00032002UL) ///< Unsupported algorithm
#define FSP_ERR_SB_CRYPTO_RESOURCE_CONFLICT             (0x00032003UL) ///< CryptoIP is in use.
#define FSP_ERR_SB_CRYPTO_PARAM_ERR                     (0x00032004UL) ///< Parameter error

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**
 * Byte size of wrapped key
 */
typedef enum e_rsip_byte_size_wrapped_key
{
    RSIP_BYTE_SIZE_WRAPPED_KEY_AES_128 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_128),                     ///< AES-128
    RSIP_BYTE_SIZE_WRAPPED_KEY_AES_192 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_192),                     ///< AES-192
    RSIP_BYTE_SIZE_WRAPPED_KEY_AES_256 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_256),                     ///< AES-256
    RSIP_BYTE_SIZE_WRAPPED_KEY_XTS_AES_128 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_XTS_AES_128),                 ///< XTS-AES-128
    RSIP_BYTE_SIZE_WRAPPED_KEY_XTS_AES_256 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_XTS_AES_256),                 ///< XTS-AES-256
    RSIP_BYTE_SIZE_WRAPPED_KEY_CHACHA20 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_CHACHA20),                    ///< ChaCha20
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP256R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC),        ///< secp256r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP384R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC),        ///< secp384r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP521R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC),        ///< secp521r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP256K1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC),        ///< secp256k1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP256R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC),  ///< brainpoolP256r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP384R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC),  ///< brainpoolP384r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP512R1_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PUBLIC),  ///< brainpoolP512r1 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_EDWARDS25519_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_EDWARDS25519_PUBLIC),     ///< edwards25519 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP256R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE),       ///< secp256r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP384R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE),       ///< secp384r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP521R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE),       ///< secp521r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_SECP256K1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE),       ///< secp256k1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP256R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE), ///< brainpoolP256r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP384R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE), ///< brainpoolP384r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_BRAINPOOLP512R1_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE), ///< brainpoolP512r1 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_ECC_EDWARDS25519_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_ECC_EDWARDS25519_PRIVATE),    ///< edwards25519 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_1024_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_1024_PUBLIC),             ///< RSA-1024 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_2048_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_2048_PUBLIC),             ///< RSA-2048 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_3072_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_3072_PUBLIC),             ///< RSA-3072 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_4096_PUBLIC =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_4096_PUBLIC),             ///< RSA-4096 public key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_1024_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_1024_PRIVATE),            ///< RSA-1024 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_2048_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_2048_PRIVATE),            ///< RSA-2048 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_3072_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_3072_PRIVATE),            ///< RSA-3072 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_4096_PRIVATE =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_RSA_4096_PRIVATE),            ///< RSA-4096 private key
    RSIP_BYTE_SIZE_WRAPPED_KEY_HMAC_SHA1 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA1),                   ///< HMAC-SHA1
    RSIP_BYTE_SIZE_WRAPPED_KEY_HMAC_SHA224 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA224),                 ///< HMAC-SHA224
    RSIP_BYTE_SIZE_WRAPPED_KEY_HMAC_SHA256 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA256),                 ///< HMAC-SHA256
    RSIP_BYTE_SIZE_WRAPPED_KEY_HMAC_SHA384 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA384),                 ///< HMAC-SHA384
    RSIP_BYTE_SIZE_WRAPPED_KEY_HMAC_SHA512 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_HMAC_SHA512),                 ///< HMAC-SHA512
    RSIP_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_SHA256 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA256),             ///< KDF HMAC-SHA256
    RSIP_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_SHA384 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA384),             ///< KDF HMAC-SHA384
    RSIP_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_SHA512 =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA512),             ///< KDF HMAC-SHA512
    RSIP_BYTE_SIZE_WRAPPED_KEY_KUK =
        RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_KUK),                         ///< Key Update Key (KUK)
} rsip_byte_size_wrapped_key_t;

/**
 * Byte size of encrypted key
 */
typedef enum e_rsip_byte_size_encrypted_key
{
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_AES_128 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_AES_128),                     ///< AES-128
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_AES_192 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_AES_192),                     ///< AES-192
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_AES_256 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_AES_256),                     ///< AES-256
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_XTS_AES_128 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_XTS_AES_128),                 ///< XTS-AES-128
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_XTS_AES_256 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_XTS_AES_256),                 ///< XTS-AES-256
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_CHACHA20 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_CHACHA20),                    ///< ChaCha20
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP256R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC),        ///< secp256r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP384R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC),        ///< secp384r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP521R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC),        ///< secp521r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP256K1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC),        ///< secp256k1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP256R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC),  ///< brainpoolP256r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP384R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC),  ///< brainpoolP384r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP512R1_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PUBLIC),  ///< brainpoolP512r1 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_EDWARDS25519_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_EDWARDS25519_PUBLIC),     ///< edwards25519 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP256R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE),       ///< secp256r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP384R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE),       ///< secp384r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP521R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE),       ///< secp521r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_SECP256K1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE),       ///< secp256k1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP256R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE), ///< brainpoolP256r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP384R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE), ///< brainpoolP384r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_BRAINPOOLP512R1_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE), ///< brainpoolP512r1 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_ECC_EDWARDS25519_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_ECC_EDWARDS25519_PRIVATE),    ///< edwards25519 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_1024_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_1024_PUBLIC),             ///< RSA-1024 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_2048_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_2048_PUBLIC),             ///< RSA-2048 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_3072_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_3072_PUBLIC),             ///< RSA-3072 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_4096_PUBLIC =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_4096_PUBLIC),             ///< RSA-4096 public key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_1024_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_1024_PRIVATE),            ///< RSA-1024 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_2048_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_2048_PRIVATE),            ///< RSA-2048 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_3072_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_3072_PRIVATE),            ///< RSA-3072 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_RSA_4096_PRIVATE =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_RSA_4096_PRIVATE),            ///< RSA-4096 private key
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_HMAC_SHA1 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_HMAC_SHA1),                   ///< HMAC-SHA1
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_HMAC_SHA224 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_HMAC_SHA224),                 ///< HMAC-SHA224
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_HMAC_SHA256 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_HMAC_SHA256),                 ///< HMAC-SHA256
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_HMAC_SHA384 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_HMAC_SHA384),                 ///< HMAC-SHA384
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_HMAC_SHA512 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_HMAC_SHA512),                 ///< HMAC-SHA512
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_KDF_HMAC_SHA256 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA256),             ///< KDF HMAC-SHA256
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_KDF_HMAC_SHA384 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA384),             ///< KDF HMAC-SHA384
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_KDF_HMAC_SHA512 =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_KDF_HMAC_SHA512),             ///< KDF HMAC-SHA512
    RSIP_BYTE_SIZE_ENCRYPTED_KEY_KUK =
        RSIP_BYTE_SIZE_ENCRYPTED_KEY(RSIP_KEY_TYPE_KUK),                         ///< Key Update Key (KUK)
} rsip_byte_size_encrypted_key_t;

/** Byte size of wrapped key */
typedef enum e_rsip_byte_size_wrapped_dkm
{
    RSIP_BYTE_SIZE_WRAPPED_DKM_HEADER       = 12,                                  ///< Header
    RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA256 = RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(8),  ///< A block of SHA-256
    RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA384 = RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(12), ///< A block of SHA-384
    RSIP_BYTE_SIZE_WRAPPED_DKM_BLOCK_SHA512 = RSIP_PRV_BYTE_SIZE_WRAPPED_DATA(16), ///< A block of SHA-384
} rsip_byte_size_wrapped_dkm_t;

/* Working area for AES block cipher */
typedef struct st_rsip_aes_cihper_handle
{
    const void * p_func;               // Pointer to primitive functions
} rsip_aes_cipher_handle_t;

/* Working area for AES-GCM */
typedef struct st_rsip_aes_gcm_handle
{
    const void * p_func;                               // Pointer to primitive functions
    uint8_t      buffer[RSIP_PRV_BYTE_SIZE_AES_BLOCK]; // Buffer for AAD and plaintext/ciphertext
    uint32_t     buffered_length;                      // Buffered AAD and plaintext/ciphertext length
    uint32_t     total_length;                         // Total plaintext/ciphertext length
    uint32_t     total_aad_length;                     // Total AAD length
} rsip_aes_gcm_handle_t;

/* Working area for AES-CCM */
typedef struct st_rsip_aes_ccm_handle
{
    const void       * p_func;                                                               // Pointer to primitive functions
    rsip_wrapped_key_t wrapped_key;                                                          // Wrapped key
    uint8_t            wrapped_key_value[RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_256)]; // Wrapped key value
    uint8_t            nonce_buffer[RSIP_PRV_BYTE_SIZE_CCM_NONCE_MAX];                       // Buffer for nonce
    uint32_t           nonce_length;                                                         // Nonce length
    uint8_t            buffer[RSIP_PRV_BYTE_SIZE_CCM_AAD_MAX];                               // Buffer for AAD and plaintext/ciphertext
    uint32_t           buffered_length;                                                      // Buffered AAD and plaintext/ciphertext length
    uint32_t           input_aad_length;                                                     // Input AAD length
    uint32_t           total_aad_length;                                                     // Total AAD length
    uint32_t           input_length;                                                         // Input plaintext/ciphertext length
    uint32_t           total_length;                                                         // Total plaintext/ciphertext length
    uint32_t           tag_length;                                                           // Tag length
} rsip_aes_ccm_handle_t;

/* Working area for AES-CMAC */
typedef struct st_rsip_aes_cmac_handle
{
    const void * p_func;                               // Pointer to primitive functions
    uint8_t      buffer[RSIP_PRV_BYTE_SIZE_AES_BLOCK]; // Buffer for message
    uint32_t     buffered_length;                      // Buffered message length
    uint32_t     total_length;                         // Total message length
} rsip_aes_cmac_handle_t;

/** Working area for SHA functions. DO NOT MODIFY. */
typedef struct st_rsip_sha_handle
{
    rsip_hash_type_t         type;                                                      // Hash type
    uint8_t                  buffer[RSIP_PRV_BYTE_SIZE_SHA_BLOCK_BUF];                  // Stored message
    uint32_t                 buffered_length;                                           // Buffered message length
    uint32_t                 total_length;                                              // Total message length input to primitive
    uint32_t                 block_size;                                                // Block size
    uint32_t                 internal_state[RSIP_PRV_WORD_SIZE_SHA_INTERNAL_STATE_BUF]; // Internal state
    rsip_user_handle_state_t handle_state;                                              // Handle state
} rsip_sha_handle_t;

/** Working area for HMAC functions. DO NOT MODIFY. */
typedef struct st_rsip_hmac_handle
{
    const void             * p_func;                                                     // Pointer to primitive functions
    rsip_wrapped_key_t       wrapped_key;                                                // Wrapped key
    uint8_t                  wrapped_key_value[RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_HMAC_BUF]; // Wrapped key value
    uint8_t                  buffer[RSIP_PRV_BYTE_SIZE_HMAC_BLOCK_BUF];                  // Stored message
    uint32_t                 buffered_length;                                            // Buffered message length
    uint32_t                 total_length;                                               // Total message length input to primitive
    uint32_t                 block_size;                                                 // Block size
    uint32_t                 internal_state[RSIP_PRV_WORD_SIZE_HMAC_INTERNAL_STATE_BUF]; // Internal state
    rsip_user_handle_state_t handle_state;                                               // Handle state
} rsip_hmac_handle_t;

/** Working area for KDF SHA functions. DO NOT MODIFY. */
typedef struct st_rsip_kdf_sha_handle
{
    rsip_hash_type_t         type;                                                      // Hash type
    uint8_t                  buffer1[4];                                                // Stored message1
    uint32_t                 buffered_length1;                                          // Buffered message length1
    uint8_t                  buffer2[RSIP_PRV_BYTE_SIZE_KDF_SHA_BLOCK_BUF];             // Stored message2
    uint32_t                 buffered_length2;                                          // Buffered message length2
    uint32_t                 total_length;                                              // Total message length input to primitive
    uint32_t                 block_size;                                                // Block size
    uint32_t                 internal_state[RSIP_PRV_WORD_SIZE_SHA_INTERNAL_STATE_BUF]; // Internal state
    rsip_user_handle_state_t handle_state;                                              // Handle state

    uint8_t  wrapped_msg[RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF];                       // Wrapped message
    uint32_t wrapped_msg_length;                                                        // Wrapped message length
    uint32_t actual_wrapped_msg_length;                                                 // Actual wrapped message length
} rsip_kdf_sha_handle_t;

/** Working area for KDF HMAC functions. DO NOT MODIFY. */
typedef struct st_rsip_kdf_hmac_handle
{
    const void             * p_func;                                                         // Pointer to primitive functions
    rsip_wrapped_key_t       wrapped_key;                                                    // Wrapped key
    uint8_t                  wrapped_key_value[RSIP_PRV_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_BUF]; // Wrapped key value
    uint8_t                  buffer[RSIP_PRV_BYTE_SIZE_KDF_HMAC_BLOCK_BUF];                  // Stored message
    uint32_t                 buffered_length;                                                // Buffered message length
    uint32_t                 total_length;                                                   // Total message length input to primitive
    uint32_t                 block_size;                                                     // Block size
    uint32_t                 internal_state[RSIP_PRV_WORD_SIZE_HMAC_INTERNAL_STATE_BUF];     // Internal state
    rsip_user_handle_state_t handle_state;                                                   // Handle state

    uint8_t  wrapped_msg[RSIP_PRV_BYTE_SIZE_KDF_WRAPPED_MSG_BUF];                            // Wrapped message
    uint32_t wrapped_msg_length;                                                             // Wrapped message length
    uint32_t actual_wrapped_msg_length;                                                      // Actual wrapped message length
} rsip_kdf_hmac_handle_t;

/** Verified certificate information */
typedef struct st_rsip_verified_cert_info
{
    uint8_t value[RSIP_PRV_BYTE_SIZE_PKI_ENC_CERT_INFO];
} rsip_verified_cert_info_t;

/** Wrapped ECDH secret structure for ECDH and KDF APIs. */
typedef struct st_rsip_wrapped_secret
{
    uint8_t type;                                              // Internal key type ID
    uint8_t info[3];                                           // Reserved area
    uint8_t value[RSIP_PRV_BYTE_SIZE_ECDH_WRAPPED_SECRET_BUF]; // Wrapped secret
} rsip_wrapped_secret_t;

/* Working area for RSIP cryptographic algorithms. This union is included in private control block. */
typedef union u_rsip_handle
{
    rsip_aes_cipher_handle_t aes_cipher; // AES block cipher
    rsip_aes_gcm_handle_t    aes_gcm;    // AES-GCM
    rsip_aes_ccm_handle_t    aes_ccm;    // AES-CCM
    rsip_aes_cmac_handle_t   aes_cmac;   // AES-CMAC
    rsip_sha_handle_t        sha;        // SHA
    rsip_hmac_handle_t       hmac;       // HMAC
    rsip_kdf_sha_handle_t    kdf_sha;    // KDF SHA
    rsip_kdf_hmac_handle_t   kdf_hmac;   // KDF HMAC
} rsip_handle_t;

/* State that specifies functions that can be called next */
typedef enum e_rsip_state
{
    RSIP_STATE_MAIN,                    // Main
    RSIP_STATE_AES_CIPHER,              // AES-ECB, AES-CBC, AES-CTR
    RSIP_STATE_AES_XTS_UPDATE,          // XTS-AES update
    RSIP_STATE_AES_XTS_FINISH,          // XTS-AES finalization
    RSIP_STATE_AES_GCM_ENC_UPDATE_AAD,  // AES-GCM encryption, AAD input
    RSIP_STATE_AES_GCM_ENC_UPDATE_TEXT, // AES-GCM encryption, plaintext/ciphertext input
    RSIP_STATE_AES_GCM_DEC_UPDATE_AAD,  // AES-GCM decryption, AAD input
    RSIP_STATE_AES_GCM_DEC_UPDATE_TEXT, // AES-GCM decryption, plaintext/ciphertext input
    RSIP_STATE_AES_CCM_ENC_SET_LENGTH,  // AES-CCM encryption, length setting
    RSIP_STATE_AES_CCM_ENC_UPDATE_AAD,  // AES-CCM encryption, AAD input
    RSIP_STATE_AES_CCM_ENC_UPDATE_TEXT, // AES-CCM encryption, plaintext/ciphertext input
    RSIP_STATE_AES_CCM_ENC_FINISH,      // AES-CCM encryption, finish
    RSIP_STATE_AES_CCM_DEC_SET_LENGTH,  // AES-CCM decryption, length setting
    RSIP_STATE_AES_CCM_DEC_UPDATE_AAD,  // AES-CCM decryption, AAD input
    RSIP_STATE_AES_CCM_DEC_UPDATE_TEXT, // AES-CCM decryption, plaintext/ciphertext input
    RSIP_STATE_AES_CCM_DEC_VERI,        // AES-CCM encryption, verification
    RSIP_STATE_AES_CMAC,                // AES-CMAC
    RSIP_STATE_SHA,                     // SHA
    RSIP_STATE_HMAC,                    // HMAC
    RSIP_STATE_KDF_SHA,                 // KDF SHA
    RSIP_STATE_KDF_HMAC,                // KDF HMAC
} rsip_state_t;

/** RSIP private control block. DO NOT MODIFY. Initialization occurs when R_RSIP_Open() is called. */
typedef struct st_rsip_instance_ctrl
{
    uint32_t           open;                          // Indicates whether the open() API has been successfully
    rsip_cfg_t const * p_cfg;                         // Pointer to the configuration block
    rsip_handle_t      handle;                        // Handle of algorithms that cannot be suspended
    rsip_state_t       state;                         // Flags to limit the next API to call

    rsip_verified_cert_info_t pki_verified_cert_info; // Verified certificate info
} rsip_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rsip_api_t g_rsip_on_rsip;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/* r_rsip.c */
fsp_err_t R_RSIP_Open(rsip_ctrl_t * const p_ctrl, rsip_cfg_t const * const p_cfg);
fsp_err_t R_RSIP_Close(rsip_ctrl_t * const p_ctrl);
fsp_err_t R_RSIP_RandomNumberGenerate(rsip_ctrl_t * const p_ctrl, uint8_t * const p_random);
fsp_err_t R_RSIP_KeyGenerate(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t * const p_wrapped_key);
fsp_err_t R_RSIP_KeyPairGenerate(rsip_ctrl_t * const        p_ctrl,
                                 rsip_wrapped_key_t * const p_wrapped_public_key,
                                 rsip_wrapped_key_t * const p_wrapped_private_key);
fsp_err_t R_RSIP_EncryptedKeyWrap(rsip_ctrl_t * const              p_ctrl,
                                  rsip_wrapped_key_t const * const p_key_update_key,
                                  void const * const               p_initial_vector,
                                  void const * const               p_encrypted_key,
                                  rsip_wrapped_key_t * const       p_wrapped_key);
fsp_err_t R_RSIP_RFC3394_KeyWrap(rsip_ctrl_t * const              p_ctrl,
                                 rsip_wrapped_key_t const * const p_wrapped_kek,
                                 rsip_wrapped_key_t const * const p_wrapped_target_key,
                                 uint8_t * const                  p_rfc3394_wrapped_target_key);
fsp_err_t R_RSIP_RFC3394_KeyUnwrap(rsip_ctrl_t * const              p_ctrl,
                                   rsip_wrapped_key_t const * const p_wrapped_kek,
                                   uint8_t const * const            p_rfc3394_wrapped_target_key,
                                   rsip_wrapped_key_t * const       p_wrapped_target_key);
fsp_err_t R_RSIP_PublicKeyExport(rsip_wrapped_key_t const * const p_wrapped_public_key,
                                 uint8_t * const                  p_raw_public_key);

/* r_rsip_aes.c */
fsp_err_t R_RSIP_AES_Cipher_Init(rsip_ctrl_t * const              p_ctrl,
                                 rsip_aes_cipher_mode_t const     mode,
                                 rsip_wrapped_key_t const * const p_wrapped_key,
                                 uint8_t const * const            p_initial_vector);
fsp_err_t R_RSIP_AES_Cipher_Update(rsip_ctrl_t * const   p_ctrl,
                                   uint8_t const * const p_input,
                                   uint8_t * const       p_output,
                                   uint32_t const        length);
fsp_err_t R_RSIP_AES_Cipher_Finish(rsip_ctrl_t * const p_ctrl);
fsp_err_t R_RSIP_AES_AEAD_Init(rsip_ctrl_t * const              p_ctrl,
                               rsip_aes_aead_mode_t const       mode,
                               rsip_wrapped_key_t const * const p_wrapped_key,
                               uint8_t const * const            p_nonce,
                               uint32_t const                   nonce_length);
fsp_err_t R_RSIP_AES_AEAD_LengthsSet(rsip_ctrl_t * const p_ctrl,
                                     uint32_t const      total_aad_length,
                                     uint32_t const      total_text_length,
                                     uint32_t const      tag_length);
fsp_err_t R_RSIP_AES_AEAD_AADUpdate(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_aad, uint32_t const aad_length);
fsp_err_t R_RSIP_AES_AEAD_Update(rsip_ctrl_t * const   p_ctrl,
                                 uint8_t const * const p_input,
                                 uint32_t const        input_length,
                                 uint8_t * const       p_output,
                                 uint32_t * const      p_output_length);
fsp_err_t R_RSIP_AES_AEAD_Finish(rsip_ctrl_t * const p_ctrl,
                                 uint8_t * const     p_output,
                                 uint32_t * const    p_output_length,
                                 uint8_t * const     p_tag);
fsp_err_t R_RSIP_AES_AEAD_Verify(rsip_ctrl_t * const   p_ctrl,
                                 uint8_t * const       p_output,
                                 uint32_t * const      p_output_length,
                                 uint8_t const * const p_tag,
                                 uint32_t const        tag_length);

fsp_err_t R_RSIP_AES_MAC_Init(rsip_ctrl_t * const              p_ctrl,
                              rsip_aes_mac_mode_t const        mode,
                              rsip_wrapped_key_t const * const p_wrapped_key);
fsp_err_t R_RSIP_AES_MAC_Update(rsip_ctrl_t * const   p_ctrl,
                                uint8_t const * const p_message,
                                uint32_t const        message_length);
fsp_err_t R_RSIP_AES_MAC_SignFinish(rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac);
fsp_err_t R_RSIP_AES_MAC_VerifyFinish(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_mac,
                                      uint32_t const mac_length);

/* r_rsip_ecc.c */
fsp_err_t R_RSIP_ECDSA_Sign(rsip_ctrl_t * const              p_ctrl,
                            rsip_wrapped_key_t const * const p_wrapped_private_key,
                            uint8_t const * const            p_hash,
                            uint8_t * const                  p_signature);
fsp_err_t R_RSIP_ECDSA_Verify(rsip_ctrl_t * const              p_ctrl,
                              rsip_wrapped_key_t const * const p_wrapped_public_key,
                              uint8_t const * const            p_hash,
                              uint8_t const * const            p_signature);
fsp_err_t R_RSIP_PureEdDSA_Sign(rsip_ctrl_t * const              p_ctrl,
                                rsip_wrapped_key_t const * const p_wrapped_private_key,
                                rsip_wrapped_key_t const * const p_wrapped_public_key,
                                uint8_t const * const            p_message,
                                uint64_t const                   message_length,
                                uint8_t * const                  p_signature);
fsp_err_t R_RSIP_PureEdDSA_Verify(rsip_ctrl_t * const              p_ctrl,
                                  rsip_wrapped_key_t const * const p_wrapped_public_key,
                                  uint8_t const * const            p_message,
                                  uint64_t const                   message_length,
                                  uint8_t const * const            p_signature);
fsp_err_t R_RSIP_ECDH_KeyAgree(rsip_ctrl_t * const              p_ctrl,
                               rsip_wrapped_key_t const * const p_wrapped_private_key,
                               rsip_wrapped_key_t const * const p_wrapped_public_key,
                               rsip_wrapped_secret_t * const    p_wrapped_secret);
fsp_err_t R_RSIP_ECDH_PlainKeyAgree(rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_private_key,
                                    uint8_t const * const            p_plain_public_key,
                                    rsip_wrapped_secret_t * const    p_wrapped_secret);

/* r_rsip_rsa.c */
fsp_err_t R_RSIP_RSA_Encrypt(rsip_ctrl_t * const              p_ctrl,
                             rsip_wrapped_key_t const * const p_wrapped_public_key,
                             uint8_t const * const            p_plain,
                             uint8_t * const                  p_cipher);
fsp_err_t R_RSIP_RSA_Decrypt(rsip_ctrl_t * const              p_ctrl,
                             rsip_wrapped_key_t const * const p_wrapped_private_key,
                             uint8_t const * const            p_cipher,
                             uint8_t * const                  p_plain);
fsp_err_t R_RSIP_RSAES_PKCS1_V1_5_Encrypt(rsip_ctrl_t * const              p_ctrl,
                                          rsip_wrapped_key_t const * const p_wrapped_public_key,
                                          uint8_t const * const            p_plain,
                                          uint32_t const                   plain_length,
                                          uint8_t * const                  p_cipher);
fsp_err_t R_RSIP_RSAES_PKCS1_V1_5_Decrypt(rsip_ctrl_t * const              p_ctrl,
                                          rsip_wrapped_key_t const * const p_wrapped_private_key,
                                          uint8_t const * const            p_cipher,
                                          uint8_t * const                  p_plain,
                                          uint32_t * const                 p_plain_length,
                                          uint32_t const                   plain_buffer_length);
fsp_err_t R_RSIP_RSAES_OAEP_Encrypt(rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_public_key,
                                    rsip_hash_type_t const           hash_function,
                                    rsip_mgf_type_t const            mask_generation_function,
                                    uint8_t const * const            p_label,
                                    uint32_t const                   label_length,
                                    uint8_t const * const            p_plain,
                                    uint32_t const                   plain_length,
                                    uint8_t * const                  p_cipher);
fsp_err_t R_RSIP_RSAES_OAEP_Decrypt(rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_private_key,
                                    rsip_hash_type_t const           hash_function,
                                    rsip_mgf_type_t const            mask_generation_function,
                                    uint8_t const * const            p_label,
                                    uint32_t const                   label_length,
                                    uint8_t const * const            p_cipher,
                                    uint8_t * const                  p_plain,
                                    uint32_t * const                 p_plain_length,
                                    uint32_t const                   plain_buffer_length);
fsp_err_t R_RSIP_RSASSA_PKCS1_V1_5_Sign(rsip_ctrl_t * const              p_ctrl,
                                        rsip_wrapped_key_t const * const p_wrapped_private_key,
                                        rsip_hash_type_t const           hash_function,
                                        uint8_t const * const            p_hash,
                                        uint8_t * const                  p_signature);
fsp_err_t R_RSIP_RSASSA_PKCS1_V1_5_Verify(rsip_ctrl_t * const              p_ctrl,
                                          rsip_wrapped_key_t const * const p_wrapped_public_key,
                                          rsip_hash_type_t const           hash_function,
                                          uint8_t const * const            p_hash,
                                          uint8_t const * const            p_signature);
fsp_err_t R_RSIP_RSASSA_PSS_Sign(rsip_ctrl_t * const              p_ctrl,
                                 rsip_wrapped_key_t const * const p_wrapped_private_key,
                                 rsip_hash_type_t const           hash_function,
                                 rsip_mgf_type_t const            mask_generation_function,
                                 uint32_t const                   salt_length,
                                 uint8_t const * const            p_hash,
                                 uint8_t * const                  p_signature);
fsp_err_t R_RSIP_RSASSA_PSS_Verify(rsip_ctrl_t * const              p_ctrl,
                                   rsip_wrapped_key_t const * const p_wrapped_public_key,
                                   rsip_hash_type_t const           hash_function,
                                   rsip_mgf_type_t const            mask_generation_function,
                                   uint32_t const                   salt_length,
                                   uint8_t const * const            p_hash,
                                   uint8_t const * const            p_signature);

/* r_rsip_sha.c */
fsp_err_t R_RSIP_SHA_Compute(rsip_ctrl_t * const    p_ctrl,
                             rsip_hash_type_t const hash_type,
                             uint8_t const * const  p_message,
                             uint32_t const         message_length,
                             uint8_t * const        p_digest);
fsp_err_t R_RSIP_SHA_Init(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type);
fsp_err_t R_RSIP_SHA_Update(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message, uint32_t const message_length);
fsp_err_t R_RSIP_SHA_Finish(rsip_ctrl_t * const p_ctrl, uint8_t * const p_digest);
fsp_err_t R_RSIP_SHA_Suspend(rsip_ctrl_t * const p_ctrl, rsip_sha_handle_t * const p_handle);
fsp_err_t R_RSIP_SHA_Resume(rsip_ctrl_t * const p_ctrl, rsip_sha_handle_t const * const p_handle);
fsp_err_t R_RSIP_HMAC_Compute(rsip_ctrl_t * const        p_ctrl,
                              const rsip_wrapped_key_t * p_wrapped_key,
                              uint8_t const * const      p_message,
                              uint32_t const             message_length,
                              uint8_t * const            p_mac);
fsp_err_t R_RSIP_HMAC_Verify(rsip_ctrl_t * const        p_ctrl,
                             const rsip_wrapped_key_t * p_wrapped_key,
                             uint8_t const * const      p_message,
                             uint32_t const             message_length,
                             uint8_t const * const      p_mac,
                             uint32_t const             mac_length);
fsp_err_t R_RSIP_HMAC_Init(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key);
fsp_err_t R_RSIP_HMAC_Update(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                             uint32_t const message_length);
fsp_err_t R_RSIP_HMAC_SignFinish(rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac);
fsp_err_t R_RSIP_HMAC_VerifyFinish(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_mac, uint32_t const mac_length);
fsp_err_t R_RSIP_HMAC_Suspend(rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_t * const p_handle);
fsp_err_t R_RSIP_HMAC_Resume(rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_t const * const p_handle);

/* r_rsip_pki.c */
fsp_err_t R_RSIP_PKI_ECDSA_CertVerify(rsip_ctrl_t * const              p_ctrl,
                                      rsip_wrapped_key_t const * const p_wrapped_public_key,
                                      uint8_t const * const            p_hash,
                                      uint8_t const * const            p_signature);
fsp_err_t R_RSIP_PKI_RSASSA_PKCS1_V1_5_CertVerify(rsip_ctrl_t * const              p_ctrl,
                                                  rsip_wrapped_key_t const * const p_wrapped_public_key,
                                                  rsip_hash_type_t const           hash_function,
                                                  uint8_t const * const            p_hash,
                                                  uint8_t const * const            p_signature);
fsp_err_t R_RSIP_PKI_RSASSA_PSS_CertVerify(rsip_ctrl_t * const              p_ctrl,
                                           rsip_wrapped_key_t const * const p_wrapped_public_key,
                                           rsip_hash_type_t const           hash_function,
                                           rsip_mgf_type_t const            mask_generation_function,
                                           uint32_t const                   salt_length,
                                           uint8_t const * const            p_hash,
                                           uint8_t const * const            p_signature);
fsp_err_t R_RSIP_PKI_VerifiedCertInfoExport(rsip_ctrl_t * const               p_ctrl,
                                            rsip_verified_cert_info_t * const p_verified_cert_info);
fsp_err_t R_RSIP_PKI_VerifiedCertInfoImport(rsip_ctrl_t * const                     p_ctrl,
                                            rsip_verified_cert_info_t const * const p_verified_cert_info);
fsp_err_t R_RSIP_PKI_CertKeyImport(rsip_ctrl_t * const        p_ctrl,
                                   uint8_t const * const      p_cert,
                                   uint32_t const             cert_length,
                                   uint8_t const * const      p_key_param1,
                                   uint32_t const             key_param1_length,
                                   uint8_t const * const      p_key_param2,
                                   uint32_t const             key_param2_length,
                                   rsip_hash_type_t const     hash_function,
                                   rsip_wrapped_key_t * const p_wrapped_public_key);

/* r_rsip_kdf.c */
fsp_err_t R_RSIP_KDF_SHA_Init(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type);
fsp_err_t R_RSIP_KDF_SHA_ECDHSecretUpdate(rsip_ctrl_t * const                 p_ctrl,
                                          rsip_wrapped_secret_t const * const p_wrapped_secret);
fsp_err_t R_RSIP_KDF_SHA_Update(rsip_ctrl_t * const   p_ctrl,
                                uint8_t const * const p_message,
                                uint32_t const        message_length);
fsp_err_t R_RSIP_KDF_SHA_Finish(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t * const p_wrapped_dkm);
fsp_err_t R_RSIP_KDF_SHA_Suspend(rsip_ctrl_t * const p_ctrl, rsip_kdf_sha_handle_t * const p_handle);
fsp_err_t R_RSIP_KDF_SHA_Resume(rsip_ctrl_t * const p_ctrl, rsip_kdf_sha_handle_t const * const p_handle);
fsp_err_t R_RSIP_KDF_HMAC_DKMKeyImport(rsip_ctrl_t * const              p_ctrl,
                                       rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                       uint32_t const                   key_length,
                                       rsip_wrapped_key_t * const       p_wrapped_key);
fsp_err_t R_RSIP_KDF_HMAC_ECDHSecretKeyImport(rsip_ctrl_t * const                 p_ctrl,
                                              rsip_wrapped_secret_t const * const p_wrapped_secret,
                                              rsip_wrapped_key_t * const          p_wrapped_key);
fsp_err_t R_RSIP_KDF_HMAC_Init(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key);
fsp_err_t R_RSIP_KDF_HMAC_DKMUpdate(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t const * const p_wrapped_dkm);
fsp_err_t R_RSIP_KDF_HMAC_ECDHSecretUpdate(rsip_ctrl_t * const                 p_ctrl,
                                           rsip_wrapped_secret_t const * const p_wrapped_secret);
fsp_err_t R_RSIP_KDF_HMAC_Update(rsip_ctrl_t * const   p_ctrl,
                                 uint8_t const * const p_message,
                                 uint32_t const        message_length);
fsp_err_t R_RSIP_KDF_HMAC_SignFinish(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t * const p_wrapped_dkm);
fsp_err_t R_RSIP_KDF_HMAC_Suspend(rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_t * const p_handle);
fsp_err_t R_RSIP_KDF_HMAC_Resume(rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_t const * const p_handle);
fsp_err_t R_RSIP_KDF_DKMConcatenate(rsip_wrapped_dkm_t * const       p_wrapped_dkm1,
                                    rsip_wrapped_dkm_t const * const p_wrapped_dkm2,
                                    uint32_t const                   wrapped_dkm1_buffer_length);
fsp_err_t R_RSIP_KDF_DerivedKeyImport(rsip_ctrl_t * const              p_ctrl,
                                      rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                      uint32_t const                   position,
                                      rsip_wrapped_key_t * const       p_wrapped_key);
fsp_err_t R_RSIP_KDF_DerivedIVWrap(rsip_ctrl_t * const              p_ctrl,
                                   rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                   rsip_initial_vector_type_t const initial_vector_type,
                                   uint32_t const                   position,
                                   uint8_t const * const            p_tls_sequence_num,
                                   uint8_t * const                  p_wrapped_initial_vector);

/* r_rsip_otf.c */
fsp_err_t R_RSIP_OTF_Init(rsip_ctrl_t * const        p_ctrl,
                          rsip_otf_channel_t const   channel,
                          rsip_wrapped_key_t * const p_wrapped_key,
                          uint8_t const * const      p_seed);

/* r_rsip_ra.c */
fsp_err_t R_RSIP_FSBL_OEM_BL_Digest_Generate(rsip_ctrl_t * const   p_ctrl,
                                             uint8_t const * const p_key_cert,
                                             uint32_t const        key_cert_max_length,
                                             uint8_t const * const p_code_cert,
                                             uint32_t const        code_cert_max_length,
                                             uint32_t * const      p_mac);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RSIP_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/
