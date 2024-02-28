/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
static fsp_err_t aes_final(rsip_ctrl_t * p_ctrl);

static fsp_err_t xts_init(rsip_ctrl_t              * p_ctrl,
                          rsip_aes_cipher_mode_t     mode,
                          const rsip_wrapped_key_t * p_wrapped_key,
                          const uint8_t            * p_initial_vector);
static fsp_err_t xts_update(rsip_ctrl_t * p_ctrl, const uint8_t * p_input, uint8_t * p_output, uint32_t input_length);
static fsp_err_t xts_final(rsip_ctrl_t * p_ctrl);
static fsp_err_t xts_final_primitive(rsip_func_subset_aes_xts_t * p_func,
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
 * Set parameters of AES cipher.<br>
 * Implements @ref rsip_api_t::aesCipherInit.
 *
 * \<Usage Precautions>
 * @arg p_initial_vector is not required for ECB mode.
 * @arg p_initial_vector is IV for CBC mode or XTS mode.
 * @arg p_initial_vector is nonce for CTR mode.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal3"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_AES</td>
 * <tr><td>Others<td>No change</td>
 * </table>
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
    FSP_ASSERT(p_initial_vector || (RSIP_AES_CIPHER_MODE_ECB_ENC == mode) ||
               (RSIP_AES_CIPHER_MODE_ECB_DEC == mode));
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN((RSIP_ALG_AES == p_wrapped_key->alg) ||
                     (RSIP_ALG_XTS_AES == p_wrapped_key->alg),
                     FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);
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
 * Encrypts plaintext.<br>
 * Implements @ref rsip_api_t::aesCipherUpdate.
 *
 * \<Usage Precautions>
 * @arg Requires prerequisite that R_RSIP_AES_Cipher_Init or R_RSIP_AES_Cipher_Update results in FSP_SUCCESS.
 * @arg The length is as follows:
 *
 * <table>
 * <caption id="length"> </caption>
 * <tr><th colspan="2">length</tr>
 * <tr><td>ECB,CBC,CTR<td>Must be 0 or a multiple of 16.</td>
 * <tr><td>XTS<td>Must be 0 or greater than or equal to 16.<br>
 * After an integer not divisible by 16 is input, update will no longer be able to execute.</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal4"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>Any<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
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
 * Finalize AES operation.<br>
 * Implements @ref rsip_api_t::aesCipherFinish.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal5"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_ERR_ASSERTION<br>FSP_ERR_NOT_OPEN<br>FSP_ERR_INVALID_STATE<td>No change</td>
 * <tr><td>Others<td>STATE_MAIN</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
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
            err = aes_final(p_ctrl);
            break;
        }

        /* AES-XTS (update, finish) */
        case RSIP_STATE_AES_XTS_UPDATE:
        case RSIP_STATE_AES_XTS_FINISH:
        {
            err = xts_final(p_ctrl);
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
 * Prepares an AES-AEAD function.<br>
 * Implements @ref rsip_api_t::aesAeadInit.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_key must be RSIP_KEY_TYPE_AES_xxx.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal6"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_AES_AEAD</td>
 * <tr><td>Others<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
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
    FSP_ASSERT(p_nonce);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_AES == p_wrapped_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);
