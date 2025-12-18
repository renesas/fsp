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

void r_rsip_func071 (const uint32_t ARG1[])
{
    r_rsip_func_sub022(0x30003000U, 0x00050020U, 0x0000b420U);
    r_rsip_func_sub022(0x017f9e4eU, 0x00030040U, 0x0000b420U);
    r_rsip_func_sub022(0x01b24fdbU, 0x00070040U, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x01b2b66bU);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_00D0H, 0x300710c4U);
    r_rsip_func_sub012(0x81010020U, 0x00490005U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00001419U);
    r_rsip_func_sub011(0x00000fc1U, 0x00000300U, 0xf7049d07U);
    WR4_ADDR(REG_002CH, &ARG1[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[4]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000141eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[8]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[12]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00D0H, 0x07040d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[16]);

    r_rsip_func_sub013(0x8c100005U, 0x00410011U);
}
