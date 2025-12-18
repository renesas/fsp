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

void r_rsip_func407 (const uint32_t ARG1[])
{
    WR1_PROG(REG_0094H, 0x00003407U);

    r_rsip_func_sub014(0x000000c7U, 0x800100c0U);
    WR1_PROG(REG_002CH, ARG1[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f407U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xb6b6ed97U),
                   bswap_32big(0xda99e9e8U),
                   bswap_32big(0x0fceae70U),
                   bswap_32big(0xb9d0b7bdU));
    r_rsip_func043();

    WR1_PROG(REG_0094H, 0x0000b4c0U);
    WR1_PROG(REG_0094H, 0x015c5d71U);

    r_rsip_func_sub002(0x000000a7U, 0x800100e0U, 0x0000f407U, 0x00000000U);

    r_rsip_func101(bswap_32big(0xaa915973U),
                   bswap_32big(0x21e8ad34U),
                   bswap_32big(0x468c23e7U),
                   bswap_32big(0xa6655b2cU));
    r_rsip_func044();

    r_rsip_func_sub008(0x000000a1U, 0x08000044U, 0x00000000U);
    r_rsip_func_sub008(0x000000a1U, 0x08000054U, 0x00000000U);

    r_rsip_func_sub011(0x000007c1U, 0x40000100U, 0xf7009d07U);
    WR4_ADDR(REG_002CH, &ARG1[1]);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &ARG1[5]);

    r_rsip_func_sub009(0x00001404U, 0x00c10021U, 0x00001800U);

    r_rsip_func_sub011(0x000003c1U, 0x40000000U, 0x07008d05U);
    WR4_ADDR(REG_002CH, &ARG1[9]);

    r_rsip_func_sub013(0x9c100005U, 0x00410011U);

    WR1_PROG(REG_0094H, 0x000034e0U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
}
