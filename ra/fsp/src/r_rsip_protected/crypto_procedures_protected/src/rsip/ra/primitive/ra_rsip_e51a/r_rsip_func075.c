/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func075 (void)
{
    WR1_PROG(REG_1600H, 0x30003340U);
    WR1_PROG(REG_1600H, 0x00050020U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000022U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x0000001cU);
    WR1_PROG(REG_1600H, 0x00070040U);
    WR1_PROG(REG_1600H, 0x30003380U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000016U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000014U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000012U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x00000080U);
}
