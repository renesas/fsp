/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestUpdateSub (const uint32_t InData_Msg[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WAIT_STS(REG_118H, 0, 1);

    WR1_PROG(REG_14H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR16_ADDR(REG_2CH, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_14H, 0x00000000U);
    WAIT_STS(REG_118H, 8, 0);
    WR1_PROG(REG_40H, 0x00001600U);

    HW_SCE_p_func101(0xddf37327U, 0xdf618691U, 0x69aa585aU, 0xbb042445U);

    return FSP_SUCCESS;
}
