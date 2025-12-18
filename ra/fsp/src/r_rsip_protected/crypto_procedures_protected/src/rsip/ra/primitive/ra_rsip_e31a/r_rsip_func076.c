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

void r_rsip_func076 (void)
{
    r_rsip_func_sub022(0x38000c21U, 0x00030020U, 0x0000b4c0U);
    r_rsip_func_sub022(0x00000019U, 0x00000060U, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x0000001fU);
    WR1_PROG(REG_0094H, 0x00000080U);
}
