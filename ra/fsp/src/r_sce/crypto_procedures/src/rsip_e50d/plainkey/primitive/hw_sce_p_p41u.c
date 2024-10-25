/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CmacUpdateSub (const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_1824H, 0x0e000406U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func216();

    HW_SCE_p_func101(0xbf0d39c2U, 0x11d464a5U, 0xf082dc04U, 0x177822f8U);
}
