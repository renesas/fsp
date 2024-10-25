/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub (const uint32_t InData_CurveType[],
                                            const uint32_t InData_Cmd[],
                                            const uint32_t InData_KeyIndex[],
                                            const uint32_t InData_MsgDgst[],
                                            const uint32_t InData_DomainParam[],
                                            uint32_t       OutData_Signature[])
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

    WR1_PROG(REG_1B00H, 0x00f00001U);
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

    WR1_PROG(REG_1444H, 0x000007c7U);
    WR1_PROG(REG_1608H, 0x8088001eU);
    for (iLoop = 0U; iLoop < 8U; iLoop++)
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, InData_MsgDgst[iLoop]);
    }

    WR1_PROG(REG_1458H, 0x00000000U);

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

    HW_SCE_p_func100(0x9f63ba50U, 0xc6f10b13U, 0x5443a939U, 0x2335590eU);
    WR1_PROG(REG_143CH, 0x00400000U);

    if (CHCK_STS(REG_143CH, 22, 1))
    {
        HW_SCE_p_func102(0x8728e799U, 0x0980b959U, 0xc9de3998U, 0xdac0cc1fU);
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x075b04e7U, 0x1f871795U, 0x3cc5273cU, 0x26b46c39U);
        HW_SCE_p_func070_r2(InData_DomainParam);

        HW_SCE_p_func100(0x9550d9d6U, 0xcdb14dd9U, 0xac563b5cU, 0x0c96beb0U);

        WR1_PROG(REG_1404H, 0x11400000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
        WR1_PROG(REG_1400H, 0x00c0001dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x000000c0U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x00000430U);

        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x00000430U);

        WR1_PROG(REG_1004H, 0x04040010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);

        WR1_PROG(REG_1004H, 0x04040010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x10f00000U);
        HW_SCE_p_func103();
        HW_SCE_p_func100(0xbb709378U, 0xe0385b61U, 0xf6847de3U, 0x7229df1fU);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        HW_SCE_p_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000000U));
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_101CH, 0x00000430U);
        WR1_PROG(REG_1020H, 0x00000160U);
        WR1_PROG(REG_1010H, 0x00000020U);

        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1404H, 0x14380000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0001dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30, 0);
        WR1_PROG(REG_143CH, 0x00001800U);

        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000458U);
        WR1_PROG(REG_1020H, 0x00000340U);

        WR1_PROG(REG_1004H, 0x04040009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x000000c0U);

        WR1_PROG(REG_1004H, 0x04040010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0, 0);

        HW_SCE_p_func100(0x8ea66f57U, 0xc0b0a47eU, 0x42a748f6U, 0x6c40f33fU);
        HW_SCE_p_func071_r2(InData_DomainParam);

        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WAIT_STS(REG_1444H, 31, 1);
        WR1_PROG(REG_1420H, change_endian_long(0x000000f0U));
        WR1_PROG(REG_1458H, 0x00000000U);

        HW_SCE_p_func101(0xd1c8d308U, 0xee653fe8U, 0xbd0fb56dU, 0xc84a638fU);
        HW_SCE_p_func088_r1();

        HW_SCE_p_func100(0x866ae4f7U, 0xaf825411U, 0x62152033U, 0x4fe91948U);
        WR1_PROG(REG_143CH, 0x00400000U);

        if (CHCK_STS(REG_143CH, 22, 1))
        {
            HW_SCE_p_func102(0xaee06646U, 0x068d15c0U, 0x0cff73bfU, 0xea9476afU);
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000020U);

            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002a0U);

            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31, 1);
            WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0001dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30, 0);
            WR1_PROG(REG_143CH, 0x00001800U);

            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x00000140U);

            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0, 0);

            WR1_PROG(REG_143CH, 0x00210000U);

            HW_SCE_p_func100(0x0caa0c87U, 0xa5762ff2U, 0x7feb5b1cU, 0x8f3e9e2fU);
            WR1_PROG(REG_143CH, 0x00400000U);

            if (CHCK_STS(REG_143CH, 22, 1))
            {
                HW_SCE_p_func102(0x21e4d6eaU, 0x3301e1fbU, 0x7889b018U, 0x1197a856U);
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0x1a5644dcU, 0x1bb07e7bU, 0xe6388aecU, 0xf13e2df6U);
                WR1_PROG(REG_1404H, 0x11400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c0001dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1014H, 0x000000c0U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_1020H, 0x00000110U);

                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1014H, 0x00000340U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000160U);

                WR1_PROG(REG_1004H, 0x0404000fU);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);
                WR1_PROG(REG_143CH, 0x00000d00U);

                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000840U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000110U);

                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0, 0);

                WR1_PROG(REG_1600H, 0x00000bdeU);
                WR1_PROG(REG_1608H, 0x8188001eU);
                WR1_PROG(REG_1404H, 0x11400000U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30, 0);
                WR1_PROG(REG_143CH, 0x00001800U);

                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x800100e0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x000000f0U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0x1e527673U, 0x8501dbf1U, 0x11bb11e2U, 0x7b538897U);
                HW_SCE_p_func043_r1();

                HW_SCE_p_func074_r1();

                WR1_PROG(REG_1600H, 0x000034feU);

                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WAIT_STS(REG_1444H, 31, 1);
                WR1_PROG(REG_1420H, change_endian_long(0x000000f0U));
                WR1_PROG(REG_1458H, 0x00000000U);

                HW_SCE_p_func101(0xdb88045aU, 0x8374601eU, 0xca10abc3U, 0x2b29f3fcU);
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

                WR1_PROG(REG_1404H, 0x11e00000U);
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

                HW_SCE_p_func100(0x322eb291U, 0x9cd45ba3U, 0xba838404U, 0x880f13ddU);
                WR1_PROG(REG_143CH, 0x00400000U);

                if (CHCK_STS(REG_143CH, 22, 1))
                {
                    HW_SCE_p_func102(0x0d5ce824U, 0xdce53491U, 0xeb8b67baU, 0xca4c6e5eU);
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000840U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x000001b0U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x00000200U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000160U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);

                    WR1_PROG(REG_1004H, 0x04040005U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1014H, 0x00000110U);
                    WR1_PROG(REG_1018H, 0x000001b0U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x00000200U);

                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_1404H, 0x10f00000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31, 1);
                    WR1_PROG(REG_1420H, change_endian_long(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0001dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30, 0);
                    WR1_PROG(REG_143CH, 0x00001800U);

                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000110U);
                    WR1_PROG(REG_1020H, 0x00000140U);

                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0, 0);

                    WR1_PROG(REG_143CH, 0x00210000U);

                    HW_SCE_p_func100(0xedbd5fb9U, 0x72dc1c93U, 0xf94f58c0U, 0x156c13a3U);
                    WR1_PROG(REG_143CH, 0x00400000U);

                    if (CHCK_STS(REG_143CH, 22, 1))
                    {
                        HW_SCE_p_func102(0x1bc1d32fU, 0x422df128U, 0xbf9e76b6U, 0x6c85da27U);
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        HW_SCE_p_func100(0x15c0a64aU, 0x11924217U, 0x0b68b638U, 0xcc9625fbU);
                        WR1_PROG(REG_1404H, 0x12800000U);
                        WR1_PROG(REG_1A2CH, 0x00000100U);
                        WR1_PROG(REG_1A24H, 0x08008107U);
                        WR1_PROG(REG_1400H, 0x00830021U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_Signature[0]);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_Signature[4]);

                        HW_SCE_p_func100(0xe50ff73aU, 0xa554abd9U, 0x5a169ef1U, 0x5be51708U);
                        WR1_PROG(REG_1404H, 0x11e00000U);
                        WR1_PROG(REG_1A2CH, 0x00000100U);
                        WR1_PROG(REG_1A24H, 0x08008107U);
                        WR1_PROG(REG_1400H, 0x00830021U);
                        WAIT_STS(REG_1404H, 30, 0);
                        WR1_PROG(REG_143CH, 0x00001800U);

                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_Signature[8]);
                        WAIT_STS(REG_1408H, 30, 1);
                        RD4_ADDR(REG_1420H, &OutData_Signature[12]);

                        HW_SCE_p_func102(0x61a36e5fU, 0xfd7b5544U, 0x99263c14U, 0xd6428288U);
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12, 0);

                        return FSP_SUCCESS;
                    }
                }
            }
        }
    }
}
