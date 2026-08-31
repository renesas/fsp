/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func314 (uint32_t ARG1)
{
    HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

    HW_SCE_p_func_sub013(0x400009cdU, 0x00002213U);

    WR1_PROG(REG_04H, 0x00000213U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &S_HEAP[ARG1]);
}
