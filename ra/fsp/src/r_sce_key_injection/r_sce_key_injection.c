/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include <string.h>
#include "r_sce_key_injection.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* SCE5 */
#if defined(BSP_MCU_GROUP_RA4M1) || defined(BSP_MCU_GROUP_RA4W1)
 #define SCE5      (1U)
#else
 #define SCE5      (0U)
#endif

/* SCE5_B */
#if defined(BSP_MCU_GROUP_RA6T2)
 #define SCE5_B    (1U)
#else
 #define SCE5_B    (0U)
#endif

/* SCE7 */
#if defined(BSP_MCU_GROUP_RA6M1) || defined(BSP_MCU_GROUP_RA6M2) || defined(BSP_MCU_GROUP_RA6M3) || \
    defined(BSP_MCU_GROUP_RA6T1)
 #define SCE7      (1U)
#else
 #define SCE7      (0U)
#endif

/* SCE9 */
#if defined(BSP_MCU_GROUP_RA4M2) || defined(BSP_MCU_GROUP_RA4M3) || defined(BSP_MCU_GROUP_RA6M4) || \
    defined(BSP_MCU_GROUP_RA6M5)
 #define SCE9      (1U)
#else
 #define SCE9      (0U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const sce_key_injection_api_t g_sce_key_injection_on_sce =
{
    .AES128_InitialKeyWrap = R_SCE_AES128_InitialKeyWrap,
    .AES256_InitialKeyWrap = R_SCE_AES256_InitialKeyWrap,
#if ((SCE5) || (SCE7))
    .KeyUpdateKeyWrap        = R_SCE_KeyUpdateKeyWrap,
    .AES128_EncryptedKeyWrap = R_SCE_AES128_EncryptedKeyWrap,
    .AES256_EncryptedKeyWrap = R_SCE_AES256_EncryptedKeyWrap,
#endif
#if (SCE7)
    .RSA2048_InitialPublicKeyWrap          = R_SCE_RSA2048_InitialPublicKeyWrap,
    .RSA2048_InitialPrivateKeyWrap         = R_SCE_RSA2048_InitialPrivateKeyWrap,
    .RSA2048_EncryptedPublicKeyWrap        = R_SCE_RSA2048_EncryptedPublicKeyWrap,
    .RSA2048_EncryptedPrivateKeyWrap       = R_SCE_RSA2048_EncryptedPrivateKeyWrap,
    .ECC_secp256r1_InitialPublicKeyWrap    = R_SCE_ECC_secp256r1_InitialPublicKeyWrap,
    .ECC_secp256r1_InitialPrivateKeyWrap   = R_SCE_ECC_secp256r1_InitialPrivateKeyWrap,
    .ECC_secp256r1_EncryptedPublicKeyWrap  = R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap,
    .ECC_secp256r1_EncryptedPrivateKeyWrap = R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap,
#endif
};

