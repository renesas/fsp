/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p36u_func100_001[] =
    {
        0x001e4f2bU, 0x3c22c7baU, 0x4a63c948U, 0x18076020U,
    };
    HW_SCE_p_func100(Param_p36u_func100_001);

    WR1_PROG(REG_00H, 0x80007100U);
    WR1_PROG(REG_104H, 0x000000b1U);
    WR1_PROG(REG_A4H, 0x00000886U);
    WR1_PROG(REG_D0H, 0x40000020U);
    WR1_PROG(REG_C4H, 0x000087b6U);
    WR1_PROG(REG_04H, 0x0000c200U);

    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_Text[iLoop]);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);

    WAIT_STS(REG_74H, 18, 0);

    HW_SCE_p_func200();

    static const uint32_t Param_p36u_func101_001[] =
    {
        0x07698af7U, 0xd862af5aU, 0x4e5cb293U, 0x1d825a3fU,
    };
    HW_SCE_p_func101(Param_p36u_func101_001);
}
