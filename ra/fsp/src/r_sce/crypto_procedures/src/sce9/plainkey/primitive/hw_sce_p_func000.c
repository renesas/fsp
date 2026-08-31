/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_p_func000 (uint32_t InData_PaddedMsg[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_104H, 0x000000b4U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR16_ADDR(REG_100H, &InData_PaddedMsg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_74H, 18, 0);
    WR1_PROG(REG_104H, 0x00000000U);
    WR1_PROG(REG_1CH, 0x00001600U);
}
