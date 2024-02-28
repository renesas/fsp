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

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static rsip_func_key_generate_t       select_func_key_generate(rsip_key_type_t key_type);
static rsip_func_key_pair_generate_t  select_func_key_pair_generate(rsip_key_pair_type_t key_pair_type);
static rsip_func_encrypted_key_wrap_t select_func_encrypted_key_wrap(rsip_key_type_t key_type);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_ecc_param1_pos[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QX,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_521_QX,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
    [RSIP_KEY_ECC_BRAINPOOLP384R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QX,
    [RSIP_KEY_ECC_BRAINPOOLP512R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_512_QX,
    [RSIP_KEY_ECC_EDWARDS25519]    = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_EDWARDS25519_Q
};

static const uint32_t gs_ecc_param1_len[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_BYTE_SIZE_ECC_384_PARAM,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_BYTE_SIZE_ECC_521_PARAM,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP384R1] = RSIP_PRV_BYTE_SIZE_ECC_384_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP512R1] = RSIP_PRV_BYTE_SIZE_ECC_512_PARAM,
    [RSIP_KEY_ECC_EDWARDS25519]    = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM
};

static const uint32_t gs_ecc_param2_pos[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QY,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_521_QY,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
    [RSIP_KEY_ECC_BRAINPOOLP384R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_384_QY,
    [RSIP_KEY_ECC_BRAINPOOLP512R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_512_QY,
    [RSIP_KEY_ECC_EDWARDS25519]    = 0
};

static const uint32_t gs_ecc_param2_len[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_SECP384R1]       = RSIP_PRV_BYTE_SIZE_ECC_384_PARAM,
    [RSIP_KEY_ECC_SECP521R1]       = RSIP_PRV_BYTE_SIZE_ECC_521_PARAM,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP384R1] = RSIP_PRV_BYTE_SIZE_ECC_384_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP512R1] = RSIP_PRV_BYTE_SIZE_ECC_512_PARAM,
    [RSIP_KEY_ECC_EDWARDS25519]    = 0
};

static const uint32_t gs_rsa_n_pos[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_1024] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_1024_N,
    [RSIP_KEY_RSA_2048] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_2048_N,
    [RSIP_KEY_RSA_3072] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_3072_N,
    [RSIP_KEY_RSA_4096] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_4096_N
};

static const uint32_t gs_rsa_n_len[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_1024] = RSIP_PRV_BYTE_SIZE_RSA_1024_N,
    [RSIP_KEY_RSA_2048] = RSIP_PRV_BYTE_SIZE_RSA_2048_N,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_BYTE_SIZE_RSA_3072_N,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_BYTE_SIZE_RSA_4096_N
};

