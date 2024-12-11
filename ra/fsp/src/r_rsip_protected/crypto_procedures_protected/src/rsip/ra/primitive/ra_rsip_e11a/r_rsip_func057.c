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

void r_rsip_func057 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[])
{
    uint32_t iLoop = 0U;
    uint32_t oLoop = 0U;

    WR1_PROG(REG_0094H, 0x00003467U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x08000065U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[0]);

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000074U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0094H, 0x000034c0U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000ffU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x32cfc93aU), bswap_32big(0xa9be18e2U), bswap_32big(0xfa6b6e02U), bswap_32big(0x6db296e3U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x000034c4U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000feU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x55727707U), bswap_32big(0x797b7bd3U), bswap_32big(0xba811ed4U), bswap_32big(0xd52d8996U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x55ff7185U), bswap_32big(0x3879ae50U), bswap_32big(0x736b379dU), bswap_32big(0xc1ccb42aU));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000044U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x08000054U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    r_rsip_func081();

    WR1_PROG(REG_0094H, 0x00007c01U);
    WR1_PROG(REG_0040H, 0x00600000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    oLoop = 0U;
    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0x1766ee4dU), bswap_32big(0x00e04254U), bswap_32big(0x3564739eU), bswap_32big(0x6aa26212U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0xd922090dU);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &ARG2[iLoop]);

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xe7008d05U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &ARG3[1 + iLoop]);

            r_rsip_func101(bswap_32big(0xbf958e49U), bswap_32big(0x7969269bU), bswap_32big(0xde1e2eacU), bswap_32big(0x81db679eU));
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0x6d5db736U), bswap_32big(0xe01fbf58U), bswap_32big(0x64d3fb52U), bswap_32big(0xdaf02bfaU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000016U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0x4c11fd5bU), bswap_32big(0xea6204a2U), bswap_32big(0x8dcf1218U), bswap_32big(0xd2e2cf64U));
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0xd922090dU);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &ARG2[iLoop]);

            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0xe8008105U);
            WR1_PROG(REG_0000H, 0x00410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0008H, 0x00001012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD4_ADDR(REG_002CH, &ARG3[1 + iLoop]);

            r_rsip_func101(bswap_32big(0x582bf76dU), bswap_32big(0x92517251U), bswap_32big(0x6dcaf171U), bswap_32big(0xade6ea13U));
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0xf1702669U), bswap_32big(0xfb20dc03U), bswap_32big(0x5c0b23b9U), bswap_32big(0x26006f6cU));
    }

    r_rsip_func100(bswap_32big(0xcb76b4ceU), bswap_32big(0x4355f6f9U), bswap_32big(0x94aa6b09U), bswap_32big(0x43495277U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c000104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x09108105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &ARG3[1 + oLoop]);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x0922090dU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG2[iLoop]);

    WR1_PROG(REG_00D0H, 0x9c300005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0094H, 0x000034e3U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
