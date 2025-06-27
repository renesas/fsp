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

void r_rsip_p89u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xf303b8e1U), bswap_32big(0x1af85895U), bswap_32big(0xd5b03a02U),
                       bswap_32big(0x6e44dc9dU));

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0a008106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x5edc1b03U), bswap_32big(0xd9391454U), bswap_32big(0xe3126acdU),
                       bswap_32big(0x3ea084ddU));

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0a00810eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xe455a433U), bswap_32big(0xe1a0e21aU), bswap_32big(0x4c3ca482U),
                       bswap_32big(0x8168c8a7U));

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0e008506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xe41e0443U), bswap_32big(0x1f8369b5U), bswap_32big(0x188c6164U),
                       bswap_32big(0xf34dee1eU));

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0900890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x7ad2412cU), bswap_32big(0x32e3ba10U), bswap_32big(0x81728959U),
                       bswap_32big(0x3e431a0dU));

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
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

        r_rsip_func101(bswap_32big(0xe314fed8U), bswap_32big(0x2f1b277fU), bswap_32big(0x5ee0601eU),
                       bswap_32big(0x20dc8d93U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0xac21296cU), bswap_32big(0x74c982d6U), bswap_32big(0x9c2cd4b5U),
                       bswap_32big(0x228a3134U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0xd04cf276U), bswap_32big(0x0f2de17eU), bswap_32big(0x4b5d93f7U),
                       bswap_32big(0x7b7feebaU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0xb99d2cb7U), bswap_32big(0xd1c91f22U), bswap_32big(0xb66687b5U),
                       bswap_32big(0x3ce6f5dbU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func214();

        r_rsip_func101(bswap_32big(0x9654977aU), bswap_32big(0xd9dab7afU), bswap_32big(0x60d4b208U),
                       bswap_32big(0xda074296U));
    }
    else
    {
        ;
    }
}
