/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func501 (const uint32_t ARG1[], const uint32_t ARG2[], const uint32_t ARG3)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x08000145U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[0]);

    WR1_PROG(REG_D0H, 0x08000065U);
    WR1_PROG(REG_00H, 0x00410011U);
    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x07000c04U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x08000054U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

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
