/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func028 (const uint32_t ARG1[])
{
    HW_SCE_p_func_sub001(0x38000c00U, 0x00030020U, 0x0000b420U, 0x01732b87U);
    HW_SCE_p_func_sub001(0x00000060U, 0x0000b420U, 0x0136eacdU, 0x00000080U);

    WR1_PROG(REG_D0H, 0x300710c4U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub003(0x00490005U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00009423U);
    HW_SCE_p_func_sub007(0x000017c1U, 0x00000500U, 0xf7049d07U);
    WR4_ADDR(REG_2CH, &ARG1[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[4]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[8]);
    HW_SCE_p_func_sub003(0x00c10031U);

    WR1_PROG(REG_B0H, 0x0000942aU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[12]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[16]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[20]);
    HW_SCE_p_func_sub003(0x00c10031U);

    HW_SCE_p_func_sub011(0x000003c1U, 0x07040d05U);
    WR4_ADDR(REG_2CH, &ARG1[24]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub003(0x00410011U);
}
