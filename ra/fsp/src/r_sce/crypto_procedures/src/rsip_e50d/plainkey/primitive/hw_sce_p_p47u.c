/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0xb0459582U, 0x8570d5e7U, 0x694e1965U, 0x8a8ee9a3U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a000106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x959b2113U, 0xa138783dU, 0xaf5a9beeU, 0x69cd5459U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a00010eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x4a566684U, 0x41af7e85U, 0xd4967198U, 0x55baff73U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0e000506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x02b36b33U, 0xcbc50b6bU, 0xa4dcff7fU, 0x60e64a0fU);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0900090eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x246969d4U, 0x27d11a33U, 0x47e89be3U, 0x9dd5a6b3U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x07000d06U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else
    {
        ;
    }

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Text[0]);
    for (iLoop = 4U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x01c06606U, 0x8f00ce3aU, 0x958f7c69U, 0xf2f6d685U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x319a1775U, 0xa2d7f61bU, 0x30ef6c53U, 0xb5cb66dbU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xd9360414U, 0xe932a8d5U, 0x71e383a0U, 0xd39bf838U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x596adfc2U, 0x7fe38e33U, 0x436bb0cbU, 0xb4d8fe76U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x8c7570f3U, 0x40d317ccU, 0x6e82fb51U, 0x91cf9b9fU);
    }
    else
    {
        ;
    }
}
