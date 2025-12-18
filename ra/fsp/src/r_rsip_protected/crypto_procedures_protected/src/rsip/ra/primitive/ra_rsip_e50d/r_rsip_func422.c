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

void r_rsip_func422 (const uint32_t ARG1[], uint32_t ARG2)
{
    uint32_t jLoop = 0U;

    r_rsip_func100(bswap_32big(0xa5963577U),
                   bswap_32big(0xac8d53eeU),
                   bswap_32big(0xb4eb4162U),
                   bswap_32big(0x3865a5e3U));
    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x00000010U);
    WR1_PROG(REG_1444H, 0x000003c7U);
    WR1_PROG(REG_1608H, 0x80840007U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, ARG1[ARG2 + 4]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, ARG1[ARG2 + 5]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, ARG1[ARG2 + 6]);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, ARG1[ARG2 + 7]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x0000b4a0U);
    WR1_PROG(REG_1600H, 0x00000004U);

    WR1_PROG(REG_1600H, 0x00003500U);
    WR1_PROG(REG_1600H, 0x00036908U);
    WR1_PROG(REG_1600H, 0x00008d00U);
    WR1_PROG(REG_1600H, 0x0000000cU);

    WR1_PROG(REG_1600H, 0x000024c8U);

    WR1_PROG(REG_1600H, 0x000024e8U);

    WR1_PROG(REG_1600H, 0x00003826U);

    WR1_PROG(REG_1600H, 0x00003847U);

    WR1_PROG(REG_1600H, 0x00003460U);
    WR1_PROG(REG_1600H, 0x00008c60U);
    WR1_PROG(REG_1600H, 0x0000001fU);

    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1600H, 0xffffffffU);
    WR1_PROG(REG_1600H, 0x00004403U);
    WR1_PROG(REG_1600H, 0x00007484U);

    WR1_PROG(REG_1600H, 0x00000c24U);

    WR1_PROG(REG_1600H, 0x00001484U);

    WR1_PROG(REG_1600H, 0x00000c44U);

    WR1_PROG(REG_1600H, 0x00001041U);

    WR1_PROG(REG_1600H, 0x00003c47U);

    WR1_PROG(REG_1600H, 0x000037e0U);
    WR1_PROG(REG_1600H, 0x00008fe0U);
    WR1_PROG(REG_1600H, 0x0000007fU);

    WR1_PROG(REG_1600H, 0x38008fe0U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x1000a7e0U);
    WR1_PROG(REG_1600H, 0x00000020U);

    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x00002bdfU);
    WR1_PROG(REG_1600H, 0x00056bdeU);
    WR1_PROG(REG_1600H, 0x0000353eU);

    WR1_PROG(REG_1608H, 0x810103c0U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
    {
        WR1_PROG(REG_1600H, 0x000024c5U);
        WR1_PROG(REG_1600H, 0x000024e5U);

        WR1_PROG(REG_1600H, 0x00003b86U);
        WR1_PROG(REG_1600H, 0x00003f87U);

        WR1_PROG(REG_1600H, 0x000033c0U);
        r_rsip_func101(bswap_32big(0xb77f8759U), bswap_32big(0xdaf38eccU), bswap_32big(0x122d89bdU),
                       bswap_32big(0xc1f0ee34U));
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000fdeU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_143CH, 0x00402000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
