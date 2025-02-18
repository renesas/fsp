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

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define MSTP_SECURITY                                       R_MSTP->MSTPCRC_b.MSTPC31

/* For SHA, HMAC-SHA */
#define RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER                  (16U)

/* Block length (in bytes) of SHA */
#define SHA_BLOCK8_LEN                                      (64U)
#define HMAC_LAST_BLOCK_ADD_LEN                             (64U)
#define SHA_STOP_BIT                                        (0x80)

/* Initial values for SHA operation */
#define RSIP_PRV_SHA224_INIT_VALUE1                         (0xc1059ed8)
#define RSIP_PRV_SHA224_INIT_VALUE2                         (0x367cd507)
#define RSIP_PRV_SHA224_INIT_VALUE3                         (0x3070dd17)
#define RSIP_PRV_SHA224_INIT_VALUE4                         (0xf70e5939)
#define RSIP_PRV_SHA224_INIT_VALUE5                         (0xffc00b31)
#define RSIP_PRV_SHA224_INIT_VALUE6                         (0x68581511)
#define RSIP_PRV_SHA224_INIT_VALUE7                         (0x64f98fa7)
#define RSIP_PRV_SHA224_INIT_VALUE8                         (0xbefa4fa4)

#define RSIP_PRV_SHA256_INIT_VALUE1                         (0x6a09e667)
#define RSIP_PRV_SHA256_INIT_VALUE2                         (0xbb67ae85)
#define RSIP_PRV_SHA256_INIT_VALUE3                         (0x3c6ef372)
#define RSIP_PRV_SHA256_INIT_VALUE4                         (0xa54ff53a)
#define RSIP_PRV_SHA256_INIT_VALUE5                         (0x510e527f)
#define RSIP_PRV_SHA256_INIT_VALUE6                         (0x9b05688c)
#define RSIP_PRV_SHA256_INIT_VALUE7                         (0x1f83d9ab)
#define RSIP_PRV_SHA256_INIT_VALUE8                         (0x5be0cd19)

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
static void set_sha2_final_block (const uint8_t * p_message,
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
    MSTP_SECURITY = 0U;
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
    MSTP_SECURITY = 1U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);

    return RSIP_RET_PASS;
}

void r_rsip_kuk_set (const uint8_t * p_key_update_key_value)
{
    S_INST2 = (uint32_t *) p_key_update_key_value;
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
            rsip_ret = r_rsip_p72(gs_sha224_init_value,
                                  (const uint32_t *) p_message,
                                  r_rsip_byte_to_word_convert((uint32_t) message_length),
                                  internal_state);
            break;
        }

        /* SHA-256 */
        case RSIP_HASH_TYPE_SHA256:
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_p72(gs_sha256_init_value,
                                  (const uint32_t *) p_message,
                                  r_rsip_byte_to_word_convert((uint32_t) message_length),
                                  internal_state);
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
    return r_rsip_sha1sha2_update(hash_type,
                                  p_message,
                                  message_length,
                                  internal_state);
}

rsip_ret_t r_rsip_sha1sha2_update (rsip_hash_type_t hash_type,
                                   const uint8_t  * p_message,
                                   uint64_t         message_length,
                                   uint32_t       * internal_state)
{
    FSP_PARAMETER_NOT_USED(hash_type);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p72(internal_state,
                      (const uint32_t *) p_message,
                      r_rsip_byte_to_word_convert((uint32_t) message_length),
                      internal_state);
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
    rsip_ret_t rsip_ret                       = RSIP_RET_FAIL;
    uint8_t    padded_msg[SHA_BLOCK8_LEN * 2] = {0};
    uint32_t   set_prc_byte_size              = 0;

    set_sha2_final_block(p_message,
                         message_length,
                         message_length,
                         padded_msg,
                         &set_prc_byte_size);

    switch (hash_type)
    {
        /* SHA-224 */
        case RSIP_HASH_TYPE_SHA224:
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_p72(gs_sha224_init_value,
                                  (const uint32_t *) padded_msg,
                                  r_rsip_byte_to_word_convert(set_prc_byte_size),
                                  (uint32_t *) p_digest);
            break;
        }

        /* SHA-256 */
        case RSIP_HASH_TYPE_SHA256:
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_p72(gs_sha256_init_value,
                                  (const uint32_t *) padded_msg,
                                  r_rsip_byte_to_word_convert(set_prc_byte_size),
                                  (uint32_t *) p_digest);
            break;
        }

        default:
        {
            break;
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
    return r_rsip_sha1sha2_final(hash_type,
                                 p_message,
                                 message_length,
                                 total_message_length,
                                 p_digest,
                                 internal_state);
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

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length,
                         p_message,
                         &set_prc_byte_size);

    /* Call primitive (cast to match the argument type with the primitive function) */
    return r_rsip_p72(internal_state,
                      (const uint32_t *) p_message,
                      r_rsip_byte_to_word_convert(set_prc_byte_size),
                      (uint32_t *) p_digest);
}

