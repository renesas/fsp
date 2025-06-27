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

void r_rsip_func074 (void)
{
    WR1_PROG(REG_1600H, 0x30003340U);
    WR1_PROG(REG_1600H, 0x00050020U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000023U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x0000001dU);
    WR1_PROG(REG_1600H, 0x00070040U);
    WR1_PROG(REG_1600H, 0x30003380U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000017U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000015U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1600H, 0x00000013U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1600H, 0x00000080U);
}
