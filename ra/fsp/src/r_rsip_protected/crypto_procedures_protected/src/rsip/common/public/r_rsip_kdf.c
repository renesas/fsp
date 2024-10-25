/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_public.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define RSIP_PRV_BYTE_SIZE_KDF_HMAC_SHA256_MIN    (32U)
#define RSIP_PRV_BYTE_SIZE_KDF_HMAC_SHA256_MAX    (64U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static rsip_func_kdf_derived_key_import_t select_func_derived_key_import(uint8_t         kdf_mac_type,
                                                                         rsip_key_type_t key_type);
static rsip_ret_t kdf_hmac_update(rsip_ctrl_t * const p_ctrl,
                                  const uint8_t     * p_message,
                                  uint32_t            message_length);
static rsip_ret_t kdf_hmac_sign_finish(rsip_ctrl_t * const p_ctrl, uint8_t * p_mac);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Converts wrapped data to wrapped HMAC key for KDF.
 *
 * Implements @ref rsip_api_t::kdfMacKeyImport.
 *
 * @par Conditions
 * @parblock
 * Argument key_type must be one of the following:
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA256
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA384 (*)
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA512 (*)
 *
 * (*) These features are not supported in this version.
 *
 * The argument p_wrapped_mac must be input the result of R_RSIP_KDF_HMAC_SignFinish().
 * @endparblock
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_MACKeyImport (rsip_ctrl_t * const              p_ctrl,
                                   rsip_key_type_t const            key_type,
                                   rsip_wrapped_mac_t const * const p_wrapped_mac,
                                   uint32_t const                   kdf_data_length,
                                   rsip_wrapped_key_t * const       p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    uint8_t subtype = RSIP_KEY_KDF_HMAC_SHA256;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_mac);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_KEY_TYPE_HMAC_SHA256 == key_type, FSP_ERR_CRYPTO_RSIP_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(gp_func_kdf_mac_key_import[subtype], FSP_ERR_NOT_ENABLED);
