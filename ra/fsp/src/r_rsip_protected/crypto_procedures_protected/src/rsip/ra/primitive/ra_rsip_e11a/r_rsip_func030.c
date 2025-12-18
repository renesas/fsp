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

void r_rsip_func030 (void)
{
    r_rsip_func_sub016(0x38008800U, 0x00000000U, 0x1000b4a0U);
    r_rsip_func_sub016(0x00000002U, 0x1000b4c0U, 0x00000005U);
    r_rsip_func_sub016(0x1000b4e0U, 0x00000009U, 0x38008800U);
    r_rsip_func_sub016(0x00000002U, 0x1000b4a0U, 0x00000004U);
    r_rsip_func_sub016(0x1000b4c0U, 0x00000007U, 0x1000b4e0U);
    WR1_PROG(REG_0094H, 0x0000000dU);
}
