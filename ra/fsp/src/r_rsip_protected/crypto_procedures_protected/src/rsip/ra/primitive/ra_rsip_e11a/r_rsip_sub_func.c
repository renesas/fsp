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

void r_rsip_func_sub001 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_00B4H, arg1);
    WR1_PROG(REG_00B8H, arg2);
    WR1_PROG(REG_00A4H, arg3);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub002 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, arg1);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(arg2));
    WR1_PROG(REG_0024H, 0x00000000U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub003 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_009CH, arg1);
    WR1_PROG(REG_0000H, arg2);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub004 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_00B0H, arg1);
    WR1_PROG(REG_0000H, arg2);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub005 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0014H, arg1);
    WR1_PROG(REG_00D0H, arg2);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(arg3));
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub006 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_00D0H, arg1);
    WR1_PROG(REG_0000H, arg2);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub007 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_0094H, arg2);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, arg3);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub008 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0014H, arg1);
    WR1_PROG(REG_00D4H, arg2);
    WR1_PROG(REG_00D0H, arg3);
    WAIT_STS(REG_0014H, 31, 1);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub009 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_0000H, arg1);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0094H, arg2);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub010 (uint32_t arg1)
{
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);
    WR1_PROG(REG_0040H, 0x00402000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub011 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0070H, arg1);
    WR1_PROG(REG_004CH, 0x00000000U);
    WR1_PROG(REG_0014H, arg2);
    WR1_PROG(REG_009CH, arg3);
    WAIT_STS(REG_0014H, 31, 1);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub012 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_0024H, 0x00000000U);
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, arg2);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub013 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, arg2);
    WAIT_STS(REG_0014H, 31, 1);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub014 (uint32_t arg1, uint32_t arg2)
{
    WR1_PROG(REG_0070H, arg1);
    WR1_PROG(REG_004CH, 0x00000000U);
    WR1_PROG(REG_0094H, 0x0000b4a0U);
    WR1_PROG(REG_0094H, arg2);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub015 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_009CH, arg2);
    WR1_PROG(REG_0008H, arg3);
    WAIT_STS(REG_0008H, 30, 1);
}

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func_sub016 (uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    WR1_PROG(REG_0094H, arg1);
    WR1_PROG(REG_0094H, arg2);
    WR1_PROG(REG_0094H, arg3);
}
