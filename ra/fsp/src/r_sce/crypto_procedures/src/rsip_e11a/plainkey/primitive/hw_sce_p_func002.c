/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func002 (void)
{
    WR1_PROG(REG_00H, 0x01410041U);
    WR1_PROG(REG_14H, 0x00000fa1U);

    WR1_PROG(REG_D0H, 0x0c000105U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_PROG(REG_2CH,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WR1_PROG(REG_D0H, 0x0c100105U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_PROG(REG_2CH,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WR1_PROG(REG_D4H, 0x00000100U);
    WR1_PROG(REG_D0H, 0x08008107U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_PROG(REG_2CH,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));
    WAIT_STS(REG_14H, 31, 1);
    WR4_PROG(REG_2CH,
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU),
             change_endian_long(0x5c5c5c5cU));

    WAIT_STS(REG_04H, 30, 0);
    WR1_PROG(REG_40H, 0x00001800U);
}
