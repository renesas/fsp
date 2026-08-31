/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func102 (const uint32_t ARG1[])
{
    WR1_PROG(REG_C4H, 0x000d3a8dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H,
             change_endian_long(ARG1[0]),
             change_endian_long(ARG1[1]),
             change_endian_long(ARG1[2]),
             change_endian_long(ARG1[3]));
}
