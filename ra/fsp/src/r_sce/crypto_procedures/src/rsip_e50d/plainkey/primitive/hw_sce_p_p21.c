/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

    if (RD1_MASK(REG_14BCH, 0x0000001fU) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    else
    {
        ;
    }

    WR1_PROG(REG_1B00H, 0x00210001U);
    WR1_PROG(REG_144CH, 0x00000000U);

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_182CH, 0x00070000U);
    WR1_PROG(REG_1824H, 0x08008005U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_HV[0]);

    WR1_PROG(REG_1444H, 0x000003c1U);
    WR1_PROG(REG_1824H, 0x08000025U);
    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_IV[0]);

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00018000U);
    WR1_PROG(REG_1824H, 0x0a058006U);

    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func216();

    HW_SCE_p_func100(0x12a89875U, 0x2f76a7d8U, 0xcb51754bU, 0x7cff2dccU);
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_182CH, 0x00400000U);
    WR1_PROG(REG_1824H, 0x0c008104U);
    WAIT_STS(REG_1444H, 31, 1);
    WR1_PROG(REG_1420H, change_endian_long(0x00000000U));

    WR1_PROG(REG_1408H, 0x00001012U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_DataT[0]);

    HW_SCE_p_func102(0xf56e0086U, 0x71517d6dU, 0x01c7a7d6U, 0xc1c2166cU);
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return FSP_SUCCESS;
}

