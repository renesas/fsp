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

void r_rsip_func441 (const uint32_t ARG1[])
{
    WR1_PROG(REG_0094H, 0x00003467U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000441U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xdd165f6bU),
                   bswap_32big(0x55769a38U),
                   bswap_32big(0x20156a64U),
                   bswap_32big(0xe455b52eU));
    r_rsip_func143();

    WR1_PROG(REG_0094H, 0x000034c5U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x00000441U, 0x00000000U);

    r_rsip_func101(bswap_32big(0x41d33946U),
                   bswap_32big(0xb0bdb099U),
                   bswap_32big(0xb7a8aeeeU),
                   bswap_32big(0x48ab9a08U));
    r_rsip_func044();

    r_rsip_func_sub011(0x000007c1U, 0x40000100U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &ARG1[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[5]);

    r_rsip_func_sub009(0x0000141eU, 0x00c10021U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &ARG1[9]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    WR1_PROG(REG_0094H, 0x000034e3U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
