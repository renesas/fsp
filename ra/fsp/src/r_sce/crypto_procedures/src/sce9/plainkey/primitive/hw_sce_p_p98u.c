/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p98u_func100_001[] =
    {
        0x637820ffU, 0xe3c3138eU, 0x44d0311dU, 0x74408fdfU,
    };
    HW_SCE_p_func100(Param_p98u_func100_001);
    WR1_PROG(REG_104H, 0x000000b1U);

    WR1_PROG(REG_A4H, 0x00f007b6U);
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

    static const uint32_t Param_p98u_func101_001[] =
    {
        0xdcd6eefdU, 0xdac4a136U, 0xe93fb895U, 0x6de334e9U,
    };
    HW_SCE_p_func101(Param_p98u_func101_001);
}
