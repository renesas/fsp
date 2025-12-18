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

void r_rsip_func423 (uint32_t ARG1[], uint32_t ARG2)
{
    uint32_t jLoop = 0U;

    WR1_PROG(REG_1600H, 0x000008c6U);

    WR1_PROG(REG_1600H, 0x000024c8U);

    WR1_PROG(REG_1600H, 0x00003826U);

    WR1_PROG(REG_1600H, 0x00000c24U);

    WR1_PROG(REG_1600H, 0x00003c26U);

    WR1_PROG(REG_1600H, 0x00000bffU);

    for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
    {
        WR1_PROG(REG_1600H, 0x000024c5U);

        WR1_PROG(REG_1600H, 0x00003fe6U);

        WR1_PROG(REG_1600H, 0x00003120U);
        r_rsip_func101(bswap_32big(0x3cd11efeU), bswap_32big(0x247c55d2U), bswap_32big(0x73a3eb4cU),
                       bswap_32big(0xf970f89dU));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0x552f951bU),
                   bswap_32big(0x58204dc9U),
                   bswap_32big(0xfe1ab997U),
                   bswap_32big(0x8e59d6bdU));
    WR1_PROG(REG_1600H, 0x38000d29U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x000008c6U);
    WR1_PROG(REG_1608H, 0x81840006U);
    WR1_PROG(REG_1408H, 0x00005012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &ARG1[ARG2 + 4]);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &ARG1[ARG2 + 5]);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &ARG1[ARG2 + 6]);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &ARG1[ARG2 + 7]);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
