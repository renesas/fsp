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

#define RSIP_PRV_BYTE_AES_CCM_B    (128U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t aes_init(rsip_ctrl_t              * p_ctrl,
                          rsip_aes_cipher_mode_t     mode,
                          const rsip_wrapped_key_t * p_wrapped_key,
                          const uint8_t            * p_initial_vector);
static fsp_err_t aes_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_input, uint8_t * p_output, uint32_t input_length);
static fsp_err_t aes_finish(rsip_ctrl_t * p_ctrl);

static fsp_err_t xts_init(rsip_ctrl_t              * p_ctrl,
                          rsip_aes_cipher_mode_t     mode,
                          const rsip_wrapped_key_t * p_wrapped_key,
                          const uint8_t            * p_initial_vector);
static fsp_err_t xts_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_input, uint8_t * p_output, uint32_t input_length);
static fsp_err_t xts_finish(rsip_ctrl_t * p_ctrl);
static fsp_err_t xts_finish_primitive(rsip_func_subset_aes_xts_t * p_func,
                                      const uint8_t              * p_input,
                                      uint8_t                    * p_output,
                                      uint32_t                     input_length);

static fsp_err_t gcm_init(rsip_ctrl_t              * p_ctrl,
                          rsip_aes_aead_mode_t       mode,
                          const rsip_wrapped_key_t * p_wrapped_key,
                          const uint8_t            * p_nonce,
                          uint32_t                   nonce_length);
static fsp_err_t gcm_aad_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length);
static fsp_err_t gcm_update(rsip_ctrl_t         * p_ctrl,
                            uint8_t const * const p_input,
                            uint32_t const        input_length,
                            uint8_t * const       p_output,
                            uint32_t * const      p_output_length);
static fsp_err_t gcm_finish(rsip_ctrl_t * const p_ctrl,
                            uint8_t * const     p_output,
                            uint32_t * const    p_output_length,
                            uint8_t * const     p_tag);
static fsp_err_t gcm_verify(rsip_ctrl_t * const   p_ctrl,
                            uint8_t * const       p_output,
                            uint32_t * const      p_output_length,
                            uint8_t const * const p_tag,
                            uint32_t const        tag_length);
static fsp_err_t gcm_iv_prepare(const rsip_func_subset_aes_cipher_t * p_func_aes_cipher,
                                const uint8_t                       * p_initial_vector,
                                uint32_t                              initial_vector_length,
                                const rsip_wrapped_key_t            * p_wrapped_key,
                                uint32_t                            * p_hashed_ivec);
static void gcm_aad_input_terminate(rsip_instance_ctrl_t * p_instance_ctrl);

static fsp_err_t ccm_init(rsip_ctrl_t              * p_ctrl,
                          rsip_aes_aead_mode_t       mode,
                          const rsip_wrapped_key_t * p_wrapped_key,
                          const uint8_t            * p_nonce,
                          uint32_t                   nonce_length);
static fsp_err_t ccm_length_set(rsip_ctrl_t * const p_ctrl,
                                uint32_t const      total_aad_length,
                                uint32_t const      total_text_length,
                                uint32_t const      tag_length);
static fsp_err_t ccm_aad_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length);
static fsp_err_t ccm_update(rsip_ctrl_t         * p_ctrl,
                            uint8_t const * const p_input,
                            uint32_t const        input_length,
                            uint8_t * const       p_output,
                            uint32_t * const      p_output_length);
static fsp_err_t ccm_finish(rsip_ctrl_t * const p_ctrl,
                            uint8_t * const     p_output,
                            uint32_t * const    p_output_length,
                            uint8_t * const     p_tag);
static fsp_err_t ccm_verify(rsip_ctrl_t * const   p_ctrl,
                            uint8_t * const       p_output,
                            uint32_t * const      p_output_length,
                            uint8_t const * const p_tag,
                            uint32_t const        tag_length);
static void ccm_format(const uint8_t * nonce,
                       uint32_t        nonce_len,
                       const uint8_t * adata,
                       uint8_t         a_len,
                       uint32_t        payload_len,
                       uint32_t        mac_len,
                       uint8_t       * counter,
                       uint8_t       * formatted_data,
                       uint32_t      * formatted_length);

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
 * Starts AES cipher operation in confidentiality mode (ECB/CBC/CTR) or XTS mode.
 *
 * Implements @ref rsip_api_t::aesCipherInit.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_AES_128, @ref RSIP_KEY_TYPE_AES_192, @ref RSIP_KEY_TYPE_AES_256
 * - @ref RSIP_KEY_TYPE_XTS_AES_128, @ref RSIP_KEY_TYPE_XTS_AES_256
 *
 * Argument mode must be the following:
 * - AES key
 *   - @ref RSIP_AES_CIPHER_MODE_ECB_ENC, @ref RSIP_AES_CIPHER_MODE_ECB_DEC
 *   - @ref RSIP_AES_CIPHER_MODE_CBC_ENC, @ref RSIP_AES_CIPHER_MODE_CBC_DEC
 *   - @ref RSIP_AES_CIPHER_MODE_CTR
 * - XTS-AES key
 *   - @ref RSIP_AES_CIPHER_MODE_XTS_ENC, @ref RSIP_AES_CIPHER_MODE_XTS_DEC
 *
 * Argument p_initial_vector must be the following:
 * - [ECB] Not used
 * - [CBC] Raw initial vector
 * - [CTR] Raw nonce
 * - [XTS] Raw initial vector
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state|
 * |------------|----------|
 * |FSP_SUCCESS |STATE_AES |
 * |Others      |No change |
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type or mode is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_Cipher_Init (rsip_ctrl_t * const              p_ctrl,
                                  rsip_aes_cipher_mode_t const     mode,
                                  rsip_wrapped_key_t const * const p_wrapped_key,
                                  uint8_t const * const            p_initial_vector)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ASSERT(p_initial_vector || (RSIP_AES_CIPHER_MODE_ECB_ENC == mode) ||
               (RSIP_AES_CIPHER_MODE_ECB_DEC == mode));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type

    FSP_ERROR_RETURN((RSIP_PRV_ALG_AES == key_type_ext.alg) || (RSIP_PRV_ALG_XTS_AES == key_type_ext.alg),
                     FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);                               // Check key type
