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

void r_rsip_func143 (void)
{
    WR1_PROG(REG_00A0H, 0x00010000U);

    r_rsip_func100(bswap_32big(0xe70b0311U),
                   bswap_32big(0xf2a7329bU),
                   bswap_32big(0x5a167e53U),
                   bswap_32big(0x6f4fecedU));
    WR1_PROG(REG_00B0H, 0x00001898U);
    r_rsip_func_sub006(0x08000085U, 0x00430011U);

    r_rsip_func100(bswap_32big(0xd4aad776U),
                   bswap_32big(0xcd33f88dU),
                   bswap_32big(0x61166039U),
                   bswap_32big(0xb0743597U));
    r_rsip_func_sub006(0x08000095U, 0x00430011U);

    r_rsip_func100(bswap_32big(0x07143c6fU),
                   bswap_32big(0xc52e2a1bU),
                   bswap_32big(0xa851536bU),
                   bswap_32big(0x2b75f0fbU));

    WR1_PROG(REG_00D0H, 0x080000c5U);
    r_rsip_func_sub004(0x00000893U, 0x00430009U);
    r_rsip_func_sub004(0x00000894U, 0x00430009U);

    WR1_PROG(REG_00D0H, 0x0b040104U);
    r_rsip_func_sub003(0x810100c0U, 0x00490005U);

    WR1_PROG(REG_0094H, 0x000008c6U);

    r_rsip_func_sub003(0x80840006U, 0x03410011U);

    r_rsip_func_sub016(0x00003846U, 0x00008c40U, 0x00ffffffU);
    r_rsip_func_sub016(0x00009040U, 0x01000000U, 0x00003c46U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009105U);
    r_rsip_func_sub003(0x81840006U, 0x00490011U);

    r_rsip_func_sub016(0x00008c40U, 0x00ffffffU, 0x00009040U);
    WR1_PROG(REG_0094H, 0x02000000U);
    WR1_PROG(REG_0094H, 0x00003c46U);

    r_rsip_func100(bswap_32big(0x4ebcf62eU),
                   bswap_32big(0x79ae282fU),
                   bswap_32big(0x759f2c12U),
                   bswap_32big(0xdd1bd903U));
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009095U);
    r_rsip_func_sub003(0x81840006U, 0x00490011U);

    r_rsip_func100(bswap_32big(0x23f11179U),
                   bswap_32big(0x6635ab8dU),
                   bswap_32big(0xcfcc652eU),
                   bswap_32big(0x5301513fU));
    r_rsip_func_sub006(0x08000085U, 0x00410011U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
