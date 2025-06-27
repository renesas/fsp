/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SECURITY_INTERFACES
 * @defgroup RSIP_PROTECTED_API RSIP Interface
 * @brief Interface for Renesas Secure IP (RSIP) functions.
 *
 * @section RSIP_PROTECTED_API_Summary Summary
 * The RSIP interface provides RSIP functionality.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_API_H
#define R_RSIP_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Internal macro (calculation of key type values) */
#define RSIP_PRV_KEY_TYPE_VAL(plain_words, alg, subtype)    (((alg) << 24) | ((subtype) << 16) | (plain_words))
#define RSIP_PRV_KEY_TYPE_VAL_ALG(key_type_val)             ((uint8_t) \
                                                             (((uint32_t) (key_type_val) & 0xff000000U) >> 24))
#define RSIP_PRV_KEY_TYPE_VAL_SUBTYPE(key_type_val)         ((uint8_t) \
                                                             (((uint32_t) (key_type_val) & 0x00ff0000U) >> 16))
#define RSIP_PRV_KEY_TYPE_VAL_PLAIN_WORDS(key_type_val)     (((uint32_t) (key_type_val) & 0x0000ffffU) >> 0)

/* Internal algorithm ID */
#define RSIP_PRV_ALG_INVALID                        (0x00)
#define RSIP_PRV_ALG_AES                            (0x01)
#define RSIP_PRV_ALG_XTS_AES                        (0x02)
#define RSIP_PRV_ALG_CHACHA                         (0x03)
#define RSIP_PRV_ALG_ECC_PUBLIC                     (0x04)
#define RSIP_PRV_ALG_ECC_PRIVATE                    (0x05)
#define RSIP_PRV_ALG_RSA_PUBLIC                     (0x06)
#define RSIP_PRV_ALG_RSA_PRIVATE                    (0x07)
#define RSIP_PRV_ALG_HMAC                           (0x08)
#define RSIP_PRV_ALG_KDF_HMAC                       (0x09)
#define RSIP_PRV_ALG_MISC                           (0xff)

/* Internal key subtype ID */
#define RSIP_PRV_KEY_SUBTYPE_INVALID                (0x0)
#define RSIP_PRV_KEY_SUBTYPE_AES_128                (0x0)
#define RSIP_PRV_KEY_SUBTYPE_AES_192                (0x1)
#define RSIP_PRV_KEY_SUBTYPE_AES_256                (0x2)
#define RSIP_PRV_KEY_SUBTYPE_AES_NUM                (0x3)
#define RSIP_PRV_KEY_SUBTYPE_CHACHA_CHACHA20        (0x0)
#define RSIP_PRV_KEY_SUBTYPE_CHACHA_NUM             (0x1)
#define RSIP_PRV_KEY_SUBTYPE_ECC_SECP256R1          (0x0)
#define RSIP_PRV_KEY_SUBTYPE_ECC_SECP384R1          (0x1)
#define RSIP_PRV_KEY_SUBTYPE_ECC_SECP521R1          (0x2)
#define RSIP_PRV_KEY_SUBTYPE_ECC_SECP256K1          (0x3)
#define RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP256R1    (0x4)
#define RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP384R1    (0x5)
#define RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP512R1    (0x6)
#define RSIP_PRV_KEY_SUBTYPE_ECC_EDWARDS25519       (0x7)
#define RSIP_PRV_KEY_SUBTYPE_ECC_NUM                (0x8)
#define RSIP_PRV_KEY_SUBTYPE_RSA_1024               (0x0)
#define RSIP_PRV_KEY_SUBTYPE_RSA_2048               (0x1)
#define RSIP_PRV_KEY_SUBTYPE_RSA_3072               (0x2)
#define RSIP_PRV_KEY_SUBTYPE_RSA_4096               (0x3)
#define RSIP_PRV_KEY_SUBTYPE_RSA_NUM                (0x4)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_SHA1              (0x0)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224            (0x1)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256            (0x2)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_SHA384            (0x3)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_SHA512            (0x4)
#define RSIP_PRV_KEY_SUBTYPE_HMAC_NUM               (0x5)
#define RSIP_PRV_KEY_SUBTYPE_MISC_KUK               (0x0)
#define RSIP_PRV_KEY_SUBTYPE_MISC_NUM               (0x1)

/* Internal DKM algorithm ID */
#define RSIP_PRV_DKM_ALG_INVALID                    (0x0)
#define RSIP_PRV_DKM_ALG_SHA                        (0x1)
#define RSIP_PRV_DKM_ALG_HMAC                       (0x2)

