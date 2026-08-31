/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x000003c1U);
    static const uint32_t Param_p50u_func100_001[] =
    {
        0x0e87f7f7U, 0x1a0fc8dcU, 0x3ae769cdU, 0x1b5ac95aU,
    };
    HW_SCE_p_func100(Param_p50u_func100_001);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_9CH, 0x00000008U);
    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D0H, 0x00008006U);
    WR1_PROG(REG_08H, 0x000c1000U);

    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_Text[MAX_CNT - 4]);

    HW_SCE_p_func206();

    static const uint32_t Param_p50u_func101_001[] =
    {
        0x2204296aU, 0x74b7d3eeU, 0xd1090816U, 0xdb33fdfeU,
    };
    HW_SCE_p_func101(Param_p50u_func101_001);
}
