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

void r_rsip_func044 (void)
{
    r_rsip_func_sub022(0x00008cc0U, 0x00ffffffU, 0x000090c0U);
    WR1_PROG(REG_0094H, 0x01000000U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009104U);
    r_rsip_func_sub006(0x810100c0U, 0x00490005U, 0x00008cc0U, 0x00ffffffU);
    WR1_PROG(REG_0094H, 0x000090c0U);
    WR1_PROG(REG_0094H, 0x02000000U);

    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x30009044U);
    r_rsip_func_sub012(0x810100c0U, 0x00490005U);

    r_rsip_func100(bswap_32big(0x49d91db0U),
                   bswap_32big(0x73036ed5U),
                   bswap_32big(0x433b4d64U),
                   bswap_32big(0xc97f833fU));
    r_rsip_func_sub013(0x08000085U, 0x00410011U);

    r_rsip_func100(bswap_32big(0x9bd099f4U),
                   bswap_32big(0x7aca702eU),
                   bswap_32big(0xe16e6048U),
                   bswap_32big(0x1f661610U));
    r_rsip_func_sub008(0x000000a1U, 0x0c000094U, 0x00000000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