static const uint32_t gs_rsa_e_pos[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_1024] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_1024_E,
    [RSIP_KEY_RSA_2048] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_2048_E,
    [RSIP_KEY_RSA_3072] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_3072_E,
    [RSIP_KEY_RSA_4096] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_RSA_4096_E
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const rsip_api_t g_rsip_on_rsip =
{
    .open                 = R_RSIP_Open,
    .close                = R_RSIP_Close,
    .randomNumberGenerate = R_RSIP_RandomNumberGenerate,
    .keyGenerate          = R_RSIP_KeyGenerate,
    .keyPairGenerate      = R_RSIP_KeyPairGenerate,
    .encryptedKeyWrap     = R_RSIP_EncryptedKeyWrap,
    .publicKeyExport      = R_RSIP_PublicKeyExport,
    .aesCipherInit        = R_RSIP_AES_Cipher_Init,
    .aesCipherUpdate      = R_RSIP_AES_Cipher_Update,
    .aesCipherFinish      = R_RSIP_AES_Cipher_Finish,
    .aesAeadInit          = R_RSIP_AES_AEAD_Init,
    .aesAeadLengthsSet    = R_RSIP_AES_AEAD_LengthsSet,
    .aesAeadAadUpdate     = R_RSIP_AES_AEAD_AADUpdate,
    .aesAeadUpdate        = R_RSIP_AES_AEAD_Update,
    .aesAeadFinish        = R_RSIP_AES_AEAD_Finish,
    .aesAeadVerify        = R_RSIP_AES_AEAD_Verify,
    .aesMacInit           = R_RSIP_AES_MAC_Init,
    .aesMacUpdate         = R_RSIP_AES_MAC_Update,
    .aesMacSignFinish     = R_RSIP_AES_MAC_SignFinish,
    .aesMacVerifyFinish   = R_RSIP_AES_MAC_VerifyFinish,
    .ecdsaSign            = R_RSIP_ECDSA_Sign,
    .ecdsaVerify          = R_RSIP_ECDSA_Verify,
    .rsaEncrypt           = R_RSIP_RSA_Encrypt,
    .rsaDecrypt           = R_RSIP_RSA_Decrypt,
    .rsaesPkcs1V15Encrypt = R_RSIP_RSAES_PKCS1_V1_5_Encrypt,
    .rsaesPkcs1V15Decrypt = R_RSIP_RSAES_PKCS1_V1_5_Decrypt,
    .rsaesOaepEncrypt     = R_RSIP_RSAES_OAEP_Encrypt,
    .rsaesOaepDecrypt     = R_RSIP_RSAES_OAEP_Decrypt,
    .rsassaPkcs1V15Sign   = R_RSIP_RSASSA_PKCS1_V1_5_Sign,
    .rsassaPkcs1V15Verify = R_RSIP_RSASSA_PKCS1_V1_5_Verify,
    .rsassaPssSign        = R_RSIP_RSASSA_PSS_Sign,
    .rsassaPssVerify      = R_RSIP_RSASSA_PSS_Verify,
    .shaCompute           = R_RSIP_SHA_Compute,
    .shaInit              = R_RSIP_SHA_Init,
    .shaUpdate            = R_RSIP_SHA_Update,
    .shaFinish            = R_RSIP_SHA_Finish,
    .shaSuspend           = R_RSIP_SHA_Suspend,
    .shaResume            = R_RSIP_SHA_Resume,
    .hmacCompute          = R_RSIP_HMAC_Compute,
    .hmacVerify           = R_RSIP_HMAC_Verify,
    .hmacInit             = R_RSIP_HMAC_Init,
    .hmacUpdate           = R_RSIP_HMAC_Update,
    .hmacSignFinish       = R_RSIP_HMAC_SignFinish,
    .hmacVerifyFinish     = R_RSIP_HMAC_VerifyFinish,
    .hmacSuspend          = R_RSIP_HMAC_Suspend,
    .hmacResume           = R_RSIP_HMAC_Resume,
};

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables use of Renesas Secure IP functionality.<br>
 * Implements @ref rsip_api_t::open.
 * 
 * \<Operational State><br>
 * This API can only be executed in the STATE_INITIAL, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal1"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_MAIN</td>
 * <tr><td>Others<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_ALREADY_OPEN                  Module is already open.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Internal key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Hardware initialization is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption or hardware fault is detected.
 *
 * @note  This version does not have an optional feature to disable TRNG initialization.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_Open (rsip_ctrl_t * const p_ctrl, rsip_cfg_t const * const p_cfg)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ERROR_RETURN(RSIP_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set configuration */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Device-specific sequence */
    rsip_ret_t rsip_ret = r_rsip_open();

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* Reset handle */
            r_rsip_handle_reset(&p_instance_ctrl->handle);

            /* State transition */
            p_instance_ctrl->state = RSIP_STATE_MAIN;

            /* Set driver status to open */
            p_instance_ctrl->open = RSIP_OPEN;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        /* Treat PASS_1 as FAIL */
        case RSIP_RET_FAIL:
        case RSIP_RET_PASS_1:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        case RSIP_RET_KEY_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        /* Treat RETRY as FATAL */
        case RSIP_RET_RETRY:
        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Disables use of Renesas Secure IP functionality.<br>
 * Implements @ref rsip_api_t::close.
 *
 * \<Operational State><br>
 * This API can be executed in except STATE_INITIAL, and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal2"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_INITIAL</td>
 * <tr><td>Others<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_Close (rsip_ctrl_t * const p_ctrl)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Device-specific sequence */
    rsip_ret_t rsip_ret = r_rsip_close();

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            /* Set driver status to close */
            p_instance_ctrl->open = 0U;

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
 * Generates a 128-bit random number.<br>
 * Implements @ref rsip_api_t::randomNumberGenerate.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
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
fsp_err_t R_RSIP_RandomNumberGenerate (rsip_ctrl_t * const p_ctrl, uint8_t * const p_random)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_random);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    return r_rsip_random_number_generate(p_ctrl, p_random);
}

