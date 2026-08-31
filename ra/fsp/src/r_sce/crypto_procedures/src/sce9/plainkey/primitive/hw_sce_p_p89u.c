/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p89u_func100_001[] =
        {
            0xf2720436U, 0x566f8ebfU, 0x8600badfU, 0x8b943ad3U,
        };
        HW_SCE_p_func100(Param_p89u_func100_001);

        WR1_PROG(REG_104H, 0x000000b1U);

        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x00008a86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p89u_func100_002[] =
        {
            0x1726c41eU, 0xdc246ce5U, 0x66981e2bU, 0x3d2adcdcU,
        };
        HW_SCE_p_func100(Param_p89u_func100_002);

        WR1_PROG(REG_104H, 0x000000b1U);

        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x0000ca86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p89u_func100_003[] =
        {
            0xc605e562U, 0xaea80e58U, 0xf22f88faU, 0x30d5a7c1U,
        };
        HW_SCE_p_func100(Param_p89u_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);

        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x00008e96U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p89u_func100_004[] =
        {
            0x8af836f5U, 0x6e503bd4U, 0xb28a1123U, 0x81021aafU,
        };
        HW_SCE_p_func100(Param_p89u_func100_004);

        WR1_PROG(REG_104H, 0x000000b1U);

        WR1_PROG(REG_B0H, 0x40000010U);
        WR1_PROG(REG_A4H, 0x0000c9a6U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p89u_func100_005[] =
        {
            0x4b9602acU, 0xc9a8ee92U, 0x9dc351f8U, 0x5e9a52d7U,
        };
        HW_SCE_p_func100(Param_p89u_func100_005);

        WR1_PROG(REG_104H, 0x000000b1U);

        WR1_PROG(REG_B0H, 0x40000010U);
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

        static const uint32_t Param_p89u_func101_001[] =
        {
            0x229f460cU, 0xfcdaec64U, 0xd2d073dbU, 0xf5b19467U,
        };
        HW_SCE_p_func101(Param_p89u_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p89u_func101_002[] =
        {
            0x61db0a12U, 0x60c99b33U, 0xea6949b8U, 0x2be8ef9bU,
        };
        HW_SCE_p_func101(Param_p89u_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p89u_func101_003[] =
        {
            0xfa0454c5U, 0x974a12ccU, 0x2a23dddbU, 0xe2ef57bdU,
        };
        HW_SCE_p_func101(Param_p89u_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p89u_func101_004[] =
        {
            0x96e87ddcU, 0x869f5434U, 0xf6eec13fU, 0x408a88e2U,
        };
        HW_SCE_p_func101(Param_p89u_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p89u_func101_005[] =
        {
            0x9332c1e8U, 0xf702f588U, 0xca87649cU, 0xafc9c1feU,
        };
        HW_SCE_p_func101(Param_p89u_func101_005);
    }
}