/* Internal DKM subtype ID */
#define RSIP_PRV_DKM_SUBTYPE_INVALID                (0x0)
#define RSIP_PRV_DKM_SUBTYPE_SHA_256                (0x0)
#define RSIP_PRV_DKM_SUBTYPE_SHA_384                (0x1)
#define RSIP_PRV_DKM_SUBTYPE_SHA_NUM                (0x2)
#define RSIP_PRV_DKM_SUBTYPE_HMAC_SHA256            (0x0)
#define RSIP_PRV_DKM_SUBTYPE_HMAC_SHA384            (0x1)
#define RSIP_PRV_DKM_SUBTYPE_HMAC_SHA512            (0x2)
#define RSIP_PRV_DKM_SUBTYPE_HMAC_NUM               (0x3)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Key types */
typedef enum e_rsip_key_type
{
    RSIP_KEY_TYPE_INVALID =
        RSIP_PRV_KEY_TYPE_VAL(0, RSIP_PRV_ALG_INVALID, RSIP_PRV_KEY_SUBTYPE_INVALID),                  ///< Invalid key
    RSIP_KEY_TYPE_AES_128 =
        RSIP_PRV_KEY_TYPE_VAL(4, RSIP_PRV_ALG_AES, RSIP_PRV_KEY_SUBTYPE_AES_128),                      ///< AES-128
    RSIP_KEY_TYPE_AES_192 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_AES, RSIP_PRV_KEY_SUBTYPE_AES_192),                      ///< AES-192
    RSIP_KEY_TYPE_AES_256 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_AES, RSIP_PRV_KEY_SUBTYPE_AES_256),                      ///< AES-256
    RSIP_KEY_TYPE_XTS_AES_128 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_XTS_AES, RSIP_PRV_KEY_SUBTYPE_AES_128),                  ///< XTS-AES-128
    RSIP_KEY_TYPE_XTS_AES_256 =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_XTS_AES, RSIP_PRV_KEY_SUBTYPE_AES_256),                 ///< XTS-AES-256
    RSIP_KEY_TYPE_CHACHA20 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_CHACHA, RSIP_PRV_KEY_SUBTYPE_CHACHA_CHACHA20),           ///< ChaCha20
    RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_SECP256R1),        ///< secp256r1 public key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(24, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_SECP384R1),        ///< secp384r1 public key (also known as NIST P-384)
    RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(40, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_SECP521R1),        ///< secp521r1 public key (also known as NIST P-521)
    RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_SECP256K1),        ///< secp256k1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP256R1),  ///< brainpoolP256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(24, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP384R1),  ///< brainpoolP384r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(32, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP512R1),  ///< brainpoolP512r1 public key
    RSIP_KEY_TYPE_ECC_EDWARDS25519_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_ECC_PUBLIC, RSIP_PRV_KEY_SUBTYPE_ECC_EDWARDS25519),      ///< edwards25519 public key
    RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_SECP256R1),        ///< secp256r1 private key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(12, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_SECP384R1),       ///< secp384r1 private key (also known as NIST P-384)
    RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(20, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_SECP521R1),       ///< secp521r1 private key (also known as NIST P-521)
    RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_SECP256K1),        ///< secp256k1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP256R1),  ///< brainpoolP256r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(12, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP384R1), ///< brainpoolP384r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP512R1), ///< brainpoolP512r1 private key
    RSIP_KEY_TYPE_ECC_EDWARDS25519_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_ECC_PRIVATE, RSIP_PRV_KEY_SUBTYPE_ECC_EDWARDS25519),     ///< edwards25519 private key
    RSIP_KEY_TYPE_RSA_1024_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(36, RSIP_PRV_ALG_RSA_PUBLIC, RSIP_PRV_KEY_SUBTYPE_RSA_1024),             ///< RSA-1024 public key
    RSIP_KEY_TYPE_RSA_2048_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(68, RSIP_PRV_ALG_RSA_PUBLIC, RSIP_PRV_KEY_SUBTYPE_RSA_2048),             ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_3072_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(100, RSIP_PRV_ALG_RSA_PUBLIC, RSIP_PRV_KEY_SUBTYPE_RSA_3072),            ///< RSA-3072 public key
    RSIP_KEY_TYPE_RSA_4096_PUBLIC =
        RSIP_PRV_KEY_TYPE_VAL(132, RSIP_PRV_ALG_RSA_PUBLIC, RSIP_PRV_KEY_SUBTYPE_RSA_4096),            ///< RSA-4096 public key
    RSIP_KEY_TYPE_RSA_1024_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(64, RSIP_PRV_ALG_RSA_PRIVATE, RSIP_PRV_KEY_SUBTYPE_RSA_1024),            ///< RSA-1024 private key
    RSIP_KEY_TYPE_RSA_2048_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(128, RSIP_PRV_ALG_RSA_PRIVATE, RSIP_PRV_KEY_SUBTYPE_RSA_2048),           ///< RSA-2048 private key
    RSIP_KEY_TYPE_RSA_3072_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(192, RSIP_PRV_ALG_RSA_PRIVATE, RSIP_PRV_KEY_SUBTYPE_RSA_3072),           ///< RSA-3072 private key
    RSIP_KEY_TYPE_RSA_4096_PRIVATE =
        RSIP_PRV_KEY_TYPE_VAL(256, RSIP_PRV_ALG_RSA_PRIVATE, RSIP_PRV_KEY_SUBTYPE_RSA_4096),           ///< RSA-4096 private key
    RSIP_KEY_TYPE_HMAC_SHA1 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA1),                   ///< HMAC-SHA1
    RSIP_KEY_TYPE_HMAC_SHA224 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224),                 ///< HMAC-SHA224
    RSIP_KEY_TYPE_HMAC_SHA256 =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256),                 ///< HMAC-SHA256
    RSIP_KEY_TYPE_HMAC_SHA384 =
        RSIP_PRV_KEY_TYPE_VAL(12, RSIP_PRV_ALG_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA384),                ///< HMAC-SHA384
    RSIP_KEY_TYPE_HMAC_SHA512 =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA512),                ///< HMAC-SHA512
    RSIP_KEY_TYPE_KDF_HMAC_SHA256 =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_KDF_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256),            ///< HMAC-SHA256
    RSIP_KEY_TYPE_KDF_HMAC_SHA384 =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_KDF_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA384),            ///< HMAC-SHA384
    RSIP_KEY_TYPE_KDF_HMAC_SHA512 =
        RSIP_PRV_KEY_TYPE_VAL(16, RSIP_PRV_ALG_KDF_HMAC, RSIP_PRV_KEY_SUBTYPE_HMAC_SHA512),            ///< HMAC-SHA512
    RSIP_KEY_TYPE_KUK =
        RSIP_PRV_KEY_TYPE_VAL(8, RSIP_PRV_ALG_MISC, RSIP_PRV_KEY_SUBTYPE_MISC_KUK),                    ///< Key Update Key (KUK)
} rsip_key_type_t;

/** Block cipher modes of operation for AES */
typedef enum e_rsip_aes_cipher_mode
{
    RSIP_AES_CIPHER_MODE_ECB_ENC,            ///< Electronic Codebook (ECB) mode encryption
    RSIP_AES_CIPHER_MODE_ECB_DEC,            ///< Electronic Codebook (ECB) mode decryption
    RSIP_AES_CIPHER_MODE_CBC_ENC,            ///< Cipher Block Chaining (CBC) mode encryption
    RSIP_AES_CIPHER_MODE_CBC_DEC,            ///< Cipher Block Chaining (CBC) mode decryption
    RSIP_AES_CIPHER_MODE_CTR,                ///< Counter (CTR) mode encryption or decryption
    RSIP_AES_CIPHER_MODE_XTS_ENC,            ///< XEX-based tweaked-codebook mode with ciphertext stealing (XTS) encryption
    RSIP_AES_CIPHER_MODE_XTS_DEC,            ///< XEX-based tweaked-codebook mode with ciphertext stealing (XTS) decryption

    RSIP_AES_CIPHER_MODE_CBC_ENC_WRAPPED_IV, ///< Cipher Block Chaining (CBC) mode encryption with wrapped IV
    RSIP_AES_CIPHER_MODE_CBC_DEC_WRAPPED_IV, ///< Cipher Block Chaining (CBC) mode decryption with wrapped IV
} rsip_aes_cipher_mode_t;

/** AEAD modes of operation for AES */
typedef enum e_rsip_aes_aead_mode
{
    RSIP_AES_AEAD_MODE_GCM_ENC,            ///< Galois/Counter Mode (GCM) encryption
    RSIP_AES_AEAD_MODE_GCM_DEC,            ///< Galois/Counter Mode (GCM) decryption
    RSIP_AES_AEAD_MODE_CCM_ENC,            ///< Counter with CBC-MAC (CCM) encryption
    RSIP_AES_AEAD_MODE_CCM_DEC,            ///< Counter with CBC-MAC (CCM) decryption

    RSIP_AES_AEAD_MODE_GCM_ENC_WRAPPED_IV, ///< Galois/Counter Mode (GCM) encryption with wrapped IV
    RSIP_AES_AEAD_MODE_GCM_DEC_WRAPPED_IV, ///< Galois/Counter Mode (GCM) decryption with wrapped IV
} rsip_aes_aead_mode_t;

