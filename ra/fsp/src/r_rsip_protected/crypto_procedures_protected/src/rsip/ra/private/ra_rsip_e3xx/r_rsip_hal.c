/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_private.h"
#include "r_rsip_primitive.h"
#include "r_rsip_util.h"
#include "r_rsip_reg.h"
#include "r_rsip_wrapper.h"
#include "r_rsip_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* For SHA, HMAC-SHA */
#define RSIP_PRV_SHA_INIT_VAL1                (0x80000000U)
#define RSIP_PRV_SHA_INIT_VAL2                (0x00000000U)
#define RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER    (16U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_hmac_cmd
{
    RSIP_HMAC_CMD_SIGN   = 0U,
    RSIP_HMAC_CMD_VERIFY = 1U,
} rsip_hmac_cmd_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_sha_hash_type[] =
{
    [RSIP_HASH_TYPE_SHA1]       = BSWAP_32BIG_C(0U),
    [RSIP_HASH_TYPE_SHA224]     = BSWAP_32BIG_C(1U),
    [RSIP_HASH_TYPE_SHA256]     = BSWAP_32BIG_C(2U),
    [RSIP_HASH_TYPE_SHA384]     = BSWAP_32BIG_C(5U),
    [RSIP_HASH_TYPE_SHA512]     = BSWAP_32BIG_C(6U),
    [RSIP_HASH_TYPE_SHA512_224] = BSWAP_32BIG_C(3U),
    [RSIP_HASH_TYPE_SHA512_256] = BSWAP_32BIG_C(4U),
};

static const uint32_t gs_kdf_sha_hash_type[] =
{
    [RSIP_HASH_TYPE_SHA256] = BSWAP_32BIG_C(0U),
    [RSIP_HASH_TYPE_SHA384] = BSWAP_32BIG_C(1U),
};

