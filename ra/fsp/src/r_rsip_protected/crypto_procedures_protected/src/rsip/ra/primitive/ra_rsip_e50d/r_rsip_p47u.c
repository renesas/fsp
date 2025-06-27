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

void r_rsip_p47u (uint32_t const InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x3a2354a1U), bswap_32big(0x54199b04U), bswap_32big(0xc4156b93U),
                       bswap_32big(0xd55f6ebaU));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a000106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x99ba8cefU), bswap_32big(0x63f5414cU), bswap_32big(0x8cdcd890U),
                       bswap_32big(0x24d210d7U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a00010eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x993f883fU), bswap_32big(0x7920a7f7U), bswap_32big(0x9e2488a7U),
                       bswap_32big(0x7db23ae7U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0e000506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x395149eaU), bswap_32big(0x82cecc13U), bswap_32big(0xc38d8759U),
                       bswap_32big(0x077fa6dbU));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0900090eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xdbb0efd9U), bswap_32big(0xecf2f4e6U), bswap_32big(0x7084cfb6U),
                       bswap_32big(0x5b481e64U));

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x07000d06U);
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

        r_rsip_func101(bswap_32big(0xe0ab8198U), bswap_32big(0x89323c6bU), bswap_32big(0xecfdb396U),
                       bswap_32big(0x2b843bcaU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x7d057555U), bswap_32big(0x69c1a7ecU), bswap_32big(0x590253c9U),
                       bswap_32big(0xcccd5b37U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x8d3652b1U), bswap_32big(0x1b846e72U), bswap_32big(0xdeb48362U),
                       bswap_32big(0x2b00c63fU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x9f659e29U), bswap_32big(0x934675e9U), bswap_32big(0xa9b54b7bU),
                       bswap_32big(0xb93e085dU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x2c71731eU), bswap_32big(0x60d7f514U), bswap_32big(0x169e094eU),
                       bswap_32big(0xfa9f7109U));
    }
    else
    {
        ;
    }
}
