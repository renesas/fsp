/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_MAC[],
                                           const uint32_t InData_MACLength[],
                                           uint32_t       OutData_Text[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pa4f_func100_001[] =
    {
        0x1947bce2U, 0xb6dd8cefU, 0x72f49a52U, 0xaf05502eU,
    };
    HW_SCE_p_func100(Param_pa4f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa4f_func102_001[] =
        {
            0x7c1b7ea3U, 0xf18dfaa8U, 0xe8780c1fU, 0x9959f912U,
        };
        HW_SCE_p_func102(Param_pa4f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_104H, 0x00000068U);
        WR1_PROG(REG_E0H, 0x80010140U);
        WAIT_STS(REG_104H, 31, 1);
        WR1_PROG(REG_100H, InData_MACLength[0]);

        HW_SCE_p_func_sub014(0x38008940U, 0x00000000U, 0x00260000U);

        HW_SCE_p_func_sub007(0x0000b7e0U, 0x00000010U, 0x34202beaU, 0x00260000U);

        static const uint32_t Param_pa4f_func100_002[] =
        {
            0xb2cb41d9U, 0x8f1c5bc0U, 0x95ce1a2aU, 0x5b1f71d8U,
        };
        HW_SCE_p_func100(Param_pa4f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_pa4f_func102_002[] =
            {
                0x6ea3e4f6U, 0xd9b8445fU, 0xa3c85ad4U, 0x274f912aU,
            };
            HW_SCE_p_func102(Param_pa4f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_104H, 0x00000068U);
            WR1_PROG(REG_E0H, 0x80010000U);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, InData_TextLen[0]);

            WR1_PROG(REG_ECH, 0x00008c00U);
            HW_SCE_p_func_sub007(0x0000000fU, 0x38008800U, 0x00000000U, 0x00A60000U);

            static const uint32_t Param_pa4f_func100_003[] =
            {
                0x4d69888dU, 0x907ce4c9U, 0xec2167c2U, 0xb4887c76U,
            };
            HW_SCE_p_func100(Param_pa4f_func100_003);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                WR1_PROG(REG_104H, 0x00000361U);
                WR1_PROG(REG_B0H, 0x40000000U);
                WR1_PROG(REG_A4H, 0x000087b5U);
                WAIT_STS(REG_104H, 31, 1);
                WR4_ADDR(REG_100H, &InData_Text[0]);

                WR1_PROG(REG_ECH, 0x0000b420U);
                WR1_PROG(REG_ECH, 0x00000080U);
                HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

                HW_SCE_p_func_sub022(0x00000821U, 0x0000a400U, 0x00000080U, 0x0000b7e0U);
                WR1_PROG(REG_ECH, 0x00000080U);

                for (iLoop = 0U; iLoop < 16U; iLoop++)
                {
                    WR1_PROG(REG_ECH, 0x3c002be0U);
                    WR1_PROG(REG_ECH, 0x12003c3fU);
                    WR1_PROG(REG_ECH, 0x00002fe0U);
                }

                static const uint32_t Param_pa4f_func100_004[] =
                {
                    0xe0008a61U, 0xaf3a2505U, 0x1b72c8feU, 0x4cda0270U,
                };
                HW_SCE_p_func100(Param_pa4f_func100_004);
                WR1_PROG(REG_ECH, 0x0000b420U);
                WR1_PROG(REG_ECH, 0x00000080U);
                WR1_PROG(REG_E0H, 0x81840001U);
                WR1_PROG(REG_04H, 0x00000613U);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[0]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[1]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[2]);
                WAIT_STS(REG_04H, 30, 1);
                RD1_ADDR(REG_100H, &OutData_Text[3]);

                WR1_PROG(REG_B0H, 0x40000000U);
                WR1_PROG(REG_A4H, 0x00008e55U);
                HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);

                static const uint32_t Param_pa4f_func101_001[] =
                {
                    0xce3ca2efU, 0x00dca552U, 0xf00addadU, 0x663336a2U,
                };
                HW_SCE_p_func101(Param_pa4f_func101_001);
            }
            else
            {
                static const uint32_t Param_pa4f_func101_002[] =
                {
                    0x22d19c6dU, 0xd99bd025U, 0x0c4adab8U, 0x6d1b9a12U,
                };
                HW_SCE_p_func101(Param_pa4f_func101_002);
            }

            HW_SCE_p_func_sub021(0x00000cc4U);

            WR1_PROG(REG_B0H, 0x40000000U);
            HW_SCE_p_func_sub019(0x010087b5U, 0x00001113U);

            WR1_PROG(REG_ECH, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000080U);
            HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

            HW_SCE_p_func_sub022(0x0000a540U, 0x00000080U, 0x0000b7e0U, 0x00000080U);

            WR1_PROG(REG_ECH, 0x00000821U);

            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x3c002beaU);
                WR1_PROG(REG_ECH, 0x12003c3fU);
                WR1_PROG(REG_ECH, 0x00002fe0U);
            }

            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00050805U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_MAC[0]);

            WR1_PROG(REG_A4H, 0x00900c45U);
            WR1_PROG(REG_ECH, 0x0000b420U);
            WR1_PROG(REG_ECH, 0x00000080U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00001813U);
            WR1_PROG(REG_A4H, 0x00000000U);

            static const uint32_t Param_pa4f_func100_005[] =
            {
                0x235204faU, 0xad071674U, 0xb3f8bbf8U, 0x2d30b4c2U,
            };
            HW_SCE_p_func100(Param_pa4f_func100_005);
            WR1_PROG(REG_1CH, 0x00400000U);
            WR1_PROG(REG_1D0H, 0x00000000U);

            if (CHCK_STS(REG_1CH, 22, 1))
            {
                static const uint32_t Param_pa4f_func102_003[] =
                {
                    0xbffe685dU, 0xcbcc5e7dU, 0x522ea743U, 0x0d3d1bc3U,
                };
                HW_SCE_p_func102(Param_pa4f_func102_003);

                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                static const uint32_t Param_pa4f_func102_004[] =
                {
                    0x3baf747fU, 0x701ef143U, 0xc69f0243U, 0x7171a199U,
                };
                HW_SCE_p_func102(Param_pa4f_func102_004);
                WR1_PROG(REG_1BCH, 0x00000040U);
                WAIT_STS(REG_18H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
