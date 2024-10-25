/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x9acee02dU, 0x08503b73U, 0xfd139ed3U, 0x05024045U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a008106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x75b1a20bU, 0x7ce002b1U, 0xffdfd808U, 0xe65cbfeeU);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a00810eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x658ab3dcU, 0xea94142dU, 0xb8f3ef14U, 0x8b5e5761U);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x7ac16ba5U, 0xd29598bbU, 0xfe05567aU, 0xe6400bebU);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0900890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x3e59c297U, 0x6df0b3b1U, 0x0cf8e94bU, 0x27c94c2dU);

        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x07008d06U);
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

        HW_SCE_p_func101(0x407566e7U, 0x19a25946U, 0x15d37e05U, 0x081506b8U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xab1c0648U, 0x79eba40dU, 0xca654264U, 0xf9234295U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xbed343b1U, 0xde27515dU, 0x3afd2421U, 0x29769355U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xbbcf2a77U, 0x57e19d51U, 0x097510b4U, 0xe0f31b32U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x705c47ecU, 0xc3ba119bU, 0x4bf2ffafU, 0x20ff89a9U);
    }
    else
    {
        ;
    }
}
