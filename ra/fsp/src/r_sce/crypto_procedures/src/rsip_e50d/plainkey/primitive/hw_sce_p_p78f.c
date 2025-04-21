/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha3GenerateMessageDigestFinalSub (const uint32_t InData_Msg[],
                                                    uint32_t       OutData_MsgDigest[],
                                                    const uint32_t MAX_CNT)
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
    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT - MAX_CNT % S_RAM[0]); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2440H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001400U);

    WAIT_STS(REG_2440H, 4, 1);

    HW_SCE_p_func100(0xcfbb6d4bU, 0x5b63543dU, 0x1f7e5c8bU, 0xe608ef2dU);
    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func100(0xbc5aed3bU, 0xe8036a6fU, 0x46b71433U, 0x568a20dcU);
        WR1_PROG(REG_1408H, 0x0000601eU);
        WAIT_STS(REG_1408H, 30, 1);
        RD7_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xe38bca2dU, 0xc9e10f1aU, 0x8798a045U, 0x6d5fa3fdU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func100(0x843a890eU, 0xaab2e85aU, 0x90efdd5dU, 0x40298be7U);
        WR1_PROG(REG_1408H, 0x00006022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD8_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xa33248d3U, 0x4527dc89U, 0x40eaa70cU, 0x18ca7982U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func100(0x89b11123U, 0xe258a1f4U, 0x0821cf28U, 0xf70abc87U);
        WR1_PROG(REG_1408H, 0x00006032U);
        WAIT_STS(REG_1408H, 30, 1);
        RD12_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x108ef542U, 0x67a99dfeU, 0x5943fd8cU, 0x45d195ceU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func100(0xb0f83b1fU, 0x09678909U, 0xb6f40856U, 0x28a87afcU);
        WR1_PROG(REG_1408H, 0x00006042U);
        WAIT_STS(REG_1408H, 30, 1);
        RD16_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xe153c7a1U, 0x0484f180U, 0xb21a8ab4U, 0x00c435c6U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }

    return FSP_SUCCESS;
}
