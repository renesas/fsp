/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"
#include "hw_sce_p_sub_func.h"

void HW_SCE_p_func430 (const uint32_t ARG1[], const uint32_t ARG2)
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func_sub018(0x00008000U, 0x0e128456U);

    for (iLoop = 0U; iLoop < ARG2; )
    {
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &ARG1[iLoop]);
        iLoop = iLoop + 4U;
    }

    HW_SCE_p_func205_r1();
}
