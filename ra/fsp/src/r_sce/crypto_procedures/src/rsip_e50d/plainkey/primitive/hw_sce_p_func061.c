/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func061 (uint32_t ARG1, const uint32_t ARG2[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x00001fc1U);
    WR1_PROG(REG_182CH, 0x00000700U);
    WR1_PROG(REG_1824H, 0xd900890fU);

    for (iLoop = ARG1; iLoop < ARG1 + 32U; )
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

