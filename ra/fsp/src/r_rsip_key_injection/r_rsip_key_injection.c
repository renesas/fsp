/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128_XTS                      = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256_XTS                      = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_CHACHA20                        = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA2048_PRIVATE_KEY             = 132U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA3072_PRIVATE_KEY             = 196U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_RSA4096_PRIVATE_KEY             = 260U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY       = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP384R1_PRIVATE_KEY       = 16U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP521R1_PRIVATE_KEY       = 24U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP384R1_PRIVATE_KEY = 16U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP512R1_PRIVATE_KEY = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY       = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_ED25519_PRIVATE_KEY         = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA224                     = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA256                     = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA384                     = 16U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512                     = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_224                 = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_256                 = 20U,
} e_rsip_word_size_oem_key_inst_data_t;

/* OEM Command */
typedef enum e_rsip_oem_cmd
{
    RSIP_OEM_CMD_INVALID                     = 0U,
    RSIP_OEM_CMD_AES128                      = 5U,
    RSIP_OEM_CMD_AES192                      = 6U,
    RSIP_OEM_CMD_AES256                      = 7U,
    RSIP_OEM_CMD_AES128_XTS                  = 8U,
    RSIP_OEM_CMD_AES256_XTS                  = 9U,
    RSIP_OEM_CMD_RSA2048_PRIVATE             = 13U,
    RSIP_OEM_CMD_RSA3072_PRIVATE             = 15U,
    RSIP_OEM_CMD_RSA4096_PRIVATE             = 17U,
    RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE       = 23U,
    RSIP_OEM_CMD_ECC_SECP384R1_PRIVATE       = 25U,
    RSIP_OEM_CMD_HMAC_SHA224                 = 26U,
    RSIP_OEM_CMD_HMAC_SHA256                 = 27U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE = 29U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PRIVATE = 31U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP512R1_PRIVATE = 33U,
    RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE       = 35U,
    RSIP_OEM_CMD_ECC_SECP521R1_PRIVATE       = 37U,
    RSIP_OEM_CMD_ECC_ED25519_PRIVATE         = 39U,
    RSIP_OEM_CMD_HMAC_SHA384                 = 40U,
    RSIP_OEM_CMD_HMAC_SHA512                 = 41U,
    RSIP_OEM_CMD_HMAC_SHA512_224             = 42U,
    RSIP_OEM_CMD_HMAC_SHA512_256             = 43U,
    RSIP_OEM_CMD_CHACHA20                    = 48U,
} rsip_oem_cmd_t;

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
    .AES192_InitialKeyWrap                     = R_RSIP_AES192_InitialKeyWrap,
    .AES256_InitialKeyWrap                     = R_RSIP_AES256_InitialKeyWrap,
    .AES128_XTS_InitialKeyWrap                 = R_RSIP_AES128_XTS_InitialKeyWrap,
    .AES256_XTS_InitialKeyWrap                 = R_RSIP_AES256_XTS_InitialKeyWrap,
    .ChaCha20_InitialKeyWrap                   = R_RSIP_ChaCha20_InitialKeyWrap,
    .RSA2048_InitialPrivateKeyWrap             = R_RSIP_RSA2048_InitialPrivateKeyWrap,
    .RSA3072_InitialPrivateKeyWrap             = R_RSIP_RSA3072_InitialPrivateKeyWrap,
    .RSA4096_InitialPrivateKeyWrap             = R_RSIP_RSA4096_InitialPrivateKeyWrap,
    .ECC_secp256r1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp256r1_InitialPrivateKeyWrap,
    .ECC_secp384r1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp384r1_InitialPrivateKeyWrap,
    .ECC_secp521r1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp521r1_InitialPrivateKeyWrap,
    .ECC_secp256k1_InitialPrivateKeyWrap       = R_RSIP_ECC_secp256k1_InitialPrivateKeyWrap,
    .ECC_brainpoolP256r1_InitialPrivateKeyWrap = R_RSIP_ECC_brainpoolP256r1_InitialPrivateKeyWrap,
    .ECC_brainpoolP384r1_InitialPrivateKeyWrap = R_RSIP_ECC_brainpoolP384r1_InitialPrivateKeyWrap,
    .ECC_brainpoolP512r1_InitialPrivateKeyWrap = R_RSIP_ECC_brainpoolP512r1_InitialPrivateKeyWrap,
    .ECC_Ed25519_InitialPrivateKeyWrap         = R_RSIP_ECC_Ed25519_InitialPrivateKeyWrap,
    .HMAC_SHA224_InitialKeyWrap                = R_RSIP_HMAC_SHA224_InitialKeyWrap,
    .HMAC_SHA256_InitialKeyWrap                = R_RSIP_HMAC_SHA256_InitialKeyWrap,
    .HMAC_SHA384_InitialKeyWrap                = R_RSIP_HMAC_SHA384_InitialKeyWrap,
    .HMAC_SHA512_InitialKeyWrap                = R_RSIP_HMAC_SHA512_InitialKeyWrap,
    .HMAC_SHA512_224_InitialKeyWrap            = R_RSIP_HMAC_SHA512_224_InitialKeyWrap,
    .HMAC_SHA512_256_InitialKeyWrap            = R_RSIP_HMAC_SHA512_256_InitialKeyWrap,
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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES192);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 * This API generates 128-bit AES-XTS key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           128-bit AES-XTS wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES128_XTS_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                            uint8_t const * const           p_wrapped_user_factory_programming_key,
                                            uint8_t const * const           p_initial_vector,
                                            uint8_t const * const           p_user_key,
                                            rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES128_XTS);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128_XTS;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128_XTS - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_128_XTS;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit AES-XTS key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit AES-XTS wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES256_XTS_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                            uint8_t const * const           p_wrapped_user_factory_programming_key,
                                            uint8_t const * const           p_initial_vector,
                                            uint8_t const * const           p_user_key,
                                            rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES256_XTS);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256_XTS;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256_XTS - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_256_XTS;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ChaCha20-Poly-1305 key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ChaCha20 wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                          uint8_t const * const               p_wrapped_user_factory_programming_key,
                                          uint8_t const * const               p_initial_vector,
                                          uint8_t const * const               p_user_key,
                                          rsip_chacha20_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_CHACHA20);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_CHACHA20;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_CHACHA20 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_CHACHA20;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;

