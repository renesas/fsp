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

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x02e2bebbU), bswap_32big(0x197f36b2U), bswap_32big(0x2dab0db6U),
                       bswap_32big(0x8a6edbf4U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a008106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x8e117143U), bswap_32big(0xf50e82bbU), bswap_32big(0x24d387a5U),
                       bswap_32big(0x08be162cU));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a00810eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x8f5136ceU), bswap_32big(0xcc92a0bfU), bswap_32big(0xae1d5aa4U),
                       bswap_32big(0x4c80ddc3U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xc5831880U), bswap_32big(0x638beea0U), bswap_32big(0xef27fe4fU),
                       bswap_32big(0x39eb4be1U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0900890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x7c9a6a45U), bswap_32big(0x1458c047U), bswap_32big(0xbe0431e0U),
                       bswap_32big(0x4f94615bU));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x07008d06U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else
    {
        ;
    }

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Text[0]);
    for (iLoop = 4U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x08d83b3aU), bswap_32big(0xf809bf2eU), bswap_32big(0x078e4610U),
                       bswap_32big(0x221efdd8U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0xe5187f09U), bswap_32big(0xac474836U), bswap_32big(0x1afc0432U),
                       bswap_32big(0x958fd8faU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0xf3dc0990U), bswap_32big(0x5239d741U), bswap_32big(0xe177e8caU),
                       bswap_32big(0xaedd1c19U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x6c296703U), bswap_32big(0x3ab077efU), bswap_32big(0xc39ef4e1U),
                       bswap_32big(0x8d60bf8fU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x27bd620fU), bswap_32big(0xbf71e04aU), bswap_32big(0xf2b0b401U),
                       bswap_32big(0x39d52466U));
    }
    else
    {
        ;
    }
}
