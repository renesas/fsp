/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010140U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_MACLength[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38008940U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    WR1_PROG(REG_1600H, 0x0000b7e0U);
    WR1_PROG(REG_1600H, 0x00000010U);
    WR1_PROG(REG_1600H, 0x34202beaU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x639b5ab8U, 0x0851b11dU, 0x5a60d136U, 0xd0871e29U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x3b0dc8a9U, 0xd93bf9c0U, 0x989254bcU, 0xcc7374fbU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
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

        HW_SCE_p_func100(0x25dc60e3U, 0xcc183615U, 0x591b55a2U, 0x69be7771U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000000U);
            WR1_PROG(REG_1824H, 0x07008d05U);
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

            HW_SCE_p_func100(0x829be5a2U, 0x3b4f7064U, 0x10049c66U, 0xc8b234ecU);
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

            WR1_PROG(REG_182CH, 0x40000000U);
            WR1_PROG(REG_1824H, 0x0e108405U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func101(0x68bed659U, 0x533ad24cU, 0xa307bb2fU, 0xb4da8996U);
        }
        else
        {
            HW_SCE_p_func101(0x0c35aab7U, 0x95a33046U, 0x264a0642U, 0xad1938c0U);
        }

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x0c100104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x07208d05U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1400H, 0x03410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1600H, 0x0000a540U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x00000821U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_1600H, 0x3c002beaU);
            WR1_PROG(REG_1600H, 0x12003c3fU);
            WR1_PROG(REG_1600H, 0x00002fe0U);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000055U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_MAC[0]);

        WR1_PROG(REG_1824H, 0x9c100005U);
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1608H, 0x81840001U);
        WR1_PROG(REG_1400H, 0x00490011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1824H, 0x00000000U);

        HW_SCE_p_func100(0x7cc27054U, 0x7a04b9a7U, 0xf4a3d8dbU, 0xc654031cU);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xf6c6067dU, 0xc0442ddaU, 0xde54f441U, 0xd9514aa9U);

            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0x5b2f94e0U, 0x1db1d69aU, 0x7fe2e974U, 0xe9e9eae9U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
