/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func207 (void)
{
    WR1_PROG(REG_04H, 0x00000000U);
    WR1_PROG(REG_104H, 0x00000000U);
    WAIT_STS(REG_A8H, 6, 0);

    WR1_PROG(REG_1CH, 0x002c0000U);
    WR1_PROG(REG_1CH, 0x002d0000U);
    WR1_PROG(REG_B0H, 0x00000001U);
    WR1_PROG(REG_A4H, 0x00000000U);
}
