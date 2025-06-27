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

void r_rsip_func016 (uint32_t ARG1)
{
    uint32_t oLoop = 0U;

    r_rsip_func100(bswap_32big(0x6f1ac5a9U),
                   bswap_32big(0xa623b33bU),
                   bswap_32big(0xbe75b461U),
                   bswap_32big(0x5cd3d5ccU));
    WR1_PROG(REG_1600H, 0x00000821U);
    WR1_PROG(REG_1600H, 0x0000b440U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x00000863U);

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000044U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000054U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0 + 2]);
    S_RAM[0 + 2] = bswap_32big(S_RAM[0 + 2]);

    for (oLoop = 0U; oLoop < S_RAM[0 + 2]; )
    {
        WR1_PROG(REG_1600H, 0x34202820U);
        WR1_PROG(REG_1600H, 0x2000d060U);
        WR1_PROG(REG_1600H, 0x00007c03U);
        WR1_PROG(REG_143CH, 0x00602000U);
        WR1_PROG(REG_1458H, 0x00000000U);

        r_rsip_func100(bswap_32big(0x9c2e3e2aU), bswap_32big(0x7ee70e3bU), bswap_32big(0x22c4ad1fU),
                       bswap_32big(0xe2233620U));
        WR1_PROG(REG_1A24H, 0xe70c0d05U);
        WR1_PROG(REG_1400H, 0x00830011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1408H, 0x00002012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &S_HEAP[ARG1 + oLoop]);

        WR1_PROG(REG_1600H, 0x00002422U);

        r_rsip_func101(bswap_32big(0x33a34c03U), bswap_32big(0x2465cc63U), bswap_32big(0x760883d2U),
                       bswap_32big(0x69a0de7dU));
        oLoop = oLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000801U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0x0199b139U),
                   bswap_32big(0x136515d9U),
                   bswap_32big(0xef3162ccU),
                   bswap_32big(0xe347a6faU));
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c000104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));

    WR1_PROG(REG_1A24H, 0x091c0105U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1408H, 0x00002012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &S_HEAP[ARG1 + oLoop]);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
