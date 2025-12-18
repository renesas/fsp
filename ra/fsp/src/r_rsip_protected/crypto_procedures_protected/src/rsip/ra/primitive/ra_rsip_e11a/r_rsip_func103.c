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

void r_rsip_func103 (void)
{
    r_rsip_func_sub005(0x000002a1U, 0x07330c04U, 0x00000000U);

    WR1_PROG(REG_00D0H, 0x07330d04U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_00D0H, 0x07330d04U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    r_rsip_func_sub006(0x08000065U, 0x00410011U);

    r_rsip_func_sub005(0x000000a1U, 0x06330074U, 0x00000000U);

    r_rsip_func_sub006(0x080000b5U, 0x00410011U);
}
