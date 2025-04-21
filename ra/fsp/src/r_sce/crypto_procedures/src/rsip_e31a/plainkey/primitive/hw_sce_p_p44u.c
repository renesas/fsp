/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256CmacUpdateSub (const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D4H, 0x40000000U);
    WR1_PROG(REG_D0H, 0x0e008406U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205();

    HW_SCE_p_func101(0xae9a8d1fU, 0x5528d41dU, 0x1bb0e725U, 0x38317f76U);
}
