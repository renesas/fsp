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

void r_rsip_func030 (void)
{
    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_0094H, 0x1000b4a0U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x1000b4c0U);
    WR1_PROG(REG_0094H, 0x00000005U);
    WR1_PROG(REG_0094H, 0x1000b4e0U);
    WR1_PROG(REG_0094H, 0x00000009U);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000002U);
    WR1_PROG(REG_0094H, 0x1000b4a0U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x1000b4c0U);
    WR1_PROG(REG_0094H, 0x00000007U);
    WR1_PROG(REG_0094H, 0x1000b4e0U);
    WR1_PROG(REG_0094H, 0x0000000dU);
}
