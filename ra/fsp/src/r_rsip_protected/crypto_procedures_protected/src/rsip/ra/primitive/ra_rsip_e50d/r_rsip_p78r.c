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

rsip_ret_t r_rsip_p78r (const uint32_t InData_HashType[], const uint32_t InData_State[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00780001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xc9de5e79U), bswap_32big(0x94fcc9a8U), bswap_32big(0x6152437dU), bswap_32big(0x45d10fafU));
    WR1_PROG(REG_2400H, 0x00000001U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x2000b400U);
    WR1_PROG(REG_1600H, 0x00000003U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_2404H, 0x00001001U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000024U);

        r_rsip_func101(bswap_32big(0xa33c413dU), bswap_32big(0xb0dae658U), bswap_32big(0xdeb98f0cU), bswap_32big(0x67830508U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_2404H, 0x00001011U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000022U);

        r_rsip_func101(bswap_32big(0x7f2cf0fbU), bswap_32big(0xa219a453U), bswap_32big(0x1be3ab9fU), bswap_32big(0x43bd4b0dU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_2404H, 0x00001021U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x0000001aU);

        r_rsip_func101(bswap_32big(0xdbe2c707U), bswap_32big(0x9397b085U), bswap_32big(0x11fb3de1U), bswap_32big(0x1ab27372U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_2404H, 0x00001031U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000012U);

        r_rsip_func101(bswap_32big(0x0bc4ba32U), bswap_32big(0xba7188caU), bswap_32big(0xe59ddaefU), bswap_32big(0x30e55b98U));
    }

    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2414H, InData_State[50]);
    WR1_PROG(REG_1444H, 0x00000040U);
    WR1_PROG(REG_2410H, InData_State[51]);

    for (iLoop = 0U; iLoop < 50; iLoop++)
    {
        WR1_PROG(REG_1444H, 0x00000040U);
        WR1_PROG(REG_2438H, InData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    r_rsip_func100(bswap_32big(0xbf8498aeU), bswap_32big(0x5add2501U), bswap_32big(0xf6717301U), bswap_32big(0x5425d5c0U));
    WR1_PROG(REG_1608H, 0x81010020U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = bswap_32big(S_RAM[0]);

    r_rsip_func101(bswap_32big(0x6cabc4ceU), bswap_32big(0xaa09ecd6U), bswap_32big(0x38b1fdebU), bswap_32big(0xcfe7485aU));

    return RSIP_RET_PASS;
}
