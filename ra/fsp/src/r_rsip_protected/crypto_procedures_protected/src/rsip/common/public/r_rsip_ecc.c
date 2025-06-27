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

#define RSIP_PRV_BYTE_SIZE_EDWARDS25519_MESSAGE_MAX    (uint64_t) (0x1FFFFFFFFFFFFFBFU)

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

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Generates an ECDSA signature.
 *
 * Implements @ref rsip_api_t::ecdsaSign.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_private_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE
 *
 * Message hash p_hash should be computed in advance.
 * In the case of hash length is less than the key length, padding is required to make it the same as the key length.
 *
 * For secp521r1 operation, the length of p_hash must be set to 64 bytes.
 *
 * For secp521r1 operation, the length of the argument p_signature must be set as 132 byte.
 * Since 521 bit is not a 8-bit multiple, zero padding is required and the data format is as follows:
 *  <table>
 *      <tr>
 *          <th colspan="4">Data Format for secp521r1 (132 byte)</th>
 *      </tr>
 *      <tr>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature r (521 bit)</td>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature s (521 bit)</td>
 *      </tr>
 *  </table>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              @arg Input parameter is illegal.
 *                                               @arg Signature generation is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECDSA_Sign (rsip_ctrl_t * const              p_ctrl,
                             rsip_wrapped_key_t const * const p_wrapped_private_key,
                             uint8_t const * const            p_hash,
                             uint8_t * const                  p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_wrapped_private_key->p_value);
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_private_key->type);         // Parse key type
    rsip_func_ecdsa_sign_t p_func       = gp_func_ecdsa_sign[key_type_ext.subtype];                   // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PRIVATE == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                    // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func((const uint32_t *) p_wrapped_private_key->p_value, (const uint32_t *) p_hash, (uint32_t *) p_signature);

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
 * Verifies an ECDSA signature.
 *
 * Implements @ref rsip_api_t::ecdsaVerify.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_public_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC
 * - @ref RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PUBLIC
 *
 * Message hash p_hash should be computed in advance.
 * In the case of hash length is less than the key length, padding is required to make it the same as the key length.
 *
 * For secp521r1 operation, the length of p_hash must be set to 64 bytes.
 *
 * For secp521r1 operation, the length of the argument p_signature must be set as 132 byte.
 * Since 521 bit is not a 8-bit multiple, zero padding is required and the data format is as follows:
 *  <table>
 *      <tr>
 *          <th colspan="4">Data Format for secp521r1 (132 byte)</th>
 *      </tr>
 *      <tr>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature r (521 bit)</td>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature s (521 bit)</td>
 *      </tr>
 *  </table>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              @arg Input parameter is illegal.
 *                                               @arg Signature verification is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECDSA_Verify (rsip_ctrl_t * const              p_ctrl,
                               rsip_wrapped_key_t const * const p_wrapped_public_key,
                               uint8_t const * const            p_hash,
                               uint8_t const * const            p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_public_key->p_value);
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t   key_type_ext = r_rsip_key_type_parse(p_wrapped_public_key->type);       // Parse key type
    rsip_func_ecdsa_verify_t p_func       = gp_func_ecdsa_verify[key_type_ext.subtype];              // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PUBLIC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                   // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func((const uint32_t *) p_wrapped_public_key->p_value,
               (const uint32_t *) p_hash,
               (const uint32_t *) p_signature);

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
 * Verifies a public key certificate with ECDSA.
 *
 * Implements @ref rsip_api_t::pkiEcdsaCertVerify.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_public_key must be one of the following:
 *  - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC
 *
 * Message hash p_hash should be computed in advance.
 * In the case of hash length is less than the key length, padding is required to make it the same as the key length.
 *
 * For secp521r1 operation, the length of p_hash must be set to 64 bytes.
 *
 * For secp521r1 operation, the length of the argument p_signature must be set as 132 byte.
 * Since 521 bit is not a 8-bit multiple, zero padding is required and the data format is as follows:
 *  <table>
 *      <tr>
 *          <th colspan="4">Data Format for secp521r1 (132 byte)</th>
 *      </tr>
 *      <tr>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature r (521 bit)</td>
 *          <td>zero padding (7 bit)</td>
 *          <td>signature s (521 bit)</td>
 *      </tr>
 *  </table>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              @arg Input parameter is illegal.
 *                                               @arg Signature verification is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PKI_ECDSA_CertVerify (rsip_ctrl_t * const              p_ctrl,
                                       rsip_wrapped_key_t const * const p_wrapped_public_key,
                                       uint8_t const * const            p_hash,
                                       uint8_t const * const            p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_public_key->p_value);
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t              key_type_ext = r_rsip_key_type_parse(p_wrapped_public_key->type); // Parse key type
    rsip_func_subset_pki_ecdsa_verify_t p_func       = gp_func_pki_ecdsa_verify[key_type_ext.subtype];    // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PUBLIC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);      // Check key type
    FSP_ERROR_RETURN(p_func.p_init, FSP_ERR_NOT_ENABLED);                                                 // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func.p_init((const uint32_t *) p_wrapped_public_key->p_value,
                      (const uint32_t *) p_hash,
                      (const uint32_t *) p_signature);

    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = p_func.p_final((uint32_t *) &p_instance_ctrl->pki_verified_cert_info);
    }

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
 * Generates an EdDSA signature.
 *
 * Implements @ref rsip_api_t::eddsaSign.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_private_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_ECC_EDWARDS25519_PRIVATE
 *
 * Key type of p_wrapped_public_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_ECC_EDWARDS25519_PUBLIC
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
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PureEdDSA_Sign (rsip_ctrl_t * const              p_ctrl,
                                 rsip_wrapped_key_t const * const p_wrapped_private_key,
                                 rsip_wrapped_key_t const * const p_wrapped_public_key,
                                 uint8_t const * const            p_message,
                                 uint64_t const                   message_length,
                                 uint8_t * const                  p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_wrapped_private_key->p_value);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_public_key->p_value);
    FSP_ASSERT(p_message);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t private_key_type_ext = r_rsip_key_type_parse(p_wrapped_private_key->type);                // Parse key type
    rsip_func_eddsa_sign_t p_func               = gp_func_eddsa_sign[private_key_type_ext.subtype];                  // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_key_type_extend_t public_key_type_ext = r_rsip_key_type_parse(p_wrapped_public_key->type);                  // Parse key type

    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PRIVATE == private_key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);        // Check key type
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PUBLIC == public_key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);          // Check key type
    FSP_ERROR_RETURN(private_key_type_ext.subtype == public_key_type_ext.subtype, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                                   // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Check length */
    FSP_ERROR_RETURN(RSIP_PRV_BYTE_SIZE_EDWARDS25519_MESSAGE_MAX >= message_length, FSP_ERR_INVALID_SIZE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((const uint32_t *) p_wrapped_private_key->p_value,
                                 (const uint32_t *) p_wrapped_public_key->p_value,
                                 (const uint32_t *) p_message,
                                 message_length,
                                 (uint32_t *) p_signature);

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
 * Verifies an EdDSA signature.
 *
 * Implements @ref rsip_api_t::eddsaVerify.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_public_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_ECC_EDWARDS25519_PUBLIC
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
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PureEdDSA_Verify (rsip_ctrl_t * const              p_ctrl,
                                   rsip_wrapped_key_t const * const p_wrapped_public_key,
                                   uint8_t const * const            p_message,
                                   uint64_t const                   message_length,
                                   uint8_t const * const            p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_public_key->p_value);
    FSP_ASSERT(p_message);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t   key_type_ext = r_rsip_key_type_parse(p_wrapped_public_key->type);       // Parse key type
    rsip_func_eddsa_verify_t p_func       = gp_func_eddsa_verify[key_type_ext.subtype];              // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PUBLIC == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                   // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Check length */
    FSP_ERROR_RETURN(RSIP_PRV_BYTE_SIZE_EDWARDS25519_MESSAGE_MAX >= message_length, FSP_ERR_INVALID_SIZE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((const uint32_t *) p_wrapped_public_key->p_value,
                                 (const uint32_t *) p_message,
                                 message_length,
                                 (uint32_t *) p_signature);

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
 * Computes ECDH secret with wrapped private key and wrapped public key.
 *
 * Implements @ref rsip_api_t::ecdhKeyAgree.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_private_key and p_wrapped_public_key must be one of the following:
 *  - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECDH_KeyAgree (rsip_ctrl_t * const              p_ctrl,
                                rsip_wrapped_key_t const * const p_wrapped_private_key,
                                rsip_wrapped_key_t const * const p_wrapped_public_key,
                                rsip_wrapped_secret_t * const    p_wrapped_secret)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_wrapped_private_key->p_value);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_public_key->p_value);
    FSP_ASSERT(p_wrapped_secret);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t private_key_type_ext = r_rsip_key_type_parse(p_wrapped_private_key->type);                // Parse key type
    rsip_func_ecdh_t       p_func               = gp_func_ecdh_wrapped[private_key_type_ext.subtype];                // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_key_type_extend_t public_key_type_ext = r_rsip_key_type_parse(p_wrapped_public_key->type);                  // Parse key type

    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PRIVATE == private_key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);        // Check key type
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PUBLIC == public_key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);          // Check key type
    FSP_ERROR_RETURN(private_key_type_ext.subtype == public_key_type_ext.subtype, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                                   // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((const uint32_t *) p_wrapped_public_key->p_value,
                                 (const uint32_t *) p_wrapped_private_key->p_value,
                                 (uint32_t *) p_wrapped_secret->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_secret->type = private_key_type_ext.subtype;

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
 * Computes ECDH secret with wrapped private key and plain public key.
 *
 * Implements @ref rsip_api_t::ecdhPlainKeyAgree.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_private_key must be one of the following:
 *  - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC
 *
 * For secp521r1 operation, the length of the argument p_plain_public_key must be set as 132 byte.
 * Since 521 bit is not a 8-bit multiple, zero padding is required and the data format is as follows:
 *  <table>
 *      <tr>
 *          <th colspan="4">Data Format for secp521r1 (132 byte)</th>
 *      </tr>
 *      <tr>
 *          <td>zero padding (7 bit)</td>
 *          <td>public_key Qx (521 bit)</td>
 *          <td>zero padding (7 bit)</td>
 *          <td>public_key Qy (521 bit)</td>
 *      </tr>
 *  </table>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @attention Unauthenticated public key of Diffie–Hellman key exchange generally carry the risk of man-in-the-middle
 *            (MITM) attack. Please use R_RSIP_ECDH_KeyAgree() or implement signature verification whenever possible.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ECDH_PlainKeyAgree (rsip_ctrl_t * const              p_ctrl,
                                     rsip_wrapped_key_t const * const p_wrapped_private_key,
                                     uint8_t const * const            p_plain_public_key,
                                     rsip_wrapped_secret_t * const    p_wrapped_secret)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_wrapped_private_key->p_value);
    FSP_ASSERT(p_plain_public_key);
    FSP_ASSERT(p_wrapped_secret);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_private_key->type);         // Parse key type
    rsip_func_ecdh_t       p_func       = gp_func_ecdh_plain[key_type_ext.subtype];                   // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_ECC_PRIVATE == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);                                                    // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((const uint32_t *) p_plain_public_key,
                                 (const uint32_t *) p_wrapped_private_key->p_value,
                                 (uint32_t *) p_wrapped_secret->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_secret->type = key_type_ext.subtype;

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
 * @} (end addtogroup RSIP)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
