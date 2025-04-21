/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha3GenerateMessageDigestSuspendSub (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    for (iLoop = 0U; iLoop < 50; iLoop++)
    {
        RD1_ADDR(REG_243CH, &OutData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    RD1_ADDR(REG_2414H, &OutData_State[50]);
    RD1_ADDR(REG_2410H, &OutData_State[51]);

    HW_SCE_p_func102(0x5a13cc3cU, 0x67a4fc17U, 0xaec96092U, 0x23e47cf7U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
