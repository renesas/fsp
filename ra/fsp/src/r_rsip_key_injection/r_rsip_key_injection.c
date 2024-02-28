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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_key_injection.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Key update. */
#define R_RSIP_INSTALL_KEY_RING_INDEX    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Key Inst Data Size. */
typedef enum e_rsip_word_size_oem_key_inst_data
{
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128                          = 8U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES192                          = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256                          = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PUBLIC_KEY              = 72U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PRIVATE_KEY             = 132U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PUBLIC_KEY              = 104U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PRIVATE_KEY             = 196U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PUBLIC_KEY              = 136U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PRIVATE_KEY             = 260U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PUBLIC_KEY        = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY       = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PUBLIC_KEY        = 28U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PRIVATE_KEY       = 16U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PUBLIC_KEY  = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PUBLIC_KEY  = 28U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PRIVATE_KEY = 16U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PUBLIC_KEY        = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY       = 12U,
} e_rsip_word_size_oem_key_inst_data_t;

/* OEM Command */
typedef enum e_rsip_oem_cmd
{
    RSIP_OEM_CMD_INVALID                     = 0U,
    RSIP_OEM_CMD_AES128                      = 5U,
    RSIP_OEM_CMD_AES192                      = 6U,
    RSIP_OEM_CMD_AES256                      = 7U,
    RSIP_OEM_CMD_RSA2048_PUBLIC              = 12U,
    RSIP_OEM_CMD_RSA2048_PRIVATE             = 13U,
    RSIP_OEM_CMD_RSA3072_PUBLIC              = 14U,
    RSIP_OEM_CMD_RSA3072_PRIVATE             = 15U,
    RSIP_OEM_CMD_RSA4096_PUBLIC              = 16U,
    RSIP_OEM_CMD_RSA4096_PRIVATE             = 17U,
    RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC        = 22U,
    RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE       = 23U,
    RSIP_OEM_CMD_ECC_SECP384R1_PUBLIC        = 24U,
    RSIP_OEM_CMD_ECC_SECP384R1_PRIVATE       = 25U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC  = 28U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE = 29U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PUBLIC  = 30U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PRIVATE = 31U,
    RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC        = 34U,
    RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE       = 35U,
} rsip_oem_cmd_t;

/* Key types */
typedef enum e_rsip_key_type
{
    RSIP_KEY_TYPE_INVALID,                      ///< Invalid key
    RSIP_KEY_TYPE_AES_128,                      ///< AES-128
    RSIP_KEY_TYPE_AES_192,                      ///< AES-192
    RSIP_KEY_TYPE_AES_256,                      ///< AES-256
    RSIP_KEY_TYPE_RSA_2048_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_2048_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_RSA_3072_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_3072_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_RSA_4096_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_4096_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC,         ///< secp256r1 public key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE,        ///< secp256r1 private key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC,         ///< secp384r1 public key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE,        ///< secp384r1 private key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC,   ///< brainpool256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE,  ///< brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC,   ///< brainpool256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE,  ///< brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC,         ///< secp256k1 public key
    RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE,        ///< secp256k1 private key
    RSIP_KEY_TYPE_MAKE_ENUM_LONG = 0xFFFFFFFFUL // Make this enum 32-bit data
} rsip_key_type_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const rsip_key_injection_api_t g_rsip_key_injection_on_rsip =
{
    .AES128_InitialKeyWrap                     = R_RSIP_AES128_InitialKeyWrap,
    .AES256_InitialKeyWrap                     = R_RSIP_AES256_InitialKeyWrap,
    .RSA2048_InitialPublicKeyWrap              = R_RSIP_RSA2048_InitialPublicKeyWrap,
    .RSA2048_InitialPrivateKeyWrap             = R_RSIP_RSA2048_InitialPrivateKeyWrap,
    .RSA3072_InitialPublicKeyWrap              = R_RSIP_RSA3072_InitialPublicKeyWrap,
    .RSA3072_InitialPrivateKeyWrap             = R_RSIP_RSA3072_InitialPrivateKeyWrap,
    .RSA4096_InitialPublicKeyWrap              = R_RSIP_RSA4096_InitialPublicKeyWrap,
    .RSA4096_InitialPrivateKeyWrap             = R_RSIP_RSA4096_InitialPrivateKeyWrap,
    .ECC_secp256r1_InitialPublicKeyWrap        = R_RSIP_ECC_secp256r1_InitialPublicKeyWrap,
    .ECC_secp256r1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp256r1_InitialPrivateKeyWrap,
    .ECC_secp384r1_InitialPublicKeyWrap        = R_RSIP_ECC_secp384r1_InitialPublicKeyWrap,
    .ECC_secp384r1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp384r1_InitialPrivateKeyWrap,
    .ECC_secp256k1_InitialPublicKeyWrap        = R_RSIP_ECC_secp256k1_InitialPublicKeyWrap,
    .ECC_secp256k1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp256k1_InitialPrivateKeyWrap,
    .ECC_brainpoolP256r1_InitialPublicKeyWrap  = R_RSIP_ECC_brainpoolP256r1_InitialPublicKeyWrap,
    .ECC_brainpoolP256r1_InitialPrivateKeyWrap = R_RSIP_ECC_brainpoolP256r1_InitialPrivateKeyWrap,
    .ECC_brainpoolP384r1_InitialPublicKeyWrap  = R_RSIP_ECC_brainpoolP384r1_InitialPublicKeyWrap,
    .ECC_brainpoolP384r1_InitialPrivateKeyWrap = R_RSIP_ECC_brainpoolP384r1_InitialPrivateKeyWrap,
};

