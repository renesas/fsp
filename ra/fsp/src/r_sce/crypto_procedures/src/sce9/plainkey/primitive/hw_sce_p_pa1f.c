/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           uint32_t       OutData_Text[],
                                           uint32_t       OutData_MAC[])
{
    uint32_t iLoop = 0U;

    static const uint32_t Param_pa1f_func100_001[] =
    {
        0x547a3ccfU, 0xf5355e5dU, 0x3e91bfacU, 0xc4257c3fU,
    };
    HW_SCE_p_func100(Param_pa1f_func100_001);
    WR1_PROG(REG_1CH, 0x00400000U);
    WR1_PROG(REG_1D0H, 0x00000000U);

    if (CHCK_STS(REG_1CH, 22, 1))
    {
        static const uint32_t Param_pa1f_func102_001[] =
        {
            0xefc12503U, 0xc06f4847U, 0x69b50c3bU, 0x3b230642U,
        };
        HW_SCE_p_func102(Param_pa1f_func102_001);
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

        static const uint32_t Param_pa1f_func100_002[] =
        {
            0x0f7b7772U, 0xd8485cb0U, 0x3f64a0e8U, 0x464e9d9eU,
        };
        HW_SCE_p_func100(Param_pa1f_func100_002);
        WR1_PROG(REG_1CH, 0x00400000U);
        WR1_PROG(REG_1D0H, 0x00000000U);

        if (CHCK_STS(REG_1CH, 22, 1))
        {
            WR1_PROG(REG_104H, 0x00000361U);
            WR1_PROG(REG_B0H, 0x40000000U);
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

            static const uint32_t Param_pa1f_func100_003[] =
            {
                0x8af9e419U, 0x65bedac8U, 0xe10579a8U, 0x533cb403U,
            };
            HW_SCE_p_func100(Param_pa1f_func100_003);
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

            static const uint32_t Param_pa1f_func101_001[] =
            {
                0x9db528ceU, 0x43161566U, 0x4014aaf4U, 0x3f878197U,
            };
            HW_SCE_p_func101(Param_pa1f_func101_001);
        }
        else
        {
            static const uint32_t Param_pa1f_func101_002[] =
            {
                0x024348c1U, 0x767c9441U, 0x1c8f4731U, 0xbf875d7aU,
            };
            HW_SCE_p_func101(Param_pa1f_func101_002);
        }

        HW_SCE_p_func_sub021(0x01000c84U);

        static const uint32_t Param_pa1f_func100_004[] =
        {
            0x08309318U, 0x2cb56d5aU, 0x89548d5cU, 0xd0097ef1U,
        };
        HW_SCE_p_func100(Param_pa1f_func100_004);
        WR1_PROG(REG_B0H, 0x40000000U);
        HW_SCE_p_func_sub019(0x000089c5U, 0x00001113U);

        WR1_PROG(REG_04H, 0x00000113U);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_MAC[0]);

        static const uint32_t Param_pa1f_func102_002[] =
        {
            0xa6743017U, 0x3577430dU, 0x87776077U, 0x45ded6e7U,
        };
        HW_SCE_p_func102(Param_pa1f_func102_002);
        WR1_PROG(REG_1BCH, 0x00000040U);
        WAIT_STS(REG_18H, 12, 0);

        return FSP_SUCCESS;
    }
}
