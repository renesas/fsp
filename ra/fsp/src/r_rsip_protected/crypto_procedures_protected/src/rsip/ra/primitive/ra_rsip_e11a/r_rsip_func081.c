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

void r_rsip_func081 (void)
{
    WR1_PROG(REG_0094H, 0x00003424U);

    WR1_PROG(REG_0094H, 0x3420a880U);
    WR1_PROG(REG_0094H, 0x0000000aU);
    WR1_PROG(REG_0094H, 0x10000821U);

    WR1_PROG(REG_0094H, 0x0000b4e0U);
    WR1_PROG(REG_0094H, 0x0000000dU);
    WR1_PROG(REG_0094H, 0x342028e4U);
    WR1_PROG(REG_0094H, 0x10000821U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000016U);
    WR1_PROG(REG_0094H, 0x1000b420U);
    WR1_PROG(REG_0094H, 0x00000016U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x0000001cU);
    WR1_PROG(REG_0094H, 0x1000b420U);
    WR1_PROG(REG_0094H, 0x00000016U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000022U);
    WR1_PROG(REG_0094H, 0x1000b420U);
    WR1_PROG(REG_0094H, 0x00000016U);
}
