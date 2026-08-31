/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func028_r2 (uint32_t ARG1)
{
    HW_SCE_p_func_sub022(0x38000f5aU, 0x00030020U, 0x0000b7c0U, 0x01166403U);
    HW_SCE_p_func_sub022(0x00000060U, 0x0000b7c0U, 0x013659ffU, 0x00000080U);

    WR1_PROG(REG_C4H, 0x00443a0cU);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, change_endian_long(0x00000000U));
    WR1_PROG(REG_C4H, 0x000c3e1cU);
    WR1_PROG(REG_E0H, 0x810103c0U);
    WR1_PROG(REG_00H, 0x00002807U);
    HW_SCE_p_func_sub003(0x00001762U, 0x00000500U, 0x02f087bfU);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 0]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 4]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 8]);
    HW_SCE_p_func_sub011(0x00003233U, 0x0000001aU);

    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 12]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 16]);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 20]);
    HW_SCE_p_func_sub011(0x00003233U, 0x0000001bU);

    WR1_PROG(REG_C4H, 0x000007bdU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_FLASH2[ARG1 + 24]);

    HW_SCE_p_func_sub013(0x00800c45U, 0x00002213U);
}
