/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x000003c1U);
    static const uint32_t Param_p50u_func100_001[] =
    {
        0x4264a1feU, 0x69f4bc96U, 0x2afb6540U, 0x0fd78b3aU,
    };
    HW_SCE_p_func100(Param_p50u_func100_001);

    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_9CH, 0x00000008U);
    WR1_PROG(REG_14H, 0x00020061U);
    HW_SCE_p_func_sub019(0x00008006U);
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
        0x80cc2b05U, 0xdac72214U, 0x648846e9U, 0x27bb461cU,
    };
    HW_SCE_p_func101(Param_p50u_func101_001);
}
