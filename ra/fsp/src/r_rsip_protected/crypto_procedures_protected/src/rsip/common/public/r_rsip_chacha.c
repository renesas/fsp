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

#define RSIP_PRV_CHACHA_INIT_LEN    (0xFFFFFFFFU)

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
 * Prepares a ChaCha20 function.
 *
 * Implements @ref rsip_api_t::chacha20Init.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_key must be RSIP_KEY_TYPE_CHACHA20.
 *
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state   |
 * |------------|-------------|
 * |FSP_SUCCESS |STATE_CHACHA |
 * |Others      |No change    |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Init (rsip_ctrl_t * const              p_ctrl,
                                rsip_wrapped_key_t const * const p_wrapped_key,
                                uint8_t const * const            p_nonce,
                                uint32_t const                   counter)
{
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_handle_t * p_handle        = &p_instance_ctrl->handle.chacha20;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ASSERT(p_nonce);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t              key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_chacha20_t * p_func       = &gp_func_chacha20[key_type_ext.subtype];    // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_CHACHA == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);   // Check key type
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);                                         // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Set function */
    p_handle->p_func = p_func;

    /* Copy wrapped key */
    p_handle->wrapped_key.type    = p_wrapped_key->type;
    p_handle->wrapped_key.p_value = p_handle->wrapped_key_value;
    memcpy(p_handle->wrapped_key_value, p_wrapped_key->p_value, RSIP_BYTE_SIZE_WRAPPED_KEY(p_wrapped_key->type));

    /* Copy nonce */
    p_handle->nonce_buffer[0] = bswap_32big(((uint32_t *) p_nonce)[0]);
    p_handle->nonce_buffer[1] = bswap_32big(((uint32_t *) p_nonce)[1]);
    p_handle->nonce_buffer[2] = bswap_32big(((uint32_t *) p_nonce)[2]);

    /* Reset handle */
    memset(p_handle->buffer, 0, sizeof(p_handle->buffer));
    p_handle->buffered_length = 0;
    p_handle->total_length    = 0;

    /* Call function (cast to match the argument type with the primitive function) */
    uint32_t   init_length[1] = {RSIP_PRV_CHACHA_INIT_LEN};
    rsip_ret_t rsip_ret       = p_func->p_init((const uint32_t *) p_handle->wrapped_key_value,
                                               &counter,
                                               p_handle->nonce_buffer,
                                               init_length);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition*/
            p_instance_ctrl->state = RSIP_STATE_CHACHA;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
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
 * Encrypts plaintext or decrypts ciphertext.
 *
 * Implements @ref rsip_api_t::chacha20Update.
 *
 * @par Output length
 * Output length to p_output (p_output_length) is calculated text that has not yet been output in multiple of 64 bytes.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **RSIP_STATE_CHACHA**, and does not cause any state transitions.
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Update (rsip_ctrl_t * const   p_ctrl,
                                  uint8_t const * const p_input,
                                  uint32_t const        input_length,
                                  uint8_t * const       p_output,
                                  uint32_t * const      p_output_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_input || (0 == input_length));
    FSP_ASSERT(p_output || (0 == input_length));
    FSP_ASSERT(p_output_length);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_chacha20_handle_t      * p_handle = &p_instance_ctrl->handle.chacha20;
    rsip_func_subset_chacha20_t * p_func   = (rsip_func_subset_chacha20_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_CHACHA == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t length_rest = 0;
    *p_output_length = 0;

    /* Input plaintext/ciphertext */
    if (0 != input_length)
    {
        p_handle->total_length += input_length;
        if ((p_handle->buffered_length + input_length) >= RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)
        {
            /* Input remaining data in buffer */
            memcpy((&p_handle->buffer[0] + p_handle->buffered_length),
                   p_input,
                   RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK - p_handle->buffered_length);

            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_update((uint32_t *) (p_handle->buffer), (uint32_t *) (p_output),
                             r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK));
            length_rest = input_length -
                          (RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK - p_handle->buffered_length);
            *p_output_length += RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK;
            memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

            /* Input block data */
            if (length_rest >= RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)
            {
                uint32_t block_data_length = (length_rest / RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK) *
                                             RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK;

                /* Call function (cast to match the argument type with the primitive function) */
                p_func->p_update((const uint32_t *) (p_input +
                                                     (RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK -
                                                      p_handle->buffered_length)),
                                 (uint32_t *) (p_output + RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK),
                                 r_rsip_byte_to_word_convert(block_data_length));
                length_rest      -= block_data_length;
                *p_output_length += block_data_length;
            }

            p_handle->buffered_length = 0;

            /* Store remaining data to buffer */
            memcpy(p_handle->buffer, p_input + (input_length - length_rest), length_rest);
            p_handle->buffered_length = length_rest;
        }
        else
        {
            /* Store remaining data to buffer */
            memcpy(&p_handle->buffer[0] + p_handle->buffered_length, p_input, input_length);
            p_handle->buffered_length += input_length;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Finalize ChaCha20 operation.
 *
 * Implements @ref rsip_api_t::chacha20Finish.
 *
 * @par Output length
 * @parblock
 * Output length to p_output (p_output_length) is the remaining calculated text length.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **RSIP_STATE_CHACHA**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Finish (rsip_ctrl_t * const p_ctrl, uint8_t * const p_output,
                                  uint32_t * const p_output_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_output);
    FSP_ASSERT(p_output_length);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_chacha20_handle_t      * p_handle = &p_instance_ctrl->handle.chacha20;
    rsip_func_subset_chacha20_t * p_func   = (rsip_func_subset_chacha20_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_CHACHA == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Set remaining data */
    if ((0 != (p_handle->total_length % RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)) ||
        (0 == p_handle->total_length))
    {
        memset(p_handle->buffer + p_handle->buffered_length, 0,
               (RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK - p_handle->buffered_length));
    }

    /* Set parameters */
    *p_output_length = p_handle->buffered_length;

    /* Call function (cast to match the argument type with the primitive function) */
    uint32_t internal_state[2];

    /* The suspend function always returns RSIP_RET_PASS, so the return value is not checked */
    p_func->p_suspend(internal_state);

    /* Reflect remaining text length in the internal state */
    internal_state[1] = p_handle->buffered_length;
    rsip_ret_t rsip_ret = p_func->p_resume((const uint32_t *) p_handle->wrapped_key_value,
                                           (const uint32_t *) p_handle->nonce_buffer,
                                           internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            p_func->p_final((uint32_t *) (p_handle->buffer), (uint32_t *) p_output,
                            r_rsip_byte_to_word_convert(p_handle->buffered_length));
    }

    /* State transition*/
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
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
 * @} (end addtogroup RSIP)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
