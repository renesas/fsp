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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func402 (void)
{
    r_rsip_func_sub016(0x38000c00U, 0x00000080U, 0x00270000U);

    r_rsip_func100(bswap_32big(0xae5154c3U),
                   bswap_32big(0xcda4ccd9U),
                   bswap_32big(0x3059a9a6U),
                   bswap_32big(0xd7336d49U));
    WR1_PROG(REG_0040H, 0x00400000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        r_rsip_func_sub001(0x0087008cU, 0x00730000U, 0x0404000aU);

        r_rsip_func_sub001(0x00870091U, 0x00780000U, 0x0404000aU);

        r_rsip_func_sub001(0x00870096U, 0x007d0000U, 0x0404000aU);

        r_rsip_func101(bswap_32big(0x24bc1cebU), bswap_32big(0xa0007d96U), bswap_32big(0x65c3ff78U),
                       bswap_32big(0x8764a127U));
    }
    else
    {
        r_rsip_func_sub001(0x00870046U, 0x00730000U, 0x0404000aU);

        r_rsip_func_sub001(0x0087004bU, 0x00780000U, 0x0404000aU);

        r_rsip_func_sub001(0x00870050U, 0x007d0000U, 0x0404000aU);

        r_rsip_func101(bswap_32big(0xe419fce0U), bswap_32big(0xc48c44c3U), bswap_32big(0xc28ddc28U),
                       bswap_32big(0xc2469ab5U));
    }

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
