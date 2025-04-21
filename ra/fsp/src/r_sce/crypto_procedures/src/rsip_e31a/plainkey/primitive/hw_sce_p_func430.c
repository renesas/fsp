/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func430 (const uint32_t ARG1[], uint32_t ARG2)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D4H, 0x00008000U);
    WR1_PROG(REG_D0H, 0x0e128456U);

    for (iLoop = 0U; iLoop < ARG2; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205();
}
