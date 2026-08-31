/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes256CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pa4u_func100_001[] =
    {
        0xcebd2d47U, 0xb4bd786eU, 0xc3cd21a7U, 0x108c1a48U,
    };
    HW_SCE_p_func100(Param_pa4u_func100_001);
    HW_SCE_p_func_sub018(0x40000000U, 0xf7008d06U);
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

    static const uint32_t Param_pa4u_func101_001[] =
    {
        0xab0c3dceU, 0x542670acU, 0x9d347a6dU, 0x361eaf8dU,
    };
    HW_SCE_p_func101(Param_pa4u_func101_001);
}