/*******************************************************************************************************************//**
 * @addtogroup SCE_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API generates 128-bit AES key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_InitialKeyWrap (const uint8_t * const         key_type,
                                       const uint8_t * const         wrapped_user_factory_programming_key,
                                       const uint8_t * const         initial_vector,
                                       const uint8_t * const         encrypted_key,
                                       sce_aes_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE5)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateAes128PlainKeyIndexSub(&indata_keytype,
                                                       &install_key_ring_index,
                                                       (uint32_t *) wrapped_user_factory_programming_key,
                                                       (uint32_t *) initial_vector,
                                                       (uint32_t *) encrypted_key,
                                                       wrapped_key->value);
#elif ((SCE5_B) || (SCE9))
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    uint32_t indata_cmd = SCE_OEM_CMD_AES128;
    indata_keytype = change_endian_long((uint32_t) (*key_type));

    if (0 == *key_type)
    {
        INST_DATA_SIZE = sce_oem_key_size[indata_cmd];
    }
    else
    {
        INST_DATA_SIZE = sce_oem_key_size[indata_cmd] - 4;
    }

    error_code = HW_SCE_GenerateOemKeyIndexSub(&indata_keytype,
                                               &indata_cmd,
                                               &install_key_ring_index,
                                               (uint32_t *) wrapped_user_factory_programming_key,
                                               (uint32_t *) initial_vector,
                                               (uint32_t *) encrypted_key,
                                               wrapped_key->value);
#elif (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));
    error_code     = HW_SCE_GenerateAes128KeyIndexSub(&indata_keytype,
                                                      &install_key_ring_index,
                                                      (uint32_t *) wrapped_user_factory_programming_key,
                                                      (uint32_t *) initial_vector,
                                                      (uint32_t *) encrypted_key,
                                                      wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit AES key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_InitialKeyWrap (const uint8_t * const         key_type,
                                       const uint8_t * const         wrapped_user_factory_programming_key,
                                       const uint8_t * const         initial_vector,
                                       const uint8_t * const         encrypted_key,
                                       sce_aes_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE5)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateAes256PlainKeyIndexSub(&indata_keytype,
                                                       &install_key_ring_index,
                                                       (uint32_t *) wrapped_user_factory_programming_key,
                                                       (uint32_t *) initial_vector,
                                                       (uint32_t *) encrypted_key,
                                                       wrapped_key->value);
#elif ((SCE5_B) || (SCE9))
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    uint32_t indata_cmd = SCE_OEM_CMD_AES256;
    indata_keytype = change_endian_long((uint32_t) (*key_type));

    if (0 == *key_type)
    {
        INST_DATA_SIZE = sce_oem_key_size[indata_cmd];
    }
    else
    {
        INST_DATA_SIZE = sce_oem_key_size[indata_cmd] - 4;
    }

    error_code = HW_SCE_GenerateOemKeyIndexSub(&indata_keytype,
                                               &indata_cmd,
                                               &install_key_ring_index,
                                               (uint32_t *) wrapped_user_factory_programming_key,
                                               (uint32_t *) initial_vector,
                                               (uint32_t *) encrypted_key,
                                               wrapped_key->value);
#elif (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));
    error_code     = HW_SCE_GenerateAes256KeyIndexSub(&indata_keytype,
                                                      &install_key_ring_index,
                                                      (uint32_t *) wrapped_user_factory_programming_key,
                                                      (uint32_t *) initial_vector,
                                                      (uint32_t *) encrypted_key,
                                                      wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates a key update key which is used for functions of the key updating.
 *
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] key_update_key                        Key update key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_KeyUpdateKeyWrap (const uint8_t * const        wrapped_user_factory_programming_key,
                                  const uint8_t * const        initial_vector,
                                  const uint8_t * const        encrypted_key,
                                  sce_key_update_key_t * const key_update_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE5)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    error_code = HW_SCE_GenerateUpdatePlainKeyRingKeyIndexSub(&indata_keytype,
                                                              &install_key_ring_index,
                                                              (uint32_t *) wrapped_user_factory_programming_key,
                                                              (uint32_t *) initial_vector,
                                                              (uint32_t *) encrypted_key,
                                                              key_update_key->value);
#elif (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    error_code = HW_SCE_GenerateUpdateKeyRingKeyIndexSub(&indata_keytype,
                                                         &install_key_ring_index,
                                                         (uint32_t *) wrapped_user_factory_programming_key,
                                                         (uint32_t *) initial_vector,
                                                         (uint32_t *) encrypted_key,
                                                         key_update_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        key_update_key->type = SCE_KEY_INDEX_TYPE_UPDATE_KEY_RING;
    }
    else
    {
        key_update_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 128-bit AES key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES128_EncryptedKeyWrap (const uint8_t * const              initial_vector,
                                         const uint8_t * const              encrypted_key,
                                         const sce_key_update_key_t * const key_update_key,
                                         sce_aes_wrapped_key_t * const      wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if ((SCE5) || (SCE7))
    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = HW_SCE_UpdateAes128KeyIndexSub((uint32_t *) initial_vector,
                                                (uint32_t *) encrypted_key,
                                                wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 256-bit AES key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_AES256_EncryptedKeyWrap (const uint8_t * const              initial_vector,
                                         const uint8_t * const              encrypted_key,
                                         const sce_key_update_key_t * const key_update_key,
                                         sce_aes_wrapped_key_t * const      wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if ((SCE5) || (SCE7))
    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code = HW_SCE_UpdateAes256KeyIndexSub((uint32_t *) initial_vector,
                                                (uint32_t *) encrypted_key,
                                                wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 2048-bit RSA key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           2048-bit RSA wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_InitialPublicKeyWrap (const uint8_t * const                    key_type,
                                              const uint8_t * const                    wrapped_user_factory_programming_key,
                                              const uint8_t * const                    initial_vector,
                                              const uint8_t * const                    encrypted_key,
                                              sce_rsa2048_public_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateRsa2048PublicKeyIndexSub(&indata_keytype,
                                                         &install_key_ring_index,
                                                         (uint32_t *) wrapped_user_factory_programming_key,
                                                         (uint32_t *) initial_vector,
                                                         (uint32_t *) encrypted_key,
                                                         (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 2048-bit RSA key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           2048-bit RSA wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_InitialPrivateKeyWrap (const uint8_t * const                     key_type,
                                               const uint8_t * const                     wrapped_user_factory_programming_key,
                                               const uint8_t * const                     initial_vector,
                                               const uint8_t * const                     encrypted_key,
                                               sce_rsa2048_private_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateRsa2048PrivateKeyIndexSub(&indata_keytype,
                                                          &install_key_ring_index,
                                                          (uint32_t *) wrapped_user_factory_programming_key,
                                                          (uint32_t *) initial_vector,
                                                          (uint32_t *) encrypted_key,
                                                          (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 2048-bit RSA key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   2048-bit RSA wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_EncryptedPublicKeyWrap (const uint8_t * const                    initial_vector,
                                                const uint8_t * const                    encrypted_key,
                                                const sce_key_update_key_t * const       key_update_key,
                                                sce_rsa2048_public_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code =
        HW_SCE_UpdateRsa2048PublicKeyIndexSub((uint32_t *) initial_vector,
                                              (uint32_t *) encrypted_key,
                                              (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 2048-bit RSA key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   2048-bit RSA wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_RSA2048_EncryptedPrivateKeyWrap (const uint8_t * const                     initial_vector,
                                                 const uint8_t * const                     encrypted_key,
                                                 const sce_key_update_key_t * const        key_update_key,
                                                 sce_rsa2048_private_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code =
        HW_SCE_UpdateRsa2048PrivateKeyIndexSub((uint32_t *) initial_vector,
                                               (uint32_t *) encrypted_key,
                                               (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_RSA2048_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           256-bit ECC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_InitialPublicKeyWrap (const uint8_t * const                key_type,
                                                    const uint8_t * const                wrapped_user_factory_programming_key,
                                                    const uint8_t * const                initial_vector,
                                                    const uint8_t * const                encrypted_key,
                                                    sce_ecc_public_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;
    uint32_t indata_cmd             = change_endian_long(0); /* P-256 */;
    uint32_t indata_curve_type      = change_endian_long(0); /* NIST */;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateEccPublicKeyIndexSub(&indata_keytype,
                                                     &install_key_ring_index,
                                                     (uint32_t *) wrapped_user_factory_programming_key,
                                                     &indata_curve_type,
                                                     &indata_cmd,
                                                     (uint32_t *) initial_vector,
                                                     (uint32_t *) encrypted_key,
                                                     (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC key within the user routine.
 *
 * @param[in]     key_type                              Selection key type when generating wrapped key
 *                                                      (0: for encrypted key, 1: for plain key)
 * @param[in]     wrapped_user_factory_programming_key  Wrapped user factory programming key by the Renesas Key Wrap Service.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     initial_vector                        Initialization vector when generating encrypted_key.
 *                                                      When key_type is 1 as plain key, this is not required and
 *                                                      any value can be specified.
 * @param[in]     encrypted_key                         Encrypted user key and MAC appended
 * @param[in,out] wrapped_key                           256-bit ECC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_InitialPrivateKeyWrap (const uint8_t * const                 key_type,
                                                     const uint8_t * const                 wrapped_user_factory_programming_key,
                                                     const uint8_t * const                 initial_vector,
                                                     const uint8_t * const                 encrypted_key,
                                                     sce_ecc_private_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_keytype         = 0;
    uint32_t install_key_ring_index = R_SCE_INSTALL_KEY_RING_INDEX;
    uint32_t indata_cmd             = change_endian_long(0); /* P-256 */;
    uint32_t indata_curve_type      = change_endian_long(0); /* NIST */;

    indata_keytype = change_endian_long((uint32_t) (*key_type));

    error_code = HW_SCE_GenerateEccPrivateKeyIndexSub(&indata_keytype,
                                                      &install_key_ring_index,
                                                      (uint32_t *) wrapped_user_factory_programming_key,
                                                      &indata_curve_type,
                                                      &indata_cmd,
                                                      (uint32_t *) initial_vector,
                                                      (uint32_t *) encrypted_key,
                                                      wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(key_type);
    FSP_PARAMETER_NOT_USED(wrapped_user_factory_programming_key);
    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 256-bit ECC key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   256-bit ECC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPublicKeyWrap (const uint8_t * const                initial_vector,
                                                      const uint8_t * const                encrypted_key,
                                                      const sce_key_update_key_t * const   key_update_key,
                                                      sce_ecc_public_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_cmd       = change_endian_long(0); /* P-256 */
    uint32_t inData_curveType = change_endian_long(0); /* NIST */

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code =
        HW_SCE_UpdateEccPublicKeyIndexSub(&inData_curveType,
                                          &indata_cmd,
                                          (uint32_t *) initial_vector,
                                          (uint32_t *) encrypted_key,
                                          (uint32_t *) &wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PUBLIC;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * This API wraps 256-bit ECC key within the user routine.
 *
 * @param[in] initial_vector Initialization vector when generating encrypted_key
 * @param[in] encrypted_key  User key encryptedand MAC appended
 * @param[in] key_update_key Key update keyring
 * @param[in,out] wrapped_key   256-bit ECC wrapped key
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_UNSUPPORTED                  API not supported.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL Internal I/O buffer is not empty.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_SCE_ECC_secp256r1_EncryptedPrivateKeyWrap (const uint8_t * const                 initial_vector,
                                                       const uint8_t * const                 encrypted_key,
                                                       const sce_key_update_key_t * const    key_update_key,
                                                       sce_ecc_private_wrapped_key_t * const wrapped_key)
{
    fsp_err_t error_code = FSP_SUCCESS;

#if (SCE7)
    uint32_t indata_cmd       = change_endian_long(0); /* P-256 */
    uint32_t inData_curveType = change_endian_long(0); /* NIST */

    memcpy(S_INST2, key_update_key->value, sizeof(S_INST2));

    error_code =
        HW_SCE_UpdateEccPrivateKeyIndexSub(&inData_curveType,
                                           &indata_cmd,
                                           (uint32_t *) initial_vector,
                                           (uint32_t *) encrypted_key,
                                           wrapped_key->value);
#else
    error_code = FSP_ERR_UNSUPPORTED;

    FSP_PARAMETER_NOT_USED(initial_vector);
    FSP_PARAMETER_NOT_USED(encrypted_key);
    FSP_PARAMETER_NOT_USED(key_update_key);
    FSP_PARAMETER_NOT_USED(wrapped_key);
#endif

    if (FSP_SUCCESS == error_code)
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_ECC_P256_PRIVATE;
    }
    else
    {
        wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }

    return error_code;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_KEY_INJECTION)
 **********************************************************************************************************************/
