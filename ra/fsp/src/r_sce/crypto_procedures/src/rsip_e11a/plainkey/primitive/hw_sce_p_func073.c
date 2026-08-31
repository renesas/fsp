/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func073_r2 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    HW_SCE_p_func070_r1(ARG1);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_B8H, 0x0000000aU);

    WR1_PROG(REG_A4H, 0x04040010U);

    HW_SCE_p_func_sub017();

    WR1_PROG(REG_B0H, 0x0000141eU);
    HW_SCE_p_func_sub002(0x00c0001dU);
    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub003(0x001e000aU, 0x00140000U, 0x0404000aU);

    HW_SCE_p_func_sub003(0x00690014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub003(0x001e0069U, 0x00190000U, 0x0404000aU);
    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub003(0x006e0014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub003(0x001e006eU, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func073_func100_001[] =
    {
        0xfbd5542eU, 0x952a2feaU, 0x3c2aed29U, 0xebd14e69U,
    };
    HW_SCE_p_func100(Param_func073_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func073_func101_001[] =
        {
            0x651d3942U, 0xc81c04ccU, 0x902eba45U, 0xad8abbbeU,
        };
        HW_SCE_p_func101(Param_func073_func101_001);
    }
    else
    {
        static const uint32_t Param_func073_func100_002[] =
        {
            0x3b9fd33bU, 0x48c66d72U, 0xf7a02abfU, 0xbecc9087U,
        };
        HW_SCE_p_func100(Param_func073_func100_002);

        HW_SCE_p_func_sub003(0x001e0014U, 0x00190000U, 0x0404000aU);

        WR1_PROG(REG_B4H, 0x0019006eU);
        WR1_PROG(REG_B8H, 0x000f000aU);

        WR1_PROG(REG_A4H, 0x04040000U);
        WR1_PROG(REG_08H, 0x00020000U);
        HW_SCE_p_func_sub017();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub003(0x005a000fU, 0x0014000aU, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001423U);
        HW_SCE_p_func_sub002(0x00c00021U);

        HW_SCE_p_func_sub003(0x00230072U, 0x000f0000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x0014000fU, 0x000f000aU, 0x04040002U);

        HW_SCE_p_func_sub003(0x00140069U, 0x0032000aU, 0x04040002U);

        WR1_PROG(REG_B8H, 0x00000005U);

        WR1_PROG(REG_A4H, 0x04040010U);

        HW_SCE_p_func_sub017();

        HW_SCE_p_func_sub003(0x00230069U, 0x000a0000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x00370076U, 0x004b0005U, 0x04040002U);

        HW_SCE_p_func_sub003(0x0037007aU, 0x00500005U, 0x04040002U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub002(0x00c0001dU);
        HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub003(0x00140037U, 0x00550005U, 0x04040002U);

        HW_SCE_p_func_sub003(0x0023005fU, 0x00280000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x00230005U, 0x002d0000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x00000415U);
        HW_SCE_p_func_sub002(0x00c00009U);

        WR1_PROG(REG_B0H, 0x0000041aU);
        HW_SCE_p_func_sub002(0x00c00009U);
        HW_SCE_p_func071_r1(ARG1);

        HW_SCE_p_func_sub003(0x00230019U, 0x005a0000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x0023001eU, 0x005f0000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x00230055U, 0x00640000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x0000046fU);
        HW_SCE_p_func_sub002(0x00c00009U);

        HW_SCE_p_func_sub003(0x004b005aU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub003(0x005a004bU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub003(0x0050005fU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub003(0x005f0050U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func073_func100_003[] =
        {
            0xb9f638aaU, 0x04e724bfU, 0x6e65a466U, 0x8c39c436U,
        };
        HW_SCE_p_func100(Param_func073_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub003(0x00550064U, 0x00730005U, 0x04040013U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func073_func101_002[] =
            {
                0xe1f4ee2fU, 0x75aa3651U, 0x81aa981bU, 0x789291a9U,
            };
            HW_SCE_p_func101(Param_func073_func101_002);
        }
        else
        {
            HW_SCE_p_func_sub003(0x00000064U, 0x0073002dU, 0x04040014U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func073_func101_003[] =
            {
                0x5ea94b57U, 0x22ad553eU, 0x671034e3U, 0xbb3c21b0U,
            };
            HW_SCE_p_func101(Param_func073_func101_003);
        }

        HW_SCE_p_func_sub003(0x0023000fU, 0x00370000U, 0x04040009U);

        HW_SCE_p_func_sub003(0x00190019U, 0x00190000U, 0x0404000aU);

        HW_SCE_p_func_sub003(0x001e001eU, 0x001e0000U, 0x0404000aU);

        HW_SCE_p_func_sub003(0x00230023U, 0x00230000U, 0x0404000aU);

        WR1_PROG(REG_94H, 0x00000800U);
        for (iLoop = 0U; iLoop < 2U; iLoop++)
        {
            HW_SCE_p_func_sub006(0x000008a5U, 0x38000c00U, 0x00260000U);

            static const uint32_t Param_func073_func100_004[] =
            {
                0xa43752a7U, 0xa2546688U, 0x8a0d542cU, 0xcf0d9996U,
            };
            HW_SCE_p_func100(Param_func073_func100_004);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_B0H, 0x00000834U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000835U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x0000082fU);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);

                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000830U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);

                static const uint32_t Param_func073_func101_004[] =
                {
                    0x8910f206U, 0x80e1dc72U, 0x366bf9b2U, 0xdacd751fU,
                };
                HW_SCE_p_func101(Param_func073_func101_004);
            }
            else
            {
                WR1_PROG(REG_B0H, 0x00000836U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000837U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);
                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000831U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);

                WR1_PROG(REG_94H, 0x0000a4a0U);
                WR1_PROG(REG_94H, 0x00000008U);

                WR1_PROG(REG_B0H, 0x00000832U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub002(0x03430009U);

                static const uint32_t Param_func073_func101_005[] =
                {
                    0x6d7607cdU, 0x98e8abb4U, 0xfc2ff8aaU, 0xa29c657bU,
                };
                HW_SCE_p_func101(Param_func073_func101_005);
            }

            WR1_PROG(REG_94H, 0x00000821U);

            for (jLoop = 0U; jLoop < 4; jLoop++)
            {
                HW_SCE_p_func_sub001(0x000034a1U, 0x00026ca5U, 0x00003865U);

                HW_SCE_p_func_sub001(0x0000a4a0U, 0x00000010U, 0x00003885U);

                WR1_PROG(REG_94H, 0x00000842U);

                for (kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    HW_SCE_p_func_sub001(0x000008a5U, 0x01816ca3U, 0x01816ca4U);
                    WR1_PROG(REG_94H, 0x00016c63U);
                    WR1_PROG(REG_94H, 0x00016c84U);

                    WR1_PROG(REG_B0H, 0x00001414U);
                    HW_SCE_p_func_sub002(0x00c0001dU);
                    HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

                    HW_SCE_p_func_sub003(0x00140019U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    HW_SCE_p_func_sub003(0x00140023U, 0x000f0000U, 0x0404000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    static const uint32_t Param_func073_func100_005[] =
                    {
                        0x88c8b6a6U, 0x4d63eb4bU, 0x33560ff5U, 0xe0b8c9a2U,
                    };
                    HW_SCE_p_func100(Param_func073_func100_005);
                    WR1_PROG(REG_40H, 0x00400000U);
                    WR1_PROG(REG_24H, 0x00000000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        HW_SCE_p_func_sub003(0x00000023U, 0x0023002dU, 0x04040014U);
                        WR1_PROG(REG_40H, 0x00000d00U);

                        static const uint32_t Param_func073_func101_006[] =
                        {
                            0x9956f2deU, 0x6a52539cU, 0xbfdf3d24U, 0xe916de71U,
                        };
                        HW_SCE_p_func101(Param_func073_func101_006);
                    }
                    else
                    {
                        static const uint32_t Param_func073_func101_007[] =
                        {
                            0x4c092db6U, 0x0a2bedd0U, 0x0a03bf06U, 0x5ebf6c8fU,
                        };
                        HW_SCE_p_func101(Param_func073_func101_007);
                    }

                    HW_SCE_p_func_sub009(0x38000ca5U, 0x00A60000U);

                    static const uint32_t Param_func073_func100_006[] =
                    {
                        0xea80025cU, 0x45991c53U, 0x2ecba78eU, 0xdd390f5cU,
                    };
                    HW_SCE_p_func100(Param_func073_func100_006);
                    WR1_PROG(REG_40H, 0x00400000U);
                    WR1_PROG(REG_24H, 0x00000000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        static const uint32_t Param_func073_func100_007[] =
                        {
                            0xe3d10b80U, 0x9ef023e9U, 0x109791d7U, 0xc4026da0U,
                        };
                        HW_SCE_p_func100(Param_func073_func100_007);

                        WR1_PROG(REG_B0H, 0x00001414U);
                        HW_SCE_p_func_sub002(0x00c00021U);

                        HW_SCE_p_func_sub015(0x00007c05U, 0x00600000U);

                        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
                        {
                            HW_SCE_p_func_sub003(0x0014004bU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140050U, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140055U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_008[] =
                            {
                                0xc43ba917U, 0x84af8888U, 0x8831f1c2U, 0x7440f424U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_008);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
                        {
                            HW_SCE_p_func_sub003(0x0014005aU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x0014005fU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140064U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_009[] =
                            {
                                0xab66326cU, 0x7d082ed5U, 0xf5de9d35U, 0x9b6743e7U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_009);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
                        {
                            HW_SCE_p_func_sub003(0x00140069U, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x0014006eU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140073U, 0x00460000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_010[] =
                            {
                                0x23fde833U, 0xced2af78U, 0x694482dbU, 0x76472b23U,
                            };
                            HW_SCE_p_func101(Param_func073_func101_010);
                        }

                        WR1_PROG(REG_B0H, 0x00001414U);
                        HW_SCE_p_func_sub002(0x00c0001dU);
                        HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

                        HW_SCE_p_func_sub003(0x00140019U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        HW_SCE_p_func_sub003(0x00140023U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        static const uint32_t Param_func073_func100_008[] =
                        {
                            0x40533ebcU, 0xa810e74bU, 0xf716a1feU, 0x819c3fafU,
                        };
                        HW_SCE_p_func100(Param_func073_func100_008);
                        WR1_PROG(REG_40H, 0x00400000U);
                        WR1_PROG(REG_24H, 0x00000000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            HW_SCE_p_func_sub003(0x0014003cU, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            HW_SCE_p_func_sub003(0x00140046U, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            static const uint32_t Param_func073_func100_009[] =
                            {
                                0xe8a31908U, 0x3c354c9fU, 0xa6bafa21U, 0x2423b330U,
                            };
                            HW_SCE_p_func100(Param_func073_func100_009);
                            WR1_PROG(REG_40H, 0x00400000U);
                            WR1_PROG(REG_24H, 0x00000000U);

                            if (CHCK_STS(REG_40H, 22, 1))
                            {
                                HW_SCE_p_func_sub003(0x003c0019U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub003(0x0019003cU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub003(0x0041001eU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub003(0x001e0041U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub003(0x00460023U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub003(0x00230046U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                static const uint32_t Param_func073_func100_010[] =
                                {
                                    0x7a9e22e0U, 0xaff8a5daU, 0xbfc23596U, 0x0fb9c168U,
                                };
                                HW_SCE_p_func100(Param_func073_func100_010);
                                WR1_PROG(REG_40H, 0x00400000U);
                                WR1_PROG(REG_24H, 0x00000000U);

                                if (CHCK_STS(REG_40H, 22, 1))
                                {
                                    HW_SCE_p_func_sub003(0x00460023U, 0x00230005U, 0x04040013U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func073_func101_011[] =
                                    {
                                        0x71794b8cU, 0xd941f2ddU, 0x5049c4fcU, 0x833b78cdU,
                                    };
                                    HW_SCE_p_func101(Param_func073_func101_011);
                                }
                                else
                                {
                                    HW_SCE_p_func_sub003(0x00000023U, 0x0023002dU, 0x04040014U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func073_func101_012[] =
                                    {
                                        0x98d72b6bU, 0x79df63e6U, 0x1667b303U, 0x37819442U,
                                    };
                                    HW_SCE_p_func101(Param_func073_func101_012);
                                }
                            }
                            else
                            {
                                static const uint32_t Param_func073_func101_013[] =
                                {
                                    0xf5468a24U, 0xc5b3ff77U, 0x0927871eU, 0x89c06b74U,
                                };
                                HW_SCE_p_func101(Param_func073_func101_013);
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_B0H, 0x00001414U);
                            HW_SCE_p_func_sub002(0x00c00021U);

                            HW_SCE_p_func_sub003(0x0014003cU, 0x00190000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140041U, 0x001e0000U, 0x04040009U);

                            HW_SCE_p_func_sub003(0x00140046U, 0x00230000U, 0x04040009U);

                            static const uint32_t Param_func073_func101_014[] =
                            {
                                0x5ae9a181U, 0x7e2e7909U, 0xec792e18U, 0xd40e1b9dU,
                            };
                            HW_SCE_p_func101(Param_func073_func101_014);
                        }
                    }
                    else
                    {
                        static const uint32_t Param_func073_func101_015[] =
                        {
                            0x7cf5c949U, 0x91e3f2a0U, 0x73d62b22U, 0x71941881U,
                        };
                        HW_SCE_p_func101(Param_func073_func101_015);
                    }

                    WR1_PROG(REG_94H, 0x00002c40U);
                    static const uint32_t Param_func073_func101_016[] =
                    {
                        0xa27d3f84U, 0x1b7849eaU, 0x6087fdf4U, 0xb43d2c41U,
                    };
                    HW_SCE_p_func101(Param_func073_func101_016);
                }

                HW_SCE_p_func_sub006(0x38008840U, 0x00000020U, 0x00260000U);

                WR1_PROG(REG_40H, 0x00402000U);
                WR1_PROG(REG_24H, 0x00000000U);

                WR1_PROG(REG_94H, 0x00002c20U);

                static const uint32_t Param_func073_func101_017[] =
                {
                    0xda636b89U, 0x31b87fabU, 0xd53d97e6U, 0x09dc30fdU,
                };
                HW_SCE_p_func101(Param_func073_func101_017);
            }

            HW_SCE_p_func_sub006(0x38008820U, 0x00000004U, 0x00260000U);

            WR1_PROG(REG_40H, 0x00402000U);
            WR1_PROG(REG_24H, 0x00000000U);

            WR1_PROG(REG_94H, 0x00002c00U);

            static const uint32_t Param_func073_func101_018[] =
            {
                0x50902deeU, 0x123da2e4U, 0x04512913U, 0x0e23b620U,
            };
            HW_SCE_p_func101(Param_func073_func101_018);
        }

        HW_SCE_p_func_sub006(0x38008800U, 0x00000002U, 0x00260000U);

        WR1_PROG(REG_40H, 0x00402000U);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub002(0x00c00021U);

        HW_SCE_p_func_sub003(0x0014000aU, 0x00690000U, 0x04040009U);

        WR1_PROG(REG_B0H, 0x00001414U);
        HW_SCE_p_func_sub002(0x00c0001dU);
        HW_SCE_p_func_sub011(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub003(0x00140023U, 0x002d0000U, 0x0404000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func073_func100_011[] =
        {
            0x2de83fddU, 0x024b97f1U, 0xa2cd1e68U, 0x12fd75a9U,
        };
        HW_SCE_p_func100(Param_func073_func100_011);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            static const uint32_t Param_func073_func101_019[] =
            {
                0x239b7b4aU, 0x92f67b81U, 0x5b3d0e22U, 0x4cb80450U,
            };
            HW_SCE_p_func101(Param_func073_func101_019);
        }
        else
        {
            static const uint32_t Param_func073_func100_012[] =
            {
                0xf6c7fccfU, 0x8a1a0839U, 0x69276465U, 0x2439f328U,
            };
            HW_SCE_p_func100(Param_func073_func100_012);

            HW_SCE_p_func_sub003(0x00140023U, 0x00280005U, 0x04040002U);

            WR1_PROG(REG_B0H, 0x00001414U);
            HW_SCE_p_func_sub002(0x00c0001dU);
            HW_SCE_p_func_sub011(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub003(0x00140005U, 0x000f0000U, 0x0404000aU);

            WR1_PROG(REG_B4H, 0x000f0028U);
            WR1_PROG(REG_B8H, 0x00140005U);

            WR1_PROG(REG_A4H, 0x04040000U);
            WR1_PROG(REG_08H, 0x00020000U);
            HW_SCE_p_func_sub017();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub003(0x00140019U, 0x00280005U, 0x04040002U);

            HW_SCE_p_func_sub003(0x00690028U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub003(0x00280069U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_func073_func100_013[] =
            {
                0x6e113c0bU, 0x2804d393U, 0x4dffb453U, 0xd4f86295U,
            };
            HW_SCE_p_func100(Param_func073_func100_013);
            WR1_PROG(REG_40H, 0x00400000U);
            WR1_PROG(REG_24H, 0x00000000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                static const uint32_t Param_func073_func101_020[] =
                {
                    0x36421426U, 0x457d8fc9U, 0x445ca6d4U, 0x053f92abU,
                };
                HW_SCE_p_func101(Param_func073_func101_020);
            }
            else
            {
                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0x740d7282U);

                static const uint32_t Param_func073_func101_021[] =
                {
                    0xa8a4d3bfU, 0xf6ddc9c4U, 0x80a14770U, 0xd0dac480U,
                };
                HW_SCE_p_func101(Param_func073_func101_021);
            }
        }
    }

    HW_SCE_p_func_sub006(0x38008800U, 0x740d7282U, 0x00A60000U);

    HW_SCE_p_func_sub015(0x00007c07U, 0x00602000U);
}
