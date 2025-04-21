/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha2HmacSuspendSub (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    for (iLoop = 0U; iLoop < 18U; iLoop++)
    {
        RD1_ADDR(REG_114H, &OutData_State[iLoop]);
    }

    RD1_ADDR(REG_104H, &OutData_State[18]);
    RD1_ADDR(REG_100H, &OutData_State[19]);

    HW_SCE_p_func102(0xae346b86U, 0x9036ef5dU, 0xc912e10cU, 0x01a3db46U);
    WR1_PROG(REG_6CH, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
