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

void r_rsip_func440 (const uint32_t ARG1[])
{
    WR1_PROG(REG_0094H, 0x00003467U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000440U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x560ceb2eU),
                   bswap_32big(0x9895a871U),
                   bswap_32big(0x41df56e2U),
                   bswap_32big(0xe14ba39aU));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x000034c5U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000440U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xd56db95cU),
                   bswap_32big(0x0a702a12U),
                   bswap_32big(0xc8e45a4cU),
                   bswap_32big(0xe9867d15U));
    r_rsip_func044();

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0xf7009d05U);
    WR4_ADDR(REG_002CH, &ARG1[1]);

    r_rsip_func_sub009(0x00000401U, 0x00c10009U, 0x00001800U);
    r_rsip_func_sub009(0x00000402U, 0x00c10009U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &ARG1[5]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    WR1_PROG(REG_0094H, 0x000034e3U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
