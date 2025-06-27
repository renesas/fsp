/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestSuspendSub (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    for (iLoop = 0U; iLoop < 18U; iLoop++)
    {
        RD1_ADDR(REG_202CH, &OutData_State[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    RD1_ADDR(REG_2014H, &OutData_State[18]);
    RD1_ADDR(REG_2010H, &OutData_State[19]);

    HW_SCE_p_func102(0xe8b3b58fU, 0x6f8ec7f5U, 0x55563abaU, 0x50979ba8U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
