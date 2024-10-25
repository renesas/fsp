/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes256CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x4a008104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xe36cbef0U, 0xd1f3b380U, 0x2047fcb3U, 0x111c601aU);
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x5a008104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x35e7877cU, 0x6aa6e895U, 0x00781be3U, 0x35db88c4U);
    }

    WR1_PROG(REG_1824H, 0x0c000045U);
    WR1_PROG(REG_1400H, 0x00410011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x3601f463U, 0xec9c354aU, 0x3709dcf1U, 0x4abb8a0fU);
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008505U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[0]);

        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_DataT[0]);

        HW_SCE_p_func102(0x94bb0536U, 0x7ab7d942U, 0xf8d26060U, 0x01992d7fU);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010040U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_DataTLen[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3420a840U);
        WR1_PROG(REG_1600H, 0x00000010U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x0000b460U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1600H, 0x34202862U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0xea4d30aeU, 0x83aa7385U, 0x3aa85822U, 0xac773950U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xd8c3a568U, 0x1f3adc37U, 0x0f42d86cU, 0x1e20896cU);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000000U);
            WR1_PROG(REG_1824H, 0x0e008505U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);

            WR1_PROG(REG_1600H, 0x00000821U);
            WR1_PROG(REG_1608H, 0x80840001U);
            WR1_PROG(REG_1400H, 0x03410011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1600H, 0x000034e2U);
            WR1_PROG(REG_1600H, 0x000568e7U);
            WR1_PROG(REG_1600H, 0x00026ce7U);

            WR1_PROG(REG_1600H, 0x00003827U);

            WR1_PROG(REG_1600H, 0x0000b4c0U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1600H, 0x00003402U);
            WR1_PROG(REG_1600H, 0x00008c00U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x000028c0U);
            WR1_PROG(REG_1600H, 0x00008cc0U);
            WR1_PROG(REG_1600H, 0x0000001fU);

            WR1_PROG(REG_1600H, 0x00004406U);

            WR1_PROG(REG_1600H, 0x00007421U);
            WR1_PROG(REG_1600H, 0x00007821U);

            WR1_PROG(REG_1600H, 0x00003c27U);

            WR1_PROG(REG_1600H, 0x000034c2U);
            WR1_PROG(REG_1600H, 0x0000a4c0U);
            WR1_PROG(REG_1600H, 0x0000001fU);
            WR1_PROG(REG_1600H, 0x000568c6U);

            WR1_PROG(REG_1600H, 0x000034e6U);
            WR1_PROG(REG_1600H, 0x00026ce7U);

            WR1_PROG(REG_1600H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4U; iLoop++)
            {
                WR1_PROG(REG_1600H, 0x3420a8e0U);
                WR1_PROG(REG_1600H, 0x0000000dU);
                WR1_PROG(REG_1600H, 0x10003c27U);

                WR1_PROG(REG_1600H, 0x1000a4e0U);
                WR1_PROG(REG_1600H, 0x00000004U);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            WR1_PROG(REG_1824H, 0x08000045U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x9c000005U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_DataT[0]);

            HW_SCE_p_func100(0xfa93240bU, 0x14ad8332U, 0xf1b374ebU, 0x71fc6c42U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x6a502d73U, 0x601e6f62U, 0xe7365b07U, 0xaabd2595U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0xc73db6d5U, 0x52998f78U, 0xc5bc2d1cU, 0x9b206637U);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
