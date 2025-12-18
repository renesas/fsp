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

    r_rsip_func100(bswap_32big(0x07c79359U),
                   bswap_32big(0x59dffabdU),
                   bswap_32big(0xf33cd9e0U),
                   bswap_32big(0xa7c99718U));
    WR1_PROG(REG_00B0H, 0x000018b8U);
    r_rsip_func_sub013(0x08000085U, 0x00430011U);

    r_rsip_func100(bswap_32big(0xd00421b7U),
                   bswap_32big(0xd75e80edU),
                   bswap_32big(0x8126d2ceU),
                   bswap_32big(0x19c9568bU));
    r_rsip_func_sub013(0x08000095U, 0x00430011U);

    r_rsip_func100(bswap_32big(0x7269c7f0U),
                   bswap_32big(0x82402db9U),
                   bswap_32big(0x0c3b9cd2U),
                   bswap_32big(0xb62a0555U));

    WR1_PROG(REG_0094H, 0x000008a5U);

    WR1_PROG(REG_00D0H, 0x080000c5U);
    r_rsip_func_sub009(0x000008b3U, 0x00430009U, 0x00001800U);
    r_rsip_func_sub009(0x000008b4U, 0x00430009U, 0x00001800U);

    WR1_PROG(REG_00D0H, 0x0b040104U);
    r_rsip_func_sub012(0x810100c0U, 0x00490005U);

    r_rsip_func_sub006(0x80840005U, 0x03410011U, 0x00003845U, 0x00008c40U);
    r_rsip_func_sub022(0x00ffffffU, 0x00009040U, 0x01000000U);
    WR1_PROG(REG_0094H, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009105U);
    r_rsip_func_sub006(0x81840005U, 0x00490011U, 0x00008c40U, 0x00ffffffU);
    r_rsip_func_sub022(0x00009040U, 0x02000000U, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009045U);
    r_rsip_func_sub012(0x81840005U, 0x00490011U);

    r_rsip_func100(bswap_32big(0x5c8e93b8U),
                   bswap_32big(0xcf8d588bU),
                   bswap_32big(0xa70f363cU),
                   bswap_32big(0x38d61633U));
    r_rsip_func_sub013(0x08000085U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x111130a3U),
                   bswap_32big(0x9aa5cb7aU),
                   bswap_32big(0x41fbc7aaU),
                   bswap_32big(0xf34c4c8eU));
    r_rsip_func_sub008(0x000000a1U, 0x0c000094U, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
