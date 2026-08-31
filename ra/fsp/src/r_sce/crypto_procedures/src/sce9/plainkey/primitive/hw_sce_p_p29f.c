/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_DataT[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_ECH, 0x000035c8U);

    WR1_PROG(REG_104H, 0x00000168U);
    WR1_PROG(REG_E0H, 0x80020100U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[0]);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_TextLen[1]);

    HW_SCE_p_func_sub014(0x3420a9c0U, 0x00000004U, 0x00260000U);

    static const uint32_t Param_p29f_func100_001[] =
    {
        0x2c66c2a4U, 0xc2eb5cfaU, 0x1d714d5dU, 0xbb0b2839U,
    };
    HW_SCE_p_func100(Param_p29f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        WR1_PROG(REG_ECH, 0x0000b580U);
        WR1_PROG(REG_ECH, 0x0000007FU);
        WR1_PROG(REG_ECH, 0x0000b5a0U);
        HW_SCE_p_func_sub007(0xFFFFFF00U, 0x0c0029a9U, 0x04a02988U, 0x00260000U);

        static const uint32_t Param_p29f_func101_001[] =
        {
            0xbbf5c6ccU, 0x75486aeaU, 0x47964e72U, 0x23095891U,
        };
        HW_SCE_p_func101(Param_p29f_func101_001);
    }
    else
    {
        WR1_PROG(REG_ECH, 0x0000b580U);
        WR1_PROG(REG_ECH, 0x00000000U);
        WR1_PROG(REG_ECH, 0x0000b5a0U);
        HW_SCE_p_func_sub007(0x00020800U, 0x0c0029a9U, 0x04a02988U, 0x00260000U);

        static const uint32_t Param_p29f_func101_002[] =
        {
            0xf1eb4b3bU, 0x181c87e8U, 0x7dadf7c5U, 0x2f2766a4U,
        };
        HW_SCE_p_func101(Param_p29f_func101_002);
    }

    static const uint32_t Param_p29f_func100_002[] =
    {
        0xc0fd4e69U, 0x3ba09400U, 0x06086078U, 0x1b079f81U,
    };
    HW_SCE_p_func100(Param_p29f_func100_002);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p29f_func102_001[] =
        {
            0x4f90e3d0U, 0x8b465689U, 0x00083e4cU, 0x5fa523cfU,
        };
        HW_SCE_p_func102(Param_p29f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);
        HW_SCE_p_func_sub007(0x00036800U, 0x08008c00U, 0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p29f_func100_003[] =
        {
            0xfe2b5eb8U, 0x09f40409U, 0x07449ce9U, 0x86116556U,
        };
        HW_SCE_p_func100(Param_p29f_func100_003);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x00000020U);
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

            static const uint32_t Param_p29f_func100_004[] =
            {
                0xe989d8f1U, 0x3c5db4caU, 0x30a5e09aU, 0x2dd6ef26U,
            };
            HW_SCE_p_func100(Param_p29f_func100_004);
            WR1_PROG(REG_A4H, 0x00000885U);
            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00004813U);
            WR1_PROG(REG_04H, 0x00000113U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[0]);

            static const uint32_t Param_p29f_func101_003[] =
            {
                0xaa2db342U, 0xfdbf9a4bU, 0x6feabdf1U, 0xde682364U,
            };
            HW_SCE_p_func101(Param_p29f_func101_003);
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

        static const uint32_t Param_p29f_func100_005[] =
        {
            0x20b2bf1fU, 0x7ec79001U, 0x6ab17f25U, 0x01bf43ccU,
        };
        HW_SCE_p_func100(Param_p29f_func100_005);
        WR1_PROG(REG_B0H, 0x00000020U);
        WR1_PROG(REG_A4H, 0x000087b5U);
        WR1_PROG(REG_00H, 0x00001513U);
        WR1_PROG(REG_74H, 0x00000008U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_DataT[0]);

        static const uint32_t Param_p29f_func102_002[] =
        {
            0x5fbe76abU, 0xba1b0bb7U, 0x6c4d225dU, 0x2ab8c3f6U,
        };
        HW_SCE_p_func102(Param_p29f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
