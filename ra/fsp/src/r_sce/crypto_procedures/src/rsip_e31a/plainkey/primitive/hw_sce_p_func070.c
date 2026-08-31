/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func070 (const uint32_t ARG1[])
{
    HW_SCE_p_func_sub001(0x30003000U, 0x00050020U, 0x0000b420U, 0x0130d7c2U);
    HW_SCE_p_func_sub001(0x00030040U, 0x0000b420U, 0x01a04920U, 0x00070040U);
    HW_SCE_p_func_sub022(0x0000b420U, 0x01f88a8bU, 0x00000080U);

    WR1_PROG(REG_D0H, 0x300710c4U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub003(0x00490005U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00001405U);
    HW_SCE_p_func_sub007(0x00002fc1U, 0x00000b00U, 0xf7049d07U);
    WR4_ADDR(REG_2CH, &ARG1[20]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[24]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x00001437U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[28]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[32]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000145fU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[36]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[40]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x00001464U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[44]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[48]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000140aU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[52]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[56]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000145aU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[60]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[64]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[68]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub003(0x00410011U);
}
