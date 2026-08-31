/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub (const uint32_t InData_CurveType[],
                                                   const uint32_t InData_KeyType[],
                                                   uint32_t       OutData_PubKeyIndex[],
                                                   uint32_t       OutData_PubKey[],
                                                   uint32_t       OutData_PrivKeyIndex[],
                                                   uint32_t       OutData_PrivKey[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000f902U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_pf9_func100_001[] =
    {
        0xba8ae618U, 0x5d822127U, 0xa6afe272U, 0x6caf7220U,
    };
    HW_SCE_p_func100(Param_pf9_func100_001);
    WR1_PROG(REG_28H, 0x008b0001U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010340U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_CurveType[0]);

    HW_SCE_p_func_sub022(0x38000f5aU, 0x00030020U, 0x0000b400U, 0x000002B4U);
    HW_SCE_p_func_sub022(0x00000060U, 0x0000b400U, 0x000003D8U, 0x00000080U);

    WR1_PROG(REG_E0H, 0x81010000U);
    WR1_PROG(REG_04H, 0x00000606U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);
    OFS_ADR  = S_RAM[0];

    static const uint32_t Param_pf9_func100_002[] =
    {
        0x0b6231a1U, 0x4082f030U, 0x48c52f06U, 0x5326581dU,
    };
    HW_SCE_p_func100(Param_pf9_func100_002);
    HW_SCE_p_func027_r2(OFS_ADR);

    static const uint32_t Param_pf9_func100_003[] =
    {
        0x0b7f37d0U, 0xd0a2a81eU, 0x474b3adfU, 0x9178501bU,
    };
    HW_SCE_p_func100(Param_pf9_func100_003);
    WR1_PROG(REG_28H, 0x008d0001U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_004[] =
    {
        0x41340726U, 0x77095143U, 0x72576630U, 0x93c93c46U,
    };
    HW_SCE_p_func100(Param_pf9_func100_004);
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    HW_SCE_p_func_sub011(0x00003213U, 0x00000011U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_005[] =
    {
        0xe7d4d41fU, 0x6983ba59U, 0x15f1cca4U, 0xf5ee9a3eU,
    };
    HW_SCE_p_func100(Param_pf9_func100_005);
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00003213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf9_func100_006[] =
    {
        0xb89c36f1U, 0xebc180b7U, 0xd992e7d8U, 0x4a0de3e7U,
    };
    HW_SCE_p_func100(Param_pf9_func100_006);
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
    WR1_PROG(REG_00H, 0x00003213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    WR1_PROG(REG_00H, 0x0000320bU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);
    WR1_PROG(REG_00H, 0x0000020bU);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
    WR1_PROG(REG_24H, 0x0000c0c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_18H, 0x00000004U);
    WR1_PROG(REG_24H, 0x0000a206U);
    WAIT_STS(REG_18H, 10, 0);
    WR1_PROG(REG_18H, 0x00000000U);

    WR1_PROG(REG_24H, 0x000016c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000682U);
    HW_SCE_p_func_sub015(0x0000a0c2U, 0x008b0001U);

    HW_SCE_p_func_sub006(0x0000dcd0U, 0x00000820U, 0x80009cd0U);

    static const uint32_t Param_pf9_func100_007[] =
    {
        0x3d1a8336U, 0x622e0f62U, 0xb1697e91U, 0xa005292fU,
    };
    HW_SCE_p_func100(Param_pf9_func100_007);
    HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);

    WR1_PROG(REG_24H, 0x100019b1U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00004404U);
    HW_SCE_p_func_sub006(0x0000e8d0U, 0x00000808U, 0x8000f0d0U);

    HW_SCE_p_func028_r2(OFS_ADR);
    static const uint32_t Param_pf9_func100_008[] =
    {
        0x64d66971U, 0x64ca9b9eU, 0x5940c872U, 0x204325b7U,
    };
    HW_SCE_p_func100(Param_pf9_func100_008);
    WR1_PROG(REG_34H, 0x00000802U);
    HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

    HW_SCE_p_func_sub002(0x00000bffU, 0x808c001fU, 0x00008333U, 0x00000021U);

    HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

    HW_SCE_p_func_sub022(0x0000b480U, 0x00000180U, 0x0000b7a0U, 0x000000f9U);

    WR1_PROG(REG_ECH, 0x00000b9cU);

    WR1_PROG(REG_E0H, 0x81010380U);
    WR1_PROG(REG_04H, 0x00000607U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    for (iLoop = 0U; iLoop < 384; iLoop++)
    {
        static const uint32_t Param_pf9_func101_001[] =
        {
            0xdbe796a4U, 0x6b1d9355U, 0xf4fd2662U, 0xd98cb7d6U,
        };
        HW_SCE_p_func101(Param_pf9_func101_001);
        HW_SCE_p_func300();

        if (S_RAM[0] == 0x00000001U)
        {
            break;
        }

        static const uint32_t Param_pf9_func101_002[] =
        {
            0xc0de3a65U, 0xfe27f27fU, 0x4d239102U, 0xb50f0d0aU,
        };
        HW_SCE_p_func101(Param_pf9_func101_002);
    }

    WR1_PROG(REG_24H, 0x00001dc0U);
    HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    static const uint32_t Param_pf9_func100_009[] =
    {
        0x1daa4a2dU, 0x7ce5aa27U, 0xa5415a80U, 0x914b2f17U,
    };
    HW_SCE_p_func100(Param_pf9_func100_009);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf9_func102_001[] =
        {
            0x162e3ccbU, 0x2f9a1e6fU, 0x693474d6U, 0x94d238e3U,
        };
        HW_SCE_p_func102(Param_pf9_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_24H, 0x00001dc0U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub001(0x000080c1U, 0x00000800U, 0x8000f4d0U, 0x000019c0U);
        HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
        WR1_PROG(REG_24H, 0x0000a0c1U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x00005004U);
        HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
        WR1_PROG(REG_ECH, 0x00000004U);

        HW_SCE_p_func_sub002(0x00000bffU, 0x808c001fU, 0x00008333U, 0x00000021U);

        for (iLoop = 0U; iLoop < 12U; iLoop++)
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

                static const uint32_t Param_pf9_func100_010[] =
                {
                    0x8f9c2a77U, 0xf33844d5U, 0x8455d6fdU, 0x13143ad2U,
                };
                HW_SCE_p_func100(Param_pf9_func100_010);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                    static const uint32_t Param_pf9_func101_003[] =
                    {
                        0x86ef67c2U, 0xe8cf24d0U, 0x37804e2aU, 0xf098530dU,
                    };
                    HW_SCE_p_func101(Param_pf9_func101_003);
                }
                else
                {
                    static const uint32_t Param_pf9_func101_004[] =
                    {
                        0xf2132842U, 0x74acefcdU, 0x0c004a87U, 0x08b9d513U,
                    };
                    HW_SCE_p_func101(Param_pf9_func101_004);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1U);

            static const uint32_t Param_pf9_func101_005[] =
            {
                0x01c83fafU, 0xef7c4381U, 0x10d53a54U, 0x051e247eU,
            };
            HW_SCE_p_func101(Param_pf9_func101_005);
        }

        WR1_PROG(REG_ECH, 0x00008be0U);
        WR1_PROG(REG_ECH, 0x00000030U);

        WR1_PROG(REG_ECH, 0x00007c1fU);
        WR1_PROG(REG_1CH, 0x00602000U);

        HW_SCE_p_func301();

        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x800103e0U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_KeyType[0]);

        WR1_PROG(REG_ECH, 0x38000fffU);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_pf9_func100_011[] =
        {
            0xce707779U, 0xfb460c41U, 0xe67274ebU, 0xc8a74ae1U,
        };
        HW_SCE_p_func100(Param_pf9_func100_011);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf9_func100_012[] =
            {
                0x0ad1252dU, 0x3da91055U, 0x5c2dc575U, 0x14254972U,
            };
            HW_SCE_p_func100(Param_pf9_func100_012);
            HW_SCE_p_func103();

            HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

            HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
            WR1_PROG(REG_00H, 0x0000020fU);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x000000f9U);

            static const uint32_t Param_pf9_func101_006[] =
            {
                0xd454d93aU, 0xf70736dcU, 0xb0a1febbU, 0xc00b81f0U,
            };
            HW_SCE_p_func101(Param_pf9_func101_006);
            HW_SCE_p_func043();

            HW_SCE_p_func076();

            HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f9U);

            static const uint32_t Param_pf9_func101_007[] =
            {
                0xa5113cbeU, 0x6d527565U, 0x8445bbf4U, 0xa1034407U,
            };
            HW_SCE_p_func101(Param_pf9_func101_007);
            HW_SCE_p_func044();

            static const uint32_t Param_pf9_func100_013[] =
            {
                0x6762285cU, 0x0d4cf93dU, 0xa3506f40U, 0x1ceecb69U,
            };
            HW_SCE_p_func100(Param_pf9_func100_013);
            WR1_PROG(REG_D0H, 0x40000200U);
            WR1_PROG(REG_C4H, 0x02e087b7U);
            HW_SCE_p_func_sub011(0x00002333U, 0x0000002dU);

            WR1_PROG(REG_04H, 0x00000232U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[1]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[5]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[9]);

            static const uint32_t Param_pf9_func100_014[] =
            {
                0xe81c9889U, 0x67692950U, 0xbe826a22U, 0x2e8a4dbeU,
            };
            HW_SCE_p_func100(Param_pf9_func100_014);
            HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

            WR1_PROG(REG_D0H, 0x40000000U);
            HW_SCE_p_func_sub013(0x000089c5U, 0x00002213U);

            WR1_PROG(REG_04H, 0x00000212U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[13]);

            static const uint32_t Param_pf9_func100_015[] =
            {
                0x13b2eeb6U, 0xc897657dU, 0x440a39ffU, 0xa369cdd9U,
            };
            HW_SCE_p_func100(Param_pf9_func100_015);
            WR1_PROG(REG_E0H, 0x81010000U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &OutData_PrivKeyIndex[0]);

            static const uint32_t Param_pf9_func100_016[] =
            {
                0x5582f747U, 0x39e01cb7U, 0x3691c4c7U, 0xe0da29edU,
            };
            HW_SCE_p_func100(Param_pf9_func100_016);
            HW_SCE_p_func103();

            HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

            HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
            WR1_PROG(REG_00H, 0x0000020fU);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000027U);

            static const uint32_t Param_pf9_func101_008[] =
            {
                0x70f41c99U, 0xba1e2bc7U, 0xa7b2ae76U, 0xe6f2e9fcU,
            };
            HW_SCE_p_func101(Param_pf9_func101_008);
            HW_SCE_p_func043();

            HW_SCE_p_func077();

            HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x00000028U);

            static const uint32_t Param_pf9_func101_009[] =
            {
                0x2cabf676U, 0x643a1a6bU, 0xb94816b0U, 0xd195fadaU,
            };
            HW_SCE_p_func101(Param_pf9_func101_009);
            HW_SCE_p_func044();

            static const uint32_t Param_pf9_func100_017[] =
            {
                0x3901d920U, 0x63dad967U, 0x365fd72cU, 0x2905477dU,
            };
            HW_SCE_p_func100(Param_pf9_func100_017);
            WR1_PROG(REG_D0H, 0x40000200U);
            WR1_PROG(REG_C4H, 0x02e08887U);
            HW_SCE_p_func_sub011(0x00002333U, 0x00000022U);

            WR1_PROG(REG_04H, 0x00000232U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[1]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[5]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[9]);

            static const uint32_t Param_pf9_func100_018[] =
            {
                0xdc1ff7abU, 0x50b66339U, 0x2bc1b6f1U, 0x0303639fU,
            };
            HW_SCE_p_func100(Param_pf9_func100_018);
            WR1_PROG(REG_D0H, 0x40000200U);
            WR1_PROG(REG_C4H, 0x00e08887U);
            HW_SCE_p_func_sub011(0x00002333U, 0x00000023U);

            WR1_PROG(REG_04H, 0x00000232U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[13]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[17]);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[21]);

            static const uint32_t Param_pf9_func100_019[] =
            {
                0x7d1ad014U, 0xbcf9baa2U, 0x3a53ca7cU, 0x64a40b32U,
            };
            HW_SCE_p_func100(Param_pf9_func100_019);
            HW_SCE_p_func_sub018(0x00000052U, 0x40000000U, 0x000089c4U);
            WR1_PROG(REG_100H, change_endian_long(0x00000000U));

            WR1_PROG(REG_04H, 0x00000212U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_PubKeyIndex[25]);

            static const uint32_t Param_pf9_func100_020[] =
            {
                0x5e7bb2b6U, 0xa502456fU, 0xbca534c6U, 0x74f8870fU,
            };
            HW_SCE_p_func100(Param_pf9_func100_020);
            WR1_PROG(REG_E0H, 0x81010000U);
            WR1_PROG(REG_04H, 0x00000606U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &OutData_PubKeyIndex[0]);

            static const uint32_t Param_pf9_func101_010[] =
            {
                0x63efbb39U, 0xe075f07eU, 0x3022bf96U, 0x349cd2ecU,
            };
            HW_SCE_p_func101(Param_pf9_func101_010);
        }
        else
        {
            static const uint32_t Param_pf9_func100_021[] =
            {
                0xbb9c7e38U, 0x41ec0365U, 0x69b55d2eU, 0x2b43c754U,
            };
            HW_SCE_p_func100(Param_pf9_func100_021);
            WR1_PROG(REG_2CH, 0x0000002dU);
            WR1_PROG(REG_04H, 0x00000332U);
            WAIT_STS(REG_04H, 30, 1);
            RD12_ADDR(REG_100H, &OutData_PrivKey[0]);

            static const uint32_t Param_pf9_func100_022[] =
            {
                0x6de30be7U, 0x126dbb17U, 0xf401140aU, 0x0ef0ee36U,
            };
            HW_SCE_p_func100(Param_pf9_func100_022);
            WR1_PROG(REG_2CH, 0x00000022U);
            WR1_PROG(REG_04H, 0x00000332U);
            WAIT_STS(REG_04H, 30, 1);
            RD12_ADDR(REG_100H, &OutData_PubKey[0]);

            static const uint32_t Param_pf9_func100_023[] =
            {
                0x02d5e48aU, 0x6ed01b95U, 0x7f1bf0bcU, 0x4a45ecf6U,
            };
            HW_SCE_p_func100(Param_pf9_func100_023);
            WR1_PROG(REG_2CH, 0x00000023U);
            WR1_PROG(REG_04H, 0x00000332U);
            WAIT_STS(REG_04H, 30, 1);
            RD12_ADDR(REG_100H, &OutData_PubKey[12]);

            static const uint32_t Param_pf9_func101_011[] =
            {
                0xd01e5a9fU, 0xd4e75e84U, 0xaf1653baU, 0xc7655bbbU,
            };
            HW_SCE_p_func101(Param_pf9_func101_011);
        }

        static const uint32_t Param_pf9_func102_002[] =
        {
            0xa048ac0cU, 0x830190d2U, 0xb1bc5a15U, 0xdba0fb07U,
        };
        HW_SCE_p_func102(Param_pf9_func102_002);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
