/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func054 (uint32_t ARG1, uint32_t ARG2)
{
    WR1_PROG(REG_14H, change_endian_long(ARG1));
    WR1_PROG(REG_14H, change_endian_long(ARG2));
    WR1_PROG(REG_1D0H, 0x00000000U);
    WR1_PROG(REG_1D0H, 0x00000000U);
}
