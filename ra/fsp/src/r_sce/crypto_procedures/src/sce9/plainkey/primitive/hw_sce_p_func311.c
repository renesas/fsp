/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func311_r1 (void)
{
    uint32_t iLoop  = 0U;
    uint32_t oLoop1 = 0U;

    static const uint32_t Param_func311_func100_001[] =
    {
        0xfd4b176bU, 0xd5a81478U, 0x6420f33dU, 0xf5728f32U,
    };
    HW_SCE_p_func100(Param_func311_func100_001);
    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x0000002cU);
    WR1_PROG(REG_ECH, 0x00003c1eU);

    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00870001U);
    WR1_PROG(REG_34H, 0x00000800U);
    WR1_PROG(REG_24H, 0x800080c1U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_28H, 0x00bf0001U);
    WR1_PROG(REG_24H, 0x04000591U);
    HW_SCE_p_func_sub015(0x000040c1U, 0x00870001U);
    WR1_PROG(REG_34H, 0x00000008U);
    HW_SCE_p_func_sub006(0x800011c0U, 0x00000008U, 0x82001191U);
    HW_SCE_p_func_sub008(0x00bf0001U, 0x01b9d3a9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_002[] =
    {
        0xa9ea96d7U, 0x43b13488U, 0x024e5431U, 0x4c64617bU,
    };
    HW_SCE_p_func100(Param_func311_func100_002);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(680);

    HW_SCE_p_func_sub009(0x80010020U, 0x012dc3c7U);

    HW_SCE_p_func080();

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func312(748);

    HW_SCE_p_func_sub023(0x000001c0U, 0x04001991U);

    WR1_PROG(REG_24H, 0x060049c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x02001191U);
    HW_SCE_p_func_sub017(0x00000581U, 0x00210000U);

    oLoop1 = 1;
    while (oLoop1 == 1)
    {
        static const uint32_t Param_func311_func100_003[] =
        {
            0xd6e08aa7U, 0xec23e33dU, 0x69c55027U, 0xb230fa25U,
        };
        HW_SCE_p_func100(Param_func311_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_func311_func101_001[] =
            {
                0x6a97a04bU, 0x686aafbaU, 0x37cc5886U, 0xf353c266U,
            };
            HW_SCE_p_func101(Param_func311_func101_001);
            oLoop1 = 0;
        }
        else
        {
            HW_SCE_p_func_sub023(0x000049c1U, 0x04001991U);

            WR1_PROG(REG_24H, 0x060049c1U);
            HW_SCE_p_func_sub017(0x02001191U, 0x00210000U);

            static const uint32_t Param_func311_func101_002[] =
            {
                0x7f0eb3ebU, 0x8636ae7eU, 0xa78fc1faU, 0x8247ea08U,
            };
            HW_SCE_p_func101(Param_func311_func101_002);
        }
    }

    static const uint32_t Param_func311_func100_004[] =
    {
        0xb4873111U, 0xecb38ea8U, 0x15a4ff05U, 0x06e2ba67U,
    };
    HW_SCE_p_func100(Param_func311_func100_004);
    HW_SCE_p_func_sub023(0x000049c1U, 0x04001981U);
    WR1_PROG(REG_24H, 0x060049c1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x02001181U, 0x016bcaa1U);

    HW_SCE_p_func080();
    static const uint32_t Param_func311_func100_005[] =
    {
        0x089ef4feU, 0x15bbe85fU, 0x80a2f025U, 0x29ff60e2U,
    };
    HW_SCE_p_func100(Param_func311_func100_005);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(136);

    static const uint32_t Param_func311_func100_006[] =
    {
        0x99313b51U, 0x88d8f2e1U, 0xdb56f33bU, 0xb6d38a7fU,
    };
    HW_SCE_p_func100(Param_func311_func100_006);
    HW_SCE_p_func314(136 + 64);

    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);

    static const uint32_t Param_func311_func100_007[] =
    {
        0xcfda5444U, 0x2be84e0fU, 0xe0e2bd7bU, 0xa7c355d9U,
    };
    HW_SCE_p_func100(Param_func311_func100_007);
    HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

    HW_SCE_p_func080();
    static const uint32_t Param_func311_func100_008[] =
    {
        0xa765abb1U, 0x26cce39dU, 0x4b9fdea1U, 0xf6435bdbU,
    };
    HW_SCE_p_func100(Param_func311_func100_008);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(204);

    static const uint32_t Param_func311_func100_009[] =
    {
        0x8d279c22U, 0xfc68a162U, 0x2fbd3f61U, 0x61c9e67fU,
    };
    HW_SCE_p_func100(Param_func311_func100_009);
    HW_SCE_p_func314(204 + 64);

    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_ECH, 0x00000a52U);

    for (iLoop = 0U; iLoop < 256U; iLoop++)
    {
        static const uint32_t Param_func311_func100_010[] =
        {
            0x9bdc8e76U, 0xa1c2a576U, 0xf7908ae4U, 0xa3ee9d7fU,
        };
        HW_SCE_p_func100(Param_func311_func100_010);

        HW_SCE_p_func_sub023(0x040049c1U, 0x04000149U);

        HW_SCE_p_func_sub023(0x060049c1U, 0x0400d0d0U);
        HW_SCE_p_func_sub004(0x02000149U, 0x01b9d3a9U);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func312(680);

        WR1_PROG(REG_ECH, 0x00002e40U);

        static const uint32_t Param_func311_func101_003[] =
        {
            0x7d34eb40U, 0x5747f818U, 0x1be65614U, 0xd6ed34b3U,
        };
        HW_SCE_p_func101(Param_func311_func101_003);
    }

    static const uint32_t Param_func311_func100_011[] =
    {
        0x142ecffcU, 0x326510a6U, 0x8cbe023bU, 0x026a5df9U,
    };
    HW_SCE_p_func100(Param_func311_func100_011);
    HW_SCE_p_func_sub014(0x38008a40U, 0x00000100U, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    HW_SCE_p_func_sub023(0x040049c1U, 0x040019a1U);
    HW_SCE_p_func_sub023(0x060049c1U, 0x0400d0d0U);
    HW_SCE_p_func_sub004(0x020019a1U, 0x01b9d3a9U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_012[] =
    {
        0xb896da45U, 0x16e2080fU, 0x293b4f68U, 0x9dc078e9U,
    };
    HW_SCE_p_func100(Param_func311_func100_012);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000014U);
    HW_SCE_p_func312(680);

    HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_013[] =
    {
        0x718e4ecbU, 0x6d103300U, 0xcb1eb1bbU, 0x52ffc030U,
    };
    HW_SCE_p_func100(Param_func311_func100_013);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(408);

    static const uint32_t Param_func311_func100_014[] =
    {
        0xf0047e74U, 0xc38cc552U, 0x8a3454a0U, 0x0dc9fc09U,
    };
    HW_SCE_p_func100(Param_func311_func100_014);
    HW_SCE_p_func314(408 + 64);

    static const uint32_t Param_func311_func100_015[] =
    {
        0xb89c82d1U, 0xca37b6d4U, 0xfebe0198U, 0x2992116aU,
    };
    HW_SCE_p_func100(Param_func311_func100_015);
    HW_SCE_p_func_sub009(0x80010020U, 0x01e59c3dU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_016[] =
    {
        0x8c0b1577U, 0xd80af8b9U, 0x8a28fa6aU, 0xb8691f5aU,
    };
    HW_SCE_p_func100(Param_func311_func100_016);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(544);

    static const uint32_t Param_func311_func100_017[] =
    {
        0x6a8f8a7bU, 0xea162157U, 0xf8e0b9d6U, 0xb3d9155bU,
    };
    HW_SCE_p_func100(Param_func311_func100_017);
    HW_SCE_p_func314(544 + 64);

    WR1_PROG(REG_24H, 0x000049c1U);
    WAIT_STS(REG_24H, 21, 0);
    static const uint32_t Param_func311_func100_018[] =
    {
        0x0cd9debeU, 0x90441b42U, 0x6c48e06dU, 0xd5ce096eU,
    };
    HW_SCE_p_func100(Param_func311_func100_018);
    HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_019[] =
    {
        0x95056b4fU, 0xa2022506U, 0xd5895c90U, 0xc9016455U,
    };
    HW_SCE_p_func100(Param_func311_func100_019);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(476);

    static const uint32_t Param_func311_func100_020[] =
    {
        0x8de7ac54U, 0x2086ac6eU, 0xda5ccc3dU, 0x720b13b1U,
    };
    HW_SCE_p_func100(Param_func311_func100_020);
    HW_SCE_p_func314(476 + 64);

    static const uint32_t Param_func311_func100_021[] =
    {
        0xd9c89923U, 0xda6185eeU, 0x520354eaU, 0x62d3ec2bU,
    };
    HW_SCE_p_func100(Param_func311_func100_021);
    HW_SCE_p_func_sub009(0x80010020U, 0x019fce91U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_022[] =
    {
        0x8c5f3115U, 0x6e3076f9U, 0xc072f381U, 0x3dceb2c9U,
    };
    HW_SCE_p_func100(Param_func311_func100_022);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(612);

    static const uint32_t Param_func311_func100_023[] =
    {
        0x0221233fU, 0x3eb2c7f3U, 0x2f53721bU, 0x87b0f538U,
    };
    HW_SCE_p_func100(Param_func311_func100_023);
    HW_SCE_p_func314(612 + 64);

    WR1_PROG(REG_ECH, 0x00000a52U);

    for (iLoop = 0U; iLoop < 4; iLoop++)
    {
        WR1_PROG(REG_ECH, 0x0000b400U);
        WR1_PROG(REG_ECH, 0x00000085U);
        static const uint32_t Param_func311_func101_004[] =
        {
            0x6d1dde65U, 0x27e804aaU, 0x0353a48aU, 0xc63e1af4U,
        };
        HW_SCE_p_func101(Param_func311_func101_004);
        HW_SCE_p_func309_r1();

        static const uint32_t Param_func311_func100_024[] =
        {
            0x52609d4fU, 0x2847540dU, 0xe7fd5f89U, 0xf730b53dU,
        };
        HW_SCE_p_func100(Param_func311_func100_024);
        HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

        HW_SCE_p_func080();

        static const uint32_t Param_func311_func100_025[] =
        {
            0xe6b75748U, 0xf45d1592U, 0xee7bfe91U, 0x326aca9dU,
        };
        HW_SCE_p_func100(Param_func311_func100_025);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func313(476);

        static const uint32_t Param_func311_func100_026[] =
        {
            0xe9fe5121U, 0xce726d25U, 0xa83a96a3U, 0xb8b584aaU,
        };
        HW_SCE_p_func100(Param_func311_func100_026);
        HW_SCE_p_func314(476 + 64);

        static const uint32_t Param_func311_func100_027[] =
        {
            0xb3bc9911U, 0xf6c18db0U, 0xfc732293U, 0x3cd6f686U,
        };
        HW_SCE_p_func100(Param_func311_func100_027);
        HW_SCE_p_func_sub009(0x80010020U, 0x019fce91U);

        HW_SCE_p_func080();

        static const uint32_t Param_func311_func100_028[] =
        {
            0x6dd6c2adU, 0x7c99c2a6U, 0x3a7d202dU, 0x33864215U,
        };
        HW_SCE_p_func100(Param_func311_func100_028);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func313(612);

        static const uint32_t Param_func311_func100_029[] =
        {
            0x00e68939U, 0x22376fe5U, 0x1dc88c20U, 0x4f16dbfeU,
        };
        HW_SCE_p_func100(Param_func311_func100_029);
        HW_SCE_p_func314(612 + 64);

        static const uint32_t Param_func311_func100_030[] =
        {
            0x225f07a7U, 0xe5c06b6bU, 0xd5ad4e40U, 0x77a94de9U,
        };
        HW_SCE_p_func100(Param_func311_func100_030);
        HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

        HW_SCE_p_func080();

        static const uint32_t Param_func311_func100_031[] =
        {
            0x161d0285U, 0x582fea60U, 0x8ddb0abfU, 0xf3e3813fU,
        };
        HW_SCE_p_func100(Param_func311_func100_031);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func313(408);

        static const uint32_t Param_func311_func100_032[] =
        {
            0xba986d4aU, 0x8c0c05c3U, 0x9106460cU, 0x4fcb22b1U,
        };
        HW_SCE_p_func100(Param_func311_func100_032);
        HW_SCE_p_func314(408 + 64);

        static const uint32_t Param_func311_func100_033[] =
        {
            0xba3a26c5U, 0xab973a6dU, 0x113d70d0U, 0x17ceceabU,
        };
        HW_SCE_p_func100(Param_func311_func100_033);
        HW_SCE_p_func_sub009(0x80010020U, 0x01e59c3dU);

        HW_SCE_p_func080();

        static const uint32_t Param_func311_func100_034[] =
        {
            0xed966499U, 0xffbb31adU, 0x0babdc9eU, 0x028e43eaU,
        };
        HW_SCE_p_func100(Param_func311_func100_034);
        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func313(544);

        static const uint32_t Param_func311_func100_035[] =
        {
            0x70e80bbeU, 0x80e52ebcU, 0xc889fbaeU, 0x908cde5dU,
        };
        HW_SCE_p_func100(Param_func311_func100_035);
        HW_SCE_p_func314(544 + 64);

        WR1_PROG(REG_ECH, 0x00002e40U);

        static const uint32_t Param_func311_func101_005[] =
        {
            0xe79021aaU, 0x8e1a3178U, 0x17485e2aU, 0x7739cc4aU,
        };
        HW_SCE_p_func101(Param_func311_func101_005);
    }

    HW_SCE_p_func_sub014(0x38008a40U, 0x00000004U, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    static const uint32_t Param_func311_func100_036[] =
    {
        0xa7713f01U, 0xff3d0159U, 0x902c8403U, 0xa6e08877U,
    };
    HW_SCE_p_func100(Param_func311_func100_036);
    HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_037[] =
    {
        0xd79142abU, 0xdda79cd3U, 0xa39e379bU, 0x30387819U,
    };
    HW_SCE_p_func100(Param_func311_func100_037);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(476);

    static const uint32_t Param_func311_func100_038[] =
    {
        0x840d4a08U, 0x2d844345U, 0xcafbbf9fU, 0x5f275859U,
    };
    HW_SCE_p_func100(Param_func311_func100_038);
    HW_SCE_p_func314(476 + 64);

    static const uint32_t Param_func311_func100_039[] =
    {
        0xebcced92U, 0x52a220a6U, 0x4b7a4cfbU, 0xe36bc013U,
    };
    HW_SCE_p_func100(Param_func311_func100_039);
    HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_040[] =
    {
        0xf2e9a370U, 0x660aefceU, 0x405fff51U, 0xb7af9bb1U,
    };
    HW_SCE_p_func100(Param_func311_func100_040);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(408);

    static const uint32_t Param_func311_func100_041[] =
    {
        0x17c8247cU, 0xa0ddb080U, 0x9e68312cU, 0xef695d8eU,
    };
    HW_SCE_p_func100(Param_func311_func100_041);
    HW_SCE_p_func314(408 + 64);

    static const uint32_t Param_func311_func100_042[] =
    {
        0x8de20e43U, 0x8198b797U, 0x50909c69U, 0xe206fb6eU,
    };
    HW_SCE_p_func100(Param_func311_func100_042);
    HW_SCE_p_func_sub009(0x80010020U, 0x0132d44bU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_043[] =
    {
        0x8bd2bbe9U, 0x0be9aca0U, 0x6bf6b397U, 0x2b511dbfU,
    };
    HW_SCE_p_func100(Param_func311_func100_043);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func312(68);

    HW_SCE_p_func_sub009(0x80010020U, 0x01432c7aU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_044[] =
    {
        0x8921c32eU, 0x0b09dafaU, 0x0a0bda14U, 0x9944d54cU,
    };
    HW_SCE_p_func100(Param_func311_func100_044);
    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    HW_SCE_p_func312(0);

    HW_SCE_p_func_sub009(0x80010020U, 0x019fce91U);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_045[] =
    {
        0x2541ef28U, 0x061e859cU, 0xe88ecdd7U, 0x0f6035d5U,
    };
    HW_SCE_p_func100(Param_func311_func100_045);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(612);

    static const uint32_t Param_func311_func100_046[] =
    {
        0x4d51142bU, 0x42fff715U, 0x472627e9U, 0x603bdc70U,
    };
    HW_SCE_p_func100(Param_func311_func100_046);
    HW_SCE_p_func314(612 + 64);

    static const uint32_t Param_func311_func100_047[] =
    {
        0x0efd708cU, 0xcc94585bU, 0xc223494aU, 0xc6eb2968U,
    };
    HW_SCE_p_func100(Param_func311_func100_047);
    HW_SCE_p_func_sub009(0x80010020U, 0x01e59c3dU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_048[] =
    {
        0xa3fc9c35U, 0x200d7e68U, 0x469464daU, 0x5b9149ecU,
    };
    HW_SCE_p_func100(Param_func311_func100_048);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(544);

    static const uint32_t Param_func311_func100_049[] =
    {
        0xcbb87f2cU, 0xcdf462d9U, 0x6ff399b9U, 0x9b315f2dU,
    };
    HW_SCE_p_func100(Param_func311_func100_049);
    HW_SCE_p_func314(544 + 64);

    WR1_PROG(REG_ECH, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000086U);
    static const uint32_t Param_func311_func101_006[] =
    {
        0x3cbf7cedU, 0x9f0ca8c1U, 0x9fc1b0a7U, 0x1fb8e5cbU,
    };
    HW_SCE_p_func101(Param_func311_func101_006);
    HW_SCE_p_func309_r1();

    static const uint32_t Param_func311_func100_050[] =
    {
        0xd887c518U, 0x5a403aa4U, 0xc6176be4U, 0x5ce2816eU,
    };
    HW_SCE_p_func100(Param_func311_func100_050);
    HW_SCE_p_func_sub009(0x80010020U, 0x0132d44bU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_051[] =
    {
        0x33ef899cU, 0x80ff43e7U, 0x24d6eaa4U, 0x1fcd4bb9U,
    };
    HW_SCE_p_func100(Param_func311_func100_051);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(68);

    static const uint32_t Param_func311_func100_052[] =
    {
        0x4eb32dd0U, 0x894b3a68U, 0x790aeb44U, 0x83d869b6U,
    };
    HW_SCE_p_func100(Param_func311_func100_052);
    HW_SCE_p_func314(68 + 64);

    static const uint32_t Param_func311_func100_053[] =
    {
        0x6441f351U, 0x8a23ac4eU, 0xaf9adeadU, 0xeae53c32U,
    };
    HW_SCE_p_func100(Param_func311_func100_053);
    HW_SCE_p_func_sub009(0x80010020U, 0x01432c7aU);

    HW_SCE_p_func080();

    static const uint32_t Param_func311_func100_054[] =
    {
        0xbdf03440U, 0x37792dbcU, 0x58df6b26U, 0x61fffe27U,
    };
    HW_SCE_p_func100(Param_func311_func100_054);
    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(0);

    static const uint32_t Param_func311_func100_055[] =
    {
        0x10098830U, 0x68ef79e5U, 0x8d4399a9U, 0x320f688fU,
    };
    HW_SCE_p_func100(Param_func311_func100_055);
    HW_SCE_p_func314(0 + 64);

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x0000002cU, 0x0000381eU, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);
}
