/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_TextLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1600H, 0x0000000fU);

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0x034e60d1U, 0x8a673a88U, 0x06919f82U, 0x6261d98eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0xe7008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[0]);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1400H, 0x03410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x00000821U);

        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1600H, 0x00000080U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x3c002be0U);
            WR1_PROG(REG_1600H, 0x12003c3fU);
            WR1_PROG(REG_1600H, 0x00002fe0U);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func100(0x4fc201e1U, 0x656c6cffU, 0x6929a601U, 0x46e7d6f6U);
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x81840001U);
        WR1_PROG(REG_1408H, 0x00005012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[0]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[1]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[2]);
        WAIT_STS(REG_1408H, 30, 1);
        RD1_ADDR(REG_1420H, &OutData_Text[3]);

        HW_SCE_p_func101(0x8facfb63U, 0x2329ca85U, 0x4b3744e7U, 0x06473041U);
    }
    else
    {
        HW_SCE_p_func101(0x98ab77f5U, 0xc2897eeeU, 0xeb1abcafU, 0xf79eda28U);
    }

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xbd7164d7U, 0x0dcd0993U, 0x7e5caaf7U, 0x12b9c764U);
    WR1_PROG(REG_182CH, 0x40000010U);
    WR1_PROG(REG_1824H, 0x09108105U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1408H, 0x00001012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_MAC[0]);

    HW_SCE_p_func102(0xb85eae9cU, 0x75671eb4U, 0x212d5fddU, 0x4c60e9f1U);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}
