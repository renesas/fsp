/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func324 (void)
{
    uint32_t iLoop  = 0U;
    uint32_t oLoop1 = 0U;

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x00000004U);
    WR1_PROG(REG_ECH, 0x00003fbeU);

    static const uint32_t Param_func324_func100_001[] =
    {
        0xba800165U, 0x9d0773f6U, 0xc404520bU, 0x64890201U,
    };
    HW_SCE_p_func100(Param_func324_func100_001);
    WR1_PROG(REG_28H, 0x00bf0001U);

    HW_SCE_p_func_sub020(0x009f0001U, 0x000005c0U, 0x000060c1U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000040c1U, 0x019410dfU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_002[] =
    {
        0xd5fc2c48U, 0x3ee36e03U, 0x5d0a4911U, 0x3a0bf64dU,
    };
    HW_SCE_p_func100(Param_func324_func100_002);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func320(680);

    HW_SCE_p_func_sub009(0x80010020U, 0x010273a4U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_003[] =
    {
        0x8b104378U, 0x5c4821e6U, 0xd5ad0910U, 0x350a2659U,
    };
    HW_SCE_p_func100(Param_func324_func100_003);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000015U);
    HW_SCE_p_func320(716);

    HW_SCE_p_func_sub004(0x0000a0c1U, 0x018e0c4cU);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func320(752);

    HW_SCE_p_func_sub020(0x00bf0001U, 0x000001c0U, 0x04001991U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x060049c1U);
    HW_SCE_p_func_sub017(0x02001191U, 0x00210000U);

    oLoop1 = 1;
    while (oLoop1 == 1)
    {
        static const uint32_t Param_func324_func100_004[] =
        {
            0xf53e35c6U, 0xd82158c6U, 0xb88968fcU, 0xc7b36f20U,
        };
        HW_SCE_p_func100(Param_func324_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_func324_func101_001[] =
            {
                0x905bfec7U, 0x34f45708U, 0x8a2c63ffU, 0x0f52cc31U,
            };
            HW_SCE_p_func101(Param_func324_func101_001);
            oLoop1 = 0;
        }
        else
        {
            HW_SCE_p_func_sub023(0x000049c1U, 0x04001991U);

            WR1_PROG(REG_24H, 0x060049c1U);
            HW_SCE_p_func_sub017(0x02001191U, 0x00210000U);

            static const uint32_t Param_func324_func101_002[] =
            {
                0x6fd622f4U, 0xc5c30bdbU, 0x97754975U, 0xabab04e2U,
            };
            HW_SCE_p_func101(Param_func324_func101_002);
        }
    }

    static const uint32_t Param_func324_func100_005[] =
    {
        0x21bbb393U, 0xcd9f14a3U, 0x26a0865fU, 0x7ab63a5fU,
    };
    HW_SCE_p_func100(Param_func324_func100_005);
    HW_SCE_p_func_sub023(0x000049c1U, 0x04001981U);
    HW_SCE_p_func_sub023(0x060049c1U, 0x02001181U);

    HW_SCE_p_func_sub008(0x009f0001U, 0x01ef2f1cU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_006[] =
    {
        0xfc6ff514U, 0xa79a0df4U, 0x7e3fac51U, 0x4283d461U,
    };
    HW_SCE_p_func100(Param_func324_func100_006);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(136);

    static const uint32_t Param_func324_func100_007[] =
    {
        0x94f25a99U, 0xdcf9f94bU, 0xcc235501U, 0x569b42ddU,
    };
    HW_SCE_p_func100(Param_func324_func100_007);
    HW_SCE_p_func314(136 + 32);

    static const uint32_t Param_func324_func100_008[] =
    {
        0xc3c50340U, 0x1fed1a99U, 0xc269950cU, 0xe7766b8eU,
    };
    HW_SCE_p_func100(Param_func324_func100_008);
    HW_SCE_p_func_sub009(0x80010020U, 0x012e06e6U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_009[] =
    {
        0x8cebb57cU, 0x04b0382fU, 0x60452136U, 0xde3445a7U,
    };
    HW_SCE_p_func100(Param_func324_func100_009);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(172);

    static const uint32_t Param_func324_func100_010[] =
    {
        0xf53e25d8U, 0x61d4a5ceU, 0xd3c4952aU, 0x9acca047U,
    };
    HW_SCE_p_func100(Param_func324_func100_010);
    HW_SCE_p_func314(172 + 32);

    static const uint32_t Param_func324_func100_011[] =
    {
        0xb8a00ca9U, 0x28cfa0d8U, 0x81dd7ba0U, 0xa28e4d9fU,
    };
    HW_SCE_p_func100(Param_func324_func100_011);
    WR1_PROG(REG_28H, 0x00bf0001U);
    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub008(0x009f0001U, 0x0100abe1U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_012[] =
    {
        0x6f9aab8fU, 0xabe2fdc1U, 0xd809f527U, 0x5f0cfc44U,
    };
    HW_SCE_p_func100(Param_func324_func100_012);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(208);

    static const uint32_t Param_func324_func100_013[] =
    {
        0x85986bc9U, 0xdfec6f9fU, 0xd0187c6dU, 0x35b96576U,
    };
    HW_SCE_p_func100(Param_func324_func100_013);
    HW_SCE_p_func314(208 + 32);
    WR1_PROG(REG_28H, 0x00bf0001U);
    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000a52U);

    for (iLoop = 0U; iLoop < 128U; iLoop++)
    {
        static const uint32_t Param_func324_func100_014[] =
        {
            0x676328e0U, 0x613dcc15U, 0xb5174525U, 0x35e75a6fU,
        };
        HW_SCE_p_func100(Param_func324_func100_014);

        HW_SCE_p_func_sub023(0x040049c1U, 0x04000149U);

        HW_SCE_p_func_sub023(0x060049c1U, 0x0400d0d0U);
        WR1_PROG(REG_24H, 0x02000149U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub008(0x009f0001U, 0x019410dfU);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_015[] =
        {
            0x23195e77U, 0x97f9f9e3U, 0x3a294c80U, 0x21a31b5fU,
        };
        HW_SCE_p_func100(Param_func324_func100_015);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func320(680);

        HW_SCE_p_func_sub009(0x80010020U, 0x010273a4U);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000015U);
        HW_SCE_p_func320(716);

        WR1_PROG(REG_28H, 0x00bf0001U);

        WR1_PROG(REG_ECH, 0x00002e40U);

        static const uint32_t Param_func324_func101_003[] =
        {
            0xe6f2fb13U, 0x44ac6782U, 0xacacfa2cU, 0xc6ce06baU,
        };
        HW_SCE_p_func101(Param_func324_func101_003);
    }

    HW_SCE_p_func_sub014(0x38008a40U, 0x00000080U, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    static const uint32_t Param_func324_func100_016[] =
    {
        0xdff19989U, 0xed86b6e4U, 0x810692d1U, 0x4054ba1fU,
    };
    HW_SCE_p_func100(Param_func324_func100_016);
    HW_SCE_p_func_sub023(0x040049c1U, 0x040019a1U);
    HW_SCE_p_func_sub023(0x060049c1U, 0x0400d0d0U);
    WR1_PROG(REG_24H, 0x020019a1U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub008(0x009f0001U, 0x019410dfU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_017[] =
    {
        0xb252e8f6U, 0xa305ef14U, 0xae64b69aU, 0x585821f5U,
    };
    HW_SCE_p_func100(Param_func324_func100_017);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func320(680);

    HW_SCE_p_func_sub009(0x80010020U, 0x010273a4U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_018[] =
    {
        0xe3ac09b8U, 0xed2ade8eU, 0x09e0d6a0U, 0x53c92617U,
    };
    HW_SCE_p_func100(Param_func324_func100_018);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000015U);
    HW_SCE_p_func320(716);

    WR1_PROG(REG_28H, 0x00bf0001U);
    HW_SCE_p_func_sub008(0x009f0001U, 0x011af8f9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_019[] =
    {
        0x4a733c3dU, 0x2b978923U, 0xc70ac96aU, 0xf892a403U,
    };
    HW_SCE_p_func100(Param_func324_func100_019);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(408);

    static const uint32_t Param_func324_func100_020[] =
    {
        0x6a895ce5U, 0x6c42347fU, 0x214cfe83U, 0x59e7049eU,
    };
    HW_SCE_p_func100(Param_func324_func100_020);
    HW_SCE_p_func314(408 + 32);

    static const uint32_t Param_func324_func100_021[] =
    {
        0xdea06f25U, 0x53d8df33U, 0x9c88cf0eU, 0x67a0090aU,
    };
    HW_SCE_p_func100(Param_func324_func100_021);
    HW_SCE_p_func_sub009(0x80010020U, 0x0130aeffU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_022[] =
    {
        0xbf3bc416U, 0x136f6b3eU, 0xacf5f90fU, 0x3425f707U,
    };
    HW_SCE_p_func100(Param_func324_func100_022);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(444);

    static const uint32_t Param_func324_func100_023[] =
    {
        0x1c85df96U, 0x3d70a07dU, 0x430218bcU, 0xb738452dU,
    };
    HW_SCE_p_func100(Param_func324_func100_023);
    HW_SCE_p_func314(444 + 32);

    static const uint32_t Param_func324_func100_024[] =
    {
        0x4894e0eaU, 0x1ed6fd66U, 0x44c98fa9U, 0x93476849U,
    };
    HW_SCE_p_func100(Param_func324_func100_024);
    HW_SCE_p_func_sub009(0x80010020U, 0x01574730U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_025[] =
    {
        0x27653520U, 0xaf747027U, 0xdc554257U, 0xf7ab9d4bU,
    };
    HW_SCE_p_func100(Param_func324_func100_025);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(544);

    static const uint32_t Param_func324_func100_026[] =
    {
        0x799b94d4U, 0xc20a7cd7U, 0x9cca7baaU, 0x7cb589a4U,
    };
    HW_SCE_p_func100(Param_func324_func100_026);
    HW_SCE_p_func314(544 + 32);

    static const uint32_t Param_func324_func100_027[] =
    {
        0x88fb9181U, 0xb55c73deU, 0x7d7588f0U, 0xf5f0778cU,
    };
    HW_SCE_p_func100(Param_func324_func100_027);
    HW_SCE_p_func_sub009(0x80010020U, 0x01f11123U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_028[] =
    {
        0xf3a6d287U, 0xc0bae19aU, 0x4a678488U, 0x782770a3U,
    };
    HW_SCE_p_func100(Param_func324_func100_028);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(580);

    static const uint32_t Param_func324_func100_029[] =
    {
        0x713444a7U, 0xc18c9532U, 0x50c8e298U, 0x48490351U,
    };
    HW_SCE_p_func100(Param_func324_func100_029);
    HW_SCE_p_func314(580 + 32);

    static const uint32_t Param_func324_func100_030[] =
    {
        0xc516255bU, 0xc4f1442cU, 0xe9885d55U, 0xb986eeb2U,
    };
    HW_SCE_p_func100(Param_func324_func100_030);
    WR1_PROG(REG_28H, 0x00bf0001U);
    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub008(0x009f0001U, 0x010964eaU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_031[] =
    {
        0x54c6a527U, 0x13c8e927U, 0xb44ce6aaU, 0xeb9e9d3fU,
    };
    HW_SCE_p_func100(Param_func324_func100_031);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(480);

    static const uint32_t Param_func324_func100_032[] =
    {
        0x265120a7U, 0x73fc5c2eU, 0xef24e3f8U, 0x4fbcfaadU,
    };
    HW_SCE_p_func100(Param_func324_func100_032);
    HW_SCE_p_func314(480 + 32);

    static const uint32_t Param_func324_func100_033[] =
    {
        0x61f0fe5eU, 0x0f4cbddfU, 0x1ad3a9e8U, 0x1a0d7668U,
    };
    HW_SCE_p_func100(Param_func324_func100_033);
    HW_SCE_p_func_sub009(0x80010020U, 0x01ac62c9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_034[] =
    {
        0x7be00fceU, 0x9aeb3edeU, 0x25026ce9U, 0xc2d0db59U,
    };
    HW_SCE_p_func100(Param_func324_func100_034);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(616);

    static const uint32_t Param_func324_func100_035[] =
    {
        0x73a48fa9U, 0x38d334c0U, 0xadf63b4dU, 0xf330a5ccU,
    };
    HW_SCE_p_func100(Param_func324_func100_035);
    HW_SCE_p_func314(616 + 32);

    WR1_PROG(REG_ECH, 0x00000a52U);

    for (iLoop = 0U; iLoop < 3U; iLoop++)
    {
        WR1_PROG(REG_ECH, 0x0000b7a0U);
        WR1_PROG(REG_ECH, 0x000000f0U);
        static const uint32_t Param_func324_func101_004[] =
        {
            0x20fa9c73U, 0xbbf1986dU, 0x9bfb0b9dU, 0x272b4a9eU,
        };
        HW_SCE_p_func101(Param_func324_func101_004);
        HW_SCE_p_func318();

        static const uint32_t Param_func324_func100_036[] =
        {
            0x91e54cabU, 0xdaa2840bU, 0xe523dc34U, 0x667f6b46U,
        };
        HW_SCE_p_func100(Param_func324_func100_036);
        HW_SCE_p_func_sub008(0x009f0001U, 0x011af8f9U);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_037[] =
        {
            0xb669ddffU, 0xc3ef8260U, 0x5350ad91U, 0x9fa7b544U,
        };
        HW_SCE_p_func100(Param_func324_func100_037);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func319(408);

        static const uint32_t Param_func324_func100_038[] =
        {
            0x147c2639U, 0x9cc02970U, 0x583dd0dbU, 0x528abff7U,
        };
        HW_SCE_p_func100(Param_func324_func100_038);
        HW_SCE_p_func314(408 + 32);

        static const uint32_t Param_func324_func100_039[] =
        {
            0x1714ce33U, 0x4aad3236U, 0x7b544d55U, 0xd9609333U,
        };
        HW_SCE_p_func100(Param_func324_func100_039);
        HW_SCE_p_func_sub009(0x80010020U, 0x0130aeffU);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_040[] =
        {
            0x1cd470e5U, 0x633c9ff4U, 0x1cdcb115U, 0x26eda65cU,
        };
        HW_SCE_p_func100(Param_func324_func100_040);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000023U);
        HW_SCE_p_func319(444);

        static const uint32_t Param_func324_func100_041[] =
        {
            0xb9364cc7U, 0xbefc7673U, 0x0e7a2b28U, 0x2ad0bb86U,
        };
        HW_SCE_p_func100(Param_func324_func100_041);
        HW_SCE_p_func314(444 + 32);

        static const uint32_t Param_func324_func100_042[] =
        {
            0x51f70bf0U, 0x01fd1d85U, 0x88cd7d7aU, 0xc11c13c1U,
        };
        HW_SCE_p_func100(Param_func324_func100_042);
        HW_SCE_p_func_sub009(0x80010020U, 0x010964eaU);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_043[] =
        {
            0x859aa5c9U, 0x89c173aeU, 0x7aab7a3eU, 0x4bd05495U,
        };
        HW_SCE_p_func100(Param_func324_func100_043);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func319(480);

        static const uint32_t Param_func324_func100_044[] =
        {
            0xa64744e4U, 0xa6a5a5c4U, 0x6f2d5dc6U, 0x2fe1048eU,
        };
        HW_SCE_p_func100(Param_func324_func100_044);
        HW_SCE_p_func314(480 + 32);

        static const uint32_t Param_func324_func100_045[] =
        {
            0xfa4d90b8U, 0x0d966024U, 0x19970766U, 0x2c40f92eU,
        };
        HW_SCE_p_func100(Param_func324_func100_045);
        HW_SCE_p_func_sub009(0x80010020U, 0x01574730U);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_046[] =
        {
            0x7f6a3d31U, 0x15656e45U, 0x8350c92bU, 0xa29a076dU,
        };
        HW_SCE_p_func100(Param_func324_func100_046);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func319(544);

        static const uint32_t Param_func324_func100_047[] =
        {
            0xe8a70fe7U, 0x4d8a9e70U, 0x3f48c23aU, 0x89eeb55eU,
        };
        HW_SCE_p_func100(Param_func324_func100_047);
        HW_SCE_p_func314(544 + 32);

        static const uint32_t Param_func324_func100_048[] =
        {
            0x5c04f776U, 0x21f0f81fU, 0x4e3a8a5bU, 0x76098a00U,
        };
        HW_SCE_p_func100(Param_func324_func100_048);
        HW_SCE_p_func_sub009(0x80010020U, 0x01f11123U);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_049[] =
        {
            0x472aaf2aU, 0xf9d8f81cU, 0x07508940U, 0xd7a49d5aU,
        };
        HW_SCE_p_func100(Param_func324_func100_049);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000023U);
        HW_SCE_p_func319(580);

        static const uint32_t Param_func324_func100_050[] =
        {
            0x05d64b3fU, 0x793b0085U, 0xa705f245U, 0xe95259deU,
        };
        HW_SCE_p_func100(Param_func324_func100_050);
        HW_SCE_p_func314(580 + 32);

        static const uint32_t Param_func324_func100_051[] =
        {
            0xfa3b4138U, 0xbe30de6cU, 0xfc3bd1eaU, 0x2e93d150U,
        };
        HW_SCE_p_func100(Param_func324_func100_051);
        HW_SCE_p_func_sub009(0x80010020U, 0x01ac62c9U);

        HW_SCE_p_func080();

        static const uint32_t Param_func324_func100_052[] =
        {
            0xa6ec6b8cU, 0xaa9fd90bU, 0x46b98ebeU, 0xfbe37dfcU,
        };
        HW_SCE_p_func100(Param_func324_func100_052);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func319(616);

        static const uint32_t Param_func324_func100_053[] =
        {
            0x0f67fcf6U, 0xd661c9b8U, 0x78b71659U, 0xdc1671e7U,
        };
        HW_SCE_p_func100(Param_func324_func100_053);
        HW_SCE_p_func314(616 + 32);

        WR1_PROG(REG_ECH, 0x00002e40U);

        static const uint32_t Param_func324_func101_005[] =
        {
            0x61371d76U, 0x8955c0e3U, 0xf57d2ea6U, 0x6b052d94U,
        };
        HW_SCE_p_func101(Param_func324_func101_005);
    }

    HW_SCE_p_func_sub014(0x38008a40U, 0x00000003U, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    WR1_PROG(REG_ECH, 0x0000b7a0U);
    WR1_PROG(REG_ECH, 0x000000f1U);
    static const uint32_t Param_func324_func101_006[] =
    {
        0x8bba8cdbU, 0xa7e18e91U, 0xf71d87c8U, 0x797aa69cU,
    };
    HW_SCE_p_func101(Param_func324_func101_006);
    HW_SCE_p_func318();

    static const uint32_t Param_func324_func100_054[] =
    {
        0x322547acU, 0x9b5539eeU, 0x631909e9U, 0xa317cbbbU,
    };
    HW_SCE_p_func100(Param_func324_func100_054);
    HW_SCE_p_func_sub008(0x009f0001U, 0x011af8f9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_055[] =
    {
        0x1759ee18U, 0x3b01deecU, 0x6a8590f4U, 0xf6c5f969U,
    };
    HW_SCE_p_func100(Param_func324_func100_055);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(408);

    static const uint32_t Param_func324_func100_056[] =
    {
        0x96c47023U, 0x7df6d2ccU, 0xf3632006U, 0x6fe7f4f8U,
    };
    HW_SCE_p_func100(Param_func324_func100_056);
    HW_SCE_p_func314(408 + 32);

    static const uint32_t Param_func324_func100_057[] =
    {
        0x91a24210U, 0xcbb101b4U, 0xb5ba4705U, 0xfbf14b32U,
    };
    HW_SCE_p_func100(Param_func324_func100_057);
    HW_SCE_p_func_sub009(0x80010020U, 0x0130aeffU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_058[] =
    {
        0x2c310da3U, 0x5ea30255U, 0xa29d782eU, 0x0bc1f93eU,
    };
    HW_SCE_p_func100(Param_func324_func100_058);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(444);

    static const uint32_t Param_func324_func100_059[] =
    {
        0x8b87eef7U, 0x213e09a1U, 0xa69cfedbU, 0xfb9276f3U,
    };
    HW_SCE_p_func100(Param_func324_func100_059);
    HW_SCE_p_func314(444 + 32);

    static const uint32_t Param_func324_func100_060[] =
    {
        0xd41003baU, 0x105fbe5aU, 0x561c8390U, 0x4b945c86U,
    };
    HW_SCE_p_func100(Param_func324_func100_060);
    HW_SCE_p_func_sub009(0x80010020U, 0x010964eaU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_061[] =
    {
        0x48db3531U, 0x94b996bdU, 0x060dbf20U, 0x9520a664U,
    };
    HW_SCE_p_func100(Param_func324_func100_061);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func319(480);

    static const uint32_t Param_func324_func100_062[] =
    {
        0xb51fc317U, 0xc794cd92U, 0xb477efbcU, 0x81dce284U,
    };
    HW_SCE_p_func100(Param_func324_func100_062);
    HW_SCE_p_func314(480 + 32);

    WR1_PROG(REG_ECH, 0x0000b7a0U);
    WR1_PROG(REG_ECH, 0x000000f2U);
    static const uint32_t Param_func324_func101_007[] =
    {
        0xbf232622U, 0x10d13a51U, 0x848c8464U, 0x5f80635dU,
    };
    HW_SCE_p_func101(Param_func324_func101_007);
    HW_SCE_p_func318();

    static const uint32_t Param_func324_func100_063[] =
    {
        0x30a00026U, 0x69802337U, 0x7cd74e4fU, 0x52041efcU,
    };
    HW_SCE_p_func100(Param_func324_func100_063);
    HW_SCE_p_func_sub008(0x009f0001U, 0x01d34587U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_064[] =
    {
        0x553d552eU, 0xb04761ecU, 0x3077aef8U, 0x831743f4U,
    };
    HW_SCE_p_func100(Param_func324_func100_064);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(272);

    static const uint32_t Param_func324_func100_065[] =
    {
        0x7432c608U, 0xc9fed9c7U, 0xec726f19U, 0x8d5f8875U,
    };
    HW_SCE_p_func100(Param_func324_func100_065);
    HW_SCE_p_func314(272 + 32);

    static const uint32_t Param_func324_func100_066[] =
    {
        0xaace0e99U, 0x42f2e878U, 0xdd957896U, 0xcd0de241U,
    };
    HW_SCE_p_func100(Param_func324_func100_066);
    HW_SCE_p_func_sub009(0x80010020U, 0x01315552U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_067[] =
    {
        0x5c31900bU, 0x2680183dU, 0xe043b5a4U, 0x8db6cf2dU,
    };
    HW_SCE_p_func100(Param_func324_func100_067);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(308);

    static const uint32_t Param_func324_func100_068[] =
    {
        0xcdd8331eU, 0xa782fd53U, 0xc031e37eU, 0xf9541b33U,
    };
    HW_SCE_p_func100(Param_func324_func100_068);
    HW_SCE_p_func314(308 + 32);

    static const uint32_t Param_func324_func100_069[] =
    {
        0x36ab5860U, 0x7d1990c3U, 0xd106d439U, 0xd15c9b71U,
    };
    HW_SCE_p_func100(Param_func324_func100_069);
    HW_SCE_p_func_sub009(0x80010020U, 0x011a27dfU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_070[] =
    {
        0x6fc441bdU, 0x7bce0d3bU, 0xe350cbc9U, 0x0d856aceU,
    };
    HW_SCE_p_func100(Param_func324_func100_070);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func319(344);

    static const uint32_t Param_func324_func100_071[] =
    {
        0xe4f910e8U, 0x57082666U, 0x3975f343U, 0xeb5a48a4U,
    };
    HW_SCE_p_func100(Param_func324_func100_071);
    HW_SCE_p_func314(344 + 32);

    static const uint32_t Param_func324_func100_072[] =
    {
        0x8de19a0bU, 0x8f9aed6fU, 0x47fdf7ecU, 0x62fb4c80U,
    };
    HW_SCE_p_func100(Param_func324_func100_072);
    HW_SCE_p_func_sub008(0x009f0001U, 0x011af8f9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_073[] =
    {
        0x26831bc6U, 0xcde42f4fU, 0x8b4d5307U, 0xca3cecfeU,
    };
    HW_SCE_p_func100(Param_func324_func100_073);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(408);

    static const uint32_t Param_func324_func100_074[] =
    {
        0x68d5d8f0U, 0x2d218dd1U, 0xd6eea468U, 0xb35336b8U,
    };
    HW_SCE_p_func100(Param_func324_func100_074);
    HW_SCE_p_func314(408 + 32);

    static const uint32_t Param_func324_func100_075[] =
    {
        0x021c7250U, 0x492cdf1fU, 0x3a45037fU, 0xefeca1b5U,
    };
    HW_SCE_p_func100(Param_func324_func100_075);
    HW_SCE_p_func_sub009(0x80010020U, 0x0130aeffU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_076[] =
    {
        0x0cb3fc26U, 0xcb04bc14U, 0xb6de0377U, 0x53ba5f3fU,
    };
    HW_SCE_p_func100(Param_func324_func100_076);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(444);

    static const uint32_t Param_func324_func100_077[] =
    {
        0x2e642543U, 0x4902544aU, 0x51f5ebe8U, 0x72794910U,
    };
    HW_SCE_p_func100(Param_func324_func100_077);
    HW_SCE_p_func314(444 + 32);

    static const uint32_t Param_func324_func100_078[] =
    {
        0x8f9d782eU, 0x81c16d66U, 0x5e85807eU, 0x6ef1b6d8U,
    };
    HW_SCE_p_func100(Param_func324_func100_078);
    HW_SCE_p_func_sub009(0x80010020U, 0x010964eaU);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_079[] =
    {
        0xc718fd71U, 0x78b1a7f1U, 0x20b0a1fcU, 0x08efeaa0U,
    };
    HW_SCE_p_func100(Param_func324_func100_079);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func319(480);

    static const uint32_t Param_func324_func100_080[] =
    {
        0x1703905fU, 0x2588568cU, 0x62ecbe40U, 0x232f9133U,
    };
    HW_SCE_p_func100(Param_func324_func100_080);
    HW_SCE_p_func314(480 + 32);

    static const uint32_t Param_func324_func100_081[] =
    {
        0x3a1733d4U, 0x86275a46U, 0x6eccc0a1U, 0x33a7dc95U,
    };
    HW_SCE_p_func100(Param_func324_func100_081);
    HW_SCE_p_func_sub008(0x009f0001U, 0x01fe1091U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_082[] =
    {
        0x8e52d68bU, 0x1f5c3894U, 0x691f3877U, 0x2243d7a3U,
    };
    HW_SCE_p_func100(Param_func324_func100_082);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000012U);
    HW_SCE_p_func320(0);

    HW_SCE_p_func_sub009(0x80010020U, 0x019969f4U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_083[] =
    {
        0x29bf281fU, 0x90730ae8U, 0x5c16ffe4U, 0x9746b752U,
    };
    HW_SCE_p_func100(Param_func324_func100_083);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000013U);
    HW_SCE_p_func320(36);

    HW_SCE_p_func_sub009(0x80010020U, 0x019de420U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_084[] =
    {
        0xc6d651f1U, 0xea4e04fbU, 0x1e97b80eU, 0x728f545cU,
    };
    HW_SCE_p_func100(Param_func324_func100_084);
    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func320(72);

    HW_SCE_p_func_sub009(0x80010020U, 0x01574730U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_085[] =
    {
        0x4f8d632aU, 0xfd956a83U, 0x8a13de73U, 0x6dd74cadU,
    };
    HW_SCE_p_func100(Param_func324_func100_085);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(544);

    static const uint32_t Param_func324_func100_086[] =
    {
        0xc1fe21f7U, 0x1494de69U, 0xb4a7584bU, 0x901cd492U,
    };
    HW_SCE_p_func100(Param_func324_func100_086);
    HW_SCE_p_func314(544 + 32);

    static const uint32_t Param_func324_func100_087[] =
    {
        0x0e1dc5d7U, 0x2032e656U, 0x84c0fcffU, 0x1b85a4d7U,
    };
    HW_SCE_p_func100(Param_func324_func100_087);
    HW_SCE_p_func_sub009(0x80010020U, 0x01f11123U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_088[] =
    {
        0x085429ddU, 0x35c43703U, 0x5059446fU, 0x997691b1U,
    };
    HW_SCE_p_func100(Param_func324_func100_088);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(580);

    static const uint32_t Param_func324_func100_089[] =
    {
        0x6d916213U, 0xb2da4cceU, 0x367fbab5U, 0x2acea943U,
    };
    HW_SCE_p_func100(Param_func324_func100_089);
    HW_SCE_p_func314(580 + 32);

    static const uint32_t Param_func324_func100_090[] =
    {
        0x18057ff5U, 0x754a8c51U, 0x086a4be3U, 0x90067525U,
    };
    HW_SCE_p_func100(Param_func324_func100_090);
    HW_SCE_p_func_sub009(0x80010020U, 0x01ac62c9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_091[] =
    {
        0x325a9a89U, 0x535dc5d9U, 0x1f05a791U, 0xcd2f9884U,
    };
    HW_SCE_p_func100(Param_func324_func100_091);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func319(616);

    static const uint32_t Param_func324_func100_092[] =
    {
        0xc75b4b8fU, 0x620e68b0U, 0xbbebe121U, 0xe12fba81U,
    };
    HW_SCE_p_func100(Param_func324_func100_092);
    HW_SCE_p_func314(616 + 32);

    WR1_PROG(REG_ECH, 0x0000b7a0U);
    WR1_PROG(REG_ECH, 0x000000f3U);
    static const uint32_t Param_func324_func101_008[] =
    {
        0x06aa632cU, 0x2c294586U, 0x524b9262U, 0x937064feU,
    };
    HW_SCE_p_func101(Param_func324_func101_008);
    HW_SCE_p_func318();

    static const uint32_t Param_func324_func100_093[] =
    {
        0x7ea795a3U, 0x8915f2cbU, 0xa7c41020U, 0x0f89207eU,
    };
    HW_SCE_p_func100(Param_func324_func100_093);
    HW_SCE_p_func_sub008(0x009f0001U, 0x01fe1091U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_094[] =
    {
        0x9a6b4727U, 0x19829e58U, 0xb07a6fc7U, 0x1ec71baeU,
    };
    HW_SCE_p_func100(Param_func324_func100_094);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func319(0);

    static const uint32_t Param_func324_func100_095[] =
    {
        0xb85e4c02U, 0x1065c4d4U, 0x565140bcU, 0x9e233683U,
    };
    HW_SCE_p_func100(Param_func324_func100_095);
    HW_SCE_p_func314(0 + 32);

    static const uint32_t Param_func324_func100_096[] =
    {
        0x0f6b1778U, 0xbd59c987U, 0x90211bb5U, 0x109bfbf8U,
    };
    HW_SCE_p_func100(Param_func324_func100_096);
    HW_SCE_p_func_sub009(0x80010020U, 0x019969f4U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_097[] =
    {
        0xb356879fU, 0xa9e41716U, 0x28645099U, 0x0bf86938U,
    };
    HW_SCE_p_func100(Param_func324_func100_097);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000023U);
    HW_SCE_p_func319(36);

    static const uint32_t Param_func324_func100_098[] =
    {
        0xb6a059a7U, 0xb27e1a91U, 0xe6575256U, 0x7d8b8dbcU,
    };
    HW_SCE_p_func100(Param_func324_func100_098);
    HW_SCE_p_func314(36 + 32);

    static const uint32_t Param_func324_func100_099[] =
    {
        0xe0209cc9U, 0xc3e5b064U, 0xe233e02bU, 0xb82949e6U,
    };
    HW_SCE_p_func100(Param_func324_func100_099);
    HW_SCE_p_func_sub009(0x80010020U, 0x019de420U);

    HW_SCE_p_func080();

    static const uint32_t Param_func324_func100_100[] =
    {
        0xcf7deda8U, 0xb4cb207eU, 0x706bb36cU, 0xd048408eU,
    };
    HW_SCE_p_func100(Param_func324_func100_100);
    WR1_PROG(REG_00H, 0x00002383U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func319(72);

    static const uint32_t Param_func324_func100_101[] =
    {
        0x39eb6316U, 0x27f38705U, 0x8667e6f3U, 0xf04bff62U,
    };
    HW_SCE_p_func100(Param_func324_func100_101);
    HW_SCE_p_func314(72 + 32);

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000004U, 0x00003bbeU, 0x00007c1dU);
    WR1_PROG(REG_1CH, 0x00602000U);
}
