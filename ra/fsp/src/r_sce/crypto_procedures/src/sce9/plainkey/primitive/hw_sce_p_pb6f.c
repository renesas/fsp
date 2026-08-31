/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub (uint32_t InData_TextBitLen[], uint32_t InData_Text[],
                                           uint32_t OutData_Text[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010000U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextBitLen[0]);

    HW_SCE_p_func_sub022(0x000037c0U, 0x00076bdeU, 0x00026fdeU, 0x00000bffU);

    HW_SCE_p_func_sub022(0x38008c00U, 0x0000007fU, 0x00020020U, 0x3420a800U);
    WR1_PROG(REG_ECH, 0x00000080U);
    WR1_PROG(REG_ECH, 0x1000d3e0U);
    WR1_PROG(REG_ECH, 0x2000abc0U);
    HW_SCE_p_func_sub007(0x00000004U, 0x00000080U, 0x38000fffU, 0x00A60000U);

    static const uint32_t Param_pb6f_func100_001[] =
    {
        0xca624a8dU, 0xdadff4e7U, 0x2a86a494U, 0xbafc5094U,
    };
    HW_SCE_p_func100(Param_pb6f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb6f_func102_001[] =
        {
            0xd37a0b7cU, 0xc42aa712U, 0x183f3f79U, 0x3b712616U,
        };
        HW_SCE_p_func102(Param_pb6f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pb6f_func100_002[] =
        {
            0x1565838dU, 0xc2d03568U, 0x6ad73cfbU, 0x860aef7fU,
        };
        HW_SCE_p_func100(Param_pb6f_func100_002);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        static const uint32_t Param_pb6f_func100_003[] =
        {
            0xf539e42bU, 0x46f05f8dU, 0xfaaa2b74U, 0xf2bd30b3U,
        };
        HW_SCE_p_func100(Param_pb6f_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x00000020U);
        WR1_PROG(REG_A4H, 0x0000cda6U);
        WR1_PROG(REG_04H, 0x0000c100U);

        iLoop = 0U;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);
            for (iLoop = 4; iLoop < S_RAM[0]; )
            {
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Text[iLoop]);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);
                iLoop = iLoop + 4U;
            }

            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);
        }

        HW_SCE_p_func206();

        static const uint32_t Param_pb6f_func100_004[] =
        {
            0xbbc12c23U, 0x0cfb3332U, 0x1ac38658U, 0x5528d3dcU,
        };
        HW_SCE_p_func100(Param_pb6f_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pb6f_func102_002[] =
            {
                0xb0f2e41aU, 0x8539baf3U, 0x13fe00e9U, 0x40a8cdbeU,
            };
            HW_SCE_p_func102(Param_pb6f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub014(0x38008c00U, 0x0000007fU, 0x00A60000U);

            static const uint32_t Param_pb6f_func100_005[] =
            {
                0x8b26e6abU, 0x4d0c31c0U, 0xf8a616f6U, 0x2c8001f6U,
            };
            HW_SCE_p_func100(Param_pb6f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pb6f_func100_006[] =
                {
                    0x6b7ed0d5U, 0xf35452ddU, 0xa81e9a1aU, 0xd5e7e882U,
                };
                HW_SCE_p_func100(Param_pb6f_func100_006);

                HW_SCE_p_func_sub021(0x00000c84U);
                HW_SCE_p_func_sub010(0x80040140U, 0x00008113U);

                WR1_PROG(REG_104H, 0x00000051U);
                WR1_PROG(REG_B0H, 0x00000020U);
                WR1_PROG(REG_A4H, 0x0000cd24U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, change_endian_long(0x00000000U));

                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x00000020U);
                WR1_PROG(REG_A4H, 0x0000cda5U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Text[iLoop]);

                WR1_PROG(REG_ECH, 0x000008c6U);
                HW_SCE_p_func_sub010(0x80840006U, 0x00008113U);

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000010U);
                WR1_PROG(REG_104H, 0x00000368U);
                WR1_PROG(REG_E0H, 0x80840007U);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Text[iLoop + 4]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Text[iLoop + 5]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Text[iLoop + 6]);
                WAIT_STS(REG_104H, 31, 1);
                WR1_PROG(REG_100H, InData_Text[iLoop + 7]);

                HW_SCE_p_func_sub022(0x0000b4a0U, 0x00000004U, 0x00003500U, 0x00036908U);
                HW_SCE_p_func_sub022(0x00008d00U, 0x0000000cU, 0x000024c8U, 0x000024e8U);

                HW_SCE_p_func_sub022(0x00003826U, 0x00003847U, 0x00003460U, 0x00008c60U);
                HW_SCE_p_func_sub022(0x0000001fU, 0x0000b480U, 0xffffffffU, 0x00004403U);
                HW_SCE_p_func_sub022(0x00007484U, 0x00000c24U, 0x00001484U, 0x00000c44U);

                HW_SCE_p_func_sub022(0x00001041U, 0x00003c47U, 0x000037e0U, 0x00008fe0U);
                HW_SCE_p_func_sub022(0x0000007fU, 0x38008fe0U, 0x0000001fU, 0x1000a7e0U);
                HW_SCE_p_func_sub022(0x00000020U, 0x0000b7c0U, 0x00000080U, 0x00002bdfU);
                WR1_PROG(REG_ECH, 0x00056bdeU);
                WR1_PROG(REG_ECH, 0x0000353eU);

                WR1_PROG(REG_E0H, 0x810103c0U);
                WR1_PROG(REG_04H, 0x00000607U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &S_RAM[0]);
                S_RAM[0] = change_endian_long(S_RAM[0]);

                for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
                {
                    HW_SCE_p_func_sub022(0x000024c5U, 0x000024e5U, 0x00003ba6U, 0x00003fa7U);

                    WR1_PROG(REG_ECH, 0x000033c0U);
                    static const uint32_t Param_pb6f_func101_001[] =
                    {
                        0xcddc449bU, 0x4e86b813U, 0x9f7d8b1fU, 0xa333ba6fU,
                    };
                    HW_SCE_p_func101(Param_pb6f_func101_001);
                }

                static const uint32_t Param_pb6f_func100_007[] =
                {
                    0x630cb437U, 0xe87d589dU, 0x42e79c01U, 0xc3d8d05eU,
                };
                HW_SCE_p_func100(Param_pb6f_func100_007);

                WR1_PROG(REG_ECH, 0x38000fdeU);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                WR1_PROG(REG_1CH, 0x00402000U);

                WR1_PROG(REG_A4H, 0x00040805U);
                HW_SCE_p_func_sub010(0x81040140U, 0x00001813U);

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000010U);
                WR1_PROG(REG_B0H, 0x00000020U);
                WR1_PROG(REG_A4H, 0x0000cda5U);
                HW_SCE_p_func_sub010(0x81840007U, 0x00001813U);

                WR1_PROG(REG_04H, 0x00000113U);
                WAIT_STS(REG_04H, 30, 1);
                RD4_ADDR(REG_100H, &OutData_Text[iLoop]);

                HW_SCE_p_func_sub022(0x000008c6U, 0x000024c8U, 0x00003826U, 0x00000c24U);

                WR1_PROG(REG_ECH, 0x00003c26U);

                WR1_PROG(REG_ECH, 0x00000bffU);

                for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
                {
                    WR1_PROG(REG_ECH, 0x000024c5U);

                    WR1_PROG(REG_ECH, 0x00003fe6U);

                    WR1_PROG(REG_ECH, 0x00003120U);
                    static const uint32_t Param_pb6f_func101_002[] =
                    {
                        0x3ffc373fU, 0x6967e754U, 0xec3ec0dbU, 0x2f0c1b7eU,
                    };
                    HW_SCE_p_func101(Param_pb6f_func101_002);
                }

                static const uint32_t Param_pb6f_func100_008[] =
                {
                    0x9f55dc28U, 0xe577c2f2U, 0x87e6055aU, 0xa66aecd0U,
                };
                HW_SCE_p_func100(Param_pb6f_func100_008);

                WR1_PROG(REG_ECH, 0x38000d29U);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                WR1_PROG(REG_1CH, 0x00402000U);

                WR1_PROG(REG_ECH, 0x000008c6U);
                WR1_PROG(REG_E0H, 0x81840006U);
                WR1_PROG(REG_04H, 0x00000613U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[iLoop + 4]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[iLoop + 5]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[iLoop + 6]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[iLoop + 7]);

                static const uint32_t Param_pb6f_func101_003[] =
                {
                    0x5c4e6f65U, 0x36ef7d88U, 0x846364a9U, 0xfe581a43U,
                };
                HW_SCE_p_func101(Param_pb6f_func101_003);
            }

            static const uint32_t Param_pb6f_func102_003[] =
            {
                0x642757a2U, 0x712ec770U, 0x3bde479bU, 0x19e636faU,
            };
            HW_SCE_p_func102(Param_pb6f_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
