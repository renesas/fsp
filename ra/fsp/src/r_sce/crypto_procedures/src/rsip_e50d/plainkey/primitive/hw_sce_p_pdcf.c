/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha224HmacFinalSub (const uint32_t InData_Cmd[],
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
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);

    HW_SCE_p_func100(0xab85de68U, 0xaf014be3U, 0xc32647eaU, 0x21141bdeU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func100(0xfaa90b04U, 0xdb05fc45U, 0xf116e179U, 0x4c563193U);
        WR1_PROG(REG_1408H, 0x0000401eU);
        for (iLoop = 0U; iLoop < 7U; iLoop++)
        {
            WAIT_STS(REG_1408H, 30, 1);
            RD1_ADDR(REG_1420H, &OutData_MAC[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func102(0xda7dea0eU, 0x084e3f18U, 0x60567062U, 0x73ce8591U);
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
        WR1_PROG(REG_1600H, 0x0000001dU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);

        HW_SCE_p_func100(0xb33b47c0U, 0x878649d1U, 0xc4fc729cU, 0xa6bb2640U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xa7a3d327U, 0xdf977905U, 0x4920feabU, 0x27d0b64dU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1608H, 0x8087001fU);
            WR1_PROG(REG_1400H, 0x0345001dU);
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

            WR1_PROG(REG_1444H, 0x000006c1U);
            WR1_PROG(REG_1824H, 0x9c000005U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_MAC[0]);

            WR1_PROG(REG_1824H, 0x9c100005U);
            WAIT_STS(REG_1444H, 31, 1);
            WR3_ADDR(REG_1420H, &InData_MAC[4]);
            WR1_PROG(REG_1444H, 0x000000a1U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            HW_SCE_p_func100(0x04d8d90cU, 0x6b96c9c6U, 0x9e0e4e93U, 0xf0794cdaU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0xb094a8fbU, 0xa137bccbU, 0x7277d755U, 0x65b717e2U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func102(0x405ebcaeU, 0xb4555f29U, 0x19437680U, 0x1f1d8e16U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
