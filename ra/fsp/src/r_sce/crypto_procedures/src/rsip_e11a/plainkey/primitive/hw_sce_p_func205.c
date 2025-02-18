/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func205_r1 (void)
{
    WR1_PROG(REG_14H, 0x00000000U);
    WAIT_STS(REG_C8H, 6, 0);
    WR1_PROG(REG_40H, 0x00000400U);
    WR1_PROG(REG_40H, 0x00000600U);
    WR1_PROG(REG_40H, 0x00000500U);
    WR1_PROG(REG_D0H, 0x00000000U);
}