static const uint32_t gs_sha_msg_len_multi[2] =
{
    RSIP_PRV_SHA_INIT_VAL1, RSIP_PRV_SHA_INIT_VAL2
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_open (void)
{
    uint32_t   LC[1]    = {0};
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    R_BSP_MODULE_START(FSP_IP_SCE, 0U);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    r_rsip_p00();

    rsip_ret = r_rsip_p81();

    if (RSIP_RET_PASS == rsip_ret)
    {
        WR1_PROG(REG_0018H, RSIP_PRV_CMD_REG_0018H);
        WR1_PROG(REG_001CH, RSIP_PRV_CMD_REG_001CH);
        rsip_ret = r_rsip_p82();
        if (RSIP_RET_RETRY == rsip_ret)
        {
            rsip_ret = r_rsip_p82();
            if (RSIP_RET_RETRY == rsip_ret)
            {
                rsip_ret = r_rsip_p82();
            }
        }
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        LC[0]    = (R_PSCU->DLMMON);
        rsip_ret = r_rsip_p40(LC);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_close (void)
{
    r_rsip_p00();

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    /* Casting structure pointer is used for address. */
    R_BSP_MODULE_STOP(FSP_IP_SCE, 0U);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    return RSIP_RET_PASS;
}

void r_rsip_kuk_set (const void * p_key_update_key)
{
    S_INST2 = (uint32_t *) p_key_update_key;
}

fsp_err_t get_rfc3394_key_wrap_param (rsip_key_type_t key_type,
                                      uint32_t      * wrapped_key_type,
                                      uint32_t      * key_index_size,
                                      uint32_t      * wrapped_key_size)
{
    fsp_err_t err = FSP_ERR_INVALID_ARGUMENT;

    switch (key_type)
    {
        case RSIP_KEY_TYPE_AES_128:
        {
            wrapped_key_type[0] = BSWAP_32BIG_C(0U);
            *key_index_size     = r_rsip_byte_to_word_convert(RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_128));
            *wrapped_key_size   = r_rsip_byte_to_word_convert(RSIP_BYTE_SIZE_PLAIN_KEY(RSIP_KEY_TYPE_AES_128) + 8);
            err                 = FSP_SUCCESS;
            break;
        }

        case RSIP_KEY_TYPE_AES_256:
        {
            wrapped_key_type[0] = BSWAP_32BIG_C(2U);
            *key_index_size     = r_rsip_byte_to_word_convert(RSIP_BYTE_SIZE_WRAPPED_KEY(RSIP_KEY_TYPE_AES_256));
            *wrapped_key_size   = r_rsip_byte_to_word_convert(RSIP_BYTE_SIZE_PLAIN_KEY(RSIP_KEY_TYPE_AES_256) + 8);
            err                 = FSP_SUCCESS;
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return err;
}

rsip_ret_t r_rsip_sha1sha2_init_update (rsip_hash_type_t hash_type,
                                        const uint8_t  * p_message,
                                        uint64_t         message_length,
                                        uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p73i(&gs_sha_hash_type[hash_type], gs_sha_msg_len_multi);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_p73u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_sha1sha2_resume_update (rsip_hash_type_t hash_type,
                                          const uint8_t  * p_message,
                                          uint64_t         message_length,
                                          uint32_t       * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p73r(&gs_sha_hash_type[hash_type], internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_p73u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_sha1sha2_update (rsip_hash_type_t hash_type,
                                   const uint8_t  * p_message,
                                   uint64_t         message_length,
                                   uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(hash_type);
    FSP_PARAMETER_NOT_USED(internal_state);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p73u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
}

rsip_ret_t r_rsip_sha1sha2_suspend (uint32_t * internal_state)
{

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p73s(internal_state);
}

rsip_ret_t r_rsip_sha1sha2_init_final (rsip_hash_type_t hash_type,
                                       const uint8_t  * p_message,
                                       uint64_t         message_length,
                                       uint8_t        * p_digest)
{
    uint32_t msg_len[2] =
    {
        r_rsip_byte_to_bit_convert_upper(message_length),
        r_rsip_byte_to_bit_convert_lower(message_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p73i(&gs_sha_hash_type[hash_type], msg_len);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p73f((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) p_digest);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_sha1sha2_resume_final (rsip_hash_type_t hash_type,
                                         uint8_t        * p_message,
                                         uint64_t         message_length,
                                         uint64_t         total_message_length,
                                         uint8_t        * p_digest,
                                         uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(total_message_length);

    /* Overwrite internal state */
    internal_state[18] = r_rsip_byte_to_bit_convert_upper(message_length);
    internal_state[19] = r_rsip_byte_to_bit_convert_lower(message_length);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p73r(&gs_sha_hash_type[hash_type], internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret =
            r_rsip_p73f((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length),
                        (uint32_t *) p_digest);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_sha1sha2_final (rsip_hash_type_t hash_type,
                                  uint8_t        * p_message,
                                  uint64_t         message_length,
                                  uint64_t         total_message_length,
                                  uint8_t        * p_digest,
                                  uint32_t       * internal_state)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_p73s(internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_sha1sha2_resume_final(hash_type,
                                                p_message,
                                                message_length,
                                                total_message_length,
                                                p_digest,
                                                internal_state);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_init_update (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_resume_update (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_update (const rsip_wrapped_key_t * p_wrapped_key,
                               const uint8_t            * p_message,
                               uint64_t                   message_length,
                               uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_suspend (rsip_hmac_handle_t * p_handle)
{
    FSP_PARAMETER_NOT_USED(p_handle);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_init_final (const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint8_t                  * p_mac)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(p_mac);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_resume_final (const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint64_t                   total_message_length,
                                     uint8_t                  * p_mac,
                                     uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_final (const rsip_wrapped_key_t * p_wrapped_key,
                              uint8_t                  * p_message,
                              uint64_t                   message_length,
                              uint64_t                   total_message_length,
                              uint8_t                  * p_mac,
                              uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_init_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    const uint8_t            * p_mac,
                                    uint32_t                   mac_length)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(mac_length);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_resume_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint64_t                   total_message_length,
                                      const uint8_t            * p_mac,
                                      uint32_t                   mac_length,
                                      uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(mac_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_verify (const rsip_wrapped_key_t * p_wrapped_key,
                               uint8_t                  * p_message,
                               uint64_t                   message_length,
                               uint64_t                   total_message_length,
                               const uint8_t            * p_mac,
                               uint32_t                   mac_length,
                               uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(mac_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_sha_init_update (rsip_kdf_sha_handle_t * p_handle,
                                       const uint8_t         * p_message,
                                       uint64_t                message_length)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefi(&gs_kdf_sha_hash_type[p_handle->type], gs_sha_msg_len_multi);
    if (RSIP_RET_PASS == rsip_ret)
    {
        uint32_t msg1_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length1))};
        uint32_t enc_msg_len[1] = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->actual_wrapped_msg_length))};
        uint32_t msg2_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert((uint32_t) message_length))};

        rsip_ret = r_rsip_pefu((const uint32_t *) p_handle->buffer1,
                               msg1_len,
                               (const uint32_t *) p_handle->wrapped_msg,
                               enc_msg_len,
                               (const uint32_t *) p_message,
                               msg2_len);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_sha_resume_update (rsip_kdf_sha_handle_t * p_handle,
                                         const uint8_t         * p_message,
                                         uint64_t                message_length)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefr(&gs_kdf_sha_hash_type[p_handle->type], p_handle->internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        uint32_t msg1_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length1))};
        uint32_t enc_msg_len[1] = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->actual_wrapped_msg_length))};
        uint32_t msg2_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert((uint32_t) message_length))};

        rsip_ret = r_rsip_pefu((const uint32_t *) p_handle->buffer1,
                               msg1_len,
                               (const uint32_t *) p_handle->wrapped_msg,
                               enc_msg_len,
                               (const uint32_t *) p_message,
                               msg2_len);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_sha_update (rsip_kdf_sha_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length)
{
    uint32_t msg1_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length1))};
    uint32_t enc_msg_len[1] = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->actual_wrapped_msg_length))};
    uint32_t msg2_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert((uint32_t) message_length))};

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefu((const uint32_t *) p_handle->buffer1,
                                      msg1_len,
                                      (const uint32_t *) p_handle->wrapped_msg,
                                      enc_msg_len,
                                      (const uint32_t *) p_message,
                                      msg2_len);

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_sha_suspend (uint32_t * internal_state)
{

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_pefs(internal_state);
}

