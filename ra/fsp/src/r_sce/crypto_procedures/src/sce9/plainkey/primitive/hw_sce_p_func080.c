/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func080 (void)
{
    WR1_PROG(REG_C4H, 0x00440a0cU);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));

    WR1_PROG(REG_C4H, 0x00080e9cU);
    HW_SCE_p_func_sub010(0x81010020U, 0x00002807U);
}
