/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub (const uint32_t InData_CurveType[],
                                               const uint32_t InData_Cmd[],
                                               const uint32_t InData_KeyType[],
                                               uint32_t       OutData_PubKeyIndex[],
                                               uint32_t       OutData_PubKey[],
                                               uint32_t       OutData_PrivKeyIndex[],
                                               uint32_t       OutData_PrivKey[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x0000f402U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010340U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_CurveType[0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010380U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_Cmd[0]);

    HW_SCE_p_func_sub022(0x3020ab80U, 0x00000003U, 0x00060020U, 0x0000b780U);
    HW_SCE_p_func_sub022(0x00000002U, 0x00000080U, 0x00000bffU, 0x30000f5aU);
    HW_SCE_p_func_sub022(0x00030020U, 0x0000d3e1U, 0x00000060U, 0x38000f9cU);
    WR1_PROG(REG_ECH, 0x1000d3e1U);
    HW_SCE_p_func_sub007(0x00000080U, 0x38008be0U, 0x00000002U, 0x00A60000U);

    static const uint32_t Param_pf4_func100_001[] =
    {
        0x559bf95fU, 0xebb795a1U, 0x6dc7cb91U, 0x6ee821fbU,
    };
    HW_SCE_p_func100(Param_pf4_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf4_func102_001[] =
        {
            0x7fbe7fe1U, 0xa5906d5eU, 0x43e09b67U, 0x4d4cf4ffU,
        };
        HW_SCE_p_func102(Param_pf4_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pf4_func100_002[] =
        {
            0xb7d91f1dU, 0x1603c2b5U, 0x01b8091dU, 0x6410772cU,
        };
        HW_SCE_p_func100(Param_pf4_func100_002);
        WR1_PROG(REG_28H, 0x00870001U);

        HW_SCE_p_func_sub022(0x30003340U, 0x00050020U, 0x0000b400U, 0x000004C8U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000b400U, 0x0000031CU, 0x00070040U);
        HW_SCE_p_func_sub022(0x30003380U, 0x00070020U, 0x0000b400U, 0x00000080U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000b400U, 0x0000013CU, 0x00050040U);
        HW_SCE_p_func_sub022(0x0000b400U, 0x000001F8U, 0x00000080U, 0x00000080U);

        WR1_PROG(REG_E0H, 0x81010000U);
        WR1_PROG(REG_04H, 0x00000606U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);
        OFS_ADR  = S_RAM[0];

        static const uint32_t Param_pf4_func100_003[] =
        {
            0x93efae5eU, 0xdfb854afU, 0xeaead505U, 0xf922d3fbU,
        };
        HW_SCE_p_func100(Param_pf4_func100_003);
        HW_SCE_p_func070_r2(OFS_ADR);

        static const uint32_t Param_pf4_func100_004[] =
        {
            0xac5929b8U, 0x9009251bU, 0x3d6d1fdfU, 0x1da02173U,
        };
        HW_SCE_p_func100(Param_pf4_func100_004);
        WR1_PROG(REG_34H, 0x00000400U);
        WR1_PROG(REG_24H, 0x8000c0d0U);
        WAIT_STS(REG_24H, 21, 0);
        WR1_PROG(REG_28H, 0x00890001U);

        HW_SCE_p_func103();
        static const uint32_t Param_pf4_func100_005[] =
        {
            0x88a8f9acU, 0x709537c5U, 0xef19b46aU, 0xd7f9fa8fU,
        };
        HW_SCE_p_func100(Param_pf4_func100_005);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
        HW_SCE_p_func_sub011(0x00003213U, 0x00000011U);

        HW_SCE_p_func103();
        static const uint32_t Param_pf4_func100_006[] =
        {
            0xb4ea2121U, 0x3fec0e34U, 0xde041e9dU, 0xb8f5bb73U,
        };
        HW_SCE_p_func100(Param_pf4_func100_006);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);
        WR1_PROG(REG_00H, 0x00003213U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func103();
        static const uint32_t Param_pf4_func100_007[] =
        {
            0x780a5964U, 0x6e5c9e99U, 0x8c0a5040U, 0x002f258aU,
        };
        HW_SCE_p_func100(Param_pf4_func100_007);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        WR1_PROG(REG_00H, 0x0000320bU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);
        WR1_PROG(REG_00H, 0x0000020bU);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_ECH, 0x00007c1cU);
        WR1_PROG(REG_1CH, 0x00600000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
        {
            WR1_PROG(REG_28H, 0x00890001U);

            static const uint32_t Param_pf4_func101_001[] =
            {
                0x9f1db89dU, 0x0f5aa67bU, 0x2b151cd8U, 0x3dc562ecU,
            };
            HW_SCE_p_func101(Param_pf4_func101_001);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
        {
            WR1_PROG(REG_28H, 0x00880001U);

            static const uint32_t Param_pf4_func101_002[] =
            {
                0xca3f7eeeU, 0x09a4472aU, 0x2e218f86U, 0x908b33daU,
            };
            HW_SCE_p_func101(Param_pf4_func101_002);
        }
        else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
        {
            WR1_PROG(REG_28H, 0x00870001U);

            static const uint32_t Param_pf4_func101_003[] =
            {
                0x9c093ae5U, 0x1ed6255aU, 0x8f67f24aU, 0xeb53eefbU,
            };
            HW_SCE_p_func101(Param_pf4_func101_003);
        }

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
        HW_SCE_p_func_sub015(0x0000a0c2U, 0x00870001U);

        HW_SCE_p_func_sub006(0x0000dcd0U, 0x00000820U, 0x80009cd0U);

        static const uint32_t Param_pf4_func100_008[] =
        {
            0xb0cc8c1aU, 0xdabf4f6eU, 0x50ddfd40U, 0x55d7e34fU,
        };
        HW_SCE_p_func100(Param_pf4_func100_008);
        HW_SCE_p_func_sub023(0x000084d0U, 0x00021028U);

        WR1_PROG(REG_24H, 0x100019b1U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00004404U);
        HW_SCE_p_func_sub006(0x0000e8d0U, 0x00000808U, 0x8000f0d0U);

        HW_SCE_p_func071_r2(OFS_ADR);
        static const uint32_t Param_pf4_func100_009[] =
        {
            0x40c0ae57U, 0x29ba04aeU, 0xc761c11eU, 0x1bd201abU,
        };
        HW_SCE_p_func100(Param_pf4_func100_009);
        WR1_PROG(REG_34H, 0x00000802U);
        HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

        HW_SCE_p_func_sub002(0x00000bffU, 0x8088001fU, 0x00008323U, 0x00000021U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x00000100U, 0x0000b7a0U, 0x000000f4U);

        WR1_PROG(REG_ECH, 0x0000377cU);

        WR1_PROG(REG_ECH, 0x00000b9cU);

        WR1_PROG(REG_E0H, 0x81010380U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < 256U; iLoop++)
        {
            static const uint32_t Param_pf4_func101_004[] =
            {
                0xc75067e4U, 0x65f5d835U, 0x270dd151U, 0x1ff8007fU,
            };
            HW_SCE_p_func101(Param_pf4_func101_004);
            HW_SCE_p_func300();

            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }

            static const uint32_t Param_pf4_func101_005[] =
            {
                0x8e822641U, 0xa560dfdbU, 0xcd8aa6f6U, 0x7ac6e030U,
            };
            HW_SCE_p_func101(Param_pf4_func101_005);
        }

        WR1_PROG(REG_24H, 0x00001dc0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_pf4_func100_010[] =
        {
            0xe2066680U, 0xf0184b25U, 0xf343846fU, 0xa63764f2U,
        };
        HW_SCE_p_func100(Param_pf4_func100_010);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf4_func102_002[] =
            {
                0x4356149eU, 0x5afb71ceU, 0xe511df28U, 0xdd8745e2U,
            };
            HW_SCE_p_func102(Param_pf4_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
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

            HW_SCE_p_func_sub002(0x00000bffU, 0x8088001fU, 0x00008323U, 0x00000021U);

            for (iLoop = 0U; iLoop < 8U; iLoop++)
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

                    static const uint32_t Param_pf4_func100_011[] =
                    {
                        0x837faa79U, 0xae805b51U, 0xa4f2c9bfU, 0x7ffc4df8U,
                    };
                    HW_SCE_p_func100(Param_pf4_func100_011);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_pf4_func101_006[] =
                        {
                            0xaeabc302U, 0x1b959fdcU, 0xd1c51b83U, 0x95ab024fU,
                        };
                        HW_SCE_p_func101(Param_pf4_func101_006);
                    }
                    else
                    {
                        static const uint32_t Param_pf4_func101_007[] =
                        {
                            0xbf206840U, 0x607bab5dU, 0x9367a3bfU, 0x193a6d4aU,
                        };
                        HW_SCE_p_func101(Param_pf4_func101_007);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_pf4_func101_008[] =
                {
                    0x4a374666U, 0x52864535U, 0xc339c67cU, 0x34409fbaU,
                };
                HW_SCE_p_func101(Param_pf4_func101_008);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000020U);

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

            static const uint32_t Param_pf4_func100_012[] =
            {
                0xda6efe49U, 0x0193da14U, 0x413f34aeU, 0x66b6673dU,
            };
            HW_SCE_p_func100(Param_pf4_func100_012);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pf4_func100_013[] =
                {
                    0xefd47e77U, 0xeb7bfaeeU, 0x7abc684cU, 0x6d1cfc27U,
                };
                HW_SCE_p_func100(Param_pf4_func100_013);
                HW_SCE_p_func103();
                HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

                HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
                WR1_PROG(REG_00H, 0x0000020fU);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x000000f4U);

                static const uint32_t Param_pf4_func101_009[] =
                {
                    0xedd705fdU, 0x7c2f451fU, 0xd9176d40U, 0xcc058eecU,
                };
                HW_SCE_p_func101(Param_pf4_func101_009);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000379bU);
                HW_SCE_p_func074_r1();

                HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f4U);

                static const uint32_t Param_pf4_func101_010[] =
                {
                    0xb255d103U, 0xd13ef5d2U, 0x45974775U, 0xadde338bU,
                };
                HW_SCE_p_func101(Param_pf4_func101_010);
                HW_SCE_p_func044();

                static const uint32_t Param_pf4_func100_014[] =
                {
                    0x0e9623e0U, 0xf58c286aU, 0xf778486aU, 0x4df18dd9U,
                };
                HW_SCE_p_func100(Param_pf4_func100_014);
                WR1_PROG(REG_D0H, 0x40000100U);
                WR1_PROG(REG_C4H, 0x02e087b7U);
                HW_SCE_p_func_sub011(0x00002323U, 0x0000002dU);

                WR1_PROG(REG_04H, 0x00000222U);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[1]);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[5]);

                static const uint32_t Param_pf4_func100_015[] =
                {
                    0x3019d35cU, 0x645ddc1dU, 0x35918009U, 0x199ce470U,
                };
                HW_SCE_p_func100(Param_pf4_func100_015);
                HW_SCE_p_func_sub012(0x00000052U, 0x00000c84U, 0x00000000U);

                WR1_PROG(REG_D0H, 0x40000000U);
                HW_SCE_p_func_sub013(0x000089c5U, 0x00002213U);

                WR1_PROG(REG_04H, 0x00000212U);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PrivKeyIndex[9]);

                static const uint32_t Param_pf4_func100_016[] =
                {
                    0x425dd56dU, 0xaab5a89cU, 0x75d7c47fU, 0xdacdb289U,
                };
                HW_SCE_p_func100(Param_pf4_func100_016);
                WR1_PROG(REG_E0H, 0x81010000U);
                WR1_PROG(REG_04H, 0x00000606U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_PrivKeyIndex[0]);

                static const uint32_t Param_pf4_func100_017[] =
                {
                    0xec71435aU, 0x62d6e866U, 0xaca8918dU, 0x3c88529aU,
                };
                HW_SCE_p_func100(Param_pf4_func100_017);
                HW_SCE_p_func103();
                HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

                HW_SCE_p_func_sub010(0x80010000U, 0x00008207U);
                WR1_PROG(REG_00H, 0x0000020fU);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800U);

                HW_SCE_p_func_sub005(0x000034e0U, 0x00000058U, 0x800103a0U, 0x00000001U);

                static const uint32_t Param_pf4_func101_011[] =
                {
                    0x878f63fdU, 0x1d540d16U, 0x7ec1ac78U, 0xb20bf112U,
                };
                HW_SCE_p_func101(Param_pf4_func101_011);
                HW_SCE_p_func043();

                HW_SCE_p_func075_r1();

                HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x00000002U);

                static const uint32_t Param_pf4_func101_012[] =
                {
                    0xb177a360U, 0xa939f773U, 0x7d142f97U, 0x6344bcedU,
                };
                HW_SCE_p_func101(Param_pf4_func101_012);
                HW_SCE_p_func044();

                static const uint32_t Param_pf4_func100_018[] =
                {
                    0xbb1bd422U, 0xef8c3c92U, 0x4cd047daU, 0x8a62dbe3U,
                };
                HW_SCE_p_func100(Param_pf4_func100_018);
                WR1_PROG(REG_D0H, 0x40000200U);
                WR1_PROG(REG_C4H, 0x02e08887U);
                HW_SCE_p_func_sub011(0x00002323U, 0x00000022U);
                HW_SCE_p_func_sub011(0x00002313U, 0x00000023U);

                WR1_PROG(REG_04H, 0x00000232U);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PubKeyIndex[1]);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PubKeyIndex[5]);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PubKeyIndex[9]);

                static const uint32_t Param_pf4_func100_019[] =
                {
                    0x5ca913faU, 0x6604aba7U, 0x5e907a49U, 0xe6ac5f43U,
                };
                HW_SCE_p_func100(Param_pf4_func100_019);
                WR1_PROG(REG_D0H, 0x40000000U);
                WR1_PROG(REG_C4H, 0x00e08885U);
                WR1_PROG(REG_00H, 0x00002313U);
                HW_SCE_p_func_sub003(0x00000052U, 0x40000000U, 0x000089c4U);
                WR1_PROG(REG_100H, change_endian_long(0x00000000U));

                WR1_PROG(REG_04H, 0x00000222U);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PubKeyIndex[13]);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_PubKeyIndex[17]);

                static const uint32_t Param_pf4_func100_020[] =
                {
                    0xa27751c1U, 0x16ee123cU, 0x8536a299U, 0x3fe25d73U,
                };
                HW_SCE_p_func100(Param_pf4_func100_020);
                WR1_PROG(REG_E0H, 0x81010000U);
                WR1_PROG(REG_04H, 0x00000606U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_PubKeyIndex[0]);

                static const uint32_t Param_pf4_func101_013[] =
                {
                    0x72005084U, 0x90c1d887U, 0x2eb14108U, 0x07a53a3fU,
                };
                HW_SCE_p_func101(Param_pf4_func101_013);
            }
            else
            {
                static const uint32_t Param_pf4_func100_021[] =
                {
                    0xf5306cf4U, 0x62579919U, 0x96ba9447U, 0xb79cac61U,
                };
                HW_SCE_p_func100(Param_pf4_func100_021);
                WR1_PROG(REG_2CH, 0x0000002dU);
                WR1_PROG(REG_04H, 0x00000322U);
                WAIT_STS(REG_04H, 30, 1);
                RD8_ADDR(REG_100H, &OutData_PrivKey[0]);

                static const uint32_t Param_pf4_func100_022[] =
                {
                    0x81532d5fU, 0x53f4e578U, 0xe3c6dbb7U, 0xf0eb45caU,
                };
                HW_SCE_p_func100(Param_pf4_func100_022);
                WR1_PROG(REG_2CH, 0x00000022U);
                WR1_PROG(REG_04H, 0x00000322U);
                WAIT_STS(REG_04H, 30, 1);
                RD8_ADDR(REG_100H, &OutData_PubKey[0]);

                static const uint32_t Param_pf4_func100_023[] =
                {
                    0xc40351ecU, 0x5732d942U, 0x2de778c0U, 0xc9957558U,
                };
                HW_SCE_p_func100(Param_pf4_func100_023);
                WR1_PROG(REG_2CH, 0x00000023U);
                WR1_PROG(REG_04H, 0x00000322U);
                WAIT_STS(REG_04H, 30, 1);
                RD8_ADDR(REG_100H, &OutData_PubKey[8]);

                WR1_PROG(REG_34H, 0x00000400U);
                WR1_PROG(REG_24H, 0x800048d0U);
                HW_SCE_p_func_sub015(0x00004cd0U, 0x008f0001U);
                static const uint32_t Param_pf4_func100_024[] =
                {
                    0x3b6098f0U, 0x5d240785U, 0xbe8738feU, 0xf27ec80aU,
                };
                HW_SCE_p_func100(Param_pf4_func100_024);
                WR1_PROG(REG_2CH, 0x00000022U);
                WR1_PROG(REG_04H, 0x00000342U);
                WAIT_STS(REG_04H, 30, 1);
                RD16_ADDR(REG_100H, &OutData_PubKey[16]);

                static const uint32_t Param_pf4_func101_014[] =
                {
                    0x55c94b15U, 0xa3eca2aeU, 0x26ee840eU, 0x2bd2ece0U,
                };
                HW_SCE_p_func101(Param_pf4_func101_014);
            }

            static const uint32_t Param_pf4_func102_003[] =
            {
                0x53d867a0U, 0x375d6bf4U, 0xd8193df0U, 0x78b87c3aU,
            };
            HW_SCE_p_func102(Param_pf4_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
