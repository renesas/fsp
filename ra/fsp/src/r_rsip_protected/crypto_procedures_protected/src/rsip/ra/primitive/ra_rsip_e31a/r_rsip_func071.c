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

void r_rsip_func071 (const uint32_t ARG1[])
{
    WR1_PROG(REG_0094H, 0x30003000U);
    WR1_PROG(REG_0094H, 0x00050020U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x017f9e4eU);
    WR1_PROG(REG_0094H, 0x00030040U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x01b24fdbU);
    WR1_PROG(REG_0094H, 0x00070040U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x01b2b66bU);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_00D0H, 0x300710c4U);
    WR1_PROG(REG_009CH, 0x81010020U);
    WR1_PROG(REG_0000H, 0x00490005U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B0H, 0x00001419U);
    WR1_PROG(REG_0014H, 0x00000fc1U);
    WR1_PROG(REG_00D4H, 0x00000300U);
    WR1_PROG(REG_00D0H, 0xf7049d07U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[4]);
    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000141eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[8]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[12]);
    WR1_PROG(REG_0000H, 0x00c10021U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00D0H, 0x07040d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[16]);

    WR1_PROG(REG_00D0H, 0x8c100005U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
}
