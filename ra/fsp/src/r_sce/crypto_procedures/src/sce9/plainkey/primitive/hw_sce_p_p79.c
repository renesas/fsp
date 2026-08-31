/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub (const uint32_t InData_KeyIndex[],
                                                   const uint32_t InData_Text[],
                                                   uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00007903U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x00000079U);

    static const uint32_t Param_p79_func101_001[] =
    {
        0x9930b009U, 0x81e95a8cU, 0xe8edfc49U, 0xa9c2f412U,
    };
    HW_SCE_p_func101(Param_p79_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x0000000eU, 0x00000058U, 0x800103a0U, 0x00000079U);

    static const uint32_t Param_p79_func101_002[] =
    {
        0x6b0497cfU, 0x2c4fe92bU, 0x51befe47U, 0xb7bd24b5U,
    };
    HW_SCE_p_func101(Param_p79_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    WR1_PROG(REG_28H, 0x009f0001U);
    WR1_PROG(REG_104H, 0x00006362U);
    WR1_PROG(REG_D0H, 0x40001800U);
    WR1_PROG(REG_C4H, 0x02e08887U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000010U);
    for (iLoop = 0U; iLoop < 32U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000012U);
    for (iLoop = 32; iLoop < 64U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00003283U);
    WR1_PROG(REG_2CH, 0x00000014U);
    for (iLoop = 64; iLoop < 96U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

    HW_SCE_p_func_sub010(0x80010280U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 5]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p79_func100_001[] =
    {
        0x7ee8691bU, 0x37b5f60aU, 0x87859dc1U, 0x394206a8U,
    };
    HW_SCE_p_func100(Param_p79_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p79_func102_001[] =
        {
            0x1e94bb70U, 0xd0807b52U, 0xb19b60a0U, 0x875879ffU,
        };
        HW_SCE_p_func102(Param_p79_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p79_func100_002[] =
        {
            0x115bdcb3U, 0x073a2576U, 0xa28bdb20U, 0x2f2d587aU,
        };
        HW_SCE_p_func100(Param_p79_func100_002);
        HW_SCE_p_func103();
        static const uint32_t Param_p79_func100_003[] =
        {
            0xa970f4faU, 0xb28af495U, 0x5d28b925U, 0x2ec6dfa3U,
        };
        HW_SCE_p_func100(Param_p79_func100_003);
        HW_SCE_p_func_sub012(0x00000052U, 0x010c0c04U, 0x00000000U);

        static const uint32_t Param_p79_func100_004[] =
        {
            0x4350ff0fU, 0x54672d5aU, 0x3e9ea952U, 0xed9785daU,
        };
        HW_SCE_p_func100(Param_p79_func100_004);
        HW_SCE_p_func_sub009(0x80010020U, 0x018e0c4cU);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_005[] =
        {
            0x830263b0U, 0x987f3967U, 0xdd7089eaU, 0xfb6164b3U,
        };
        HW_SCE_p_func100(Param_p79_func100_005);
        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func319(752);

        static const uint32_t Param_p79_func100_006[] =
        {
            0x7d8ff34eU, 0x39614ffaU, 0x02d73beeU, 0x32051da9U,
        };
        HW_SCE_p_func100(Param_p79_func100_006);
        HW_SCE_p_func314(752 + 32);

        static const uint32_t Param_p79_func100_007[] =
        {
            0x336798e0U, 0x6d49a1fbU, 0x49bd8f75U, 0x8a0e9fa7U,
        };
        HW_SCE_p_func100(Param_p79_func100_007);
        HW_SCE_p_func_sub009(0x80010020U, 0x010273a4U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_008[] =
        {
            0xa0287871U, 0x20908695U, 0x4fda4e72U, 0x8d0d67a8U,
        };
        HW_SCE_p_func100(Param_p79_func100_008);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func319(716);

        static const uint32_t Param_p79_func100_009[] =
        {
            0xe3e3d8acU, 0xa1e30561U, 0x83e21b2eU, 0x7d239563U,
        };
        HW_SCE_p_func100(Param_p79_func100_009);
        HW_SCE_p_func314(716 + 32);

        static const uint32_t Param_p79_func100_010[] =
        {
            0xfa3af305U, 0xdb097dcfU, 0xf809dec6U, 0xfd840cdeU,
        };
        HW_SCE_p_func100(Param_p79_func100_010);
        HW_SCE_p_func_sub009(0x80010020U, 0x019410dfU);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_011[] =
        {
            0x9fd08737U, 0x4f2d0f36U, 0x1b1a4873U, 0xf3b346f4U,
        };
        HW_SCE_p_func100(Param_p79_func100_011);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func319(680);

        static const uint32_t Param_p79_func100_012[] =
        {
            0xe3cbffc7U, 0xa0ff85e1U, 0x18893f9fU, 0xae2c8b0eU,
        };
        HW_SCE_p_func100(Param_p79_func100_012);
        HW_SCE_p_func314(680 + 32);

        HW_SCE_p_func_sub011(0x0000037fU, 0x00000024U);
        HW_SCE_p_func_sub010(0x800103e0U, 0x00008307U);

        WR1_PROG(REG_ECH, 0x3800dbe0U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00001f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR32_ADDR(REG_100H, &InData_Text[0]);
        WR1_PROG(REG_24H, 0x0000a0d0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00bf0001U);
        WR1_PROG(REG_2CH, 0x00000014U);
        WR1_PROG(REG_104H, 0x00003f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR64_ADDR(REG_100H, &InData_Text[32]);
        WR1_PROG(REG_28H, 0x009f0001U);

        static const uint32_t Param_p79_func100_013[] =
        {
            0x3b932c9dU, 0xe60b45f9U, 0x4c68dc70U, 0xbab75753U,
        };
        HW_SCE_p_func100(Param_p79_func100_013);
        HW_SCE_p_func_sub009(0x80010020U, 0x019de420U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_014[] =
        {
            0xf14dc81dU, 0x08c983d3U, 0x2ab61a1eU, 0x451526acU,
        };
        HW_SCE_p_func100(Param_p79_func100_014);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func319(72);

        static const uint32_t Param_p79_func100_015[] =
        {
            0x2038a22aU, 0xb18b5053U, 0xaeaa8fb6U, 0x146a776cU,
        };
        HW_SCE_p_func100(Param_p79_func100_015);
        HW_SCE_p_func314(72 + 32);

        static const uint32_t Param_p79_func100_016[] =
        {
            0x98d4795dU, 0xc5730533U, 0x8758a926U, 0x59185715U,
        };
        HW_SCE_p_func100(Param_p79_func100_016);
        HW_SCE_p_func_sub009(0x80010020U, 0x019969f4U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_017[] =
        {
            0x219de09dU, 0x3123024fU, 0x16875a12U, 0x75a53b8eU,
        };
        HW_SCE_p_func100(Param_p79_func100_017);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000025U);
        HW_SCE_p_func319(36);

        static const uint32_t Param_p79_func100_018[] =
        {
            0x95492014U, 0xb970b606U, 0x4ce340ceU, 0x17ca043aU,
        };
        HW_SCE_p_func100(Param_p79_func100_018);
        HW_SCE_p_func314(36 + 32);

        static const uint32_t Param_p79_func100_019[] =
        {
            0x815aba79U, 0x0c7e88ddU, 0xaa881027U, 0x49e7c658U,
        };
        HW_SCE_p_func100(Param_p79_func100_019);
        HW_SCE_p_func_sub009(0x80010020U, 0x01fe1091U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_020[] =
        {
            0x50c99eb5U, 0xb362b304U, 0xa260fd0cU, 0xd13b0444U,
        };
        HW_SCE_p_func100(Param_p79_func100_020);

        WR1_PROG(REG_00H, 0x00002383U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func319(0);

        static const uint32_t Param_p79_func100_021[] =
        {
            0x99efb969U, 0xc88fe10cU, 0x3a83bfc6U, 0xd056ba30U,
        };
        HW_SCE_p_func100(Param_p79_func100_021);
        HW_SCE_p_func314(0 + 32);

        static const uint32_t Param_p79_func100_022[] =
        {
            0x037788a3U, 0x79be5549U, 0xe46f539eU, 0x5aab9302U,
        };
        HW_SCE_p_func100(Param_p79_func100_022);
        HW_SCE_p_func_sub020(0x00bf0001U, 0x000040d0U, 0x000005c0U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x04001991U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000049c1U);
        HW_SCE_p_func_sub017(0x02001191U, 0x00a10000U);

        HW_SCE_p_func_sub023(0x000005c0U, 0x00000581U);
        WR1_PROG(REG_24H, 0x0000c0c1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub008(0x009f0001U, 0x019410dfU);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_023[] =
        {
            0x526c5725U, 0x2b7bafbcU, 0x6f8db96cU, 0xeb735ef5U,
        };
        HW_SCE_p_func100(Param_p79_func100_023);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func320(680);
        HW_SCE_p_func_sub004(0x000011c0U, 0x010273a4U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_024[] =
        {
            0x0865271cU, 0x120ff1a1U, 0x71f5a98aU, 0xfccde033U,
        };
        HW_SCE_p_func100(Param_p79_func100_024);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000011U);
        HW_SCE_p_func320(716);
        HW_SCE_p_func_sub004(0x000016c0U, 0x018e0c4cU);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_025[] =
        {
            0xaf4abd00U, 0x732a43fdU, 0xf1b0a12cU, 0x8b129d76U,
        };
        HW_SCE_p_func100(Param_p79_func100_025);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000012U);
        HW_SCE_p_func320(752);
        WR1_PROG(REG_24H, 0x000060d0U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub020(0x00bf0001U, 0x000080d0U, 0x04001991U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub023(0x060049c1U, 0x02001191U);

        WR1_PROG(REG_24H, 0x000049c1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub008(0x009f0001U, 0x01fe1091U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_026[] =
        {
            0x31290a2bU, 0xbf7356c4U, 0x4d0cccfaU, 0x22e1373fU,
        };
        HW_SCE_p_func100(Param_p79_func100_026);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func320(0);

        HW_SCE_p_func_sub009(0x80010020U, 0x019969f4U);

        HW_SCE_p_func080();

        static const uint32_t Param_p79_func100_027[] =
        {
            0x8c99cd47U, 0x2868da89U, 0x91452e8eU, 0x7963c836U,
        };
        HW_SCE_p_func100(Param_p79_func100_027);
        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000015U);
        HW_SCE_p_func320(36);

        HW_SCE_p_func_sub009(0x80010020U, 0x019de420U);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00003283U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func320(72);

        WR1_PROG(REG_24H, 0x0000a0d0U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub020(0x00bf0001U, 0x04001991U, 0x060049c1U);
        HW_SCE_p_func_sub017(0x02001191U, 0x00210000U);

        static const uint32_t Param_p79_func100_028[] =
        {
            0x3578337cU, 0xf2829ff4U, 0xcfc2f8a8U, 0xf4ebc9baU,
        };
        HW_SCE_p_func100(Param_p79_func100_028);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p79_func102_002[] =
            {
                0xa3c643d5U, 0xbeb0bc69U, 0xc8cb1884U, 0x31c8ab72U,
            };
            HW_SCE_p_func102(Param_p79_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000b7a0U);
            WR1_PROG(REG_ECH, 0x00000079U);
            static const uint32_t Param_p79_func101_003[] =
            {
                0xee77e57cU, 0x9533b284U, 0x8d1c3bc5U, 0x7dafdaabU,
            };
            HW_SCE_p_func101(Param_p79_func101_003);
            HW_SCE_p_func325_r1();

            WR1_PROG(REG_28H, 0x009f0001U);
            static const uint32_t Param_p79_func100_029[] =
            {
                0xad4e3029U, 0x051ef4dfU, 0xf5ba502aU, 0x0f985354U,
            };
            HW_SCE_p_func100(Param_p79_func100_029);
            WR1_PROG(REG_2CH, 0x00000020U);
            WR1_PROG(REG_04H, 0x00000382U);
            WAIT_STS(REG_04H, 30, 1);
            RD32_ADDR(REG_100H, &OutData_Text[0]);
            WR1_PROG(REG_28H, 0x00bf0001U);
            static const uint32_t Param_p79_func100_030[] =
            {
                0x1ecc620bU, 0x57edb624U, 0x96cb0511U, 0x89d05b36U,
            };
            HW_SCE_p_func100(Param_p79_func100_030);
            WR1_PROG(REG_2CH, 0x00000022U);
            WR1_PROG(REG_04H, 0x00000302U);
            WAIT_STS(REG_04H, 30, 1);
            RD64_ADDR(REG_100H, &OutData_Text[32]);

            static const uint32_t Param_p79_func102_003[] =
            {
                0x0bd7bf02U, 0xee336e55U, 0xbb83a9edU, 0x0c98b241U,
            };
            HW_SCE_p_func102(Param_p79_func102_003);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