#endif

    /* Check argument */
    fsp_err_t err = FSP_ERR_INVALID_ARGUMENT;
    switch (mode)
    {
        /* AES-ECB, AES-CBC, AES-CTR */
        case RSIP_AES_CIPHER_MODE_ECB_ENC:
        case RSIP_AES_CIPHER_MODE_ECB_DEC:
        case RSIP_AES_CIPHER_MODE_CBC_ENC:
        case RSIP_AES_CIPHER_MODE_CBC_DEC:
        case RSIP_AES_CIPHER_MODE_CBC_ENC_WRAPPED_IV:
        case RSIP_AES_CIPHER_MODE_CBC_DEC_WRAPPED_IV:
        case RSIP_AES_CIPHER_MODE_CTR:
        {
            err = aes_init(p_ctrl, mode, p_wrapped_key, p_initial_vector);
            break;
        }

        /* AES-XTS */
        case RSIP_AES_CIPHER_MODE_XTS_ENC:
        case RSIP_AES_CIPHER_MODE_XTS_DEC:
        {
            err = xts_init(p_ctrl, mode, p_wrapped_key, p_initial_vector);
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
 * Encrypts plaintext or decrypts ciphertext.
 *
 * Implements @ref rsip_api_t::aesCipherUpdate.
 *
 * @par Conditions
 * Argument length must be the following:
 * - [ECB][CBC][CTR] 0 or a multiple of 16.
 * - [XTS] 0 or greater than or equal to 16.
 *
 * @par Output length
 * Output length to p_output is `length`.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES**, and does not cause any state transitions.
 *
 * In XTS mode, if once an integer other than 0 or a multiple of 16 is input, this API can no longer be called.
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_Cipher_Update (rsip_ctrl_t * const   p_ctrl,
                                    uint8_t const * const p_input,
                                    uint8_t * const       p_output,
                                    uint32_t const        length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_input || (0 == length));
    FSP_ASSERT(p_output || (0 == length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* AES-ECB, AES-CBC, AES-CTR */
        case RSIP_STATE_AES_CIPHER:
        {
            err = aes_update(p_ctrl, p_input, p_output, length);
            break;
        }

        /* AES-XTS (update) */
        case RSIP_STATE_AES_XTS_UPDATE:
        {
            err = xts_update(p_ctrl, p_input, p_output, length);
            break;
        }

        /* AES-XTS (finish) */
        case RSIP_STATE_AES_XTS_FINISH:
        default:
        {
            /* Invalid state */
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finishes AES operation.
 *
 * Implements @ref rsip_api_t::aesCipherFinish.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_Cipher_Finish (rsip_ctrl_t * const p_ctrl)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        /* AES-ECB, AES-CBC, AES-CTR */
        case RSIP_STATE_AES_CIPHER:
        {
            err = aes_finish(p_ctrl);
            break;
        }

        /* AES-XTS (update, finish) */
        case RSIP_STATE_AES_XTS_UPDATE:
        case RSIP_STATE_AES_XTS_FINISH:
        {
            err = xts_finish(p_ctrl);
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
 * Starts AES AEAD function.
 *
 * Implements @ref rsip_api_t::aesAeadInit.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_AES_128
 * - @ref RSIP_KEY_TYPE_AES_192
 * - @ref RSIP_KEY_TYPE_AES_256
 *
 * Argument mode accepts any member of enumeration @ref rsip_aes_aead_mode_t.
 *
 * Argument nonce_length must be the following:
 * - [GCM] Any length is accepted, but 12 bytes is generally recommended.
 * - [CCM] 7 to 13 bytes.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state    |
 * |------------|--------------|
 * |FSP_SUCCESS |STATE_AES_AEAD|
 * |Others      |No change     |
 *
 * The next callable API functions in STATE_AES_AEAD are as below.
 * - [GCM] R_RSIP_AES_AEAD_AADUpdate(), R_RSIP_AES_AEAD_Update(), R_RSIP_AES_AEAD_Finish() (encryption),
 *   R_RSIP_AES_AEAD_Verify() (decryption)
 * - [CCM] R_RSIP_AES_AEAD_LengthsSet()
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_Init (rsip_ctrl_t * const              p_ctrl,
                                rsip_aes_aead_mode_t             mode,
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

    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);         // Parse key type

    FSP_ERROR_RETURN(RSIP_PRV_ALG_AES == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL); // Check key type
#endif

    /* Check argument */
    fsp_err_t err = FSP_ERR_INVALID_ARGUMENT;
    switch (mode)
    {
        /* AES-GCM */
        case RSIP_AES_AEAD_MODE_GCM_ENC:
        case RSIP_AES_AEAD_MODE_GCM_DEC:
        case RSIP_AES_AEAD_MODE_GCM_ENC_WRAPPED_IV:
        case RSIP_AES_AEAD_MODE_GCM_DEC_WRAPPED_IV:
        {
            err = gcm_init(p_ctrl, mode, p_wrapped_key, p_nonce, nonce_length);
            break;
        }

        /* AES-CCM */
        case RSIP_AES_AEAD_MODE_CCM_ENC:
        case RSIP_AES_AEAD_MODE_CCM_DEC:
        {
            err = ccm_init(p_ctrl, mode, p_wrapped_key, p_nonce, nonce_length);
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
 * Sets text and tag lengths for CCM mode.
 *
 * Implements @ref rsip_api_t::aesAeadLengthsSet.
 *
 * @par Conditions
 * @parblock
 * Argument total_aad_length must be equal to the length of AAD and must be 110 or less.
 *
 * Argument total_test_length must be equal to the length of the plaintext or ciphertext.
 *
 * Argument tag_length must be 4, 6, 8, 10, 12, 14, or 16.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_AEAD**, and does not cause any state transitions.
 *
 * The next callable API functions in STATE_AES_AEAD are as below.
 * - [CCM] R_RSIP_AES_AEAD_AADUpdate()
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note In GCM mode, this API must NOT be called. If called, FSP_ERR_INVALID_STATE will be returned.
 *       AAD length and text length are indeterminate and output tag length is fixed to 16 bytes.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_LengthsSet (rsip_ctrl_t * const p_ctrl,
                                      uint32_t const      total_aad_length,
                                      uint32_t const      total_text_length,
                                      uint32_t const      tag_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    fsp_err_t err = FSP_ERR_INVALID_STATE;
    switch (p_instance_ctrl->state)
    {
        case RSIP_STATE_AES_CCM_ENC_SET_LENGTH:
        case RSIP_STATE_AES_CCM_DEC_SET_LENGTH:
        {
            err = ccm_length_set(p_ctrl, total_aad_length, total_text_length, tag_length);
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
 * Implements @ref rsip_api_t::aesAeadAadUpdate.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_AEAD**, and does not cause any state transitions.
 *
 * - [GCM] R_RSIP_AES_AEAD_AADUpdate(), R_RSIP_AES_AEAD_Update(), R_RSIP_AES_AEAD_Finish() (encryption),
 *   R_RSIP_AES_AEAD_Verify() (decryption)
 * - [CCM] R_RSIP_AES_AEAD_AADUpdate() (AAD input is not completed),
 *   R_RSIP_AES_AEAD_Update() (AAD input is completed)
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  aad_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_AADUpdate (rsip_ctrl_t * const p_ctrl, uint8_t const * const p_aad, uint32_t const aad_length)
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
        /* AES-GCM (AAD update) */
        case RSIP_STATE_AES_GCM_ENC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_DEC_UPDATE_AAD:
        {
            err = gcm_aad_update(p_ctrl, p_aad, aad_length);
            break;
        }

        /* AES-CCM (AAD update) */
        case RSIP_STATE_AES_CCM_ENC_UPDATE_AAD:
        case RSIP_STATE_AES_CCM_DEC_UPDATE_AAD:
        {
            err = ccm_aad_update(p_ctrl, p_aad, aad_length);
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
 * Implements @ref rsip_api_t::aesAeadUpdate.
 *
 * @par Output length
 * Output length to p_output (p_output_length) is calculated text that has not yet been output in multiple of 16 bytes.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_AEAD**, and does not cause any state transitions.
 *
 * - [GCM] R_RSIP_AES_AEAD_Update(), R_RSIP_AES_AEAD_Finish() (encryption), R_RSIP_AES_AEAD_Verify() (decryption)
 * - [CCM] R_RSIP_AES_AEAD_Update() (text input is not completed),
 *   R_RSIP_AES_AEAD_Finish() (text input is completed, encryption),
 *   R_RSIP_AES_AEAD_Verify() (text input is completed, decryption)
 * @endparblock
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @note In GCM mode, if this API is skipped, GMAC will be calculated. For detailed usage, refer to example code.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_Update (rsip_ctrl_t * const   p_ctrl,
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
        /* AES-GCM (AAD update, text update) */
        case RSIP_STATE_AES_GCM_ENC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_DEC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_ENC_UPDATE_TEXT:
        case RSIP_STATE_AES_GCM_DEC_UPDATE_TEXT:
        {
            err = gcm_update(p_ctrl, p_input, input_length, p_output, p_output_length);
            break;
        }

        /* AES-CCM (text update) */
        case RSIP_STATE_AES_CCM_ENC_UPDATE_TEXT:
        case RSIP_STATE_AES_CCM_DEC_UPDATE_TEXT:
        {
            err = ccm_update(p_ctrl, p_input, input_length, p_output, p_output_length);
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
 * Finalizes an AES AEAD encryption.
 *
 * Implements @ref rsip_api_t::aesAeadFinish.
 *
 * @par Output length
 * @parblock
 * Output length to p_output (p_output_length) is the remaining calculated text length.
 *
 * Output length to p_tag as below.
 * - [GCM] 16 bytes.
 * - [CCM] Input value as tag_length in R_RSIP_AES_AEAD_LengthsSet().
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_AEAD**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_Finish (rsip_ctrl_t * const p_ctrl,
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
        /* AES-GCM encryption (AAD update, text update) */
        case RSIP_STATE_AES_GCM_ENC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_ENC_UPDATE_TEXT:
        {
            err = gcm_finish(p_ctrl, p_output, p_output_length, p_tag);
            break;
        }

        /* AES-CCM (finish) */
        case RSIP_STATE_AES_CCM_ENC_FINISH:
        {
            err = ccm_finish(p_ctrl, p_output, p_output_length, p_tag);
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
 * Finalizes an AES AEAD decryption.
 *
 * If there is 16-byte fractional data indicated by the total data length of the value of p_cipher that was input by
 * R_RSIP_AES_GCM_DecryptUpdate(), this API will output the result of decrypting that fractional data to p_cipher.
 * Here, the portion that does not reach 16 bytes will be padded with zeros.
 *
 * Implements @ref rsip_api_t::aesAeadVerify.
 *
 * @par Conditions
 * Argument tag_length must be as below.
 * - [GCM] 1 to 16 bytes.
 * - [CCM] Input value as tag_length in R_RSIP_AES_AEAD_LengthsSet().
 *
 * @par Output length
 * Output length to p_output (p_output_length) is the remaining calculated text length.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_AEAD**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_AEAD_Verify (rsip_ctrl_t * const   p_ctrl,
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
        /* AES-GCM decryption (AAD update, text update) */
        case RSIP_STATE_AES_GCM_DEC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_DEC_UPDATE_TEXT:
        {
            err = gcm_verify(p_ctrl, p_output, p_output_length, p_tag, tag_length);
            break;
        }

        /* AES-CCM decryption (finish) */
        case RSIP_STATE_AES_CCM_DEC_VERI:
        {
            err = ccm_verify(p_ctrl, p_output, p_output_length, p_tag, tag_length);
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
 * Starts an AES MAC operation.
 *
 * Implements @ref rsip_api_t::aesMacInit.
 *
 * @par Conditions
 * @parblock
 * Key type of p_wrapped_key must be one of the following:
 * - @ref RSIP_KEY_TYPE_AES_128
 * - @ref RSIP_KEY_TYPE_AES_192
 * - @ref RSIP_KEY_TYPE_AES_256
 *
 * Argument mode accepts any member of enumeration @ref rsip_aes_aead_mode_t.
 * @endparblock
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_MAIN**, and causes state transition.
 *
 * |Return value|Next state    |
 * |------------|--------------|
 * |FSP_SUCCESS |STATE_AES_MAC |
 * |Others      |No change     |
 * @endparblock
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
 * @note To calculate AES-GMAC, please use not R_RSIP_MAC_*() but R_RSIP_AEAD_*().
 *       For detailed usage, refer to example code.
 *
 * @sa Section @ref r-rsip-protected-supported-algorithms "Supported Algorithms".
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_MAC_Init (rsip_ctrl_t * const              p_ctrl,
                               rsip_aes_mac_mode_t const        mode,
                               rsip_wrapped_key_t const * const p_wrapped_key)
{
    FSP_PARAMETER_NOT_USED(mode);      // Always select AES-CMAC
    rsip_instance_ctrl_t   * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cmac_handle_t * p_handle        = &p_instance_ctrl->handle.aes_cmac;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t              key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_aes_cmac_t * p_func       = &gp_func_aes_cmac[key_type_ext.subtype];    // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RSIP_PRV_ALG_AES == key_type_ext.alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);      // Check key type
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);                                         // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set function to handle */
    p_handle->p_func = p_func;

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func->p_init((const uint32_t *) p_wrapped_key->p_value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition*/
            p_instance_ctrl->state = RSIP_STATE_AES_CMAC;

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
 * Inputs message.
 *
 * Implements @ref rsip_api_t::aesMacUpdate.
 *
 * Inside this function, the data that is input by the user is buffered until the input value of p_message exceeds 16 bytes.
 * If the input value, p_message, is not a multiple of 16 bytes, it will be padded within the function.
 *
 * @par State transition
 * This API can only be executed in **STATE_AES_MAC**, and does not cause any state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_MAC_Update (rsip_ctrl_t * const   p_ctrl,
                                 uint8_t const * const p_message,
                                 uint32_t const        message_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_message || (0 == message_length));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_aes_cmac_handle_t      * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_cmac_t * p_func   = (rsip_func_subset_aes_cmac_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t length_rest = 0;

    p_handle->total_length += message_length;
    if ((p_handle->buffered_length + message_length) > RSIP_PRV_BYTE_SIZE_AES_BLOCK)
    {
        /* Input remaining data in buffer */
        memcpy((&p_handle->buffer[0] + p_handle->buffered_length),
               p_message,
               RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);

        /* Call function (cast to match the argument type with the primitive function) */
        p_func->p_update((const uint32_t *) (p_handle->buffer),
                         r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_AES_BLOCK));
        length_rest = message_length -
                      (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
        memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

        /* Input block data */
        if (length_rest > RSIP_PRV_BYTE_SIZE_AES_BLOCK)
        {
            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_update((const uint32_t *) (p_message +
                                                 (RSIP_PRV_BYTE_SIZE_AES_BLOCK -
                                                  p_handle->buffered_length)),
                             r_rsip_byte_to_word_convert(((length_rest - 1) / RSIP_PRV_BYTE_SIZE_AES_BLOCK) *
                                                         RSIP_PRV_BYTE_SIZE_AES_BLOCK));
            length_rest -= (((length_rest - 1) / RSIP_PRV_BYTE_SIZE_AES_BLOCK) * RSIP_PRV_BYTE_SIZE_AES_BLOCK);
        }

        p_handle->buffered_length = 0;

        /* Store remaining data to buffer */
        memcpy(p_handle->buffer, p_message + (message_length - length_rest), length_rest);
        p_handle->buffered_length = length_rest;
    }
    else
    {
        /* Store remaining data to buffer */
        memcpy(&p_handle->buffer[0] + p_handle->buffered_length, p_message, message_length);
        p_handle->buffered_length += message_length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Outputs AES MAC.
 *
 * Implements @ref rsip_api_t::aesMacSignFinish.
 *
 * @par Output length
 * Output length to p_mac is 16 bytes.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_MAC**, and causes state transition.
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
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_MAC_SignFinish (rsip_ctrl_t * const p_ctrl, uint8_t * const p_mac)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_aes_cmac_handle_t      * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_cmac_t * p_func   = (rsip_func_subset_aes_cmac_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /*
     * Check buffered data
     * If the buffered data is not a complete block, fill the blank with 10/ (NIST SP 800-38B 6.2 Step4).
     */
    if ((0 != (p_handle->buffered_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK)) ||
        (0 == p_handle->total_length))
    {
        p_handle->buffer[p_handle->buffered_length] = 1 << 7;
        memset(p_handle->buffer + (p_handle->buffered_length + 1), 0,
               RSIP_PRV_BYTE_SIZE_AES_BLOCK - (p_handle->buffered_length + 1));
    }

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_generateFinal((const uint32_t *) p_handle->buffer, (uint32_t *) p_mac, p_handle->total_length);

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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
 * Verifies AES MAC.
 *
 * Implements @ref rsip_api_t::aesMacVerifyFinish.
 *
 * @par Conditions
 * Argument mac_length must be as below.
 * - [CMAC] 2 to 16 bytes.
 *
 * @par State transition
 * @parblock
 * This API can only be executed in **STATE_AES_MAC**, and causes state transition.
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
 * @retval FSP_ERR_INVALID_SIZE                  mac_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_AES_MAC_VerifyFinish (rsip_ctrl_t * const   p_ctrl,
                                       uint8_t const * const p_mac,
                                       uint32_t const        mac_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_mac);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_aes_cmac_handle_t      * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_cmac_t * p_func   = (rsip_func_subset_aes_cmac_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CMAC == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* mac_length must be 2 to 16 */
    FSP_ERROR_RETURN((2 <= mac_length) && (mac_length <= RSIP_PRV_BYTE_SIZE_AES_BLOCK), FSP_ERR_INVALID_SIZE);

    /* Set parameters */
    uint32_t mac_length_bit[1] =
    {
        bswap_32big(mac_length * 8)
    };
    uint32_t mac_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t)] =
    {
        0
    };
    memcpy(mac_tmp, p_mac, mac_length);

    /*
     * Check buffered data
     * If the buffered data is not a complete block, fill the blank with 10/ (NIST SP 800-38B 6.2 Step4).
     */
    if ((0 != (p_handle->buffered_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK)) ||
        (0 == p_handle->total_length))
    {
        p_handle->buffer[p_handle->buffered_length] = 1 << 7;
        memset(p_handle->buffer + (p_handle->buffered_length + 1), 0,
               RSIP_PRV_BYTE_SIZE_AES_BLOCK - (p_handle->buffered_length + 1));
    }

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_verifyFinal((const uint32_t *) p_handle->buffer,
                              (const uint32_t *) mac_tmp,
                              mac_length_bit,
                              p_handle->total_length);

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
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

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Prepares an AES-ECB/CBC/CTR.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t aes_init (rsip_ctrl_t              * p_ctrl,
                           rsip_aes_cipher_mode_t     mode,
                           const rsip_wrapped_key_t * p_wrapped_key,
                           const uint8_t            * p_initial_vector)
{
    rsip_instance_ctrl_t     * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t * p_handle        = &p_instance_ctrl->handle.aes_cipher;

    rsip_key_type_extend_t                key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_aes_cipher_t * p_func       = &gp_func_aes_cipher[key_type_ext.subtype];  // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_func->p_init_ecb_enc, FSP_ERR_NOT_ENABLED);                                   // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set function */
    p_handle->p_func = p_func;

    /* Select init function */
    rsip_func_aes_cipher_init_t p_func_init;
    switch (mode)
    {
        case RSIP_AES_CIPHER_MODE_ECB_ENC:
        {
            p_func_init = p_func->p_init_ecb_enc;
            break;
        }

        case RSIP_AES_CIPHER_MODE_ECB_DEC:
        {
            p_func_init = p_func->p_init_ecb_dec;
            break;
        }

        case RSIP_AES_CIPHER_MODE_CBC_ENC:
        {
            p_func_init = p_func->p_init_cbc_enc;
            break;
        }

        case RSIP_AES_CIPHER_MODE_CBC_DEC:
        {
            p_func_init = p_func->p_init_cbc_dec;
            break;
        }

        case RSIP_AES_CIPHER_MODE_CBC_ENC_WRAPPED_IV:
        {
            p_func_init = p_func->p_init_cbc_enc_wrapped_iv;
            break;
        }

        case RSIP_AES_CIPHER_MODE_CBC_DEC_WRAPPED_IV:
        {
            p_func_init = p_func->p_init_cbc_dec_wrapped_iv;
            break;
        }

        default:                       // RSIP_AES_CIPHER_MODE_CTR
        {
            p_func_init = p_func->p_init_ctr;
        }
    }

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func_init((const uint32_t *) p_wrapped_key->p_value, (const uint32_t *) p_initial_vector);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition*/
            p_instance_ctrl->state = RSIP_STATE_AES_CIPHER;

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
 * Executes AES-ECB/CBC/CTR encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 **********************************************************************************************************************/
static fsp_err_t aes_update (rsip_ctrl_t * p_ctrl, const uint8_t * p_input, uint8_t * p_output, uint32_t input_length)

{
    rsip_instance_ctrl_t          * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_cipher_t * p_func          = (rsip_func_subset_aes_cipher_t *) p_handle->p_func;

    /* input_length must be a multiple of AES block length */
    FSP_ERROR_RETURN(0 == (input_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK), FSP_ERR_INVALID_SIZE);

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CIPHER == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    if (0 != input_length)
    {
        /* Call function (cast to match the argument type with the primitive function) */
        p_func->p_update((const uint32_t *) p_input, (uint32_t *) p_output, r_rsip_byte_to_word_convert(input_length));
    }
    else
    {
        /* Do nothing */
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Finalizes an AES-ECB/CBC/CTR.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t aes_finish (rsip_ctrl_t * p_ctrl)
{
    rsip_instance_ctrl_t          * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_cipher_t * p_func          = (rsip_func_subset_aes_cipher_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CIPHER == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func->p_final();

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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
 * Prepares an AES-XTS.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t xts_init (rsip_ctrl_t              * p_ctrl,
                           rsip_aes_cipher_mode_t     mode,
                           const rsip_wrapped_key_t * p_wrapped_key,
                           const uint8_t            * p_initial_vector)
{
    rsip_instance_ctrl_t     * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t * p_handle        = &p_instance_ctrl->handle.aes_cipher;

    rsip_key_type_extend_t             key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_aes_xts_t * p_func       = (RSIP_AES_CIPHER_MODE_XTS_ENC == mode) ?
                                                      &gp_func_aes_xts_enc[key_type_ext.subtype] :
                                                      &gp_func_aes_xts_dec[key_type_ext.subtype]; // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);                                        // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set function */
    p_handle->p_func = p_func;

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_init((const uint32_t *) p_wrapped_key->p_value, (const uint32_t *) p_initial_vector);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* State transition*/
            p_instance_ctrl->state = RSIP_STATE_AES_XTS_UPDATE;

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
 * Executes AES-XTS encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t xts_update (rsip_ctrl_t * p_ctrl, const uint8_t * p_input, uint8_t * p_output, uint32_t input_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t   * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_xts_t * p_func          = (rsip_func_subset_aes_xts_t *) p_handle->p_func;

    /* Input_length must be 0 or >= 16 */
    FSP_ERROR_RETURN((0 == input_length) || (RSIP_PRV_BYTE_SIZE_AES_BLOCK <= input_length), FSP_ERR_INVALID_SIZE);

    /* Set length */
    uint32_t remaining_length = (0 == (input_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK)) ? 0 :
                                input_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK + RSIP_PRV_BYTE_SIZE_AES_BLOCK;
    uint32_t block_length = input_length - remaining_length;

    fsp_err_t err = FSP_SUCCESS;
    if (0 != input_length)
    {
        if (0 != block_length)
        {
            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_update((const uint32_t *) p_input,
                             (uint32_t *) p_output,
                             r_rsip_byte_to_word_convert(block_length));
        }

        /* Input remaining blocks */
        if (0 != (input_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK))
        {
            uint8_t buffer[RSIP_PRV_BYTE_SIZE_AES_BLOCK * 2] = {0};
            memcpy(buffer, p_input + block_length, remaining_length);

            err = xts_finish_primitive(p_func, buffer, p_output + block_length, remaining_length);

            /* After input remaining blocks, final function must be called */
            p_instance_ctrl->state = RSIP_STATE_AES_XTS_FINISH;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes an AES-XTS.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t xts_finish (rsip_ctrl_t * p_ctrl)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t   * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_xts_t * p_func          = (rsip_func_subset_aes_xts_t *) p_handle->p_func;

    fsp_err_t err = FSP_SUCCESS;
    if (RSIP_STATE_AES_XTS_UPDATE == p_instance_ctrl->state)
    {
        /* If final function have not called (remaining blocks have not been input), Call function for empty message */
        err = xts_finish_primitive(p_func, NULL, NULL, 0);
    }

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* State transition*/
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes an AES-XTS.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t xts_finish_primitive (rsip_func_subset_aes_xts_t * p_func,
                                       const uint8_t              * p_input,
                                       uint8_t                    * p_output,
                                       uint32_t                     input_length)
{
    uint32_t output_length_bit[1] =
    {
        bswap_32big(r_rsip_byte_to_bit_convert_lower(input_length))
    };

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func->p_final(output_length_bit, (uint32_t *) p_input, (uint32_t *) (p_output));

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* After this function returns, final function must be called */
            err = FSP_SUCCESS;

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
 * Prepares an AES-GCM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t gcm_init (rsip_ctrl_t              * p_ctrl,
                           rsip_aes_aead_mode_t       mode,
                           const rsip_wrapped_key_t * p_wrapped_key,
                           const uint8_t            * p_nonce,
                           uint32_t                   nonce_length)
{
    rsip_instance_ctrl_t  * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t * p_handle        = &p_instance_ctrl->handle.aes_gcm;

    rsip_key_type_extend_t             key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_aes_gcm_t * p_func       =
        ((RSIP_AES_AEAD_MODE_GCM_ENC == mode) || (RSIP_AES_AEAD_MODE_GCM_ENC_WRAPPED_IV == mode)) ?
        &gp_func_aes_gcm_enc[key_type_ext.subtype] : &gp_func_aes_gcm_dec[key_type_ext.subtype];  // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);                                        // Check configuration
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set function */
    p_handle->p_func = p_func;

    /* Call function (cast to match the argument type with the primitive function) */
    fsp_err_t  err      = FSP_ERR_CRYPTO_RSIP_FATAL;
    rsip_ret_t rsip_ret = RSIP_RET_UNKNOWN;
    switch (mode)
    {
        /* Plain IV */
        case RSIP_AES_AEAD_MODE_GCM_ENC:
        case RSIP_AES_AEAD_MODE_GCM_DEC:
        {
            /* Generate IV */
            uint32_t hashed_ivec[4] =
            {
                0
            };

            err = gcm_iv_prepare(&gp_func_aes_cipher[key_type_ext.subtype],
                                 p_nonce,
                                 nonce_length,
                                 p_wrapped_key,
                                 hashed_ivec);

            if (FSP_SUCCESS == err)
            {
                rsip_ret = p_func->p_init((const uint32_t *) p_wrapped_key->p_value, hashed_ivec);
            }

            break;
        }

        /* Wrapped IV */
        case RSIP_AES_AEAD_MODE_GCM_ENC_WRAPPED_IV:
        case RSIP_AES_AEAD_MODE_GCM_DEC_WRAPPED_IV:
        {
            err      = FSP_SUCCESS;
            rsip_ret = p_func->p_init_wrapped_iv((const uint32_t *) p_wrapped_key->p_value, (const uint32_t *) p_nonce);

            break;
        }

        default:
        {
            /* Invalid mode */
        }
    }

    if (FSP_SUCCESS == err)
    {
        /* Check error */
        switch (rsip_ret)
        {
            case RSIP_RET_PASS:
            {
                /*
                 * State transition
                 * RSIP_AES_AEAD_MODE_GCM_ENC -> RSIP_STATE_AES_GCM_ENC_UPDATE_AAD
                 * RSIP_AES_AEAD_MODE_GCM_DEC -> RSIP_STATE_AES_GCM_DEC_UPDATE_AAD
                 */
                p_instance_ctrl->state =
                    ((RSIP_AES_AEAD_MODE_GCM_ENC == mode) || (RSIP_AES_AEAD_MODE_GCM_ENC_WRAPPED_IV == mode)) ?
                    RSIP_STATE_AES_GCM_ENC_UPDATE_AAD : RSIP_STATE_AES_GCM_DEC_UPDATE_AAD;

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
    }
    else
    {
        /* Do nothing */
    }

    return err;
}

/*******************************************************************************************************************//**
 * Inputs aad and executes encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 **********************************************************************************************************************/
static fsp_err_t gcm_aad_update (rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_gcm;
    rsip_func_subset_aes_gcm_t * p_func          = (rsip_func_subset_aes_gcm_t *) p_handle->p_func;

    uint32_t length_rest = 0;

    /* Input AAD */
    if (0 != aad_length)
    {
        p_handle->total_aad_length += aad_length;

        if ((p_handle->buffered_length + aad_length) >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
        {
            /* Input remaining data in buffer */
            memcpy((&p_handle->buffer[0] + p_handle->buffered_length),
                   p_aad,
                   RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);

            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_updateAad((uint32_t *) (p_handle->buffer),
                                r_rsip_byte_to_word_convert((RSIP_PRV_BYTE_SIZE_AES_BLOCK)));
            length_rest = aad_length -
                          (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
            memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

            /* Input block data */
            if (length_rest >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
            {
                /* Call function (cast to match the argument type with the primitive function) */
                p_func->p_updateAad((const uint32_t *) (p_aad +
                                                        (RSIP_PRV_BYTE_SIZE_AES_BLOCK -
                                                         p_handle->buffered_length)),
                                    r_rsip_byte_to_word_convert((length_rest / RSIP_PRV_BYTE_SIZE_AES_BLOCK) *
                                                                RSIP_PRV_BYTE_SIZE_AES_BLOCK));
                length_rest -= ((length_rest / RSIP_PRV_BYTE_SIZE_AES_BLOCK) * RSIP_PRV_BYTE_SIZE_AES_BLOCK);
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
 **********************************************************************************************************************/
static fsp_err_t gcm_update (rsip_ctrl_t         * p_ctrl,
                             uint8_t const * const p_input,
                             uint32_t const        input_length,
                             uint8_t * const       p_output,
                             uint32_t * const      p_output_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_gcm;
    rsip_func_subset_aes_gcm_t * p_func          = (rsip_func_subset_aes_gcm_t *) p_handle->p_func;

    uint32_t length_rest = 0;
    *p_output_length = 0;

    /* If plaintext/ciphertext is input for the first time, input remaining AAD and prohibit new AAD input */
    switch (p_instance_ctrl->state)
    {
        case RSIP_STATE_AES_GCM_ENC_UPDATE_AAD:
        case RSIP_STATE_AES_GCM_DEC_UPDATE_AAD:
        {
            gcm_aad_input_terminate(p_instance_ctrl);
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    /* Input plaintext/ciphertext */
    if (0 != input_length)
    {
        p_handle->total_length += input_length;
        if ((p_handle->buffered_length + input_length) >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
        {
            /* Input remaining data in buffer */
            memcpy((&p_handle->buffer[0] + p_handle->buffered_length),
                   p_input,
                   RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);

            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_update((uint32_t *) (p_handle->buffer), (uint32_t *) (p_output),
                             r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_AES_BLOCK));
            length_rest = input_length -
                          (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
            *p_output_length += RSIP_PRV_BYTE_SIZE_AES_BLOCK;
            memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

            /* Input block data */
            if (length_rest >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
            {
                uint32_t block_data_length = (length_rest / RSIP_PRV_BYTE_SIZE_AES_BLOCK) *
                                             RSIP_PRV_BYTE_SIZE_AES_BLOCK;

                /* Call function (cast to match the argument type with the primitive function) */
                p_func->p_update((const uint32_t *) (p_input +
                                                     (RSIP_PRV_BYTE_SIZE_AES_BLOCK -
                                                      p_handle->buffered_length)),
                                 (uint32_t *) (p_output + RSIP_PRV_BYTE_SIZE_AES_BLOCK),
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
 * Finalizes an AES-GCM encryption.
 *
 * If there is 16-byte fractional data indicated by the total data length of the value of p_plain that was input by
 * R_RSIP_AES_GCM_EncryptUpdate(), this API will output the result of encrypting that fractional data to p_cipher.
 * Here, the portion that does not reach 16 bytes will be padded with zeros.
 *
 * @param[in,out] p_ctrl          Pointer to control block.
 * @param[out]    p_output        Pointer to destination of ciphertext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of ciphertext length.
 * @param[out]    p_tag           Pointer to destination of tag for authentication. The length is 16 bytes.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t gcm_finish (rsip_ctrl_t * const p_ctrl,
                             uint8_t * const     p_output,
                             uint32_t * const    p_output_length,
                             uint8_t * const     p_tag)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_gcm;
    rsip_func_subset_aes_gcm_t * p_func          = (rsip_func_subset_aes_gcm_t *) p_handle->p_func;

    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };

    /* If unprocessed AAD still exists in buffer, input it */
    if (RSIP_STATE_AES_GCM_ENC_UPDATE_AAD == p_instance_ctrl->state)
    {
        gcm_aad_input_terminate(p_instance_ctrl);
    }

    /* Set remaining data */
    if ((0 != (p_handle->total_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK)) ||
        (0 == p_handle->total_length))
    {
        memset(p_handle->buffer + p_handle->buffered_length, 0,
               (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length));
    }

    /* Set parameters */
    aad_bit_size[0]  = bswap_32big(r_rsip_byte_to_bit_convert_upper(p_handle->total_aad_length));
    aad_bit_size[1]  = bswap_32big(r_rsip_byte_to_bit_convert_lower(p_handle->total_aad_length));
    data_bit_size[0] = bswap_32big((r_rsip_byte_to_bit_convert_upper(p_handle->total_length)));
    data_bit_size[1] = bswap_32big(r_rsip_byte_to_bit_convert_lower(p_handle->total_length));
    *p_output_length = p_handle->buffered_length;

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_encryptFinal((uint32_t *) (p_handle->buffer), aad_bit_size, data_bit_size, (uint32_t *) p_output,
                               (uint32_t *) p_tag);

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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
 * Finalizes an AES-GCM decryption.
 *
 * If there is 16-byte fractional data indicated by the total data length of the value of p_cipher that was input by
 * R_RSIP_AES_GCM_DecryptUpdate(), this API will output the result of decrypting that fractional data to p_cipher.
 * Here, the portion that does not reach 16 bytes will be padded with zeros.
 *
 * @param[in,out] p_ctrl         Pointer to control block.
 * @param[out]    p_output        Pointer to destination of plaintext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of plaintext length.
 * @param[in]     p_tag          Pointer to tag for authentication. The length depends on tag_length.
 * @param[in]     tag_length     Byte length of tag. Must be 1 to 16.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  tag_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t gcm_verify (rsip_ctrl_t * const   p_ctrl,
                             uint8_t * const       p_output,
                             uint32_t * const      p_output_length,
                             uint8_t const * const p_tag,
                             uint32_t const        tag_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_gcm;
    rsip_func_subset_aes_gcm_t * p_func          = (rsip_func_subset_aes_gcm_t *) p_handle->p_func;

    /* tag_length must be from 1 to 16 */
    FSP_ERROR_RETURN((0 < tag_length) && (tag_length <= 16), FSP_ERR_INVALID_SIZE);

    uint32_t aad_bit_size[2] =
    {
        0
    };
    uint32_t data_bit_size[2] =
    {
        0
    };
    uint32_t tag_length_tmp[1] =
    {
        0
    };
    uint32_t tag_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t)] =
    {
        0
    };

    /* If unprocessed AAD still exists in buffer, input it */
    if (RSIP_STATE_AES_GCM_DEC_UPDATE_AAD == p_instance_ctrl->state)
    {
        gcm_aad_input_terminate(p_instance_ctrl);
    }

    /* Set remaining data */
    if ((0 != (p_handle->total_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK)) ||
        (0 == p_handle->total_length))
    {
        memset(p_handle->buffer + p_handle->buffered_length, 0,
               (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length));
    }

    /* Copy tag */
    memcpy(tag_tmp, p_tag, tag_length);

    /* Set parameters */
    aad_bit_size[0]   = bswap_32big(r_rsip_byte_to_bit_convert_upper(p_handle->total_aad_length));
    aad_bit_size[1]   = bswap_32big(r_rsip_byte_to_bit_convert_lower(p_handle->total_aad_length));
    data_bit_size[0]  = bswap_32big(r_rsip_byte_to_bit_convert_upper(p_handle->total_length));
    data_bit_size[1]  = bswap_32big(r_rsip_byte_to_bit_convert_lower(p_handle->total_length));
    tag_length_tmp[0] = bswap_32big(tag_length);
    *p_output_length  = p_handle->buffered_length;

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func->p_decryptFinal((uint32_t *) (p_handle->buffer),
                                                 (uint32_t *) tag_tmp,
                                                 aad_bit_size,
                                                 data_bit_size,
                                                 (uint32_t *) tag_length_tmp,
                                                 (uint32_t *) p_output);

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

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

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
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

/*******************************************************************************************************************//**
 * Generates of input parameter for AES-GCM functions.
 *
 * @param[in]     p_func_aes_cipher     Pointer to function subset of AES cipher (AES-ECB)
 * @param[in]     p_initial_vector      Pointer to initialization vector.
 * @param[in]     initial_vector_length Initial vector byte size.
 * @param[in]     p_wrapped_key         Wrapped key area.
 * @param[out]    p_hashed_ivec         Pointer to destination of initialization vector
 *                                      (using length of initial_vector_length as a condition)
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *********************************************************************************************************************/
static fsp_err_t gcm_iv_prepare (const rsip_func_subset_aes_cipher_t * p_func_aes_cipher,
                                 const uint8_t                       * p_initial_vector,
                                 uint32_t                              initial_vector_length,
                                 const rsip_wrapped_key_t            * p_wrapped_key,
                                 uint32_t                            * p_hashed_ivec)
{
    uint32_t hash_subkey[4] =
    {
        0
    };
    uint32_t hashed_ivec_tmp[4] =
    {
        0
    };
    uint32_t zero[4] =
    {
        0
    };
    uint32_t ivec_length_rest = 0;
    uint32_t ivec_bit_len[4]  =
    {
        0
    };
    uint32_t ivec_tmp[4] =
    {
        0
    };

    fsp_err_t  err      = FSP_ERR_CRYPTO_RSIP_FATAL;
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    /* If initial_vector_length is 12 (96 bit), hashed_ivec is (initial_vector || 0^{31} || 1)  */
    if (12U == initial_vector_length)
    {
        memcpy(p_hashed_ivec, p_initial_vector, 12U);
        p_hashed_ivec[3] = bswap_32big(0x00000001U);
        err              = FSP_SUCCESS;
    }
    /* If iv_len is not 12 (96 bit), calculate GHASH */
    else
    {
        /* Call function (cast to match the argument type with the primitive function) */
        rsip_ret = p_func_aes_cipher->p_init_ecb_enc((const uint32_t *) p_wrapped_key->p_value, zero);
        if (RSIP_RET_PASS == rsip_ret)
        {
            p_func_aes_cipher->p_update(zero, hash_subkey, RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t));
            rsip_ret = p_func_aes_cipher->p_final();
        }

        if (RSIP_RET_PASS == rsip_ret)
        {
            if (RSIP_PRV_BYTE_SIZE_AES_BLOCK <= initial_vector_length)
            {
                /* Call function (cast to match the argument type with the primitive function) */
                rsip_ret =
                    gp_func_ghash_compute(hash_subkey, zero, (const uint32_t *) p_initial_vector, hashed_ivec_tmp,
                                          (initial_vector_length / RSIP_PRV_BYTE_SIZE_AES_BLOCK) * sizeof(uint32_t));
                if (RSIP_RET_PASS == rsip_ret)
                {
                    ivec_length_rest = initial_vector_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK;
                    if (0 != ivec_length_rest)
                    {
                        memcpy(ivec_tmp, p_initial_vector + (initial_vector_length - ivec_length_rest),
                               ivec_length_rest);

                        /* Call function (cast to match the argument type with the primitive function) */
                        rsip_ret = gp_func_ghash_compute(hash_subkey,
                                                         hashed_ivec_tmp,
                                                         ivec_tmp,
                                                         hashed_ivec_tmp,
                                                         RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t));
                    }
                }
            }
            else
            {
                memcpy(ivec_tmp, p_initial_vector, initial_vector_length);

                /* Call function (cast to match the argument type with the primitive function) */
                rsip_ret = gp_func_ghash_compute(hash_subkey,
                                                 zero,
                                                 ivec_tmp,
                                                 hashed_ivec_tmp,
                                                 RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t));
            }

            if (RSIP_RET_PASS == rsip_ret)
            {
                /* Calculate ivec bit length */
                ivec_bit_len[0] = 0U;
                ivec_bit_len[1] = 0U;
                ivec_bit_len[2] = bswap_32big(r_rsip_byte_to_bit_convert_upper(initial_vector_length));
                ivec_bit_len[3] = bswap_32big(r_rsip_byte_to_bit_convert_lower(initial_vector_length));

                /* Call function (cast to match the argument type with the primitive function) */
                rsip_ret = gp_func_ghash_compute(hash_subkey,
                                                 hashed_ivec_tmp,
                                                 ivec_bit_len,
                                                 p_hashed_ivec,
                                                 RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t));
            }
        }

        /* Check error */
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
    }

    return err;
}

static void gcm_aad_input_terminate (rsip_instance_ctrl_t * p_instance_ctrl)
{
    rsip_aes_gcm_handle_t      * p_handle = &p_instance_ctrl->handle.aes_gcm;
    rsip_func_subset_aes_gcm_t * p_func   = (rsip_func_subset_aes_gcm_t *) p_handle->p_func;

    if (0 != (p_handle->buffered_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK))
    {
        /* Input remaining AAD */
        memset(&p_handle->buffer[0] + p_handle->buffered_length,
               0,
               RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);

        /* Call function (cast to match the argument type with the primitive function) */
        p_func->p_updateAad((uint32_t *) (p_handle->
                                          buffer),
                            r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_AES_BLOCK));
    }

    /* Reset buffer */
    memset(p_handle->buffer, 0, sizeof(p_handle->buffer));
    p_handle->buffered_length = 0;

    /* Prohibit AAD input and start plaintext/ciphertext input */
    p_func->p_updateTransition();

    /*
     * State transition
     * RSIP_STATE_AES_GCM_ENC_UPDATE_AAD -> RSIP_STATE_AES_GCM_ENC_UPDATE_TEXT
     * RSIP_STATE_AES_GCM_DEC_UPDATE_AAD -> RSIP_STATE_AES_GCM_DEC_UPDATE_TEXT
     */
    p_instance_ctrl->state = (p_instance_ctrl->state == RSIP_STATE_AES_GCM_ENC_UPDATE_AAD) ?
                             RSIP_STATE_AES_GCM_ENC_UPDATE_TEXT : RSIP_STATE_AES_GCM_DEC_UPDATE_TEXT;
}

/*******************************************************************************************************************//**
 * Prepares an AES-CCM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 **********************************************************************************************************************/
static fsp_err_t ccm_init (rsip_ctrl_t              * p_ctrl,
                           rsip_aes_aead_mode_t       mode,
                           const rsip_wrapped_key_t * p_wrapped_key,
                           const uint8_t            * p_nonce,
                           uint32_t                   nonce_length)
{
    rsip_instance_ctrl_t  * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t * p_handle        = &p_instance_ctrl->handle.aes_ccm;

    rsip_key_type_extend_t             key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    const rsip_func_subset_aes_ccm_t * p_func       =
        (RSIP_AES_AEAD_MODE_CCM_ENC == mode) ?
        &gp_func_aes_ccm_enc[key_type_ext.subtype] : &gp_func_aes_ccm_dec[key_type_ext.subtype];  // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN((p_func->p_encryptInit || p_func->p_decryptInit), FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Check length */
    FSP_ERROR_RETURN((7 <= nonce_length) && (nonce_length <= 13), FSP_ERR_INVALID_SIZE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set function */
    p_handle->p_func = p_func;

    /* Copy wrapped key */
    p_handle->wrapped_key.type    = p_wrapped_key->type;
    p_handle->wrapped_key.p_value = p_handle->wrapped_key_value;
    memcpy(p_handle->wrapped_key_value, p_wrapped_key->p_value, RSIP_BYTE_SIZE_WRAPPED_KEY(p_wrapped_key->type));

    /* Copy nonce */
    memcpy(p_handle->nonce_buffer, p_nonce, nonce_length);
    p_handle->nonce_length = nonce_length;

    /*
     * State transition
     * RSIP_AES_AEAD_MODE_CCM_ENC -> RSIP_STATE_AES_CCM_ENC_SET_LENGTH
     * RSIP_AES_AEAD_MODE_CCM_DEC -> RSIP_STATE_AES_CCM_DEC_SET_LENGTH
     */
    p_instance_ctrl->state = (RSIP_AES_AEAD_MODE_CCM_ENC == mode) ?
                             RSIP_STATE_AES_CCM_ENC_SET_LENGTH : RSIP_STATE_AES_CCM_DEC_SET_LENGTH;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set lengths of AES-CCM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 **********************************************************************************************************************/
static fsp_err_t ccm_length_set (rsip_ctrl_t * const p_ctrl,
                                 uint32_t const      total_aad_length,
                                 uint32_t const      total_text_length,
                                 uint32_t const      tag_length)
{
    rsip_instance_ctrl_t  * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t * p_handle        = &p_instance_ctrl->handle.aes_ccm;

    /* Check length */
    FSP_ERROR_RETURN(total_aad_length <= RSIP_PRV_BYTE_SIZE_CCM_AAD_MAX, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN((tag_length % 2 == 0) &&
                     (4 <= tag_length) &&
                     (tag_length <= 16),
                     FSP_ERR_INVALID_SIZE); // 4, 6, 8, 10, 12, 14, or 16

    /* Set lengths */
    p_handle->total_aad_length = total_aad_length;
    p_handle->total_length     = total_text_length;
    p_handle->tag_length       = tag_length;

    /*
     * State transition
     * RSIP_STATE_AES_CCM_ENC_SET_LENGTH -> RSIP_STATE_AES_CCM_ENC_UPDATE_AAD
     * RSIP_STATE_AES_CCM_DEC_SET_LENGTH -> RSIP_STATE_AES_CCM_DEC_UPDATE_AAD
     */
    p_instance_ctrl->state = (p_instance_ctrl->state == RSIP_STATE_AES_CCM_ENC_SET_LENGTH) ?
                             RSIP_STATE_AES_CCM_ENC_UPDATE_AAD : RSIP_STATE_AES_CCM_DEC_UPDATE_AAD;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Inputs aad and executes encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  aad_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t ccm_aad_update (rsip_ctrl_t * p_ctrl, const uint8_t * p_aad, uint32_t aad_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_ccm;
    rsip_func_subset_aes_ccm_t * p_func          = (rsip_func_subset_aes_ccm_t *) p_handle->p_func;
    rsip_wrapped_key_t         * p_wrapped_key   = &p_handle->wrapped_key;

    /* Check length */
    FSP_ERROR_RETURN((p_handle->input_aad_length + aad_length) <= p_handle->total_aad_length, FSP_ERR_INVALID_SIZE);

    /* Copy AAD to buffer */
    memcpy(p_handle->buffer + p_handle->input_aad_length, p_aad, aad_length);
    p_handle->input_aad_length += aad_length;

    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    if (p_handle->input_aad_length == p_handle->total_aad_length)
    {
        /* format B and generate counter */
        uint8_t  counter[RSIP_PRV_BYTE_SIZE_AES_BLOCK];
        uint8_t  formatted_data[RSIP_PRV_BYTE_AES_CCM_B];
        uint32_t formatted_length = 0;
        memset(counter, 0, sizeof(counter));
        memset(formatted_data, 0, sizeof(formatted_data));
        ccm_format(p_handle->nonce_buffer,
                   p_handle->nonce_length,
                   p_handle->buffer,       // AAD
                   (uint8_t) p_handle->total_aad_length,
                   p_handle->total_length, // payload length
                   p_handle->tag_length,
                   counter,
                   formatted_data,
                   &formatted_length);

        /* Clear buffer for ccm_update */
        memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

        /* Call function (cast to match the argument type with the primitive function) */
        rsip_ret_t rsip_ret       = RSIP_RET_UNKNOWN;
        uint32_t   length_tmp     = bswap_32big(p_handle->total_length);
        uint32_t   tag_length_tmp = bswap_32big(p_handle->tag_length);
        if (RSIP_STATE_AES_CCM_ENC_UPDATE_AAD == p_instance_ctrl->state)
        {
            rsip_ret =
                p_func->p_encryptInit((const uint32_t *) p_wrapped_key->p_value,
                                      &length_tmp,
                                      (const uint32_t *) counter,
                                      (const uint32_t *) formatted_data,
                                      formatted_length);
        }
        else                           // RSIP_STATE_AES_CCM_DEC_UPDATE_AAD == p_instance_ctrl->state
        {
            rsip_ret =
                p_func->p_decryptInit((const uint32_t *) p_wrapped_key->p_value, &length_tmp, &tag_length_tmp,
                                      (const uint32_t *) counter, (const uint32_t *) formatted_data, formatted_length);
        }

        /* Check error */
        switch (rsip_ret)
        {
            case RSIP_RET_PASS:
            {
                /*
                 * State transition
                 * RSIP_AES_AEAD_MODE_CCM_ENC -> RSIP_STATE_AES_CCM_ENC_UPDATE_AAD
                 * RSIP_AES_AEAD_MODE_CCM_DEC -> RSIP_STATE_AES_CCM_DEC_UPDATE_AAD
                 */
                p_instance_ctrl->state = (RSIP_STATE_AES_CCM_ENC_UPDATE_AAD == p_instance_ctrl->state) ?
                                         RSIP_STATE_AES_CCM_ENC_UPDATE_TEXT : RSIP_STATE_AES_CCM_DEC_UPDATE_TEXT;

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

                /* State transition*/
                p_instance_ctrl->state = RSIP_STATE_MAIN;
                break;
            }

            default:
            {
                err = FSP_ERR_CRYPTO_RSIP_FATAL;
            }
        }
    }
    else
    {
        err = FSP_SUCCESS;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Inputs aad and executes encryption and decryption.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  input_length is illegal.
 **********************************************************************************************************************/
static fsp_err_t ccm_update (rsip_ctrl_t         * p_ctrl,
                             uint8_t const * const p_input,
                             uint32_t const        input_length,
                             uint8_t * const       p_output,
                             uint32_t * const      p_output_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_ccm;
    rsip_func_subset_aes_ccm_t * p_func          = (rsip_func_subset_aes_ccm_t *) p_handle->p_func;

    /* Check length */
    FSP_ERROR_RETURN((p_handle->input_length + input_length) <= p_handle->total_length, FSP_ERR_INVALID_SIZE);

    uint32_t length_rest = 0;
    *p_output_length = 0;

    p_handle->input_length += input_length;

    /* Input plaintext/ciphertext */
    if ((p_handle->buffered_length + input_length) >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
    {
        /* Input remaining data in buffer */
        memcpy(p_handle->buffer + p_handle->buffered_length,
               p_input,
               RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);

        /* Call function (cast to match the argument type with the primitive function) */
        p_func->p_update((uint32_t *) p_handle->buffer, (uint32_t *) p_output,
                         r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_AES_BLOCK));
        length_rest = input_length -
                      (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
        *p_output_length += RSIP_PRV_BYTE_SIZE_AES_BLOCK;

        /* Input block data */
        if (length_rest >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
        {
            uint32_t block_data_length = (length_rest / RSIP_PRV_BYTE_SIZE_AES_BLOCK) *
                                         RSIP_PRV_BYTE_SIZE_AES_BLOCK;

            /* Call function (cast to match the argument type with the primitive function) */
            p_func->p_update((uint32_t *) (p_input +
                                           (RSIP_PRV_BYTE_SIZE_AES_BLOCK -
                                            p_handle->buffered_length)),
                             (uint32_t *) (p_output + RSIP_PRV_BYTE_SIZE_AES_BLOCK),
                             r_rsip_byte_to_word_convert(block_data_length));
            length_rest      -= block_data_length;
            *p_output_length += block_data_length;
        }

        p_handle->buffered_length = 0;

        memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

        /* Store remaining data to buffer */
        memcpy(p_handle->buffer, p_input + (input_length - length_rest), length_rest);
        p_handle->buffered_length = length_rest;
    }
    else
    {
        /* Store remaining data to buffer */
        memcpy(p_handle->buffer + p_handle->buffered_length, p_input, input_length);
        p_handle->buffered_length += input_length;
    }

    if (p_handle->total_length == p_handle->input_length)
    {
        /*
         * State transition
         * RSIP_STATE_AES_CCM_ENC_UPDATE_TEXT -> RSIP_STATE_AES_CCM_ENC_FINISH
         * RSIP_STATE_AES_CCM_DEC_UPDATE_TEXT -> RSIP_STATE_AES_CCM_DEC_VERI
         */
        p_instance_ctrl->state = (p_instance_ctrl->state == RSIP_STATE_AES_CCM_ENC_UPDATE_TEXT) ?
                                 RSIP_STATE_AES_CCM_ENC_FINISH : RSIP_STATE_AES_CCM_DEC_VERI;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Finalizes an AES-CCM encryption.
 *
 * @param[in,out] p_ctrl          Pointer to control block.
 * @param[out]    p_output        Pointer to destination of ciphertext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of ciphertext length.
 * @param[out]    p_tag           Pointer to destination of tag for authentication. The length is 16 bytes.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t ccm_finish (rsip_ctrl_t * const p_ctrl,
                             uint8_t * const     p_output,
                             uint32_t * const    p_output_length,
                             uint8_t * const     p_tag)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_ccm;
    rsip_func_subset_aes_ccm_t * p_func          = (rsip_func_subset_aes_ccm_t *) p_handle->p_func;

    uint32_t length_tmp = bswap_32big(p_handle->total_length);
    uint8_t  tag_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK] =
    {
        0
    };
    uint32_t output_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK] =
    {
        0
    };

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_encryptFinal((uint32_t *) p_handle->buffer, &length_tmp, (uint32_t *) output_tmp,
                               (uint32_t *) tag_tmp);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            memcpy(p_output, output_tmp, p_handle->buffered_length);
            *p_output_length = p_handle->buffered_length;
            memcpy(p_tag, tag_tmp, p_handle->tag_length);

            err = FSP_SUCCESS;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* State transition*/
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return err;
}

/*******************************************************************************************************************//**
 * Finalizes an AES-CCM decryption.
 *
 * @param[in,out] p_ctrl          Pointer to control block.
 * @param[out]    p_output        Pointer to destination of plaintext. The fractional block is output.
 * @param[out]    p_output_length Pointer to destination of plaintext length.
 * @param[in]     p_tag           Pointer to tag for authentication. The length depends on tag_length.
 * @param[in]     tag_length      Byte length of tag. Must be 1 to 16.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  tag_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
 * @retval FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    Authentication is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t ccm_verify (rsip_ctrl_t * const   p_ctrl,
                             uint8_t * const       p_output,
                             uint32_t * const      p_output_length,
                             uint8_t const * const p_tag,
                             uint32_t const        tag_length)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_ccm;
    rsip_func_subset_aes_ccm_t * p_func          = (rsip_func_subset_aes_ccm_t *) p_handle->p_func;

    /* Check length */
    FSP_ERROR_RETURN(p_handle->tag_length == tag_length, FSP_ERR_INVALID_SIZE);

    uint32_t length_tmp     = bswap_32big(p_handle->total_length);
    uint32_t tag_length_tmp = bswap_32big(tag_length);
    uint8_t  tag_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK] =
    {
        0
    };
    uint32_t output_tmp[RSIP_PRV_BYTE_SIZE_AES_BLOCK] =
    {
        0
    };

    /* Copy tag */
    memcpy(tag_tmp, p_tag, tag_length);

    /* Call function (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func->p_decryptFinal((uint32_t *) p_handle->buffer, &length_tmp, (uint32_t *) tag_tmp, &tag_length_tmp,
                               (uint32_t *) output_tmp);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            memcpy(p_output, output_tmp, p_handle->buffered_length);
            *p_output_length = p_handle->buffered_length;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
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

    /* Reset handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* State transition*/
    p_instance_ctrl->state = RSIP_STATE_MAIN;

    return err;
}

/*******************************************************************************************************************//**
 * Format B and generate counter (SP 800-38C 5.4)
 *
 * @param[in]  nonce            Nonce.
 * @param[in]  nonce_len        Nonce data length (byte).
 * @param[in]  adata            Associated data.
 * @param[in]  a_len            Associated data length (byte).
 * @param[in]  payload_len      Payload length (byte).
 * @param[in]  mac_len          MAC data length (byte).
 * @param[out] counter          Counter blocks area.
 * @param[out] formatted_data   Formatted data area.
 * @param[out] formatted_length Formatted data length.
 *********************************************************************************************************************/
static void ccm_format (const uint8_t * nonce,
                        uint32_t        nonce_len,
                        const uint8_t * adata,
                        uint8_t         a_len,
                        uint32_t        payload_len,
                        uint32_t        mac_len,
                        uint8_t       * counter,
                        uint8_t       * formatted_data,
                        uint32_t      * formatted_length)
{
    uint8_t  flag                 = 0;
    uint8_t  mac_len_tmp          = 0;
    uint8_t  q_len                = 0;
    uint32_t formatted_length_tmp = 0;

    /* Out of range check */
    if (((7 > nonce_len) || (13 < nonce_len)) ||
        (((4 > mac_len) || (16 < mac_len)) || ((0 != (mac_len % 2)) || (RSIP_PRV_BYTE_SIZE_CCM_AAD_MAX < a_len))))
    {
        return;
    }

    /* formatting flag section in formatted data B */
    if (0 < a_len)
    {
        flag = 1 << 6;
    }

    mac_len_tmp = (uint8_t) ((mac_len - 2) / 2);
    mac_len_tmp = (uint8_t) (mac_len_tmp << 3);
    flag       |= mac_len_tmp;
    q_len       = (uint8_t) (15 - nonce_len);
    flag       |= (uint8_t) (q_len - 1);
    formatted_data[formatted_length_tmp] = flag;
    formatted_length_tmp++;

    /* adding nonce to formatted data B */
    memcpy(formatted_data + formatted_length_tmp, nonce, nonce_len);
    formatted_length_tmp += 11;
    if (12 <= nonce_len)
    {
        formatted_length_tmp++;
    }

    if (13 <= nonce_len)
    {
        formatted_length_tmp++;
    }

    /* adding Q to formatted data B */
    do
    {
        /* Casting uint32_t data to uint8_t data array. */
        formatted_data[formatted_length_tmp] = (uint8_t) (payload_len >> (8 * (15 - formatted_length_tmp)));
        formatted_length_tmp++;
    } while (16 != formatted_length_tmp);

    /* adding Adata to formatted data B */
    if (0 < a_len)
    {
        formatted_length_tmp++;
        formatted_data[formatted_length_tmp] = a_len;
        formatted_length_tmp++;
        memcpy(formatted_data + formatted_length_tmp, adata, a_len);
        formatted_length_tmp += a_len;
        if (0 != (formatted_length_tmp % RSIP_PRV_BYTE_SIZE_AES_BLOCK))
        {
            formatted_length_tmp +=
                (RSIP_PRV_BYTE_SIZE_AES_BLOCK - (formatted_length_tmp % RSIP_PRV_BYTE_SIZE_AES_BLOCK));
        }
    }

    *formatted_length = formatted_length_tmp >> 2;

    /* formatting flag section in counter0 */
    flag       = (uint8_t) (q_len - 1);
    counter[0] = flag;

    /* adding nonce to counter0 */
    memcpy(counter + 1, nonce, nonce_len);
}
