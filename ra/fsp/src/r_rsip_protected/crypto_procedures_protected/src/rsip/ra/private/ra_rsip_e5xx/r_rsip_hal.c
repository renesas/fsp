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
        WR1_PROG(REG_1424H, RSIP_PRV_CMD_REG_1424H);
        WR1_PROG(REG_1428H, RSIP_PRV_CMD_REG_1428H);
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

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
