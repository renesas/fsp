/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x2b8d926bU, 0xb97befc9U, 0x0c164e23U, 0x948695d3U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0a008106U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0xc74767b6U, 0x927ef370U, 0xf916e49bU, 0xb34dd02aU);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0a00810eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x5359f3d9U, 0x43d8658bU, 0x2e795726U, 0xbcbab3e3U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008506U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x6facccb3U, 0xe808945eU, 0x24b24ec1U, 0xcea20548U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0900890eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x5a326a37U, 0x5668c8b2U, 0xe14c176fU, 0x431b9572U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d06U);
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

        HW_SCE_p_func101(0xa0b81baeU, 0xa69758d8U, 0x8084044bU, 0x922bb77fU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xfe3713dcU, 0xe111cabeU, 0xd1e191efU, 0x59cea2f3U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x82f9ba2bU, 0x346df8deU, 0xcb6ab4c2U, 0x89749176U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x35c703a7U, 0x20b50bd8U, 0x27dda4dcU, 0x9ee95bf5U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x6b18beb4U, 0x82063165U, 0xeb447772U, 0xd77efb61U);
    }
}
