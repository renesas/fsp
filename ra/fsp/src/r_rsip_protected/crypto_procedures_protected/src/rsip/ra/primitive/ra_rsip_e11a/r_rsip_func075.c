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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func075 (void)
{
    r_rsip_func_sub016(0x30003020U, 0x00050020U, 0x0000b4c0U);
    r_rsip_func_sub016(0x00000022U, 0x00030040U, 0x0000b4c0U);
    r_rsip_func_sub016(0x0000001cU, 0x00070040U, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x00000016U);
    WR1_PROG(REG_0094H, 0x00000080U);
}
