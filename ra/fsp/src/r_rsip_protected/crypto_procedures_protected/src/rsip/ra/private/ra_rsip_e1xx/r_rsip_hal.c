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
#define RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER              (16U)
#define RSIP_PRV_WORD_SIZE_SHA_MESSAGE_DIGEST_BUFFER    (8U)

/* Block length (in bytes) of SHA */
#define SHA_BLOCK8_LEN                                  (64U)
#define HMAC_LAST_BLOCK_ADD_LEN                         (64U)
#define SHA_STOP_BIT                                    (0x80)
#define SHA_PADDING_DATA_LEN                            (9U)
#define SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN                (SHA_BLOCK8_LEN * 2 - SHA_PADDING_DATA_LEN)

/* Initial values for SHA operation */
#define RSIP_PRV_SHA224_INIT_VALUE1                     (0xc1059ed8)
#define RSIP_PRV_SHA224_INIT_VALUE2                     (0x367cd507)
#define RSIP_PRV_SHA224_INIT_VALUE3                     (0x3070dd17)
#define RSIP_PRV_SHA224_INIT_VALUE4                     (0xf70e5939)
#define RSIP_PRV_SHA224_INIT_VALUE5                     (0xffc00b31)
#define RSIP_PRV_SHA224_INIT_VALUE6                     (0x68581511)
#define RSIP_PRV_SHA224_INIT_VALUE7                     (0x64f98fa7)
#define RSIP_PRV_SHA224_INIT_VALUE8                     (0xbefa4fa4)

#define RSIP_PRV_SHA256_INIT_VALUE1                     (0x6a09e667)
#define RSIP_PRV_SHA256_INIT_VALUE2                     (0xbb67ae85)
#define RSIP_PRV_SHA256_INIT_VALUE3                     (0x3c6ef372)
#define RSIP_PRV_SHA256_INIT_VALUE4                     (0xa54ff53a)
#define RSIP_PRV_SHA256_INIT_VALUE5                     (0x510e527f)
#define RSIP_PRV_SHA256_INIT_VALUE6                     (0x9b05688c)
#define RSIP_PRV_SHA256_INIT_VALUE7                     (0x1f83d9ab)
#define RSIP_PRV_SHA256_INIT_VALUE8                     (0x5be0cd19)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_hmac_cmd
{
    RSIP_HMAC_CMD_SIGN   = 0U,
    RSIP_HMAC_CMD_VERIFY = 1U,
} rsip_hmac_cmd_t;

typedef union u_rsip_dword_data
{
    uint64_t dword;
    struct
    {
        uint8_t pos_1st;
        uint8_t pos_2nd;
        uint8_t pos_3rd;
        uint8_t pos_4th;
        uint8_t pos_5th;
        uint8_t pos_6th;
        uint8_t pos_7th;
        uint8_t pos_8th;
    } byte;
} rsip_dword_data_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void set_sha2_final_block(const uint8_t * p_message,
                                 uint64_t        message_length,
                                 uint64_t        total_message_length,
                                 uint8_t       * p_last_block,
                                 uint32_t      * p_last_block_length);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static const uint32_t gs_hmac_cmd[] =
{
    [RSIP_HMAC_CMD_SIGN]   = BSWAP_32BIG_C(0U),
    [RSIP_HMAC_CMD_VERIFY] = BSWAP_32BIG_C(1U),
};

static const uint32_t gs_sha224_init_value[8] =
{
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE1),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE2),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE3),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE4),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE5),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE6),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE7),
    BSWAP_32BIG_C(RSIP_PRV_SHA224_INIT_VALUE8),
};

static const uint32_t gs_sha256_init_value[8] =
{
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE1),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE2),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE3),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE4),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE5),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE6),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE7),
    BSWAP_32BIG_C(RSIP_PRV_SHA256_INIT_VALUE8),
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
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    switch (hash_type)
    {
        /* SHA-224 */
        case RSIP_HASH_TYPE_SHA224:
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret =
                r_rsip_p72(gs_sha224_init_value, (const uint32_t *) p_message,
                           r_rsip_byte_to_word_convert((uint32_t) message_length), internal_state);
            break;
        }

        /* SHA-256 */
        case RSIP_HASH_TYPE_SHA256:
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret =
                r_rsip_p72(gs_sha256_init_value, (const uint32_t *) p_message,
                           r_rsip_byte_to_word_convert((uint32_t) message_length), internal_state);
            break;
        }

        default:
        {
            break;
        }
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_sha1sha2_resume_update (rsip_hash_type_t hash_type,
                                          const uint8_t  * p_message,
                                          uint64_t         message_length,
                                          uint32_t       * internal_state)
{
    return r_rsip_sha1sha2_update(hash_type, p_message, message_length, internal_state);
}

