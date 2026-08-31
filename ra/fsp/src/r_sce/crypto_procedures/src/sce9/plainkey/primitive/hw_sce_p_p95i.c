/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128CcmEncryptInitSub (uint32_t InData_KeyType[],
                                          uint32_t InData_DataType[],
                                          uint32_t InData_Cmd[],
                                          uint32_t InData_TextLen[],
                                          uint32_t InData_KeyIndex[],
                                          uint32_t InData_IV[],
                                          uint32_t InData_Header[],
                                          uint32_t Header_Len,
                                          uint32_t InData_SeqNum[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00009502U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x00003640U);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010120U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[0]);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000004U, 0x00260000U);

    static const uint32_t Param_p95i_func100_001[] =
    {
        0xb6d3d7aeU, 0x03f459d0U, 0x3cb9783aU, 0x1f0c76d4U,
    };
    HW_SCE_p_func100(Param_p95i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        HW_SCE_p_func_sub014(0x3420a920U, 0x00004101U, 0x00A60000U);

        static const uint32_t Param_p95i_func101_001[] =
        {
            0xdce8ab0eU, 0xea170c82U, 0x65b077c3U, 0x3bddd9b6U,
        };
        HW_SCE_p_func101(Param_p95i_func101_001);
    }

    HW_SCE_p_func_sub014(0x38008800U, 0x00000001U, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008800U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_p95i_func100_002[] =
    {
        0x32a26b65U, 0xe0b80ac4U, 0x386ec472U, 0x7f816533U,
    };
    HW_SCE_p_func100(Param_p95i_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p95i_func102_001[] =
        {
            0x7d1776bfU, 0x1c374f67U, 0xa4abd4c9U, 0x340bd235U,
        };
        HW_SCE_p_func102(Param_p95i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub014(0x3420a800U, 0x00000004U, 0x00260000U);

        static const uint32_t Param_p95i_func100_003[] =
        {
            0x7c069788U, 0x57b0ae31U, 0xd9b2d6b4U, 0x38682636U,
        };
        HW_SCE_p_func100(Param_p95i_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x38000c00U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p95i_func100_004[] =
            {
                0xdf48dc71U, 0x74c3a437U, 0x094587f5U, 0xe7bee5d9U,
            };
            HW_SCE_p_func100(Param_p95i_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000095U);

                static const uint32_t Param_p95i_func101_002[] =
                {
                    0x083336eeU, 0x60b8c114U, 0x03ec69fcU, 0x96f1bc4eU,
                };
                HW_SCE_p_func101(Param_p95i_func101_002);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000005U);

                static const uint32_t Param_p95i_func101_003[] =
                {
                    0x44f176b3U, 0x0542a71eU, 0xf9677c0aU, 0xd57ffb5eU,
                };
                HW_SCE_p_func101(Param_p95i_func101_003);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010140U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000095U);

                static const uint32_t Param_p95i_func101_004[] =
                {
                    0xc3d74994U, 0x2396f33aU, 0xde076f70U, 0x45910600U,
                };
                HW_SCE_p_func101(Param_p95i_func101_004);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x0146c04bU);

                static const uint32_t Param_p95i_func101_005[] =
                {
                    0x4578cdf9U, 0x8cc5940bU, 0xfaee4bbdU, 0x999d9911U,
                };
                HW_SCE_p_func101(Param_p95i_func101_005);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000095U);

            static const uint32_t Param_p95i_func101_006[] =
            {
                0x8a77630fU, 0x85838b13U, 0xacf95c17U, 0x3f5a3bffU,
            };
            HW_SCE_p_func101(Param_p95i_func101_006);
            HW_SCE_p_func044();

            static const uint32_t Param_p95i_func100_005[] =
            {
                0x29ccfd70U, 0x5f7a7f3fU, 0x1309d3e3U, 0xb3c106beU,
            };
            HW_SCE_p_func100(Param_p95i_func100_005);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p95i_func101_007[] =
            {
                0xaae410a7U, 0xf00e5a90U, 0x2410ec74U, 0x265bc778U,
            };
            HW_SCE_p_func101(Param_p95i_func101_007);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010020U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_DataType[0]);

            WR1_PROG(REG_ECH, 0x38000c21U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p95i_func100_006[] =
            {
                0xa0286701U, 0x7b258d53U, 0x952230bdU, 0xc64fe911U,
            };
            HW_SCE_p_func100(Param_p95i_func100_006);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010000U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Cmd[0]);

                WR1_PROG(REG_ECH, 0x000036a0U);

                WR1_PROG(REG_ECH, 0x0000b6c0U);
                HW_SCE_p_func_sub005(0x01c18a1aU, 0x00000058U, 0x800103a0U, 0x00000095U);

                static const uint32_t Param_p95i_func101_008[] =
                {
                    0x645e69f2U, 0xbb125192U, 0xbe8a99eaU, 0x02067853U,
                };
                HW_SCE_p_func101(Param_p95i_func101_008);
                HW_SCE_p_func082();

                static const uint32_t Param_p95i_func101_009[] =
                {
                    0x99be7b5dU, 0xbef7c002U, 0xac667246U, 0xc6be6bfdU,
                };
                HW_SCE_p_func101(Param_p95i_func101_009);
            }
            else
            {
                HW_SCE_p_func_sub009(0x800103a0U, 0x000000dfU);

                static const uint32_t Param_p95i_func101_010[] =
                {
                    0xde1dd999U, 0x6cb89cd2U, 0x825102d6U, 0x8c8555ddU,
                };
                HW_SCE_p_func101(Param_p95i_func101_010);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                HW_SCE_p_func_sub005(0x01d6575eU, 0x00000058U, 0x800103a0U, 0x000000ebU);

                static const uint32_t Param_p95i_func101_011[] =
                {
                    0x8c9e99e9U, 0x37554738U, 0xcdd61cb4U, 0xc8924910U,
                };
                HW_SCE_p_func101(Param_p95i_func101_011);
                HW_SCE_p_func044();

                static const uint32_t Param_p95i_func101_012[] =
                {
                    0x1cdebdebU, 0x9c5b7556U, 0xa53a1999U, 0x848fff3bU,
                };
                HW_SCE_p_func101(Param_p95i_func101_012);
            }

            static const uint32_t Param_p95i_func100_007[] =
            {
                0x3e45fc6dU, 0x962c09ddU, 0x093b46c2U, 0xd3969b66U,
            };
            HW_SCE_p_func100(Param_p95i_func100_007);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            WR1_PROG(REG_E0H, 0x80040080U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p95i_func101_013[] =
            {
                0x84dc3d3eU, 0x5acc7e85U, 0xbda14854U, 0x01d016b8U,
            };
            HW_SCE_p_func101(Param_p95i_func101_013);
        }

        static const uint32_t Param_p95i_func100_008[] =
        {
            0xff548021U, 0x70e8fca7U, 0x696ff4ccU, 0x000e04a5U,
        };
        HW_SCE_p_func100(Param_p95i_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p95i_func102_002[] =
            {
                0x8234135dU, 0xa43a55aaU, 0x5977549aU, 0x775bd901U,
            };
            HW_SCE_p_func102(Param_p95i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub007(0x00003412U, 0x3420a800U, 0x00000004U, 0x00260000U);

            static const uint32_t Param_p95i_func100_009[] =
            {
                0xb1ccfaaeU, 0x6226c18cU, 0x059a3b6cU, 0xd3236dfaU,
            };
            HW_SCE_p_func100(Param_p95i_func100_009);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040885U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

                HW_SCE_p_func_sub021(0x00000734U);

                HW_SCE_p_func_sub021(0x00050804U);

                WR1_PROG(REG_104H, 0x000000b1U);
                WR1_PROG(REG_A4H, 0x00f00806U);

                for (iLoop = 0U; iLoop < Header_Len; )
                {
                    WAIT_STS(REG_104H, 31, 1);
                    WR4_ADDR(REG_100H, &InData_Header[iLoop]);
                    iLoop = iLoop + 4U;
                }

                HW_SCE_p_func205();

                static const uint32_t Param_p95i_func101_014[] =
                {
                    0x2f96d604U, 0xcd1b75c6U, 0xf083c04aU, 0x4221e51cU,
                };
                HW_SCE_p_func101(Param_p95i_func101_014);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000168U);
                WR1_PROG(REG_E0H, 0x800201c0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[0]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[1]);

                HW_SCE_p_func_sub022(0x000008aeU, 0x000008cfU, 0x0000b460U, 0x00000002U);

                HW_SCE_p_func_sub022(0x01986c64U, 0x01986c85U, 0x01986ca6U, 0x00186cc6U);

                WR1_PROG(REG_A4H, 0x00040885U);
                HW_SCE_p_func_sub010(0x81040060U, 0x00001813U);

                HW_SCE_p_func_sub019(0x00060805U, 0x00001113U);

                HW_SCE_p_func_sub021(0x00000734U);

                HW_SCE_p_func_sub021(0x00050804U);

                WR1_PROG(REG_ECH, 0x0000b540U);
                WR1_PROG(REG_ECH, 0x00000010U);
                HW_SCE_p_func031(InData_Header);

                static const uint32_t Param_p95i_func101_015[] =
                {
                    0x8c6ae1adU, 0x18269089U, 0x59571e54U, 0xedaa9de2U,
                };
                HW_SCE_p_func101(Param_p95i_func101_015);
            }

            static const uint32_t Param_p95i_func100_010[] =
            {
                0x6c603327U, 0xae7570afU, 0x2a39d291U, 0x98fd10adU,
            };
            HW_SCE_p_func100(Param_p95i_func100_010);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_p95i_func102_003[] =
                {
                    0xecf7f101U, 0xea31c459U, 0x69c3a2daU, 0x0c3a9ff1U,
                };
                HW_SCE_p_func102(Param_p95i_func102_003);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_p95i_func101_016[] =
                {
                    0x733fa2afU, 0xd52b796fU, 0x99673d12U, 0xd9024448U,
                };
                HW_SCE_p_func101(Param_p95i_func101_016);

                return FSP_SUCCESS;
            }
        }
    }
}
