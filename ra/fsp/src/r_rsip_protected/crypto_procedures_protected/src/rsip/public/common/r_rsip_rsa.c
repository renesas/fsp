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

/* Buffer size of EM */
#if RSIP_CFG_RSA_4096_ENABLE
 #define RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER    (RSIP_PRV_BYTE_SIZE_RSA_4096_N)
#elif RSIP_CFG_RSA_3072_ENABLE
 #define RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER    (RSIP_PRV_BYTE_SIZE_RSA_3072_N)
#elif RSIP_CFG_RSA_2048_ENABLE
 #define RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER    (RSIP_PRV_BYTE_SIZE_RSA_2048_N)
#else
 #define RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER    (RSIP_PRV_BYTE_SIZE_RSA_1024_N)
#endif

/* Buffer size of hash function */
#define RSIP_PRV_BYTE_SIZE_HASH_BUFFER       (RSIP_PRV_BYTE_SIZE_DIGEST_SHA512)

/* PS (padding string) of EMSA-PKCS1-v1_5 */
#define RSIP_PRV_EMSA_PKCS1_V1_5_PS          (0xFF)

/* Mask for EMSA-PSS */
#define RSIP_PRV_EMSA_PSS_MASK               (0xFF)

/* Trailer field of EMSA-PSS (constant) */
#define RSIP_PRV_EMSA_PSS_TRAILER_FIELD      (0xBC)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t r_rsip_rsa_encrypt(rsip_wrapped_key_t const * const p_wrapped_public_key,
                                    uint8_t const * const            p_plain,
                                    uint8_t * const                  p_cipher);
static fsp_err_t r_rsip_rsa_decrypt(rsip_wrapped_key_t const * const p_wrapped_private_key,
                                    uint8_t const * const            p_cipher,
                                    uint8_t * const                  p_plain);
static fsp_err_t eme_pkcs1_v1_5_ps_generate(rsip_ctrl_t * const p_ctrl, uint8_t * p_ps, uint32_t ps_length);
static fsp_err_t emsa_pkcs1_v1_5_encode(rsip_hash_type_t const hash_function,
                                        uint8_t const * const  p_hash,
                                        uint8_t * const        p_em,
                                        uint32_t const         em_length);
static fsp_err_t emsa_pss_encode(rsip_ctrl_t * const    p_ctrl,
                                 rsip_hash_type_t const hash_function,
                                 rsip_mgf_type_t const  mask_generation_function,
                                 uint32_t const         salt_length,
                                 uint8_t const * const  p_mhash,
                                 uint8_t * const        p_em,
                                 uint32_t const         em_bit_length);
static fsp_err_t emsa_pss_verify(rsip_ctrl_t * const    p_ctrl,
                                 rsip_hash_type_t const hash_function,
                                 rsip_mgf_type_t const  mask_generation_function,
                                 uint32_t const         salt_length,
                                 uint8_t const * const  p_mhash,
                                 uint8_t * const        p_em,
                                 uint32_t const         em_bit_length);
static fsp_err_t emsa_pss_h_generate(rsip_ctrl_t * const    p_ctrl,
                                     rsip_hash_type_t const hash_function,
                                     uint8_t const * const  p_mhash,
                                     uint32_t const         hlen,
                                     uint8_t const * const  p_salt,
                                     uint32_t const         slen,
                                     uint8_t * const        p_h);
static fsp_err_t emsa_pss_salt_generate(rsip_ctrl_t * const p_ctrl,
                                        uint8_t * const     p_salt,
                                        uint32_t const      salt_length);
fsp_err_t emsa_pss_ps_check(uint8_t const * const  p_db,
                            uint32_t const         dblen,
                            uint8_t const ** const pp_salt,
                            uint32_t * const       p_slen,
                            bool const             salt_auto_detection);
static fsp_err_t mgf1_mask(rsip_ctrl_t * const    p_ctrl,
                           rsip_hash_type_t const hash_function,
                           uint8_t const * const  p_mgf_seed,
                           uint32_t const         mgf_seed_len,
                           uint8_t * const        p_mask,
                           uint32_t const         mask_len);
static uint32_t             secure_memcmp(const void * buf1, const void * buf2, uint32_t num);
static void               * memxor(void * buf1, void * buf2, uint32_t num);
RSIP_PRV_STATIC_INLINE void stack_clear(void * p_buf, const uint32_t num);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

const uint32_t gs_hash_length[] =
{
    [RSIP_HASH_TYPE_SHA1]       = RSIP_PRV_BYTE_SIZE_DIGEST_SHA1,
    [RSIP_HASH_TYPE_SHA224]     = RSIP_PRV_BYTE_SIZE_DIGEST_SHA224,
    [RSIP_HASH_TYPE_SHA256]     = RSIP_PRV_BYTE_SIZE_DIGEST_SHA256,
    [RSIP_HASH_TYPE_SHA384]     = RSIP_PRV_BYTE_SIZE_DIGEST_SHA384,
    [RSIP_HASH_TYPE_SHA512]     = RSIP_PRV_BYTE_SIZE_DIGEST_SHA512,
    [RSIP_HASH_TYPE_SHA512_224] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA224,
    [RSIP_HASH_TYPE_SHA512_256] = RSIP_PRV_BYTE_SIZE_DIGEST_SHA256
};

static const uint32_t gs_key_length[RSIP_KEY_RSA_NUM] =
{
    [RSIP_KEY_RSA_1024] = RSIP_PRV_BYTE_SIZE_RSA_1024_N,
    [RSIP_KEY_RSA_2048] = RSIP_PRV_BYTE_SIZE_RSA_2048_N,
    [RSIP_KEY_RSA_3072] = RSIP_PRV_BYTE_SIZE_RSA_3072_N,
    [RSIP_KEY_RSA_4096] = RSIP_PRV_BYTE_SIZE_RSA_4096_N,
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
 * Encrypts plaintext with raw RSA.<br>
 * Implements @ref rsip_api_t::rsaEncrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_RSA_xxx_PUBLIC.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen1"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PUBLIC</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PUBLIC</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PUBLIC</td>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note This API provides RSA low-level primitives (RSAEP/RSAVP1).
 *       It should be used in conjunction with any padding scheme.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA_Encrypt (rsip_ctrl_t * const              p_ctrl,
                              rsip_wrapped_key_t const * const p_wrapped_public_key,
                              uint8_t const * const            p_plain,
                              uint8_t * const                  p_cipher)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_plain);
    FSP_ASSERT(p_cipher);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_public[p_wrapped_public_key->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    return r_rsip_rsa_encrypt(p_wrapped_public_key, p_plain, p_cipher);
}

