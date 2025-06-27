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

void r_rsip_func043 (void)
{
    WR1_PROG(REG_00A0H, 0x00010000U);

    r_rsip_func100(bswap_32big(0x07c79359U),
                   bswap_32big(0x59dffabdU),
                   bswap_32big(0xf33cd9e0U),
                   bswap_32big(0xa7c99718U));
    WR1_PROG(REG_00B0H, 0x000018b8U);
    WR1_PROG(REG_00D0H, 0x08000085U);
    WR1_PROG(REG_0000H, 0x00430011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xd00421b7U),
                   bswap_32big(0xd75e80edU),
                   bswap_32big(0x8126d2ceU),
                   bswap_32big(0x19c9568bU));
    WR1_PROG(REG_00D0H, 0x08000095U);
    WR1_PROG(REG_0000H, 0x00430011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x7269c7f0U),
                   bswap_32big(0x82402db9U),
                   bswap_32big(0x0c3b9cd2U),
                   bswap_32big(0xb62a0555U));

    WR1_PROG(REG_0094H, 0x000008a5U);

    WR1_PROG(REG_00D0H, 0x080000c5U);
    WR1_PROG(REG_00B0H, 0x000008b3U);
    WR1_PROG(REG_0000H, 0x00430009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_00B0H, 0x000008b4U);
    WR1_PROG(REG_0000H, 0x00430009U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00D0H, 0x0b040104U);
    WR1_PROG(REG_009CH, 0x810100c0U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_009CH, 0x80840005U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00003845U);
    WR1_PROG(REG_0094H, 0x00008c40U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x00009040U);
    WR1_PROG(REG_0094H, 0x01000000U);
    WR1_PROG(REG_0094H, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009105U);
    WR1_PROG(REG_009CH, 0x81840005U);
    WR1_PROG(REG_0000H, 0x00490011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00008c40U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x00009040U);
    WR1_PROG(REG_0094H, 0x02000000U);
    WR1_PROG(REG_0094H, 0x00003c45U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009045U);
    WR1_PROG(REG_009CH, 0x81840005U);
    WR1_PROG(REG_0000H, 0x00490011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x5c8e93b8U),
                   bswap_32big(0xcf8d588bU),
                   bswap_32big(0xa70f363cU),
                   bswap_32big(0x38d61633U));
    WR1_PROG(REG_00D0H, 0x08000085U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x111130a3U),
                   bswap_32big(0x9aa5cb7aU),
                   bswap_32big(0x41fbc7aaU),
                   bswap_32big(0xf34c4c8eU));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000094U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
