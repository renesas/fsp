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

rsip_ret_t r_rsip_p47f (void)
{
    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func101(bswap_32big(0x7c1839bbU), bswap_32big(0xdb1964afU), bswap_32big(0x3b18725cU),
                       bswap_32big(0x0c30bfc8U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0x15622c79U), bswap_32big(0xad7a4026U), bswap_32big(0x6da71cb7U),
                       bswap_32big(0xdbfc6783U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0xa2326a27U), bswap_32big(0x0864d1d2U), bswap_32big(0x700d8ad2U),
                       bswap_32big(0xcef8c280U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0x386d4cfeU), bswap_32big(0xac6fd53aU), bswap_32big(0xd3eaf72fU),
                       bswap_32big(0xacbbbb20U));
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0xc1cfad39U), bswap_32big(0x54191ceeU), bswap_32big(0xb8d68cc6U),
                       bswap_32big(0x77a0a3ceU));
    }
    else
    {
        ;
    }

    r_rsip_func102(bswap_32big(0xf9c7aeceU),
                   bswap_32big(0xf05b2fb2U),
                   bswap_32big(0x46ea5307U),
                   bswap_32big(0x72377664U));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12, 0);

    return RSIP_RET_PASS;
}
