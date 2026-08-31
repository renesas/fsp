/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pa7f_func100_001[] =
    {
        0x0955f5c4U, 0x6f589e4aU, 0x094a9029U, 0x51c3c8deU,
    };
    HW_SCE_p_func100(Param_pa7f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa7f_func102_001[] =
        {
            0x447006aaU, 0x2106c9d2U, 0x2b2f4193U, 0xb7fe3f1dU,
        };
        HW_SCE_p_func102(Param_pa7f_func102_001);
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

        static const uint32_t Param_pa7f_func100_002[] =
        {
            0x533194d8U, 0xc6c53b53U, 0xce9b76a1U, 0xc7285458U,
        };
        HW_SCE_p_func100(Param_pa7f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x40000010U);
            WR1_PROG(REG_A4H, 0x00e087b5U);
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

            static const uint32_t Param_pa7f_func100_003[] =
            {
                0x265ce6e0U, 0x8fbee97eU, 0x2194fe55U, 0xe97fec01U,
            };
            HW_SCE_p_func100(Param_pa7f_func100_003);
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

            static const uint32_t Param_pa7f_func101_001[] =
            {
                0x9696e04dU, 0x2bafad47U, 0xb0deacf3U, 0x3f0c7e1bU,
            };
            HW_SCE_p_func101(Param_pa7f_func101_001);
        }
        else
        {
            static const uint32_t Param_pa7f_func101_002[] =
            {
                0x0e71a7c9U, 0x7b823e4aU, 0x8f0b3487U, 0x68378caaU,
            };
            HW_SCE_p_func101(Param_pa7f_func101_002);
        }

        HW_SCE_p_func_sub021(0x01000c84U);

        static const uint32_t Param_pa7f_func100_004[] =
        {
            0xe876698cU, 0xca041bb6U, 0x98be0d1dU, 0x3ecc49c9U,
        };
        HW_SCE_p_func100(Param_pa7f_func100_004);
        WR1_PROG(REG_B0H, 0x40000010U);
        HW_SCE_p_func_sub019(0x000089c5U, 0x00001113U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_MAC[0]);

        static const uint32_t Param_pa7f_func102_002[] =
        {
            0x50393f64U, 0x8200d2a3U, 0x7d51364aU, 0x5d7bbba9U,
        };
        HW_SCE_p_func102(Param_pa7f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
