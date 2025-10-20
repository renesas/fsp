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

static fsp_err_t chacha_poly_init(rsip_ctrl_t              * p_ctrl,
                                  rsip_chacha_poly_mode_t    mode,
                                  const rsip_wrapped_key_t * p_wrapped_key,
                                  const uint8_t            * p_nonce,
                                  uint32_t                   nonce_length);
static fsp_err_t chacha_poly_aad_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length);
static fsp_err_t chacha_poly_update(rsip_ctrl_t         * p_ctrl,
                                    uint8_t const * const p_input,
                                    uint32_t const        input_length,
                                    uint8_t * const       p_output,
                                    uint32_t * const      p_output_length);
static fsp_err_t chacha_poly_finish(rsip_ctrl_t * const p_ctrl,
                                    uint8_t * const     p_output,
                                    uint32_t * const    p_output_length,
                                    uint8_t * const     p_tag);
static fsp_err_t chacha_poly_verify(rsip_ctrl_t * const   p_ctrl,
                                    uint8_t * const       p_output,
                                    uint32_t * const      p_output_length,
                                    uint8_t const * const p_tag,
                                    uint32_t const        tag_length);

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
 * Prepares a ChaCha20-Poly1305 function.
 *
 * Implements @ref rsip_api_t::chacha20Poly1305Init.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_key must be RSIP_KEY_TYPE_CHACHA20.
 *
 * Argument mode accepts any member of enumeration @ref rsip_chacha_poly_mode_t.
 *
 * Argument nonce_length must be 12 bytes.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state        |
 * |------------|------------------|
 * |FSP_SUCCESS |STATE_CHACHA_POLY |
 * |Others      |No change         |
 *
 * The next callable API functions in STATE_CHACHA_POLY are as below.
 * - R_RSIP_ChaCha20_Poly1305_AADUpdate(), R_RSIP_ChaCha20_Poly1305_Update(), R_RSIP_ChaCha20_Poly1305_Finish() (encryption),
 *   R_RSIP_ChaCha20_Poly1305_Verify() (decryption)
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input mode is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Poly1305_Init (rsip_ctrl_t * const              p_ctrl,
                                         rsip_chacha_poly_mode_t const    mode,
                                         rsip_wrapped_key_t const * const p_wrapped_key,
                                         uint8_t const * const            p_nonce,
                                         uint32_t const                   nonce_length)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ASSERT(p_nonce);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);            // Parse key type

    FSP_ERROR_RETURN(RSIP_PRV_ALG_CHACHA == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
#endif

    /* Check argument */
    fsp_err_t err = FSP_ERR_INVALID_ARGUMENT;
    switch (mode)
    {
        /* ChaCha20-Poly1305 */
        case RSIP_CHACHA20_POLY1305_MODE_ENC:
        case RSIP_CHACHA20_POLY1305_MODE_DEC:
        {
            err = chacha_poly_init(p_ctrl, mode, p_wrapped_key, p_nonce, nonce_length);
            break;
        }

        default:
        {
            /* Invalid argument */
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Inputs Additional Authentication Data (AAD).
 *
 * Implements @ref rsip_api_t::chacha20Poly1305AadUpdate.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_CHACHA_POLY**, and does not cause any state transitions.
 *
 * - R_RSIP_ChaCha20_Poly1305_AADUpdate(), R_RSIP_ChaCha20_Poly1305_Update(), R_RSIP_ChaCha20_Poly1305_Finish() (encryption),
 *   R_RSIP_ChaCha20_Poly1305_Verify() (decryption)
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Poly1305_AADUpdate (rsip_ctrl_t * const   p_ctrl,
                                              uint8_t const * const p_aad,
                                              uint32_t const        aad_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_aad || (0 == aad_length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* ChaCha20-Poly1305 (AAD update) */
        case RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD:
        case RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD:
        {
            err = chacha_poly_aad_update(p_ctrl, p_aad, aad_length);
            break;
        }

        default:
        {
            /* Invalid state */
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Encrypts plaintext or decrypts ciphertext.
 *
 * Implements @ref rsip_api_t::chacha20Poly1305Update.
 *
 * @par Conditions
 * At least one byte of data must be input with this API before calling R_RSIP_ChaCha20_Poly1305_Finish() or R_RSIP_ChaCha20_Poly1305_Verify().
 *
 * @par Output length
 * Output length to p_output (p_output_length) is calculated text that has not yet been output in multiple of 64 bytes.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_CHACHA_POLY**, and does not cause any state transitions.
 *
 * - R_RSIP_ChaCha20_Poly1305_Update(), R_RSIP_ChaCha20_Poly1305_Finish() (encryption), R_RSIP_ChaCha20_Poly1305_Verify() (decryption)
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Poly1305_Update (rsip_ctrl_t * const   p_ctrl,
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

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* ChaCha20-Poly1305 (AAD update, text update) */
        case RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD:
        case RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD:
        case RSIP_STATE_CHACHA_POLY_ENC_UPDATE_TEXT:
        case RSIP_STATE_CHACHA_POLY_DEC_UPDATE_TEXT:
        {
            err = chacha_poly_update(p_ctrl, p_input, input_length, p_output, p_output_length);
            break;
        }

        default:
        {
            /* Invalid state */
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a ChaCha20-Poly1305 encryption.
 *
 * Implements @ref rsip_api_t::chacha20Poly1305Finish.
 *
 * @par Output length
 * @parblock
 * Output length to p_output (p_output_length) is the remaining calculated text length.
 *
 * Output length to p_tag is 16 bytes.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_CHACHA_POLY**, and causes state transition.
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
 * @retval FSP_ERR_INVALID_SIZE                  Input text length is illegal. (zero byte)
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Poly1305_Finish (rsip_ctrl_t * const p_ctrl,
                                           uint8_t * const     p_output,
                                           uint32_t * const    p_output_length,
                                           uint8_t * const     p_tag)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_output);
    FSP_ASSERT(p_output_length);
    FSP_ASSERT(p_tag);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* ChaCha20-Poly1305 encryption (text update) */
        case RSIP_STATE_CHACHA_POLY_ENC_UPDATE_TEXT:
        {
            err = chacha_poly_finish(p_ctrl, p_output, p_output_length, p_tag);
            break;
        }

        default:
        {
            /* Invalid state */
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a ChaCha20-Poly1305 decryption.
 *
 * Implements @ref rsip_api_t::chacha20Poly1305Verify.
 *
 * @par Conditions
 * Argument tag_length must be 16 bytes.
 *
 * @par Output length
 * Output length to p_output (p_output_length) is the remaining calculated text length.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_CHACHA_POLY**, and causes state transition.
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
 * @retval FSP_ERR_INVALID_SIZE                  tag_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_ChaCha20_Poly1305_Verify (rsip_ctrl_t * const   p_ctrl,
                                           uint8_t * const       p_output,
                                           uint32_t * const      p_output_length,
                                           uint8_t const * const p_tag,
                                           uint32_t const        tag_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_output);
    FSP_ASSERT(p_output_length);
    FSP_ASSERT(p_tag);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* ChaCha20-Poly1305 decryption (text update) */
        case RSIP_STATE_CHACHA_POLY_DEC_UPDATE_TEXT:
        {
            err = chacha_poly_verify(p_ctrl, p_output, p_output_length, p_tag, tag_length);
            break;
        }

        default:
        {
            /* Invalid state */
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

/*******************************************************************************************************************//**
 * Prepares a ChaCha20-Poly1305.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t chacha_poly_init (rsip_ctrl_t              * p_ctrl,
                                   rsip_chacha_poly_mode_t    mode,
                                   const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_nonce,
                                   uint32_t                   nonce_length)
{
    rsip_instance_ctrl_t            * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_poly1305_handle_t * p_handle        = &p_instance_ctrl->handle.chacha20_poly1305;

    rsip_key_type_extend_t key_type_ext                 = r_rsip_key_type_parse(p_wrapped_key->type);       // Parse key type
    const rsip_func_subset_chacha20_poly1305_t * p_func = &gp_func_chacha20_poly1305[key_type_ext.subtype]; // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_func->p_init_enc, FSP_ERR_NOT_ENABLED);                                              // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Check size */
    FSP_ERROR_RETURN(nonce_length == 12, FSP_ERR_INVALID_SIZE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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

    /* Select init function */
    rsip_func_chacha_poly_init_t p_func_init = (RSIP_CHACHA20_POLY1305_MODE_ENC == mode) ?
                                               p_func->p_init_enc : p_func->p_init_dec;

    /* Call function (cast to match the argument type with the primitive function) */
    uint32_t   init_length[1]     = {RSIP_PRV_CHACHA_INIT_LEN};
    uint32_t   init_aad_length[1] = {RSIP_PRV_CHACHA_INIT_LEN};
    rsip_ret_t rsip_ret           = p_func_init((const uint32_t *) p_handle->wrapped_key_value,
                                                p_handle->nonce_buffer,
                                                init_length,
                                                init_aad_length);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /*
             * State transition
             * RSIP_CHACHA20_POLY1305_MODE_ENC -> RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD
             * RSIP_CHACHA20_POLY1305_MODE_DEC -> RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD
             */
            p_instance_ctrl->state =
                (RSIP_CHACHA20_POLY1305_MODE_ENC == mode) ?
                RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD : RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD;

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
 * Inputs aad and executes encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 **********************************************************************************************************************/
static fsp_err_t chacha_poly_aad_update (rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length)
{
    rsip_instance_ctrl_t                 * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_poly1305_handle_t      * p_handle        = &p_instance_ctrl->handle.chacha20_poly1305;
    rsip_func_subset_chacha20_poly1305_t * p_func          = (rsip_func_subset_chacha20_poly1305_t *) p_handle->p_func;

    uint32_t length_rest = 0;

    /* Input AAD */
    if (0 != aad_length)
    {
        p_handle->total_aad_length += aad_length;

        if ((p_handle->buffered_length + aad_length) >= RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)
        {
            /* Input remaining data in buffer */
            memcpy((&p_handle->buffer[0] + p_handle->buffered_length),
                   p_aad,
                   RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK - p_handle->buffered_length);

            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_updateAad((uint32_t *) (p_handle->buffer),
                                r_rsip_byte_to_word_convert((RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)));
            length_rest = aad_length -
                          (RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK - p_handle->buffered_length);
            memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

            /* Input block data */
            if (length_rest >= RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK)
            {
                /* Call function (cast to match the argument type with the primitive function) */
                p_func->p_updateAad((const uint32_t *) (p_aad +
                                                        (RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK -
                                                         p_handle->buffered_length)),
                                    r_rsip_byte_to_word_convert((length_rest / RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK) *
                                                                RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK));
                length_rest -= ((length_rest / RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK) * RSIP_PRV_BYTE_SIZE_CHACHA20_BLOCK);
            }

            p_handle->buffered_length = 0;

            /* Store remaining data to buffer */
            memcpy(p_handle->buffer, p_aad + (aad_length - length_rest), length_rest);
            p_handle->buffered_length = length_rest;
        }
        else
        {
            /* Store remaining data to buffer */
            memcpy(&p_handle->buffer[0] + p_handle->buffered_length, p_aad, aad_length);
            p_handle->buffered_length += aad_length;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs aad and executes encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t chacha_poly_update (rsip_ctrl_t         * p_ctrl,
                                     uint8_t const * const p_input,
                                     uint32_t const        input_length,
                                     uint8_t * const       p_output,
                                     uint32_t * const      p_output_length)
{
    rsip_instance_ctrl_t                 * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_poly1305_handle_t      * p_handle        = &p_instance_ctrl->handle.chacha20_poly1305;
    rsip_func_subset_chacha20_poly1305_t * p_func          = (rsip_func_subset_chacha20_poly1305_t *) p_handle->p_func;

    uint32_t length_rest = 0;
    *p_output_length = 0;

    /* If plaintext/ciphertext is input for the first time, input remaining AAD and prohibit new AAD input */
    rsip_ret_t rsip_ret = RSIP_RET_UNKNOWN;
    switch (p_instance_ctrl->state)
    {
        case RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD:
        case RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD:
        {
            /* The suspend function always returns RSIP_RET_PASS, so the return value is not checked */
            uint32_t internal_state[16];
            p_func->p_suspend(internal_state);

            /* Select resume function */
            rsip_func_chacha_poly_resume_t p_func_resume =
                (RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD == p_instance_ctrl->state) ?
                p_func->p_resume_enc : p_func->p_resume_dec;

            /* Reflect remaining AAD length and total AAD length in the internal state */
            internal_state[2] = p_handle->buffered_length;  // Set remaining AAD length
            internal_state[9] = p_handle->total_aad_length; // Set total AAD length
            rsip_ret          = p_func_resume((uint32_t *) p_handle->wrapped_key_value,
                                              p_handle->nonce_buffer,
                                              internal_state);

            if (RSIP_RET_PASS_1 == rsip_ret)
            {
                /* Update remaining AAD */
                p_func->p_updateAad((uint32_t *) (p_handle->
                                                  buffer),
                                    r_rsip_byte_to_word_convert(p_handle->buffered_length));

                /* Reset buffer */
                memset(p_handle->buffer, 0, sizeof(p_handle->buffer));
                p_handle->buffered_length = 0;

                /* Prohibit AAD input and start plaintext/ciphertext input */
                p_func->p_updateTransition();

                /*
                 * State transition
                 * RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD -> RSIP_STATE_CHACHA_POLY_ENC_UPDATE_TEXT
                 * RSIP_STATE_CHACHA_POLY_DEC_UPDATE_AAD -> RSIP_STATE_CHACHA_POLY_DEC_UPDATE_TEXT
                 */
                p_instance_ctrl->state = (p_instance_ctrl->state == RSIP_STATE_CHACHA_POLY_ENC_UPDATE_AAD) ?
                                         RSIP_STATE_CHACHA_POLY_ENC_UPDATE_TEXT : RSIP_STATE_CHACHA_POLY_DEC_UPDATE_TEXT;
            }

            break;
        }

        default:
        {
            rsip_ret = RSIP_RET_PASS_1;
        }
    }

    /* Input plaintext/ciphertext */
    if (RSIP_RET_PASS_1 == rsip_ret)
    {
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
    }

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS_1:
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

        /* RSIP_RET_KEY_FAIL does not occur unless the key value in the handle structure is destroyed,
         * so it is returned as FSP_ERR_CRYPTO_RSIP_FATAL */
        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a ChaCha20-Poly1305 encryption.
 *
 * @param[in,out] p_ctrl          Pointer to control block.
 * @param[out]    p_output        Pointer to destination of ciphertext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of ciphertext length.
 * @param[out]    p_tag           Pointer to destination of tag for authentication. The length is 16 bytes.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  Input data length is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t chacha_poly_finish (rsip_ctrl_t * const p_ctrl,
                                     uint8_t * const     p_output,
                                     uint32_t * const    p_output_length,
                                     uint8_t * const     p_tag)
{
    rsip_instance_ctrl_t                 * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_poly1305_handle_t      * p_handle        = &p_instance_ctrl->handle.chacha20_poly1305;
    rsip_func_subset_chacha20_poly1305_t * p_func          = (rsip_func_subset_chacha20_poly1305_t *) p_handle->p_func;

    *p_output_length = p_handle->buffered_length;

    /* Check total input length */
    FSP_ERROR_RETURN(p_handle->total_length >= 1, FSP_ERR_INVALID_SIZE);

    /* The suspend function always returns RSIP_RET_PASS, so the return value is not checked */
    uint32_t internal_state[16];
    p_func->p_suspend(internal_state);

    /* Reflect remaining Text length and total Text length in the internal state */
    internal_state[1] = p_handle->buffered_length; // Set remaining Text length
    internal_state[8] = p_handle->total_length;    // Set total Text length
    rsip_ret_t rsip_ret = p_func->p_resume_enc((uint32_t *) p_handle->wrapped_key_value,
                                               p_handle->nonce_buffer,
                                               internal_state);

    if (RSIP_RET_PASS_2 == rsip_ret)
    {
        rsip_ret = p_func->p_final((uint32_t *) (p_handle->buffer),
                                   NULL,
                                   (uint32_t *) p_output,
                                   (uint32_t *) p_tag,
                                   bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length)));
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

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes a ChaCha20-Poly1305 decryption.
 *
 * @param[in,out] p_ctrl          Pointer to control block.
 * @param[out]    p_output        Pointer to destination of plaintext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of plaintext length.
 * @param[in]     p_tag           Pointer to tag for authentication. The length depends on tag_length.
 * @param[in]     tag_length      Byte length of tag. Must be 16.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  Input data length or tag_length is invalid.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t chacha_poly_verify (rsip_ctrl_t * const   p_ctrl,
                                     uint8_t * const       p_output,
                                     uint32_t * const      p_output_length,
                                     uint8_t const * const p_tag,
                                     uint32_t const        tag_length)
{
    rsip_instance_ctrl_t                 * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_chacha20_poly1305_handle_t      * p_handle        = &p_instance_ctrl->handle.chacha20_poly1305;
    rsip_func_subset_chacha20_poly1305_t * p_func          = (rsip_func_subset_chacha20_poly1305_t *) p_handle->p_func;

    *p_output_length = p_handle->buffered_length;

    /* Check total input length and tag_length */
    FSP_ERROR_RETURN((p_handle->total_length >= 1) && (tag_length == 16), FSP_ERR_INVALID_SIZE);

    /* The suspend function always returns RSIP_RET_PASS, so the return value is not checked */
    uint32_t internal_state[16];
    p_func->p_suspend(internal_state);

    /* Reflect remaining Text length and total Text length in the internal state */
    internal_state[1] = p_handle->buffered_length; // Set remaining Text length
    internal_state[8] = p_handle->total_length;    // Set total Text length
    rsip_ret_t rsip_ret = p_func->p_resume_dec((uint32_t *) p_handle->wrapped_key_value,
                                               p_handle->nonce_buffer,
                                               internal_state);

    if (RSIP_RET_PASS_2 == rsip_ret)
    {
        rsip_ret = p_func->p_final((uint32_t *) (p_handle->buffer),
                                   (uint32_t *) p_tag,
                                   (uint32_t *) p_output,
                                   NULL,
                                   bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length)));
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

        case RSIP_RET_AUTH_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_AUTHENTICATION;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}
