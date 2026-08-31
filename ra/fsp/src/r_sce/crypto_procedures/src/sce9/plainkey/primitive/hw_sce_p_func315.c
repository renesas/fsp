/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func315 (uint32_t ARG1)
{
    WR1_PROG(REG_28H, 0x00800001U);
    WR1_PROG(REG_104H, 0x00000157U);
    WR1_PROG(REG_2CH, 0x00000050U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000001U));

    WR1_PROG(REG_E0H, 0x8181001eU);
    HW_SCE_p_func_sub011(0x00003807U, ARG1);

    WR1_PROG(REG_2CH, 0x00000050U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));
    WR1_PROG(REG_28H, 0x00bf0001U);
}