/*******************************************************************************************************************//**
 * Decrypts ciphertext with raw RSA.<br>
 * Implements @ref rsip_api_t::rsaDecrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_private_key must be RSIP_KEY_TYPE_RSA_xxx_PRIVATE.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen2"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PRIVATE</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PRIVATE</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PRIVATE</td>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note This API provides RSA low-level primitives (RSADP/RSASP1).
 *       It should be used in conjunction with any padding scheme.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSA_Decrypt (rsip_ctrl_t * const              p_ctrl,
                              rsip_wrapped_key_t const * const p_wrapped_private_key,
                              uint8_t const * const            p_cipher,
                              uint8_t * const                  p_plain)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_cipher);
    FSP_ASSERT(p_plain);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PRIVATE == p_wrapped_private_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_private[p_wrapped_private_key->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    return r_rsip_rsa_decrypt(p_wrapped_private_key, p_cipher, p_plain);
}

/*******************************************************************************************************************//**
 * Encrypts plaintext with RSAES-PKCS1-v1_5.<br>
 * Implements @ref rsip_api_t::rsaesPkcs1V15Encrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_RSA_xxx_PUBLIC.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen3"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PUBLIC</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PUBLIC</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PUBLIC</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * `mLen` (plain_length) and `k` (RSA key length) must meet the following condition.
 *
 * `mlen <= k - 11`
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSAES_PKCS1_V1_5_Encrypt (rsip_ctrl_t * const              p_ctrl,
                                           rsip_wrapped_key_t const * const p_wrapped_public_key,
                                           uint8_t const * const            p_plain,
                                           uint32_t const                   plain_length,
                                           uint8_t * const                  p_cipher)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_plain);
    FSP_ASSERT(p_cipher);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_public[p_wrapped_public_key->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_public_key->subtype]; // Actual name on RFC8017 is "k"
    uint32_t mlen = plain_length;

    /* Check length */
    FSP_ERROR_RETURN(mlen <= (klen - 11), FSP_ERR_INVALID_SIZE);

    uint8_t * p_em = &p_cipher[0];

    /*
     * EME-PKCS1-v1_5 encoding
     * EM = 0x00 || 0x02 || PS || 0x00 || M
     *
     * cipher = EM
     */
    p_em[0] = 0x00;
    p_em[1] = 0x02;
    fsp_err_t err = eme_pkcs1_v1_5_ps_generate(p_ctrl, &p_em[2], klen - mlen - 3);
    p_em[klen - mlen - 1] = 0x00;
    memcpy(&p_em[klen - mlen], p_plain, mlen);

    if (FSP_SUCCESS == err)
    {
        /*
         * c = RSAEP ((n, e), m)
         *
         * cipher = c
         */
        err = r_rsip_rsa_encrypt(p_wrapped_public_key, p_em, p_em);
    }

    /* Clear plaintext if the operation fails */
    if (FSP_SUCCESS != err)
    {
        memset(p_em, 0, klen);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Decrypts with RSAES-PKCS1-v1_5.<br>
 * Implements @ref rsip_api_t::rsaesPkcs1V15Decrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_private_key must be RSIP_KEY_TYPE_RSA_xxx_PRIVATE.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen4"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PRIVATE</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PRIVATE</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PRIVATE</td>
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
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note The stack usage of this function depends on the maximum key length for RSA decryption enabled in configuration.
 *       For example, if RSA-2048 is enabled, this function uses at least 256 bytes (2048 bits) of stack.
 *       To shrink the stack size, please disable unused key length in configuration.
 * @note This API skips the ciphertext length checking at RFC8017 (PKCS#1 v2.2) Section 7.2.2 Step 1.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSAES_PKCS1_V1_5_Decrypt (rsip_ctrl_t * const              p_ctrl,
                                           rsip_wrapped_key_t const * const p_wrapped_private_key,
                                           uint8_t const * const            p_cipher,
                                           uint8_t * const                  p_plain,
                                           uint32_t * const                 p_plain_length,
                                           uint32_t const                   plain_buffer_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_cipher);
    FSP_ASSERT(p_plain);
    FSP_ASSERT(p_plain_length);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PRIVATE == p_wrapped_private_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_private[p_wrapped_private_key->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_private_key->subtype]; // Actual name in RFC 8107 is "k"
    uint32_t mlen = 0;

    /*
     * Prepare EME-PKCS1-v1_5 decoding input
     * EM = 0x00 || 0x02 || PS || 0x00 || M
     *
     * buffer = EM
     */
    uint8_t em_buffer[RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER] =
    {
        0
    };
    uint8_t * p_em = &em_buffer[0];

    /* m = RSADP (K, c) */
    fsp_err_t err = r_rsip_rsa_decrypt(p_wrapped_private_key, p_cipher, p_em);

    /*
     * Verification
     * In accordance with PKCS #1 v2.2 7.2.2., error code and timing is unified.
     */
    if (FSP_SUCCESS == err)
    {
        uint32_t          ptr             = 0;
        volatile uint32_t error_detection = 0;

        /* Error: The first octet of EM does not have hexadecimal value 0x00 */
        error_detection |= p_em[ptr];
        ptr++;

        /* Error: The second octet of EM does not have hexadecimal value 0x02 */
        error_detection |= p_em[ptr] ^ 0x02;
        ptr++;

        /* Error: The length of PS is less than 8 octets */
        for (uint32_t i = 0; i < 8; i++)
        {
            error_detection |= !p_em[ptr];
            ptr++;
        }

        /* Error: There is no octet with hexadecimal value 0x00 to separate PS from M */
        uint32_t zero_detection = 0;
        mlen = klen - ptr;
        while (klen > ptr)
        {
            mlen -= !zero_detection;

            zero_detection |= !p_em[ptr];
            ptr++;
        }

        error_detection |= !zero_detection;

        if (error_detection)
        {
            /* Wipe error_detection */
            error_detection = 0;
            err             = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    /* Output the message M */
    if (FSP_SUCCESS == err)
    {
        *p_plain_length = mlen;

        /* Buffer length must be equal or grater than actual plaintext length */
        if (*p_plain_length > plain_buffer_length)
        {
            err = FSP_ERR_INVALID_SIZE;
        }
        else
        {
            memcpy(p_plain, &p_em[klen - mlen], mlen);
        }
    }

    /* Clear plaintext in stack */
    stack_clear(p_em, klen);

    return err;
}

/*******************************************************************************************************************//**
 * Encrypts plaintext with RSAES-OAEP.<br>
 * Implements @ref rsip_api_t::rsaesOaepEncrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_RSA_xxx_PUBLIC.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen5"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PUBLIC</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PUBLIC</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PUBLIC</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg Argument mask_generation_function only supports the features listed below.
 * <table>
 * <caption id="rsaMaskFunc"> </caption>
 * <tr><th>Mask Generation Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_MGF_TYPE_MGF1_SHA256</td>
 * <tr><td>SHA384<td>RSIP_MGF_TYPE_MGF1_SHA384</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * `mLen` (plain_length), `hLen` (output length of hash_function), and `k` (RSA key length)
 * must meet the following condition.
 *
 * `mLen <= k - 2 hLen - 2`
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSAES_OAEP_Encrypt (rsip_ctrl_t * const              p_ctrl,
                                     rsip_wrapped_key_t const * const p_wrapped_public_key,
                                     rsip_hash_type_t const           hash_function,
                                     rsip_mgf_type_t const            mask_generation_function,
                                     uint8_t const * const            p_label,
                                     uint32_t const                   label_length,
                                     uint8_t const * const            p_plain,
                                     uint32_t const                   plain_length,
                                     uint8_t * const                  p_cipher)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_label || (0 == label_length));
    FSP_ASSERT(p_plain);
    FSP_ASSERT(p_cipher);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_public[p_wrapped_public_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[mask_generation_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen  = gs_key_length[p_wrapped_public_key->subtype]; // Actual name on RFC8017 is "k"
    uint32_t hlen  = gs_hash_length[hash_function];
    uint32_t mlen  = plain_length;
    uint32_t dblen = klen - hlen - 1;

    /* Check length */
    FSP_ERROR_RETURN(mlen <= (klen - 2 * hlen - 2), FSP_ERR_INVALID_SIZE);

    /*
     * Prepare EME-OAEP encoding input
     * 0x00 || seed || DB
     * DB = lHash || PS || 0x01 || M
     *
     * cipher = 0x00 || seed || DB
     */
    uint8_t * p_em       = &p_cipher[0];
    uint8_t * p_seed     = &p_em[1];
    uint8_t * p_db       = &p_em[1 + hlen];
    uint8_t * p_lhash    = &p_em[1 + hlen];
    uint8_t * p_sentinel = &p_em[klen - mlen - 1]; // Position of 0x01
    uint8_t * p_message  = &p_em[klen - mlen];

    /* Zero filling */
    memset(p_em, 0, klen);

    /* Generate seed (length: hlen) */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;

    for (uint32_t i = 0; i * RSIP_PRV_BYTE_SIZE_RNG < hlen; i++)
    {
        uint8_t seed_buffer[RSIP_PRV_BYTE_SIZE_RNG];
        err = r_rsip_random_number_generate(p_ctrl, seed_buffer);

        if (FSP_SUCCESS == err)
        {
            memcpy(&p_seed[i * RSIP_PRV_BYTE_SIZE_RNG],
                   seed_buffer,
                   ((hlen / RSIP_PRV_BYTE_SIZE_RNG) > i) ? RSIP_PRV_BYTE_SIZE_RNG : (hlen % RSIP_PRV_BYTE_SIZE_RNG));
        }
    }

    if (FSP_SUCCESS == err)
    {
        /* Generate lHash (length: hlen) */
        err = r_rsip_sha_init(p_ctrl, hash_function);

        if (FSP_SUCCESS == err)
        {
            err = r_rsip_sha_update(p_ctrl, p_label, label_length);

            if (FSP_SUCCESS == err)
            {
                err = r_rsip_sha_finish(p_ctrl, p_lhash);
            }
        }

        /* Insert 0x01 */
        *p_sentinel = 0x01;

        /* Copy message */
        memcpy(p_message, p_plain, mlen);
    }

    /*
     * EME-OAEP encoding
     * EM = 0x00 || maskedSeed || maskedDB
     *
     * cipher = EM
     */
    rsip_hash_type_t mgf1_hash = (rsip_hash_type_t) mask_generation_function;

    if (FSP_SUCCESS == err)
    {
        /*
         * dbMask = MGF(seed, k - hLen - 1)
         * maskedDB = DB \xor dbMask
         */
        err = mgf1_mask(p_ctrl, mgf1_hash, p_seed, hlen, p_db, dblen);
    }

    if (FSP_SUCCESS == err)
    {
        /*
         * seedMask = MGF(maskedDB, hLen)
         * maskedSeed = seed \xor seedMask
         */
        err = mgf1_mask(p_ctrl, mgf1_hash, p_db, dblen, p_seed, hlen);
    }

    if (FSP_SUCCESS == err)
    {
        /*
         * c = RSAEP ((n, e), m)
         *
         * cipher = c
         */
        err = r_rsip_rsa_encrypt(p_wrapped_public_key, p_em, p_cipher);
    }

    /* Clear plaintext if the operation fails */
    if (FSP_SUCCESS != err)
    {
        memset(p_em, 0, klen);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Decrypts ciphertext with RSAES-OAEP.<br>
 * Implements @ref rsip_api_t::rsaesOaepDecrypt.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_private_key must be RSIP_KEY_TYPE_RSA_xxx_PRIVATE.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen6"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PRIVATE</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PRIVATE</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PRIVATE</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc2"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg Argument mask_generation_function only supports the features listed below.
 * <table>
 * <caption id="rsaMaskFunc2"> </caption>
 * <tr><th>Mask Generation Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_MGF_TYPE_MGF1_SHA256</td>
 * <tr><td>SHA384<td>RSIP_MGF_TYPE_MGF1_SHA384</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * `hLen` (output length of hash_function) and `k` (RSA key length) must meet the following condition.
 *
 * `k >= 2 hLen + 2`
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note The stack usage of this function depends on the maximum key length for RSA decryption enabled in configuration.
 *       For example, if RSA-2048 is enabled, this function uses at least 256 bytes (2048 bits) of stack.
 *       To shrink the stack size, please disable unused key length in configuration.
 * @note This API skips the ciphertext length checking at RFC8017 (PKCS#1 v2.2) Section 7.1.2 Step 1.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSAES_OAEP_Decrypt (rsip_ctrl_t * const              p_ctrl,
                                     rsip_wrapped_key_t const * const p_wrapped_private_key,
                                     rsip_hash_type_t const           hash_function,
                                     rsip_mgf_type_t const            mask_generation_function,
                                     uint8_t const * const            p_label,
                                     uint32_t const                   label_length,
                                     uint8_t const * const            p_cipher,
                                     uint8_t * const                  p_plain,
                                     uint32_t * const                 p_plain_length,
                                     uint32_t const                   plain_buffer_length)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_label || (0 == label_length));
    FSP_ASSERT(p_cipher);
    FSP_ASSERT(p_plain);
    FSP_ASSERT(p_plain_length);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PRIVATE == p_wrapped_private_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_private[p_wrapped_private_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[mask_generation_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen  = gs_key_length[p_wrapped_private_key->subtype]; // Actual name in RFC 8107 is "k"
    uint32_t hlen  = gs_hash_length[hash_function];
    uint32_t mlen  = 0;
    uint32_t dblen = klen - hlen - 1;

    /* Check length */
    FSP_ERROR_RETURN(klen >= (2 * hlen + 2), FSP_ERR_INVALID_SIZE);

    /*
     * Prepare EME-OAEP decoding input
     * EM = Y || maskedSeed || maskedDB
     *
     * buffer = EM
     */
    uint8_t   em_buffer[RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER];
    uint8_t   hash_buffer[RSIP_PRV_BYTE_SIZE_HASH_BUFFER];
    uint8_t * p_em       = &em_buffer[0];
    uint8_t * p_seed     = &p_em[1];
    uint8_t * p_db       = &p_em[1 + hlen];
    uint8_t * p_lhash    = &p_em[1 + hlen];
    uint8_t * p_sentinel = NULL;       // Position of 0x01
    uint8_t * p_message  = NULL;

    /* m = RSADP (K, c) */
    fsp_err_t err = r_rsip_rsa_decrypt(p_wrapped_private_key, p_cipher, p_em);

    /*
     * EME-OAEP decoding
     * Y || seed || DB
     * DB = lHash' || PS || 0x01 || M
     *
     * buffer = Y || seed || DB
     */
    rsip_hash_type_t mgf1_hash = (rsip_hash_type_t) mask_generation_function;

    if (FSP_SUCCESS == err)
    {
        /*
         * seedMask = MGF(maskedDB, hLen)
         * seed = maskedSeed \xor seedMask
         */
        err = mgf1_mask(p_ctrl, mgf1_hash, p_db, dblen, p_seed, hlen);
    }

    if (FSP_SUCCESS == err)
    {
        /*
         * dbMask = MGF(seed, k - hLen - 1)
         * DB = maskedDB \xor dbMask
         */
        err = mgf1_mask(p_ctrl, mgf1_hash, p_seed, hlen, p_db, dblen);
    }

    if (FSP_SUCCESS == err)
    {
        /* Generate lHash' (output to p_mask) */
        err = r_rsip_sha_init(p_ctrl, hash_function);

        if (FSP_SUCCESS == err)
        {
            err = r_rsip_sha_update(p_ctrl, p_label, label_length);

            if (FSP_SUCCESS == err)
            {
                err = r_rsip_sha_finish(p_ctrl, hash_buffer);
            }
        }
    }

    /*
     * Verification
     * In accordance with PKCS #1 v2.2 7.1.2., error code and timing is unified.
     */
    if (FSP_SUCCESS == err)
    {
        volatile uint32_t error_detection = 0;

        /* Error: There is no octet with hexadecimal value 0x01 to separate PS from M */
        uint32_t nonzero_detection = 0;
        mlen = klen - 2 * hlen - 2;    // Maximum length

        for (uint32_t i = mlen; i > 0; i--)
        {
            nonzero_detection |= p_em[klen - i - 1];
            mlen              -= !nonzero_detection;
        }

        p_sentinel       = &p_em[klen - mlen - 1];
        p_message        = &p_em[klen - mlen];
        error_detection |= *p_sentinel ^ 0x01;

        /* Error: lHash does not equal lHash' */
        error_detection |= secure_memcmp(p_lhash, hash_buffer, hlen);

        /* Error: Y is nonzero */
        error_detection |= p_em[0];

        if (error_detection)
        {
            /* Wipe error_detection */
            error_detection = 0;
            err             = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    /* Output the message M */
    if (FSP_SUCCESS == err)
    {
        *p_plain_length = mlen;

        /* Buffer length must be equal or grater than actual plaintext length */
        if (*p_plain_length > plain_buffer_length)
        {
            err = FSP_ERR_INVALID_SIZE;
        }
        else
        {
            memcpy(p_plain, p_message, mlen);
        }
    }

    /* Clear stack data */
    stack_clear(p_em, klen);
    stack_clear(hash_buffer, hlen);

    return err;
}

/*******************************************************************************************************************//**
 * Signs message with RSASSA-PKCS1-v1_5.<br>
 * Implements @ref rsip_api_t::rsassaPkcs1V15Sign.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_private_key must be RSIP_KEY_TYPE_RSA_xxx_PRIVATE.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen7"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PRIVATE</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PRIVATE</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PRIVATE</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc3"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg The hash value must be computed and passed to the argument p_hash before executing this API.<br>
 * Also, the argument hash_function must specify the one used when computing the hash value above.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSASSA_PKCS1_V1_5_Sign (rsip_ctrl_t * const              p_ctrl,
                                         rsip_wrapped_key_t const * const p_wrapped_private_key,
                                         rsip_hash_type_t const           hash_function,
                                         uint8_t const * const            p_hash,
                                         uint8_t * const                  p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PRIVATE == p_wrapped_private_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_private[p_wrapped_private_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_private_key->subtype]; // Actual name in RFC 8107 is "k"

    /*
     * EMSA-PKCS1-v1_5 encoding
     * EM = EMSA-PKCS1-V1_5-ENCODE (M, k)
     *
     * signature = EM
     */
    fsp_err_t err = emsa_pkcs1_v1_5_encode(hash_function, p_hash, p_signature, klen);

    /*
     * s = RSASP1 (K, m)
     *
     * signature = s
     */
    if (FSP_SUCCESS == err)
    {
        err = r_rsip_rsa_decrypt(p_wrapped_private_key, p_signature, p_signature);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Verifies signature with RSASSA-PKCS1-v1_5.<br>
 * Implements @ref rsip_api_t::rsassaPkcs1V15Verify.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_RSA_xxx_PUBLIC.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen8"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PUBLIC</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PUBLIC</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PUBLIC</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc4"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg The hash value must be computed and passed to the argument p_hash before executing this API.<br>
 * Also, the argument hash_function must specify the one used when computing the hash value above.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note The stack usage of this function depends on the maximum key length for RSA decryption enabled in configuration.
 *       For example, if RSA-2048 is enabled, this function uses at least 512 bytes (2048 bits * 2) of stack.
 *       To shrink the stack size, please disable unused key length in configuration.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSASSA_PKCS1_V1_5_Verify (rsip_ctrl_t * const              p_ctrl,
                                           rsip_wrapped_key_t const * const p_wrapped_public_key,
                                           rsip_hash_type_t const           hash_function,
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
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_public[p_wrapped_public_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_public_key->subtype]; // Actual name in RFC 8107 is "k"

    uint8_t em1_buffer[RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER];
    uint8_t em2_buffer[RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER];

    /*
     * s = OS2IP (S)
     * m = RSAVP1 ((n, e), s)
     * EM = I2OSP (m, k)
     *
     * em1_buffer = EM
     */
    fsp_err_t err = r_rsip_rsa_encrypt(p_wrapped_public_key, p_signature, em1_buffer);

    if (FSP_SUCCESS == err)
    {
        /*
         * EMSA-PKCS1-v1_5 encoding
         * EM' = EMSA-PKCS1-V1_5-ENCODE (M, k)
         *
         * em2_buffer = EM'
         */
        err = emsa_pkcs1_v1_5_encode(hash_function, p_hash, em2_buffer, klen);
    }

    if (FSP_SUCCESS == err)
    {
        /* Compare the encoded message EM and the second encoded message EM' */
        if (0 != memcmp(em1_buffer, em2_buffer, klen))
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Signs message with RSASSA-PSS.<br>
 * Implements @ref rsip_api_t::rsassaPssSign.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_private_key must be RSIP_KEY_TYPE_RSA_xxx_PRIVATE.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen9"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PRIVATE</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PRIVATE</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PRIVATE</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc5"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg Argument mask_generation_function only supports the features listed below.
 * <table>
 * <caption id="rsaMaskFunc3"> </caption>
 * <tr><th>Mask Generation Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_MGF_TYPE_MGF1_SHA256</td>
 * <tr><td>SHA384<td>RSIP_MGF_TYPE_MGF1_SHA384</td>
 * </table>
 * @arg Argument salt_length must follow the list below.
 * <table>
 * <caption id="rsaSaltLen1"> </caption>
 * <tr><th>Parameter<th>Description</tr>
 * <tr><td>RSIP_RSA_SALT_LENGTH_AUTO<td>The salt length is set to
 * RSIP_RSA_SALT_LENGTH_MAX or　RSIP_RSA_SALT_LENGTH_HASH,
 * whichever is shorter. When verifying, the salt length is detected automatically.</td>
 * <tr><td>RSIP_RSA_SALT_LENGTH_HASH<td>The salt length is set to the hash length.</td>
 * <tr><td>RSIP_RSA_SALT_LENGTH_MAX<td>The salt length is set to emLen - hLen - 2,
 * where emLen is the same as the key length and hLen is the hash length.</td>
 * <tr><td>zero or positive integers<td>The following conditions must be satisfied.<br>
 * salt_length <= emLen - hLen - 2 where emLen is the same as the key length and hLen is the hash length.</td>
 * </table>
 * @arg The hash value must be computed and passed to the argument p_hash before executing this API.<br>
 * Also, the argument hash_function must specify the one used when computing the hash value above.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSASSA_PSS_Sign (rsip_ctrl_t * const              p_ctrl,
                                  rsip_wrapped_key_t const * const p_wrapped_private_key,
                                  rsip_hash_type_t const           hash_function,
                                  rsip_mgf_type_t const            mask_generation_function,
                                  uint32_t const                   salt_length,
                                  uint8_t const * const            p_hash,
                                  uint8_t * const                  p_signature)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ASSERT(p_hash);
    FSP_ASSERT(p_signature);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PRIVATE == p_wrapped_private_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_private[p_wrapped_private_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[mask_generation_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_private_key->subtype]; // Actual name in RFC 8107 is "k"

    fsp_err_t err = emsa_pss_encode(p_ctrl,
                                    hash_function,
                                    mask_generation_function,
                                    salt_length,
                                    p_hash,
                                    p_signature,
                                    klen * 8 - 1);

    /*
     * s = RSASP1 (K, m)
     *
     * signature = s
     */
    if (FSP_SUCCESS == err)
    {
        /*
         * EMSA-PSS encoding
         * EM = EMSA-PSS-ENCODE (M, modBits - 1)
         *
         * signature = EM
         */
        err = r_rsip_rsa_decrypt(p_wrapped_private_key, p_signature, p_signature);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Verifies signature with RSASSA-PSS.<br>
 * Implements @ref rsip_api_t::rsassaPssVerify.
 *
 * \<Usage Precautions>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_RSA_xxx_PUBLIC.
 * @arg This version supports the following key types:
 * <table>
 * <caption id="rsaKeyLen10"> </caption>
 * <tr><th>Key Length<th>Key Type</tr>
 * <tr><td>2048 bit<td>RSIP_KEY_TYPE_RSA_2048_PUBLIC</td>
 * <tr><td>3072 bit<td>RSIP_KEY_TYPE_RSA_3072_PUBLIC</td>
 * <tr><td>4096 bit<td>RSIP_KEY_TYPE_RSA_4096_PUBLIC</td>
 * </table>
 * @arg Argument hash_function only supports the features listed below.
 * <table>
 * <caption id="rsaHashFunc6"> </caption>
 * <tr><th>Hash Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_HASH_TYPE_SHA256</td>
 * <tr><td>SHA384<td>RSIP_HASH_TYPE_SHA384</td>
 * </table>
 * @arg Argument mask_generation_function only supports the features listed below.
 * <table>
 * <caption id="rsaMaskFunc4"> </caption>
 * <tr><th>Mask Generation Function<th>Corresponding Parameter</tr>
 * <tr><td>SHA256<td>RSIP_MGF_TYPE_MGF1_SHA256</td>
 * <tr><td>SHA384<td>RSIP_MGF_TYPE_MGF1_SHA384</td>
 * </table>
 * @arg Argument salt_length must follow the list below.
 * <table>
 * <caption id="rsaSaltLen2"> </caption>
 * <tr><th>Parameter<th>Description</tr>
 * <tr><td>RSIP_RSA_SALT_LENGTH_AUTO<td>The salt length is set to
 * RSIP_RSA_SALT_LENGTH_MAX or　RSIP_RSA_SALT_LENGTH_HASH,
 * whichever is shorter. When verifying, the salt length is detected automatically.</td>
 * <tr><td>RSIP_RSA_SALT_LENGTH_HASH<td>The salt length is set to the hash length.</td>
 * <tr><td>RSIP_RSA_SALT_LENGTH_MAX<td>The salt length is set to emLen - hLen - 2,
 * where emLen is the same as the key length and hLen is the hash length.</td>
 * <tr><td>zero or positive integers<td>The following conditions must be satisfied.<br>
 * salt_length <= emLen - hLen - 2 where emLen is the same as the key length and hLen is the hash length.</td>
 * </table>
 * @arg The hash value must be computed and passed to the argument p_hash before executing this API.<br>
 * Also, the argument hash_function must specify the one used when computing the hash value above.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Any length is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 *
 * @note The stack usage of this function depends on the maximum key length for RSA decryption enabled in configuration.
 *       For example, if RSA-2048 is enabled, this function uses at least 512 bytes (2048 bits * 2) of stack.
 *       To shrink the stack size, please disable unused key length in configuration.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RSASSA_PSS_Verify (rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_public_key,
                                    rsip_hash_type_t const           hash_function,
                                    rsip_mgf_type_t const            mask_generation_function,
                                    uint32_t const                   salt_length,
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
    FSP_ERROR_RETURN(RSIP_ALG_RSA_PUBLIC == p_wrapped_public_key->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rsa_public[p_wrapped_public_key->subtype], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[hash_function], FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(g_sha_enabled[mask_generation_function], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    uint32_t klen = gs_key_length[p_wrapped_public_key->subtype]; // Actual name in RFC 8107 is "k"

    uint8_t em_buffer[RSIP_PRV_BYTE_SIZE_RSA_EM_BUFFER];

    /*
     * s = OS2IP (S)
     * m = RSAVP1 ((n, e), s)
     * EM = I2OSP (m, emLen)
     *
     * em_buffer = EM
     */
    fsp_err_t err = r_rsip_rsa_encrypt(p_wrapped_public_key, p_signature, em_buffer);

    if (FSP_SUCCESS == err)
    {
        /*
         * EMSA-PSS verification
         * Result = EMSA-PSS-VERIFY (M, EM, modBits - 1)
         */
        err = emsa_pss_verify(p_ctrl,
                              hash_function,
                              mask_generation_function,
                              salt_length,
                              p_hash,
                              em_buffer,
                              klen * 8 - 1);
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
 * Encrypts plaintext with raw RSA.
 *
 * @param[in]     p_wrapped_public_key Pointer to wrapped key of RSA public key.
 * @param[in]     p_plain              Pointer to plaintext. The length is as same as the key length.
 * @param[out]    p_cipher             Pointer to destination of ciphertext. The length is as same as the key length.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t r_rsip_rsa_encrypt (rsip_wrapped_key_t const * const p_wrapped_public_key,
                                     uint8_t const * const            p_plain,
                                     uint8_t * const                  p_cipher)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        g_func.p_rsa_public[p_wrapped_public_key->subtype]((const uint32_t *) p_wrapped_public_key->
                                                           value, (const uint32_t *) p_plain,
                                                           (uint32_t *) p_cipher);

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
 * Decrypts ciphertext with raw RSA.
 *
 * @param[in]     p_wrapped_private_key Pointer to wrapped key of RSA private key.
 * @param[in]     p_cipher              Pointer to ciphertext. The length is as same as the key length.
 * @param[out]    p_plain               Pointer to destination of plaintext. The length is as same as the key length.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t r_rsip_rsa_decrypt (rsip_wrapped_key_t const * const p_wrapped_private_key,
                                     uint8_t const * const            p_cipher,
                                     uint8_t * const                  p_plain)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret =
        g_func.p_rsa_private[p_wrapped_private_key->subtype]((const uint32_t *) p_wrapped_private_key->
                                                             value, (const uint32_t *) p_cipher,
                                                             (uint32_t *) p_plain);

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
 * Generates PS (Padding String) for EME-PKCS1-v1_5
 *
 * @param[in,out] p_ctrl    Pointer to control block.
 * @param[out]    p_ps      Pointer to PS.
 * @param[in]     ps_length Length of PS.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 ***********************************************************************************************************************/
static fsp_err_t eme_pkcs1_v1_5_ps_generate (rsip_ctrl_t * const p_ctrl, uint8_t * const p_ps, uint32_t const ps_length)
{
    fsp_err_t err      = FSP_ERR_CRYPTO_RSIP_FATAL;
    uint32_t  rand_ptr = 0;
    uint8_t   rand_tmp[RSIP_PRV_BYTE_SIZE_RNG];

    while (ps_length > rand_ptr)
    {
        err = r_rsip_random_number_generate(p_ctrl, rand_tmp);
        if (FSP_SUCCESS != err)
        {
            break;
        }

        for (uint32_t i = 0; i < RSIP_PRV_BYTE_SIZE_RNG; i++)
        {
            if (0 != rand_tmp[i])
            {
                p_ps[rand_ptr] = rand_tmp[i];
                rand_ptr++;
            }

            if (ps_length == rand_ptr)
            {
                break;
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Computes EMSA-PKCS1-v1_5-ENCODE.
 *
 * @param[in]     hash_function         Hash function in EMSA-PKCS1-v1_5.
 * @param[in]     p_hash                Pointer to input hash.
 * @param[out]    p_em                  Pointer to destination of EM (Encoded Message).
 * @param[in]     em_length             Length of EM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_SIZE                  Key length is too short.
 **********************************************************************************************************************/
static fsp_err_t emsa_pkcs1_v1_5_encode (rsip_hash_type_t const hash_function,
                                         uint8_t const * const  p_hash,
                                         uint8_t * const        p_em,
                                         uint32_t const         em_length)
{
    static const uint8_t digest_info_prefix[][19] =
    {
        [RSIP_HASH_TYPE_SHA1] =
        {
        0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14
        },
        [RSIP_HASH_TYPE_SHA224] =
        {
        0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04, 0x05,
        0x00, 0x04, 0x1c
        },
        [RSIP_HASH_TYPE_SHA256] =
        {
        0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
        0x00, 0x04, 0x20
        },
        [RSIP_HASH_TYPE_SHA384] =
        {
        0x30, 0x41, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02, 0x05,
        0x00, 0x04, 0x30
        },
        [RSIP_HASH_TYPE_SHA512] =
        {
        0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05,
        0x00, 0x04, 0x40
        },
        [RSIP_HASH_TYPE_SHA512_224] =
        {
        0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x05, 0x05,
        0x00, 0x04, 0x1c
        },
        [RSIP_HASH_TYPE_SHA512_256] =
        {
        0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x06, 0x05,
        0x00, 0x04, 0x20
        },
    };
    static const uint32_t digest_info_prefix_len[] =
    {
        [RSIP_HASH_TYPE_SHA1]       = 15,
        [RSIP_HASH_TYPE_SHA224]     = 19,
        [RSIP_HASH_TYPE_SHA256]     = 19,
        [RSIP_HASH_TYPE_SHA384]     = 19,
        [RSIP_HASH_TYPE_SHA512]     = 19,
        [RSIP_HASH_TYPE_SHA512_224] = 19,
        [RSIP_HASH_TYPE_SHA512_256] = 19
    };

    uint8_t const * t_prefix     = digest_info_prefix[hash_function];
    uint32_t        t_prefix_len = digest_info_prefix_len[hash_function];
    uint32_t        t_hash_len   = gs_hash_length[hash_function];

    /* Check length */
    FSP_ERROR_RETURN((t_prefix_len + t_hash_len + 11) <= em_length, FSP_ERR_INVALID_SIZE);

    /* Padding */
    p_em[0] = 0x00;
    p_em[1] = 0x01;
    memset(&p_em[2], RSIP_PRV_EMSA_PKCS1_V1_5_PS, em_length - t_prefix_len - t_hash_len - 3);
    p_em[em_length - t_prefix_len - t_hash_len - 1] = 0x00;

    /* Copy the prefix of DER encoding T */
    memcpy(&p_em[em_length - t_prefix_len - t_hash_len], t_prefix, t_prefix_len);

    /* Copy hash */
    memcpy(&p_em[em_length - t_hash_len], p_hash, t_hash_len);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Computes EMSA-PSS-ENCODE.
 *
 * @param[in,out] p_ctrl                   Pointer to control block.
 * @param[in]     hash_function            Hash function in EMSA-PSS-ENCODE.
 * @param[in]     mask_generation_function Mask generation function in EMSA-PSS-ENCODE.
 * @param[in]     salt_length              Salt length.
 * @param[in]     p_mhash                  Pointer to mHash.
 * @param[out]    p_em                     Pointer to destination of EM (Encoded Message).
 * @param[in]     em_bit_length            Bit length of EM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Key length is too short.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t emsa_pss_encode (rsip_ctrl_t * const    p_ctrl,
                                  rsip_hash_type_t const hash_function,
                                  rsip_mgf_type_t const  mask_generation_function,
                                  uint32_t const         salt_length,
                                  uint8_t const * const  p_mhash,
                                  uint8_t * const        p_em,
                                  uint32_t const         em_bit_length)
{
    uint32_t slen;
    uint32_t hlen  = gs_hash_length[hash_function];
    uint32_t emlen = (em_bit_length + 7) / 8; // round up

    /* Set salt length */
    uint32_t slen_max = emlen - hlen - 2;
    switch (salt_length)
    {
        case RSIP_RSA_SALT_LENGTH_AUTO:
        {
            slen = (slen_max >= hlen) ? hlen : slen_max;
            break;
        }

        case RSIP_RSA_SALT_LENGTH_HASH:
        {
            slen = hlen;
            break;
        }

        case RSIP_RSA_SALT_LENGTH_MAX:
        {
            slen = slen_max;
            break;
        }

        default:
        {
            slen = salt_length;
        }
    }

    uint8_t * p_db   = &p_em[0];
    uint8_t * p_salt = &p_em[emlen - slen - hlen - 1];
    uint8_t * p_hash = &p_em[emlen - hlen - 1];

    /* Check length */
    FSP_ERROR_RETURN(emlen >= hlen + slen + 2, FSP_ERR_INVALID_SIZE);

    /*
     * DB = PS ((0x)00 00 ...) || 0x01 || salt
     *
     * em = DB
     */
    memset(p_db, 0x00, emlen - hlen - slen - 2);
    p_em[emlen - hlen - slen - 2] = 0x01;
    fsp_err_t err = emsa_pss_salt_generate(p_ctrl, p_salt, slen);

    if (FSP_SUCCESS == err)
    {
        /*
         * mHash = Hash(M)
         * M' = Padding1 ((0x)00 00 00 00 00 00 00 00) || mHash || salt
         * H = Hash(M')
         * Set trailer field (0xbc)
         *
         * em = DB || H || 0xbc
         */
        err             = emsa_pss_h_generate(p_ctrl, hash_function, p_mhash, hlen, p_salt, slen, p_hash);
        p_em[emlen - 1] = RSIP_PRV_EMSA_PSS_TRAILER_FIELD;
    }

    if (FSP_SUCCESS == err)
    {
        /*
         * dbMask = MGF(H, emLen - hLen - 1)
         * maskedDB = DB \xor dbMask
         *
         * em = maskedDB || H || 0xbc
         */
        rsip_hash_type_t mgf1_hash = (rsip_hash_type_t) mask_generation_function;
        err = mgf1_mask(p_ctrl, mgf1_hash, p_hash, hlen, p_db, emlen - hlen - 1);
    }

    if (FSP_SUCCESS == err)
    {
        /* Set the leftmost 8emLen - emBits bits of the leftmost octet in maskedDB to zero */
        p_em[0] &= (uint8_t) (RSIP_PRV_EMSA_PSS_MASK >> (8 * emlen - em_bit_length));
    }

    return err;
}

/*******************************************************************************************************************//**
 * Computes EMSA-PSS-VERIFY.
 *
 * @param[in,out] p_ctrl                   Pointer to control block.
 * @param[in]     hash_function            Hash function in EMSA-PSS-VERIFY.
 * @param[in]     mask_generation_function Mask generation function in EMSA-PSS-VERIFY.
 * @param[in]     salt_length              Salt length.
 * @param[in]     p_mhash                  Pointer to mHash.
 * @param[in,out] p_em                     Pointer to EM (Encoded Message). This argument is used as working area.
 *                                         Therefore, the value is destroyed after executing this function.
 * @param[in]     em_bit_length            Bit length of EM.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_INVALID_SIZE                  Key length is too short.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Verification failed.
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t emsa_pss_verify (rsip_ctrl_t * const    p_ctrl,
                                  rsip_hash_type_t const hash_function,
                                  rsip_mgf_type_t const  mask_generation_function,
                                  uint32_t const         salt_length,
                                  uint8_t const * const  p_mhash,
                                  uint8_t * const        p_em,
                                  uint32_t const         em_bit_length)
{
    uint32_t slen                = 0;
    uint32_t hlen                = gs_hash_length[hash_function];
    uint32_t emlen               = (em_bit_length + 7) / 8; // round up
    bool     salt_auto_detection = false;

    /* Set salt length*/
    uint32_t slen_max = emlen - hlen - 2;
    switch (salt_length)
    {
        case RSIP_RSA_SALT_LENGTH_AUTO:
        {
            salt_auto_detection = true;
            break;
        }

        case RSIP_RSA_SALT_LENGTH_HASH:
        {
            slen = hlen;
            break;
        }

        case RSIP_RSA_SALT_LENGTH_MAX:
        {
            slen = slen_max;
            break;
        }

        default:
        {
            slen = salt_length;
        }
    }

    uint8_t   hash_buffer[RSIP_PRV_BYTE_SIZE_HASH_BUFFER];
    uint8_t * p_db   = &p_em[0];
    uint8_t * p_salt = &p_em[emlen - slen - hlen - 1];
    uint8_t * p_hash = &p_em[emlen - hlen - 1];

    /* Check length */
    FSP_ERROR_RETURN(emlen >= hlen + slen + 2, FSP_ERR_INVALID_SIZE);

    /* Error: the rightmost octet of EM does not have hexadecimal value 0xbc */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;

    if (p_em[emlen - 1] != RSIP_PRV_EMSA_PSS_TRAILER_FIELD)
    {
        err = FSP_ERR_CRYPTO_RSIP_FAIL;
    }
    else
    {
        err = FSP_SUCCESS;
    }

    /* the leftmost 8emLen - emBits bits of the leftmost octet in maskedDB are not all equal to zero */
    if (FSP_SUCCESS == err)
    {
        if (0x00 != (p_em[0] & ~(RSIP_PRV_EMSA_PSS_MASK >> (8 * emlen - em_bit_length))))
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    /*
     * dbMask = MGF(H, emLen - hLen - 1)
     * DB = maskedDB \xor dbMask
     *
     * em = DB || H || 0xbc
     */
    if (FSP_SUCCESS == err)
    {
        rsip_hash_type_t mgf1_hash = (rsip_hash_type_t) mask_generation_function;
        err = mgf1_mask(p_ctrl, mgf1_hash, p_hash, hlen, p_db, emlen - hlen - 1);
    }

    if (FSP_SUCCESS == err)
    {
        /* Set the leftmost 8emLen - emBits bits of the leftmost octet in DB to zero */
        p_em[0] &= (uint8_t) (RSIP_PRV_EMSA_PSS_MASK >> (8 * emlen - em_bit_length));

        /*
         * Error: the emLen - hLen - sLen - 2 leftmost octets of DB are not zero or the octet at position
         * emLen - hLen - sLen - 1 (the leftmost position is "position 1") does not have hexadecimal value 0x01
         */
        err = emsa_pss_ps_check(p_db, emlen - hlen - 1, (uint8_t const **) &p_salt, &slen, salt_auto_detection);
    }

    /*
     * mHash = Hash(M)
     * M' = Padding1 ((0x)00 00 00 00 00 00 00 00) || mHash || salt
     * H' = Hash(M')
     *
     * hash_buffer = H'
     */
    if (FSP_SUCCESS == err)
    {
        err = emsa_pss_h_generate(p_ctrl, hash_function, p_mhash, hlen, p_salt, slen, hash_buffer);
    }

    /* Compare H and H' */
    if (FSP_SUCCESS == err)
    {
        if (0 != memcmp(p_hash, hash_buffer, hlen))
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Computes H or H' in EMSA-PSS.
 *
 * @param[in,out] p_ctrl        Pointer to control block.
 * @param[in]     hash_function Hash function in EMSA-PSS.
 * @param[in]     p_mhash       Pointer to mHash.
 * @param[in]     hlen          hLen.
 * @param[in]     p_salt        Pointer to salt.
 * @param[in]     slen          sLen.
 * @param[out]    p_h           Pointer to destination of H or H'.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
static fsp_err_t emsa_pss_h_generate (rsip_ctrl_t * const    p_ctrl,
                                      rsip_hash_type_t const hash_function,
                                      uint8_t const * const  p_mhash,
                                      uint32_t const         hlen,
                                      uint8_t const * const  p_salt,
                                      uint32_t const         slen,
                                      uint8_t * const        p_h)
{
    /* "Padding1" in EMSA-PSS */
    static const uint8_t padding1[8] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    fsp_err_t err = r_rsip_sha_init(p_ctrl, hash_function);

    if (FSP_SUCCESS == err)
    {
        err = r_rsip_sha_update(p_ctrl, padding1, sizeof(padding1));

        if (FSP_SUCCESS == err)
        {
            err = r_rsip_sha_update(p_ctrl, p_mhash, hlen);

            if (FSP_SUCCESS == err)
            {
                err = r_rsip_sha_update(p_ctrl, p_salt, slen);

                if (FSP_SUCCESS == err)
                {
                    err = r_rsip_sha_finish(p_ctrl, p_h);
                }
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Generates salt for EMSA-PSS-ENCODE
 *
 * @param[in,out] p_ctrl      Pointer to control block.
 * @param[out]    p_salt      Pointer to salt.
 * @param[in]     salt_length Length of salt.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 ***********************************************************************************************************************/
static fsp_err_t emsa_pss_salt_generate (rsip_ctrl_t * const p_ctrl, uint8_t * const p_salt, uint32_t const salt_length)
{
    fsp_err_t err      = FSP_SUCCESS;
    uint32_t  rand_ptr = 0;
    uint8_t   rand_tmp[RSIP_PRV_BYTE_SIZE_RNG];

    for (uint32_t i = 0; i < salt_length / 16; i++)
    {
        err       = r_rsip_random_number_generate(p_ctrl, &p_salt[rand_ptr]);
        rand_ptr += 16;
    }

    if (rand_ptr < salt_length)
    {
        err = r_rsip_random_number_generate(p_ctrl, rand_tmp);
        memcpy(&p_salt[rand_ptr], rand_tmp, salt_length - rand_ptr);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Check PS for EMSA-PSS-VERIFY
 *
 * @param[in]     p_db                Pointer to DB (Data Block).
 * @param[in]     dblen               DB length.
 * @param[out]    pp_salt             Pointer to start address of salt. If salt_auto_detection is true,
 *                                    the address is updated in this function.
 * @param[in,out] p_slen              Pointer to salt length. If salt_auto_detection is true,
 *                                    detected salt length is output. Otherwise, the known salt length should be input.
 * @param[in]     salt_auto_detection If true, salt length is detected automatically.
 *                                    Otherwise, this function use input salt length.
 *
 * @retval FSP_SUCCESS                Normal termination.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL   PS is invalid.
 **********************************************************************************************************************/
fsp_err_t emsa_pss_ps_check (uint8_t const * const  p_db,
                             uint32_t const         dblen,
                             uint8_t const ** const pp_salt,
                             uint32_t * const       p_slen,
                             bool const             salt_auto_detection)
{
    fsp_err_t err    = FSP_SUCCESS;
    uint32_t  ps_ptr = 0;

    if (salt_auto_detection)
    {
        /* Detect salt */
        while ((ps_ptr < dblen) && (0x00 == p_db[ps_ptr]))
        {
            ps_ptr++;
        }

        if (0x01 != p_db[ps_ptr])
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
        else
        {
            *p_slen  = dblen - ps_ptr - 1;
            *pp_salt = &p_db[dblen - *p_slen];
        }
    }
    else
    {
        /* Verify sLen */
        for (ps_ptr = 0; ps_ptr < dblen - *p_slen - 1; ps_ptr++)
        {
            if (0x00 != p_db[ps_ptr])
            {
                err = FSP_ERR_CRYPTO_RSIP_FAIL;
            }
        }

        if (0x01 != p_db[ps_ptr])
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Computes MGF1 and outputs (input XOR MGF1).
 *
 * @param[in,out] p_ctrl        Pointer to control block.
 * @param[in]     hash_function Hash function used in MGF1.
 * @param[in]     p_mgf_seed    Seed used in MGF1.
 * @param[in]     mgf_seed_len  Length of seed.
 * @param[in,out] p_mask        Pointer to input data and destination of output data.
 * @param[in]     mask_len      Length of mask.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 ***********************************************************************************************************************/
static fsp_err_t mgf1_mask (rsip_ctrl_t * const    p_ctrl,
                            rsip_hash_type_t const hash_function,
                            uint8_t const * const  p_mgf_seed,
                            uint32_t const         mgf_seed_len,
                            uint8_t * const        p_mask,
                            uint32_t const         mask_len)
{
    fsp_err_t err  = FSP_ERR_CRYPTO_RSIP_FATAL;
    uint32_t  hlen = gs_hash_length[hash_function];
    uint8_t   buffer[RSIP_PRV_BYTE_SIZE_HASH_BUFFER];

    for (uint32_t counter = 0; counter * hlen < mask_len; counter++)
    {
        /* Generate mask */
        err = r_rsip_sha_init(p_ctrl, hash_function);
        if (FSP_SUCCESS == err)
        {
            err = r_rsip_sha_update(p_ctrl, p_mgf_seed, mgf_seed_len);
            if (FSP_SUCCESS == err)
            {
                uint32_t counter_big[1] = {bswap_32big(counter)};
                err = r_rsip_sha_update(p_ctrl, (uint8_t *) counter_big, 4);
                if (FSP_SUCCESS == err)
                {
                    err = r_rsip_sha_finish(p_ctrl, buffer);
                }
            }
        }

        /* Output masked data */
        if (FSP_SUCCESS == err)
        {
            memxor(&p_mask[counter * hlen], buffer, ((mask_len / hlen) > counter) ? hlen : (mask_len % hlen));
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Compares buf1 and buf2 while protecting against timing attack.
 *
 * @param[in] buf1 Pointer to buf1.
 * @param[in] buf2 Pointer to buf2.
 * @param[in] num  Byte size of buf1 and buf2.
 *
 * @retval 0 buf1 and buf2 are equal.
 * @retval 1 buf1 and buf2 are not equal.
 **********************************************************************************************************************/
static uint32_t secure_memcmp (const void * buf1, const void * buf2, uint32_t num)
{
    uint8_t * p_buf1 = (uint8_t *) buf1;
    uint8_t * p_buf2 = (uint8_t *) buf2;
    uint32_t  tmp    = 0;

    for (uint32_t i = 0; i < num; i++)
    {
        tmp |= p_buf1[i] ^ p_buf2[i];
    }

    return tmp > 0;
}

/*******************************************************************************************************************//**
 * Computes buf1 XOR buf2.
 *
 * @param[in,out] buf1 Pointer to buf1. buf1 XOR buf2 is output.
 * @param[in]     buf2 Pointer to buf2.
 * @param[in]     num  Byte size of buf1 and buf2.
 *
 * @return Pointer to buf1.
 **********************************************************************************************************************/
static void * memxor (void * buf1, void * buf2, uint32_t num)
{
    uint8_t * p_buf1 = (uint8_t *) buf1;
    uint8_t * p_buf2 = (uint8_t *) buf2;

    for (uint32_t i = 0; i < num; i++)
    {
        p_buf1[i] ^= p_buf2[i];
    }

    return buf1;
}

/*******************************************************************************************************************//**
 * Clears stack data.
 *
 * If memset_s is supported, it is guaranteed that this function will not be optimized.
 *
 * @param[in,out] p_buf Stack data to be cleared.
 * @param[in]     num   Stack data size.
 ***********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE void stack_clear (void * p_buf, const uint32_t num)
{
#if __STDC_WANT_LIB_EXT1__
    memset_s(p_buf, num, 0, num);
#else
    void * (* volatile p_memset)(void *, int, size_t) = memset;
    p_memset(p_buf, 0, num);
#endif
}
