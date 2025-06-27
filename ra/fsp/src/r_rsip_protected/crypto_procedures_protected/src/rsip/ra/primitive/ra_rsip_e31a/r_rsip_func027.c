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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_func027 (const uint32_t ARG1[])
{
    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_0094H, 0x00030020U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x01d44437U);
    WR1_PROG(REG_0094H, 0x00000060U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x0170d303U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_00D0H, 0x300710c4U);
    WR1_PROG(REG_009CH, 0x81010020U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00009407U);
    WR1_PROG(REG_0014H, 0x000047c1U);
    WR1_PROG(REG_00D4H, 0x00001100U);
    WR1_PROG(REG_00D0H, 0xf7049d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[28]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[32]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[36]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000944dU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[40]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[44]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[48]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00009485U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[52]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[56]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[60]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000948cU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[64]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[68]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[72]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000940eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[76]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[80]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[84]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000947eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[88]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[92]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[96]);
    WR1_PROG(REG_0000H, 0x00c10031U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x07040d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[100]);

    WR1_PROG(REG_00D0H, 0x8c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}
