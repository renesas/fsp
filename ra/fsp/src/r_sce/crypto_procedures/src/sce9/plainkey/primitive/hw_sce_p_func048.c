/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func048 (uint32_t ARG1[])
{
    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(ARG1[0]));
}
