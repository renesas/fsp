/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaSignatureVerificationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_Cmd[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_MsgDgst[],
                                                const uint32_t InData_Signature[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000f101U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010340U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_CurveType[0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010380U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_Cmd[0]);

    WR1_PROG(REG_ECH, 0x00000bdeU);

    WR1_PROG(REG_104H, 0x00001768U);
    WR1_PROG(REG_E0H, 0x8098001eU);
    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_Signature[iLoop]);
    }

    for (iLoop = 0U; iLoop < 8U; iLoop++)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_MsgDgst[iLoop]);
    }

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        HW_SCE_p_func_sub022(0x00000bffU, 0x30003380U, 0x00070020U, 0x0000d3e0U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000381eU, 0x38000c00U, 0x1000d3e0U);
        HW_SCE_p_func_sub022(0x00050040U, 0x0000381eU, 0x000037beU, 0x0000a7a0U);
        WR1_PROG(REG_ECH, 0x00000004U);
        WR1_PROG(REG_ECH, 0x0000383dU);
        WR1_PROG(REG_ECH, 0x38001001U);
        HW_SCE_p_func_sub007(0x1000d3e0U, 0x00000080U, 0x38000fffU, 0x00260000U);

        WR1_PROG(REG_ECH, 0x0000a7c0U);
        WR1_PROG(REG_ECH, 0x00000020U);
    }

    HW_SCE_p_func_sub022(0x30000f5aU, 0x00030020U, 0x0000d3e1U, 0x00000060U);
    WR1_PROG(REG_ECH, 0x38000f9cU);
    WR1_PROG(REG_ECH, 0x1000d3e1U);
    HW_SCE_p_func_sub007(0x00000080U, 0x38008be0U, 0x00000003U, 0x00A60000U);

    static const uint32_t Param_pf1_func100_001[] =
    {
        0xb3a4bb56U, 0x412a388cU, 0x4f9be231U, 0xe3706b28U,
    };
    HW_SCE_p_func100(Param_pf1_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf1_func102_001[] =
        {
            0x0ea78a51U, 0xe36bea34U, 0xc54dd04cU, 0xa2ffc22aU,
        };
        HW_SCE_p_func102(Param_pf1_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_28H, 0x00870001U);

        static const uint32_t Param_pf1_func100_002[] =
        {
            0x55305e12U, 0x530c0fb5U, 0x1c13599eU, 0x4532a352U,
        };
        HW_SCE_p_func100(Param_pf1_func100_002);

        HW_SCE_p_func_sub022(0x30003340U, 0x00050020U, 0x0000b400U, 0x000004C8U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000b400U, 0x0000031CU, 0x00070040U);
        HW_SCE_p_func_sub022(0x30003380U, 0x00070020U, 0x0000b400U, 0x00000080U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000b400U, 0x0000013CU, 0x00050040U);
        HW_SCE_p_func_sub022(0x0000b400U, 0x000001F8U, 0x00000080U, 0x00000080U);

        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        OFS_ADR  = S_RAM[0];

        static const uint32_t Param_pf1_func100_003[] =
        {
            0x8f8943c0U, 0x598761b3U, 0xe9847b6eU, 0x8453ab3eU,
        };
        HW_SCE_p_func100(Param_pf1_func100_003);
        HW_SCE_p_func070_r2(OFS_ADR);

        WR1_PROG(REG_34H, 0x00000800U);
        WR1_PROG(REG_24H, 0x8000bcd0U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub002(0x00000bffU, 0x8190001fU, 0x00003823U, 0x00000015U);

        HW_SCE_p_func_sub011(0x00003823U, 0x00000010U);

        WR1_PROG(REG_ECH, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000140U, 0x8088001fU, 0x00008323U, 0x00000024U);

        HW_SCE_p_func_sub023(0x000070d0U, 0x000084d0U);
        HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);
        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00008cd0U);

        HW_SCE_p_func_sub023(0x00001dc0U, 0x000060c1U);

        WR1_PROG(REG_24H, 0x000019c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591U);
        HW_SCE_p_func_sub017(0x00000d91U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        WR1_PROG(REG_24H, 0x00000dc0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        WR1_PROG(REG_24H, 0x000019c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_24H, 0x00000591U);
        HW_SCE_p_func_sub017(0x00001191U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        WR1_PROG(REG_24H, 0x000011c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_pf1_func100_004[] =
        {
            0x590b209bU, 0xc82029c5U, 0x60cf2f49U, 0x6b7025c3U,
        };
        HW_SCE_p_func100(Param_pf1_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf1_func102_002[] =
            {
                0xf6aee8c1U, 0x440d430dU, 0x36ee5c4eU, 0x8625dc70U,
            };
            HW_SCE_p_func102(Param_pf1_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
            HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

            WR1_PROG(REG_24H, 0x00005004U);
            HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000004U);

            WR1_PROG(REG_ECH, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000100U, 0x8088001fU, 0x00008323U, 0x00000021U);

            for (iLoop = 0U; iLoop < 8U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x0000381fU);

                for (jLoop = 0U; jLoop < 32U; jLoop++)
                {
                    HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                    WR1_PROG(REG_24H, 0x000019a1U);
                    HW_SCE_p_func_sub016(0x000080c1U, 0x3800d81fU);
                    WR1_PROG(REG_E0H, 0x00000080U);
                    WR1_PROG(REG_1CH, 0x00A60000U);

                    WR1_PROG(REG_ECH, 0x00016c00U);

                    static const uint32_t Param_pf1_func100_005[] =
                    {
                        0x2201181cU, 0x9eb62239U, 0x8daf8909U, 0x42c0e057U,
                    };
                    HW_SCE_p_func100(Param_pf1_func100_005);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_pf1_func101_001[] =
                        {
                            0xce3c73fbU, 0x286447d7U, 0x58f537c8U, 0xfb51f8bfU,
                        };
                        HW_SCE_p_func101(Param_pf1_func101_001);
                    }
                    else
                    {
                        static const uint32_t Param_pf1_func101_002[] =
                        {
                            0xfcf15e4dU, 0xa058aa75U, 0x613ad247U, 0x512b85e6U,
                        };
                        HW_SCE_p_func101(Param_pf1_func101_002);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_pf1_func101_003[] =
                {
                    0x3c499c8aU, 0x6ea4ec8fU, 0x030ea18cU, 0x70d4f24fU,
                };
                HW_SCE_p_func101(Param_pf1_func101_003);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000120U);

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            static const uint32_t Param_pf1_func100_006[] =
            {
                0x7d936becU, 0xe1c658d1U, 0xd42327a8U, 0x9d36429eU,
            };
            HW_SCE_p_func100(Param_pf1_func100_006);

            WR1_PROG(REG_24H, 0x00001dc0U);
            HW_SCE_p_func_sub016(0x000060c1U, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000040U, 0x8188001fU, 0x00003823U, 0x00000011U);

            HW_SCE_p_func_sub002(0x0000094aU, 0x8088000aU, 0x00008323U, 0x00000023U);

            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

            HW_SCE_p_func_sub023(0x000011c0U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x000094d0U, 0x00000c2cU);
            HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
            HW_SCE_p_func_sub023(0x0000a0c1U, 0x000009c0U);
            HW_SCE_p_func_sub001(0x0000e0c1U, 0x00000008U, 0x8000d4d0U, 0x000084d0U);
            HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);
            HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x8000c0c1U);

            WR1_PROG(REG_34H, 0x00000003U);
            WR1_PROG(REG_24H, 0x800048d0U);
            WAIT_STS(REG_24H, 21, 0);

            HW_SCE_p_func071_r2(OFS_ADR);
            WR1_PROG(REG_34H, 0x00000802U);
            HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

            WR1_PROG(REG_ECH, 0x0000b540U);
            HW_SCE_p_func_sub002(0x00000040U, 0x8088000aU, 0x00008323U, 0x00000025U);

            HW_SCE_p_func_sub023(0x000009c0U, 0x000080c1U);

            HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);
            WR1_PROG(REG_24H, 0x000019a1U);
            HW_SCE_p_func_sub016(0x0000e0c1U, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000100U, 0x8088001fU, 0x00008323U, 0x00000021U);

            HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

            HW_SCE_p_func_sub022(0x0000b480U, 0x00000100U, 0x0000b7a0U, 0x000000f1U);

            WR1_PROG(REG_ECH, 0x0000377cU);

            WR1_PROG(REG_ECH, 0x00000b9cU);

            static const uint32_t Param_pf1_func100_007[] =
            {
                0x60e62d54U, 0x797b21c9U, 0x1e8cd1c3U, 0xd81aced7U,
            };
            HW_SCE_p_func100(Param_pf1_func100_007);
            WR1_PROG(REG_E0H, 0x81010380U);
            WR1_PROG(REG_04H, 0x00000607U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                static const uint32_t Param_pf1_func101_004[] =
                {
                    0xf6ba2066U, 0x71c4054cU, 0x82369773U, 0x52f78ec2U,
                };
                HW_SCE_p_func101(Param_pf1_func101_004);
                HW_SCE_p_func302();

                if (S_RAM[0] == 0x00000001U)
                {
                    break;
                }

                static const uint32_t Param_pf1_func101_005[] =
                {
                    0x3bbc5587U, 0x0ec4b9dfU, 0xfc6d0c6aU, 0x4b97b23cU,
                };
                HW_SCE_p_func101(Param_pf1_func101_005);
            }

            WR1_PROG(REG_ECH, 0x00000a73U);
            WR1_PROG(REG_ECH, 0x0000b660U);
            HW_SCE_p_func_sub002(0x00000040U, 0x81880013U, 0x00003823U, 0x0000001aU);

            WR1_PROG(REG_24H, 0x00001dc0U);
            HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_pf1_func100_008[] =
            {
                0x55b2bd60U, 0x788ffd90U, 0x69408616U, 0x9bf25968U,
            };
            HW_SCE_p_func100(Param_pf1_func100_008);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pf1_func102_003[] =
                {
                    0xbc5993a1U, 0x4614565bU, 0x1e1848c2U, 0xbf3b91dfU,
                };
                HW_SCE_p_func102(Param_pf1_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                WR1_PROG(REG_34H, 0x00000003U);
                HW_SCE_p_func_sub001(0x800048d0U, 0x00000800U, 0x800068d0U, 0x00001dc0U);
                HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
                HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
                WR1_PROG(REG_24H, 0x0000a0c1U);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_24H, 0x00005004U);
                HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
                WR1_PROG(REG_ECH, 0x00000004U);

                WR1_PROG(REG_ECH, 0x0000b7e0U);
                HW_SCE_p_func_sub002(0x00000100U, 0x8088001fU, 0x00008323U, 0x00000021U);

                for (iLoop = 0U; iLoop < 8U; iLoop++)
                {
                    WR1_PROG(REG_ECH, 0x0000381fU);

                    for (jLoop = 0U; jLoop < 32U; jLoop++)
                    {
                        HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                        WR1_PROG(REG_24H, 0x000019a1U);
                        HW_SCE_p_func_sub016(0x000080c1U, 0x3800d81fU);
                        WR1_PROG(REG_E0H, 0x00000080U);
                        WR1_PROG(REG_1CH, 0x00A60000U);

                        WR1_PROG(REG_ECH, 0x00016c00U);

                        static const uint32_t Param_pf1_func100_009[] =
                        {
                            0x9392224cU, 0x4611f3adU, 0x503f7b17U, 0x7545889cU,
                        };
                        HW_SCE_p_func100(Param_pf1_func100_009);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 1))
                        {
                            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                            HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                            static const uint32_t Param_pf1_func101_006[] =
                            {
                                0xa70971feU, 0x5d3a322cU, 0xdd3f98e8U, 0x8d873476U,
                            };
                            HW_SCE_p_func101(Param_pf1_func101_006);
                        }
                        else
                        {
                            static const uint32_t Param_pf1_func101_007[] =
                            {
                                0xdd8687b0U, 0xce2201d7U, 0xba53b658U, 0xeab59d81U,
                            };
                            HW_SCE_p_func101(Param_pf1_func101_007);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x000027e1U);

                    static const uint32_t Param_pf1_func101_008[] =
                    {
                        0x2957d6f7U, 0x2f37a3cdU, 0x94d16a5fU, 0x7d4f21fcU,
                    };
                    HW_SCE_p_func101(Param_pf1_func101_008);
                }

                WR1_PROG(REG_ECH, 0x00008be0U);
                WR1_PROG(REG_ECH, 0x00000120U);

                WR1_PROG(REG_ECH, 0x00007c1fU);
                WR1_PROG(REG_1CH, 0x00602000U);

                WR1_PROG(REG_34H, 0x00000002U);
                HW_SCE_p_func_sub023(0x80000dc0U, 0x000040c1U);

                WR1_PROG(REG_24H, 0x000009c0U);
                WAIT_STS(REG_24H, 21, 0);
                HW_SCE_p_func_sub001(0x0000a0c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);
                HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
                WR1_PROG(REG_24H, 0x000019a1U);
                WAIT_STS(REG_24H, 21, 0);
                HW_SCE_p_func_sub001(0x000040c1U, 0x00000008U, 0x800015c0U, 0x000060c1U);
                HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x000015c0U, 0x000080c1U);
                HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);
                WR1_PROG(REG_24H, 0x000019a1U);
                WAIT_STS(REG_24H, 21, 0);
                HW_SCE_p_func_sub001(0x0000e0c1U, 0x00000002U, 0x800009c0U, 0x0000a0c1U);

                HW_SCE_p_func_sub001(0x000009c0U, 0x00000800U, 0x800080c1U, 0x000011c0U);
                WR1_PROG(REG_24H, 0x000040c1U);
                WAIT_STS(REG_24H, 21, 0);

                WR1_PROG(REG_ECH, 0x0000379bU);
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x000000f1U);

                static const uint32_t Param_pf1_func101_009[] =
                {
                    0xa2143480U, 0xab721c7dU, 0x400794fbU, 0x90b7f286U,
                };
                HW_SCE_p_func101(Param_pf1_func101_009);
                HW_SCE_p_func043();

                HW_SCE_p_func075_r1();

                HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f1U);

                static const uint32_t Param_pf1_func101_010[] =
                {
                    0xdfb7aecbU, 0x249b9e49U, 0xbd4f48f9U, 0x09ce82beU,
                };
                HW_SCE_p_func101(Param_pf1_func101_010);
                HW_SCE_p_func044();

                HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

                HW_SCE_p_func_sub018(0x00000f62U, 0x40000300U, 0x02e08887U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[5]);
                HW_SCE_p_func_sub011(0x00003223U, 0x00000010U);

                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[9]);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[13]);
                WR1_PROG(REG_00H, 0x00003223U);
                WR1_PROG(REG_2CH, 0x0000001bU);
                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[17]);

                HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

                static const uint32_t Param_pf1_func100_010[] =
                {
                    0xcde594d5U, 0x132b8725U, 0xbc346b76U, 0xb366788aU,
                };
                HW_SCE_p_func100(Param_pf1_func100_010);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_pf1_func102_004[] =
                    {
                        0x1f11c475U, 0x7cc92153U, 0x52eadf9eU, 0xee64c69bU,
                    };
                    HW_SCE_p_func102(Param_pf1_func102_004);
                    WR1_PROG(REG_1BCH, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
                }
                else
                {
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                    WR1_PROG(REG_24H, 0x000011c0U);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_34H, 0x00000800U);
                    HW_SCE_p_func_sub001(0x800040c1U, 0x00000002U, 0x80008cd0U, 0x0000082cU);
                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
                    HW_SCE_p_func_sub023(0x000080c1U, 0x000011c0U);
                    WR1_PROG(REG_34H, 0x00000800U);
                    HW_SCE_p_func_sub001(0x800060c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);

                    WR1_PROG(REG_34H, 0x00000002U);
                    HW_SCE_p_func_sub006(0x800009c0U, 0x00000800U, 0x800080c1U);

                    WR1_PROG(REG_34H, 0x00000002U);
                    HW_SCE_p_func_sub006(0x80000dc0U, 0x00000800U, 0x8000a0c1U);

                    WR1_PROG(REG_ECH, 0x0000b540U);
                    HW_SCE_p_func_sub002(0x00000080U, 0x8088000aU, 0x00008323U, 0x00000022U);

                    WR1_PROG(REG_ECH, 0x0000b540U);
                    HW_SCE_p_func_sub002(0x000000C0U, 0x8088000aU, 0x00008323U, 0x00000023U);

                    WR1_PROG(REG_ECH, 0x0000b7e0U);
                    HW_SCE_p_func_sub002(0x00000100U, 0x8088001fU, 0x00008323U, 0x00000021U);

                    HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

                    HW_SCE_p_func_sub022(0x0000b480U, 0x00000100U, 0x0000b7a0U, 0x00000001U);

                    WR1_PROG(REG_ECH, 0x00000b9cU);

                    static const uint32_t Param_pf1_func100_011[] =
                    {
                        0x26f45b8bU, 0x622dcf12U, 0x37ebeb9aU, 0x07bc3f54U,
                    };
                    HW_SCE_p_func100(Param_pf1_func100_011);
                    WR1_PROG(REG_E0H, 0x81010380U);
                    WR1_PROG(REG_04H, 0x00000607U);
                    WAIT_STS(REG_04H, 30, 1);
                    RD1_ADDR(REG_100H, &S_RAM[0]);
                    S_RAM[0] = change_endian_long(S_RAM[0]);

                    for (iLoop = 0U; iLoop < 256U; iLoop++)
                    {
                        static const uint32_t Param_pf1_func101_011[] =
                        {
                            0xfa6fa228U, 0xead297ceU, 0x1fc0b519U, 0x12a298ecU,
                        };
                        HW_SCE_p_func101(Param_pf1_func101_011);
                        HW_SCE_p_func302();

                        if (S_RAM[0] == 0x00000001U)
                        {
                            break;
                        }

                        static const uint32_t Param_pf1_func101_012[] =
                        {
                            0xf284d5a3U, 0x6e54b6ddU, 0x2b8ba9d2U, 0x19948033U,
                        };
                        HW_SCE_p_func101(Param_pf1_func101_012);
                    }

                    WR1_PROG(REG_24H, 0x00001dc0U);
                    HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
                    WR1_PROG(REG_1CH, 0x00210000U);

                    static const uint32_t Param_pf1_func100_012[] =
                    {
                        0xfff9e72aU, 0x6a9b2259U, 0x9b87326cU, 0x07f21f83U,
                    };
                    HW_SCE_p_func100(Param_pf1_func100_012);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        static const uint32_t Param_pf1_func102_005[] =
                        {
                            0x7bf8560fU, 0x90b8357bU, 0x986d0b9eU, 0x78964becU,
                        };
                        HW_SCE_p_func102(Param_pf1_func102_005);
                        WR1_PROG(REG_1BCH, 0x00000040U);
                        WAIT_STS(REG_18H, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        WR1_PROG(REG_ECH, 0x0000b660U);
                        HW_SCE_p_func_sub002(0x00000080U, 0x81880013U, 0x00003823U, 0x0000001aU);

                        WR1_PROG(REG_ECH, 0x0000b660U);
                        HW_SCE_p_func_sub002(0x000000C0U, 0x81880013U, 0x00003823U, 0x0000001bU);

                        HW_SCE_p_func_sub023(0x00009cd0U, 0x0000102cU);

                        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                        WR1_PROG(REG_24H, 0x000070d0U);
                        WAIT_STS(REG_24H, 21, 0);
                        HW_SCE_p_func_sub001(0x000080c1U, 0x00000002U, 0x800048d0U, 0x0000082cU);

                        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                        HW_SCE_p_func_sub023(0x000040c1U, 0x00000c2cU);

                        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                        HW_SCE_p_func_sub006(0x000080c1U, 0x00000008U, 0x800011c0U);

                        WR1_PROG(REG_34H, 0x00000200U);
                        HW_SCE_p_func_sub006(0x80000a41U, 0x00000008U, 0x800011c0U);

                        WR1_PROG(REG_34H, 0x00000200U);
                        HW_SCE_p_func_sub001(0x80000951U, 0x00000002U, 0x80004cd0U, 0x0000082cU);

                        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                        WR1_PROG(REG_34H, 0x00000280U);
                        HW_SCE_p_func_sub001(0x800019a1U, 0x00000080U, 0x800080c1U, 0x000040c1U);
                        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x0000e0c1U);

                        HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                        HW_SCE_p_func_sub006(0x00000c2cU, 0x00000200U, 0x900019b1U);

                        WR1_PROG(REG_34H, 0x00000280U);
                        HW_SCE_p_func_sub001(0x800019a1U, 0x00000008U, 0x800015c0U, 0x00000941U);
                        HW_SCE_p_func_sub001(0x000080c1U, 0x00000008U, 0x800015c0U, 0x00000951U);
                        WR1_PROG(REG_34H, 0x00000080U);
                        HW_SCE_p_func_sub001(0x800040c2U, 0x00000200U, 0x800012c0U, 0x00008cd0U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x00008cd0U);
                        HW_SCE_p_func_sub023(0x000040c1U, 0x0000102cU);

                        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                        WR1_PROG(REG_24H, 0x00000951U);
                        WAIT_STS(REG_24H, 21, 0);

                        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x800080c1U, 0x00000149U);
                        HW_SCE_p_func_sub023(0x000060c1U, 0x000009c0U);
                        HW_SCE_p_func_sub023(0x00000d51U, 0x000040c1U);
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        WR1_PROG(REG_24H, 0x000019a1U);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_34H, 0x00000080U);
                        HW_SCE_p_func_sub001(0x800080c1U, 0x00000080U, 0x800060c2U, 0x000040c1U);
                        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
                        HW_SCE_p_func_sub023(0x000009c0U, 0x00000d51U);

                        WR1_PROG(REG_24H, 0x000019a1U);
                        WAIT_STS(REG_24H, 21, 0);

                        HW_SCE_p_func_sub001(0x00000145U, 0x00000800U, 0x8000a0c1U, 0x00001dc0U);
                        WR1_PROG(REG_24H, 0x00000591U);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_1CH, 0x00001f00U);
                        WR1_PROG(REG_1CH, 0x00210000U);

                        static const uint32_t Param_pf1_func100_013[] =
                        {
                            0xf8dae94fU, 0x10eb8740U, 0xd99a2a7fU, 0x5994642eU,
                        };
                        HW_SCE_p_func100(Param_pf1_func100_013);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 1))
                        {
                            static const uint32_t Param_pf1_func102_006[] =
                            {
                                0x3ebc5aabU, 0xb88b7fd2U, 0x30e22266U, 0xd261e34dU,
                            };
                            HW_SCE_p_func102(Param_pf1_func102_006);
                            WR1_PROG(REG_1BCH, 0x00000040U);
                            WAIT_STS(REG_18H, 12, 0);

                            return FSP_ERR_CRYPTO_SCE_FAIL;
                        }
                        else
                        {
                            WR1_PROG(REG_34H, 0x00000003U);
                            HW_SCE_p_func_sub001(0x800048d0U, 0x00000800U, 0x800068d0U, 0x00001dc0U);
                            HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
                            HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
                            WR1_PROG(REG_24H, 0x0000a0c1U);
                            WAIT_STS(REG_24H, 21, 0);

                            WR1_PROG(REG_24H, 0x00005004U);
                            HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
                            WR1_PROG(REG_ECH, 0x00000004U);

                            WR1_PROG(REG_ECH, 0x0000b7e0U);
                            HW_SCE_p_func_sub002(0x00000100U, 0x8088001fU, 0x00008323U, 0x00000021U);

                            for (iLoop = 0U; iLoop < 8U; iLoop++)
                            {
                                WR1_PROG(REG_ECH, 0x0000381fU);

                                for (jLoop = 0U; jLoop < 32U; jLoop++)
                                {
                                    HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                                    WR1_PROG(REG_24H, 0x000019a1U);
                                    HW_SCE_p_func_sub016(0x000080c1U, 0x3800d81fU);
                                    WR1_PROG(REG_E0H, 0x00000080U);
                                    WR1_PROG(REG_1CH, 0x00A60000U);

                                    WR1_PROG(REG_ECH, 0x00016c00U);

                                    static const uint32_t Param_pf1_func100_014[] =
                                    {
                                        0xa674de4bU, 0x7cfddb14U, 0x04a7a5f9U, 0xe48f30a2U,
                                    };
                                    HW_SCE_p_func100(Param_pf1_func100_014);
                                    WR1_PROG(REG_1CH, 0x00400000U);
                                    WR1_PROG(REG_1D0H, 0x00000000U);

                                    if (CHCK_STS(REG_1CH, 22, 1))
                                    {
                                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                                        static const uint32_t Param_pf1_func101_013[] =
                                        {
                                            0x7073dd36U, 0x2dd6f3acU, 0xc91b5027U, 0xd78a65c5U,
                                        };
                                        HW_SCE_p_func101(Param_pf1_func101_013);
                                    }
                                    else
                                    {
                                        static const uint32_t Param_pf1_func101_014[] =
                                        {
                                            0x92571603U, 0xfcfec157U, 0x36856296U, 0x6a9eb6b0U,
                                        };
                                        HW_SCE_p_func101(Param_pf1_func101_014);
                                    }
                                }

                                WR1_PROG(REG_ECH, 0x000027e1U);

                                static const uint32_t Param_pf1_func101_015[] =
                                {
                                    0x953447d6U, 0x130e6df0U, 0x513a9531U, 0xcf569436U,
                                };
                                HW_SCE_p_func101(Param_pf1_func101_015);
                            }

                            WR1_PROG(REG_ECH, 0x00008be0U);
                            WR1_PROG(REG_ECH, 0x00000120U);

                            WR1_PROG(REG_ECH, 0x00007c1fU);
                            WR1_PROG(REG_1CH, 0x00602000U);

                            WR1_PROG(REG_34H, 0x00000002U);
                            HW_SCE_p_func_sub023(0x80000dc0U, 0x000040c1U);

                            WR1_PROG(REG_24H, 0x000009c0U);
                            WAIT_STS(REG_24H, 21, 0);
                            HW_SCE_p_func_sub001(0x0000a0c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);
                            HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
                            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                            WR1_PROG(REG_24H, 0x000019a1U);
                            HW_SCE_p_func_sub016(0x000040c1U, 0x0000b7e0U);
                            HW_SCE_p_func_sub002(0x00000140U, 0x8188001fU, 0x00003823U, 0x00000014U);

                            HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);
                            WR1_PROG(REG_24H, 0x100019b1U);
                            WAIT_STS(REG_24H, 21, 0);
                            HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x000088d0U);
                            HW_SCE_p_func_sub023(0x00009004U, 0x00001028U);
                            WR1_PROG(REG_24H, 0x100019b1U);
                            WAIT_STS(REG_24H, 21, 0);
                            WR1_PROG(REG_24H, 0x000019a1U);
                            HW_SCE_p_func_sub016(0x000040c1U, 0x0000b660U);
                            HW_SCE_p_func_sub002(0x00000000U, 0x81880013U, 0x00003823U, 0x00000014U);

                            WR1_PROG(REG_24H, 0x000009c0U);
                            HW_SCE_p_func_sub017(0x00001991U, 0x00001f00U);
                            WR1_PROG(REG_1CH, 0x00210000U);

                            WR1_PROG(REG_24H, 0x000019c0U);
                            HW_SCE_p_func_sub017(0x00000991U, 0x00001f00U);
                            WR1_PROG(REG_1CH, 0x00210000U);

                            static const uint32_t Param_pf1_func100_015[] =
                            {
                                0x0407c0bdU, 0x083c771aU, 0xf0b7db95U, 0xc265fa8cU,
                            };
                            HW_SCE_p_func100(Param_pf1_func100_015);
                            WR1_PROG(REG_1CH, 0x00400000U);
                            WR1_PROG(REG_1D0H, 0x00000000U);

                            if (CHCK_STS(REG_1CH, 22, 1))
                            {
                                static const uint32_t Param_pf1_func102_007[] =
                                {
                                    0x85746d5fU, 0x25b93196U, 0x52b9dc3eU, 0x9cbb1883U,
                                };
                                HW_SCE_p_func102(Param_pf1_func102_007);
                                WR1_PROG(REG_1BCH, 0x00000040U);
                                WAIT_STS(REG_18H, 12, 0);

                                return FSP_ERR_CRYPTO_SCE_FAIL;
                            }
                            else
                            {
                                static const uint32_t Param_pf1_func102_008[] =
                                {
                                    0x06dfc759U, 0xb0c6aaa4U, 0x39be31bcU, 0x42fe0748U,
                                };
                                HW_SCE_p_func102(Param_pf1_func102_008);
                                WR1_PROG(REG_1BCH, 0x00000040U);
                                WAIT_STS(REG_18H, 12, 0);

                                return FSP_SUCCESS;
                            }
                        }
                    }
                }
            }
        }
    }
}
