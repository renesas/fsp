/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Chacha20Poly1305UpdateTransitionSub (void)
{
    HW_SCE_p_func100(0xc44c19e8U, 0xb2c78668U, 0x5c78af6bU, 0xaa624806U);
    WR1_PROG(REG_1600H, 0x0000b440U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1608H, 0x81010040U);
    WR1_PROG(REG_1408H, 0x00005006U);
    WAIT_STS(REG_1408H, 30, 1);
    RD1_ADDR(REG_1420H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    HW_SCE_p_func101(0x3d359954U, 0x61073a9bU, 0x3bfea2c4U, 0x2d8e7a37U);
}
