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
        r_rsip_func100(bswap_32big(0xffc4b465U), bswap_32big(0x15077599U), bswap_32big(0x899fa274U), bswap_32big(0x7eb380adU));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a008106U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x0ca6720dU), bswap_32big(0xf16d7354U), bswap_32big(0xce0cb1caU), bswap_32big(0x83172e4eU));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a00810eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x97ec1b9dU), bswap_32big(0x189782caU), bswap_32big(0xec8d27f5U), bswap_32big(0xb16c8904U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008506U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0xb5408aa7U), bswap_32big(0x2f5d00c6U), bswap_32big(0xa73c5997U), bswap_32big(0x3cd849c0U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0900890eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        r_rsip_func100(bswap_32big(0x8d32f856U), bswap_32big(0x680e37fcU), bswap_32big(0x5c757c44U), bswap_32big(0x6f614b45U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d06U);
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

        r_rsip_func101(bswap_32big(0x30a18cc1U), bswap_32big(0xfa44cdb5U), bswap_32big(0xfae6803bU), bswap_32big(0x31415d42U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x90b4500bU), bswap_32big(0x0af6d614U), bswap_32big(0x4b08a45fU), bswap_32big(0x8a29fcfbU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x9030080fU), bswap_32big(0x7370c431U), bswap_32big(0x293de86bU), bswap_32big(0x068225d6U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x1b1cceb3U), bswap_32big(0x81e35b2bU), bswap_32big(0x646b14bfU), bswap_32big(0xc090ee9dU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func206();

        r_rsip_func101(bswap_32big(0x28bd1984U), bswap_32big(0xb9099a76U), bswap_32big(0xd2e34511U), bswap_32big(0xad888345U));
    }
}
