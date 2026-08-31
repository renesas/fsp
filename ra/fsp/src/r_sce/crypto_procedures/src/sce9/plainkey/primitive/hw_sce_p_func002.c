/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func002 (void)
{
    WR1_PROG(REG_00H, 0x00005143U);
    WR1_PROG(REG_104H, 0x00000f51U);

    WR1_PROG(REG_A4H, 0x00000c85U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WR1_PROG(REG_A4H, 0x00000cc5U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WR1_PROG(REG_B0H, 0x00000100U);
    WR1_PROG(REG_A4H, 0x00008887U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));
    WAIT_STS(REG_104H, 31, 1);
    WR4_PROG(REG_100H,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
}
