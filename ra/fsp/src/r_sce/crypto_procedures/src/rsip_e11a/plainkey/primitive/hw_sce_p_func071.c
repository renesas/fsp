/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func071_r1 (const uint32_t ARG1[])
{
    HW_SCE_p_func_sub001(0x30003000U, 0x00050020U, 0x0000b420U);
    HW_SCE_p_func_sub001(0x01942287U, 0x00030040U, 0x0000b420U);
    HW_SCE_p_func_sub001(0x01881fe1U, 0x00070040U, 0x0000b420U);
    WR1_PROG(REG_94H, 0x01b03468U);
    WR1_PROG(REG_94H, 0x00000080U);

    WR1_PROG(REG_D0H, 0x300710c4U);
    WR1_PROG(REG_9CH, 0x81010020U);
    HW_SCE_p_func_sub002(0x00490005U);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00001419U);
    HW_SCE_p_func_sub007(0x00000fc1U, 0x00000300U, 0xf7049d07U);
    WR4_ADDR(REG_2CH, &ARG1[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[4]);
    HW_SCE_p_func_sub002(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000141eU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[8]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[12]);
    HW_SCE_p_func_sub002(0x00c10021U);

    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[16]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub002(0x00410011U);
}
