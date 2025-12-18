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

void r_rsip_func028 (const uint32_t ARG1[])
{
    r_rsip_func_sub022(0x38000c00U, 0x00030020U, 0x0000b420U);
    r_rsip_func_sub022(0x01732b87U, 0x00000060U, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x0136eacdU);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_00D0H, 0x300710c4U);
    r_rsip_func_sub012(0x81010020U, 0x00490005U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00009423U);
    r_rsip_func_sub011(0x000017c1U, 0x00000500U, 0xf7049d07U);
    WR4_ADDR(REG_002CH, &ARG1[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[4]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[8]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000942aU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[12]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[16]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[20]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    r_rsip_func_sub019(0x000003c1U, 0x07040d05U);
    WR4_ADDR(REG_002CH, &ARG1[24]);

    r_rsip_func_sub013(0x8c100005U, 0x00410011U);
}
