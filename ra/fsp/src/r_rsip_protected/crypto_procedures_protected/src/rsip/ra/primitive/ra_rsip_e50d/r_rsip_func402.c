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

void r_rsip_func402 (void)
{
    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    r_rsip_func100(bswap_32big(0xe7c7a388U),
                   bswap_32big(0x6405c604U),
                   bswap_32big(0xa473c22aU),
                   bswap_32big(0xa487fa46U));
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1014H, 0x00000b60U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x00000750U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000bb0U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x000007a0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000c00U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x000007f0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        r_rsip_func101(bswap_32big(0x872cd0c2U), bswap_32big(0x3971cf55U), bswap_32big(0x47df5790U),
                       bswap_32big(0x98c9a2f9U));
    }
    else
    {
        WR1_PROG(REG_1014H, 0x00000480U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x00000750U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x000004d0U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x000007a0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1014H, 0x00000520U);
        WR1_PROG(REG_1018H, 0x00000b10U);
        WR1_PROG(REG_1020H, 0x000007f0U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        r_rsip_func101(bswap_32big(0xdfcff10dU), bswap_32big(0xdd0d6da3U), bswap_32big(0x80135499U),
                       bswap_32big(0xc7b3463aU));
    }

    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
