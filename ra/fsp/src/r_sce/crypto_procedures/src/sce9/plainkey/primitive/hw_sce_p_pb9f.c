/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub (uint32_t InData_TextBitLen[], uint32_t InData_Text[],
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

    static const uint32_t Param_pb9f_func100_001[] =
    {
        0xe915e6d7U, 0x1d65d1c4U, 0x8ff5b85bU, 0xa4526103U,
    };
    HW_SCE_p_func100(Param_pb9f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb9f_func102_001[] =
        {
            0xe3234672U, 0x27bcdd00U, 0xcdf184b4U, 0xc0195e81U,
        };
        HW_SCE_p_func102(Param_pb9f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pb9f_func100_002[] =
        {
            0xd572f89fU, 0x8c16b8adU, 0xc63fc14eU, 0x5b2dafdcU,
        };
        HW_SCE_p_func100(Param_pb9f_func100_002);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        static const uint32_t Param_pb9f_func100_003[] =
        {
            0xe22fe9a3U, 0x19b8ff1dU, 0x41e0e0ccU, 0x7f45f38aU,
        };
        HW_SCE_p_func100(Param_pb9f_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000020U);
        WR1_PROG(REG_A4H, 0x00008da6U);
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

        static const uint32_t Param_pb9f_func100_004[] =
        {
            0xbb591048U, 0x64c28870U, 0x5398d50dU, 0x5e3ab165U,
        };
        HW_SCE_p_func100(Param_pb9f_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pb9f_func102_002[] =
            {
                0x3f5592d3U, 0x4bcce341U, 0x90e9f640U, 0x3be1cb9aU,
            };
            HW_SCE_p_func102(Param_pb9f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub014(0x38008c00U, 0x0000007fU, 0x00A60000U);

            static const uint32_t Param_pb9f_func100_005[] =
            {
                0x1eec6f52U, 0x5e74c52aU, 0x1b2d8528U, 0x000c9a2dU,
            };
            HW_SCE_p_func100(Param_pb9f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x40000020U);
                WR1_PROG(REG_A4H, 0x00008da5U);
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

                static const uint32_t Param_pb9f_func100_006[] =
                {
                    0x4c3b7f8eU, 0x431841b4U, 0xcf3c2a19U, 0x475aee98U,
                };
                HW_SCE_p_func100(Param_pb9f_func100_006);
                WR1_PROG(REG_E0H, 0x810103c0U);
                WR1_PROG(REG_04H, 0x00000607U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &S_RAM[0]);
                S_RAM[0] = change_endian_long(S_RAM[0]);

                for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
                {
                    HW_SCE_p_func_sub022(0x000024c5U, 0x000024e5U, 0x00003ba6U, 0x00003fa7U);

                    WR1_PROG(REG_ECH, 0x000033c0U);
                    static const uint32_t Param_pb9f_func101_001[] =
                    {
                        0x951a9435U, 0xe4953a42U, 0x053c0042U, 0x3e4cfe4aU,
                    };
                    HW_SCE_p_func101(Param_pb9f_func101_001);
                }

                WR1_PROG(REG_ECH, 0x38000fdeU);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                WR1_PROG(REG_1CH, 0x00402000U);

                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000010U);
                static const uint32_t Param_pb9f_func100_007[] =
                {
                    0xc7c98e4dU, 0x464f55caU, 0x7a20898fU, 0xe1485eb3U,
                };
                HW_SCE_p_func100(Param_pb9f_func100_007);
                WR1_PROG(REG_B0H, 0x40000020U);
                WR1_PROG(REG_A4H, 0x00008da5U);
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
                    static const uint32_t Param_pb9f_func101_002[] =
                    {
                        0x88630b84U, 0x09e52004U, 0xa0f8a19fU, 0x3e97a8a7U,
                    };
                    HW_SCE_p_func101(Param_pb9f_func101_002);
                }

                WR1_PROG(REG_ECH, 0x38000d29U);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                WR1_PROG(REG_1CH, 0x00402000U);

                static const uint32_t Param_pb9f_func100_008[] =
                {
                    0xb7ce9444U, 0x95bb5d55U, 0xa6254961U, 0x786d3859U,
                };
                HW_SCE_p_func100(Param_pb9f_func100_008);
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

                static const uint32_t Param_pb9f_func101_003[] =
                {
                    0x31dbc936U, 0xd6f4103cU, 0xb55ba7e0U, 0x9f882e30U,
                };
                HW_SCE_p_func101(Param_pb9f_func101_003);
            }

            static const uint32_t Param_pb9f_func102_003[] =
            {
                0x1af1cb45U, 0xcbab59ffU, 0x4010b50eU, 0x0ad6f321U,
            };
            HW_SCE_p_func102(Param_pb9f_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
