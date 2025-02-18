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
    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        r_rsip_func101(bswap_32big(0xe090f1d4U), bswap_32big(0xe1802813U), bswap_32big(0xd3e31c98U), bswap_32big(0xd97410faU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        r_rsip_func101(bswap_32big(0xd5e9105eU), bswap_32big(0x551f4bb8U), bswap_32big(0x3efdc9a2U), bswap_32big(0xd35faf8fU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        r_rsip_func101(bswap_32big(0x5a8d8ef7U), bswap_32big(0x283e451fU), bswap_32big(0x7bbf788cU), bswap_32big(0x1794ffbeU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        r_rsip_func101(bswap_32big(0xd7c10828U), bswap_32big(0x7e7e321cU), bswap_32big(0x7fdc79a9U), bswap_32big(0xa3ee6f1aU));
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        r_rsip_func101(bswap_32big(0x3fda842fU), bswap_32big(0x8002d55eU), bswap_32big(0x5c3d43e6U), bswap_32big(0xafeb22b4U));
    }

    r_rsip_func102(bswap_32big(0x6350e1bdU), bswap_32big(0x0e8abd5fU), bswap_32big(0xdc69a596U), bswap_32big(0x5ed024ddU));
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return RSIP_RET_PASS;
}
