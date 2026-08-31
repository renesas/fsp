/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func501 (const uint32_t ARG1[], const uint32_t ARG2[], const uint32_t ARG3)
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub011(0x000003c1U, 0x08000145U);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    WR1_PROG(REG_D0H, 0x08000065U);
    HW_SCE_p_func_sub003(0x00410011U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x07000c04U, 0x00000000U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x08000054U, 0x00000000U);

    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D0H, 0x0e108406U);

    for (iLoop = 0U; iLoop < ARG3; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG2[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205();
}
