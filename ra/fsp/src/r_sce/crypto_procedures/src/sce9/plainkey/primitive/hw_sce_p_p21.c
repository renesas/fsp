/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Ghash (uint32_t InData_HV[],
                        uint32_t InData_IV[],
                        uint32_t InData_Text[],
                        uint32_t OutData_DataT[],
                        uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002101U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_7CH, 0x00000001U);
    WR1_PROG(REG_7CH, 0x00000041U);

    WR1_PROG(REG_74H, 0x00001000U);
    WR1_PROG(REG_104H, 0x00000364U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_HV[0]);

    WR1_PROG(REG_74H, 0x00000004U);
    WR1_PROG(REG_104H, 0x00000364U);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_IV[0]);

    WR1_PROG(REG_74H, 0x00000002U);
    WR1_PROG(REG_104H, 0x000000b4U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_74H, 18, 0);
    WR1_PROG(REG_104H, 0x00000000U);

    static const uint32_t Param_p21_func100_001[] =
    {
        0xa49f2fb4U, 0xcf741bfeU, 0x976976aeU, 0xda8be0abU,
    };
    HW_SCE_p_func100(Param_p21_func100_001);
    WR1_PROG(REG_74H, 0x00000008U);
    WR1_PROG(REG_04H, 0x00000513U);
    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_DataT[0]);

    static const uint32_t Param_p21_func102_001[] =
    {
        0xe069ddfdU, 0x5f466981U, 0x494caa8aU, 0xc542b9fdU,
    };
    HW_SCE_p_func102(Param_p21_func102_001);
    WR1_PROG(REG_1BCH, 0x00000040U);
    WAIT_STS(REG_18H, 12, 0);

    return FSP_SUCCESS;
}
