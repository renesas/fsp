/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func100(0xeaf60dacU, 0x8d0906c6U, 0x2d11bb08U, 0xd3c2ab44U);
    WR1_PROG(REG_14H, 0x00020061U);

    WR1_PROG(REG_D0H, 0xe7000d06U);
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

    HW_SCE_p_func101(0xd26ef09cU, 0x29b30c02U, 0xa6803263U, 0xd0ce94ccU);
}
