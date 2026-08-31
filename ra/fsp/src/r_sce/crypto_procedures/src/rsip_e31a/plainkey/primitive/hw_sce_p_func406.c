/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func406 (const uint32_t ARG1[])
{
    HW_SCE_p_func_sub004(0x000000a1U, 0x300710c4U, 0x0109cee8U);

    WR1_PROG(REG_B0H, 0x00001405U);
    HW_SCE_p_func_sub007(0x000033c1U, 0x00000c00U, 0xf7049d07U);
    WR4_ADDR(REG_2CH, &ARG1[20]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[24]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000140aU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[28]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[32]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000141eU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[36]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[40]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x00000440U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[44]);
    HW_SCE_p_func_sub003(0x00c10009U);

    WR1_PROG(REG_B0H, 0x00000441U);
    HW_SCE_p_func_sub003(0x00c10009U);

    WR1_PROG(REG_B0H, 0x00001419U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[48]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[52]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000140fU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[56]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[60]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x00001414U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[64]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[68]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[72]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub003(0x00410011U);
}
