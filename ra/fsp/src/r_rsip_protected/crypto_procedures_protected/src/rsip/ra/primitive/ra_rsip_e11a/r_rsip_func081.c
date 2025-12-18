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

void r_rsip_func081 (void)
{
    r_rsip_func_sub016(0x00003424U, 0x3420a880U, 0x0000000aU);
    r_rsip_func_sub016(0x10000821U, 0x0000b4e0U, 0x0000000dU);
    r_rsip_func_sub016(0x342028e4U, 0x10000821U, 0x38008880U);
    r_rsip_func_sub016(0x00000016U, 0x1000b420U, 0x00000016U);

    r_rsip_func_sub016(0x38008880U, 0x0000001cU, 0x1000b420U);
    r_rsip_func_sub016(0x00000016U, 0x38008880U, 0x00000022U);
    WR1_PROG(REG_0094H, 0x1000b420U);
    WR1_PROG(REG_0094H, 0x00000016U);
}
