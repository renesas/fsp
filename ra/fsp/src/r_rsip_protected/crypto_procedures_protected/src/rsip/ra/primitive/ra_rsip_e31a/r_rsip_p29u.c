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

void r_rsip_p29u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    r_rsip_func100(bswap_32big(0x22eb8177U),
                   bswap_32big(0x4a26345bU),
                   bswap_32big(0xec7873ebU),
                   bswap_32big(0xdc603260U));

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D4H, 0x00000020U);
    WR1_PROG(REG_00D0H, 0x20008d06U);
    WR1_PROG(REG_0008H, 0x000c1000U);

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
    RD4_ADDR(REG_002CH, &OutData_Text[iLoop - 4]);

    r_rsip_func206();

    r_rsip_func101(bswap_32big(0xd371d4e5U),
                   bswap_32big(0xacc75c48U),
                   bswap_32big(0x65dc610aU),
                   bswap_32big(0xbe26b091U));
}
