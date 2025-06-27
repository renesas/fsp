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

rsip_ret_t r_rsip_p89f (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func101(bswap_32big(0xf351fd8fU), bswap_32big(0x5df42a44U), bswap_32big(0x2093f6bdU),
                       bswap_32big(0xd54e3977U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0x23d0f905U), bswap_32big(0xec060a28U), bswap_32big(0xba8e4acfU),
                       bswap_32big(0xe5aad16cU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0xc0dddca4U), bswap_32big(0xd8384309U), bswap_32big(0x0718c944U),
                       bswap_32big(0x53e5c656U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0x7410d6eeU), bswap_32big(0xb7e6a471U), bswap_32big(0x6a718631U),
                       bswap_32big(0xb48c248dU));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0x8290ca26U), bswap_32big(0x1dbdd9aaU), bswap_32big(0x9388548dU),
                       bswap_32big(0x3532f2a8U));
    }
    else
    {
        ;
    }

    r_rsip_func102(bswap_32big(0xd97f89a3U),
                   bswap_32big(0xaa23577eU),
                   bswap_32big(0xd6bf1091U),
                   bswap_32big(0xbee3efcaU));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
