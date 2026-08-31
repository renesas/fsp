/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func401 (const uint32_t ARG1[])
{
    HW_SCE_p_func_sub004(0x000000a1U, 0x300710c4U, 0x01dfacbaU);

    WR1_PROG(REG_A0H, 0x20010000U);
    WR1_PROG(REG_B0H, 0x00001446U);
    HW_SCE_p_func_sub007(0x00000fc1U, 0x00000300U, 0xf7049d07U);
    WR4_ADDR(REG_2CH, &ARG1[0]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[4]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_B0H, 0x0000144bU);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[8]);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[12]);
    HW_SCE_p_func_sub003(0x00c10021U);

    WR1_PROG(REG_D0H, 0x07040d05U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &ARG1[16]);

    WR1_PROG(REG_D0H, 0x8c100005U);
    HW_SCE_p_func_sub003(0x00410011U);
}
