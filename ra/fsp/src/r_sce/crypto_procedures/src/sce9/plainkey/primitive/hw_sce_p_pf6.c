/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub (const uint32_t InData_CurveType[],
                                                    const uint32_t InData_KeyIndex[],
                                                    const uint32_t InData_MsgDgst[],
                                                    const uint32_t InData_Signature[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000f601U);
    WR1_PROG(REG_108H, 0x00000000U);

    static const uint32_t Param_pf6_func100_001[] =
    {
        0xde86a436U, 0x5028d235U, 0xd797fae2U, 0xe51894ddU,
    };
    HW_SCE_p_func100(Param_pf6_func100_001);
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

    static const uint32_t Param_pf6_func100_002[] =
    {
        0x50f75db7U, 0x80f401ceU, 0x2b894e39U, 0xb0cb9752U,
    };
    HW_SCE_p_func100(Param_pf6_func100_002);
    HW_SCE_p_func027_r2(OFS_ADR);

    WR1_PROG(REG_34H, 0x00000800U);
    HW_SCE_p_func_sub006(0x80006cd0U, 0x00000800U, 0x8000bcd0U);

    WR1_PROG(REG_2CH, 0x00000015U);
    WR1_PROG(REG_104H, 0x00000b67U);
    WAIT_STS(REG_104H, 31, 1);
    WR12_ADDR(REG_100H, &InData_Signature[0]);

    WR1_PROG(REG_2CH, 0x00000010U);
    WR1_PROG(REG_104H, 0x00000b67U);
    WAIT_STS(REG_104H, 31, 1);
    WR12_ADDR(REG_100H, &InData_Signature[12]);

    WR1_PROG(REG_ECH, 0x0000b7e0U);
    HW_SCE_p_func_sub002(0x00000140U, 0x808c001fU, 0x00008333U, 0x00000024U);

    HW_SCE_p_func_sub023(0x000070d0U, 0x000084d0U);
    HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);
    HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00008cd0U);

    HW_SCE_p_func_sub023(0x00001dc0U, 0x000060c1U);

    WR1_PROG(REG_24H, 0x000019c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591U);
    HW_SCE_p_func_sub017(0x00000d91U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    WR1_PROG(REG_24H, 0x00000dc0U);
    HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    WR1_PROG(REG_24H, 0x000019c0U);
    WAIT_STS(REG_24H, 21, 0);
    WR1_PROG(REG_24H, 0x00000591U);
    HW_SCE_p_func_sub017(0x00001191U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    WR1_PROG(REG_24H, 0x000011c0U);
    HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
    WR1_PROG(REG_1CH, 0x00210000U);

    static const uint32_t Param_pf6_func100_003[] =
    {
        0x48dc9437U, 0x7d99e59aU, 0x359b6d56U, 0x26bc5175U,
    };
    HW_SCE_p_func100(Param_pf6_func100_003);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf6_func102_001[] =
        {
            0xb0a214e8U, 0x3ea6e6fdU, 0x18a83f65U, 0x349085f8U,
        };
        HW_SCE_p_func102(Param_pf6_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub023(0x000019c0U, 0x00000591U);
        HW_SCE_p_func_sub023(0x00000591U, 0x0000a0c1U);

        WR1_PROG(REG_24H, 0x00005004U);
        HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
        WR1_PROG(REG_ECH, 0x00000004U);

        WR1_PROG(REG_ECH, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000100U, 0x808c001fU, 0x00008333U, 0x00000021U);

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

                static const uint32_t Param_pf6_func100_004[] =
                {
                    0x4f50ce7aU, 0x5b245d5dU, 0x09650643U, 0x292d4bbfU,
                };
                HW_SCE_p_func100(Param_pf6_func100_004);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                    static const uint32_t Param_pf6_func101_001[] =
                    {
                        0xbfbe8c9cU, 0x3d95ed3cU, 0x3cf22247U, 0xa53ed86cU,
                    };
                    HW_SCE_p_func101(Param_pf6_func101_001);
                }
                else
                {
                    static const uint32_t Param_pf6_func101_002[] =
                    {
                        0xc389e42cU, 0x971fe1eaU, 0xd116d4fcU, 0x87c07bd4U,
                    };
                    HW_SCE_p_func101(Param_pf6_func101_002);
                }
            }

            WR1_PROG(REG_ECH, 0x000027e1U);

            static const uint32_t Param_pf6_func101_003[] =
            {
                0x89976506U, 0x0f51be2dU, 0x4581d2b3U, 0x31ad08acU,
            };
            HW_SCE_p_func101(Param_pf6_func101_003);
        }

        WR1_PROG(REG_ECH, 0x00008be0U);
        WR1_PROG(REG_ECH, 0x00000130U);

        WR1_PROG(REG_ECH, 0x00007c1fU);
        WR1_PROG(REG_1CH, 0x00602000U);

        static const uint32_t Param_pf6_func100_005[] =
        {
            0x6e827556U, 0x95f748d3U, 0x599c27e2U, 0x22b78e38U,
        };
        HW_SCE_p_func100(Param_pf6_func100_005);

        HW_SCE_p_func_sub023(0x00001dc0U, 0x000060c1U);

        WR1_PROG(REG_2CH, 0x00000011U);
        WR1_PROG(REG_104H, 0x00000b67U);
        WAIT_STS(REG_104H, 31, 1);
        WR12_ADDR(REG_100H, &InData_MsgDgst[0]);

        HW_SCE_p_func_sub002(0x0000094aU, 0x808c000aU, 0x00008333U, 0x00000023U);

        HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

        HW_SCE_p_func_sub023(0x000011c0U, 0x000060c1U);

        HW_SCE_p_func_sub023(0x000094d0U, 0x00000c2cU);
        HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
        HW_SCE_p_func_sub023(0x0000a0c1U, 0x000009c0U);
        HW_SCE_p_func_sub001(0x0000e0c1U, 0x00000008U, 0x8000d4d0U, 0x000084d0U);
        HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);
        HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x8000c0c1U);

        WR1_PROG(REG_34H, 0x00000002U);
        WR1_PROG(REG_24H, 0x80004cd0U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func028_r2(OFS_ADR);
        WR1_PROG(REG_34H, 0x00000802U);
        HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

        WR1_PROG(REG_ECH, 0x0000b540U);
        HW_SCE_p_func_sub002(0x00000040U, 0x808c000aU, 0x00008333U, 0x00000025U);

        HW_SCE_p_func_sub023(0x000009c0U, 0x000080c1U);

        HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);
        WR1_PROG(REG_24H, 0x000019a1U);
        HW_SCE_p_func_sub016(0x0000e0c1U, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000100U, 0x808c001fU, 0x00008333U, 0x00000021U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x00000180U, 0x0000b7a0U, 0x000000f6U);

        WR1_PROG(REG_ECH, 0x00000b9cU);

        static const uint32_t Param_pf6_func100_006[] =
        {
            0x207fcddaU, 0x5d1f4932U, 0x025fe82bU, 0x311610c3U,
        };
        HW_SCE_p_func100(Param_pf6_func100_006);
        WR1_PROG(REG_E0H, 0x81010380U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < 384; iLoop++)
        {
            static const uint32_t Param_pf6_func101_004[] =
            {
                0x343faaa0U, 0xc8a220e1U, 0x9e286aadU, 0x12ebe9cfU,
            };
            HW_SCE_p_func101(Param_pf6_func101_004);
            HW_SCE_p_func302();

            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }

            static const uint32_t Param_pf6_func101_005[] =
            {
                0xfe611096U, 0xf63529f2U, 0x1bc80c49U, 0xb74546a0U,
            };
            HW_SCE_p_func101(Param_pf6_func101_005);
        }

        WR1_PROG(REG_ECH, 0x0000b660U);
        HW_SCE_p_func_sub002(0x00000040U, 0x818c0013U, 0x00003833U, 0x0000001aU);

        WR1_PROG(REG_24H, 0x00001dc0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_pf6_func100_007[] =
        {
            0x77781b31U, 0x7ee34842U, 0x3e67a132U, 0x866f6dffU,
        };
        HW_SCE_p_func100(Param_pf6_func100_007);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf6_func102_002[] =
            {
                0x0d2df2eaU, 0xcafdcc6dU, 0x4b14a008U, 0xeecb2b39U,
            };
            HW_SCE_p_func102(Param_pf6_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_24H, 0x00004404U);
            HW_SCE_p_func_sub016(0x00004804U, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000040U, 0x808c001fU, 0x00008333U, 0x00000022U);
            WR1_PROG(REG_34H, 0x00000800U);
            HW_SCE_p_func_sub023(0x800068d0U, 0x00001dc0U);
            HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
            HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
            WR1_PROG(REG_24H, 0x0000a0c1U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_24H, 0x00005004U);
            HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000004U);

            WR1_PROG(REG_ECH, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000100U, 0x808c001fU, 0x00008333U, 0x00000021U);

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

                    static const uint32_t Param_pf6_func100_008[] =
                    {
                        0x1f9de355U, 0x2cf5dd10U, 0xafc11e8cU, 0x2e0989d4U,
                    };
                    HW_SCE_p_func100(Param_pf6_func100_008);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_pf6_func101_006[] =
                        {
                            0x63ed1c79U, 0x60fce20bU, 0xfd1676abU, 0x4b71e169U,
                        };
                        HW_SCE_p_func101(Param_pf6_func101_006);
                    }
                    else
                    {
                        static const uint32_t Param_pf6_func101_007[] =
                        {
                            0xf236aa04U, 0xdba8fd83U, 0xf47ee85eU, 0x10f90084U,
                        };
                        HW_SCE_p_func101(Param_pf6_func101_007);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_pf6_func101_008[] =
                {
                    0x09d2c05eU, 0xfc984d92U, 0xe5594ea9U, 0x41078609U,
                };
                HW_SCE_p_func101(Param_pf6_func101_008);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000130U);

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            WR1_PROG(REG_34H, 0x00000002U);
            HW_SCE_p_func_sub023(0x80000dc0U, 0x000040c1U);

            WR1_PROG(REG_24H, 0x000009c0U);
            WAIT_STS(REG_24H, 21, 0);
            HW_SCE_p_func_sub001(0x0000a0c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);
            HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

            HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
            WR1_PROG(REG_24H, 0x000019a1U);
            WAIT_STS(REG_24H, 21, 0);
            HW_SCE_p_func_sub001(0x000040c1U, 0x00000008U, 0x800015c0U, 0x000060c1U);
            HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x00000e2cU, 0x100019b1U);
            HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

            HW_SCE_p_func_sub023(0x000015c0U, 0x000080c1U);
            HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);
            WR1_PROG(REG_24H, 0x000019a1U);
            WAIT_STS(REG_24H, 21, 0);
            HW_SCE_p_func_sub001(0x0000e0c1U, 0x00000002U, 0x800009c0U, 0x0000a0c1U);

            HW_SCE_p_func_sub001(0x000009c0U, 0x00000800U, 0x800080c1U, 0x000011c0U);
            WR1_PROG(REG_24H, 0x000040c1U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x800100e0U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub009(0x800103a0U, 0x000000f6U);

            static const uint32_t Param_pf6_func101_009[] =
            {
                0xabde0957U, 0x0fbfdc07U, 0x816885b7U, 0x6864b23eU,
            };
            HW_SCE_p_func101(Param_pf6_func101_009);
            HW_SCE_p_func043();

            HW_SCE_p_func077();

            HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f6U);

            static const uint32_t Param_pf6_func101_010[] =
            {
                0x11952f36U, 0x92fa06b0U, 0xbec6cccfU, 0xdd60618cU,
            };
            HW_SCE_p_func101(Param_pf6_func101_010);
            HW_SCE_p_func044();

            HW_SCE_p_func_sub012(0x00000052U, 0x00040804U, 0x00000000U);

            HW_SCE_p_func_sub018(0x00001762U, 0x40000500U, 0x02e08887U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);
            HW_SCE_p_func_sub011(0x00003233U, 0x00000010U);

            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[13]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[17]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[21]);
            WR1_PROG(REG_00H, 0x00003233U);
            WR1_PROG(REG_2CH, 0x0000001bU);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[25]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_pf6_func100_009[] =
            {
                0xf18601a4U, 0x70bb1760U, 0x318349cbU, 0xff5d1355U,
            };
            HW_SCE_p_func100(Param_pf6_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pf6_func102_003[] =
                {
                    0x559c24e4U, 0xf2aa0acdU, 0x8b9b73a1U, 0x3b80136fU,
                };
                HW_SCE_p_func102(Param_pf6_func102_003);
                WR1_PROG(REG_1B8H, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                WR1_PROG(REG_24H, 0x000011c0U);
                WAIT_STS(REG_24H, 21, 0);
                WR1_PROG(REG_34H, 0x00000800U);
                HW_SCE_p_func_sub001(0x800040c1U, 0x00000002U, 0x80008cd0U, 0x0000082cU);
                HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);
                HW_SCE_p_func_sub023(0x000080c1U, 0x000011c0U);
                WR1_PROG(REG_34H, 0x00000800U);
                HW_SCE_p_func_sub001(0x800060c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);

                WR1_PROG(REG_34H, 0x00000002U);
                HW_SCE_p_func_sub006(0x800009c0U, 0x00000800U, 0x800080c1U);

                WR1_PROG(REG_34H, 0x00000002U);
                HW_SCE_p_func_sub006(0x80000dc0U, 0x00000800U, 0x8000a0c1U);

                WR1_PROG(REG_ECH, 0x0000b540U);
                HW_SCE_p_func_sub002(0x00000080U, 0x808c000aU, 0x00008333U, 0x00000022U);

                WR1_PROG(REG_ECH, 0x0000b540U);
                HW_SCE_p_func_sub002(0x000000C0U, 0x808c000aU, 0x00008333U, 0x00000023U);

                WR1_PROG(REG_ECH, 0x0000b7e0U);
                HW_SCE_p_func_sub002(0x00000100U, 0x808c001fU, 0x00008333U, 0x00000021U);

                HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

                HW_SCE_p_func_sub022(0x0000b480U, 0x00000180U, 0x0000b7a0U, 0x00000002U);

                WR1_PROG(REG_ECH, 0x00000b9cU);

                static const uint32_t Param_pf6_func100_010[] =
                {
                    0xf316d8d2U, 0x79929798U, 0x751a3d39U, 0xe14b89b8U,
                };
                HW_SCE_p_func100(Param_pf6_func100_010);
                WR1_PROG(REG_E0H, 0x81010380U);
                WR1_PROG(REG_04H, 0x00000607U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &S_RAM[0]);
                S_RAM[0] = change_endian_long(S_RAM[0]);

                for (iLoop = 0U; iLoop < 384; iLoop++)
                {
                    static const uint32_t Param_pf6_func101_011[] =
                    {
                        0x67d6accfU, 0x410dac54U, 0xd335e1bfU, 0x3a9b29d0U,
                    };
                    HW_SCE_p_func101(Param_pf6_func101_011);
                    HW_SCE_p_func302();

                    if (S_RAM[0] == 0x00000001U)
                    {
                        break;
                    }

                    static const uint32_t Param_pf6_func101_012[] =
                    {
                        0x8dc9b62aU, 0xea2a3202U, 0x330c3721U, 0xed7351f2U,
                    };
                    HW_SCE_p_func101(Param_pf6_func101_012);
                }

                WR1_PROG(REG_24H, 0x00001dc0U);
                HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
                WR1_PROG(REG_1CH, 0x00210000U);

                static const uint32_t Param_pf6_func100_011[] =
                {
                    0x53ca79ecU, 0x8c5fbfbeU, 0x789481f8U, 0x2f64684cU,
                };
                HW_SCE_p_func100(Param_pf6_func100_011);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_pf6_func102_004[] =
                    {
                        0x17c9dd80U, 0x82da83bfU, 0x0d790543U, 0x50485666U,
                    };
                    HW_SCE_p_func102(Param_pf6_func102_004);
                    WR1_PROG(REG_1B8H, 0x00000040U);
                    WAIT_STS(REG_18H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    WR1_PROG(REG_ECH, 0x0000b660U);
                    HW_SCE_p_func_sub002(0x00000080U, 0x818c0013U, 0x00003833U, 0x0000001aU);

                    WR1_PROG(REG_ECH, 0x0000b660U);
                    HW_SCE_p_func_sub002(0x000000C0U, 0x818c0013U, 0x00003833U, 0x0000001bU);

                    HW_SCE_p_func_sub023(0x00009cd0U, 0x0000102cU);

                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                    WR1_PROG(REG_24H, 0x000070d0U);
                    WAIT_STS(REG_24H, 21, 0);
                    HW_SCE_p_func_sub001(0x000080c1U, 0x00000002U, 0x800048d0U, 0x0000082cU);

                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                    HW_SCE_p_func_sub023(0x000040c1U, 0x00000c2cU);

                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                    HW_SCE_p_func_sub006(0x000080c1U, 0x00000008U, 0x800011c0U);

                    WR1_PROG(REG_34H, 0x00000200U);
                    HW_SCE_p_func_sub006(0x80000a41U, 0x00000008U, 0x800011c0U);

                    WR1_PROG(REG_34H, 0x00000200U);
                    HW_SCE_p_func_sub001(0x80000951U, 0x00000002U, 0x80004cd0U, 0x0000082cU);

                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                    WR1_PROG(REG_34H, 0x00000280U);
                    HW_SCE_p_func_sub001(0x800019a1U, 0x00000080U, 0x800080c1U, 0x000040c1U);
                    HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x0000e0c1U);

                    HW_SCE_p_func_sub023(0x0000102cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);

                    HW_SCE_p_func_sub006(0x00000c2cU, 0x00000200U, 0x900019b1U);

                    WR1_PROG(REG_34H, 0x00000280U);
                    HW_SCE_p_func_sub001(0x800019a1U, 0x00000008U, 0x800015c0U, 0x00000941U);
                    HW_SCE_p_func_sub001(0x000080c1U, 0x00000008U, 0x800015c0U, 0x00000951U);
                    WR1_PROG(REG_34H, 0x00000080U);
                    HW_SCE_p_func_sub001(0x800040c2U, 0x00000200U, 0x800012c0U, 0x00008cd0U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x00008cd0U);
                    HW_SCE_p_func_sub023(0x000040c1U, 0x0000102cU);

                    HW_SCE_p_func_sub023(0x100019b1U, 0x000019a1U);

                    WR1_PROG(REG_24H, 0x00000951U);
                    WAIT_STS(REG_24H, 21, 0);

                    HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x800080c1U, 0x00000149U);
                    HW_SCE_p_func_sub023(0x000060c1U, 0x000009c0U);
                    HW_SCE_p_func_sub023(0x00000d51U, 0x000040c1U);
                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                    WR1_PROG(REG_24H, 0x000019a1U);
                    WAIT_STS(REG_24H, 21, 0);

                    WR1_PROG(REG_34H, 0x00000080U);
                    HW_SCE_p_func_sub001(0x800080c1U, 0x00000080U, 0x800060c2U, 0x000040c1U);
                    HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);

                    HW_SCE_p_func_sub023(0x000019a1U, 0x000060c1U);
                    HW_SCE_p_func_sub023(0x000009c0U, 0x00000d51U);

                    WR1_PROG(REG_24H, 0x000019a1U);
                    WAIT_STS(REG_24H, 21, 0);

                    HW_SCE_p_func_sub001(0x00000145U, 0x00000800U, 0x8000a0c1U, 0x00001dc0U);
                    WR1_PROG(REG_24H, 0x00000591U);
                    WAIT_STS(REG_24H, 21, 0);
                    WR1_PROG(REG_1CH, 0x00001f00U);
                    WR1_PROG(REG_1CH, 0x00210000U);

                    static const uint32_t Param_pf6_func100_012[] =
                    {
                        0x5a83c212U, 0x26eaa86eU, 0x1abecd3aU, 0xf8dd0538U,
                    };
                    HW_SCE_p_func100(Param_pf6_func100_012);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        static const uint32_t Param_pf6_func102_005[] =
                        {
                            0x69e5c4abU, 0xbc0d5482U, 0xc110625bU, 0x71573c04U,
                        };
                        HW_SCE_p_func102(Param_pf6_func102_005);
                        WR1_PROG(REG_1B8H, 0x00000040U);
                        WAIT_STS(REG_18H, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        WR1_PROG(REG_ECH, 0x0000b7e0U);
                        HW_SCE_p_func_sub002(0x00000040U, 0x818c001fU, 0x00003833U, 0x00000012U);
                        WR1_PROG(REG_34H, 0x00000800U);
                        HW_SCE_p_func_sub023(0x800068d0U, 0x00001dc0U);
                        HW_SCE_p_func_sub023(0x000080c1U, 0x000019c0U);
                        HW_SCE_p_func_sub023(0x00000591U, 0x00000591U);
                        WR1_PROG(REG_24H, 0x0000a0c1U);
                        WAIT_STS(REG_24H, 21, 0);

                        WR1_PROG(REG_24H, 0x00005004U);
                        HW_SCE_p_func_sub016(0x00008404U, 0x0000b420U);
                        WR1_PROG(REG_ECH, 0x00000004U);

                        WR1_PROG(REG_ECH, 0x0000b7e0U);
                        HW_SCE_p_func_sub002(0x00000100U, 0x808c001fU, 0x00008333U, 0x00000021U);

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

                                static const uint32_t Param_pf6_func100_013[] =
                                {
                                    0x1fca6902U, 0xdb92fa7cU, 0x246ef741U, 0x05211b66U,
                                };
                                HW_SCE_p_func100(Param_pf6_func100_013);
                                WR1_PROG(REG_1CH, 0x00400000U);
                                WR1_PROG(REG_1D0H, 0x00000000U);

                                if (CHCK_STS(REG_1CH, 22, 1))
                                {
                                    HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                                    HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                                    static const uint32_t Param_pf6_func101_013[] =
                                    {
                                        0x26c9111fU, 0x476535c1U, 0x13d0b543U, 0xe890e9f3U,
                                    };
                                    HW_SCE_p_func101(Param_pf6_func101_013);
                                }
                                else
                                {
                                    static const uint32_t Param_pf6_func101_014[] =
                                    {
                                        0x03806e32U, 0xa9ed89feU, 0x00e95f20U, 0x5db753ccU,
                                    };
                                    HW_SCE_p_func101(Param_pf6_func101_014);
                                }
                            }

                            WR1_PROG(REG_ECH, 0x000027e1U);

                            static const uint32_t Param_pf6_func101_015[] =
                            {
                                0xd048889eU, 0x80940a86U, 0x6baaaf20U, 0x544eb0bfU,
                            };
                            HW_SCE_p_func101(Param_pf6_func101_015);
                        }

                        WR1_PROG(REG_ECH, 0x00008be0U);
                        WR1_PROG(REG_ECH, 0x00000130U);

                        WR1_PROG(REG_ECH, 0x00007c1fU);
                        WR1_PROG(REG_1CH, 0x00602000U);

                        WR1_PROG(REG_34H, 0x00000002U);
                        HW_SCE_p_func_sub023(0x80000dc0U, 0x000040c1U);

                        WR1_PROG(REG_24H, 0x000009c0U);
                        WAIT_STS(REG_24H, 21, 0);
                        HW_SCE_p_func_sub001(0x0000a0c1U, 0x00000008U, 0x800011c0U, 0x000040c1U);
                        HW_SCE_p_func_sub023(0x00000a2cU, 0x100019b1U);
                        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                        HW_SCE_p_func_sub023(0x000019a1U, 0x000040c1U);

                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);
                        WR1_PROG(REG_24H, 0x000019a1U);
                        HW_SCE_p_func_sub016(0x000040c1U, 0x0000b7e0U);
                        HW_SCE_p_func_sub002(0x00000140U, 0x818c001fU, 0x00003833U, 0x00000014U);

                        HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);
                        WR1_PROG(REG_24H, 0x100019b1U);
                        WAIT_STS(REG_24H, 21, 0);
                        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x000088d0U);
                        HW_SCE_p_func_sub023(0x00009004U, 0x00001028U);
                        WR1_PROG(REG_24H, 0x100019b1U);
                        WAIT_STS(REG_24H, 21, 0);
                        WR1_PROG(REG_24H, 0x000019a1U);
                        HW_SCE_p_func_sub016(0x000040c1U, 0x0000b660U);
                        HW_SCE_p_func_sub002(0x00000000U, 0x818c0013U, 0x00003833U, 0x00000014U);

                        WR1_PROG(REG_24H, 0x000009c0U);
                        HW_SCE_p_func_sub017(0x00001991U, 0x00001f00U);
                        WR1_PROG(REG_1CH, 0x00210000U);

                        WR1_PROG(REG_24H, 0x000019c0U);
                        HW_SCE_p_func_sub017(0x00000991U, 0x00001f00U);
                        WR1_PROG(REG_1CH, 0x00210000U);

                        static const uint32_t Param_pf6_func100_014[] =
                        {
                            0x5c2d0ec5U, 0xc2315674U, 0xdcad06ccU, 0x6322755fU,
                        };
                        HW_SCE_p_func100(Param_pf6_func100_014);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 1))
                        {
                            static const uint32_t Param_pf6_func102_006[] =
                            {
                                0xdb95f1aaU, 0xbf1fe75bU, 0xa804bf04U, 0x7c374249U,
                            };
                            HW_SCE_p_func102(Param_pf6_func102_006);
                            WR1_PROG(REG_1B8H, 0x00000040U);
                            WAIT_STS(REG_18H, 12, 0);

                            return FSP_ERR_CRYPTO_SCE_FAIL;
                        }
                        else
                        {
                            static const uint32_t Param_pf6_func102_007[] =
                            {
                                0x914a2eb8U, 0x0568a5aeU, 0x5d214490U, 0xb78ae4f6U,
                            };
                            HW_SCE_p_func102(Param_pf6_func102_007);
                            WR1_PROG(REG_1B8H, 0x00000040U);
                            WAIT_STS(REG_18H, 12, 0);

                            return FSP_SUCCESS;
                        }
                    }
                }
            }
        }
    }
}