rsip_ret_t r_rsip_hmac_init_update (const rsip_wrapped_key_t * p_wrapped_key,
                                    const uint8_t            * p_message,
                                    uint64_t                   message_length,
                                    uint32_t                 * internal_state)
{
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;
    FSP_PARAMETER_NOT_USED(internal_state);

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((const uint32_t *) p_wrapped_key->value);
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((const uint32_t *) p_wrapped_key->value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
            rsip_ret = RSIP_RET_PASS;
        }
        else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
        {
            /* Call primitive (cast to match the argument type with the primitive function) */
            r_rsip_p76u((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
            rsip_ret = RSIP_RET_PASS;
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
    FSP_PARAMETER_NOT_USED(internal_state);

    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert((uint32_t) message_length));
        rsip_ret = RSIP_RET_PASS;
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
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

rsip_ret_t r_rsip_hmac_suspend (uint32_t * internal_state)
{
    FSP_PARAMETER_NOT_USED(internal_state);

    return RSIP_RET_FAIL;
}

rsip_ret_t r_rsip_hmac_init_final (const rsip_wrapped_key_t * p_wrapped_key,
                                   const uint8_t            * p_message,
                                   uint64_t                   message_length,
                                   uint8_t                  * p_mac)
{
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    uint8_t  padded_msg[SHA_BLOCK8_LEN * 2] = {0};
    uint32_t set_prc_byte_size              = 0;

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((const uint32_t *) p_wrapped_key->value);
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((const uint32_t *) p_wrapped_key->value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        set_sha2_final_block(p_message,
                             message_length,
                             message_length + HMAC_LAST_BLOCK_ADD_LEN,
                             padded_msg,
                             &set_prc_byte_size);

        if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
        {
            r_rsip_pdcu((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
        }
        else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
        {
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
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;
    FSP_PARAMETER_NOT_USED(internal_state);

    uint32_t set_prc_byte_size = 0;

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         p_message,
                         &set_prc_byte_size);

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_SIGN], NULL, NULL, (uint32_t *) p_mac);
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
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
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;

    uint32_t InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] = {0};
    uint8_t  padded_msg[SHA_BLOCK8_LEN * 2]                 = {0};
    uint32_t set_prc_byte_size                              = 0;
    memcpy(InData_MAC, p_mac, mac_length);
    uint32_t mac_len[1] = {bswap_32big(mac_length)};

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdci((const uint32_t *) p_wrapped_key->value);
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
    {
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_p76i((const uint32_t *) p_wrapped_key->value);
    }
    else
    {
        rsip_ret = RSIP_RET_FAIL;
    }

    if (RSIP_RET_PASS == rsip_ret)
    {
        set_sha2_final_block(p_message,
                             message_length,
                             message_length + HMAC_LAST_BLOCK_ADD_LEN,
                             padded_msg,
                             &set_prc_byte_size);

        if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
        {
            r_rsip_pdcu((const uint32_t *) padded_msg, r_rsip_byte_to_word_convert(set_prc_byte_size));
            /* Call primitive (cast to match the argument type with the primitive function) */
            rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
        }
        else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
        {
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
    rsip_ret_t rsip_ret = RSIP_RET_FAIL;
    FSP_PARAMETER_NOT_USED(internal_state);

    uint32_t InData_MAC[RSIP_PRV_WORD_SIZE_HMAC_MAC_BUFFER] = {0};
    uint32_t mac_len[1]                                     = {bswap_32big(mac_length)};
    uint32_t set_prc_byte_size                              = 0;

    set_sha2_final_block(p_message,
                         message_length,
                         total_message_length + HMAC_LAST_BLOCK_ADD_LEN,
                         p_message,
                         &set_prc_byte_size);

    memcpy(InData_MAC, p_mac, mac_length);

    if (RSIP_KEY_HMAC_SHA224 == p_wrapped_key->subtype)
    {
        r_rsip_pdcu((const uint32_t *) p_message, r_rsip_byte_to_word_convert(set_prc_byte_size));
        /* Call primitive (cast to match the argument type with the primitive function) */
        rsip_ret = r_rsip_pdcf(&gs_hmac_cmd[RSIP_HMAC_CMD_VERIFY], InData_MAC, mac_len, NULL);
    }
    else if (RSIP_KEY_HMAC_SHA256 == p_wrapped_key->subtype)
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
 * @param[in]  message_length       Byte length of message.
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

    memset(&p_last_block[message_length], 0 , (size_t)(SHA_BLOCK8_LEN * 2 - message_length));
    memcpy(p_last_block, p_message, (size_t) message_length);
    p_last_block[message_length] = SHA_STOP_BIT;

    if ((SHA_BLOCK8_LEN - message_length) >= 9) /* another block unnecessary */
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
        p_last_block_length[0] = SHA_BLOCK8_LEN;
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
        p_last_block_length[0] = 2 * SHA_BLOCK8_LEN;
    }
}
