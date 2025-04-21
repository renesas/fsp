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

void r_rsip_func510 (const uint32_t ARG1[], const uint32_t ARG2[])
{
    WR1_PROG(REG_0094H, 0x00003427U);

    WR1_PROG(REG_0094H, 0x00000800U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c84U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    r_rsip_func100(bswap_32big(0x203daa87U),
                   bswap_32big(0xab900ce7U),
                   bswap_32big(0x0b9183a3U),
                   bswap_32big(0xcda3e139U));
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x08000105U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[0]);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x80840003U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func101(bswap_32big(0xfff99d4cU), bswap_32big(0xaa691ee6U), bswap_32big(0xdb8aa153U),
                       bswap_32big(0xbb6d3a2fU));
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, ARG2[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f510U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x2a3c25b5U), bswap_32big(0xfed4ec64U), bswap_32big(0xbec5c7bcU),
                       bswap_32big(0xc4426412U));
        r_rsip_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x0199e556U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, bswap_32big(0x0000f510U));
        WR1_PROG(REG_0024H, 0x00000000U);

        r_rsip_func101(bswap_32big(0x1e3cd45dU), bswap_32big(0x3a32184bU), bswap_32big(0xfd60a9aaU),
                       bswap_32big(0x28491e7dU));
        r_rsip_func044();

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[1]);
        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x80840003U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG2[5]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        r_rsip_func100(bswap_32big(0x50a85b83U), bswap_32big(0xc4ca0f31U), bswap_32big(0x27b62bb9U),
                       bswap_32big(0x61eba6e2U));
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00002c00U);
            r_rsip_func101(bswap_32big(0xacbb1d54U), bswap_32big(0x2a921056U), bswap_32big(0x5ba78575U),
                           bswap_32big(0x962760d9U));
        }

        r_rsip_func101(bswap_32big(0x537fc8d6U), bswap_32big(0xd2e352ddU), bswap_32big(0xb4d9b92bU),
                       bswap_32big(0x53fcd60aU));
    }

    WR1_PROG(REG_0094H, 0x000034e1U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
