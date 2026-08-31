/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func073_r3 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    HW_SCE_p_func070(ARG1);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_B8H, 0x0000000aU);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub012();

    WR1_PROG(REG_B0H, 0x0000141eU);
    HW_SCE_p_func_sub003(0x00c0001dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x001e000aU, 0x00140000U, 0x0404000aU);

    HW_SCE_p_func_sub002(0x00690014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x001e0069U, 0x00190000U, 0x0404000aU);
    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x006e0014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x001e006eU, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func073_func100_001[] =
    {
        0xd44326cfU, 0xcc4c8da1U, 0x09650840U, 0x168841b4U,
    };
    HW_SCE_p_func100(Param_func073_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func073_func101_001[] =
        {
            0x15223210U, 0x048974d4U, 0xbf795623U, 0x0cc6c2e5U,
        };
        HW_SCE_p_func101(Param_func073_func101_001);
    }
    else
    {
        static const uint32_t Param_func073_func100_002[] =
        {
            0xf015a2d2U, 0x4d6c5ea7U, 0x8f4247b4U, 0x34e1a825U,
        };
        HW_SCE_p_func100(Param_func073_func100_002);

        HW_SCE_p_func_sub002(0x001e0014U, 0x00190000U, 0x0404000aU);

        HW_SCE_p_func_sub019(0x0019006eU, 0x000f000aU, 0x04040000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub002(0x005a000fU, 0x0014000aU, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001423U);
        HW_SCE_p_func_sub003(0x00c00021U);

        HW_SCE_p_func_sub002(0x00230072U, 0x000f0000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x0014000fU, 0x000f000aU, 0x04040002U);

        HW_SCE_p_func_sub002(0x00140069U, 0x0032000aU, 0x04040002U);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub012();

        HW_SCE_p_func_sub002(0x00230069U, 0x000a0000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x00370076U, 0x004b0005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x0037007aU, 0x00500005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x00140037U, 0x00550005U, 0x04040002U);

        HW_SCE_p_func_sub002(0x0023005fU, 0x00280000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x00230005U, 0x002d0000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x00000415U);
        HW_SCE_p_func_sub003(0x00c00009U);

        WR1_PROG(REG_B0H, 0x0000041aU);
        HW_SCE_p_func_sub003(0x00c00009U);
        HW_SCE_p_func071(ARG1);

        HW_SCE_p_func_sub002(0x00230019U, 0x005a0000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x0023001eU, 0x005f0000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x00230055U, 0x00640000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x0000046fU);
        HW_SCE_p_func_sub003(0x00c00009U);

        HW_SCE_p_func_sub002(0x004b005aU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x005a004bU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x0050005fU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x005f0050U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func073_func100_003[] =
        {
            0xddf243d7U, 0xa423d005U, 0x3bd6f7c8U, 0xd187ee6cU,
        };
        HW_SCE_p_func100(Param_func073_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub002(0x00550064U, 0x00730005U, 0x04040013U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func073_func101_002[] =
            {
                0xe3fc1b40U, 0x44b75688U, 0x09354e09U, 0xd126dd98U,
            };
            HW_SCE_p_func101(Param_func073_func101_002);
        }
        else
        {
            HW_SCE_p_func_sub002(0x00000064U, 0x0073002dU, 0x04040014U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func073_func101_003[] =
            {
                0xf224d8abU, 0x8167811fU, 0x5c12584fU, 0x833a6c01U,
            };
            HW_SCE_p_func101(Param_func073_func101_003);
        }

        HW_SCE_p_func_sub002(0x0023000fU, 0x00370000U, 0x04040009U);

        HW_SCE_p_func_sub002(0x00190019U, 0x00190000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x001e001eU, 0x001e0000U, 0x0404000aU);

        HW_SCE_p_func_sub002(0x00230023U, 0x00230000U, 0x0404000aU);

        WR1_PROG(REG_94H, 0x00000800U);
        for (iLoop = 0U; iLoop < 2U; iLoop++)
        {
            HW_SCE_p_func_sub006(0x000008a5U, 0x38000c00U, 0x00270000U);

            static const uint32_t Param_func073_func100_004[] =
            {
                0x94010accU, 0xb6acc956U, 0xd6224e72U, 0x58986c24U,
            };
            HW_SCE_p_func100(Param_func073_func100_004);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_B0H, 0x00000834U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000835U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x0000082fU);
                HW_SCE_p_func_sub003(0x03430009U);

                HW_SCE_p_func_sub014(0x00000830U);
                HW_SCE_p_func_sub003(0x03430009U);

                static const uint32_t Param_func073_func101_004[] =
                {
                    0xf8c1d30bU, 0x200eb628U, 0x5d6416ecU, 0xdf6ee117U,
                };
                HW_SCE_p_func101(Param_func073_func101_004);
            }
            else
            {
                WR1_PROG(REG_B0H, 0x00000836U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000837U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000831U);
                HW_SCE_p_func_sub003(0x03430009U);

                HW_SCE_p_func_sub014(0x00000832U);
                HW_SCE_p_func_sub003(0x03430009U);

                static const uint32_t Param_func073_func101_005[] =
                {
                    0x8a72d1cfU, 0x999805d9U, 0x474ff2caU, 0x17504d70U,
                };
                HW_SCE_p_func101(Param_func073_func101_005);
            }

            WR1_PROG(REG_94H, 0x00000821U);

            for (jLoop = 0U; jLoop < 4U; jLoop++)
            {
                HW_SCE_p_func_sub001(0x000034a1U, 0x00026ca5U, 0x00003865U, 0x0000a4a0U);
                HW_SCE_p_func_sub022(0x00000010U, 0x00003885U, 0x00000842U);

                for (kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    HW_SCE_p_func_sub001(0x000008a5U, 0x01816ca3U, 0x01816ca4U, 0x00016c63U);
                    WR1_PROG(REG_94H, 0x00016c84U);

                    WR1_PROG(REG_B0H, 0x00001414U);
                    HW_SCE_p_func_sub003(0x00c0001dU);
                    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                    HW_SCE_p_func_sub002(0x00140019U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    HW_SCE_p_func_sub002(0x00140023U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    static const uint32_t Param_func073_func100_005[] =
                    {
                        0x0472c7a8U, 0x5363d49dU, 0x6e422d40U, 0x17637d0cU,
                    };
                    HW_SCE_p_func100(Param_func073_func100_005);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        HW_SCE_p_func_sub002(0x00000023U, 0x0023002dU, 0x04040014U);
                        WR1_PROG(REG_40H, 0x00000d00U);

                        static const uint32_t Param_func073_func101_006[] =
                        {
                            0x656affc3U, 0xf594d350U, 0x234a2ddfU, 0xabebf293U,
                        };
                        HW_SCE_p_func101(Param_func073_func101_006);
                    }
                    else
                    {
                        static const uint32_t Param_func073_func101_007[] =
                        {
                            0xdf8c09abU, 0xee6b1638U, 0xd68d436fU, 0x7620be60U,
                        };
                        HW_SCE_p_func101(Param_func073_func101_007);
                    }

                    HW_SCE_p_func_sub010(0x38000ca5U, 0x00A70000U);

                    static const uint32_t Param_func073_func100_006[] =
                    {
                        0x1033ada8U, 0xaa087ee5U, 0xc7ce5a60U, 0x0fa2e522U,
                    };
                    HW_SCE_p_func100(Param_func073_func100_006);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        static const uint32_t Param_func073_func100_007[] =
                        {
                            0xdc377967U, 0x7018f313U, 0x1591c55dU, 0x6200f4adU,
                        };
                        HW_SCE_p_func100(Param_func073_func100_007);

                        WR1_PROG(REG_B0H, 0x00001414U);
                        HW_SCE_p_func_sub003(0x00c00021U);

                        WR1_PROG(REG_94H, 0x00007c05U);
                        WR1_PROG(REG_40H, 0x00600000U);

                        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
                        {
                            HW_SCE_p_func_sub002(0x0014004bU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140050U, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140055U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_008[] =
                            {
                                0xd9f2a1afU, 0x36443713U, 0x31c5ca55U, 0xed51c392U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_008);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
                        {
                            HW_SCE_p_func_sub002(0x0014005aU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x0014005fU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140064U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_009[] =
                            {
                                0x2996b285U, 0x82aec079U, 0x89bb240eU, 0x31027650U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_009);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
                        {
                            HW_SCE_p_func_sub002(0x00140069U, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x0014006eU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140073U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_010[] =
                            {
                                0x86a0c4b5U, 0x1d4b7a02U, 0x905353f1U, 0x599837e7U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_010);
                        }

                        WR1_PROG(REG_B0H, 0x00001414U);
                        HW_SCE_p_func_sub003(0x00c0001dU);
                        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                        HW_SCE_p_func_sub002(0x00140019U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        HW_SCE_p_func_sub002(0x00140023U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        static const uint32_t Param_func073_func100_008[] =
                        {
                            0x9ec30cecU, 0xaf1fe16eU, 0x2e4fcba6U, 0x879d21ccU,
                        };
                        HW_SCE_p_func100(Param_func073_func100_008);
                        WR1_PROG(REG_40H, 0x00400000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            HW_SCE_p_func_sub002(0x0014003cU, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            HW_SCE_p_func_sub002(0x00140046U, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            static const uint32_t Param_func073_func100_009[] =
                            {
                                0x173624dcU, 0xa3ea5c81U, 0x9ac97b2dU, 0xef93ed00U,
                            };
                            HW_SCE_p_func100(Param_func073_func100_009);
                            WR1_PROG(REG_40H, 0x00400000U);

                            if (CHCK_STS(REG_40H, 22, 1))
                            {
                                HW_SCE_p_func_sub002(0x003c0019U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x0019003cU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x0041001eU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x001e0041U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x00460023U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x00230046U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                static const uint32_t Param_func073_func100_010[] =
                                {
                                    0x8aea722fU, 0xcd737685U, 0x65fd1f3dU, 0x1b1ca693U,
                                };
                                HW_SCE_p_func100(Param_func073_func100_010);
                                WR1_PROG(REG_40H, 0x00400000U);

                                if (CHCK_STS(REG_40H, 22, 1))
                                {
                                    HW_SCE_p_func_sub002(0x00460023U, 0x00230005U, 0x04040013U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func073_func101_011[] =
                                    {
                                        0xb6ed1778U, 0x3cde6dc6U, 0x38eef0b6U, 0x3325dea6U,
                                    };
                                    HW_SCE_p_func101(Param_func073_func101_011);
                                }
                                else
                                {
                                    HW_SCE_p_func_sub002(0x00000023U, 0x0023002dU, 0x04040014U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func073_func101_012[] =
                                    {
                                        0x4b07d3c2U, 0x1cbb75b8U, 0xe772770eU, 0x5304c00bU,
                                    };
                                    HW_SCE_p_func101(Param_func073_func101_012);
                                }
                            }
                            else
                            {
                                static const uint32_t Param_func073_func101_013[] =
                                {
                                    0x6c53ae6bU, 0x8bd65050U, 0x2d986b2aU, 0x0e88c60aU,
                                };
                                HW_SCE_p_func101(Param_func073_func101_013);
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_B0H, 0x00001414U);
                            HW_SCE_p_func_sub003(0x00c00021U);

                            HW_SCE_p_func_sub002(0x0014003cU, 0x00190000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140041U, 0x001e0000U, 0x04040009U);

                            HW_SCE_p_func_sub002(0x00140046U, 0x00230000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_014[] =
                            {
                                0x684aa554U, 0x72a82464U, 0x8adb7d99U, 0xed6acda3U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_014);
                        }
                    }
                    else
                    {
                        static const uint32_t Param_func073_func101_015[] =
                        {
                            0x4005b519U, 0x6657c68fU, 0x0db70743U, 0x30407c0cU,
                        };
                        HW_SCE_p_func101(Param_func073_func101_015);
                    }

                    WR1_PROG(REG_94H, 0x00002c40U);
                    static const uint32_t Param_func073_func101_016[] =
                    {
                        0x81ae2678U, 0x5b63367bU, 0x7edb0e92U, 0x92b60bfbU,
                    };
                    HW_SCE_p_func101(Param_func073_func101_016);
                }

                HW_SCE_p_func_sub006(0x38008840U, 0x00000020U, 0x00270000U);

                WR1_PROG(REG_40H, 0x00402000U);

                WR1_PROG(REG_94H, 0x00002c20U);

                static const uint32_t Param_func073_func101_017[] =
                {
                    0xc3a10a91U, 0x77b8f7d9U, 0x35127eaeU, 0xd28bd99cU,
                };
                HW_SCE_p_func101(Param_func073_func101_017);
            }

            HW_SCE_p_func_sub006(0x38008820U, 0x00000004U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_94H, 0x00002c00U);

            static const uint32_t Param_func073_func101_018[] =
            {
                0x4730b82eU, 0x93731f89U, 0x72ad1513U, 0x29c42420U,
            };
            HW_SCE_p_func101(Param_func073_func101_018);
        }

        HW_SCE_p_func_sub006(0x38008800U, 0x00000002U, 0x00270000U);

        WR1_PROG(REG_40H, 0x00402000U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub003(0x00c00021U);

        HW_SCE_p_func_sub002(0x0014000aU, 0x00690000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub003(0x00c0001dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x00140023U, 0x002d0000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func073_func100_011[] =
        {
            0x446ff254U, 0x3dca4f31U, 0x7a4fb084U, 0x466eadc5U,
        };
        HW_SCE_p_func100(Param_func073_func100_011);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            static const uint32_t Param_func073_func101_019[] =
            {
                0xd4c0a804U, 0x3f0d7b92U, 0x8f0e1601U, 0x3a1cc264U,
            };
            HW_SCE_p_func101(Param_func073_func101_019);
        }
        else
        {
            static const uint32_t Param_func073_func100_012[] =
            {
                0x7445c5a7U, 0x7aae8e0aU, 0xcd2fd552U, 0x8a923af2U,
            };
            HW_SCE_p_func100(Param_func073_func100_012);

            HW_SCE_p_func_sub002(0x00140023U, 0x00280005U, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001414U);
            HW_SCE_p_func_sub003(0x00c0001dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub002(0x00140005U, 0x000f0000U, 0x0404000aU);

            HW_SCE_p_func_sub019(0x000f0028U, 0x00140005U, 0x04040000U);
            HW_SCE_p_func_sub012();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub002(0x00140019U, 0x00280005U, 0x04040002U);

            HW_SCE_p_func_sub002(0x00690028U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub002(0x00280069U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_func073_func100_013[] =
            {
                0x983fe418U, 0xa81ba2cdU, 0x185a3d20U, 0x67425464U,
            };
            HW_SCE_p_func100(Param_func073_func100_013);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                static const uint32_t Param_func073_func101_020[] =
                {
                    0x011b36e9U, 0xbba2b20eU, 0x7588ab4fU, 0x64fa8feaU,
                };
                HW_SCE_p_func101(Param_func073_func101_020);
            }
            else
            {
                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0x603ce63aU);

                static const uint32_t Param_func073_func101_021[] =
                {
                    0xee2f86e6U, 0x5e9c9e4bU, 0x7a9d9cdeU, 0xcb2c5cfaU,
                };
                HW_SCE_p_func101(Param_func073_func101_021);
            }
        }
    }

    HW_SCE_p_func_sub006(0x38008800U, 0x603ce63aU, 0x00A70000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
