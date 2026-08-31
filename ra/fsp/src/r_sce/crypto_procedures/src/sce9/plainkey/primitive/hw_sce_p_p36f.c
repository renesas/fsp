/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           const uint32_t InData_DataT[],
                                           const uint32_t InData_DataTLen[],
                                           uint32_t       OutData_Text[])
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

    WR1_PROG(REG_104H, 0x00000068U);
    WR1_PROG(REG_E0H, 0x80010140U);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, InData_DataTLen[0]);

    HW_SCE_p_func_sub014(0x38008940U, 0x00000000U, 0x00260000U);

    HW_SCE_p_func_sub007(0x0000b7e0U, 0x00000010U, 0x34202beaU, 0x00260000U);

    static const uint32_t Param_p36f_func100_001[] =
    {
        0x18cbbc67U, 0xb6f57f2eU, 0xde3361b3U, 0x6adcdf24U,
    };
    HW_SCE_p_func100(Param_p36f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_p36f_func102_001[] =
        {
            0x4f0d908dU, 0xf301e51bU, 0xcf69e9efU, 0x651a3635U,
        };
        HW_SCE_p_func102(Param_p36f_func102_001);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_ECH, 0x00003409U);
        HW_SCE_p_func_sub007(0x00036800U, 0x08008c00U, 0x0000000fU, 0x00A60000U);

        static const uint32_t Param_p36f_func100_002[] =
        {
            0x5d383a10U, 0x51e5e005U, 0x791700abU, 0x579427d6U,
        };
        HW_SCE_p_func100(Param_p36f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_A4H, 0x00000885U);
            WAIT_STS(REG_104H, 31, 1);
            WR4_ADDR(REG_100H, &InData_Text[0]);

            WR1_PROG(REG_D0H, 0x40000020U);
            HW_SCE_p_func_sub013(0x000087b5U, 0x00007113U);

            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x80840001U, 0x00008213U);

            WR1_PROG(REG_ECH, 0x00000bffU);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_ECH, 0x3c002be0U);
                WR1_PROG(REG_ECH, 0x12003c3fU);
                WR1_PROG(REG_ECH, 0x00002fe0U);
            }

            static const uint32_t Param_p36f_func100_003[] =
            {
                0x6c205451U, 0x3598ed83U, 0x6671b2c1U, 0x5e0c223dU,
            };
            HW_SCE_p_func100(Param_p36f_func100_003);
            WR1_PROG(REG_C4H, 0x00000885U);
            WR1_PROG(REG_ECH, 0x00000821U);
            HW_SCE_p_func_sub010(0x81840001U, 0x00002813U);
            WR1_PROG(REG_04H, 0x00000213U);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_100H, &OutData_Text[0]);

            static const uint32_t Param_p36f_func101_001[] =
            {
                0x21068dd5U, 0xaff8800bU, 0x4dd41e59U, 0x4790d650U,
            };
            HW_SCE_p_func101(Param_p36f_func101_001);
        }

        WR1_PROG(REG_104H, 0x00000164U);
        WAIT_STS(REG_104H, 31, 1);
        WR2_ADDR(REG_100H, &InData_DataALen[0]);

        HW_SCE_p_func_sub010(0x81020100U, 0x0000580bU);

        WAIT_STS(REG_74H, 18, 0);
        WR1_PROG(REG_1CH, 0x00001600U);
        WR1_PROG(REG_74H, 0x00000000U);

        WR1_PROG(REG_C4H, 0x00040805U);
        HW_SCE_p_func_sub010(0x81040080U, 0x00002813U);

        WR1_PROG(REG_D0H, 0x40000020U);
        WR1_PROG(REG_C4H, 0x000087b5U);
        WR1_PROG(REG_00H, 0x00002513U);
        WR1_PROG(REG_74H, 0x00000008U);
        WAIT_STS(REG_00H, 25, 0);
        WR1_PROG(REG_1CH, 0x00001800U);

        WR1_PROG(REG_ECH, 0x00000821U);
        HW_SCE_p_func_sub010(0x80840001U, 0x00008213U);

        WR1_PROG(REG_ECH, 0x00000bffU);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_ECH, 0x3c002beaU);
            WR1_PROG(REG_ECH, 0x12003c3fU);
            WR1_PROG(REG_ECH, 0x00002fe0U);
        }

        WR1_PROG(REG_104H, 0x00000362U);
        WR1_PROG(REG_C4H, 0x00050805U);
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_DataT[0]);

        WR1_PROG(REG_C4H, 0x00900c45U);
        WR1_PROG(REG_ECH, 0x00000821U);
        HW_SCE_p_func_sub010(0x81840001U, 0x00002813U);
        WR1_PROG(REG_C4H, 0x00000000U);

        static const uint32_t Param_p36f_func100_004[] =
        {
            0xa74fff9aU, 0xd3933c3bU, 0x43f4b2ceU, 0x4a7e5283U,
        };
        HW_SCE_p_func100(Param_p36f_func100_004);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            static const uint32_t Param_p36f_func102_002[] =
            {
                0x2e4778e7U, 0x1e5f555bU, 0x893c4abfU, 0x7241f880U,
            };
            HW_SCE_p_func102(Param_p36f_func102_002);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            static const uint32_t Param_p36f_func102_003[] =
            {
                0x7a084c94U, 0x6fda4b16U, 0xef812686U, 0xb0c16c35U,
            };
            HW_SCE_p_func102(Param_p36f_func102_003);
            WR1_PROG(REG_1BCH, 0x00000040U);
            WAIT_STS(REG_18H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
