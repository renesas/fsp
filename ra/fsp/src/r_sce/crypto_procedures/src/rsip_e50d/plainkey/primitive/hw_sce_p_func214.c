/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func214(void)
{
    WR1_PROG(REG_1408H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00000400U);
    WR1_PROG(REG_143CH, 0x00000600U);
    WR1_PROG(REG_143CH, 0x00000500U);
    WR1_PROG(REG_1824H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}