/*******************************************************************************************************************//**
 * Generate a wrapped symmetric key from a random number.
 * In this API, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.<br>
 * Implements @ref rsip_api_t::keyGenerate.
 *
 * \<Usage Precautions>
 * @arg Valid key types.
 *
 * <table>
 * <caption id="key_type"> </caption>
 * <tr><th>key_type<td>RSIP_KEY_TYPE_AES_128<br>
 * RSIP_KEY_TYPE_AES_256<br>
 * RSIP_KEY_TYPE_XTS_AES_128<br>
 * RSIP_KEY_TYPE_XTS_AES_256<br>
 * RSIP_KEY_TYPE_HMAC_SHA256
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-key-management "Key Management"
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KeyGenerate (rsip_ctrl_t * const        p_ctrl,
                              rsip_key_type_t const      key_type,
                              rsip_wrapped_key_t * const p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_key_generate_t p_func = select_func_key_generate(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_key->alg     = (uint8_t) r_rsip_key_type_to_alg(key_type);
            p_wrapped_key->subtype = r_rsip_key_type_to_subtype(key_type);

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
 * Generate a wrapped asymmetric key pair from a random number. In this API, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.<br>
 * Implements @ref rsip_api_t::keyPairGenerate.
 *
 * \<Usage Precautions>
 * @arg Valid key pair types.
 *
 * <table>
 * <caption id="key_pair_type"> </caption>
 * <tr><th>key_pair_type<td>RSIP_KEY_PAIR_TYPE_ECC_SECP256R1<br>
 * RSIP_KEY_PAIR_TYPE_ECC_SECP384R1<br>
 * RSIP_KEY_PAIR_TYPE_RSA_2048<br>
 * RSIP_KEY_PAIR_TYPE_RSA_3072<br>
 * RSIP_KEY_PAIR_TYPE_RSA_4096
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @sa Section @ref r-rsip-key-management "Key Management"
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KeyPairGenerate (rsip_ctrl_t * const        p_ctrl,
                                  rsip_key_pair_type_t const key_pair_type,
                                  rsip_wrapped_key_t * const p_wrapped_public_key,
                                  rsip_wrapped_key_t * const p_wrapped_private_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_key_pair_generate_t p_func = select_func_key_pair_generate(key_pair_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((uint32_t *) p_wrapped_public_key->value, (uint32_t *) p_wrapped_private_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_public_key->alg      = (uint8_t) r_rsip_key_pair_type_to_public_alg(key_pair_type);
            p_wrapped_public_key->subtype  = r_rsip_key_pair_type_to_subtype(key_pair_type);
            p_wrapped_private_key->alg     = (uint8_t) r_rsip_key_pair_type_to_private_alg(key_pair_type);
            p_wrapped_private_key->subtype = r_rsip_key_pair_type_to_subtype(key_pair_type);

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
 * Decrypt the encrypted user key with Key Update Key (KUK) and wrap it with the Hardware Unique Key (HUK).<br>
 * Implements @ref rsip_api_t::encryptedKeyWrap.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
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
 * @sa Section @ref r-rsip-key-management "Key Management"
 **********************************************************************************************************************/
