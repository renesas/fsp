/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func312 (uint32_t ARG1)
{
    uint32_t iLoop2 = 0U;

    WR1_PROG(REG_104H, 0x00003f62U);
    WR1_PROG(REG_D0H, 0x00000f00U);
    WR1_PROG(REG_C4H, 0x42f087bfU);

    for (iLoop2 = 0; iLoop2 < 64; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &S_HEAP[ARG1 + iLoop2]);
        iLoop2 = iLoop2 + 4;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_C4H, 0x400007bdU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_HEAP[ARG1 + iLoop2]);

    HW_SCE_p_func_sub013(0x00800c45U, 0x00002213U);
}
