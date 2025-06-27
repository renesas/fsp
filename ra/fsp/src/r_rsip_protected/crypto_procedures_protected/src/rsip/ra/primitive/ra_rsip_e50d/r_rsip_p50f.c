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

rsip_ret_t r_rsip_p50f (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func101(bswap_32big(0x51918b25U), bswap_32big(0x21cb2e29U), bswap_32big(0x5e8bb2eaU),
                       bswap_32big(0xa9e46fccU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0x514cac3bU), bswap_32big(0x8d94dd1fU), bswap_32big(0x0fe693a1U),
                       bswap_32big(0xce7152ceU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0xa25522a4U), bswap_32big(0x803beb1fU), bswap_32big(0xbf2c1e3bU),
                       bswap_32big(0xe7efe428U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0xaef7b372U), bswap_32big(0x944d935bU), bswap_32big(0xed52892bU),
                       bswap_32big(0xe0d2eb96U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0xa8e06244U), bswap_32big(0x868e7c5fU), bswap_32big(0x9888fdedU),
                       bswap_32big(0x25ab8c6eU));
    }

    r_rsip_func102(bswap_32big(0x4380f41aU),
                   bswap_32big(0x6029e898U),
                   bswap_32big(0x61ae0705U),
                   bswap_32big(0xe7be0026U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
