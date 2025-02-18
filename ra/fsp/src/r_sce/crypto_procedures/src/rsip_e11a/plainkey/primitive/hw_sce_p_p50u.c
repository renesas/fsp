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
        HW_SCE_p_func100(0x72c4ba36U, 0xcbe3d0f6U, 0x9b50c9adU, 0x523ffd06U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0a008106U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x1e865a2bU, 0x61f06fd0U, 0x21c29d7eU, 0x5f88a3c7U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0a00810eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x5016a475U, 0xcf53c48fU, 0xa51069beU, 0x3dc35bc8U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0e008506U);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x61354aecU, 0xac26e9f7U, 0xf5b5ca46U, 0xfe8aa518U);

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x0900890eU);
        WR1_PROG(REG_08H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_14H, 0x000003c1U);
        HW_SCE_p_func100(0x4dd8adefU, 0xb518cfa1U, 0x12669286U, 0x50b0d680U);

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

        HW_SCE_p_func101(0xa3743bffU, 0x616e8d2cU, 0x91b488f6U, 0x9464b7a2U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xfc2a2e62U, 0x69d664c1U, 0xad395df5U, 0x4b23da0cU);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x8db9f0d5U, 0x19326f36U, 0x5f0c15e8U, 0x80427851U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x4323e847U, 0x27b8654aU, 0x31cf7f97U, 0x7cce9ed1U);
    }
    else if (RD1_MASK(REG_44H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x8500ea92U, 0x77b723caU, 0x9e8734ffU, 0x595b20a1U);
    }
}
