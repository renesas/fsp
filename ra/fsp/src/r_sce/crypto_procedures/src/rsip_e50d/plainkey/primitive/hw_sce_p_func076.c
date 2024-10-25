/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func076_r1 (void)
{
    WR1_PROG(REG_1600H, 0x38000f5aU);
    WR1_PROG(REG_1600H, 0x00030020U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000019U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1600H, 0x00000080U);
}
