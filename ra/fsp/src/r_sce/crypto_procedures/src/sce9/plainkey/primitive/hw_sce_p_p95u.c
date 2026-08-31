/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p95u_func100_001[] =
    {
        0x79ec7ce6U, 0x192c8e50U, 0xa482edbcU, 0x84fdaa03U,
    };
    HW_SCE_p_func100(Param_p95u_func100_001);
    WR1_PROG(REG_104H, 0x000000b1U);

    WR1_PROG(REG_A4H, 0x00e007b6U);
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

    static const uint32_t Param_p95u_func101_001[] =
    {
        0xd7e08a8bU, 0xc155debfU, 0x3ced38f0U, 0x606d0df4U,
    };
    HW_SCE_p_func101(Param_p95u_func101_001);
}
