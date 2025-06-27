/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_public.h"
#include "r_rsip_primitive.h"
#include "r_rsip_wrapper.h"
#if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED
 #include "r_sb_api.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

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
 * Verifies a Manifest signature and outputs the MAC of image and code certificate.
 * The hash algorithm only supports HMAC-SHA256.
 * The signature algorithm only supports ECDSA secp256r1.
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @note If this API returns FSP_ERR_SB_LOWER_IMAGE_VERSION or FSP_ERR_SB_CRYPTO_AUTH_FAIL, RSIP stops working.
 *       In this case, RSIP can be resumed by executing R_RSIP_Close() and R_RSIP_Open() in that order.
 *
 * @param[in,out] p_ctrl               Pointer to control block.
 * @param[in]     p_key_cert           Pointer to key certificate.
 * @param[in]     key_cert_max_length  Maximum length of key certificate.
 * @param[in]     p_code_cert          Pointer to key code certificate.
 * @param[in]     code_cert_max_length Maximum length of code certificate.
 * @param[out]    p_mac                Pointer to output MAC.
 *                                     It is output in TLV format and consists of a 4-byte Type-Length and a 32-byte Value.
 *
 * @retval FSP_SUCCESS                             Normal termination.
 * @retval FSP_ERR_ASSERTION                       A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                        Module is not open.
 * @retval FSP_ERR_INVALID_STATE                   Internal state is illegal.
 *
 * @retval FSP_ERR_SB_INTERNAL_FAIL                An internal failure.
 * @retval FSP_ERR_SB_INVALID_ARG                  An invalid argument was entered.
 * @retval FSP_ERR_SB_UNSUPPORTED_FUNCTION         Unsupported function executed.
 * @retval FSP_ERR_SB_INVALID_ALIGNMENT            Data entered with incorrect alignment.
 * @retval FSP_ERR_SB_SAME_IMAGE_VERSION           An image of the same version as the current version is input.
 *                                                 (verification completed successfully)
 * @retval FSP_ERR_SB_LOWER_IMAGE_VERSION          Image version lower than the current image version is installed.
 * @retval FSP_ERR_SB_MANI_INVALID_MAGIC           An invalid magic number is set.
 * @retval FSP_ERR_SB_MANI_UNSUPPORTED_VERSION     Unsupported version is set.
 * @retval FSP_ERR_SB_MANI_OUT_OF_RANGE_LEN        Out of range TLV Length is set.
 * @retval FSP_ERR_SB_MANI_TLV_FIELD_ERR           Missing required TLV field.
 * @retval FSP_ERR_SB_MANI_TLV_INVALID_LEN         The length exceeding the end of the manifest is specified
 *                                                 in length of the TLV field.
 * @retval FSP_ERR_SB_MANI_INVALID_IMAGE_LEN       An invalid image length is set.
 * @retval FSP_ERR_SB_MANI_MISMATCH_SIGN_ALGORITHM There is a wrong combination of signature algorithms.
 * @retval FSP_ERR_SB_MANI_UNSUPPORTED_ALGORITHM   An algorithm was specified that the manifest does not support.
 * @retval FSP_ERR_SB_CRYPTO_FAIL                  Cryptographic processing failure.
 * @retval FSP_ERR_SB_CRYPTO_AUTH_FAIL             Verification failed.
 * @retval FSP_ERR_SB_CRYPTO_PARAM_ERR             Parameter error.
 * @retval FSP_ERR_SB_CRYPTO_RESOURCE_CONFLICT     CryptoIP is in use.
 * @retval FSP_ERR_UNSUPPORTED                     This API is not supported on this device.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_FSBL_OEM_BL_Digest_Generate (rsip_ctrl_t * const   p_ctrl,
                                              uint8_t const * const p_key_cert,
                                              uint32_t const        key_cert_max_length,
                                              uint8_t const * const p_code_cert,
                                              uint32_t const        code_cert_max_length,
                                              uint32_t * const      p_mac)
{
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;

#if BSP_FEATURE_RSIP_RSIP_E51A_SUPPORTED
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

 #if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call SB-Lib function */
    sb_ret_t sb_ret = R_SB_CheckIntegrity(p_key_cert,
                                          key_cert_max_length,
                                          p_code_cert,
                                          code_cert_max_length,
                                          SB_MAC_TYPE_HMAC_SHA2_256,
                                          p_mac);

    /* Check error */
    switch (sb_ret)
    {
        case SB_RET_SUCCESS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case SB_RET_ERR_INTERNAL_FAIL:
        {
            err = (fsp_err_t) FSP_ERR_SB_INTERNAL_FAIL;
            break;
        }

        case SB_RET_ERR_INVALID_ARG:
        {
            err = (fsp_err_t) FSP_ERR_SB_INVALID_ARG;
            break;
        }

        case SB_RET_ERR_UNSUPPORTED_FUNCTION:
        {
            err = (fsp_err_t) FSP_ERR_SB_UNSUPPORTED_FUNCTION;
            break;
        }

        case SB_RET_ERR_INVALID_ALIGNMENT:
        {
            err = (fsp_err_t) FSP_ERR_SB_INVALID_ALIGNMENT;
            break;
        }

        case SB_RET_SAME_IMAGE_VERSION:
        {
            err = (fsp_err_t) FSP_ERR_SB_SAME_IMAGE_VERSION;
            break;
        }

        case SB_RET_ERR_LOWER_IMAGE_VERSION:
        {
            err = (fsp_err_t) FSP_ERR_SB_LOWER_IMAGE_VERSION;
            break;
        }

        case SB_RET_ERR_MANI_INVALID_MAGIC:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_INVALID_MAGIC;
            break;
        }

        case SB_RET_ERR_MANI_UNSUPPORTED_VERSION:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_UNSUPPORTED_VERSION;
            break;
        }

        case SB_RET_ERR_MANI_OUT_OF_RANGE_LEN:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_OUT_OF_RANGE_LEN;
            break;
        }

        case SB_RET_ERR_MANI_TLV_FIELD_ERR:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_TLV_FIELD_ERR;
            break;
        }

        case SB_RET_ERR_MANI_TLV_INVALID_LEN:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_TLV_INVALID_LEN;
            break;
        }

        case SB_RET_ERR_MANI_INVALID_IMAGE_LEN:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_INVALID_IMAGE_LEN;
            break;
        }

        case SB_RET_ERR_MANI_MISMATCH_SIGN_ALGORITHM:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_MISMATCH_SIGN_ALGORITHM;
            break;
        }

        case SB_RET_ERR_MANI_UNSUPPORTED_ALGORITHM:
        {
            err = (fsp_err_t) FSP_ERR_SB_MANI_UNSUPPORTED_ALGORITHM;
            break;
        }

        case SB_RET_ERR_CRYPTO_FAIL:
        {
            err = (fsp_err_t) FSP_ERR_SB_CRYPTO_FAIL;
            break;
        }

        case SB_RET_ERR_CRYPTO_AUTH_FAIL:
        {
            err = (fsp_err_t) FSP_ERR_SB_CRYPTO_AUTH_FAIL;
            break;
        }

        case SB_RET_ERR_CRYPTO_PARAM_ERR:
        {
            err = (fsp_err_t) FSP_ERR_SB_CRYPTO_PARAM_ERR;
            break;
        }

        case SB_RET_ERR_CRYPTO_RESOURCE_CONFLICT:
        {
            err = (fsp_err_t) FSP_ERR_SB_CRYPTO_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = (fsp_err_t) FSP_ERR_SB_INTERNAL_FAIL;
        }
    }

#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_key_cert);
    FSP_PARAMETER_NOT_USED(key_cert_max_length);
    FSP_PARAMETER_NOT_USED(p_code_cert);
    FSP_PARAMETER_NOT_USED(code_cert_max_length);
    FSP_PARAMETER_NOT_USED(p_mac);

    err = FSP_ERR_UNSUPPORTED;
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
