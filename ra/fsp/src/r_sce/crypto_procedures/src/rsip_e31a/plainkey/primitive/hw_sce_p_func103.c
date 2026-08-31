/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func103 (void)
{
    HW_SCE_p_func_sub004(0x000002a1U, 0x07330c04U, 0x00000000U);

    HW_SCE_p_func_sub018(0x07330d04U, 0x00000000U);

    HW_SCE_p_func_sub018(0x07330d04U, 0x00000000U);

    WR1_PROG(REG_D0H, 0x08000065U);
    HW_SCE_p_func_sub003(0x00410011U);

    HW_SCE_p_func_sub004(0x000000a1U, 0x06330074U, 0x00000000U);

    WR1_PROG(REG_D0H, 0x080000b5U);
    HW_SCE_p_func_sub003(0x00410011U);
}
