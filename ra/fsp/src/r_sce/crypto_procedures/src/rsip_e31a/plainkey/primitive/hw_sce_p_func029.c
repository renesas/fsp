/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func029 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    HW_SCE_p_func027(ARG1);

    WR1_PROG(REG_A0H, 0x20010000U);

    WR1_PROG(REG_B8H, 0x0000000eU);

    WR1_PROG(REG_A4H, 0x06060010U);

    HW_SCE_p_func_sub012();

    WR1_PROG(REG_B0H, 0x0000942aU);
    HW_SCE_p_func_sub003(0x00c0002dU);
    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

    HW_SCE_p_func_sub002(0x002a000eU, 0x001c0000U, 0x0606000aU);

    HW_SCE_p_func_sub002(0x0093001cU, 0x00230000U, 0x0606000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x002a0093U, 0x00230000U, 0x0606000aU);
    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x009a001cU, 0x00230000U, 0x0606000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    HW_SCE_p_func_sub002(0x002a009aU, 0x00230000U, 0x0606000aU);

    WR1_PROG(REG_40H, 0x00210000U);

    static const uint32_t Param_func029_func100_001[] =
    {
        0x34aa358aU, 0x47257611U, 0xb44c50bdU, 0xff627c1fU,
    };
    HW_SCE_p_func100(Param_func029_func100_001);
    WR1_PROG(REG_40H, 0x00400000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        WR1_PROG(REG_94H, 0x00000800U);

        static const uint32_t Param_func029_func101_001[] =
        {
            0xaa898cbdU, 0x3431e6bbU, 0x15ec3eacU, 0x9a824f7fU,
        };
        HW_SCE_p_func101(Param_func029_func101_001);
    }
    else
    {
        static const uint32_t Param_func029_func100_002[] =
        {
            0x3d885ae5U, 0x80246c31U, 0xfe880014U, 0x0ecd1ffcU,
        };
        HW_SCE_p_func100(Param_func029_func100_002);

        HW_SCE_p_func_sub002(0x002a001cU, 0x00230000U, 0x0606000aU);

        HW_SCE_p_func_sub019(0x0023009aU, 0x0015000eU, 0x06060000U);
        HW_SCE_p_func_sub012();
        WR1_PROG(REG_40H, 0x00000d00U);

        HW_SCE_p_func_sub002(0x007e0015U, 0x001c000eU, 0x06060002U);

        WR1_PROG(REG_B0H, 0x00009431U);
        HW_SCE_p_func_sub003(0x00c00031U);

        HW_SCE_p_func_sub002(0x003100a1U, 0x00150000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x001c0015U, 0x0015000eU, 0x06060002U);

        HW_SCE_p_func_sub002(0x001c0093U, 0x0046000eU, 0x06060002U);

        WR1_PROG(REG_B8H, 0x00000007U);

        WR1_PROG(REG_A4H, 0x06060010U);

        HW_SCE_p_func_sub012();

        HW_SCE_p_func_sub002(0x00310093U, 0x000e0000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x004d00a7U, 0x00690007U, 0x06060002U);

        HW_SCE_p_func_sub002(0x004d00adU, 0x00700007U, 0x06060002U);

        WR1_PROG(REG_B0H, 0x0000941cU);
        HW_SCE_p_func_sub003(0x00c0002dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x001c004dU, 0x00770007U, 0x06060002U);

        HW_SCE_p_func_sub002(0x00310085U, 0x00380000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x00310007U, 0x003f0000U, 0x06060009U);

        WR1_PROG(REG_B0H, 0x0000041dU);
        HW_SCE_p_func_sub003(0x00c00009U);

        WR1_PROG(REG_B0H, 0x00000424U);
        HW_SCE_p_func_sub003(0x00c00009U);
        HW_SCE_p_func028(ARG1);

        HW_SCE_p_func_sub002(0x00310023U, 0x007e0000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x0031002aU, 0x00850000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x00310077U, 0x008c0000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x0069007eU, 0x001c0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x007e0069U, 0x001c0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x00700085U, 0x001c0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        HW_SCE_p_func_sub002(0x00850070U, 0x001c0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func029_func100_003[] =
        {
            0xae8c0d0aU, 0x550fbccbU, 0x92ee8d89U, 0xfcf8a9cfU,
        };
        HW_SCE_p_func100(Param_func029_func100_003);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func_sub002(0x0077008cU, 0x00a10007U, 0x06060013U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func029_func101_002[] =
            {
                0x3c27da52U, 0x8e369cbcU, 0xf716cdb8U, 0x24c6be0fU,
            };
            HW_SCE_p_func101(Param_func029_func101_002);
        }
        else
        {
            HW_SCE_p_func_sub002(0x0000008cU, 0x00a1003fU, 0x06060014U);
            WR1_PROG(REG_40H, 0x00000d00U);

            static const uint32_t Param_func029_func101_003[] =
            {
                0x51bad22dU, 0xefc8f6b9U, 0xfb605b6fU, 0xd2536dc6U,
            };
            HW_SCE_p_func101(Param_func029_func101_003);
        }

        HW_SCE_p_func_sub002(0x00310015U, 0x004d0000U, 0x06060009U);

        HW_SCE_p_func_sub002(0x00230023U, 0x00230000U, 0x0606000aU);

        HW_SCE_p_func_sub002(0x002a002aU, 0x002a0000U, 0x0606000aU);

        HW_SCE_p_func_sub002(0x00310031U, 0x00310000U, 0x0606000aU);

        WR1_PROG(REG_94H, 0x00000800U);
        for (iLoop = 0U; iLoop < 3U; iLoop++)
        {
            static const uint32_t Param_func029_func100_004[] =
            {
                0x57b9fe79U, 0xf7e66d87U, 0xf3c4b394U, 0x8415e691U,
            };
            HW_SCE_p_func100(Param_func029_func100_004);
            WR1_PROG(REG_94H, 0x000008a5U);

            WR1_PROG(REG_94H, 0x00007c00U);
            WR1_PROG(REG_40H, 0x00600000U);

            if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
            {
                WR1_PROG(REG_B0H, 0x00000848U);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000849U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000841U);
                HW_SCE_p_func_sub003(0x03430009U);

                HW_SCE_p_func_sub014(0x00000842U);
                HW_SCE_p_func_sub003(0x03430009U);

                static const uint32_t Param_func029_func101_004[] =
                {
                    0x48c05735U, 0xc87c580cU, 0xbdf3e0c2U, 0xfed8e76bU,
                };
                HW_SCE_p_func101(Param_func029_func101_004);
            }
            else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
            {
                WR1_PROG(REG_B0H, 0x0000084aU);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x0000084bU);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000843U);
                HW_SCE_p_func_sub003(0x03430009U);

                HW_SCE_p_func_sub014(0x00000844U);
                HW_SCE_p_func_sub003(0x03430009U);

                static const uint32_t Param_func029_func101_005[] =
                {
                    0xe327f8d1U, 0x683c6319U, 0x9c3082ddU, 0xbf8b9130U,
                };
                HW_SCE_p_func101(Param_func029_func101_005);
            }
            else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
            {
                WR1_PROG(REG_B0H, 0x0000084cU);
                WR1_PROG(REG_9CH, 0x80820005U);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x0000084dU);
                HW_SCE_p_func_sub003(0x03430009U);
                HW_SCE_p_func_sub014(0x00000845U);
                HW_SCE_p_func_sub003(0x03430009U);

                HW_SCE_p_func_sub014(0x00000846U);
                HW_SCE_p_func_sub003(0x03430009U);

                static const uint32_t Param_func029_func101_006[] =
                {
                    0xf5b378c6U, 0xe823263dU, 0x15220f4eU, 0x49fb67b7U,
                };
                HW_SCE_p_func101(Param_func029_func101_006);
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

                    WR1_PROG(REG_B0H, 0x0000941cU);
                    HW_SCE_p_func_sub003(0x00c0002dU);
                    HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                    HW_SCE_p_func_sub002(0x001c0023U, 0x00150000U, 0x0606000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    HW_SCE_p_func_sub002(0x001c0031U, 0x00150000U, 0x0606000aU);

                    WR1_PROG(REG_40H, 0x00a10000U);

                    static const uint32_t Param_func029_func100_005[] =
                    {
                        0x1fb9527cU, 0xb9f356b0U, 0xbc174347U, 0x774aecdcU,
                    };
                    HW_SCE_p_func100(Param_func029_func100_005);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        HW_SCE_p_func_sub002(0x00000031U, 0x0031003fU, 0x06060014U);
                        WR1_PROG(REG_40H, 0x00000d00U);

                        static const uint32_t Param_func029_func101_007[] =
                        {
                            0xce8288feU, 0x62833eb0U, 0xc7438ff5U, 0xcfdd26cbU,
                        };
                        HW_SCE_p_func101(Param_func029_func101_007);
                    }
                    else
                    {
                        static const uint32_t Param_func029_func101_008[] =
                        {
                            0x460e3fcfU, 0x668d2faaU, 0x00df380dU, 0x10bb5661U,
                        };
                        HW_SCE_p_func101(Param_func029_func101_008);
                    }

                    HW_SCE_p_func_sub010(0x38000ca5U, 0x00A70000U);

                    static const uint32_t Param_func029_func100_006[] =
                    {
                        0x053f4fccU, 0x08691833U, 0xb9737c14U, 0x42e32737U,
                    };
                    HW_SCE_p_func100(Param_func029_func100_006);
                    WR1_PROG(REG_40H, 0x00400000U);

                    if (CHCK_STS(REG_40H, 22, 1))
                    {
                        static const uint32_t Param_func029_func100_007[] =
                        {
                            0xea6588ecU, 0x82205472U, 0xf0d56107U, 0x401467b8U,
                        };
                        HW_SCE_p_func100(Param_func029_func100_007);

                        WR1_PROG(REG_B0H, 0x0000941cU);
                        HW_SCE_p_func_sub003(0x00c00031U);

                        WR1_PROG(REG_94H, 0x00007c05U);
                        WR1_PROG(REG_40H, 0x00600000U);

                        if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
                        {
                            HW_SCE_p_func_sub002(0x001c0069U, 0x00540000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c0070U, 0x005b0000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c0077U, 0x00620000U, 0x06060009U);

                            static const uint32_t Param_func029_func101_009[] =
                            {
                                0x4bd84b01U, 0x57491317U, 0xb415751cU, 0xe1023aa9U,
                            };
                            HW_SCE_p_func101(Param_func029_func101_009);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
                        {
                            HW_SCE_p_func_sub002(0x001c007eU, 0x00540000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c0085U, 0x005b0000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c008cU, 0x00620000U, 0x06060009U);

                            static const uint32_t Param_func029_func101_010[] =
                            {
                                0x608f8db1U, 0xe5844129U, 0x837aef6bU, 0x83851d45U,
                            };
                            HW_SCE_p_func101(Param_func029_func101_010);
                        }
                        else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
                        {
                            HW_SCE_p_func_sub002(0x001c0093U, 0x00540000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c009aU, 0x005b0000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c00a1U, 0x00620000U, 0x06060009U);

                            static const uint32_t Param_func029_func101_011[] =
                            {
                                0xe96c416dU, 0x3d6a3462U, 0xba47b21dU, 0xcf8fc29fU,
                            };
                            HW_SCE_p_func101(Param_func029_func101_011);
                        }

                        WR1_PROG(REG_B0H, 0x0000941cU);
                        HW_SCE_p_func_sub003(0x00c0002dU);
                        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

                        HW_SCE_p_func_sub002(0x001c0023U, 0x00150000U, 0x0606000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        HW_SCE_p_func_sub002(0x001c0031U, 0x00150000U, 0x0606000aU);

                        WR1_PROG(REG_40H, 0x00a10000U);

                        static const uint32_t Param_func029_func100_008[] =
                        {
                            0xd1508e24U, 0x9e120a82U, 0x1a67e095U, 0x47d3a1d6U,
                        };
                        HW_SCE_p_func100(Param_func029_func100_008);
                        WR1_PROG(REG_40H, 0x00400000U);

                        if (CHCK_STS(REG_40H, 22, 1))
                        {
                            HW_SCE_p_func_sub002(0x001c0054U, 0x00150000U, 0x0606000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            HW_SCE_p_func_sub002(0x001c0062U, 0x00150000U, 0x0606000aU);

                            WR1_PROG(REG_40H, 0x00a10000U);

                            static const uint32_t Param_func029_func100_009[] =
                            {
                                0x68d35b16U, 0xc8b8bbecU, 0x96334301U, 0x07b2043eU,
                            };
                            HW_SCE_p_func100(Param_func029_func100_009);
                            WR1_PROG(REG_40H, 0x00400000U);

                            if (CHCK_STS(REG_40H, 22, 1))
                            {
                                HW_SCE_p_func_sub002(0x00540023U, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x00230054U, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x005b002aU, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x002a005bU, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x00620031U, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                HW_SCE_p_func_sub002(0x00310062U, 0x00150000U, 0x0606000aU);

                                WR1_PROG(REG_40H, 0x00210000U);

                                static const uint32_t Param_func029_func100_010[] =
                                {
                                    0x80c67986U, 0x5e4be63bU, 0x9a2fff3bU, 0x6f826539U,
                                };
                                HW_SCE_p_func100(Param_func029_func100_010);
                                WR1_PROG(REG_40H, 0x00400000U);

                                if (CHCK_STS(REG_40H, 22, 1))
                                {
                                    HW_SCE_p_func_sub002(0x00620031U, 0x00310007U, 0x06060013U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func029_func101_012[] =
                                    {
                                        0xc0eb732eU, 0x36d92ee1U, 0x9edea470U, 0x73b454d0U,
                                    };
                                    HW_SCE_p_func101(Param_func029_func101_012);
                                }
                                else
                                {
                                    HW_SCE_p_func_sub002(0x00000031U, 0x0031003fU, 0x06060014U);
                                    WR1_PROG(REG_40H, 0x00000d00U);

                                    static const uint32_t Param_func029_func101_013[] =
                                    {
                                        0xdfc04404U, 0xb9c3c7daU, 0xd9ed2348U, 0x6afeb2a2U,
                                    };
                                    HW_SCE_p_func101(Param_func029_func101_013);
                                }
                            }
                            else
                            {
                                static const uint32_t Param_func029_func101_014[] =
                                {
                                    0x6bf085ffU, 0x8df4a3ceU, 0x928a49d6U, 0x825dc563U,
                                };
                                HW_SCE_p_func101(Param_func029_func101_014);
                            }
                        }
                        else
                        {
                            WR1_PROG(REG_B0H, 0x0000941cU);
                            HW_SCE_p_func_sub003(0x00c00031U);

                            HW_SCE_p_func_sub002(0x001c0054U, 0x00230000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c005bU, 0x002a0000U, 0x06060009U);

                            HW_SCE_p_func_sub002(0x001c0062U, 0x00310000U, 0x06060009U);

                            static const uint32_t Param_func029_func101_015[] =
                            {
                                0x5d379656U, 0x94d1a644U, 0xc542ca87U, 0x1f4f27abU,
                            };
                            HW_SCE_p_func101(Param_func029_func101_015);
                        }
                    }
                    else
                    {
                        static const uint32_t Param_func029_func101_016[] =
                        {
                            0x5ad56351U, 0xce2c6b6fU, 0x900d1caeU, 0xc423f070U,
                        };
                        HW_SCE_p_func101(Param_func029_func101_016);
                    }

                    WR1_PROG(REG_94H, 0x00002c40U);
                    static const uint32_t Param_func029_func101_017[] =
                    {
                        0xf074be13U, 0x1a9d932cU, 0x6f1f7adbU, 0x3ef01905U,
                    };
                    HW_SCE_p_func101(Param_func029_func101_017);
                }

                HW_SCE_p_func_sub006(0x38008840U, 0x00000020U, 0x00270000U);

                WR1_PROG(REG_40H, 0x00402000U);

                WR1_PROG(REG_94H, 0x00002c20U);

                static const uint32_t Param_func029_func101_018[] =
                {
                    0x09d85d55U, 0x92441481U, 0xb491b2bfU, 0x8b2158f9U,
                };
                HW_SCE_p_func101(Param_func029_func101_018);
            }

            HW_SCE_p_func_sub006(0x38008820U, 0x00000004U, 0x00270000U);

            WR1_PROG(REG_40H, 0x00402000U);

            WR1_PROG(REG_94H, 0x00002c00U);

            static const uint32_t Param_func029_func101_019[] =
            {
                0x3d0b2078U, 0x2f6ef02dU, 0x645e81fcU, 0xacb1a2d5U,
            };
            HW_SCE_p_func101(Param_func029_func101_019);
        }

        HW_SCE_p_func_sub006(0x38008800U, 0x00000003U, 0x00270000U);

        WR1_PROG(REG_40H, 0x00402000U);

        WR1_PROG(REG_B0H, 0x0000941cU);
        HW_SCE_p_func_sub003(0x00c00031U);

        HW_SCE_p_func_sub002(0x001c000eU, 0x00930000U, 0x06060009U);

        WR1_PROG(REG_B0H, 0x0000941cU);
        HW_SCE_p_func_sub003(0x00c0002dU);
        HW_SCE_p_func_sub008(0x000000a5U, 0x00000001U);

        HW_SCE_p_func_sub002(0x001c0031U, 0x003f0000U, 0x0606000aU);

        WR1_PROG(REG_40H, 0x00210000U);

        static const uint32_t Param_func029_func100_011[] =
        {
            0x0e8cc8d9U, 0x1ecdff62U, 0x058e6c05U, 0xcc72fcdfU,
        };
        HW_SCE_p_func100(Param_func029_func100_011);
        WR1_PROG(REG_40H, 0x00400000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            WR1_PROG(REG_94H, 0x00000800U);

            static const uint32_t Param_func029_func101_020[] =
            {
                0xe6afdcd2U, 0xea572cf4U, 0xf8cde08cU, 0x24db89faU,
            };
            HW_SCE_p_func101(Param_func029_func101_020);
        }
        else
        {
            static const uint32_t Param_func029_func100_012[] =
            {
                0x038fa21fU, 0xa3d0256aU, 0x7558a36bU, 0x3b7e8752U,
            };
            HW_SCE_p_func100(Param_func029_func100_012);

            HW_SCE_p_func_sub002(0x001c0031U, 0x00380007U, 0x06060002U);

            WR1_PROG(REG_B0H, 0x0000941cU);
            HW_SCE_p_func_sub003(0x00c0002dU);
            HW_SCE_p_func_sub008(0x000000a5U, 0x00000002U);

            HW_SCE_p_func_sub002(0x001c0007U, 0x00150000U, 0x0606000aU);

            HW_SCE_p_func_sub019(0x00150038U, 0x001c0007U, 0x06060000U);
            HW_SCE_p_func_sub012();
            WR1_PROG(REG_40H, 0x00000d00U);

            HW_SCE_p_func_sub002(0x001c0023U, 0x00380007U, 0x06060002U);

            HW_SCE_p_func_sub002(0x00930038U, 0x00230000U, 0x0606000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            HW_SCE_p_func_sub002(0x00380093U, 0x00230000U, 0x0606000aU);

            WR1_PROG(REG_40H, 0x00210000U);

            static const uint32_t Param_func029_func100_013[] =
            {
                0xdf6b9bc7U, 0xe03a92e2U, 0xcc1628b5U, 0x03916ac6U,
            };
            HW_SCE_p_func100(Param_func029_func100_013);
            WR1_PROG(REG_40H, 0x00400000U);

            if (CHCK_STS(REG_40H, 22, 1))
            {
                WR1_PROG(REG_94H, 0x00000800U);

                static const uint32_t Param_func029_func101_021[] =
                {
                    0x7ca5d7d6U, 0x017eafc2U, 0xbe16f328U, 0x332e8f8fU,
                };
                HW_SCE_p_func101(Param_func029_func101_021);
            }
            else
            {
                WR1_PROG(REG_94H, 0x0000b400U);
                WR1_PROG(REG_94H, 0xf639e4adU);

                static const uint32_t Param_func029_func101_022[] =
                {
                    0xe4386590U, 0x364de709U, 0xe4d03fd5U, 0x7b5927dcU,
                };
                HW_SCE_p_func101(Param_func029_func101_022);
            }
        }
    }

    HW_SCE_p_func_sub006(0x38008800U, 0xf639e4adU, 0x00A70000U);

    WR1_PROG(REG_94H, 0x00007c07U);
    WR1_PROG(REG_40H, 0x00602000U);
}
