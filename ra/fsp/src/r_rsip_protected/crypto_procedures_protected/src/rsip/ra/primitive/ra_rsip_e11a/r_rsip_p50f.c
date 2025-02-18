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
    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func101(bswap_32big(0x05032ee4U), bswap_32big(0xea84d8d1U), bswap_32big(0xebb80140U), bswap_32big(0xeb01a1c8U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0x8234478cU), bswap_32big(0x2842eb0aU), bswap_32big(0xf549797bU), bswap_32big(0x85b6ca9eU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0xc6887182U), bswap_32big(0x56edd598U), bswap_32big(0xcc19d5deU), bswap_32big(0x87762a42U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0x687107b0U), bswap_32big(0xc5565ef9U), bswap_32big(0x74c47275U), bswap_32big(0x5f3f513dU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0x0c2c1563U), bswap_32big(0x682645dcU), bswap_32big(0x214351f6U), bswap_32big(0x1ef2d245U));
    }

    r_rsip_func102(bswap_32big(0xf7b7c4c8U), bswap_32big(0x8021a2d0U), bswap_32big(0xc3965693U), bswap_32big(0xdda1fcb2U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
