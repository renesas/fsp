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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func043 (void)
{
    WR1_PROG(REG_00A0H, 0x00010000U);

    r_rsip_func100(bswap_32big(0xbe38028cU),
                   bswap_32big(0x2ae0c40cU),
                   bswap_32big(0xa76061b8U),
                   bswap_32big(0xe078ea39U));
    WR1_PROG(REG_00B0H, 0x00001898U);
    r_rsip_func_sub006(0x08000085U, 0x00430011U);

    r_rsip_func100(bswap_32big(0x2f42e4ccU),
                   bswap_32big(0x2f24ad71U),
                   bswap_32big(0x256da778U),
                   bswap_32big(0x3964c21bU));
    r_rsip_func_sub006(0x08000095U, 0x00430011U);

    r_rsip_func100(bswap_32big(0xee08a900U),
                   bswap_32big(0x0d7a051eU),
                   bswap_32big(0xa611e91fU),
                   bswap_32big(0xb4748ad4U));

    WR1_PROG(REG_0094H, 0x000008a5U);

    WR1_PROG(REG_00D0H, 0x080000c5U);
    r_rsip_func_sub004(0x00000893U, 0x00430009U);
    r_rsip_func_sub004(0x00000894U, 0x00430009U);

    WR1_PROG(REG_00D0H, 0x0b040104U);
    r_rsip_func_sub003(0x810100c0U, 0x00490005U);

    r_rsip_func_sub003(0x80840005U, 0x03410011U);

    r_rsip_func_sub016(0x00003845U, 0x00008c40U, 0x00ffffffU);
    r_rsip_func_sub016(0x00009040U, 0x01000000U, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009105U);
    r_rsip_func_sub003(0x81840005U, 0x00490011U);

    r_rsip_func_sub016(0x00008c40U, 0x00ffffffU, 0x00009040U);
    WR1_PROG(REG_0094H, 0x02000000U);
    WR1_PROG(REG_0094H, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009045U);
    r_rsip_func_sub003(0x81840005U, 0x00490011U);

    r_rsip_func100(bswap_32big(0xf6064af5U),
                   bswap_32big(0xef12ba9fU),
                   bswap_32big(0x98e961f2U),
                   bswap_32big(0xd8a89f2cU));
    r_rsip_func_sub006(0x08000085U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x5b5832b3U),
                   bswap_32big(0xa51e0bb2U),
                   bswap_32big(0x455ff309U),
                   bswap_32big(0xdd99c93dU));
    r_rsip_func_sub005(0x000000a1U, 0x0c000094U, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
