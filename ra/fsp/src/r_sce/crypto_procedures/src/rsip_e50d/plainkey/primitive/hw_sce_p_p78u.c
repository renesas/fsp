/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha3GenerateMessageDigestUpdateSub (const uint32_t InData_Msg[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WAIT_STS(REG_2440H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020065U);

    for (iLoop = 0U; iLoop < (MAX_CNT - MAX_CNT % S_RAM[0]); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        for (jLoop = 0U; jLoop < S_RAM[0]; )
        {
            WR2_ADDR(REG_1420H, &InData_Msg[iLoop + jLoop]);
            jLoop = jLoop + 2;
        }
        iLoop = iLoop + S_RAM[0];
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2440H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001400U);

    HW_SCE_p_func101(0xa8356a79U, 0x87242ff4U, 0x0d2e634dU, 0x90300180U);

    return FSP_SUCCESS;
}
