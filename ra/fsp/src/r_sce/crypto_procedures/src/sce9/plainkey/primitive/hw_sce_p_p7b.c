/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub (const uint32_t InData_KeyIndex[],
                                                   const uint32_t InData_Text[],
                                                   uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00007b03U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x800100e0U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyIndex[0]);

    HW_SCE_p_func_sub009(0x800103a0U, 0x0000007bU);

    static const uint32_t Param_p7b_func101_001[] =
    {
        0xb075d3d7U, 0xf61f2d39U, 0xc46c26acU, 0x8db6a4f9U,
    };
    HW_SCE_p_func101(Param_p7b_func101_001);
    HW_SCE_p_func043();

    WR1_PROG(REG_ECH, 0x0000b4e0U);
    HW_SCE_p_func_sub005(0x00000010U, 0x00000058U, 0x800103a0U, 0x0000007bU);

    static const uint32_t Param_p7b_func101_002[] =
    {
        0x2309da37U, 0xf0f28872U, 0x6cfd2509U, 0xa7f31384U,
    };
    HW_SCE_p_func101(Param_p7b_func101_002);
    HW_SCE_p_func044();

    HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

    WR1_PROG(REG_28H, 0x00bf0001U);
    WR1_PROG(REG_104H, 0x00007f62U);
    WR1_PROG(REG_D0H, 0x40001f00U);
    WR1_PROG(REG_C4H, 0x02e08887U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000010U);
    for (iLoop = 0U; iLoop < 64U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    WR1_PROG(REG_00H, 0x00013203U);
    WR1_PROG(REG_2CH, 0x00000012U);
    for (iLoop = 64; iLoop < 128U; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00e08885U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

    HW_SCE_p_func_sub010(0x80010280U, 0x00008207U);
    WR1_PROG(REG_00H, 0x0000020fU);
    HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 5]);

    HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

    static const uint32_t Param_p7b_func100_001[] =
    {
        0x903b968eU, 0xad9da53cU, 0xaba0cd07U, 0x97b48c76U,
    };
    HW_SCE_p_func100(Param_p7b_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p7b_func102_001[] =
        {
            0x54d41d5aU, 0x06b3a163U, 0x53f979b9U, 0x47bf5286U,
        };
        HW_SCE_p_func102(Param_p7b_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p7b_func100_002[] =
        {
            0x461f3249U, 0x2efadb3eU, 0xbaf07020U, 0xaeeceaecU,
        };
        HW_SCE_p_func100(Param_p7b_func100_002);
        HW_SCE_p_func103();
        static const uint32_t Param_p7b_func100_003[] =
        {
            0xe5463b0dU, 0xcd954697U, 0x740fdb08U, 0xc51bf68cU,
        };
        HW_SCE_p_func100(Param_p7b_func100_003);
        HW_SCE_p_func_sub012(0x00000052U, 0x010c0c04U, 0x00000000U);

        static const uint32_t Param_p7b_func100_004[] =
        {
            0x666934e9U, 0x793e6d91U, 0x0e43c17eU, 0x0616660cU,
        };
        HW_SCE_p_func100(Param_p7b_func100_004);
        HW_SCE_p_func_sub009(0x80010020U, 0x012dc3c7U);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_005[] =
        {
            0xe5642d63U, 0xc3d07339U, 0xa16918beU, 0xa74ae22eU,
        };
        HW_SCE_p_func100(Param_p7b_func100_005);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func313(748);

        static const uint32_t Param_p7b_func100_006[] =
        {
            0x3839dc3dU, 0x00caee54U, 0xce7cc0a9U, 0xc779149fU,
        };
        HW_SCE_p_func100(Param_p7b_func100_006);
        HW_SCE_p_func314(748 + 64);

        static const uint32_t Param_p7b_func100_007[] =
        {
            0x82eca6bdU, 0xdb97e979U, 0x36f8c5f4U, 0x8f0548a4U,
        };
        HW_SCE_p_func100(Param_p7b_func100_007);
        HW_SCE_p_func_sub009(0x80010020U, 0x01b9d3a9U);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_008[] =
        {
            0x4fa851eaU, 0xfe31e49eU, 0xbf16a61aU, 0x411d969cU,
        };
        HW_SCE_p_func100(Param_p7b_func100_008);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000022U);
        HW_SCE_p_func313(680);

        static const uint32_t Param_p7b_func100_009[] =
        {
            0x9810dd6aU, 0x2c76d595U, 0xd604ae28U, 0xf8772679U,
        };
        HW_SCE_p_func100(Param_p7b_func100_009);
        HW_SCE_p_func314(680 + 64);

        HW_SCE_p_func_sub011(0x000003ffU, 0x00000022U);
        HW_SCE_p_func_sub010(0x800103e0U, 0x00008307U);

        WR1_PROG(REG_ECH, 0x3800dbe0U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p7b_func100_010[] =
        {
            0x2fd0da4fU, 0xc0180b8eU, 0x9b930e08U, 0x25b04aecU,
        };
        HW_SCE_p_func100(Param_p7b_func100_010);
        WR1_PROG(REG_2CH, 0x00000010U);
        WR1_PROG(REG_104H, 0x00003f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR64_ADDR(REG_100H, &InData_Text[0]);
        HW_SCE_p_func_sub009(0x80010020U, 0x0132d44bU);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_011[] =
        {
            0x3279f1d9U, 0x0f2dfdfbU, 0x0f0ffcb2U, 0x6357c36aU,
        };
        HW_SCE_p_func100(Param_p7b_func100_011);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000020U);
        HW_SCE_p_func313(68);

        static const uint32_t Param_p7b_func100_012[] =
        {
            0xf2add757U, 0xfa02b79bU, 0x6c5ffee4U, 0x82be2125U,
        };
        HW_SCE_p_func100(Param_p7b_func100_012);
        HW_SCE_p_func314(68 + 64);

        static const uint32_t Param_p7b_func100_013[] =
        {
            0x692e1d9fU, 0x0ff2e4d0U, 0x35103c8dU, 0x81420ab6U,
        };
        HW_SCE_p_func100(Param_p7b_func100_013);
        WR1_PROG(REG_2CH, 0x00000014U);
        WR1_PROG(REG_104H, 0x00003f67U);
        WAIT_STS(REG_104H, 31, 1);
        WR64_ADDR(REG_100H, &InData_Text[64]);
        HW_SCE_p_func_sub009(0x80010020U, 0x01432c7aU);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_014[] =
        {
            0x6856f51bU, 0x67c3861bU, 0x0f98564fU, 0x1c2173b6U,
        };
        HW_SCE_p_func100(Param_p7b_func100_014);

        WR1_PROG(REG_00H, 0x00012303U);
        WR1_PROG(REG_2CH, 0x00000024U);
        HW_SCE_p_func313(0);

        static const uint32_t Param_p7b_func100_015[] =
        {
            0x2cc7c29fU, 0x55989bb4U, 0xe0885821U, 0x47946e2bU,
        };
        HW_SCE_p_func100(Param_p7b_func100_015);
        HW_SCE_p_func314(0 + 64);

        static const uint32_t Param_p7b_func100_016[] =
        {
            0x4a70a9f1U, 0x00cbb8f2U, 0xd7e7b87cU, 0xb4b60fccU,
        };
        HW_SCE_p_func100(Param_p7b_func100_016);
        HW_SCE_p_func_sub023(0x000040d0U, 0x000005c0U);

        WR1_PROG(REG_24H, 0x04001991U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x060049c1U);
        HW_SCE_p_func_sub017(0x02001191U, 0x00a10000U);

        HW_SCE_p_func_sub023(0x000005c0U, 0x00000581U);
        HW_SCE_p_func_sub004(0x0000c0c1U, 0x01b9d3a9U);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_017[] =
        {
            0x9ac95ad5U, 0x6a879f56U, 0x923eb619U, 0x26d3747bU,
        };
        HW_SCE_p_func100(Param_p7b_func100_017);

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func312(680);
        HW_SCE_p_func_sub004(0x000011c0U, 0x012dc3c7U);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_018[] =
        {
            0x4f01d2cfU, 0x0d4eb0adU, 0xcaba60efU, 0x3970713cU,
        };
        HW_SCE_p_func100(Param_p7b_func100_018);

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000012U);
        HW_SCE_p_func312(748);

        HW_SCE_p_func_sub023(0x000080d0U, 0x04001991U);

        HW_SCE_p_func_sub023(0x060049c1U, 0x02001191U);

        HW_SCE_p_func_sub004(0x000049c1U, 0x01432c7aU);

        HW_SCE_p_func080();
        static const uint32_t Param_p7b_func100_019[] =
        {
            0xacafc88eU, 0xdbd38fc2U, 0xb6c15c6aU, 0x17f023f3U,
        };
        HW_SCE_p_func100(Param_p7b_func100_019);

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000014U);
        HW_SCE_p_func312(0);

        HW_SCE_p_func_sub009(0x80010020U, 0x0132d44bU);

        HW_SCE_p_func080();

        WR1_PROG(REG_00H, 0x00013203U);
        WR1_PROG(REG_2CH, 0x00000010U);
        HW_SCE_p_func312(68);

        WR1_PROG(REG_24H, 0x04001991U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x060049c1U);
        HW_SCE_p_func_sub017(0x02001191U, 0x00210000U);

        static const uint32_t Param_p7b_func100_020[] =
        {
            0xee4a893eU, 0x61180774U, 0x5f024dfeU, 0x354fe237U,
        };
        HW_SCE_p_func100(Param_p7b_func100_020);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p7b_func102_002[] =
            {
                0xcbeb2459U, 0x60ad9840U, 0x6aa33f73U, 0xc3e165e4U,
            };
            HW_SCE_p_func102(Param_p7b_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_ECH, 0x0000b400U);
            WR1_PROG(REG_ECH, 0x0000007bU);
            static const uint32_t Param_p7b_func101_003[] =
            {
                0xad1ea16dU, 0xf8e9b417U, 0x6e7fb16aU, 0x0cb69393U,
            };
            HW_SCE_p_func101(Param_p7b_func101_003);
            HW_SCE_p_func307_r1();

            static const uint32_t Param_p7b_func100_021[] =
            {
                0x79311285U, 0xe19252e8U, 0x6b8254d5U, 0x5380f50eU,
            };
            HW_SCE_p_func100(Param_p7b_func100_021);
            WR1_PROG(REG_2CH, 0x00000020U);
            WR1_PROG(REG_04H, 0x00000302U);
            WAIT_STS(REG_04H, 30, 1);
            RD64_ADDR(REG_100H, &OutData_Text[0]);
            static const uint32_t Param_p7b_func100_022[] =
            {
                0x05cf816cU, 0xaebbba33U, 0xc92ae771U, 0x1fba7f70U,
            };
            HW_SCE_p_func100(Param_p7b_func100_022);
            WR1_PROG(REG_2CH, 0x00000022U);
            WR1_PROG(REG_04H, 0x00000302U);
            WAIT_STS(REG_04H, 30, 1);
            RD64_ADDR(REG_100H, &OutData_Text[64]);

            static const uint32_t Param_p7b_func102_003[] =
            {
                0xd5b1053bU, 0x51915abdU, 0x25d683eeU, 0x9890acd5U,
            };
            HW_SCE_p_func102(Param_p7b_func102_003);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