#endif

    /* Check argument */
    fsp_err_t err = FSP_ERR_INVALID_ARGUMENT;
    switch (mode)
    {
        /* AES-GCM */
        case RSIP_AES_AEAD_MODE_GCM_ENC:
        case RSIP_AES_AEAD_MODE_GCM_DEC:
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
 * Set text and tag lengths for specific mode.<br>
 * Implements @ref rsip_api_t::aesAeadLengthsSet.
 *
 * \<Usage Precautions>
 * @arg Requires prerequisite that R_RSIP_AES_AEAD_Init results in FSP_SUCCESS.
 * @arg The lengths are as follows:
 * <table>
 * <caption id="length2"> </caption>
 * <tr><td>total_aad_length<td>Must be 110 or less.</td>
 * <tr><td>tag_length<td>The following values are allowed<br>4, 6, 8, 10, 12, 14, 16</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_AEAD, and there are no state transitions.<br>
 * However, this function can only be called once.<br>
 *
 * \<About CCM processing><br>
 * This API must be called directly after executing R_RSIP_AES_AEAD_Init API.<br>
 *
 * \<About GCM processing><br>
 * This API must NOT be called. Each input length is indeterminate and output tag length is fixed to 16 bytes.<br>
 * If called, FSP_ERR_INVALID_STATE will be returned.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
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
 * Inputs additional authentication data.<br>
 * Implements @ref rsip_api_t::aesAeadAadUpdate.
 *
 * \<Usage Precautions>
 * @arg For GCM processing requires prerequisite that R_RSIP_AES_AEAD_Init or R_RSIP_AES_AEAD_AADUpdate results in FSP_SUCCESS.
 * @arg For CCM processing requires prerequisite that R_RSIP_AES_AEAD_LengthsSet or R_RSIP_AES_AEAD_AADUpdate results in FSP_SUCCESS.
 * @arg This API can be called repeatedly, and in the case of CCM, it must be called at least once.
 * @arg This API cannot be called after the R_RSIP_AES_AEAD_Update API has been executed.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_AEAD, and there are no state transitions.
 *
 * \<About GCM processing><br>
 * For GCM processing, this API can be skipped.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
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
 * Inputs additional authentication data.<br>
 * Implements @ref rsip_api_t::aesAeadUpdate.
 *
 * \<Usage Precautions>
 * @arg For GCM processing requires prerequisite that R_RSIP_AES_AEAD_Init, R_RSIP_AES_AEAD_AADUpdate, or R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 * @arg For CCM processing requires prerequisite that R_RSIP_AES_AEAD_AADUpdate or R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 * @arg In the case of CCM, it must be called at least once.
 * @arg This API must be called after all input by R_RSIP_AES_AEAD_AADUpdate API is complete.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_AEAD, and there are no state transitions.
 *
 * \<About GMAC processing><br>
 * GMAC processing can be performed by skipping this API.<br>
 * For detailed usage, refer to the example code.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
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
 * Finalizes an AES-AEAD encryption.<br>
 * Implements @ref rsip_api_t::aesAeadFinish.
 *
 * \<Usage Precautions>
 * @arg RSIP_AES_AEAD_MODE_GCM_ENC or RSIP_AES_AEAD_MODE_CCM_ENC must be input as the mode in R_RSIP_AES_AEAD_Init.
 * @arg For GCM processing, requires prerequisite that R_RSIP_AES_AEAD_Init, R_RSIP_AES_AEAD_AADUpdate, or R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 * @arg For CCM processing, requires prerequisite that R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 *
 * \<Operational State><br>
 * This API can be executed in the STATE_AES_AEAD, and the state after execution changes as follows depending on the return value.
 *
 * <table>
 * <caption id="RetVal7"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_ERR_ASSERTION<br>FSP_ERR_NOT_OPEN<br>FSP_ERR_INVALID_STATE<td>No change</td>
 * <tr><td>Any<td>STATE_MAIN</td>
 * </table>
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
 * Finalizes an AES-AEAD decryption.<br>
 * Implements @ref rsip_api_t::aesAeadVerify.
 *
 * \<Usage Precautions>
 * @arg RSIP_AES_AEAD_MODE_GCM_DEC or RSIP_AES_AEAD_MODE_CCM_DEC must be input as the mode in R_RSIP_AES_AEAD_Init.
 * @arg For GCM processing, requires prerequisite that R_RSIP_AES_AEAD_Init, R_RSIP_AES_AEAD_AADUpdate, or R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 * @arg For CCM processing, requires prerequisite that R_RSIP_AES_AEAD_Update results in FSP_SUCCESS.
 *
 * \<Operational State><br>
 * This API can be executed in the STATE_AES_AEAD, and the state after execution changes as follows depending on the return value.
 *
 * <table>
 * <caption id="RetVal8"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_ERR_ASSERTION<br>FSP_ERR_NOT_OPEN<br>FSP_ERR_INVALID_STATE<td>No change</td>
 * <tr><td>Any<td>STATE_MAIN</td>
 * </table>
 *
 * If there is 16-byte fractional data indicated by the total data length of the value of p_cipher that was input by
 * R_RSIP_AES_GCM_DecryptUpdate(), this API will output the result of decrypting that fractional data to p_cipher.
 * Here, the portion that does not reach 16 bytes will be padded with zeros.
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
 * Prepares an AES-MAC generation and verification.<br>
 * Implements @ref rsip_api_t::aesMacInit.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_key must be RSIP_KEY_TYPE_AES_xxx.
 * @arg The argument mode only supports the feature listed below.
 * <table>
 * <caption id="MacMode"> </caption>
 * <tr><th>Mode<th>Corresponding Parameter</tr>
 * <tr><td>CMAC<td>RSIP_AES_MAC_MODE_CMAC</td>
 * </table>
 * * GMAC processing can be performed with R_RSIP_AES_AEAD_xxx API.<br>
 * 　 Refer to the desceription about R_RSIP_AES_AEAD_Update() API.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal9"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_AES_MAC</td>
 * <tr><td>Others<td>No change</td>
 * </table>
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
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_AES == p_wrapped_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(g_func.p_aes_mac[p_wrapped_key->subtype].p_init, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set primitive */
    p_handle->p_func = &g_func.p_aes_mac[p_wrapped_key->subtype];

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_func_subset_aes_mac_t * p_func = (rsip_func_subset_aes_mac_t *) p_handle->p_func;
    rsip_ret_t rsip_ret                 = p_func->p_init((const uint32_t *) p_wrapped_key->value);

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
 * Input message.<br>
 * Implements @ref rsip_api_t::aesMacUpdate.
 *
 * Inside this function, the data that is input by the user is buffered until the input value of p_message exceeds 16 bytes.
 * If the input value, p_message, is not a multiple of 16 bytes, it will be padded within the function.
 *
 * \<Usage Precautions>
 * @arg Requires prerequisite that R_RSIP_AES_MAC_Init or R_RSIP_AES_MAC_Update results in FSP_SUCCESS.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_MAC, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal10"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>Any<td>No change</td>
 * </table>
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

    rsip_aes_cmac_handle_t     * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_mac_t * p_func   = (rsip_func_subset_aes_mac_t *) p_handle->p_func;

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

        /* Call primitive (cast to match the argument type with the primitive function) */
        p_func->p_update((const uint32_t *) (p_handle->buffer),
                         r_rsip_byte_to_word_convert(RSIP_PRV_BYTE_SIZE_AES_BLOCK));
        length_rest = message_length -
                      (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
        memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

        /* Input block data */
        if (length_rest > RSIP_PRV_BYTE_SIZE_AES_BLOCK)
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
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
 * Finalizes an AES-MAC generation.<br>
 * Implements @ref rsip_api_t::aesMacSignFinish.
 *
 * \<Usage Precautions>
 * @arg Requires prerequisite that R_RSIP_AES_MAC_Init or R_RSIP_AES_MAC_Update results in FSP_SUCCESS.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_MAC, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal11"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_ERR_ASSERTION<br>FSP_ERR_NOT_OPEN<br>FSP_ERR_INVALID_STATE<td>No change</td>
 * <tr><td>Others<td>STATE_MAIN</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_INVALID_SIZE                  Input length is illegal.
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

    rsip_aes_cmac_handle_t     * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_mac_t * p_func   = (rsip_func_subset_aes_mac_t *) p_handle->p_func;

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

    /* Call primitive (cast to match the argument type with the primitive function) */
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
 * Finalizes an AES-MAC verification.<br>
 * Implements @ref rsip_api_t::aesMacVerifyFinish.
 *
 * \<Usage Precautions>
 * @arg Requires prerequisite that R_RSIP_AES_MAC_Init or R_RSIP_AES_MAC_Update results in FSP_SUCCESS.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_AES_MAC, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal12"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_ERR_ASSERTION<br>FSP_ERR_NOT_OPEN<br>FSP_ERR_INVALID_STATE<br>FSP_ERR_INVALID_SIZE<td>No change</td>
 * <tr><td>Others<td>STATE_MAIN</td>
 * </table>
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

    rsip_aes_cmac_handle_t     * p_handle = &p_instance_ctrl->handle.aes_cmac;
    rsip_func_subset_aes_mac_t * p_func   = (rsip_func_subset_aes_mac_t *) p_handle->p_func;

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

    /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
    rsip_instance_ctrl_t                * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t            * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    const rsip_func_subset_aes_cipher_t * p_func          = &g_func.p_aes_cipher[p_wrapped_key->subtype];

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func->p_init_ecb_enc, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set primitive */
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

        default:                       // RSIP_AES_CIPHER_MODE_CTR
        {
            p_func_init = p_func->p_init_ctr;
        }
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func_init((const uint32_t *) p_wrapped_key->value, (const uint32_t *) p_initial_vector);

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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
        /* Call primitive (cast to match the argument type with the primitive function) */
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
static fsp_err_t aes_final (rsip_ctrl_t * p_ctrl)
{
    rsip_instance_ctrl_t          * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t      * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_cipher_t * p_func          = (rsip_func_subset_aes_cipher_t *) p_handle->p_func;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_AES_CIPHER == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
    rsip_instance_ctrl_t             * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t         * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    const rsip_func_subset_aes_xts_t * p_func          = (RSIP_AES_CIPHER_MODE_XTS_ENC == mode) ?
                                                         &g_func.p_aes_xts_enc[p_wrapped_key->subtype] : &g_func.
                                                         p_aes_xts_dec[p_wrapped_key->subtype];

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set primitive */
    p_handle->p_func = p_func;

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func->p_init((const uint32_t *) p_wrapped_key->value, (const uint32_t *) p_initial_vector);

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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
            /* Call primitive (cast to match the argument type with the primitive function) */
            p_func->p_update((const uint32_t *) p_input,
                             (uint32_t *) p_output,
                             r_rsip_byte_to_word_convert(block_length));
        }

        /* Input remaining blocks */
        if (0 != (input_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK))
        {
            uint8_t buffer[RSIP_PRV_BYTE_SIZE_AES_BLOCK * 2] = {0};
            memcpy(buffer, p_input + block_length, remaining_length);

            err = xts_final_primitive(p_func, buffer, p_output + block_length, remaining_length);

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
static fsp_err_t xts_final (rsip_ctrl_t * p_ctrl)
{
    rsip_instance_ctrl_t       * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_cipher_handle_t   * p_handle        = &p_instance_ctrl->handle.aes_cipher;
    rsip_func_subset_aes_xts_t * p_func          = (rsip_func_subset_aes_xts_t *) p_handle->p_func;

    fsp_err_t err = FSP_SUCCESS;
    if (RSIP_STATE_AES_XTS_UPDATE == p_instance_ctrl->state)
    {
        /* If final function have not called (remaining blocks have not been input), Call primitive for empty message */
        err = xts_final_primitive(p_func, NULL, NULL, 0);
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
static fsp_err_t xts_final_primitive (rsip_func_subset_aes_xts_t * p_func,
                                      const uint8_t              * p_input,
                                      uint8_t                    * p_output,
                                      uint32_t                     input_length)
{
    uint32_t output_length_bit[1] =
    {
        bswap_32big(r_rsip_byte_to_bit_convert_lower(input_length))
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
    rsip_instance_ctrl_t             * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_gcm_handle_t            * p_handle        = &p_instance_ctrl->handle.aes_gcm;
    const rsip_func_subset_aes_gcm_t * p_func          = (RSIP_AES_AEAD_MODE_GCM_ENC == mode) ?
                                                         &g_func.p_aes_gcm_enc[p_wrapped_key->subtype] : &g_func.
                                                         p_aes_gcm_dec[p_wrapped_key->subtype];

#if RSIP_CFG_PARAM_CHECKING_ENABLE

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func->p_init, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Initialize handle */
    r_rsip_handle_reset(&p_instance_ctrl->handle);

    /* Set primitive */
    p_handle->p_func = p_func;

    /* Generate IV */
    uint32_t hashed_ivec[4] =
    {
        0
    };

    fsp_err_t err =
        gcm_iv_prepare(&g_func.p_aes_cipher[p_wrapped_key->subtype], p_nonce, nonce_length, p_wrapped_key, hashed_ivec);

    if (FSP_SUCCESS == err)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret_t rsip_ret = p_func->p_init((const uint32_t *) p_wrapped_key->value, hashed_ivec);

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
                p_instance_ctrl->state = (RSIP_AES_AEAD_MODE_GCM_ENC == mode) ?
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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

            /* Call primitive (cast to match the argument type with the primitive function) */
            p_func->p_updateAad((uint32_t *) (p_handle->buffer),
                                r_rsip_byte_to_word_convert((RSIP_PRV_BYTE_SIZE_AES_BLOCK)));
            length_rest = aad_length -
                          (RSIP_PRV_BYTE_SIZE_AES_BLOCK - p_handle->buffered_length);
            memset(p_handle->buffer, 0, sizeof(p_handle->buffer));

            /* Input block data */
            if (length_rest >= RSIP_PRV_BYTE_SIZE_AES_BLOCK)
            {
                /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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

            /* Call primitive (cast to match the argument type with the primitive function) */
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

                /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
    *p_output_length = p_handle->total_length;

    /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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
    *p_output_length  = p_handle->total_length;
    tag_length_tmp[0] = bswap_32big(tag_length);

    /* Call primitive (cast to match the argument type with the primitive function) */
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
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = p_func_aes_cipher->p_init_ecb_enc((const uint32_t *) p_wrapped_key->value, zero);
        if (RSIP_RET_PASS == rsip_ret)
        {
            p_func_aes_cipher->p_update(zero, hash_subkey, RSIP_PRV_BYTE_SIZE_AES_BLOCK / sizeof(uint32_t));
            rsip_ret = p_func_aes_cipher->p_final();
        }

        if (RSIP_RET_PASS == rsip_ret)
        {
            if (RSIP_PRV_BYTE_SIZE_AES_BLOCK <= initial_vector_length)
            {
                /* Call primitive (cast to match the argument type with the primitive function) */
                rsip_ret =
                    g_func.p_ghash_compute(hash_subkey, zero, (const uint32_t *) p_initial_vector, hashed_ivec_tmp,
                                           (initial_vector_length / RSIP_PRV_BYTE_SIZE_AES_BLOCK) * sizeof(uint32_t));
                if (RSIP_RET_PASS == rsip_ret)
                {
                    ivec_length_rest = initial_vector_length % RSIP_PRV_BYTE_SIZE_AES_BLOCK;
                    if (0 != ivec_length_rest)
                    {
                        memcpy(ivec_tmp, p_initial_vector + (initial_vector_length - ivec_length_rest),
                               ivec_length_rest);

                        /* Call primitive (cast to match the argument type with the primitive function) */
                        rsip_ret = g_func.p_ghash_compute(hash_subkey,
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

                /* Call primitive (cast to match the argument type with the primitive function) */
                rsip_ret = g_func.p_ghash_compute(hash_subkey,
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

                /* Call primitive (cast to match the argument type with the primitive function) */
                rsip_ret = g_func.p_ghash_compute(hash_subkey,
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

        /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 **********************************************************************************************************************/
static fsp_err_t ccm_init (rsip_ctrl_t              * p_ctrl,
                           rsip_aes_aead_mode_t       mode,
                           const rsip_wrapped_key_t * p_wrapped_key,
                           const uint8_t            * p_nonce,
                           uint32_t                   nonce_length)
{
    rsip_instance_ctrl_t             * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;
    rsip_aes_ccm_handle_t            * p_handle        = &p_instance_ctrl->handle.aes_ccm;
    const rsip_func_subset_aes_ccm_t * p_func          = (RSIP_AES_AEAD_MODE_CCM_ENC == mode) ?
                                                         &g_func.p_aes_ccm_enc[p_wrapped_key->subtype] : &g_func.
                                                         p_aes_ccm_dec[p_wrapped_key->subtype];

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

    /* Set primitive */
    p_handle->p_func = p_func;

    /* Copy wrapped key */
    memcpy(p_handle->wrapped_key, p_wrapped_key, RSIP_BYTE_SIZE_WRAPPED_KEY_AES_256);

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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
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
    rsip_wrapped_key_t         * p_wrapped_key   = (rsip_wrapped_key_t *) p_handle->wrapped_key;

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

        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret_t rsip_ret       = RSIP_RET_UNKNOWN;
        uint32_t   length_tmp     = bswap_32big(p_handle->total_length);
        uint32_t   tag_length_tmp = bswap_32big(p_handle->tag_length);
        if (RSIP_STATE_AES_CCM_ENC_UPDATE_AAD == p_instance_ctrl->state)
        {
            rsip_ret =
                p_func->p_encryptInit((const uint32_t *) p_wrapped_key->value,
                                      &length_tmp,
                                      (const uint32_t *) counter,
                                      (const uint32_t *) formatted_data,
                                      formatted_length);
        }
        else                           // RSIP_STATE_AES_CCM_DEC_UPDATE_AAD == p_instance_ctrl->state
        {
            rsip_ret =
                p_func->p_decryptInit((const uint32_t *) p_wrapped_key->value, &length_tmp, &tag_length_tmp,
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_INVALID_SIZE                  nonce_length is illegal.
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

        /* Call primitive (cast to match the argument type with the primitive function) */
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

            /* Call primitive (cast to match the argument type with the primitive function) */
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
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

    /* Call primitive (cast to match the argument type with the primitive function) */
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
            *p_output_length = p_handle->total_length;
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
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_INVALID_SIZE                  tag_length is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Internal error.
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

    /* Call primitive (cast to match the argument type with the primitive function) */
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
            *p_output_length = p_handle->total_length;

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
