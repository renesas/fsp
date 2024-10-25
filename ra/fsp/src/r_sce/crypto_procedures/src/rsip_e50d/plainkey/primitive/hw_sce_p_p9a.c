/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_Cmd[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_PubKey[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t       OutData_R[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_14B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x009a0001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010340U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_CurveType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010380U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x00000bdeU);

    WR1_PROG(REG_1444H, 0x00000fc7U);
    WR1_PROG(REG_1608H, 0x8090001eU);
    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_PubKey[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    for (iLoop = 0U; iLoop < 2U; iLoop++)
    {
        WR1_PROG(REG_1600H, 0x00000bffU);

        WR1_PROG(REG_1600H, 0x30003380U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1600H, 0x0000d3e0U);
        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1600H, 0x0000381eU);
        WR1_PROG(REG_1600H, 0x38000c00U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1600H, 0x0000381eU);
        WR1_PROG(REG_1600H, 0x000037beU);
        WR1_PROG(REG_1600H, 0x0000a7a0U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1600H, 0x0000383dU);
        WR1_PROG(REG_1600H, 0x38001001U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1600H, 0x00000080U);

        WR1_PROG(REG_1600H, 0x38000fffU);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);

        WR1_PROG(REG_1600H, 0x0000a7c0U);
        WR1_PROG(REG_1600H, 0x00000020U);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

    WR1_PROG(REG_1600H, 0x30000f5aU);
    WR1_PROG(REG_1600H, 0x00030020U);
    WR1_PROG(REG_1600H, 0x0000d3e1U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1600H, 0x38000f9cU);
    WR1_PROG(REG_1600H, 0x1000d3e1U);
    WR1_PROG(REG_1600H, 0x00000080U);

    WR1_PROG(REG_1600H, 0x38008be0U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);

    HW_SCE_p_func100(0x5aa4bbf8U, 0xbc0b49d0U, 0xc9084846U, 0x540a8890U);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0xfdcb5f0fU, 0x3aed7143U, 0x90da5e43U, 0xfe7c7f76U);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x800100e0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_KeyIndex[0]);
        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0000009aU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xa5a8873bU, 0xb0326e70U, 0x4649c07bU, 0x35ed2382U);
        HW_SCE_p_func043_r1();

        HW_SCE_p_func074_r1();

        WR1_PROG(REG_1600H, 0x000034feU);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x0000009aU));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0x5e8cba89U, 0x2aa535e6U, 0xf2defdc9U, 0x38883b74U);
        HW_SCE_p_func044_r1();

        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_1444H, 31, 1);
            WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        WR1_PROG(REG_1458H, 0x00000000U);

        WR1_PROG(REG_1404H, 0x13200000U);
        WR1_PROG(REG_1400H, 0x00c20021U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 1]);

        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func100(0xa633b195U, 0xa1769e94U, 0x7d0becbdU, 0x9dc80501U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0x0f31570bU, 0x50a922beU, 0xd5c1de50U, 0x070f45e8U);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0xc9e5323eU, 0xf1d0f7fdU, 0xe2a57fd4U, 0xb2c4155cU);
            HW_SCE_p_func070_r2(InData_DomainParam);

            WR1_PROG(REG_1010H, 0x00000020U);
            WR1_PROG(REG_101CH, 0x000000c0U);

            WR1_PROG(REG_1004H, 0x04040010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1010H, 0x00000018U);
            WR1_PROG(REG_101CH, 0x00000070U);

            WR1_PROG(REG_1004H, 0x04040010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1600H, 0x00000bdeU);
            WR1_PROG(REG_1608H, 0x8190001eU);

            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1404H, 0x11400000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            HW_SCE_p_func008_r1();

            HW_SCE_p_func100(0x15d54b2aU, 0xa3f652faU, 0x7fa597feU, 0x564eedaeU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0xdb7ceb4dU, 0xbc3773a8U, 0x1b01bcd4U, 0x1808b7d3U);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_1404H, 0x10f00000U);
                WR1_PROG(REG_1400H, 0x00c00021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x00000200U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_1020H, 0x00000228U);

                WR1_PROG(REG_1004H, 0x04040009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x000001b0U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_1020H, 0x00000200U);

                WR1_PROG(REG_1004H, 0x04040009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x0000009aU));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x5bc65a3eU, 0x147966d3U, 0xf39bba30U, 0x5ed1feb4U);
                HW_SCE_p_func088_r1();

                HW_SCE_p_func100(0xed8515b2U, 0x722a7d11U, 0x3652fd90U, 0x1006f47dU);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0x8b6e3aeeU, 0xa4314376U, 0x0b4461d4U, 0x42669883U);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0xf1952344U, 0x13725da0U, 0xa9539708U, 0x6ca2f264U);
                    WR1_PROG(REG_1404H, 0x12800000U);
                    WR1_PROG(REG_1A2CH, 0x00000100U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002022U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[0]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[4]);

                    HW_SCE_p_func100(0xfee89de8U, 0x2d768e5cU, 0x6b741038U, 0x1f481647U);
                    WR1_PROG(REG_1404H, 0x12d00000U);
                    WR1_PROG(REG_1A2CH, 0x00000100U);
                    WR1_PROG(REG_1A24H, 0x08008107U);
                    WR1_PROG(REG_1400H, 0x00830021U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1408H, 0x00002022U);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[8]);
                    WAIT_STS(REG_1408H, 30, 1);
                    RD4_ADDR(REG_1420H, &OutData_R[12]);

                    HW_SCE_p_func102(0x769c2d07U, 0xe3660406U, 0x7943a021U, 0x892e160aU);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
