/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128CmacUpdateSub (const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D0H, 0x0e000406U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205_r1();

    HW_SCE_p_func101(0x497119e6U, 0xceedc857U, 0x390af361U, 0x19975608U);
}
