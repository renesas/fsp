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

void r_rsip_func063 (const uint32_t ARG1, const uint32_t ARG2[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x00003fc1U);
    WR1_PROG(REG_182CH, 0x00000f00U);
    WR1_PROG(REG_1824H, 0xd900890fU);

    for (iLoop = ARG1; iLoop < ARG1 + 64U; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop]);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &ARG2[iLoop + 4]);
        WR1_PROG(REG_1400H, 0x00c10021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        iLoop = iLoop + 8U;
    }
}
