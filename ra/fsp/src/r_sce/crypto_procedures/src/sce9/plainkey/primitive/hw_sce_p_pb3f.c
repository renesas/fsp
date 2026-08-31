/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub (uint32_t InData_TextBitLen[], uint32_t InData_Text[],
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

    static const uint32_t Param_pb3f_func100_001[] =
    {
        0xad40f525U, 0x552fe1a0U, 0x010897f9U, 0xe0e389ddU,
    };
    HW_SCE_p_func100(Param_pb3f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pb3f_func102_001[] =
        {
            0x0009f09aU, 0x9d3e2b34U, 0x6ae01d0cU, 0x4bf49bf1U,
        };
        HW_SCE_p_func102(Param_pb3f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        static const uint32_t Param_pb3f_func100_002[] =
        {
            0xfe5dca73U, 0x08cc0978U, 0x98b6f585U, 0xa843022aU,
        };
        HW_SCE_p_func100(Param_pb3f_func100_002);
        WR1_PROG(REG_E0H, 0x810103c0U);
        WR1_PROG(REG_04H, 0x00000607U);
        WAIT_STS(REG_04H, 30, 1);
        RD1_ADDR(REG_100H, &S_RAM[0]);
        S_RAM[0] = change_endian_long(S_RAM[0]);

        static const uint32_t Param_pb3f_func100_003[] =
        {
            0xe0102f0cU, 0xf120e54cU, 0x11b41821U, 0xbd53d74dU,
        };
        HW_SCE_p_func100(Param_pb3f_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x00000020U);
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

        static const uint32_t Param_pb3f_func100_004[] =
        {
            0xe172eb4aU, 0x2d4b73feU, 0x7554ebaaU, 0xf0d03c8bU,
        };
        HW_SCE_p_func100(Param_pb3f_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pb3f_func102_002[] =
            {
                0xdbe6b8d7U, 0x70b75292U, 0x08bff4a7U, 0x0321e806U,
            };
            HW_SCE_p_func102(Param_pb3f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func_sub014(0x38008c00U, 0x0000007fU, 0x00A60000U);

            static const uint32_t Param_pb3f_func100_005[] =
            {
                0xf7feb80bU, 0xf012f7edU, 0x61b6bcbcU, 0x544a1c4aU,
            };
            HW_SCE_p_func100(Param_pb3f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x00000020U);
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

                static const uint32_t Param_pb3f_func100_006[] =
                {
                    0x43b55f31U, 0x800162aaU, 0xe080c202U, 0xf8240dc2U,
                };
                HW_SCE_p_func100(Param_pb3f_func100_006);
                WR1_PROG(REG_E0H, 0x810103c0U);
                WR1_PROG(REG_04H, 0x00000607U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &S_RAM[0]);
                S_RAM[0] = change_endian_long(S_RAM[0]);

                for (jLoop = 0U; jLoop < S_RAM[0]; jLoop++)
                {
                    HW_SCE_p_func_sub022(0x000024c5U, 0x000024e5U, 0x00003ba6U, 0x00003fa7U);

                    WR1_PROG(REG_ECH, 0x000033c0U);
                    static const uint32_t Param_pb3f_func101_001[] =
                    {
                        0xb7a81182U, 0xf79854d8U, 0xe46b3c43U, 0x4ed0ac4fU,
                    };
                    HW_SCE_p_func101(Param_pb3f_func101_001);
                }

                WR1_PROG(REG_ECH, 0x38000fdeU);
                WR1_PROG(REG_E0H, 0x00000080U);
                WR1_PROG(REG_1CH, 0x00260000U);

                WR1_PROG(REG_1CH, 0x00402000U);

                static const uint32_t Param_pb3f_func100_007[] =
                {
                    0x94909a24U, 0xce4d9e60U, 0x76135666U, 0xb5af3e2bU,
                };
                HW_SCE_p_func100(Param_pb3f_func100_007);
                WR1_PROG(REG_ECH, 0x0000b4e0U);
                WR1_PROG(REG_ECH, 0x00000010U);
                WR1_PROG(REG_B0H, 0x00000020U);
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
                    static const uint32_t Param_pb3f_func101_002[] =
                    {
                        0xd0f5eec8U, 0xacc05fcdU, 0x76ac3301U, 0x03700592U,
                    };
                    HW_SCE_p_func101(Param_pb3f_func101_002);
                }

                static const uint32_t Param_pb3f_func100_008[] =
                {
                    0x1a1a0d1cU, 0xf347e5e8U, 0x5e9966d6U, 0xbc3fca09U,
                };
                HW_SCE_p_func100(Param_pb3f_func100_008);
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

                static const uint32_t Param_pb3f_func101_003[] =
                {
                    0x26c1c523U, 0x69d64c70U, 0x201c76dcU, 0x42b3d6bdU,
                };
                HW_SCE_p_func101(Param_pb3f_func101_003);
            }

            static const uint32_t Param_pb3f_func102_003[] =
            {
                0xc6c80c94U, 0x4115ede4U, 0x3cd02c22U, 0x212a144aU,
            };
            HW_SCE_p_func102(Param_pb3f_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
