/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func209 (void)
{
    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_1A28H, 6, 0);
    WR1_PROG(REG_143CH, 0x00000800U);
    WR1_PROG(REG_143CH, 0x00000a00U);
    WR1_PROG(REG_143CH, 0x00000900U);
    WR1_PROG(REG_1A24H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}

