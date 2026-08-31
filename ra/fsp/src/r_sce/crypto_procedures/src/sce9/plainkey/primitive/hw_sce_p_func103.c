/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func103 (void)
{
    HW_SCE_p_func_sub012(0x00000252U, 0x01003774U, 0x00000000U);

    WR1_PROG(REG_C4H, 0x010037f4U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_C4H, 0x010037f4U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    HW_SCE_p_func_sub013(0x00060805U, 0x00002213U);

    HW_SCE_p_func_sub012(0x00000052U, 0x01073644U, 0x00000000U);

    HW_SCE_p_func_sub013(0x000b0805U, 0x00002213U);
}
