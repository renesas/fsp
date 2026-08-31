/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1CH, 0xff000000U) == 0x00000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p47u_func100_001[] =
        {
            0x9c2bad13U, 0x79b50416U, 0x08b4a371U, 0xa6936ecaU,
        };
        HW_SCE_p_func100(Param_p47u_func100_001);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00000a86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p47u_func100_002[] =
        {
            0x1f26deedU, 0x56986197U, 0x4d36f8e9U, 0xd2396fe3U,
        };
        HW_SCE_p_func100(Param_p47u_func100_002);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00004a86U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p47u_func100_003[] =
        {
            0x46890128U, 0xa4bea142U, 0x46108c23U, 0x5eb9e253U,
        };
        HW_SCE_p_func100(Param_p47u_func100_003);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x00000e96U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p47u_func100_004[] =
        {
            0xf1e2c1c3U, 0xabc1c083U, 0xb30732a7U, 0x8c59ae8dU,
        };
        HW_SCE_p_func100(Param_p47u_func100_004);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x000049a6U);
        WR1_PROG(REG_04H, 0x0000c100U);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        WR1_PROG(REG_104H, 0x00000362U);
        static const uint32_t Param_p47u_func100_005[] =
        {
            0xb0e543a4U, 0xa63ab851U, 0xb0bb040bU, 0x54ffef58U,
        };
        HW_SCE_p_func100(Param_p47u_func100_005);

        WR1_PROG(REG_104H, 0x000000b1U);
        WR1_PROG(REG_A4H, 0x000007b6U);
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

        static const uint32_t Param_p47u_func101_001[] =
        {
            0x3e045906U, 0x3dab084bU, 0x7f066ce2U, 0xc6491214U,
        };
        HW_SCE_p_func101(Param_p47u_func101_001);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x01000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p47u_func101_002[] =
        {
            0xfb0d3b5cU, 0x665b5756U, 0xf6d445c4U, 0xf1f34104U,
        };
        HW_SCE_p_func101(Param_p47u_func101_002);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x02000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p47u_func101_003[] =
        {
            0xbee7945aU, 0x9846b5c0U, 0x2a31d3d7U, 0xa5080511U,
        };
        HW_SCE_p_func101(Param_p47u_func101_003);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x03000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p47u_func101_004[] =
        {
            0xe585a470U, 0xf5c70a3aU, 0x81d43f35U, 0xe506b30fU,
        };
        HW_SCE_p_func101(Param_p47u_func101_004);
    }
    else if (RD1_MASK(REG_1CH, 0xff000000U) == 0x04000000U)
    {
        HW_SCE_p_func206();

        static const uint32_t Param_p47u_func101_005[] =
        {
            0x115cf208U, 0xb5af7fdeU, 0x2d878176U, 0xb6d311d0U,
        };
        HW_SCE_p_func101(Param_p47u_func101_005);
    }
}
