/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_MsgDgst[],
                                                uint32_t       OutData_Signature[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000f502U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_pf5_func100_001[] =
    {
        0x312c0105U, 0xe39ac18fU, 0x3efce70dU, 0x82ee3947U,
    };
    HW_SCE_p_func100(Param_pf5_func100_001);
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

    static const uint32_t Param_pf5_func100_002[] =
    {
        0x254f5bceU, 0xd0e0ae32U, 0x5e264fe5U, 0xe6343b1bU,
    };
    HW_SCE_p_func100(Param_pf5_func100_002);
    HW_SCE_p_func027_r2(OFS_ADR);
    static const uint32_t Param_pf5_func100_003[] =
    {
        0x5b67e65cU, 0x89b76efbU, 0x195f48f7U, 0x3a5ca1cfU,
    };
    HW_SCE_p_func100(Param_pf5_func100_003);

    HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);
    WR1_PROG(REG_24H, 0x100019b1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x8000c0c1U);

    HW_SCE_p_func103();
    static const uint32_t Param_pf5_func100_004[] =
    {
        0x4d397cd5U, 0xbd352a05U, 0x2cc33cbaU, 0xd1dd9e81U,
    };
    HW_SCE_p_func100(Param_pf5_func100_004);
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    HW_SCE_p_func_sub011(0x00003213U, 0x00000011U);

    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    WR1_PROG(REG_00H, 0x00003213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    static const uint32_t Param_pf5_func100_005[] =
    {
        0xd3087966U, 0xf666cb88U, 0x5f0fa4acU, 0xa25c4eceU,
    };
    HW_SCE_p_func100(Param_pf5_func100_005);
    HW_SCE_p_func103();
    HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

    WR1_PROG(REG_00H, 0x00003213U);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800U);

    HW_SCE_p_func_sub023(0x00001228U, 0x100019b1U);
    HW_SCE_p_func_sub023(0x000019a1U, 0x0000a0c1U);

    static const uint32_t Param_pf5_func100_006[] =
    {
        0x03845026U, 0xbbcf7d47U, 0xedb094b2U, 0x90542a64U,
    };
    HW_SCE_p_func100(Param_pf5_func100_006);

    HW_SCE_p_func028_r2(OFS_ADR);
    WR1_PROG(REG_34H, 0x00000802U);
    HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

    WR1_PROG(REG_ECH, 0x0000b7e0U);
    HW_SCE_p_func_sub002(0x00000040U, 0x808c001fU, 0x00008333U, 0x00000024U);

    HW_SCE_p_func_sub023(0x00001dc0U, 0x0000c0c1U);

    HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);
    WR1_PROG(REG_24H, 0x100019b1U);
    WAIT_STS(REG_24H, 21, 0);
    HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00000dc0U);
    HW_SCE_p_func_sub023(0x000080c1U, 0x00001028U);
    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
    WR1_PROG(REG_24H, 0x0000e0c1U);
    WAIT_STS(REG_24H, 21, 0);

    WR1_PROG(REG_24H, 0x00000dc0U);
    HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7e0U);
    HW_SCE_p_func_sub002(0x00000080U, 0x808c001fU, 0x00008333U, 0x00000020U);

    WR1_PROG(REG_24H, 0x00005cd0U);
    WAIT_STS(REG_24H, 21, 0);

    HW_SCE_p_func_sub002(0x00000bffU, 0x808c001fU, 0x00008333U, 0x00000021U);

    HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

    HW_SCE_p_func_sub022(0x0000b480U, 0x00000180U, 0x0000b7a0U, 0x000000f5U);

    WR1_PROG(REG_ECH, 0x00000b9cU);

    static const uint32_t Param_pf5_func100_007[] =
    {
        0x61153670U, 0xfb15e115U, 0xdfc162fdU, 0xc428f26aU,
    };
    HW_SCE_p_func100(Param_pf5_func100_007);
    WR1_PROG(REG_E0H, 0x81010380U);
    WR1_PROG(REG_04H, 0x00000607U);
    WAIT_STS(REG_04H, 30, 1);
    RD1_ADDR(REG_100H, &S_RAM[0]);
    S_RAM[0] = change_endian_long(S_RAM[0]);

    for (iLoop = 0U; iLoop < 384; iLoop++)
    {
        static const uint32_t Param_pf5_func101_001[] =
        {
            0x60de8cceU, 0x0a5d67faU, 0xd6c84176U, 0xc734a08bU,
        };
        HW_SCE_p_func101(Param_pf5_func101_001);

        HW_SCE_p_func300();

        if (S_RAM[0] == 0x00000001U)
        {
            break;
        }

        static const uint32_t Param_pf5_func101_002[] =
        {
            0x8c1694a4U, 0xf381dd63U, 0x9a202387U, 0x1768b8d1U,
        };
        HW_SCE_p_func101(Param_pf5_func101_002);
    }

    WR1_PROG(REG_24H, 0x00001dc0U);
    HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    static const uint32_t Param_pf5_func100_008[] =
    {
        0x39c0dc33U, 0x9bcb18aaU, 0x36173556U, 0x886fc9aeU,
    };
    HW_SCE_p_func100(Param_pf5_func100_008);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf5_func102_001[] =
        {
            0x11db319aU, 0x49dca8d9U, 0x36d85a2fU, 0x6b6d45e6U,
        };
        HW_SCE_p_func102(Param_pf5_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub023(0x00001dc0U, 0x000080c1U);

        HW_SCE_p_func_sub001(0x000015c0U, 0x00000800U, 0x800040c1U, 0x000019c0U);
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

                static const uint32_t Param_pf5_func100_009[] =
                {
                    0x04116ab8U, 0xf01acb4dU, 0x8c467b1eU, 0x3d7c1bc3U,
                };
                HW_SCE_p_func100(Param_pf5_func100_009);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                    static const uint32_t Param_pf5_func101_003[] =
                    {
                        0x0e9406bfU, 0x21a9c2a2U, 0xf4105826U, 0xfc3f06f7U,
                    };
                    HW_SCE_p_func101(Param_pf5_func101_003);
                }
                else
                {
                    static const uint32_t Param_pf5_func101_004[] =
                    {
                        0x72a17c90U, 0x7c36ae1eU, 0xb595c4e4U, 0xae6a585aU,
                    };
                    HW_SCE_p_func101(Param_pf5_func101_004);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1U);

            static const uint32_t Param_pf5_func101_005[] =
            {
                0x812e0e4eU, 0x578b4115U, 0x11558fe1U, 0x2dc4c15bU,
            };
            HW_SCE_p_func101(Param_pf5_func101_005);
        }

        WR1_PROG(REG_ECH, 0x00008be0U);
        WR1_PROG(REG_ECH, 0x00000030U);

        WR1_PROG(REG_ECH, 0x00007c1fU);
        WR1_PROG(REG_1CH, 0x00602000U);

        HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);

        WR1_PROG(REG_24H, 0x000019a1U);
        HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000080U, 0x818c001fU, 0x00003833U, 0x00000012U);

        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

        WR1_PROG(REG_24H, 0x000009c0U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub001(0x0000a0c1U, 0x00000008U, 0x800012c0U, 0x000040c2U);
        HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

        WR1_PROG(REG_24H, 0x000009c0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_34H, 0x00000800U);
        HW_SCE_p_func_sub001(0x800060c1U, 0x00000008U, 0x800016c0U, 0x000060c2U);
        HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

        HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
        WR1_PROG(REG_24H, 0x000019a1U);
        HW_SCE_p_func_sub016(0x000060c1U, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000040U, 0x818c001fU, 0x00003833U, 0x00000014U);

        HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);
        WR1_PROG(REG_24H, 0x100019b1U);
        WAIT_STS(REG_24H, 21, 0);
        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00006404U);
        HW_SCE_p_func_sub001(0x00006c04U, 0x00000800U, 0x8000ecd0U, 0x0000a8d0U);

        WR1_PROG(REG_34H, 0x00000020U);
        HW_SCE_p_func_sub023(0x80001dc0U, 0x000040c1U);

        HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

        HW_SCE_p_func_sub023(0x000060c1U, 0x00000828U);
        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
        WR1_PROG(REG_24H, 0x000040c1U);
        WAIT_STS(REG_24H, 21, 0);

        WR1_PROG(REG_24H, 0x000009c0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_pf5_func100_010[] =
        {
            0xcf6556d4U, 0xf5d2420bU, 0xc8dde221U, 0x0d9cb2c7U,
        };
        HW_SCE_p_func100(Param_pf5_func100_010);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf5_func102_002[] =
            {
                0x7fcc5618U, 0x320d458dU, 0x741a2441U, 0x37fd27f7U,
            };
            HW_SCE_p_func102(Param_pf5_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_24H, 0x00000ac0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000800U);
            HW_SCE_p_func_sub001(0x800060c2U, 0x00000002U, 0x800009c0U, 0x000080c1U);

            HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
            HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

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

                    static const uint32_t Param_pf5_func100_011[] =
                    {
                        0xdb684c16U, 0xad882196U, 0x69ddeeb8U, 0x68182e14U,
                    };
                    HW_SCE_p_func100(Param_pf5_func100_011);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_pf5_func101_006[] =
                        {
                            0x09cb3c18U, 0x5022d562U, 0xbc96621fU, 0x02f4e99eU,
                        };
                        HW_SCE_p_func101(Param_pf5_func101_006);
                    }
                    else
                    {
                        static const uint32_t Param_pf5_func101_007[] =
                        {
                            0xc154907dU, 0x3be52efcU, 0xcaee0c01U, 0x3cc1eca4U,
                        };
                        HW_SCE_p_func101(Param_pf5_func101_007);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_pf5_func101_008[] =
                {
                    0xc37a8313U, 0x7f7e61f2U, 0xcf184d70U, 0xad35711dU,
                };
                HW_SCE_p_func101(Param_pf5_func101_008);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000030U);

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);

            HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

            WR1_PROG(REG_2CH, 0x00000011U);
            WR1_PROG(REG_104H, 0x00000b67U);
            WAIT_STS(REG_104H, 31, 1);
            WR12_ADDR(REG_100H, &InData_MsgDgst[0]);

            WR1_PROG(REG_34H, 0x00000020U);
            WR1_PROG(REG_24H, 0x80001dc0U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000800U);
            HW_SCE_p_func_sub001(0x800040c1U, 0x00000002U, 0x80000a2cU, 0x100019b1U);
            WR1_PROG(REG_24H, 0x000019a1U);
            WAIT_STS(REG_24H, 21, 0);
            WR1_PROG(REG_34H, 0x00000800U);
            HW_SCE_p_func_sub001(0x800040c1U, 0x00000002U, 0x800009c0U, 0x0000a0c1U);
            WR1_PROG(REG_34H, 0x00000020U);
            HW_SCE_p_func_sub006(0x80001dc0U, 0x00000800U, 0x800040c1U);

            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000f5U);

            static const uint32_t Param_pf5_func101_009[] =
            {
                0x596a904bU, 0x3314484cU, 0xcdb16c37U, 0xa8077997U,
            };
            HW_SCE_p_func101(Param_pf5_func101_009);
            HW_SCE_p_func043();

            HW_SCE_p_func076();

            HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f5U);

            static const uint32_t Param_pf5_func101_010[] =
            {
                0xf196b0d1U, 0x2c071f11U, 0xef46062dU, 0xe381c81dU,
            };
            HW_SCE_p_func101(Param_pf5_func101_010);
            HW_SCE_p_func044();

            WR1_PROG(REG_104H, 0x00000b62U);
            WR1_PROG(REG_D0H, 0x40000200U);
            WR1_PROG(REG_C4H, 0x02f087b7U);

            WR1_PROG(REG_00H, 0x00003233U);
            WR1_PROG(REG_2CH, 0x00000018U);

            for (iLoop = 0U; iLoop < 12U; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
                iLoop = iLoop + 4U;
            }

            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_pf5_func100_012[] =
            {
                0x040820f3U, 0x57958e1eU, 0xf4199077U, 0x88f0a702U,
            };
            HW_SCE_p_func100(Param_pf5_func100_012);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pf5_func102_003[] =
                {
                    0x5d4fa2dcU, 0x09346111U, 0xd90d7c4fU, 0x3877f5daU,
                };
                HW_SCE_p_func102(Param_pf5_func102_003);
                WR1_PROG(REG_1B8H, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub001(0x000015c0U, 0x00000008U, 0x80000c2dU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
                WR1_PROG(REG_24H, 0x000019a1U);
                WAIT_STS(REG_24H, 21, 0);
                HW_SCE_p_func_sub001(0x000080c1U, 0x00000002U, 0x8000082cU, 0x100019b1U);
                WR1_PROG(REG_24H, 0x000019a1U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_34H, 0x00000800U);
                HW_SCE_p_func_sub001(0x800040c1U, 0x00000002U, 0x800009c0U, 0x00000591U);
                WR1_PROG(REG_1CH, 0x00001f00U);
                WR1_PROG(REG_1CH, 0x00210000U);

                static const uint32_t Param_pf5_func100_013[] =
                {
                    0x47e77302U, 0xe077a25cU, 0xdb1110c9U, 0x5aa753c7U,
                };
                HW_SCE_p_func100(Param_pf5_func100_013);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_pf5_func102_004[] =
                    {
                        0x793d7493U, 0x9ec5b3eaU, 0xb0aa4fc7U, 0x0c1c8446U,
                    };
                    HW_SCE_p_func102(Param_pf5_func102_004);
                    WR1_PROG(REG_1B8H, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    static const uint32_t Param_pf5_func100_014[] =
                    {
                        0x146cf125U, 0xea842b6aU, 0xe3494589U, 0xda9fcd01U,
                    };
                    HW_SCE_p_func100(Param_pf5_func100_014);
                    WR1_PROG(REG_2CH, 0x0000002bU);
                    WR1_PROG(REG_04H, 0x00000332U);
                    WAIT_STS(REG_04H, 30, 1);
                    RD12_ADDR(REG_100H, &OutData_Signature[0]);

                    static const uint32_t Param_pf5_func100_015[] =
                    {
                        0xd530f48bU, 0x02e526f6U, 0x375ec265U, 0x6eb53f6fU,
                    };
                    HW_SCE_p_func100(Param_pf5_func100_015);
                    WR1_PROG(REG_2CH, 0x0000002aU);
                    WR1_PROG(REG_04H, 0x00000332U);
                    WAIT_STS(REG_04H, 30, 1);
                    RD12_ADDR(REG_100H, &OutData_Signature[12]);

                    static const uint32_t Param_pf5_func102_005[] =
                    {
                        0x58b223e8U, 0x9262ba2cU, 0x01fed64bU, 0x9da18bd7U,
                    };
                    HW_SCE_p_func102(Param_pf5_func102_005);
                    WR1_PROG(REG_1B8H, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
