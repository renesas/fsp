/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestFinalSub (const uint32_t InData_Msg[],
                                                   uint32_t       OutData_MsgDigest[],
                                                   const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WAIT_STS(REG_2030H, 0, 1);

    WR1_PROG(REG_1444H, 0x00020064U);

    for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WAIT_STS(REG_1444H, 31, 1);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
    {
        WR1_PROG(REG_1420H, InData_Msg[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2030H, 8, 0);
    WR1_PROG(REG_143CH, 0x00001600U);

    WAIT_STS(REG_2030H, 4, 1);

    HW_SCE_p_func100(0xc913dd50U, 0x18ae93dcU, 0x5ae24dfeU, 0xd50a08adU);
    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000001U);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1600H, 0x1000b400U);
    WR1_PROG(REG_1600H, 0x00000002U);

    WR1_PROG(REG_1600H, 0x00007c00U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func100(0x1bdc5896U, 0xb6fb69e7U, 0x01adc6adU, 0xa9942a71U);
        WR1_PROG(REG_1408H, 0x00004016U);
        WAIT_STS(REG_1408H, 30, 1);
        RD5_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0xe770e9a9U, 0x8c25c9e2U, 0x70b0c4ebU, 0x2b7dfdddU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func100(0x418b6555U, 0xdabc1a98U, 0xd9df88a3U, 0xc794e7ebU);
        WR1_PROG(REG_1408H, 0x0000401eU);
        WAIT_STS(REG_1408H, 30, 1);
        RD7_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x8bed1022U, 0x069fbd16U, 0x99b14016U, 0x3f485f1cU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func100(0x935eb043U, 0xdf9a5138U, 0xc63d19d7U, 0x1bc575d5U);
        WR1_PROG(REG_1408H, 0x00004022U);
        WAIT_STS(REG_1408H, 30, 1);
        RD8_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x19b494ecU, 0xae98ef3dU, 0x7a3c1165U, 0x9310c9feU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000005U)
    {
        HW_SCE_p_func100(0x2cd55c86U, 0x60d7df05U, 0xbfde3579U, 0x1ac07245U);
        WR1_PROG(REG_1408H, 0x00004032U);
        WAIT_STS(REG_1408H, 30, 1);
        RD12_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x0b29913bU, 0xf6a4dde2U, 0xf6d14a5bU, 0x2c3541e1U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000006U)
    {
        HW_SCE_p_func100(0x6d4889acU, 0xb44854cdU, 0x8dddba00U, 0xaa5d2291U);
        WR1_PROG(REG_1408H, 0x00004042U);
        WAIT_STS(REG_1408H, 30, 1);
        RD16_ADDR(REG_1420H, &OutData_MsgDigest[0]);

        HW_SCE_p_func102(0x11ffc560U, 0x8e4af3faU, 0x53189e1fU, 0x44fa6e24U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);
    }

    return FSP_SUCCESS;
}
