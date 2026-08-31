/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes192GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_104H, 0x000000b4U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_DataA[iLoop]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_104H, 0x00000000U);

    static const uint32_t Param_p83a_func101_001[] =
    {
        0x8165a682U, 0x057c2c61U, 0x22687c65U, 0xf6c82157U,
    };
    HW_SCE_p_func101(Param_p83a_func101_001);
}
