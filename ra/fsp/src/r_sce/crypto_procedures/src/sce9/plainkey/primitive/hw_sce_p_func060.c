/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func060 (void)
{
    WR1_PROG(REG_18H, 0x00000004U);
    WR1_PROG(REG_24H, 0x00004404U);
    WAIT_STS(REG_18H, 10, 0);

    WR1_PROG(REG_24H, 0x00004804U);
    WAIT_STS(REG_18H, 10, 0);
    WR1_PROG(REG_18H, 0x00000000U);
}