fsp_err_t R_RSIP_EncryptedKeyWrap (rsip_ctrl_t * const                 p_ctrl,
                                   rsip_key_update_key_t const * const p_key_update_key,
                                   uint8_t const * const               p_initial_vector,
                                   rsip_key_type_t const               key_type,
                                   uint8_t const * const               p_encrypted_key,
                                   rsip_wrapped_key_t * const          p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_encrypted_key_wrap_t p_func = select_func_encrypted_key_wrap(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_key_update_key);
    FSP_ASSERT(p_initial_vector);
    FSP_ASSERT(p_encrypted_key);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Store KUK */
    r_rsip_kuk_store(p_key_update_key->value);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        p_func((uint32_t const *) p_initial_vector,
               (uint32_t const *) p_encrypted_key,
               (uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            p_wrapped_key->alg     = (uint8_t) r_rsip_key_type_to_alg(key_type);
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
 * Exports public key parameters from a wrapped key.<br>
 * Implements @ref rsip_api_t::publicKeyExport.
 *
 * \<Usage Precautions><br>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_ECC_xxx_PUBLIC or RSIP_KEY_TYPE_RSA_xxx_PUBLIC
 * @arg For ECC public keys, raw_public_key has QX placed first and QY placed after that.
 * @arg For RSA public keys, raw_public_key has N placed first and E placed after that.
 * @arg The value location of each elements in public key is shown in below:
 * <table>
 * <caption id="EccBitLen"> </caption>
 * <tr><th>ECC bit length<th>QX location<th>QY location</tr>
 * <tr><td>192(*)<td>0<td>24</td>
 * <tr><td>224(*)<td>0<td>28</td>
 * <tr><td>256<td>0<td>32</td>
 * <tr><td>384<td>0<td>48</td>
 * <tr><td>512(*)<td>0<td>64</td>
 * <tr><td>521(*)<td>0<td>66</td>
 * </table>
 *
 * <table>
 * <caption id="RsaBitLen"> </caption>
 * <tr><th>RSA bit length<th>N location<th>E location</tr>
 * <tr><td>1024(*)<td>0<td>128</td>
 * <tr><td>2048<td>0<td>256</td>
 * <tr><td>3072<td>0<td>384</td>
 * <tr><td>4096<td>0<td>512</td>
 * </table>
 * (*) These bit lengths are not supported in V.5.2.0.
 *
 * \<Operational State><br>
 * This API can be executed in any state including STATE_INITIAL, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @sa Section @ref r-rsip-key-management "Key Management"
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PublicKeyExport (rsip_wrapped_key_t const * const p_wrapped_public_key,
                                  uint8_t * const                  p_raw_public_key)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_raw_public_key);
#endif

    fsp_err_t err  = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
    uint8_t * base = (uint8_t *) p_wrapped_public_key->value;
    uint32_t  param1_pos;
    uint32_t  param1_len;
    uint32_t  param2_pos;
    uint32_t  param2_len;

    switch (p_wrapped_public_key->alg)
    {
        case RSIP_ALG_ECC_PUBLIC:
        {
            param1_pos = gs_ecc_param1_pos[p_wrapped_public_key->subtype];
            param1_len = gs_ecc_param1_len[p_wrapped_public_key->subtype];
            param2_pos = gs_ecc_param2_pos[p_wrapped_public_key->subtype];
            param2_len = gs_ecc_param2_len[p_wrapped_public_key->subtype];
            err        = FSP_SUCCESS;
            break;
        }

        case RSIP_ALG_RSA_PUBLIC:
        {
            param1_pos = gs_rsa_n_pos[p_wrapped_public_key->subtype];
            param1_len = gs_rsa_n_len[p_wrapped_public_key->subtype];
            param2_pos = gs_rsa_e_pos[p_wrapped_public_key->subtype];
            param2_len = RSIP_PRV_BYTE_SIZE_RSA_E;
            err        = FSP_SUCCESS;
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    if (FSP_SUCCESS == err)
    {
        memcpy(p_raw_public_key, base + param1_pos, param1_len);
        memcpy(p_raw_public_key + param1_len, base + param2_pos, param2_len);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Generates a 128-bit random number.
 *
 * @param[in,out] p_ctrl   Pointer to control block.
 * @param[out]    p_random Pointer to destination of random number. The length is 16 bytes.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t r_rsip_random_number_generate (rsip_ctrl_t * const p_ctrl, uint8_t * const p_random)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = g_func.p_rng((uint32_t *) p_random);

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

static rsip_func_key_generate_t select_func_key_generate (rsip_key_type_t key_type)
{
    rsip_func_key_generate_t ret     = NULL;
    rsip_alg_t               alg     = r_rsip_key_type_to_alg(key_type);
    uint32_t                 subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = g_func.p_key_generate_aes[subtype];
            break;
        }

        case RSIP_ALG_XTS_AES:
        {
            ret = g_func.p_key_generate_xts_aes[subtype];
            break;
        }

        case RSIP_ALG_CHACHA:
        {
            ret = g_func.p_key_generate_chacha[subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = g_func.p_key_generate_hmac[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

static rsip_func_key_pair_generate_t select_func_key_pair_generate (rsip_key_pair_type_t key_pair_type)
{
    rsip_func_key_pair_generate_t ret = NULL;
    rsip_alg_t alg     = r_rsip_key_pair_type_to_public_alg(key_pair_type);
    uint32_t   subtype = r_rsip_key_pair_type_to_subtype(key_pair_type);

    switch (alg)
    {
        case RSIP_ALG_ECC_PUBLIC:
        {
            ret = g_func.p_key_pair_generate_ecc[subtype];
            break;
        }

        case RSIP_ALG_RSA_PUBLIC:
        {
            ret = g_func.p_key_pair_generate_rsa[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

static rsip_func_encrypted_key_wrap_t select_func_encrypted_key_wrap (rsip_key_type_t key_type)
{
    rsip_func_encrypted_key_wrap_t ret = NULL;
    rsip_alg_t alg     = r_rsip_key_type_to_alg(key_type);
    uint32_t   subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = g_func.p_encrypted_key_wrap_aes[subtype];
            break;
        }

        case RSIP_ALG_XTS_AES:
        {
            ret = g_func.p_encrypted_key_wrap_xts_aes[subtype];
            break;
        }

        case RSIP_ALG_CHACHA:
        {
            ret = g_func.p_encrypted_key_wrap_chacha[subtype];
            break;
        }

        case RSIP_ALG_ECC_PUBLIC:
        {
            ret = g_func.p_encrypted_key_wrap_ecc_pub[subtype];
            break;
        }

        case RSIP_ALG_ECC_PRIVATE:
        {
            ret = g_func.p_encrypted_key_wrap_ecc_priv[subtype];
            break;
        }

        case RSIP_ALG_RSA_PUBLIC:
        {
            ret = g_func.p_encrypted_key_wrap_rsa_pub[subtype];
            break;
        }

        case RSIP_ALG_RSA_PRIVATE:
        {
            ret = g_func.p_encrypted_key_wrap_rsa_priv[subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = g_func.p_encrypted_key_wrap_hmac[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}
