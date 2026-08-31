/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyType[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00004702U);
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

    static const uint32_t Param_p47i_func100_001[] =
    {
        0x532c8e1cU, 0xd74f9414U, 0xf0668f09U, 0xdb7c033fU,
    };
    HW_SCE_p_func100(Param_p47i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p47i_func102_001[] =
        {
            0x08fc129bU, 0xca48bf72U, 0x83bffd7bU, 0xe2ae50ebU,
        };
        HW_SCE_p_func102(Param_p47i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        HW_SCE_p_func_sub022(0x3000a800U, 0x00000006U, 0x00010020U, 0x0000b400U);
        WR1_PROG(REG_ECH, 0x00000006U);
        HW_SCE_p_func_sub007(0x00000080U, 0x3420a800U, 0x00000005U, 0x00260000U);

        static const uint32_t Param_p47i_func100_002[] =
        {
            0x0cf2a0baU, 0xfaa011d9U, 0xd6260a22U, 0x6b06c529U,
        };
        HW_SCE_p_func100(Param_p47i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_ECH, 0x38000c21U);
            WR1_PROG(REG_E0H, 0x00000080U);
            WR1_PROG(REG_1CH, 0x00260000U);

            static const uint32_t Param_p47i_func100_003[] =
            {
                0x9d6b7d16U, 0xb1711fa5U, 0xb576511fU, 0x6e4369ceU,
            };
            HW_SCE_p_func100(Param_p47i_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x800100e0U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000047U);

                static const uint32_t Param_p47i_func101_001[] =
                {
                    0xd20024d3U, 0xacee990cU, 0x97604b90U, 0x603c6bf1U,
                };
                HW_SCE_p_func101(Param_p47i_func101_001);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000005U);

                static const uint32_t Param_p47i_func101_002[] =
                {
                    0x8008a7c5U, 0x05828c5bU, 0x56c92714U, 0xc12875f0U,
                };
                HW_SCE_p_func101(Param_p47i_func101_002);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010140U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_KeyIndex[0]);

                HW_SCE_p_func_sub009(0x800103a0U, 0x00000047U);

                static const uint32_t Param_p47i_func101_003[] =
                {
                    0x14e64260U, 0xced09e8dU, 0xeb683f31U, 0x5d23c058U,
                };
                HW_SCE_p_func101(Param_p47i_func101_003);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x0146c04bU);

                static const uint32_t Param_p47i_func101_004[] =
                {
                    0x5e4130b7U, 0x2f8db7dfU, 0x1fa3ae39U, 0xb088b8bdU,
                };
                HW_SCE_p_func101(Param_p47i_func101_004);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000047U);

            static const uint32_t Param_p47i_func101_005[] =
            {
                0xbd5f7685U, 0x83297732U, 0xe56b3888U, 0x418c6101U,
            };
            HW_SCE_p_func101(Param_p47i_func101_005);
            HW_SCE_p_func044();

            static const uint32_t Param_p47i_func100_004[] =
            {
                0x5250cc11U, 0xb301ced7U, 0x9817c7a8U, 0x9bd7e48bU,
            };
            HW_SCE_p_func100(Param_p47i_func100_004);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p47i_func101_006[] =
            {
                0x71a31542U, 0x9aed6fa8U, 0xf59174f1U, 0x27db8085U,
            };
            HW_SCE_p_func101(Param_p47i_func101_006);
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
            HW_SCE_p_func_sub022(0x38008be0U, 0x00000000U, 0x1000d3c0U, 0x38008800U);
            HW_SCE_p_func_sub022(0x00000005U, 0x1000b540U, 0x0000000fU, 0x2000b540U);
            HW_SCE_p_func_sub022(0x0000000eU, 0x3800584aU, 0x2000d3c1U, 0x000037e2U);

            HW_SCE_p_func_sub022(0x00008fe0U, 0x000000feU, 0x38008be0U, 0x00000000U);
            HW_SCE_p_func_sub007(0x1000d3c2U, 0x38008bc0U, 0x00000007U, 0x00A60000U);

            HW_SCE_p_func_sub022(0x0000a800U, 0x00000003U, 0x00003542U, 0x00003563U);
            WR1_PROG(REG_ECH, 0x00003584U);
            HW_SCE_p_func_sub005(0x000035a5U, 0x00000058U, 0x800103a0U, 0x00000047U);

            static const uint32_t Param_p47i_func101_007[] =
            {
                0x1687882dU, 0x9da40824U, 0xc51cb495U, 0x72e5393fU,
            };
            HW_SCE_p_func101(Param_p47i_func101_007);
            HW_SCE_p_func059();

            static const uint32_t Param_p47i_func100_005[] =
            {
                0x1d35c958U, 0x8ab99b81U, 0x1fab250aU, 0xeeb14dabU,
            };
            HW_SCE_p_func100(Param_p47i_func100_005);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[4]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[8]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p47i_func101_008[] =
            {
                0x2ed80b05U, 0x05c0a092U, 0x2d7c1493U, 0xa013dd18U,
            };
            HW_SCE_p_func101(Param_p47i_func101_008);
        }

        static const uint32_t Param_p47i_func100_006[] =
        {
            0x23d71ff2U, 0x269e97edU, 0x7c5758d6U, 0x7eee3c98U,
        };
        HW_SCE_p_func100(Param_p47i_func100_006);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p47i_func102_002[] =
            {
                0xc49afd04U, 0xad543216U, 0x365184f1U, 0x682bed01U,
            };
            HW_SCE_p_func102(Param_p47i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            static const uint32_t Param_p47i_func100_007[] =
            {
                0xaeda5fa2U, 0xde5b2655U, 0xf5f717d4U, 0x561961b6U,
            };
            HW_SCE_p_func100(Param_p47i_func100_007);
            WR1_PROG(REG_ECH, 0x00007c00U);
            WR1_PROG(REG_1CH, 0x00600000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
            {
                static const uint32_t Param_p47i_func101_009[] =
                {
                    0x6317b67fU, 0x19fb60bbU, 0xfd5be6a1U, 0xe4ba0012U,
                };
                HW_SCE_p_func101(Param_p47i_func101_009);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
            {
                static const uint32_t Param_p47i_func101_010[] =
                {
                    0x2cbc50c3U, 0x98f57fb0U, 0x6cb20cc8U, 0xb53b230fU,
                };
                HW_SCE_p_func101(Param_p47i_func101_010);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p47i_func101_011[] =
                {
                    0xbb9fe1d2U, 0x1a6df08bU, 0x363b6c60U, 0xd6a6c086U,
                };
                HW_SCE_p_func101(Param_p47i_func101_011);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p47i_func101_012[] =
                {
                    0x2071f517U, 0x5e521a7cU, 0x0778d7aaU, 0xf1658938U,
                };
                HW_SCE_p_func101(Param_p47i_func101_012);
            }
            else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_A4H, 0x00040805U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_IV[0]);

                static const uint32_t Param_p47i_func101_013[] =
                {
                    0xc1078ed4U, 0x62c94addU, 0x1c3172c4U, 0x73654dd1U,
                };
                HW_SCE_p_func101(Param_p47i_func101_013);
            }

            return FSP_SUCCESS;
        }
    }
}
