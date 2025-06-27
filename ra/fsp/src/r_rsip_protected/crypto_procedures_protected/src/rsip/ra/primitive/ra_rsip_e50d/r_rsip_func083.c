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

void r_rsip_func083 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;

    r_rsip_func100(bswap_32big(0x0568b4e1U),
                   bswap_32big(0xbf0433caU),
                   bswap_32big(0x66adef04U),
                   bswap_32big(0xde527ecdU));
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100c0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, ARG1[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00003416U);
    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x0000b440U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x00002840U);

    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_1600H, 0x000008a5U);

    WR1_PROG(REG_1600H, 0x00003466U);

    for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
    {
        WR1_PROG(REG_1608H, 0x81010060U);
        WR1_PROG(REG_1400H, 0x12490005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x1009000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00086c63U);

        WR1_PROG(REG_1600H, 0x00002ca0U);

        r_rsip_func101(bswap_32big(0x821546c5U), bswap_32big(0xe5cbedc8U), bswap_32big(0x3782e44eU),
                       bswap_32big(0x6a9ecf45U));
    }

    WR1_PROG(REG_1600H, 0x38000845U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0x5a1e4294U),
                   bswap_32big(0xb7b2d990U),
                   bswap_32big(0x6074e52eU),
                   bswap_32big(0x73069a3cU));

    WR1_PROG(REG_1600H, 0x000034e6U);

    WR1_PROG(REG_1600H, 0x00036c00U);
    WR1_PROG(REG_1600H, 0x00004400U);

    WR1_PROG(REG_1608H, 0x81010160U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000001U);

    for (iLoop = 1; iLoop < S_RAM[0]; iLoop++)
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100c0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, ARG1[iLoop]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x00003506U);
        WR1_PROG(REG_1600H, 0x01807507U);
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1400H, 0x02490005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x000034e6U);

        WR1_PROG(REG_1600H, 0x00002ca0U);

        r_rsip_func101(bswap_32big(0x20482510U), bswap_32big(0x05a4e180U), bswap_32big(0xa3667c53U),
                       bswap_32big(0xe8d7b0fbU));
    }

    WR1_PROG(REG_1600H, 0x38000965U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38008ec0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    r_rsip_func100(bswap_32big(0x84d3852eU),
                   bswap_32big(0xe3377619U),
                   bswap_32big(0x415df6ebU),
                   bswap_32big(0x364c220bU));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1600H, 0x00000908U);
        WR1_PROG(REG_1600H, 0x01807507U);
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1400H, 0x02490005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        r_rsip_func101(bswap_32big(0x645141fcU), bswap_32big(0x6939e82aU), bswap_32big(0xe9f488bbU),
                       bswap_32big(0x4a7740b8U));
    }

    r_rsip_func100(bswap_32big(0xf5fcea36U),
                   bswap_32big(0xd41ed011U),
                   bswap_32big(0x386435cbU),
                   bswap_32big(0x3a0dbf36U));
    WR1_PROG(REG_1600H, 0x00003416U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x00026800U);
    WR1_PROG(REG_1600H, 0x0000240bU);

    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x0000b440U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x00002840U);

    WR1_PROG(REG_1600H, 0x00008c40U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    WR1_PROG(REG_1600H, 0x000008a5U);

    for (iLoop = 0U; iLoop < S_RAM[0]; iLoop++)
    {
        WR1_PROG(REG_1400H, 0x00400005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00002ca0U);

        r_rsip_func101(bswap_32big(0x007ba068U), bswap_32big(0xf1369610U), bswap_32big(0x1b6cbcc6U),
                       bswap_32big(0xa9a88bbeU));
    }

    WR1_PROG(REG_1600H, 0x38000845U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_2030H, 4, 1);

    WAIT_STS(REG_1828H, 6, 0);
    WR1_PROG(REG_143CH, 0x00000400U);
    WR1_PROG(REG_1824H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x8084001eU);
    WR1_PROG(REG_1400H, 0x03410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
