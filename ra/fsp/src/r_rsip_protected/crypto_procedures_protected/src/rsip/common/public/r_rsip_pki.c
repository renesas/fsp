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

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static rsip_func_pki_cert_key_import_t select_func_cert_key_import(rsip_key_type_t key_type);

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
 * Verifies a public key certificate with ECDSA.
 *
 * Implements @ref rsip_api_t::pkiEcdsaCertVerify.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_public_key must be one of the following:
 *  - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC (*)
 *  - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC (*)
 *
 * (*) These features are not supported in this version.
 *
 * Message hash p_hash should be computed in advance.
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
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_ECC_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);
#endif

    /* Set function */
    rsip_func_subset_pki_ecdsa_verify_t p_func = gp_func_pki_ecdsa_verify[p_wrapped_public_key->subtype];

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check configuration */
    FSP_ERROR_RETURN(p_func.p_init, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func.p_init((const uint32_t *) p_wrapped_public_key->value,
                      (const uint32_t *) p_hash,
                      (const uint32_t *) p_signature);

    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = p_func.p_final((uint32_t *) p_instance_ctrl->pki_enc_cert_info);
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
 * Wraps the public key in the verified public key certificate.
 *
 * Implements @ref rsip_api_t::pkiCertKeyImport.
 *
 * @par Conditions
 * @parblock
 * Argument key_type must be one of the following:
 *  - @ref RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC
 *  - @ref RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC (*)
 *  - @ref RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC (*)
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
 *
 * @note
 * - Argument p_cert must correspond to the signature of the last called function R_RSIP_PKI_ECDSA_CertVerify(),
 *   R_RSIP_PKI_RSASSA_PKCS1_V1_5_CertVerify(), or R_RSIP_PKI_RSASSA_PSS_CertVerify().
 * - For arguments p_key_param1 and p_key_param2, specify an address inside the certificate.
 *   Addresses outside the certificate are invalid.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PKI_CertKeyImport (rsip_ctrl_t * const        p_ctrl,
                                    uint8_t const * const      p_cert,
                                    uint32_t const             cert_length,
                                    rsip_key_type_t const      key_type,
                                    uint8_t const * const      p_key_param1,
                                    uint32_t const             key_param1_length,
                                    uint8_t const * const      p_key_param2,
                                    uint32_t const             key_param2_length,
                                    rsip_hash_type_t const     hash_function,
                                    rsip_wrapped_key_t * const p_wrapped_public_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cert);
    FSP_ASSERT(p_key_param1);
    FSP_ASSERT(p_key_param2);
    FSP_ASSERT(p_wrapped_public_key);

    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set function */
    rsip_func_pki_cert_key_import_t p_func = select_func_cert_key_import(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t certificate_length[1] =
    {
        bswap_32big(cert_length)
    };

    uint32_t certificate_pubkey[4] =
    {
        bswap_32big((uint32_t) p_key_param1 - (uint32_t) p_cert),                         // Start position of param1
        bswap_32big((uint32_t) p_key_param1 - (uint32_t) p_cert + key_param1_length - 1), // End position of param1
        bswap_32big((uint32_t) p_key_param2 - (uint32_t) p_cert),                         // Start position of param2
        bswap_32big((uint32_t) p_key_param2 - (uint32_t) p_cert + key_param2_length - 1), // End position of param2
    };

    uint32_t hash_type[1] =
    {
        bswap_32big(g_pki_hash_type[hash_function])
    };

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func(hash_type,
                                 (uint32_t const *) p_cert,
                                 certificate_length,
                                 (uint32_t const *) certificate_pubkey,
                                 (uint32_t *) p_instance_ctrl->pki_enc_cert_info,
                                 (uint32_t *) p_wrapped_public_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_public_key->alg     = r_rsip_key_type_to_alg(key_type);
            p_wrapped_public_key->subtype = r_rsip_key_type_to_subtype(key_type);

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
 * Get parameter length from key type.
 *
 * @param[in]  key_type      Key type.
 ***********************************************************************************************************************/
static rsip_func_pki_cert_key_import_t select_func_cert_key_import (rsip_key_type_t key_type)
{
    rsip_func_pki_cert_key_import_t ret = NULL;

    switch (key_type)
    {
        case RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC:
        {
            ret = gp_func_pki_cert_key_import_ecc[RSIP_KEY_ECC_SECP256R1];
            break;
        }

        case RSIP_KEY_TYPE_RSA_2048_PUBLIC:
        {
            ret = gp_func_pki_cert_key_import_rsa[RSIP_KEY_RSA_2048];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}
