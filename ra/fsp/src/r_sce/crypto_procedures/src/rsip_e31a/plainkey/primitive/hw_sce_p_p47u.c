/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0xba1b2028U, 0x197c6de3U, 0x0db19d03U, 0xe6703806U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0a000106U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x818fec61U, 0x795549b5U, 0xec6f7e53U, 0x502e354dU);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0a00010eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x4e858a42U, 0x61daf798U, 0xdb47ebe0U, 0x0fa77422U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0e000506U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x0b74a369U, 0x87c803feU, 0xfbaaf113U, 0x018e5ad7U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0900090eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0xa7cefbfbU, 0x89b70590U, 0xd1775163U, 0xbbf65898U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x07000d06U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }

    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        WAIT_STS(REG_08H, 30, 1);
        RD4_ADDR(REG_2CH, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x23198d15U, 0xa803cb34U, 0x20e6e3a8U, 0x09ce3f3dU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x5c66aa89U, 0xe8cf1382U, 0xa6fa34c0U, 0xa3cacf6cU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xd4787828U, 0x8f068227U, 0x40a2347aU, 0xdbde93c1U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xfd6ba740U, 0xab98fad5U, 0x0caa6ffeU, 0x01af9372U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xdda59c91U, 0xbd60ec48U, 0xa03d6c21U, 0xdaefc3faU);
    }
}
