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
    WR1_PROG(REG_002CH, bswap_32big(0x0000f057U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xdb2f5c77U),
                   bswap_32big(0x06ab7c7eU),
                   bswap_32big(0x99aec338U),
                   bswap_32big(0x8f44f983U));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x000034c4U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x0000f057U));
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func101(bswap_32big(0xafeebd1fU),
                   bswap_32big(0x4eca3f4aU),
                   bswap_32big(0x4a08f0a0U),
                   bswap_32big(0xcf44400fU));
    r_rsip_func044();

    r_rsip_func100(bswap_32big(0xddbdb442U),
                   bswap_32big(0x20ef8f72U),
                   bswap_32big(0xf061caaaU),
                   bswap_32big(0x9d38d670U));

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

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); iLoop = iLoop + 4U)
        {
            r_rsip_func100(bswap_32big(0x4045d99fU), bswap_32big(0x9a972f9eU), bswap_32big(0x51d763b6U),
                           bswap_32big(0xacaa9e21U));
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

            r_rsip_func101(bswap_32big(0x39d94737U), bswap_32big(0x46b17419U), bswap_32big(0x457d72efU),
                           bswap_32big(0x18c93db3U));
        }

        r_rsip_func101(bswap_32big(0xd401b5dbU), bswap_32big(0x60a6c5a1U), bswap_32big(0x0fcbb5deU),
                       bswap_32big(0x3a68fb4cU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000016U)
    {
        for (iLoop = 0U; iLoop < (INST_DATA_SIZE - 4); iLoop = iLoop + 4U)
        {
            r_rsip_func100(bswap_32big(0xd761268aU), bswap_32big(0x557de3d6U), bswap_32big(0x8ddb7e79U),
                           bswap_32big(0xe9e53892U));
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

            r_rsip_func101(bswap_32big(0xf1562fd3U), bswap_32big(0x0b79a2cbU), bswap_32big(0xf0a8b0a2U),
                           bswap_32big(0xb839b8b1U));
        }

        r_rsip_func101(bswap_32big(0x7d82ea86U), bswap_32big(0x7a045896U), bswap_32big(0x74f92816U),
                       bswap_32big(0x885a4e85U));
    }

    r_rsip_func100(bswap_32big(0xe7fafb88U),
                   bswap_32big(0x3f7fc741U),
                   bswap_32big(0x1d74c440U),
                   bswap_32big(0xd3023a8dU));
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
    RD4_ADDR(REG_002CH, &ARG3[1 + iLoop]);

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
}
