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

void r_rsip_func406 (const uint32_t ARG1[])
{
    r_rsip_func_sub008(0x000000a1U, 0x300710c4U, 0x0109cee8U);

    WR1_PROG(REG_00B0H, 0x00001405U);
    r_rsip_func_sub011(0x000033c1U, 0x00000c00U, 0xf7049d07U);
    WR4_ADDR(REG_002CH, &ARG1[20]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[24]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000140aU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[28]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[32]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000141eU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[36]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[40]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00000440U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[44]);
    r_rsip_func_sub015(0x00c10009U, 0x00001800U);

    r_rsip_func_sub009(0x00000441U, 0x00c10009U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001419U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[48]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[52]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x0000140fU);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[56]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[60]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001414U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[64]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[68]);
    r_rsip_func_sub015(0x00c10021U, 0x00001800U);

    WR1_PROG(REG_00D0H, 0x07040d05U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[72]);

    r_rsip_func_sub013(0x8c100005U, 0x00410011U);
}
