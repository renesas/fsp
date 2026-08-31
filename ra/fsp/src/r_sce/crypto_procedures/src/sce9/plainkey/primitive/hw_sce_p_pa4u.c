/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pa4u_func100_001[] =
    {
        0xdea86ac4U, 0x80614a90U, 0x583fc2b0U, 0xf48ed5ebU,
    };
    HW_SCE_p_func100(Param_pa4u_func100_001);
    WR1_PROG(REG_104H, 0x000000b1U);

    WR1_PROG(REG_B0H, 0x40000000U);
    WR1_PROG(REG_A4H, 0x00f087b6U);
    WR1_PROG(REG_04H, 0x0000c100U);

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
    RD4_ADDR(REG_100H, &OutData_Text[MAX_CNT - 4]);

    HW_SCE_p_func207();

    static const uint32_t Param_pa4u_func101_001[] =
    {
        0x6fb47568U, 0x0401ee23U, 0x9c86f289U, 0x92194a0cU,
    };
    HW_SCE_p_func101(Param_pa4u_func101_001);
}
