/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_GhashSub (const uint32_t InData_HV[],
                           const uint32_t InData_IV[],
                           const uint32_t InData_Text[],
                           uint32_t       OutData_DataT[],
                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_68H, 0x00000016U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00210001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func100(0x9a60b099U, 0xc2c6d059U, 0x07528517U, 0x9b76f3b3U);
    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x080000a5U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_HV[0]);
    WR1_PROG(REG_14H, 0x000003c1U);
    WR1_PROG(REG_D0H, 0x08000055U);
    WAIT_STS(REG_14H, 31, 1);
    WR4_ADDR(REG_2CH, &InData_IV[0]);

    WR1_PROG(REG_14H, 0x00020061U);
    WR1_PROG(REG_D4H, 0x00008000U);
    WR1_PROG(REG_D0H, 0x0e128456U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205_r1();

    WR1_PROG(REG_14H, 0x000000a1U);
    WR1_PROG(REG_D0H, 0x0c100104U);
    WAIT_STS(REG_14H, 31, 1);
    WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xef3b40c4U, 0x3abdff90U, 0x94d7da1fU, 0xe43630cfU);
    WR1_PROG(REG_08H, 0x00001012U);
    WAIT_STS(REG_08H, 30, 1);
    RD4_ADDR(REG_2CH, &OutData_DataT[0]);

    HW_SCE_p_func102(0x56624e05U, 0xf357e2c7U, 0x98236fcaU, 0x4e06fbbcU);
    WR1_PROG(REG_68H, 0x00000040U);
    WAIT_STS(REG_20H, 12, 0);

    return FSP_SUCCESS;
}
