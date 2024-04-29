/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_public.h"
#include "r_rsip_primitive.h"

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
 * Initialize on-the-fly decryption on RSIP.
 * Implements @ref rsip_api_t::otfInit.
 *
 * \<Usage Precautions>
 * @arg Argument "channel" represents channel number to be used, and supports the features listed below.
 * <table>
 * <caption id="DoftType1"> </caption>
 * <tr><th>Channel<th>Corresponding Parameter</tr>
 * <tr><td>CH-0<td>RSIP_OTF_CHANNEL_0</td>
 * <tr><td>CH-1 (*)<td>RSIP_OTF_CHANNEL_1</td>
 * </table>
 * (*) These features are not supported in v5.3.0.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @param[in,out] p_ctrl        Pointer to control block.
 * @param[in]     channel       Channel number.
 * @param[in]     p_wrapped_key Pointer to wrapped AES key.
 * @param[in]     p_seed        Pointer to seed.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled or selected channel is invalid.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-key-management "Key Management"
 *
 * @attention This function is only part of on-the-fly decryption activation process and intended to be called from
 *            a higher level FSP module. Even if a user calls this function directly, the feature will not be enabled.
 *            The number of channels for the channel parameter is dependent on the hardware.
 *            RA8x1 supports only one channel, and channel parameter must always be set to RSIP_OTF_CHANNEL_0.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_OTF_Init (rsip_ctrl_t * const        p_ctrl,
                           rsip_otf_channel_t const   channel,
                           rsip_wrapped_key_t * const p_wrapped_key,
                           uint8_t const * const      p_seed)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_seed);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_AES == p_wrapped_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check if the key type is enabled on configuration and the channel is enabled */
    FSP_ERROR_RETURN(g_func.p_func_otf[channel][p_wrapped_key->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = g_func.p_func_otf[channel][p_wrapped_key->subtype]
                              ((const uint32_t *) p_wrapped_key->value, (const uint32_t *) p_seed);

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
