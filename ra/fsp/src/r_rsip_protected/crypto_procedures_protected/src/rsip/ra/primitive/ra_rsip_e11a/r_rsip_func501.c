/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func501 (const uint32_t ARG1[], const uint32_t ARG2)
{
    uint32_t iLoop = 0U;

    r_rsip_func_sub005(0x000000a1U, 0x0c000104U, 0x00000000U);

    r_rsip_func_sub006(0x08000065U, 0x00410011U);

    r_rsip_func_sub005(0x000000a1U, 0x07000c04U, 0x00000000U);

    r_rsip_func_sub005(0x000000a1U, 0x08000054U, 0x00000000U);

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D0H, 0x0e108406U);

    for (iLoop = 0U; iLoop < ARG2; )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &ARG1[iLoop]);
        iLoop = iLoop + 4U;
    }

    r_rsip_func205();
}