rsip_ret_t r_rsip_kdf_sha_init_final (rsip_kdf_sha_handle_t * p_handle,
                                      const uint8_t         * p_message,
                                      uint64_t                message_length,
                                      uint64_t                total_message_length,
                                      uint8_t               * p_digest)
{
    FSP_PARAMETER_NOT_USED(total_message_length);

    uint32_t msg_len[2] =
    {
        r_rsip_byte_to_bit_convert_upper(
            p_handle->buffered_length1 + p_handle->actual_wrapped_msg_length + message_length),
        r_rsip_byte_to_bit_convert_lower(
            p_handle->buffered_length1 + p_handle->actual_wrapped_msg_length + message_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefi(&gs_kdf_sha_hash_type[p_handle->type], msg_len);
    if (RSIP_RET_PASS == rsip_ret)
    {
        uint32_t msg1_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length1))};
        uint32_t enc_msg_len[1] = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->actual_wrapped_msg_length))};
        uint32_t msg2_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert((uint32_t) message_length))};

        rsip_ret = r_rsip_peff((const uint32_t *) p_handle->buffer1,
                               msg1_len,
                               (const uint32_t *) p_handle->wrapped_msg,
                               enc_msg_len,
                               (const uint32_t *) p_message,
                               msg2_len,
                               (uint32_t *) p_digest);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_sha_resume_final (rsip_kdf_sha_handle_t * p_handle,
                                        uint8_t               * p_message,
                                        uint64_t                message_length,
                                        uint64_t                total_message_length,
                                        uint8_t               * p_digest)
{
    FSP_PARAMETER_NOT_USED(total_message_length);

    /* Overwrite internal state */
    p_handle->internal_state[18] = r_rsip_byte_to_bit_convert_upper(message_length);
    p_handle->internal_state[19] = r_rsip_byte_to_bit_convert_lower(message_length);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefr(&gs_kdf_sha_hash_type[p_handle->type], p_handle->internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        uint32_t msg1_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->buffered_length1))};
        uint32_t enc_msg_len[1] = {bswap_32big(r_rsip_byte_to_word_convert(p_handle->actual_wrapped_msg_length))};
        uint32_t msg2_len[1]    = {bswap_32big(r_rsip_byte_to_word_convert((uint32_t) message_length))};

        rsip_ret = r_rsip_peff((const uint32_t *) p_handle->buffer1,
                               msg1_len,
                               (const uint32_t *) p_handle->wrapped_msg,
                               enc_msg_len,
                               (const uint32_t *) p_message,
                               msg2_len,
                               (uint32_t *) p_digest);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_sha_final (rsip_kdf_sha_handle_t * p_handle,
                                 uint8_t               * p_message,
                                 uint64_t                message_length,
                                 uint64_t                total_message_length,
                                 uint8_t               * p_digest)
{
    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = r_rsip_pefs(p_handle->internal_state);
    if (RSIP_RET_PASS == rsip_ret)
    {
        rsip_ret = r_rsip_kdf_sha_resume_final(p_handle, p_message, message_length, total_message_length, p_digest);
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_kdf_hmac_init_update (const rsip_wrapped_key_t * p_wrapped_key,
                                        const uint8_t            * p_message,
                                        uint64_t                   message_length,
                                        const uint8_t            * p_wrapped_msg,
                                        uint64_t                   wrapped_msg_length,
                                        uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(p_wrapped_msg);
    FSP_PARAMETER_NOT_USED(wrapped_msg_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_resume_update (const rsip_wrapped_key_t * p_wrapped_key,
                                          const uint8_t            * p_message,
                                          uint64_t                   message_length,
                                          const uint8_t            * p_wrapped_msg,
                                          uint64_t                   wrapped_msg_length,
                                          uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(p_wrapped_msg);
    FSP_PARAMETER_NOT_USED(wrapped_msg_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_update (const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_suspend (uint32_t * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_init_final (const rsip_wrapped_key_t * p_wrapped_key,
                                       const uint8_t            * p_message,
                                       uint64_t                   message_length,
                                       const uint8_t            * p_wrapped_msg,
                                       uint64_t                   wrapped_msg_length,
                                       uint64_t                   actual_wrapped_msg_length,
                                       uint8_t                  * p_mac)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(p_wrapped_msg);
    FSP_PARAMETER_NOT_USED(wrapped_msg_length);
    FSP_PARAMETER_NOT_USED(actual_wrapped_msg_length);
    FSP_PARAMETER_NOT_USED(p_mac);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_resume_final (const rsip_wrapped_key_t * p_wrapped_key,
                                         const uint8_t            * p_message,
                                         uint64_t                   message_length,
                                         uint64_t                   total_message_length,
                                         uint8_t                  * p_mac,
                                         uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_hmac_final (const rsip_wrapped_key_t * p_wrapped_key,
                                  const uint8_t            * p_message,
                                  uint64_t                   message_length,
                                  uint64_t                   total_message_length,
                                  uint8_t                  * p_mac,
                                  uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(p_wrapped_key);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);
    FSP_PARAMETER_NOT_USED(p_mac);
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}