/*******************************************************************************************************************//**
 * @addtogroup RSIP_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API generates 128-bit AES key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES128_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES128);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128 - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_128;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 192-bit AES key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           192-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES192_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES192);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES192;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES192 - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_192;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit AES key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES256_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES256);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256 - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_256;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 2048-bit RSA public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           2048-bit RSA wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA2048_InitialPublicKeyWrap (rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa2048_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA2048_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_2048_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 2048-bit RSA private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           2048-bit RSA wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA2048_InitialPrivateKeyWrap (rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa2048_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA2048_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_2048_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 3072-bit RSA public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           3072-bit RSA wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA3072_InitialPublicKeyWrap (rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa3072_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA3072_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_3072_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 3072-bit RSA private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           3072-bit RSA wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA3072_InitialPrivateKeyWrap (rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa3072_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA3072_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_3072_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 4096-bit RSA public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           4096-bit RSA wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA4096_InitialPublicKeyWrap (rsip_key_injection_type_t const           key_injection_type,
                                               uint8_t const * const                     p_wrapped_user_factory_programming_key,
                                               uint8_t const * const                     p_initial_vector,
                                               uint8_t const * const                     p_user_key,
                                               rsip_rsa4096_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA4096_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_4096_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 4096-bit RSA private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           4096-bit RSA wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA4096_InitialPrivateKeyWrap (rsip_key_injection_type_t const            key_injection_type,
                                                uint8_t const * const                      p_wrapped_user_factory_programming_key,
                                                uint8_t const * const                      p_initial_vector,
                                                uint8_t const * const                      p_user_key,
                                                rsip_rsa4096_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA4096_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_RSA_4096_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp256r1_InitialPublicKeyWrap (rsip_key_injection_type_t const       key_injection_type,
                                                     uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                 p_initial_vector,
                                                     uint8_t const * const                 p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp256r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                      uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 384-bit ECC public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           384-bit ECC wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp384r1_InitialPublicKeyWrap (rsip_key_injection_type_t const       key_injection_type,
                                                     uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                 p_initial_vector,
                                                     uint8_t const * const                 p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP384R1_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 384-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           384-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp384r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                      uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP384R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp256k1_InitialPublicKeyWrap (rsip_key_injection_type_t const       key_injection_type,
                                                     uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                     uint8_t const * const                 p_initial_vector,
                                                     uint8_t const * const                 p_user_key,
                                                     rsip_ecc_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp256k1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                      uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit brainpool ECC public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_brainpoolP256r1_InitialPublicKeyWrap (rsip_key_injection_type_t const       key_injection_type,
                                                           uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                 p_initial_vector,
                                                           uint8_t const * const                 p_user_key,
                                                           rsip_ecc_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit brainpool ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_brainpoolP256r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                            uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 384-bit brainpool ECC public key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           384-bit ECC wrapped public key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_brainpoolP384r1_InitialPublicKeyWrap (rsip_key_injection_type_t const       key_injection_type,
                                                           uint8_t const * const                 p_wrapped_user_factory_programming_key,
                                                           uint8_t const * const                 p_initial_vector,
                                                           uint8_t const * const                 p_user_key,
                                                           rsip_ecc_public_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PUBLIC);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PUBLIC_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PUBLIC_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 384-bit brainpool ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_brainpoolP384r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                            uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PRIVATE_KEY - 4;
    }

    error_code =
        HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                      &in_data_cmd,
                                      &in_data_shared_key_index,
                                      (uint32_t const *) p_wrapped_user_factory_programming_key,
                                      (uint32_t const *) p_initial_vector,
                                      (uint32_t const *) p_user_key,
                                      (uint32_t *) p_wrapped_key->value);

    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION)
 **********************************************************************************************************************/
