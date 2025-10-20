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

    WR1_PROG(REG_0014H, 0x000003c1U);
    r_rsip_func100(bswap_32big(0xd3cf3464U),
                   bswap_32big(0x7a0ecd06U),
                   bswap_32big(0x18aeae21U),
                   bswap_32big(0xe7194bf5U));

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_009CH, 0x00000008U);
    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D0H, 0x00008006U);
    WR1_PROG(REG_0008H, 0x000c1000U);

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

    r_rsip_func206();

    r_rsip_func101(bswap_32big(0x48cc80e5U),
                   bswap_32big(0x899f0225U),
                   bswap_32big(0x8833a9d2U),
                   bswap_32big(0x067e6f97U));
}
