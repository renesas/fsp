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
        HW_SCE_p_func100(0xe328c699U, 0x2070b45dU, 0x8161cc79U, 0xf4afa3c4U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0a000106U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x90259b20U, 0xa8c5acaeU, 0x7eee33fdU, 0xc6c727d1U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0a00010eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x5657f6eeU, 0x39dd13afU, 0x878296eeU, 0x7a03a2f7U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0e000506U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x20411ef4U, 0x1d42cab4U, 0xf097d414U, 0xc9f5d68fU);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D0H, 0x0900090eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0xdde79ba4U, 0xa80c7752U, 0xb8f3c5beU, 0x0bda82a4U);

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

        HW_SCE_p_func101(0x49f6dcb5U, 0x325fca2fU, 0x623f62a9U, 0xa5f0b6acU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xecbe6b1eU, 0x87d413dbU, 0xf3016614U, 0xd2d38e2fU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xae7cd1f2U, 0x4a9b9d1cU, 0xc2a7bcfcU, 0x80eaf6f7U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x352fb80cU, 0xef79e6f2U, 0xd4032798U, 0x60b5c291U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xd4b626beU, 0x3cb7ed93U, 0x794aa619U, 0xb378a9c8U);
    }
}
