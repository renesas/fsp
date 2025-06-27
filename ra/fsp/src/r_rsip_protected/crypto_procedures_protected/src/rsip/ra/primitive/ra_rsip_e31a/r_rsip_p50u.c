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

void r_rsip_p50u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0xa6e70cd4U), bswap_32big(0xeecab6b1U), bswap_32big(0x4ce59772U),
                       bswap_32big(0xc04c1d3fU));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a008106U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x08c6c554U), bswap_32big(0x976337a9U), bswap_32big(0x0e14de77U),
                       bswap_32big(0x56f7de28U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a00810eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0xe4808fb5U), bswap_32big(0xab9c55a7U), bswap_32big(0x640679b6U),
                       bswap_32big(0x441b5078U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008506U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x56d70ed0U), bswap_32big(0x943c20aaU), bswap_32big(0x17ffc166U),
                       bswap_32big(0x7e9b9d07U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0900890eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x92795774U), bswap_32big(0xf92f7398U), bswap_32big(0x071234a3U),
                       bswap_32big(0x3b696162U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d06U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_Text[iLoop - 4]);
    }

    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x8618be11U), bswap_32big(0xc6e7c77dU), bswap_32big(0x567af3a4U),
                       bswap_32big(0xc2b3ed27U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x7d1f1b71U), bswap_32big(0xfb9afc5bU), bswap_32big(0xf720fcbeU),
                       bswap_32big(0xf510ef2dU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0xbac003b5U), bswap_32big(0xe8dc7359U), bswap_32big(0x12d6906aU),
                       bswap_32big(0xa57a0834U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0xd82ecd20U), bswap_32big(0xcf935597U), bswap_32big(0xbbfb815eU),
                       bswap_32big(0xb5eda2f0U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0xd4af07f2U), bswap_32big(0xce361b41U), bswap_32big(0x041e2fdaU),
                       bswap_32big(0x22056c4eU));
    }
}
