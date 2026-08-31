/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func050 (uint32_t ARG1)
{
    WR1_PROG(REG_138H, 0xf597806AU);
    WR1_PROG(REG_F0H, 0x00000000U);
    WR1_PROG(REG_14H, 0x10000000U);
    WR1_PROG(REG_10CH, change_endian_long(ARG1));
}
