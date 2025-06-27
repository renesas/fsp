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

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_p73s (uint32_t OutData_State[])
{
    uint32_t iLoop = 0U;

    for (iLoop = 0U; iLoop < 18U; iLoop++)
    {
        RD1_ADDR(REG_0114H, &OutData_State[iLoop]);
    }

    RD1_ADDR(REG_0104H, &OutData_State[18]);
    RD1_ADDR(REG_0100H, &OutData_State[19]);

    r_rsip_func102(bswap_32big(0xc14ab5ffU),
                   bswap_32big(0x9303c0faU),
                   bswap_32big(0x9cafdb76U),
                   bswap_32big(0x69300ffaU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
