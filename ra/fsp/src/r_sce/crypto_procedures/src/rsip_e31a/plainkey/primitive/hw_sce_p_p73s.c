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
        RD1_ADDR(REG_114H, &OutData_State[iLoop]);
    }

    RD1_ADDR(REG_104H, &OutData_State[18]);
    RD1_ADDR(REG_100H, &OutData_State[19]);

    HW_SCE_p_func102(0x5dc04975U, 0x0d0e02f8U, 0x90d996fbU, 0x5fd1d453U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
