/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func405 (void)
{
    WR1_PROG(REG_1600H, 0x000037e8U);
    WR1_PROG(REG_1600H, 0x00056bffU);
    WR1_PROG(REG_1600H, 0x00026fffU);
    WR1_PROG(REG_1600H, 0x0000381fU);

    WR1_PROG(REG_1600H, 0x000037e8U);
    WR1_PROG(REG_1600H, 0x000037c1U);
    WR1_PROG(REG_1600H, 0x00000fe1U);
    WR1_PROG(REG_1600H, 0x00002bdfU);
    WR1_PROG(REG_1600H, 0x0000441eU);
    WR1_PROG(REG_1600H, 0x00007400U);
    WR1_PROG(REG_1600H, 0x00000c13U);
}
