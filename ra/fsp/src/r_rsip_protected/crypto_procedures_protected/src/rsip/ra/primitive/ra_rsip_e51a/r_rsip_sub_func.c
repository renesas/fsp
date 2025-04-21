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

void r_rsip_func_sub001 (uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
    WR1_PROG(REG_1014H, arg1);
    WR1_PROG(REG_1018H, arg2);
    WR1_PROG(REG_1020H, arg3);

    WR1_PROG(REG_1004H, arg4);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);
}

void r_rsip_func_sub002 (uint32_t arg1)
{
    WR1_PROG(REG_1400H, arg1);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);
}

void r_rsip_func_sub003 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_101CH, arg1);
    WR1_PROG(REG_1020H, arg2);

    WR1_PROG(REG_1004H, arg3);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0, 0);
}
