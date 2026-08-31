/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func064 (uint32_t ARG1, uint32_t ARG2[])
{
    uint32_t oLoop = 0U;

    WR1_PROG(REG_D0H, 0x40000f00U);
    WR1_PROG(REG_C4H, 0x00e087b7U);
    WR1_PROG(REG_04H, 0x00000202U);

    for (oLoop = ARG1; oLoop < ARG1 + 64; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &ARG2[1 + oLoop]);
        oLoop = oLoop + 4;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}