#else
    FSP_PARAMETER_NOT_USED(key_type);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Check length */
    FSP_ERROR_RETURN(RSIP_PRV_BYTE_SIZE_KDF_HMAC_SHA256_MIN <= kdf_data_length, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(RSIP_PRV_BYTE_SIZE_KDF_HMAC_SHA256_MAX >= kdf_data_length, FSP_ERR_INVALID_SIZE);

    uint32_t blocks[1] = {bswap_32big((RSIP_PRV_BYTE_SIZE_KDF_HMAC_SHA256_MIN == kdf_data_length) ? 1 : 2)};
    uint32_t len[1]    = {bswap_32big(kdf_data_length)};

    /* Call function */
    rsip_ret_t rsip_ret = gp_func_kdf_mac_key_import[subtype]((const uint32_t *) p_wrapped_mac->value,
                                                              (const uint32_t *) blocks,
                                                              (const uint32_t *) len,
                                                              (uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_key->alg     = RSIP_ALG_KDF_HMAC;
            p_wrapped_key->subtype = subtype;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Converts wrapped ECDH secret to wrapped HMAC key for KDF.
 *
 * Implements @ref rsip_api_t::kdfEcdhSecretKeyImport.
 *
 * @par Conditions
 * @parblock
 * Argument key_type must be one of the following:
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA256
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA384 (*)
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA512 (*)
 *
 * (*) These features are not supported in this version.
 * @endparblock
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_ECDHSecretKeyImport (rsip_ctrl_t * const                 p_ctrl,
                                          rsip_key_type_t const               key_type,
                                          rsip_wrapped_secret_t const * const p_wrapped_secret,
                                          rsip_wrapped_key_t * const          p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    uint8_t subtype = RSIP_KEY_KDF_HMAC_SHA256;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_secret);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_KEY_TYPE_HMAC_SHA256 == key_type, FSP_ERR_CRYPTO_RSIP_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(gp_func_kdf_ecdh_secret_key_import[subtype], FSP_ERR_NOT_ENABLED);
#else
    FSP_PARAMETER_NOT_USED(key_type);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function */
    rsip_ret_t rsip_ret =
        gp_func_kdf_ecdh_secret_key_import[subtype]((const uint32_t *) p_wrapped_secret->value,
                                                    (uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_key->alg     = RSIP_ALG_KDF_HMAC;
            p_wrapped_key->subtype = subtype;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Prepares a HMAC generation.
 *
 * Implements @ref rsip_api_t::kdfhmacInit.
 *
 * @par Conditions
 * Argument p_wrapped_key must be one of the following:
 *  - Output data p_wrapped_key from R_RSIP_KDF_ECDHSecretKeyImport().
 *  - Key type of p_wrapped_key is RSIP_KEY_TYPE_HMAC_xxx.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state    |
 * |------------|--------------|
 * |FSP_SUCCESS |STATE_KDF_HMAC|
 * |Others      |No change     |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_Init (rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    uint8_t subtype = RSIP_KEY_HMAC_SHA256; // for g_hmac_enabled

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN((RSIP_ALG_KDF_HMAC == p_wrapped_key->alg) || (RSIP_ALG_HMAC == p_wrapped_key->alg),
                     FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_hmac_enabled[subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_kdf_hmac_handle_t * p_handle = &p_instance_ctrl->handle.kdf_hmac;

    /* Reset handle */
    p_handle->buffered_length           = 0;
    p_handle->total_length              = 0;
    p_handle->wrapped_msg_length        = 0;
    p_handle->actual_wrapped_msg_length = 0;

    /* Copy wrapped key */
    memcpy(p_handle->wrapped_key, p_wrapped_key, RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_KDF_HMAC_MAX);

    /* Set block size */
    p_handle->block_size = RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA1_SHA224_SHA256;

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_KDF_HMAC;
    p_handle->handle_state = RSIP_USER_HANDLE_STATE_INIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs wrapped MAC as a message.
 *
 * Implements @ref rsip_api_t::kdfhmacMacUpdate.
 *
 * @par Conditions
 * The argument p_wrapped_mac must be input the result of R_RSIP_KDF_HMAC_SignFinish().
 *
 * @par State transition
 * This API can only be executed in **STATE_KDF_HMAC**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_MACUpdate (rsip_ctrl_t * const p_ctrl, rsip_wrapped_mac_t const * const p_wrapped_mac)
{
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_kdf_hmac_handle_t * p_handle        = &p_instance_ctrl->handle.kdf_hmac;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_KDF_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->buffered_length, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->total_length, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->wrapped_msg_length, FSP_ERR_INVALID_STATE);

    /* Copy wrapped MAC */
    memcpy(p_handle->wrapped_msg, p_wrapped_mac->value, RSIP_CFG_BYTE_SIZE_KDF_WRAPPED_MSG_MAX);

    /* Set length */
    p_handle->wrapped_msg_length        = RSIP_CFG_BYTE_SIZE_KDF_WRAPPED_MAC_SHA256;
    p_handle->actual_wrapped_msg_length = RSIP_PRV_BYTE_SIZE_DIGEST_SHA256;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs wrapped ECDH secret as a message.
 *
 * Implements @ref rsip_api_t::kdfhmacEcdhSecretUpdate.
 *
 * @par Conditions
 * The argument p_wrapped_secret must be input the result of R_RSIP_ECDH_KeyAgree() or R_RSIP_ECDH_PlainKeyAgree().
 *
 * @par State transition
 * This API can only be executed in **STATE_KDF_HMAC**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_ECDHSecretUpdate (rsip_ctrl_t * const                 p_ctrl,
                                            rsip_wrapped_secret_t const * const p_wrapped_secret)
{
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_kdf_hmac_handle_t * p_handle        = &p_instance_ctrl->handle.kdf_hmac;
    uint8_t subtype = RSIP_KEY_KDF_HMAC_SHA256;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_secret);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set function */
    rsip_func_kdf_ecdh_secret_key_import_t p_func = gp_func_kdf_ecdh_secret_msg_wrap[subtype];

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    /* Check configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_KDF_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->buffered_length, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->total_length, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(0 == p_handle->wrapped_msg_length, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((const uint32_t *) (p_wrapped_secret->value), (uint32_t *) (p_handle->wrapped_msg));

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* Set length */
            p_handle->wrapped_msg_length        = RSIP_CFG_BYTE_SIZE_ECDH_WRAPPED_SECRET_256;
            p_handle->actual_wrapped_msg_length = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Inputs message.
 *
 * Implements @ref rsip_api_t::kdfhmacUpdate.
 *
 * @par State transition
 * This API can only be executed in **STATE_KDF_HMAC**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_Update (rsip_ctrl_t * const   p_ctrl,
                                  uint8_t const * const p_message,
                                  uint32_t const        message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err             = FSP_ERR_CRYPTO_RSIP_FATAL;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_KDF_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_kdf_hmac_handle_t * p_handle = &p_instance_ctrl->handle.kdf_hmac;

    if (0 == message_length)
    {
        err = FSP_SUCCESS;
    }
    else
    {
        rsip_ret_t      rsip_ret      = RSIP_RET_PASS;
        const uint8_t * p_msg_pos     = p_message;
        uint32_t        processed_len = 0;

        /* (0) Remaining message in buffer and head of new input message (wrapped) */
        if ((0 != p_handle->actual_wrapped_msg_length) &&
            (p_handle->block_size < (p_handle->actual_wrapped_msg_length + p_handle->buffered_length + message_length)))
        {
            uint32_t len = p_handle->block_size - p_handle->buffered_length - p_handle->actual_wrapped_msg_length;

            /* Copy head of new message to buffer */
            memcpy(p_handle->buffer + p_handle->buffered_length, p_msg_pos, len);

            /* Call function */
            rsip_ret = kdf_hmac_update(p_ctrl, p_handle->buffer, p_handle->block_size);

            p_handle->wrapped_msg_length        = 0;
            p_handle->actual_wrapped_msg_length = 0;
            p_handle->buffered_length           = 0;
            p_handle->total_length             += p_handle->block_size;
            processed_len += len;
        }

        /* (1) Remaining message in buffer and head of new input message */
        if ((0 != p_handle->buffered_length) &&
            (p_handle->block_size < (p_handle->buffered_length + message_length)))
        {
            uint32_t len = p_handle->block_size - p_handle->buffered_length;

            /* Copy head of new message to buffer */
            memcpy(p_handle->buffer + p_handle->buffered_length, p_msg_pos, len);

            /* Call function */
            rsip_ret = kdf_hmac_update(p_ctrl, p_handle->buffer, p_handle->block_size);

            p_handle->buffered_length = 0;
            p_handle->total_length   += p_handle->block_size;
            processed_len            += len;
        }

        /* (2) New input message except last block */
        if ((p_handle->block_size < message_length - processed_len) && (RSIP_RET_PASS == rsip_ret))
        {
            uint32_t len = ((message_length - processed_len - 1) / p_handle->block_size) *
                           p_handle->block_size;

            /* Call function */
            rsip_ret = kdf_hmac_update(p_ctrl, p_message + processed_len, len);

            p_handle->total_length += len;
            processed_len          += len;
        }

        /* Check error */
        switch (rsip_ret)
        {
            case RSIP_RET_PASS:
            {
                /* (3) Last block */
                memcpy(p_handle->buffer + p_handle->buffered_length,
                       p_message + processed_len,
                       message_length - processed_len);
                p_handle->buffered_length += message_length - processed_len;

                err = FSP_SUCCESS;
                break;
            }

            case RSIP_RET_RESOURCE_CONFLICT:
            {
                err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
                break;
            }

            case RSIP_RET_FAIL:
            {
                err = FSP_ERR_CRYPTO_RSIP_FAIL;
                break;
            }

            case RSIP_RET_KEY_FAIL:
            {
                err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
                break;
            }

            default:
            {
                err = FSP_ERR_CRYPTO_RSIP_FATAL;
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a HMAC generation.
 *
 * Implements @ref rsip_api_t::kdfhmacSignFinish.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_KDF_HMAC**, and causes state transition.
 *
 * |Return value         |Next state|
 * |---------------------|----------|
 * |FSP_SUCCESS          |STATE_MAIN|
 * |FSP_ERR_ASSERTION    |No change |
 * |FSP_ERR_NOT_OPEN     |No change |
 * |FSP_ERR_INVALID_STATE|No change |
 * |Others               |STATE_MAIN|
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_SignFinish (rsip_ctrl_t * const p_ctrl, rsip_wrapped_mac_t * const p_wrapped_mac)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err             = FSP_ERR_CRYPTO_RSIP_FATAL;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_KDF_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function */
    rsip_ret_t rsip_ret = kdf_hmac_sign_finish(p_ctrl, p_wrapped_mac->value);

    /* Check error */
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition */
            p_instance_ctrl->state = RSIP_STATE_MAIN;

            p_wrapped_mac->alg          = RSIP_ALG_KDF_HMAC;
            p_wrapped_mac->subtype      = RSIP_KEY_KDF_HMAC_SHA256;
            p_wrapped_mac->block_length = RSIP_CFG_BYTE_SIZE_KDF_WRAPPED_MAC_SHA256;
            p_wrapped_mac->blocks       = 1;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Suspends HMAC operation.
 *
 * This API releases RSIP resource and outputs intermediate results. Therefore, it can be used in the following cases:
 * - Execute another cryptographic operations during inputting successive chunks of the message.
 * - Reuse intermediate results.
 *
 * Implements @ref rsip_api_t::kdfhmacSuspend.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_KDF_HMAC**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_MAIN|
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_Suspend (rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_t * const p_handle)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err             = FSP_ERR_CRYPTO_RSIP_FATAL;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_handle);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_KDF_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_ret_t rsip_ret;
    switch (p_instance_ctrl->handle.kdf_hmac.handle_state)
    {
        /* If the state is update, call suspension function */
        case RSIP_USER_HANDLE_STATE_UPDATE:
        {
            /* Read internal state */
            rsip_ret = r_rsip_kdf_hmac_suspend(p_instance_ctrl->handle.kdf_hmac.internal_state);

            /* Handle state transition */
            p_instance_ctrl->handle.kdf_hmac.handle_state = RSIP_USER_HANDLE_STATE_RESUME;
            break;
        }

        default:
        {
            rsip_ret = RSIP_RET_PASS;
        }
    }

    /* Check error */
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* Copy handle */
            *p_handle = p_instance_ctrl->handle.kdf_hmac;

            err = FSP_SUCCESS;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return err;
}

/*******************************************************************************************************************//**
 * Resumes HMAC operation suspended by R_RSIP_KDF_HMAC_Suspend().
 *
 * Implements @ref rsip_api_t::kdfhmacResume.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state    |
 * |------------|--------------|
 * |FSP_SUCCESS |STATE_KDF_HMAC|
 * |Others      |No change     |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_HMAC_Resume (rsip_ctrl_t * const p_ctrl, rsip_kdf_hmac_handle_t const * const p_handle)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_handle);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Copy handle */
    p_instance_ctrl->handle.kdf_hmac = *p_handle;

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_KDF_HMAC;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Concatenates two wrapped MACs.
 *
 * MAC1 || MAC2 is output to p_wrapped_mac1.
 *
 * Implements @ref rsip_api_t::kdfMacConcatenate.
 *
 * @par State transition
 * This API can be executed in **any state** including STATE_INITIAL, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_MACConcatenate (rsip_wrapped_mac_t * const       p_wrapped_mac1,
                                     rsip_wrapped_mac_t const * const p_wrapped_mac2,
                                     uint32_t const                   wrapped_mac1_buffer_length)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_wrapped_mac1);
    FSP_ASSERT(p_wrapped_mac2);

    /* Check mac type */
    FSP_ERROR_RETURN(p_wrapped_mac1->subtype == p_wrapped_mac2->subtype, FSP_ERR_CRYPTO_RSIP_FAIL);
#endif

    uint32_t len1 = p_wrapped_mac1->block_length * p_wrapped_mac1->blocks;
    uint32_t len2 = p_wrapped_mac2->block_length * p_wrapped_mac2->blocks;

    /* Check length */
    FSP_ERROR_RETURN(wrapped_mac1_buffer_length >= (sizeof(rsip_wrapped_mac_t) + len1 + len2), FSP_ERR_INVALID_SIZE);

    /* Copy MAC */
    memcpy(p_wrapped_mac1->value + len1, p_wrapped_mac2->value, len2);
    p_wrapped_mac1->blocks += p_wrapped_mac2->blocks;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Outputs a wrapped key from KDF output.
 *
 * Implements @ref rsip_api_t::kdfDerivedKeyImport.
 *
 * @par Conditions
 * @parblock
 * Argument p_wrapped_mac must be input the result of R_RSIP_KDF_HMAC_SignFinish() or R_RSIP_KDF_MACConcatenate().
 * Argument key_type must be one of the following:
 *  - @ref RSIP_KEY_TYPE_AES_128
 *  - @ref RSIP_KEY_TYPE_AES_256
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA256
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA384 (*)
 *  - @ref RSIP_KEY_TYPE_HMAC_SHA512 (*)
 *
 * (*) These features are not supported in this version.
 * @endparblock
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_DerivedKeyImport (rsip_ctrl_t * const              p_ctrl,
                                       rsip_wrapped_mac_t const * const p_wrapped_mac,
                                       rsip_key_type_t const            key_type,
                                       uint32_t const                   position,
                                       rsip_wrapped_key_t * const       p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set function */
    rsip_func_kdf_derived_key_import_t p_func = select_func_derived_key_import(p_wrapped_mac->subtype, key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    /* Check configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t blocks[1] = {bswap_32big(p_wrapped_mac->blocks)};
    uint32_t pos[1]    = {bswap_32big(position)};

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func((const uint32_t *) p_wrapped_mac->value, blocks, pos, (uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_key->alg     = r_rsip_key_type_to_alg(key_type);
            p_wrapped_key->subtype = r_rsip_key_type_to_subtype(key_type);

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Outputs a initial vector from KDF output.
 *
 * Implements @ref rsip_api_t::kdfDerivedIvWrap.
 *
 * @par Conditions
 * @parblock
 * Argument p_wrapped_mac must be input the result of R_RSIP_KDF_HMAC_SignFinish() or R_RSIP_KDF_MACConcatenate().
 * Argument initial_vector_type must be one of the following:
 *  - @ref RSIP_INITIAL_VECTOR_TYPE_AES_16_BYTE
 * @endparblock
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KDF_DerivedIVWrap (rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_mac_t const * const p_wrapped_mac,
                                    rsip_initial_vector_type_t const initial_vector_type,
                                    uint32_t const                   position,
                                    uint8_t const * const            p_tls_sequence_num,
                                    uint8_t * const                  p_wrapped_initial_vector)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_tls_sequence_num || (RSIP_INITIAL_VECTOR_TYPE_AES_16_BYTE == initial_vector_type) ||
               (RSIP_INITIAL_VECTOR_TYPE_AES_TLS12_CBC == initial_vector_type));
    FSP_ASSERT(p_wrapped_initial_vector);
    FSP_ASSERT(p_wrapped_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check mac type */
    FSP_ERROR_RETURN(RSIP_KEY_KDF_HMAC_SHA256 == p_wrapped_mac->subtype, FSP_ERR_CRYPTO_RSIP_FAIL);
#endif

    /* Set function */
    rsip_func_kdf_derived_iv_wrap_t p_func = gp_func_kdf_derived_iv_wrap[p_wrapped_mac->subtype][initial_vector_type];

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    /* Check configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t blocks[1] = {bswap_32big(p_wrapped_mac->blocks)};
    uint32_t pos[1]    = {bswap_32big(position)};

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func((const uint32_t *) p_wrapped_mac->value,
               blocks,
               pos,
               (const uint32_t *) p_tls_sequence_num,
               (uint32_t *) p_wrapped_initial_vector);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Select primitive function of key import from key type.
 *
 * @param[in] kdf_mac_type KDF MAC type.
 * @param[in] key_type     Key type.
 *
 * @return Pointer to function.
 ***********************************************************************************************************************/
static rsip_func_kdf_derived_key_import_t select_func_derived_key_import (uint8_t         kdf_mac_type,
                                                                          rsip_key_type_t key_type)
{
    rsip_func_kdf_derived_key_import_t ret = NULL;
    uint8_t alg     = r_rsip_key_type_to_alg(key_type);
    uint8_t subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = gp_func_kdf_derived_key_import_aes[kdf_mac_type][subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = gp_func_kdf_derived_key_import_hmac[kdf_mac_type][subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Inputs message.
 *
 * @param[in,out] p_ctrl         Pointer to control block.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message (0 or more bytes).
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
static rsip_ret_t kdf_hmac_update (rsip_ctrl_t * const p_ctrl, const uint8_t * p_message, uint32_t message_length)
{
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_kdf_hmac_handle_t * p_handle        = &p_instance_ctrl->handle.kdf_hmac;

    rsip_ret_t ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret = r_rsip_kdf_hmac_init_update((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                              p_message,
                                              message_length - p_handle->actual_wrapped_msg_length,
                                              p_handle->wrapped_msg,
                                              p_handle->wrapped_msg_length,
                                              p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_kdf_hmac_resume_update((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                                p_message,
                                                message_length,
                                                p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_kdf_hmac_update((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                         p_message,
                                         message_length,
                                         p_handle->internal_state);
        }
    }

    /* Check error */
    switch (ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition */
            p_handle->handle_state = RSIP_USER_HANDLE_STATE_UPDATE;
            break;
        }

        default:
        {
            /* State transition (abort) */
            p_instance_ctrl->state = RSIP_STATE_MAIN;
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Finalizes a HMAC generation.
 *
 * @param[in,out] p_ctrl   Pointer to control block.
 * @param[out]    p_mac    Pointer to destination of message digest. The length depends on MAC type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
static rsip_ret_t kdf_hmac_sign_finish (rsip_ctrl_t * const p_ctrl, uint8_t * p_mac)
{
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_kdf_hmac_handle_t * p_handle        = &p_instance_ctrl->handle.kdf_hmac;
    rsip_ret_t               ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret =
                r_rsip_kdf_hmac_init_final((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                           p_handle->buffer,
                                           p_handle->buffered_length,
                                           p_handle->wrapped_msg,
                                           p_handle->wrapped_msg_length,
                                           p_handle->actual_wrapped_msg_length,
                                           p_mac);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_kdf_hmac_resume_final((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                               p_handle->buffer,
                                               p_handle->buffered_length,
                                               p_handle->total_length + p_handle->buffered_length,
                                               p_mac,
                                               p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_kdf_hmac_final((rsip_wrapped_key_t *) p_handle->wrapped_key,
                                        p_handle->buffer,
                                        p_handle->buffered_length,
                                        p_handle->total_length + p_handle->buffered_length,
                                        p_mac,
                                        p_handle->internal_state);
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return ret;
}
