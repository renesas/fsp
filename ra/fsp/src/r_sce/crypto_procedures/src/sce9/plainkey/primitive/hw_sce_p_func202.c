/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func202 (void)
{
    WR1_PROG(REG_04H, 0x00000000U);
    WR1_PROG(REG_104H, 0x00000000U);
    WR1_PROG(REG_A4H, 0x00000000U);
    WR1_PROG(REG_1CH, 0x00001800U);
    WR1_PROG(REG_00H, 0x00000000U);
    WR1_PROG(REG_C4H, 0x00000000U);
    WR1_PROG(REG_1CH, 0x00000900U);
}
