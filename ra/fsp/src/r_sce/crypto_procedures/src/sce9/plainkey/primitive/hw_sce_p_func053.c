/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func053 (uint32_t ARG1)
{
    HW_SCE_p_func051();

    WR1_PROG(REG_80H, 0x00000001U);
    WR1_PROG(REG_8CH, change_endian_long(ARG1));
    WR1_PROG(REG_14H, 0x00003008U);
    WR1_PROG(REG_14H, 0x00003018U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
    WAIT_STS(REG_00H, 31, 0);
}
