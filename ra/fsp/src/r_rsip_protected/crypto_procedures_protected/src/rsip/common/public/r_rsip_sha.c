/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static rsip_ret_t sha_update(rsip_ctrl_t * const p_ctrl, const uint8_t * p_message, uint32_t message_length);
static rsip_ret_t sha_finish(rsip_ctrl_t * const p_ctrl, uint8_t * p_digest);
static rsip_ret_t hmac_update(rsip_ctrl_t * const p_ctrl, const uint8_t * p_message, uint32_t message_length);
static rsip_ret_t hmac_sign_finish(rsip_ctrl_t * const p_ctrl, uint8_t * p_mac);
static rsip_ret_t hmac_verify_finish(rsip_ctrl_t * const p_ctrl, const uint8_t * p_mac, const uint32_t mac_length);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_hmac_length[] =
{
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA1]   = RSIP_PRV_BYTE_SIZE_DIGEST_SHA1,
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA224,
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA256,
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA384] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA384,
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA512] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA512,
};

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
 * Generates SHA message digest. (Total input message must be less than 2^64 bits.)
 *
 * Implements @ref rsip_api_t::shaCompute.
 *
 * @par Conditions
 * See R_RSIP_SHA_Init().
 *
 * @par Output length
 * See R_RSIP_SHA_Finish().
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_SHA_Compute (rsip_ctrl_t * const    p_ctrl,
                              rsip_hash_type_t const hash_type,
                              uint8_t const * const  p_message,
                              uint32_t const         message_length,
                              uint8_t * const        p_digest)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ASSERT(p_digest);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check configuration */
    FSP_ERROR_RETURN(g_sha_enabled[hash_type], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the function) */
    rsip_ret_t rsip_ret = r_rsip_sha1sha2_init_final(hash_type, p_message, message_length, p_digest);

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

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Starts SHA operation.
 *
 * Implements @ref rsip_api_t::shaInit.
 *
 * @par Conditions
 * Argument hash_function accepts any member of enumeration @ref rsip_hash_type_t.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_SHA |
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_SHA_Init (rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check configuration */
    FSP_ERROR_RETURN(g_sha_enabled[hash_type], FSP_ERR_NOT_ENABLED);
#endif

    return r_rsip_sha_init(p_ctrl, hash_type);
}

