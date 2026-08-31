/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func321 (uint32_t ARG1)
{
    uint32_t iLoop2 = 0U;

    WR1_PROG(REG_D0H, 0x00000800U);
    WR1_PROG(REG_C4H, 0x42e087bfU);
    WR1_PROG(REG_04H, 0x00000292U);

    for (iLoop2 = 0; iLoop2 < 36; )
    {
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &S_HEAP[ARG1 + iLoop2]);
        iLoop2 = iLoop2 + 4;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}
