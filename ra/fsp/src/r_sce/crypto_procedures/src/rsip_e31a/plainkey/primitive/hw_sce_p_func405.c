/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func405 (void)
{
    WR1_PROG(REG_94H, 0x00003466U);
    WR1_PROG(REG_94H, 0x00056863U);
    WR1_PROG(REG_94H, 0x00026c63U);
    WR1_PROG(REG_94H, 0x00003803U);

    WR1_PROG(REG_94H, 0x00003466U);
    WR1_PROG(REG_94H, 0x00003481U);
    WR1_PROG(REG_94H, 0x00000c61U);
    WR1_PROG(REG_94H, 0x00002883U);
    WR1_PROG(REG_94H, 0x00004404U);
    WR1_PROG(REG_94H, 0x00007400U);
    WR1_PROG(REG_94H, 0x00000c02U);
}
