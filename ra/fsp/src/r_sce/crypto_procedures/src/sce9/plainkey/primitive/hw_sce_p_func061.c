/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func061 (uint32_t ARG1, uint32_t ARG2[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_104H, 0x00001f61U);
    WR1_PROG(REG_B0H, 0x00000700U);
    WR1_PROG(REG_A4H, 0x00d0c9a7U);

    for (iLoop = ARG1; iLoop < ARG1 + 32; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &ARG2[iLoop]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}
