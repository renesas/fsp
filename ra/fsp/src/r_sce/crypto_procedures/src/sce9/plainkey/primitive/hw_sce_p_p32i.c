/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmDecryptInitSub (uint32_t InData_KeyType[], uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    uint32_t InData_DataType[1] = {0};
    uint32_t InData_Cmd[1]      = {0};
    uint32_t InData_SeqNum[2]   = {0, 0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00003202U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010100U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    WR1_PROG(REG_ECH, 0x38000d08U);
    WR1_PROG(REG_E0H, 0x00000080U);
    WR1_PROG(REG_1CH, 0x00260000U);

    HW_SCE_p_func_sub014(0x38008900U, 0x00000002U, 0x00260000U);

    static const uint32_t Param_p32i_func100_001[] =
    {
        0xdd9640ceU, 0x25ac9382U, 0x64198734U, 0x80932e7eU,
    };
    HW_SCE_p_func100(Param_p32i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x800100e0U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_KeyIndex[0]);

        WR1_PROG(REG_ECH, 0x38000d08U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        static const uint32_t Param_p32i_func100_002[] =
        {
            0x7b27127eU, 0xd8d290bbU, 0x5769c33cU, 0x23dee02bU,
        };
        HW_SCE_p_func100(Param_p32i_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            HW_SCE_p_func_sub009(0x800103a0U, 0x00000032U);

            static const uint32_t Param_p32i_func101_001[] =
            {
                0x792ec90dU, 0xdd1224f8U, 0xb9cefd1dU, 0x18de7561U,
            };
            HW_SCE_p_func101(Param_p32i_func101_001);
            HW_SCE_p_func043();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x00000005U);

            static const uint32_t Param_p32i_func101_002[] =
            {
                0x58a83a1fU, 0xd313ece4U, 0xdc2ffadcU, 0xf032b621U,
            };
            HW_SCE_p_func101(Param_p32i_func101_002);
        }
        else
        {
            HW_SCE_p_func_sub005(0x00003547U, 0x00000058U, 0x800103a0U, 0x00000032U);

            static const uint32_t Param_p32i_func101_003[] =
            {
                0xd82d0abbU, 0x8980254aU, 0x11ebd2dfU, 0x4f2b95f2U,
            };
            HW_SCE_p_func101(Param_p32i_func101_003);
            HW_SCE_p_func068();

            WR1_PROG(REG_ECH, 0x0000b4e0U);
            WR1_PROG(REG_ECH, 0x0146c04bU);

            static const uint32_t Param_p32i_func101_004[] =
            {
                0x909743dcU, 0x6a3f7342U, 0x54f93845U, 0xc8d45c52U,
            };
            HW_SCE_p_func101(Param_p32i_func101_004);
        }

        HW_SCE_p_func_sub009(0x800103a0U, 0x00000032U);

        static const uint32_t Param_p32i_func101_005[] =
        {
            0xab118389U, 0xb0997d8fU, 0x2f4502a2U, 0x77b66011U,
        };
        HW_SCE_p_func101(Param_p32i_func101_005);
        HW_SCE_p_func044();

        HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

        WR1_PROG(REG_E0H, 0x80040000U);
        WR1_PROG(REG_00H, 0x00008213U);
        HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
        WR4_ADDR(REG_100H, &InData_KeyIndex[5]);

        HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

        WR1_PROG(REG_104H, 0x00000368U);
        WR1_PROG(REG_E0H, 0x80040080U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[0]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[1]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[2]);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_IV[3]);

        static const uint32_t Param_p32i_func101_006[] =
        {
            0xa9a16879U, 0x9ca06cd5U, 0xc7b34f6bU, 0x04a1afadU,
        };
        HW_SCE_p_func101(Param_p32i_func101_006);
    }
    else
    {
        HW_SCE_p_func_sub014(0x38008900U, 0x00000001U, 0x00260000U);

        static const uint32_t Param_p32i_func100_003[] =
        {
            0x35391339U, 0xfe32aa12U, 0x10e80637U, 0x6e8c67c5U,
        };
        HW_SCE_p_func100(Param_p32i_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000368U);
            WR1_PROG(REG_E0H, 0x80040000U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[1]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[2]);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[3]);

            HW_SCE_p_func_sub022(0x00000bdeU, 0x000037e0U, 0x00008fe0U, 0x00ff0000U);
            HW_SCE_p_func_sub022(0x38008be0U, 0x00120000U, 0x1000d3c0U, 0x3800d80eU);
            HW_SCE_p_func_sub022(0x2000d3c1U, 0x000037e0U, 0x00008fe0U, 0x000000feU);

            WR1_PROG(REG_ECH, 0x38008be0U);
            WR1_PROG(REG_ECH, 0x00000000U);
            HW_SCE_p_func_sub007(0x1000d3c2U, 0x38008bc0U, 0x00000007U, 0x00A60000U);

            WR1_PROG(REG_ECH, 0x00003540U);
            WR1_PROG(REG_ECH, 0x00003561U);
            WR1_PROG(REG_ECH, 0x00003582U);
            HW_SCE_p_func_sub005(0x000035a3U, 0x00000058U, 0x800103a0U, 0x00000032U);

            static const uint32_t Param_p32i_func101_007[] =
            {
                0x99a917feU, 0xcc1ee76bU, 0x82ca28d2U, 0x2983be85U,
            };
            HW_SCE_p_func101(Param_p32i_func101_007);
            HW_SCE_p_func059();

            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[4]);

            WR1_PROG(REG_E0H, 0x80040000U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[8]);
            WR1_PROG(REG_E0H, 0x80040080U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[12]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p32i_func101_008[] =
            {
                0xaaf493abU, 0xd14d7026U, 0x40fe3605U, 0x7189daefU,
            };
            HW_SCE_p_func101(Param_p32i_func101_008);
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010140U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_KeyIndex[0]);

            HW_SCE_p_func_sub014(0x3800a900U, 0x00000003U, 0x00260000U);

            static const uint32_t Param_p32i_func100_004[] =
            {
                0x17503aa9U, 0x165c2793U, 0x1bf5a78cU, 0xc9a1780dU,
            };
            HW_SCE_p_func100(Param_p32i_func100_004);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub009(0x800103a0U, 0x00000005U);

                static const uint32_t Param_p32i_func101_009[] =
                {
                    0x4aec236bU, 0xa76966d2U, 0x7c3357beU, 0x4cacae75U,
                };
                HW_SCE_p_func101(Param_p32i_func101_009);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                HW_SCE_p_func_sub005(0x0195f71dU, 0x00000058U, 0x800103a0U, 0x00000005U);

                static const uint32_t Param_p32i_func101_010[] =
                {
                    0xae0bda23U, 0x6d486cb9U, 0x4cd9b7bbU, 0xc741ba11U,
                };
                HW_SCE_p_func101(Param_p32i_func101_010);
                HW_SCE_p_func044();

                static const uint32_t Param_p32i_func101_011[] =
                {
                    0xc7aa49fbU, 0x7f88901fU, 0x58b8d0adU, 0xac20a386U,
                };
                HW_SCE_p_func101(Param_p32i_func101_011);
            }
            else
            {
                WR1_PROG(REG_104H, 0x00000068U);
                WR1_PROG(REG_E0H, 0x80010020U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_DataType[0]);

                WR1_PROG(REG_ECH, 0x38000c21U);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                static const uint32_t Param_p32i_func100_005[] =
                {
                    0xa68b31bcU, 0x77a2b679U, 0xa66cff9eU, 0x884132aeU,
                };
                HW_SCE_p_func100(Param_p32i_func100_005);
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
                    HW_SCE_p_func_sub005(0x0126ee7fU, 0x00000058U, 0x800103a0U, 0x00000032U);

                    static const uint32_t Param_p32i_func101_012[] =
                    {
                        0x63756f95U, 0xdf1f784dU, 0xc9ddae30U, 0xaba98eebU,
                    };
                    HW_SCE_p_func101(Param_p32i_func101_012);
                    HW_SCE_p_func082();

                    static const uint32_t Param_p32i_func101_013[] =
                    {
                        0x1efbeae5U, 0x5b3e1313U, 0x2e9033c5U, 0x49aa5537U,
                    };
                    HW_SCE_p_func101(Param_p32i_func101_013);
                }
                else
                {
                    HW_SCE_p_func_sub009(0x800103a0U, 0x000000ecU);

                    static const uint32_t Param_p32i_func101_014[] =
                    {
                        0xe368a5f9U, 0xeffac90cU, 0x2c19ec6bU, 0x7e2a0c68U,
                    };
                    HW_SCE_p_func101(Param_p32i_func101_014);
                    HW_SCE_p_func068();

                    WR1_PROG(REG_ECH, 0x0000b4e0U);
                    HW_SCE_p_func_sub005(0x01bae316U, 0x00000058U, 0x800103a0U, 0x000000ecU);

                    static const uint32_t Param_p32i_func101_015[] =
                    {
                        0xbe62186bU, 0x2c17636bU, 0x186d4f8cU, 0x8398b9bbU,
                    };
                    HW_SCE_p_func101(Param_p32i_func101_015);
                    HW_SCE_p_func044();

                    static const uint32_t Param_p32i_func101_016[] =
                    {
                        0x81a2c8daU, 0xe36ae01cU, 0x90156779U, 0x357cbb76U,
                    };
                    HW_SCE_p_func101(Param_p32i_func101_016);
                }

                WR1_PROG(REG_104H, 0x00000168U);
                WR1_PROG(REG_E0H, 0x80020360U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[0]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[1]);

                static const uint32_t Param_p32i_func101_017[] =
                {
                    0xe05b980dU, 0x73a1f29bU, 0x159afecbU, 0x9387431dU,
                };
                HW_SCE_p_func101(Param_p32i_func101_017);
            }

            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_E0H, 0x80040000U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[5]);
            WR1_PROG(REG_E0H, 0x80040080U);
            WR1_PROG(REG_00H, 0x00008213U);
            HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[9]);

            HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);

            static const uint32_t Param_p32i_func101_018[] =
            {
                0x96487d5cU, 0x2b80fe4fU, 0x5c3a7fa5U, 0x5c6f2d46U,
            };
            HW_SCE_p_func101(Param_p32i_func101_018);
        }

        static const uint32_t Param_p32i_func101_019[] =
        {
            0x42144622U, 0x23463917U, 0x5a687bd1U, 0x1b2ac5b1U,
        };
        HW_SCE_p_func101(Param_p32i_func101_019);
    }

    static const uint32_t Param_p32i_func100_006[] =
    {
        0x8288a3f2U, 0x9d4c7699U, 0x30fddadeU, 0xb26157c4U,
    };
    HW_SCE_p_func100(Param_p32i_func100_006);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p32i_func102_001[] =
        {
            0x13eeffc6U, 0xe6ce0b0bU, 0x2eae03eeU, 0x2a9b5de9U,
        };
        HW_SCE_p_func102(Param_p32i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        static const uint32_t Param_p32i_func100_007[] =
        {
            0xc1e91d46U, 0xdf317272U, 0x9ce8c12eU, 0x73f154c6U,
        };
        HW_SCE_p_func100(Param_p32i_func100_007);
        HW_SCE_p_func_sub022(0x3000a900U, 0x00000004U, 0x00010020U, 0x000008bbU);
        HW_SCE_p_func_sub022(0x000008dcU, 0x0000b4e0U, 0x00000001U, 0x00000080U);

        WR1_PROG(REG_E0H, 0x81040000U);
        HW_SCE_p_func_sub013(0x00080805U, 0x00002813U);

        WR1_PROG(REG_7CH, 0x00000001U);
        WR1_PROG(REG_7CH, 0x00000041U);

        HW_SCE_p_func_sub012(0x00000052U, 0x00000a84U, 0x00000000U);

        WR1_PROG(REG_00H, 0x00005213U);
        WR1_PROG(REG_74H, 0x00001000U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_74H, 0x00000004U);
        WR1_PROG(REG_104H, 0x00000354U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                 change_endian_long(0x00000000U), change_endian_long(0x00000000U));

        WR1_PROG(REG_74H, 0x00000002U);

        static const uint32_t Param_p32i_func101_020[] =
        {
            0x3406306bU, 0x11c79103U, 0xb70824e1U, 0xf9ea4bd4U,
        };
        HW_SCE_p_func101(Param_p32i_func101_020);

        return FSP_SUCCESS;
    }
}
