/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p50u_func100_001[] =
        {
            0x12fec111U, 0x837686bcU, 0x29da676fU, 0x2a15b6c6U,
        };
        HW_SCE_p_func100(Param_p50u_func100_001);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x00008a86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p50u_func100_002[] =
        {
            0x57bd8fe5U, 0x5a462c45U, 0x9678f8abU, 0x95526c3fU,
        };
        HW_SCE_p_func100(Param_p50u_func100_002);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x0000ca86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p50u_func100_003[] =
        {
            0x587a8d69U, 0xa2d8f37eU, 0xc55267b3U, 0x7b67886cU,
        };
        HW_SCE_p_func100(Param_p50u_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x00008e96U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p50u_func100_004[] =
        {
            0xb2c8f072U, 0x646e4af5U, 0xa7435e98U, 0x59950484U,
        };
        HW_SCE_p_func100(Param_p50u_func100_004);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x0000c9a6U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p50u_func100_005[] =
        {
            0x6e63e543U, 0x0b1c2b84U, 0x13059a4fU, 0xe340fb26U,
        };
        HW_SCE_p_func100(Param_p50u_func100_005);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_B0H, 0x40000000U);
        WR1_PROG(REG_A4H, 0x000087b6U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }

    WAIT_STS(REG_104H, 31, 1);
    WR4_ADDR(REG_100H, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_104H, 31, 1);
        WR4_ADDR(REG_100H, &InData_Text[iLoop]);
        WAIT_STS(REG_04H, 30, 1);
        RD4_ADDR(REG_100H, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_04H, 30, 1);
    RD4_ADDR(REG_100H, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p50u_func101_001[] =
        {
            0xb89f76b5U, 0xee125499U, 0x98999e50U, 0x3ea99faaU,
        };
        HW_SCE_p_func101(Param_p50u_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p50u_func101_002[] =
        {
            0xf861eaa0U, 0xb24c5d5dU, 0x3e2a924cU, 0x5c7ad83bU,
        };
        HW_SCE_p_func101(Param_p50u_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p50u_func101_003[] =
        {
            0x279da2a4U, 0x7268bac3U, 0xe5d5d986U, 0xb26c9b0fU,
        };
        HW_SCE_p_func101(Param_p50u_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p50u_func101_004[] =
        {
            0xf1bdb534U, 0x2313da8dU, 0x7fd36cd2U, 0x78f418caU,
        };
        HW_SCE_p_func101(Param_p50u_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p50u_func101_005[] =
        {
            0x2db3fdb1U, 0xe0c0ef7fU, 0x665c0a8dU, 0xd752d49eU,
        };
        HW_SCE_p_func101(Param_p50u_func101_005);
    }
}
