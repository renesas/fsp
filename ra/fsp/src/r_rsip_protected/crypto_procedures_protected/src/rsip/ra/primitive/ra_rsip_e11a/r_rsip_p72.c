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

rsip_ret_t r_rsip_p72 (const uint32_t InData_InitVal[], const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0068H, 0x00000016U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00720001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F4H, 0x00000010U);

    WAIT_STS(REG_00F8H, 0, 1);

    WR1_PROG(REG_0014H, 0x000007c4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_ADDR(REG_002CH, &InData_InitVal[0]);

    WR1_PROG(REG_00F4H, 0x00000011U);

    WAIT_STS(REG_00F8H, 0, 1);

    WR1_PROG(REG_0014H, 0x00000064U);
    for (iLoop = 0U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &InData_PaddedMsg[iLoop]);
        iLoop = iLoop + 16U;
    }

    WAIT_STS(REG_00F8H, 2, 0);

    WR1_PROG(REG_0014H, 0x00000000U);

    WR1_PROG(REG_00F4H, 0x00000100U);

    WR1_PROG(REG_00F4H, 0x00000020U);

    WAIT_STS(REG_00F8H, 1, 1);

    r_rsip_func100(bswap_32big(0xd5c794efU), bswap_32big(0xce7c7a3eU), bswap_32big(0xc28e8f4dU), bswap_32big(0x0397efbaU));
    WR1_PROG(REG_0008H, 0x00004022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD8_ADDR(REG_002CH, &OutData_MsgDigest[0]);

    r_rsip_func102(bswap_32big(0x0ba55075U), bswap_32big(0x2f2be51dU), bswap_32big(0x2589c3e2U), bswap_32big(0x152821acU));
    WR1_PROG(REG_0068H, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
