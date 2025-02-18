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

void r_rsip_func214 (void)
{
    WR1_PROG(REG_1408H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00000400U);
    WR1_PROG(REG_143CH, 0x00000600U);
    WR1_PROG(REG_143CH, 0x00000500U);
    WR1_PROG(REG_1824H, 0x00000000U);
}