/*******************************************************************************************************************//**
 * Inputs SHA message. (Total input message must be less than 2^64 bits.)
 *
 * Implements @ref rsip_api_t::shaUpdate.
 *
 * @par State transition
 * This API can only be executed in **STATE_SHA**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_SHA_Update (rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message, uint32_t const message_length)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    return r_rsip_sha_update(p_ctrl, p_message, message_length);
}

/*******************************************************************************************************************//**
 * Outputs SHA message digest.
 *
 * Implements @ref rsip_api_t::shaFinish.
 *
 * @par Output length
 * Output length to p_digest depends on hash_function.
 *   - 28 ( @ref RSIP_HASH_TYPE_SHA224, @ref RSIP_HASH_TYPE_SHA512_224)
 *   - 32 ( @ref RSIP_HASH_TYPE_SHA256, @ref RSIP_HASH_TYPE_SHA512_256)
 *   - 48 ( @ref RSIP_HASH_TYPE_SHA384)
 *   - 64 ( @ref RSIP_HASH_TYPE_SHA512)
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_SHA**, and causes state transition.
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
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_SHA_Finish (rsip_ctrl_t * const p_ctrl, uint8_t * const p_digest)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_digest);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    return r_rsip_sha_finish(p_ctrl, p_digest);
}

/*******************************************************************************************************************//**
 * Suspends SHA operation.
 *
 * This API releases RSIP resource and outputs intermediate results. Therefore, it can be used in the following cases:
 * - Execute another cryptographic operations during inputting successive chunks of the message.
 * - Reuse intermediate results.
 *
 * Implements @ref rsip_api_t::shaSuspend.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_SHA**, and causes state transition.
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
fsp_err_t R_RSIP_SHA_Suspend (rsip_ctrl_t * const p_ctrl, rsip_sha_handle_t * const p_handle)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_handle);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_SHA == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_ret_t rsip_ret;
    switch (p_instance_ctrl->handle.sha.handle_state)
    {
        /* If the state is update, call suspension function */
        case RSIP_USER_HANDLE_STATE_UPDATE:
        {
            /* Read internal state */
            rsip_ret = r_rsip_sha1sha2_suspend(p_instance_ctrl->handle.sha.internal_state);

            /* Handle state transition */
            p_instance_ctrl->handle.sha.handle_state = RSIP_USER_HANDLE_STATE_RESUME;
            break;
        }

        default:
        {
            rsip_ret = RSIP_RET_PASS;
        }
    }

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* Copy handle */
            *p_handle = p_instance_ctrl->handle.sha;

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
 * Resumes SHA operation suspended by R_RSIP_SHA_Suspend().
 *
 * Implements @ref rsip_api_t::shaResume.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_SHA |
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_SHA_Resume (rsip_ctrl_t * const p_ctrl, rsip_sha_handle_t const * const p_handle)
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
    p_instance_ctrl->handle.sha = *p_handle;

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_SHA;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Generates HMAC. (Total input message must be less than 2^64 bits.)
 *
 * Implements @ref rsip_api_t::hmacCompute.
 *
 * @par Conditions
 * See R_RSIP_HMAC_Init().
 *
 * @par Output length
 * See R_RSIP_HMAC_SignFinish().
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_Compute (rsip_ctrl_t * const        p_ctrl,
                               const rsip_wrapped_key_t * p_wrapped_key,
                               uint8_t const * const      p_message,
                               uint32_t const             message_length,
                               uint8_t * const            p_mac)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);          // Parse key type

    FSP_ERROR_RETURN(RSIP_PRV_ALG_HMAC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(g_hmac_enabled[key_type_ext.subtype], FSP_ERR_NOT_ENABLED);               // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the function) */
    rsip_ret_t rsip_ret = r_rsip_hmac_init_final(p_wrapped_key, p_message, message_length, p_mac);

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

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        /* RSIP_RET_FAIL is not used in this function */
        case RSIP_RET_FAIL:
        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Verifies HMAC. (Total input message must be less than 2^64 bits.)
 *
 * Implements @ref rsip_api_t::hmacVerify.
 *
 * @par Conditions
 * See R_RSIP_HMAC_Init() and R_RSIP_HMAC_VerifyFinish().
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  mac_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              MAC verification is failed.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_Verify (rsip_ctrl_t * const        p_ctrl,
                              const rsip_wrapped_key_t * p_wrapped_key,
                              uint8_t const * const      p_message,
                              uint32_t const             message_length,
                              uint8_t const * const      p_mac,
                              uint32_t const             mac_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);          // Parse key type

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_HMAC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(g_hmac_enabled[key_type_ext.subtype], FSP_ERR_NOT_ENABLED);               // Check configuration
#endif

    /* mac_length must be 4 or greater (common) */
    FSP_ERROR_RETURN(4 <= mac_length, FSP_ERR_INVALID_SIZE);

    /* mac_length must be MAC size or less */
    FSP_ERROR_RETURN(mac_length <= gs_hmac_length[key_type_ext.subtype], FSP_ERR_INVALID_SIZE);

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the function) */
    rsip_ret_t rsip_ret = r_rsip_hmac_init_verify(p_wrapped_key, p_message, message_length, p_mac, mac_length);

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

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
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
 * Starts HMAC operation.
 *
 * Implements @ref rsip_api_t::hmacInit.
 *
 * @par Conditions
 * Key type of p_wrapped_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_HMAC_SHA224
 * - @ref RSIP_KEY_TYPE_HMAC_SHA256
 * - @ref RSIP_KEY_TYPE_HMAC_SHA384
 * - @ref RSIP_KEY_TYPE_HMAC_SHA512
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_HMAC|
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_Init (rsip_ctrl_t * const p_ctrl, rsip_wrapped_key_t const * const p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);          // Parse key type

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_HMAC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(g_hmac_enabled[key_type_ext.subtype], FSP_ERR_NOT_ENABLED);               // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_hmac_handle_t * p_handle = &p_instance_ctrl->handle.hmac;

    /* Reset handle */
    p_handle->buffered_length = 0;
    p_handle->total_length    = 0;

    /* Copy wrapped key */
    p_handle->wrapped_key.type    = p_wrapped_key->type;
    p_handle->wrapped_key.p_value = p_handle->wrapped_key_value;
    memcpy(p_handle->wrapped_key_value, p_wrapped_key->p_value, RSIP_BYTE_SIZE_WRAPPED_KEY(p_wrapped_key->type));

    /* Set block size */
    switch (key_type_ext.subtype)
    {
        /* SHA-1, SHA-224, SHA-256 */
        case RSIP_PRV_KEY_SUBTYPE_HMAC_SHA1:
        case RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224:
        case RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256:
        {
            p_handle->block_size = RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA1_SHA224_SHA256;
            break;
        }

        /* SHA-384, SHA-512 */
        default:
        {
            p_handle->block_size = RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA384_SHA512;
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_HMAC;
    p_handle->handle_state = RSIP_USER_HANDLE_STATE_INIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs HMAC message. (Total input message must be less than 2^64 bits.)
 *
 * Implements @ref rsip_api_t::hmacUpdate.
 *
 * @par State transition
 * This API can only be executed in **STATE_HMAC**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_Update (rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message,
                              uint32_t const message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    if (0 == message_length)
    {
        err = FSP_SUCCESS;
    }
    else
    {
        rsip_ret_t           rsip_ret      = RSIP_RET_PASS;
        rsip_hmac_handle_t * p_handle      = &p_instance_ctrl->handle.hmac;
        const uint8_t      * p_msg_pos     = p_message;
        uint32_t             processed_len = 0;

        /* (1) Remaining message in buffer and head of new input message */
        if ((0 != p_handle->buffered_length) &&
            (p_handle->block_size < (p_handle->buffered_length + message_length)))
        {
            uint32_t len = p_handle->block_size - p_handle->buffered_length;

            /* Copy head of new message to buffer */
            memcpy(p_handle->buffer + p_handle->buffered_length, p_msg_pos, len);

            /* Call function */
            rsip_ret = hmac_update(p_ctrl, p_handle->buffer, p_handle->block_size);

            p_handle->buffered_length = 0;
            p_handle->total_length   += p_handle->block_size;
            processed_len            += len;
        }

        /* (2) New input message except last block */
        if ((p_handle->block_size < message_length) && (RSIP_RET_PASS == rsip_ret))
        {
            uint32_t len = ((message_length - processed_len - 1) / p_handle->block_size) *
                           p_handle->block_size;

            /* Call function */
            rsip_ret = hmac_update(p_ctrl, p_message + processed_len, len);

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

            case RSIP_RET_KEY_FAIL:
            {
                err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
                break;
            }

            /* RSIP_RET_FAIL is not used in this function */
            case RSIP_RET_FAIL:
            default:
            {
                err = FSP_ERR_CRYPTO_RSIP_FATAL;
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Outputs HMAC.
 *
 * Implements @ref rsip_api_t::hmacSignFinish.
 *
 * @par Output length
 * Output length to p_mac depends on key type of p_wrapped_key.
 * - 28 ( @ref RSIP_KEY_TYPE_HMAC_SHA224)
 * - 32 ( @ref RSIP_KEY_TYPE_HMAC_SHA256)
 * - 48 ( @ref RSIP_KEY_TYPE_HMAC_SHA384)
 * - 64 ( @ref RSIP_KEY_TYPE_HMAC_SHA512)
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_HMAC**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_SignFinish (rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function */
    rsip_ret_t rsip_ret = hmac_sign_finish(p_ctrl, p_mac);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition */
            p_instance_ctrl->state = RSIP_STATE_MAIN;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        /* RSIP_RET_FAIL is not used in this function */
        case RSIP_RET_FAIL:
        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Verifies HMAC.
 *
 * Implements @ref rsip_api_t::hmacVerifyFinish.
 *
 * @par Conditions
 * Argument mac_length depends on key type of p_wrapped_key. Usually the longest length is recommended.
 * - 4 to 28 ( @ref RSIP_KEY_TYPE_HMAC_SHA224)
 * - 4 to 32 ( @ref RSIP_KEY_TYPE_HMAC_SHA256)
 * - 4 to 48 ( @ref RSIP_KEY_TYPE_HMAC_SHA384)
 * - 4 to 64 ( @ref RSIP_KEY_TYPE_HMAC_SHA512)
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_HMAC**, and causes state transition.
 *
 * |Return value         |Next state|
 * |---------------------|----------|
 * |FSP_SUCCESS          |STATE_MAIN|
 * |FSP_ERR_ASSERTION    |No change |
 * |FSP_ERR_NOT_OPEN     |No change |
 * |FSP_ERR_INVALID_STATE|No change |
 * |FSP_ERR_INVALID_SIZE |No change |
 * |Others               |STATE_MAIN|
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  mac_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              MAC verification is failed.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_VerifyFinish (rsip_ctrl_t * const p_ctrl, uint8_t const * const p_mac, uint32_t const mac_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_hmac_handle_t   * p_handle     = &p_instance_ctrl->handle.hmac;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_handle->wrapped_key.type);

    /* mac_length must be 4 or greater (common) */
    FSP_ERROR_RETURN(4 <= mac_length, FSP_ERR_INVALID_SIZE);

    /* mac_length must be MAC size or less */
    FSP_ERROR_RETURN(mac_length <= gs_hmac_length[key_type_ext.subtype], FSP_ERR_INVALID_SIZE);

    /* Call function (cast to match the argument type with the function) */
    rsip_ret_t rsip_ret = hmac_verify_finish(p_ctrl, p_mac, mac_length);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition */
            p_instance_ctrl->state = RSIP_STATE_MAIN;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
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
 * Suspends HMAC operation.
 *
 * This API releases RSIP resource and outputs intermediate results. Therefore, it can be used in the following cases:
 * - Execute another cryptographic operations during inputting successive chunks of the message.
 * - Reuse intermediate results.
 *
 * Implements @ref rsip_api_t::hmacSuspend.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_HMAC**, and causes state transition.
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
fsp_err_t R_RSIP_HMAC_Suspend (rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_t * const p_handle)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_handle);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_HMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    fsp_err_t  err = FSP_ERR_CRYPTO_RSIP_FATAL;
    rsip_ret_t rsip_ret;
    switch (p_instance_ctrl->handle.hmac.handle_state)
    {
        /* If the state is update, call suspension function */
        case RSIP_USER_HANDLE_STATE_UPDATE:
        {
            /* Read internal state */
            rsip_ret = r_rsip_hmac_suspend(&p_instance_ctrl->handle.hmac);

            /* Handle state transition */
            p_instance_ctrl->handle.hmac.handle_state = RSIP_USER_HANDLE_STATE_RESUME;
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
            *p_handle = p_instance_ctrl->handle.hmac;

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
 * Resumes HMAC operation suspended by R_RSIP_HMAC_Suspend().
 *
 * Implements @ref rsip_api_t::hmacResume.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_HMAC|
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_HMAC_Resume (rsip_ctrl_t * const p_ctrl, rsip_hmac_handle_t const * const p_handle)
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
    p_instance_ctrl->handle.hmac = *p_handle;

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_HMAC;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Prepares a SHA generation.
 *
 * @param[in,out] p_ctrl    Pointer to control block.
 * @param[in]     hash_type Generating hash type.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t r_rsip_sha_init (rsip_ctrl_t * const p_ctrl, rsip_hash_type_t const hash_type)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_sha_handle_t * p_handle = &p_instance_ctrl->handle.sha;

    /* Reset handle */
    p_handle->buffered_length = 0;
    p_handle->total_length    = 0;

    /* Set hash type */
    p_handle->type = hash_type;

    /* Set block size */
    switch (hash_type)
    {
        /* SHA-1, SHA-224, SHA-256 */
        case RSIP_HASH_TYPE_SHA1:
        case RSIP_HASH_TYPE_SHA224:
        case RSIP_HASH_TYPE_SHA256:
        {
            p_handle->block_size = RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA1_SHA224_SHA256;
            break;
        }

        /* SHA-384, SHA-512, SHA-512/224, SHA-512/256 */
        default:
        {
            p_handle->block_size = RSIP_PRV_BYTE_SIZE_HASH_BLOCK_SHA384_SHA512;
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_SHA;
    p_handle->handle_state = RSIP_USER_HANDLE_STATE_INIT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs message.
 *
 * @param[in,out] p_ctrl         Pointer to control block.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message (0 or more bytes).
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t r_rsip_sha_update (rsip_ctrl_t * const p_ctrl, uint8_t const * const p_message, uint32_t const message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_SHA == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    rsip_sha_handle_t * p_handle = &p_instance_ctrl->handle.sha;

    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    if (0 == message_length)
    {
        err = FSP_SUCCESS;
    }
    else
    {
        rsip_ret_t      rsip_ret      = RSIP_RET_PASS;
        const uint8_t * p_msg_pos     = p_message;
        uint32_t        processed_len = 0;

        /* (1) Remaining message in buffer and head of new input message */
        if ((0 != p_handle->buffered_length) &&
            (p_handle->block_size < (p_handle->buffered_length + message_length)))
        {
            uint32_t len = p_handle->block_size - p_handle->buffered_length;

            /* Copy head of new message to buffer */
            memcpy(p_handle->buffer + p_handle->buffered_length, p_msg_pos, len);

            /* Call function */
            rsip_ret = sha_update(p_ctrl, p_handle->buffer, p_handle->block_size);

            p_handle->buffered_length = 0;
            p_handle->total_length   += p_handle->block_size;
            processed_len            += len;
        }

        /* (2) New input message except last block */
        if ((p_handle->block_size < message_length) && (RSIP_RET_PASS == rsip_ret))
        {
            uint32_t len = ((message_length - processed_len - 1) / p_handle->block_size) *
                           p_handle->block_size;

            /* Call function */
            rsip_ret = sha_update(p_ctrl, p_message + processed_len, len);

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

            default:
            {
                err = FSP_ERR_CRYPTO_RSIP_FATAL;
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a SHA generation.
 *
 * @param[in,out] p_ctrl   Pointer to control block.
 * @param[out]    p_digest Pointer to destination of message digest. The length depends on hash type.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t r_rsip_sha_finish (rsip_ctrl_t * const p_ctrl, uint8_t * const p_digest)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_SHA == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function */
    rsip_ret_t rsip_ret = sha_finish(p_ctrl, p_digest);

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

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Inputs message.
 *
 * @param[in,out] p_ctrl         Pointer to control block.
 * @param[in]     p_message      Pointer to message. The length is message_length.
 * @param[in]     message_length Byte length of message (0 or more bytes).
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
static rsip_ret_t sha_update (rsip_ctrl_t * const p_ctrl, const uint8_t * p_message, uint32_t message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_sha_handle_t    * p_handle        = &p_instance_ctrl->handle.sha;

    rsip_ret_t ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret = r_rsip_sha1sha2_init_update(p_handle->type, p_message, message_length, p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_sha1sha2_resume_update(p_handle->type, p_message, message_length, p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_sha1sha2_update(p_handle->type, p_message, message_length, p_handle->internal_state);
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
 * Finalizes a SHA generation.
 *
 * @param[in,out] p_ctrl   Pointer to control block.
 * @param[out]    p_digest Pointer to destination of message digest. The length depends on hash type.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
static rsip_ret_t sha_finish (rsip_ctrl_t * const p_ctrl, uint8_t * p_digest)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_sha_handle_t    * p_handle        = &p_instance_ctrl->handle.sha;
    rsip_ret_t             ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret = r_rsip_sha1sha2_init_final(p_handle->type, p_handle->buffer, p_handle->buffered_length, p_digest);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_sha1sha2_resume_final(p_handle->type,
                                               p_handle->buffer,
                                               p_handle->buffered_length,
                                               p_handle->total_length + p_handle->buffered_length,
                                               p_digest,
                                               p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_sha1sha2_final(p_handle->type,
                                        p_handle->buffer,
                                        p_handle->buffered_length,
                                        p_handle->total_length + p_handle->buffered_length,
                                        p_digest,
                                        p_handle->internal_state);
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_MAIN;

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
static rsip_ret_t hmac_update (rsip_ctrl_t * const p_ctrl, const uint8_t * p_message, uint32_t message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_hmac_handle_t   * p_handle        = &p_instance_ctrl->handle.hmac;

    rsip_ret_t ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret = r_rsip_hmac_init_update(&p_handle->wrapped_key, p_message, message_length, p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret =
                r_rsip_hmac_resume_update(&p_handle->wrapped_key, p_message, message_length, p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_hmac_update(&p_handle->wrapped_key, p_message, message_length, p_handle->internal_state);
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
static rsip_ret_t hmac_sign_finish (rsip_ctrl_t * const p_ctrl, uint8_t * p_mac)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_hmac_handle_t   * p_handle        = &p_instance_ctrl->handle.hmac;
    rsip_ret_t             ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret =
                r_rsip_hmac_init_final(&p_handle->wrapped_key, p_handle->buffer, p_handle->buffered_length, p_mac);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_hmac_resume_final(&p_handle->wrapped_key,
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
            ret = r_rsip_hmac_final(&p_handle->wrapped_key,
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

/*******************************************************************************************************************//**
 * Finalizes a HMAC verification.
 *
 * @param[in,out] p_ctrl     Pointer to control block.
 * @param[in]     p_mac      Pointer to MAC. The length depends on mac_length.
 * @param[in]     mac_length Byte length of MAC.
 *
 * @return The return value of the internally called primitive function.
 **********************************************************************************************************************/
static rsip_ret_t hmac_verify_finish (rsip_ctrl_t * const p_ctrl, const uint8_t * p_mac, const uint32_t mac_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_hmac_handle_t   * p_handle        = &p_instance_ctrl->handle.hmac;
    rsip_ret_t             ret;
    switch (p_handle->handle_state)
    {
        case RSIP_USER_HANDLE_STATE_INIT:
        {
            ret =
                r_rsip_hmac_init_verify(&p_handle->wrapped_key,
                                        p_handle->buffer,
                                        p_handle->buffered_length,
                                        p_mac,
                                        mac_length);
            break;
        }

        case RSIP_USER_HANDLE_STATE_RESUME:
        {
            ret = r_rsip_hmac_resume_verify(&p_handle->wrapped_key,
                                            p_handle->buffer,
                                            p_handle->buffered_length,
                                            p_handle->total_length + p_handle->buffered_length,
                                            p_mac,
                                            mac_length,
                                            p_handle->internal_state);
            break;
        }

        case RSIP_USER_HANDLE_STATE_UPDATE:
        default:
        {
            ret = r_rsip_hmac_verify(&p_handle->wrapped_key,
                                     p_handle->buffer,
                                     p_handle->buffered_length,
                                     p_handle->total_length + p_handle->buffered_length,
                                     p_mac,
                                     mac_length,
                                     p_handle->internal_state);
        }
    }

    /* State transition */
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return ret;
}