rsip_ret_t r_rsip_sha1sha2_update (rsip_hash_type_t hash_type,
                                   const uint8_t  * p_message,
                                   uint64_t         message_length,
                                   uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(hash_type);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p72(internal_state, (const uint32_t *) p_message,
                      r_rsip_byte_to_word_convert((uint32_t) message_length), internal_state);
}

rsip_ret_t r_rsip_sha1sha2_suspend (uint32_t * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_PASS;
}

rsip_ret_t r_rsip_sha1sha2_init_final (rsip_hash_type_t hash_type,
                                       const uint8_t  * p_message,
                                       uint64_t         message_length,
                                       uint8_t        * p_digest)
{
    rsip_ret_t       rsip_ret = RSIP_RET_FAIL;
    uint8_t          padded_msg[SHA_BLOCK8_LEN * 2] = {0};
    uint32_t         set_prc_byte_size              = 0;
    uint64_t         tmp_message_length             = message_length;
    const uint8_t  * p_tmp_message = p_message;
    const uint32_t * p_tmp_digest;
    uint32_t         digest_buffer[RSIP_PRV_WORD_SIZE_SHA_MESSAGE_DIGEST_BUFFER] = {0};

    switch (hash_type)
    {
        /* SHA-224 */
        case RSIP_HASH_TYPE_SHA224:
        {
            p_tmp_digest = gs_sha224_init_value;
            rsip_ret     = RSIP_RET_PASS;
            break;
        }

        /* SHA-256 */
        case RSIP_HASH_TYPE_SHA256:
        {
            p_tmp_digest = gs_sha256_init_value;
            rsip_ret     = RSIP_RET_PASS;
            break;
        }

        default:
        {
            break;
        }
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
        {
            tmp_message_length = message_length & (SHA_BLOCK8_LEN - 1);
            p_tmp_message      = p_message + (message_length - tmp_message_length);
            rsip_ret           =
                r_rsip_p72(p_tmp_digest, (const uint32_t *) p_message,
                           r_rsip_byte_to_word_convert((uint32_t) (message_length - tmp_message_length)),
                           digest_buffer);
            p_tmp_digest = digest_buffer;
        }

        if (RSIP_RET_PASS == rsip_ret)
        {
            set_sha2_final_block(p_tmp_message, tmp_message_length, message_length, padded_msg, &set_prc_byte_size);

            rsip_ret =
                r_rsip_p72(p_tmp_digest,
                           (const uint32_t *) padded_msg,
                           r_rsip_byte_to_word_convert(set_prc_byte_size),
                           (uint32_t *) p_digest);
        }
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
    return r_rsip_sha1sha2_final(hash_type, p_message, message_length, total_message_length, p_digest, internal_state);
}

rsip_ret_t r_rsip_sha1sha2_final (rsip_hash_type_t hash_type,
                                  uint8_t        * p_message,
                                  uint64_t         message_length,
                                  uint64_t         total_message_length,
                                  uint8_t        * p_digest,
                                  uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(hash_type);

    uint32_t set_prc_byte_size = 0;

    set_sha2_final_block(p_message, message_length, total_message_length, p_message, &set_prc_byte_size);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p72(internal_state, (const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size),
                      (uint32_t *) p_digest);
}

rsip_ret_t r_rsip_hmac_init_update (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((uint32_t *) p_wrapped_key->p_value);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((uint32_t *) p_wrapped_key->p_value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        }
        else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        }
        else
        {
            rsip_ret = RSIP_RET_FAIL;
        }
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_update (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint32_t                 * internal_state)
{
    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    /* Call primitive (cast to match the argument type with the primitive function) */
    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_pdcr((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        }
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_p76r((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        }
    }
    else
    {
        /* Do nothing */
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_update (const rsip_wrapped_key_t * p_wrapped_key,
                               const uint8_t            * p_message,
                               uint64_t                   message_length,
                               uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        rsip_ret = RSIP_RET_PASS;
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        rsip_ret = RSIP_RET_PASS;
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_suspend (rsip_hmac_handle_t * p_handle)
{
    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_handle->wrapped_key.type);

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdcs(p_handle->internal_state);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76s(p_handle->internal_state);
    }
    else
    {
        /* Do nothing */
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_init_final (const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint8_t                  * p_mac)
{
    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    uint8_t         padded_msg[SHA_BLOCK8_LEN * 2] = {0};
    uint32_t        set_prc_byte_size              = 0;
    uint64_t        tmp_message_length             = message_length;
    const uint8_t * p_tmp_message = p_message;

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((uint32_t *) p_wrapped_key->p_value);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((uint32_t *) p_wrapped_key->p_value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
        {
            tmp_message_length = message_length & (SHA_BLOCK8_LEN - 1);
            p_tmp_message      = p_message + (message_length - tmp_message_length);
        }

        set_sha2_final_block(p_tmp_message,
                             tmp_message_length,
                             message_length + HMAC_LAST_BLOCK_ADD_LEN,
                             padded_msg,
                             &set_prc_byte_size);

        if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
        {
            if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
            {
                r_rsip_pdcu((const uint32_t *) p_message,
                            r_rsip_byte_to_word_convert((uint32_t) (message_length - tmp_message_length)));
            }

            r_rsip_pdcu((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));

            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
        }
        else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
        {
            if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
            {
                r_rsip_p76u((const uint32_t *) p_message,
                            r_rsip_byte_to_word_convert((uint32_t) (message_length - tmp_message_length)));
            }

            r_rsip_p76u((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));

            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
        }
        else
        {
            rsip_ret = RSIP_RET_FAIL;
        }
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_final (const rsip_wrapped_key_t * p_wrapped_key,
                                     const uint8_t            * p_message,
                                     uint64_t                   message_length,
                                     uint64_t                   total_message_length,
                                     uint8_t                  * p_mac,
                                     uint32_t                 * internal_state)
{
    uint32_t               set_prc_byte_size = 0;
    rsip_key_type_extend_t key_type_ext      = r_rsip_key_type_parse(p_wrapped_key->type);

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         (uint8_t *) p_message,
                         &set_prc_byte_size);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;
    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_pdcr((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
            rsip_ret =
                r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
        }
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_p76r((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
            rsip_ret =
                r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
        }
    }
    else
    {
        /* Do nothing */
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_final (const rsip_wrapped_key_t * p_wrapped_key,
                              uint8_t                  * p_message,
                              uint64_t                   message_length,
                              uint64_t                   total_message_length,
                              uint8_t                  * p_mac,
                              uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    rsip_ret_t             rsip_ret          = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext      = r_rsip_key_type_parse(p_wrapped_key->type);
    uint32_t               set_prc_byte_size = 0;

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         p_message,
                         &set_prc_byte_size);

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));

        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));

        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_init_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    const uint8_t            * p_mac,
                                    uint32_t                   mac_length)
{
    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    uint32_t        InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] = {0};
    uint8_t         padded_msg[SHA_BLOCK8_LEN * 2]                 = {0};
    uint32_t        set_prc_byte_size  = 0;
    uint64_t        tmp_message_length = message_length;
    const uint8_t * p_tmp_message      = p_message;
    memcpy(InData_MAC, p_mac, mac_length);
    uint32_t mac_len[1] = {bswap_32big(mac_length)};

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((uint32_t *) p_wrapped_key->p_value);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((uint32_t *) p_wrapped_key->p_value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
        {
            tmp_message_length = message_length & (SHA_BLOCK8_LEN - 1);
            p_tmp_message      = p_message + (message_length - tmp_message_length);
        }

        set_sha2_final_block(p_tmp_message,
                             tmp_message_length,
                             message_length + HMAC_LAST_BLOCK_ADD_LEN,
                             padded_msg,
                             &set_prc_byte_size);

        if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
        {
            if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
            {
                r_rsip_pdcu((const uint32_t *) p_message,
                            r_rsip_byte_to_word_convert((uint32_t) (message_length - tmp_message_length)));
            }

            r_rsip_pdcu((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));

            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
        }
        else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
        {
            if (SHA2_FINAL_BLOCK_MAX_MESSAGE_LEN <= message_length)
            {
                r_rsip_p76u((const uint32_t *) p_message,
                            r_rsip_byte_to_word_convert((uint32_t) (message_length - tmp_message_length)));
            }

            r_rsip_p76u((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));

            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
        }
        else
        {
            rsip_ret = RSIP_RET_FAIL;
        }
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_resume_verify (const rsip_wrapped_key_t * p_wrapped_key,
                                      const uint8_t            * p_message,
                                      uint64_t                   message_length,
                                      uint64_t                   total_message_length,
                                      const uint8_t            * p_mac,
                                      uint32_t                   mac_length,
                                      uint32_t                 * internal_state)
{
    rsip_key_type_extend_t key_type_ext      = r_rsip_key_type_parse(p_wrapped_key->type);
    uint32_t               set_prc_byte_size = 0;
    uint32_t               InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] =
    {
        0
    };

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         (uint8_t *) p_message,
                         &set_prc_byte_size);

    memcpy(InData_MAC, p_mac, mac_length);
    uint32_t mac_len[1] =
    {
        bswap_32big(mac_length)
    };

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;
    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_pdcr((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
            rsip_ret =
                r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, (uint32_t *) NULL);
        }
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        rsip_ret = r_rsip_p76r((uint32_t *) p_wrapped_key->p_value, internal_state);
        if (RSIP_RET_PASS == rsip_ret)
        {
            r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
            rsip_ret =
                r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, (uint32_t *) NULL);
        }
    }
    else
    {
        /* Do nothing */
    }

    return rsip_ret;
}

rsip_ret_t r_rsip_hmac_verify (const rsip_wrapped_key_t * p_wrapped_key,
                               uint8_t                  * p_message,
                               uint64_t                   message_length,
                               uint64_t                   total_message_length,
                               const uint8_t            * p_mac,
                               uint32_t                   mac_length,
                               uint32_t                 * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    rsip_ret_t             rsip_ret     = RSIP_RET_FAIL;
    rsip_key_type_extend_t key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type);

    uint32_t InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] = {0};
    uint32_t mac_len[1]        = {bswap_32big(mac_length)};
    uint32_t set_prc_byte_size = 0;

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         p_message,
                         &set_prc_byte_size);

    memcpy(InData_MAC, p_mac, mac_length);

    if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224 == key_type_ext.subtype)
    {
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));

        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
    }
    else if (RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256 == key_type_ext.subtype)
    {
        r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));

        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76f(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    return rsip_ret;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_kdf_sha_init_update (rsip_kdf_sha_handle_t * p_handle,
                                       const uint8_t         * p_message,
                                       uint64_t                message_length)
{
    FSP_PARAMETER_NOT_USED(p_handle);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_sha_resume_update (rsip_kdf_sha_handle_t * p_handle,
                                         const uint8_t         * p_message,
                                         uint64_t                message_length)
{
    FSP_PARAMETER_NOT_USED(p_handle);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_sha_update (rsip_kdf_sha_handle_t * p_handle, const uint8_t * p_message, uint64_t message_length)
{
    FSP_PARAMETER_NOT_USED(p_handle);
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_kdf_sha_suspend (uint32_t * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_PASS;
}

rsip_ret_t r_rsip_kdf_sha_init_final (rsip_kdf_sha_handle_t * p_handle,
                                      const uint8_t         * p_message,
                                      uint64_t                message_length,
                                      uint64_t                total_message_length,
                                      uint8_t               * p_digest)
{
    FSP_PARAMETER_NOT_USED(p_message);
    FSP_PARAMETER_NOT_USED(message_length);
    FSP_PARAMETER_NOT_USED(total_message_length);

    uint32_t total_length = p_handle->buffered_length1 + p_handle->actual_wrapped_msg_length +
                            p_handle->buffered_length2;
    rsip_dword_data_t total_bit_length = {.dword = total_length << 3};
    uint8_t           padded_buffer2[SHA_BLOCK8_LEN * 2 + SHA_PADDING_DATA_LEN] = {0};
    uint32_t          zero_padding_len = 0;

    memcpy(padded_buffer2, p_handle->buffer2, p_handle->buffered_length2);
    zero_padding_len = SHA_BLOCK8_LEN - ((total_length + SHA_PADDING_DATA_LEN) & (SHA_BLOCK8_LEN - 1));

    padded_buffer2[p_handle->buffered_length2] = SHA_STOP_BIT;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 1] = total_bit_length.byte.pos_8th;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 2] = total_bit_length.byte.pos_7th;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 3] = total_bit_length.byte.pos_6th;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 4] = total_bit_length.byte.pos_5th;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 5] = total_bit_length.byte.pos_4th;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 6] = total_bit_length.byte.pos_3rd;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 7] = total_bit_length.byte.pos_2nd;
    padded_buffer2[p_handle->buffered_length2 + zero_padding_len + 8] = total_bit_length.byte.pos_1st;

    uint32_t padded_buffer2_len = p_handle->buffered_length2 + zero_padding_len + SHA_PADDING_DATA_LEN;
    uint32_t msg1_len[1]        = {bswap_32big(p_handle->buffered_length1)};
    uint32_t enc_msg_len[1]     = {bswap_32big(p_handle->actual_wrapped_msg_length)};
    uint32_t msg2_len[1]        = {bswap_32big(padded_buffer2_len)};

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_pef((const uint32_t *) p_handle->buffer1,
                      msg1_len,
                      (const uint32_t *) p_handle->wrapped_msg,
                      enc_msg_len,
                      (const uint32_t *) padded_buffer2,
                      msg2_len,
                      (uint32_t *) p_digest);
}

