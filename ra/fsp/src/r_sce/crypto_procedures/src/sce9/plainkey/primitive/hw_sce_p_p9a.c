/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_Cmd[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_PubKey[],
                                                uint32_t       OutData_R[])
{
    uint32_t OFS_ADR = 0U;
    uint32_t iLoop   = 0U;
    uint32_t jLoop   = 0U;

    if (RD1_MASK(REG_1B8H, 0x0000001eU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00009a02U);
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

    WR1_PROG(REG_ECH, 0x00000bdeU);

    WR1_PROG(REG_104H, 0x00000f68U);
    WR1_PROG(REG_E0H, 0x8090001eU);
    for (iLoop = 0U; iLoop < 16U; iLoop++)
    {
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_PubKey[iLoop]);
    }

    for (iLoop = 0U; iLoop < 2U; iLoop++)
    {
        HW_SCE_p_func_sub022(0x00000bffU, 0x30003380U, 0x00070020U, 0x0000d3e0U);
        HW_SCE_p_func_sub022(0x00030040U, 0x0000381eU, 0x38000c00U, 0x1000d3e0U);
        HW_SCE_p_func_sub022(0x00050040U, 0x0000381eU, 0x000037beU, 0x0000a7a0U);
        WR1_PROG(REG_ECH, 0x00000004U);
        WR1_PROG(REG_ECH, 0x0000383dU);
        WR1_PROG(REG_ECH, 0x38001001U);
        HW_SCE_p_func_sub007(0x1000d3e0U, 0x00000080U, 0x38000fffU, 0x00260000U);

        WR1_PROG(REG_ECH, 0x0000a7c0U);
        WR1_PROG(REG_ECH, 0x00000020U);
    }

    HW_SCE_p_func_sub022(0x30000f5aU, 0x00030020U, 0x0000d3e1U, 0x00000060U);
    WR1_PROG(REG_ECH, 0x38000f9cU);
    WR1_PROG(REG_ECH, 0x1000d3e1U);
    HW_SCE_p_func_sub007(0x00000080U, 0x38008be0U, 0x00000003U, 0x00A60000U);

    static const uint32_t Param_p9a_func100_001[] =
    {
        0x3965c2d2U, 0x82748bcdU, 0xc40cd983U, 0x4cfda6a2U,
    };
    HW_SCE_p_func100(Param_p9a_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p9a_func102_001[] =
        {
            0x57ec98c4U, 0x37655b01U, 0xbd5955d6U, 0x4b280573U,
        };
        HW_SCE_p_func102(Param_p9a_func102_001);
        WR1_PROG(REG_1B8H, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x800100e0U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_KeyIndex[0]);

        HW_SCE_p_func_sub009(0x800103a0U, 0x0000009aU);

        static const uint32_t Param_p9a_func101_001[] =
        {
            0x3aa30067U, 0x566ddb9aU, 0x5cee2e76U, 0x4083c512U,
        };
        HW_SCE_p_func101(Param_p9a_func101_001);
        HW_SCE_p_func043();

        HW_SCE_p_func074_r1();

        HW_SCE_p_func_sub005(0x000034feU, 0x00000058U, 0x800103a0U, 0x0000009aU);

        static const uint32_t Param_p9a_func101_002[] =
        {
            0x832ab6cbU, 0xf2fc811cU, 0x465c0d18U, 0x085b85d7U,
        };
        HW_SCE_p_func101(Param_p9a_func101_002);
        HW_SCE_p_func044();

        WR1_PROG(REG_104H, 0x00000762U);
        WR1_PROG(REG_D0H, 0x40000100U);
        WR1_PROG(REG_C4H, 0x02f087b7U);

        WR1_PROG(REG_00H, 0x00003223U);
        WR1_PROG(REG_2CH, 0x00000011U);

        for (iLoop = 0U; iLoop < 8U; )
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[iLoop + 1]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        static const uint32_t Param_p9a_func100_002[] =
        {
            0x3d38fe92U, 0x745739efU, 0x96383b59U, 0x1fcc88e9U,
        };
        HW_SCE_p_func100(Param_p9a_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p9a_func102_002[] =
            {
                0x71c33e0dU, 0xb021c479U, 0x6b63089eU, 0x571fde41U,
            };
            HW_SCE_p_func102(Param_p9a_func102_002);
            WR1_PROG(REG_1B8H, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            static const uint32_t Param_p9a_func100_003[] =
            {
                0x86959a7cU, 0xa4eed527U, 0xeeec7768U, 0xff9ea61bU,
            };
            HW_SCE_p_func100(Param_p9a_func100_003);

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

            static const uint32_t Param_p9a_func100_004[] =
            {
                0x1ed97c6fU, 0x109d0bc2U, 0xfa651f26U, 0xf32e898eU,
            };
            HW_SCE_p_func100(Param_p9a_func100_004);
            HW_SCE_p_func070_r2(OFS_ADR);
            static const uint32_t Param_p9a_func100_005[] =
            {
                0xd1fe94f1U, 0x147cf197U, 0xf1f0ff33U, 0xab3dc8c1U,
            };
            HW_SCE_p_func100(Param_p9a_func100_005);

            WR1_PROG(REG_34H, 0x00000003U);
            WR1_PROG(REG_24H, 0x800068d0U);
            WAIT_STS(REG_24H, 21, 0);

            HW_SCE_p_func_sub001(0x0000dcd0U, 0x00000820U, 0x80009cd0U, 0x000084d0U);
            HW_SCE_p_func_sub023(0x00021028U, 0x100019b1U);

            HW_SCE_p_func_sub001(0x000019a1U, 0x00000800U, 0x8000c0c1U, 0x00004404U);
            HW_SCE_p_func_sub006(0x0000e8d0U, 0x00000808U, 0x8000f0d0U);

            HW_SCE_p_func_sub002(0x00000bffU, 0x8188001fU, 0x00003823U, 0x00000010U);
            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x800040c1U);
            WR1_PROG(REG_34H, 0x00000800U);
            WR1_PROG(REG_24H, 0x800080c1U);
            WAIT_STS(REG_24H, 21, 0);

            WR1_PROG(REG_ECH, 0x0000b7e0U);
            HW_SCE_p_func_sub002(0x00000020U, 0x8188001fU, 0x00003823U, 0x00000010U);
            HW_SCE_p_func_sub023(0x00000c2cU, 0x100019b1U);
            HW_SCE_p_func_sub006(0x000019a1U, 0x00000800U, 0x800060c1U);
            WR1_PROG(REG_34H, 0x00000800U);
            WR1_PROG(REG_24H, 0x8000a0c1U);
            WAIT_STS(REG_24H, 21, 0);

            HW_SCE_p_func_sub002(0x00000bffU, 0x8088001fU, 0x00008323U, 0x00000021U);

            HW_SCE_p_func_sub022(0x00000bdeU, 0x00000842U, 0x0000b420U, 0x00000004U);

            HW_SCE_p_func_sub022(0x0000b480U, 0x00000100U, 0x0000b7a0U, 0x0000009aU);

            WR1_PROG(REG_ECH, 0x0000377cU);

            WR1_PROG(REG_ECH, 0x00000b9cU);

            WR1_PROG(REG_E0H, 0x81010380U);
            WR1_PROG(REG_04H, 0x00000607U);
            WAIT_STS(REG_04H, 30, 1);
            RD1_ADDR(REG_100H, &S_RAM[0]);
            S_RAM[0] = change_endian_long(S_RAM[0]);

            for (iLoop = 0U; iLoop < 256U; iLoop++)
            {
                static const uint32_t Param_p9a_func101_003[] =
                {
                    0xae6f33b4U, 0x064fc23eU, 0x7a4c092bU, 0xd9ff2a9eU,
                };
                HW_SCE_p_func101(Param_p9a_func101_003);
                HW_SCE_p_func300();

                if (S_RAM[0] == 0x00000001U)
                {
                    break;
                }

                static const uint32_t Param_p9a_func101_004[] =
                {
                    0xf42c3d9eU, 0x179e2b97U, 0xac23a620U, 0xc94db83bU,
                };
                HW_SCE_p_func101(Param_p9a_func101_004);
            }

            WR1_PROG(REG_24H, 0x00001dc0U);
            HW_SCE_p_func_sub017(0x00000591U, 0x00001f00U);
            WR1_PROG(REG_1CH, 0x00210000U);

            static const uint32_t Param_p9a_func100_006[] =
            {
                0xfa0e2dd1U, 0x0d9f7059U, 0xe5c47b66U, 0x1267bf4fU,
            };
            HW_SCE_p_func100(Param_p9a_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p9a_func102_003[] =
                {
                    0xd1535a62U, 0x712ffe15U, 0x35a7c325U, 0xaec12d1fU,
                };
                HW_SCE_p_func102(Param_p9a_func102_003);
                WR1_PROG(REG_1B8H, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func_sub023(0x00001dc0U, 0x000080c1U);

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

                        static const uint32_t Param_p9a_func100_007[] =
                        {
                            0xbfa07cbbU, 0x892d135cU, 0x6f39790aU, 0x1ebe4fcbU,
                        };
                        HW_SCE_p_func100(Param_p9a_func100_007);
                        WR1_PROG(REG_1CH, 0x00400000U);
                        WR1_PROG(REG_1D0H, 0x00000000U);

                        if (CHCK_STS(REG_1CH, 22, 1))
                        {
                            HW_SCE_p_func_sub023(0x0000082cU, 0x100019b1U);

                            HW_SCE_p_func_sub023(0x000019a1U, 0x000080c1U);

                            static const uint32_t Param_p9a_func101_005[] =
                            {
                                0xcd606843U, 0x98cbb1f5U, 0x4052dda2U, 0x61b8fdd1U,
                            };
                            HW_SCE_p_func101(Param_p9a_func101_005);
                        }
                        else
                        {
                            static const uint32_t Param_p9a_func101_006[] =
                            {
                                0x0ce52ca3U, 0x9ceedb58U, 0x5f26d152U, 0x98cc1206U,
                            };
                            HW_SCE_p_func101(Param_p9a_func101_006);
                        }
                    }

                    WR1_PROG(REG_ECH, 0x000027e1U);

                    static const uint32_t Param_p9a_func101_007[] =
                    {
                        0x84355fe5U, 0xb797abfcU, 0xc5bc5e73U, 0xf3cdaec0U,
                    };
                    HW_SCE_p_func101(Param_p9a_func101_007);
                }

                WR1_PROG(REG_ECH, 0x00008be0U);
                WR1_PROG(REG_ECH, 0x00000020U);

                WR1_PROG(REG_ECH, 0x00007c1fU);
                WR1_PROG(REG_1CH, 0x00602000U);

                HW_SCE_p_func301();

                static const uint32_t Param_p9a_func100_008[] =
                {
                    0x0c5448bdU, 0xe38e6a0dU, 0xbc1dc8f3U, 0xc7fa8025U,
                };
                HW_SCE_p_func100(Param_p9a_func100_008);
                WR1_PROG(REG_2CH, 0x00000022U);
                WR1_PROG(REG_04H, 0x00000322U);
                WAIT_STS(REG_04H, 30, 1);
                RD8_ADDR(REG_100H, &OutData_R[0]);

                static const uint32_t Param_p9a_func100_009[] =
                {
                    0x11f40d9dU, 0xc57e5588U, 0x575e1647U, 0x235ad24bU,
                };
                HW_SCE_p_func100(Param_p9a_func100_009);
                WR1_PROG(REG_2CH, 0x00000023U);
                WR1_PROG(REG_04H, 0x00000322U);
                WAIT_STS(REG_04H, 30, 1);
                RD8_ADDR(REG_100H, &OutData_R[8]);

                static const uint32_t Param_p9a_func102_004[] =
                {
                    0x69e7c53aU, 0x0f736cf0U, 0xc4577672U, 0x449008dcU,
                };
                HW_SCE_p_func102(Param_p9a_func102_004);
                WR1_PROG(REG_1B8H, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
