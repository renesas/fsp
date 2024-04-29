/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p20 (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00200002U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x5f999519U), bswap_32big(0xeb8ecdd3U), bswap_32big(0xf6d92450U), bswap_32big(0xe78ad94fU));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x2802c28bU), bswap_32big(0x1ec94789U), bswap_32big(0x92d2617dU), bswap_32big(0x337bea9eU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[0]);

    r_rsip_func102(bswap_32big(0xca1dbac7U), bswap_32big(0x789beb6aU), bswap_32big(0xd14cdad1U), bswap_32big(0x7e50f415U));

    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
