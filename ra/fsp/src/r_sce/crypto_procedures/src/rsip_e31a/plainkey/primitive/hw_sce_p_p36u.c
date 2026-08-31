/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_Aes256GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_p36u_func100_001[] =
    {
        0xd2f69887U, 0xd2f0647fU, 0xbf271001U, 0x421927c5U,
    };
    HW_SCE_p_func100(Param_p36u_func100_001);

    HW_SCE_p_func_sub016(0x00020061U, 0x40008020U, 0x20008d06U);
    WR1_PROG(REG_08H, 0x000c1000U);

    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);

    HW_SCE_p_func206();

    static const uint32_t Param_p36u_func101_001[] =
    {
        0x14a7cb10U, 0x2e05da47U, 0xddb9b3b2U, 0x210f2df5U,
    };
    HW_SCE_p_func101(Param_p36u_func101_001);
}
