/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes256GcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p34u_func100_001[] =
    {
        0x2cfe9806U, 0x8ec8e205U, 0xb24ff983U, 0xf57022edU,
    };
    HW_SCE_p_func100(Param_p34u_func100_001);

    HW_SCE_p_func_sub016(0x00020061U, 0x40000020U, 0x20008d06U);
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
    RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);

    HW_SCE_p_func206();

    static const uint32_t Param_p34u_func101_001[] =
    {
        0xca37f5ddU, 0x4a6ce486U, 0x7429753bU, 0x893c64d4U,
    };
    HW_SCE_p_func101(Param_p34u_func101_001);
}
