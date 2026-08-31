/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_104H, 0x00000168U);
    WR1_PROG(REG_E0H, 0x80020100U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[0]);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[1]);

    WR1_PROG(REG_ECH, 0x0000b580U);
    WR1_PROG(REG_ECH, 0x0000007FU);
    WR1_PROG(REG_ECH, 0x0000b5a0U);
    HW_SCE_p_func_sub007(0xFFFFFF00U, 0x0c0029a9U, 0x04a02988U, 0x00260000U);

    static const uint32_t Param_p83f_func100_001[] =
    {
        0x1c5fd38aU, 0xbb281f4cU, 0x06f32c33U, 0x3f0d1a13U,
    };
    HW_SCE_p_func100(Param_p83f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p83f_func102_001[] =
        {
            0xf84b38c2U, 0x5d3f0695U, 0x73fdba7fU, 0xecbf89e3U,
        };
        HW_SCE_p_func102(Param_p83f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);
        HW_SCE_p_func_sub007(0x00036800U, 0x08008c00U, 0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p83f_func100_002[] =
        {
            0x7670c563U, 0xd967071eU, 0xb87a350bU, 0x2870cc29U,
        };
        HW_SCE_p_func100(Param_p83f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x40000030U);
            WR1_PROG(REG_A4H, 0x000087b5U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);

            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x80840001U, 0x00008113U);

            WR1_PROG(REG_ECH, 0x00000bffU);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x3c002be0U);
                WR1_PROG(REG_ECH, 0x12003c3fU);
                WR1_PROG(REG_ECH, 0x00002fe0U);
            }

            static const uint32_t Param_p83f_func100_003[] =
            {
                0x59efb123U, 0xbb4edc63U, 0x1d3268caU, 0x56c5122aU,
            };
            HW_SCE_p_func100(Param_p83f_func100_003);
            WR1_PROG(REG_A4H, 0x00000885U);
            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00004813U);
            WR1_PROG(REG_04H, 0x00000113U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[0]);

            static const uint32_t Param_p83f_func101_001[] =
            {
                0xcc3ebaa1U, 0xc7fa9dc1U, 0xf9869924U, 0x8d88b03bU,
            };
            HW_SCE_p_func101(Param_p83f_func101_001);
        }

        WR1_PROG(REG_104H, 0x00000164U);
        WAIT_STS(REG_104H, 31, 1);
        WR2_ADDR(REG_100H, &InData_DataALen[0]);

        HW_SCE_p_func_sub010(0x81020100U, 0x0000580bU);

        WAIT_STS(REG_74H, 18, 0);
        WR1_PROG(REG_1CH, 0x00001600U);
        WR1_PROG(REG_74H, 0x00000000U);

        WR1_PROG(REG_A4H, 0x00040805U);
        HW_SCE_p_func_sub010(0x81040080U, 0x00001813U);

        static const uint32_t Param_p83f_func100_004[] =
        {
            0x3ad1e64fU, 0x298378e7U, 0xef5241a8U, 0x09ccb269U,
        };
        HW_SCE_p_func100(Param_p83f_func100_004);
        WR1_PROG(REG_B0H, 0x40000030U);
        WR1_PROG(REG_A4H, 0x000087b5U);
        WR1_PROG(REG_00H, 0x00001513U);
        WR1_PROG(REG_74H, 0x00000008U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_DataT[0]);

        static const uint32_t Param_p83f_func102_002[] =
        {
            0x5e51140aU, 0x46ecc5d4U, 0x6fd45c30U, 0x99793214U,
        };
        HW_SCE_p_func102(Param_p83f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
