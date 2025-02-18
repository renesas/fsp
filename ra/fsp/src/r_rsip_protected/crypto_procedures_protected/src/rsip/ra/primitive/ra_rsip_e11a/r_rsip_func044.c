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

void r_rsip_func044 (void)
{
    WR1_PROG(REG_0094H, 0x00008cc0U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x000090c0U);
    WR1_PROG(REG_0094H, 0x01000000U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009104U);
    WR1_PROG(REG_009CH, 0x810100c0U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00008cc0U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x000090c0U);
    WR1_PROG(REG_0094H, 0x02000000U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009044U);
    WR1_PROG(REG_009CH, 0x810100c0U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x42d35f05U), bswap_32big(0x2e2f4f28U), bswap_32big(0x7e241f51U), bswap_32big(0x93b47cdeU));
    WR1_PROG(REG_00D0H, 0x08000085U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xdb1bb873U), bswap_32big(0xae363a34U), bswap_32big(0xe5ae30d6U), bswap_32big(0x970ee6caU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000094U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
