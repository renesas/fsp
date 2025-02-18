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

rsip_ret_t r_rsip_p20 (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00200002U);
    WR1_PROG(REG_004CH, 0x00000000U);

    r_rsip_func100(bswap_32big(0x466e169dU), bswap_32big(0x6ba86c1cU), bswap_32big(0x1116394cU), bswap_32big(0xe151d83fU));
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x39771fcfU), bswap_32big(0xf5bbe206U), bswap_32big(0x94229b14U), bswap_32big(0xc57e8e42U));
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, bswap_32big(0x00000000U));

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[0]);

    r_rsip_func102(bswap_32big(0x033f3f05U), bswap_32big(0xea4f993bU), bswap_32big(0x4c346526U), bswap_32big(0x9be4e224U));

    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
