/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub (const uint32_t InData_Text[],
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

    static const uint32_t Param_p34f_func100_001[] =
    {
        0xa2ab3ccbU, 0x3ea9b7f2U, 0x3b45fa5bU, 0xfac762d6U,
    };
    HW_SCE_p_func100(Param_p34f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p34f_func102_001[] =
        {
            0x777e8592U, 0x90e4b57aU, 0x7f2ed30fU, 0x2e356c35U,
        };
        HW_SCE_p_func102(Param_p34f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);
        HW_SCE_p_func_sub007(0x00036800U, 0x08008c00U, 0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p34f_func100_002[] =
        {
            0xe4e6cd10U, 0x3d0d8d18U, 0x895d69adU, 0xafeb01eaU,
        };
        HW_SCE_p_func100(Param_p34f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x40000020U);
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

            static const uint32_t Param_p34f_func100_003[] =
            {
                0x3352beb1U, 0x697d6205U, 0x55fced5eU, 0x0fa0b58fU,
            };
            HW_SCE_p_func100(Param_p34f_func100_003);
            WR1_PROG(REG_A4H, 0x00000885U);
            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00004813U);
            WR1_PROG(REG_04H, 0x00000113U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[0]);

            static const uint32_t Param_p34f_func101_001[] =
            {
                0xa76d4578U, 0x5bffb46eU, 0xd9142159U, 0x21b1a27eU,
            };
            HW_SCE_p_func101(Param_p34f_func101_001);
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

        static const uint32_t Param_p34f_func100_004[] =
        {
            0x49d5260eU, 0x6eabc9cdU, 0x9f44122dU, 0x2f7a78a6U,
        };
        HW_SCE_p_func100(Param_p34f_func100_004);
        WR1_PROG(REG_B0H, 0x40000020U);
        WR1_PROG(REG_A4H, 0x000087b5U);
        WR1_PROG(REG_00H, 0x00001513U);
        WR1_PROG(REG_74H, 0x00000008U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_DataT[0]);

        static const uint32_t Param_p34f_func102_002[] =
        {
            0x213da8b3U, 0x9303aa36U, 0x5b9260beU, 0x4508a912U,
        };
        HW_SCE_p_func102(Param_p34f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
