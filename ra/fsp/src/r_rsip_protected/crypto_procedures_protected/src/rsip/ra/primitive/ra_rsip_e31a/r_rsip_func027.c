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

void r_rsip_func027 (const uint32_t ARG1[])
{
    r_rsip_func_sub022(0x38000c00U, 0x00030020U, 0x0000b420U);
    r_rsip_func_sub022(0x01d44437U, 0x00000060U, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x0170d303U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_00D0H, 0x300710c4U);
    r_rsip_func_sub012(0x81010020U, 0x00490005U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00009407U);
    r_rsip_func_sub011(0x000047c1U, 0x00001100U, 0xf7049d07U);
    WR4_ADDR(REG_002CH, &ARG1[28]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[32]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[36]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000944dU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[40]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[44]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[48]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00009485U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[52]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[56]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[60]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000948cU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[64]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[68]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[72]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000940eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[76]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[80]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[84]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000947eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[88]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[92]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[96]);
    r_rsip_func_sub015(0x00c10031U, 0x00001800U);

    r_rsip_func_sub019(0x000003c1U, 0x07040d05U);
    WR4_ADDR(REG_002CH, &ARG1[100]);

    r_rsip_func_sub013(0x8c100005U, 0x00410011U);
}
