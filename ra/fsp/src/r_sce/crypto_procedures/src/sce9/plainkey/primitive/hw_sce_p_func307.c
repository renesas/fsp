/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func307_r1 (void)
{
    uint32_t jLoop = 0U;

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x00000090U);
    WR1_PROG(REG_ECH, 0x00003c1eU);

    WR1_PROG(REG_28H, 0x00bf0001U);

    WR1_PROG(REG_ECH, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000080U);
    static const uint32_t Param_func307_func101_001[] =
    {
        0x46765f77U, 0x5749f546U, 0xffae0ff7U, 0x8b2d018eU,
    };
    HW_SCE_p_func101(Param_func307_func101_001);
    HW_SCE_p_func311_r1();

    WR1_PROG(REG_ECH, 0x00000a73U);

    WR1_PROG(REG_ECH, 0x00000a31U);

    for (jLoop = 0U; jLoop < 32U; jLoop++)
    {
        HW_SCE_p_func_sub014(0x00002e20U, 0x38002673U, 0x00A60000U);
        static const uint32_t Param_func307_func100_001[] =
        {
            0x0efed670U, 0x4c5eb194U, 0xde5be454U, 0x29041d0fU,
        };
        HW_SCE_p_func100(Param_func307_func100_001);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);
        if (CHCK_STS(REG_1CH, 22, 0))
        {
            static const uint32_t Param_func307_func101_002[] =
            {
                0x733f12abU, 0xecc5543eU, 0xc537a171U, 0x48357424U,
            };
            HW_SCE_p_func101(Param_func307_func101_002);
        }
        else
        {
            static const uint32_t Param_func307_func100_002[] =
            {
                0x2d664c4dU, 0xd9d9fd9dU, 0xe34eae6aU, 0x62d43b41U,
            };
            HW_SCE_p_func100(Param_func307_func100_002);
            HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_003[] =
            {
                0xe804d856U, 0xe4909999U, 0xa52e04fdU, 0xfe75ac58U,
            };
            HW_SCE_p_func100(Param_func307_func100_003);

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000010U);
            HW_SCE_p_func312(204);

            HW_SCE_p_func_sub009(0x80010020U, 0x016bcaa1U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_004[] =
            {
                0x517c7161U, 0x77c03114U, 0x61d87db2U, 0x4f1c9985U,
            };
            HW_SCE_p_func100(Param_func307_func100_004);

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000012U);
            HW_SCE_p_func312(136);

            HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_005[] =
            {
                0x989e30fdU, 0xfb087ef5U, 0xec2e871bU, 0x64eb0658U,
            };
            HW_SCE_p_func100(Param_func307_func100_005);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(476);

            static const uint32_t Param_func307_func100_006[] =
            {
                0xbf56fa09U, 0x821175ccU, 0x1891f091U, 0x8f3b024aU,
            };
            HW_SCE_p_func100(Param_func307_func100_006);
            HW_SCE_p_func314(476 + 64);

            static const uint32_t Param_func307_func100_007[] =
            {
                0xd2825fcdU, 0xc659f6e8U, 0x10029c48U, 0x47827fb5U,
            };
            HW_SCE_p_func100(Param_func307_func100_007);
            HW_SCE_p_func_sub009(0x80010020U, 0x019fce91U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_008[] =
            {
                0xa3c241c7U, 0x45c0ad6bU, 0xe6a7bb38U, 0x84b04d8bU,
            };
            HW_SCE_p_func100(Param_func307_func100_008);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(612);

            static const uint32_t Param_func307_func100_009[] =
            {
                0x3f406e95U, 0x13025ff8U, 0xf8b51b24U, 0x4c05351cU,
            };
            HW_SCE_p_func100(Param_func307_func100_009);
            HW_SCE_p_func314(612 + 64);

            static const uint32_t Param_func307_func100_010[] =
            {
                0x0830ae7aU, 0x6d43b3e9U, 0xd4ccc5eaU, 0xe6dcdce5U,
            };
            HW_SCE_p_func100(Param_func307_func100_010);
            HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_011[] =
            {
                0x40901979U, 0xc4600862U, 0x60d83598U, 0xf0d8941fU,
            };
            HW_SCE_p_func100(Param_func307_func100_011);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(408);

            static const uint32_t Param_func307_func100_012[] =
            {
                0x2c04ab0bU, 0x0e747ad8U, 0x7eb80229U, 0xf876f457U,
            };
            HW_SCE_p_func100(Param_func307_func100_012);
            HW_SCE_p_func314(408 + 64);

            static const uint32_t Param_func307_func100_013[] =
            {
                0xa016bd2cU, 0x3aa9aa45U, 0x7542dc38U, 0xdcc879c6U,
            };
            HW_SCE_p_func100(Param_func307_func100_013);
            HW_SCE_p_func_sub009(0x80010020U, 0x01e59c3dU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_014[] =
            {
                0x20c49ee6U, 0x329d4116U, 0xa1fa89feU, 0x0340299cU,
            };
            HW_SCE_p_func100(Param_func307_func100_014);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(544);

            static const uint32_t Param_func307_func100_015[] =
            {
                0x6e9c8d98U, 0x6120d3adU, 0x665f0919U, 0x27efb3baU,
            };
            HW_SCE_p_func100(Param_func307_func100_015);
            HW_SCE_p_func314(544 + 64);

            WR1_PROG(REG_ECH, 0x0000b400U);
            WR1_PROG(REG_ECH, 0x00000081U);
            static const uint32_t Param_func307_func101_003[] =
            {
                0xca53192fU, 0x211abfddU, 0xa870386fU, 0xb8e79d3eU,
            };
            HW_SCE_p_func101(Param_func307_func101_003);
            HW_SCE_p_func309_r1();

            static const uint32_t Param_func307_func100_016[] =
            {
                0xcd35d372U, 0x54dbdbceU, 0xb0afbbdbU, 0xf796fc29U,
            };
            HW_SCE_p_func100(Param_func307_func100_016);
            HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_017[] =
            {
                0xaee9f5b2U, 0x522163adU, 0x95ef5614U, 0x66787e86U,
            };
            HW_SCE_p_func100(Param_func307_func100_017);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(204);

            static const uint32_t Param_func307_func100_018[] =
            {
                0x2e1850f0U, 0x07ff76f0U, 0xce36e13cU, 0x6eea89e8U,
            };
            HW_SCE_p_func100(Param_func307_func100_018);
            HW_SCE_p_func314(204 + 64);

            static const uint32_t Param_func307_func100_019[] =
            {
                0x05d76537U, 0xa64e6099U, 0x19533700U, 0x491094b8U,
            };
            HW_SCE_p_func100(Param_func307_func100_019);
            HW_SCE_p_func_sub009(0x80010020U, 0x016bcaa1U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_020[] =
            {
                0xe6475365U, 0x1fae56fbU, 0x565db664U, 0xa6771660U,
            };
            HW_SCE_p_func100(Param_func307_func100_020);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(136);

            static const uint32_t Param_func307_func100_021[] =
            {
                0xfe310ec6U, 0xff3bb340U, 0x3af230a3U, 0xbcedede9U,
            };
            HW_SCE_p_func100(Param_func307_func100_021);
            HW_SCE_p_func314(136 + 64);

            static const uint32_t Param_func307_func101_004[] =
            {
                0x9fa02c96U, 0xfaf805deU, 0x6623feddU, 0xbc1389aeU,
            };
            HW_SCE_p_func101(Param_func307_func101_004);
        }

        WR1_PROG(REG_ECH, 0x3800da9fU);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00A60000U);

        static const uint32_t Param_func307_func100_022[] =
        {
            0x3d92f89aU, 0xa4b197f4U, 0x583087f9U, 0x353f282dU,
        };
        HW_SCE_p_func100(Param_func307_func100_022);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 0))
        {
            static const uint32_t Param_func307_func101_005[] =
            {
                0x60afc885U, 0xc0ff181bU, 0x12ea81aeU, 0x2804d93eU,
            };
            HW_SCE_p_func101(Param_func307_func101_005);
        }
        else
        {
            static const uint32_t Param_func307_func100_023[] =
            {
                0xb9b491e0U, 0x1463bd81U, 0x8cdca180U, 0x461e2b79U,
            };
            HW_SCE_p_func100(Param_func307_func100_023);
            HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_024[] =
            {
                0x909714ffU, 0xd0219bf6U, 0x9f8fbbbdU, 0xd4083fd2U,
            };
            HW_SCE_p_func100(Param_func307_func100_024);

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000010U);
            HW_SCE_p_func312(204);

            HW_SCE_p_func_sub009(0x80010020U, 0x016bcaa1U);

            HW_SCE_p_func080();

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000012U);
            HW_SCE_p_func312(136);

            static const uint32_t Param_func307_func100_025[] =
            {
                0x5592c700U, 0x5a6eaa8aU, 0xd9bf08bdU, 0x69ab981dU,
            };
            HW_SCE_p_func100(Param_func307_func100_025);
            HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_026[] =
            {
                0x5925d68dU, 0x7a61ecf6U, 0x5bae60ccU, 0x83f7e3a4U,
            };
            HW_SCE_p_func100(Param_func307_func100_026);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(476);

            static const uint32_t Param_func307_func100_027[] =
            {
                0xa3ca016bU, 0x8aaf93d3U, 0xbdc90e30U, 0x56d8ac7dU,
            };
            HW_SCE_p_func100(Param_func307_func100_027);
            HW_SCE_p_func314(476 + 64);

            static const uint32_t Param_func307_func100_028[] =
            {
                0xb313c752U, 0x5c602865U, 0xec2fe69cU, 0x7be094a4U,
            };
            HW_SCE_p_func100(Param_func307_func100_028);
            HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_029[] =
            {
                0xa821b521U, 0x461c4e09U, 0x65b8de9cU, 0x3ce623a5U,
            };
            HW_SCE_p_func100(Param_func307_func100_029);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(408);

            static const uint32_t Param_func307_func100_030[] =
            {
                0x1360b584U, 0xf686799dU, 0xab5b69bfU, 0x19469924U,
            };
            HW_SCE_p_func100(Param_func307_func100_030);
            HW_SCE_p_func314(408 + 64);

            static const uint32_t Param_func307_func100_031[] =
            {
                0x7af0c270U, 0x7ed6ff84U, 0x92765f4fU, 0xc608e17fU,
            };
            HW_SCE_p_func100(Param_func307_func100_031);
            HW_SCE_p_func_sub009(0x80010020U, 0x0132d44bU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_032[] =
            {
                0x6964e4b4U, 0xe864d305U, 0xc84d8bb4U, 0x07ec5ec8U,
            };
            HW_SCE_p_func100(Param_func307_func100_032);

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000010U);
            HW_SCE_p_func312(68);

            HW_SCE_p_func_sub009(0x80010020U, 0x01432c7aU);

            HW_SCE_p_func080();

            WR1_PROG(REG_00H, 0x00013203U);
            WR1_PROG(REG_2CH, 0x00000012U);
            HW_SCE_p_func312(0);

            static const uint32_t Param_func307_func100_033[] =
            {
                0xd7e164c0U, 0x1ecc338bU, 0x510e64e7U, 0x6a2613a5U,
            };
            HW_SCE_p_func100(Param_func307_func100_033);
            HW_SCE_p_func_sub009(0x80010020U, 0x019fce91U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_034[] =
            {
                0x4e82d9a2U, 0x40be6e96U, 0x0fe40003U, 0x6ff6e827U,
            };
            HW_SCE_p_func100(Param_func307_func100_034);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(612);

            static const uint32_t Param_func307_func100_035[] =
            {
                0xa348c089U, 0x43d0ff84U, 0x778ff6b8U, 0x67521438U,
            };
            HW_SCE_p_func100(Param_func307_func100_035);
            HW_SCE_p_func314(612 + 64);

            static const uint32_t Param_func307_func100_036[] =
            {
                0xdc825e03U, 0x32ed1ec4U, 0x42c88adfU, 0x371b0bc8U,
            };
            HW_SCE_p_func100(Param_func307_func100_036);
            HW_SCE_p_func_sub009(0x80010020U, 0x01e59c3dU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_037[] =
            {
                0x0e29cd80U, 0x38300037U, 0x45986240U, 0x957d7b77U,
            };
            HW_SCE_p_func100(Param_func307_func100_037);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(544);

            static const uint32_t Param_func307_func100_038[] =
            {
                0x4e55f63aU, 0x2241701bU, 0x4a60cce7U, 0x29c0bbd9U,
            };
            HW_SCE_p_func100(Param_func307_func100_038);
            HW_SCE_p_func314(544 + 64);

            WR1_PROG(REG_ECH, 0x0000b400U);
            WR1_PROG(REG_ECH, 0x00000082U);
            static const uint32_t Param_func307_func101_006[] =
            {
                0x8389d01fU, 0xe6c6ffddU, 0x142d5ccfU, 0x7a0e9c6dU,
            };
            HW_SCE_p_func101(Param_func307_func101_006);
            HW_SCE_p_func309_r1();

            static const uint32_t Param_func307_func100_039[] =
            {
                0xdee3518fU, 0xb273ad82U, 0x9fe71ee7U, 0x2edf8f2cU,
            };
            HW_SCE_p_func100(Param_func307_func100_039);
            HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_040[] =
            {
                0xb9c1509fU, 0xbf54f012U, 0x98c8652aU, 0x203d25fcU,
            };
            HW_SCE_p_func100(Param_func307_func100_040);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000020U);
            HW_SCE_p_func313(204);

            static const uint32_t Param_func307_func100_041[] =
            {
                0x8eea8326U, 0x2d4020ceU, 0x4d41424cU, 0xe4982805U,
            };
            HW_SCE_p_func100(Param_func307_func100_041);
            HW_SCE_p_func314(204 + 64);

            static const uint32_t Param_func307_func100_042[] =
            {
                0xbf7df5f8U, 0x324650caU, 0x225fdd08U, 0x90466761U,
            };
            HW_SCE_p_func100(Param_func307_func100_042);
            HW_SCE_p_func_sub009(0x80010020U, 0x016bcaa1U);

            HW_SCE_p_func080();

            static const uint32_t Param_func307_func100_043[] =
            {
                0x45705ce6U, 0xd8eacde4U, 0x3a795df3U, 0xbe5b4797U,
            };
            HW_SCE_p_func100(Param_func307_func100_043);

            WR1_PROG(REG_00H, 0x00012303U);
            WR1_PROG(REG_2CH, 0x00000022U);
            HW_SCE_p_func313(136);

            static const uint32_t Param_func307_func100_044[] =
            {
                0x1fe6691eU, 0xe9108d9aU, 0x57f0bf4cU, 0x6708d01cU,
            };
            HW_SCE_p_func100(Param_func307_func100_044);
            HW_SCE_p_func314(136 + 64);

            WR1_PROG(REG_ECH, 0x0000d260U);

            static const uint32_t Param_func307_func101_007[] =
            {
                0x6358b604U, 0x6dc2d12bU, 0x6cbb7715U, 0x3eb0ec45U,
            };
            HW_SCE_p_func101(Param_func307_func101_007);
        }

        WR1_PROG(REG_ECH, 0x01816e94U);

        static const uint32_t Param_func307_func101_008[] =
        {
            0xf737726cU, 0x7dc9f6f9U, 0xe1731169U, 0x6df578f1U,
        };
        HW_SCE_p_func101(Param_func307_func101_008);
    }

    HW_SCE_p_func_sub014(0x38008a20U, 0x00000020U, 0x00260000U);
    WR1_PROG(REG_1CH, 0x00402000U);

    static const uint32_t Param_func307_func100_045[] =
    {
        0x07ff897aU, 0x247d24c7U, 0xfbf81f2cU, 0x1baceb97U,
    };
    HW_SCE_p_func100(Param_func307_func100_045);
    HW_SCE_p_func_sub009(0x80010020U, 0x019c85beU);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_046[] =
    {
        0x5035ba16U, 0xf255a3adU, 0x1ed0bc13U, 0x92e894d5U,
    };
    HW_SCE_p_func100(Param_func307_func100_046);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000010U);
    HW_SCE_p_func312(204);

    HW_SCE_p_func_sub009(0x80010020U, 0x016bcaa1U);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_047[] =
    {
        0x4a5f6826U, 0xfa67b379U, 0x995c12b3U, 0x2c6cab19U,
    };
    HW_SCE_p_func100(Param_func307_func100_047);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    HW_SCE_p_func312(136);

    HW_SCE_p_func_sub009(0x80010020U, 0x01a67f45U);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_048[] =
    {
        0x9f2effcaU, 0xfa8f0918U, 0x75ac2514U, 0xf921ad9fU,
    };
    HW_SCE_p_func100(Param_func307_func100_048);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(476);

    static const uint32_t Param_func307_func100_049[] =
    {
        0x932f0373U, 0x17ca4781U, 0x75f63f1dU, 0x12347107U,
    };
    HW_SCE_p_func100(Param_func307_func100_049);
    HW_SCE_p_func314(476 + 64);

    static const uint32_t Param_func307_func100_050[] =
    {
        0x5e19c95eU, 0x1bf7f515U, 0xa49b9e82U, 0xdebab01eU,
    };
    HW_SCE_p_func100(Param_func307_func100_050);
    HW_SCE_p_func_sub009(0x80010020U, 0x011f5dcdU);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_051[] =
    {
        0xc5a99131U, 0x9797c7d3U, 0xea9c1037U, 0xb9f0451dU,
    };
    HW_SCE_p_func100(Param_func307_func100_051);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(408);

    static const uint32_t Param_func307_func100_052[] =
    {
        0x95a8001eU, 0x9fb1b0ecU, 0xf62ab0a9U, 0x2b362008U,
    };
    HW_SCE_p_func100(Param_func307_func100_052);
    HW_SCE_p_func314(408 + 64);

    static const uint32_t Param_func307_func100_053[] =
    {
        0x4bcfab8fU, 0x3ffb18cfU, 0x786aa6c9U, 0x3bab7324U,
    };
    HW_SCE_p_func100(Param_func307_func100_053);
    WR1_PROG(REG_24H, 0x000001c0U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000080c1U, 0x019fce91U);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_054[] =
    {
        0x4078b7d0U, 0x46f98634U, 0x880c48a1U, 0x7cf1df0dU,
    };
    HW_SCE_p_func100(Param_func307_func100_054);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000020U);
    HW_SCE_p_func313(612);

    static const uint32_t Param_func307_func100_055[] =
    {
        0x68145b96U, 0x8dfc7766U, 0xc0a86193U, 0x9d16ea7aU,
    };
    HW_SCE_p_func100(Param_func307_func100_055);
    HW_SCE_p_func314(612 + 64);

    static const uint32_t Param_func307_func100_056[] =
    {
        0xb2940826U, 0xa63e577fU, 0x926b6b1eU, 0x16a88b70U,
    };
    HW_SCE_p_func100(Param_func307_func100_056);
    WR1_PROG(REG_24H, 0x00000581U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub004(0x000040c1U, 0x01e59c3dU);

    HW_SCE_p_func080();

    static const uint32_t Param_func307_func100_057[] =
    {
        0x17c2749cU, 0x8d75c162U, 0xfd7d6916U, 0x945b30a9U,
    };
    HW_SCE_p_func100(Param_func307_func100_057);

    WR1_PROG(REG_00H, 0x00012303U);
    WR1_PROG(REG_2CH, 0x00000022U);
    HW_SCE_p_func313(544);

    static const uint32_t Param_func307_func100_058[] =
    {
        0x5cdf4f3dU, 0xc1445dfaU, 0x7c2cd0aaU, 0x42ffc8a0U,
    };
    HW_SCE_p_func100(Param_func307_func100_058);
    HW_SCE_p_func314(544 + 64);

    WR1_PROG(REG_ECH, 0x0000b400U);
    WR1_PROG(REG_ECH, 0x00000083U);
    static const uint32_t Param_func307_func101_009[] =
    {
        0x24e91976U, 0x418be7b2U, 0x2aeeec01U, 0x65afa0b3U,
    };
    HW_SCE_p_func101(Param_func307_func101_009);
    HW_SCE_p_func309_r1();

    HW_SCE_p_func_sub022(0x0000b7c0U, 0x00000090U, 0x0000381eU, 0x00007c00U);
    WR1_PROG(REG_1CH, 0x00602000U);
}
