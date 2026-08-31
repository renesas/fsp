/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub (const uint32_t InData_CurveType[],
                                            const uint32_t InData_Cmd[],
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

    WR1_PROG(REG_84H, 0x0000f002U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_28H, 0x00870001U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010340U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_CurveType[0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010380U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_Cmd[0]);

    WR1_PROG(REG_ECH, 0x0000b7c0U);
    WR1_PROG(REG_ECH, 0x000000c0U);

    WR1_PROG(REG_104H, 0x00000768U);
    WR1_PROG(REG_E0H, 0x8088001eU);
    for (iLoop = 0U; iLoop < 8U; iLoop++)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_MsgDgst[iLoop]);
    }

    HW_SCE_p_func_sub022(0x00000bffU, 0x30003380U, 0x00070020U, 0x0000d3e0U);
    HW_SCE_p_func_sub022(0x00030040U, 0x0000381eU, 0x38000c00U, 0x1000d3e0U);
    HW_SCE_p_func_sub022(0x00050040U, 0x0000381eU, 0x000037beU, 0x0000a7a0U);
    HW_SCE_p_func_sub022(0x00000004U, 0x0000383dU, 0x38001001U, 0x1000d3e0U);
    HW_SCE_p_func_sub022(0x00000080U, 0x30000f5aU, 0x00030020U, 0x0000d3e1U);
    WR1_PROG(REG_ECH, 0x00000060U);
    WR1_PROG(REG_ECH, 0x38000f9cU);
    WR1_PROG(REG_ECH, 0x1000d3e1U);
    HW_SCE_p_func_sub007(0x00000080U, 0x38008be0U, 0x00000003U, 0x00A60000U);

    static const uint32_t Param_pf0_func100_001[] =
    {
        0x80b99bc2U, 0x9ee4a418U, 0x49ce3627U, 0x4351adfaU,
    };
    HW_SCE_p_func100(Param_pf0_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pf0_func102_001[] =
        {
            0x563d1fa8U, 0x5a5d6fb3U, 0x1459421cU, 0xe53d7473U,
        };
        HW_SCE_p_func102(Param_pf0_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pf0_func100_002[] =
        {
            0x451200efU, 0xc8d401b7U, 0x2fa241a7U, 0xb8a7f10cU,
        };
        HW_SCE_p_func100(Param_pf0_func100_002);
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

        static const uint32_t Param_pf0_func100_003[] =
        {
            0xf071916eU, 0xbb83fee2U, 0xd34567d9U, 0x5f50077eU,
        };
        HW_SCE_p_func100(Param_pf0_func100_003);
        HW_SCE_p_func070_r2(OFS_ADR);
        static const uint32_t Param_pf0_func100_004[] =
        {
            0x470710d8U, 0x2d41069cU, 0xa5095108U, 0xfec111dbU,
        };
        HW_SCE_p_func100(Param_pf0_func100_004);

        WR1_PROG(REG_34H, 0x00000003U);
        HW_SCE_p_func_sub023(0x800068d0U, 0x000084d0U);
        HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);
        HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x8000c0c1U);

        HW_SCE_p_func103();
        static const uint32_t Param_pf0_func100_005[] =
        {
            0x704a81dfU, 0xd750501aU, 0xfdc7daaaU, 0x30ad6bdfU,
        };
        HW_SCE_p_func100(Param_pf0_func100_005);
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        HW_SCE_p_func_sub011(0x00003213U, 0x00000011U);

        HW_SCE_p_func103();
        HW_SCE_p_func_sub012(0x00000052U, 0x01000c84U, 0x00000000U);

        WR1_PROG(REG_00H, 0x00003213U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        HW_SCE_p_func_sub023(0x00001228U, 0x100019b1U);
        HW_SCE_p_func_sub023(0x000019a1U, 0x0000a0c1U);

        static const uint32_t Param_pf0_func100_006[] =
        {
            0xef5f6f61U, 0x8b7b541dU, 0x60a83d4cU, 0xe6fcc2f3U,
        };
        HW_SCE_p_func100(Param_pf0_func100_006);

        HW_SCE_p_func071_r2(OFS_ADR);
        WR1_PROG(REG_34H, 0x00000802U);
        HW_SCE_p_func_sub006(0x800088d0U, 0x00000802U, 0x8000acd0U);

        WR1_PROG(REG_ECH, 0x0000b7e0U);
        HW_SCE_p_func_sub002(0x00000040U, 0x8088001fU, 0x00008323U, 0x00000024U);

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
        HW_SCE_p_func_sub002(0x00000080U, 0x8088001fU, 0x00008323U, 0x00000020U);

        WR1_PROG(REG_24H, 0x00005cd0U);
        WAIT_STS(REG_24H, 21, 0);

        HW_SCE_p_func_sub002(0x00000bffU, 0x8088001fU, 0x00008323U, 0x00000021U);

        HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

        HW_SCE_p_func_sub022(0x0000b480U, 0x00000100U, 0x0000b7a0U, 0x000000f0U);

        WR1_PROG(REG_ECH, 0x0000373cU);

        WR1_PROG(REG_ECH, 0x00000b9cU);

        static const uint32_t Param_pf0_func100_007[] =
        {
            0x1d4ac2e4U, 0x51589b8eU, 0x542a868aU, 0x975cf1b6U,
        };
        HW_SCE_p_func100(Param_pf0_func100_007);
        WR1_PROG(REG_E0H, 0x81010380U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        for (iLoop = 0U; iLoop < 256U; iLoop++)
        {
            static const uint32_t Param_pf0_func101_001[] =
            {
                0x78e307d7U, 0x63d014e3U, 0x594119d3U, 0xc6df9701U,
            };
            HW_SCE_p_func101(Param_pf0_func101_001);

            HW_SCE_p_func300();

            if (S_RAM[0] == 0x00000001U)
            {
                break;
            }

            static const uint32_t Param_pf0_func101_002[] =
            {
                0x6db06aceU, 0xebbad615U, 0x7726e7c9U, 0x4983ea35U,
            };
            HW_SCE_p_func101(Param_pf0_func101_002);
        }

        WR1_PROG(REG_24H, 0x00001dc0U);
        HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
        WR1_PROG(REG_1CH, 0x00210000U);

        static const uint32_t Param_pf0_func100_008[] =
        {
            0xa9085fbeU, 0x25a8489cU, 0xe5f22119U, 0x0e253310U,
        };
        HW_SCE_p_func100(Param_pf0_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pf0_func102_002[] =
            {
                0x85ca9aa5U, 0x59e5f5b6U, 0x4e2034b2U, 0x9a0a1c47U,
            };
            HW_SCE_p_func102(Param_pf0_func102_002);
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

                    static const uint32_t Param_pf0_func100_009[] =
                    {
                        0x32739d60U, 0x0e2671edU, 0x23998dfeU, 0x4f6c4200U,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_009);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                        HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                        static const uint32_t Param_pf0_func101_003[] =
                        {
                            0x8258f1e6U, 0x553b5587U, 0x4f1e0975U, 0xd75763f4U,
                        };
                        HW_SCE_p_func101(Param_pf0_func101_003);
                    }
                    else
                    {
                        static const uint32_t Param_pf0_func101_004[] =
                        {
                            0x539fd0d3U, 0xea3031baU, 0x97e22ba0U, 0x5000a199U,
                        };
                        HW_SCE_p_func101(Param_pf0_func101_004);
                    }
                }

                WR1_PROG(REG_ECH, 0x000027e1U);

                static const uint32_t Param_pf0_func101_005[] =
                {
                    0x5919a370U, 0x0f6d04c5U, 0xce11e96aU, 0x4d2ef3faU,
                };
                HW_SCE_p_func101(Param_pf0_func101_005);
            }

            WR1_PROG(REG_ECH, 0x00008be0U);
            WR1_PROG(REG_ECH, 0x00000020U);

            WR1_PROG(REG_ECH, 0x00007c1fU);
            WR1_PROG(REG_1CH, 0x00602000U);

            HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);

            WR1_PROG(REG_24H, 0x000019a1U);
            HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000080U, 0x8188001fU, 0x00003823U, 0x00000012U);

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
            HW_SCE_p_func_sub002(0x00000040U, 0x8188001fU, 0x00003823U, 0x00000014U);

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

            static const uint32_t Param_pf0_func100_010[] =
            {
                0xc94388e0U, 0x9a7e6cb9U, 0xce5c4ac7U, 0xb132c2d9U,
            };
            HW_SCE_p_func100(Param_pf0_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pf0_func102_003[] =
                {
                    0x117e7a37U, 0xe9611638U, 0xe3b97e76U, 0xadd63588U,
                };
                HW_SCE_p_func102(Param_pf0_func102_003);
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

                        static const uint32_t Param_pf0_func100_011[] =
                        {
                            0xf488209bU, 0x8754f3d9U, 0x9dcac910U, 0x6a315209U,
                        };
                        HW_SCE_p_func100(Param_pf0_func100_011);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 1))
                        {
                            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                            HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                            static const uint32_t Param_pf0_func101_006[] =
                            {
                                0x564da9c0U, 0x175afa15U, 0xdb42594eU, 0x2a5f439fU,
                            };
                            HW_SCE_p_func101(Param_pf0_func101_006);
                        }
                        else
                        {
                            static const uint32_t Param_pf0_func101_007[] =
                            {
                                0x707f79d8U, 0xf36e9205U, 0xc8bbbdfcU, 0xa87d56c3U,
                            };
                            HW_SCE_p_func101(Param_pf0_func101_007);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x000027e1U);

                    static const uint32_t Param_pf0_func101_008[] =
                    {
                        0x4e12ae86U, 0x9ec13781U, 0x54edd46aU, 0x1512b2b6U,
                    };
                    HW_SCE_p_func101(Param_pf0_func101_008);
                }

                WR1_PROG(REG_ECH, 0x00008be0U);
                WR1_PROG(REG_ECH, 0x00000020U);

                WR1_PROG(REG_ECH, 0x00007c1fU);
                WR1_PROG(REG_1CH, 0x00602000U);

                HW_SCE_p_func_sub023(0x00001028U, 0x100019b1U);

                WR1_PROG(REG_24H, 0x000019a1U);
                HW_SCE_p_func_sub016(0x000080c1U, 0x0000b7e0U);
                HW_SCE_p_func_sub002(0x000000c0U, 0x8188001fU, 0x00003823U, 0x00000011U);

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

                HW_SCE_p_func_sub009(0x800103a0U, 0x000000f0U);

                static const uint32_t Param_pf0_func101_009[] =
                {
                    0xf1d0563cU, 0xbbd53440U, 0x9277dcaaU, 0xf580df08U,
                };
                HW_SCE_p_func101(Param_pf0_func101_009);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x00003799U);
                HW_SCE_p_func074_r1();

                HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x000000f0U);

                static const uint32_t Param_pf0_func101_010[] =
                {
                    0xeb59fefbU, 0xc02a6ecbU, 0xdaec63f0U, 0x7971ef3dU,
                };
                HW_SCE_p_func101(Param_pf0_func101_010);
                HW_SCE_p_func044();

                WR1_PROG(REG_104H, 0x00000762U);
                WR1_PROG(REG_D0H, 0x40000100U);
                WR1_PROG(REG_C4H, 0x02f087b7U);

                WR1_PROG(REG_00H, 0x00003223U);
                WR1_PROG(REG_2CH, 0x00000018U);

                for (iLoop = 0U; iLoop < 8U; )
                {
                    WAIT_STS(REG_104H, 31, 1);
                    WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
                    iLoop = iLoop + 4U;
                }

                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

                HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

                static const uint32_t Param_pf0_func100_012[] =
                {
                    0x8a7f35bcU, 0x18556ebdU, 0xb1818f43U, 0x312f0c9fU,
                };
                HW_SCE_p_func100(Param_pf0_func100_012);
                WR1_PROG(REG_1CH, 0x00400000U);
                WR1_PROG(REG_1D0H, 0x00000000U);

                if (CHCK_STS(REG_1CH, 22, 1))
                {
                    static const uint32_t Param_pf0_func102_004[] =
                    {
                        0x508e103bU, 0x5176429fU, 0x3455628aU, 0x1a3d6475U,
                    };
                    HW_SCE_p_func102(Param_pf0_func102_004);
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

                    static const uint32_t Param_pf0_func100_013[] =
                    {
                        0x54820b6aU, 0x3952524aU, 0xa5020e8bU, 0x902155ffU,
                    };
                    HW_SCE_p_func100(Param_pf0_func100_013);
                    WR1_PROG(REG_1CH, 0x00400000U);
                    WR1_PROG(REG_1D0H, 0x00000000U);

                    if (CHCK_STS(REG_1CH, 22, 1))
                    {
                        static const uint32_t Param_pf0_func102_005[] =
                        {
                            0xca61be04U, 0xf4a62121U, 0x1d40756bU, 0x97a09354U,
                        };
                        HW_SCE_p_func102(Param_pf0_func102_005);
                        WR1_PROG(REG_1B8H, 0x00000040U);
                        WAIT_STS(REG_18H, 12, 0);

                        return FSP_ERR_CRYPTO_SCE_FAIL;
                    }
                    else
                    {
                        static const uint32_t Param_pf0_func100_014[] =
                        {
                            0x64195d93U, 0xee1713e1U, 0x2b8c720bU, 0xb8b83929U,
                        };
                        HW_SCE_p_func100(Param_pf0_func100_014);
                        WR1_PROG(REG_2CH, 0x0000002bU);
                        WR1_PROG(REG_04H, 0x00000322U);
                        WAIT_STS(REG_04H, 30, 1);
                        RD8_ADDR(REG_100H, &OutData_Signature[0]);

                        static const uint32_t Param_pf0_func100_015[] =
                        {
                            0x7f837de5U, 0x2783bdc9U, 0x09f9efa6U, 0xdc30d0abU,
                        };
                        HW_SCE_p_func100(Param_pf0_func100_015);
                        WR1_PROG(REG_2CH, 0x0000002aU);
                        WR1_PROG(REG_04H, 0x00000322U);
                        WAIT_STS(REG_04H, 30, 1);
                        RD8_ADDR(REG_100H, &OutData_Signature[8]);

                        static const uint32_t Param_pf0_func102_006[] =
                        {
                            0x582e0cefU, 0x9b53cdceU, 0x3672fe6dU, 0x4599d89dU,
                        };
                        HW_SCE_p_func102(Param_pf0_func102_006);
                        WR1_PROG(REG_1B8H, 0x00000040U);
                        WAIT_STS(REG_18H, 12, 0);

                        return FSP_SUCCESS;
                    }
                }
            }
        }
    }
}
