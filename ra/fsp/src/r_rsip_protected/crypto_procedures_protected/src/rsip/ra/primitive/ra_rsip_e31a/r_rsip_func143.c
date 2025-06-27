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

void r_rsip_func143 (void)
{
    WR1_PROG(REG_00A0H, 0x00010000U);

    r_rsip_func100(bswap_32big(0xf848b1e8U),
                   bswap_32big(0xeee62ceeU),
                   bswap_32big(0x8c1ebe2bU),
                   bswap_32big(0xfbcbb1c0U));
    WR1_PROG(REG_00B0H, 0x000018b8U);
    WR1_PROG(REG_00D0H, 0x08000085U);
    WR1_PROG(REG_0000H, 0x00430011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x7898f29fU),
                   bswap_32big(0x89ef16f9U),
                   bswap_32big(0xa55c32aaU),
                   bswap_32big(0xd3fb3e0bU));
    WR1_PROG(REG_00D0H, 0x08000095U);
    WR1_PROG(REG_0000H, 0x00430011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0x2e758ab2U),
                   bswap_32big(0x0160a534U),
                   bswap_32big(0x7d37ea8fU),
                   bswap_32big(0x3b8d7b09U));

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

    WR1_PROG(REG_0094H, 0x000008c6U);

    WR1_PROG(REG_009CH, 0x80840006U);
    WR1_PROG(REG_0000H, 0x03410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00003846U);
    WR1_PROG(REG_0094H, 0x00008c40U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x00009040U);
    WR1_PROG(REG_0094H, 0x01000000U);
    WR1_PROG(REG_0094H, 0x00003c46U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009105U);
    WR1_PROG(REG_009CH, 0x81840006U);
    WR1_PROG(REG_0000H, 0x00490011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00008c40U);
    WR1_PROG(REG_0094H, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x00009040U);
    WR1_PROG(REG_0094H, 0x02000000U);
    WR1_PROG(REG_0094H, 0x00003c46U);

    r_rsip_func100(bswap_32big(0x9e269ca6U),
                   bswap_32big(0x7841e28fU),
                   bswap_32big(0xa2a2e5a9U),
                   bswap_32big(0x34d5760bU));
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009095U);
    WR1_PROG(REG_009CH, 0x81840006U);
    WR1_PROG(REG_0000H, 0x00490011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    r_rsip_func100(bswap_32big(0xae3b5fedU),
                   bswap_32big(0x1abfa8f1U),
                   bswap_32big(0xd3d8f263U),
                   bswap_32big(0x3d79b1abU));
    WR1_PROG(REG_00D0H, 0x08000085U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
