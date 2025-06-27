/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_p0e (void)
{
    if (RD1_MASK(REG_149CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x000e0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x3f546405U),
                   bswap_32big(0x64da2a5aU),
                   bswap_32big(0xfa00eed4U),
                   bswap_32big(0xdf669c15U));
    WR1_PROG(REG_1438H, 0x400000c0U);

    WR1_PROG(REG_1600H, 0x0000b7e0U);
    WR1_PROG(REG_1600H, 0x000000a8U);

    WR1_PROG(REG_1608H, 0x8181001fU);
    WR1_PROG(REG_1400H, 0x02090005U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1B08H, 0x00000202U);

    r_rsip_func102(bswap_32big(0xbd061a08U),
                   bswap_32big(0xa06898b4U),
                   bswap_32big(0x52c08ccbU),
                   bswap_32big(0x2a4d4c67U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
