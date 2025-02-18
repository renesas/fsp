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

void r_rsip_p47u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x222cc1e1U), bswap_32big(0x82df501cU), bswap_32big(0x99e6c6c5U), bswap_32big(0x86db9554U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0a000106U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x119e8bdbU), bswap_32big(0x8b65fcfeU), bswap_32big(0x1853028fU), bswap_32big(0x2bb5ed36U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0a00010eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0xedf05a81U), bswap_32big(0x7507e84bU), bswap_32big(0x732c8312U), bswap_32big(0x94505e02U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0e000506U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0xd3e10e5eU), bswap_32big(0x61979596U), bswap_32big(0xc0097a9aU), bswap_32big(0xddcda80eU));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0900090eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x531b7f20U), bswap_32big(0x83a74dd3U), bswap_32big(0xe9211538U), bswap_32big(0x678bb59aU));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x07000d06U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x55c3b39bU), bswap_32big(0x006ea0f7U), bswap_32big(0x3a26156aU), bswap_32big(0xd67723c6U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x7c1497a4U), bswap_32big(0x89003029U), bswap_32big(0x7520cff5U), bswap_32big(0x1dac5a67U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0xb02d9275U), bswap_32big(0xe10bdc5cU), bswap_32big(0xa7e129c7U), bswap_32big(0x8d0b176eU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0xc836c506U), bswap_32big(0xa36a87b2U), bswap_32big(0xdbc51c43U), bswap_32big(0xfdc71320U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x0729199cU), bswap_32big(0x1ffcc9c3U), bswap_32big(0x38be75baU), bswap_32big(0xc4556a0eU));
    }
}