#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA2048_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA3072_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_RSA4096_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP384R1_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 521-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           521-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_secp521r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                      uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                      uint8_t const * const                  p_initial_vector,
                                                      uint8_t const * const                  p_user_key,
                                                      rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP521R1_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP521R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP521R1_PRIVATE_KEY - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
 * This API generates 384-bit brainpool ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           384-bit ECC wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
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
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP384R1_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

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

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 512-bit brainpool ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           512-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_brainpoolP512r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                            uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                            uint8_t const * const                  p_initial_vector,
                                                            uint8_t const * const                  p_user_key,
                                                            rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP512R1_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP512R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP512R1_PRIVATE_KEY - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit Edwards curve ECC private key within the user routine.
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
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECC_Ed25519_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                                    uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                                    uint8_t const * const                  p_initial_vector,
                                                    uint8_t const * const                  p_user_key,
                                                    rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_ED25519_PRIVATE);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_ED25519_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_ED25519_PRIVATE_KEY - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_ED25519_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 224-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           224-bit HMAC-SHA wrapped key
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
fsp_err_t R_RSIP_HMAC_SHA224_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                             uint8_t const * const               p_wrapped_user_factory_programming_key,
                                             uint8_t const * const               p_initial_vector,
                                             uint8_t const * const               p_user_key,
                                             rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E11A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)

    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA224);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA224;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA224 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA224;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#elif (BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit HMAC-SHA wrapped key
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
fsp_err_t R_RSIP_HMAC_SHA256_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                             uint8_t const * const               p_wrapped_user_factory_programming_key,
                                             uint8_t const * const               p_initial_vector,
                                             uint8_t const * const               p_user_key,
                                             rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA256);
    uint32_t  in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA256;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA256 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA256;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 384-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           384-bit HMAC-SHA wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_SHA384_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                             uint8_t const * const               p_wrapped_user_factory_programming_key,
                                             uint8_t const * const               p_initial_vector,
                                             uint8_t const * const               p_user_key,
                                             rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA384);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA384;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA384 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA384;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 512-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           512-bit HMAC-SHA wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_SHA512_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                             uint8_t const * const               p_wrapped_user_factory_programming_key,
                                             uint8_t const * const               p_initial_vector,
                                             uint8_t const * const               p_user_key,
                                             rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED || \
     BSP_FEATURE_RSIP_RSIP_E31A_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA512);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA512;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 512/224-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           512/224-bit HMAC-SHA wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_SHA512_224_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                                 uint8_t const * const               p_wrapped_user_factory_programming_key,
                                                 uint8_t const * const               p_initial_vector,
                                                 uint8_t const * const               p_user_key,
                                                 rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA512_224);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_224;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_224 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA512_224;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 512/256-bit HMAC-SHA key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain, this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain, it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           512/256-bit HMAC-SHA wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_ASSERTION                     A required parameter is NULL.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *         * FSP_ERR_CRYPTO_UNKNOWN                An unknown error occurred.
 *         * FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *         * FSP_ERR_UNSUPPORTED                   This API is not supported on this device.
 *
 * @note The pre-run state is RSIP Enabled State.
 *       After the function runs the state transitions to RSIP Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_SHA512_256_InitialKeyWrap (rsip_key_injection_type_t const     key_injection_type,
                                                 uint8_t const * const               p_wrapped_user_factory_programming_key,
                                                 uint8_t const * const               p_initial_vector,
                                                 uint8_t const * const               p_user_key,
                                                 rsip_hmac_sha_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;
#if (BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED || BSP_FEATURE_RSIP_RSIP_E50D_SUPPORTED)
    uint32_t in_data_key_type         = key_injection_type;
    uint32_t in_data_cmd              = change_endian_long(RSIP_OEM_CMD_HMAC_SHA512_256);
    uint32_t in_data_shared_key_index = R_RSIP_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_256;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA512_256 - 4;
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
        p_wrapped_key->type = RSIP_KEY_TYPE_HMAC_SHA512_256;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

#else
    error_code          = FSP_ERR_UNSUPPORTED;
    p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;

    FSP_PARAMETER_NOT_USED(key_injection_type);
    FSP_PARAMETER_NOT_USED(p_wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(p_initial_vector);
    FSP_PARAMETER_NOT_USED(p_user_key);
#endif

    return error_code;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_KEY_INJECTION)
 **********************************************************************************************************************/