rsip_ret_t r_rsip_kdf_sha_resume_final (rsip_kdf_sha_handle_t * p_handle,
                                        uint8_t               * p_message,
                                        uint64_t                message_length,
                                        uint64_t                total_message_length,
                                        uint8_t               * p_digest)
{
    return r_rsip_kdf_sha_init_final(p_handle, p_message, message_length, total_message_length, p_digest);
}

rsip_ret_t r_rsip_kdf_sha_final (rsip_kdf_sha_handle_t * p_handle,
                                 uint8_t               * p_message,
                                 uint64_t                message_length,
                                 uint64_t                total_message_length,
                                 uint8_t               * p_digest)
{
    return r_rsip_kdf_sha_init_final(p_handle, p_message, message_length, total_message_length, p_digest);
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

/*******************************************************************************************************************//**
 * Set sha final block.
 *
 * @param[in]  p_message            Last block_message.
 * @param[in]  message_length       Byte length of message.(Must be (128 - 9)byte or less)
 * @param[in]  total_message_length Total message length.
 * @param[out] p_last_block         Last block data (This area is need 128byte).
 * @param[out] p_last_block_length  Last block length.
 *
 * @return void.
 **********************************************************************************************************************/
static void set_sha2_final_block (const uint8_t * p_message,
                                  uint64_t        message_length,
                                  uint64_t        total_message_length,
                                  uint8_t       * p_last_block,
                                  uint32_t      * p_last_block_length)
{
    rsip_dword_data_t total_bit_length = {.dword = total_message_length << 3};

    memset(&p_last_block[message_length], 0, (size_t) (SHA_BLOCK8_LEN * 2 - message_length));
    memcpy(p_last_block, p_message, (size_t) message_length);
    p_last_block[message_length] = SHA_STOP_BIT;

    if (SHA_BLOCK8_LEN >= (SHA_PADDING_DATA_LEN + message_length)) /* another block unnecessary */
    {
        /* Casting uint64_t data to uint8_t data array. */
        p_last_block[SHA_BLOCK8_LEN - 8] = total_bit_length.byte.pos_8th;
        p_last_block[SHA_BLOCK8_LEN - 7] = total_bit_length.byte.pos_7th;
        p_last_block[SHA_BLOCK8_LEN - 6] = total_bit_length.byte.pos_6th;
        p_last_block[SHA_BLOCK8_LEN - 5] = total_bit_length.byte.pos_5th;
        p_last_block[SHA_BLOCK8_LEN - 4] = total_bit_length.byte.pos_4th;
        p_last_block[SHA_BLOCK8_LEN - 3] = total_bit_length.byte.pos_3rd;
        p_last_block[SHA_BLOCK8_LEN - 2] = total_bit_length.byte.pos_2nd;
        p_last_block[SHA_BLOCK8_LEN - 1] = total_bit_length.byte.pos_1st;
        p_last_block_length[0]           = SHA_BLOCK8_LEN;
    }
    else
    {
        /* another block necessary */
        /* Casting uint64_t data to uint8_t data array. */
        p_last_block[(2 * SHA_BLOCK8_LEN) - 8] = total_bit_length.byte.pos_8th;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 7] = total_bit_length.byte.pos_7th;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 6] = total_bit_length.byte.pos_6th;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 5] = total_bit_length.byte.pos_5th;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 4] = total_bit_length.byte.pos_4th;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 3] = total_bit_length.byte.pos_3rd;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 2] = total_bit_length.byte.pos_2nd;
        p_last_block[(2 * SHA_BLOCK8_LEN) - 1] = total_bit_length.byte.pos_1st;
        p_last_block_length[0]                 = 2 * SHA_BLOCK8_LEN;
    }
}
