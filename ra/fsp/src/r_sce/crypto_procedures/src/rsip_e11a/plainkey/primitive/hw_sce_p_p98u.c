/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes128CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p98u_func100_001[] =
    {
        0x911ded28U, 0x94d776fbU, 0xa2badc99U, 0xfef50ce3U,
    };
    HW_SCE_p_func100(Param_p98u_func100_001);
    WR1_PROG(REG_14H, 0x00020061U);

    HW_SCE_p_func_sub019(0xf7000d06U);
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

    static const uint32_t Param_p98u_func101_001[] =
    {
        0xb94c228cU, 0x60f1783bU, 0xd0639acdU, 0x74158509U,
    };
    HW_SCE_p_func101(Param_p98u_func101_001);
}
