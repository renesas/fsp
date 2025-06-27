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

void r_rsip_func040 (void)
{
    r_rsip_func100(bswap_32big(0xe960a74fU),
                   bswap_32big(0x4d3fc9fbU),
                   bswap_32big(0x5d4eb718U),
                   bswap_32big(0xffb5a7a7U));
    WR1_PROG(REG_1A24H, 0x4a470044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A24H, 0x0e470484U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x01ea725dU));

    r_rsip_func100(bswap_32big(0xb2141d54U),
                   bswap_32big(0x49dba92cU),
                   bswap_32big(0x92aa10b5U),
                   bswap_32big(0x6f4942dfU));
    WR1_PROG(REG_1A24H, 0x4a470044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A24H, 0x0e470494U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x02ea725dU));

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
