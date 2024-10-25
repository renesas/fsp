/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_SoftwareResetSub (void)
{
    WR1_PROG(REG_140CH, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}

