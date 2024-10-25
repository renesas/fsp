/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Sha256HmacMessageDigest (const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Cmd[],
                                          const uint32_t InData_Msg[],
                                          const uint32_t InData_MsgLen[],
                                          const uint32_t InData_MAC[],
                                          const uint32_t InData_length[],
                                          uint32_t       InData_State[],
                                          uint32_t       OutData_MAC[],
                                          uint32_t       OutData_State[],
                                          const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00750001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800100e0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_KeyIndex[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000075U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0xd8cdc84eU, 0x4e58c39eU, 0x9c2e859eU, 0x3d6836a8U);
    HW_SCE_p_func043_r1();

    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1600H, 0x0000001bU);

    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000075U));
    WR1_PROG(REG_1458H, 0x00000000U);

    HW_SCE_p_func101(0x4e970dc8U, 0x41790fb3U, 0x27ccf559U, 0x64c69112U);
    HW_SCE_p_func044_r1();

    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[1]);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[5]);

    WR1_PROG(REG_1600H, 0x00000800U);
    WR1_PROG(REG_1608H, 0x80880000U);
    WR1_PROG(REG_1400H, 0x03420021U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_KeyIndex[9]);

    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30, 0);
    WR1_PROG(REG_143CH, 0x00001800U);

    HW_SCE_p_func100(0xcdaecd60U, 0xad1dc540U, 0x3be7aa6eU, 0x27db89acU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xc8cf5ad5U, 0x2716ed71U, 0x4fea464aU, 0xdd8d7452U);
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_2000H, 0x00000001U);

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010020U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_Cmd[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1600H, 0x3420a820U);
        WR1_PROG(REG_1600H, 0x00000006U);
        WR1_PROG(REG_1600H, 0x2000b420U);
        WR1_PROG(REG_1600H, 0x00000005U);

        WR1_PROG(REG_1600H, 0x38000c21U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x8c61caadU, 0xa243673aU, 0x13f0720aU, 0x457bf025U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            WR1_PROG(REG_2004H, 0x00000050U);

            WR1_PROG(REG_2008H, 0x00000013U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1608H, 0x81880000U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
            {
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2010H, 0x00000080U);

                WR1_PROG(REG_200CH, 0x00000001U);

                WAIT_STS(REG_2030H, 8, 0);

                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x00000020U);
                WR1_PROG(REG_2010H, 0x00000000U);

                WR1_PROG(REG_200CH, 0x00000100U);

                HW_SCE_p_func101(0xc50e5632U, 0x0962f865U, 0xbb702a6dU, 0xa65b110aU);
            }
            else
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2014H, InData_MsgLen[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2010H, InData_MsgLen[1]);

                WR1_PROG(REG_200CH, 0x00000001U);

                HW_SCE_p_func101(0x74010413U, 0xcca0fe11U, 0x276fcb06U, 0x2d996ab5U);
            }

            HW_SCE_p_func101(0x8835e914U, 0x94e50a9aU, 0x13fd7d68U, 0x46781495U);
        }
        else
        {
            WR1_PROG(REG_2004H, 0x00001050U);

            WR1_PROG(REG_2008H, 0x00000013U);

            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1608H, 0x81880000U);
            WR1_PROG(REG_1400H, 0x01490021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2014H, InData_State[18]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_PROG(REG_2010H, InData_State[19]);

            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_PROG(REG_2028H, InData_State[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            HW_SCE_p_func101(0x5def8264U, 0xd0117141U, 0x519b83a2U, 0x5555bab8U);
        }

        WAIT_STS(REG_2030H, 0, 1);

        WR1_PROG(REG_1444H, 0x00020064U);

        for (iLoop = 0U; iLoop < (MAX_CNT & 0xfffffff0U); )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR16_ADDR(REG_1420H, &InData_Msg[iLoop]);
            iLoop = iLoop + 16U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop++)
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, InData_Msg[iLoop]);
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x00000000U);
        WAIT_STS(REG_2030H, 8, 0);
        WR1_PROG(REG_143CH, 0x00001600U);

        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x38008820U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        HW_SCE_p_func100(0x756303f5U, 0xcbbf4499U, 0x1ac072d2U, 0xcd17b873U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            for (iLoop = 0U; iLoop < 18U; iLoop++)
            {
                RD1_ADDR(REG_202CH, &OutData_State[iLoop]);
            }

            WR1_PROG(REG_1458H, 0x00000000U);

            RD1_ADDR(REG_2014H, &OutData_State[18]);
            RD1_ADDR(REG_2010H, &OutData_State[19]);

            HW_SCE_p_func102(0xaa907f00U, 0xa355cb1cU, 0xfb574a2aU, 0x558c10c1U);
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_SUCCESS;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38000c21U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_1600H, 0x38008820U);
            WR1_PROG(REG_1600H, 0x00000003U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);

            HW_SCE_p_func100(0x95a1f904U, 0xd0ffc6a7U, 0x86801fcaU, 0xd1d4a34cU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func100(0x158b4651U, 0x664d2259U, 0xc16830b0U, 0x4c31b5b3U);
                WR1_PROG(REG_1408H, 0x00004022U);
                WAIT_STS(REG_1408H, 30, 1);
                RD8_ADDR(REG_1420H, &OutData_MAC[0]);

                HW_SCE_p_func102(0x8f714f90U, 0x2628496aU, 0x01f3d198U, 0x37697c0dU);
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_SUCCESS;
            }
            else
            {
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010020U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_length[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1600H, 0x3420a820U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);

                WR1_PROG(REG_1600H, 0x3420a820U);
                WR1_PROG(REG_1600H, 0x00000021U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);

                HW_SCE_p_func100(0xd86622f7U, 0x85e33801U, 0xe8ed8f15U, 0x292af5f4U);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0x5b5f2d80U, 0x9d883acbU, 0xe99da31bU, 0xf38f5539U);
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

                    HW_SCE_p_func100(0xf2fc6ceaU, 0x1c8b40f5U, 0x08ec44cdU, 0x1e06d3fbU);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func102(0x216145e9U, 0x6e19a32dU, 0x6cffe29bU, 0x1dd3625aU);
                        WR1_PROG(REG_14BCH, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        HW_SCE_p_func102(0x8fb87652U, 0xaee6ca2aU, 0xd54b181cU, 0xdf4ef224U);
                        WR1_PROG(REG_14BCH, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_SUCCESS;
                    }
                }
            }
        }
    }
}
