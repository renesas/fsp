/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128XtsDecryptUpdateSub (uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pb6u_func100_001[] =
    {
        0x1f5b9b2aU, 0xdc4bb111U, 0xcc7658c6U, 0xe2a8e6e4U,
    };
    HW_SCE_p_func100(Param_pb6u_func100_001);

    WR1_PROG(REG_104H, 0x000000b1U);
    WR1_PROG(REG_B0H, 0x00000020U);
    WR1_PROG(REG_A4H, 0x0000cda6U);
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
    RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);

    HW_SCE_p_func206();

    static const uint32_t Param_pb6u_func101_001[] =
    {
        0x0bad6ff4U, 0x21a29b22U, 0xb39b0111U, 0x27bbba8cU,
    };
    HW_SCE_p_func101(Param_pb6u_func101_001);
}
