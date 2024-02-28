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
#define R_RSIP_AES256_KEY_INDEX_WORD_SIZE          (13U)

/* For RSA operation. */
#define R_RSIP_RSA2048_PUBLIC_KEY_INDEX_WORD_SIZE  (73U)
#define R_RSIP_RSA3072_PUBLIC_KEY_INDEX_WORD_SIZE  (105U)
#define R_RSIP_RSA4096_PUBLIC_KEY_INDEX_WORD_SIZE  (137U)
#define R_RSIP_RSA2048_PRIVATE_KEY_INDEX_WORD_SIZE (133U)
#define R_RSIP_RSA3072_PRIVATE_KEY_INDEX_WORD_SIZE (197U)
#define R_RSIP_RSA4096_PRIVATE_KEY_INDEX_WORD_SIZE (261U)

/* For ECC operation. */
#define R_RSIP_ECCP384_PUBLIC_KEY_INDEX_WORD_SIZE  (29U)
#define R_RSIP_ECCP384_PRIVATE_KEY_INDEX_WORD_SIZE (17U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Key injection type. */
typedef enum e_rsip_key_injection_type
{
    RSIP_KEY_INJECTION_TYPE_ENCRYPTED = 0, ///< Input encrypted user key
    RSIP_KEY_INJECTION_TYPE_PLAIN     = 1, ///< Input plain user key
} rsip_key_injection_type_t;


/*******************************************************************************************************************//**
 * @cond
 **********************************************************************************************************************/

/** AES128/256 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_aes_wrapped_key
{
    uint32_t type;                                      ///< Key type
    uint32_t value[R_RSIP_AES256_KEY_INDEX_WORD_SIZE];  ///< Wrapped key value
} rsip_aes_wrapped_key_t;

/** RSA 2048bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa2048_public_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA2048_PUBLIC_KEY_INDEX_WORD_SIZE];  ///< Wrapped key value
} rsip_rsa2048_public_wrapped_key_t;

/** RSA 3072bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa3072_public_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA3072_PUBLIC_KEY_INDEX_WORD_SIZE];  ///< Wrapped key value
} rsip_rsa3072_public_wrapped_key_t;

/** RSA 4096bit public wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_rsa4096_public_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_RSA4096_PUBLIC_KEY_INDEX_WORD_SIZE];  ///< Wrapped key value
} rsip_rsa4096_public_wrapped_key_t;

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

/** ECC 256/384 public wrapped key data structure */
typedef struct rsip_ecc_public_wrapped_key
{
    uint32_t type;                                             ///< Key type
    uint32_t value[R_RSIP_ECCP384_PUBLIC_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_ecc_public_wrapped_key_t;

/** ECC 256/384 private wrapped key data structure */
typedef struct rsip_ecc_private_wrapped_key
{
    uint32_t type;                                              ///< Key type
    uint32_t value[R_RSIP_ECCP384_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_ecc_private_wrapped_key_t;

/*******************************************************************************************************************//**
 * @endcond
 **********************************************************************************************************************/

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
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key);

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
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key);

    /** This API outputs 2048-bit RSA wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           2048-bit RSA wrapped public key
     */
    fsp_err_t (* RSA2048_InitialPublicKeyWrap)(rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa2048_public_wrapped_key_t * const p_wrapped_key);

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
    fsp_err_t (* RSA2048_InitialPrivateKeyWrap)(rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa2048_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 3072-bit RSA wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           3072-bit RSA wrapped public key
     */
    fsp_err_t (* RSA3072_InitialPublicKeyWrap)(rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa3072_public_wrapped_key_t * const p_wrapped_key);

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
    fsp_err_t (* RSA3072_InitialPrivateKeyWrap)(rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa3072_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 4096-bit RSA wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           4096-bit RSA wrapped public key
     */
    fsp_err_t (* RSA4096_InitialPublicKeyWrap)(rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa4096_public_wrapped_key_t * const p_wrapped_key);

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
    fsp_err_t (* RSA4096_InitialPrivateKeyWrap)(rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa4096_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
     */
    fsp_err_t (* ECC_secp256r1_InitialPublicKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                     uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const           p_initial_vector,
                                                     uint8_t const * const           p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

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
                                                      uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const           p_initial_vector,
                                                      uint8_t const * const           p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 384-bit ECC wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           384-bit ECC wrapped public key
     */
    fsp_err_t (* ECC_secp384r1_InitialPublicKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                     uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const           p_initial_vector,
                                                     uint8_t const * const           p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

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
                                                      uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const           p_initial_vector,
                                                      uint8_t const * const           p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
     */
    fsp_err_t (* ECC_secp256k1_InitialPublicKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                     uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const           p_initial_vector,
                                                     uint8_t const * const           p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

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
                                                      uint8_t const * const           p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const           p_initial_vector,
                                                      uint8_t const * const           p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit brainpool ECC wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
     */
    fsp_err_t (* ECC_brainpoolP256r1_InitialPublicKeyWrap)(rsip_key_injection_type_t const       key_injection_type,
                                                           uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                 p_initial_vector,
                                                           uint8_t const * const                 p_user_key,
                                                           rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

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
    fsp_err_t (* ECC_brainpoolP256r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const        key_injection_type,
                                                            uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 384-bit brainpool ECC wrapped public key.
     *
     * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
     * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
     *                                                     When key injection type is plain, this is not required and any value can be specified.
     * @param[in]  p_user_key                              User key. If key injection type is not plain, it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           384-bit ECC wrapped public key
     */
    fsp_err_t (* ECC_brainpoolP384r1_InitialPublicKeyWrap)(rsip_key_injection_type_t const       key_injection_type,
                                                           uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                 p_initial_vector,
                                                           uint8_t const * const                 p_user_key,
                                                           rsip_ecc_public_wrapped_key_t * const p_wrapped_key);

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
    fsp_err_t (* ECC_brainpoolP384r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const        key_injection_type,
                                                            uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

} rsip_key_injection_api_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_RSIP_KEY_INJECTION_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION_API)
 **********************************************************************************************************************/
