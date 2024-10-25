/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Aes192CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func100(0x001ba8edU, 0x39320322U, 0xcd0c9656U, 0x24631606U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x531ca459U, 0x8a2e2a98U, 0x3e79ec51U, 0x6cee3406U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x4a008104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            HW_SCE_p_func101(0x9f337803U, 0x55833d57U, 0x032b4fd0U, 0xac60f337U);
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x5a008104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

            HW_SCE_p_func101(0x8fcbb10fU, 0xd746096aU, 0x77b645aaU, 0x5df74aa9U);
        }

        WR1_PROG(REG_1824H, 0x0c000045U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
        {
            HW_SCE_p_func100(0xede50bdbU, 0x93d4269cU, 0x37363131U, 0xba9c2632U);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_182CH, 0x40000010U);
            WR1_PROG(REG_1824H, 0x0e008505U);
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_Text[0]);

            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30, 1);
            RD4_ADDR(REG_1420H, &OutData_DataT[0]);

            HW_SCE_p_func102(0xfbce1a04U, 0x51148e36U, 0x92e9abd8U, 0xa590b94cU);
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

            HW_SCE_p_func100(0xb326af84U, 0x8d3ff170U, 0xafde495aU, 0x531bdb96U);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x520dee03U, 0xe1b712f0U, 0x9aeebe49U, 0x231075eeU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_182CH, 0x40000010U);
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

                HW_SCE_p_func100(0xf9f0d3b1U, 0xcd660a5eU, 0x68e01d67U, 0xe2794294U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0xeb0108b1U, 0x8bbff7c4U, 0x58090e47U, 0x91bd1b8fU);
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
                }
                else
                {
                    HW_SCE_p_func102(0x4b5024d2U, 0x45c98896U, 0x1d6ecc98U, 0x8d3bbc05U);
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
