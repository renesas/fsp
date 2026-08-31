/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CmacUpdateSub (uint32_t InData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_104H, 0x000000b1U);
    WR1_PROG(REG_A4H, 0x00000e16U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205();

    static const uint32_t Param_p41u_func101_001[] =
    {
        0x3076c9f4U, 0x318697edU, 0x87ee80b1U, 0x3ac079e1U,
    };
    HW_SCE_p_func101(Param_p41u_func101_001);
}
