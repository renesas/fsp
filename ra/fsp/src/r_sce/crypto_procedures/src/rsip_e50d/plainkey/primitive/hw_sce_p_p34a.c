/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00018000U);
    WR1_PROG(REG_1824H, 0x0a008006U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_DataA[iLoop]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func216();

    HW_SCE_p_func101(0x02c26207U, 0x7801771fU, 0x75e344b0U, 0xb623733bU);
}
