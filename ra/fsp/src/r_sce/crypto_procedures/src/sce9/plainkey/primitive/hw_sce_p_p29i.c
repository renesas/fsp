/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub (uint32_t InData_KeyType[], uint32_t InData_KeyIndex[], uint32_t InData_IV[])
{
    uint32_t InData_DataType[1] = {0};
    uint32_t InData_Cmd[1]      = {0};
    uint32_t InData_SeqNum[2]   = {0, 0};

    if (RD1_MASK(REG_1BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_84H, 0x00002902U);
    WR1_PROG(REG_108H, 0x00000000U);

    WR1_PROG(REG_C4H, 0x200e1a0dU);
    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &S_RAM[20 + 0]);

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010100U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_KeyType[0]);

    HW_SCE_p_func_sub014(0x38008900U, 0x00000003U, 0x00260000U);

    static const uint32_t Param_p29i_func100_001[] =
    {
        0x6b382aa4U, 0x33174681U, 0xefbf17aeU, 0x06fadd5bU,
    };
    HW_SCE_p_func100(Param_p29i_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p29i_func102_001[] =
        {
            0xe522b6b7U, 0x4f9df3d1U, 0x8bf4a601U, 0x8588e7f8U,
        };
        HW_SCE_p_func102(Param_p29i_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x38000d08U);
        WR1_PROG(REG_E0H, 0x00000080U);
        WR1_PROG(REG_1CH, 0x00260000U);

        HW_SCE_p_func_sub014(0x38008900U, 0x00000002U, 0x00260000U);

        static const uint32_t Param_p29i_func100_002[] =
        {
            0x0bde1b8fU, 0x7b7dd407U, 0xe9706775U, 0x5a99bf42U,
        };
        HW_SCE_p_func100(Param_p29i_func100_002);
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

            static const uint32_t Param_p29i_func100_003[] =
            {
                0x4c369988U, 0x4f4d8a68U, 0x1bc827d6U, 0x7a926df4U,
            };
            HW_SCE_p_func100(Param_p29i_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                HW_SCE_p_func_sub009(0x800103a0U, 0x00000029U);

                static const uint32_t Param_p29i_func101_001[] =
                {
                    0x052b7216U, 0x91f9cb7eU, 0xa126049fU, 0x464ed006U,
                };
                HW_SCE_p_func101(Param_p29i_func101_001);
                HW_SCE_p_func043();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000005U);

                static const uint32_t Param_p29i_func101_002[] =
                {
                    0xe901524bU, 0x3472aa7bU, 0xaba040b0U, 0xa105b27bU,
                };
                HW_SCE_p_func101(Param_p29i_func101_002);
            }
            else
            {
                HW_SCE_p_func_sub005(0x00003547U, 0x00000058U, 0x800103a0U, 0x00000029U);

                static const uint32_t Param_p29i_func101_003[] =
                {
                    0x0305165dU, 0x12770d2cU, 0x638119d4U, 0xab9f838cU,
                };
                HW_SCE_p_func101(Param_p29i_func101_003);
                HW_SCE_p_func068();

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x0146c04bU);

                static const uint32_t Param_p29i_func101_004[] =
                {
                    0xe420a06fU, 0x2d5c4d73U, 0x07a4a937U, 0x9a0afc88U,
                };
                HW_SCE_p_func101(Param_p29i_func101_004);
            }

            HW_SCE_p_func_sub009(0x800103a0U, 0x00000029U);

            static const uint32_t Param_p29i_func101_005[] =
            {
                0x41acb932U, 0x1a93d263U, 0x1040891fU, 0x85c5664eU,
            };
            HW_SCE_p_func101(Param_p29i_func101_005);
            HW_SCE_p_func044();

            static const uint32_t Param_p29i_func100_004[] =
            {
                0xd177a4d2U, 0x55fd89a4U, 0x4101c1d1U, 0xdbacd9feU,
            };
            HW_SCE_p_func100(Param_p29i_func100_004);
            HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
            WR4_ADDR(REG_100H, &InData_KeyIndex[1]);

            WR1_PROG(REG_A4H, 0x00080805U);
            WR1_PROG(REG_00H, 0x00001213U);
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

            static const uint32_t Param_p29i_func101_006[] =
            {
                0x7c240052U, 0x386c9704U, 0xb361b7ffU, 0x1e4f00bfU,
            };
            HW_SCE_p_func101(Param_p29i_func101_006);
        }
        else
        {
            HW_SCE_p_func_sub014(0x38008900U, 0x00000001U, 0x00260000U);

            static const uint32_t Param_p29i_func100_005[] =
            {
                0xf7f5d62fU, 0xd414c789U, 0x62d34fcaU, 0xa08c4049U,
            };
            HW_SCE_p_func100(Param_p29i_func100_005);
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
                HW_SCE_p_func_sub022(0x38008be0U, 0x00120000U, 0x1000d3c0U, 0x3800d80fU);
                HW_SCE_p_func_sub022(0x2000d3c1U, 0x000037e0U, 0x00008fe0U, 0x000000feU);

                WR1_PROG(REG_ECH, 0x38008be0U);
                WR1_PROG(REG_ECH, 0x00000000U);
                HW_SCE_p_func_sub007(0x1000d3c2U, 0x38008bc0U, 0x00000007U, 0x00A60000U);

                WR1_PROG(REG_ECH, 0x00003540U);
                WR1_PROG(REG_ECH, 0x00003561U);
                WR1_PROG(REG_ECH, 0x00003582U);
                HW_SCE_p_func_sub005(0x000035a3U, 0x00000058U, 0x800103a0U, 0x00000029U);

                static const uint32_t Param_p29i_func101_007[] =
                {
                    0x0e8dc5a7U, 0xb49ecf91U, 0x36535c56U, 0x9d795f50U,
                };
                HW_SCE_p_func101(Param_p29i_func101_007);
                HW_SCE_p_func059();

                static const uint32_t Param_p29i_func100_006[] =
                {
                    0x85c33db3U, 0xfaf76717U, 0x874d3287U, 0x50161587U,
                };
                HW_SCE_p_func100(Param_p29i_func100_006);
                HW_SCE_p_func_sub018(0x00000362U, 0x40000000U, 0x02f087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[4]);

                WR1_PROG(REG_A4H, 0x00080805U);
                WR1_PROG(REG_00H, 0x00001213U);
                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x00f087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[8]);
                WR1_PROG(REG_E0H, 0x80040080U);
                WR1_PROG(REG_00H, 0x00008213U);
                HW_SCE_p_func_sub003(0x00000362U, 0x40000000U, 0x000087b5U);
                WR4_ADDR(REG_100H, &InData_KeyIndex[12]);

                HW_SCE_p_func_sub013(0x00900c45U, 0x00002213U);
                static const uint32_t Param_p29i_func101_008[] =
                {
                    0x3f2fe7f5U, 0x739749ffU, 0x44e9ba49U, 0x61bce77aU,
                };
                HW_SCE_p_func101(Param_p29i_func101_008);
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

                static const uint32_t Param_p29i_func100_007[] =
                {
                    0xeff93c39U, 0x77b1edbcU, 0x4f973ac1U, 0x672ecef6U,
                };
                HW_SCE_p_func100(Param_p29i_func100_007);
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
                    HW_SCE_p_func_sub005(0x01c18a1aU, 0x00000058U, 0x800103a0U, 0x00000029U);

                    static const uint32_t Param_p29i_func101_009[] =
                    {
                        0x89e3d905U, 0x08b0f537U, 0xc476c938U, 0x75c7d7b7U,
                    };
                    HW_SCE_p_func101(Param_p29i_func101_009);
                    HW_SCE_p_func082();

                    static const uint32_t Param_p29i_func101_010[] =
                    {
                        0xe8b5a5cfU, 0xfa50c674U, 0x343c3f83U, 0xe8899844U,
                    };
                    HW_SCE_p_func101(Param_p29i_func101_010);
                }
                else
                {
                    HW_SCE_p_func_sub009(0x800103a0U, 0x000000edU);

                    static const uint32_t Param_p29i_func101_011[] =
                    {
                        0x01b680e5U, 0x22cf6c6aU, 0xe9ae05ecU, 0x4cbb570eU,
                    };
                    HW_SCE_p_func101(Param_p29i_func101_011);
                    HW_SCE_p_func068();

                    WR1_PROG(REG_ECH, 0x0000b4e0U);
                    HW_SCE_p_func_sub005(0x01d6575eU, 0x00000058U, 0x800103a0U, 0x000000edU);

                    static const uint32_t Param_p29i_func101_012[] =
                    {
                        0x22447b96U, 0x29e0435bU, 0x2fc3a7feU, 0xb6c60312U,
                    };
                    HW_SCE_p_func101(Param_p29i_func101_012);
                    HW_SCE_p_func044();

                    static const uint32_t Param_p29i_func101_013[] =
                    {
                        0x6e4d01daU, 0x0527013aU, 0x6981610fU, 0xb912b293U,
                    };
                    HW_SCE_p_func101(Param_p29i_func101_013);
                }

                WR1_PROG(REG_104H, 0x00000168U);
                WR1_PROG(REG_E0H, 0x80020360U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[0]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_SeqNum[1]);

                static const uint32_t Param_p29i_func100_008[] =
                {
                    0xbb207189U, 0x5c201d05U, 0x5555ed55U, 0xda785248U,
                };
                HW_SCE_p_func100(Param_p29i_func100_008);
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

                static const uint32_t Param_p29i_func101_014[] =
                {
                    0x3fcf986cU, 0x93ab7bdaU, 0x7568a4b5U, 0x17ae5806U,
                };
                HW_SCE_p_func101(Param_p29i_func101_014);
            }

            static const uint32_t Param_p29i_func101_015[] =
            {
                0xe857747eU, 0x860c8888U, 0x1a7b13d1U, 0x87d92187U,
            };
            HW_SCE_p_func101(Param_p29i_func101_015);
        }

        static const uint32_t Param_p29i_func100_009[] =
        {
            0x8bff74d4U, 0x226b6052U, 0x135a49e1U, 0xaf348c2bU,
        };
        HW_SCE_p_func100(Param_p29i_func100_009);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p29i_func102_002[] =
            {
                0x66eabf73U, 0xf41d1e94U, 0xf9a72548U, 0x06165eacU,
            };
            HW_SCE_p_func102(Param_p29i_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub022(0x3000a900U, 0x00000004U, 0x00010020U, 0x000008bbU);
            HW_SCE_p_func_sub022(0x000008dcU, 0x0000b4e0U, 0x00000001U, 0x00000080U);

            WR1_PROG(REG_7CH, 0x00000001U);
            WR1_PROG(REG_7CH, 0x00000041U);

            HW_SCE_p_func_sub021(0x00000a84U);

            WR1_PROG(REG_00H, 0x00005113U);
            WR1_PROG(REG_74H, 0x00001000U);
            WAIT_STS(REG_00H, 25, 0);
            WR1_PROG(REG_1CH, 0x00001800U);

            WR1_PROG(REG_74H, 0x00000004U);
            WR1_PROG(REG_104H, 0x00000354U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_PROG(REG_100H, change_endian_long(0x00000000U), change_endian_long(0x00000000U),
                     change_endian_long(0x00000000U), change_endian_long(0x00000000U));

            WR1_PROG(REG_74H, 0x00000002U);

            static const uint32_t Param_p29i_func101_016[] =
            {
                0xdd6d541cU, 0x9bcf665cU, 0x1cdc93f5U, 0xf6d0f1c1U,
            };
            HW_SCE_p_func101(Param_p29i_func101_016);

            return FSP_SUCCESS;
        }
    }
}
