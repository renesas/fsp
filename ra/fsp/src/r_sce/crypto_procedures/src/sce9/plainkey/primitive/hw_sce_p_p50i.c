/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyType[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00005002U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_E0H, 0x80020000U);
    WR1_PROG(REG_104H, 0x00000168U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_Cmd[0]);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008820U, 0x00000001U, 0x00260000U);

    static const uint32_t Param_p50i_func100_001[] =
    {
        0x16c69ca2U, 0x6f2d0d17U, 0x1bb97fc0U, 0x52438106U,
    };
    HW_SCE_p_func100(Param_p50i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p50i_func102_001[] =
        {
            0x3ffdc58bU, 0x308f816aU, 0x66329743U, 0xad87264eU,
        };
        HW_SCE_p_func102(Param_p50i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub022(0x3000a800U, 0x00000006U, 0x00010020U, 0x0000b400U);
        WR1_PROG(REG_ECH, 0x00000006U);
        HW_SCE_p_func_sub007(0x00000080U, 0x3420a800U, 0x00000005U, 0x00260000U);

        static const uint32_t Param_p50i_func100_002[] =
        {
            0xb8d606c7U, 0xda6c9782U, 0x3843312eU, 0x4f82a40eU,
        };
        HW_SCE_p_func100(Param_p50i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x38000c21U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p50i_func100_003[] =
            {
                0x4c892443U, 0x3aee2f7aU, 0x932a749dU, 0x001e0d73U,
            };
            HW_SCE_p_func100(Param_p50i_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000050U);

                static const uint32_t Param_p50i_func101_001[] =
                {
                    0x3a670b62U, 0x49d899ebU, 0x177bde9fU, 0x419688d6U,
                };
                HW_SCE_p_func101(Param_p50i_func101_001);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000007U);

                static const uint32_t Param_p50i_func101_002[] =
                {
                    0x9e43586dU, 0xd870c7deU, 0x3e9d2089U, 0x6b404b30U,
                };
                HW_SCE_p_func101(Param_p50i_func101_002);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010140U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000050U);

                static const uint32_t Param_p50i_func101_003[] =
                {
                    0x23e57fecU, 0x52911439U, 0x6b98afd7U, 0x476b4437U,
                };
                HW_SCE_p_func101(Param_p50i_func101_003);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x01d04999U);

                static const uint32_t Param_p50i_func101_004[] =
                {
                    0x301bbfc3U, 0x311c1605U, 0xb1d94629U, 0xbd2989fdU,
                };
                HW_SCE_p_func101(Param_p50i_func101_004);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000050U);

            static const uint32_t Param_p50i_func101_005[] =
            {
                0xb787dacdU, 0x1029a880U, 0x350af480U, 0xf1892ae5U,
            };
            HW_SCE_p_func101(Param_p50i_func101_005);
            HW_SCE_p_func044();

            static const uint32_t Param_p50i_func100_004[] =
            {
                0x66dc5d68U, 0x94d4454cU, 0x572c97f9U, 0xb1ae352dU,
            };
            HW_SCE_p_func100(Param_p50i_func100_004);
            HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

            static const uint32_t Param_p50i_func100_005[] =
            {
                0xa3d98bd6U, 0xde409614U, 0x4865160bU, 0xe2778f91U,
            };
            HW_SCE_p_func100(Param_p50i_func100_005);
            WR1_PROG(REG_A4H, 0x00090805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p50i_func101_006[] =
            {
                0x17dff15fU, 0x20f1bb5bU, 0x898d984fU, 0x7254aa8bU,
            };
            HW_SCE_p_func101(Param_p50i_func101_006);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000368U);
            WR1_PROG(REG_E0H, 0x80040040U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[2]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[3]);

            HW_SCE_p_func_sub022(0x00000bdeU, 0x000037e2U, 0x00008fe0U, 0x00ff0000U);
            HW_SCE_p_func_sub022(0x38008be0U, 0x00010000U, 0x1000d3c0U, 0x38008800U);
            HW_SCE_p_func_sub022(0x00000005U, 0x1000b540U, 0x0000000fU, 0x2000b540U);
            HW_SCE_p_func_sub022(0x0000000eU, 0x3800584aU, 0x2000d3c1U, 0x000037e2U);

            HW_SCE_p_func_sub022(0x00008fe0U, 0x000000feU, 0x38008be0U, 0x00000000U);
            HW_SCE_p_func_sub007(0x1000d3c2U, 0x38008bc0U, 0x00000007U, 0x00A60000U);

            HW_SCE_p_func_sub022(0x0000a800U, 0x00000003U, 0x00003542U, 0x00003563U);
            WR1_PROG(REG_ECH, 0x00003584U);
            HW_SCE_p_func_sub005(0x000035a5U, 0x00000058U, 0x800103a0U, 0x00000050U);

            static const uint32_t Param_p50i_func101_007[] =
            {
                0xe430e76eU, 0xad57e32aU, 0xf7574b2cU, 0xf4eb1a01U,
            };
            HW_SCE_p_func101(Param_p50i_func101_007);
            HW_SCE_p_func059();

            static const uint32_t Param_p50i_func100_006[] =
            {
                0xfc41514eU, 0x17da911bU, 0xd1be8b6aU, 0xb76ef6c2U,
            };
            HW_SCE_p_func100(Param_p50i_func100_006);
            HW_SCE_p_func_sub018(0x00000762U, 0x40000100U, 0x02f087b7U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[4]);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_KeyIndex[8]);

            HW_SCE_p_func_sub019(0x00080805U, 0x00001213U);

            static const uint32_t Param_p50i_func100_007[] =
            {
                0x0d06633fU, 0x33b5eaf5U, 0xe669c903U, 0xe82117f6U,
            };
            HW_SCE_p_func100(Param_p50i_func100_007);
            WR1_PROG(REG_A4H, 0x00090805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[12]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p50i_func101_008[] =
            {
                0x8c69626bU, 0x5de5b806U, 0x5bac9351U, 0x6dd3268aU,
            };
            HW_SCE_p_func101(Param_p50i_func101_008);
        }

        static const uint32_t Param_p50i_func100_008[] =
        {
            0x5ff04b9dU, 0x57ca6309U, 0x23b899f2U, 0x745813d3U,
        };
        HW_SCE_p_func100(Param_p50i_func100_008);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p50i_func102_002[] =
            {
                0x182c0c60U, 0x403e5024U, 0x4c783f34U, 0xa5931c4fU,
            };
            HW_SCE_p_func102(Param_p50i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            static const uint32_t Param_p50i_func100_009[] =
            {
                0xe90e057dU, 0x751e1344U, 0x0c457b65U, 0xc6384d26U,
            };
            HW_SCE_p_func100(Param_p50i_func100_009);
            WR1_PROG(REG_ECH, 0x00007c00U);
            WR1_PROG(REG_1CH, 0x00600000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
            {
                static const uint32_t Param_p50i_func101_009[] =
                {
                    0xf7564ec6U, 0xfc8fee14U, 0x68d8f04dU, 0x7cd97ddfU,
                };
                HW_SCE_p_func101(Param_p50i_func101_009);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
            {
                static const uint32_t Param_p50i_func101_010[] =
                {
                    0x9b8c735fU, 0x1996db69U, 0x27ad127dU, 0x5baa1bafU,
                };
                HW_SCE_p_func101(Param_p50i_func101_010);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p50i_func101_011[] =
                {
                    0x9a3481c6U, 0x23ad7f13U, 0xb98191efU, 0x8583a18aU,
                };
                HW_SCE_p_func101(Param_p50i_func101_011);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p50i_func101_012[] =
                {
                    0x24dfd549U, 0xa86c095cU, 0x7ab0b3e6U, 0x1250ea99U,
                };
                HW_SCE_p_func101(Param_p50i_func101_012);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p50i_func101_013[] =
                {
                    0xa4ee5387U, 0x04926488U, 0x640c45a0U, 0x6b18613cU,
                };
                HW_SCE_p_func101(Param_p50i_func101_013);
            }

            return FSP_SUCCESS;
        }
    }
}
