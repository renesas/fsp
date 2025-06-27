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

rsip_ret_t r_rsip_p21 (const uint32_t InData_HV[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Text[],
                       uint32_t       OutData_DataT[],
                       uint32_t       MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0068H, 0x00000016U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00210001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0xd3961764U),
                   bswap_32big(0x78402dabU),
                   bswap_32big(0xfc5c992aU),
                   bswap_32big(0x4eabf806U));
    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x080000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_HV[0]);
    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x08000055U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_IV[0]);

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D4H, 0x00008000U);
    WR1_PROG(REG_00D0H, 0x0e128456U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
    }

    r_rsip_func205();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c100104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    r_rsip_func100(bswap_32big(0x23ba16fdU),
                   bswap_32big(0x5b1bab0aU),
                   bswap_32big(0x5f44d5c3U),
                   bswap_32big(0x0435e745U));
    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_DataT[0]);

    r_rsip_func102(bswap_32big(0x2b2653dbU),
                   bswap_32big(0xefa81ddaU),
                   bswap_32big(0x16996a3aU),
                   bswap_32big(0xa5922dedU));
    WR1_PROG(REG_0068H, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
