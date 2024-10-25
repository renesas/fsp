/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha256HmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_MAC[],
                                     const uint32_t InData_MACLength[],
                                     uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WAIT_STS(REG_2030H, 4, 1);

    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1600H, 0x1000b780U);
    WR1_PROG(REG_1600H, 0x00002000U);
    WR1_PROG(REG_1600H, 0x2000b780U);
    WR1_PROG(REG_1600H, 0x00001000U);

    WR1_PROG(REG_1600H, 0x38000f9bU);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0x407397d5U, 0x5d29ab6aU, 0x0b0273e0U, 0x1e09991dU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x9bee7614U, 0x61e89e4aU, 0xbdbbfed8U, 0x8d9a4020U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x30f21789U, 0xcea3f161U, 0x6a4222f4U, 0x76742727U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func100(0xe93eff7dU, 0xf2107aa1U, 0x93c84bc9U, 0xf7aa32c5U);
            WR1_PROG(REG_1408H, 0x00004022U);
            for (iLoop = 0U; iLoop < 8U; iLoop++)
            {
                WAIT_STS(REG_1408H, 30, 1);
                RD1_ADDR(REG_1420H, &OutData_MAC[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func102(0xc6478cf9U, 0xf188132aU, 0xb513e95dU, 0xae761889U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010020U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_MACLength[0]);
            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1600H, 0x3420a820U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            WR1_PROG(REG_1600H, 0x3420a820U);
            WR1_PROG(REG_1600H, 0x00000021U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);

            HW_SCE_p_func100(0xb17c651fU, 0x27a93aa4U, 0x8ee95100U, 0xd50a1038U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0xb141c4fcU, 0x5a12c64bU, 0x9369d2e1U, 0xd7ec6592U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_1600H, 0x00000bffU);
                WR1_PROG(REG_1608H, 0x8088001fU);
                WR1_PROG(REG_1400H, 0x03450021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1600H, 0x00000800U);
                for (iLoop = 0U; iLoop < 32U; iLoop++)
                {
                    WR1_PROG(REG_1600H, 0x3c002be1U);
                    WR1_PROG(REG_1600H, 0x12003c1fU);
                    WR1_PROG(REG_1600H, 0x00002fe0U);
                }

                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1824H, 0x08000045U);
                WR1_PROG(REG_1600H, 0x00000bffU);
                WR1_PROG(REG_1608H, 0x8188001fU);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1824H, 0x08000055U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000007c1U);
                WR1_PROG(REG_1824H, 0x9c000005U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_MAC[0]);

                WR1_PROG(REG_1824H, 0x9c100005U);
                WAIT_STS(REG_1444H, 31, 1);
                WR4_ADDR(REG_1420H, &InData_MAC[4]);

                HW_SCE_p_func100(0xb8ee34ccU, 0x09bbfd48U, 0x7476f64dU, 0x9c367c20U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0x57175126U, 0xfd5324c9U, 0x9fdb84cdU, 0xfcebd5c5U);
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func102(0x3dda05f2U, 0x13593a36U, 0xd2c915eaU, 0x5ff0576aU);
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
