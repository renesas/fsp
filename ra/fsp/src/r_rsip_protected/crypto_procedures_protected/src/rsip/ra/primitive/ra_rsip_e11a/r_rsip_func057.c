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

    r_rsip_func101(bswap_32big(0x32cfc93aU),
                   bswap_32big(0xa9be18e2U),
                   bswap_32big(0xfa6b6e02U),
                   bswap_32big(0x6db296e3U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x000034c4U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x000000feU));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0x55727707U),
                   bswap_32big(0x797b7bd3U),
                   bswap_32big(0xba811ed4U),
                   bswap_32big(0xd52d8996U));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0x9d755203U),
                   bswap_32big(0xcd4c6313U),
                   bswap_32big(0x3bc31b32U),
                   bswap_32big(0xb7ca2e83U));

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
            r_rsip_func100(bswap_32big(0x33d6092bU), bswap_32big(0x82f4b241U), bswap_32big(0xdad07a92U),
                           bswap_32big(0xc660daa9U));
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

            r_rsip_func101(bswap_32big(0xada8180aU), bswap_32big(0x279b92d7U), bswap_32big(0xb4ad3bccU),
                           bswap_32big(0x7e67de85U));
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0xbe6ae8bfU), bswap_32big(0xdf2021a2U), bswap_32big(0x89b0c369U),
                       bswap_32big(0xf604d556U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000016U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); )
        {
            r_rsip_func100(bswap_32big(0x95e38f3eU), bswap_32big(0xab2f89dfU), bswap_32big(0x3e49f63cU),
                           bswap_32big(0x7d4f9186U));
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

            r_rsip_func101(bswap_32big(0xdc7887cbU), bswap_32big(0x0c39edeaU), bswap_32big(0xb63e4fa0U),
                           bswap_32big(0xb29a7997U));
            iLoop = iLoop + 4U;
        }

        oLoop = iLoop;

        r_rsip_func101(bswap_32big(0x14ab75f8U), bswap_32big(0xe2a1a6b4U), bswap_32big(0x795bffefU),
                       bswap_32big(0xc8013792U));
    }

    r_rsip_func100(bswap_32big(0xcb76b4ceU),
                   bswap_32big(0x4355f6f9U),
                   bswap_32big(0x94aa6b09U),
                   bswap_32big(0x43495277U));
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