/** MAC modes of operation for AES */
typedef enum e_rsip_aes_mac_mode
{
    RSIP_AES_MAC_MODE_CMAC,            ///< Cipher-based MAC (CMAC)
} rsip_aes_mac_mode_t;

/** Hash type */
typedef enum e_rsip_hash_type
{
    RSIP_HASH_TYPE_SHA1,               ///< SHA-1
    RSIP_HASH_TYPE_SHA224,             ///< SHA-224
    RSIP_HASH_TYPE_SHA256,             ///< SHA-256
    RSIP_HASH_TYPE_SHA384,             ///< SHA-384
    RSIP_HASH_TYPE_SHA512,             ///< SHA-512
    RSIP_HASH_TYPE_SHA512_224,         ///< SHA-512/224
    RSIP_HASH_TYPE_SHA512_256,         ///< SHA-512/256
    RSIP_HASH_TYPE_NUM                 // Number of hash types
} rsip_hash_type_t;

/** MGF type */
typedef enum e_rsip_mgf_type
{
    RSIP_MGF_TYPE_MGF1_SHA1       = RSIP_HASH_TYPE_SHA1,       ///< MGF1 with SHA-1
    RSIP_MGF_TYPE_MGF1_SHA224     = RSIP_HASH_TYPE_SHA224,     ///< MGF1 with SHA-224
    RSIP_MGF_TYPE_MGF1_SHA256     = RSIP_HASH_TYPE_SHA256,     ///< MGF1 with SHA-256
    RSIP_MGF_TYPE_MGF1_SHA384     = RSIP_HASH_TYPE_SHA384,     ///< MGF1 with SHA-384
    RSIP_MGF_TYPE_MGF1_SHA512     = RSIP_HASH_TYPE_SHA512,     ///< MGF1 with SHA-512
    RSIP_MGF_TYPE_MGF1_SHA512_224 = RSIP_HASH_TYPE_SHA512_224, ///< MGF1 with SHA-512/224
    RSIP_MGF_TYPE_MGF1_SHA512_256 = RSIP_HASH_TYPE_SHA512_256  ///< MGF1 with SHA-512/256
} rsip_mgf_type_t;

/** RSA salt length */
typedef enum e_rsip_rsa_salt_length
{
    RSIP_RSA_SALT_LENGTH_AUTO = 0xFFFFFFFFU, ///< When signing, the salt length is set to @ref RSIP_RSA_SALT_LENGTH_MAX or @ref RSIP_RSA_SALT_LENGTH_HASH, whichever is shorter. When verifying, the salt length is detected automatically.
    RSIP_RSA_SALT_LENGTH_HASH = 0xFFFFFFFEU, ///< The salt length is set to the hash length.
    RSIP_RSA_SALT_LENGTH_MAX  = 0xFFFFFFFDU, ///< The salt length is set to emLen - hLen - 2, where emLen is the same as the key length and hLen is the hash length.
} rsip_rsa_salt_length_t;

/* State that specifies functions that can be called next. This enum is private. */
typedef enum e_rsip_user_handle_state
{
    RSIP_USER_HANDLE_STATE_INIT,       // Init function can be called.
    RSIP_USER_HANDLE_STATE_RESUME,     // Resume
    RSIP_USER_HANDLE_STATE_UPDATE      // Update
} rsip_user_handle_state_t;

/** IV data types */
typedef enum e_rsip_initial_vector_type
{
    RSIP_INITIAL_VECTOR_TYPE_AES_16_BYTE,    ///< Wrapped AES initial vector (unprocessed)
    RSIP_INITIAL_VECTOR_TYPE_AES_TLS12_AEAD, ///< Wrapped AES nonce (TLS1.2 AES AEAD)
    RSIP_INITIAL_VECTOR_TYPE_AES_TLS13_AEAD, ///< Wrapped AES nonce (TLS1.3 AES AEAD)
} rsip_initial_vector_type_t;

/** Channel number of on-the-fly decryption/encryption module. */
typedef enum e_rsip_otf_channel
{
    RSIP_OTF_CHANNEL_0,                ///< Channel 0
    RSIP_OTF_CHANNEL_1,                ///< Channel 1
    RSIP_OTF_CHANNEL_2,                ///< Channel 2
    RSIP_OTF_CHANNEL_NUM               // Number of channels
} rsip_otf_channel_t;

/** Wrapped key structure for all supported algorithms. */
typedef struct st_rsip_wrapped_key
{
    rsip_key_type_t type;              ///< Key type
    void          * p_value;           ///< Key value
} rsip_wrapped_key_t;

/** Wrapped Derived Keying Material (DKM) structure for KDF APIs. */
typedef struct st_rsip_wrapped_dkm
{
    uint8_t  alg;                      // Internal algorithm ID
    uint8_t  subtype;                  // Internal key type ID
    uint8_t  info[2];                  // Reserved area
    uint32_t block_length;             // DKM block length
    uint32_t blocks;                   // Number of DKM blocks

    uint8_t value[];                   // Variable length array to store the data value
} rsip_wrapped_dkm_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_sha_handle_abstractor_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_hmac_handle_abstractor_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_kdf_sha_handle_abstractor_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_kdf_hmac_handle_abstractor_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_wrapped_secret_abstractor_t;

/** Allocate an instance specific handle to pass into the API calls. */
typedef void rsip_verified_cert_info_abstractor_t;

/** RSIP Control block. Allocate an instance specific control block to pass into the API calls. */
typedef void rsip_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_rsip_cfg
{
    void const * p_extend;             ///< Hardware-dependent configuration
} rsip_cfg_t;

