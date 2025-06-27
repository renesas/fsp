/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SECURITY_INTERFACES
 * @defgroup RSIP_KEY_INJECTION_API RSIP key injection Interface
 * @brief Interface for key injection by Renesas Secure IP (RSIP) functions.
 *
 * @section RSIP_API_Summary Summary
 * The RSIP key injection interface provides RSIP functionality.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_KEY_INJECTION_API_H
#define R_RSIP_KEY_INJECTION_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* For AES operation. */
#define R_RSIP_AES256_KEY_INDEX_WORD_SIZE             (13U)
#define R_RSIP_AES256_XTS_KEY_INDEX_WORD_SIZE         (21U)

/* For CHACHA operation. */
#define R_RSIP_CHACHA20_KEY_INDEX_WORD_SIZE           (13U)

/* For HMAC operation. */
#define R_RSIP_HMAC_SHA224_KEY_INDEX_WORD_SIZE        (13U)
#define R_RSIP_HMAC_SHA256_KEY_INDEX_WORD_SIZE        (13U)
#define R_RSIP_HMAC_SHA384_KEY_INDEX_WORD_SIZE        (17U)
#define R_RSIP_HMAC_SHA512_KEY_INDEX_WORD_SIZE        (21U)
#define R_RSIP_HMAC_SHA512_224_KEY_INDEX_WORD_SIZE    (21U)
#define R_RSIP_HMAC_SHA512_256_KEY_INDEX_WORD_SIZE    (21U)

/* For RSA operation. */
#define R_RSIP_RSA2048_PRIVATE_KEY_INDEX_WORD_SIZE    (133U)
#define R_RSIP_RSA3072_PRIVATE_KEY_INDEX_WORD_SIZE    (197U)
#define R_RSIP_RSA4096_PRIVATE_KEY_INDEX_WORD_SIZE    (261U)

/* For ECC operation. */
#define R_RSIP_ECCP384_PRIVATE_KEY_INDEX_WORD_SIZE    (17U)
#define R_RSIP_ECCP521_PRIVATE_KEY_INDEX_WORD_SIZE    (25U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Key injection type. */
typedef enum e_rsip_key_injection_type
{
    RSIP_KEY_INJECTION_TYPE_ENCRYPTED = 0, ///< Input encrypted user key
    RSIP_KEY_INJECTION_TYPE_PLAIN     = 1, ///< Input plain user key
} rsip_key_injection_type_t;

/** AES128/256 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_aes_wrapped_key
{
    uint32_t type;                                         ///< Key type
    uint32_t value[R_RSIP_AES256_XTS_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_aes_wrapped_key_t;

/** CHACHA20 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_chacha20_wrapped_key
{
    uint32_t type;                                       ///< Key type
    uint32_t value[R_RSIP_CHACHA20_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_chacha20_wrapped_key_t;

/** RSA 2048bit private wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa2048_private_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA2048_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_rsa2048_private_wrapped_key_t;

/** RSA 3072bit private wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa3072_private_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA3072_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_rsa3072_private_wrapped_key_t;

/** RSA 4096bit private wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa4096_private_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA4096_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_rsa4096_private_wrapped_key_t;

/** ECC 256/384/512/521 private wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_ecc_private_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_ECCP521_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_ecc_private_wrapped_key_t;

/** HMAC 256/342/512 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_hmac_sha_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_HMAC_SHA512_KEY_INDEX_WORD_SIZE];     ///< Wrapped key value
} rsip_hmac_sha_wrapped_key_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_rsip_key_injection_api
{
    /** This API outputs 128-bit AES wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           128-bit AES wrapped key
     */
    fsp_err_t (* AES128_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 192-bit AES wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           192-bit AES wrapped key
     */
    fsp_err_t (* AES192_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit AES wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit AES wrapped key
     */
    fsp_err_t (* AES256_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 128-bit AES-XTS wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           128-bit AES-XTS wrapped key
     */
    fsp_err_t (* AES128_XTS_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                            uint8_t const * const p_wrapped_user_factory_programming_key,
                                            uint8_t const * const p_initial_vector,
                                            uint8_t const * const p_user_key, rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit AES-XTS wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit AES-XTS wrapped key
     */
    fsp_err_t (* AES256_XTS_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                            uint8_t const * const p_wrapped_user_factory_programming_key,
                                            uint8_t const * const p_initial_vector,
                                            uint8_t const * const p_user_key, rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ChaCha20 wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ChaCha20 wrapped key
     */
    fsp_err_t (* ChaCha20_InitialKeyWrap)(rsip_key_injection_type_t const     key_injection_type,
                                          uint8_t const * const               p_wrapped_user_factory_programming_key,
                                          uint8_t const * const               p_initial_vector,
                                          uint8_t const * const               p_user_key,
                                          rsip_chacha20_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 2048-bit RSA wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           2048-bit RSA wrapped private key
     */
    fsp_err_t (* RSA2048_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const
                                                p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa2048_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 3072-bit RSA wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           3072-bit RSA wrapped private key
     */
    fsp_err_t (* RSA3072_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const
                                                p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa3072_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 4096-bit RSA wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           4096-bit RSA wrapped private key
     */
    fsp_err_t (* RSA4096_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const
                                                p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa4096_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp256r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                      uint8_t const * const
                                                      p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 384-bit ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           384-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp384r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                      uint8_t const * const
                                                      p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 521-bit ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           521-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp521r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                      uint8_t const * const
                                                      p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp256k1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                      uint8_t const * const
                                                      p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit brainpool ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_brainpoolP256r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                            uint8_t const * const
                                                            p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 384-bit brainpool ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           384-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_brainpoolP384r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                            uint8_t const * const
                                                            p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 512-bit brainpool ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           512-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_brainpoolP512r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                            uint8_t const * const
                                                            p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit Edwards curve ECC wrapped private key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_Ed25519_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                    uint8_t const * const
                                                    p_wrapped_user_factory_programming_key,
                                                    uint8_t const * const                  p_initial_vector,
                                                    uint8_t const * const                  p_user_key,
                                                    rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 224-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           224-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA224_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA256_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 384-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           384-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA384_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 512-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           512-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA512_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 512/224-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           512/224-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA512_224_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 512/256-bit HMAC-SHA wrapped key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           512/256-bit HMAC-SHA wrapped key
     */
    fsp_err_t (* HMAC_SHA512_256_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key, rsip_hmac_sha_wrapped_key_t * const p_wrapped_key);

} rsip_key_injection_api_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RSIP_KEY_INJECTION_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION_API)
 **********************************************************************************************************************/
