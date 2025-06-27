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
        r_rsip_func101(bswap_32big(0x22fffe54U), bswap_32big(0xce331a73U), bswap_32big(0xec89a231U),
                       bswap_32big(0xa35d2187U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0x640d12f1U), bswap_32big(0xc82e8211U), bswap_32big(0x971056f8U),
                       bswap_32big(0x2ae092a0U));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0x28303f8fU), bswap_32big(0xb847740cU), bswap_32big(0xc4087c24U),
                       bswap_32big(0xb87d83bfU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0x8702369cU), bswap_32big(0x14ca11d9U), bswap_32big(0x711d4b17U),
                       bswap_32big(0x8cbd9f7aU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0xc97f0452U), bswap_32big(0xe1a14155U), bswap_32big(0x24b9c679U),
                       bswap_32big(0x9ad67454U));
    }

    r_rsip_func102(bswap_32big(0xd9d315c0U),
                   bswap_32big(0x3823a756U),
                   bswap_32big(0xe033c8cdU),
                   bswap_32big(0xbeb093c7U));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