/** RSIP driver structure.  General RSIP functions implemented at the HAL layer follow this API. */
typedef struct st_rsip_api
{
    /**
     * Enables use of Renesas Secure IP functionality.
     *
     * @param[in,out] p_ctrl Pointer to control block.
     * @param[in]     p_cfg  Pointer to configuration structure.
     */
    fsp_err_t (* open)(rsip_ctrl_t * const p_ctrl, rsip_cfg_t const * const p_cfg);

    /**
     * Disables use of Renesas Secure IP functionality.
     *
     * @param[in,out]   p_ctrl     Pointer to control block.
     */
    fsp_err_t (* close)(rsip_ctrl_t * const p_ctrl);

    /**
     * Generates a 128-bit random number.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_random 128bit random numbers.
     */
    fsp_err_t (* randomNumberGenerate)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_random);

    /**
     * Generate a wrapped symmetric key from a random number.
     * In this API, user key input is unnecessary.
     * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in,out] p_wrapped_key Pointer to destination of wrapped key. The length depends on key type. Refer "Key Size Table".
     */
    fsp_err_t (* keyGenerate)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t * const p_wrapped_key);

    /**
     * Generate a wrapped asymmetric key pair from a random number. In this API, user key input is unnecessary.
     * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in,out] p_wrapped_public_key  Key index for Public Key. The length depends on the key type. Refer "Key Size Table".
     * @param[in,out] p_wrapped_private_key Key index for Private Key. The length depends on the key type. Refer "Key Size Table".
     */
    fsp_err_t (* keyPairGenerate)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t * const p_wrapped_public_key,
                                  rsip_wrapped_key_t * const p_wrapped_private_key);

    /**
     * Decrypt the encrypted user key with Key Update Key (KUK) and wrap it with the Hardware Unique Key (HUK).
     *
     * @param[in,out] p_ctrl           Pointer to control block.
     * @param[in]     p_key_update_key Pointer to Key Update Key.
     * @param[in]     p_initial_vector Initialization vector when generating encrypted_key.
     *                                 The length is 16 bytes.
     * @param[in]     p_encrypted_key  Encrypted user key. The length depends on the key type. Refer "Key Size Table".
     * @param[in,out] p_wrapped_key    Pointer to destination of wrapped key. The length depends on key type. Refer "Key Size Table".
     */
    fsp_err_t (* encryptedKeyWrap)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_key_update_key,
                                   void const * const p_initial_vector, void const * const p_encrypted_key,
                                   rsip_wrapped_key_t * const p_wrapped_key);

    /**
     * This function provides Key Wrap algorithm compliant with RFC3394.
     * Using p_wrapped_kek to wrap p_wrapped_target_key, and output the result to p_rfc3394_wrapped_target_key.
     *
     * @param[in,out] p_ctrl                       Pointer to control block.
     * @param[in]     p_wrapped_kek                Pointer to wrapped key-encryption-key used to RFC3394-wrap the target key.
     * @param[in]     p_wrapped_target_key         Pointer to wrapped target key to be RFC3394-wrapped.
     * @param[out]    p_rfc3394_wrapped_target_key Pointer to destination of RFC3394-wrapped target key.
     */
    fsp_err_t (* rfc3394_KeyWrap)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_kek,
                                  rsip_wrapped_key_t const * const p_wrapped_target_key,
                                  uint8_t * const p_rfc3394_wrapped_target_key);

    /**
     * This function provides Key Unwrap algorithm compliant with RFC3394.
     * Using p_wrapped_kek to unwrap p_rfc3394_wrapped_target_key, and output the result to p_wrapped_target_key.
     *
     * @param[in,out] p_ctrl                       Pointer to control block.
     * @param[in]     p_wrapped_kek                Pointer to wrapped key-encryption-key used to RFC3394-unwrap the target key.
     * @param[in]     p_rfc3394_wrapped_target_key Pointer to AES-wrapped target key to be RFC3394-unwrapped.
     * @param[in,out] p_wrapped_target_key         Pointer to destination of RFC3394-unwrapped target key.
     */
    fsp_err_t (* rfc3394_KeyUnwrap)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_kek,
                                    uint8_t const * const p_rfc3394_wrapped_target_key,
                                    rsip_wrapped_key_t * const p_wrapped_target_key);

    /**
     * Exports public key parameters from a wrapped key.
     *
     * @param[in]  p_wrapped_public_key Key index for Public Key. The length depends on the key type. Refer "Key Size Table".
     * @param[out] p_raw_public_key     Pointer to destination of raw public key. The length depends on the key length.
     */
    fsp_err_t (* publicKeyExport)(rsip_wrapped_key_t const * const p_wrapped_public_key,
                                  uint8_t * const                  p_raw_public_key);

    /**
     * Set parameters of AES cipher.
     *
     * @param[in,out] p_ctrl           Pointer to control block.
     * @param[in]     mode             Block cipher modes of operation for AES.
     * @param[in]     p_wrapped_key    Pointer to wrapped key of AES or XTS-AES key.
     * @param[in]     p_initial_vector Pointer to initialization vector (IV) or nonce. The length is 16 bytes.
     *                                 @arg [ECB] Not required
     *                                 @arg [CBC][XTS] IV
     *                                 @arg [CTR] Nonce
     */
    fsp_err_t (* aesCipherInit)(rsip_ctrl_t * const p_ctrl, rsip_aes_cipher_mode_t const mode,
                                rsip_wrapped_key_t const * const p_wrapped_key, uint8_t const * const p_initial_vector);

    /**
     * Encrypt plaintext.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[in]     p_input  Pointer to input text. The length is given as the argument.
     * @param[out]    p_output Pointer to destination of output text. The length is given as the argument.
     * @param[in]     length   Byte length of input and output.
     *                         @arg [ECB][CBC][CTR] Must be 0 or a multiple of 16.
     *                         @arg [XTS] Must be 0 or greater than or equal to 16.
     *                         After an integer not divisible by 16 is input, update can no longer be executed.
     */
    fsp_err_t (* aesCipherUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_input, uint8_t * const p_output,
                                  uint32_t const length);

    /**
     * Finalize AES operation.
     *
     * @param[in,out] p_ctrl Pointer to control block.
     */
    fsp_err_t (* aesCipherFinish)(rsip_ctrl_t * const p_ctrl);

    /**
     * Prepares an AES-AEAD function.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     mode          AEAD mode of operation.
     * @param[in]     p_wrapped_key Pointer to wrapped key of AES key.
     * @param[in]     p_nonce       Pointer to nonce. The length is nonce_length.
     * @param[in]     nonce_length  Byte length of nonce. Input 1 or more.
     */
    fsp_err_t (* aesAeadInit)(rsip_ctrl_t * const p_ctrl, rsip_aes_aead_mode_t const mode,
                              rsip_wrapped_key_t const * const p_wrapped_key, uint8_t const * const p_nonce,
                              uint32_t const nonce_length);

    /**
     * Set text and tag lengths for specific mode.
     *
     * @param[in,out] p_ctrl            Pointer to control block.
     * @param[in]     total_aad_length  Total AAD length.
     * @param[in]     total_text_length Total input and output text length.
     * @param[in]     tag_length        Input or output tag length.
     */
    fsp_err_t (* aesAeadLengthsSet)(rsip_ctrl_t * const p_ctrl, uint32_t const total_aad_length,
                                    uint32_t const total_text_length, uint32_t const tag_length);

    /**
     * Inputs additional authentication data.
     *
     * @param[in,out] p_ctrl     Pointer to control block.
     * @param[in]     p_aad      Additional authentication data. The length depends on aad_length.
     * @param[in]     aad_length Byte length of additional authentication data (0 or more bytes).
     *                           After starting input of plaintext, this value must always be 0.
     */
    fsp_err_t (* aesAeadAadUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_aad, uint32_t const aad_length);

    /**
     * Inputs test and executes encryption and decryption.
     *
     * @param[in,out] p_ctrl          Pointer to control block.
     * @param[in]     p_input         Pointer to input text. The length is input_length.
     * @param[in]     input_length    Byte length of input text (0 or more bytes).
     * @param[out]    p_output        Pointer to destination of output text. The length is p_output_length.
     * @param[out]    p_output_length Pointer to destination of output text length.
     */
    fsp_err_t (* aesAeadUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_input, uint32_t const input_length,
                                uint8_t * const p_output, uint32_t * const p_output_length);

    /**
     * Finalizes an AES-GCM encryption.
     *
     * If there is 16-byte fractional data indicated by the total data length of the value of p_plain that was input by
     * R_RSIP_AES_GCM_EncryptUpdate(), this API will output the result of encrypting that fractional data to p_cipher.
     * Here, the portion that does not reach 16 bytes will be padded with zeros.
     *
     * @param[in,out] p_ctrl          Pointer to control block.
     * @param[out]    p_output        Pointer to destination of output text. The fractional block is output.
     * @param[out]    p_output_length Pointer to destination of output text length.
     * @param[out]    p_tag           Pointer to destination of tag for authentication.
     *                                GCM : The length is 16 bytes.
     *                                      *If a different tag length is required, truncate the 16-byte tag
     *                                        to the required tag length (NIST SP800-38D 7.1).
     *                                CCM : The length is the value set by the API R_RSIP_AES_AEAD_LengthsSet().
     */
    fsp_err_t (* aesAeadFinish)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_output, uint32_t * const p_output_length,
                                uint8_t * const p_tag);

    /**
     * Finalizes an AES-GCM decryption.
     *
     * If there is 16-byte fractional data indicated by the total data length of the value of p_cipher that was input by
     * R_RSIP_AES_GCM_DecryptUpdate(), this API will output the result of decrypting that fractional data to p_cipher.
     * Here, the portion that does not reach 16 bytes will be padded with zeros.
     *
     * @param[in,out] p_ctrl          Pointer to control block.
     * @param[out]    p_output        Pointer to destination of decrypted data.
     * @param[out]    p_output_length Pointer to destination of decrypted data length.
     * @param[in]     p_tag           Pointer to destination of tag for authentication. The length depends on tag_length.
     * @param[in]     tag_length      Byte length of tag. Must be 1 to 16.
     */
    fsp_err_t (* aesAeadVerify)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_output, uint32_t * const p_output_length,
                                uint8_t const * const p_tag, uint32_t const tag_length);

    /**
     * Prepares an AES-MAC generation and verification.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     mode          MAC mode of operation
     * @param[in]     p_wrapped_key Pointer to wrapped key of AES key.
     */
    fsp_err_t (* aesMacInit)(rsip_ctrl_t * const p_ctrl, rsip_aes_mac_mode_t const mode,
                             rsip_wrapped_key_t const * const p_wrapped_key);

    /**
     * Input message.
     * Inside this function, the data that is input by the user is buffered until the input value of p_message exceeds 16 bytes.
     * If the input value, p_message, is not a multiple of 16 bytes, it will be padded within the function.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     */
    fsp_err_t (* aesMacUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                               uint32_t const message_length);

    /**
     * Finalizes an AES-CMAC generation.
     *
     * @param[in,out] p_ctrl Pointer to control block.
     * @param[out]    p_mac  Pointer to destination of MAC. The length is 16 bytes.
     */
    fsp_err_t (* aesMacSignFinish)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac);

    /** Finalizes an AES-CMAC verification.
     *
     * @param[in,out] p_ctrl     Pointer to control block.
     * @param[in]     p_mac      Pointer to MAC. The length depends on mac_length.
     * @param[in]     mac_length Byte length of MAC. Must be 2 to 16.
     */
    fsp_err_t (* aesMacVerifyFinish)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_mac,
                                     uint32_t const mac_length);

    /**
     * Signs a hashed message. The message hash should be generated in advance.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Pointer to wrapped key of ECC private key.
     * @param[in]     p_hash                Pointer to hash value. The length is as same as the key length.
     * @param[out]    p_signature           Pointer to destination of signature (r, s).
     *                                      The length is twice as long as the key length.
     */
    fsp_err_t (* ecdsaSign)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                            uint8_t const * const p_hash, uint8_t * const p_signature);

    /**
     * Verifies a hashed message. The message hash should be generated in advance.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of ECC public key.
     * @param[in]     p_hash               Pointer to hash value. The length is as same as the key length.
     * @param[in]     p_signature          Pointer to signature (r, s). The length is twice as long as the key length.
     */
    fsp_err_t (* ecdsaVerify)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                              uint8_t const * const p_hash, uint8_t const * const p_signature);

    /**
     * Sign the message using EdDSA.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Pointer to wrapped key of ECC private key.
     * @param[in]     p_wrapped_public_key  Pointer to wrapped key of ECC public key.
     * @param[in]     p_message             Pointer to message. The length is message_length.
     * @param[in]     message_length        Byte length of message.
     * @param[out]    p_signature           Pointer to destination of signature (r, s).
     *                                      The length is twice as long as the key length.
     */
    fsp_err_t (* eddsaSign)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                            rsip_wrapped_key_t const * const p_wrapped_public_key, uint8_t const * const p_message,
                            uint64_t const message_length, uint8_t * const p_signature);

    /**
     * Verifies the message using EdDSA.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of ECC public key.
     * @param[in]     p_message            Pointer to message. The length is message_length.
     * @param[in]     message_length       Byte length of message.
     * @param[in]     p_signature          Pointer to signature (r, s). The length is twice as long as the key length.
     */
    fsp_err_t (* eddsaVerify)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                              uint8_t const * const p_message, uint64_t const message_length,
                              uint8_t const * const p_signature);

    /**
     * Computes ECDH secret with wrapped private key and wrapped public key.
     *
     * @param[in,out] p_ctrl                 Pointer to control block.
     * @param[in]     p_wrapped_private_key  Wrapped secp256r1 private key.
     * @param[in]     p_wrapped_public_key   Wrapped secp256r1 public key.
     * @param[out]    p_wrapped_secret       Pointer to destination of wrapped secret
     */
    fsp_err_t (* ecdhKeyAgree)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                               rsip_wrapped_key_t const * const p_wrapped_public_key,
                               rsip_wrapped_secret_abstractor_t * const p_wrapped_secret);

    /**
     * Computes ECDH secret with wrapped private key and plain public key.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Wrapped secp256r1 private key.
     * @param[in]     p_plain_public_key    Plain secp256r1 public key.
     * @param[out]    p_wrapped_secret      Pointer to destination of wrapped secret.
     */
    fsp_err_t (* ecdhPlainKeyAgree)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                                    uint8_t const * const p_plain_public_key,
                                    rsip_wrapped_secret_abstractor_t * const p_wrapped_secret);

    /**
     * Encrypts plaintext with raw RSA.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of RSA public key.
     * @param[in]     p_plain              Pointer to plaintext. The length is as same as the key length.
     * @param[out]    p_cipher             Pointer to destination of ciphertext. The length is as same as the key length.
     */
    fsp_err_t (* rsaEncrypt)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                             uint8_t const * const p_plain, uint8_t * const p_cipher);

    /**
     * Decrypts ciphertext with raw RSA.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Pointer to wrapped key of RSA private key.
     * @param[in]     p_cipher              Pointer to ciphertext. The length is as same as the key length.
     * @param[out]    p_plain               Pointer to destination of plaintext. The length is as same as the key length.
     */
    fsp_err_t (* rsaDecrypt)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                             uint8_t const * const p_cipher, uint8_t * const p_plain);

    /**
     * Encrypts plaintext with RSAES-PKCS1-v1_5.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of RSA public key.
     * @param[in]     p_plain              Pointer to plaintext.
     * @param[in]     plain_length         Length of plaintext.
     * @param[out]    p_cipher             Pointer to destination of ciphertext. The length is as same as the key length.
     */
    fsp_err_t (* rsaesPkcs1V15Encrypt)(rsip_ctrl_t * const p_ctrl,
                                       rsip_wrapped_key_t const * const p_wrapped_public_key,
                                       uint8_t const * const p_plain, uint32_t const plain_length,
                                       uint8_t * const p_cipher);

    /**
     * Decrypts with RSAES-PKCS1-v1_5.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Pointer to wrapped key of RSA private key.
     * @param[in]     p_cipher              Pointer to ciphertext. The length is as same as the key length.
     * @param[out]    p_plain               Pointer to destination of plaintext.
     * @param[out]    p_plain_length        Pointer to destination of actual plaintext length.
     * @param[in]     plain_buffer_length   Length of plaintext destination. It must be equal to or greater than *p_plain_length.
     */
    fsp_err_t (* rsaesPkcs1V15Decrypt)(rsip_ctrl_t * const p_ctrl,
                                       rsip_wrapped_key_t const * const p_wrapped_private_key,
                                       uint8_t const * const p_cipher, uint8_t * const p_plain,
                                       uint32_t * const p_plain_length, uint32_t const plain_buffer_length);

    /**
     * Encrypts plaintext with RSAES-OAEP.
     *
     * @param[in,out] p_ctrl                   Pointer to control block.
     * @param[in]     p_wrapped_public_key     Pointer to wrapped key of RSA public key.
     * @param[in]     hash_function            Hash function for label.
     * @param[in]     mask_generation_function Mask generation function in EME-OAEP encoding.
     * @param[in]     p_label                  Pointer to label. If label_length != 0, p_label must not be NULL.
     * @param[in]     label_length             Length of label. Please set 0 or more.
     * @param[in]     p_plain                  Pointer to plaintext.
     * @param[in]     plain_length             Length of plaintext.
     * @param[out]    p_cipher                 Pointer to destination of ciphertext. The length is as same as the key length.
     */
    fsp_err_t (* rsaesOaepEncrypt)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                                   rsip_hash_type_t const hash_function, rsip_mgf_type_t const mask_generation_function,
                                   uint8_t const * const p_label,
                                   uint32_t const label_length, uint8_t const * const p_plain,
                                   uint32_t const plain_length, uint8_t * const p_cipher);

    /**
     * Decrypts ciphertext with RSAES-OAEP.
     *
     * @param[in,out] p_ctrl                   Pointer to control block.
     * @param[in]     p_wrapped_private_key    Pointer to wrapped key of RSA private key.
     * @param[in]     hash_function            Hash function for label.
     * @param[in]     mask_generation_function Mask generation function in EME-OAEP encoding.
     * @param[in]     p_label                  Pointer to label. If label_length != 0, p_label must not be NULL.
     * @param[in]     label_length             Length of label. Please set 0 or more.
     * @param[in]     p_cipher                 Pointer to ciphertext. The length is as same as the key length.
     * @param[out]    p_plain                  Pointer to destination of plaintext.
     * @param[out]    p_plain_length           Pointer to destination of actual plaintext length.
     * @param[in]     plain_buffer_length      Length of plaintext destination. It must be equal to or greater than
     *                                         *p_plain_length.
     */
    fsp_err_t (* rsaesOaepDecrypt)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                                   rsip_hash_type_t const hash_function, rsip_mgf_type_t const mask_generation_function,
                                   uint8_t const * const p_label,
                                   uint32_t const label_length, uint8_t const * const p_cipher, uint8_t * const p_plain,
                                   uint32_t * const p_plain_length, uint32_t const plain_buffer_length);

    /**
     * Signs message with RSASSA-PKCS1-v1_5.
     *
     * @param[in,out] p_ctrl                Pointer to control block.
     * @param[in]     p_wrapped_private_key Pointer to wrapped key of RSA private key.
     * @param[in]     hash_function         Hash function in EMSA-PKCS1-v1_5.
     * @param[in]     p_hash                Pointer to input hash.
     * @param[out]    p_signature           Pointer to destination of signature.
     */
    fsp_err_t (* rsassaPkcs1V15Sign)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                                     rsip_hash_type_t const hash_function, uint8_t const * const p_hash,
                                     uint8_t * const p_signature);

    /**
     * Verifies signature with RSASSA-PKCS1-v1_5.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of RSA public key.
     * @param[in]     hash_function        Hash function in EMSA-PKCS1-v1_5.
     * @param[in]     p_hash               Pointer to input hash.
     * @param[in]     p_signature          Pointer to input signature.
     */
    fsp_err_t (* rsassaPkcs1V15Verify)(rsip_ctrl_t * const p_ctrl,
                                       rsip_wrapped_key_t const * const p_wrapped_public_key,
                                       rsip_hash_type_t const hash_function,
                                       uint8_t const * const p_hash, uint8_t const * const p_signature);

    /**
     * Signs message with RSASSA-PSS.
     *
     * @param[in,out] p_ctrl                   Pointer to control block.
     * @param[in]     p_wrapped_private_key    Pointer to wrapped key of RSA private key.
     * @param[in]     hash_function            Hash function in EMSA-PSS-ENCODE.
     * @param[in]     mask_generation_function Mask generation function in EMSA-PSS-ENCODE.
     * @param[in]     salt_length              Salt length.
     * @param[in]     p_hash                   Pointer to input hash.
     * @param[out]    p_signature              Pointer to destination of signature.
     */
    fsp_err_t (* rsassaPssSign)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_private_key,
                                rsip_hash_type_t const hash_function, rsip_mgf_type_t const mask_generation_function,
                                uint32_t const salt_length,
                                uint8_t const * const p_hash, uint8_t * const p_signature);

    /**
     * Verifies signature with RSASSA-PSS.
     *
     * @param[in,out] p_ctrl                   Pointer to control block.
     * @param[in]     p_wrapped_public_key     Pointer to wrapped key of RSA public key.
     * @param[in]     hash_function            Hash function in EMSA-PSS-VERIFY.
     * @param[in]     mask_generation_function Mask generation function in EMSA-PSS-VERIFY.
     * @param[in]     salt_length              Salt length.
     * @param[in]     p_hash                   Pointer to input hash.
     * @param[in]     p_signature              Pointer to input signature.
     */
    fsp_err_t (* rsassaPssVerify)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                                  rsip_hash_type_t const hash_function, rsip_mgf_type_t const mask_generation_function,
                                  uint32_t const salt_length,
                                  uint8_t const * const p_hash, uint8_t const * const p_signature);

    /**
     * Generates SHA message digest.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     hash_type      Generating hash type.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     * @param[out]    p_digest       Pointer to destination of message digest. The length depends on hash type.
     */
    fsp_err_t (* shaCompute)(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type,
                             uint8_t const * const p_message, uint32_t const message_length, uint8_t * const p_digest);

    /**
     * Prepares a SHA generation.
     *
     * @param[in,out] p_ctrl    Pointer to control block.
     * @param[in]     hash_type Generating hash type.
     */
    fsp_err_t (* shaInit)(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type);

    /**
     * Inputs message.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     */
    fsp_err_t (* shaUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message, uint32_t const message_length);

    /**
     * Finalizes a SHA generation.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_digest Pointer to destination of message digest. The length depends on hash type.
     */
    fsp_err_t (* shaFinish)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_digest);

    /**
     * Suspend SHA generation.
     * This API allows you to suspend processing, for example, if you are in the middle of computing digest value for successive chunks of the message and need to perform another process.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_handle Pointer to destination of SHA control block.
     */
    fsp_err_t (* shaSuspend)(rsip_ctrl_t * const p_ctrl, rsip_sha_handle_abstractor_t * const p_handle);

    /**
     * Resume SHA generation.
     * This API allows you to resume a process that has been suspended by R_RSIP_SHA_Suspend() API.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[in]     p_handle Pointer to SHA control block.
     */
    fsp_err_t (* shaResume)(rsip_ctrl_t * const p_ctrl, rsip_sha_handle_abstractor_t const * const p_handle);

    /**
     * Generates HMAC.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     * @param[out]    p_mac          Pointer to destination of message digest. The length depends on MAC type.
     */
    fsp_err_t (* hmacCompute)(rsip_ctrl_t * const p_ctrl, const rsip_wrapped_key_t * p_wrapped_key,
                              uint8_t const * const p_message, uint32_t const message_length, uint8_t * const p_mac);

    /**
     * Verifies HMAC.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_wrapped_key  Pointer to wrapped key of HMAC key.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     * @param[in]     p_mac          Pointer to MAC. The length depends on mac_length.
     * @param[in]     mac_length     Byte length of MAC.
     */
    fsp_err_t (* hmacVerify)(rsip_ctrl_t * const p_ctrl, const rsip_wrapped_key_t * p_wrapped_key,
                             uint8_t const * const p_message, uint32_t const message_length,
                             uint8_t const * const p_mac,
                             uint32_t const mac_length);

    /**
     * Prepares a HMAC generation.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     p_wrapped_key Pointer to wrapped key of HMAC key.
     */
    fsp_err_t (* hmacInit)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key);

    /**
     * Inputs message.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     */
    fsp_err_t (* hmacUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                             uint32_t const message_length);

    /**
     * Finalizes a HMAC generation.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_mac    Pointer to destination of message digest. The length depends on MAC type.
     */
    fsp_err_t (* hmacSignFinish)(rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac);

    /**
     * Finalizes a HMAC verification.
     *
     * @param[in,out] p_ctrl     Pointer to control block.
     * @param[in]     p_mac      Pointer to MAC. The length depends on mac_length.
     * @param[in]     mac_length Byte length of MAC.
     */
    fsp_err_t (* hmacVerifyFinish)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_mac, uint32_t const mac_length);

    /**
     * Suspend HMAC generation.
     * This API allows you to suspend processing, for example, if you are in the middle of computing HMAC for successive chunks of the message and need to perform another process.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_handle Pointer to destination of HMAC control block.
     */
    fsp_err_t (* hmacSuspend)(rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_abstractor_t * const p_handle);

    /**
     * Resume HMAC generation.
     * This API allows you to resume a process that has been suspended by R_RSIP_HMAC_Suspend() API.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[in]     p_handle Pointer to HMAC control block.
     */
    fsp_err_t (* hmacResume)(rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_abstractor_t const * const p_handle);

    /**
     * Verifies a public key certificate with ECDSA.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_wrapped_public_key Pointer to wrapped key of ECC public key.
     * @param[in]     p_hash               Pointer to hash value. The length is as same as the key length.
     * @param[in]     p_signature          Pointer to signature (r, s). The length is twice as long as the key length.
     */
    fsp_err_t (* pkiEcdsaCertVerify)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_public_key,
                                     uint8_t const * const p_hash, uint8_t const * const p_signature);

    /**
     * Exports verified certificate information stored in this driver.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[out]    p_verified_cert_info Pointer to certificate to be signed
     */
    fsp_err_t (* pkiVerifiedCertInfoExport)(rsip_ctrl_t * const                          p_ctrl,
                                            rsip_verified_cert_info_abstractor_t * const p_verified_cert_info);

    /**
     * Imports verified certificate information.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_verified_cert_info Pointer to certificate to be signed
     */
    fsp_err_t (* pkiVerifiedCertInfoImport)(rsip_ctrl_t * const                                p_ctrl,
                                            rsip_verified_cert_info_abstractor_t const * const p_verified_cert_info);

    /**
     * Wraps the public key in the verified public key certificate.
     *
     * @param[in,out] p_ctrl               Pointer to control block.
     * @param[in]     p_cert               Pointer to certificate.
     * @param[in]     cert_length          Certificate length.
     * @param[in]     p_key_param1         Pointer to start address of the public key parameter in certificate.
     *                                     - [ECC] Qx
     * @param[in]     key_param1_length    Length of key_param1 stored in the certificate.
     * @param[in]     p_key_param2         Pointer to start address of the public key parameter in certificate.
     *                                     - [ECC] Qy
     * @param[in]     key_param2_length    Length of key_param2 stored in the certificate.
     * @param[in]     hash_function        The hash function used when verifying certificate signature.
     * @param[in,out] p_wrapped_public_key Pointer to wrapped key of public key in the certificate.
     */
    fsp_err_t (* pkiCertKeyImport)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_cert, uint32_t const cert_length,
                                   uint8_t const * const p_key_param1, uint32_t const key_param1_length,
                                   uint8_t const * const p_key_param2,
                                   uint32_t const key_param2_length, rsip_hash_type_t const hash_function,
                                   rsip_wrapped_key_t * const p_wrapped_public_key);

    /**
     * Prepares a SHA generation.
     *
     * @param[in,out] p_ctrl    Pointer to control block.
     * @param[in]     hash_type Generating hash type.
     */
    fsp_err_t (* kdfShaInit)(rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type);

    /**
     * Inputs wrapped ECDH secret as a message.
     *
     * @param[in,out] p_ctrl           Pointer to control block.
     * @param[in]     p_wrapped_secret Pointer to wrapped secret.
     */
    fsp_err_t (* kdfShaEcdhSecretUpdate)(rsip_ctrl_t * const                            p_ctrl,
                                         rsip_wrapped_secret_abstractor_t const * const p_wrapped_secret);

    /**
     * Inputs message.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     */
    fsp_err_t (* kdfShaUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                               uint32_t const message_length);

    /**
     * Finalizes a SHA operation and generate DKM (Derived Keying Material).
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[out]    p_wrapped_dkm Pointer to destination of wrapped DKM.
     */
    fsp_err_t (* kdfShaFinish)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t * const p_wrapped_dkm);

    /**
     * Suspend SHA generation.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_handle Pointer to destination of KDF SHA control block.
     */
    fsp_err_t (* kdfShaSuspend)(rsip_ctrl_t * const p_ctrl, rsip_kdf_sha_handle_abstractor_t * const p_handle);

    /**
     * Resume SHA generation.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[in]     p_handle Pointer to KDF SHA control block.
     */
    fsp_err_t (* kdfShaResume)(rsip_ctrl_t * const p_ctrl, rsip_kdf_sha_handle_abstractor_t const * const p_handle);

    /**
     * Converts wrapped Derived Keying Material (DKM) to HMAC key for KDF.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     p_wrapped_dkm Pointer to wrapped DKM.
     * @param[in]     key_length    Length of HMAC key to be extracted from DKM.
     * @param[in,out] p_wrapped_key Pointer to destination wrapped HMAC key for KDF.
     */
    fsp_err_t (* kdfHmacDkmKeyImport)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                      uint32_t const key_length, rsip_wrapped_key_t * const p_wrapped_key);

    /**
     * Converts wrapped ECDH secret to wrapped HMAC key for KDF.
     *
     * @param[in,out] p_ctrl           Pointer to control block.
     * @param[in]     p_wrapped_secret Pointer to wrapped secret.
     * @param[in,out] p_wrapped_key    Pointer to destination wrapped HMAC key for KDF.
     */
    fsp_err_t (* kdfHmacEcdhSecretKeyImport)(rsip_ctrl_t * const                            p_ctrl,
                                             rsip_wrapped_secret_abstractor_t const * const p_wrapped_secret,
                                             rsip_wrapped_key_t * const                     p_wrapped_key);

    /**
     * Prepares a HMAC generation.
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     p_wrapped_key Pointer to wrapped key of HMAC key.
     */
    fsp_err_t (* kdfHmacInit)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key);

    /**
     * Inputs wrapped Derived Keying Material (DKM) as a message.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_wrapped_dkm  Pointer to wrapped DKM.
     */
    fsp_err_t (* kdfHmacDkmUpdate)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t const * const p_wrapped_dkm);

    /**
     * Inputs wrapped ECDH secret as a message.
     *
     * @param[in,out] p_ctrl           Pointer to control block.
     * @param[in]     p_wrapped_secret Pointer to wrapped secret.
     */
    fsp_err_t (* kdfHmacEcdhSecretUpdate)(rsip_ctrl_t * const                            p_ctrl,
                                          rsip_wrapped_secret_abstractor_t const * const p_wrapped_secret);

    /**
     * Inputs message.
     *
     * @param[in,out] p_ctrl         Pointer to control block.
     * @param[in]     p_message      Pointer to message. The length is message_length.
     * @param[in]     message_length Byte length of message (0 or more bytes).
     */
    fsp_err_t (* kdfHmacUpdate)(rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                                uint32_t const message_length);

    /**
     * Finalizes a HMAC generation.
     *
     * @param[in,out] p_ctrl Pointer to control block.
     * @param[out]    p_wrapped_dkm  Pointer to destination of wrapped Derived Keying Material (DKM).
     */
    fsp_err_t (* kdfHmacSignFinish)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t * const p_wrapped_dkm);

    /**
     * Suspends HMAC operation.
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[out]    p_handle Pointer to destination of KDF HMAC control block.
     */
    fsp_err_t (* kdfHmacSuspend)(rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_abstractor_t * const p_handle);

    /**
     * Resumes HMAC operation suspended by R_RSIP_KDF_HMAC_Suspend().
     *
     * @param[in,out] p_ctrl   Pointer to control block.
     * @param[in]     p_handle Pointer to KDF HMAC control block.
     */
    fsp_err_t (* kdfHmacResume)(rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_abstractor_t const * const p_handle);

    /**
     * Concatenates two wrapped derived keying materials (DKMs).
     *
     * @param[in,out] p_wrapped_dkm1             Pointer to first DKM (DKM1).
     * @param[in]     p_wrapped_dkm2             Pointer to second DKM (DKM2).
     * @param[in]     wrapped_dkm1_buffer_length Length of wrapped_dkm1 buffer.
     *                                           It must be equal to or greater than DKM1 || DKM2.
     */
    fsp_err_t (* kdfDkmConcatenate)(rsip_wrapped_dkm_t * const       p_wrapped_dkm1,
                                    rsip_wrapped_dkm_t const * const p_wrapped_dkm2,
                                    uint32_t const                   wrapped_dkm1_buffer_length);

    /**
     * Outputs a wrapped key from Derived Keying Material (DKM).
     *
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     p_wrapped_dkm Pointer to wrapped DKM.
     * @param[in]     position      Start position of output key value in the DKM.
     * @param[in,out] p_wrapped_key Pointer to destination of wrapped key.
     */
    fsp_err_t (* kdfDerivedKeyImport)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                      uint32_t const position, rsip_wrapped_key_t * const p_wrapped_key);

    /**
     * Outputs a initial vector from Derived Keying Material (DKM).
     *
     * @param[in,out] p_ctrl                   Pointer to control block.
     * @param[in]     p_wrapped_dkm            Pointer to wrapped DKM.
     * @param[in]     initial_vector_type      Initial vector type.
     * @param[in]     position                 Start position of output data value in the DKM.
     * @param[in]     p_tls_sequence_num       TLS sequence number. This argument is valid only for TLS-related data type.
     * @param[out]    p_wrapped_initial_vector Pointer to destination of wrapped initial vector.
     */
    fsp_err_t (* kdfDerivedIvWrap)(rsip_ctrl_t * const p_ctrl, rsip_wrapped_dkm_t const * const p_wrapped_dkm,
                                   rsip_initial_vector_type_t const initial_vector_type, uint32_t const position,
                                   uint8_t const * const p_tls_sequence_num, uint8_t * const p_wrapped_initial_vector);

    /**
     * Initialize on-the-fly decryption on RSIP.
     * @param[in,out] p_ctrl        Pointer to control block.
     * @param[in]     channel       Channel number.
     * @param[in]     p_wrapped_key Pointer to wrapped AES key.
     * @param[in]     p_seed        Pointer to seed.
     */
    fsp_err_t (* otfInit)(rsip_ctrl_t * const p_ctrl, rsip_otf_channel_t const channel,
                          rsip_wrapped_key_t * const p_wrapped_key, uint8_t const * const p_seed);
} rsip_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rsip_instance
{
    rsip_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    rsip_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    rsip_api_t const * p_api;          ///< Pointer to the API structure for this instance
} rsip_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RSIP_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED_API)
 **********************************************************************************************************************/
